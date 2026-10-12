#!/usr/bin/env python3
"""Restore history from the last successful Pages deployment, never a cached page."""
import argparse
import hashlib
from datetime import datetime
import io
import json
import os
from pathlib import Path
import re
import subprocess
import tarfile
import zipfile

ROOT=Path(__file__).resolve().parents[1]
REPOSITORY='mitsevox/nflstreet2'
HISTORY_ARTIFACT='published-history-v1'


def encoded(document):
    return json.dumps(document,sort_keys=True,separators=(',',':')).encode()


def history_document(document, target, revision):
    import activity
    rows=activity.validate_history(document,target)
    if document.get('revision')!=revision or not rows or rows[-1]['revision']!=revision:
        raise ValueError('Archived history differs from its published deployment')
    return document


def durable_archive(archive, artifact, run, attempt, revision, target):
    if len(archive)>10*1024*1024 or artifact.get('digest')!='sha256:'+hashlib.sha256(archive).hexdigest():
        raise ValueError('History archive digest or size is invalid')
    with zipfile.ZipFile(io.BytesIO(archive)) as zipped:
        entries=zipped.infolist()
        if len(entries)!=2 or {e.filename for e in entries}!={'activity.json','manifest.json'} or \
                any(e.file_size>10*1024*1024 or ((e.external_attr>>16)&0o170000) not in (0,0o100000) for e in entries):
            raise ValueError('Invalid history archive entries')
        payload=zipped.read('activity.json')
        manifest=json.loads(zipped.read('manifest.json'))
    expected={'schema':1,'repository':REPOSITORY,'revision':revision,'run':run,
              'attempt':attempt,'target_sha1':target,'activity_sha256':hashlib.sha256(payload).hexdigest()}
    if manifest!=expected:
        raise ValueError('History archive manifest differs from its deployment')
    return history_document(json.loads(payload),target,revision)


def audited_recovery(seed, receipt, deployment, run):
    import activity
    if receipt.get('schema')!=1 or any(receipt.get(key)!=value for key,value in
            [('deployment',deployment['id']),('run',run),('revision',deployment['sha'])]) or \
            receipt.get('history_sha256')!=hashlib.sha256(encoded(seed)).hexdigest() or \
            receipt.get('snapshot_count')!=len(seed.get('snapshots',[])):
        raise ValueError('Missing history is outside the exact audited recovery')
    rows=activity.validate_history(seed,seed['target_sha1'])
    if not rows or rows[-1]['revision']!=deployment['sha']:
        raise ValueError('Audited recovery lacks the deployed revision')
    return dict(seed,revision=deployment['sha'])


def prepare_history(root, revision, run, attempt):
    target=json.loads((root/'config/GN7E69/history.json').read_text())['target_sha1']
    payload=(root/'build/site/activity.json').read_bytes()
    history_document(json.loads(payload),target,revision)
    if type(run) is not int or run<=0 or type(attempt) is not int or attempt<=0:
        raise ValueError('History archive needs a workflow run and attempt')
    manifest={'schema':1,'repository':REPOSITORY,'revision':revision,'run':run,'attempt':attempt,
              'target_sha1':target,'activity_sha256':hashlib.sha256(payload).hexdigest()}
    output=root/'build/activity/archive'
    output.mkdir(parents=True,exist_ok=True)
    (output/'activity.json').write_bytes(payload)
    (output/'manifest.json').write_bytes(encoded(manifest)+b'\n')


def api(path):
    return subprocess.check_output(['gh','api','--method','GET',f'repos/{REPOSITORY}/{path}'])


def published_run(deployments, statuses):
    for deployment in deployments:
        success=next((s for s in statuses(deployment['id']) if s['state']=='success'),None)
        if success:
            match=re.fullmatch(r'https://github.com/mitsevox/nflstreet2/actions/runs/(\d+)/job/\d+',success.get('log_url',''))
            if not match:
                raise ValueError('Published deployment lacks a workflow run receipt')
            return deployment,int(match[1]),success['created_at']
    raise ValueError('No successful Pages deployment; bootstrap needs a verified publication')


def read_archive(archive):
    if len(archive)>32*1024*1024:
        raise ValueError('Pages archive exceeds size limit')
    with zipfile.ZipFile(io.BytesIO(archive)) as zipped:
        names=[n for n in zipped.namelist() if n=='artifact.tar']
        if len(names)!=1 or zipped.getinfo(names[0]).file_size>80*1024*1024:
            raise ValueError('Unexpected Pages archive')
        with tarfile.open(fileobj=io.BytesIO(zipped.read(names[0])),mode='r:*') as tar:
            candidates=[m for m in tar.getmembers() if m.name in ('activity.json','./activity.json')]
            if not candidates:return None
            if len(candidates)!=1 or not candidates[0].isfile() or candidates[0].size>10*1024*1024:
                raise ValueError('Invalid archived activity feed')
            return json.loads(tar.extractfile(candidates[0]).read())


