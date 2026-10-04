"""Compare draft bodies in normal source files without putting them in the game build."""
import copy
import json
import math
import re
import shutil
from pathlib import Path

import source_build as sb
import diagnostic_object

CONFIG = 'config/GN7E69/comparisons.json'


def configured(root, binary):
    config = json.loads((root / CONFIG).read_text())
    if set(config) != {'schema', 'units'} or config['schema'] != 2 or not isinstance(config['units'], list):
        raise ValueError('Comparison configuration requires schema 2')
    accepted = json.loads((root / 'config/GN7E69/units.json').read_text())
    target = json.loads((root / 'config/GN7E69/baseline.json').read_text())
    sections = sb.target_sections(binary, target, {})
    evidence = {(a, b) for a, b, _ in sb.function_extents(root)}
    data_evidence = {(a, b) for a, b in sb.data_extents(root)}
    units, seen = [], []
    for candidate in config['units']:
        if set(candidate) != {'source', 'profile', 'evidence', 'sections', 'functions'}:
            raise ValueError('Comparison units need source, profile, evidence, sections and functions')
        if not candidate['source'].startswith('src/'):
            raise ValueError('Comparison source belongs in its normal src/ location')
        if not isinstance(candidate['functions'], list) or not candidate['functions']:
            raise ValueError('Comparison units require explicit target functions')
        compiled = copy.deepcopy(accepted)
        compiled['units'] = [{k: v for k, v in candidate.items() if k != 'functions'}]
        validated, _, _ = sb.load_manifest(compiled, sections, accepted['compiler'])
        unit = validated[0]
        existing = next((u for u in accepted['units'] if u['source'] == candidate['source']), None)
        if existing and existing['profile'] != candidate['profile']:
            raise ValueError('Accepted and comparison source must use the same compiler profile')
        for row in candidate['functions']:
            if set(row) != {'symbol', 'start', 'end'} or not isinstance(row['symbol'], str) or not row['symbol']:
                raise ValueError('Comparison functions need symbol, start and end')
            a, b = sb.address(row['start']), sb.address(row['end'])
            if (a, b) not in evidence or not any(s['kind'] == 'code' and not s['follows'] and
                    s['start'] <= a < b <= s['end'] for s in unit['sections']):
                raise ValueError('Comparison function lacks evidenced boundaries or code placement')
            seen.append((a, b))
        if len({r['symbol'] for r in candidate['functions']}) != len(candidate['functions']):
            raise ValueError('Duplicate comparison function symbol')
        for section in unit['sections']:
            if section['kind'] == 'data' and (section['start'], section['end']) not in data_evidence:
                raise ValueError('Comparison data needs evidenced boundaries')
            if section['kind'] == 'data':
                seen.append((section['start'], section['end']))
            if section['follows']:
                raise ValueError('Comparison data in code requires a separately supported target object')
        unit['functions'] = candidate['functions']
        units.append(unit)
    seen.sort()
    if any(b > c for (_, b), (c, _) in zip(seen, seen[1:])) or len({u['source'] for u in units}) != len(units):
        raise ValueError('Overlapping or duplicate comparison functions')
    return accepted, units


