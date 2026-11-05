"""Tests for the file-closing tools: naming, rename, the constant check, the dump flag and the
sibling tables."""
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import closes
import function_compare
import naming
import prodg_cc
import rename
import sibling_tables


def ppc(*words):
    return b''.join(struct.pack('>I', w) for w in words)


def addi(d, a, imm):
    return (14 << 26) | (d << 21) | (a << 16) | (imm & 0xFFFF)


def lfs(d, a, disp):
    return (48 << 26) | (d << 21) | (a << 16) | (disp & 0xFFFF)


def lfd(d, a, disp):
    return (50 << 26) | (d << 21) | (a << 16) | (disp & 0xFFFF)


def mr(a, s):  # or rA, rS, rS
    return (31 << 26) | (s << 21) | (a << 16) | (s << 11) | (444 << 1)


class Naming(unittest.TestCase):
    def test_placeholders(self):
        for name in ('fn_8000ABCD', 'lbl_803EC0F0', 'Class_803EC99C::GetName', 'Record_8036AD28', 'cu_80004AF0',
                     'sUnknown803EC0F0', 'mUnknown', 'vfn_01', 'ModuleGroup_8003450C', 'data_800236BC'):
            self.assertTrue(naming.placeholder(name), name)
        for name in ('PlayCaller::Update', 'CamFreeFloatInit', 'DVDInit', 'addEffect', 'GXTexImage1Ids',
                     '_NM_bExitGame', 'tmclip', 'Vec3_t', 'Known'):
            self.assertFalse(naming.placeholder(name), name)

    def test_generated(self):
        for symbol in ('gcc2_compiled.', '_GLOBAL_.I.GetDependencies__5Debug', '__static_initialization_and_destruction_0',
                       '__tcf_0', '_.tmp_3.105', '...data.0', '@123'):
            self.assertTrue(naming.generated(symbol), symbol)
        self.assertFalse(naming.generated('sInstance.105'))
        self.assertEqual(naming.base_name('sInstance.105'), 'sInstance')

    def test_demangle(self):
        self.assertEqual(naming.demangle('GetName__3Obj'), 'Obj::GetName')
        self.assertEqual(naming.demangle('_._6Module'), 'Module::~Module')
        self.assertEqual(naming.demangle('__14Class_801E27A4i'), 'Class_801E27A4::Class_801E27A4')
        self.assertEqual(naming.demangle('_TIMEUpdateFPS__FUi'), '_TIMEUpdateFPS')
        self.assertEqual(naming.demangle('DVDInit'), 'DVDInit')
        self.assertIsNone(naming.demangle('_GLOBAL_.I.vfn_01__14Class_80005618iPiT2'))


class Rename(unittest.TestCase):
    def test_text(self):
        old, new = 'Class_80005618', 'BootTaskQueue'
        self.assertEqual(rename.rename_text('Class_80005618::vfn_01 and Class_80005618Ex', old, new),
                         'BootTaskQueue::vfn_01 and Class_80005618Ex')
        self.assertEqual(rename.rename_text('vfn_01__14Class_80005618iPiT2', old, new), 'vfn_01__13BootTaskQueueiPiT2')
        self.assertEqual(rename.rename_text('x 114Class_80005618 y', old, new), 'x 114Class_80005618 y')
        self.assertEqual(rename.rename_text('fn_800D0408__14Class_803EC99C', 'fn_800D0408', 'IsReady'),
                         'IsReady__14Class_803EC99C')
        self.assertEqual(rename.rename_text('fn_800D04080 fn_800D0408.', 'fn_800D0408', 'IsReady'), 'fn_800D04080 IsReady.')

    def test_json_keys_and_values(self):
        data = {'externals': {'vfn_03__14Class_802A6BB0iPiT2': {'address': '0x80182A88', 'evidence': 'type row Class_802A6BB0.'}},
                'units': [{'source': 'src/game/cu_80181330.cpp', 'symbol': 'Class_802A6BB0'}]}
        renamed = rename.rename_json(data, 'Class_802A6BB0', 'MenuTable')
        self.assertEqual(list(renamed['externals']), ['vfn_03__9MenuTableiPiT2'])
        # An evidence value is a record and keeps its text.
        self.assertEqual(renamed['externals']['vfn_03__9MenuTableiPiT2']['evidence'], 'type row Class_802A6BB0.')
        self.assertEqual(renamed['units'][0]['symbol'], 'MenuTable')


