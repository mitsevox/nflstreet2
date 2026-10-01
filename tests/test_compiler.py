"""Verify driver equivalence, parallel compilation, and fail-closed output handling."""

import concurrent.futures
import os
import subprocess
import sys
import tempfile
import time
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import prodg_cc
from setup_compiler import setup


class CompilerChecks(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory, cls.wrapper = setup()

    def setUp(self):
        parent = ROOT / "build" / "compiler-check"
        parent.mkdir(parents=True, exist_ok=True)
        self.temporary = tempfile.TemporaryDirectory(dir=parent)
        self.addCleanup(self.temporary.cleanup)
        self.work = Path(self.temporary.name)

    def compile(self, source, output, *extra):
        return subprocess.run([
            sys.executable, str(ROOT / "tools/prodg_cc.py"),
            "--dir", str(self.directory), "--wrapper", str(self.wrapper),
            "-O2", *extra, "-c", str(source), "-o", str(output),
        ], capture_output=True, text=True, timeout=40)

    def test_native_driver_equivalence(self):
        sources = {
            "sample.c": "unsigned char value; int Read(void) { return value + 17; }\n",
            "virtual.cpp": "class Base { public: virtual int Read() {return 17;} }; int Dispatch(Base* p) {return p->Read();}\n",
            "float.cpp": "float Scale(float a, float b) { return a*b+1.0f; }\n",
        }
        environment = os.environ.copy()
        environment["SN_NGC_PATH"] = "Z:" + str(self.directory).replace("/", "\\")
        for name, contents in sources.items():
            with self.subTest(source=name):
                source = self.work / name
                source.write_text(contents)
                native = self.work / (name + ".native.o")
                result = subprocess.run([
                    str(self.wrapper), str(self.directory / "ngccc.exe"), "-O2",
                    "-c", source.name, "-o", native.name,
                ], cwd=self.work, env=environment, capture_output=True, text=True, timeout=40)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                output = self.work / (name + ".o")
                result = self.compile(source, output)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual(native.read_bytes(), output.read_bytes())

    def test_parallel_outputs(self):
        source = self.work / "parallel.cpp"
        source.write_text("float Scale(float a, float b) {return a*b+1.0f;}\n")
        def build(number):
            output = self.work / f"parallel-{number}.o"
            result = self.compile(source, output)
            self.assertEqual(result.returncode, 0, result.stderr)
            return output.read_bytes()
        with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
            outputs = list(executor.map(build, range(16)))
        self.assertTrue(all(output == outputs[0] for output in outputs))

    def test_invalid_arguments_and_missing_outputs(self):
        source = self.work / "sample.c"
        source.write_text("int Read(void) {return 1;}\n")
        output = self.work / "sample.o"
        result = self.compile(source, output, "-x", "invalid")
        self.assertNotEqual(result.returncode, 0)
        self.assertFalse(output.exists())
        with self.assertRaises(ValueError):
            prodg_cc.parse(["--dir"])
        runner = self.work / "empty-runner"
        runner.write_text("#!/usr/bin/env python3\n")
        runner.chmod(0o755)
        with self.assertRaisesRegex(RuntimeError, "did not produce"):
            prodg_cc.compile_unit({"--dir": str(self.directory), "--wrapper": str(runner),
                                  "-c": str(source), "-o": str(output)}, [], [], "c")
        self.assertFalse(output.exists())

    def test_compile_error_preserves_previous_object(self):
        source = self.work / "sample.c"
        source.write_text("int Read(void) {return 1;}\n")
        output = self.work / "sample.o"
        result = self.compile(source, output)
        self.assertEqual(result.returncode, 0, result.stderr)
        previous = output.read_bytes()
        source.write_text("int broken( {\n")
        result = self.compile(source, output)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(previous, output.read_bytes())

    def test_dependency_paths_and_line_endings(self):
        includes = self.work / "include folder"
        includes.mkdir()
        header = includes / "values header.h"
        header.write_text("#define VALUE 17\n")
        source = self.work / "sample.c"
        source.write_text('#include "values header.h"\nint Read(void) {return VALUE;}\n')
        depfile = self.work / "sample.d"
        result = self.compile(source, self.work / "sample.o", "-I", str(includes), "--depfile", str(depfile))
        self.assertEqual(result.returncode, 0, result.stderr)
        dependencies = depfile.read_bytes()
        self.assertNotIn(b"\r", dependencies)
        self.assertIn(b"values\\ header.h", dependencies)

    def test_timeout_stops_descendant_writes(self):
        late_output = self.work / "late-output"
        runner = self.work / "hang.py"
        runner.write_text("import os,time\nfrom pathlib import Path\n"
                          "if os.fork()==0:\n time.sleep(1)\n Path(" + repr(str(late_output)) + ").write_text('late')\n"
                          "else:\n time.sleep(60)\n")
        with patch.object(prodg_cc, "STAGE_TIMEOUT", 0.4):
            with self.assertRaisesRegex(RuntimeError, "timed out"):
                prodg_cc.stage([sys.executable, str(runner)], self.work / "missing-output")
        time.sleep(1.1)
        self.assertFalse(late_output.exists())


if __name__ == "__main__":
    unittest.main()