def generate(original, source_report, tool):
    import matching
    root = sb.ROOT
    binary = original.read_bytes()
    manifest, units = configured(root, binary)
    if not units:
        return []
    target = json.loads((root / 'config/GN7E69/baseline.json').read_text())
    target_sections = sb.target_sections(binary, target, json.loads((root/'config/GN7E69/analysis.json').read_text())['output_sections'])
    accepted = json.loads(source_report.read_text())['units']
    accepted_bounds = [(int(s['start'], 16), int(s['end'], 16)) for u in accepted for s in u['sections']]
    externals = {name: int(e['address'], 16) for name, e in manifest['externals'].items()}
    for u in accepted:
        # Only public definitions may resolve another file's undefined reference.
        stem = re.sub(r'[^A-Za-z0-9]+', '_', u['source']).strip('_')
        index = accepted.index(u)
        native = root / 'build/source/obj' / f'unit{index:03d}_{stem}.o'
        if sb.sha256(native) != u['native_object_sha256']:
            raise ValueError('Accepted external object differs from verified compiler receipt')
        public = {s['name'] for s in sb.read_elf(native.read_bytes())[1] if s['bind'] == sb.STB_GLOBAL and s['shndx'] != sb.SHN_UNDEF}
        externals.update({f['symbol']: int(f['address'], 16) for f in u['functions'] if f['symbol'] in public})
    compiler, wrapper = sb.setup_compiler.setup()
    sdk = sb.setup_compiler.setup_sdk() if any(u['compiler'] == 'mwcc' for u in units) else None
    work = root / 'build/matching/candidates'
    if work.exists():
        shutil.rmtree(work)
    work.mkdir(parents=True)
    result = []
    for index, unit in enumerate(units):
        folder = work / str(index)
        folder.mkdir()
        unit['object'] = folder / 'native.o'
        unit['depfile'] = folder / 'native.d'
        sb.compile_unit(unit, compiler, wrapper, sdk, manifest['include_dirs'], comparison=True)
        native_hash = sb.sha256(unit['object'])
        sections, symbols = sb.read_elf(unit['object'].read_bytes())
        allocated = {s['name']: s for s in sections if s['flags'] & sb.SHF_ALLOC and s['size']}
        placements = {s['section']: s for s in unit['sections']}
        if set(allocated) - set(placements):
            raise ValueError('Comparison object has unconfigured allocated sections')
        if any(not re.fullmatch(r'\.[A-Za-z0-9_.]+', name) for name in allocated):
            raise ValueError('Unsafe comparison section name')
        for name, section in allocated.items():
            kind = placements[name]['kind']
            if bool(section['flags'] & sb.SHF_EXECINSTR) != (kind == 'code') or section['type'] != (
                    sb.SHT_NOBITS if kind == 'bss' else sb.SHT_PROGBITS):
                raise ValueError('Comparison section type differs from placement')
        functions = {s['name']: s for s in symbols if s['type'] == 2 and s['size'] and s['shndx'] != sb.SHN_UNDEF}
        resolved = {}
        defined = {s['name'] for s in symbols if s['shndx'] != sb.SHN_UNDEF}
        for symbol in symbols:
            name = symbol['name']
            if symbol['shndx'] != sb.SHN_UNDEF or not name or name in defined:
                continue
            neutral = sb.NEUTRAL.fullmatch(name)
            if name in externals:
                resolved[name] = externals[name]
            elif neutral:
                resolved[name] = int(neutral[1], 16)
            else:
                raise ValueError(f'Unresolved comparison symbol {name}')
        targets = {f['symbol']: (int(f['address'],16), int(f['address'],16)+f['size'])
                   for u in accepted if u['source'] == unit['source'] for f in u['functions']}
        targets.update({r['symbol']: (sb.address(r['start']), sb.address(r['end'])) for r in unit['functions']})
        entries, pairs = [], []
        for number, row in enumerate(unit['functions']):
            a, b = sb.address(row['start']), sb.address(row['end'])
            symbol = functions.get(row['symbol'])
            if symbol is None:
                raise ValueError(f"Comparison compiler omitted function {row['symbol']}")
            section = next(s for s in allocated.values() if s['index'] == symbol['shndx'])
            if not section['flags'] & sb.SHF_EXECINSTR or symbol['value'] + symbol['size'] > section['size']:
                raise ValueError('Comparison function exceeds native code')
            overlaps = [(left, right) for left, right in accepted_bounds if a < right and left < b]
            if overlaps:
                if not any(left <= a < b <= right for left, right in overlaps):
                    raise ValueError('Comparison partially overlaps linked source')
            pair = folder / str(number)
            pair.mkdir()
            fragment = pair / 'fragment.o'
            fragment_symbol, references, reference_script = diagnostic_object.fragment(unit['object'].read_bytes(), section, symbol['value'],
                symbol['size'], a, functions, targets, placements, externals, fragment, target_sections)
            script = pair / 'link.ld'
            script.write_text(f"SECTIONS {{\n_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n" +
                              f"{section['name']} 0x{a:08X} : {{ *({section['name']}) }}\n" + '\n'.join(reference_script) + '\n}\n')
            output = pair / 'resolved.elf'
            sb.run('comparison link', [str(wrapper), str(compiler / 'ngcld.exe'), '-T', str(script),
                '-o', str(output), str(fragment), *map(str, references)], pair / 'link.log')
            linked_sections, linked_symbols = sb.read_elf(output.read_bytes())
            linked = [s for s in linked_symbols if s['name'] == fragment_symbol and s['type'] == 2]
            if len(linked) != 1 or linked[0]['value'] != a or linked[0]['size'] != symbol['size']:
                raise ValueError('Diagnostic link changed comparison function identity')
            linked_section = next(s for s in linked_sections if s['index'] == linked[0]['shndx'])
            offset = a - linked_section['addr']
            actual = linked_section['data'][offset:offset + symbol['size']]
            expected = sb.dol_bytes(binary, a, b)
            if expected is None or len(actual) != symbol['size']:
                raise ValueError('Comparison requires complete function bytes')
            score = matching.score_pair(tool, expected, actual,
                [{'name': 'function', 'value': 0, 'size': b-a, 'type': 2, 'shndx': 1}], 'code', pair)
            if overlaps:
                continue
            entries.append(dict(row, **score, type='function', kind='code', source=unit['source'], linked=False))
            pairs.append({'path': output.relative_to(root).as_posix(), 'sha256': sb.sha256(output),
                          'symbol': row['symbol'], 'output_symbol': fragment_symbol, 'start': row['start'], 'end': row['end']})
        for name, section in allocated.items():
            placement = placements[name]
            if placement['kind'] != 'data':
                continue
            a, b = placement['start'], placement['end']
            overlaps = [(left, right) for left, right in accepted_bounds if a < right and left < b]
            if overlaps:
                if not any(left <= a < b <= right for left, right in overlaps):
                    raise ValueError('Comparison data partially overlaps linked source')
                continue
            data_fragment = pair / ('data' + name + '.o')
            data_symbol, references, reference_script = diagnostic_object.fragment(unit['object'].read_bytes(), section, 0, section['size'],
                a, functions, targets, placements, externals, data_fragment, target_sections)
            data_script = pair / ('data' + name + '.ld')
            data_script.write_text(f"SECTIONS {{\n_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n{name} 0x{a:08X} : {{ *({name}) }}\n" + '\n'.join(reference_script) + '\n}\n')
            data_output = pair / ('data' + name + '.elf')
            sb.run('comparison data link', [str(wrapper), str(compiler/'ngcld.exe'), '-T', str(data_script),
                '-o', str(data_output), str(data_fragment), *map(str, references)], pair/'data-link.log')
            data_sections, _ = sb.read_elf(data_output.read_bytes())
            linked_section = next(s for s in data_sections if s['name'] == name)
            if linked_section['addr'] != a or linked_section['size'] != section['size']:
                raise ValueError('Diagnostic link changed data placement or size')
            pair_folder = folder / ('data-' + name.lstrip('.'))
            pair_folder.mkdir()
            expected, actual = sb.dol_bytes(binary, a, b), linked_section['data']
            score = matching.score_pair(tool, expected, actual, [], 'data', pair_folder)
            row = {'symbol': name, 'start': f'0x{a:08X}', 'end': f'0x{b:08X}'}
            entries.append(dict(row, **score, type='bytes', kind='data', source=unit['source'], linked=False))
            pairs.append(dict(row, output_symbol=data_symbol, path=data_output.relative_to(root).as_posix(), sha256=sb.sha256(data_output)))
        if sb.sha256(unit['object']) != native_hash:
            raise ValueError('Diagnostic linker modified native compiler input')
        result.append({'source': unit['source'], 'sha256': sb.sha256(unit['path']),
            'dependencies': unit['dependencies'], 'object': unit['object'].relative_to(root).as_posix(),
            'object_sha256': native_hash, 'depfile': unit['depfile'].relative_to(root).as_posix(),
            'depfile_sha256': sb.sha256(unit['depfile']), 'entries': entries, 'pairs': pairs})
    return result


