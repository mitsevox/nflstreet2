"""Same-game mode of tools/boundaries.py: file-edge evidence for this game's own code.

    python3 tools/boundaries.py --game [--target ID]   summary, agreement checks and the current rows it contradicts

The NASCAR 2005 alignment (tools/boundaries.py) covers the EA engine libraries only: below them is
football code that no sibling with symbols shares. Here the evidence comes from this target and
from the PS2 release of the same game (SLUS_211.18: the same ProDG GCC family, nearly the same
function order (17 inversions among 7,261 mapped game functions), no string merging across files).
The run covers GAME_RANGE and classifies each cut between two consecutive functions. Nothing here
establishes an extent: the tables are proposals, and a closing PR decides its own file's edges.

- **edge**, evidence that a file ends at the cut:
  - `static-init`: a function listed in the .ctors/.dtors lists (a C++ file's static initialiser
    or finaliser) is the last function of its file, or the second last when the next function
    calls the same callees (the twin GCC emits beside it). Support from outside this target: in
    NASCAR 2005, whose symbols name every file, all 172 `_GLOBAL_.I.` functions are followed in
    their file only by other `_GLOBAL_` functions. On this target the 71 edges are current unit
    edges, but those rows cite the same signal, so that agreement is not independent.
  - `tag`: a file-name string such as "ASSIGN.C" that no function loads, at the head of a file's
    .data, names the file that starts between the highest function owning .data before it and the
    lowest owning .data after it. When that range holds exactly one untied cut, the edge is that
    cut; otherwise the range is reported with the name.
  - `strings`: two PS2 copies of the same literal sit in two different files, so some cut between
    their users is an edge; when exactly one untied cut lies between two such users, it is the edge.
- **tied**, evidence that the functions on both sides are in one file:
  - `string-copy`: GC functions whose PS2 counterparts load the same PS2 copy of a literal. A copy
    counts only when the reference is to the start of the string, the copy is in .rodata or .sdata
    (a .data string is a named array), its users do not straddle a `static-init` edge, and the GC
    build agrees: every user loads one GC .rodata copy of the same text, and no user of another PS2
    copy loads that GC copy (this build keeps a copy per file too). Every copy of a text that fails
    one test is dropped. Neither build tells a literal from a named `const char[]` used by several
    files, so a copy whose users lie more than WINDOW functions apart ties a cut only where the
    copies of at least two different texts cover it.
  - `data-order`: within a file the linker keeps its data together, so a data item owned by a
    function left of the cut that sits above an item owned by a function right of it, in the same
    section, ties the cut. An item is owned when exactly one function references it; the pair must
    be owned by functions at most WINDOW apart and lie at most SPAN bytes apart (an item defined in
    another file but used by one function here otherwise gives false ties: without the window
    every static-init edge is tied). .sdata2 is a merged pool and is left out.
  - `ps2-data-order`: the same test on the PS2 side, on the whole literals the PS2 code loads.
- **open**, when neither.

Not used: .rodata (or any section) alignment. ProDG aligns a file's .rodata to 4 or 8 by its
contents (102 of 186 compiled game objects use 4), so an item 4 past an 8-byte boundary can start a
file.

`--game` prints, besides the summary, how many tie pairs join two different linked objects of the
current build and how many tied cuts are current unit edges. These are agreement checks against
rows that are themselves mostly provisional, not a known answer; the only `exact` unit edges in the
game range are listed with their state.

An **atom** is a maximal run of functions joined by tied cuts. A **span** is a run of atoms
between two edges (or the ends of GAME_RANGE). The class hints are reported, never used to decide:
a GCC vtable (two zero words, then 8-byte entries ending in a function pointer) whose methods
appear in no other vtable groups those methods; the span from the first to the last is one class's
code, usually one file in Tiburon's code, but a class can be split over files.

Outputs, config/<target>/boundaries/: game_spans.tsv, game_edges.tsv and game_atoms.tsv
(committed, checked for drift like the engine tables). Inputs: evidence.tsv (function extents),
the analysis python3 build.py writes to build/analysis/, the original main.dol (for .ctors,
vtables and tag strings) and references/NFL Street 2/SLUS-21118/ps2-strings.tsv
(tools/sibling_tables.py ps2-strings, from the private SLUS_211.18 and the GC-to-PS2 map; CI
cannot regenerate it, so it is refreshed by hand when the map is)."""
import bisect
import csv
import hashlib
import re
import struct
from collections import Counter, defaultdict
from pathlib import Path

