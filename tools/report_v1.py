#!/usr/bin/env python3
"""Project the verified public reports onto the shared site's report-v1 producer inputs.

Reads only outputs this job already validated (build/site progress and activity, the contributor
ledger and, for a reused main publication, the authenticated PR receipt). Packaging and the
contract's semantic checks run in the site's pinned packager; this tool never measures anything.
"""
import argparse
import json
import os
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
REPOSITORY = 'mitsevox/nflstreet2'
WORKFLOW = '.github/workflows/baseline.yml'
METHODOLOGY = 'nflstreet2-report-v1'
GENERATION = 1
ARTIFACT = 'report-v1'
# report-v1 map nodes accept only these fields; NFL's evidence fields stay in its own report.
NODE_FIELDS = ('name', 'kind', 'size', 'linked', 'matched', 'fuzzy', 'address', 'mapped_extents',
               'children', 'type', 'function_address', 'original_size')


def encoded(value):
    return (json.dumps(value, sort_keys=True, separators=(',', ':')) + '\n').encode()


def git(root, *args):
    return subprocess.check_output(['git', *args], cwd=root, text=True).strip()


def summary(site):
    return {**{kind: {'totalBytes': m['total'], 'linkedBytes': m['linked'], 'matchedBytes': m['matched'],
                      'fuzzyEquivalentBytes': m.get('fuzzy')}
               for kind, m in ((k, site['measures'][k]) for k in ('code', 'data'))},
            'functions': site['functions'], 'files': site['file_counts']}


def node(item):
    result = {k: item[k] for k in NODE_FIELDS if k in item and k != 'children'}
    if item.get('children'):
        result['children'] = [node(c) for c in item['children']]
    return result


def map_document(site):
    return {'schemaVersion': 1, 'sections': [node(s) for s in site['sections']],
            'files': [node(f) for f in site['files']]}


def function_id(site, item):
    return f"{site['target']}:0x{int(item['function_address'], 16):08X}:{item['original_size']}"


def exact_identities(site):
    """(source, address) → report-v1 function id, by the same criteria as activity.exact_functions."""
    identities = {}
    def visit(item):
        source = item.get('comparison_source') or item.get('source')
        if item.get('type') == 'function' and source and item['size'] > 0 \
                and item['size'] == item['original_size'] and item['matched'] == item['size']:
            key = (source, item['function_address'])
            if key in identities:
                raise ValueError('Exact function appears more than once in the public map')
            identities[key] = function_id(site, item)
        for child in item.get('children', []):
            visit(child)
    for item in site['files']:
        visit(item)
    if len(identities) != site['functions']['exact'] or len(set(identities.values())) != len(identities):
        raise ValueError('Exact function identities differ from the public inventory')
    return identities


def contributors_document(site, feed, ledger):
    identities = exact_identities(site)
    profiles = ledger['contributors']
    authors = {}
    for entry in ledger['entries']:
        for address in entry['functions']:
            key = (entry['source'], address)
            if key in identities:
                if identities[key] in authors:
                    raise ValueError('Function credited more than once')
                authors[identities[key]] = sorted(profiles[login]['id'] for login in entry['contributors'])
    if set(authors) != set(identities.values()):
        raise ValueError('Exact function lacks ledger attribution')
    people = [{'login': p['login'], 'id': p['id'], 'functions': p['functions']} for p in feed['contributors']]
    counts = {p['id']: 0 for p in people}
    for ids in authors.values():
        for person in ids:
            if person not in counts:
                raise ValueError('Function author is absent from the verified contributor feed')
            counts[person] += 1
    # The feed was produced by activity.contributors in this job; both projections must agree.
    if any(counts[p['id']] != p['functions'] for p in people) or feed['credited_functions'] != len(authors):
        raise ValueError('Function ledger differs from the verified contributor feed')
    return {'schemaVersion': 1, 'credited_functions': len(authors), 'contributors': people,
            'functions': [{'id': key, 'authors': authors[key]} for key in sorted(authors)]}


def source(provenance):
    """One deterministic identity per recorded execution, so accepted rows never change."""
    kind = provenance['kind']
    if kind == 'workflow-artifact':
        return (f"nflstreet2 workflow-artifact run {provenance['run']} artifact {provenance['artifact']}"
                f" report sha256:{provenance['report_sha256']}")
    if kind == 'verified-source-build':
        return f"nflstreet2 verified-source-build report sha256:{provenance['report_sha256']}"
    raise ValueError('Unknown history provenance')


