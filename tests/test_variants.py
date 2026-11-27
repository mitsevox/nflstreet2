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

    def test_json_checks_names(self):
        for regions in [[{'replace': 'r', 'old': 'x', 'with': {'orig': 'y'}}],
                        [{'permute': 'p', 'items': [['a', 'x'], ['a', 'y']]}],
                        [{'replace': 'r;x', 'old': 'x', 'with': {'b': 'y'}}],
                        [{'replace': 'r', 'old': 'x', 'with': {'b\tc': 'y'}}],
                        [{'replace': 'r', 'old': 'x', 'with': {'b': '%% end'}}]]:
            with self.subTest(regions=regions), self.assertRaises(v.SpecError):
                v.load_spec(write(self.folder / 'bad.json', json.dumps({'regions': regions})))

    def test_percent_signs_in_source(self):
        spec = write(self.folder / 'p.txt', '%% replace fmt\n    printf("%d%%", n);\n%% with b\n    printf("%d%% ", n);\n%% end\n')
        self.assertEqual(v.load_spec(spec)[0][0]['old'], '    printf("%d%%", n);')

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
        # A swap keeps the count but changes the form.
        self.assertEqual(v.forbidden_added('#pragma implementation "x.h"\nx;', '#pragma optimize off\nx;'), ['#pragma'])
        # A comment or string that names a form is no form; turning it into one is.
        self.assertEqual(v.forbidden_added('/* asm */ x;', '"asm" x;'), [])
        self.assertEqual(v.forbidden_added('// asm\nx;', 'asm { nop }\nx;'), ['asm'])
        # Splices, comments in the directive, digraphs and trigraphs.
        self.assertEqual(v.forbidden_added('x;', '#pr\\\nagma optimize off\nx;'), ['#pragma'])
        self.assertEqual(v.forbidden_added('x;', '# /**/ pragma optimize off\nx;'), ['#pragma'])
        self.assertEqual(v.forbidden_added('x;', '%:pragma optimize off\nx;'), ['#pragma'])
        self.assertEqual(v.forbidden_added('x;', '??=pragma optimize off\nx;'), ['#pragma'])
        self.assertEqual(v.forbidden_added('x;', 'int y __attri\\\nbute__((x));'), ['__attribute__'])
        self.assertEqual(v.forbidden_added('x;', '#define C(a, b) a##b\nx;'), ['##'])
        self.assertEqual(v.forbidden_added('x;', '??=pr??/\nagma optimize off\nx;'), ['#pragma'])
        # A changed argument is a changed form (the tree's own cases).
        self.assertEqual(v.forbidden_added('register int *n asm("r0");', 'register int *n asm("r31");'), ['asm'])
        self.assertEqual(v.forbidden_added('#pragma implementation "phystime.h"', '#pragma implementation "DynObj.h"'),
                         ['#pragma'])
        self.assertEqual(v.forbidden_added('float x __attribute__((section(".sdata2")));',
                                           'float x __attribute__((section(".sdata")));'), ['__attribute__'])
        self.assertEqual(v.forbidden_added('x;', 'u8 b[4] ATTRIBUTE_ALIGN(32);'), ['__attribute__'])
        # Moving a line that holds a form is no change.
        self.assertEqual(v.forbidden_added('#pragma once\nint a;\nint b;', 'int a;\n#pragma once\nint b;'), [])