class RenameEvidence(unittest.TestCase):
    HEADER = ['kind', 'start', 'end', 'subject', 'origin', 'start_boundary', 'end_boundary', 'evidence']

    def rows(self, *rows):
        return [row.split('|') for row in rows]

    def test_boundary_row_only_gets_a_name_row(self):
        rows = self.rows('function|0x801F34C0|0x801F3524|fn_801F34C0|target|exact|exact|bl target from 0x801F1548.')
        out = rename.rename_evidence(self.HEADER, rows, 'fn_801F34C0', 'HashString', 'Hashes a string.', 'inferred')
        self.assertEqual(out, self.rows('function|0x801F34C0|0x801F3524|HashString|target|exact|exact|bl target from 0x801F1548.',
                                        'name|0x801F34C0|-|HashString|inferred|-|-|Hashes a string.'))

    def test_neutral_row_is_replaced(self):
        rows = self.rows('name|0x800D0408|-|fn_800D0408|inferred|-|-|Neutral address label.',
                         'function|0x800D0408|0x800D0420|fn_800D0408|target|exact|exact|Called by fn_800D0408 users.')
        out = rename.rename_evidence(self.HEADER, rows, 'fn_800D0408', 'IsReady', 'Returns state +10.', 'inferred')
        self.assertEqual(out, self.rows('name|0x800D0408|-|IsReady|inferred|-|-|Returns state +10.',
                                        'function|0x800D0408|0x800D0420|IsReady|target|exact|exact|Called by fn_800D0408 users.'))

    def test_related_name_is_kept_as_record(self):
        rows = self.rows('name|0x8021A068|-|UISFindRateFnc|related|-|-|Madden STABS: Uint32 UISFindRateFnc(UISInfoT*)')
        out = rename.rename_evidence(self.HEADER, rows, 'UISFindRateFnc', 'ScanRateTable', 'Scans the table.', 'inferred')
        self.assertEqual(out, rows + self.rows('name|0x8021A068|-|ScanRateTable|inferred|-|-|Scans the table.'))

    def test_related_rows_are_never_changed(self):
        rows = self.rows('function|0x80250000|0x80250040|SIRefreshSamplingRate|related|exact|exact|Nintendo SDK reference name.',
                         'external|0x80250000|-|SIRefreshSamplingRate|related|-|-|BFBB symbol.')
        out = rename.rename_evidence(self.HEADER, rows, 'SIRefreshSamplingRate', 'RefreshRate', 'Refreshes.', 'inferred')
        self.assertEqual(out, rows[:1] + self.rows('name|0x80250000|-|RefreshRate|inferred|-|-|Refreshes.') + rows[1:])

    def test_our_descriptive_name_is_superseded(self):
        rows = self.rows('name|0x80027B5C|-|FELoop::GetDependencies|inferred|-|-|Returns the empty list.')
        out = rename.rename_evidence(self.HEADER, rows, 'GetDependencies', 'EmptyLinks', 'Returns 0x803EA2E8.', 'inferred')
        self.assertEqual(out, self.rows('name|0x80027B5C|-|FELoop::EmptyLinks|inferred|-|-|Returns 0x803EA2E8.'))
        back = rename.rename_evidence(self.HEADER, out, 'EmptyLinks', 'GetDependencies', 'Back.', 'inferred')
        self.assertEqual(back, self.rows('name|0x80027B5C|-|FELoop::GetDependencies|inferred|-|-|Back.'))

    def test_record_name_elsewhere_is_in_use(self):
        rows = self.rows('function|0x801F346C|0x801F34C0|ResLooseFileOpen|related|exact|exact|Related build.',
                         'function|0x801F34C0|0x801F3524|fn_801F34C0|target|exact|exact|bl target.',
                         'function|0x80250000|0x80250040|SIRefreshSamplingRate|related|exact|exact|SDK name.',
                         'name|0x80250000|-|RefreshRate|inferred|-|-|Refreshes.')
        self.assertTrue(rename.evidence_uses(self.HEADER, rows, 'fn_801F34C0', 'ResLooseFileOpen'))
        self.assertFalse(rename.evidence_uses(self.HEADER, rows, 'RefreshRate', 'SIRefreshSamplingRate'))
        self.assertTrue(rename.evidence_uses(self.HEADER, rows, 'fn_801F34C0', 'RefreshRate'))

    def test_target_name_row_is_a_record(self):
        rows = self.rows('name|0x8009FF00|-|DefPred::GetName|target|-|-|Returns the game string "DefPred".')
        out = rename.rename_evidence(self.HEADER, rows, 'GetName', 'Label', 'Returns its label.', 'inferred')
        self.assertEqual(out, rows + self.rows('name|0x8009FF00|-|DefPred::Label|inferred|-|-|Returns its label.'))

    def test_class_rename_adds_type_row(self):
        rows = self.rows('type|-|-|Class_802A6BB0 (include/game/x.h)|inferred|-|-|Base class of Class_80005578.',
                         'name|0x80182A88|-|Class_802A6BB0::Class_802A6BB0|inferred|-|-|Constructor.')
        out = rename.rename_evidence(self.HEADER, rows, 'Class_802A6BB0', 'MenuTable', 'Owns the menu.', 'inferred')
        self.assertEqual(out, self.rows('type|-|-|MenuTable (include/game/x.h)|inferred|-|-|Base class of Class_80005578.',
                                        'type|-|-|MenuTable|inferred|-|-|Owns the menu.',
                                        'name|0x80182A88|-|MenuTable::MenuTable|inferred|-|-|Constructor.'))

    def test_unrecorded_name_is_refused(self):
        with self.assertRaises(SystemExit):
            rename.rename_evidence(self.HEADER, [], 'fn_80000000', 'Thing', 'x', 'inferred')


