"""Exercise SDK compilation, dependency tracking and conservative candidate screening."""

import copy
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import sdk_cc
import sdk_scan
import setup_compiler
import source_build
from test_source_build import TARGET, synthetic_dol

FLAGS = ["-nodefaults", "-proc", "gekko", "-fp", "hard", "-Cpp_exceptions", "off",
         "-enum", "int", "-char", "unsigned", "-warn", "pragmas", "-requireprotos",
         "-pragma", "cats off", "-O4,p", "-inline", "auto", "-I-", "-lang=c"]


class Dependencies(unittest.TestCase):
    def test_wibo_paths_and_source_are_preserved(self):
        native = "out\\a.o: src\\a.c \\\r\n\tZ:\\repo with spaces\\inc\\a.h \\\r\n\tZ:\\repo with spaces\\inc\\a.h\r\n"
        self.assertEqual(sdk_cc.dependency_paths(native), ["src/a.c", "/repo with spaces/inc/a.h"])

    def test_foreign_drive_and_empty_dependency_lists_fail(self):
        for value in ("", "out: ", "out: C:\\private\\a.h"):
            with self.subTest(value=value), self.assertRaises(ValueError):
                sdk_cc.dependency_paths(value)

    def test_flags_cannot_override_io_or_add_matching_tricks(self):
        sdk_cc.validate_flags(FLAGS)
        for bad in (["-o", "elsewhere"], ["-D__LINE__=97"], ["-pragma", "optimization_level 0"], ["-proc"]):
            with self.subTest(flags=bad), self.assertRaises(ValueError):
                sdk_cc.validate_flags(bad)

    def test_sdk_profile_is_library_scoped_and_pinned(self):
        sections = source_build.target_sections(synthetic_dol(), TARGET, {})
        manifest = {"schema": 1, "target": "GN7E69", "compiler": "3.9.3", "include_dirs": [],
                    "profiles": {"sdk": {"compiler": "mwcc", "flags": FLAGS, "evidence": "upstream release",
                                         "include_dirs": ["include/libc"]}}, "units": []}
        self.assertEqual(source_build.load_manifest(manifest, sections, "3.9.3")[0], [])
        wrong = copy.deepcopy(manifest)
        wrong["profiles"]["sdk"]["compiler"] = "unreviewed"
        with self.assertRaisesRegex(ValueError, "unsupported compiler"):
            source_build.load_manifest(wrong, sections, "3.9.3")
        wrong = copy.deepcopy(manifest)
        wrong["profiles"]["sdk"]["include_dirs"] = ["../private"]
        with self.assertRaisesRegex(ValueError, "relative repository path"):
            source_build.load_manifest(wrong, sections, "3.9.3")


class Fingerprints(unittest.TestCase):
    def test_only_relocation_fields_are_ignored(self):
        code = struct.pack(">8I", 0x7C0802A6, 0x48000001, 0x9421FFF0, 0x38630001,
                           0x80010014, 0x38210010, 0x7C0803A6, 0x4E800020)
        target = bytearray(code)
        struct.pack_into(">I", target, 4, 0x48012345)
        self.assertEqual(sdk_scan.locate(code, [0, 0x03FFFFFC] + [0] * 6, [(0x80003100, target)]), [0x80003100])
        target[12] ^= 1
        self.assertEqual(sdk_scan.locate(code, [0, 0x03FFFFFC] + [0] * 6, [(0x80003100, target)]), [])

    def test_duplicate_hits_are_not_unique(self):
        code = struct.pack(">8I", *range(1, 9))
        self.assertEqual(sdk_scan.locate(code, [0] * 8, [(0x80003100, code + code)]), [0x80003100, 0x80003120])

    def test_truncated_code_sections_fail(self):
        with self.assertRaisesRegex(ValueError, "Truncated"):
            sdk_scan.code_sections(b"")
        with self.assertRaisesRegex(ValueError, "Invalid DOL"):
            sdk_scan.code_sections(synthetic_dol()[:0x13F])


