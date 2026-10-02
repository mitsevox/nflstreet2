"""Check source-unit placement, symbol resolution and fail-closed verification on synthetic data."""

import copy
import hashlib
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import source_build as sb


def synthetic_dol():
    """A tiny DOL: one code section, one data section and an uninitialized extent."""
    binary = bytearray(0x100)
    struct.pack_into(">I", binary, 0x00, 0x100)
    struct.pack_into(">I", binary, 0x48, 0x80003100)
    struct.pack_into(">I", binary, 0x90, 0x40)
    struct.pack_into(">I", binary, 0x1C, 0x140)
    struct.pack_into(">I", binary, 0x64, 0x80004000)
    struct.pack_into(">I", binary, 0xAC, 0x20)
    struct.pack_into(">II", binary, 0xD8, 0x80005000, 0x40)
    struct.pack_into(">I", binary, 0xE0, 0x80003100)
    binary += bytes(range(0x40)) + bytes(range(0x80, 0xA0))
    return bytes(binary)


TARGET = {"entry": "0x80003100", "sda_base": "0x80008000", "sda2_base": "0x80010000",
          "sections": {".init": "0x80003100", ".data2": "0x80004000", ".bss": "0x80005000"}}


def compiled(sections, symbols):
    """Read back a synthetic relocatable object built with the tool's own writer."""
    with tempfile.TemporaryDirectory() as temporary:
        path = Path(temporary) / "unit.o"
        sb.write_object(path, sections, symbols)
        return sb.read_elf(path.read_bytes())


def text(size, align=4):
    return {"name": ".text", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC | sb.SHF_EXECINSTR,
            "size": size, "align": align, "data": bytes(size)}


def rodata(size):
    return {"name": ".rodata", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC, "size": size,
            "align": 4, "data": bytes(size)}


class Fixture(unittest.TestCase):
    def setUp(self):
        self.binary = synthetic_dol()
        self.sections = sb.target_sections(self.binary, TARGET, {})
        self.manifest = {
            "schema": 1, "target": "GN7E69", "compiler": "3.9.3", "include_dirs": [],
            "profiles": {"library": {"flags": ["-O2"], "evidence": "library-level locator"}},
            "externals": {},
            "units": [{"source": "src/unit.c", "profile": "library", "evidence": "unit locator",
                       "sections": [{"section": ".text", "placement": ".init",
                                     "start": "0x80003110", "end": "0x80003118"},
                                    {"section": ".rodata", "placement": ".data2",
                                     "start": "0x80004008", "end": "0x8000400C"}]}]}

    def load(self, manifest=None):
        return sb.load_manifest(manifest or self.manifest, self.sections, "3.9.3")

    def plan(self, objects, manifest=None):
        units, externals, _ = self.load(manifest)
        return sb.plan(self.sections, units, objects, externals)


