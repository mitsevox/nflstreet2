import copy
import json
import os
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
import report_v1
import progress
import check_progress_maps
import matching
import test_export_progress


class HistoryTests(unittest.TestCase):
    def row(self, revision='a'*40, linked=10):
        return {'revision':revision,'built_at':'2026-10-03T10:00:00Z',
                'code':{'linked':linked,'total':100}, 'data':{'linked':20,'total':200},
                'provenance':{'kind':'workflow-artifact','run':1,'artifact':2,'report_sha256':'b'*64}}

    def document(self, rows):
        return {'schema':1,'target':'GN7E69-rev0','target_sha1':'c'*40,'snapshots':rows}

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
        self.ledger={'schema':1,'target':'GN7E69-rev0','contributors':{'alice':{'id':1},'bob':{'id':2}},'entries':[self.entry]}
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

    def test_tree_lookup_answers_exactly_like_batch_check(self):
        (self.root/'top.c').write_text('int top;')
        (self.root/'src/deep').mkdir()
        (self.root/'src/deep/inner.c').write_text('int inner;')
        self.git('add','top.c','src/deep/inner.c')
        head=self.commit_source('int function(void) { return 4; }')
        queries=[f'{revision}:{path}' for revision in (head, head+'^', self.commit, 'c'*40)
                 for path in ('src/test.c','top.c','src/deep/inner.c','src/deep','src/test.c/x',
                              'src/absent.c','absent/test.c','src//test.c','src/deep/','src/./test.c',
                              'src/deep/../test.c','./src/test.c')]
        expected=subprocess.run(['git','cat-file','--batch-check=%(objectname)'],cwd=self.root,
                                input=''.join(q+'\n' for q in queries),capture_output=True,text=True).stdout.splitlines()
        self.assertEqual(activity._tree_objects(self.root,queries),expected)

    def test_path_history_walk_matches_rev_list_for_former_directories(self):
        (self.root/'src/test.c').unlink()
        (self.root/'src/test.c').mkdir()
        (self.root/'src/test.c/inner.c').write_text('int inner;')
        self.git('add','-A')
        self.git('-c','user.name=Test','-c','user.email=test@example.invalid','commit','-qm','Directory')
        (self.root/'src/test.c/inner.c').write_text('int inner2;')
        self.git('add','-A')
        self.git('-c','user.name=Test','-c','user.email=test@example.invalid','commit','-qm','Edit')
        revision=self.git('rev-parse','HEAD')
        walked=activity._linear_path_history(self.root,revision,['src/test.c','src/test.c/inner.c'])
        for path in walked:
            self.assertEqual(walked[path],self.git('rev-list',revision,'--',path).split())

    def test_prefetch_matches_one_by_one_answers(self):
        self.commit_source('int function(void) { return 5; }')
        revision=self.git('rev-parse','HEAD')
        activity.prefetch(self.root,self.ledger,revision)
        batched=(set(activity._VERIFIED_COMMITS_CACHE),dict(activity._SOURCE_BLOB_CACHE),
                 dict(activity._HISTORICAL_BLOBS_CACHE))
        activity.clear_cache()
        activity.provenance_commit(self.root,self.commit)
        activity.source_blob(self.root,self.commit,'src/test.c')
        activity.historical_source_blobs(self.root,revision,'src/test.c')
        self.assertEqual(batched,(set(activity._VERIFIED_COMMITS_CACHE),dict(activity._SOURCE_BLOB_CACHE),
                                  dict(activity._HISTORICAL_BLOBS_CACHE)))

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

    def test_path_migration_preserves_original_source_provenance(self):
        self.git('mv', 'src/test.c', 'src/moved.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Move source')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/moved.c'
        self.entry['source'] = 'src/moved.c'
        self.entry['provenance']['original_source'] = 'src/test.c'
        self.assertEqual(self.credits()[0]['login'], 'alice')

    def test_path_migration_after_source_edits_preserves_credit(self):
        self.commit_source('int function(void) { return 2; }')
        renamed_blob = self.git('rev-parse', 'HEAD:src/test.c')
        self.git('mv', 'src/test.c', 'src/moved.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Move edited source')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/moved.c'
        self.entry['source'] = 'src/moved.c'
        self.entry['provenance'].update(original_source='src/test.c', renamed_blob=renamed_blob)
        self.assertEqual(self.credits()[0]['login'], 'alice')

    def test_source_merge_preserves_original_source_provenance(self):
        (self.root/'src/merged.c').write_text('int other(void) { return 2; }\n'
                                             'int function(void) { return 1; }\n')
        self.git('add', 'src/merged.c')
        self.git('rm', '-q', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Merge sources')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/merged.c'
        self.entry['source'] = 'src/merged.c'
        self.entry['provenance'].update(original_source='src/test.c', merged_source=True,
                                      migration_commit=self.commit,
                                      merged_blob=self.git('rev-parse', self.commit + ':src/merged.c'))
        self.assertEqual(self.credits()[0]['login'], 'alice')
        self.entry['provenance']['renamed_blob'] = self.git('rev-parse', 'HEAD:src/merged.c')
        with self.assertRaisesRegex(ValueError, 'merged source provenance'):
            self.credits()
        del self.entry['provenance']['renamed_blob']
        self.entry['provenance']['merged_source'] = 1
        with self.assertRaisesRegex(ValueError, 'merged source provenance'):
            self.credits()

    def test_source_merge_needs_a_commit_that_replaces_the_original_path(self):
        (self.root/'src/merged.c').write_text('int function(void) { return 1; }\n')
        self.git('add', 'src/merged.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Add a second source')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/merged.c'
        self.entry['source'] = 'src/merged.c'
        self.entry['provenance'].update(original_source='src/test.c', merged_source=True,
                                      migration_commit=self.commit,
                                      merged_blob=self.git('rev-parse', self.commit + ':src/merged.c'))
        with self.assertRaisesRegex(ValueError, 'Merged source lacks'):
            self.credits()
        self.git('rm', '-q', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Remove the original later')
        self.commit = self.git('rev-parse', 'HEAD')
        activity.clear_cache()
        with self.assertRaisesRegex(ValueError, 'Merged source lacks'):
            self.credits()

    def test_source_merge_rejects_a_pure_rename(self):
        self.git('mv', 'src/test.c', 'src/merged.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Rename the source')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/merged.c'
        self.entry['source'] = 'src/merged.c'
        self.entry['provenance'].update(original_source='src/test.c', merged_source=True,
                                      migration_commit=self.commit,
                                      merged_blob=self.git('rev-parse', self.commit + ':src/merged.c'))
        with self.assertRaisesRegex(ValueError, 'Merged source lacks'):
            self.credits()

    def test_source_merge_root_commit_has_no_parent_to_replace(self):
        self.assertFalse(activity.merged_source(self.root, self.commit, 'src/test.c',
                                                'src/merged.c', self.commit, self.blob))
        self.assertFalse(activity.merged_source(self.root, self.commit, 'src/test.c',
                                                'src/test.c', self.commit, self.blob))

    def test_source_merge_requires_an_explicit_receipt(self):
        (self.root/'src/merged.c').write_text('int unrelated(void) { return 99; }\n')
        self.git('add', 'src/merged.c'); self.git('rm', '-q', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Unrelated replacement')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/merged.c'
        self.entry['source'] = 'src/merged.c'
        self.entry['provenance'].update(original_source='src/test.c', merged_source=True)
        with self.assertRaisesRegex(ValueError, 'Invalid merged source provenance'):
            self.credits()

    def test_source_merge_pinned_receipt_needs_the_same_reachable_transition(self):
        original = self.commit
        (self.root/'src/merged.c').write_text('int function(void) { return 1; }\nint other;\n')
        self.git('add', 'src/merged.c'); self.git('rm', '-q', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Reviewed migration')
        migration = self.git('rev-parse', 'HEAD')
        merged_blob = self.git('rev-parse', 'HEAD:src/merged.c')
        self.entry['source'] = self.build['units'][0]['source'] = 'src/merged.c'
        self.entry['provenance'].update(original_source='src/test.c', merged_source=True,
                                      migration_commit=migration, merged_blob=merged_blob)
        # A squash with the same parent blobs and transition preserves the receipt.
        tree = self.git('rev-parse', 'HEAD^{tree}')
        self.commit = self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                               'commit-tree', tree, '-p', original, text='Squash migration\n')
        self.assertEqual(self.credits()[0]['functions'], 1)
        # The proof object still exists, but a different reachable replacement cannot use it.
        self.git('reset', '--hard', original)
        (self.root/'src/merged.c').write_text('int unrelated(void) { return 99; }\n')
        self.git('add', 'src/merged.c'); self.git('rm', '-q', 'src/test.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Unrelated replacement')
        self.commit = self.git('rev-parse', 'HEAD')
        activity.clear_cache()
        with self.assertRaisesRegex(ValueError, 'Merged source lacks'):
            self.credits()

    def test_path_migration_rejects_unrelated_current_source(self):
        (self.root/'src/unrelated.c').write_text('int function(void) { return 99; }')
        self.git('add', 'src/unrelated.c')
        self.git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'Unrelated source')
        self.commit = self.git('rev-parse', 'HEAD')
        self.build['units'][0]['source'] = 'src/unrelated.c'
        self.entry['source'] = 'src/unrelated.c'
        self.entry['provenance']['original_source'] = 'src/test.c'
        with self.assertRaisesRegex(ValueError, 'Renamed source'):
            self.credits()
        self.entry['provenance']['renamed_blob'] = self.git('rev-parse', 'HEAD:src/unrelated.c')
        with self.assertRaisesRegex(ValueError, 'Renamed source'):
            self.credits()

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
    target='c'*40

    def feed(self, *revisions):
        rows=[]
        for n,revision in enumerate(revisions):
            row=HistoryTests().row(revision,10+n);row['built_at']=f'2026-10-0{n+1}T10:00:00Z'
            if n%2:row['provenance']={'kind':'verified-source-build','report_sha256':'e'*64}
            rows.append(row)
        return dict(HistoryTests().document(rows),target_sha1=self.target,revision=revisions[-1])

    def manifest(self, revision, timeline, schema='timeline-v1', path='timeline.json'):
        return {'repository':restore_history.REPOSITORY,'revision':revision,'target':{'sha1':self.target},
                'modules':{'timeline':{'status':'supported','asset':{'path':path,'schema':schema,
                                                                     'sha256':restore_history.digest(timeline)}}}}

    def package(self, feed, cutover=None):
        site={'revision':feed['revision'],'built_at':feed['snapshots'][-1]['built_at'],
              'measures':{k:{'total':100,'linked':10} for k in ('code','data')}}
        timeline=json.dumps(report_v1.timeline_document(site,feed,1,1,cutover)).encode()
        output=io.BytesIO()
        with zipfile.ZipFile(output,'w') as zipped:
            for name in ('manifest.json','receipt.json','summary.json','map.json','timeline.json','contributors.json'):
                zipped.writestr(name,json.dumps(self.manifest(feed['revision'],timeline)) if name=='manifest.json'
                                else timeline if name=='timeline.json' else b'{}')
        return output.getvalue()

    def setup(self, runs, store=None, ancestors=None):
        responses={'actions/workflows/baseline.yml/runs?branch=main&status=success&per_page=50':
                   {'workflow_runs':[{'id':r['id']} for r in runs]}}
        archives={}
        for run in runs:
            run.setdefault('head_branch','main');run.setdefault('event','push');run.setdefault('conclusion','success')
            run.setdefault('path',restore_history.WORKFLOW);run.setdefault('run_attempt',1)
            run.setdefault('head_repository',{'full_name':restore_history.REPOSITORY})
            run.setdefault('run_started_at','2026-10-26T01:00:00Z')
            responses[f"actions/runs/{run['id']}"]=run
            responses[f"actions/runs/{run['id']}/attempts/1/jobs?per_page=100"]={'jobs':[
                {'name':'Toolchain baseline','run_attempt':1,'completed_at':'2026-10-26T01:10:00Z'}]}
            artifacts=[]
            if 'archive' in run:
                archives[run['id']]=archive=run.pop('archive')
                artifacts.append({'id':run['id']+1000,'name':'report-v1','expired':False,'workflow_run':{'id':run['id']},
                                  'digest':'sha256:'+restore_history.digest(archive),'created_at':'2026-10-26T01:05:00Z'})
            responses[f"actions/runs/{run['id']}/artifacts?per_page=100"]={'artifacts':artifacts}
        files={}
        if store is not None:
            document,schema=store
            timeline=json.dumps(document).encode()
            path='data/nflstreet2/snapshots/x'
            manifest=json.dumps(self.manifest(document['revision'],timeline,schema,'activity.json')).encode()
            files={'data/reports.lock.json':json.dumps({'projects':{'nflstreet2':{
                       'path':path,'revision':document['revision'],'manifestSha256':restore_history.digest(manifest)}}}).encode(),
                   path+'/manifest.json':manifest,path+'/activity.json':timeline}
        else:
            files={'data/reports.lock.json':json.dumps({'projects':{}}).encode()}
        def api(path, repository=restore_history.REPOSITORY, raw=False):
            if repository==restore_history.SITE:
                return files[path.split('?')[0].removeprefix('contents/')]
            if path.startswith('actions/artifacts/'):
                return archives[int(path.split('/')[2])-1000]
            return json.dumps(responses[path]).encode()
        allowed=ancestors
        return (patch.object(restore_history,'api',side_effect=api),
                patch.object(restore_history,'is_ancestor',side_effect=lambda root,c,r:allowed is None or c in allowed))

    def restore(self, runs, store=None, ancestors=None):
        api,ancestor=self.setup(runs,store,ancestors)
        with api,ancestor:
            return restore_history.restore(Path('.'),{'target_sha1':self.target},'f'*40)

    def test_report_v1_timeline_round_trips_to_the_verified_feed(self):
        feed=self.feed('a'*40,'b'*40,'d'*40)
        cutover={'revision':'b'*40,'built_at':feed['snapshots'][1]['built_at']}
        for cut in (None,cutover):
            site={'revision':'d'*40,'built_at':feed['snapshots'][-1]['built_at'],
                  'measures':{k:{'total':100,'linked':10} for k in ('code','data')}}
            timeline=report_v1.timeline_document(site,feed,1,1,cut)
            self.assertEqual(report_v1.history_feed(timeline,self.target,'d'*40),feed)
        with self.assertRaisesRegex(ValueError,'Unknown history source'):
            report_v1.provenance_of('nflstreet2 pull-request candidate run 1 attempt 1')

    def test_merges_the_last_main_package_with_the_site_store(self):
        own=self.feed('a'*40,'b'*40,'d'*40);store=self.feed('a'*40,'e'*40)
        document,receipt=self.restore([{'id':7,'head_sha':'d'*40,'archive':self.package(own)}],(store,'nfl-activity-v1'))
        self.assertEqual({r['revision'] for r in document['snapshots']},{'a'*40,'b'*40,'d'*40,'e'*40})
        self.assertEqual([r['kind'] for r in receipt['sources']],['main-package','site-store'])
        self.assertEqual(document['revision'],'d'*40)

    def test_skips_runs_without_a_package_or_off_this_history(self):
        old=self.feed('a'*40)
        document,receipt=self.restore([{'id':9,'head_sha':'b'*40},{'id':8,'head_sha':'e'*40,'archive':self.package(self.feed('e'*40))},
                                       {'id':7,'head_sha':'a'*40,'archive':self.package(old)}],ancestors={'a'*40,'b'*40})
        self.assertEqual(receipt['sources'][0]['run'],7)
        self.assertEqual(document['snapshots'],old['snapshots'])

    def test_site_store_alone_restores_once_packages_expire(self):
        store=self.feed('a'*40,'b'*40)
        document,receipt=self.restore([],(store,'nfl-activity-v1'))
        self.assertEqual(document['snapshots'],store['snapshots'])
        site={'revision':'b'*40,'built_at':store['snapshots'][-1]['built_at'],
              'measures':{k:{'total':100,'linked':10} for k in ('code','data')}}
        v1=report_v1.timeline_document(site,store,1,1)
        api,ancestor=self.setup([],(dict(v1,revision='b'*40),'timeline-v1'))
        with api,ancestor:
            document,_=restore_history.restore(Path('.'),{'target_sha1':self.target},'f'*40)
        self.assertEqual(document['snapshots'],store['snapshots'])

    def test_no_authenticated_source_never_resets_history(self):
        with self.assertRaisesRegex(ValueError,'cannot reset history'):
            self.restore([{'id':7,'head_sha':'a'*40}])

    def test_tampered_packages_and_store_fail_instead_of_falling_back(self):
        archive=self.package(self.feed('a'*40))
        api,ancestor=self.setup([{'id':7,'head_sha':'a'*40,'archive':archive}])
        with api as mock,ancestor:
            original=mock.side_effect
            mock.side_effect=lambda path,*a,**k:original(path,*a,**k)+b'x' if path.startswith('actions/artifacts/') else original(path,*a,**k)
            with self.assertRaisesRegex(ValueError,'digest or size'):
                restore_history.restore(Path('.'),{'target_sha1':self.target},'f'*40)
        with self.assertRaisesRegex(ValueError,'another revision'):
            self.restore([{'id':7,'head_sha':'b'*40,'archive':archive}])
        store=self.feed('a'*40)
        api,ancestor=self.setup([],(store,'nfl-activity-v1'))
        with api as mock,ancestor:
            original=mock.side_effect
            mock.side_effect=lambda path,*a,**k:original(path,*a,**k)+b' ' if path.endswith('manifest.json?ref=report-data') else original(path,*a,**k)
            with self.assertRaisesRegex(ValueError,'differs from its lock'):
                restore_history.restore(Path('.'),{'target_sha1':self.target},'f'*40)
        with self.assertRaisesRegex(ValueError,'outside this revision history'):
            self.restore([],(store,'nfl-activity-v1'),ancestors=set())

    def test_main_package_cannot_change_a_row_the_site_accepted(self):
        own=self.feed('a'*40,'b'*40);store=self.feed('a'*40,'b'*40)
        store['snapshots'][1]['provenance']={'kind':'verified-source-build','report_sha256':'d'*64}
        with self.assertRaisesRegex(ValueError,'differs from the rows the site accepted'):
            self.restore([{'id':7,'head_sha':'b'*40,'archive':self.package(own)}],(store,'nfl-activity-v1'))
        store=self.feed('a'*40,'b'*40);store['snapshots'][1]['built_at']='2026-10-03T10:00:00Z'
        with self.assertRaisesRegex(ValueError,'differs from the rows the site accepted'):
            self.restore([{'id':7,'head_sha':'b'*40,'archive':self.package(own)}],(store,'nfl-activity-v1'))

    def test_package_entries_follow_the_manifest(self):
        feed=self.feed('a'*40)
        archive=self.package(feed)
        output=io.BytesIO()
        with zipfile.ZipFile(io.BytesIO(archive)) as source,zipfile.ZipFile(output,'w') as zipped:
            for entry in source.infolist():
                zipped.writestr(entry.filename,source.read(entry))
            zipped.writestr('extra.json',b'{}')
        document,_=self.restore([{'id':7,'head_sha':'a'*40,'archive':output.getvalue()}])
        self.assertEqual(document['snapshots'],feed['snapshots'])
        output=io.BytesIO()
        with zipfile.ZipFile(io.BytesIO(archive)) as source,zipfile.ZipFile(output,'w') as zipped:
            for entry in source.infolist():
                if entry.filename!='timeline.json':zipped.writestr(entry.filename,source.read(entry))
        with self.assertRaisesRegex(ValueError,'Invalid report package entries'):
            self.restore([{'id':7,'head_sha':'a'*40,'archive':output.getvalue()}])


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
        evidence = self.root/'config/GN7E69-rev0/evidence.tsv'
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

    def test_forged_numeric_fuzzy_count_is_rejected(self):
        # An accepted comparison receipt gives the fixture a real numeric fuzzy measure.
        (self.root/'tools/matching-tools.json').write_text(json.dumps(
            {'objdiff':{'version':'fixture'}}))
        for name in matching.INPUTS:
            path = self.root/name
            if not path.exists():
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('fixture '+name)
        target_path = self.root/'config/GN7E69-rev0/baseline.json'
        target = json.loads(target_path.read_text())
        target['sections'] = {'.init':'0x80003100', '.data':'0x80004100', '.bss':'0x80005000'}
        target_path.write_text(json.dumps(target))
        self.source_report['tools']['config/GN7E69-rev0/baseline.json'] = progress.digest(target_path)
        self.save()
        with patch.object(matching, 'ROOT', self.root):
            payload = {'schema':1, 'target_sha1':self.target, 'inputs':matching.bindings(),
                'objdiff':'fixture', 'sources':{'src/unit.c':{
                    'sha256':self.source_report['units'][0]['source_sha256'],
                    'dependencies':self.source_report['units'][0]['dependencies']}},
                'build_receipt':{'path':'build/source/report.json',
                                 'sha256':progress.digest(self.report_path)},
                'entries':[{'source':'src/unit.c', 'type':'function', 'kind':'code',
                            'start':'0x80003104', 'end':'0x8000310C', 'matched':8, 'fuzzy':8}],
                'candidates':[]}
            comparison = self.root/'build/matching/report.json'
            comparison.parent.mkdir(parents=True, exist_ok=True)
            comparison.write_text(json.dumps(payload))
            real_report = progress.report
            def measured_report(binary, revision, source_report, analysis_dir, comparison_report=None):
                # Supply the optional accepted measurement; do not substitute a result.
                return real_report(binary, revision, source_report, analysis_dir, comparison)
            self.site = measured_report(self.binary, self.revision, self.report_path, self.analysis)
            self.assertEqual(self.site['measures']['code']['fuzzy'], 8)
            with patch.object(progress, 'report', side_effect=measured_report):
                self.assertEqual(self.export()['credited_functions'], 1)
                bad = copy.deepcopy(self.site); bad['measures']['code']['fuzzy'] += 1
                with self.assertRaisesRegex(ValueError, 'measurements differ'):
                    self.export(bad)

    def test_foreign_revision_cannot_append_history(self):
        bad = copy.deepcopy(self.site); bad['revision'] = '0'*40
        previous = json.loads((self.root/'config/GN7E69-rev0/history.json').read_text())
        with self.assertRaisesRegex(ValueError, 'outside this revision history'):
            self.export(bad, previous=previous, append=True)


class LiveReceiptTests(unittest.TestCase):
    def test_real_build_reconciles_maps_and_exact_function_credit(self):
        root = activity.ROOT
        report = root/'build/source/report.json'
        site_path = root/'build/site/progress.json'
        if not report.exists() or not site_path.exists():
            self.skipTest('Integration export step supplies the verified build and public map')
        if os.environ.get('LIVE_RECEIPTS') == 'false':
            self.skipTest('CI policy runs this second export of the same receipts on main only')
        site = json.loads(site_path.read_text())
        # Validate the actual receipts and inventory once; corruption cases use bound fixtures.
        result = activity.export(root, site, report)
        published = json.loads((site_path.parent/'activity.json').read_text())
        decomp = json.loads((root/'build/GN7E69-rev0/report.json').read_text())
        check_progress_maps.verify(root, site, decomp, json.loads(report.read_text())['units'], site)
        self.assertEqual(result['revision'], site['revision'])
        self.assertEqual(result['credited_functions'], site['functions']['exact'])
        self.assertEqual(result['contributors'], published['contributors'])
        self.assertEqual(result['credited_functions'], published['credited_functions'])


if __name__=='__main__':unittest.main()
