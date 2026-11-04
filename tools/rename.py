#!/usr/bin/env python3
"""Rename a function, variable, type or class everywhere the project records it, in one step, and
check that the recorded names agree.

    python3 tools/rename.py fn_800D0408 IsKickoffPending --evidence "Returns whether state +10 ..."
    python3 tools/rename.py Class_803EC99C PlayCaller --evidence "Owns the play-call menu ..."
    python3 tools/rename.py OLD NEW --dry-run      list the changes without writing them
    python3 tools/rename.py --check                after `python3 build.py`: names agree?

A rename changes, as whole identifiers:
- src/ and include/: every use of OLD (code and comments).
- config/<target>/evidence.tsv: OLD in the subject column (also as `Class::OLD` or `OLD::member`) and
  GCC 2.95 mangled spellings that carry it (`OLD__14Class_8000ABCD`, `fn_8000ABCD__<len>OLD`), whose
  length prefix is rewritten. The evidence column is a record and is never rewritten.
- config/<target>/units.json (externals, link_roots, folded) and comparisons.json (function, storage
  and discarded symbols): the same, mangled spellings included.
Every rename needs --evidence: what the code does that gives NEW, recorded as a `name` row at OLD's
address (a `type` row for a type), origin `inferred` (or --origin). A `name` row for a neutral label
(fn_/lbl_/data_/Class_/Block_ plus an address) said the label is not a recovered name, and is
replaced; a descriptive name row for OLD (a related build's name, say) is kept as the record of that
claim, and the new row follows it. Evidence describes what the code does and goes in evidence.tsv,
never in a code comment. NEW must not already be in use. Files named after OLD (for example
include/game/Class_803EC99C.h) are listed, not moved.

--check compares the names the last source build compiled (build/source/report.json, with
comparisons.json for registered functions) with evidence.tsv: every function that has a descriptive
compiled name needs a `name` or `external` row at its address that gives that name (unqualified,
`Class::name` or mangled; a `function` row from a related build or SDK signature counts too), and every
units.json external needs a row with its name at its address.
Exit 1 lists each disagreement.
"""
import argparse
import difflib
import hashlib
import json
from pathlib import Path
import re
import sys

from naming import demangle, evidence_names, placeholder

ROOT = Path(__file__).resolve().parents[1]
TARGET = 'GN7E69-rev0'
CONFIG = ROOT / 'config' / TARGET
SOURCE_DIRS = ('src', 'include')
SOURCE_SUFFIXES = {'.c', '.cpp', '.cp', '.cc', '.h', '.hpp', '.inc', '.s'}
IDENTIFIER = re.compile(r'[A-Za-z_][A-Za-z0-9_]*')


def word(name):
    return re.compile(r'(?<![A-Za-z0-9_])' + re.escape(name) + r'(?![A-Za-z0-9_])')


def rename_text(text, old, new):
    """Rename OLD in free text and in GCC 2.95 mangled symbols: a whole-identifier use, the leading
    name of `OLD__...`, and a length-prefixed `<len>OLD` inside a mangled name."""
    text = re.sub(r'(?<![0-9A-Za-z_])' + re.escape(old) + r'(?=__[A-Za-z0-9_])', new, text)
    # The length prefix bounds the name, so parameter codes may follow it directly (`14Class_8000ABCDiPi`).
    text = re.sub(r'(?<![0-9])' + str(len(old)) + re.escape(old), str(len(new)) + new, text)
    return word(old).sub(new, text)


def source_files():
    for directory in SOURCE_DIRS:
        for path in sorted((ROOT / directory).rglob('*')):
            if path.is_file() and path.suffix.lower() in SOURCE_SUFFIXES:
                yield path


def rename_json(value, old, new):
    if isinstance(value, dict):
        # An `evidence` value is a record, as in evidence.tsv, and keeps its text.
        return {k if k == 'evidence' else rename_text(k, old, new): v if k == 'evidence' else rename_json(v, old, new)
                for k, v in value.items()}
    if isinstance(value, list):
        return [rename_json(v, old, new) for v in value]
    if isinstance(value, str):
        return rename_text(value, old, new)
    return value


