import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import sdk_map


class SDKMapTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'config/GN7E69').mkdir(parents=True)
        self.sha1 = hashlib.sha1(b'target').hexdigest()
        (self.root / 'config/GN7E69/baseline.json').write_text(json.dumps({'sha1': self.sha1}))
        self.map = {'schema': 1, 'target_sha1': self.sha1,
                    'coverage': [{'section': '.text', 'start': '0x80001000', 'end': '0x80001020'}],
                    'units': [self.unit('src/dolphin/os/OS.c', '0x80001000', '0x80001010'),
                              self.unit('sdk/unassigned/80001010', '0x80001010', '0x80001020', False)]}
        self.sections = [{'name': '.text', 'start': 0x80001000, 'end': 0x80001020}]

    def unit(self, name, start, end, source=True):
        return {'name': name, 'source': name if source else None, 'library': 'OS',
                'evidence': 'Target references and independently checked file edges.',
                'sections': [{'section': '.text', 'start': start, 'end': end,
                              'start_boundary': 'provisional', 'end_boundary': 'provisional',
                              'evidence': 'Function-consistent target ranges.'}]}

    def save(self):
        (self.root / sdk_map.MAP_PATH).write_text(json.dumps(self.map))

    def load(self):
        self.save()
        return sdk_map.load(self.root, self.sections)

    def test_missing_map_preserves_old_baseline(self):
        self.assertEqual(sdk_map.load(self.root), [])

    def test_partition_and_neutral_owner_do_not_claim_source(self):
        units = self.load()
        self.assertIsNone(units[1]['source'])
        self.assertIn('.text start:0x80001000 end:0x80001010', sdk_map.split_text(units))

    def test_target_mismatch_is_rejected(self):
        self.map['target_sha1'] = '0' * 40
        with self.assertRaisesRegex(ValueError, 'different target'):
            self.load()

    def test_overlap_and_gap_are_rejected(self):
        original = copy.deepcopy(self.map)
        for start, message in [('0x8000100C', 'overlap'), ('0x80001014', 'gap')]:
            with self.subTest(start=start):
                self.map = copy.deepcopy(original)
                self.map['units'][1]['sections'][0]['start'] = start
                with self.assertRaisesRegex(ValueError, message):
                    self.load()

    def test_instruction_and_section_edges_are_enforced(self):
        for end, message in [('0x80001011', 'instruction'), ('0x80001024', 'outside')]:
            with self.subTest(end=end):
                self.map['units'][1]['sections'][0]['end'] = end
                with self.assertRaisesRegex(ValueError, message):
                    self.load()

    def test_unsafe_names_and_unbound_source_are_rejected(self):
        for name in ['../OS.c', '/src/dolphin/os/OS.c', 'src/dolphin/os/OS.c;command']:
            with self.subTest(name=name):
                self.map['units'][0]['name'] = name
                with self.assertRaisesRegex(ValueError, 'safe relative'):
                    self.load()
        self.map['units'][0]['name'] = 'src/dolphin/os/OS.c'
        self.map['units'][0]['source'] = 'src/dolphin/os/Other.c'
        with self.assertRaisesRegex(ValueError, 'source ownership'):
            self.load()

    def test_data_seeds_cannot_resize_code_or_use_truthy_strings(self):
        extent = self.map['units'][0]['sections'][0]
        for value in [True, 'false', 1]:
            with self.subTest(value=value):
                extent['object_seed'] = value
                with self.assertRaisesRegex(ValueError, 'boolean data'):
                    self.load()
        extent['section'] = '.data3'
        extent['object_seed'] = True
        self.map['coverage'] = []
        self.sections.append({'name': '.data3', 'start': 0x80001000, 'end': 0x80001010})
        self.assertEqual(len(self.load()), 2)

    def test_section_names_cannot_inject_split_directives(self):
        self.map['units'][0]['sections'][0]['section'] = '.text\nmalicious:'
        with self.assertRaisesRegex(ValueError, 'section identifiers'):
            self.load()

    def test_separated_file_globals_use_private_fragments_without_claiming_holes(self):
        unit = copy.deepcopy(self.map['units'][0])
        unit['sections'] += [dict(unit['sections'][0], section='.sbss', start='0x80002000', end='0x80002004'),
                             dict(unit['sections'][0], section='.sbss', start='0x80002008', end='0x8000200C')]
        parts = sdk_map.object_units([unit])
        self.assertEqual(len(parts), 2)
        self.assertEqual([part['source'] for part in parts], [unit['source']] * 2)
        self.assertEqual([len(part['sections']) for part in parts], [2, 1])
        self.assertEqual(sum(int(e['end'], 16) - int(e['start'], 16)
                             for part in parts for e in part['sections']), 24)
        self.assertNotEqual(parts[0]['name'], parts[1]['name'])

    def test_private_fragment_names_cannot_collide(self):
        unit = copy.deepcopy(self.map['units'][0])
        unit['sections'].append(dict(unit['sections'][0], start='0x80001030', end='0x80001040'))
        other = copy.deepcopy(self.map['units'][1])
        other['name'] = 'src/dolphin/os/OS.__part001.c'
        with self.assertRaisesRegex(ValueError, 'collide'):
            sdk_map.object_units([unit, other])

    def test_analysis_hashes_bind_map_seed_manifest_and_tool(self):
        self.save()
        for path in sdk_map.BASE_INPUTS + ('tools/sdk_map.py', 'config/GN7E69/units.json'):
            target = self.root / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(path)
        before = sdk_map.analysis_inputs(self.root)
        for path in (sdk_map.MAP_PATH, 'tools/sdk_map.py', 'config/GN7E69/units.json'):
            target = self.root / path
            old = target.read_text()
            target.write_text(old + '\n')
            self.assertNotEqual(before[path], sdk_map.analysis_inputs(self.root)[path])
            target.write_text(old)


if __name__ == '__main__':
    unittest.main()
