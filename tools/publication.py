#!/usr/bin/env python3
"""Reuse public reports from successful final-integration CI on an identical tree."""
import argparse
from datetime import datetime, timezone
import hashlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import zipfile
import zlib

import activity
import check_progress_maps
import decomp_report
import restore_history

ROOT = Path(__file__).resolve().parents[1]
REPOSITORY = 'mitsevox/nflstreet2'
WORKFLOW = '.github/workflows/baseline.yml'
ARTIFACT = 'verified-publication-v1'
FILES = {'progress.json', 'compiled.json', 'credits.json', 'manifest.json'}
MAX_ARCHIVE = 32 * 1024 * 1024
MAX_PAYLOAD = 80 * 1024 * 1024
REQUIRED_STEPS = (
    'Verify publication handoff rules', 'Verify review clearance logic', 'Verify complete original-object relink',
    'Verify compiler stages', 'Verify SN linker against complete target',
    'Verify source build against complete target', 'Verify provisional function inventory',
    'Verify inventory cache invalidation and real warm reuse',
    'Measure exact and fuzzy source comparisons',
    'Verify both progress exports, maps, history and contributor credits',
    'Verify activity and live receipts on the host',
    'Prepare verified publication handoff', 'Upload verified publication handoff',
)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def encoded(value):
    return (json.dumps(value, sort_keys=True, separators=(',', ':')) + '\n').encode()


def git(root, *args):
    return subprocess.check_output(['git', *args], cwd=root, text=True).strip()


def api(path):
    return restore_history.api(path)


def pages(path, field=None):
    result = []
    for page in range(1, 101):
        separator = '&' if '?' in path else '?'
        data = json.loads(api(f'{path}{separator}per_page=100&page={page}'))
        rows = data[field] if field else data
        result.extend(rows)
        if len(rows) < 100:
            return result
    raise ValueError('GitHub response exceeds publication lookup bound')


def sanitized(build):
    return {**{key: build[key] for key in
               ('schema', 'target', 'target_sha1', 'complete', 'manifest_sha256')},
            'units': [dict(source=u['source'], source_sha256=u['source_sha256'],
                           sections=[{k: s[k] for k in ('section', 'placement', 'kind', 'start', 'end')}
                                     for s in u['sections']],
                           functions=[{k: f[k] for k in ('address', 'size')} for f in u['functions']])
                      for u in build['units']]}


def prepare(root, environment, event, output):
    pr = event['pull_request']
    revision = os.environ['GITHUB_SHA']
    site = json.loads((root/'build/site/progress.json').read_text())
    credits = json.loads((root/'build/site/activity.json').read_text())
    build = json.loads((root/'build/source/report.json').read_text())
    if site['revision'] != revision or credits['revision'] != revision or build['complete'] != 'identical':
        raise ValueError('Handoff is not the final verified integration revision')
    tree = git(root, 'rev-parse', revision+'^{tree}')
    parents = git(root, 'show', '-s', '--format=%P', revision).split()
    if parents != [pr['base']['sha'], pr['head']['sha']]:
        raise ValueError('Tested merge differs from event head/base')
    if pr['head']['repo']['full_name'] != REPOSITORY:
        raise ValueError('Foreign contribution repository')
    payloads = {'progress.json': encoded(site), 'compiled.json': encoded(sanitized(build)),
                'credits.json': encoded(credits)}
    manifest = dict(schema=1, repository=REPOSITORY, target='GN7E69', environment=environment,
                    revision=revision, tree=tree, head=pr['head']['sha'], base=pr['base']['sha'],
                    pull_request=pr['number'], run=int(os.environ['GITHUB_RUN_ID']),
                    attempt=int(os.environ['GITHUB_RUN_ATTEMPT']),
                    workflow_blob=git(root, 'rev-parse', revision+':'+WORKFLOW),
                    files={name: digest(data) for name, data in payloads.items()})
    # Export only these reviewed JSON projections, never a build directory.
    if output.exists():
        shutil.rmtree(output)
    output.mkdir(parents=True)
    for name, data in payloads.items():
        (output/name).write_bytes(data)
    (output/'manifest.json').write_bytes(encoded(manifest))


def read_archive(archive, expected_digest):
    if len(archive) > MAX_ARCHIVE or expected_digest != 'sha256:'+digest(archive):
        raise ValueError('Publication archive digest or size differs')
    with zipfile.ZipFile(io.BytesIO(archive)) as zipped:
        entries = zipped.infolist()
        if len(entries) != len(FILES) or {e.filename for e in entries} != FILES \
                or sum(e.file_size for e in entries) > MAX_PAYLOAD \
                or any(e.is_dir() or ((e.external_attr >> 16) & 0o170000) == 0o120000 for e in entries):
            raise ValueError('Unexpected publication archive entries')
        payloads = {e.filename: zipped.read(e) for e in entries}
    manifest = json.loads(payloads['manifest.json'])
    if set(manifest['files']) != FILES - {'manifest.json'} or any(
            manifest['files'][name] != digest(payloads[name]) for name in manifest['files']):
        raise ValueError('Publication payload digest differs')
    return manifest, {name: json.loads(data) for name, data in payloads.items() if name != 'manifest.json'}


