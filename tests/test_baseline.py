"""Reject successful stage exits that leave old or absent relink outputs."""

import hashlib
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import baseline


class RelinkFreshness(unittest.TestCase):
    def exercise(self, link_output, conversion_output):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            build = root / "build"
            build.mkdir()
            (build / "main.elf").write_bytes(b"old ELF")
            original = root / "input.dol"
            original.write_bytes(b"test target")
            (build / "main.dol").write_bytes(original.read_bytes())
            config = root / "config/GN7E69"
            config.mkdir(parents=True)
            (config / "baseline.json").write_text(json.dumps({
                "size": original.stat().st_size,
                "sha1": hashlib.sha1(original.read_bytes()).hexdigest(),
                "entry": "0x80003100", "sda_base": "0x803F22A0",
                "sda2_base": "0x804022A0", "sections": {".text": "0x800034A0"},
            }))
            (root / "tools").mkdir()
            (root / "tools/baseline-tools.json").write_bytes((ROOT / "tools/baseline-tools.json").read_bytes())

            def stage(command, **kwargs):
                if command[1:3] == ["dol", "split"]:
                    split = build / "split"
                    split.mkdir()
                    (split / "config.json").write_text('{"units": []}')
                elif "-T" in command:
                    if link_output is not None:
                        (build / "main.elf").write_bytes(link_output)
                elif command[1] == "elf2dol":
                    if conversion_output is not None:
                        (build / "main.dol").write_bytes(conversion_output)

            with patch.object(baseline, "ROOT", root), patch.object(baseline, "BUILD", build), \
                 patch.object(baseline, "get_tool", return_value=root / "tool"), \
                 patch.object(baseline.subprocess, "run", side_effect=stage), \
                 patch("sys.argv", ["baseline.py", "--original", str(original)]):
                baseline.main()

    def test_zero_exit_linker_cannot_reuse_old_elf(self):
        with self.assertRaisesRegex(RuntimeError, "fresh ELF"):
            self.exercise(None, b"test target")

    def test_zero_exit_converter_cannot_reuse_old_dol(self):
        with self.assertRaisesRegex(RuntimeError, "fresh DOL"):
            self.exercise(b"fresh ELF", None)

    def test_empty_linker_output_fails(self):
        with self.assertRaisesRegex(RuntimeError, "fresh ELF"):
            self.exercise(b"", b"test target")

    def test_new_mismatching_output_still_fails(self):
        with self.assertRaisesRegex(RuntimeError, "differs"):
            self.exercise(b"fresh ELF", b"wrong target")
