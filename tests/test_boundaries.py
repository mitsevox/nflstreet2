from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import boundaries


class FakeSibling:
    """Two compile units: A holds sizes 16..52, B holds 60..96 (all distinct)."""

    def __init__(self, sizes, units, files):
        self.size = sizes
        self.unit = units
        self.unit_files = files
        self.name = ['s%d' % i for i in range(len(sizes))]
        self.address = [0x1000 + 0x100 * i for i in range(len(sizes))]
        self.unmarked = set()
        self.unique_name = {n: i for i, n in enumerate(self.name)}
        self.bounds = [0x1000, 0x1000 + 0x100 * units.count(0), 0x1000 + 0x100 * len(sizes)]

    def unit_bytes(self, unit):
        return sum(s for s, u in zip(self.size, self.unit) if u == unit)


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
        self.items = []


class BoundaryTests(unittest.TestCase):
    def setUp(self):
        a = [16, 20, 24, 28, 32, 36, 40, 44, 48, 52]
        b = [60, 64, 68, 72, 76, 80, 84, 88, 92, 96]
        self.sibling = FakeSibling(a + b, [0] * 10 + [1] * 10, ['a.c', 'b.c'])
        self.target = FakeTarget(a + b)

    def test_size_anchors_are_mutual_unique(self):
        pairs = boundaries.size_anchors(self.target, self.sibling)
        self.assertEqual(pairs, {i: i for i in range(20)})
        # A repeated run in the target is not unique and gives no anchor.
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
        kept = [(0, 0, 'size'), (5, 5, 'size')]
        paired = boundaries.align(self.target, self.sibling, kept)
        self.assertEqual(sorted(paired), [0, 1, 2, 3, 4, 5])
        self.assertEqual(paired[3], (3, 'gap'))

    def test_units_and_alignment_edge_without_references(self):
        kept = boundaries.anchors(self.target, self.sibling)
        paired = boundaries.align(self.target, self.sibling, kept)
        units = boundaries.propose_units(self.target, self.sibling, paired)
        self.assertEqual([(u['file'], u['first'], u['last']) for u in units], [('a.c', 0, 9), ('b.c', 10, 19)])
        edges = boundaries.text_edges(self.target, self.sibling, units, paired, None)
        self.assertEqual(len(edges), 1)
        self.assertEqual(edges[0]['kind'], 'alignment')
        self.assertEqual(edges[0]['address'], self.target.start[10])

    def test_data_moves_the_cut(self):
        kept = boundaries.anchors(self.target, self.sibling)
        paired = boundaries.align(self.target, self.sibling, kept)
        units = boundaries.propose_units(self.target, self.sibling, paired)
        # Functions 0..11 share item 1 and 12.. share item 2, so the only cut with no shared item
        # inside the window is at 12, two functions right of the alignment's cut at 10.
        data = {i: {1} for i in range(12)}
        data.update({i: {2} for i in range(12, 20)})
        edges = boundaries.text_edges(self.target, self.sibling, units, paired, FakeReferences(data))
        self.assertEqual((edges[0]['kind'], edges[0]['address']), ('data', self.target.start[12]))

    def test_size_rule_rejects_a_sparse_unit(self):
        sizes = self.target.size[:10] + [1000] * 20 + self.target.size[10:]
        target = FakeTarget(sizes)
        kept = boundaries.anchors(target, self.sibling)
        paired = boundaries.align(target, self.sibling, kept)
        units = boundaries.propose_units(target, self.sibling, paired)
        self.assertEqual([u['file'] for u in units], ['a.c', 'b.c'])
        self.assertEqual(units[1]['first'], 30)

    def test_shrink_assigns_gap_by_calls(self):
        left = {'first': 0, 'last': 3}
        right = {'first': 6, 'last': 9}
        references = FakeReferences(calls={4: {1}, 5: {8}})
        self.assertTrue(boundaries.shrink(references, left, right))
        self.assertEqual((left['last'], right['first']), (4, 5))

    def test_neighbours_need_no_occupied_unit_between(self):
        sibling = FakeSibling([4, 8, 12], [0, 1, 2], ['a', 'b', 'c'])
        self.assertTrue(boundaries.neighbours(sibling, {'unit': 0}, {'unit': 1}))
        self.assertFalse(boundaries.neighbours(sibling, {'unit': 0}, {'unit': 2}))


if __name__ == '__main__':
    unittest.main()
