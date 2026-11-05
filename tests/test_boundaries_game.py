from collections import defaultdict
from pathlib import Path
import bisect
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import boundaries_game as game


class FakeTarget:
    def __init__(self, count, base=0x80000000, size=0x10):
        self.start = [base + i * size for i in range(count)]
        self.end = [s + size for s in self.start]
        self.index_of = set(self.start)

    def index(self, address):
        return bisect.bisect_left(self.start, address)


class FakeDol:
    def __init__(self, base, data):
        self.base, self.data = base, data

    def read(self, address, size):
        offset = address - self.base
        if offset < 0 or offset + size > len(self.data):
            return None
        return self.data[offset:offset + size]

    def word(self, address):
        raw = self.read(address, 4)
        return None if raw is None else struct.unpack('>I', raw)[0]


class FakeOwners:
    def __init__(self, items, users=None, calls=None, sections=None):
        self.items = items
        self.starts = [i[0] for i in items]
        self.users = defaultdict(set, users or {})
        self.calls = defaultdict(set, calls or {})
        self.sections = sections or {}

    def region(self, section):
        return self.sections[section]


class OrderTies(unittest.TestCase):
    def test_reversed_pair_ties_the_cuts_between_its_owners(self):
        # Function 3 owns the item at 0x100, function 1 the one above it at 0x110: cuts 2 and 3 tied.
        ties = game.order_ties({'.rodata': [(3, 0x100), (1, 0x110)]})
        self.assertEqual(sorted(ties), [2, 3])

    def test_ordered_items_tie_nothing(self):
        self.assertEqual(game.order_ties({'.rodata': [(1, 0x100), (3, 0x110)]}), {})

    def test_window_and_span_limit_the_pairs(self):
        self.assertEqual(game.order_ties({'s': [(40, 0x100), (1, 0x110)]}, window=16), {})
        self.assertEqual(game.order_ties({'s': [(3, 0x100), (1, 0x900)]}, span=0x400), {})

    def test_sections_are_compared_separately(self):
        self.assertEqual(game.order_ties({'a': [(3, 0x100)], 'b': [(1, 0x110)]}), {})


class StaticInit(unittest.TestCase):
    def setUp(self):
        self.target = FakeTarget(6)
        self.ctors = 0x90000000

    def run_edges(self, calls):
        dol = FakeDol(self.ctors, struct.pack('>II', self.target.start[2], 0))
        owners = FakeOwners([], calls=calls, sections={'.data2': (self.ctors, self.ctors + 8)})
        return game.static_init_edges(self.target, dol, owners, self.target.start[0], self.target.end[-1])

    def test_file_ends_after_the_ctors_function(self):
        self.assertEqual(self.run_edges({2: {0}, 3: {1}}), {3: 'static-init'})

    def test_destructor_twin_stays_with_it(self):
        self.assertEqual(self.run_edges({2: {0}, 3: {0}}), {4: 'static-init'})


class StringCopies(unittest.TestCase):
    def setUp(self):
        self.target = FakeTarget(10)
        self.low, self.high = self.target.start[0], self.target.end[-1]

    def row(self, address, users, section='.rodata', at_start=True, text='t1'):
        return {'address': address, 'section': section, 'at_start': at_start, 'text': text,
                'users': [self.target.start[u] for u in users], 'unmapped': 0}

    def gc(self, mapping):
        loaded = defaultdict(dict)
        for user, copy in mapping.items():
            loaded[user]['t1'] = {copy}
        return loaded

    def test_one_copy_ties_its_users_and_two_copies_separate(self):
        rows = [self.row(0x100, [1, 3]), self.row(0x200, [6])]
        ties, separators, dropped = game.string_copies(self.target, rows, {}, self.low, self.high,
                                                       self.gc({1: 0xA, 3: 0xA, 6: 0xB}))
        self.assertEqual((ties, separators, dropped), ([(1, 3, 't1')], [(4, 6)], set()))

    def test_gc_disagreement_drops_the_text(self):
        rows = [self.row(0x100, [1, 3])]
        _, _, dropped = game.string_copies(self.target, rows, {}, self.low, self.high, self.gc({1: 0xA, 3: 0xB}))
        self.assertEqual(dropped, {'t1'})

    def test_named_arrays_and_globals_drop_the_text(self):
        gc = self.gc({1: 0xA, 3: 0xA})
        for row, edges in ((self.row(0x100, [1, 3], section='.data'), {}),
                           (self.row(0x100, [1, 3], at_start=False), {}),
                           (self.row(0x100, [1, 3]), {2: 'static-init'})):
            _, _, dropped = game.string_copies(self.target, [row], edges, self.low, self.high, gc)
            self.assertEqual(dropped, {'t1'})


class CopyTiedCuts(unittest.TestCase):
    def test_narrow_copies_tie_wide_ones_need_two_texts(self):
        # One narrow copy (functions 1-3) ties cuts 2 and 3; one text over 10-40 alone ties nothing,
        # a second text over 20-30 makes cuts 21-30 tied.
        self.assertEqual(game.copy_tied_cuts([(1, 3, 'a')], window=16), {2, 3})
        self.assertEqual(game.copy_tied_cuts([(10, 40, 'a')], window=16), set())
        self.assertEqual(game.copy_tied_cuts([(10, 40, 'a'), (20, 50, 'b')], window=16), set(range(21, 41)))
        self.assertEqual(game.copy_tied_cuts([(10, 40, 'a'), (10, 40, 'a')], window=16), set())


class Combine(unittest.TestCase):
    def test_atoms_spans_and_separators(self):
        # Functions 0..9; edge at cut 5; cuts 2 and 3 tied; a separator over cuts 7-8 with cut 8 tied
        # places an edge at cut 7; a tag over cuts 1-4 holds no single free cut and stays a range.
        edges, atoms, spans, unresolved = game.combine(
            0, 10, {5: 'static-init'}, {2: {'data-order'}, 3: {'rodata-padding'}, 8: {'data-order'}},
            [(7, 8, 'strings', '-'), (1, 4, 'tag', 'X.C')], [(1, 4, 'X.C', 0)])
        self.assertEqual(edges, {5: 'static-init', 7: 'strings'})
        self.assertEqual([(a['first'], a['last'], a['end']) for a in atoms],
                         [(0, 0, 'open'), (1, 3, 'open'), (4, 4, 'static-init'), (5, 5, 'open'),
                          (6, 6, 'strings'), (7, 8, 'open'), (9, 9, 'end')])
        self.assertEqual([(s['first'], s['last'], s['start_class'], s['end_class']) for s in spans],
                         [(0, 4, 'range', 'static-init'), (5, 6, 'static-init', 'strings'), (7, 9, 'strings', 'range')])
        self.assertEqual(unresolved, [(1, 4, 'tag', 'X.C')])
        self.assertEqual(spans[0]['required'], 1)

    def test_a_tag_range_with_one_edge_names_the_file(self):
        _, _, spans, _ = game.combine(0, 6, {3: 'static-init'}, {}, [(2, 4, 'tag', 'Y.C')], [(2, 4, 'Y.C', 0)])
        self.assertEqual(spans[1]['name'], 'Y.C')


if __name__ == '__main__':
    unittest.main()
