#!/usr/bin/env python3
"""Propose unit (file) boundaries from a sibling build's compile units (wiki: "Recover unit splits
from a sibling build").

    python3 tools/boundaries.py [--target ID]              print a summary of the run
    python3 tools/boundaries.py --write [--target ID]      update the committed tables
    python3 tools/boundaries.py --check [--target ID]      fail when the committed tables differ
    python3 tools/boundaries.py --calibrate [--target ID]  known-answer test against established edges

The sibling is NASCAR 2005 (Tiburon, 2004, same ProDG toolchain): its symbol table names every
function, its size and, through the `gcc2_compiled.` markers and the file-name rows before them,
the compile unit that holds it. The sibling's executable is not kept, so functions are paired by
names and sizes, never by code:

1. Anchors. A name anchor is a target function whose label equals the name of exactly one sibling
   function, unless the label came from this script's alignment (its `name` row starts with
   POSITIONAL_PHRASE). A size anchor is a run of RUN consecutive functions whose sizes occur once
   in each build and nowhere else (mutual unique). Name anchors outweigh size anchors; the kept
   anchors are the heaviest chain that increases in both builds (link order: the same linker, so
   the sibling's order is the template, which the chain confirms by existing).
2. Alignment. Between two anchors, the functions pair one to one when both gaps hold the same
   sizes in the same order; otherwise equal sizes pair by longest common subsequence.
3. Units. A sibling compile unit becomes a proposed unit over its paired target functions when they
   carry at least MIN_SUPPORT anchors, at least DENSITY of the target functions in that extent are
   paired, and its function count and size are close to the sibling's (RATIO, wider with a name
   anchor: RATIO_NAMED). Compile units with no marker-separated structure
   (over UNMARKED_SIZE bytes, the CodeWarrior SDK run and similar piles) propose nothing.
4. Text edges. Between two consecutive proposed units, each function boundary from WINDOW
   functions before the alignment's cut to WINDOW after (or across the unpaired gap) is scored by
   the data items referenced from both sides; ties break by calls. The class records what decided
   it: data, calls, alignment (the alignment's own cut kept among ties) or open. An open edge then
   shrinks from both ends: an unpaired function joins the neighbour it alone calls, is called by or
   shares data with.
5. Data edges. In every data section an item belongs to a unit when only that unit references it.
   The edge between two units lies between the left unit's last item and the right unit's first;
   an inverted pair is reported as a conflict, a sign of a wrong text edge.

Claims: a `unit` row whose evidence column starts with CLAIM_PHRASE claims its extent. A claim with
both edges exact replaces the proposal it overlaps; any other claim takes only functions no
proposal holds. Every other `unit` row is ignored. The output is a proposal; it establishes no
extent. Inputs are the sibling symbol table, `evidence.tsv` (function extents and names) and the
analysis split objects (relocations) that `python3 build.py` writes to build/analysis/."""
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
ANALYSIS = ROOT / 'build/analysis'
OUTPUT = 'boundaries'
TABLES = ('units.tsv', 'edges.tsv', 'names.tsv')

RUN = 4               # functions in a size anchor
RUN_MIN_BYTES = 64    # a size anchor covers at least this many bytes
MIN_SUPPORT = 2       # anchors a unit needs before it is proposed
DENSITY = 0.6         # share of the target functions in a proposed unit that must be paired
RATIO = (0.75, 1.33)  # target / sibling function count of a proposed unit
RATIO_NAMED = (0.5, 2.0)  # the same with a name anchor inside the unit
UNMARKED_SIZE = 0x8000 * 4  # sibling compile units larger than this have no usable inner markers
WINDOW = 2            # functions each side of the alignment's cut that the edge scorer may try
GAP_LIMIT = 64        # longest unpaired gap the subsequence alignment attempts
POSITIONAL_PHRASE = 'Sibling alignment:'
CLAIM_PHRASE = 'Boundary claim:'
SECTION_NAMES = {'.data2': '.ctors/.dtors', '.data3': '.rodata', '.data4': '.data', '.bss': '.bss',
                 '.data5': '.sdata', '.sbss': '.sbss', '.data6': '.sdata2'}
