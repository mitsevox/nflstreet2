#!/usr/bin/env python3
"""Try one variant of a function: compile one source file, link each chosen function alone at its
target address and compare its bytes with the original. Exit 0 when every chosen function is
identical and uses the original's constants, 1 when one differs.

    python3 tools/trial.py src/game/cu_800F81C0.cpp                 every registered function
    python3 tools/trial.py src/game/cu_800F81C0.cpp fn_800F8A88     one function, by symbol
    python3 tools/trial.py src/game/cu_800F81C0.cpp 0x800F8A88      or by target address
    python3 tools/trial.py src/game/cu_800F81C0.cpp fn_800F8A88 --diff   instruction diff
    python3 tools/trial.py src/game/cu_800F81C0.cpp --dump /tmp/rtl      keep cc1's -da RTL dumps

It reads the file's entry in config/<target>/comparisons.json (compiled with DECOMP_COMPARE, as the
comparisons are) or, for a linked file without one, its units.json entry with the functions the
source build placed. It needs one verified `python3 build.py` first: other files' functions and
data resolve at the addresses that build placed them. It writes only under build/trial/ and the
dump folder; the source tree, the build's own outputs and the report are untouched. The verdict is
the one the build would reach for these bytes, but credit still comes only from the build.
"""
import argparse
import json
from pathlib import Path
import re
import shutil
import sys

import function_compare as fc
import matching
import prodg_cc
import source_build as sb
import baseline

ROOT = sb.ROOT
TARGET = 'GN7E69-rev0'


def unit_for(source, binary):
    """The source file's compile unit with the functions to compare, and whether it is a comparison."""
    comparisons = json.loads((ROOT / fc.CONFIG).read_text())
    if any(u['source'] == source for u in comparisons['units']):
        _, units = fc.configured(ROOT, binary)
        return next(u for u in units if u['source'] == source), True
    manifest = json.loads((ROOT / f'config/{TARGET}/units.json').read_text())
    entry = next((u for u in manifest['units'] if u['source'] == source), None)
    if entry is None:
        raise SystemExit(f'trial: {source} is in neither comparisons.json nor units.json')
    target = json.loads((ROOT / f'config/{TARGET}/baseline.json').read_text())
    units, _, _ = sb.load_manifest(dict(manifest, units=[entry]), sb.target_sections(binary, target, {}),
                                   manifest['compiler'])
    report = json.loads((ROOT / 'build/source/report.json').read_text())
    placed = next(u for u in report['units'] if u['source'] == source)
    unit = units[0]
    unit['functions'] = [{'symbol': f['symbol'], 'start': f['address'],
                          'end': f"0x{int(f['address'], 16) + f['size']:08X}"} for f in placed['functions']]
    unit['storage'], unit['discarded'] = None, list((entry.get('link_roots') or {}).get('discarded', []))
    unit['linked_storage'] = {name: int(value, 16) for name, value in (placed.get('storage') or {}).items()}
    return unit, False


def linked_storage(sections, symbols, placements, mapped):
    """For a linked file with a COMMON storage map: {symbol index: address} for each COMMON symbol,
    at the address the build defined it, and for each named object of its placed uninitialized
    sections, at its placement start plus its offset, as the build linked them."""
    nobits = {s['index']: s['name'] for s in sections if s['type'] == sb.SHT_NOBITS and s['flags'] & sb.SHF_ALLOC}
    bound = {}
    for index, symbol in enumerate(symbols):
        if symbol['shndx'] == sb.SHN_COMMON:
            if symbol['name'] not in mapped:
                raise SystemExit(f"trial: COMMON symbol {symbol['name']} is not in the build's storage map")
            bound[index] = mapped[symbol['name']]
        elif symbol['shndx'] in nobits and symbol['name'] and symbol['size'] and symbol['type'] in (0, 1):
            bound[index] = placements[nobits[symbol['shndx']]]['start'] + symbol['value']
    return bound


def chosen(unit, names):
    if not names:
        return unit['functions']
    rows = []
    for name in names:
        found = [r for r in unit['functions'] if r['symbol'] == name or
                 (name.lower().startswith('0x') and sb.address(r['start']) == int(name, 16))]
        if not found:
            raise SystemExit(f"trial: {name} is not a function of {unit['source']}; its functions are "
                             + ', '.join(r['symbol'] for r in unit['functions']))
        rows += found
    return rows


