#!/usr/bin/env python3
"""Export public section-level progress from the verified original-object baseline."""

import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import shutil
import struct

ROOT = Path(__file__).resolve().parents[1]


def report(binary, revision):
    target = json.loads((ROOT / "config/GN7E69/baseline.json").read_text())
    if len(binary) != target["size"] or hashlib.sha1(binary).hexdigest() != target["sha1"]:
        raise ValueError("Progress requires the verified target executable")
    if not re.fullmatch(r"[0-9a-f]{40}", revision):
        raise ValueError("Progress requires a full commit revision")
    # The baseline links original objects only. Source builds need their own measured report.
    source = ROOT / "src"
    if source.exists() and any(p.is_file() for p in source.rglob("*")):
        raise ValueError("Source units require a measured source-build progress exporter")
    sections = []
    for kind, count, offset_base, address_base, size_base in (
        ("code", 7, 0x00, 0x48, 0x90),
        ("data", 11, 0x1C, 0x64, 0xAC),
    ):
        for index in range(count):
            offset = struct.unpack_from(">I", binary, offset_base + index * 4)[0]
            address = struct.unpack_from(">I", binary, address_base + index * 4)[0]
            size = struct.unpack_from(">I", binary, size_base + index * 4)[0]
            if not size:
                continue
            if offset < 0x100 or offset + size > len(binary):
                raise ValueError("Invalid executable section extent")
            sections.append({"name": f"{kind.title()} section {index + 1}",
                             "kind": kind, "address": f"0x{address:08X}",
                             "size": size, "linked": 0, "matched": 0})
    address, size = struct.unpack_from(">II", binary, 0xD8)
    uninitialized = [(address, address + size)] if size else []
    # DOL's BSS extent can overlap loaded sections. Count each memory byte once.
    for section in sections:
        start = int(section["address"], 16)
        end = start + section["size"]
        remaining = []
        for left, right in uninitialized:
            if end <= left or start >= right:
                remaining.append((left, right))
            else:
                if left < start:
                    remaining.append((left, start))
                if end < right:
                    remaining.append((end, right))
        uninitialized = remaining
    for index, (left, right) in enumerate(uninitialized, 1):
        sections.append({"name": f"Uninitialized data {index}", "kind": "data",
                         "address": f"0x{left:08X}", "size": right - left,
                         "linked": 0, "matched": 0})
    measures = {kind: {"total": sum(s["size"] for s in sections if s["kind"] == kind),
                       "linked": 0, "matched": 0} for kind in ("code", "data")}
    return {"schema": 1, "revision": revision,
            "built_at": datetime.now(timezone.utc).isoformat(),
            "target": "GN7E69", "target_sha1": target["sha1"],
            "basis": "executable-sections", "baseline": "verified",
            "measures": measures, "sections": sections}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--output", type=Path, default=ROOT / "build/site")
    args = parser.parse_args()
    data = report(args.dol.read_bytes(), args.revision)
    args.output.mkdir(parents=True, exist_ok=True)
    for name in ("index.html", "style.css", "progress.js", "cover.jpg"):
        shutil.copyfile(ROOT / "web" / name, args.output / name)
    (args.output / "progress.json").write_text(json.dumps(data, indent=2) + "\n")


if __name__ == "__main__":
    main()
