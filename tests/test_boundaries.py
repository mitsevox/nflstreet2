from collections import Counter, defaultdict
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import boundaries


class FakeSibling:
    """Compile units given as lists of function sizes."""

    def __init__(self, units, files):
        self.size, self.unit = [], []
        for n, sizes in enumerate(units):
            self.size += sizes
            self.unit += [n] * len(sizes)
        self.unit_files = files
        self.name = ['s%d' % i for i in range(len(self.size))]
        self.unmarked = set()
        self.unique_name = {n: i for i, n in enumerate(self.name)}
        self.counts = Counter(self.unit)
        self.bytes = Counter()
        for unit, size in zip(self.unit, self.size):
            self.bytes[unit] += size
        self.other_files = defaultdict(list)

    def file(self, unit):
        return self.unit_files[unit] if unit >= 0 else '-'


class FakeTarget:
    def __init__(self, sizes, labels=None):
        self.size = sizes
        self.start, address = [], 0x8000
        for size in sizes:
            self.start.append(address)
            address += size
        self.end = [s + z for s, z in zip(self.start, sizes)]
        self.label = labels or ['fn_%X' % s for s in self.start]
        self.positional = set()
        self.claims = []

    def index(self, address):
        import bisect
        return bisect.bisect_left(self.start, address)


class FakeReferences:
    def __init__(self, data=None, calls=None):
        self.data = data or {}
        self.calls = calls or {}
        self.callers = defaultdict(set)
        for caller, callees in self.calls.items():
            for callee in callees:
                self.callers[callee].add(caller)
        self.items = []
        self.region = []


A = [16, 20, 24, 28, 32, 36, 40, 44, 48, 52]
B = [60, 64, 68, 72, 76, 80, 84, 88, 92, 96]


