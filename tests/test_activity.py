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

    def test_explicit_joint_credit_counts_once_per_person(self):
        self.entry['contributors'].append('bob')
        self.assertEqual([(c['login'],c['functions']) for c in self.credits()],[('alice',1),('bob',1)])

    def test_duplicate_function_credit_fails(self):
        self.ledger['entries'].append(copy.deepcopy(self.entry))
        with self.assertRaisesRegex(ValueError,'more than once'):self.credits()

    def test_new_functions_require_explicit_attribution(self):
        self.build['units'][0]['functions'].append({'address':'0x80000004'})
        with self.assertRaisesRegex(ValueError,'Unattributed compiled function'):self.credits()

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


class LiveReceiptTests(unittest.TestCase):
    def test_activity_rejects_stale_receipts_and_mismatched_linked_counts(self):
        root=activity.ROOT;report=root/'build/source/report.json';site_path=root/'build/site/progress.json'
        if not report.exists() or not site_path.exists():
            self.skipTest('Integration export step supplies the verified build and public map')
        site=json.loads(site_path.read_text());build=json.loads(report.read_text())
        activity.export(root,site,report)
        mutations=[]
        stale=copy.deepcopy(build);stale['manifest_sha256']='0'*64;mutations.append(stale)
        stale=copy.deepcopy(build);stale['tools']={};mutations.append(stale)
        stale=copy.deepcopy(build);stale['units'][0]['functions'].pop();mutations.append(stale)
        stale=copy.deepcopy(build);stale['units'][0]['source_sha256']='0'*64;mutations.append(stale)
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'report.json';(path.parent/'main.dol').symlink_to(report.parent/'main.dol')
            for stale in mutations:
                path.write_text(json.dumps(stale))
                with self.subTest(stale=stale.keys()),self.assertRaises(ValueError):
                    activity.export(root,site,path)
        bad=copy.deepcopy(site);bad['measures']['code']['linked']+=1
        with self.assertRaisesRegex(ValueError,'measurements differ'):
            activity.export(root,bad,report)
        branch_site=copy.deepcopy(site);branch_site['revision']='0'*40
        with self.assertRaises(ValueError):
            activity.export(root,branch_site,report,previous=json.loads((root/'config/GN7E69/history.json').read_text()),append=True)


if __name__=='__main__':unittest.main()
