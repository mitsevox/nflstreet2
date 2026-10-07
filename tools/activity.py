#!/usr/bin/env python3
"""Export linked-build history and exact-function credits from recorded evidence."""
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


_HISTORICAL_BLOBS_CACHE = {}
_SOURCE_BLOB_CACHE = {}
_VERIFIED_COMMITS_CACHE = set()


def clear_cache():
    _HISTORICAL_BLOBS_CACHE.clear()
    _SOURCE_BLOB_CACHE.clear()
    _VERIFIED_COMMITS_CACHE.clear()


def provenance_commit(root, commit, fetch_missing=False):
    if not SHA.fullmatch(commit):
        raise ValueError('Invalid source provenance commit')
    key = (str(root), commit)
    if key in _VERIFIED_COMMITS_CACHE:
        return
    def present():
        return subprocess.run(['git','cat-file','-e',commit+'^{commit}'], cwd=root,
                              stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode == 0
    if present():
        _VERIFIED_COMMITS_CACHE.add(key)
        return
    if fetch_missing:
        # Explicit host-side opt-in: retrieve only the pinned object from this checkout's origin.
        subprocess.run(['git','fetch','--no-tags','origin',commit], cwd=root,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=False)
    if not present():
        raise ValueError('Source provenance commit is unavailable; fetch the pinned commit from origin')
    _VERIFIED_COMMITS_CACHE.add(key)


def source_blob(root, commit, source):
    key = (str(root), commit, source)
    if key in _SOURCE_BLOB_CACHE:
        return _SOURCE_BLOB_CACHE[key]
    result = subprocess.run(['git','rev-parse',commit+':'+source], cwd=root,
                            capture_output=True, text=True)
    if result.returncode:
        raise ValueError('Source provenance commit lacks the recorded source')
    blob = result.stdout.strip()
    _SOURCE_BLOB_CACHE[key] = blob
    return blob


def historical_source_blobs(root, revision, source):
    # The current revision alone is insufficient: prove an actual source-path tree in its history.
    if any(character in source for character in ('\r', '\n', '\0')):
        raise ValueError('Invalid attribution source path')
    key = (str(root), revision, source)
    if key in _HISTORICAL_BLOBS_CACHE:
        return _HISTORICAL_BLOBS_CACHE[key]
    commits = subprocess.check_output(['git','rev-list',revision,'--',source], cwd=root, text=True).splitlines()
    if not commits:
        _HISTORICAL_BLOBS_CACHE[key] = set()
        return set()
    # Query real historical trees together; missing paths remain missing evidence.
    queries = [commit + ':' + source for commit in commits]
    result = subprocess.run(['git', 'cat-file', '--batch-check=%(objectname)'], cwd=root,
                            input=''.join(query + '\n' for query in queries),
                            capture_output=True, text=True, check=True)
    rows = result.stdout.splitlines()
    if len(rows) != len(queries) or any(
            not SHA.fullmatch(row) and row != query + ' missing'
            for query, row in zip(queries, rows)):
        raise ValueError('Invalid Git historical source response')
    blobs = set(rows)
    _HISTORICAL_BLOBS_CACHE[key] = blobs
    return blobs


def historical_source_blob(root, revision, source, blob):
    return blob in historical_source_blobs(root, revision, source)


def merged_source(root, revision, historical_source, source):
    # A merge into a combined source: some commit in this history writes the current
    # path while removing the original path that its first parent still had.
    if any(character in path for path in (historical_source, source)
           for character in ('\r', '\n', '\0')):
        raise ValueError('Invalid attribution source path')
    commits = subprocess.check_output(['git','rev-list',revision,'--',historical_source],
                                      cwd=root, text=True).splitlines()
    queries = []
    for commit in commits:
        queries += [commit + ':' + source, commit + '^:' + source,
                    commit + ':' + historical_source, commit + '^:' + historical_source]
    if not queries:
        return False
    result = subprocess.run(['git', 'cat-file', '--batch-check=%(objectname)'], cwd=root,
                            input=''.join(query + '\n' for query in queries),
                            capture_output=True, text=True, check=True)
    rows = result.stdout.splitlines()
    if len(rows) != len(queries) or any(
            not SHA.fullmatch(row) and row != query + ' missing'
            for query, row in zip(queries, rows)):
        raise ValueError('Invalid Git historical source response')
    return any(SHA.fullmatch(rows[i]) and rows[i] != rows[i + 1]
               and not SHA.fullmatch(rows[i + 2]) and SHA.fullmatch(rows[i + 3])
               for i in range(0, len(rows), 4))


def contributors(root, ledger, build, revision, fetch_missing=False, exact_inventory=None):
    if ledger.get('schema') != 1 or ledger.get('target') != 'GN7E69' or build.get('complete') != 'identical':
        raise ValueError('Function credit requires the verified source build')
    profiles = ledger.get('contributors', {})
    for login, profile in profiles.items():
        if not LOGIN.fullmatch(login) or type(profile.get('id')) is not int or profile['id'] <= 0:
            raise ValueError('Invalid contributor identity')
    inventory = {(u['source'], f['address']) for u in build['units'] for f in u['functions']}
    if sum(len(u['functions']) for u in build['units']) != len(inventory):
        raise ValueError('Compiler inventory duplicates a function')
    if exact_inventory is not None:
        if not inventory <= exact_inventory:
            raise ValueError('Exact inventory omits a verified linked function')
        inventory = exact_inventory
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
        commit = provenance['commit']
        provenance_commit(root, commit, fetch_missing)
        historical_source = provenance.get('original_source', source)
        if not isinstance(historical_source, str) or not historical_source.startswith('src/') or '..' in Path(historical_source).parts:
            raise ValueError('Invalid attribution original source path')
        if source_blob(root, commit, historical_source) != provenance['introduced_blob']:
            raise ValueError('Attribution differs from the introduced source')
        original_commit = provenance.get('original_commit', commit)
        provenance_commit(root, original_commit, fetch_missing)
        if source_blob(root, original_commit, historical_source) != original:
            raise ValueError('Attribution differs from the original source')
        if not historical_source_blob(root, revision, historical_source, provenance['introduced_blob']):
            raise ValueError('Introduced source is absent from this revision history')
        if 'merged_source' in provenance:
            if provenance['merged_source'] is not True or historical_source == source \
                    or 'renamed_blob' in provenance:
                raise ValueError('Invalid merged source provenance')
            if not merged_source(root, revision, historical_source, source):
                raise ValueError('Merged source lacks a commit that replaces the original path')
        elif historical_source != source:
            renamed_blob = provenance.get('renamed_blob', provenance['introduced_blob'])
            if not isinstance(renamed_blob, str) or not SHA.fullmatch(renamed_blob):
                raise ValueError('Invalid renamed source blob')
            if not all(historical_source_blob(root, revision, path, renamed_blob)
                       for path in (historical_source, source)):
                raise ValueError('Renamed source is absent from old or current path history')
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
        raise ValueError(f'Unattributed exact function {source} {address}; update contributors.json')
    return [{'login':login, 'id':profiles[login]['id'], 'functions':len(functions),
             'pull_requests':sorted(references[login])}
            for login, functions in sorted(counts.items(), key=lambda pair:(-len(pair[1]), pair[0])) if functions]


def exact_functions(site):
    """Use full function identities from an independently validated progress receipt."""
    inventory = set()
    def visit(item):
        source = item.get('comparison_source') or item.get('source')
        if item.get('type') == 'function' and source and item['size'] > 0 \
                and item['size'] == item['original_size'] and item['matched'] == item['size']:
            key = (source, item['function_address'])
            if key in inventory:
                raise ValueError('Exact function appears more than once in the public map')
            inventory.add(key)
        for child in item.get('children', []):
            visit(child)
    for item in site['files']:
        visit(item)
    if len(inventory) != site['functions']['exact']:
        raise ValueError('Exact function count differs from the attribution inventory')
    return inventory


def squash_preflight(root, ledger, build, revision, base, exact_inventory=None):
    # Model the repository's squash merge: no contribution-branch ancestors survive.
    check_ancestor(root, base, revision)
    tree = subprocess.check_output(['git','rev-parse',revision+'^{tree}'], cwd=root, text=True).strip()
    squashed = subprocess.check_output(
        ['git','-c','user.name=Attribution preflight','-c','user.email=preflight@example.invalid',
         'commit-tree',tree,'-p',base], cwd=root, input='Private attribution squash preflight\n', text=True).strip()
    return contributors(root, ledger, build, squashed, exact_inventory=exact_inventory)


def export(root, site, source_report, previous=None, append=False, fetch_missing=False, squash_base=None):
    build = json.loads(source_report.read_text())
    if site.get('baseline') != 'verified' or site.get('target_sha1') != build.get('target_sha1'):
        raise ValueError('Activity target differs from the public progress build')
    import progress
    verified = progress.report((source_report.parent/'main.dol').read_bytes(), site['revision'],
                               source_report, root/'build/analysis',
                               root/'build/matching/report.json' if json.loads((root/'config/GN7E69/comparisons.json').read_text())['units'] else None)
    if site.get('source') != verified['source'] or site.get('functions') != verified['functions'] or any(
            site['measures'][kind].get(field) != verified['measures'][kind].get(field)
            for kind in ('code','data') for field in ('linked','matched','fuzzy','total')):
        raise ValueError('Activity measurements differ from the verified source receipt')
    return _export_verified(root, verified, source_report, previous, append, fetch_missing, squash_base)


def _export_verified(root, site, source_report, previous=None, append=False, fetch_missing=False, squash_base=None):
    """Internal pipeline stage; site must come directly from progress.report in this process."""
    import hashlib
    build = json.loads(source_report.read_text())
    def mapped_functions(item):
        if item.get('type') == 'function' and item.get('linked',0) > 0:
            return {(item['source'],item['function_address'],item['original_size'])}
        return set().union(*(mapped_functions(child) for child in item.get('children',[])))
    mapped = set().union(*(mapped_functions(item) for item in site['files']))
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
    exact = exact_functions(site)
    ledger = json.loads((root/'config/GN7E69/contributors.json').read_text())
    credits = contributors(root, ledger, build, site['revision'], fetch_missing, exact)
    if squash_base:
        if squash_preflight(root, ledger, build, site['revision'], squash_base, exact) != credits:
            raise ValueError('Squash preflight changes original source attribution')
    return {'schema':1, 'target':'GN7E69', 'target_sha1':site['target_sha1'],
            'revision':site['revision'], 'snapshots':history,
            'contribution_basis':'exact-functions', 'credited_functions':len(exact),
            'contributors':credits}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--site', type=Path, default=ROOT/'build/site/progress.json')
    parser.add_argument('--source-report', type=Path, default=ROOT/'build/source/report.json')
    parser.add_argument('--output', type=Path, default=ROOT/'build/site/activity.json')
    parser.add_argument('--previous', type=Path)
    parser.add_argument('--append-current', action='store_true')
    parser.add_argument('--fetch-provenance', action='store_true',
                        help='Fetch unavailable pinned source provenance commits from origin (CI host only)')
    parser.add_argument('--squash-base', help='Verify attribution after a synthetic squash onto the actual PR base SHA')
    args = parser.parse_args()
    site = json.loads(args.site.read_text())
    previous = json.loads(args.previous.read_text()) if args.previous else None
    if args.append_current and previous is None:
        raise ValueError('Main publication requires restored prior deployment history')
    result = export(ROOT, site, args.source_report, previous, args.append_current, args.fetch_provenance, args.squash_base)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print(f"Exported {len(result['snapshots'])} verified snapshots and {len(result['contributors'])} contributors")


if __name__ == '__main__':
    main()
