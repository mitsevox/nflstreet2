import copy
import json
from pathlib import Path
import shutil
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import function_compare
import matching
import source_build as sb
import decomp_report


class ExportSemantics(unittest.TestCase):
    def data(self):
        return {'files': [
            {'name': 'file.c', 'source': 'src/file.c', 'kind': 'code', 'size': 100,
             'linked': 20, 'matched': 30, 'fuzzy': 40, 'children': []},
            {'name': 'file.c', 'source': 'src/file.c', 'kind': 'data', 'size': 100,
             'linked': 90, 'matched': 90, 'fuzzy': 95, 'children': []},
            {'name': 'done.c', 'source': 'src/done.c', 'kind': 'code', 'size': 20, 'complete': True,
             'linked': 20, 'matched': 20, 'fuzzy': 20, 'children': []},
            {'name': 'unmapped', 'kind': 'data', 'size': 20,
             'linked': 20, 'matched': 20, 'fuzzy': 20, 'children': []}]}

    def test_code_fuzzy_denominator_is_independent_of_data(self):
        report = decomp_report.objdiff_report(self.data())
        self.assertEqual(report['measures']['fuzzy_match_percent'], 50)
        self.assertEqual(report['measures']['matched_code'], '50')
        self.assertEqual(report['measures']['complete_code'], '40')
        self.assertNotIn('categories', report)
        unit = next(u for u in report['units'] if u['name'] == 'src/file.c')
        self.assertEqual(unit['sections'][1]['fuzzy_match_percent'], 95)

    def test_completion_requires_boundary_evidence_all_extents_linked_and_real_source(self):
        report = decomp_report.objdiff_report(self.data())
        units = {u['name']: u for u in report['units']}
        self.assertFalse(units['src/file.c']['metadata']['complete'])
        self.assertTrue(units['src/done.c']['metadata']['complete'])
        self.assertFalse(units['unmapped']['metadata']['complete'])
        self.assertEqual(report['measures']['complete_units'], 1)
        self.assertEqual(units['src/done.c']['measures']['complete_units'], 1)


