import copy
import json
import io
import tarfile
import zipfile
from unittest.mock import patch
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import activity
import restore_history
import progress
import check_progress_maps
import test_export_progress


class HistoryTests(unittest.TestCase):
    def row(self, revision='a'*40, linked=10):
        return {'revision':revision,'built_at':'2026-10-03T10:00:00Z',
                'code':{'linked':linked,'total':100}, 'data':{'linked':20,'total':200},
                'provenance':{'kind':'workflow-artifact','run':1,'artifact':2,'report_sha256':'b'*64}}

    def document(self, rows):
        return {'schema':1,'target':'GN7E69','target_sha1':'c'*40,'snapshots':rows}

    def test_history_merges_seed_previous_and_current_without_duplicate_reruns(self):
        first=self.row();repeat=copy.deepcopy(first);repeat['built_at']='2026-10-03T11:00:00Z'
        next_row=self.row('d'*40,15);next_row['built_at']='2026-10-03T12:00:00Z'
        current=self.row('e'*40,18);current['built_at']='2026-10-03T13:00:00Z'
        result=activity.merge_history(self.document([first]),self.document([repeat,next_row]),current)
        self.assertEqual(result,[first,next_row,current])
        self.assertEqual(activity.merge_history(self.document(result),None,current),result)

    def test_conflicting_measurement_of_one_revision_fails(self):
        with self.assertRaisesRegex(ValueError,'conflicting'):
            activity.merge_history(self.document([self.row()]),self.document([self.row(linked=11)]))

    def test_foreign_target_duplicate_revision_invalid_scores_or_unverified_history_fail(self):
        mutations=[]
        data=self.document([self.row()]);data['target_sha1']='wrong';mutations.append(data)
        mutations.append(self.document([self.row(),self.row()]))
        data=self.document([self.row()]);data['snapshots'][0]['code']['linked']=101;mutations.append(data)
        data=self.document([self.row()]);data['snapshots'][0]['code']['linked']=True;mutations.append(data)
        data=self.document([self.row()]);data['snapshots'][0]['provenance']={};mutations.append(data)
        data=self.document([self.row()]);data['snapshots'][0]['built_at']='2026-10-03T10:00:00';mutations.append(data)
        for data in mutations:
            with self.subTest(data=data),self.assertRaises(ValueError):
                activity.validate_history(data,'c'*40)


