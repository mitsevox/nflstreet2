#!/usr/bin/env python3
"""Propose unit (file) boundaries from a sibling build's compile units (wiki: "Recover unit splits
from a sibling build").

    python3 tools/boundaries.py [--target ID]              print a summary of the run
    python3 tools/boundaries.py --write [--target ID]      update the committed tables
    python3 tools/boundaries.py --check [--target ID]      fail when the committed tables differ
    python3 tools/boundaries.py --calibrate [--target ID]  hold-out test against established units

The sibling is NASCAR 2005 (Tiburon, 2004, same ProDG toolchain and SN linker). Its symbol table
names every function and its size, and its file rows (Type 4) and `gcc2_compiled.` markers say
where each file's code starts. The sibling's executable is not kept, so functions are paired by
names and sizes, never by code, and the wiki's callee check (refuse a pair whose callees differ)
cannot be run.

1. Sibling units come from the committed table `compile_units.tsv` (tools/sibling_tables.py
   nascar-units): a unit starts at its file's `gcc2_compiled.` marker or, for a file without one,
   at its lowest local function (`first-function`), in which case its global functions may start
   earlier, so the edge into it is `at-or-before`. A unit over UNMARKED_FUNCTIONS functions or
   UNMARKED_SIZE bytes is a pile of files whose edges the table does not show, and so is a
   `first-function` unit unless both its neighbours have markers (the CodeWarrior SDK run, whose
   functions the export lists almost all as globals); neither proposes anything. A file with neither a marker nor a local function (the export lists globals apart
   from their files) is not in the table: it is reported in the other_files of the unit listed
   before it, and that unit may hold more than one file.
2. Anchors. A name anchor is a target function whose label equals the name of exactly one sibling
   function of the same size, unless the label came from this script's alignment (its `name` row
   starts with POSITIONAL_PHRASE). A size anchor is a run of RUN consecutive functions whose sizes
   occur once in each build (mutual unique). The kept anchors are the heaviest chain that increases
   in both builds, name anchors outweighing size anchors. This takes the sibling's own order as the
   link order: both builds use SN's linker, and the chain covering the engine libraries in one run
   is the confirmation; where the orders differ (28 SDK name anchors) the chain drops anchors.
3. Alignment. Between two anchors, the functions pair one to one when both gaps hold the same sizes
   in the same order; otherwise equal sizes pair by longest common subsequence. The sibling's
   pairing is authoritative: a target function paired with sibling unit X is never given to
   another unit by a later step.
4. Units. A sibling unit becomes a proposed unit over its paired target functions when it has a
   name anchor or at least RUN size-anchored functions, at least DENSITY of the target functions in
   that extent are paired, and its function count and byte size are within RATIO of the sibling's
   (RATIO_NAMED with a name anchor). The rule is re-applied after the edges settle.
5. Text edges, between proposed units that are neighbours in the sibling (no sibling unit with
   functions between them; otherwise the edge is `open`). With no unpaired function between them,
   the alignment's cut is the edge: `data` when it crosses strictly fewer unit-local data items than
   every other cut within WINDOW functions, else `alignment`. Calls are not used there: files call
   each other's APIs by design, and on the engine libraries the cut with the fewest crossing calls
   lands inside a file (T3DB_Compiler/T3DB_Lexer: 23 calls at the right cut, 2 at a wrong one).
   Across unpaired functions, each cut is scored by crossing data items, then crossing calls
   (`data`, `calls`); with no unique winner the gap shrinks from both ends, an unpaired function
   joining the neighbour it alone calls, is called by or shares data with (`calls` or `data` by the
   signal that closed it), and what remains is `open`. A gap holding a function the sibling pairs
   with a third unit is left `open`. A claimed unit never grows beyond its row.
6. Data edges, between the same neighbouring units, per data section and per original-object region
   of that section (the analysis splits a section where other objects or the uninitialised commons
   sit; each region holds the units in order). An item belongs to a unit when no function outside
   that unit references it; strings (`data:string`) and the merged `.sdata2` pool are left out. The
   cut misplaces the fewest owned items: `data` with none misplaced and two or more items each side,
   `thin` with none misplaced but one item on a side, `mixed` or `conflict` otherwise.

Claims: a `unit` row whose evidence column starts with CLAIM_PHRASE claims its extent. A claim with
both edges exact pins the unit: it must cover whole functions or the run fails, it replaces the
proposals it overlaps, and its edges never move. Any other claim is added only when it takes no
function a proposal holds; otherwise it is reported and skipped. Every other `unit` row is ignored.
The output is a proposal; it establishes no extent. Inputs: the sibling symbol table,
`evidence.tsv` (function extents and labels) and the analysis that `python3 build.py` writes to
build/analysis/ (symbols.txt, splits.txt and the split objects' relocations; their own inputs are
analysis.json, sdk.json, units.json and the pinned dtk)."""
import argparse
import bisect
import csv
import hashlib
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SIBLING = ROOT / 'references/NASCAR 2005/DOL-GN4E-USA/symbols/symbols.tsv'
COMPILE_UNITS = ROOT / 'references/NASCAR 2005/DOL-GN4E-USA/symbols/compile_units.tsv'
ANALYSIS = ROOT / 'build/analysis'
OUTPUT = 'boundaries'
TABLES = ('units.tsv', 'edges.tsv', 'names.tsv')