class CompilerReporting(unittest.TestCase):
    def test_mixed_report_attributes_each_unit_to_its_pinned_compiler(self):
        import hashlib
        import json
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "tools").mkdir()
            (root / "tools/compiler-tools.json").write_text(json.dumps({
                "compiler_version": "3.9.3", "sdk_compiler_version": "GC/1.2.5n"}))
            binary = synthetic_dol()
            target = dict(TARGET, sha1=hashlib.sha1(binary).hexdigest())
            sections = source_build.target_sections(binary, target, {})
            units = []
            for index, family in enumerate(("prodg", "mwcc")):
                path = root / f"unit{index}.c"
                path.write_text("int value;\n")
                units.append({"source": path.name, "path": path, "compile_path": None,
                              "compiler": family, "profile": family, "flags": [], "dependencies": {},
                              "sections": [{"section": ".text", "placement": ".init", "kind": "code",
                                            "start": 0x80003100 + index * 4,
                                            "end": 0x80003104 + index * 4, "compiled": 4}]})
            with patch.object(source_build, "ROOT", root):
                result = source_build.measure(target, sections, units, b"{}", binary, True, {})
            self.assertEqual(result["compilers"], {"prodg": "3.9.3", "mwcc": "GC/1.2.5n"})
            self.assertEqual([unit["compiler"] for unit in result["units"]], [
                {"family": "prodg", "version": "3.9.3"}, {"family": "mwcc", "version": "GC/1.2.5n"}])
            self.assertNotIn("compiler", result)


