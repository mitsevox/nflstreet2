"""Compare draft bodies in normal source files without putting them in the game build."""
import copy
import json
import math
import re
import shutil
import struct
from pathlib import Path

import source_build as sb
import diagnostic_object

CONFIG = 'config/GN7E69/comparisons.json'


def data_slices(source, placement, linked):
    """Return the target slices of a comparison data placement that lie outside linked source.

    `linked` holds (source, start, end) ranges of the accepted build. The full placement still
    positions the compiled section for relocating draft code; only these slices are measured.
    Linked bytes inside the placement must belong to the same source file and lie wholly within
    it, so every placement byte is either linked source of that file or a measured slice."""
    a, b = placement['start'], placement['end']
    cuts = []
    for owner, left, right in linked:
        if left < b and a < right:
            if owner != source:
                raise ValueError("Comparison data overlaps another file's linked source")
            if left <= a and b <= right and (left, right) != (a, b):
                raise ValueError('Comparison data lies inside linked source')
            if not a <= left < right <= b:
                raise ValueError('Comparison data partially overlaps linked source')
            cuts.append((left, right))
    slices, cursor = [], a
    for left, right in sorted(cuts):
        if left > cursor:
            slices.append((cursor, left))
        cursor = max(cursor, right)
    if cursor < b:
        slices.append((cursor, b))
    return slices


def linked_ranges(units, address=lambda value: value):
    return [(u['source'], address(s['start']), address(s['end'])) for u in units for s in u['sections']]


STT_NOTYPE, STT_OBJECT = 0, 1


def accepted_data_symbols(objects, externals):
    """Resolve public data objects defined by accepted (linked) source.

    `objects` holds (report sections, ELF sections, ELF symbols) for each accepted native object.
    A public data symbol (STT_OBJECT, or STT_NOTYPE as ProDG emits for .bss
    variables) resolves to its linked target address: the verified placement start
    of its compiled section plus the symbol value. Symbols in code sections are
    left to the function inventory. Sections whose compiled size differs from their
    placement, data placed after code, repeated section names and symbols outside their section
    resolve nothing. A name defined more than once, or also known at a different address from
    `externals`, is returned as ambiguous so a comparison that references it fails closed."""
    resolved, ambiguous = {}, set()
    for placements, sections, symbols in objects:
        by_name = {}
        for placement in placements:
            name = placement.get('section')
            if name is None:
                continue
            start, end = sb.address(placement['start']), sb.address(placement['end'])
            exact = placement.get('compiled') == end - start and not placement.get('follows')
            by_name[name] = None if name in by_name or not exact else (start, end)
        for symbol in symbols:
            if symbol['bind'] != sb.STB_GLOBAL or symbol['type'] not in (STT_NOTYPE, STT_OBJECT) or not symbol['name']:
                continue
            if symbol['shndx'] in (sb.SHN_UNDEF, sb.SHN_ABS, sb.SHN_COMMON) or symbol['shndx'] >= len(sections):
                continue
            if sections[symbol['shndx']]['flags'] & sb.SHF_EXECINSTR:
                continue
            place = by_name.get(sections[symbol['shndx']]['name'])
            name = symbol['name']
            if place is None or symbol['value'] + symbol['size'] > place[1] - place[0]:
                ambiguous.add(name)
                continue
            value = place[0] + symbol['value']
            if name in resolved and resolved[name] != value:
                ambiguous.add(name)
            resolved[name] = value
    for name, value in resolved.items():
        if name in externals and externals[name] != value:
            ambiguous.add(name)
    for name in ambiguous:
        resolved.pop(name, None)
    return resolved, ambiguous


def comparison_references(externals, data_symbols):
    """Addresses that another file's references may resolve to: public data of accepted source,
    overridden by configured externals and accepted function addresses."""
    references = dict(data_symbols)
    references.update(externals)
    return references