import boundaries

ROOT = boundaries.ROOT
PS2_STRINGS = ROOT / 'references/NFL Street 2/SLUS-21118/ps2-strings.tsv'
# From the start of text segment 1 (unit row 0x800034A0) to the start of the libsn runtime (unit
# row 0x801AA640); the engine libraries after it are tools/boundaries.py's NASCAR alignment.
GAME_RANGE = {'GN7E69-rev0': (0x800034A0, 0x801AA640)}
WINDOW = 16        # functions between the owners of a data-order pair
SPAN = 0x400       # bytes between the two items of a data-order pair
TAG = re.compile(rb'[A-Z][A-Z0-9_]*\.(?:C|CPP)\x00')
OUTPUT_TABLES = ('game_spans.tsv', 'game_edges.tsv', 'game_atoms.tsv')


class Dol:
    def __init__(self, data):
        self.segments = []
        self.data = data
        for i in range(18):
            offset, address, size = (struct.unpack_from('>I', data, base + i * 4)[0] for base in (0, 0x48, 0x90))
            if size:
                self.segments.append((address, size, offset))

    def read(self, address, size):
        for start, length, offset in self.segments:
            if start <= address and address + size <= start + length:
                return self.data[offset + address - start:offset + address - start + size]
        return None

    def word(self, address):
        raw = self.read(address, 4)
        return None if raw is None else struct.unpack('>I', raw)[0]


class Owners:
    """Data items (strings included, .sdata2 left out) and the functions that reference each."""

    def __init__(self, target, analysis=boundaries.ANALYSIS):
        symbol_address, items = boundaries.read_symbols(analysis / 'symbols.txt')
        self.items = [i for i in items if i[2] in boundaries.SECTION_NAMES and i[2] not in boundaries.POOLED]
        self.starts = [i[0] for i in self.items]
        self.sections = defaultdict(list)    # section -> (start, end) regions
        self.users = defaultdict(set)
        self.calls = defaultdict(set)
        splits = boundaries.read_splits(analysis / 'splits.txt')
        for path, sections in splits.items():
            for section, extent in sections.items():
                self.sections[section].append(extent)
            obj = analysis / 'split/obj' / Path(path).with_suffix('.o')
            if not obj.exists():
                raise SystemExit('boundaries: split object %s missing; rebuild with python3 build.py' % obj)
            starts = {s: r[0] for s, r in sections.items()}
            for source, destination in boundaries.elf_relocations(obj, starts, symbol_address):
                caller = bisect.bisect_right(target.start, source) - 1
                if caller < 0 or source >= target.end[caller]:
                    continue
                callee = bisect.bisect_right(target.start, destination) - 1
                if callee >= 0 and destination < target.end[callee]:
                    if callee != caller:
                        self.calls[caller].add(callee)
                    continue
                k = bisect.bisect_right(self.starts, destination) - 1
                if k >= 0 and destination < self.items[k][0] + max(self.items[k][1], 1):
                    self.users[k].add(caller)

    def owned(self):
        """{item index: owner} for items exactly one function references."""
        return {k: next(iter(u)) for k, u in self.users.items() if len(u) == 1}

    def region(self, section):
        return min(s for s, _ in self.sections[section]), max(e for _, e in self.sections[section])


# ------------------------------------------------------------------- edges

def static_init_edges(target, dol, owners, low, high):
    """{cut: 'static-init'}: the cut after each .ctors function (after its destructor twin when
    the next function calls the same callees)."""
    start, end = owners.region('.data2')
    edges = {}
    for address in range(start, end, 4):
        value = dol.word(address)
        i = target.index(value) if value else len(target.start)
        if i >= len(target.start) or target.start[i] != value or not low <= value < high:
            continue
        cut = i + 1
        if cut < len(target.start) and owners.calls.get(cut) and owners.calls.get(cut) == owners.calls.get(i):
            cut += 1
        edges[cut] = 'static-init'
    return edges