def timeline_document(site, feed, run, attempt):
    rows = [{'revision': r['revision'], 'built_at': r['built_at'],
             'code': {'total': r['code']['total'], 'linked': r['code']['linked']},
             'data': {'total': r['data']['total'], 'linked': r['data']['linked']},
             'provenance': {'kind': 'measured', 'source': source(r['provenance'])}}
            for r in feed['snapshots']]
    if site['revision'] not in {r['revision'] for r in rows}:
        # A PR's tested merge is candidate evidence only; main appends landed revisions.
        rows.append({'revision': site['revision'], 'built_at': site['built_at'],
                     **{k: {f: site['measures'][k][f] for f in ('total', 'linked')} for k in ('code', 'data')},
                     'provenance': {'kind': 'measured',
                                    'source': f'nflstreet2 pull-request candidate run {run} attempt {attempt}'}})
    return {'schemaVersion': 1, 'snapshots': rows}


def policy(root, environment, blob):
    template = json.loads((root/'config/GN7E69/report-v1-producer.json').read_text())
    if template['tools'] != [{'name': 'build-environment', 'identity': environment}]:
        raise ValueError('Producer policy names another build environment')
    # The packager checks structure against this run's own workflow; the site's approved
    # blob list is the authority when it imports the artifact.
    if 'workflowBlobs' in template:
        raise ValueError('Producer template must not approve workflow revisions')
    return {**template, 'workflowBlobs': [blob]}


def prepare(root, output, environment, run, attempt, receipt=None):
    site = json.loads((root/'build/site/progress.json').read_text())
    feed = json.loads((root/'build/site/activity.json').read_text())
    ledger = json.loads((root/'config/GN7E69/contributors.json').read_text())
    revision = git(root, 'rev-parse', 'HEAD')
    if site['revision'] != revision or feed['revision'] != revision or site.get('baseline') != 'verified':
        raise ValueError('Public reports are not this verified revision')
    blob = git(root, 'rev-parse', f'{revision}:{WORKFLOW}')
    inputs = output/'input'
    inputs.mkdir(parents=True)
    for name, document in (('summary.json', summary(site)), ('map.json', map_document(site)),
                           ('timeline.json', timeline_document(site, feed, run, attempt)),
                           ('contributors.json', contributors_document(site, feed, ledger))):
        (inputs/name).write_bytes(encoded(document))
    metadata = {'project': 'nflstreet2', 'repository': REPOSITORY,
                'target': {'id': site['target'], 'console': 'GameCube', 'sha1': site['target_sha1']},
                'revision': revision, 'tree': git(root, 'rev-parse', revision+'^{tree}'),
                'methodology': METHODOLOGY, 'generation': GENERATION,
                'measuredAt': site['built_at'], 'publishedAt': site['built_at'],
                'tools': [{'name': 'build-environment', 'identity': environment}],
                'runId': run, 'attempt': attempt, 'workflowBlob': blob, 'mode': 'full', 'source': None}
    if receipt is not None:
        original = receipt['report_v1']
        metadata['measuredAt'] = receipt['payloads']['progress.json']['built_at']
        metadata['mode'] = 'reused'
        metadata['source'] = {'runId': receipt['provenance']['run'], 'attempt': original['attempt'],
                              'artifactId': original['artifact'], 'artifactSha256': original['sha256'],
                              'revision': receipt['manifest']['revision'], 'tree': receipt['manifest']['tree'],
                              'measuredAt': metadata['measuredAt']}
    (output/'metadata.json').write_bytes(encoded(metadata))
    (output/'policy.json').write_bytes(encoded(policy(root, environment, blob)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT/'build/report-v1')
    parser.add_argument('--environment', default=os.environ.get('BUILD_ENVIRONMENT'))
    parser.add_argument('--reused-receipt', type=Path,
                        help='Authenticated receipt from publication.py select (reused main publication)')
    args = parser.parse_args()
    if args.output.exists():
        raise ValueError('report-v1 staging directory must be new')
    receipt = json.loads(args.reused_receipt.read_text()) if args.reused_receipt else None
    prepare(ROOT, args.output, args.environment, int(os.environ['GITHUB_RUN_ID']),
            int(os.environ['GITHUB_RUN_ATTEMPT']), receipt)
    print(f'Prepared report-v1 inputs in {args.output}')


if __name__ == '__main__':
    main()
