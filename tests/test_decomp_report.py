import json
from pathlib import Path
import subprocess
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import decomp_report
from test_progress import ProgressBase
import test_progress


class DecompReportTests(ProgressBase):
    def test_original_objects_have_no_source_credit(self):
        data = decomp_report.objdiff_report(decomp_report.progress.report(self.binary, "a" * 40))
        self.assertEqual(data["version"], 2)
        self.assertEqual(data["measures"]["total_code"], "16")
        self.assertEqual(data["measures"]["total_data"], "48")
        self.assertEqual(data["measures"]["matched_code"], "0")
        self.assertEqual(data["measures"]["complete_data"], "0")
        self.assertEqual(data["measures"]["complete_units"], 0)
        self.assertEqual(data["measures"]["fuzzy_match_percent"], 0)
        self.assertNotIn("total_functions", data["measures"])
        self.assertTrue(all(u["metadata"]["auto_generated"] for u in data["units"]))
        self.assertNotIn(str(self.root), json.dumps(data))

    def test_empty_kind_has_finite_percentages(self):
        data = decomp_report.measures([{"kind": "code", "size": 16, "linked": 16, "matched": 16}])
        self.assertEqual(data["matched_data_percent"], 0)
        self.assertEqual(data["complete_units"], 1)
        self.assertEqual(data["matched_code_percent"], 100)

    def test_cli_failure_removes_stale_report(self):
        output = self.root / "report.json"
        output.write_text("stale")
        binary = self.root / "bad.dol"
        binary.write_bytes(b"invalid")
        script = Path(decomp_report.__file__)
        result = subprocess.run([sys.executable, str(script), "--dol", str(binary),
                                 "--revision", "a" * 40, "--output", str(output)],
                                capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse(output.exists())


class MeasuredDecompReportTests(ProgressBase):
    def test_verified_bytes_and_unmapped_remainder_are_preserved(self):
        # Reuse the measured-build fixture, including its source/dependency hashes.
        test_progress.SourceReportTests.write_source(self)
        data = decomp_report.objdiff_report(
            decomp_report.progress.report(self.binary, "a" * 40, self.report_path))
        m = data["measures"]
        self.assertEqual((m["total_code"], m["matched_code"], m["complete_code"]), ("16", "8", "8"))
        self.assertEqual((m["total_data"], m["matched_data"], m["complete_data"]), ("48", "4", "4"))
        self.assertEqual(m["matched_code_percent"], 50)
        self.assertAlmostEqual(m["matched_data_percent"], 100 * 4 / 48)
        self.assertEqual(m["fuzzy_match_percent"], 100 * 12 / 64)
        self.assertEqual(m["total_units"], 3)
        self.assertEqual(m["complete_units"], 0)
        for kind in ("code", "data"):
            for field in ("total", "matched", "complete"):
                key = f"{field}_{kind}"
                self.assertEqual(int(m[key]), sum(int(u["measures"][key]) for u in data["units"]))

    save = test_progress.SourceReportTests.save


if __name__ == "__main__":
    unittest.main()
