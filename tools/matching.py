#!/usr/bin/env python3
"""Measure bounded compiled source with objdiff, without granting linked-build credit."""
import argparse
import csv
import hashlib
import json
import math
from pathlib import Path
import subprocess

import baseline
import source_build

ROOT = source_build.ROOT
CONFIG = 'config/GN7E69/comparisons.json'
INPUTS = ('tools/matching.py', 'tools/matching-tools.json', CONFIG,
          'config/GN7E69/units.json', 'config/GN7E69/evidence.tsv', 'tools/function_compare.py', 'tools/diagnostic_object.py', *source_build.TRUSTED_TOOLS)


def bindings():
    return {p: source_build.sha256(ROOT / p) for p in INPUTS}


def manifest():
    return json.loads((ROOT / 'config/GN7E69/units.json').read_text())


def score_pair(tool, expected, actual, symbols, kind, directory):
    """Compare resolved bytes; exactness uses bytes, fuzzy similarity uses objdiff."""
    size = len(expected)
    if not actual or not size:
        raise ValueError('Comparison requires a complete bounded range')
    if kind == 'data':
        symbols = [{'name': 'data', 'value': 0, 'size': size, 'shndx': 1, 'type': 1}]
    section = {'name': '.text' if kind == 'code' else '.data', 'flags': 6 if kind == 'code' else 3,
               'size': size, 'align': 4 if kind == 'code' else 1, 'type': 1}
    for label, data in (('target', expected), ('base', actual)):
        pair_symbols = [dict(s, size=len(data)) for s in symbols] if len(symbols) == 1 else symbols
        source_build.write_object(directory / (label + '.o'), [dict(section, data=data, size=len(data))], pair_symbols)
    output = directory / 'diff.json'
    output.unlink(missing_ok=True)
    subprocess.run([str(tool), 'diff', '-1', str(directory / 'target.o'), '-2', str(directory / 'base.o'),
                    '-o', str(output)], check=True, timeout=120, stdout=subprocess.DEVNULL)
    result = json.loads(output.read_text())['left']
    if kind == 'data':
        rows = [s for s in result.get('symbols', []) if s.get('name') == 'data']
        if len(rows) != 1:
            raise ValueError('objdiff omitted the bounded data symbol')
        percent = rows[0].get('match_percent', 0)
    else:
        rows = [s for s in result.get('symbols', []) if s.get('kind') == 'SYMBOL_FUNCTION']
        found = {s['name']: s for s in rows}
        if set(found) != {s['name'] for s in symbols}:
            raise ValueError('objdiff function inventory differs from bounded comparison')
        percent = sum(s['size'] * found[s['name']].get('match_percent', 0) for s in symbols) / size
    if not isinstance(percent, (int, float)) or not math.isfinite(percent) or not 0 <= percent <= 100:
        raise ValueError('Invalid objdiff score')
    # Instruction similarity can round to 100 for nonidentical bytes; it never grants exact credit.
    return {'matched': size if expected == actual else 0,
            'fuzzy': size if expected == actual else min(size, size * percent / 100)}


