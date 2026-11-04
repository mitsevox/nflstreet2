"""Tests for the file-closing tools: naming, rename, the constant check, the dump flag and the
sibling tables."""
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
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
        self.assertEqual(renamed['externals']['vfn_03__9MenuTableiPiT2']['evidence'], 'type row MenuTable.')
        self.assertEqual(renamed['units'][0]['symbol'], 'MenuTable')


class ConstantCheck(unittest.TestCase):
    def test_base_uses(self):
        code = ppc(addi(9, 9, 0x10), lfs(1, 9, 0), lfd(2, 9, 8), 0x4E800020)
        self.assertEqual(function_compare.base_uses(code, 0, 9), [(0, 4), (8, 8)])
        passed = ppc(addi(9, 9, 0x10), mr(3, 9), lfs(1, 9, 0))
        self.assertIsNone(function_compare.base_uses(passed, 0, 9))
        overwritten = ppc(addi(9, 9, 0x10), lfs(1, 9, 0), (32 << 26) | (9 << 21) | (9 << 16), lfs(2, 9, 4))
        self.assertEqual(function_compare.base_uses(overwritten, 0, 9), [(0, 4), (0, 4)])

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


class SiblingTables(unittest.TestCase):
    def test_nascar_units_up_to_date(self):
        path, text = sibling_tables.nascar_units()
        self.assertEqual(path.read_text(), text, 'run python3 tools/sibling_tables.py nascar-units')

    def test_ps2_map_shape(self):
        lines = [line for line in sibling_tables.PS2_MAP.read_text().splitlines() if not line.startswith('#')]
        self.assertEqual(lines[0], 'gc_start\tgc_end\tps2_start\tps2_end')
        starts = [int(line.split('\t')[0], 16) for line in lines[1:]]
        self.assertEqual(starts, sorted(starts))


if __name__ == '__main__':
    unittest.main()
