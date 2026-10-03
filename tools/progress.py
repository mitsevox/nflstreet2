#!/usr/bin/env python3
"""Export public byte and source-file progress from the verified measured source build."""

import argparse
import csv
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import shutil
import struct

import sdk_map
import game_map
import source_build

ROOT = Path(__file__).resolve().parents[1]
# Files the source build trusts; a report is valid only for the same versions.
TRUSTED_TOOLS = ("tools/source_build.py", "tools/prodg_cc.py", "tools/sdk_cc.py", "tools/setup_compiler.py",
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
        claimed = [(s["section"], s["placement"], int(s["start"], 16), int(s["end"], 16), s.get("follows"))
                   for s in unit["sections"]]
        expected = [(s["section"], s["placement"], int(s["start"], 16), int(s["end"], 16), s.get("follows"))
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


def source_functions(source_report):
    """Require the compiler inventory from the validated, source-bound build report."""
    units = json.loads(source_report.read_text())["units"] if source_report and source_report.exists() else []
    functions = []
    for unit in units:
        rows = unit.get("functions")
        if not isinstance(rows, list):
            raise ValueError(f"Source unit {unit['source']} lacks compiler function coverage")
        # Read-only data configured to follow its unit's code is credited to the code section
        # that contains it, but holds no compiled functions.
        code = [(int(section["start"], 16), int(section["end"], 16))
                for section in unit["sections"] if section["kind"] == "code" and not section.get("follows")]
        seen = set()
        for row in rows:
            try:
                symbol, start, size = row["symbol"], source_build.address(row["address"]), row["size"]
                valid = isinstance(symbol, str) and bool(symbol) and type(size) is int and size > 0
            except (KeyError, TypeError, ValueError):
                valid = False
            if not valid or (symbol, start) in seen or not any(left <= start < start + size <= right
                                                              for left, right in code):
                raise ValueError(f"Source unit {unit['source']} has invalid compiler function coverage")
            neutral = re.fullmatch(r"(?:fn|lbl|data)_([0-9A-Fa-f]{8})", symbol)
            if neutral is None:
                neutral = re.fullmatch(r"fn_([0-9A-Fa-f]{8})__[A-Za-z0-9_]+", symbol)
            if neutral and int(neutral[1], 16) != start:
                raise ValueError(f"Source unit {unit['source']} has a misplaced neutral function")
            seen.add((symbol, start))
            slot = re.fullmatch(r"vfn_0[2-6](?:__[A-Za-z0-9_]+)?", symbol)
            functions.append(dict(row, source=unit["source"], neutral=bool(neutral or slot)))
        if any(not any(left <= int(row["address"], 16) < right for row in rows) for left, right in code):
            raise ValueError(f"Source unit {unit['source']} lacks compiler function coverage for code")
    return functions


def data_in_code(source_report):
    """Read-only data ranges configured to follow their unit's code, from a validated report."""
    units = json.loads(source_report.read_text())["units"] if source_report and source_report.exists() else []
    return [(int(section["start"], 16), int(section["end"], 16), unit["source"])
            for unit in units for section in unit["sections"] if section.get("follows")]


def function_inventory(target, ranges, analysis_dir, compiled=(), data_spans=()):
    """Count candidates from a bound analysis and curated names, never address labels.

    Data placed after code (`data_spans`) must not overlap a candidate."""
    if analysis_dir is None:
        if any(not function["neutral"] for function in compiled):
            raise ValueError("Named compiler functions require a verified function inventory")
        return {"total": None, "exact": None, "named": None, "basis": "unavailable"}, []
    summary = json.loads((analysis_dir / "summary.json").read_text())
    symbols = analysis_dir / "symbols.txt"
    inputs = sdk_map.analysis_inputs(ROOT)
    if summary.get("target_sha1") != target["sha1"] or summary.get("complete_relink") != "identical" \
            or summary.get("inventory") != "provisional" or summary.get("inputs") != inputs \
            or summary.get("symbols_sha256") != digest(symbols):
        raise ValueError("Function inventory is stale or unverified")
    candidates = {}
    for line in symbols.read_text().splitlines():
        if "type:function" not in line:
            continue
        match = re.search(r"= [^:]+:(0x[0-9A-Fa-f]+);.*type:function.*size:(0x[0-9A-Fa-f]+)", line)
        if not match:
            raise ValueError("Malformed function candidate")
        start, size = (int(value, 16) for value in match.groups())
        if start in candidates or size <= 0:
            raise ValueError("Invalid function candidate")
        candidates[start] = size
    if len(candidates) != summary["candidate_counts"]["function"]:
        raise ValueError("Function inventory count is inconsistent")
    source_build.check_data_in_code(data_spans, [(start, start + size, f"candidate fn_{start:08X}")
                                                 for start, size in candidates.items()])
    evidence_path = ROOT / "config/GN7E69/evidence.tsv"
    records = []
    if evidence_path.exists():
        with evidence_path.open() as file:
            records = list(csv.DictReader(file, delimiter="\t"))
    names, extents = {}, {}
    neutral = re.compile(r"(?:fn|lbl|data)_[0-9A-Fa-f]{8}$")
    for row in records:
        if row["kind"] not in ("name", "function") or row["start"] == "-":
            continue
        start = int(row["start"], 16)
        if start not in candidates:
            continue
        if not neutral.fullmatch(row["subject"]):
            if start in names and names[start] != row["subject"]:
                raise ValueError("Conflicting function names")
            names[start] = row["subject"]
        if row["kind"] == "function" and row["start_boundary"] == row["end_boundary"] == "exact":
            end = int(row["end"], 16)
            if end <= start or (start in extents and extents[start] != end):
                raise ValueError("Invalid or conflicting function extent")
            extents[start] = end
    ordered = sorted(extents.items())
    if any(right[0] < left[1] for left, right in zip(ordered, ordered[1:])):
        raise ValueError("Exact function extents overlap")
    exact = {start: end for start, end in extents.items() if any(
        kind == "code" and left <= start < end <= right for kind, left, right in ranges)}
    ordered_candidates = sorted(candidates.items())
    if any(right[0] < left[0] + left[1] for left, right in zip(ordered_candidates, ordered_candidates[1:])):
        raise ValueError("Function candidates overlap")
    for function in compiled:
        start = int(function["address"], 16)
        if start not in candidates or function["size"] != candidates[start]:
            raise ValueError(f"Compiler function {function['symbol']} in {function['source']} "
                             "is missing from the function inventory or has inconsistent bounds")
        if not function["neutral"] and start not in names:
            raise ValueError(f"Compiler function {function['symbol']} in {function['source']} "
                             "is missing curated name evidence")
    functions = []
    for start, size in ordered_candidates:
        covered = sum(max(0, min(start + size, right) - max(start, left))
                      for kind, left, right in ranges if kind == "code")
        functions.append({"name": names.get(start, f"fn_{start:08X}"), "kind": "code",
                          "address": f"0x{start:08X}", "size": size,
                          "linked": covered, "matched": covered})
    return {"total": len(candidates), "exact": len(exact), "named": len(names),
            "basis": "provisional-analysis"}, functions


def source_map(sections, source_report, functions):
    """Expose measured source ownership; unclaimed bytes remain explicitly unmapped."""
    units = json.loads(source_report.read_text())["units"] if source_report and source_report.exists() else []
    for section in sections:
        left = int(section["address"], 16)
        right = left + section["size"]
        if section["kind"] == "code":
            children = [f for f in functions if left <= int(f["address"], 16)
                        and int(f["address"], 16) + f["size"] <= right]
            section["children"] = children + remainder(section, children)
            continue
        children = []
        for unit in units:
            for extent in unit["sections"]:
                start, end = int(extent["start"], 16), int(extent["end"], 16)
                if extent["kind"] != section["kind"] or not left <= start < end <= right:
                    continue
                item = {"name": unit["source"], "kind": section["kind"],
                        "address": extent["start"], "size": end - start,
                        "linked": end - start, "matched": end - start}
                children.append(item)
        section["children"] = children + remainder(section, children)


def file_map(sections, source_report, functions, ownership=()):
    """Partition mapped ownership while crediting only verified compiled-source ranges."""
    units = json.loads(source_report.read_text())["units"] if source_report and source_report.exists() else []
    files = {}
    unknown = []
    for section in sections:
        left = int(section["address"], 16)
        right = left + section["size"]
        measured = [(int(extent["start"], 16), int(extent["end"], 16), unit["source"])
                    for unit in units for extent in unit["sections"]
                    if extent["kind"] == section["kind"]
                    and left <= int(extent["start"], 16) < int(extent["end"], 16) <= right]
        owned = [(int(extent["start"], 16), int(extent["end"], 16), unit["name"], unit.get("source"))
                 for unit in ownership for extent in unit["sections"]
                 if left <= int(extent["start"], 16) < int(extent["end"], 16) <= right]
        for start, end, source in measured:
            overlaps = [item for item in owned if start < item[1] and item[0] < end]
            if overlaps:
                if len(overlaps) != 1 or not overlaps[0][0] <= start < end <= overlaps[0][1] \
                        or overlaps[0][3] != source:
                    raise ValueError("SDK ownership conflicts with a measured source range")
            else:
                owned.append((start, end, source, source))
        cursor = left
        partitions = []
        for start, end, name, source in sorted(owned):
            if start < cursor:
                raise ValueError("Mapped file extents overlap")
            if cursor < start:
                partitions.append((cursor, start, None, None))
            partitions.append((start, end, name, source))
            cursor = end
        if cursor < right:
            partitions.append((cursor, right, None, None))

        def covered(start, end):
            return sum(max(0, min(end, finish) - max(start, begin)) for begin, finish, _ in measured)
        unmapped = {"name": "Unmapped / " + section["name"], "kind": section["kind"],
                    "auto_generated": True, "complete": False,
                    "size": 0, "linked": 0, "matched": 0, "children": []}
        for start, end, name, source in partitions:
            key = (name, section["kind"])
            if name is None:
                item = unmapped
            else:
                item = files.setdefault(key, {
                    "name": name, "kind": section["kind"],
                    "boundary": "provisional", "scope": ("candidate-ranges" if any(u.get("candidate") and u["name"] == name
                               for u in ownership) else "mapped-ranges" if ownership else "measured-ranges"), "complete": False,
                    "size": 0, "linked": 0, "matched": 0, "children": []})
            if name:
                item.setdefault("mapped_extents", []).append({
                    "start": f"0x{start:08X}", "end": f"0x{end:08X}"})
            size = end - start
            item["size"] += size
            if source:
                item["source"] = source
            elif name:
                item["auto_generated"] = True
            item["linked"] += covered(start, end)
            item["matched"] += covered(start, end)
            children = []
            for function in functions if section["kind"] == "code" else []:
                function_start = int(function["address"], 16)
                function_end = function_start + function["size"]
                begin, finish = max(start, function_start), min(end, function_end)
                if begin >= finish:
                    continue
                child = {**function, "address": f"0x{begin:08X}", "size": finish - begin,
                         "linked": covered(begin, finish),
                         "matched": covered(begin, finish),
                         "type": "function" if (begin, finish) == (function_start, function_end)
                                 else "function-fragment",
                         "function_address": function["address"], "original_size": function["size"]}
                if source:
                    child["source"] = source
                children.append(child)
            parent = {"name": "Source bytes" if source else "Unmapped bytes", "kind": section["kind"],
                      "size": size, "linked": covered(start, end), "matched": covered(start, end)}
            children += remainder(parent, children)
            if source:
                for child in children:
                    child["source"] = source
            item["children"].extend(children)
        if unmapped["size"]:
            unknown.append(unmapped)
    result = list(files.values()) + unknown
    for kind in ("code", "data"):
        for field in ("size", "linked", "matched"):
            if sum(item[field] for item in result if item["kind"] == kind) != sum(
                    section[field] for section in sections if section["kind"] == kind):
                raise ValueError("File map does not preserve executable byte totals")
    represented = {}
    for item in result:
        for child in item["children"]:
            if "function_address" in child:
                address = child["function_address"]
                represented[address] = represented.get(address, 0) + child["size"]
    if represented != {function["address"]: function["size"] for function in functions}:
        raise ValueError("File map does not preserve function candidates")
    return result


def remainder(parent, children):
    remaining = {field: parent[field] - sum(c[field] for c in children)
                 for field in ("size", "linked", "matched")}
    if not 0 <= remaining["matched"] <= remaining["linked"] <= remaining["size"]:
        raise ValueError("Map children exceed measured parent bytes")
    return [{"name": "Other bytes in " + parent["name"], "kind": parent["kind"], **remaining}] \
        if remaining["size"] else []


def report(binary, revision, source_report=None, analysis_dir=None):
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
    data_spans = data_in_code(source_report)
    source_build.check_data_in_code(data_spans, source_build.function_extents(ROOT),
                                    source_build.data_extents(ROOT))
    functions, function_items = function_inventory(target, ranges, analysis_dir, source_functions(source_report),
                                                   data_spans)
    source_map(sections, source_report, function_items)
    mapped_functions = sum(1 for section in sections if section["kind"] == "code"
                           for child in section["children"] if "address" in child)
    if mapped_functions != len(function_items):
        raise ValueError("Function candidates fall outside executable sections")
    ownership = sdk_map.load(ROOT, source_build.target_sections(binary, target, {})) \
        if (ROOT / sdk_map.MAP_PATH).exists() else []
    measured_units = json.loads(source_report.read_text())["units"] \
        if source_report and source_report.exists() else []
    ownership += game_map.load(ROOT, sections, ownership + measured_units)
    return {"schema": 1, "revision": revision,
            "built_at": datetime.now(timezone.utc).isoformat(),
            "target": "GN7E69", "target_sha1": target["sha1"],
            "basis": "executable-sections", "baseline": "verified",
            "source": {"units": unit_count, "report": "measured" if source_report and
                       source_report.exists() else "absent"},
            "functions": functions, "measures": measures, "sections": sections,
            "files": file_map(sections, source_report, function_items,
                              ownership)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--source-report", type=Path, default=ROOT / "build/source/report.json")
    parser.add_argument("--analysis-dir", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / "build/site")
    args = parser.parse_args()
    data = report(args.dol.read_bytes(), args.revision, args.source_report, args.analysis_dir)
    args.output.mkdir(parents=True, exist_ok=True)
    for name in ("index.html", "style.css", "progress.js", "cover.jpg", "logo.png"):
        shutil.copyfile(ROOT / "web" / name, args.output / name)
    (args.output / "progress.json").write_text(json.dumps(data, indent=2) + "\n")


if __name__ == "__main__":
    main()