class EvidenceNames(unittest.TestCase):
    def test_boundary_rows_do_not_name(self):
        import tempfile
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / 'evidence.tsv'
            path.write_text('\t'.join(RenameEvidence.HEADER) + '\n' + ''.join('\t'.join(row.split('|')) + '\n' for row in (
                'function|0x80000010|0x80000020|HashString|target|exact|exact|bl target.',
                'function|0x80000030|0x80000040|CARDGetBlock|related|exact|exact|SDK donor body.',
                'name|0x80000050|-|Update|inferred|-|-|Updates.',
                'data|0x80000060|0x80000064|__piReg storage|related|exact|exact|SDK.')))
            given = naming.evidence_names(path)
        self.assertNotIn(0x80000010, given)
        self.assertIn('CARDGetBlock', given[0x80000030])
        self.assertIn('Update', given[0x80000050])
        self.assertIn('__piReg', given[0x80000060])


class ConstantCheck(unittest.TestCase):
    def test_base_uses(self):
        code = ppc(addi(9, 9, 0x10), lfs(1, 9, 0), lfd(2, 9, 8), 0x4E800020)
        self.assertEqual(function_compare.base_uses(code, 0, 9), [(0, 4), (8, 8)])
        passed = ppc(addi(9, 9, 0x10), mr(3, 9), lfs(1, 9, 0))
        self.assertIsNone(function_compare.base_uses(passed, 0, 9))
        overwritten = ppc(addi(9, 9, 0x10), lfs(1, 9, 0), (32 << 26) | (9 << 21) | (9 << 16), lfs(2, 9, 4))
        self.assertEqual(function_compare.base_uses(overwritten, 0, 9), [(0, 4), (0, 4)])
        branch = (16 << 26) | (12 << 21) | (2 << 16) | 8  # beq +8
        call = (18 << 26) | 0x100 | 1  # bl
        # A callee-saved base outlives a branch or a call: later loads cannot be followed.
        self.assertIsNone(function_compare.base_uses(ppc(addi(31, 9, 0), lfs(1, 31, 0), branch, lfs(2, 31, 4), 0x4E800020), 0, 31))
        self.assertIsNone(function_compare.base_uses(ppc(addi(31, 9, 0), lfs(1, 31, 0), call, lfs(2, 31, 4)), 0, 31))
        # A volatile base does not survive a call; the function's return ends the scan.
        self.assertEqual(function_compare.base_uses(ppc(addi(9, 9, 0), lfs(1, 9, 0), call, lfs(2, 9, 4)), 0, 9), [(0, 4)])
        self.assertEqual(function_compare.base_uses(ppc(addi(9, 9, 0), lfs(1, 9, 0), 0x4E800020, lfs(2, 9, 4)), 0, 9), [(0, 4)])
        lmw = (46 << 26) | (29 << 21) | (9 << 16) | 8  # lmw r29, 8(r9): three words
        self.assertEqual(function_compare.base_uses(ppc(addi(9, 9, 0), lmw), 0, 9), [(8, 12)])

    def test_extent(self):
        sections = [{'name': '.rodata', 'index': 1, 'size': 0x20}]
        symbols = [{'name': 'table', 'shndx': 1, 'type': 1, 'value': 0x10, 'size': 0x10}]
        original = b'abcd\0\0\0\0' + b'\x3f\x80\0\0' + b'\0' * 4 + b'\x11' * 16
        extent = function_compare.literal_extent
        self.assertEqual(extent(sections, symbols, [], '.rodata', 8, (0, 4), original), (8, 12))
        self.assertEqual(extent(sections, symbols, [], '.rodata', 0, None, original), (0, 5))
        self.assertEqual(extent(sections, symbols, [], '.rodata', 0x14, None, original), (0x10, 0x20))
        self.assertEqual(extent(sections, symbols, [('.rodata', 12, None)], '.rodata', 8, None, original), (8, 12))

    def test_wrong_constant_fails(self):
        dol = bytearray(0x100 + 0x10)
        struct.pack_into('>I', dol, 0, 0x100)  # Text section 0: file offset 0x100,
        struct.pack_into('>I', dol, 0x48, 0x80003100)  # address 0x80003100,
        struct.pack_into('>I', dol, 0x90, 0x10)  # 16 bytes.
        dol[0x100:0x108] = b'\x3f\x80\0\0\x40\0\0\0'
        resolved = {'.rodata': (0x80003100, b'\x3f\x80\0\0\x40\0\0\0' + b'\0' * 8)}
        function_compare.check_literals('src/x.c', 'f', [('.rodata', (0, 4)), ('.rodata', (4, 8))], resolved, bytes(dol))
        swapped = {'.rodata': (0x80003100, b'\x40\0\0\0\x3f\x80\0\0' + b'\0' * 8)}
        with self.assertRaisesRegex(ValueError, 'f uses .rodata\\+0x0'):
            function_compare.check_literals('src/x.c', 'f', [('.rodata', (0, 4))], swapped, bytes(dol))