def discarded_references(native, sections, symbols, discarded):
    """Undefined names that only the listed discarded functions reference.

    A discarded function is compiled with its file but is neither registered nor measured, so a
    callee that the target also discarded may stay unresolved. Every relocation to such a name
    must lie inside one of these functions; any other use still has to resolve."""
    if not discarded:
        return set()
    bodies = [s for s in symbols if s['name'] in discarded and s['type'] == 2 and s['size']
              and s['shndx'] != sb.SHN_UNDEF]
    if {s['name'] for s in bodies} != set(discarded) or len(bodies) != len(discarded):
        raise ValueError('Comparison discarded functions must be defined once in the compiled source')
    inside, outside = set(), set()
    for relocation_section in sections:
        if relocation_section['type'] != 4:
            continue
        for at in range(relocation_section['offset'], relocation_section['offset'] + relocation_section['size'], 12):
            position, info, _ = struct.unpack_from('>IIi', native, at)
            index = info >> 8
            if not 0 < index <= len(symbols):
                raise ValueError('Invalid native relocation symbol')
            symbol = symbols[index - 1]
            if symbol['shndx'] != sb.SHN_UNDEF:
                continue
            within = any(b['shndx'] == relocation_section['info'] and b['value'] <= position < b['value'] + b['size']
                         for b in bodies)
            (inside if within else outside).add(symbol['name'])
    return inside - outside


def resolve_undefined(symbols, references, ambiguous, discarded_only=frozenset()):
    """Resolve a comparison object's undefined references.

    Names in `references` resolve to their address and neutral fn_/lbl_ labels resolve by their
    address. An ambiguous accepted data name always fails closed, as does any other unknown name,
    except one that only registered discarded functions reference (see discarded_references)."""
    defined = {s['name'] for s in symbols if s['shndx'] != sb.SHN_UNDEF}
    resolved = {}
    for symbol in symbols:
        name = symbol['name']
        if symbol['shndx'] != sb.SHN_UNDEF or not name or name in defined:
            continue
        if name in discarded_only and name not in references and not sb.NEUTRAL.fullmatch(name):
            continue
        if name in ambiguous:
            raise ValueError(f'Ambiguous comparison symbol {name}')
        neutral = sb.NEUTRAL.fullmatch(name)
        if name in references:
            resolved[name] = references[name]
        elif neutral:
            resolved[name] = int(neutral[1], 16)
        else:
            raise ValueError(f'Unresolved comparison symbol {name}')
    return resolved


def measured_data(placement):
    """Initialized data placements are measured, including read-only data placed after code."""
    return placement['kind'] == 'data' or bool(placement['follows'])


def entry_kind(placement):
    """Data after code is credited to the code section that holds it, as for linked source."""
    return 'code' if placement['follows'] else 'data'


def storage_entries(rows, placements, data_evidence):
    """Validate a comparison unit's optional address map for its uninitialized symbols.

    Function-local statics in public inline functions become COMMON symbols under -fno-weak,
    and the target can interleave them with the file's own .sbss/.bss objects, so contiguous
    section placement cannot locate them. Each row names one symbol and its target extent,
    which must equal an exact evidence data row and lie inside one of the unit's own
    uninitialized placements; names are unique and extents do not overlap. The map only
    positions references; uninitialized storage is never measured."""
    if rows is None:
        return None
    if not isinstance(rows, list) or not rows:
        raise ValueError('Comparison storage must list evidenced uninitialized symbols')
    entries = {}
    for row in rows:
        if not isinstance(row, dict) or set(row) != {'symbol', 'start', 'end'} \
                or not isinstance(row['symbol'], str) or not row['symbol']:
            raise ValueError('Comparison storage needs symbol, start and end')
        a, b = sb.address(row['start']), sb.address(row['end'])
        if (a, b) not in data_evidence:
            raise ValueError(f"Comparison storage {row['symbol']} lacks an exact evidence data row")
        if not any(p['kind'] == 'bss' and p['start'] <= a < b <= p['end'] for p in placements):
            raise ValueError(f"Comparison storage {row['symbol']} lies outside the unit's uninitialized placements")
        if row['symbol'] in entries:
            raise ValueError(f"Duplicate comparison storage symbol {row['symbol']}")
        entries[row['symbol']] = (a, b)
    spans = sorted(entries.values())
    if any(b > c for (_, b), (c, _) in zip(spans, spans[1:])):
        raise ValueError('Overlapping comparison storage')
    return entries


