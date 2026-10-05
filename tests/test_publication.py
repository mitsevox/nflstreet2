import copy
import io
import json
import os
from pathlib import Path
import shutil
import sys
import unittest
from unittest.mock import patch
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools'))
import publication
import export_progress
from test_export_progress import ReceiptFixture


class ArchiveTests(unittest.TestCase):
    def archive(self, entries=None):
        payloads = {'progress.json': b'{}\n', 'compiled.json': b'{}\n', 'credits.json': b'{}\n'}
        payloads['manifest.json'] = publication.encoded({'files': {k: publication.digest(v) for k,v in payloads.items()}})
        output = io.BytesIO()
        with zipfile.ZipFile(output, 'w') as z:
            for name,data in (entries or payloads).items(): z.writestr(name, data)
        return output.getvalue()

    def test_digest_entry_allowlist_and_payload_hashes(self):
        archive = self.archive()
        self.assertEqual(set(publication.read_archive(archive, 'sha256:'+publication.digest(archive))[1]),
                         {'progress.json', 'compiled.json', 'credits.json'})
        with self.assertRaisesRegex(ValueError, 'digest'):
            publication.read_archive(archive, 'sha256:'+'0'*64)
        archive = self.archive({'../main.dol': b'private'})
        with self.assertRaisesRegex(ValueError, 'entries'):
            publication.read_archive(archive, 'sha256:'+publication.digest(archive))
        payloads = {'progress.json': b'{}', 'compiled.json': b'{}', 'credits.json': b'{}',
                    'manifest.json': publication.encoded({'files':{k:'0'*64 for k in publication.FILES-{'manifest.json'}}})}
        archive = self.archive(payloads)
        with self.assertRaisesRegex(ValueError, 'payload digest'):
            publication.read_archive(archive, 'sha256:'+publication.digest(archive))

    def test_duplicate_and_symlink_entries_rejected(self):
        for symlink in (False, True):
            output=io.BytesIO()
            with zipfile.ZipFile(output,'w') as z:
                for name in publication.FILES:
                    info=zipfile.ZipInfo(name)
                    if symlink and name=='progress.json': info.external_attr=0o120777 << 16
                    z.writestr(info,b'{}')
                if not symlink: z.writestr('progress.json',b'{}')
            archive=output.getvalue()
            with self.assertRaisesRegex(ValueError,'entries'):
                publication.read_archive(archive,'sha256:'+publication.digest(archive))