class DumpFlag(unittest.TestCase):
    def options(self, *extra):
        return ['--dir', '.', '-c', 'unit.c', '-o', 'unit.o', *extra]

    def test_valid(self):
        options = prodg_cc.parse(self.options('--dump-dir', str(ROOT / 'build/dumps'), '--dump', '-dl,-dg'))[0]
        self.assertEqual(prodg_cc.dump_options(options), (['-dl', '-dg'], (ROOT / 'build/dumps').resolve()))
        options = prodg_cc.parse(self.options('--dump-dir', '/tmp/dumps'))[0]
        self.assertEqual(prodg_cc.dump_options(options)[0], ['-da'])
        self.assertEqual(prodg_cc.dump_options(prodg_cc.parse(self.options())[0]), (None, None))

    def test_rejected(self):
        for extra in (('--dump-dir', str(ROOT / 'src/dumps')), ('--dump-dir', str(ROOT)),
                      ('--dump-dir', '/tmp/d', '--dump', '-O2'), ('--dump', '-da')):
            with self.assertRaises(ValueError, msg=extra):
                prodg_cc.parse(self.options(*extra))


class Closes(unittest.TestCase):
    def test_claimed(self):
        self.assertEqual(closes.claimed('Tier C\nCloses: `src/engine/hash.c`, src/game/FELoop.cpp\n'),
                         ['src/engine/hash.c', 'src/game/FELoop.cpp'])
        self.assertEqual(closes.claimed('**Closes:** none'), [])
        self.assertEqual(closes.claimed('Tier C, no files'), [])
        for form in ('- Closes: src/a.c', '* Closes: src/a.c', '> Closes: src/a.c', '_Closes:_ src/a.c',
                     '## Closes: src/a.c', '**Closes**: src/a.c', 'closes: src/a.c'):
            self.assertEqual(closes.claimed(form), ['src/a.c'], form)
        self.assertEqual(closes.claimed('Fixes #12. Closes #123.'), [])
        self.assertEqual(closes.claimed('<!-- e.g. `Closes: src/x.c` -->\nCloses: none'), [])
        self.assertEqual(closes.claimed('- A body line `Closes: <path>` fails CI unless the file is closed.'), [])
        with self.assertRaises(ValueError):
            closes.claimed('This PR closes: src/a.c')

    def test_check(self):
        import tempfile
        with tempfile.TemporaryDirectory() as folder:
            table = Path(folder) / 'files.tsv'
            table.write_text('source\tlinked\tfile_named\tlabels\tplaceholders\tunevidenced\tclosed\texamples\n'
                             'src/engine/hash.c\tyes\tyes\t1\t0\t0\tyes\t\n'
                             'src/game/cu_80060948.cpp\tpartly\tno\t9\t4\t0\tno\tfn_80060A9C\n')
            self.assertEqual(closes.check(['src/engine/hash.c'], table), [])
            problems = closes.check(['src/game/cu_80060948.cpp', 'src/x.c'], table)
        self.assertIn('not wholly linked', problems[0])
        self.assertIn('4 placeholder name(s)', problems[0])
        self.assertIn('not a source file', problems[1])