def storage_symbols(sections, symbols, entries):
    """Bind a comparison object's uninitialized symbols to their mapped target addresses.

    Returns {symbol list index: address}, or None when the unit has no storage map. With a
    map, every COMMON symbol and every named, sized object in an uninitialized section must be
    mapped exactly once, at its compiled size and, for COMMON, its required alignment; every
    mapped name must be such a symbol."""
    if entries is None:
        return None
    nobits = {s['index'] for s in sections if s['type'] == sb.SHT_NOBITS and s['flags'] & sb.SHF_ALLOC}
    bound = {}
    for index, symbol in enumerate(symbols):
        name = symbol['name']
        common = symbol['shndx'] == sb.SHN_COMMON
        if not common and not (symbol['shndx'] in nobits and symbol['type'] in (STT_NOTYPE, STT_OBJECT)
                               and name and symbol['size']):
            continue
        if name not in entries:
            raise ValueError(f'Comparison storage omits uninitialized symbol {name}')
        if sum(s['name'] == name for s in symbols) != 1:
            raise ValueError(f'Ambiguous comparison storage symbol {name}')
        a, b = entries[name]
        if b - a != symbol['size'] or (common and a % max(symbol['value'], 1)):
            raise ValueError(f'Comparison storage {name} differs from its compiled size or alignment')
        bound[index] = a
    if set(entries) != {symbols[index]['name'] for index in bound}:
        raise ValueError('Comparison storage names a symbol that is not compiled uninitialized storage')
    return bound