def tag_ranges(target, dol, owners, owned):
    """[(first cut, last cut, name, tag address)]: unloaded file-name strings in .data/.sdata (not
    preceded by a printable byte) and the cut range from after the highest function owning one of
    the eight owned items of that section starting before the tag to the lowest owning one of the
    eight from it on. The analysis may size the item before the tag over it, so items are taken by
    start address."""
    loaded = {owners.items[k][0] for k in owners.users}
    found = []
    for section in ('.data4', '.data5'):
        start, end = owners.region(section)
        blob = dol.read(start, end - start) or b''
        owned_here = sorted((owners.items[k][0], owners.items[k][1], owner) for k, owner in owned.items()
                            if owners.items[k][2] == section)
        addresses = [a for a, _, _ in owned_here]
        for match in TAG.finditer(blob):
            tag = start + match.start()
            previous = blob[match.start() - 1:match.start()]
            if (previous and 32 <= previous[0] < 127) or tag in loaded:
                continue
            j = bisect.bisect_left(addresses, tag)
            before = [o for _, _, o in owned_here[max(0, j - 8):j]]
            after = [o for _, _, o in owned_here[j:j + 8]]
            if before and after and max(before) < min(after):
                found.append((max(before) + 1, min(after), match.group()[:-1].decode(), tag))
    return found


# -------------------------------------------------------------------- ties

def read_ps2_strings(path=PS2_STRINGS):
    rows = []
    for line in path.read_text().splitlines():
        if line.startswith('#') or line.startswith('ps2_address'):
            continue
        address, section, at_start, text, users, unmapped = line.split('\t')
        rows.append({'address': int(address, 16), 'section': section, 'at_start': at_start == '1',
                     'text': text, 'users': [int(u, 16) for u in users.split(',')], 'unmapped': int(unmapped)})
    return rows


def gc_string_copies(owners, dol):
    """{function: {text hash: {GC string item address}}}: the .rodata strings each function loads
    from their first byte."""
    loaded = defaultdict(lambda: defaultdict(set))
    for k, users in owners.users.items():
        start, _, section, _, _ = owners.items[k]
        if section != '.data3':
            continue
        text = cstring(dol, start)
        if text is None or len(text) < 2:
            continue
        digest = hashlib.sha256(text.encode()).hexdigest()[:12]
        for user in users:
            loaded[user][digest].add(start)
    return loaded


def cstring(dol, address):
    out = bytearray()
    while len(out) <= 300:
        byte = dol.read(address + len(out), 1)
        if byte is None or not (byte[0] == 0 or 32 <= byte[0] < 127 or byte[0] in (9, 10, 13)):
            return None
        if byte[0] == 0:
            return out.decode()
        out.append(byte[0])
    return out.decode()


def string_copies(target, rows, edges, low, high, gc_copies):
    """(ties [(first function, last function, text)], separators [(first cut, last cut)], dropped texts):
    see the module docstring. A PS2 copy counts only when all its GC users load one GC .rodata copy
    of the same text, which no user of another PS2 copy loads (the GC build keeps a copy per file
    too); a text with any copy that fails is dropped."""
    copies = defaultdict(dict)
    for row in rows:
        users = sorted({target.index(u) for u in row['users'] if low <= u < high and u in target.index_of})
        if users:
            copies[row['text']][row['address']] = (row, users)
    dropped = set()
    for text, by_copy in copies.items():
        seen = {}
        for address, (row, users) in by_copy.items():
            gc = set().union(*(gc_copies.get(u, {}).get(text, set()) for u in users))
            if (not row['at_start'] or row['section'] not in ('.rodata', '.sdata') or len(gc) != 1
                    or not all(gc_copies.get(u, {}).get(text) == gc for u in users)
                    or any(users[0] < cut <= users[-1] for cut in edges)
                    or any(seen.setdefault(c, address) != address for c in gc)):
                dropped.add(text)
    ties, separators = [], []
    for text, by_copy in sorted(copies.items()):
        if text in dropped:
            continue
        for row, users in by_copy.values():
            if len(users) > 1:
                ties.append((users[0], users[-1], text))
        if len(by_copy) > 1:
            sequence = sorted((u, address) for address, (_, users) in by_copy.items() for u in users)
            for (a, copy_a), (b, copy_b) in zip(sequence, sequence[1:]):
                if copy_a != copy_b and a != b:
                    separators.append((a + 1, b))
    return ties, separators, dropped


def copy_tied_cuts(copy_ties, window=WINDOW):
    """The cuts string copies tie: copy_ties is [(first function, last function, text)]. A copy
    whose users lie at most window functions apart ties its cuts; a wider one only cuts that wide
    copies of at least two different texts cover."""
    tied, wide = set(), defaultdict(set)
    for lo, hi, text in copy_ties:
        for cut in range(lo + 1, hi + 1):
            if hi - lo <= window:
                tied.add(cut)
            else:
                wide[cut].add(text)
    return tied | {cut for cut, texts in wide.items() if len(texts) >= 2}