POOLED = {'.data6'}   # merged constant pool (.sdata2): no ownership


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


# ---------------------------------------------------------------- inputs

class Sibling:
    """Functions of the sibling build in address order, each with its compile unit."""

    def __init__(self, path):
        rows = list(csv.DictReader(open(path, newline=''), delimiter='\t'))
        last_file, units = None, {}
        for row in rows:
            if row['Type'] == '4':
                last_file = row['Name']
            elif row['Name'] == 'gcc2_compiled.':
                units.setdefault(int(row['Address'], 16), last_file)
        self.unit_starts = sorted(units)
        self.unit_files = [units[a] for a in self.unit_starts]
        functions = sorted({(int(r['Address'], 16), int(r['Size']), r['Name'])
                            for r in rows if r['Type'] == '2' and int(r['Size']) > 0})
        self.address = [f[0] for f in functions]
        self.size = [f[1] for f in functions]
        self.name = [f[2] for f in functions]
        self.unit = [bisect.bisect_right(self.unit_starts, a) - 1 for a in self.address]
        end = functions[-1][0] + functions[-1][1]
        bounds = self.unit_starts + [end]
        self.bounds = bounds
        self.unmarked = {i for i in range(len(self.unit_starts)) if bounds[i + 1] - bounds[i] > UNMARKED_SIZE}
        counts = Counter(self.name)
        self.unique_name = {n: i for i, n in enumerate(self.name) if counts[n] == 1}

    def unit_bytes(self, unit):
        return self.bounds[unit + 1] - self.bounds[unit]


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
    """splits.txt -> {object path: {section: start}}"""
    objects, current = {}, None
    for line in Path(path).read_text().splitlines():
        if line and not line[0].isspace() and line.endswith(':') and line != 'Sections:':
            current = objects.setdefault(line[:-1], {})
        elif current is not None and line.strip().startswith('.') and 'start:' in line:
            fields = line.split()
            current[fields[0]] = int(fields[1].split(':')[1], 16)
    return objects


def read_symbols(path):
    """symbols.txt -> ({name: address}, [(address, size, section, name)] data items)"""
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
            items.append((value, int(size.group(1), 16) if size else 0, section, name))
    return address, sorted(items)