def show_diff(pair):
    """Print objdiff's instruction rows, target on the left and the trial on the right."""
    diff = json.loads((pair / 'diff.json').read_text())
    sides = [next(s for s in diff[side]['symbols'] if s.get('kind') == 'SYMBOL_FUNCTION') for side in ('left', 'right')]
    rows = zip(*(side.get('instructions', []) for side in sides))
    for left, right in rows:
        mark = '  ' if 'diff_kind' not in left and 'diff_kind' not in right else '! '
        text = [row.get('instruction', {}).get('formatted', '') for row in (left, right)]
        address = int(left.get('instruction', {}).get('address', right.get('instruction', {}).get('address', '0')))
        print(f'  {mark}{address:5X}  {text[0]:<36} {text[1]}')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source', help='the source file, as units.json or comparisons.json names it')
    parser.add_argument('functions', nargs='*', help='function symbols or 0x target addresses (default: all)')
    parser.add_argument('--diff', action='store_true', help='print the instruction diff of each function that differs')
    parser.add_argument('--dump', type=Path, metavar='DIR', help="keep cc1's RTL dumps here (ProDG files only; "
                        'outside the repository or under build/ or scratch/)')
    parser.add_argument('--dump-flags', default='-da', help='GCC -d flags for --dump, comma-separated, with or '
                        'without the dash: da (the default) or dl,dg; with dashes, write --dump-flags=-dl,-dg')
    args = parser.parse_args()

    original = ROOT / 'orig' / TARGET / 'sys/main.dol'
    binary = original.read_bytes()
    source_report = ROOT / 'build/source/report.json'
    if not source_report.is_file() or json.loads(source_report.read_text()).get('complete') != 'identical':
        raise SystemExit('trial: run `python3 build.py` once first; trial resolves other files against its build')
    source = Path(args.source).as_posix()
    unit, comparison = unit_for(source, binary)
    rows = chosen(unit, args.functions)

    folder = ROOT / 'build/trial' / re.sub(r'[^A-Za-z0-9]+', '_', source).strip('_')
    if folder.exists():
        shutil.rmtree(folder)
    folder.mkdir(parents=True)
    unit['object'], unit['depfile'] = folder / 'native.o', folder / 'native.d'
    if args.dump:
        if unit['compiler'] != 'prodg':
            raise SystemExit('trial: --dump needs a ProDG file; CodeWarrior has no RTL dump flags')
        flags = ','.join(f if f.startswith('-') else '-' + f for f in args.dump_flags.split(','))
        dump = ['--dump-dir', str(args.dump.resolve()), '--dump', flags]
        try:  # The wrapper's own checks, before compiling, so a refusal names its reason.
            prodg_cc.dump_options(prodg_cc.parse(dump + ['-c', 'x.c', '-o', 'x.o', '--dir', '.'])[0])
        except ValueError as error:
            raise SystemExit(f'trial: {error}')
        unit['flags'] = unit['flags'] + dump
    manifest = json.loads((ROOT / f'config/{TARGET}/units.json').read_text())
    compiler, wrapper = sb.setup_compiler.setup()
    sdk = sb.setup_compiler.setup_sdks([unit['compiler_version']]) if unit['compiler'] == 'mwcc' else None
    if unit['compile_path']:
        sb.stage(unit)
    sb.compile_unit(unit, compiler, wrapper, sdk, manifest['include_dirs'], comparison=comparison)
    if args.dump:
        print(f'RTL dumps in {args.dump.resolve()}')

    accepted = json.loads(source_report.read_text())['units']
    addresses, ambiguous = fc.reference_addresses(ROOT, manifest, accepted)
    native = unit['object'].read_bytes()
    sections, symbols = sb.read_elf(native)
    functions = {s['name']: s for s in symbols if s['type'] == 2 and s['size'] and s['shndx'] != sb.SHN_UNDEF}
    fc.resolve_undefined(symbols, addresses, ambiguous, fc.discarded_references(native, sections, symbols, unit['discarded']))
    allocated = {s['name']: s for s in sections if s['flags'] & sb.SHF_ALLOC and s['size']}
    placements = {s['section']: s for s in unit['sections']}
    if set(allocated) - set(placements):
        raise SystemExit(f'trial: the object has sections its entry does not place: {sorted(set(allocated) - set(placements))}')
    storage = fc.storage_symbols(sections, symbols, unit['storage'])
    if not comparison and unit.get('linked_storage'):
        storage = linked_storage(sections, symbols, placements, unit['linked_storage'])
    targets = {f['symbol']: (int(f['address'], 16), int(f['address'], 16) + f['size'])
               for u in accepted if u['source'] == source for f in u['functions']}
    targets.update({r['symbol']: (sb.address(r['start']), sb.address(r['end'])) for r in unit['functions']})
    target = json.loads((ROOT / f'config/{TARGET}/baseline.json').read_text())
    target_sections = sb.target_sections(binary, target,
                                         json.loads((ROOT / f'config/{TARGET}/analysis.json').read_text())['output_sections'])
    tool = baseline.get_tool('objdiff', json.loads((ROOT / 'tools/matching-tools.json').read_text()), sb.baseline_system())

    # Every initialized data section is linked whole, so each constant an identical function uses
    # can be checked against the original, linked or not.
    resolved, unchecked = {}, {}
    for name, section in allocated.items():
        placement = placements[name]
        if not fc.measured_data(placement):
            continue
        pair = folder / ('data' + name)
        pair.mkdir()
        try:
            _, _, linked = fc.link_data(native, section, placement['start'], functions, targets, placements, addresses,
                                        pair, target_sections, storage, target, compiler, wrapper)
            resolved[name] = (placement['start'], linked['data'])
        except (ValueError, RuntimeError) as error:
            unchecked[name] = str(error)
    every_reference = fc.own_data_references(native, sections, symbols)

    failed = 0
    for number, row in enumerate(rows):
        a, b = sb.address(row['start']), sb.address(row['end'])
        symbol = functions.get(row['symbol'])
        if symbol is None:
            print(f"{row['symbol']}: MISSING (the compiler did not emit it)")
            failed += 1
            continue
        section = next(s for s in allocated.values() if s['index'] == symbol['shndx'])
        pair = folder / str(number)
        pair.mkdir()
        _, _, actual = fc.link_function(native, section, symbol, a, functions, targets, placements, addresses, pair,
                                        target_sections, storage, target, compiler, wrapper)
        expected = sb.dol_bytes(binary, a, b)
        score = matching.score_pair(tool, expected, actual,
                                    [{'name': 'function', 'value': 0, 'size': b - a, 'type': 2, 'shndx': 1}], 'code', pair)
        label = f"{row['symbol']} 0x{a:08X}"
        if expected != actual:
            failed += 1
            size = '' if len(actual) == len(expected) else f', {len(actual)} bytes where the target has {len(expected)}'
            print(f"{label}: DIFFERS ({100 * score['fuzzy'] / (b - a):.2f}%{size})")
            if args.diff:
                show_diff(pair)
            continue
        references = fc.own_data_references(native, sections, symbols, section['index'], symbol['value'], symbol['size'])
        skipped = sorted({name for name, _, _ in references if name in unchecked})
        try:
            fc.check_literals(source, row['symbol'], [(name, fc.literal_extent(sections, symbols, every_reference, name, value,
                span, sb.dol_bytes(binary, resolved[name][0], resolved[name][0] + len(resolved[name][1])) or b''))
                for name, value, span in references if name in resolved], resolved, binary)
        except ValueError as error:
            failed += 1
            print(f'{label}: WRONG CONSTANT ({error})')
            continue
        note = f" (constants in {', '.join(skipped)} not checked: {'; '.join(unchecked[n] for n in skipped)})" if skipped else ''
        print(f'{label}: IDENTICAL{note}')
    print(f'{len(rows) - failed} of {len(rows)} identical')
    return 1 if failed else 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (ValueError, RuntimeError, OSError) as error:
        sys.exit(f'trial: {error}')