def order_ties(pairs, window=WINDOW, span=SPAN):
    """{cut: witnesses}: pairs is {group: [(owner, address)]}; an item above another in the same
    group whose owner is left of the other's ties every cut between the two owners."""
    witnesses = Counter()
    for owned in pairs.values():
        owned = sorted(owned, key=lambda x: x[1])
        for i, (right_owner, right_address) in enumerate(owned):
            for left_owner, left_address in owned[i + 1:]:
                if left_address - right_address > span:
                    break
                if left_owner < right_owner and right_owner - left_owner <= window:
                    for cut in range(left_owner + 1, right_owner + 1):
                        witnesses[cut] += 1
    return witnesses


def data_order(owners, owned):
    groups = defaultdict(list)
    for k, owner in owned.items():
        start, _, section, _, is_string = owners.items[k]
        groups[(section, is_string)].append((owner, start))
    return order_ties(groups)


def ps2_data_order(target, rows, low, high):
    groups = defaultdict(list)
    for row in rows:
        if len(row['users']) == 1 and row['unmapped'] == 0 and row['at_start'] and low <= row['users'][0] < high:
            groups[row['section']].append((target.index(row['users'][0]), row['address']))
    return order_ties(groups)


# ------------------------------------------------------------------- hints

def class_spans(target, dol, owners, low, high):
    """[(first function, last function, vtable address, methods)] from GCC vtables whose address
    code loads: two zero words, then entries of one word (0 or a delta/index pair) and a function
    pointer. Only methods in no other vtable count."""
    starts = set(target.start)
    loaded = {owners.items[k][0] for k in owners.users}
    tables = []
    for section in ('.data3', '.data4'):
        for address in sorted(a for a in loaded if a in range(*owners.region(section))):
            if dol.word(address) != 0 or dol.word(address + 4) != 0:
                continue
            methods, at = [], address + 8
            while True:
                head, pointer = dol.word(at), dol.word(at + 4)
                if head is None or pointer not in starts or head >> 16 not in (0, 0xFFFF):
                    break
                methods.append(target.index(pointer))
                at += 8
            if methods:
                tables.append((address, methods))
    count = Counter(m for _, methods in tables for m in set(methods))
    spans = []
    for address, methods in tables:
        own = sorted(m for m in set(methods) if count[m] == 1 and low <= target.start[m] < high)
        if len(own) >= 2:
            spans.append((own[0], own[-1], address, len(own)))
    return spans


# ----------------------------------------------------------------- combine

def combine(first, last, edges, ties, separators, tags):
    """Atoms and spans over the functions first..last-1 (indexes). edges: {cut: class}; ties:
    {cut: set of signals}; separators: [(first cut, last cut, kind, name)] that each hold an edge."""
    edges = dict(edges)
    unresolved = []
    for lo, hi, kind, name in sorted(separators):
        if any(lo <= cut <= hi for cut in edges):
            continue
        free = [cut for cut in range(lo, hi + 1) if not ties.get(cut)]
        if len(free) == 1:
            edges[free[0]] = kind
        else:
            unresolved.append((lo, hi, kind, name))
    names = {}
    for lo, hi, name, _ in tags:
        inside = [cut for cut in edges if lo <= cut <= hi]
        if len(inside) == 1:
            names[inside[0]] = name
    atoms, start = [], first
    for cut in range(first + 1, last + 1):
        if cut == last or cut in edges or not ties.get(cut):
            atoms.append({'first': start, 'last': cut - 1,
                          'signals': sorted({s for c in range(start + 1, cut) for s in ties.get(c, ())}),
                          'end': edges.get(cut, 'end' if cut == last else 'open')})
            start = cut
    spans, start = [], first
    for cut in sorted([c for c in edges if first < c < last] + [last]):
        inside = [a for a in atoms if start <= a['first'] and a['last'] < cut]
        spans.append({'first': start, 'last': cut - 1, 'start_class': 'range' if start == first else edges[start],
                      'end_class': 'range' if cut == last else edges[cut], 'name': names.get(start, '-'),
                      'atoms': len(inside), 'open': sum(1 for a in inside if a['end'] == 'open'),
                      'tied': sum(1 for c in range(start + 1, cut) if ties.get(c)),
                      'required': sum(1 for lo, hi, _, _ in unresolved if start < lo and hi < cut)})
        start = cut
    return edges, atoms, spans, unresolved


