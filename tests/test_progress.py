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


class ProgressTests(unittest.TestCase):
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


if __name__ == "__main__":
    unittest.main()