def configured(root, binary):
    config = json.loads((root / CONFIG).read_text())
    if set(config) != {'schema', 'units'} or config['schema'] != 2 or not isinstance(config['units'], list):
        raise ValueError('Comparison configuration requires schema 2')
    accepted = json.loads((root / 'config/GN7E69/units.json').read_text())
    target = json.loads((root / 'config/GN7E69/baseline.json').read_text())
    sections = sb.target_sections(binary, target, {})
    function_extents = sb.function_extents(root)
    evidence = {(a, b) for a, b, _ in function_extents}
    data_evidence = {(a, b) for a, b in sb.data_extents(root)}
    accepted_linked = linked_ranges(accepted['units'], sb.address)
    units, seen = [], []
    for candidate in config['units']:
        if set(candidate) - {'storage', 'discarded'} != {'source', 'profile', 'evidence', 'sections', 'functions'}:
            raise ValueError('Comparison units need source, profile, evidence, sections and functions, '
                             'and optionally storage and discarded')
        discarded = candidate.get('discarded', [])
        if 'discarded' in candidate and (not isinstance(discarded, list) or not discarded
                or not all(isinstance(n, str) and n for n in discarded) or len(set(discarded)) != len(discarded)
                or set(discarded) & {r.get('symbol') for r in candidate['functions']}):
            raise ValueError('Comparison discarded functions need distinct unregistered symbols')
        if not candidate['source'].startswith('src/'):
            raise ValueError('Comparison source belongs in its normal src/ location')
        if not isinstance(candidate['functions'], list) or not candidate['functions']:
            raise ValueError('Comparison units require explicit target functions')
        compiled = copy.deepcopy(accepted)
        compiled['units'] = [{k: v for k, v in candidate.items() if k not in ('functions', 'storage', 'discarded')}]
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
        unit['data_slices'] = {}
        for section in unit['sections']:
            if not measured_data(section):
                continue
            # Every placement byte is linked source of this file or an evidenced unlinked slice;
            # without linked bytes the single slice is the whole placement, as before.
            slices = data_slices(candidate['source'], section, accepted_linked)
            if any(piece not in data_evidence for piece in slices):
                raise ValueError('Comparison data needs evidenced boundaries')
            if section['follows']:
                # Read-only data after code: the code it follows holds registered functions, and
                # each slice is a recorded constant block that no function extent treats as code.
                code = next(s for s in unit['sections'] if s['section'] == section['follows'])
                if not any(code['start'] <= sb.address(r['start']) < sb.address(r['end']) <= code['end']
                           for r in candidate['functions']):
                    raise ValueError('Comparison data in code must follow registered comparison code')
                sb.check_data_in_code([(a, b, candidate['source']) for a, b in slices],
                                      function_extents, data_evidence)
            unit['data_slices'][section['section']] = slices
            seen.append((section['start'], section['end']))
        unit['storage'] = storage_entries(candidate.get('storage'), unit['sections'], data_evidence)
        unit['functions'] = candidate['functions']
        unit['discarded'] = discarded
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
    accepted_linked = linked_ranges(accepted, sb.address)
    externals = {name: int(e['address'], 16) for name, e in manifest['externals'].items()}
    accepted_objects = []
    for u in accepted:
        # Only public definitions may resolve another file's undefined reference.
        stem = re.sub(r'[^A-Za-z0-9]+', '_', u['source']).strip('_')
        index = accepted.index(u)
        native = root / 'build/source/obj' / f'unit{index:03d}_{stem}.o'
        if sb.sha256(native) != u['native_object_sha256']:
            raise ValueError('Accepted external object differs from verified compiler receipt')
        native_sections, native_symbols = sb.read_elf(native.read_bytes())
        public = {s['name'] for s in native_symbols if s['bind'] == sb.STB_GLOBAL and s['shndx'] != sb.SHN_UNDEF}
        externals.update({f['symbol']: int(f['address'], 16) for f in u['functions'] if f['symbol'] in public})
        accepted_objects.append((u['sections'], native_sections, native_symbols))
    # Public data objects of accepted source resolve at their verified linked placements.
    data_symbols, ambiguous = accepted_data_symbols(accepted_objects, externals)
    addresses = comparison_references(externals, data_symbols)
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
        # compile_unit has checked the raw compiler dependencies against this checkout.
        # Keep that file for diagnostics; bind a repository-relative copy so the same
        # receipt can be validated on the CI host after compilation inside /work.
        unit['depfile'] = folder / 'repository.d'
        unit['depfile'].write_text('native.o: ' + ' '.join(
            path.replace(' ', '\\ ') for path in unit['dependencies']) + '\n')
        if sb.dependencies(unit['depfile'], root) != unit['dependencies']:
            raise ValueError('Portable comparison dependencies differ from compiler inputs')
        native_hash = sb.sha256(unit['object'])
        sections, symbols = sb.read_elf(unit['object'].read_bytes())
        allocated = {s['name']: s for s in sections if s['flags'] & sb.SHF_ALLOC and s['size']}
        placements = {s['section']: s for s in unit['sections']}
        if set(allocated) - set(placements):
            raise ValueError('Comparison object has unconfigured allocated sections')
        if any(not re.fullmatch(r'\.[A-Za-z0-9_.]+', name) for name in allocated):
            raise ValueError('Unsafe comparison section name')
        for name, section in allocated.items():
            kind, follows = placements[name]['kind'], placements[name]['follows']
            if bool(section['flags'] & sb.SHF_EXECINSTR) != (kind == 'code' and not follows) or section['type'] != (
                    sb.SHT_NOBITS if kind == 'bss' else sb.SHT_PROGBITS) or (follows and section['flags'] & sb.SHF_WRITE):
                raise ValueError('Comparison section type differs from placement')
        for name, section in allocated.items():
            follows = placements[name]['follows']
            if follows:
                check_follows(binary, placements[name], placements[follows], section['align'])
        functions = {s['name']: s for s in symbols if s['type'] == 2 and s['size'] and s['shndx'] != sb.SHN_UNDEF}
        resolved = resolve_undefined(symbols, addresses, ambiguous, discarded_references(
            unit['object'].read_bytes(), sections, symbols, unit['discarded']))
        storage = storage_symbols(sections, symbols, unit['storage'])
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
                symbol['size'], a, functions, targets, placements, addresses, fragment, target_sections, storage)
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
            if not measured_data(placement):
                continue
            a, b = placement['start'], placement['end']
            slices = data_slices(unit['source'], placement, accepted_linked)
            if slices != unit['data_slices'][name]:
                raise ValueError('Linked source differs from configured accepted placements')
            if not slices:
                continue
            sliced = slices != [(a, b)]
            if sliced and section['size'] != b - a:
                raise ValueError('Comparison data with linked bytes must compile to its full target placement')
            data_fragment = pair / ('data' + name + '.o')
            data_symbol, references, reference_script = diagnostic_object.fragment(unit['object'].read_bytes(), section, 0, section['size'],
                a, functions, targets, placements, addresses, data_fragment, target_sections, storage)
            data_script = pair / ('data' + name + '.ld')
            data_script.write_text(f"SECTIONS {{\n_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n{name} 0x{a:08X} : {{ *({name}) }}\n" + '\n'.join(reference_script) + '\n}\n')
            data_output = pair / ('data' + name + '.elf')
            sb.run('comparison data link', [str(wrapper), str(compiler/'ngcld.exe'), '-T', str(data_script),
                '-o', str(data_output), str(data_fragment), *map(str, references)], pair/'data-link.log')
            data_sections, _ = sb.read_elf(data_output.read_bytes())
            linked_section = next(s for s in data_sections if s['name'] == name)
            if linked_section['addr'] != a or linked_section['size'] != section['size']:
                raise ValueError('Diagnostic link changed data placement or size')
            if sliced:
                check_native_placement(binary, linked_section['data'], a, b, slices)
            for start, end in slices:
                pair_folder = folder / (f'data-{name.lstrip(".")}' + (f'-{start:08X}' if sliced else ''))
                pair_folder.mkdir()
                expected = sb.dol_bytes(binary, start, end)
                actual = linked_section['data'][start - a:end - a] if sliced else linked_section['data']
                score = matching.score_pair(tool, expected, actual, [], 'data', pair_folder)
                row = {'symbol': name, 'start': f'0x{start:08X}', 'end': f'0x{end:08X}'}
                entries.append(dict(row, **score, type='bytes', kind=entry_kind(placement), source=unit['source'], linked=False))
                pairs.append(dict(row, output_symbol=data_symbol, path=data_output.relative_to(root).as_posix(), sha256=sb.sha256(data_output)))
        if sb.sha256(unit['object']) != native_hash:
            raise ValueError('Diagnostic linker modified native compiler input')
        result.append({'source': unit['source'], 'sha256': sb.sha256(unit['path']),
            'dependencies': unit['dependencies'], 'object': unit['object'].relative_to(root).as_posix(),
            'object_sha256': native_hash, 'depfile': unit['depfile'].relative_to(root).as_posix(),
            'depfile_sha256': sb.sha256(unit['depfile']), 'entries': entries, 'pairs': pairs})
    return result