RUN = 4                   # functions in a size anchor
RUN_MIN_BYTES = 64        # a size anchor covers at least this many bytes
DENSITY = 0.6             # share of the target functions in a proposed unit that must be paired
RATIO = (0.75, 1.33)      # target / sibling function count and byte size of a proposed unit
RATIO_NAMED = (0.5, 2.0)  # the same with a name anchor inside the unit
SLACK = 0x100             # bytes of tolerance on the size test
UNMARKED_SIZE = 0x20000   # sibling units larger than this are piles of files
UNMARKED_FUNCTIONS = 200  # likewise (the largest marked Tiburon unit has 163)
WINDOW = 2                # cuts each side of the alignment's cut that the data test compares
GAP_LIMIT = 64            # longest unpaired gap the subsequence alignment attempts
POSITIONAL_PHRASE = 'Sibling alignment:'
CLAIM_PHRASE = 'Boundary claim:'
SECTION_NAMES = {'.data2': '.ctors/.dtors', '.data3': '.rodata', '.data4': '.data', '.bss': '.bss',
                 '.data5': '.sdata', '.sbss': '.sbss', '.data6': '.sdata2'}
POOLED = {'.data6'}       # merged constant pool (.sdata2): no ownership


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


# ---------------------------------------------------------------- inputs

def read_compile_units(path):
    """compile_units.tsv (tools/sibling_tables.py nascar-units) -> [(start, file, start_from)]"""
    lines = [l for l in Path(path).read_text().splitlines() if l and not l.startswith('#')]
    header = lines[0].split('\t')
    rows = [dict(zip(header, l.split('\t'))) for l in lines[1:]]
    return [(int(r['start'], 16), r['file'], r['start_from']) for r in rows]


def codeless_files(rows, placed):
    """{(placed file, occurrence): [files listed after it]} for file rows the unit table could not place: no
    marker and no local function. The export lists each file's local symbols file by file, then
    every global from `__start` on, so such a file's code (globals only) may lie in the unit
    listed before it, or nowhere."""
    last = max(i for i, row in enumerate(rows) if row['Type'] == '4')
    globals_from = next(i for i, row in enumerate(rows) if i > last and row['Name'] == '__start')
    others, current, seen = defaultdict(list), None, Counter()
    for row in rows[:globals_from]:
        if row['Type'] != '4':
            continue
        if row['Name'] in placed:
            current = (row['Name'], seen[row['Name']])
            seen[row['Name']] += 1
        elif current is not None and row['Name'] not in others[current]:
            others[current].append(row['Name'])
    return others


class Sibling:
    """Functions of the sibling build in address order, each with its unit (-1 before the first).
    Units come from the committed compile-unit table; functions and sizes from the symbol table."""

    def __init__(self, path, units_path=None):
        rows = list(csv.DictReader(open(path, newline=''), delimiter='\t'))
        units = read_compile_units(units_path or COMPILE_UNITS)
        self.unit_starts = [u[0] for u in units]
        self.unit_files = [u[1] for u in units]
        self.start_from = [u[2] for u in units]
        functions = sorted({(int(r['Address'], 16), int(r['Size']), r['Name'])
                            for r in rows if r['Type'] == '2' and int(r['Size']) > 0})
        self.address = [f[0] for f in functions]
        self.size = [f[1] for f in functions]
        self.name = [f[2] for f in functions]
        self.unit = [bisect.bisect_right(self.unit_starts, a) - 1 for a in self.address]
        self.counts = Counter(u for u in self.unit if u >= 0)
        self.bytes = Counter()
        for unit, size in zip(self.unit, self.size):
            if unit >= 0:
                self.bytes[unit] += size
        # A unit without a marker is proposed only between two marked units (memorycard.c inside
        # TibNew.cpp's range); next to another unmarked unit (the CodeWarrior SDK run, where the
        # export lists almost every function as a global) neither of its ends is reliable.
        self.unmarked = {u for u in self.counts
                         if self.counts[u] > UNMARKED_FUNCTIONS or self.bytes[u] > UNMARKED_SIZE
                         or (self.start_from[u] != 'gcc2_compiled'
                             and not (0 < u < len(units) - 1 and self.start_from[u - 1] == 'gcc2_compiled'
                                      and self.start_from[u + 1] == 'gcc2_compiled'))}
        names = Counter(self.name)
        self.unique_name = {n: i for i, n in enumerate(self.name) if names[n] == 1}
        others = codeless_files(rows, set(self.unit_files))
        # Repeated names (libgcc2.c) are matched occurrence by occurrence, in address order.
        self.other_files, seen = defaultdict(list), Counter()
        for unit, name in enumerate(self.unit_files):
            key = (name, seen[name])
            seen[name] += 1
            if others.get(key) and unit in self.counts:
                self.other_files[unit] = list(others[key])

    def file(self, unit):
        return self.unit_files[unit] if unit >= 0 else '-'


