#!/usr/bin/env python3
"""Export public section-level progress from the verified target and the measured source build."""

import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import shutil
import struct

ROOT = Path(__file__).resolve().parents[1]
# Files the source build trusts; a report is valid only for the same versions.
TRUSTED_TOOLS = ("tools/source_build.py", "tools/prodg_cc.py", "tools/setup_compiler.py",
                 "tools/baseline.py", "tools/compiler-tools.json", "tools/baseline-tools.json",
                 "config/GN7E69/baseline.json", "config/GN7E69/analysis.json")


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_ranges(target, source_report):
    """Validate the source-build report against the current tree; return its matched ranges."""
    source = ROOT / "src"
    files = sorted(p.relative_to(ROOT).as_posix() for p in source.rglob("*") if p.is_file()) \
        if source.exists() else []
    manifest_path = ROOT / "config/GN7E69/units.json"
    manifest = json.loads(manifest_path.read_text()) if manifest_path.exists() else {"units": []}
    configured = [unit["source"] for unit in manifest.get("units", [])]
    if source_report is None or not source_report.exists():
        if files or configured:
            raise ValueError("Source units require a measured source-build report")
        return [], 0
    data = json.loads(source_report.read_text())
    if data.get("schema") != 1 or data.get("target") != "GN7E69" \
            or data.get("target_sha1") != target["sha1"]:
        raise ValueError("Measured source-build report is for a different target")
    if data.get("complete") != "identical" or data.get("output_sha1") != target["sha1"]:
        raise ValueError("Measured source-build report does not verify the complete target")
    if not manifest_path.exists() or data.get("manifest_sha256") != digest(manifest_path):
        raise ValueError("Measured source-build report is for a different unit manifest")
    tools = {path: digest(ROOT / path) if (ROOT / path).is_file() else None for path in TRUSTED_TOOLS}
    if data.get("tools") != tools:
        raise ValueError("Measured source-build report was produced by different build tooling")
    units = data.get("units", [])
    if [unit["source"] for unit in units] != configured:
        raise ValueError("Measured source-build report does not cover the configured units")
    measured, ranges = set(), []
    totals = {"code": [0, 0], "data": [0, 0]}
    for unit, configured_unit in zip(units, manifest["units"]):
        # The report's ranges must be exactly the configured ranges of the hashed manifest.
        claimed = [(s["section"], s["placement"], int(s["start"], 16), int(s["end"], 16))
                   for s in unit["sections"]]
        expected = [(s["section"], s["placement"], int(s["start"], 16), int(s["end"], 16))
                    for s in configured_unit["sections"]]
        if claimed != expected:
            raise ValueError(f"Source unit {unit['source']} ranges differ from the unit manifest")
        for path, expected in [(unit["source"], unit["source_sha256"])] + sorted(unit["dependencies"].items()):
            if not (ROOT / path).is_file() or digest(ROOT / path) != expected:
                raise ValueError(f"Measured source-build report is stale for {path}")
            measured.add(path)
        if unit.get("status") != "matched" or not unit["sections"]:
            raise ValueError(f"Source unit {unit['source']} is not verified")
        for section in unit["sections"]:
            start, end = int(section["start"], 16), int(section["end"], 16)
            size = end - start
            if section.get("status") != "matched" or section["kind"] not in totals or size <= 0 \
                    or section["linked"] != size or section["matched"] != size:
                raise ValueError(f"Source unit {unit['source']} has an unverified range")
            totals[section["kind"]][0] += size
            totals[section["kind"]][1] += size
            ranges.append((section["kind"], start, end))
    for kind, (linked, matched) in totals.items():
        if data["totals"][kind] != {"linked": linked, "matched": matched}:
            raise ValueError("Measured source-build totals are inconsistent")
    ordered = sorted((start, end) for _, start, end in ranges)
    if any(right[0] < left[1] for left, right in zip(ordered, ordered[1:])):
        raise ValueError("Measured source ranges overlap")
    unmeasured = [path for path in files if path not in measured]
    if unmeasured:
        raise ValueError(f"Source files are not measured by the source-build report: {unmeasured}")
    return ranges, len(units)


def report(binary, revision, source_report=None):
    target = json.loads((ROOT / "config/GN7E69/baseline.json").read_text())
    if len(binary) != target["size"] or hashlib.sha1(binary).hexdigest() != target["sha1"]:
        raise ValueError("Progress requires the verified target executable")
    if not re.fullmatch(r"[0-9a-f]{40}", revision):
        raise ValueError("Progress requires a full commit revision")
    # Original objects never count. Linked and matched bytes come only from a measured
    # source build whose complete output was identical to the target.
    ranges, unit_count = source_ranges(target, source_report)
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
    for section in sections:
        start = int(section["address"], 16)
        end = start + section["size"]
        covered = sum(max(0, min(end, right) - max(start, left)) for kind, left, right in ranges
                      if kind == section["kind"])
        section["linked"] = section["matched"] = min(covered, section["size"])
    measures = {kind: {"total": sum(s["size"] for s in sections if s["kind"] == kind),
                       "linked": sum(s["linked"] for s in sections if s["kind"] == kind),
                       "matched": sum(s["matched"] for s in sections if s["kind"] == kind)}
                for kind in ("code", "data")}
    for kind in ("code", "data"):
        if measures[kind]["linked"] != sum(right - left for k, left, right in ranges if k == kind):
            raise ValueError("Measured source ranges fall outside the executable sections")
    return {"schema": 1, "revision": revision,
            "built_at": datetime.now(timezone.utc).isoformat(),
            "target": "GN7E69", "target_sha1": target["sha1"],
            "basis": "executable-sections", "baseline": "verified",
            "source": {"units": unit_count, "report": "measured" if source_report and
                       source_report.exists() else "absent"},
            "measures": measures, "sections": sections}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--source-report", type=Path, default=ROOT / "build/source/report.json")
    parser.add_argument("--output", type=Path, default=ROOT / "build/site")
    args = parser.parse_args()
    data = report(args.dol.read_bytes(), args.revision, args.source_report)
    args.output.mkdir(parents=True, exist_ok=True)
    for name in ("index.html", "style.css", "progress.js", "cover.jpg"):
        shutil.copyfile(ROOT / "web" / name, args.output / name)
    (args.output / "progress.json").write_text(json.dumps(data, indent=2) + "\n")


if __name__ == "__main__":
    main()