class NativeCompiler(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        _, cls.wrapper = setup_compiler.setup()
        cls.directory = setup_compiler.setup_sdk()

    def test_objects_are_unmodified_and_dependencies_are_current(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
            root = Path(temporary)
            source, header = root / "sample.c", root / "sample.h"
            header.write_text("#define VALUE 17\n")
            source.write_text('#include "sample.h"\nint Read(void); int Read(void) {return VALUE;}\n')
            output, depfile = root / "sample.o", root / "sample.d"
            sdk_cc.compile(self.directory, self.wrapper, source, output, depfile, FLAGS, [root], ROOT)
            self.assertEqual(set(source_build.dependencies(depfile, ROOT)), {
                source.relative_to(ROOT).as_posix(), header.relative_to(ROOT).as_posix()})
            original = output.read_bytes()
            # The wrapper only copies the native compiler object; it does not rewrite it.
            native = root / "native"
            native.mkdir()
            import subprocess
            result = subprocess.run([str(self.wrapper), str(self.directory / "mwcceppc.exe"),
                                     *FLAGS, "-i", str(root), "-MD", "-c", str(source), "-o", str(native)],
                                    capture_output=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertEqual(original, (native / "sample.o").read_bytes())
            source.write_text("not valid C\n")
            with self.assertRaises(RuntimeError):
                sdk_cc.compile(self.directory, self.wrapper, source, output, depfile, FLAGS, [root], ROOT)
            self.assertFalse(output.exists())
            self.assertFalse(depfile.exists())




class LinkerRetention(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compiler, cls.wrapper = setup_compiler.setup()
        cls.sdk = setup_compiler.setup_sdk()

    def fixture(self, root, data=False):
        source = root / "retention.c"
        source.write_text("int Keep(void); int Drop(void); int Missing(void);\n"
                          "int Keep(void) {return 17;}\n"
                          "int Drop(void) {return Missing();}\n" +
                          ("int stored = 1;\n" if data else ""))
        obj = root / "retention.o"
        sdk_cc.compile(self.sdk, self.wrapper, source, obj, obj.with_suffix(".d"), FLAGS, [], ROOT)
        return {"source": source.name, "object": obj,
                "link_roots": {"symbols": ["Keep"], "evidence": "test retention root"}}

    def test_original_linker_retains_code_without_modifying_native_input(self):
        with tempfile.TemporaryDirectory(prefix="SDK retention ", dir=ROOT / "build") as temporary:
            unit = self.fixture(Path(temporary))
            before = unit["object"].read_bytes()
            sections, symbols = source_build.retained_layout(unit, self.compiler, self.wrapper)
            self.assertEqual(unit["object"].read_bytes(), before)
            self.assertEqual(sections[0]["size"], 8)
            self.assertEqual([s["name"] for s in symbols if s["type"] == 2], ["Keep"])
            # The unused routine and its unresolved callee are not part of the retained layout.
            self.assertNotIn("Missing", [s["name"] for s in symbols])
            self.assertEqual(unit["native_object_sha256"], source_build.sha256(unit["object"]))

    def test_absent_roots_are_rejected(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
            root = Path(temporary)
            unit = self.fixture(root)
            unit["link_roots"]["symbols"] = ["Missing"]
            with self.assertRaisesRegex(ValueError, "defined global function"):
                source_build.retained_layout(unit, self.compiler, self.wrapper)

    def test_native_static_sections_preserve_symbols_and_references(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
            root = Path(temporary)
            unit = self.fixture(root, data=True)
            source = root / "retention.c"
            source.write_text(source.read_text() +
                              "int table[10] = {1,2,3};\nint (*entry)(void) = Missing;\n")
            sdk_cc.compile(self.sdk, self.wrapper, source, unit["object"],
                           unit["object"].with_suffix(".d"), FLAGS, [], ROOT)
            before = unit["object"].read_bytes()
            sections, symbols = source_build.retained_layout(unit, self.compiler, self.wrapper)
            self.assertEqual(unit["object"].read_bytes(), before)
            self.assertEqual(next(s["size"] for s in sections if s["name"] == ".data"), 40)
            self.assertEqual(next(s["size"] for s in sections if s["name"] == ".sdata"), 8)
            self.assertIn("Missing", [s["name"] for s in symbols])
            self.assertIn("table", [s["name"] for s in symbols])
            self.assertNotIn("__sn__bss__tag__address__", [s["name"] for s in symbols])
            self.assertNotIn("__sn__bss__tag__", [s["name"] for s in symbols])

    def test_changed_static_symbol_and_generated_tag_are_rejected(self):
        for name, expected in (("stored", "static symbol"),
                               ("__sn__bss__tag__address__", "BSS tag")):
            with self.subTest(name=name), tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
                unit = self.fixture(Path(temporary), data=True)
                native = unit["object"].read_bytes()
                original_read = source_build.read_elf

                def changed(binary):
                    sections, symbols = original_read(binary)
                    if binary != native:
                        next(s for s in symbols if s["name"] == name)["value"] += 4
                    return sections, symbols

                with patch.object(source_build, "read_elf", changed), self.assertRaisesRegex(ValueError, expected):
                    source_build.retained_layout(unit, self.compiler, self.wrapper)

    def test_mutated_compiler_input_cannot_supply_a_layout(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
            unit = self.fixture(Path(temporary))
            original_run = source_build.run

            def mutate(label, command, log):
                original_run(label, command, log)
                with unit["object"].open("ab") as output:
                    output.write(b"changed")

            with patch.object(source_build, "run", mutate), self.assertRaisesRegex(RuntimeError, "changed"):
                source_build.retained_layout(unit, self.compiler, self.wrapper)

    def test_missing_roots_and_unexpected_allocated_output_fail(self):
        from test_source_build import text, rodata
        for missing, extra in ((True, False), (False, True)):
            with self.subTest(missing=missing, extra=extra), tempfile.TemporaryDirectory(dir=ROOT / "build") as temporary:
                unit = self.fixture(Path(temporary))

                def substitute(label, command, log):
                    sections = [text(8)] + ([rodata(4)] if extra else [])
                    source_build.write_object(unit["object"].with_suffix(".layout.o"), sections,
                                              [{"name": "Other" if missing else "Keep", "value": 0,
                                                "size": 8, "type": 2, "shndx": 1}])
                    log.write_text("")

                with patch.object(source_build, "run", substitute), self.assertRaisesRegex(
                        ValueError, "omitted required|Unexpected allocated"):
                    source_build.retained_layout(unit, self.compiler, self.wrapper)

    def test_retention_metadata_cannot_inject_arguments_or_apply_to_prodg(self):
        import json
        manifest = json.loads((ROOT / "config/GN7E69/units.json").read_text())
        binary = synthetic_dol()
        # A tiny source range is enough to exercise manifest validation before real placement.
        unit = manifest["units"][-1]
        unit["sections"] = [{"section": ".text", "placement": ".init",
                             "start": "0x80003100", "end": "0x80003108"}]
        manifest["units"] = [unit]
        sections = source_build.target_sections(binary, TARGET, {})
        for roots in ({"symbols": ["Keep", "Keep"], "evidence": "x"},
                      {"symbols": ["Keep\n-o other"], "evidence": "x"},
                      {"symbols": ["Keep"], "evidence": ""}):
            bad = copy.deepcopy(manifest)
            bad["units"][0]["link_roots"] = roots
            with self.subTest(roots=roots), self.assertRaisesRegex(ValueError, "link_roots"):
                source_build.load_manifest(bad, sections, "3.9.3")
        manifest["units"][0]["profile"] = "uistudio"
        with self.assertRaisesRegex(ValueError, "link_roots"):
            source_build.load_manifest(manifest, sections, "3.9.3")


if __name__ == "__main__":
    unittest.main()
