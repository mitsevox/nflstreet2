import hashlib
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import progress


class ProgressBase(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        config = self.root / "config/GN7E69"
        config.mkdir(parents=True)
        binary = bytearray(0x120)
        for offset, value in ((0, 0x100), (0x48, 0x80003100), (0x90, 16),
                              (0x1C, 0x110), (0x64, 0x80004100), (0xAC, 16),
                              (0xD8, 0x80005000), (0xDC, 32)):
            struct.pack_into(">I", binary, offset, value)
        self.binary = bytes(binary)
        (config / "baseline.json").write_text(json.dumps({
            "size": len(binary), "sha1": hashlib.sha1(binary).hexdigest()}))
        self.scope = patch.object(progress, "ROOT", self.root)
        self.scope.start()
        self.addCleanup(self.scope.stop)


class ProgressTests(ProgressBase):
    def test_original_objects_never_count_as_recovered_source(self):
        data = progress.report(self.binary, "a" * 40)
        self.assertEqual(data["measures"], {
            "code": {"total": 16, "linked": 0, "matched": 0},
            "data": {"total": 48, "linked": 0, "matched": 0}})
        self.assertEqual(len(data["sections"]), 3)
        self.assertEqual(data["basis"], "executable-sections")
        self.assertNotIn(str(self.root), json.dumps(data))

    def test_wrong_target_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "verified target"):
            progress.report(self.binary[:-1] + b"x", "a" * 40)

    def test_loaded_bytes_inside_bss_are_not_counted_twice(self):
        binary = bytearray(self.binary)
        struct.pack_into(">I", binary, 0x64, 0x80005008)
        binary = bytes(binary)
        (self.root / "config/GN7E69/baseline.json").write_text(json.dumps({
            "size": len(binary), "sha1": hashlib.sha1(binary).hexdigest()}))
        data = progress.report(binary, "a" * 40)
        self.assertEqual(data["measures"]["data"]["total"], 32)
        self.assertEqual([s["size"] for s in data["sections"] if
                          s["name"].startswith("Uninitialized")], [8, 8])

    def test_source_addition_requires_measured_exporter(self):
        (self.root / "src").mkdir()
        (self.root / "src/unit.cpp").write_text("void example() {}")
        with self.assertRaisesRegex(ValueError, "measured source-build"):
            progress.report(self.binary, "a" * 40)

    def test_revision_must_identify_a_commit(self):
        with self.assertRaisesRegex(ValueError, "full commit"):
            progress.report(self.binary, "main")


class SourceReportTests(ProgressBase):
    """Linked and matched bytes come only from a current, complete source-build report."""

    def write_source(self, units=True):
        manifest = {"schema": 1, "units": [{"source": "src/unit.c"}] if units else []}
        manifest_path = self.root / "config/GN7E69/units.json"
        manifest_path.write_text(json.dumps(manifest))
        self.report_path = self.root / "build/source/report.json"
        self.report_path.parent.mkdir(parents=True, exist_ok=True)
        measured = []
        if units:
            (self.root / "src").mkdir(exist_ok=True)
            (self.root / "include").mkdir(exist_ok=True)
            source = self.root / "src/unit.c"
            header = self.root / "include/unit.h"
            source.write_text('#include "unit.h"\n')
            header.write_text("void Unit(void);\n")
            digest = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
            measured = [{"source": "src/unit.c", "source_sha256": digest(source), "status": "matched",
                         "dependencies": {"include/unit.h": digest(header), "src/unit.c": digest(source)},
                         "sections": [
                             {"kind": "code", "start": "0x80003104", "end": "0x8000310C",
                              "linked": 8, "matched": 8, "status": "matched"},
                             {"kind": "data", "start": "0x80005008", "end": "0x8000500C",
                              "linked": 4, "matched": 4, "status": "matched"}]}]
        self.source_report = {
            "schema": 1, "target": "GN7E69", "target_sha1": hashlib.sha1(self.binary).hexdigest(),
            "manifest_sha256": hashlib.sha256(manifest_path.read_bytes()).hexdigest(),
            "complete": "identical", "output_sha1": hashlib.sha1(self.binary).hexdigest(),
            "units": measured,
            "totals": {"code": {"linked": 8 if units else 0, "matched": 8 if units else 0},
                       "data": {"linked": 4 if units else 0, "matched": 4 if units else 0}}}
        self.save()

    def save(self):
        self.report_path.write_text(json.dumps(self.source_report))

    def test_zero_unit_report_keeps_zero_progress(self):
        self.write_source(units=False)
        data = progress.report(self.binary, "a" * 40, self.report_path)
        self.assertEqual(data["measures"]["code"], {"total": 16, "linked": 0, "matched": 0})
        self.assertEqual(data["source"], {"units": 0, "report": "measured"})

    def test_measured_unit_counts_in_its_sections(self):
        self.write_source()
        data = progress.report(self.binary, "a" * 40, self.report_path)
        self.assertEqual(data["measures"], {
            "code": {"total": 16, "linked": 8, "matched": 8},
            "data": {"total": 48, "linked": 4, "matched": 4}})
        by_name = {s["name"]: (s["linked"], s["matched"]) for s in data["sections"]}
        self.assertEqual(by_name, {"Code section 1": (8, 8), "Data section 1": (0, 0),
                                   "Uninitialized data 1": (4, 4)})

    def test_configured_units_require_a_report(self):
        self.write_source()
        self.report_path.unlink()
        with self.assertRaisesRegex(ValueError, "measured source-build"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_unmeasured_source_file_is_rejected(self):
        self.write_source()
        (self.root / "src/extra.c").write_text("int extra;\n")
        with self.assertRaisesRegex(ValueError, "not measured"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_stale_source_or_dependency_is_rejected(self):
        for path in ("src/unit.c", "include/unit.h"):
            with self.subTest(path=path):
                self.write_source()
                (self.root / path).write_text("changed\n")
                with self.assertRaisesRegex(ValueError, "stale"):
                    progress.report(self.binary, "a" * 40, self.report_path)

    def test_incomplete_or_foreign_reports_are_rejected(self):
        cases = (("complete", "mismatch", "complete target"),
                 ("target_sha1", "0" * 40, "different target"),
                 ("manifest_sha256", "0" * 64, "different unit manifest"))
        for field, value, message in cases:
            with self.subTest(field=field):
                self.write_source()
                self.source_report[field] = value
                self.save()
                with self.assertRaisesRegex(ValueError, message):
                    progress.report(self.binary, "a" * 40, self.report_path)

    def test_unverified_or_inconsistent_ranges_are_rejected(self):
        self.write_source()
        self.source_report["units"][0]["sections"][0]["status"] = "range-identical"
        self.save()
        with self.assertRaisesRegex(ValueError, "unverified"):
            progress.report(self.binary, "a" * 40, self.report_path)
        self.write_source()
        self.source_report["totals"]["code"]["matched"] = 16
        self.save()
        with self.assertRaisesRegex(ValueError, "inconsistent"):
            progress.report(self.binary, "a" * 40, self.report_path)
        self.write_source()
        self.source_report["units"][0]["sections"][0].update(start="0x80003200", end="0x80003208")
        self.save()
        with self.assertRaisesRegex(ValueError, "outside the executable"):
            progress.report(self.binary, "a" * 40, self.report_path)


if __name__ == "__main__":
    unittest.main()
