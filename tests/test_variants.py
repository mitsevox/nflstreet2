"""Tests for tools/variants.py: the spec, the variant numbering, the forbidden-form check, the
worker copies, the reading of trial.py's output, and a whole run against a stand-in trial.py."""
import io
import json
import math
import os
from pathlib import Path
import sys
import shutil
import tempfile
import unittest
from contextlib import redirect_stdout
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import variants as v

SOURCE = """int f(int *p)
{
    int a;
    int b;
    a = p[0];
    b = p[1];
    return a + b;
}
"""

SPEC = """notes are ignored
%% permute loads
%% item a
    a = p[0];
%% item b
    b = p[1];
%% end
%% replace ret
%% after int f(int *p)
    return a + b;
%% with swapped
    return b + a;
%% with gone
%% end
"""

# A stand-in for tools/trial.py: IDENTICAL when the loads are in b, a order and the sum is a + b,
# a compile error for an empty return, DIFFERS otherwise.
FAKE_TRIAL = r'''import sys
from pathlib import Path
text = Path(sys.argv[1]).read_text()
if 'return' not in text:
    sys.exit('src/x.c:7: error: control reaches end')
good = text.index('b = p[1]') < text.index('a = p[0]') and 'a + b' in text
if good:
    print(sys.argv[2] + ' 0x80001000: IDENTICAL')
else:
    print(sys.argv[2] + ' 0x80001000: DIFFERS (91.50%)')
    print('    0  stwu r1, -0x10(r1)                  stwu r1, -0x10(r1)')
    print('  ! 4  lwz r4, 0x4(r3)                     lwz r4, 0x0(r3)')
print('done')
sys.exit(0 if good else 1)
'''


def write(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)
    return path


class SpecTest(unittest.TestCase):
    def setUp(self):
        self.folder = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, self.folder)
        self.spec = write(self.folder / 'spec.txt', SPEC)

    def test_text_spec(self):
        regions, _ = v.load_spec(self.spec)
        self.assertEqual([r['name'] for r in regions], ['loads', 'ret'])
        self.assertEqual(regions[0]['items'], [['a', '    a = p[0];'], ['b', '    b = p[1];']])
        self.assertEqual(regions[0]['old'], '    a = p[0];\n    b = p[1];')
        self.assertEqual(regions[1]['after'], 'int f(int *p)')
        self.assertEqual(regions[1]['options'], ['orig', 'swapped', 'gone'])
        self.assertEqual(regions[1]['with']['gone'], '')

    def test_json_spec_is_the_same(self):
        path = write(self.folder / 'spec.json', json.dumps({'regions': [
            {'permute': 'loads', 'items': [['a', '    a = p[0];'], ['b', '    b = p[1];']]},
            {'replace': 'ret', 'after': 'int f(int *p)', 'old': '    return a + b;',
             'with': {'swapped': '    return b + a;', 'gone': ''}}]}))
        self.assertEqual(v.load_spec(path)[0], v.load_spec(self.spec)[0])

    def test_bad_specs(self):
        for text in ['%% replace r\nx\n%% end\n',                     # no alternative
                     '%% permute p\n%% item a\nx\n%% end\n',           # one item
                     '%% replace r\nx\n%% with orig\ny\n%% end\n',     # reserved name
                     '%% replace r\nx\n%% with b\ny\n',                # no end
                     '%% with b\n',                                    # outside a region
                     '%% permute p\nx\n%% item a\n%% end\n',           # text before an item
                     '%% replace r\nx\n%% after y\n%% with b\nz\n%% end\n',  # late anchor
                     '%% replace r\nx\n%% with b\nz\n%% end\n%% replace r\nx\n%% with c\nz\n%% end\n']:
            with self.subTest(text=text), self.assertRaises(v.SpecError):
                v.load_spec(write(self.folder / 'bad.txt', text))

    def test_locate(self):
        regions, _ = v.load_spec(self.spec)
        v.locate(regions, SOURCE)
        self.assertEqual(SOURCE[slice(*regions[0]['span'])], regions[0]['old'])
        with self.assertRaises(v.SpecError):  # missing
            v.locate(v.load_spec(self.spec)[0], SOURCE.replace('a + b', 'a - b'))
        with self.assertRaises(v.SpecError):  # twice
            v.locate(v.load_spec(self.spec)[0], SOURCE + SOURCE.replace('int f', 'int g'))
        with self.assertRaises(v.SpecError):  # anchor twice
            v.locate(v.load_spec(self.spec)[0], SOURCE + 'int f(int *p)\n')
        overlap = write(self.folder / 'o.txt', '%% replace x\n    b = p[1];\n%% with y\n%% end\n'
                        '%% replace z\n    b = p[1];\n    return a + b;\n%% with w\n%% end\n')
        with self.assertRaises(v.SpecError):
            v.locate(v.load_spec(overlap)[0], SOURCE)

    def test_numbering(self):
        regions, _ = v.load_spec(self.spec)
        v.locate(regions, SOURCE)
        total = math.prod(v.sizes(regions))
        self.assertEqual(total, 6)
        self.assertEqual(v.render(regions, v.choice(regions, 0), SOURCE), SOURCE)
        texts = {v.render(regions, v.choice(regions, i), SOURCE) for i in range(total)}
        self.assertEqual(len(texts), total)
        self.assertEqual(v.describe(regions, v.choice(regions, 4)), 'loads=b,a;ret=swapped')
        self.assertIn('    b = p[1];\n    a = p[0];\n    return b + a;', v.render(regions, v.choice(regions, 4), SOURCE))

    def test_nth_permutation(self):
        items = list('abcde')
        orders = [tuple(v.nth_permutation(items, n)) for n in range(120)]
        self.assertEqual(len(set(orders)), 120)
        self.assertEqual(orders[0], tuple(items))
        self.assertEqual(orders[-1], tuple(reversed(items)))

    def test_selection(self):
        self.assertEqual(v.selection(5, None, 0), [0, 1, 2, 3, 4])
        sample = v.selection(1000, 10, 3)
        self.assertEqual(len(sample), 10)
        self.assertEqual(sample[0], 0)
        self.assertEqual(sample, v.selection(1000, 10, 3))
        self.assertEqual(len(set(sample)), 10)

    def test_forbidden_forms(self):
        self.assertEqual(v.forbidden_added('x;', 'x;'), [])
        self.assertEqual(v.forbidden_added('x;', '#pragma optimize off\nx;'), ['#pragma'])
        self.assertEqual(v.forbidden_added('x;', 'x __attribute__((noinline));'), ['__attribute__'])
        self.assertEqual(v.forbidden_added('x;', 'asm { nop }'), ['asm'])
        self.assertEqual(v.forbidden_added('x;', '_Pragma("x")'), ['_Pragma'])
        # Forms the file already has may stay or move.
        self.assertEqual(v.forbidden_added('# pragma once\nx;', 'x;\n#pragma once'), [])
        self.assertEqual(v.forbidden_added('x;', 'int casm; /* asmx */'), [])


