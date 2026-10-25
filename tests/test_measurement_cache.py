import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import function_compare
import source_build as sb
from unittest.mock import patch


class MeasurementCacheTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        self.cache = self.root / 'build/matching-cache'

    def measured(self, index, data=b'linked bytes'):
        folder = self.root / 'build/matching/candidates' / str(index)
        (folder / '0').mkdir(parents=True, exist_ok=True)
        (folder / '0/resolved.elf').write_bytes(data)
        path = (folder / '0/resolved.elf').relative_to(self.root).as_posix()
        receipt = {'source': 'src/a.c', 'entries': [{'symbol': 'f', 'start': '0x80000000', 'matched': 4}],
                   'pairs': [{'path': path, 'sha256': 'digest', 'symbol': 'f'}]}
        return folder, receipt

    def audit(self, key, index=0, data=b'linked bytes'):
        cache = function_compare.MeasurementCache(self.cache, 'audit')
        self.assertIsNone(cache.restore(key, self.root, self.root))
        folder, receipt = self.measured(index, data)
        cache.record(key, folder, self.root, receipt)
        return cache.finish(), receipt

    def test_reuse_restores_entries_and_outputs_at_the_current_unit_index(self):
        _, receipt = self.audit('k')
        use = function_compare.MeasurementCache(self.cache, 'use')
        folder = self.root / 'build/matching/candidates/7'
        folder.mkdir(parents=True)
        restored = use.restore('k', folder, self.root)
        self.assertEqual(restored['entries'], receipt['entries'])
        self.assertEqual(restored['pairs'], [dict(receipt['pairs'][0], path='build/matching/candidates/7/0/resolved.elf')])
        self.assertEqual((folder / '0/resolved.elf').read_bytes(), b'linked bytes')
        self.assertIsNone(use.restore('other', folder, self.root))
        self.assertEqual(use.finish(), {'mode': 'use', 'hits': 1, 'misses': 1, 'audited': 0})

    def test_use_mode_never_writes_the_cache(self):
        use = function_compare.MeasurementCache(self.cache, 'use')
        folder, receipt = self.measured(0)
        use.record('k', folder, self.root, receipt)
        use.finish()
        self.assertFalse(self.cache.exists())

    def test_audit_accepts_identical_and_rejects_any_disagreement(self):
        self.audit('k')
        stats, _ = self.audit('k', index=3)
        self.assertEqual(stats['audited'], 1)
        with self.assertRaisesRegex(ValueError, 'disagrees with a fresh measurement'):
            self.audit('k', data=b'other bytes')
        cache = function_compare.MeasurementCache(self.cache, 'audit')
        folder, receipt = self.measured(0)
        receipt['entries'][0]['matched'] = 0
        with self.assertRaisesRegex(ValueError, 'disagrees with a fresh measurement'):
            cache.record('k', folder, self.root, receipt)

    def test_audit_replaces_the_cache_with_only_fresh_measurements(self):
        self.audit('old')
        self.audit('new')
        self.assertEqual(sorted(p.name for p in self.cache.iterdir()), ['new'])

    def test_cached_paths_cannot_leave_the_unit_folder(self):
        self.audit('k')
        record = self.cache / 'k/measurement.json'
        for path in ('../escape.elf', '/etc/passwd'):
            with self.subTest(path=path):
                data = json.loads(record.read_text())
                data['pairs'][0]['path'] = path
                record.write_text(json.dumps(data))
                use = function_compare.MeasurementCache(self.cache, 'use')
                with self.assertRaisesRegex(ValueError, 'Invalid cached comparison output path'):
                    use.restore('k', self.root / 'build/matching/candidates/0', self.root)

    def test_keys_bind_every_measurement_input(self):
        cache = function_compare.MeasurementCache(self.cache, 'use')
        material = {'object': 'a', 'references': [('f', 1, False)], 'unit': {'flags': ['-O2']}}
        self.assertEqual(cache.key(material), cache.key(json.loads(json.dumps(material))))
        for field, value in (('object', 'b'), ('references', [('f', 2, False)]), ('unit', {'flags': ['-O1']})):
            with self.subTest(field=field):
                self.assertNotEqual(cache.key(material), cache.key(dict(material, **{field: value})))

    def test_invalid_mode_fails_closed(self):
        with self.assertRaisesRegex(ValueError, 'use or audit'):
            function_compare.MeasurementCache(self.cache, 'write')


class CompileCacheTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name).resolve()
        for path in sb.CompileCache.TOOLS:
            (self.root / path).parent.mkdir(parents=True, exist_ok=True)
            (self.root / path).write_text(path)
        (self.root / 'src/game').mkdir(parents=True)
        (self.root / 'include').mkdir()
        (self.root / 'src/game/a.c').write_text('#include "types.h"\n')
        (self.root / 'include/types.h').write_text('typedef int s32;\n')
        (self.root / 'build/obj').mkdir(parents=True)
        patcher = patch.object(sb, 'ROOT', self.root)
        patcher.start()
        self.addCleanup(patcher.stop)

    def unit(self):
        return {'source': 'src/game/a.c', 'path': self.root / 'src/game/a.c', 'compiler': 'prodg',
                'flags': ['-O2'], 'object': self.root / 'build/obj/a.o', 'depfile': self.root / 'build/obj/a.d'}

    def compile(self, mode, data=b'object'):
        cache = sb.CompileCache(self.root / 'build/cache/objects', mode)
        unit = self.unit()
        key = cache.key(unit, [self.root / 'include'], self.root, str(unit['path']), False)
        if cache.restore(key, unit):
            return cache, True
        unit['object'].write_bytes(data)
        unit['depfile'].write_text('a.o: src/game/a.c include/types.h\n')
        unit['dependencies'] = sb.dependencies(unit['depfile'], self.root)
        cache.record(key, unit)
        cache.finish()
        return cache, False

    def test_reuse_needs_unchanged_dependencies_and_no_new_same_named_file(self):
        self.compile('audit')
        self.assertTrue(self.compile('use')[1])
        (self.root / 'src/game/Types.h').write_text('typedef long s32;\n')
        self.assertFalse(self.compile('use')[1])
        (self.root / 'src/game/Types.h').unlink()
        self.assertTrue(self.compile('use')[1])
        (self.root / 'include/types.h').write_text('typedef short s32;\n')
        self.assertFalse(self.compile('use')[1])

    def test_source_flags_and_tools_are_part_of_the_key(self):
        cache = sb.CompileCache(self.root / 'build/cache/objects', 'use')
        unit = self.unit()
        key = cache.key(unit, [self.root / 'include'], self.root, str(unit['path']), False)
        self.assertNotEqual(key, cache.key(unit, [self.root / 'include'], self.root, str(unit['path']), True))
        self.assertNotEqual(key, cache.key(dict(unit, flags=['-O1']), [self.root / 'include'], self.root,
                                           str(unit['path']), False))
        (self.root / 'src/game/a.c').write_text('#include "types.h"\nint x;\n')
        self.assertNotEqual(key, cache.key(unit, [self.root / 'include'], self.root, str(unit['path']), False))
        (self.root / 'tools/prodg_cc.py').write_text('changed')
        other = sb.CompileCache(self.root / 'build/cache/objects', 'use')
        self.assertNotEqual(cache.key(unit, [self.root / 'include'], self.root, str(unit['path']), False),
                            other.key(unit, [self.root / 'include'], self.root, str(unit['path']), False))

    def test_audit_rejects_a_cached_object_that_differs_from_a_fresh_compile(self):
        self.compile('audit')
        self.assertEqual(self.compile('audit')[0].audited, 1)
        with self.assertRaisesRegex(ValueError, 'disagrees with a fresh compile'):
            self.compile('audit', b'different object')

    def test_use_mode_never_writes_the_cache(self):
        self.compile('use')
        self.assertFalse((self.root / 'build/cache/objects').exists())


if __name__ == '__main__':
    unittest.main()