class TrialOutputTest(unittest.TestCase):
    def test_identical(self):
        self.assertEqual(v.parse_trial('f 0x80001000: IDENTICAL\n1 of 1 identical\n', 0), ('IDENTICAL', '100.00', ''))
        note = 'f 0x80001000: IDENTICAL (constants in .sdata2 not checked: x)\n'
        self.assertEqual(v.parse_trial(note, 0)[2], '(constants in .sdata2 not checked: x)')

    def test_padded_rows(self):  # trial.py pads the offset to 5 columns
        out = ('f 0x80001000: DIFFERS (50.00%)\n'
               '       0  li r3, 0x0                           li r3, 0x0\n'
               '  !    1C  lwz r4, 0x4(r3)                      lwz r5, 0x4(r3)\n')
        self.assertEqual(v.parse_trial(out, 1)[2], '1C: lwz r4, 0x4(r3) | lwz r5, 0x4(r3)')

    def test_differs(self):
        out = ('f 0x80001000: DIFFERS (97.25%, 8 bytes where the target has 4)\n'
               '     0  li r3, 0x0                           li r3, 0x0\n'
               '  ! 1C  lwz r4, 0x4(r3)                      lwz r5, 0x4(r3)\n'
               '  ! 20  blr                                  nop\n0 of 1 identical\n')
        self.assertEqual(v.parse_trial(out, 1), ('DIFFERS', '97.25', '1C: lwz r4, 0x4(r3) | lwz r5, 0x4(r3)'))

    def test_wrong_constant_and_missing(self):
        self.assertEqual(v.parse_trial('f 0x80001000: WRONG CONSTANT (lfs reads (1.0))\n', 1),
                         ('WRONG CONSTANT', '', 'lfs reads (1.0)'))
        self.assertEqual(v.parse_trial('f 0x80001000: WRONG CONSTANT (a) and (b)\n', 1)[2], '(a) and (b)')
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
        for copy in (self.work / 'w').glob('copy?'):
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

    def test_absolute_source_is_made_relative(self):
        before = (self.root / 'src/x.c').stat().st_mtime_ns
        out = io.StringIO()
        with patch.object(v, 'ROOT', self.root), redirect_stdout(out):
            code = v.main([str(self.root / 'src/x.c'), 'f', str(self.spec), '--jobs', '2', '--work', str(self.work / 'w')])
        self.assertEqual(code, 0)
        self.assertEqual((self.root / 'src/x.c').stat().st_mtime_ns, before)  # never written
        _, rows = self.results()
        self.assertEqual(rows[3][2], 'IDENTICAL')

    def test_stamp_recopies_and_refuses_resume(self):
        self.run_tool()
        copy = self.work / 'w/copy0'
        write(self.root / 'include/h.h', 'int y;')  # what trial.py reads has changed
        with self.assertRaises(v.SpecError):  # the earlier results are refused
            self.run_tool()
        self.run_tool('--fresh')
        self.assertEqual((copy / 'include/h.h').read_text(), 'int y;')  # the copy was made again

    def test_foreign_copy_is_refused(self):
        write(self.work / 'w/copy0/precious.txt', 'not the tool\'s')
        code, _ = self.run_tool('--jobs', '1')
        self.assertEqual(code, 2)
        self.assertTrue((self.work / 'w/copy0/precious.txt').exists())

    def test_one_run_per_folder(self):
        self.run_tool('--list')
        folder = self.root / 'build/variants/src_x_c_f_spec'
        folder.mkdir(parents=True)
        import fcntl
        with (folder / '.lock').open('w') as holder:
            fcntl.flock(holder, fcntl.LOCK_EX)
            with self.assertRaises(v.SpecError):
                self.run_tool()
        (self.work / 'w').mkdir()
        with (self.work / 'w/.lock').open('w') as holder:  # the same --work, another results folder
            fcntl.flock(holder, fcntl.LOCK_EX)
            with self.assertRaises(v.SpecError):
                self.run_tool('--out', str(self.work / 'other'))

    def test_limit_first_and_list(self):
        code, output = self.run_tool('--list')
        self.assertEqual(code, 0)
        self.assertIn('6 of 6 variants', output)
        self.assertFalse((self.root / 'build/variants').exists())
        code, _ = self.run_tool('--limit', '3', '--seed', '1', '--fresh')
        folder, rows = self.results()
        self.assertEqual(len(rows), 3)
        self.assertIn(0, rows)
        code, _ = self.run_tool('--limit', '2', '--seed', '1')  # a smaller selection reports only itself
        self.assertIn('2 of 2 variants run', (folder / 'summary.txt').read_text())
        code, _ = self.run_tool('--fresh', '--first', '--jobs', '1')
        _, rows = self.results()
        self.assertEqual(max(rows), 3)

    def test_refusals(self):
        self.spec.write_text(SPEC.replace('    return b + a;', '#pragma optimize off\n    return b + a;'))
        with self.assertRaises(v.SpecError):
            self.run_tool()
        self.assertFalse((self.work / 'w').exists())
        self.spec.write_text(SPEC)
        write(self.root / 'config/units.json', '{}')  # it exists, so only the src/ rule refuses it
        (self.root / 'src/out.c').symlink_to(self.root / 'config/units.json')  # leaves src/
        for source in ('config/units.json', 'src/out.c', 'src/../src/x.c', '/elsewhere/src/x.c'):
            with self.subTest(source=source), patch.object(v, 'ROOT', self.root), self.assertRaises(v.SpecError):
                v.main([source, 'f', str(self.spec), '--work', str(self.work / 'w')])
        with self.assertRaises(v.SpecError):
            self.run_tool('--work', str(self.root / 'inside'))
        (self.root / 'build/source/report.json').write_text('{"complete": "stale"}')
        with self.assertRaises(v.SpecError):
            self.run_tool()


if __name__ == '__main__':
    unittest.main()