def run(target_id):
    config = ROOT / 'config' / target_id
    low, high = GAME_RANGE[target_id]
    target = boundaries.Target(config / 'evidence.tsv')
    target.index_of = set(target.start)
    dol = Dol((ROOT / 'orig' / target_id / 'sys/main.dol').read_bytes())
    owners = Owners(target)
    owned = owners.owned()
    first, last = target.index(low), target.index(high)
    edges = static_init_edges(target, dol, owners, low, high)
    rows = read_ps2_strings()
    ties = defaultdict(set)
    copy_ties, copy_separators, dropped = string_copies(target, rows, edges, low, high,
                                                         gc_string_copies(owners, dol))
    for cut in copy_tied_cuts(copy_ties):
        ties[cut].add('string-copy')
    for name, found in (('data-order', data_order(owners, owned)),
                        ('ps2-data-order', ps2_data_order(target, rows, low, high))):
        for cut in found:
            ties[cut].add(name)
    ties = {cut: signals for cut, signals in ties.items() if first < cut < last}
    tags = tag_ranges(target, dol, owners, owned)
    separators = [(lo, hi, 'strings', '-') for lo, hi in copy_separators]
    separators += [(lo, hi, 'tag', name) for lo, hi, name, _ in tags]
    conflicts = [cut for cut in edges if ties.get(cut)]
    edges, atoms, spans, unresolved = combine(first, last, edges, ties, separators, tags)
    return {'target': target, 'low': low, 'high': high, 'first': first, 'last': last, 'edges': edges,
            'ties': ties, 'atoms': atoms, 'spans': spans, 'unresolved': unresolved, 'tags': tags,
            'conflicts': conflicts, 'dropped': dropped, 'classes': class_spans(target, dol, owners, low, high)}


def tables(result):
    target = result['target']
    hexa = boundaries.hexa

    def until(last):
        # The next function's start (bytes between functions belong to the run before them).
        return target.start[last + 1] if last + 1 < result['last'] else result['high']
    header = ('# tools/boundaries_game.py sha256 %s\n# input %s sha256 %s\n'
              % (boundaries.digest(__file__), PS2_STRINGS.relative_to(ROOT).as_posix(), boundaries.digest(PS2_STRINGS)))
    classes = defaultdict(list)
    for lo, hi, address, _ in result['classes']:
        for atom in result['atoms']:
            if atom['first'] <= lo <= atom['last'] or lo <= atom['first'] <= hi:
                classes[atom['first']].append(hexa(address))
    spans = [header + '# Spans between proven edges; a proposal. start_class/end_class: static-init, tag, strings or range\n'
             '# (the end of the game range). atoms: unsplittable runs inside; open: atom ends no signal decides;\n'
             '# tied: tied cuts; required: ranges inside that must hold an edge (two copies of one PS2 literal).\n'
             'start\tend\tfunctions\tstart_class\tend_class\tname\tatoms\topen\ttied\trequired']
    for s in result['spans']:
        spans.append('\t'.join([hexa(target.start[s['first']]), hexa(until(s['last'])),
                                str(s['last'] - s['first'] + 1), s['start_class'], s['end_class'], s['name'],
                                str(s['atoms']), str(s['open']), str(s['tied']), str(s['required'])]))
    edges = [header + '# Edges: static-init, tag or strings at a cut (low = high = the edge), and range: a span of cuts\n'
             '# that must hold an edge (a tag, or two copies of one PS2 literal) where no single untied cut does.\n'
             'low\thigh\tclass\tname']
    tag_name = {(lo, hi): name for lo, hi, name, _ in result['tags']}
    rows = [(cut, cut, kind, '-') for cut, kind in result['edges'].items()]
    rows += [(lo, hi, 'range', name if kind == 'tag' else 'strings') for lo, hi, kind, name in result['unresolved']]
    for lo, hi, kind, name in sorted(rows):
        if kind != 'range':
            name = next((n for (a, b), n in tag_name.items() if a <= lo <= b), '-')
        edges.append('\t'.join([hexa(target.start[lo]), hexa(target.start[hi]), kind, name]))
    atoms = [header + '# Atoms: runs of functions joined by tied cuts (signals: what ties them). end: what decides the\n'
             '# cut after it (static-init, tag, strings, open, end). classes: vtables whose own methods reach it (hint).\n'
             'start\tend\tfunctions\tsignals\tend\tclasses']
    for a in result['atoms']:
        atoms.append('\t'.join([hexa(target.start[a['first']]), hexa(until(a['last'])),
                                str(a['last'] - a['first'] + 1), ','.join(a['signals']) or '-', a['end'],
                                ','.join(classes.get(a['first'], ())) or '-']))
    return {'game_spans.tsv': '\n'.join(spans) + '\n', 'game_edges.tsv': '\n'.join(edges) + '\n',
            'game_atoms.tsv': '\n'.join(atoms) + '\n'}


