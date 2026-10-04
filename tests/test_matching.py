import copy
import hashlib
import json
from pathlib import Path
import sys
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
            {'source':'nonmatching/test.c','kind':'code','start':'0x80000004','end':'0x80000008','matched':0,'fuzzy':3},
            {'source':'nonmatching/test.c','kind':'code','start':'0x80000008','end':'0x80000010','matched':8,'fuzzy':8}]}

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
            identical = matching.score_pair(tool,b'ABCDEFGH',b'ABCDEFGH',[],'data',directory)
            self.assertEqual(identical, {'matched':8,'fuzzy':8})


class CandidateReceiptTests(unittest.TestCase):
    def test_nonempty_candidate_load_uses_evidenced_function_bounds(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = 'nonmatching/test.c'
            unit = {'source':source, 'sections':[{'placement':'.text','start':'0x80000000','end':'0x80000008'}]}
            manifest = {'units':[unit]}
            for folder in ('nonmatching','config/GN7E69','tools','build/matching/compiled'):
                (root/folder).mkdir(parents=True, exist_ok=True)
            (root/source).write_text('int function(void) { return 7; }')
            (root/matching.CONFIG).write_text(json.dumps({'schema':1,'units':[unit]}))
            (root/'tools/matching-tools.json').write_text(json.dumps({'objdiff':{'version':'v3.8.2'}}))
            compiled = root/'build/matching/compiled'
            (compiled/'main.dol').write_bytes(b'compiled output')
            source_binding = {'sha256':matching.source_build.sha256(root/source), 'dependencies':{}}
            receipt = {'manifest_sha256':hashlib.sha256(json.dumps(manifest).encode()).hexdigest(),
                       'target_sha1':'target', 'tools':{},
                       'output_sha1':matching.baseline.digest(compiled/'main.dol','sha1'),
                       'units':[{'source':source,'source_sha256':source_binding['sha256'],'dependencies':{},
                                 'functions':[{'address':'0x80000000','size':8}]}]}
            (compiled/'report.json').write_text(json.dumps(receipt))
            data = {'schema':1,'target_sha1':'target','inputs':{},'sources':{source:source_binding},
                    'build_receipt':{'path':'build/matching/compiled/report.json',
                                     'sha256':matching.source_build.sha256(compiled/'report.json')},
                    'objdiff':'v3.8.2', 'entries':[{'source':source,'type':'function','kind':'code',
                       'start':'0x80000000','end':'0x80000008','matched':0,'fuzzy':5.6}]}
            report = root/'measurement.json'
            report.write_text(json.dumps(data))
            with patch.object(matching,'ROOT',root), patch.object(matching,'bindings',return_value={}), \
                    patch.object(matching,'manifest',return_value=manifest), \
                    patch.object(matching.source_build,'TRUSTED_TOOLS',()), \
                    patch.object(matching.source_build,'function_extents',return_value=[(0x80000000,0x80000008,'function')]):
                self.assertEqual(matching.load(report,{'sha1':'target'}),data)
                with patch.object(matching.source_build,'function_extents',return_value=[]):
                    with self.assertRaisesRegex(ValueError,'evidenced boundaries'):
                        matching.load(report,{'sha1':'target'})


class ReportValidationTests(unittest.TestCase):
    def test_rejects_corrupt_or_stale_measurements(self):
        report = matching.ROOT / 'build/matching/report.json'
        if not report.is_file():
            self.skipTest('Measurement integration step creates the bound report')
        payload = json.loads(report.read_text())
        target = {'sha1': payload['target_sha1']}
        matching.load(report, target)
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
                        matching.load(path, target)


if __name__ == '__main__':
    unittest.main()