class Target:
    """Function extents and labels from evidence.tsv, in address order."""

    def __init__(self, evidence):
        rows = list(csv.DictReader(open(evidence, newline=''), delimiter='\t'))
        functions = sorted({(int(r['start'], 16), int(r['end'], 16), r['subject'])
                            for r in rows if r['kind'] == 'function' and r['start'] != '-' and r['end'] != '-'})
        self.start = [f[0] for f in functions]
        self.end = [f[1] for f in functions]
        self.label = [f[2] for f in functions]
        self.size = [e - s for s, e in zip(self.start, self.end)]
        self.positional = {r['subject'] for r in rows if r['kind'] == 'name'
                           and r['evidence'].startswith(POSITIONAL_PHRASE)}
        self.claims = [r for r in rows if r['kind'] == 'unit' and r['evidence'].startswith(CLAIM_PHRASE)]

    def index(self, address):
        return bisect.bisect_left(self.start, address)


# ------------------------------------------------------------ relocations

def read_splits(path):
    """splits.txt -> {object path: {section: (start, end)}}"""
    objects, current = {}, None
    for line in Path(path).read_text().splitlines():
        if line and not line[0].isspace() and line.endswith(':') and line != 'Sections:':
            current = objects.setdefault(line[:-1], {})
        elif current is not None and line.strip().startswith('.') and 'start:' in line:
            fields = dict(f.split(':', 1) for f in line.split()[1:] if ':' in f)
            current[line.split()[0]] = (int(fields['start'], 16), int(fields['end'], 16))
    return objects


def read_symbols(path):
    """symbols.txt -> ({name: address}, [(address, size, section, name, is_string)] data items)"""
    address, items = {}, []
    pattern = re.compile(r'^(\S+) = (\.\w+):0x([0-9A-Fa-f]+); // (.*)$')
    for line in Path(path).read_text().splitlines():
        match = pattern.match(line)
        if not match:
            continue
        name, section, value, rest = match.groups()
        value = int(value, 16)
        address[name] = value
        size = re.search(r'size:0x([0-9A-Fa-f]+)', rest)
        if section not in ('.init', '.text'):
            items.append((value, int(size.group(1), 16) if size else 0, section, name,
                          'data:string' in rest))
    return address, sorted(items)


