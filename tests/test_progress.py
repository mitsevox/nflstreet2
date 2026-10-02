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
        configured = [{"section": ".text", "placement": ".init", "start": "0x80003104", "end": "0x8000310C"},
                      {"section": ".bss", "placement": ".bss", "start": "0x80005008", "end": "0x8000500C"}]
        manifest = {"schema": 1, "units": [{"source": "src/unit.c", "sections": configured}] if units else []}
        manifest_path = self.root / "config/GN7E69/units.json"
        manifest_path.write_text(json.dumps(manifest))
        self.report_path = self.root / "build/source/report.json"
        self.report_path.parent.mkdir(parents=True, exist_ok=True)
        (self.root / "tools").mkdir(exist_ok=True)
        for path in progress.TRUSTED_TOOLS:
            if path.startswith("tools/"):
                (self.root / path).write_text(f"synthetic {path}\n")
        tools = {path: hashlib.sha256((self.root / path).read_bytes()).hexdigest()
                 if (self.root / path).is_file() else None for path in progress.TRUSTED_TOOLS}
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
                             dict(configured[0], kind="code", linked=8, matched=8, status="matched"),
                             dict(configured[1], kind="data", linked=4, matched=4, status="matched")]}]
        self.source_report = {
            "schema": 1, "target": "GN7E69", "target_sha1": hashlib.sha1(self.binary).hexdigest(),
            "manifest_sha256": hashlib.sha256(manifest_path.read_bytes()).hexdigest(),
            "tools": tools,
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

    def test_report_ranges_must_equal_the_manifest(self):
        # Moving a range away from its configured placement (review E10).
        self.write_source()
        self.source_report["units"][0]["sections"][0].update(start="0x80005010", end="0x80005018")
        self.save()
        with self.assertRaisesRegex(ValueError, "differ from the unit manifest"):
            progress.report(self.binary, "a" * 40, self.report_path)
        # Duplicating a range with adjusted totals (review E9).
        self.write_source()
        unit = self.source_report["units"][0]
        unit["sections"].append(dict(unit["sections"][0]))
        self.source_report["totals"]["code"] = {"linked": 16, "matched": 16}
        self.save()
        with self.assertRaisesRegex(ValueError, "differ from the unit manifest"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_overlapping_ranges_are_rejected(self):
        self.write_source()
        manifest_path = self.root / "config/GN7E69/units.json"
        manifest = json.loads(manifest_path.read_text())
        second = dict(manifest["units"][0], source="src/second.c")
        second["sections"] = [dict(manifest["units"][0]["sections"][0])]
        manifest["units"].append(second)
        manifest_path.write_text(json.dumps(manifest))
        (self.root / "src/second.c").write_text("int second;\n")
        digest = hashlib.sha256((self.root / "src/second.c").read_bytes()).hexdigest()
        self.source_report["units"].append({
            "source": "src/second.c", "source_sha256": digest, "status": "matched",
            "dependencies": {"src/second.c": digest},
            "sections": [dict(self.source_report["units"][0]["sections"][0])]})
        self.source_report["totals"]["code"] = {"linked": 16, "matched": 16}
        self.source_report["manifest_sha256"] = hashlib.sha256(manifest_path.read_bytes()).hexdigest()
        self.save()
        with self.assertRaisesRegex(ValueError, "overlap"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_report_is_bound_to_the_build_tooling(self):
        # Changing the build tool after the report was written (review E11).
        self.write_source()
        (self.root / "tools/source_build.py").write_text("modified\n")
        with self.assertRaisesRegex(ValueError, "different build tooling"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_trusted_tool_lists_agree(self):
        sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
        import source_build
        self.assertEqual(progress.TRUSTED_TOOLS, source_build.TRUSTED_TOOLS)


class FunctionInventoryTests(ProgressBase):
    write_source = SourceReportTests.write_source
    save = SourceReportTests.save
    def write_inventory(self):
        self.write_source()
        for path in progress.sdk_map.BASE_INPUTS:
            (self.root / path).write_text("inventory input")
        # Refresh the source report's tool hashes after changing shared inputs.
        self.source_report["tools"] = {path: progress.digest(self.root / path)
                                       if (self.root / path).is_file() else None
                                       for path in progress.TRUSTED_TOOLS}
        self.save()
        self.analysis = self.root / "build/analysis"
        self.analysis.mkdir(parents=True)
        (self.analysis / "symbols.txt").write_text(
            "fn_80003104 = .text:0x80003104; // type:function size:0x8\n"
            "fn_8000310C = .text:0x8000310C; // type:function size:0x4\n")
        summary = {"target_sha1": hashlib.sha1(self.binary).hexdigest(),
                   "complete_relink": "identical", "inventory": "provisional",
                   "candidate_counts": {"function": 2},
                   "symbols_sha256": progress.digest(self.analysis / "symbols.txt"),
                   "inputs": progress.sdk_map.analysis_inputs(self.root)}
        (self.analysis / "summary.json").write_text(json.dumps(summary))
        (self.root / "config/GN7E69/evidence.tsv").write_text(
            "kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
            "function\t0x80003104\t0x8000310C\tfn_80003104\ttarget\texact\texact\tfixture\n"
            "name\t0x80003104\t-\tExample\trelated\t-\t-\tfixture\n"
            "name\t0x80003104\t-\tExample\trelated\t-\t-\tduplicate\n"
            "function\t0x8000310C\t0x80003110\tfn_8000310C\tinferred\tprovisional\topen\tfixture\n"
            "name\t0x80005008\t-\tDataName\trelated\t-\t-\tfixture\n")

    def test_counts_require_measured_code_and_function_name_evidence(self):
        self.write_inventory()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.assertEqual(data["functions"], {"total": 2, "exact": 1, "named": 1,
                                             "basis": "provisional-analysis"})
        data = progress.report(self.binary, "a" * 40, self.report_path)
        self.assertIsNone(data["functions"]["total"])

    def test_stale_inventory_is_rejected(self):
        self.write_inventory()
        with (self.analysis / "symbols.txt").open("a") as file:
            file.write("modified")
        with self.assertRaisesRegex(ValueError, "stale or unverified"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_overlapping_evidence_is_rejected_before_counting(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        with path.open("a") as file:
            file.write("function\t0x8000310C\t0x80003110\tfn_8000310C\ttarget\texact\texact\tfixture\n")
        path.write_text(path.read_text().replace("0x80003104\t0x8000310C", "0x80003104\t0x80003110"))
        with self.assertRaisesRegex(ValueError, "overlap"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_overlapping_candidates_are_rejected(self):
        self.write_inventory()
        symbols = self.analysis / "symbols.txt"
        symbols.write_text(symbols.read_text().replace("size:0x8", "size:0xC"))
        summary = self.analysis / "summary.json"
        data = json.loads(summary.read_text())
        data["symbols_sha256"] = progress.digest(symbols)
        summary.write_text(json.dumps(data))
        with self.assertRaisesRegex(ValueError, "candidates overlap"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_code_section_opens_matched_and_unmatched_functions_directly(self):
        self.write_inventory()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        functions = [item for item in data["sections"][0]["children"] if "address" in item]
        self.assertEqual([(item["name"], item["matched"]) for item in functions],
                         [("Example", 8), ("fn_8000310C", 0)])
        self.assertTrue(all("children" not in item for item in functions))

    def test_map_children_preserve_all_byte_counts(self):
        self.write_inventory()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        def check(items):
            for item in items:
                if "children" in item:
                    for field in ("size", "linked", "matched"):
                        self.assertEqual(sum(child[field] for child in item["children"]), item[field])
                    check(item["children"])
        check(data["sections"])
        function = data["sections"][0]["children"][0]
        self.assertEqual(function["name"], "Example")
        self.assertNotIn(str(self.root), json.dumps(data))


class FileMapTests(ProgressBase):
    write_source = SourceReportTests.write_source
    save = SourceReportTests.save
    write_inventory = FunctionInventoryTests.write_inventory

    def test_mapped_unreconstructed_bytes_never_gain_source_credit(self):
        self.write_inventory()
        ownership = [{"name": "src/unit.c", "source": "src/unit.c", "sections": [
            {"section": ".init", "start": "0x80003100", "end": "0x80003110"}]}]
        sections = [{"name": "Code", "kind": "code", "address": "0x80003100", "size": 16,
                     "linked": 8, "matched": 8}]
        functions = [{"name": "Candidate", "address": "0x80003100", "size": 16}]
        files = progress.file_map(sections, self.report_path, functions, ownership)
        self.assertEqual(len(files), 1)
        self.assertEqual((files[0]["size"], files[0]["linked"], files[0]["matched"]), (16, 8, 8))
        self.assertFalse(files[0]["complete"])
        self.assertEqual(files[0]["scope"], "mapped-ranges")
        self.assertEqual(files[0]["children"][0]["matched"], 8)

    def test_zero_source_file_ownership_is_visible_with_zero_progress(self):
        sections = [{"name": "Code", "kind": "code", "address": "0x80003100", "size": 16,
                     "linked": 0, "matched": 0}]
        ownership = [{"name": "src/dolphin/os/OS.c", "source": "src/dolphin/os/OS.c",
                      "sections": [{"section": ".init", "start": "0x80003100", "end": "0x80003108"}]},
                     {"name": "sdk/unassigned/80003108", "source": None,
                      "sections": [{"section": ".init", "start": "0x80003108", "end": "0x80003110"}]}]
        files = progress.file_map(sections, None, [], ownership)
        self.assertEqual(len(files), 2)
        self.assertEqual(files[0]["source"], "src/dolphin/os/OS.c")
        self.assertNotIn("source", files[1])
        self.assertTrue(files[1]["auto_generated"])
        self.assertTrue(all(item["matched"] == item["linked"] == 0 for item in files))

    def test_mapping_cannot_reassign_or_cut_through_verified_source(self):
        self.write_inventory()
        sections = [{"name": "Code", "kind": "code", "address": "0x80003100", "size": 16,
                     "linked": 8, "matched": 8}]
        for source, end in (("src/other.c", "0x80003110"), ("src/unit.c", "0x80003108")):
            with self.subTest(source=source, end=end):
                ownership = [{"name": source, "source": source, "sections": [
                    {"section": ".init", "start": "0x80003100", "end": end}]}]
                with self.assertRaisesRegex(ValueError, "conflicts"):
                    progress.file_map(sections, self.report_path, [], ownership)
    def test_file_map_groups_measured_functions_and_data(self):
        self.write_inventory()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        source = [item for item in data["files"] if item.get("source") == "src/unit.c"]
        self.assertEqual([(item["kind"], item["size"]) for item in source], [("code", 8), ("data", 4)])
        self.assertTrue(all(item["complete"] is False for item in source))
        self.assertTrue(all(item["boundary"] == "provisional" for item in source))
        self.assertEqual(source[0]["children"][0]["name"], "Example")
        self.assertEqual(source[0]["children"][0]["source"], "src/unit.c")
        unknown = next(item for item in data["files"] if item["name"] == "Unmapped / Code section 1")
        self.assertEqual(unknown["size"], 8)
        self.assertEqual(unknown["matched"], 0)
        unknown_function = next(child for child in unknown["children"] if child.get("type") == "function")
        self.assertEqual(unknown_function["name"], "fn_8000310C")
        self.assertNotIn("source", unknown_function)
        for kind in ("code", "data"):
            for field, measure in (("size", "total"), ("linked", "linked"), ("matched", "matched")):
                self.assertEqual(sum(item[field] for item in data["files"] if item["kind"] == kind),
                                 data["measures"][kind][measure])
        for item in data["files"]:
            for field in ("size", "linked", "matched"):
                self.assertEqual(sum(child[field] for child in item["children"]), item[field])

    def test_crossing_candidates_are_partitioned_without_false_ownership(self):
        self.write_inventory()
        sections = [{"name": "Code", "kind": "code", "address": "0x80003100", "size": 16,
                     "linked": 8, "matched": 8}]
        functions = [{"name": "Candidate", "kind": "code", "address": "0x80003100", "size": 16,
                      "linked": 8, "matched": 8}]
        files = progress.file_map(sections, self.report_path, functions)
        source = next(item for item in files if item.get("source"))
        self.assertEqual(source["children"][0]["type"], "function-fragment")
        self.assertEqual(source["children"][0]["size"], 8)
        unknown = next(item for item in files if item.get("auto_generated"))
        self.assertEqual([child["size"] for child in unknown["children"]], [4, 4])
        self.assertTrue(all(child["matched"] == 0 for child in unknown["children"]))
        self.assertEqual(sum(child["size"] for item in files for child in item["children"]), 16)

    def test_disjoint_ranges_of_one_file_combine(self):
        self.write_inventory()
        unit = self.source_report["units"][0]
        unit["sections"] = [dict(unit["sections"][0], start="0x80003100", end="0x80003104"),
                            dict(unit["sections"][0], start="0x8000310C", end="0x80003110")]
        self.save()
        sections = [{"name": "Code", "kind": "code", "address": "0x80003100", "size": 16,
                     "linked": 8, "matched": 8}]
        files = progress.file_map(sections, self.report_path, [])
        source = [item for item in files if item.get("source")]
        self.assertEqual(len(source), 1)
        self.assertEqual(source[0]["size"], 8)
        self.assertEqual(len(source[0]["children"]), 2)


if __name__ == "__main__":
    unittest.main()