@unittest.skipUnless(shutil.which("git"), "Git provenance tests run on the CI host")
class ContributorTests(unittest.TestCase):
    def setUp(self):
        activity.clear_cache()
        self.directory=tempfile.TemporaryDirectory();self.addCleanup(self.directory.cleanup)
        self.root=Path(self.directory.name);(self.root/'src').mkdir()
        (self.root/'src/test.c').write_text('int function(void) { return 1; }')
        def git(*args):
            return subprocess.check_output(['git',*args],cwd=self.root,stderr=subprocess.DEVNULL,text=True).strip()
        git('init','-q');git('add','src/test.c')
        git('-c','user.name=Test','-c','user.email=test@example.invalid','commit','-qm','Source contribution')
        self.commit=git('rev-parse','HEAD');self.blob=git('rev-parse','HEAD:src/test.c')
        self.entry={'source':'src/test.c','contributors':['alice'],'functions':['0x80000000'],
                    'provenance':{'pull_request':1,'merged_via':2,'commit':self.commit,'introduced_blob':self.blob}}
        self.ledger={'schema':1,'target':'GN7E69','contributors':{'alice':{'id':1},'bob':{'id':2}},'entries':[self.entry]}
        self.build={'complete':'identical','units':[{'source':'src/test.c','functions':[{'address':'0x80000000'}]}]}

    def credits(self):
        return activity.contributors(self.root,self.ledger,self.build,self.commit)

    def test_original_contributor_gets_function_credit_not_merger(self):
        self.assertEqual(self.credits(),[{'login':'alice','id':1,'functions':1,'pull_requests':[1]}])

    def test_exact_unlinked_credit_survives_promotion_and_retires_after_regression(self):
        self.entry['functions'].append('0x80000004')
        exact = {('src/test.c', '0x80000000'), ('src/test.c', '0x80000004')}
        result = activity.contributors(self.root, self.ledger, self.build, self.commit, exact_inventory=exact)
        self.assertEqual(result[0]['functions'], 2)
        self.build['units'][0]['functions'].append({'address':'0x80000004'})
        self.assertEqual(activity.contributors(self.root, self.ledger, self.build, self.commit,
                         exact_inventory=exact), result)
        self.build['units'][0]['functions'].pop()
        self.assertEqual(activity.contributors(self.root, self.ledger, self.build, self.commit,
                         exact_inventory={('src/test.c', '0x80000000')})[0]['functions'], 1)

    def test_exact_unlinked_function_requires_original_attribution(self):
        with self.assertRaisesRegex(ValueError, 'Unattributed exact function'):
            activity.contributors(self.root, self.ledger, self.build, self.commit,
                exact_inventory={('src/test.c', '0x80000000'), ('src/test.c', '0x80000004')})

    def test_explicit_joint_credit_counts_once_per_person(self):
        self.entry['contributors'].append('bob')
        self.assertEqual([(c['login'],c['functions']) for c in self.credits()],[('alice',1),('bob',1)])

    def test_duplicate_function_credit_fails(self):
        self.ledger['entries'].append(copy.deepcopy(self.entry))
        with self.assertRaisesRegex(ValueError,'more than once'):self.credits()

    def test_new_functions_require_explicit_attribution(self):
        self.build['units'][0]['functions'].append({'address':'0x80000004'})
        with self.assertRaisesRegex(ValueError,'Unattributed exact function'):self.credits()

    def test_retired_function_does_not_keep_rank_credit(self):
        self.entry['functions'].append('0x80000004')
        self.assertEqual(self.credits()[0]['functions'],1)

    def test_foreign_or_changed_provenance_fails(self):
        self.entry['provenance']['introduced_blob']='a'*40
        with self.assertRaisesRegex(ValueError,'introduced source'):self.credits()
        self.entry['provenance']['introduced_blob']=self.blob
        self.entry['provenance']['commit']='b'*40
        with self.assertRaisesRegex(ValueError,'unavailable'):self.credits()

    def git(self, *args, text=None):
        return subprocess.check_output(['git',*args],cwd=self.root,input=text,text=True,
                                       stderr=subprocess.DEVNULL).strip()

    def commit_source(self, content):
        (self.root/'src/test.c').write_text(content)
        self.git('add','src/test.c')
        self.git('-c','user.name=Test','-c','user.email=test@example.invalid','commit','-qm','Integration')
        return self.git('rev-parse','HEAD')

    def test_squash_preserves_original_credit_with_dual_source_proof(self):
        original=self.commit
        tree=self.git('rev-parse',original+'^{tree}')
        self.commit=self.git('-c','user.name=Test','-c','user.email=test@example.invalid',
                             'commit-tree',tree,text='Independent squash root\n')
        self.assertNotEqual(original,self.commit)
        self.assertEqual(self.credits()[0]['login'],'alice')

    def test_foreign_source_commit_without_historical_blob_fails(self):
        foreign=self.commit_source('int function(void) { return 2; }')
        self.entry['provenance'].update(commit=foreign,introduced_blob=self.git('rev-parse',foreign+':src/test.c'))
        with self.assertRaisesRegex(ValueError,'absent from this revision history'):self.credits()

    def test_integration_source_changes_require_explanation_and_original_proof(self):
        original=self.commit
        integrated=self.commit_source('int function(void) { return 2; }')
        q=self.entry['provenance'];q.update(commit=integrated,original_blob=self.blob,
                                         introduced_blob=self.git('rev-parse',integrated+':src/test.c'))
        self.commit=integrated
        with self.assertRaisesRegex(ValueError,'Unexplained'):self.credits()
        q['integration_adjustment']='Shared declaration reconciled; original function preserved.'
        with self.assertRaisesRegex(ValueError,'original source'):self.credits()
        q['original_commit']=original
        self.assertEqual(self.credits()[0]['functions'],1)
        q['original_blob']='a'*40
        with self.assertRaisesRegex(ValueError,'original source'):self.credits()

    def test_historical_introduction_survives_later_source_changes(self):
        self.commit=self.commit_source('int function(void) { return 3; }')
        self.assertEqual(self.credits()[0]['functions'],1)

    def test_historical_lookup_batches_deleted_and_restored_paths(self):
        self.git('rm', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Delete source')
        (self.root/'src').mkdir(exist_ok=True)
        revision = self.commit_source('int function(void) { return 3; }')
        real_run = activity.subprocess.run
        with patch.object(activity.subprocess, 'run', wraps=real_run) as run:
            self.assertTrue(activity.historical_source_blob(self.root, revision, 'src/test.c', self.blob))
        queries = [call for call in run.call_args_list if call.args[0][:2] == ['git', 'cat-file']]
        self.assertEqual(len(queries), 1)
        self.assertFalse(activity.historical_source_blob(self.root, revision, 'src/test.c', 'a' * 40))
        self.assertFalse(activity.historical_source_blob(self.root, revision, 'src/absent.c', self.blob))

    def test_historical_lookup_rejects_protocol_injection_and_invalid_responses(self):
        for source in ('src/a\n' + self.blob, 'src/a\r', 'src/a\0'):
            with self.subTest(source=source), self.assertRaisesRegex(ValueError, 'source path'):
                activity.historical_source_blob(self.root, self.commit, source, self.blob)
        for output in ('', self.blob + '\n' + self.blob + '\n', 'wrong missing\n', 'invalid\n'):
            with patch.object(activity.subprocess, 'check_output', return_value=self.commit + '\n'), \
                    patch.object(activity.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, output)), \
                    self.subTest(output=output), self.assertRaisesRegex(ValueError, 'response'):
                activity.historical_source_blob(self.root, self.commit, 'src/test.c', self.blob)

    def test_fetch_is_explicit_pinned_same_origin_and_fail_closed(self):
        missing='b'*40
        with patch.object(activity.subprocess,'run',return_value=subprocess.CompletedProcess([],1)) as run:
            with self.assertRaisesRegex(ValueError,'unavailable'):
                activity.provenance_commit(self.root,missing)
            self.assertFalse(any(call.args[0][1]=='fetch' for call in run.call_args_list))
            with self.assertRaisesRegex(ValueError,'unavailable'):
                activity.provenance_commit(self.root,missing,True)
            self.assertIn(['git','fetch','--no-tags','origin',missing],
                          [call.args[0] for call in run.call_args_list])

    def test_opt_in_fetches_missing_original_commit_from_real_origin(self):
        tree=self.git('rev-parse',self.commit+'^{tree}')
        squash=self.git('-c','user.name=Test','-c','user.email=test@example.invalid',
                        'commit-tree',tree,text='Squashed source\n')
        self.git('update-ref','refs/heads/squashed',squash)
        with tempfile.TemporaryDirectory() as directory:
            checkout=Path(directory)/'clone'
            subprocess.run(['git','clone','--quiet','--no-local','--single-branch','--branch','squashed',
                            str(self.root),str(checkout)],check=True,stderr=subprocess.DEVNULL)
            with self.assertRaisesRegex(ValueError,'unavailable'):
                activity.contributors(checkout,self.ledger,self.build,squash)
            result=activity.contributors(checkout,self.ledger,self.build,squash,fetch_missing=True)
            self.assertEqual(result[0]['login'],'alice')
            self.assertEqual(subprocess.check_output(['git','remote','get-url','origin'],cwd=checkout,
                             text=True).strip(),str(self.root))

    def test_squash_preflight_rejects_branch_only_old_blob_until_corrected(self):
        def commit(tree, parent, message):
            args=['-c','user.name=Test','-c','user.email=test@example.invalid','commit-tree',tree]
            if parent:args += ['-p',parent]
            return self.git(*args,text=message+'\n')
        empty=commit(self.git('mktree',text=''),None,'Actual base')
        original=commit(self.git('rev-parse',self.commit+'^{tree}'),empty,'Original source')
        changed=self.commit_source('int function(void) { return 2; }')
        revision=commit(self.git('rev-parse',changed+'^{tree}'),original,'Reviewed correction')
        self.entry['provenance']['commit']=original
        self.assertEqual(activity.contributors(self.root,self.ledger,self.build,revision)[0]['functions'],1)
        with self.assertRaisesRegex(ValueError,'absent from this revision history'):
            activity.squash_preflight(self.root,self.ledger,self.build,revision,empty)
        self.entry['provenance'].update(
            original_commit=original,original_blob=self.blob,commit=revision,
            introduced_blob=self.git('rev-parse',revision+':src/test.c'),
            integration_adjustment='Reviewed correction retained in the final source.')
        self.assertEqual(activity.squash_preflight(self.root,self.ledger,self.build,revision,empty)[0]['login'],'alice')

    def test_unverified_build_cannot_supply_function_credit(self):
        self.build['complete']='mismatch'
        with self.assertRaisesRegex(ValueError,'verified source build'):self.credits()