class InPlaceComparisons(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        for name in ('src', 'config/GN7E69', 'tools', 'build/source'):
            (self.root/name).mkdir(parents=True)
        self.source = self.root/'src/unit.c'
        self.source.write_text('int fn_80000000(void) { volatile int x = 1; return x; }\n')
        self.binary = self.dol(bytes.fromhex('386000014e800020'))
        self.target = {'sha1': matching.hashlib.sha1(self.binary).hexdigest(), 'size': len(self.binary),
                       'entry': '0x80000000', 'sda_base':'0x803F22A0', 'sda2_base':'0x804022A0',
                       'sections': {'.text': '0x80000000'}}
        self.manifest = {'schema':1, 'target':'GN7E69', 'compiler':'3.9.3', 'include_dirs':[],
                         'profiles':{'test':{'flags':['-O2'], 'evidence':'test fixture'}},
                         'externals':{}, 'units':[]}
        self.unit = {'source':'src/unit.c', 'profile':'test', 'evidence':'test fixture',
                     'sections':[{'section':'.text', 'placement':'.text', 'start':'0x80000000','end':'0x80000008'}],
                     'functions':[{'symbol':'fn_80000000','start':'0x80000000','end':'0x80000008'}]}
        self.config = {'schema':2, 'units':[self.unit]}
        self.write_config()
        (self.root/'config/GN7E69/analysis.json').write_text(json.dumps({'output_sections': {'.data5':'.sdata'}}))
        (self.root/'config/GN7E69/baseline.json').write_text(json.dumps(self.target))
        (self.root/'config/GN7E69/evidence.tsv').write_text('kind\tstart\tend\tstart_boundary\tend_boundary\tsubject\n'
            'function\t0x80000000\t0x80000008\texact\texact\tfn_80000000\n')
        (self.root/'build/source/report.json').write_text('{"units": []}')
        shutil.copy(sb.ROOT/'tools/prodg_cc.py', self.root/'tools/prodg_cc.py')
        self.original = self.root/'build/original.dol'
        self.original.write_bytes(self.binary)
        compiler = sb.ROOT/'build/toolchain/ProDG/3.9.3'
        wrapper = sb.ROOT/'build/toolchain/wibo'
        self.tool = sb.ROOT/'build/baseline/tools/objdiff'
        self.compiler_available = compiler.is_dir() and wrapper.is_file() and self.tool.is_file()
        self.patches = [patch.object(sb, 'ROOT', self.root), patch.object(sb, 'BUILD', self.root/'build/source'),
                        patch.object(sb.setup_compiler, 'setup', return_value=(compiler, wrapper))]
        for mocked in self.patches:
            mocked.start(); self.addCleanup(mocked.stop)

    def write_config(self):
        (self.root/'config/GN7E69/units.json').write_text(json.dumps(self.manifest))
        (self.root/function_compare.CONFIG).write_text(json.dumps(self.config))

    @staticmethod
    def dol(payload):
        header=bytearray(256)
        for offset, value in ((0,256),(0x48,0x80000000),(0x90,len(payload))):
            struct.pack_into('>I',header,offset,value)
        return bytes(header)+payload

    def test_normal_source_path_and_same_profile_are_required(self):
        self.unit['source']='nonmatching/unit.c';self.write_config()
        with self.assertRaisesRegex(ValueError,'normal src'):
            function_compare.configured(self.root,self.binary)
        self.unit['source']='src/unit.c'
        self.manifest['units']=[dict(self.unit,profile='different')];self.write_config()
        with self.assertRaisesRegex(ValueError,'same compiler profile'):
            function_compare.configured(self.root,self.binary)

    def test_evidence_and_unique_target_coverage_are_required(self):
        self.unit['functions'][0]['end']='0x80000004';self.write_config()
        with self.assertRaisesRegex(ValueError,'evidenced'):
            function_compare.configured(self.root,self.binary)
        self.unit['functions'][0]['end']='0x80000008'
        self.unit['functions'].append(copy.deepcopy(self.unit['functions'][0]));self.write_config()
        with self.assertRaises(ValueError):function_compare.configured(self.root,self.binary)

    def test_real_variable_size_compile_and_receipt_mutations(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI build/matching steps')
        # A compiler-produced two-instruction body compared with a longer target
        # containing padding instructions exercises ordinary size disagreement.
        self.source.write_text('int fn_80000000(void) { return 1; }\n')
        self.binary = self.dol(bytes.fromhex('3860000160000000600000004e800020'))
        self.original.write_bytes(self.binary)
        self.unit['sections'][0]['end'] = '0x80000010'
        self.unit['functions'][0]['end'] = '0x80000010'
        self.write_config()
        evidence = self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text().replace('0x80000008', '0x80000010'))
        receipts=function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)
        entries=function_compare.load(receipts,self.binary,self.root)
        self.assertEqual(len(entries),1)
        self.assertEqual(entries[0]['matched'],0)
        self.assertGreater(entries[0]['fuzzy'],0)
        self.assertLess(entries[0]['fuzzy'],16)
        native_sections,_=sb.read_elf((self.root/receipts[0]['object']).read_bytes())
        self.assertNotEqual(next(s['size'] for s in native_sections if s['name']=='.text'),16)
        for mutation in ('omit','duplicate','false_exact','stale_output','stale_dependency'):
            corrupt=copy.deepcopy(receipts)
            if mutation=='omit':corrupt[0]['entries']=[];corrupt[0]['pairs']=[]
            if mutation=='duplicate':corrupt[0]['entries']*=2;corrupt[0]['pairs']*=2
            if mutation=='false_exact':corrupt[0]['entries'][0].update(matched=16,fuzzy=16)
            if mutation=='stale_output':corrupt[0]['pairs'][0]['sha256']='bad'
            if mutation=='stale_dependency':next(iter(corrupt[0]['dependencies']));corrupt[0]['dependencies']['src/unit.c']='bad'
            with self.subTest(mutation=mutation),self.assertRaises(ValueError):
                function_compare.load(corrupt,self.binary,self.root)
        self.binary = self.dol(bytes.fromhex('386000014e800020'))
        self.original.write_bytes(self.binary)
        self.unit['sections'][0]['end'] = '0x80000008'
        self.unit['functions'][0]['end'] = '0x80000008'
        self.write_config()
        evidence.write_text(evidence.read_text().replace('0x80000010', '0x80000008'))
        exact=function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)
        self.assertEqual(function_compare.load(exact,self.binary,self.root)[0]['matched'],8)
        self.assertFalse(exact[0]['entries'][0]['linked'])

    def test_mixed_guarded_source_with_staged_path_and_same_profile(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.source.write_text('int fn_80000000(void) { return 1; }\n'
                               '#if defined(DECOMP_COMPARE)\n'
                               'int fn_80000100(void) { return 2; }\n#endif\n')
        self.binary = self.dol(bytes.fromhex('386000014e800020') + bytes(248) + bytes.fromhex('386000024e800020'))
        self.original.write_bytes(self.binary)
        self.unit['sections'][0]['end'] = '0x80000108'
        self.unit['functions'].append({'symbol':'fn_80000100','start':'0x80000100','end':'0x80000108'})
        self.manifest['profiles']['test']['source_root'] = {
            'directory':'src', 'file_prefix':'../../../Source', 'evidence':'staged test fixture'}
        self.write_config()
        evidence=self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text() + 'function\t0x80000100\t0x80000108\texact\texact\tfn_80000100\n')
        manifest, units=function_compare.configured(self.root,self.binary)
        unit=units[0]
        compiler, wrapper=sb.setup_compiler.setup()
        unit['object']=self.root/'build/source/normal.o';unit['depfile']=self.root/'build/source/normal.d'
        sb.compile_unit(unit,compiler,wrapper,None,[],comparison=False)
        self.assertEqual({s['name'] for s in sb.read_elf(unit['object'].read_bytes())[1] if s['type']==2}, {'fn_80000000'})
        accepted_object=self.root/'build/source/obj/unit000_src_unit_c.o'
        accepted_object.parent.mkdir();shutil.copy(unit['object'],accepted_object)
        receipt={'source':'src/unit.c','native_object_sha256':sb.sha256(accepted_object),
                 'functions':[{'symbol':'fn_80000000','address':'0x80000000','size':8}],
                 'sections':[{'start':'0x80000000','end':'0x80000008'}]}
        (self.root/'build/source/report.json').write_text(json.dumps({'units':[receipt]}))
        measured=function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)
        entries=function_compare.load(measured,self.binary,self.root)
        self.assertEqual([(e['start'],e['matched'],e['linked']) for e in entries], [('0x80000100',8,False)])
        self.assertEqual(self.source.read_text().count('fn_80000100'),1)
        self.assertEqual(sb.sha256(accepted_object),receipt['native_object_sha256'])

    def test_same_file_call_uses_evidenced_callee_address(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.source.write_text('int fn_80000100(void) { return 1; }\n'
                               'int fn_80000000(void) { return fn_80000100()+2; }\n')
        self.manifest['profiles']['test']['flags']=['-O2','-fno-inline']
        self.binary=self.dol(bytes(0x108));self.original.write_bytes(self.binary)
        self.unit['sections'][0]['end']='0x80000108'
        self.unit['functions'][0]['end']='0x80000040'
        self.unit['functions'].append({'symbol':'fn_80000100','start':'0x80000100','end':'0x80000108'})
        self.write_config()
        evidence=self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text().replace('0x80000008','0x80000040')+
            'function\t0x80000100\t0x80000108\texact\texact\tfn_80000100\n')
        measured=function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)
        pair=measured[0]['pairs'][0]
        sections,symbols=sb.read_elf((self.root/pair['path']).read_bytes())
        function=next(s for s in symbols if s['name']=='function')
        section=next(s for s in sections if s['index']==function['shndx'])
        branch_targets=[]
        for offset in range(0,function['size'],4):
            opcode=struct.unpack_from('>I',section['data'],offset)[0]
            if opcode & 0xFC000003 == 0x48000001:
                distance=opcode & 0x03FFFFFC
                if distance & 0x02000000:distance-=0x04000000
                branch_targets.append(0x80000000+offset+distance)
        self.assertEqual(branch_targets,[0x80000100])
        function_compare.load(measured,self.binary,self.root)
        # Omitting the callee's identity must fail instead of scoring a moved call.
        self.unit['functions'].pop();self.write_config()
        with self.assertRaisesRegex(ValueError,'target identity'):
            function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)

    def check_transported_receipt(self, staged):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        header = self.root / 'include/value.h'
        header.parent.mkdir()
        header.write_text('#define VALUE 1\n')
        self.source.write_text('#include "value.h"\nint fn_80000000(void) { return VALUE; }\n')
        self.manifest['include_dirs'] = ['include']
        if staged:
            self.manifest['profiles']['test']['source_root'] = {
                'directory':'src', 'file_prefix':'../../../Source', 'evidence':'staged test fixture'}
        self.write_config()
        receipts = function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        receipt = receipts[0]
        self.assertEqual(set(receipt['dependencies']), {'src/unit.c', 'include/value.h'})
        self.assertEqual(sb.sha256(self.root/receipt['object']), receipt['object_sha256'])
        self.assertNotIn(str(self.root), (self.root/receipt['depfile']).read_text())

        with tempfile.TemporaryDirectory() as directory:
            moved = Path(directory) / 'checkout with spaces'
            shutil.copytree(self.root, moved, symlinks=True)
            shutil.rmtree(self.root)
            # A transported staged checkout also retains the original, now dangling
            # source-root symlink. Receipt validation must not need that build path.
            with patch.object(sb, 'ROOT', moved), patch.object(sb, 'BUILD', moved/'build/source'), \
                    patch.object(sb, 'stage', side_effect=AssertionError('load must not stage sources')):
                entries = function_compare.load(receipts, self.binary, moved)
                self.assertEqual([(e['matched'], e['linked']) for e in entries], [(8, False)])
                self.assertEqual(sb.sha256(moved/receipt['object']), receipt['object_sha256'])
                (moved/'include/value.h').write_text('#define VALUE 2\n')
                with self.assertRaisesRegex(ValueError, 'Stale comparison source or dependencies'):
                    function_compare.load(receipts, self.binary, moved)
                (moved/'include/value.h').write_text('#define VALUE 1\n')

                depfile = moved / receipt['depfile']
                for text, error in (
                        ('native.o: src/unit.c\n', 'dependencies differ'),
                        ('native.o: src/unit.c ../foreign.h\n', 'outside the repository')):
                    with self.subTest(depfile=text):
                        depfile.write_text(text)
                        changed = copy.deepcopy(receipts)
                        changed[0]['depfile_sha256'] = sb.sha256(depfile)
                        with self.assertRaisesRegex(ValueError, error):
                            function_compare.load(changed, self.binary, moved)

    def test_receipt_survives_checkout_move(self):
        self.check_transported_receipt(staged=False)

    def test_staged_receipt_survives_checkout_move(self):
        self.check_transported_receipt(staged=True)

    def test_same_file_small_data_relocations_and_data_scores(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.source.write_text('static volatile int value = 1;\nint fn_80000000(void) { return value; }\n')
        binary=bytearray(self.dol(bytes.fromhex('806d80004e800020')))
        for offset,value in ((0x1C,len(binary)),(0x64,0x803EA2A0),(0xAC,4)):
            struct.pack_into('>I',binary,offset,value)
        binary+=bytes.fromhex('00000001')
        self.binary=bytes(binary);self.original.write_bytes(self.binary)
        self.target['sections']['.data5']='0x803EA2A0'
        (self.root/'config/GN7E69/baseline.json').write_text(json.dumps(self.target))
        self.unit['sections'].append({'section':'.sdata','placement':'.data5',
                                     'start':'0x803EA2A0','end':'0x803EA2A4'})
        self.write_config()
        evidence=self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text()+'data\t0x803EA2A0\t0x803EA2A4\texact\texact\tvalue\n')
        measured=function_compare.generate(self.original,self.root/'build/source/report.json',self.tool)
        entries=function_compare.load(measured,self.binary,self.root)
        self.assertEqual([(e['kind'],e['matched']) for e in entries],[('code',8),('data',4)])

    def partial_data_fixture(self, linked_rodata=b'linked\0\0', middle=False, tail_source=False):
        """Draft and linked functions share one compiled .rodata; only the unlinked slices are measured.

        By default the leading 12 bytes are unlinked. `middle` adds a guarded draft after the linked
        function and registers both slices around the linked bytes. `tail_source` compiles that extra
        draft while registering only the leading placement, so the compiled section is longer."""
        tail = middle or tail_source
        self.source.write_text('#if defined(DECOMP_COMPARE)\n'
                               'const char *fn_80000000(void) { return "draft text"; }\n#endif\n'
                               'const char *fn_80000100(void) { return "linked"; }\n' +
                               ('#if defined(DECOMP_COMPARE)\n'
                                'const char *fn_80000200(void) { return "tail"; }\n#endif\n' if tail else ''))
        rodata = b'draft TEXT\0\0' + linked_rodata + (b'taiL\0\0\0\0' if middle else b'')
        code = (bytes.fromhex('3c608010386300004e800020') + bytes(0xF4) +
                bytes.fromhex('3c6080103863000c4e800020'))
        if middle:
            code += bytes(0xF4) + bytes.fromhex('3c608010386300144e800020')
        binary = bytearray(self.dol(code))
        for offset, value in ((0x1C, len(binary)), (0x64, 0x80100000), (0xAC, len(rodata))):
            struct.pack_into('>I', binary, offset, value)
        self.binary = bytes(binary + rodata); self.original.write_bytes(self.binary)
        self.target['sections']['.data3'] = '0x80100000'
        (self.root/'config/GN7E69/baseline.json').write_text(json.dumps(self.target))
        accepted = {'source':'src/unit.c', 'profile':'test', 'evidence':'test fixture', 'sections':[
            {'section':'.text','placement':'.text','start':'0x80000100','end':'0x8000010C'},
            {'section':'.rodata','placement':'.data3','start':'0x8010000C','end':'0x80100014'}]}
        self.manifest['units'] = [accepted]
        end = 0x80100000 + len(rodata)
        self.unit['sections'] = [{'section':'.text','placement':'.text','start':'0x80000000',
                                  'end':'0x8000020C' if middle else '0x8000010C'},
                                 {'section':'.rodata','placement':'.data3','start':'0x80100000','end':f'0x{end:08X}'}]
        self.unit['functions'] = [{'symbol':'fn_80000000','start':'0x80000000','end':'0x8000000C'}]
        evidence = ('kind\tstart\tend\tstart_boundary\tend_boundary\tsubject\n'
                    'function\t0x80000000\t0x8000000C\texact\texact\tfn_80000000\n'
                    'function\t0x80000100\t0x8000010C\texact\texact\tfn_80000100\n'
                    'data\t0x80100000\t0x8010000C\texact\texact\tdraft strings\n')
        if middle:
            self.unit['functions'].append({'symbol':'fn_80000200','start':'0x80000200','end':'0x8000020C'})
            evidence += ('function\t0x80000200\t0x8000020C\texact\texact\tfn_80000200\n'
                         'data\t0x80100014\t0x8010001C\texact\texact\ttail string\n')
        self.write_config()
        (self.root/'config/GN7E69/evidence.tsv').write_text(evidence)
        manifest, units = function_compare.configured(self.root, self.binary)
        unit = dict(units[0], sections=accepted['sections'])
        compiler, wrapper = sb.setup_compiler.setup()
        accepted_object = self.root/'build/source/obj/unit000_src_unit_c.o'
        accepted_object.parent.mkdir(exist_ok=True)
        unit['object'] = accepted_object; unit['depfile'] = self.root/'build/source/normal.d'
        sb.compile_unit(unit, compiler, wrapper, None, [], comparison=False)
        self.report = {'units':[{'source':'src/unit.c', 'native_object_sha256':sb.sha256(accepted_object),
            'functions':[{'symbol':'fn_80000100','address':'0x80000100','size':12}],
            'sections':[{'start':s['start'],'end':s['end']} for s in accepted['sections']]}]}
        (self.root/'build/source/report.json').write_text(json.dumps(self.report))

    def test_data_slices_are_the_placement_outside_same_file_linked_source(self):
        placement = {'start': 0x100, 'end': 0x200}
        self.assertEqual(function_compare.data_slices('a', placement, []), [(0x100, 0x200)])
        self.assertEqual(function_compare.data_slices('a', placement, [('a', 0x140, 0x180), ('b', 0x200, 0x210)]),
                         [(0x100, 0x140), (0x180, 0x200)])
        self.assertEqual(function_compare.data_slices('a', placement, [('a', 0x100, 0x200)]), [])
        with self.assertRaisesRegex(ValueError, 'partially overlaps'):
            function_compare.data_slices('a', placement, [('a', 0x1F0, 0x210)])
        with self.assertRaisesRegex(ValueError, 'lies inside linked source'):
            function_compare.data_slices('a', placement, [('a', 0x0F0, 0x210)])
        with self.assertRaisesRegex(ValueError, "another file"):
            function_compare.data_slices('a', placement, [('b', 0x0F0, 0x210)])
        with self.assertRaisesRegex(ValueError, "another file"):
            function_compare.data_slices('a', placement, [('b', 0x140, 0x180)])

    def test_partial_data_overlap_keeps_full_placement_and_measures_unlinked_slice(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.partial_data_fixture()
        receipts = function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        entries = function_compare.load(receipts, self.binary, self.root)
        self.assertEqual([(e['kind'], e['start'], e['end'], e['linked']) for e in entries],
                         [('code', '0x80000000', '0x8000000C', False), ('data', '0x80100000', '0x8010000C', False)])
        # The draft's string reference relocates against the full native placement.
        self.assertEqual(entries[0]['matched'], 12)
        self.assertEqual(entries[1]['matched'], 0)
        self.assertLess(entries[1]['fuzzy'], 12)
        sections, _ = sb.read_elf((self.root/receipts[0]['pairs'][1]['path']).read_bytes())
        section = next(s for s in sections if s['name'] == '.rodata')
        self.assertEqual((section['addr'], section['size']), (0x80100000, 20))

    def test_partial_data_receipt_rejects_missing_duplicate_and_linked_byte_credit(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.partial_data_fixture()
        receipts = function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        function_compare.load(receipts, self.binary, self.root)
        data = [i for i, e in enumerate(receipts[0]['entries']) if e['kind'] == 'data']
        self.assertEqual(len(data), 1)
        index = data[0]
        cases = {}
        missing = copy.deepcopy(receipts)
        del missing[0]['entries'][index], missing[0]['pairs'][index]
        cases['missing'] = (missing, 'omits')
        duplicate = copy.deepcopy(receipts)
        duplicate[0]['entries'].append(duplicate[0]['entries'][index])
        duplicate[0]['pairs'].append(duplicate[0]['pairs'][index])
        cases['duplicate'] = (duplicate, 'more than once')
        for end in ('0x80100014', '0x80100010'):
            whole = copy.deepcopy(receipts)
            for row in (whole[0]['entries'][index], whole[0]['pairs'][index]):
                row['end'] = end
            cases['linked ' + end] = (whole, 'linked source bytes')
        extra = copy.deepcopy(receipts)
        for row in (extra[0]['entries'], extra[0]['pairs']):
            row.append(dict(row[index], start='0x8010000C', end='0x80100014'))
        cases['linked extra'] = (extra, 'linked source bytes')
        for name, (corrupt, error) in cases.items():
            with self.subTest(mutation=name), self.assertRaisesRegex(ValueError, error):
                function_compare.load(corrupt, self.binary, self.root)
        # A receipt measured against different linked placements is not reused.
        changed = copy.deepcopy(self.report)
        changed['units'][0]['sections'].pop()
        (self.root/'build/source/report.json').write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'Linked source differs'):
            function_compare.load(receipts, self.binary, self.root)

    def test_partial_data_overlap_requires_evidenced_slices_and_native_layout(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        # The last linked byte differs, so the native-layout check must cover the whole linked range.
        self.partial_data_fixture(linked_rodata=b'linked\0\1')
        with self.assertRaisesRegex(ValueError, 'linked bytes at their native placement'):
            function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        evidence = self.root/'config/GN7E69/evidence.tsv'
        evidence.write_text(evidence.read_text().replace('0x8010000C\texact\texact', '0x8010000C\texact\tprovisional'))
        with self.assertRaisesRegex(ValueError, 'evidenced'):
            function_compare.configured(self.root, self.binary)
        evidence.write_text(evidence.read_text().replace('0x8010000C\texact\tprovisional', '0x80100014\texact\texact'))
        with self.assertRaisesRegex(ValueError, 'evidenced'):
            function_compare.configured(self.root, self.binary)
        self.manifest['units'][0]['sections'][1]['end'] = '0x80100018'; self.write_config()
        with self.assertRaisesRegex(ValueError, 'partially overlaps'):
            function_compare.configured(self.root, self.binary)

    def rewrite_sliced_data(self, receipts, change):
        """Rewrite the sliced .rodata ELF of a receipt and refresh every pair hash that names it."""
        pair = next(p for p in receipts[0]['pairs'] if p['symbol'] == '.rodata')
        path = self.root/pair['path']
        data = bytearray(path.read_bytes())
        sections, _ = sb.read_elf(bytes(data))
        section = next(s for s in sections if s['name'] == '.rodata')
        shoff = struct.unpack_from('>I', data, 32)[0]
        shentsize = struct.unpack_from('>H', data, 46)[0]
        change(data, section, shoff + section['index'] * shentsize)
        path.write_bytes(bytes(data))
        changed = copy.deepcopy(receipts)
        for row in changed[0]['pairs']:
            if row['path'] == pair['path']:
                row['sha256'] = sb.sha256(path)
        return changed

    def test_partial_data_reload_rechecks_native_bytes_and_size(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.partial_data_fixture()
        receipts = function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        path = self.root/next(p for p in receipts[0]['pairs'] if p['symbol'] == '.rodata')['path']
        original = path.read_bytes()

        def last_linked_byte(data, section, header):
            data[section['offset'] + 0x13] ^= 1

        def longer(data, section, header):
            struct.pack_into('>I', data, header + 20, section['size'] + 4)

        for change, error in ((last_linked_byte, 'linked bytes at their native placement'),
                              (longer, 'must compile to its full target placement')):
            with self.subTest(change=change.__name__):
                try:
                    changed = self.rewrite_sliced_data(receipts, change)
                    with self.assertRaisesRegex(ValueError, error):
                        function_compare.load(changed, self.binary, self.root)
                finally:
                    path.write_bytes(original)
        function_compare.load(receipts, self.binary, self.root)

    def test_partial_data_generation_rejects_longer_section_and_changed_linked_placements(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        # The extra draft's string follows the linked bytes, beyond the registered placement.
        self.partial_data_fixture(tail_source=True)
        with self.assertRaisesRegex(ValueError, 'must compile to its full target placement'):
            function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        self.partial_data_fixture()
        changed = copy.deepcopy(self.report)
        changed['units'][0]['sections'].pop()
        (self.root/'build/source/report.json').write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'Linked source differs'):
            function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)

    def test_linked_bytes_in_the_middle_leave_two_measured_slices(self):
        if not self.compiler_available:
            self.skipTest('Pinned compiler and objdiff are installed by CI')
        self.partial_data_fixture(middle=True)
        receipts = function_compare.generate(self.original, self.root/'build/source/report.json', self.tool)
        entries = function_compare.load(receipts, self.binary, self.root)
        self.assertEqual([(e['kind'], e['start'], e['end'], e['matched']) for e in entries],
                         [('code', '0x80000000', '0x8000000C', 12), ('code', '0x80000200', '0x8000020C', 12),
                          ('data', '0x80100000', '0x8010000C', 0), ('data', '0x80100014', '0x8010001C', 0)])
        data_pairs = [p for p in receipts[0]['pairs'] if p['symbol'] == '.rodata']
        self.assertEqual(len({p['path'] for p in data_pairs}), 1)
        folder = self.root/'build/matching/candidates/0'
        self.assertTrue((folder/'data-rodata-80100000').is_dir())
        self.assertTrue((folder/'data-rodata-80100014').is_dir())
        index = next(i for i, e in enumerate(receipts[0]['entries']) if e['start'] == '0x80100014')
        missing = copy.deepcopy(receipts)
        del missing[0]['entries'][index], missing[0]['pairs'][index]
        with self.assertRaisesRegex(ValueError, 'omits'):
            function_compare.load(missing, self.binary, self.root)
        bridged = copy.deepcopy(receipts)
        for row in (bridged[0]['entries'][index], bridged[0]['pairs'][index]):
            row['start'] = '0x80100010'
        with self.assertRaisesRegex(ValueError, 'linked source bytes'):
            function_compare.load(bridged, self.binary, self.root)

    def test_reserved_macro_cannot_be_set_through_any_profile_flag_form(self):
        for flags in (['-DDECOMP_COMPARE=1'], ['-D','DECOMP_COMPARE=1'], ['-U','DECOMP_COMPARE'],
                      ['-Wp,-DDECOMP_COMPARE=1']):
            with self.subTest(flags=flags),self.assertRaisesRegex(ValueError,'reserved global'):
                sb.compile_unit({'flags':flags},None,None,None,[])


if __name__=='__main__':unittest.main()