def generate(original, source_report, output):
    output.unlink(missing_ok=True)
    binary = original.read_bytes()
    target = json.loads((ROOT / 'config/GN7E69/baseline.json').read_text())
    if len(binary) != target['size'] or hashlib.sha1(binary).hexdigest() != target['sha1']:
        raise ValueError('Comparison target is not the configured original executable')
    work = ROOT / 'build/matching'
    work.mkdir(parents=True, exist_ok=True)
    import progress
    progress.source_ranges(target, source_report)
    build_report = json.loads(source_report.read_text())
    compiled = source_report.parent / 'main.dol'
    result_binary = compiled.read_bytes()
    if hashlib.sha1(result_binary).hexdigest() != build_report['output_sha1']:
        raise ValueError('Comparison output differs from its build report')
    tool = baseline.get_tool('objdiff', json.loads((ROOT / 'tools/matching-tools.json').read_text()),
                             source_build.baseline_system())
    accepted = {u['source'] for u in json.loads((ROOT / 'config/GN7E69/units.json').read_text())['units']}
    evidence = {(a, b) for a, b, _ in source_build.function_extents(ROOT)}
    entries = []
    functions = []
    for index, unit in enumerate(build_report['units']):
        for number, section in enumerate(unit['sections']):
            start, end = int(section['start'], 16), int(section['end'], 16)
            expected = source_build.dol_bytes(binary, start, end)
            actual = source_build.dol_bytes(result_binary, start, end)
            if expected is None:
                # Uninitialized storage has no fuzzy byte-comparison score.
                continue
            kind = 'code' if section['kind'] == 'code' and not section.get('follows') else 'data'
            rows = [f for f in unit['functions'] if start <= int(f['address'], 16) < end] if kind == 'code' else []
            if unit['source'] not in accepted and any((int(f['address'], 16), int(f['address'], 16) + f['size'])
                                                       not in evidence for f in rows):
                raise ValueError('Unlinked function boundaries require target evidence with both edges')
            spans = sorted((int(f['address'], 16), int(f['address'], 16) + f['size']) for f in rows)
            if any(a < start or b > end for a, b in spans) or any(b > c for (_, b), (c, _) in zip(spans, spans[1:])):
                raise ValueError('Comparison functions overlap or exceed the target range')
            directory = work / f'pair-{index}-{number}'
            directory.mkdir(exist_ok=True)
            for f in rows:
                a = int(f['address'], 16)
                pair = directory / f'{a:08X}'
                pair.mkdir(exist_ok=True)
                symbols = [{'name': 'function', 'value': 0, 'size': f['size'], 'shndx': 1, 'type': 2}]
                score = score_pair(tool, expected[a-start:a-start+f['size']], actual[a-start:a-start+f['size']],
                                   symbols, 'code', pair)
                entry = dict(score, type='function', start=f['address'], end=f"0x{a+f['size']:08X}", kind='code', source=unit['source'])
                entries.append(entry)
                functions.append(dict(entry))
            # Data and code padding are compared as bytes, rather than invented functions.
            cursor = start
            for a, b in spans + [(end, end)]:
                if cursor < a:
                    pair = directory / f'bytes-{cursor:08X}'
                    pair.mkdir(exist_ok=True)
                    score = score_pair(tool, expected[cursor-start:a-start], actual[cursor-start:a-start], [], 'data', pair)
                    entries.append(dict(score, type='bytes', start=f'0x{cursor:08X}', end=f'0x{a:08X}', kind=section['kind'], source=unit['source']))
                cursor = b
    payload = {'schema': 1, 'target_sha1': target['sha1'], 'inputs': bindings(),
               'objdiff': json.loads((ROOT / 'tools/matching-tools.json').read_text())['objdiff']['version'],
               'sources': {u['source']: {'sha256': u['source_sha256'], 'dependencies': u['dependencies']}
                           for u in build_report['units']}, 'entries': entries,
               'build_receipt': {'path': source_report.relative_to(ROOT).as_posix(),
                                 'sha256': source_build.sha256(source_report)}}
    import function_compare
    payload['candidates'] = function_compare.generate(original, source_report, tool)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(payload, indent=2) + '\n')
    return payload