def authenticate(root, revision, environment, pr, run, jobs, artifact, commit, manifest):
    """Check GitHub-held execution identity separately from downloaded claims."""
    tree = git(root, 'rev-parse', revision+'^{tree}')
    parent = git(root, 'rev-parse', revision+'^')
    expected = dict(schema=1, repository=REPOSITORY, target='GN7E69', environment=environment,
                    tree=tree, pull_request=pr['number'], head=pr['head']['sha'], base=parent,
                    run=run['id'], attempt=run['run_attempt'],
                    workflow_blob=git(root, 'rev-parse', revision+':'+WORKFLOW))
    if any(manifest.get(k) != v for k, v in expected.items()):
        raise ValueError('Publication manifest differs from landed tree or final CI inputs')
    if pr.get('state') != 'closed' or not pr.get('merged_at') or pr.get('merge_commit_sha') != revision \
            or pr['base']['ref'] != 'main' or pr['base']['repo']['full_name'] != REPOSITORY \
            or pr['head']['repo']['full_name'] != REPOSITORY:
        raise ValueError('Publication does not identify the merged repository PR')
    if run.get('repository', {}).get('full_name') != REPOSITORY \
            or run.get('head_repository', {}).get('full_name') != REPOSITORY \
            or run.get('event') != 'pull_request' or run.get('path') != WORKFLOW \
            or run.get('status') != 'completed' or run.get('conclusion') != 'success' \
            or run.get('head_sha') != pr['head']['sha']:
        raise ValueError('Publication run is not successful final PR validation')
    if commit.get('sha') != manifest.get('revision') or commit['tree']['sha'] != tree \
            or [p['sha'] for p in commit['parents']] != [parent, pr['head']['sha']]:
        raise ValueError('Tested aggregate merge tree or parents differ')
    baseline = [j for j in jobs if j['name'] == 'Toolchain baseline'
                and j.get('run_attempt') == run['run_attempt']]
    if len(baseline) != 1 or baseline[0].get('conclusion') != 'success':
        raise ValueError('Publication lacks a successful baseline job on this attempt')
    steps = baseline[0]['steps']
    if any(sum(s['name'] == name and s['conclusion'] == 'success' for s in steps) != 1
           for name in REQUIRED_STEPS):
        raise ValueError('Publication lacks required final-integration steps')
    if artifact.get('name') != f"{ARTIFACT}-{run['run_attempt']}" or artifact.get('expired') \
            or artifact.get('workflow_run', {}).get('id') != run['id'] \
            or not artifact.get('digest', '').startswith('sha256:') \
            or artifact['size_in_bytes'] > MAX_ARCHIVE \
            or artifact['created_at'] < run['run_started_at'] \
            or artifact['created_at'] > baseline[0]['completed_at']:
        raise ValueError('Publication artifact is stale or outside successful attempt')


def select(root, revision, environment, output):
    """Missing or invalid execution proof falls back; publication checks fail closed."""
    output.unlink(missing_ok=True)
    try:
        pulls = pages(f'commits/{revision}/pulls')
        for summary in pulls:
            pr = json.loads(api(f"pulls/{summary['number']}"))
            if pr.get('merge_commit_sha') != revision or not pr.get('merged_at'):
                continue
            runs = pages(f"actions/workflows/baseline.yml/runs?event=pull_request&head_sha={pr['head']['sha']}", 'workflow_runs')
            for summary_run in sorted(runs, key=lambda r: r['id'], reverse=True):
                run = json.loads(api(f"actions/runs/{summary_run['id']}"))
                if run.get('conclusion') != 'success':
                    continue
                jobs = pages(f"actions/runs/{run['id']}/attempts/{run['run_attempt']}/jobs", 'jobs')
                for artifact in pages(f"actions/runs/{run['id']}/artifacts", 'artifacts'):
                    if artifact['name'] != f"{ARTIFACT}-{run['run_attempt']}" or artifact['expired'] \
                            or artifact.get('size_in_bytes', MAX_ARCHIVE+1) > MAX_ARCHIVE:
                        continue
                    try:
                        archive = api(f"actions/artifacts/{artifact['id']}/zip")
                        manifest, payloads = read_archive(archive, artifact.get('digest'))
                        commit = json.loads(api(f"git/commits/{manifest['revision']}"))
                        authenticate(root, revision, environment, pr, run, jobs, artifact, commit, manifest)
                    except (ValueError, KeyError, TypeError, zipfile.BadZipFile, zlib.error, NotImplementedError, RuntimeError):
                        continue
                    output.parent.mkdir(parents=True, exist_ok=True)
                    output.write_bytes(encoded(dict(manifest=manifest, payloads=payloads,
                        provenance=dict(kind='workflow-artifact', run=run['id'], artifact=artifact['id'],
                                        report_sha256=manifest['files']['compiled.json']))))
                    print(f"Reusing final PR #{pr['number']} proof from run {run['id']} on identical tree")
                    return True
    except (subprocess.CalledProcessError, ValueError, KeyError, TypeError):
        print('Publication proof unavailable; retaining complete main validation')
    return False


