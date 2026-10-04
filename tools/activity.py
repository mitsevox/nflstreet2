#!/usr/bin/env python3
"""Export linked-build history and function credits from recorded evidence."""
import argparse
from datetime import datetime
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[1]
SHA = re.compile(r"[a-f0-9]{40}")
LOGIN = re.compile(r"[A-Za-z0-9](?:[A-Za-z0-9-]{0,37}[A-Za-z0-9])?")


def timestamp(value):
    parsed = datetime.fromisoformat(value.replace('Z', '+00:00'))
    if parsed.tzinfo is None:
        raise ValueError('History timestamps require a timezone')
    return parsed.timestamp()


def validate_history(data, target_sha1):
    if data.get('schema') != 1 or data.get('target') != 'GN7E69' or data.get('target_sha1') != target_sha1:
        raise ValueError('Foreign progress history')
    rows = data.get('snapshots')
    if not isinstance(rows, list) or len(rows) > 10000:
        raise ValueError('Invalid progress history')
    seen = set()
    for row in rows:
        revision = row.get('revision', '')
        if not SHA.fullmatch(revision) or revision in seen:
            raise ValueError('Duplicate or invalid history revision')
        seen.add(revision)
        timestamp(row['built_at'])
        for kind in ('code', 'data'):
            measure = row[kind]
            if type(measure.get('total')) is not int or type(measure.get('linked')) is not int or \
                    not 0 <= measure['linked'] <= measure['total'] or measure['total'] <= 0:
                raise ValueError('Invalid linked history measurement')
        provenance = row.get('provenance', {})
        if provenance.get('kind') == 'workflow-artifact':
            if any(type(provenance.get(key)) is not int or provenance[key] <= 0 for key in ('run', 'artifact')) or \
                    not re.fullmatch(r'[a-f0-9]{64}', provenance.get('report_sha256', '')):
                raise ValueError('History lacks artifact provenance')
        elif provenance.get('kind') == 'verified-source-build':
            if not re.fullmatch(r'[a-f0-9]{64}', provenance.get('report_sha256', '')):
                raise ValueError('History lacks build provenance')
        else:
            raise ValueError('History lacks verification provenance')
    return rows


def merge_history(seed, previous, current=None):
    target = seed['target_sha1']
    combined = {}
    for document in (seed, previous):
        if document is None:
            continue
        for row in validate_history(document, target):
            old = combined.get(row['revision'])
            if old and any(old[k] != row[k] for k in ('code', 'data')):
                raise ValueError('One revision has conflicting historical measurements')
            # Keep its first successful measurement, not a later rerun's timestamp.
            if old is None or timestamp(row['built_at']) < timestamp(old['built_at']):
                combined[row['revision']] = row
    if current is not None:
        document = {'schema':1, 'target':'GN7E69', 'target_sha1':target, 'snapshots':[current]}
        for row in validate_history(document, target):
            old = combined.get(row['revision'])
            if old and any(old[k] != row[k] for k in ('code', 'data')):
                raise ValueError('Current build disagrees with its recorded measurement')
            if old is None:
                combined[row['revision']] = row
    return sorted(combined.values(), key=lambda row: (timestamp(row['built_at']), row['revision']))