class RestoreTests(unittest.TestCase):
    def archive(self, document=None):
        tar_bytes=io.BytesIO()
        with tarfile.open(fileobj=tar_bytes,mode='w') as tar:
            if document is not None:
                content=json.dumps(document).encode();entry=tarfile.TarInfo('./activity.json');entry.size=len(content)
                tar.addfile(entry,io.BytesIO(content))
        zipped=io.BytesIO()
        with zipfile.ZipFile(zipped,'w') as archive:archive.writestr('artifact.tar',tar_bytes.getvalue())
        return zipped.getvalue()

    def setup_api(self, seed, deployed, archived, expired=False):
        responses={
            'deployments?environment=github-pages&per_page=100':[{'id':1,'sha':deployed}],
            'deployments/1/statuses':[{'state':'success','created_at':'2026-10-03T12:00:00Z',
               'log_url':'https://github.com/mitsevox/nflstreet2/actions/runs/10/job/20'}],
            'actions/runs/10':{'head_sha':deployed,'head_branch':'main','event':'push','path':'.github/workflows/baseline.yml'},
            'actions/runs/10/artifacts?per_page=100':{'artifacts':[{'id':2,'name':'github-pages','expired':expired,'created_at':'2026-10-03T11:00:00Z'}]}}
        def api(path):
            if path=='actions/artifacts/2/zip':return self.archive(archived)
            return json.dumps(responses[path]).encode()
        return patch.object(restore_history,'api',side_effect=api)

    def test_bootstrap_only_from_audited_pre_feature_deployment(self):
        seed=HistoryTests().document([HistoryTests().row()])
        with self.setup_api(seed,'a'*40,None):
            result,receipt=restore_history.restore(seed)
            self.assertEqual(result,seed);self.assertEqual(receipt['run'],10)
        with self.setup_api(seed,'d'*40,None),self.assertRaisesRegex(ValueError,'outside the audited'):
            restore_history.restore(seed)

    def test_restores_deployed_history_and_rejects_stale_or_missing_artifacts(self):
        seed=HistoryTests().document([HistoryTests().row()])
        archived=HistoryTests().document([HistoryTests().row(),HistoryTests().row('d'*40)])
        archived['revision']='d'*40
        with self.setup_api(seed,'d'*40,archived):
            result,_=restore_history.restore(seed);self.assertEqual(result,archived)
        archived['revision']='a'*40
        with self.setup_api(seed,'d'*40,archived),self.assertRaisesRegex(ValueError,'differs from its published'):
            restore_history.restore(seed)
        with self.setup_api(seed,'d'*40,archived,expired=True),self.assertRaisesRegex(ValueError,'unavailable'):
            restore_history.restore(seed)

    def test_no_successful_deployment_is_not_silent_bootstrap(self):
        with self.assertRaisesRegex(ValueError,'No successful'):
            restore_history.published_run([{'id':1}],lambda n:[{'state':'failure'}])


