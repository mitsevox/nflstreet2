import hashlib
import json
from pathlib import Path
import sys
import subprocess
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import inventory_cache
import sdk_map


class InventoryCacheTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        for name in (*sdk_map.BASE_INPUTS, 'config/GN7E69/baseline.json', 'tools/compiler-tools.json'):
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('{}')
        self.original = b'target fixture'
        self.target = {'size': len(self.original), 'sha1': hashlib.sha1(self.original).hexdigest()}
        (self.root / 'config/GN7E69/baseline.json').write_text(json.dumps(self.target))
        self.cache = self.root / 'build/analysis'
        self.cache.mkdir(parents=True)
        (self.cache / 'symbols.txt').write_text('fixture symbols')
        self.summary = {'target_sha1': self.target['sha1'], 'complete_relink': 'identical',
                        'inventory': 'provisional', 'inputs': sdk_map.analysis_inputs(self.root),
                        'cache_inputs': inventory_cache.inputs(self.root, 'pinned-container'),
                        'symbols_sha256': hashlib.sha256((self.cache / 'symbols.txt').read_bytes()).hexdigest()}
        self.write_summary()

    def write_summary(self):
        (self.cache / 'summary.json').write_text(json.dumps(self.summary))

    def reusable(self, **kw):
        return inventory_cache.reusable(self.root, self.cache, kw.get('original', self.original),
                                        kw.get('context', 'pinned-container'))

    def test_only_identical_generation_inputs_and_environment_hit(self):
        self.assertTrue(self.reusable())
        self.assertFalse(self.reusable(context='other-container'))
        self.assertFalse(self.reusable(original=b'wrong target'))
        self.summary['cache_inputs']['python'] = [0, 0]
        self.write_summary()
        self.assertFalse(self.reusable())

    def test_changed_generation_code_and_seed_inputs_rebuild(self):
        for name in (*sdk_map.BASE_INPUTS, 'tools/compiler-tools.json', 'config/GN7E69/baseline.json'):
            with self.subTest(name=name):
                path = self.root / name
                old = path.read_bytes()
                path.write_bytes(old + b' ')
                self.assertFalse(self.reusable())
                path.write_bytes(old)
        (self.root / 'tools/new_helper.py').write_text('new analysis helper')
        self.assertFalse(self.reusable())

    def test_source_only_change_does_not_invalidate_inventory(self):
        (self.root / 'src').mkdir()
        (self.root / 'src/function.c').write_text('changed source')
        self.assertTrue(self.reusable())

    def test_missing_corrupt_or_unverified_receipts_rebuild(self):
        for value in ([], {}, {'complete_relink': 'mismatch'}, {'inventory': 'accepted'}):
            (self.cache / 'summary.json').write_text(json.dumps(value))
            self.assertFalse(self.reusable())
        (self.cache / 'summary.json').write_text('{broken')
        self.assertFalse(self.reusable())
        (self.cache / 'summary.json').unlink()
        self.assertFalse(self.reusable())
        self.write_summary()
        (self.cache / 'symbols.txt').write_text('corrupted')
        self.assertFalse(self.reusable())
        (self.cache / 'symbols.txt').unlink()
        self.assertFalse(self.reusable())

    def test_changed_mapping_and_unit_configuration_rebuild(self):
        for name in ('sdk.json', 'units.json'):
            (self.root / 'config/GN7E69' / name).write_text('{}')
        self.summary['inputs'] = sdk_map.analysis_inputs(self.root)
        self.summary['cache_inputs'] = inventory_cache.inputs(self.root, 'pinned-container')
        self.write_summary()
        self.assertTrue(self.reusable())
        for name in ('sdk.json', 'units.json'):
            path = self.root / 'config/GN7E69' / name
            path.write_text('{"changed": true}')
            self.assertFalse(self.reusable())
            path.write_text('{}')


class LiveInventoryCacheTests(unittest.TestCase):
    def test_generated_inventory_reuses_without_modifying_metadata(self):
        root = Path(__file__).resolve().parents[1]
        directory = root / 'build/analysis'
        original = Path('/orig/main.dol')
        if not original.exists() or not (directory / 'summary.json').exists():
            self.skipTest('Hosted inventory step supplies the target and generated receipt')
        before = {name: (directory / name).read_bytes() for name in ('summary.json', 'symbols.txt')}
        receipt = json.loads(before['summary.json'])
        result = subprocess.run([sys.executable, str(root / 'tools/analyze.py'),
                                 '--original', str(original), '--reuse-inventory',
                                 '--cache-context', receipt['cache_inputs']['context']],
                                capture_output=True, text=True, check=True, timeout=30)
        self.assertIn('Reused verified inventory metadata', result.stdout)
        self.assertEqual(before, {name: (directory / name).read_bytes() for name in before})


if __name__ == '__main__':
    unittest.main()
