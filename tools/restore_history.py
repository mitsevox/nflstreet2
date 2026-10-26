#!/usr/bin/env python3
"""Restore published history from authenticated report-v1 packages, never a cached page.

Two sources are merged: this repository's last successful main package, which is current, and
the shared site's accepted store, which outlives artifact retention. Every row the site has
accepted must survive unchanged, as its import requires; a disagreement fails.
"""
import argparse
import hashlib
import io
import json
from pathlib import Path
import subprocess
import zipfile

ROOT=Path(__file__).resolve().parents[1]
REPOSITORY='mitsevox/nflstreet2'
SITE='mitsevox/mitsevox.github.io'
STORE_REF='report-data'
WORKFLOW='.github/workflows/baseline.yml'
LIMIT=32*1024*1024


def digest(data):
    return hashlib.sha256(data).hexdigest()


def api(path, repository=REPOSITORY, raw=False):
    accept=['-H','Accept: application/vnd.github.raw'] if raw else []
    return subprocess.check_output(['gh','api','--method','GET',*accept,f'repos/{repository}/{path}'])


def is_ancestor(root, commit, revision):
    return subprocess.run(['git','merge-base','--is-ancestor',commit,revision],cwd=root,
                          stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL).returncode==0


def history(timeline_bytes, manifest, target):
    import activity
    import report_v1
    if manifest.get('repository')!=REPOSITORY or manifest.get('target',{}).get('sha1')!=target:
        raise ValueError('History package names another repository or target')
    module=manifest['modules']['timeline']
    if module.get('status')!='supported' or module['asset']['sha256']!=digest(timeline_bytes):
        raise ValueError('History package timeline differs from its manifest')
    if module['asset']['schema']=='timeline-v1':
        document=report_v1.history_feed(json.loads(timeline_bytes),target,manifest['revision'])
    elif module['asset']['schema']=='nfl-activity-v1':
        # The site's archived legacy package carries this repository's own feed.
        document=json.loads(timeline_bytes)
    else:
        raise ValueError('Unknown history package format')
    rows=activity.validate_history(document,target)
    if document.get('revision')!=manifest['revision'] or manifest['revision'] not in {r['revision'] for r in rows}:
        raise ValueError('History package lacks its own revision')
    return document


def package(archive, artifact, run, target):
    if len(archive)>LIMIT or artifact.get('digest')!='sha256:'+digest(archive):
        raise ValueError('Report package digest or size is invalid')
    with zipfile.ZipFile(io.BytesIO(archive)) as zipped:
        entries={e.filename:e for e in zipped.infolist()}
        # The site's packager owns the file list; only the manifest and the timeline it names are read.
        if 'manifest.json' not in entries or any(
                e.file_size>LIMIT or ((e.external_attr>>16)&0o170000) not in (0,0o100000) for e in entries.values()):
            raise ValueError('Invalid report package entries')
        manifest=json.loads(zipped.read('manifest.json'))
        path=manifest.get('modules',{}).get('timeline',{}).get('asset',{}).get('path')
        if path not in entries:
            raise ValueError('Invalid report package entries')
        timeline=zipped.read(path)
    if manifest.get('revision')!=run['head_sha']:
        raise ValueError('Report package belongs to another revision')
    return history(timeline,manifest,target)


def last_main_package(root, revision, target):
    """Newest successful main run, on this revision's history, that kept its report-v1 package."""
    import publication
    runs=json.loads(api(f'actions/workflows/baseline.yml/runs?branch=main&status=success&per_page=50'))['workflow_runs']
    for summary in sorted(runs,key=lambda r:r['id'],reverse=True):
        run=json.loads(api(f"actions/runs/{summary['id']}"))
        if run.get('conclusion')!='success' or run.get('head_branch')!='main' or run.get('path')!=WORKFLOW \
                or run.get('event') not in ('push','workflow_dispatch') \
                or run.get('head_repository',{}).get('full_name')!=REPOSITORY or not is_ancestor(root,run['head_sha'],revision):
            continue
        jobs=json.loads(api(f"actions/runs/{run['id']}/attempts/{run['run_attempt']}/jobs?per_page=100"))['jobs']
        artifacts=json.loads(api(f"actions/runs/{run['id']}/artifacts?per_page=100"))['artifacts']
        chosen=publication.report_v1_artifact(run,jobs,artifacts)
        if chosen is None:
            continue
        artifact=next(a for a in artifacts if a['id']==chosen['artifact'])
        document=package(api(f"actions/artifacts/{artifact['id']}/zip"),artifact,run,target)
        return document,{'kind':'main-package','run':run['id'],'attempt':run['run_attempt'],
                         'artifact':artifact['id'],'revision':run['head_sha']}
    return None,None


def site_store(root, revision, target):
    """The shared site's accepted package for this project, authenticated by its lock."""
    def read(path):
        data=api(f'contents/{path}?ref={STORE_REF}',SITE,raw=True)
        if len(data)>LIMIT:
            raise ValueError('Site store file exceeds size limit')
        return data
    entry=json.loads(read('data/reports.lock.json'))['projects'].get('nflstreet2')
    if entry is None:
        return None,None
    raw=read(entry['path']+'/manifest.json')
    manifest=json.loads(raw)
    if digest(raw)!=entry['manifestSha256'] or manifest.get('revision')!=entry['revision']:
        raise ValueError('Site store manifest differs from its lock')
    if not is_ancestor(root,manifest['revision'],revision):
        raise ValueError('Site store history is outside this revision history')
    module=manifest['modules']['timeline']['asset']
    document=history(read(entry['path']+'/'+module['path']),manifest,target)
    return document,{'kind':'site-store','path':entry['path'],'manifest_sha256':entry['manifestSha256'],
                     'revision':manifest['revision']}


def restore(root, seed, revision):
    import activity
    target=seed['target_sha1']
    own,own_receipt=last_main_package(root,revision,target)
    store,store_receipt=site_store(root,revision,target)
    sources=[d for d in (own,store) if d is not None]
    if not sources:
        raise ValueError('No authenticated published history; publication cannot reset history')
    rows=activity.merge_history(sources[0],sources[-1] if len(sources)>1 else None)
    if store is not None:
        # The site rejects any import that changes a row it accepted, so a disagreement fails here.
        merged={r['revision']:r for r in rows}
        if any(merged[r['revision']]!=r for r in store['snapshots']):
            raise ValueError('Main package history differs from the rows the site accepted')
    document={'schema':1,'target':'GN7E69','target_sha1':target,'revision':sources[0]['revision'],'snapshots':rows}
    return document,{'sources':[r for r in (own_receipt,store_receipt) if r is not None]}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--revision',default='HEAD')
    parser.add_argument('--output',type=Path,default=ROOT/'build/activity/previous.json')
    args=parser.parse_args()
    seed=json.loads((ROOT/'config/GN7E69/history.json').read_text())
    revision=subprocess.check_output(['git','rev-parse',args.revision],cwd=ROOT,text=True).strip()
    document,receipt=restore(ROOT,seed,revision)
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(document,indent=2)+'\n')
    args.output.with_suffix('.receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print('Restored history from '+', '.join(f"{r['kind']} {r['revision'][:7]}" for r in receipt['sources']))


if __name__=='__main__':main()