class MarkClosed(unittest.TestCase):
    def test_every_unit_carries_the_flag(self):
        import export_progress
        decomp = {'units': [{'metadata': {'source_path': 'src/engine/hash.c'}},
                            {'metadata': {'source_path': 'src/game/cu_80060948.cpp'}},
                            {'metadata': {'auto_generated': True}}]}
        export_progress.mark_closed(decomp, [{'source': 'src/engine/hash.c', 'closed': True},
                                             {'source': 'src/game/cu_80060948.cpp', 'closed': False}])
        self.assertEqual([u['metadata']['closed'] for u in decomp['units']], [True, False, False])
        with self.assertRaises(ValueError):
            export_progress.mark_closed(decomp, [{'source': 'src/missing.c', 'closed': True}])


class SiblingTables(unittest.TestCase):
    def test_nascar_units_up_to_date(self):
        path, text = sibling_tables.nascar_units()
        self.assertEqual(path.read_text(), text, 'run python3 tools/sibling_tables.py nascar-units')

    def test_ps2_map_shape(self):
        lines = [line for line in sibling_tables.PS2_MAP.read_text().splitlines() if not line.startswith('#')]
        self.assertEqual(lines[0], 'gc_start\tgc_end\tps2_start\tps2_end')
        starts = [int(line.split('\t')[0], 16) for line in lines[1:]]
        self.assertEqual(starts, sorted(starts))
        self.assertEqual(len(starts), len(set(starts)), 'one row per GameCube function')


if __name__ == '__main__':
    unittest.main()