def load(path, target, original):
    if hashlib.sha1(original).hexdigest() != target['sha1']:
        raise ValueError('Comparison target bytes differ from configured executable')
    data = json.loads(path.read_text())
    configured = manifest()['units']
    if data.get('schema') != 1 or data.get('target_sha1') != target['sha1'] or data.get('inputs') != bindings() \
            or set(data.get('sources', {})) != {u['source'] for u in configured}:
        raise ValueError('Stale or foreign objdiff measurements')
    receipt = data.get('build_receipt',{})
    if receipt.get('path') not in ('build/source/report.json','build/matching/compiled/report.json'):
        raise ValueError('Invalid comparison build receipt')
    receipt_path = ROOT/receipt['path']
    if source_build.sha256(receipt_path) != receipt.get('sha256'):
        raise ValueError('Stale comparison build receipt')
    build = json.loads(receipt_path.read_text())
    expected_manifest = source_build.sha256(ROOT/'config/GN7E69/units.json')
    if build.get('manifest_sha256') != expected_manifest or build.get('target_sha1') != target['sha1'] or \
        build.get('tools') != {p:source_build.sha256(ROOT/p) for p in source_build.TRUSTED_TOOLS}:
        raise ValueError('Foreign comparison build receipt')
    expected_sources = {u['source']:{'sha256':u['source_sha256'],'dependencies':u['dependencies']} for u in build['units']}
    if data['sources'] != expected_sources:
        raise ValueError('Comparison source bindings differ from compiler receipt')
    output_path = receipt_path.parent/'main.dol'
    result_binary = output_path.read_bytes()
    if hashlib.sha1(result_binary).hexdigest() != build['output_sha1']:
        raise ValueError('Comparison output differs from receipt')
    function_bounds = {(u['source'], f['address'], f"0x{int(f['address'],16)+f['size']:08X}")
                       for u in build['units'] for f in u['functions']}
    for source, entry in data['sources'].items():
        if source_build.sha256(ROOT / source) != entry['sha256'] or any(
                source_build.sha256(ROOT / name) != digest for name, digest in entry['dependencies'].items()):
            raise ValueError('Stale objdiff source or dependency')
    bounds = {(u['source'], s['start'], s['end']): s for u in configured for s in u['sections']}
    if data.get('objdiff') != json.loads((ROOT/'tools/matching-tools.json').read_text())['objdiff']['version']:
        raise ValueError('Wrong objdiff version')
    intervals = []
    for entry in data['entries']:
        a, b = source_build.address(entry['start']), source_build.address(entry['end'])
        size = b-a
        owners = [s for (source,start,end),s in bounds.items() if source == entry['source']
                  and int(start,16) <= a < b <= int(end,16)]
        expected_kind = 'code' if owners and owners[0]['placement'] in ('.text','.init') else 'data'
        if entry.get('type') not in ('function','bytes') or entry['kind'] != expected_kind:
            raise ValueError('Comparison kind differs from its configured placement')
        if entry['type']=='function' and (entry['source'],entry['start'],entry['end']) not in function_bounds:
            raise ValueError('Comparison function differs from compiler receipt')
        if size <= 0 or entry['kind'] not in ('code', 'data') or not any(
                source == entry['source'] and int(start,16) <= a < b <= int(end,16)
                for source, start, end in bounds):
            raise ValueError('Invalid comparison extent')
        if type(entry['matched']) is not int or entry['matched'] not in (0,size) or \
                type(entry['fuzzy']) not in (int,float) or not math.isfinite(entry['fuzzy']) or \
                not entry['matched'] <= entry['fuzzy'] <= size:
            raise ValueError('Invalid measured match score')
        expected = source_build.dol_bytes(original, a, b)
        actual = source_build.dol_bytes(result_binary, a, b)
        if expected is None or actual is None or len(expected) != size or len(actual) != size:
            raise ValueError('Comparison extent lacks resolved executable bytes')
        exact = size if expected == actual else 0
        if entry['matched'] != exact:
            raise ValueError('Comparison exact score differs from resolved bytes')
        intervals.append((a,b))
    scored_functions = {(e['source'],e['start'],e['end']) for e in data['entries'] if e['type']=='function'}
    if scored_functions != function_bounds:
        raise ValueError('Comparison report omits compiler functions')
    intervals.sort()
    if any(b > c for (_,b),(c,_) in zip(intervals,intervals[1:])):
        raise ValueError('Overlapping objdiff measurements')
    for (source,start,end),section in bounds.items():
        if section['placement'] in ('.bss','.sbss'):
            continue
        covered = sum(b-a for e in data['entries'] if e['source']==source
                      for a,b in [(int(e['start'],16),int(e['end'],16))]
                      if int(start,16)<=a<b<=int(end,16))
        if covered != int(end,16)-int(start,16):
            raise ValueError('Comparison report omits configured bytes')
    import function_compare
    candidate_entries = function_compare.load(data.get('candidates', []), original, ROOT)
    result = dict(data, entries=[dict(e, linked=True) for e in data['entries']] + candidate_entries)
    return result