class ExactInventoryTests(unittest.TestCase):
    def site(self):
        def function(address, matched, linked):
            return {'type':'function', 'source':'src/test.c', 'function_address':address,
                    'size':4, 'original_size':4, 'matched':matched, 'linked':linked}
        return {'functions':{'exact':2}, 'files':[{'children':[
            function('0x80000000',4,4), function('0x80000004',4,0),
            function('0x80000008',3,0)]}]}

    def test_counts_exact_linked_and_unlinked_but_not_fuzzy(self):
        self.assertEqual(activity.exact_functions(self.site()),
                         {('src/test.c','0x80000000'),('src/test.c','0x80000004')})

    def test_candidate_without_owned_source_uses_verified_comparison_source(self):
        site=self.site();leaf=site['files'][0]['children'][1]
        del leaf['source'];leaf['comparison_source']='src/test.c'
        self.assertIn(('src/test.c','0x80000004'), activity.exact_functions(site))
        del leaf['comparison_source']
        with self.assertRaisesRegex(ValueError, 'count differs'):
            activity.exact_functions(site)

    def test_missing_duplicate_or_fragment_identity_fails_reconciliation(self):
        for mode in ('count', 'duplicate', 'fragment'):
            site=self.site()
            if mode=='count':site['functions']['exact']+=1
            elif mode=='duplicate':site['files'][0]['children'].append(copy.deepcopy(site['files'][0]['children'][0]))
            else:site['files'][0]['children'][1]['type']='function-fragment'
            with self.subTest(mode=mode), self.assertRaises(ValueError):
                activity.exact_functions(site)