def read_evidence():
    lines = (CONFIG / 'evidence.tsv').read_text().splitlines()
    return lines[0].split('\t'), [line.split('\t') for line in lines[1:]]


def write_evidence(header, rows):
    return ''.join('\t'.join(row) + '\n' for row in [header] + rows)


def names(subject, old):
    """Whether an evidence subject names OLD itself (not a member of it or a thing qualified by it):
    `OLD`, `Class::OLD`, a mangled `OLD__...`, with or without a trailing note. A constructor or
    destructor of class OLD (`OLD::OLD`, `OLD::~OLD`) is a member, named by the class's type row."""
    first = subject.split()[0] if subject.split() else subject
    parts = (demangle(first) or first).split('::')
    return parts[-1] == old and not (len(parts) > 1 and parts[-2] == old)


def rename_evidence(header, rows, old, new, evidence, origin):
    """The evidence rows after renaming OLD to NEW. Subjects are labels and follow the rename; the
    evidence column is a record (it may quote another build's symbol) and is never rewritten. The
    name is a claim, so it gets its own row with --evidence: a neutral-label name row for OLD is
    replaced by it; a descriptive name row for OLD stays as the record of that earlier claim (what a
    related build holds, for example) and the new row follows it; with no name row, the new row
    goes after the function, data or external row that places OLD, or a type row for a type."""
    index = {name: i for i, name in enumerate(header)}
    kind, start, subject = index['kind'], index['start'], index['subject']

    def claim(row_kind, at, label):
        row = ['-'] * len(header)
        row[kind], row[start], row[subject] = row_kind, at, label
        row[index['origin']], row[index['evidence']] = origin, evidence
        return row

    located = [r for r in rows if r[kind] == 'name' and names(r[subject], old)]
    if not located:
        located = [r for r in rows if r[kind] in ('function', 'data', 'external') and r[start] != '-'
                   and names(r[subject], old)]
    if not located:
        located = [r for r in rows if r[kind] == 'type' and r[subject].split()[:1] == [old]]
    if not located:
        raise SystemExit(f'rename: no name, function, data, external or type row in evidence.tsv records {old}; '
                         'add the row that places it first')
    after, seen = {}, set()
    for row in located:
        key = (row[kind] if row[kind] == 'type' else 'name', row[start])
        if key not in seen:
            seen.add(key)
            after[id(row)] = claim(key[0], row[start], rename_text(row[subject].split()[0], old, new))
    out = []
    for row in rows:
        neutral = row[kind] == 'name' and names(row[subject], old) and placeholder(old)
        if neutral:
            if id(row) in after:
                out.append(after[id(row)])  # The neutral row said "not a name"; the claim replaces it.
            continue
        renamed = list(row)
        if not (row[kind] == 'name' and names(row[subject], old)):
            renamed[subject] = rename_text(row[subject], old, new)
        out.append(renamed)
        if id(row) in after:
            out.append(after[id(row)])
    return out


