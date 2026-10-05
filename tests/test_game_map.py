import csv
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import game_map
import progress
import decomp_report
import check_progress_maps


class GameMapTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.section = {'name': '.text', 'address': '0x00001000', 'size': 64,
                        'kind': 'code', 'linked': 0, 'matched': 0}

    def write(self, ranges):
        path = self.root / game_map.EVIDENCE_PATH
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open('w') as f:
            writer = csv.writer(f, delimiter='\t')
            writer.writerow(['kind', 'start', 'end', 'subject', 'origin',
                             'start_boundary', 'end_boundary', 'evidence'])
            for name, start, end in ranges:
                writer.writerow(['unit', start, end, name, 'inferred', 'open', 'provisional', 'candidate'])

    def test_overlap_stays_unassigned_and_sdk_wins(self):
        self.write([('cu_a', '0x1000', '0x1030'), ('cu_b', '0x1020', '0x1040')])
        sdk = [{'name': 'sdk', 'sections': [{'start': '0x1008', 'end': '0x1010'}]}]
        units = game_map.load(self.root, [self.section], sdk)
        self.assertEqual(units[0]['sections'], [
            {'start': '0x00001000', 'end': '0x00001008', 'kind': 'code'},
            {'start': '0x00001010', 'end': '0x00001020', 'kind': 'code'}])
        self.assertEqual(units[1]['sections'][0]['start'], '0x00001030')

    def test_outside_target_and_duplicate_claims_fail(self):
        for rows in [[('cu_a', '0x1000', '0x1044')],
                     [('cu_a', '0x1000', '0x1010'), ('cu_a', '0x1010', '0x1020')]]:
            self.write(rows)
            with self.assertRaises(ValueError):
                game_map.load(self.root, [self.section])

    def test_both_exports_change_when_mapping_is_added_without_source_credit(self):
        before = progress.file_map([self.section], None, [])
        self.write([('cu_a', '0x1000', '0x1020')])
        after = progress.file_map([self.section], None, [], game_map.load(self.root, [self.section]))
        self.assertEqual(sum(f['size'] for f in before), sum(f['size'] for f in after))
        self.assertEqual([f['name'] for f in after], ['Candidate / cu_a', 'Unmapped / .text'])
        self.assertEqual(after[0]['scope'], 'candidate-ranges')
        exported = decomp_report.objdiff_report({'files': after})
        self.assertIn('Candidate / cu_a', [u['name'] for u in exported['units']])
        self.assertEqual(exported['measures']['matched_code'], '0')
        self.assertEqual(exported['measures']['complete_code'], '0')

    def test_measured_source_precedence_preserves_credit(self):
        self.write([('cu_a', '0x1000', '0x1040')])
        units = [{'source': 'src/real.c', 'sections': [
            {'start': '0x1010', 'end': '0x1020', 'kind': 'code'}]}]
        report = self.root / 'report.json'
        report.write_text(json.dumps({'units': units}))
        candidates = game_map.load(self.root, [self.section], units)
        self.section["linked"] = self.section["matched"] = 16
        mapped = progress.file_map([self.section], report, [], candidates)
        self.assertEqual(sum(u['matched'] for u in mapped), 16)
        self.assertEqual(next(u for u in mapped if u.get('source'))['name'], 'src/real.c')

    def test_report_consumes_mapping_without_an_inventory(self):
        from test_progress import ProgressBase
        fixture = ProgressBase()
        fixture.setUp()
        self.addCleanup(fixture.doCleanups)
        self.root = fixture.root
        self.write([('cu_a', '0x80003100', '0x80003110')])
        data = progress.report(fixture.binary, 'a' * 40)
        self.assertIn('Candidate / cu_a', [f['name'] for f in data['files']])
        self.assertEqual(data['measures']['code']['matched'], 0)

    def test_publish_guard_rejects_missing_map_and_invented_credit(self):
        self.write([('cu_a', '0x1000', '0x1020')])
        files = progress.file_map([self.section], None, [], game_map.load(self.root, [self.section]))
        site = {'files': files, 'sections': [self.section], 'measures': {
            'code': {'total': 64, 'matched': 0, 'linked': 0},
            'data': {'total': 0, 'matched': 0, 'linked': 0}}}
        decomp = decomp_report.objdiff_report(site)
        self.assertEqual(check_progress_maps.verify(self.root, site, decomp, []), 1)
        stale = {**decomp, 'units': []}
        with self.assertRaisesRegex(ValueError, 'differs'):
            check_progress_maps.verify(self.root, site, stale, [])
        with self.assertRaisesRegex(ValueError, 'omits'):
            check_progress_maps.verify(self.root, {**site, 'files': []}, decomp, [])
        files[0]['matched'] = 4
        with self.assertRaisesRegex(ValueError, 'source credit'):
            check_progress_maps.verify(self.root, site, decomp, [])

    def test_authenticated_comparison_map_preserves_measured_partial_credit(self):
        self.write([('cu_a', '0x1000', '0x1020')])
        files = progress.file_map([self.section], None, [], game_map.load(self.root, [self.section]))
        files[0]['matched'] = 4
        site = {'files': files, 'sections': [self.section], 'measures': {
            'code': {'total': 64, 'matched': 4, 'linked': 0},
            'data': {'total': 0, 'matched': 0, 'linked': 0}}}
        decomp = decomp_report.objdiff_report(site)
        with self.assertRaisesRegex(ValueError, 'source credit'):
            check_progress_maps.verify(self.root, site, decomp, [])
        self.assertEqual(check_progress_maps.verify(self.root, site, decomp, [],
                         authenticated_comparisons=True), 1)
        files[0]['source'] = 'src/invented.c'
        with self.assertRaisesRegex(ValueError, 'source credit'):
            check_progress_maps.verify(self.root, site, decomp, [], authenticated_comparisons=True)

    def test_publish_guard_rejects_same_size_boundary_move(self):
        self.write([('cu_a', '0x1000', '0x1020')])
        files = progress.file_map([self.section], None, [], game_map.load(self.root, [self.section]))
        site = {'files': files, 'sections': [self.section], 'measures': {
            'code': {'total': 64, 'matched': 0, 'linked': 0},
            'data': {'total': 0, 'matched': 0, 'linked': 0}}}
        decomp = decomp_report.objdiff_report(site)
        self.write([('cu_a', '0x1020', '0x1040')])
        with self.assertRaisesRegex(ValueError, 'omits or changes'):
            check_progress_maps.verify(self.root, site, decomp, [])

    def test_publish_guard_checks_sdk_boundaries_too(self):
        sdk = [{'name': 'sdk/unit.c', 'sections': [
            {'start': '0x00001000', 'end': '0x00001020', 'kind': 'code'}]}]
        files = progress.file_map([self.section], None, [], sdk)
        site = {'files': files, 'sections': [self.section], 'measures': {
            'code': {'total': 64, 'matched': 0, 'linked': 0},
            'data': {'total': 0, 'matched': 0, 'linked': 0}}}
        decomp = decomp_report.objdiff_report(site)
        with patch.object(check_progress_maps.sdk_map, 'load', return_value=sdk):
            self.assertEqual(check_progress_maps.verify(self.root, site, decomp, []), 0)
            sdk[0]['sections'][0].update(start='0x00001020', end='0x00001040')
            with self.assertRaisesRegex(ValueError, 'omits or changes'):
                check_progress_maps.verify(self.root, site, decomp, [])