def check_follows(binary, placement, code, align):
    """Data after code starts at its first alignment boundary after the code placement, as the
    linker places it, and the target holds that padding as zero bytes."""
    align = max(align, 1)
    aligned = -(-code['end'] // align) * align
    if placement['start'] != aligned:
        raise ValueError('Comparison data must start at its alignment after the code it follows')
    if any(sb.dol_bytes(binary, code['end'], aligned)):
        raise ValueError('Target padding before comparison data after code is not zero')


def check_native_placement(binary, compiled, start, end, slices):
    """A sliced placement must keep the native layout: its linked bytes compile identically."""
    cursor = start
    for left, right in slices + [(end, end)]:
        if cursor < left and compiled[cursor - start:left - start] != sb.dol_bytes(binary, cursor, left):
            raise ValueError('Comparison data does not reproduce its linked bytes at their native placement')
        cursor = right


def load(receipts, binary, root):
    _, units = configured(root, binary)
    if not isinstance(receipts, list) or [r['source'] for r in receipts] != [u['source'] for u in units]:
        raise ValueError('Comparison receipt omits configured draft source')
    accepted = json.loads((root / 'build/source/report.json').read_text())['units']
    linked_bounds = [(int(s['start'], 16), int(s['end'], 16)) for u in accepted for s in u['sections']]
    accepted_linked = linked_ranges(accepted, sb.address)
    result = []
    for receipt, unit in zip(receipts, units):
        if receipt['sha256'] != sb.sha256(unit['path']) or not receipt.get('dependencies') or any(
                sb.sha256(root / sb.repository_path(p)) != digest for p, digest in receipt['dependencies'].items()):
            raise ValueError('Stale comparison source or dependencies')
        for path, digest in [(receipt['object'], receipt['object_sha256']), (receipt['depfile'], receipt['depfile_sha256'])] + [(p['path'], p['sha256']) for p in receipt['pairs']]:
            if not path.startswith('build/matching/candidates/') or sb.sha256(root / sb.repository_path(path)) != digest:
                raise ValueError('Stale or foreign comparison output')
        if sb.dependencies(root / receipt['depfile'], root) != receipt['dependencies']:
            raise ValueError('Comparison dependencies differ from compiler receipt')
        expected_rows = {(r['symbol'], r['start'], r['end']) for r in unit['functions'] if not any(
            a <= sb.address(r['start']) < sb.address(r['end']) <= b for a, b in linked_bounds)}
        # Recompute the measured data slices from build/source/report.json, independently of the
        # generator: each must be credited exactly once and no linked byte may be credited.
        placements = {s['section']: s for s in unit['sections'] if measured_data(s)}
        for name, placement in placements.items():
            if data_slices(unit['source'], placement, accepted_linked) != unit['data_slices'][name]:
                raise ValueError('Linked source differs from configured accepted placements')
        expected_rows |= {(name, f"0x{a:08X}", f"0x{b:08X}") for name, slices in unit['data_slices'].items()
                          for a, b in slices}
        actual_rows = [(e['symbol'], e['start'], e['end']) for e in receipt['entries']]
        if len(set(actual_rows)) != len(actual_rows):
            raise ValueError('Comparison receipt credits an extent more than once')
        if any(left < sb.address(e['end']) and sb.address(e['start']) < right
               for e in receipt['entries'] for left, right in linked_bounds):
            raise ValueError('Comparison receipt credits linked source bytes')
        if set(actual_rows) != expected_rows:
            raise ValueError('Comparison receipt omits configured functions or data slices')
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
            elif entry['type'] == 'bytes' and row['symbol'] in placements and entry['kind'] == entry_kind(placements[row['symbol']]):
                placement = placements[row['symbol']]
                section = next(s for s in sections if s['name'] == row['symbol'])
                if section['addr'] != placement['start']:
                    raise ValueError('Comparison data differs from configured address')
                if (a, b) == (placement['start'], placement['end']):
                    actual = section['data']
                else:
                    if section['size'] != placement['end'] - placement['start']:
                        raise ValueError('Comparison data with linked bytes must compile to its full target placement')
                    check_native_placement(binary, section['data'], placement['start'], placement['end'],
                                           unit['data_slices'][row['symbol']])
                    actual = section['data'][a - placement['start']:b - placement['start']]
            else:
                raise ValueError('Invalid comparison kind')
            expected = sb.dol_bytes(binary, a, b)
            exact = b-a if actual == expected else 0
            if type(entry['matched']) is not int or entry['matched'] != exact or type(entry['fuzzy']) not in (int, float) \
                    or not math.isfinite(entry['fuzzy']) or not exact <= entry['fuzzy'] <= b-a:
                raise ValueError('Invalid comparison score or exact bytes')
            result.append(entry)
    # Defensive only: configured() already rejects overlapping functions and data placements across
    # units, and each receipt's rows must equal its configured functions and slices, so this check
    # is not reachable through a receipt that passes the checks above.
    spans = sorted((sb.address(e['start']), sb.address(e['end'])) for e in result)
    if any(b > c for (_, b), (c, _) in zip(spans, spans[1:])):
        raise ValueError('Comparison receipt credits an extent more than once')
    return result