def load(receipts, binary, root):
    _, units = configured(root, binary)
    if not isinstance(receipts, list) or [r['source'] for r in receipts] != [u['source'] for u in units]:
        raise ValueError('Comparison receipt omits configured draft source')
    accepted = json.loads((root / 'build/source/report.json').read_text())['units']
    linked_bounds = [(int(s['start'], 16), int(s['end'], 16)) for u in accepted for s in u['sections']]
    result = []
    for receipt, unit in zip(receipts, units):
        if receipt['sha256'] != sb.sha256(unit['path']) or not receipt.get('dependencies') or any(
                sb.sha256(root / sb.repository_path(p)) != digest for p, digest in receipt['dependencies'].items()):
            raise ValueError('Stale comparison source or dependencies')
        for path, digest in [(receipt['object'], receipt['object_sha256']), (receipt['depfile'], receipt['depfile_sha256'])] + [(p['path'], p['sha256']) for p in receipt['pairs']]:
            if not path.startswith('build/matching/candidates/') or sb.sha256(root / sb.repository_path(path)) != digest:
                raise ValueError('Stale or foreign comparison output')
        base = sb.stage(unit) if unit['compile_path'] else root
        if sb.dependencies(root / receipt['depfile'], base) != receipt['dependencies']:
            raise ValueError('Comparison dependencies differ from compiler receipt')
        expected_rows = {(r['symbol'], r['start'], r['end']) for r in unit['functions'] if not any(
            a <= sb.address(r['start']) < sb.address(r['end']) <= b for a, b in linked_bounds)}
        expected_rows |= {(s['section'], f"0x{s['start']:08X}", f"0x{s['end']:08X}") for s in unit['sections']
                          if s['kind'] == 'data' and not any(a <= s['start'] < s['end'] <= b for a, b in linked_bounds)}
        actual_rows = [(e['symbol'], e['start'], e['end']) for e in receipt['entries']]
        if len(set(actual_rows)) != len(actual_rows) or set(actual_rows) != expected_rows:
            raise ValueError('Comparison receipt omits configured functions')
        if len(receipt['entries']) != len(receipt['pairs']):
            raise ValueError('Comparison pairs do not cover measured functions')
        for entry, pair in zip(receipt['entries'], receipt['pairs']):
            row = {k: entry[k] for k in ('symbol', 'start', 'end')}
            if any(pair[k] != row[k] for k in row) or entry.get('linked') is not False or entry['source'] != unit['source']:
                raise ValueError('Comparison extent differs from configuration')
            a, b = sb.address(entry['start']), sb.address(entry['end'])
            sections, symbols = sb.read_elf((root / pair['path']).read_bytes())
            if entry['type'] == 'function' and entry['kind'] == 'code' and row in unit['functions']:
                candidates = [s for s in symbols if s['name'] == pair['output_symbol'] and s['type'] == 2]
                if len(candidates) != 1 or candidates[0]['value'] != a:
                    raise ValueError('Comparison output lacks configured function')
                symbol = candidates[0]
                section = next(s for s in sections if s['index'] == symbol['shndx'])
                offset = a - section['addr']
                actual = section['data'][offset:offset + symbol['size']]
                if offset < 0 or len(actual) != symbol['size']:
                    raise ValueError('Comparison output lacks complete function bytes')
            elif entry['type'] == 'bytes' and entry['kind'] == 'data':
                section = next(s for s in sections if s['name'] == row['symbol'])
                if section['addr'] != a:
                    raise ValueError('Comparison data differs from configured address')
                actual = section['data']
            else:
                raise ValueError('Invalid comparison kind')
            expected = sb.dol_bytes(binary, a, b)
            exact = b-a if actual == expected else 0
            if type(entry['matched']) is not int or entry['matched'] != exact or type(entry['fuzzy']) not in (int, float) \
                    or not math.isfinite(entry['fuzzy']) or not exact <= entry['fuzzy'] <= b-a:
                raise ValueError('Invalid comparison score or exact bytes')
            result.append(entry)
    return result
