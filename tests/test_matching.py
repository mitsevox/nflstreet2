import copy
import hashlib
import json
from pathlib import Path
import sys
import struct
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import matching
import decomp_report


class OverlayTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.root = Path(self.directory.name)
        (self.root / 'config/GN7E69').mkdir(parents=True)
        (self.root / 'config/GN7E69/units.json').write_text(json.dumps({'units': [{'source': 'accepted.c'}]}))
        (self.root/'config/GN7E69/evidence.tsv').write_text('kind\tstart\tend\tstart_boundary\tend_boundary\n')
        self.patch = patch.object(matching, 'ROOT', self.root)
        self.patch.start()
        self.addCleanup(self.patch.stop)
        self.addCleanup(self.directory.cleanup)

    def data(self):
        children = [{'name':'function','kind':'code','address':'0x80000000','size':8,'linked':4,'matched':4},
                    {'name':'padding','kind':'code','size':8,'linked':0,'matched':0,
                     'mapped_extents':[{'start':'0x80000008','end':'0x80000010'}]}]
        root = {'name':'unit','kind':'code','address':'0x80000000','size':16,'linked':4,'matched':4,
                'children': children}
        return {'sections':[copy.deepcopy(root)], 'files':[copy.deepcopy(root)],
                'functions':{'total':1,'exact':0}, 'measures':{'code':{'total':16,'linked':4,'matched':4},
                                                          'data':{'total':0,'linked':0,'matched':0}}}

    def measurement(self):
        return {'objdiff':'v3.8.2','entries':[
            {'source':'accepted.c','kind':'code','start':'0x80000000','end':'0x80000004','matched':4,'fuzzy':4},
            {'source':'src/test.c','kind':'code','start':'0x80000004','end':'0x80000008','matched':0,'fuzzy':3},
            {'source':'src/test.c','kind':'code','start':'0x80000008','end':'0x80000010','matched':8,'fuzzy':8}]}

    def test_partial_linked_and_residual_extents(self):
        result = matching.apply(self.data(), self.measurement())
        self.assertEqual(result['measures']['code'], {'total':16,'linked':4,'matched':12,'fuzzy':15})
        self.assertEqual(result['files'][0]['children'][0]['fuzzy'], 7)
        self.assertEqual(result['files'][0]['children'][1]['matched'], 8)

    def test_accepted_exact_function_count_keeps_evidence_gate(self):
        data = self.data()
        data['sections'][0]['children'][0].update(linked=8,matched=8)
        data['files'][0]['children'][0].update(linked=8,matched=8)
        result = matching.apply(data, {'objdiff':'v3.8.2','entries':[]})
        self.assertEqual(result['functions']['exact'],0)

    def test_exact_candidate_functions_require_exact_evidence_and_are_idempotent(self):
        data = self.data()
        for root in data['sections'] + data['files']:
            root['linked'] = root['matched'] = 0
            root['children'][0]['linked'] = root['children'][0]['matched'] = 0
        data['measures']['code'].update(linked=0,matched=0)
        measurement = self.measurement()
        measurement['entries'] = [e for e in measurement['entries'] if e['source'] != 'accepted.c']
        measurement['entries'][0].update(start='0x80000000',type='function',matched=8,fuzzy=8)
        result = matching.apply(data,measurement)
        self.assertEqual(result['functions']['exact'],0)
        (self.root/'config/GN7E69/evidence.tsv').write_text(
            'kind\tstart\tend\tstart_boundary\tend_boundary\n'
            'function\t0x80000000\t0x80000008\texact\texact\n')
        matching.apply(result,measurement)
        self.assertEqual(result['functions']['exact'],1)
        matching.apply(result,measurement)
        self.assertEqual(result['functions']['exact'],1)

    def test_candidate_identity_comes_from_full_registered_comparison_not_display_name(self):
        data=self.data()
        for root in data['files']+data['sections']:
            root['linked']=root['matched']=0
            root['children'][0].update(type='function', function_address='0x80000000',
                                       original_size=8, linked=0, matched=0)
        data['measures']['code'].update(linked=0,matched=0)
        measured={'objdiff':'v3.8.2','entries':[{'source':'src/test.c','type':'function',
            'kind':'code','start':'0x80000000','end':'0x80000008','matched':8,'fuzzy':8}]}
        result=matching.apply(data,measured)
        self.assertEqual(result['files'][0]['children'][0]['comparison_source'],'src/test.c')
        self.assertNotIn('source',result['files'][0]['children'][0])
        matching.apply(result,{'objdiff':'v3.8.2','entries':[]})
        self.assertNotIn('comparison_source', result['files'][0]['children'][0])

    def test_repeat_application_does_not_duplicate_credit(self):
        result = matching.apply(self.data(), self.measurement())
        first = copy.deepcopy(result)
        matching.apply(result, self.measurement())
        self.assertEqual(result, first)

    def test_scores_cannot_overflow_map(self):
        measurement = self.measurement()
        measurement['entries'].append(copy.deepcopy(measurement['entries'][-1]))
        with self.assertRaises(ValueError):
            matching.apply(self.data(), measurement)

    def test_both_exports_use_weighted_fuzzy_score(self):
        result = matching.apply(self.data(), self.measurement())
        report = decomp_report.objdiff_report(result)
        self.assertEqual(report['measures']['complete_code'], '4')
        self.assertEqual(report['measures']['matched_code'], '12')
        self.assertEqual(report['measures']['fuzzy_match_percent'], 93.75)