class TrialOutputTest(unittest.TestCase):
    def test_identical(self):
        self.assertEqual(v.parse_trial('f 0x80001000: IDENTICAL\n1 of 1 identical\n', 0), ('IDENTICAL', '100.00', ''))

    def test_differs(self):
        out = ('f 0x80001000: DIFFERS (97.25%, 8 bytes where the target has 4)\n'
               '     0  li r3, 0x0                           li r3, 0x0\n'
               '  ! 1C  lwz r4, 0x4(r3)                      lwz r5, 0x4(r3)\n'
               '  ! 20  blr                                  nop\n0 of 1 identical\n')
        self.assertEqual(v.parse_trial(out, 1), ('DIFFERS', '97.25', '1C: lwz r4, 0x4(r3) | lwz r5, 0x4(r3)'))

    def test_wrong_constant_and_missing(self):
        self.assertEqual(v.parse_trial('f 0x80001000: WRONG CONSTANT (lfs reads 1.0)\n', 1)[:2], ('WRONG CONSTANT', ''))
        self.assertEqual(v.parse_trial('f: MISSING (the compiler did not emit it)\n', 1)[0], 'MISSING')
        self.assertEqual(v.parse_trial('trial: x.c:3: parse error\n', 1), ('ERROR', '', 'trial: x.c:3: parse error'))