def rename(old, new, evidence, origin, dry_run):
    if not IDENTIFIER.fullmatch(old) or not IDENTIFIER.fullmatch(new):
        raise SystemExit('rename: OLD and NEW must be C identifiers')
    if old == new:
        raise SystemExit('rename: OLD and NEW are the same')
    if placeholder(new):
        raise SystemExit(f'rename: {new} is itself a placeholder name; pick a descriptive one')
    used, users = word(new), []
    changes = {}
    for path in source_files():
        text = path.read_text(encoding='utf-8', errors='surrogateescape')
        if used.search(text):
            users.append(path.relative_to(ROOT).as_posix())
        renamed = word(old).sub(new, text)
        if renamed != text:
            changes[path] = (text, renamed)
    header, rows = read_evidence()
    if users or any(used.search(row[3]) for row in rows if len(row) > 3):
        raise SystemExit(f'rename: {new} is already in use ({", ".join(users) or "evidence.tsv"}); pick another name')
    if evidence is None:
        raise SystemExit('rename: give --evidence saying what the code does that gives the new name')
    out = rename_evidence(header, rows, old, new, evidence, origin)
    evidence_text = (CONFIG / 'evidence.tsv').read_text()
    new_evidence = write_evidence(header, out)
    if new_evidence != evidence_text:
        changes[CONFIG / 'evidence.tsv'] = (evidence_text, new_evidence)
    for name in ('units.json', 'comparisons.json'):
        path = CONFIG / name
        text = path.read_text()
        renamed = json.dumps(rename_json(json.loads(text), old, new), indent=2) + '\n'
        if json.loads(renamed) != json.loads(text):
            changes[path] = (text, renamed)
    if not changes:
        raise SystemExit(f'rename: {old} appears nowhere')
    for path, (before, after) in changes.items():
        count = sum(1 for line in difflib.unified_diff(before.splitlines(), after.splitlines(), n=0, lineterm='')
                    if line[:1] in '+-' and line[:3] not in ('+++', '---'))
        print(f'{path.relative_to(ROOT).as_posix()}: {count} line(s) removed or added')
    named = [p.relative_to(ROOT).as_posix() for p in source_files() if old in p.stem]
    if named:
        print(f'Files named after {old} (not moved): ' + ', '.join(named))
    if dry_run:
        return
    for path, (_, after) in changes.items():
        path.write_text(after, encoding='utf-8', errors='surrogateescape')
    print(f'Renamed {old} to {new}. Rebuild (python3 build.py), then python3 tools/rename.py --check.')


def check():
    report_path = ROOT / 'build/source/report.json'
    if not report_path.is_file():
        raise SystemExit('rename: run `python3 build.py` first; --check reads its compiled names')
    report = json.loads(report_path.read_text())
    given = evidence_names(CONFIG / 'evidence.tsv')
    compiled = [(f['symbol'], int(f['address'], 16)) for u in report['units'] for f in u['functions']]
    compiled += [(f['symbol'], int(f['start'], 16)) for u in json.loads((CONFIG / 'comparisons.json').read_text())['units']
                 for f in u['functions']]
    problems = []
    for symbol, address in sorted(set(compiled), key=lambda item: item[1]):
        name = demangle(symbol)
        if name is None or placeholder(name):
            continue
        names = given.get(address, set())
        if not names & {symbol, name, name.split('::')[-1]}:
            problems.append(f'0x{address:08X} {symbol}: compiled as {name}, evidence.tsv names '
                            + (', '.join(sorted(names)) if names else 'nothing') + ' there')
    for name, entry in json.loads((CONFIG / 'units.json').read_text())['externals'].items():
        if name not in given.get(int(entry['address'], 16), set()):
            names = given.get(int(entry['address'], 16), set())
            problems.append(f"{entry['address']} external {name}: evidence.tsv names "
                            + (', '.join(sorted(names)) if names else 'nothing') + ' there')
    stale = [u['source'] for u in report['units'] if (ROOT / u['source']).is_file() and
             hashlib.sha256((ROOT / u['source']).read_bytes()).hexdigest() != u['source_sha256']]
    for line in problems:
        print(line)
    if stale:
        print(f'Note: the build is older than {len(stale)} source file(s) ({stale[0]} ...); rebuild for a current check.')
    print(f'{len(problems)} disagreement(s) between compiled names, externals and evidence.tsv')
    return 1 if problems else 0


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('old', nargs='?')
    parser.add_argument('new', nargs='?')
    parser.add_argument('--evidence', required=False,
                        help='what the code does that gives the new name (required for a rename)')
    parser.add_argument('--origin', default='inferred', choices=('inferred', 'related', 'signature', 'target'))
    parser.add_argument('--dry-run', action='store_true')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        if args.old or args.new:
            parser.error('--check takes no names')
        return check()
    if not (args.old and args.new):
        parser.error('give OLD and NEW, or --check')
    rename(args.old, args.new, args.evidence, args.origin, args.dry_run)
    return 0


if __name__ == '__main__':
    sys.exit(main())