def promote(root, revision, receipt, previous):
    """Only called with a receipt authenticated by select in this trusted job."""
    manifest, payloads = receipt['manifest'], receipt['payloads']
    if manifest['tree'] != git(root, 'rev-parse', revision+'^{tree}') or any(
            manifest['files'][name] != digest(encoded(document)) for name, document in payloads.items()):
        raise ValueError('Authenticated publication receipt changed')
    site, build, prior = payloads['progress.json'], payloads['compiled.json'], payloads['credits.json']
    if site['revision'] != manifest['revision'] or prior['revision'] != manifest['revision'] \
            or site.get('baseline') != 'verified' or site['target_sha1'] != build['target_sha1'] \
            or build['target'] != 'GN7E69' or build['complete'] != 'identical':
        raise ValueError('Publication target or verified revision differs')
    if build['manifest_sha256'] != digest((root/'config/GN7E69/units.json').read_bytes()) \
            or any(u['source_sha256'] != digest((root/u['source']).read_bytes()) for u in build['units']):
        raise ValueError('Publication source bindings differ')
    def linked(item):
        if item.get('type') == 'function' and item.get('linked', 0) > 0:
            return {(item['source'], item['function_address'], item['original_size'])}
        return set().union(*(linked(c) for c in item.get('children', [])))
    mapped = set().union(*(linked(f) for f in site['files']))
    compiled = {(u['source'], f['address'], f['size']) for u in build['units'] for f in u['functions']}
    if mapped != compiled:
        raise ValueError('Compiler function receipt differs from authenticated map')
    # Byte comparisons were validated by the authenticated PR run, not by comparing JSON to itself.
    decomp = decomp_report.objdiff_report(site)
    check_progress_maps.verify(root, site, decomp, build['units'], authenticated_comparisons=True)
    exact = activity.exact_functions(site)
    ledger = json.loads((root/'config/GN7E69/contributors.json').read_text())
    credits = activity.contributors(root, ledger, build, revision, True, exact)
    if credits != prior['contributors'] or len(exact) != prior['credited_functions']:
        raise ValueError('Landed original contributor attribution differs from final PR')
    activity.check_ancestor(root, revision, 'refs/remotes/origin/main')
    site['revision'] = revision
    site['built_at'] = datetime.now(timezone.utc).isoformat()
    site['verification'] = {**receipt['provenance'], 'tested_revision': manifest['revision'],
                            'tree': manifest['tree'], 'environment': manifest['environment']}
    seed = json.loads((root/'config/GN7E69/history.json').read_text())
    current = dict(revision=revision, built_at=site['built_at'], provenance=receipt['provenance'],
                   **{k: {f: site['measures'][k][f] for f in ('linked', 'total')} for k in ('code', 'data')})
    history = activity.merge_history(seed, previous, current)
    for row in history:
        activity.check_ancestor(root, row['revision'], revision)
    feed = dict(schema=1, target='GN7E69', target_sha1=site['target_sha1'], revision=revision,
                snapshots=history, contribution_basis='exact-functions',
                credited_functions=len(exact), contributors=credits)
    output = root/'build/site'
    output.mkdir(parents=True, exist_ok=True)
    for name in ('index.html', 'style.css', 'progress.js', 'activity.js', 'cover.jpg', 'logo.png'):
        shutil.copyfile(root/'web'/name, output/name)
    decomp_path = root/'build/GN7E69/report.json'
    decomp_path.parent.mkdir(parents=True, exist_ok=True)
    for path, document in ((output/'progress.json', site), (output/'activity.json', feed),
                           (decomp_path, decomp_report.objdiff_report(site))):
        path.write_bytes(encoded(document))
    print(f"Published authenticated tree with {len(exact)} exact-function credits at {revision}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=('prepare', 'select', 'promote'))
    parser.add_argument('--revision', default=os.environ.get('GITHUB_SHA'))
    parser.add_argument('--environment', default=os.environ.get('BUILD_ENVIRONMENT'))
    args = parser.parse_args()
    receipt = ROOT/'build/publication-receipt.json'
    if args.mode == 'prepare':
        prepare(ROOT, args.environment, json.loads(Path(os.environ['GITHUB_EVENT_PATH']).read_text()),
                ROOT/'build/publication')
    elif args.mode == 'select':
        reused = select(ROOT, args.revision, args.environment, receipt)
        with open(os.environ['GITHUB_OUTPUT'], 'a') as output:
            output.write(f"reused={str(reused).lower()}\n")
    else:
        # History/provenance errors are publication failures, never a reason to bypass them.
        for path in (ROOT/'build/site/progress.json', ROOT/'build/site/activity.json', ROOT/'build/GN7E69/report.json'):
            path.unlink(missing_ok=True)
        promote(ROOT, args.revision, json.loads(receipt.read_text()),
                json.loads((ROOT/'build/activity/previous.json').read_text()))


if __name__ == '__main__':
    main()
