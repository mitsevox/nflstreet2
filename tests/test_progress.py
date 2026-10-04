import hashlib
import json
import shutil
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
                         "functions": [{"symbol": "fn_80003104", "address": "0x80003104", "size": 8}],
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

    def test_read_only_data_after_code_counts_in_its_code_section_without_functions(self):
        self.write_source()
        follower = {"section": ".rodata", "placement": ".init", "start": "0x8000310C", "end": "0x80003110",
                    "follows": ".text"}
        manifest_path = self.root / "config/GN7E69/units.json"
        manifest = json.loads(manifest_path.read_text())
        manifest["units"][0]["sections"].insert(1, follower)
        manifest_path.write_text(json.dumps(manifest))
        self.source_report["manifest_sha256"] = hashlib.sha256(manifest_path.read_bytes()).hexdigest()
        unit = self.source_report["units"][0]
        unit["sections"].insert(1, dict(follower, kind="code", linked=4, matched=4, status="matched"))
        self.source_report["totals"]["code"] = {"linked": 12, "matched": 12}
        self.save()
        (self.root / "config/GN7E69/evidence.tsv").write_text(
            "kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
            "data\t0x8000310C\t0x80003110\tdata_8000310C\ttarget\texact\texact\tfixture\n")
        data = progress.report(self.binary, "a" * 40, self.report_path)
        self.assertEqual(data["measures"]["code"], {"total": 16, "linked": 12, "matched": 12})
        # A report must carry the manifest's configuration, and no function may sit in the data.
        del unit["sections"][1]["follows"]
        self.save()
        with self.assertRaisesRegex(ValueError, "differ from the unit manifest"):
            progress.report(self.binary, "a" * 40, self.report_path)
        unit["sections"][1]["follows"] = ".text"
        unit["functions"].append({"symbol": "fn_8000310C", "address": "0x8000310C", "size": 4})
        self.save()
        with self.assertRaisesRegex(ValueError, "invalid compiler function coverage"):
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
            "functions": [{"symbol": "fn_80003104", "address": "0x80003104", "size": 8}],
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

    def add_follower(self):
        """Configure read-only data after the unit's code over 0x8000310C-0x80003110."""
        follower = {"section": ".rodata", "placement": ".init", "start": "0x8000310C", "end": "0x80003110",
                    "follows": ".text"}
        manifest_path = self.root / "config/GN7E69/units.json"
        manifest = json.loads(manifest_path.read_text())
        manifest["units"][0]["sections"].insert(1, follower)
        manifest_path.write_text(json.dumps(manifest))
        self.source_report["manifest_sha256"] = progress.digest(manifest_path)
        self.source_report["units"][0]["sections"].insert(
            1, dict(follower, kind="code", linked=4, matched=4, status="matched"))
        self.source_report["totals"]["code"] = {"linked": 12, "matched": 12}
        self.save()

    def without_evidence_function(self, start):
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if not line.startswith(f"function\t{start}\t")) + "\n")

    def test_data_after_code_cannot_cover_a_function_candidate(self):
        # Review of PR #78: instruction words compiled as data after code claimed matched code.
        self.write_inventory()
        self.without_evidence_function("0x8000310C")
        self.add_data_row()
        self.add_follower()
        with self.assertRaisesRegex(ValueError, "overlaps function candidate fn_8000310C"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_data_after_code_cannot_cover_an_evidence_function(self):
        self.write_inventory()
        self.add_data_row()
        self.add_follower()
        for analysis in (self.analysis, None):
            with self.subTest(analysis=analysis), \
                    self.assertRaisesRegex(ValueError, "overlaps function fn_8000310C 0x8000310C-0x80003110"):
                progress.report(self.binary, "a" * 40, self.report_path, analysis)

    def add_data_row(self, edges="exact\texact"):
        with (self.root / "config/GN7E69/evidence.tsv").open("a") as file:
            file.write(f"data\t0x8000310C\t0x80003110\tdata_8000310C\ttarget\t{edges}\tfixture\n")

    def single_candidate_inventory(self):
        """Inventory and evidence with no candidate or function over 0x8000310C-0x80003110."""
        self.write_inventory()
        self.without_evidence_function("0x8000310C")
        symbols = self.analysis / "symbols.txt"
        symbols.write_text("fn_80003104 = .text:0x80003104; // type:function size:0x8\n")
        self.add_follower()
        summary = json.loads((self.analysis / "summary.json").read_text())
        summary.update(candidate_counts={"function": 1}, symbols_sha256=progress.digest(symbols),
                       inputs=progress.sdk_map.analysis_inputs(self.root))
        (self.analysis / "summary.json").write_text(json.dumps(summary))

    def test_data_after_code_must_be_an_exact_evidence_data_block(self):
        # Hostile recheck of PR #78: code the inventory missed (no candidate, no evidence row)
        # must not be claimable as data after code.
        self.single_candidate_inventory()
        for analysis in (self.analysis, None):
            with self.subTest(analysis=analysis), \
                    self.assertRaisesRegex(ValueError, "does not equal an evidence data row with exact edges"):
                progress.report(self.binary, "a" * 40, self.report_path, analysis)
        self.add_data_row("exact\tprovisional")
        with self.assertRaisesRegex(ValueError, "does not equal an evidence data row with exact edges"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.add_data_row()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.assertEqual(data["measures"]["code"], {"total": 16, "linked": 12, "matched": 12})
        self.assertEqual(data["functions"]["total"], 1)

    def test_counts_require_measured_code_and_function_name_evidence(self):
        self.write_inventory()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.assertEqual(data["functions"], {"total": 2, "exact": 1, "named": 1,
                                             "basis": "provisional-analysis"})
        data = progress.report(self.binary, "a" * 40, self.report_path)
        self.assertIsNone(data["functions"]["total"])

    def test_compiled_methods_and_generated_functions_require_names(self):
        for symbol in ("Update__8UIScreenFv", "I.src_game_UIScreen_cpp"):
            with self.subTest(symbol=symbol):
                self.write_inventory()
                self.source_report["units"][0]["functions"][0]["symbol"] = symbol
                self.save()
                path = self.root / "config/GN7E69/evidence.tsv"
                path.write_text("\n".join(line for line in path.read_text().splitlines()
                                           if "\tExample\t" not in line) + "\n")
                with self.assertRaisesRegex(ValueError, "missing curated name evidence"):
                    progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
                with path.open("a") as file:
                    file.write("name\t0x80003104\t-\tReviewedName\tinferred\t-\t-\tfixture\n")
                data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
                self.assertEqual(data["sections"][0]["children"][0]["name"], "ReviewedName")
                source = next(item for item in data["files"] if item.get("source") == "src/unit.c"
                              and item["kind"] == "code")
                self.assertEqual(source["children"][0]["name"], "ReviewedName")
                import decomp_report
                exported = decomp_report.objdiff_report(data)
                unit = next(item for item in exported["units"] if item["name"] == "src/unit.c")
                self.assertEqual(unit["functions"][0]["name"], "ReviewedName")
                shutil.rmtree(self.analysis)

    def test_neutral_compiler_function_can_remain_explicitly_unknown(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if "\tExample\t" not in line) + "\n")
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.assertEqual(data["sections"][0]["children"][0]["name"], "fn_80003104")
        self.assertEqual(data["functions"]["named"], 0)

    def test_mangled_address_methods_remain_unknown_in_both_exports(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if "\tExample\t" not in line) + "\n")
        self.source_report["units"][0]["functions"][0]["symbol"] = "fn_80003104__8UIScreenFv"
        self.save()
        data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
        self.assertEqual(data["functions"]["named"], 0)
        import decomp_report
        exported = decomp_report.objdiff_report(data)
        unit = next(item for item in exported["units"] if item["name"] == "src/unit.c")
        self.assertEqual(unit["functions"][0]["name"], "fn_80003104")

    def test_inherited_virtual_slots_remain_unknown_in_both_exports(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if "\tExample\t" not in line) + "\n")
        import decomp_report
        for symbol in ("vfn_04", "vfn_04__10DebugGroup", "vfn_04__11SystemGroup",
                       "vfn_01__14Class_802A6B60", "vfn_10__14Class_802A6BB0"):
            with self.subTest(symbol=symbol):
                self.source_report["units"][0]["functions"][0]["symbol"] = symbol
                self.save()
                data = progress.report(self.binary, "a" * 40, self.report_path, self.analysis)
                self.assertEqual(data["functions"]["named"], 0)
                self.assertEqual(data["sections"][0]["children"][0]["name"], "fn_80003104")
                exported = decomp_report.objdiff_report(data)
                unit = next(item for item in exported["units"] if item["name"] == "src/unit.c")
                self.assertEqual(unit["functions"][0]["name"], "fn_80003104")

    def test_inherited_method_address_labels_still_require_correct_placement(self):
        self.write_source()
        self.source_report["units"][0]["functions"][0]["symbol"] = "fn_80003108__11SystemGroup"
        self.save()
        with self.assertRaisesRegex(ValueError, "misplaced neutral function"):
            progress.report(self.binary, "a" * 40, self.report_path)

    def test_descriptive_virtual_slot_suffix_still_requires_name_evidence(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if "\tExample\t" not in line) + "\n")
        for symbol in ("vfn_04Meaning__11SystemGroup", "vfn_1__11SystemGroup", "vfn_100__11SystemGroup"):
            with self.subTest(symbol=symbol):
                self.source_report["units"][0]["functions"][0]["symbol"] = symbol
                self.save()
                with self.assertRaisesRegex(ValueError, "missing curated name evidence"):
                    progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_plain_and_mangled_neutral_addresses_must_match_placement(self):
        self.write_source()
        for symbol in ("fn_80003108", "fn_80003108__8UIScreenFv"):
            with self.subTest(symbol=symbol):
                self.source_report["units"][0]["functions"][0]["symbol"] = symbol
                self.save()
                with self.assertRaisesRegex(ValueError, "misplaced neutral function"):
                    progress.report(self.binary, "a" * 40, self.report_path)

    def test_address_suffix_does_not_make_descriptive_methods_neutral(self):
        self.write_inventory()
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("\n".join(line for line in path.read_text().splitlines()
                                   if "\tExample\t" not in line) + "\n")
        self.source_report["units"][0]["functions"][0]["symbol"] = "Method_80003104__8UIScreenFv"
        self.save()
        with self.assertRaisesRegex(ValueError, "missing curated name evidence"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

    def test_missing_malformed_or_out_of_bounds_compiler_coverage_fails(self):
        cases = (None, [], [{"symbol": "Example", "address": "0x8000310C", "size": 4}],
                 [{"symbol": "Example", "address": "0x80003104", "size": 12}],
                 [{"symbol": "Example", "address": "0x80003104", "size": 0}], [{}])
        for functions in cases:
            with self.subTest(functions=functions):
                self.write_source()
                self.source_report["units"][0]["functions"] = functions
                self.save()
                with self.assertRaisesRegex(ValueError, "compiler function coverage"):
                    progress.report(self.binary, "a" * 40, self.report_path)

    def test_compiler_functions_must_have_candidate_bounds_and_inventory(self):
        self.write_inventory()
        function = self.source_report["units"][0]["functions"][0]
        function["symbol"] = "Example"
        self.save()
        with self.assertRaisesRegex(ValueError, "require a verified function inventory"):
            progress.report(self.binary, "a" * 40, self.report_path)
        function["size"] = 4
        self.save()
        with self.assertRaisesRegex(ValueError, "inconsistent bounds"):
            progress.report(self.binary, "a" * 40, self.report_path, self.analysis)

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




class FileInventoryTests(ProgressBase):
    def test_named_files_include_descriptive_names_and_count_siblings_once(self):
        def item(name, kind="code"):
            return {"name": name, "kind": kind, "size": 8, "matched": 0}
        rows = [item("src/game/cu_80003100.cpp"), item("src/game/Player.cpp"),
                item("src/game/Player.cpp", "data"), item("Candidate / src/game/Player.cpp"),
                item("Candidate / src/game/Camera.cpp"),
                item("Unmapped / Code section 1"), item("sdk/unassigned/8023ED18")]
        self.assertEqual(progress.file_inventory(rows),
                         {"total": 3, "exact": 0, "named": 2, "basis": "mapped-file-inventory"})

    def test_exact_files_require_boundaries_and_all_matched_siblings_not_linked(self):
        path = self.root / "config/GN7E69/evidence.tsv"
        path.write_text("kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
                        "unit\t0x80003100\t0x80003108\tsrc/game/Player.cpp\ttarget\texact\texact\tfixture\n")
        rows = [{"name": "src/game/Player.cpp", "source": "src/game/Player.cpp", "kind": "code",
                 "size": 8, "matched": 8, "linked": 0,
                 "mapped_extents": [{"start": "0x80003100", "end": "0x80003108"}]},
                {"name": "src/game/Player.cpp", "kind": "data", "size": 4, "matched": 4, "linked": 0}]
        self.assertEqual(progress.file_inventory(rows)["exact"], 1)
        rows[1]["matched"] = 3
        self.assertEqual(progress.file_inventory(rows)["exact"], 0)
        rows[1]["matched"] = 4
        path.write_text(path.read_text().replace("exact\texact", "provisional\texact"))
        self.assertEqual(progress.file_inventory(rows)["exact"], 0)

    def test_data_only_file_can_be_exact_with_confirmed_unit_boundaries(self):
        (self.root / "config/GN7E69/evidence.tsv").write_text(
            "kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
            "unit\t0x80004100\t0x80004108\tsrc/game/Tables.c\ttarget\texact\texact\tfixture\n")
        rows = [{"name": "src/game/Tables.c", "kind": "data", "size": 8, "matched": 8,
                 "mapped_extents": [{"start": "0x80004100", "end": "0x80004108"}]}]
        self.assertEqual(progress.file_inventory(rows)["exact"], 1)


if __name__ == "__main__":
    unittest.main()