def elf_relocations(path, section_starts, symbol_address):
    """Yield (source address, target address) for every relocation in a dtk split object."""
    data = Path(path).read_bytes()
    if data[:4] != b'\x7fELF':
        raise ValueError('%s is not an ELF object' % path)
    shoff, = struct.unpack_from('>I', data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', data, 0x2E)
    headers = [struct.unpack_from('>IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    strtab = headers[shstrndx]

    def string(table, offset):
        start = table[4] + offset
        return data[start:data.index(b'\0', start)].decode('latin-1')
    names = [string(strtab, h[0]) for h in headers]
    for header in headers:
        if header[1] != 4:   # SHT_RELA
            continue
        base = section_starts.get(names[header[7]])   # sh_info: the section relocated
        if base is None:
            continue
        symtab = headers[header[6]]
        symstr = headers[symtab[6]]
        for offset in range(header[4], header[4] + header[5], 12):
            r_offset, r_info, r_addend = struct.unpack_from('>IIi', data, offset)
            symbol = r_info >> 8
            st_name, st_value, _, _, _, st_shndx = struct.unpack_from('>IIIBBH', data, symtab[4] + symbol * 16)
            label = string(symstr, st_name)
            if label in symbol_address:
                yield base + r_offset, symbol_address[label] + r_addend
            elif 0 < st_shndx < len(names) and names[st_shndx] in section_starts:
                yield base + r_offset, section_starts[names[st_shndx]] + st_value + r_addend


class References:
    """Per target function: the data items it references and the functions it calls; per data
    item: the original-object region (split object) that holds it."""

    def __init__(self, target, analysis=ANALYSIS):
        symbol_address, items = read_symbols(analysis / 'symbols.txt')
        self.items = [i for i in items if i[2] in SECTION_NAMES]
        self.item_starts = [i[0] for i in self.items]
        self.data = defaultdict(set)
        self.calls = defaultdict(set)
        splits = read_splits(analysis / 'splits.txt')
        regions = sorted((start, end, path) for path, sections in splits.items()
                         for section, (start, end) in sections.items() if section in SECTION_NAMES)
        self.region = []
        for start, _, _, _, _ in self.items:
            i = bisect.bisect_right([r[0] for r in regions], start) - 1
            self.region.append(regions[i][2] if i >= 0 and start < regions[i][1] else '-')
        missing = []
        for path, sections in splits.items():
            obj = analysis / 'split/obj' / Path(path).with_suffix('.o')
            if not obj.exists():
                missing.append(obj)
                continue
            starts = {s: r[0] for s, r in sections.items()}
            for source, destination in elf_relocations(obj, starts, symbol_address):
                caller = bisect.bisect_right(target.start, source) - 1
                if caller < 0 or source >= target.end[caller]:
                    continue
                callee = bisect.bisect_right(target.start, destination) - 1
                if callee >= 0 and destination < target.end[callee]:
                    if callee != caller:
                        self.calls[caller].add(callee)
                    continue
                item = self.item(destination)
                if item is not None:
                    self.data[caller].add(item)
        if missing:
            raise SystemExit('boundaries: %d split objects missing (first %s); rebuild with python3 build.py'
                             % (len(missing), missing[0]))
        self.callers = defaultdict(set)
        for caller, callees in self.calls.items():
            for callee in callees:
                self.callers[callee].add(caller)

    def item(self, address):
        i = bisect.bisect_right(self.item_starts, address) - 1
        if i < 0:
            return None
        start, size, section, _, is_string = self.items[i]
        if address >= start + max(size, 1) or section in POOLED or is_string:
            return None
        return i


# ---------------------------------------------------------------- anchors

def size_anchors(target, sibling):
    """Mutual-unique runs of RUN function sizes -> {target index: sibling index}."""
    def runs(sizes):
        table = defaultdict(list)
        for i in range(len(sizes) - RUN + 1):
            table[tuple(sizes[i:i + RUN])].append(i)
        return table
    ours, theirs = runs(target.size), runs(sibling.size)
    pairs = {}
    for key, positions in ours.items():
        if len(positions) == 1 and len(theirs.get(key, ())) == 1 and sum(key) >= RUN_MIN_BYTES:
            for k in range(RUN):
                pairs.setdefault(positions[0] + k, theirs[key][0] + k)
    return pairs


def name_anchors(target, sibling):
    pairs = {}
    for i, label in enumerate(target.label):
        if label in target.positional or label.startswith(('fn_', 'lbl_')):
            continue
        j = sibling.unique_name.get(label)
        if j is not None and sibling.size[j] == target.size[i]:
            pairs[i] = j
    return pairs


def chain(candidates):
    """Heaviest chain strictly increasing in both indices: [(target, sibling, kind)]. A Fenwick
    tree over sibling indices keeps it O(n log n); the input is sorted, so equal target indices
    never chain (each candidate's target index is unique by construction)."""
    items = sorted(candidates)
    if not items:
        return []
    weight = {'name': 1000, 'size': 1}
    size = max(j for _, j, _ in items) + 2
    tree = [(0, -1)] * (size + 1)

    def query(position):
        best = (0, -1)
        while position > 0:
            best = max(best, tree[position])
            position -= position & -position
        return best

    def update(position, value):
        while position <= size:
            if value > tree[position]:
                tree[position] = value
            position += position & -position
    score, previous = [0] * len(items), [-1] * len(items)
    for n, (i, j, kind) in enumerate(items):
        best, back = query(j + 1)    # positions 1..j+1 hold sibling indices 0..j-1 (+1 shift)
        score[n], previous[n] = best + weight[kind], back
        update(j + 2, (score[n], n))
    n = max(range(len(items)), key=score.__getitem__)
    kept = []
    while n >= 0:
        kept.append(items[n])
        n = previous[n]
    return kept[::-1]


def anchors(target, sibling, names=None, sizes=None):
    names = name_anchors(target, sibling) if names is None else names
    sizes = size_anchors(target, sibling) if sizes is None else sizes
    candidates = [(i, j, 'name') for i, j in names.items()]
    candidates += [(i, j, 'size') for i, j in sizes.items() if i not in names]
    return chain(candidates)


# -------------------------------------------------------------- alignment

def common_subsequence(a, b):
    """Index pairs of a longest common subsequence of two short size lists."""
    table = [[0] * (len(b) + 1) for _ in range(len(a) + 1)]
    for x in range(len(a) - 1, -1, -1):
        for y in range(len(b) - 1, -1, -1):
            table[x][y] = table[x + 1][y + 1] + 1 if a[x] == b[y] else max(table[x + 1][y], table[x][y + 1])
    pairs, x, y = [], 0, 0
    while x < len(a) and y < len(b):
        if a[x] == b[y]:
            pairs.append((x, y))
            x, y = x + 1, y + 1
        elif table[x + 1][y] >= table[x][y + 1]:
            x += 1
        else:
            y += 1
    return pairs


def align(target, sibling, kept):
    """{target index: (sibling index, how)} for anchors and the gaps between them."""
    paired = {i: (j, kind) for i, j, kind in kept}
    for (i0, j0, _), (i1, j1, _) in zip(kept, kept[1:]):
        ours, theirs = range(i0 + 1, i1), range(j0 + 1, j1)
        if not ours or not theirs:
            continue
        a = [target.size[i] for i in ours]
        b = [sibling.size[j] for j in theirs]
        if a == b:
            for i, j in zip(ours, theirs):
                paired[i] = (j, 'gap')
        elif len(a) <= GAP_LIMIT and len(b) <= GAP_LIMIT:
            for x, y in common_subsequence(a, b):
                paired[ours[x]] = (theirs[y], 'gap')
    return paired


# ------------------------------------------------------------------ units

def size_rule(target, sibling, unit, members):
    """True when a unit [first, last] passes the size rule for its sibling unit."""
    first, last = unit['first'], unit['last']
    inside = [m for m in members if first <= m[0] <= last]
    named = any(how == 'name' for _, how in inside)
    sized = sum(1 for _, how in inside if how == 'size')
    count, theirs = last - first + 1, sibling.counts[unit['unit']]
    extent, their_bytes = target.end[last] - target.start[first], sibling.bytes[unit['unit']]
    low, high = RATIO_NAMED if named else RATIO
    return ((named or sized >= RUN) and len(inside) >= DENSITY * count
            and low <= count / theirs <= high
            and low * their_bytes - SLACK <= extent <= high * their_bytes + SLACK)


def unit_members(sibling, paired):
    members = defaultdict(list)
    for i, (j, how) in paired.items():
        if sibling.unit[j] >= 0:
            members[sibling.unit[j]].append((i, how))
    for entries in members.values():
        entries.sort()
    return members


def propose_units(target, sibling, paired, members=None):
    """[{unit, file, first, last, paired, anchors, claim}] in address order."""
    members = unit_members(sibling, paired) if members is None else members
    units = []
    for unit, entries in members.items():
        if unit in sibling.unmarked:
            continue
        candidate = {'unit': unit, 'file': sibling.file(unit), 'first': entries[0][0], 'last': entries[-1][0],
                     'claim': ''}
        if size_rule(target, sibling, candidate, entries):
            units.append(candidate)
    units.sort(key=lambda u: u['first'])
    # Overlapping proposals (interleaved sibling units) cannot both be files: keep the one with
    # more paired functions.
    kept = []
    for unit in units:
        if kept and unit['first'] <= kept[-1]['last']:
            mine = len(members[unit['unit']])
            theirs = len(members[kept[-1]['unit']])
            if mine > theirs:
                kept[-1] = unit
            continue
        kept.append(unit)
    return kept


def apply_claims(target, units, report):
    """Pinned claims replace what they overlap and must cover whole functions (else SystemExit);
    provisional claims are added only over functions no proposal holds."""
    for row in target.claims:
        start, end = int(row['start'], 16), int(row['end'], 16)
        first, last = target.index(start), target.index(end) - 1
        pinned = row['start_boundary'] == 'exact' and row['end_boundary'] == 'exact'
        whole = first <= last < len(target.start) and target.start[first] == start and target.end[last] == end
        if not whole:
            message = 'claim %s %s-%s does not cover whole functions' % (row['subject'], row['start'], row['end'])
            if pinned:
                raise SystemExit('boundaries: ' + message)
            report.append(message + '; skipped')
            continue
        overlap = [u for u in units if u['first'] <= last and first <= u['last']]
        if overlap and not pinned:
            report.append('claim %s takes functions a proposal holds (%s); skipped'
                          % (row['subject'], ', '.join(u['file'] for u in overlap)))
            continue
        if any(u['claim'] == 'exact' for u in overlap):
            raise SystemExit('boundaries: claims overlap at %s' % row['subject'])
        for unit in overlap:
            units.remove(unit)
        units.append({'unit': None, 'file': row['subject'], 'first': first, 'last': last,
                      'claim': 'exact' if pinned else 'provisional'})
    units.sort(key=lambda u: u['first'])


# ------------------------------------------------------------------ edges

def crossing(references, left, cut, right):
    """(data items, calls) shared across a cut between target index ranges [left, cut) and [cut, right]."""
    before, after = set(), set()
    for i in range(left, cut):
        before |= references.data.get(i, set())
    for i in range(cut, right + 1):
        after |= references.data.get(i, set())
    calls = 0
    for i in range(left, cut):
        calls += sum(1 for c in references.calls.get(i, ()) if cut <= c <= right)
    for i in range(cut, right + 1):
        calls += sum(1 for c in references.calls.get(i, ()) if left <= c < cut)
    return (len(before & after), calls)


def neighbours(sibling, left, right):
    """True when no sibling unit with functions lies between two proposed units."""
    if left['unit'] is None or right['unit'] is None:
        return True
    return all(u not in sibling.counts for u in range(left['unit'] + 1, right['unit']))


def link(references, function, unit):
    """The signals that tie a function to a unit's functions: a subset of {'calls', 'data'}."""
    members = range(unit['first'], unit['last'] + 1)
    signals = set()
    if any(c in members for c in references.calls.get(function, ())) \
            or any(c in members for c in references.callers.get(function, ())):
        signals.add('calls')
    items = references.data.get(function, set())
    if any(items & references.data.get(m, set()) for m in members):
        signals.add('data')
    return signals


def shrink(references, left, right, paired=()):
    """Give each end of an unpaired gap to the neighbour it alone is linked to. Returns the
    signals used; a claimed unit takes nothing, and a function the sibling pairs with another unit
    is never given away."""
    used = set()
    while left['last'] + 1 < right['first']:
        first, last = left['last'] + 1, right['first'] - 1
        a, b = link(references, first, left), link(references, first, right)
        if first not in paired and not left['claim'] and a and not b:
            left['last'] = first
            used |= a
            continue
        a, b = link(references, last, right), link(references, last, left)
        if last not in paired and not right['claim'] and a and not b:
            right['first'] = last
            used |= a
            continue
        break
    return used


def text_edges(target, sibling, units, paired, references):
    edges = []
    for left, right in zip(units, units[1:]):
        pinned = left['claim'] == 'exact' or right['claim'] == 'exact'
        gap = right['first'] - left['last'] - 1
        if pinned and gap == 0:
            edges.append(edge(target, references, left, right, right['first'], 'claimed', sibling=sibling))
            continue
        if not neighbours(sibling, left, right):
            # Sibling units between them are not proposed here: each side's end stays open.
            edges.append(edge(target, references, left, right, None, 'open', sibling=sibling))
            continue
        if gap == 0:
            cut = right['first']
            scores = {c: crossing(references, left['first'], c, right['last'])[0]
                      for c in range(max(cut - WINDOW, left['first'] + 1), min(cut + WINDOW, right['last']) + 1)}
            unique = all(scores[cut] < v for c, v in scores.items() if c != cut) and len(scores) > 1
            edges.append(edge(target, references, left, right, cut, 'data' if unique else 'alignment', sibling=sibling))
            continue
        if any(i in paired for i in range(left['last'] + 1, right['first'])):
            # The gap holds a function the sibling pairs with a third unit: a wall, not ours to cut.
            edges.append(edge(target, references, left, right, None, 'open', sibling=sibling))
            continue
        if left['claim'] or right['claim']:
            # A claimed unit holds exactly its row: only the other side may move, by shrinking.
            used = shrink(references, left, right, paired)
            closed = left['last'] + 1 == right['first']
            edges.append(edge(target, references, left, right, right['first'] if closed else None,
                              ('calls' if 'calls' in used else 'data') if closed else 'open', sibling=sibling))
            continue
        candidates = list(range(left['last'] + 1, right['first'] + 1))
        scores = {c: crossing(references, left['first'], c, right['last']) for c in candidates}
        best = min(v[0] for v in scores.values())
        tied = [c for c in candidates if scores[c][0] == best]
        fewest = min(scores[c][1] for c in tied)
        by_calls = [c for c in tied if scores[c][1] == fewest]
        if len(tied) == 1:
            edges.append(edge(target, references, left, right, tied[0], 'data', sibling=sibling))
        elif len(by_calls) == 1:
            edges.append(edge(target, references, left, right, by_calls[0], 'calls', sibling=sibling))
        else:
            used = shrink(references, left, right, paired)
            closed = left['last'] + 1 == right['first']
            kind = ('calls' if 'calls' in used else 'data') if closed else 'open'
            edges.append(edge(target, references, left, right, right['first'] if closed else None, kind, sibling=sibling))
    return edges


def edge(target, references, left, right, cut, kind, sibling=None):
    if cut is not None and kind in ('data', 'alignment', 'calls') and sibling is not None \
            and right['unit'] is not None and sibling.start_from[right['unit']] != 'gcc2_compiled':
        # The right unit's sibling start is its lowest local function: its global functions may
        # come first, so the true edge is at or before this cut.
        kind = 'at-or-before'
    if cut is not None:
        left['last'] = cut - 1
        right['first'] = cut
        data, calls = crossing(references, left['first'], cut, right['last'])
        low = high = target.start[cut]
    else:
        data = calls = None
        low, high = target.end[left['last']], target.start[right['first']]
    return {'left': left, 'right': right, 'address': target.start[cut] if cut is not None else None,
            'kind': kind, 'data': data, 'calls': calls, 'low': low, 'high': high}


def settle(target, sibling, paired, references, report):
    """Propose units, apply claims, place edges, and drop units the edges pushed outside the size
    rule, until nothing changes."""
    members = unit_members(sibling, paired)
    dropped = set()
    while True:
        units = [u for u in propose_units(target, sibling, paired, members) if u['unit'] not in dropped]
        del report[:]
        apply_claims(target, units, report)
        edges = text_edges(target, sibling, units, paired, references)
        failing = [u for u in units if u['unit'] is not None and not u['claim']
                   and not size_rule(target, sibling, u, members[u['unit']])]
        if not failing:
            return units, edges
        dropped.update(u['unit'] for u in failing)


def data_edges(units, edges, references):
    """Data-section edges between units whose text edge is between sibling neighbours."""
    unit_of = {}
    for n, unit in enumerate(units):
        for i in range(unit['first'], unit['last'] + 1):
            unit_of[i] = n
    owner = defaultdict(set)
    for function, items in references.data.items():
        for item in items:
            owner[item].add(unit_of.get(function, -1))
    owned = defaultdict(lambda: defaultdict(list))
    for item, users in owner.items():
        if len(users) == 1 and -1 not in users:
            n, = users
            owned[(references.items[item][2], references.region[item])][n].append(item)
    pairs = {id(e['left']): e for e in edges if e['kind'] != 'open' or e['address'] is not None}
    rows = []
    for (section, region), by_unit in sorted(owned.items()):
        for a in sorted(by_unit):
            b = a + 1
            if b not in by_unit or id(units[a]) not in pairs:
                continue
            left, right = sorted(by_unit[a]), sorted(by_unit[b])
            best = None
            for cut in sorted(set(left + right + [max(left + right) + 1])):
                wrong = sum(1 for i in left if i >= cut) + sum(1 for i in right if i < cut)
                if best is None or wrong < best[0]:
                    best = (wrong, cut)
            wrong, cut = best
            below = [i for i in left if i < cut]
            above = [i for i in right if i >= cut]
            low_item = references.items[max(below)] if below else None
            high_item = references.items[min(above)] if above else None
            if wrong == 0:
                kind = 'data' if min(len(left), len(right)) >= 2 else 'thin'
            else:
                kind = 'conflict' if wrong >= 2 and wrong * 2 >= min(len(left), len(right)) else 'mixed'
            rows.append({'section': SECTION_NAMES[section], 'left': units[a]['file'], 'right': units[b]['file'],
                         'low': low_item[0] + low_item[1] if low_item else None,
                         'high': high_item[0] if high_item else None, 'kind': kind, 'misplaced': wrong,
                         'items': '%d/%d' % (len(left), len(right))})
    return rows


# ---------------------------------------------------------------- run

def run(target_id):
    config = ROOT / 'config' / target_id
    sibling = Sibling(SIBLING)
    target = Target(config / 'evidence.tsv')
    references = References(target)
    kept = anchors(target, sibling)
    paired = align(target, sibling, kept)
    report = []
    units, edges = settle(target, sibling, paired, references, report)
    return {'sibling': sibling, 'target': target, 'anchors': kept, 'paired': paired, 'units': units,
            'edges': edges, 'data_edges': data_edges(units, edges, references), 'report': report}


def hexa(value):
    return '-' if value is None else '0x%08X' % value


def tables(result):
    sibling, target = result['sibling'], result['target']
    members = unit_members(sibling, result['paired'])
    header = ('# tools/boundaries.py sha256 %s\n# sibling %s sha256 %s\n# sibling %s sha256 %s\n'
              % (digest(__file__), SIBLING.relative_to(ROOT).as_posix(), digest(SIBLING),
                 COMPILE_UNITS.relative_to(ROOT).as_posix(), digest(COMPILE_UNITS)))
    units = [header + '# Proposed units; a proposal, not an established extent (evidence: one unit-anchor row per run).\n'
             'start\tend\tsibling_file\tfunctions\tpaired\tsibling_functions\tname_anchors\tsize_anchors\tclaim\tother_files']
    holder = {}
    for unit in result['units']:
        inside = [m for m in members.get(unit['unit'], ()) if unit['first'] <= m[0] <= unit['last']]
        for i in range(unit['first'], unit['last'] + 1):
            holder[i] = unit['file']
        units.append('\t'.join([hexa(target.start[unit['first']]), hexa(target.end[unit['last']]), unit['file'],
                                str(unit['last'] - unit['first'] + 1), str(len(inside)),
                                str(sibling.counts[unit['unit']]) if unit['unit'] is not None else '-',
                                str(sum(1 for _, h in inside if h == 'name')),
                                str(sum(1 for _, h in inside if h == 'size')), unit['claim'] or '-',
                                ','.join(sibling.other_files.get(unit['unit'], ())) or '-']))
    edges = [header + '# Text edges: class data, calls, alignment, claimed or open (low-high: the open range).\n'
             '# Data edges: class data, thin, mixed or conflict; crossing_data holds misplaced items, crossing_calls owned items left/right.\n'
             'section\taddress\tlow\thigh\tclass\tcrossing_data\tcrossing_calls\tleft\tright']
    for e in result['edges']:
        edges.append('\t'.join(['.text', hexa(e['address']), hexa(e['low']), hexa(e['high']), e['kind'],
                                '-' if e['data'] is None else str(e['data']),
                                '-' if e['calls'] is None else str(e['calls']), e['left']['file'], e['right']['file']]))
    for e in result['data_edges']:
        edges.append('\t'.join([e['section'], '-', hexa(e['low']), hexa(e['high']), e['kind'],
                                str(e['misplaced']), e['items'], e['left'], e['right']]))
    names = [header + '# Target functions paired with a sibling function. how: name, size (a size-run anchor) or gap\n'
             '# (paired between anchors by equal size only). unit: the proposed unit holding it, or -; only rows\n'
             '# inside a proposed unit are naming candidates, and a gap pair needs its own check.\n'
             'address\tsize\tsibling_name\thow\tsibling_file\tunit']
    for i in sorted(result['paired']):
        j, how = result['paired'][i]
        names.append('\t'.join([hexa(target.start[i]), str(target.size[i]), sibling.name[j], how,
                                sibling.file(sibling.unit[j]), holder.get(i, '-')]))
    return {'units.tsv': '\n'.join(units) + '\n', 'edges.tsv': '\n'.join(edges) + '\n',
            'names.tsv': '\n'.join(names) + '\n'}


def established(target_id):
    """Units whose extent a reviewed row establishes: `unit` rows with both edges exact."""
    rows = csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t')
    return sorted((int(r['start'], 16), int(r['end'], 16), r['subject']) for r in rows
                  if r['kind'] == 'unit' and r['start_boundary'] == 'exact' and r['end_boundary'] == 'exact')


def calibrate(target_id):
    """Hold-out test (wiki "Check before relying on it"): drop the claims and every anchor, name or
    size, inside the established units, run, and count their edges reproduced, merged (inside a
    proposed unit) and split (a proposed edge inside an established unit). The established units
    in the aligned span were themselves drawn from this sibling table, so this checks the method's
    mechanics, not the sibling's truth for this target."""
    sibling = Sibling(SIBLING)
    target = Target(ROOT / 'config' / target_id / 'evidence.tsv')
    target.claims = []
    units = established(target_id)
    held = set()
    for start, end, _ in units:
        held.update(range(target.index(start), target.index(end)))
    names = {i: j for i, j in name_anchors(target, sibling).items() if i not in held}
    sizes = {i: j for i, j in size_anchors(target, sibling).items() if i not in held}
    references = References(target)
    kept = anchors(target, sibling, names, sizes)
    paired = align(target, sibling, kept)
    proposed, edges = settle(target, sibling, paired, references, [])
    spans = [(target.start[u['first']], target.end[u['last']]) for u in proposed]
    low, high = min(s for s, _ in spans), max(e for _, e in spans)
    known = {e for s, t, _ in units for e in (s, t) if low < e < high}
    placed = {e['address']: e['kind'] for e in edges if e['address'] is not None}
    reproduced = Counter(placed[k] for k in known if k in placed)
    merged = [k for k in known if any(s < k < e for s, e in spans)]
    in_open = [k for k in known if any(e['address'] is None and e['low'] <= k <= e['high'] for e in edges)]
    split = [(a, kind) for a, kind in placed.items() if any(s < a < t for s, t, _ in units)]
    print('established units (both edges exact): %d; edges inside the aligned span: %d' % (len(units), len(known)))
    print('reproduced exactly, by class: %s' % dict(reproduced))
    print('inside an open range: %d; merged into a proposed unit: %d %s' %
          (len(in_open), len(merged), [hexa(k) for k in merged]))
    print('proposed edges inside an established unit (split): %d %s' % (len(split), [(hexa(a), k) for a, k in split]))
    print('note: the established units in this span were drawn from the same sibling table, so this '
          'is not an independent known answer')
    rows = list(csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t'))
    current = [(int(r['start'], 16), int(r['end'], 16)) for r in rows if r['kind'] == 'unit']
    run_edges = {e for u in current for e in u if low < e < high}
    full = run(target_id)
    spans = [(full['target'].start[u['first']], full['target'].end[u['last']]) for u in full['units']]
    placed = [e for e in full['edges'] if e['address'] is not None]
    print('full run against every current unit row (mostly provisional, not a known answer): agree %s, '
          'would split a current unit %s, current edges merged into a proposed unit %d' % (
              dict(Counter(e['kind'] for e in placed if e['address'] in run_edges)),
              dict(Counter(e['kind'] for e in placed if e['address'] not in run_edges)),
              sum(1 for k in run_edges if any(s < k < t for s, t in spans))))
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    parser.add_argument('--target', default='GN7E69-rev0',
                        help='target id (the analysis read is build/analysis, the one python3 build.py writes)')
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true', help='update the committed tables')
    mode.add_argument('--check', action='store_true', help='fail when the committed tables differ')
    mode.add_argument('--calibrate', action='store_true', help='hold-out test against established units')
    args = parser.parse_args(argv)
    if not (ANALYSIS / 'summary.json').exists() or not (ANALYSIS / 'split/obj').is_dir():
        sys.exit('boundaries: build/analysis is missing or incomplete (no summary.json or split objects); '
                 'run python3 build.py first')
    if args.calibrate:
        return calibrate(args.target)
    result = run(args.target)
    for line in result['report']:
        print('boundaries: ' + line, file=sys.stderr)
    produced = tables(result)
    directory = ROOT / 'config' / args.target / OUTPUT
    if args.write:
        directory.mkdir(exist_ok=True)
        for name, text in produced.items():
            (directory / name).write_text(text)
        print('boundaries: wrote %s' % ', '.join((directory / n).relative_to(ROOT).as_posix() for n in TABLES))
        return 0
    if args.check:
        stale = [n for n, text in produced.items()
                 if not (directory / n).exists() or (directory / n).read_text() != text]
        if stale:
            print('boundaries: %s differ from a fresh run; run python3 tools/boundaries.py --write and commit them'
                  % ', '.join('config/%s/%s/%s' % (args.target, OUTPUT, n) for n in stale), file=sys.stderr)
            return 1
        print('boundaries: committed tables are current')
        return 0
    print('anchors %d (%s), paired %d, units %d, text edges %d %s, data edges %d %s' % (
        len(result['anchors']), dict(Counter(k for _, _, k in result['anchors'])), len(result['paired']),
        len(result['units']), len(result['edges']), dict(Counter(e['kind'] for e in result['edges'])),
        len(result['data_edges']), dict(Counter(e['kind'] for e in result['data_edges']))))
    return 0


if __name__ == '__main__':
    sys.exit(main())