class BoundaryTests(unittest.TestCase):
    def setUp(self):
        self.sibling = FakeSibling([A, B], ['a.c', 'b.c'])
        self.target = FakeTarget(A + B)

    def proposal(self, target, references=None):
        kept = boundaries.anchors(target, self.sibling)
        paired = boundaries.align(target, self.sibling, kept)
        units, edges = boundaries.settle(target, self.sibling, paired, references or FakeReferences(), [])
        return paired, units, edges

    def test_size_anchors_are_mutual_unique(self):
        pairs = boundaries.size_anchors(self.target, self.sibling)
        self.assertEqual(pairs, {i: i for i in range(20)})
        doubled = FakeTarget(self.target.size + self.target.size[:4])
        self.assertNotIn(0, boundaries.size_anchors(doubled, self.sibling))

    def test_chain_prefers_names_over_sizes(self):
        kept = boundaries.chain([(0, 5, 'size'), (1, 6, 'size'), (2, 0, 'name')])
        self.assertEqual(kept, [(2, 0, 'name')])

    def test_chain_increases_in_both(self):
        kept = boundaries.chain([(0, 0, 'size'), (1, 3, 'size'), (2, 1, 'size'), (3, 2, 'size')])
        self.assertEqual([k[:2] for k in kept], [(0, 0), (2, 1), (3, 2)])

    def test_common_subsequence(self):
        self.assertEqual(boundaries.common_subsequence([4, 8, 12], [4, 9, 12]), [(0, 0), (2, 2)])

    def test_gap_alignment_pairs_equal_sizes(self):
        paired = boundaries.align(self.target, self.sibling, [(0, 0, 'size'), (5, 5, 'size')])
        self.assertEqual(sorted(paired), [0, 1, 2, 3, 4, 5])
        self.assertEqual(paired[3], (3, 'gap'))

    def test_adjacent_units_keep_the_alignment_cut(self):
        _, units, edges = self.proposal(self.target)
        self.assertEqual([(u['file'], u['first'], u['last']) for u in units], [('a.c', 0, 9), ('b.c', 10, 19)])
        self.assertEqual((edges[0]['kind'], edges[0]['address']), ('alignment', self.target.start[10]))

    def test_data_confirms_but_never_moves_an_aligned_cut(self):
        # Every cut but 12 shares item 1: data prefers 12, yet the paired functions stay with
        # their sibling unit, so the edge stays at 10 and is labelled `alignment`.
        data = {i: {1} for i in range(12)}
        data.update({i: {2} for i in range(12, 20)})
        _, _, edges = self.proposal(self.target, FakeReferences(data))
        self.assertEqual((edges[0]['kind'], edges[0]['address']), ('alignment', self.target.start[10]))
        # With item 1 used only before 10, the aligned cut is the unique data minimum.
        data = {i: {1} for i in range(10)}
        data.update({i: {2} for i in range(10, 20)})
        _, _, edges = self.proposal(self.target, FakeReferences(data))
        self.assertEqual((edges[0]['kind'], edges[0]['address']), ('data', self.target.start[10]))

    def test_unpaired_gap_is_cut_by_data(self):
        target = FakeTarget(A + [8, 12] + B)
        data = {i: {1} for i in range(11)}
        data.update({i: {2} for i in range(11, 22)})
        _, units, edges = self.proposal(target, FakeReferences(data))
        self.assertEqual((edges[0]['kind'], edges[0]['address']), ('data', target.start[11]))
        self.assertEqual((units[0]['last'], units[1]['first']), (10, 11))

    def test_size_rule_drops_a_unit_padded_by_unpaired_functions(self):
        target = FakeTarget(A + [1000] * 20 + B)
        _, units, _ = self.proposal(target)
        self.assertEqual([u['file'] for u in units], ['a.c', 'b.c'])
        self.assertEqual(units[1]['first'], 30)
        rule = boundaries.size_rule
        members = [(i, 'size') for i in range(10)]
        self.assertFalse(rule(target, self.sibling, {'unit': 0, 'first': 0, 'last': 29}, members))

    def test_shrink_assigns_gap_by_calls(self):
        left = {'first': 0, 'last': 3, 'claim': ''}
        right = {'first': 6, 'last': 9, 'claim': ''}
        self.assertEqual(boundaries.shrink(FakeReferences(calls={4: {1}, 5: {8}}), left, right), {'calls'})
        self.assertEqual((left['last'], right['first']), (4, 5))

    def test_shrink_never_grows_a_pinned_unit(self):
        left = {'first': 0, 'last': 3, 'claim': 'exact'}
        right = {'first': 6, 'last': 9, 'claim': ''}
        boundaries.shrink(FakeReferences(calls={4: {1}, 5: {1}}), left, right)
        self.assertEqual((left['last'], right['first']), (3, 6))

    def test_neighbours_need_no_occupied_unit_between(self):
        sibling = FakeSibling([[4], [8], [12]], ['a', 'b', 'c'])
        self.assertTrue(boundaries.neighbours(sibling, {'unit': 0}, {'unit': 1}))
        self.assertFalse(boundaries.neighbours(sibling, {'unit': 0}, {'unit': 2}))

    def claim(self, start, end, edges=('exact', 'exact')):
        return {'kind': 'unit', 'start': '0x%08X' % start, 'end': '0x%08X' % end, 'subject': 'claimed.c',
                'start_boundary': edges[0], 'end_boundary': edges[1], 'evidence': boundaries.CLAIM_PHRASE + ' x'}

    def test_pinned_claim_replaces_and_holds(self):
        self.target.claims = [self.claim(self.target.start[0], self.target.end[11])]
        _, units, edges = self.proposal(self.target)
        self.assertEqual([(u['file'], u['first'], u['last']) for u in units][0], ('claimed.c', 0, 11))
        self.assertEqual(units[0]['claim'], 'exact')

    def test_pinned_claim_must_cover_whole_functions(self):
        self.target.claims = [self.claim(self.target.start[0] + 4, self.target.end[3])]
        with self.assertRaises(SystemExit):
            self.proposal(self.target)

    def test_provisional_claim_takes_nothing_from_a_proposal(self):
        self.target.claims = [self.claim(self.target.start[0], self.target.end[3], ('provisional', 'provisional'))]
        report = []
        kept = boundaries.anchors(self.target, self.sibling)
        paired = boundaries.align(self.target, self.sibling, kept)
        units, _ = boundaries.settle(self.target, self.sibling, paired, FakeReferences(), report)
        self.assertEqual([u['file'] for u in units], ['a.c', 'b.c'])
        self.assertTrue(report and 'skipped' in report[0])

    def test_data_edges_per_region(self):
        references = FakeReferences()
        # items: two regions of one section; each unit owns one item per region in order.
        references.items = [(0x100, 4, '.bss', 'a', False), (0x104, 4, '.bss', 'b', False),
                            (0x900, 4, '.bss', 'c', False), (0x904, 4, '.bss', 'd', False)]
        references.region = ['low', 'low', 'high', 'high']
        references.data = {0: {0, 2}, 1: {1, 3}}
        units = [{'unit': 0, 'file': 'a.c', 'first': 0, 'last': 0, 'claim': ''},
                 {'unit': 1, 'file': 'b.c', 'first': 1, 'last': 1, 'claim': ''}]
        edges = [{'left': units[0], 'right': units[1], 'kind': 'alignment', 'address': 1}]
        rows = boundaries.data_edges(units, edges, references)
        self.assertEqual([(r['kind'], r['misplaced']) for r in rows], [('thin', 0), ('thin', 0)])

    def test_sibling_starts_from_markers_and_file_rows(self):
        rows = [{'Address': '0x00000000', 'Size': '0', 'Type': '4', 'Name': 'one.c'},
                {'Address': '0x80001000', 'Size': '0', 'Type': '0', 'Name': 'gcc2_compiled.'},
                {'Address': '0x80001000', 'Size': '16', 'Type': '2', 'Name': 'f'},
                {'Address': '0x00000000', 'Size': '0', 'Type': '4', 'Name': 'two.c'},
                {'Address': '0x80001040', 'Size': '16', 'Type': '2', 'Name': '_g'},
                {'Address': '0x00000000', 'Size': '0', 'Type': '4', 'Name': 'three.c'},
                {'Address': '0x80002000', 'Size': '0', 'Type': '0', 'Name': 'gcc2_compiled.'}]
        self.assertEqual(boundaries.sibling_unit_starts(rows),
                         {0x80001000: 'one.c', 0x80001040: 'two.c', 0x80002000: 'three.c'})

    def test_strings_are_not_data_items(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'symbols.txt'
            path.write_text('lbl_1 = .data3:0x80300000; // type:object size:0x8 data:string\n'
                            'lbl_2 = .data3:0x80300008; // type:object size:0x4\n')
            _, items = boundaries.read_symbols(path)
        self.assertEqual([i[4] for i in items], [True, False])


if __name__ == '__main__':
    unittest.main()