def apply(data, measurement):
    """Roll up unlinked comparison credit without changing ownership or linked credit."""
    accepted = {u['source'] for u in json.loads((ROOT / 'config/GN7E69/units.json').read_text())['units']}
    entries = [e for e in measurement['entries'] if not e.get('linked', e['source'] in accepted)]

    def subtract(spans, cuts):
        for left, right in cuts:
            spans = [(a, min(b,left)) for a,b in spans if a < left and a < min(b,left)] + \
                    [(max(a,right),b) for a,b in spans if b > right and max(a,right) < b]
        return spans

    def fill(item, spans):
        if 'mapped_extents' in item:
            spans = [(int(e['start'],16),int(e['end'],16)) for e in item['mapped_extents']]
        if 'address' in item:
            a = int(item['address'],16)
            spans = [(a,a+item['size'])]
        if item.get('children'):
            addressed = [(int(c['address'],16),int(c['address'],16)+c['size'])
                         for c in item['children'] if 'address' in c]
            remainder = subtract(spans,addressed)
            anonymous = [c for c in item['children'] if 'address' not in c and 'mapped_extents' not in c]
            if len(anonymous)>1:
                raise ValueError('Ambiguous unaddressed map leaves')
            for child in item['children']:
                fill(child,remainder if 'address' not in child else [])
            for field in ('matched','fuzzy'):
                item[field] = sum(child[field] for child in item['children'])
        else:
            matched = fuzzy = item['linked']
            for entry in entries:
                if entry['kind'] != item['kind']:
                    continue
                start,end = int(entry['start'],16),int(entry['end'],16)
                overlap = sum(max(0,min(b,end)-max(a,start)) for a,b in spans)
                matched += overlap if entry['matched'] else 0
                fuzzy += overlap * entry['fuzzy']/(end-start)
            if not 0 <= item['linked'] <= matched <= fuzzy <= item['size'] + 1e-6:
                raise ValueError('Comparison credit exceeds map range')
            item['matched'],item['fuzzy'] = matched,min(item['size'],fuzzy)
    for items in (data['sections'],data['files']):
        for item in items:
            spans = [(int(e['start'],16),int(e['end'],16)) for e in item.get('mapped_extents',[])]
            fill(item,spans)
    for kind in ('code','data'):
        for field in ('matched','fuzzy'):
            section_sum = sum(i[field] for i in data['sections'] if i['kind']==kind)
            file_sum = sum(i[field] for i in data['files'] if i['kind']==kind)
            if not math.isclose(section_sum,file_sum,abs_tol=1e-6):
                raise ValueError('Comparison credit differs between maps')
            data['measures'][kind][field] = file_sum
    additional_exact = 0
    if data['functions']['total'] is not None:
        with (ROOT/'config/GN7E69/evidence.tsv').open() as evidence:
            exact_bounds = {(int(row['start'],16),int(row['end'],16))
                            for row in csv.DictReader(evidence,delimiter='\t')
                            if row['kind']=='function' and row['start_boundary']==row['end_boundary']=='exact'}
        candidate_exact = {(int(e['start'],16),int(e['end'],16)) for e in entries
                           if e.get('type')=='function' and e['matched']==int(e['end'],16)-int(e['start'],16)}
        additional_exact = sum((int(c['address'],16),int(c['address'],16)+c['size']) in
                               (candidate_exact & exact_bounds) and c['linked']<c['size'] and c['matched']==c['size']
                               for s in data['sections'] if s['kind']=='code'
                               for c in s['children'] if 'address' in c)
        previous = data.get('comparison',{}).get('additional_exact_functions',0)
        data['functions']['exact'] += additional_exact - previous
    data['comparison'] = {'tool': measurement['objdiff'], 'basis':'resolved-bounded-objdiff',
                          'additional_exact_functions':additional_exact}
    return data


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--original',type=Path,required=True)
    parser.add_argument('--source-report',type=Path,default=ROOT/'build/source/report.json')
    parser.add_argument('--output',type=Path,default=ROOT/'build/matching/report.json')
    args=parser.parse_args()
    result=generate(args.original,args.source_report,args.output)
    print(f"Measured {sum(e['type']=='function' for e in result['entries'])} compiled functions with objdiff")

if __name__=='__main__':
    main()