class RunTest(unittest.TestCase):
    """A whole run in a stand-in checkout whose trial.py judges the variant text."""

    def setUp(self):
        self.root = Path(tempfile.mkdtemp())
        write(self.root / 'src/x.c', SOURCE)
        write(self.root / 'tools/trial.py', FAKE_TRIAL)
        write(self.root / 'build/source/report.json', json.dumps({'complete': 'identical'}))
        write(self.root / 'build/matching/big.bin', 'not copied')
        write(self.root / '.git/HEAD', 'not copied')
        stage = self.root / 'build/source/stage/p'
        stage.mkdir(parents=True)
        (stage / 'Source').symlink_to(self.root / 'src', target_is_directory=True)
        self.spec = write(Path(tempfile.mkdtemp()) / 'spec.txt', SPEC)
        self.work = Path(tempfile.mkdtemp())
        for folder in (self.root, self.spec.parent, self.work):
            self.addCleanup(shutil.rmtree, folder)

    def run_tool(self, *extra):
        out = io.StringIO()
        with patch.object(v, 'ROOT', self.root), redirect_stdout(out):
            code = v.main(['src/x.c', 'f', str(self.spec), '--jobs', '2', '--work', str(self.work / 'w'), *extra])
        return code, out.getvalue()

    def results(self):
        folder = self.root / 'build/variants/src_x_c_f_spec'
        lines = (folder / 'results.tsv').read_text().splitlines()
        return folder, {int(l.split('\t')[0]): l.split('\t') for l in lines[2:]}

    def test_run_ranks_restores_and_resumes(self):
        code, output = self.run_tool()
        self.assertEqual(code, 0)
        self.assertEqual((self.root / 'src/x.c').read_text(), SOURCE)
        folder, rows = self.results()
        self.assertEqual(sorted(rows), list(range(6)))
        status = {i: r[2] for i, r in rows.items()}
        self.assertEqual(status[0], 'DIFFERS')
        self.assertEqual(status[3], 'IDENTICAL')   # loads=b,a;ret=orig
        self.assertEqual([status[2], status[5]], ['ERROR', 'ERROR'])  # the empty return
        self.assertEqual(rows[0][3:5], ['91.50', '4: lwz r4, 0x4(r3) | lwz r4, 0x0(r3)'])
        summary = (folder / 'summary.txt').read_text()
        self.assertIn('1\t3\tIDENTICAL\t100.00\tloads=b,a;ret=orig', summary)
        self.assertIn('+    b = p[1];', (folder / 'best.diff').read_text())
        # The copies: no history, no comparison pairs, the stage link into the copy, file restored.
        for copy in (self.work / 'w').iterdir():
            self.assertFalse((copy / '.git').exists())
            self.assertFalse((copy / 'build/matching').exists())
            link = copy / 'build/source/stage/p/Source'
            self.assertEqual(Path(os.readlink(link)), copy.resolve() / 'src')
            self.assertEqual((copy / 'src/x.c').read_text(), SOURCE)
            self.assertEqual(v.escapes(copy, self.root), [])
        # A rerun runs nothing; another spec in the same folder is refused.
        code, output = self.run_tool()
        self.assertEqual(code, 0)
        self.assertNotIn('[1/', output)
        self.spec.write_text(SPEC.replace('swapped', 'other'))
        with self.assertRaises(v.SpecError):
            self.run_tool()
        self.spec.write_text(SPEC)
        (self.root / 'src/x.c').write_text(SOURCE + '\n')  # the same spec on a changed file
        with self.assertRaises(v.SpecError):
            self.run_tool()

    def test_limit_first_and_list(self):
        code, output = self.run_tool('--list')
        self.assertEqual(code, 0)
        self.assertIn('6 of 6 variants', output)
        self.assertFalse((self.root / 'build/variants').exists())
        code, _ = self.run_tool('--limit', '3', '--seed', '1', '--fresh')
        _, rows = self.results()
        self.assertEqual(len(rows), 3)
        self.assertIn(0, rows)
        code, _ = self.run_tool('--fresh', '--first', '--jobs', '1')
        _, rows = self.results()
        self.assertEqual(max(rows), 3)

    def test_refusals(self):
        self.spec.write_text(SPEC.replace('    return b + a;', '#pragma optimize off\n    return b + a;'))
        with self.assertRaises(v.SpecError):
            self.run_tool()
        self.assertFalse((self.work / 'w').exists())
        self.spec.write_text(SPEC)
        with patch.object(v, 'ROOT', self.root), self.assertRaises(v.SpecError):
            v.main(['config/units.json', 'f', str(self.spec)])
        with self.assertRaises(v.SpecError):
            self.run_tool('--work', str(self.root / 'inside'))
        (self.root / 'build/source/report.json').write_text('{"complete": "stale"}')
        with self.assertRaises(v.SpecError):
            self.run_tool()


if __name__ == '__main__':
    unittest.main()
