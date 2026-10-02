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
        self.assertEqual(data["complete_units"], 0)
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
        self.assertEqual(m["total_units"], 4)
        self.assertEqual(m["complete_units"], 0)
        for kind in ("code", "data"):
            for field in ("total", "matched", "complete"):
                key = f"{field}_{kind}"
                self.assertEqual(int(m[key]), sum(int(u["measures"][key]) for u in data["units"]))

    def test_source_unit_combines_code_and_data_without_claiming_completion(self):
        test_progress.SourceReportTests.write_source(self)
        data = decomp_report.objdiff_report(
            decomp_report.progress.report(self.binary, "a" * 40, self.report_path))
        sourced = [unit for unit in data["units"] if "source_path" in unit["metadata"]]
        self.assertEqual(len(sourced), 1)
        unit = sourced[0]
        self.assertEqual(unit["name"], "src/unit.c")
        self.assertEqual(unit["metadata"], {"source_path": "src/unit.c", "complete": False,
                                            "auto_generated": False})
        self.assertEqual(unit["measures"]["total_code"], "8")
        self.assertEqual(unit["measures"]["total_data"], "4")
        self.assertEqual(unit["measures"]["matched_code_percent"], 100)
        self.assertEqual(unit["measures"]["complete_units"], 0)
        unknown = [unit for unit in data["units"] if unit["metadata"]["auto_generated"]]
        self.assertEqual(sum(int(unit["measures"]["total_code"]) for unit in unknown), 8)
        self.assertEqual(sum(int(unit["measures"]["total_data"]) for unit in unknown), 44)

    def test_function_drilldown_preserves_source_and_unmapped_names(self):
        test_progress.FunctionInventoryTests.write_inventory(self)
        data = decomp_report.objdiff_report(
            decomp_report.progress.report(self.binary, "a" * 40, self.report_path, self.analysis))
        source = next(unit for unit in data["units"] if unit["name"] == "src/unit.c")
        self.assertEqual(source["functions"], [{"name": "Example", "size": "8",
                         "fuzzy_match_percent": 100,
                         "metadata": {"virtual_address": str(0x80003104)}}])
        unknown = next(unit for unit in data["units"] if unit["name"] == "Unmapped / Code section 1")
        self.assertEqual(unknown["functions"][0]["name"], "fn_8000310C")
        self.assertEqual(unknown["functions"][0]["fuzzy_match_percent"], 0)

    save = test_progress.SourceReportTests.save
    write_source = test_progress.SourceReportTests.write_source


if __name__ == "__main__":
    unittest.main()
