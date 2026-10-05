import copy
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools'))
import activity
import export_progress
import progress
from test_progress import ProgressBase
import test_progress


@unittest.skipUnless(shutil.which('git'), 'Contributor integration requires host Git')
class ReceiptFixture(ProgressBase):
    save = test_progress.SourceReportTests.save
    write_source = test_progress.SourceReportTests.write_source

    def setUp(self):
        super().setUp()
        activity.clear_cache()
        test_progress.FunctionInventoryTests.write_inventory(self)
        subprocess.run(['git', 'init', '-q'], cwd=self.root, check=True)
        subprocess.run(['git', 'add', 'src/unit.c'], cwd=self.root, check=True)
        subprocess.run(['git', '-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
                        'commit', '-qm', 'Source'], cwd=self.root, check=True)
        def git(*args):
            return subprocess.check_output(['git', *args], cwd=self.root, text=True).strip()
        self.revision = git('rev-parse', 'HEAD')
        self.target = hashlib.sha1(self.binary).hexdigest()
        self.dol = self.report_path.parent/'main.dol'
        self.dol.write_bytes(self.binary)
        config = self.root/'config/GN7E69'
        (config/'comparisons.json').write_text(json.dumps({'schema':1, 'units':[]}))
        (config/'history.json').write_text(json.dumps(
            {'schema':1, 'target':'GN7E69', 'target_sha1':self.target, 'snapshots':[]}))
        self.ledger = {'schema':1, 'target':'GN7E69', 'contributors':{'alice':{'id':1}},
            'entries':[{'source':'src/unit.c', 'contributors':['alice'], 'functions':['0x80003104'],
                'provenance':{'pull_request':1, 'merged_via':1, 'commit':self.revision,
                              'introduced_blob':git('rev-parse', 'HEAD:src/unit.c')}}]}
        self.ledger_path = config/'contributors.json'
        self.ledger_path.write_text(json.dumps(self.ledger))
        scope = patch.object(export_progress, 'ROOT', self.root)
        scope.start(); self.addCleanup(scope.stop)


class ExportTests(ReceiptFixture):
    def export(self, **options):
        return export_progress.export(self.dol, self.revision, self.report_path,
                                      self.analysis, None, **options)

    def test_both_maps_and_exact_credits_share_one_validated_measurement(self):
        # A stale on-disk site cannot replace the current measured inputs.
        stale = self.root/'build/site/progress.json'
        stale.parent.mkdir(parents=True); stale.write_text('{"functions":{"exact":999}}')
        with patch.object(progress, 'report', wraps=progress.report) as report:
            site, decomp, credits = self.export(squash_base=self.revision)
        self.assertEqual(report.call_count, 1)
        self.assertEqual(site['revision'], self.revision)
        self.assertEqual(site['functions']['exact'], 1)
        self.assertEqual(credits['credited_functions'], 1)
        self.assertEqual(credits['contributors'][0]['login'], 'alice')
        for kind in ('code', 'data'):
            self.assertEqual(int(decomp['measures']['matched_'+kind]), site['measures'][kind]['matched'])

    def test_stale_source_inventory_comparison_and_missing_credit_fail_before_export(self):
        for key, value in (('manifest_sha256', '0'*64), ('tools', {})):
            original = copy.deepcopy(self.source_report)
            self.source_report[key] = value; self.save()
            with self.subTest(key=key), self.assertRaises(ValueError):
                self.export()
            self.source_report = original; self.save()
        symbols = self.analysis/'symbols.txt'
        original = symbols.read_text(); symbols.write_text(original+'tampered\n')
        with self.assertRaisesRegex(ValueError, 'stale or unverified'):
            self.export()
        symbols.write_text(original)
        comparison = self.root/'comparison.json'
        comparison.write_text('{"schema":1,"entries":[]}')
        with self.assertRaises(ValueError):
            export_progress.export(self.dol, self.revision, self.report_path, self.analysis, comparison)
        self.ledger['entries'] = []; self.ledger_path.write_text(json.dumps(self.ledger))
        with self.assertRaisesRegex(ValueError, 'Unattributed exact function'):
            self.export()

    def test_main_appends_history_and_requires_previous_deployment(self):
        with self.assertRaisesRegex(ValueError, 'restored prior'):
            self.export(append=True)
        subprocess.run(['git', 'update-ref', 'refs/remotes/origin/main', self.revision],
                       cwd=self.root, check=True)
        previous = {'schema':1, 'target':'GN7E69', 'target_sha1':self.target, 'snapshots':[]}
        site, _, credits = self.export(previous=previous, append=True)
        self.assertEqual(credits['snapshots'][0]['revision'], self.revision)
        self.assertEqual(credits['snapshots'][0]['built_at'], site['built_at'])


if __name__ == '__main__':
    unittest.main()