class ReceiptRejectionTests(test_export_progress.ReceiptFixture):
    def setUp(self):
        super().setUp()
        self.site = progress.report(self.binary, self.revision, self.report_path, self.analysis)

    def export(self, site=None, **options):
        return activity.export(self.root, self.site if site is None else site,
                               self.report_path, **options)

    def test_bound_receipt_supplies_real_credit(self):
        result = self.export()
        self.assertEqual(result['credited_functions'], 1)
        self.assertEqual(result['contributors'][0]['login'], 'alice')

    def test_stale_manifest_is_rejected(self):
        self.source_report['manifest_sha256'] = '0'*64; self.save()
        with self.assertRaisesRegex(ValueError, 'different unit manifest'):
            self.export()

    def test_changed_build_tools_are_rejected(self):
        self.source_report['tools'] = {}; self.save()
        with self.assertRaisesRegex(ValueError, 'different build tooling'):
            self.export()

    def test_missing_compiler_function_is_rejected(self):
        self.source_report['units'][0]['functions'].pop(); self.save()
        with self.assertRaisesRegex(ValueError, 'lacks compiler function coverage'):
            self.export()

    def test_omitting_one_of_two_compiler_functions_is_rejected(self):
        rows = self.source_report['units'][0]['functions']
        rows[0]['size'] = 4
        rows.append({'symbol':'fn_80003108', 'address':'0x80003108', 'size':4})
        self.save()
        symbols = self.analysis/'symbols.txt'
        symbols.write_text('fn_80003104 = .text:0x80003104; // type:function size:0x4\n'
                           'fn_80003108 = .text:0x80003108; // type:function size:0x4\n'
                           'fn_8000310C = .text:0x8000310C; // type:function size:0x4\n')
        summary_path = self.analysis/'summary.json'
        summary = json.loads(summary_path.read_text())
        summary['candidate_counts']['function'] = 3
        summary['symbols_sha256'] = progress.digest(symbols)
        summary_path.write_text(json.dumps(summary))
        evidence = self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text().replace(
            'function\t0x80003104\t0x8000310C', 'function\t0x80003104\t0x80003108') +
            'function\t0x80003108\t0x8000310C\tfn_80003108\ttarget\texact\texact\tfixture\n')
        self.ledger['entries'][0]['functions'].append('0x80003108')
        self.ledger_path.write_text(json.dumps(self.ledger))
        self.site = progress.report(self.binary, self.revision, self.report_path, self.analysis)
        self.assertEqual(self.export()['credited_functions'], 2)
        # Leave a valid function in the code extent: this must reject missing coverage,
        # rather than merely reject an empty inventory.
        rows.pop(); self.save()
        with self.assertRaisesRegex(ValueError, 'Compiler function receipt differs'):
            self.export()

    def test_stale_source_hash_is_rejected(self):
        self.source_report['units'][0]['source_sha256'] = '0'*64; self.save()
        with self.assertRaisesRegex(ValueError, 'stale for src/unit.c'):
            self.export()

    def test_forged_linked_exact_and_fuzzy_counts_are_rejected(self):
        for mode in ('linked', 'exact', 'fuzzy'):
            bad = copy.deepcopy(self.site)
            if mode == 'exact':
                bad['functions']['exact'] += 1
            else:
                bad['measures']['code'][mode] = bad['measures']['code'].get(mode, 0) + 1
            with self.subTest(mode=mode), self.assertRaisesRegex(ValueError, 'measurements differ'):
                self.export(bad)

    def test_foreign_revision_cannot_append_history(self):
        bad = copy.deepcopy(self.site); bad['revision'] = '0'*40
        previous = json.loads((self.root/'config/GN7E69/history.json').read_text())
        with self.assertRaisesRegex(ValueError, 'outside this revision history'):
            self.export(bad, previous=previous, append=True)


class LiveReceiptTests(unittest.TestCase):
    def test_real_build_reconciles_maps_and_exact_function_credit(self):
        root = activity.ROOT
        report = root/'build/source/report.json'
        site_path = root/'build/site/progress.json'
        if not report.exists() or not site_path.exists():
            self.skipTest('Integration export step supplies the verified build and public map')
        site = json.loads(site_path.read_text())
        # Validate the actual receipts and inventory once; corruption cases use bound fixtures.
        result = activity.export(root, site, report)
        published = json.loads((site_path.parent/'activity.json').read_text())
        decomp = json.loads((root/'build/GN7E69/report.json').read_text())
        check_progress_maps.verify(root, site, decomp, json.loads(report.read_text())['units'], site)
        self.assertEqual(result['revision'], site['revision'])
        self.assertEqual(result['credited_functions'], site['functions']['exact'])
        self.assertEqual(result['contributors'], published['contributors'])
        self.assertEqual(result['credited_functions'], published['credited_functions'])


if __name__=='__main__':unittest.main()