class PromotionTests(ReceiptFixture):
    def git(self,*args): return publication.git(self.root,*args)

    def setUp(self):
        super().setUp()
        self.site, _, self.credits = export_progress.export(self.dol,self.revision,self.report_path,self.analysis,None)
        # Real source proof is obtained before the fixture models an independent squash commit.
        base=self.revision
        workflow=self.root/publication.WORKFLOW
        workflow.parent.mkdir(parents=True)
        workflow.write_text('name: Fixture\n')
        self.git('add','.')
        self.git('-c','user.name=Test','-c','user.email=test@example.invalid','commit','-qm','Reviewed config')
        head=self.git('rev-parse','HEAD');tree=self.git('rev-parse','HEAD^{tree}')
        def commit(parents,message):
            import subprocess
            return subprocess.check_output(['git','-c','user.name=Test','-c','user.email=test@example.invalid',
                   'commit-tree',tree,*sum((['-p',p] for p in parents),[])],cwd=self.root,input=message,text=True).strip()
        self.tested=commit([base,head],'Tested batch\n')
        self.landed=commit([base],'Squash batch\n')
        self.git('update-ref','refs/remotes/origin/main',self.landed)
        self.site['revision']=self.tested;self.credits['revision']=self.tested
        self.payloads={'progress.json':self.site,'credits.json':self.credits,
                       'compiled.json':publication.sanitized(self.source_report)}
        self.manifest=dict(schema=1,repository=publication.REPOSITORY,target='GN7E69',environment='pinned-image',
                           tree=tree,revision=self.tested,head=head,base=base,pull_request=12,run=20,attempt=1,
                           workflow_blob=self.git('rev-parse',self.landed+':'+publication.WORKFLOW),files={k:publication.digest(publication.encoded(v)) for k,v in self.payloads.items()})
        self.receipt=dict(manifest=self.manifest,payloads=self.payloads,
                          provenance=dict(kind='workflow-artifact',run=20,artifact=30,report_sha256=self.manifest['files']['compiled.json']))
        self.previous=dict(schema=1,target='GN7E69',target_sha1=self.target,snapshots=[])
        (self.root/'web').mkdir()
        for name in ('index.html','style.css','progress.js','activity.js','cover.jpg','logo.png'):
            (self.root/'web'/name).write_bytes(b'fixture')
        self.pr=dict(number=12,state='closed',merged_at='time',merge_commit_sha=self.landed,
                     head=dict(sha=head,repo=dict(full_name=publication.REPOSITORY)),
                     base=dict(ref='main',repo=dict(full_name=publication.REPOSITORY)))
        self.run=dict(id=20,run_attempt=1,event='pull_request',path=publication.WORKFLOW,status='completed',
                      conclusion='success',head_sha=head,repository=dict(full_name=publication.REPOSITORY),
                      head_repository=dict(full_name=publication.REPOSITORY),run_started_at='2026-10-05T01:00:00Z')
        self.jobs=[dict(name='Toolchain baseline',run_attempt=1,conclusion='success',completed_at='2026-10-05T01:10:00Z',
                       steps=[dict(name=n,conclusion='success') for n in publication.REQUIRED_STEPS])]
        self.artifact=dict(name=publication.ARTIFACT+'-1',expired=False,workflow_run=dict(id=20),
                           digest='sha256:'+'a'*64,size_in_bytes=100,created_at='2026-10-05T01:05:00Z')
        self.commit=dict(sha=self.tested,tree=dict(sha=tree),parents=[dict(sha=base),dict(sha=head)])

    def authenticate(self):
        publication.authenticate(self.root,self.landed,'pinned-image',self.pr,self.run,self.jobs,self.artifact,self.commit,self.manifest)

    def resign(self):
        self.manifest['files']={k:publication.digest(publication.encoded(v)) for k,v in self.payloads.items()}

    def test_final_aggregate_squash_keeps_original_credit_and_history_on_rerun(self):
        self.authenticate()
        self.assertNotEqual(self.tested,self.landed)
        publication.promote(self.root,self.landed,copy.deepcopy(self.receipt),self.previous)
        feed=json.loads((self.root/'build/site/activity.json').read_text())
        self.assertEqual(feed['contributors'],self.credits['contributors'])
        self.assertEqual(feed['snapshots'][0]['provenance']['run'],20)
        first=copy.deepcopy(feed['snapshots'])
        publication.promote(self.root,self.landed,copy.deepcopy(self.receipt),feed)
        self.assertEqual(json.loads((self.root/'build/site/activity.json').read_text())['snapshots'],first)
        site=json.loads((self.root/'build/site/progress.json').read_text())
        self.assertEqual(site['revision'],self.landed)
        self.assertEqual(site['verification']['tested_revision'],self.tested)

    def test_stale_refresh_constituent_tree_environment_or_attempt_rejected(self):
        self.authenticate()
        for key,value in [('tree','0'*40),('head','0'*40),('base','0'*40),('environment','different'),('attempt',2),('workflow_blob','old')]:
            original=self.manifest[key];self.manifest[key]=value
            with self.subTest(key=key),self.assertRaisesRegex(ValueError,'manifest'): self.authenticate()
            self.manifest[key]=original
        self.commit['parents'].reverse()
        with self.assertRaisesRegex(ValueError,'parents'): self.authenticate()

    def test_wrong_run_failed_step_foreign_repo_and_stale_artifact_rejected(self):
        for document,key,value in [(self.run,'conclusion','failure'),(self.run,'head_sha','0'*40),
                                   (self.artifact,'expired',True),(self.artifact,'created_at','2026-10-04T01:00:00Z')]:
            original=document[key];document[key]=value
            with self.subTest(key=key),self.assertRaises(ValueError): self.authenticate()
            document[key]=original
        self.jobs[0]['steps'][0]['conclusion']='skipped'
        with self.assertRaisesRegex(ValueError,'steps'): self.authenticate()

    def test_changed_payload_missing_compiled_function_or_credit_fails(self):
        self.payloads['credits.json']['credited_functions']=99
        with self.assertRaisesRegex(ValueError,'receipt changed'):
            publication.promote(self.root,self.landed,self.receipt,self.previous)
        self.resign()
        with self.assertRaisesRegex(ValueError,'attribution differs'):
            publication.promote(self.root,self.landed,self.receipt,self.previous)
        self.payloads['credits.json']['credited_functions']=1
        self.payloads['compiled.json']['units'][0]['functions']=[];self.resign()
        with self.assertRaisesRegex(ValueError,'Compiler function'):
            publication.promote(self.root,self.landed,self.receipt,self.previous)

    def test_prior_history_preserved_and_invalid_history_blocks(self):
        row=dict(revision=self.revision,built_at='2026-10-03T10:00:00Z',
                 provenance=self.receipt['provenance'],
                 **{k:{f:self.site['measures'][k][f] for f in ('linked','total')} for k in ('code','data')})
        self.previous['snapshots']=[row]
        publication.promote(self.root,self.landed,copy.deepcopy(self.receipt),self.previous)
        feed=json.loads((self.root/'build/site/activity.json').read_text())
        self.assertEqual(feed['snapshots'][0],row)
        self.previous['target_sha1']='0'*40
        with self.assertRaisesRegex(ValueError,'Foreign progress history'):
            publication.promote(self.root,self.landed,copy.deepcopy(self.receipt),self.previous)

    def test_successful_select_authenticates_download_and_attempt_specific_artifact(self):
        archive=io.BytesIO()
        with zipfile.ZipFile(archive,'w') as z:
            z.writestr('manifest.json',publication.encoded(self.manifest))
            for name,document in self.payloads.items(): z.writestr(name,publication.encoded(document))
        blob=archive.getvalue()
        self.artifact.update(id=30,digest='sha256:'+publication.digest(blob),size_in_bytes=len(blob))
        def api(path):
            if path.startswith('commits/'): document=[dict(number=12)]
            elif path=='pulls/12': document=self.pr
            elif path.startswith('actions/workflows/'): document=dict(workflow_runs=[self.run])
            elif path=='actions/runs/20': document=self.run
            elif '/attempts/1/jobs?' in path: document=dict(jobs=self.jobs)
            elif path.startswith('actions/runs/20/artifacts?'): document=dict(artifacts=[self.artifact])
            elif path=='actions/artifacts/30/zip': return blob
            elif path=='git/commits/'+self.tested: document=self.commit
            else: raise AssertionError(path)
            return json.dumps(document).encode()
        output=self.root/'receipt.json'
        with patch.object(publication,'api',side_effect=api):
            self.assertTrue(publication.select(self.root,self.landed,'pinned-image',output))
        self.assertEqual(json.loads(output.read_text())['provenance']['artifact'],30)
        self.artifact['name']=publication.ARTIFACT+'-2'
        with patch.object(publication,'api',side_effect=api):
            self.assertFalse(publication.select(self.root,self.landed,'pinned-image',output))
        self.assertFalse(output.exists())

    def test_unavailable_api_falls_back_and_clears_old_receipt(self):
        import subprocess
        output=self.root/'old.json';output.write_text('old')
        with patch.object(publication,'api',side_effect=subprocess.CalledProcessError(1,['gh'])):
            self.assertFalse(publication.select(self.root,self.landed,'pinned-image',output))
        self.assertFalse(output.exists())


if __name__=='__main__': unittest.main()
