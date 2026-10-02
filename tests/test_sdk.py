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


if __name__ == "__main__":
    unittest.main()