class TargetAndManifest(Fixture):
    def test_target_sections_follow_the_executable_header(self):
        names = [(s["name"], s["kind"], hex(s["start"]), hex(s["end"])) for s in self.sections]
        self.assertEqual(names, [(".init", "code", "0x80003100", "0x80003140"),
                                 (".data2", "data", "0x80004000", "0x80004020"),
                                 (".bss", "bss", "0x80005000", "0x80005040")])
        with self.assertRaisesRegex(ValueError, "missing"):
            sb.target_sections(self.binary, {"sections": {".init": "0x80003100", ".bss": "0x80005000"}}, {})

    def test_valid_manifest(self):
        units, externals, includes = self.load()
        self.assertEqual(units[0]["flags"], ["-O2"])
        self.assertEqual(externals, {})

    def test_flags_belong_to_an_evidenced_profile(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["flags"] = ["-O1"]
        with self.assertRaisesRegex(ValueError, "profile"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["profiles"]["library"]["evidence"] = " "
        with self.assertRaisesRegex(ValueError, "evidence"):
            self.load(manifest)
        for flags in (["-o", "x.o"], ["-Iinclude"], ["--wrapper", "x"]):
            manifest = copy.deepcopy(self.manifest)
            manifest["profiles"]["library"]["flags"] = flags
            with self.subTest(flags=flags), self.assertRaises(ValueError):
                self.load(manifest)

    def test_ranges_must_fit_and_not_overlap(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0]["end"] = "0x80003148"
        with self.assertRaisesRegex(ValueError, "outside"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        other = copy.deepcopy(manifest["units"][0])
        other["source"] = "src/other.c"
        other["sections"] = [{"section": ".text", "placement": ".init",
                              "start": "0x80003114", "end": "0x80003120"}]
        manifest["units"].append(other)
        with self.assertRaisesRegex(ValueError, "overlap"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0]["start"] = "0x8000311a"
        with self.assertRaisesRegex(ValueError, "0xXXXXXXXX"):
            self.load(manifest)

    def test_manifest_identity_and_paths(self):
        with self.assertRaisesRegex(ValueError, "pinned compiler"):
            sb.load_manifest(self.manifest, self.sections, "3.9.4")
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["source"] = "../outside.c"
        with self.assertRaisesRegex(ValueError, "relative repository path"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"fn_80003104": {"address": "0x80003104", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "non-neutral"):
            self.load(manifest)


class Placement(Fixture):
    def objects(self, text_size=8, rodata_size=4, symbols=None, extra=()):
        symbols = symbols if symbols is not None else [
            {"name": "Unit_Function", "value": 0, "shndx": 1, "type": 2},
            {"name": "fn_80003104", "value": 0, "shndx": 0},
            {"name": "lbl_80005010", "value": 0, "shndx": 0}]
        return {"src/unit.c": compiled([text(text_size), rodata(rodata_size), *extra], symbols)}

    def test_original_pieces_surround_units_and_define_externals(self):
        pieces, defined, resolved = self.plan(self.objects())
        layout = [(hex(p["start"]), hex(p["end"]), p.get("unit")) for p in pieces[".init"]]
        self.assertEqual(layout, [("0x80003100", "0x80003110", None),
                                  ("0x80003110", "0x80003118", "src/unit.c"),
                                  ("0x80003118", "0x80003140", None)])
        self.assertEqual(pieces[".init"][0]["symbols"], [{"name": "fn_80003104", "value": 4}])
        self.assertEqual(pieces[".bss"][0]["symbols"], [{"name": "lbl_80005010", "value": 0x10}])
        self.assertEqual(defined, {"Unit_Function": (0x80003110, "src/unit.c")})
        self.assertEqual(resolved, {"fn_80003104": 0x80003104, "lbl_80005010": 0x80005010})

    def test_compiled_sizes_must_equal_configured_ranges(self):
        with self.assertRaisesRegex(ValueError, "compiled .text is 0xc bytes"):
            self.plan(self.objects(text_size=12))
        with self.assertRaisesRegex(ValueError, "compiled .rodata"):
            self.plan(self.objects(rodata_size=8))

    def test_every_allocated_section_needs_a_range(self):
        data = {"name": ".data", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC | sb.SHF_WRITE,
                "size": 4, "align": 4, "data": bytes(4)}
        with self.assertRaisesRegex(ValueError, "no configured range"):
            self.plan(self.objects(extra=[data]))
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"].append(
            {"section": ".sdata", "placement": ".data2", "start": "0x80004010", "end": "0x80004014"})
        with self.assertRaisesRegex(ValueError, "was not produced"):
            self.plan(self.objects(), manifest)

    def test_section_kind_and_alignment(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0].update(placement=".data2", start="0x80004000", end="0x80004008")
        with self.assertRaisesRegex(ValueError, "cannot be placed"):
            self.plan(self.objects(), manifest)
        with self.assertRaisesRegex(ValueError, "alignment"):
            self.plan({"src/unit.c": compiled([text(8, align=32), rodata(4)], [])})

    def test_symbols_must_resolve_explicitly(self):
        with self.assertRaisesRegex(ValueError, "unresolved symbol Helper"):
            self.plan(self.objects(symbols=[{"name": "Helper", "value": 0, "shndx": 0}]))
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"Helper": {"address": "0x80004004", "evidence": "name evidence"}}
        pieces, _, resolved = self.plan(
            self.objects(symbols=[{"name": "Helper", "value": 0, "shndx": 0}]), manifest)
        self.assertEqual(resolved, {"Helper": 0x80004004})
        self.assertEqual(pieces[".data2"][0]["symbols"], [{"name": "Helper", "value": 4}])

    def test_references_cannot_bypass_a_source_unit(self):
        with self.assertRaisesRegex(ValueError, "inside source unit"):
            self.plan(self.objects(symbols=[{"name": "fn_80003114", "value": 0, "shndx": 0}]))
        with self.assertRaisesRegex(ValueError, "outside the executable"):
            self.plan(self.objects(symbols=[{"name": "lbl_80004800", "value": 0, "shndx": 0}]))
        # A section's end address is still attributable to its final original piece.
        pieces, _, _ = self.plan(self.objects(symbols=[{"name": "lbl_80004020", "value": 0, "shndx": 0}]))
        self.assertEqual(pieces[".data2"][-1]["symbols"], [{"name": "lbl_80004020", "value": 0x14}])

    def test_definitions_cannot_collide_or_misstate_addresses(self):
        with self.assertRaisesRegex(ValueError, "neutral label fn_80003100"):
            self.plan(self.objects(symbols=[{"name": "fn_80003100", "value": 0, "shndx": 1}]))
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"Unit_Function": {"address": "0x80003104", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(), manifest)
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(symbols=[{"name": "_SDA_BASE_", "value": 0, "shndx": 1}]))
        with self.assertRaisesRegex(ValueError, "common symbol"):
            self.plan(self.objects(symbols=[{"name": "shared", "value": 4, "shndx": sb.SHN_COMMON}]))

    def test_link_script_and_object_names(self):
        pieces, _, _ = self.plan(self.objects())
        for name, items in pieces.items():
            for index, piece in enumerate(items):
                piece["object"] = Path(f"/build/{name.strip('.')}_{index}.o")
                piece["input"] = name
        script = sb.link_script(TARGET, self.sections, pieces)
        self.assertIn(".init 0x80003100 : { *init_0.o(.init) *init_1.o(.init) *init_2.o(.init) }", script)
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            sb.check_basenames([Path("a/unit.o"), Path("b/myunit.o")])
        with self.assertRaisesRegex(ValueError, "not safe"):
            sb.check_basenames([Path("a/unit (1).o")])


class Build(unittest.TestCase):
    """Drive the complete build with mocked tool stages."""

    def run_build(self, output_bytes, link=True, units=True):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        root = Path(temporary.name)
        binary = synthetic_dol()
        target = dict(TARGET, size=len(binary), sha1=hashlib.sha1(binary).hexdigest())
        (root / "config/GN7E69").mkdir(parents=True)
        (root / "tools").mkdir()
        (root / "src").mkdir()
        (root / "config/GN7E69/baseline.json").write_text(json.dumps(target))
        (root / "config/GN7E69/analysis.json").write_text(json.dumps({"output_sections": {}}))
        (root / "tools/compiler-tools.json").write_text(json.dumps({"compiler_version": "3.9.3"}))
        (root / "tools/baseline-tools.json").write_text("{}")
        (root / "src/unit.c").write_text("int unit;\n")
        manifest = {"schema": 1, "target": "GN7E69", "compiler": "3.9.3", "include_dirs": [],
                    "profiles": {"library": {"flags": ["-O2"], "evidence": "locator"}}, "externals": {},
                    "units": [{"source": "src/unit.c", "profile": "library", "evidence": "locator",
                               "sections": [{"section": ".text", "placement": ".init",
                                             "start": "0x80003110", "end": "0x80003118"}]}]
                    if units else []}
        manifest_path = root / "config/GN7E69/units.json"
        manifest_path.write_text(json.dumps(manifest))
        original = root / "main.dol"
        original.write_bytes(binary)
        build = root / "build/source"
        report = build / "report.json"

        def stage(command, **kwargs):
            if "-c" in command:
                obj = Path(command[command.index("-o") + 1])
                sb.write_object(obj, [text(8)], [{"name": "Unit_Function", "value": 0, "shndx": 1}])
                Path(command[command.index("--depfile") + 1]).write_text(
                    f"unit.o: {root / 'src/unit.c'}\n")
            elif "-T" in command and link:
                sb.write_object(Path(command[command.index("-o") + 1]), [text(4)],
                                [{"name": "Unit_Function", "value": 0x80003110, "shndx": sb.SHN_ABS}])
            elif "elf2dol" in command:
                Path(command[-1]).write_bytes(output_bytes(binary))
            return type("Result", (), {"returncode": 0})()

        with patch.object(sb, "ROOT", root), patch.object(sb, "BUILD", build), \
                patch.object(sb.setup_compiler, "setup", return_value=(root / "cc", root / "wibo")), \
                patch.object(sb.baseline, "get_tool", return_value=root / "dtk"), \
                patch.object(sb.subprocess, "run", side_effect=stage):
            try:
                return sb.build(original, manifest_path, report), report
            except RuntimeError as error:
                return error, report

    def test_identical_output_reports_matched_unit_bytes(self):
        result, path = self.run_build(lambda binary: binary)
        self.assertEqual(result["complete"], "identical")
        self.assertEqual(result["totals"], {"code": {"linked": 8, "matched": 8},
                                            "data": {"linked": 0, "matched": 0}})
        self.assertEqual(result["units"][0]["dependencies"], {"src/unit.c": result["units"][0]["source_sha256"]})
        self.assertEqual(json.loads(path.read_text()), result)

    def test_zero_units_still_verify_the_complete_target(self):
        result, _ = self.run_build(lambda binary: binary, units=False)
        self.assertEqual(result["units"], [])
        self.assertEqual(result["totals"]["code"], {"linked": 0, "matched": 0})

    def test_mismatching_output_never_claims_matched_bytes(self):
        def corrupt(binary):
            changed = bytearray(binary)
            changed[0x100 + 0x30] ^= 0xFF
            return bytes(changed)
        error, path = self.run_build(corrupt)
        self.assertIsInstance(error, RuntimeError)
        report = json.loads(path.read_text())
        self.assertEqual(report["complete"], "mismatch")
        self.assertEqual(report["totals"]["code"], {"linked": 8, "matched": 0})
        self.assertEqual(report["units"][0]["sections"][0]["status"], "range-identical")

    def test_linker_must_produce_a_fresh_elf(self):
        error, path = self.run_build(lambda binary: binary, link=False)
        self.assertRegex(str(error), "fresh ELF")
        self.assertFalse(path.exists())


if __name__ == "__main__":
    unittest.main()