def contradicted(result, target_id):
    """Current unit-row edges (not open) inside an atom, with the signals that tie them."""
    target, ties = result['target'], result['ties']
    found = []
    rows = csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t')
    for row in rows:
        if row['kind'] != 'unit':
            continue
        for column, value in (('start_boundary', row['start']), ('end_boundary', row['end'])):
            address = int(value, 16)
            if row[column] == 'open' or address not in target.index_of:
                continue
            cut = target.index(address)
            if ties.get(cut):
                found.append((address, row['subject'], row[column], sorted(ties[cut])))
    return sorted(set((a, s, b, tuple(t)) for a, s, b, t in found))


def summary(result, target_id):
    lines = []
    cuts = result['last'] - result['first'] - 1
    tied = sum(1 for c in result['ties'])
    lines.append('game range %s-%s: %d functions, %d cuts; edges %s; tied cuts %d by %s; atoms %d; spans %d'
                 % (boundaries.hexa(result['low']), boundaries.hexa(result['high']), cuts + 1, cuts,
                    dict(Counter(result['edges'].values())), tied,
                    dict(Counter(s for v in result['ties'].values() for s in v)), len(result['atoms']),
                    len(result['spans'])))
    lines.append('tags: %s' % ', '.join('%s at %s (cuts %s-%s)' % (n, boundaries.hexa(t),
                 boundaries.hexa(result['target'].start[lo]), boundaries.hexa(result['target'].start[hi]))
                 for lo, hi, n, t in result['tags']))
    lines.append('edges also tied (conflict): %d; texts dropped from string-copy: %d; ranges that must hold an '
                 'edge but none is placed: %d; class spans (hint): %d'
                 % (len(result['conflicts']), len(result['dropped']), len(result['unresolved']), len(result['classes'])))
    rows = csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t')
    current = {int(r[c], 16) for r in rows if r['kind'] == 'unit'
               for c, b in (('start', 'start_boundary'), ('end', 'end_boundary')) if r[b] != 'open'}
    placed = Counter(kind for cut, kind in result['edges'].items()
                     if result['target'].start[cut] in current)
    lines.append('edges that are a current unit edge: %s of %s' % (dict(placed), dict(Counter(result['edges'].values()))))
    import json
    linked = set()
    for unit in json.loads((ROOT / 'config' / target_id / 'units.json').read_text())['units']:
        for section in unit['sections']:
            if section['section'] == '.text':
                linked.update((int(section['start'], 16), int(section['end'], 16)))
    target = result['target']
    at_object = Counter(signal for cut, signals in result['ties'].items() if target.start[cut] in linked
                        for signal in signals)
    lines.append('tied cuts at a linked object edge of the current build, by signal: %s (of %d linked edges '
                 'in the range)' % (dict(at_object), sum(1 for a in linked if result['low'] < a < result['high'])))
    rows = csv.DictReader(open(ROOT / 'config' / target_id / 'evidence.tsv', newline=''), delimiter='\t')
    exact = sorted({int(r[c], 16) for r in rows if r['kind'] == 'unit'
                    for c, b in (('start', 'start_boundary'), ('end', 'end_boundary')) if r[b] == 'exact'
                    and result['low'] < int(r[c], 16) < result['high']})
    states = []
    for address in exact:
        cut = target.index(address)
        state = result['edges'].get(cut) or ','.join(sorted(result['ties'].get(cut, ()))) or 'open'
        states.append('%s %s' % (boundaries.hexa(address), state))
    lines.append('exact unit edges in the range: %s' % ('; '.join(states) or 'none'))
    found = contradicted(result, target_id)
    lines.append('current unit-row edges inside an atom: %d' % len(found))
    for address, subject, boundary, signals in found:
        lines.append('  %s %s (%s): %s' % (boundaries.hexa(address), subject, boundary, ','.join(signals)))
    return lines
