#!/usr/bin/env python3
"""Count the source files that are closed, and say what keeps each other file open.

    python3 tools/files_closed.py            after `python3 build.py`; writes build/<target>/files.tsv

A file is closed (the project's done rule, Lucas 2026-11-04) when:
- linked: units.json links it and comparisons.json registers nothing in it, so every function in it
  is exact in the complete build;
- its name is descriptive: not cu_<address> or any other name built on an address;
- every function and every label (data object, local static) its object defines has a descriptive
  name, classes included (a method of Class_803EC99C is not named); compiler-generated symbols
  (gcc2_compiled., _GLOBAL_.I/D wrappers, __static_initialization_and_destruction_0, numbered
  unnamed statics, CodeWarrior's @123 literals) are left out;
- each of those names has an evidence.tsv row at its address that gives it (a name, external or
  data row, or a function row from a related build or SDK signature; a function row of origin
  target or inferred only sets boundaries and never names): the function's address from the
  build, a label's from its section's linked placement. A label whose section the build did not
  place one-to-one cannot be located, and counts as not evidenced. Exception (Lucas 2026-11-04): a
  data label in the imported Nintendo SDK (src/dolphin/) carries the SDK source's own name and
  needs no row of its own; its functions still do.
The two reviews are the last part of the rule; they live on the pull requests, so this count is
what the tools can see: a file it lists as closed still needs its reviews.

files.tsv has one row per source file the build links or the comparisons register: whether it is
linked, named, how many functions and labels are placeholders or lack evidence, a few examples,
and `closed`. The build prints the totals.
"""
import json
from pathlib import Path
import re
import sys

import naming
import source_build as sb

ROOT = Path(__file__).resolve().parents[1]
TARGET = 'GN7E69-rev0'
STT_FUNC, STT_SECTION, STT_FILE = 2, 3, 4
SDK = 'src/dolphin/'  # The imported Nintendo SDK, built with CodeWarrior.


def descriptive_file(source):
    stem = Path(source).stem
    return not naming.placeholder(stem) and not re.match(r'(?:cu|fn|unit|file|data|lbl)_', stem)


def unit_labels(index, unit):
    """(name, address or None, is function) for each symbol the unit's object defines."""
    stem = re.sub(r'[^A-Za-z0-9]+', '_', unit['source']).strip('_')
    native = ROOT / 'build/source/obj' / f'unit{index:03d}_{stem}.o'
    if sb.sha256(native) != unit['native_object_sha256']:
        raise ValueError(f"{native.relative_to(ROOT)} differs from the build's receipt; rebuild")
    sections, symbols = sb.read_elf(native.read_bytes())
    functions = {f['symbol']: int(f['address'], 16) for f in unit['functions']}
    placed = {}
    for placement in unit['sections']:
        start, end = int(placement['start'], 16), int(placement['end'], 16)
        if placement.get("compiled") == end - start:
            placed[placement['section']] = start
    found = []
    for symbol in symbols:
        name = symbol['name']
        if not name or symbol['type'] in (STT_SECTION, STT_FILE) or symbol['shndx'] in (sb.SHN_UNDEF, sb.SHN_ABS) \
                or naming.generated(name) or name.startswith('.'):
            continue
        if symbol['type'] == STT_FUNC:
            if name in functions:  # Functions the linker discarded are not in the game.
                found.append((name, functions[name], True))
            continue
        if symbol['shndx'] == sb.SHN_COMMON or symbol['shndx'] >= len(sections):
            found.append((name, None, False))
            continue
        section = sections[symbol['shndx']]
        if section['flags'] & sb.SHF_EXECINSTR:
            continue  # A label inside code (an assembly routine's local label) is not a data object.
        start = placed.get(section['name'])
        found.append((name, None if start is None else start + symbol['value'], False))
    return found


def survey(source_report=ROOT / 'build/source/report.json'):
    report = json.loads(Path(source_report).read_text())
    if report.get('complete') != 'identical':
        raise ValueError('build/source/report.json is not a verified build; run python3 build.py')
    comparisons = {u['source'] for u in json.loads((ROOT / f'config/{TARGET}/comparisons.json').read_text())['units']}
    given = naming.evidence_names(ROOT / f'config/{TARGET}/evidence.tsv')
    rows = []
    for index, unit in enumerate(report['units']):
        unnamed, unevidenced, total = [], [], 0
        sdk = unit['source'].startswith(SDK)
        for name, address, function in unit_labels(index, unit):
            total += 1
            readable = naming.demangle(name) or name
            if naming.placeholder(readable) or naming.placeholder(name):
                unnamed.append(readable)
                continue
            if not function and sdk:
                continue  # SDK data labels keep the SDK source's names (owner rule, 2026-11-04).
            short = naming.base_name(readable)
            names = given.get(address, set()) if address is not None else set()
            if not names & {name, readable, short, short.split('::')[-1]}:
                unevidenced.append(readable)
        rows.append({'source': unit['source'], 'linked': 'partly' if unit['source'] in comparisons else 'yes',
                     'file_named': descriptive_file(unit['source']), 'labels': total,
                     'placeholders': unnamed, 'unevidenced': unevidenced})
    for source in sorted(comparisons - {u['source'] for u in report['units']}):
        rows.append({'source': source, 'linked': 'no', 'file_named': descriptive_file(source), 'labels': None,
                     'placeholders': [], 'unevidenced': []})
    for row in rows:
        row['closed'] = row['linked'] == 'yes' and row['file_named'] and not row['placeholders'] and not row['unevidenced']
    return rows


def write(rows, path):
    lines = ['source\tlinked\tfile_named\tlabels\tplaceholders\tunevidenced\tclosed\texamples']
    for row in sorted(rows, key=lambda r: r['source']):
        examples = ', '.join((row['placeholders'] + row['unevidenced'])[:3])
        lines.append('\t'.join([row['source'], row['linked'], 'yes' if row['file_named'] else 'no',
                                '-' if row['labels'] is None else str(row['labels']),
                                str(len(row['placeholders'])), str(len(row['unevidenced'])),
                                'yes' if row['closed'] else 'no', examples]))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text('\n'.join(lines) + '\n')


def summary(rows):
    linked = [r for r in rows if r['linked'] == 'yes']
    closed = [r for r in rows if r['closed']]
    named = [r for r in linked if r['file_named']]
    labelled = [r for r in linked if not r['placeholders']]
    return (f"Files closed: {len(closed)} of {len(rows)} source files ({len(linked)} wholly linked; of those "
            f"{len(named)} have a descriptive file name and {len(labelled)} name every function and label; "
            f"reviews are not counted here)")


def main():
    rows = survey()
    path = ROOT / 'build' / TARGET / 'files.tsv'
    write(rows, path)
    print(summary(rows))
    print(f'Per-file detail: {path.relative_to(ROOT)}')
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (ValueError, OSError) as error:
        sys.exit(f'files_closed: {error}')