class ObjdiffTests(unittest.TestCase):
    def test_real_instruction_and_data_scores(self):
        tool = matching.ROOT / 'build/baseline/tools/objdiff'
        if not tool.is_file():
            self.skipTest('Pinned objdiff is installed by the matching measurement step')
        lock = json.loads((matching.ROOT/'tools/matching-tools.json').read_text())
        self.assertEqual(matching.source_build.sha256(tool), lock['objdiff'][matching.source_build.baseline_system()]['sha256'])
        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            score = matching.score_pair(tool,b'ABCDEFGH',b'ABCDXXXX',[],'data',directory)
            self.assertEqual(score, {'matched':0,'fuzzy':4.0})
            symbols = [{'name':'function','size':8,'value':0,'type':2,'shndx':1}]
            score = matching.score_pair(tool,bytes.fromhex('386000014e800020'),bytes.fromhex('386000024e800020'),symbols,'code',directory)
            self.assertEqual(score['matched'],0)
            self.assertGreater(score['fuzzy'],0)
            self.assertLess(score['fuzzy'],8)
            variable = matching.score_pair(tool, bytes.fromhex('38600001600000004e800020'),
                                           bytes.fromhex('386000014e800020'), symbols, 'code', directory)
            self.assertEqual(variable['matched'], 0)
            self.assertGreater(variable['fuzzy'], 0)
            self.assertLess(variable['fuzzy'], 12)
            identical = matching.score_pair(tool,b'ABCDEFGH',b'ABCDEFGH',[],'data',directory)
            self.assertEqual(identical, {'matched':8,'fuzzy':8})


class ReportValidationTests(unittest.TestCase):
    def test_rejects_corrupt_or_stale_measurements(self):
        report = matching.ROOT / 'build/matching/report.json'
        if not report.is_file():
            self.skipTest('Measurement integration step creates the bound report')
        payload = json.loads(report.read_text())
        target = {'sha1': payload['target_sha1']}
        original = (matching.ROOT/'build/source/main.dol').read_bytes()
        if payload.get('inputs') != matching.bindings():
            self.skipTest('Matching step regenerates receipts for this tooling revision')
        matching.load(report, target, original)
        mutations = []
        wrong_version = copy.deepcopy(payload)
        wrong_version['objdiff'] = 'untrusted'
        mutations.append(wrong_version)
        missing = copy.deepcopy(payload)
        missing['entries'].pop()
        mutations.append(missing)
        wrong_kind = copy.deepcopy(payload)
        wrong_kind['entries'][0]['kind'] = 'data' if wrong_kind['entries'][0]['kind'] == 'code' else 'code'
        mutations.append(wrong_kind)
        wrong_type = copy.deepcopy(payload)
        next(e for e in wrong_type['entries'] if e['type'] == 'function')['type'] = 'bytes'
        mutations.append(wrong_type)
        missing_dependencies = copy.deepcopy(payload)
        next(v for v in missing_dependencies['sources'].values() if v['dependencies'])['dependencies'] = {}
        mutations.append(missing_dependencies)
        wrong_score = copy.deepcopy(payload)
        wrong_score['entries'][0]['fuzzy'] = float('nan')
        mutations.append(wrong_score)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'report.json'
            for number, invalid in enumerate(mutations):
                with self.subTest(mutation=number):
                    path.write_text(json.dumps(invalid))
                    with self.assertRaises(ValueError):
                        matching.load(path, target, original)


if __name__ == '__main__':
    unittest.main()