def elf_relocations(path, section_starts, symbol_address):
    """Yield (source address, target address) for every relocation in a dtk split object."""
    data = Path(path).read_bytes()
    if data[:4] != b'\x7fELF':
        return
    shoff, = struct.unpack_from('>I', data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', data, 0x2E)
    headers = [struct.unpack_from('>IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    strtab = headers[shstrndx]

    def string(table, offset):
        start = table[4] + offset
        return data[start:data.index(b'\0', start)].decode('latin-1')
    names = [string(strtab, h[0]) for h in headers]
    for header, name in zip(headers, names):
        if header[1] != 4:   # SHT_RELA
            continue
        target_section = names[header[7]]   # sh_info
        base = section_starts.get(target_section)
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
    """Per target function: the data items it references and the functions it calls."""

    def __init__(self, target, analysis=ANALYSIS):
        symbol_address, items = read_symbols(analysis / 'symbols.txt')
        self.items = [i for i in items if i[2] in SECTION_NAMES]
        self.item_starts = [i[0] for i in self.items]
        self.data = defaultdict(set)
        self.calls = defaultdict(set)
        for path, sections in read_splits(analysis / 'splits.txt').items():
            obj = analysis / 'split/obj' / Path(path).with_suffix('.o')
            if not obj.exists():
                continue
            for source, destination in elf_relocations(obj, sections, symbol_address):
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

    def item(self, address):
        i = bisect.bisect_right(self.item_starts, address) - 1
        if i < 0:
            return None
        start, size, section, _ = self.items[i]
        if address >= start + max(size, 1) or section in POOLED or self.string(i):
            return None
        return i

    def string(self, i):
        return self.items[i][3].startswith(('@stringBase', '$$', 'str_'))


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
    """Heaviest chain increasing in both indices: [(target, sibling, kind)]."""
    items = sorted(candidates)
    weight = {'name': 1000, 'size': 1}
    # Patience-style for equal weights would lose name priority; the candidate count is small
    # enough (a few thousand) for the quadratic dynamic programme over a sorted list, but bounded
    # with a Fenwick tree over sibling indices to keep it O(n log n).
    size = max((j for _, j, _ in items), default=0) + 2
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
        best, back = query(j + 1)    # sibling indices strictly below j (positions 1..j+1 hold 0..j)
        # strict increase in target index: items with the same i are not chained (one pair per i)
        score[n], previous[n] = best + weight[kind], back
        update(j + 2, (score[n], n))
    if not items:
        return []
    n = max(range(len(items)), key=score.__getitem__)
    kept = []
    while n >= 0:
        kept.append(items[n])
        n = previous[n]
    return kept[::-1]


def anchors(target, sibling):
    names = name_anchors(target, sibling)
    sizes = size_anchors(target, sibling)
    candidates = [(i, j, 'name') for i, j in names.items()]
    candidates += [(i, j, 'size') for i, j in sizes.items() if i not in names]
    kept = chain(candidates)
    seen, result = set(), []
    for i, j, kind in kept:       # one pair per target function
        if i not in seen:
            seen.add(i)
            result.append((i, j, kind))
    return result


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

def propose_units(target, sibling, paired):
    """[{unit, file, first, last, functions, sibling_functions, support}] in address order."""
    members = defaultdict(list)
    for i, (j, how) in paired.items():
        members[sibling.unit[j]].append((i, how))
    sibling_counts = Counter(sibling.unit)
    units = []
    for unit, entries in members.items():
        if unit in sibling.unmarked:
            continue
        entries.sort()
        support = sum(1 for _, how in entries if how != 'gap')
        named = any(how == 'name' for _, how in entries)
        first, last = entries[0][0], entries[-1][0]
        count, theirs = last - first + 1, sibling_counts[unit]
        low, high = RATIO_NAMED if named else RATIO
        extent = target.end[last] - target.start[first]
        if (support < MIN_SUPPORT or len(entries) < DENSITY * count
                or not low <= count / theirs <= high or extent > high * sibling.unit_bytes(unit) + 0x100):
            continue
        units.append({'unit': unit, 'file': sibling.unit_files[unit], 'first': first, 'last': last,
                      'paired': len(entries), 'functions': last - first + 1,
                      'sibling_functions': sibling_counts[unit], 'support': support, 'claim': ''})
    units.sort(key=lambda u: u['first'])
    # Overlapping proposals (interleaved sibling units) cannot both be files: drop the weaker.
    kept = []
    for unit in units:
        if kept and unit['first'] <= kept[-1]['last']:
            if (unit['support'], unit['paired']) > (kept[-1]['support'], kept[-1]['paired']):
                kept[-1] = unit
            continue
        kept.append(unit)
    return kept


def apply_claims(target, units, report):
    for row in target.claims:
        start, end = int(row['start'], 16), int(row['end'], 16)
        first, last = target.index(start), target.index(end) - 1
        if first > last or target.start[first] != start or target.end[last] != end:
            report.append('claim %s %s-%s does not cover whole functions; skipped' % (row['subject'], row['start'], row['end']))
            continue
        pinned = row['start_boundary'] == 'exact' and row['end_boundary'] == 'exact'
        overlap = [u for u in units if u['first'] <= last and first <= u['last']]
        if not pinned and any(u['first'] < first or u['last'] > last for u in overlap):
            report.append('claim %s takes functions from a proposed unit; skipped' % row['subject'])
            continue
        for unit in overlap:
            units.remove(unit)
        units.append({'unit': None, 'file': row['subject'], 'first': first, 'last': last, 'paired': 0,
                      'functions': last - first + 1, 'sibling_functions': 0, 'support': 0,
                      'claim': 'exact' if pinned else 'provisional'})
    units.sort(key=lambda u: u['first'])


# ------------------------------------------------------------------ edges

def crossing(references, left, cut, right):
    """(data items, calls) shared across a cut between target index ranges [left, cut) and [cut, right]."""
    if references is None:
        return (0, 0)
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
    """True when no sibling compile unit with functions lies between two proposed units."""
    if left['unit'] is None or right['unit'] is None:
        return True
    occupied = set(sibling.unit)
    return all(u not in occupied for u in range(left['unit'] + 1, right['unit']))


def linked_to(references, function, unit):
    """True when a function calls, is called by, or shares a data item with a unit's functions."""
    members = range(unit['first'], unit['last'] + 1)
    if any(c in members for c in references.calls.get(function, ())):
        return True
    if any(function in references.calls.get(m, ()) for m in members):
        return True
    items = references.data.get(function, set())
    return any(items & references.data.get(m, set()) for m in members)


def shrink(references, left, right):
    """Assign the ends of an unpaired gap to the neighbour they alone are linked to."""
    moved = False
    while left['last'] + 1 < right['first']:
        first, last = left['last'] + 1, right['first'] - 1
        if linked_to(references, first, left) and not linked_to(references, first, right):
            left['last'] = first
        elif linked_to(references, last, right) and not linked_to(references, last, left):
            right['first'] = last
        else:
            break
        moved = True
    return moved


def text_edges(target, sibling, units, paired, references):
    edges = []
    names = {i for i, (_, how) in paired.items() if how == 'name'}
    for left, right in zip(units, units[1:]):
        claimed = left['claim'] == 'exact' or right['claim'] == 'exact'
        gap = right['first'] - left['last'] - 1
        if not neighbours(sibling, left, right) and not claimed:
            # Sibling units between them are missing here: each side's end stays open.
            if references is not None:
                shrink(references, left, right)
            edges.append(edge(target, left, right, None, 'open', (None, None), 0, left['last'] + 1, right['first']))
            continue
        alignment_cut = right['first'] if gap == 0 else None
        if claimed and gap == 0:
            edges.append(edge(target, left, right, right['first'], 'claimed', (0, 0), 0))
            continue
        low, high = left['last'] + 1, right['first']
        if alignment_cut is not None:
            low, high = alignment_cut - WINDOW, alignment_cut + WINDOW

        def crosses_name(c):
            a, b = sorted((c, alignment_cut if alignment_cut is not None else c))
            return any(a <= n < b for n in names)
        candidates = [c for c in range(max(low, left['first'] + 1), min(high, right['last']) + 1)
                      if not crosses_name(c)]
        scores = {c: crossing(references, left['first'], c, right['last']) for c in candidates}
        best = min(v[0] for v in scores.values())
        tied = [c for c in candidates if scores[c][0] == best]
        if references is None:
            cut, kind = alignment_cut, 'alignment' if alignment_cut is not None else 'open'
        elif len(tied) == 1:
            cut, kind = tied[0], 'data'
        else:
            fewest = min(scores[c][1] for c in tied)
            by_calls = [c for c in tied if scores[c][1] == fewest]
            if alignment_cut in tied:
                cut, kind = alignment_cut, 'calls' if by_calls == [alignment_cut] else 'alignment'
            elif len(by_calls) == 1:
                cut, kind = by_calls[0], 'calls'
            else:
                cut, kind = None, 'open'
        if cut is None and gap > 0:
            shrink(references, left, right)
            if left['last'] + 1 == right['first']:
                cut, kind = right['first'], 'calls'
            else:
                tied = [left['last'] + 1, right['first']]
        edges.append(edge(target, left, right, cut, kind, scores.get(cut, (best, None)), len(candidates),
                          tied[0], tied[-1]))
    return edges


def edge(target, left, right, cut, kind, score, tried, low=None, high=None):
    where = target.start[cut] if cut is not None else None
    span = (target.start[low], target.start[high]) if low is not None else (where, where)
    if cut is None and low is not None and high is not None:
        # an open edge spans from the left unit's last function's end to the right unit's start
        span = (target.end[low - 1] if low > 0 else target.start[low], target.start[high])
    if cut is not None:
        left['last'] = cut - 1
        right['first'] = cut
    return {'left': left['file'], 'right': right['file'], 'address': where, 'kind': kind,
            'data': score[0], 'calls': score[1], 'tried': tried, 'low': span[0], 'high': span[1]}


def data_edges(units, references):
    """Per data section, between neighbouring units: the address range that separates the items
    only the left unit references from those only the right unit references. Uninitialised
    commons and out-of-order tables can sit away from their unit's run, so the cut is the address
    that misplaces the fewest owned items; `data` when it misplaces none, `mixed` when it misplaces
    one item, or fewer than half of the smaller side, `conflict` otherwise."""
    if references is None:
        return []
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
            owned[references.items[item][2]][n].append(item)
    rows = []
    for section, by_unit in sorted(owned.items()):
        for a in sorted(by_unit):
            b = a + 1
            if b not in by_unit:
                continue      # the next unit owns nothing here: no edge to place
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
            kind = 'data' if wrong == 0 else 'conflict' if wrong >= 2 and wrong * 2 >= min(len(left), len(right)) else 'mixed'
            rows.append({'section': SECTION_NAMES[section], 'left': units[a]['file'], 'right': units[b]['file'],
                         'low': low_item[0] + low_item[1] if low_item else None,
                         'high': high_item[0] if high_item else None, 'kind': kind, 'misplaced': wrong})
    return rows


# ---------------------------------------------------------------- run

def run(target_id, references_needed=True, calibrate=False):
    config = ROOT / 'config' / target_id
    sibling = Sibling(SIBLING)
    target = Target(config / 'evidence.tsv')
    if calibrate:
        target.claims = []
    references = References(target) if references_needed else None
    kept = anchors(target, sibling)
    paired = align(target, sibling, kept)
    units = propose_units(target, sibling, paired)
    report = []
    apply_claims(target, units, report)
    edges = text_edges(target, sibling, units, paired, references)
    datas = data_edges(units, references)
    return {'sibling': sibling, 'target': target, 'anchors': kept, 'paired': paired, 'units': units,
            'edges': edges, 'data_edges': datas, 'report': report}


def hexa(value):
    return '-' if value is None else '0x%08X' % value


def tables(result, target_id):
    sibling, target = result['sibling'], result['target']
    header = ('# tools/boundaries.py sha256 %s\n# sibling %s sha256 %s\n'
              % (digest(__file__), SIBLING.relative_to(ROOT).as_posix(), digest(SIBLING)))
    units = [header + '# Proposed units; a proposal, not an established extent (evidence: one unit-anchor row per run).\n'
             'start\tend\tsibling_file\tfunctions\tpaired\tsibling_functions\tanchors\tclaim']
    for unit in result['units']:
        units.append('\t'.join([hexa(target.start[unit['first']]), hexa(target.end[unit['last']]), unit['file'],
                                str(unit['last'] - unit['first'] + 1), str(unit['paired']),
                                str(unit['sibling_functions']), str(unit['support']), unit['claim'] or '-']))
    edges = [header + '# Text edges (section .text) then data edges. class: data, calls, alignment, claimed, open; data rows: data, mixed, conflict, with misplaced items in crossing_data.\n'
             'section\taddress\tlow\thigh\tclass\tcrossing_data\tcrossing_calls\tleft\tright']
    for e in result['edges']:
        edges.append('\t'.join(['.text', hexa(e['address']), hexa(e['low']), hexa(e['high']), e['kind'],
                                '-' if e['data'] is None else str(e['data']),
                                '-' if e['calls'] is None else str(e['calls']), e['left'], e['right']]))
    for e in result['data_edges']:
        edges.append('\t'.join([e['section'], '-', hexa(e['low']), hexa(e['high']), e['kind'],
                                str(e['misplaced']), '-', e['left'], e['right']]))
    names = [header + '# Target functions paired with a sibling function (how: name, size, gap).\n'
             'address\tsize\tlabel\tsibling_name\thow\tsibling_file']
    for i in sorted(result['paired']):
        j, how = result['paired'][i]
        names.append('\t'.join([hexa(target.start[i]), str(target.size[i]), target.label[i], sibling.name[j], how,
                                sibling.unit_files[sibling.unit[j]] or '-']))
    return {'units.tsv': '\n'.join(units) + '\n', 'edges.tsv': '\n'.join(edges) + '\n',
            'names.tsv': '\n'.join(names) + '\n'}


def established(target_id):
    """Units whose extent a reviewed row establishes: `unit` rows with both edges exact."""
    rows = csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t')
    return sorted((int(r['start'], 16), int(r['end'], 16)) for r in rows
                  if r['kind'] == 'unit' and r['start_boundary'] == 'exact' and r['end_boundary'] == 'exact')


def calibrate(target_id):
    """Known-answer test (wiki): leave out the claims and the name anchors inside the established
    units, run, and count how many of their edges come back, by class, and how many proposed edges
    fall inside an established unit (wrong)."""
    sibling = Sibling(SIBLING)
    target = Target(ROOT / 'config' / target_id / 'evidence.tsv')
    target.claims = []
    units = established(target_id)
    held = set()
    for start, end in units:
        held.update(range(target.index(start), target.index(end)))
    names = {i: j for i, j in name_anchors(target, sibling).items() if i not in held}
    sizes = size_anchors(target, sibling)
    candidates = [(i, j, 'name') for i, j in names.items()]
    candidates += [(i, j, 'size') for i, j in sizes.items() if i not in names]
    kept, seen = [], set()
    for i, j, kind in chain(candidates):
        if i not in seen:
            seen.add(i)
            kept.append((i, j, kind))
    paired = align(target, sibling, kept)
    proposed = propose_units(target, sibling, paired)
    edges = text_edges(target, sibling, proposed, paired, References(target))
    if not proposed:
        print('no units proposed')
        return 1
    low, high = target.start[proposed[0]['first']], target.end[proposed[-1]['last']]
    known = {e for u in units for e in u if low < e < high}
    found = Counter()
    wrong = []
    for e in edges:
        if e['address'] is None:
            found['open'] += 1 if any(e['low'] <= k <= e['high'] for k in known) else 0
            continue
        if e['address'] in known:
            found[e['kind']] += 1
        elif any(s < e['address'] < t for s, t in units):
            wrong.append((e['address'], e['kind'], e['left'], e['right']))
    print('established units (both edges exact): %d; their edges inside the aligned span: %d' % (len(units), len(known)))
    print('reproduced exactly, by class: %s' % dict(found))
    print('proposed edges inside an established unit (wrong): %d' % len(wrong))
    for address, kind, left, right in wrong:
        print('  %s %s %s -> %s' % (hexa(address), kind, left, right))
    rows = list(csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t'))
    current = [(int(r['start'], 16), int(r['end'], 16)) for r in rows if r['kind'] == 'unit']
    edges_now = {e for u in current for e in u if low < e < high}
    placed = [e for e in edges if e['address'] is not None]
    agree = Counter(e['kind'] for e in placed if e['address'] in edges_now)
    split = Counter(e['kind'] for e in placed if e['address'] not in edges_now)
    print('against every current unit row (mostly provisional, not a known answer): '
          'agree %s, would split a current unit %s' % (dict(agree), dict(split)))
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    parser.add_argument('--target', default='GN7E69-rev0')
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true', help='update the committed tables')
    mode.add_argument('--check', action='store_true', help='fail when the committed tables differ')
    mode.add_argument('--calibrate', action='store_true', help='known-answer test against exact unit edges')
    args = parser.parse_args(argv)
    if not (ANALYSIS / 'splits.txt').exists():
        sys.exit('boundaries: build/analysis/splits.txt missing; run python3 build.py first')
    if args.calibrate:
        return calibrate(args.target)
    result = run(args.target)
    for line in result['report']:
        print('boundaries: ' + line, file=sys.stderr)
    produced = tables(result, args.target)
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
    kinds = Counter(e['kind'] for e in result['edges'])
    print('anchors %d (%s), paired %d, units %d, text edges %d %s, data edges %d %s' % (
        len(result['anchors']), dict(Counter(k for _, _, k in result['anchors'])), len(result['paired']),
        len(result['units']), len(result['edges']), dict(kinds), len(result['data_edges']),
        dict(Counter(e['kind'] for e in result['data_edges']))))
    return 0


if __name__ == '__main__':
    sys.exit(main())
