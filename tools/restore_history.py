#!/usr/bin/env python3
"""Restore history from the last successful Pages deployment, never a cached page."""
import argparse
from datetime import datetime
import io
import json
from pathlib import Path
import re
import subprocess
import tarfile
import zipfile

ROOT=Path(__file__).resolve().parents[1]
REPOSITORY='mitsevox/nflstreet2'


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


def restore(seed):
    deployments=json.loads(api('deployments?environment=github-pages&per_page=100'))
    deployment,run_id,published_at=published_run(deployments,lambda n:json.loads(api(f'deployments/{n}/statuses')))
    run=json.loads(api(f'actions/runs/{run_id}'))
    if run.get('head_sha')!=deployment['sha'] or run.get('head_branch')!='main' or \
            run.get('event') not in ('push','workflow_dispatch') or run.get('path')!='.github/workflows/baseline.yml':
        raise ValueError('Pages deployment does not identify a main baseline build')
    artifacts=json.loads(api(f'actions/runs/{run_id}/artifacts?per_page=100'))['artifacts']
    candidates=[a for a in artifacts if a['name']=='github-pages' and not a['expired'] and a['created_at']<=published_at]
    if not candidates:
        raise ValueError('Last published history artifact is unavailable; publication cannot reset history')
    artifact=max(candidates,key=lambda a:a['created_at'])
    document=read_archive(api(f"actions/artifacts/{artifact['id']}/zip"))
    if document is None:
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
    parser.add_argument('--output',type=Path,default=ROOT/'build/activity/previous.json')
    args=parser.parse_args()
    seed=json.loads((ROOT/'config/GN7E69/history.json').read_text())
    document,receipt=restore(seed)
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(document,indent=2)+'\n')
    args.output.with_suffix('.receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print(f"Restored history from successful Pages deployment {receipt['deployment']} ({receipt['revision'][:7]})")


if __name__=='__main__':main()