def check_ancestor(root, commit, revision):
    if not SHA.fullmatch(commit) or subprocess.run(
            ['git','merge-base','--is-ancestor',commit,revision], cwd=root,
            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode:
        raise ValueError('Activity provenance is outside this revision history')


def contributors(root, ledger, build, revision):
    if ledger.get('schema') != 1 or ledger.get('target') != 'GN7E69' or build.get('complete') != 'identical':
        raise ValueError('Function credit requires the verified source build')
    profiles = ledger.get('contributors', {})
    for login, profile in profiles.items():
        if not LOGIN.fullmatch(login) or type(profile.get('id')) is not int or profile['id'] <= 0:
            raise ValueError('Invalid contributor identity')
    inventory = {(u['source'], f['address']) for u in build['units'] for f in u['functions']}
    if sum(len(u['functions']) for u in build['units']) != len(inventory):
        raise ValueError('Compiler inventory duplicates a function')
    counts = {login:set() for login in profiles}
    references = {login:set() for login in profiles}
    seen = set()
    for entry in ledger['entries']:
        source = entry.get('source')
        if not isinstance(source,str) or not source.startswith('src/') or '..' in Path(source).parts:
            raise ValueError('Invalid attribution source path')
        provenance = entry['provenance']
        if not SHA.fullmatch(provenance.get('introduced_blob','')):
            raise ValueError('Invalid introduced source blob')
        original = provenance.get('original_blob',provenance['introduced_blob'])
        if not SHA.fullmatch(original) or (original != provenance['introduced_blob'] and not provenance.get('integration_adjustment')):
            raise ValueError('Unexplained source integration adjustment')
        people = entry['contributors']
        if not people or len(set(people)) != len(people) or any(p not in profiles for p in people):
            raise ValueError('Function attribution lacks contributor identity')
        for key in ('pull_request','merged_via'):
            if type(provenance.get(key)) is not int or provenance[key] <= 0:
                raise ValueError('Attribution lacks contribution PR provenance')
        check_ancestor(root, provenance['commit'], revision)
        blob = subprocess.check_output(['git','rev-parse',provenance['commit']+':'+entry['source']],
                                       cwd=root, text=True).strip()
        if blob != provenance['introduced_blob']:
            raise ValueError('Attribution differs from the introduced source')
        for address in entry['functions']:
            if not re.fullmatch(r'0x[0-9A-F]{8}', address):
                raise ValueError('Invalid credited function address')
            key = (entry['source'], address)
            if key in seen:
                raise ValueError('Function credited more than once')
            seen.add(key)
            if key not in inventory:
                continue  # Retired functions keep their historical record, but no current credit.
            for login in people:
                counts[login].add(key)
                references[login].add(provenance['pull_request'])
    missing = inventory - seen
    if missing:
        source, address = sorted(missing)[0]
        raise ValueError(f'Unattributed compiled function {source} {address}; update contributors.json')
    return [{'login':login, 'id':profiles[login]['id'], 'functions':len(functions),
             'pull_requests':sorted(references[login])}
            for login, functions in sorted(counts.items(), key=lambda pair:(-len(pair[1]), pair[0])) if functions]


def export(root, site, source_report, previous=None, append=False):
    import hashlib
    build = json.loads(source_report.read_text())
    if site.get('baseline') != 'verified' or site.get('target_sha1') != build.get('target_sha1'):
        raise ValueError('Activity target differs from the public progress build')
    import progress
    verified = progress.report((source_report.parent/'main.dol').read_bytes(), site['revision'],
                               source_report, root/'build/analysis')
    if site.get('source') != verified['source'] or any(
            site['measures'][kind][field] != verified['measures'][kind][field]
            for kind in ('code','data') for field in ('linked','total')):
        raise ValueError('Activity measurements differ from the verified source receipt')
    def mapped_functions(item):
        if item.get('type') == 'function' and item.get('linked',0) > 0:
            return {(item['source'],item['function_address'],item['original_size'])}
        return set().union(*(mapped_functions(child) for child in item.get('children',[])))
    mapped = set().union(*(mapped_functions(item) for item in verified['files']))
    compiled = {(u['source'],f['address'],f['size']) for u in build['units'] for f in u['functions']}
    if mapped != compiled:
        raise ValueError('Compiler function receipt differs from the verified public inventory')
    seed = json.loads((root/'config/GN7E69/history.json').read_text())
    current = None
    if append:
        check_ancestor(root, site['revision'], 'refs/remotes/origin/main')
        current = {'revision':site['revision'], 'built_at':site['built_at'],
                   **{kind:{'linked':site['measures'][kind]['linked'], 'total':site['measures'][kind]['total']}
                      for kind in ('code','data')},
                   'provenance':{'kind':'verified-source-build',
                                 'report_sha256':hashlib.sha256(source_report.read_bytes()).hexdigest()}}
    history = merge_history(seed, previous, current)
    for row in history:
        check_ancestor(root, row['revision'], site['revision'])
    ledger = json.loads((root/'config/GN7E69/contributors.json').read_text())
    return {'schema':1, 'target':'GN7E69', 'target_sha1':site['target_sha1'],
            'revision':site['revision'], 'snapshots':history,
            'contributors':contributors(root, ledger, build, site['revision'])}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--site', type=Path, default=ROOT/'build/site/progress.json')
    parser.add_argument('--source-report', type=Path, default=ROOT/'build/source/report.json')
    parser.add_argument('--output', type=Path, default=ROOT/'build/site/activity.json')
    parser.add_argument('--previous', type=Path)
    parser.add_argument('--append-current', action='store_true')
    args = parser.parse_args()
    site = json.loads(args.site.read_text())
    previous = json.loads(args.previous.read_text()) if args.previous else None
    if args.append_current and previous is None:
        raise ValueError('Main publication requires restored prior deployment history')
    result = export(ROOT, site, args.source_report, previous, args.append_current)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print(f"Exported {len(result['snapshots'])} verified snapshots and {len(result['contributors'])} contributors")


if __name__ == '__main__':
    main()