def restore(seed, recovery=None):
    deployments=json.loads(api('deployments?environment=github-pages&per_page=100'))
    deployment,run_id,published_at=published_run(deployments,lambda n:json.loads(api(f'deployments/{n}/statuses')))
    run=json.loads(api(f'actions/runs/{run_id}'))
    if run.get('head_sha')!=deployment['sha'] or run.get('head_branch')!='main' or \
            run.get('event') not in ('push','workflow_dispatch') or run.get('path')!='.github/workflows/baseline.yml':
        raise ValueError('Pages deployment does not identify a main baseline build')
    artifacts=json.loads(api(f'actions/runs/{run_id}/artifacts?per_page=100'))['artifacts']
    durable=[a for a in artifacts if a['name'].startswith(HISTORY_ARTIFACT+'-') and not a['expired']]
    if durable:
        statuses=json.loads(api(f"deployments/{deployment['id']}/statuses"))
        success=next(s for s in statuses if s['state']=='success')
        job_id=re.fullmatch(r'https://github.com/mitsevox/nflstreet2/actions/runs/\d+/job/(\d+)',success['log_url'])[1]
        job=json.loads(api(f'actions/jobs/{job_id}'))
        if job.get('run_id')!=run_id or job.get('head_sha')!=deployment['sha'] or job.get('conclusion')!='success':
            raise ValueError('History archive lacks a successful deployment job')
        attempt=job['run_attempt']
        matching=[a for a in durable if a['name']==f'{HISTORY_ARTIFACT}-{attempt}' and a['created_at']<=published_at]
        if len(matching)!=1:
            raise ValueError('History archive is not bound to the published attempt')
        artifact=matching[0]
        if artifact.get('workflow_run',{}).get('id')!=run_id:
            raise ValueError('History archive belongs to another workflow run')
        document=durable_archive(api(f"actions/artifacts/{artifact['id']}/zip"),artifact,run_id,
                                 attempt,deployment['sha'],seed['target_sha1'])
        return document,{'deployment':deployment['id'],'run':run_id,'artifact':artifact['id'],
                         'revision':deployment['sha'],'kind':'durable-history'}
    candidates=[a for a in artifacts if a['name']=='github-pages' and not a['expired'] and a['created_at']<=published_at]
    if not candidates:
        if recovery is not None:
            document=audited_recovery(seed,recovery,deployment,run_id)
            return document,{'deployment':deployment['id'],'run':run_id,'revision':deployment['sha'],
                             'kind':'audited-recovery','history_sha256':recovery['history_sha256']}
        raise ValueError('Last published history artifact is unavailable; publication cannot reset history')
    artifact=max(candidates,key=lambda a:a['created_at'])
    document=read_archive(api(f"actions/artifacts/{artifact['id']}/zip"))
    if document is None:
        if recovery is not None:
            document=audited_recovery(seed,recovery,deployment,run_id)
            return document,{'deployment':deployment['id'],'run':run_id,'artifact':artifact['id'],
                             'revision':deployment['sha'],'kind':'audited-recovery',
                             'history_sha256':recovery['history_sha256']}
        if deployment['sha'] not in {row['revision'] for row in seed['snapshots']}:
            raise ValueError('Published history is missing outside the audited bootstrap revisions')
        document=seed
    else:
        import activity
        rows=activity.validate_history(document,seed['target_sha1'])
        if document.get('revision')!=deployment['sha'] or deployment['sha'] not in {row['revision'] for row in rows}:
            raise ValueError('Archived history differs from its published deployment')
    return document,{'deployment':deployment['id'],'run':run_id,'artifact':artifact['id'],'revision':deployment['sha']}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--prepare',action='store_true',help='Prepare a verified main publication history archive')
    parser.add_argument('--output',type=Path,default=ROOT/'build/activity/previous.json')
    args=parser.parse_args()
    if args.prepare:
        if os.environ.get('GITHUB_REF')!='refs/heads/main' or os.environ.get('GITHUB_EVENT_NAME') not in ('push','workflow_dispatch'):
            raise ValueError('History archives are prepared only for main publication')
        prepare_history(ROOT,os.environ['GITHUB_SHA'],int(os.environ['GITHUB_RUN_ID']),int(os.environ['GITHUB_RUN_ATTEMPT']))
        return
    seed=json.loads((ROOT/'config/GN7E69/history.json').read_text())
    recovery_path=ROOT/'config/GN7E69/history-recovery.json'
    recovery=json.loads(recovery_path.read_text())
    document,receipt=restore(seed,recovery)
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(document,indent=2)+'\n')
    args.output.with_suffix('.receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print(f"Restored history from successful Pages deployment {receipt['deployment']} ({receipt['revision'][:7]})")


if __name__=='__main__':main()
