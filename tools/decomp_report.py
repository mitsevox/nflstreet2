#!/usr/bin/env python3
"""Export verified source-file progress using objdiff's v2 report schema, in the shape the site's
publish action reads (mitsevox/mitsevox.github.io contract): each unit's sections are its extents,
named after the executable section that holds them and placed at their address, and the totals
count functions and exact functions."""

import argparse
import json
from pathlib import Path

import progress


def measures(sections):
    result = {"total_units": len(sections),
              "complete_units": 0}
    code = [s for s in sections if s["kind"] == "code"]
    total = sum(s["size"] for s in code)
    fuzzy = sum(s.get("fuzzy", s["matched"]) for s in code)
    result["fuzzy_match_percent"] = 100 * fuzzy / total if total else 0
    for kind in ("code", "data"):
        selected = [s for s in sections if s["kind"] == kind]
        size = sum(s["size"] for s in selected)
        result[f"total_{kind}"] = str(size)
        for source, field in (("matched", "matched"), ("linked", "complete")):
            count = sum(s[source] for s in selected)
            result[f"{field}_{kind}"] = str(count)
            result[f"{field}_{kind}_percent"] = 100 * count / size if size else 0
    return result


CODE_SECTIONS = tuple(f"Code section {index}" for index in range(1, 8))


def section_name(sections, kind, start, end):
    """The executable section holding one extent; extents never cross a section."""
    for section in sections:
        left = int(section["address"], 16)
        if section["kind"] == kind and left <= start < end <= left + section["size"]:
            return section["name"]
    raise ValueError(f"Extent 0x{start:08X}..0x{end:08X} lies outside the {kind} sections")


def objdiff_report(data):
    """Source ranges identify partial units; unassigned executable bytes stay visible."""
    grouped = {}
    for item in data["files"]:
        name = item.get("source", item["name"])
        grouped.setdefault(name, []).append(item)
    units = []
    for name, items in grouped.items():
        source = items[0].get("source")
        unit_measures = measures(items)
        unit_measures["total_units"] = 1
        # `complete` is objdiff's meaning, which the site uses for every game: the whole unit is
        # built from verified source and linked, so its bytes count as linked. A partly linked
        # file's linked bytes stay in progress.json. `confirmed` is stricter: unit evidence also
        # establishes the file's exact boundaries.
        complete = bool(source) and all(item["size"] > 0 and item["linked"] == item["size"] for item in items)
        confirmed = complete and all(item.get("complete") is True for item in items)
        unit_measures["complete_units"] = int(complete)
        if not complete:
            for kind in ("code", "data"):
                unit_measures[f"complete_{kind}"] = "0"
                unit_measures[f"complete_{kind}_percent"] = 0
        metadata = {"auto_generated": source is None, "complete": complete, "confirmed": confirmed}
        if source:
            metadata["source_path"] = source
        functions = [{"name": child["name"], "size": str(child["size"]),
                      "fuzzy_match_percent": 100 * child.get("fuzzy", child["matched"]) / child["size"],
                      "metadata": {"virtual_address": str(int(child["address"], 16))}}
                     for item in items for child in item["children"]
                     if child.get("type") == "function"]
        section_items = []
        for item in items:
            extents = [(int(e["start"], 16), int(e["end"], 16)) for e in item.get("mapped_extents", [])]
            if sum(end - start for start, end in extents) != item["size"]:
                raise ValueError(f"{name}: extents do not add up to the item's size")
            percent = 100 * item.get("fuzzy", item["matched"]) / item["size"] if item["size"] else 0
            for start, end in extents:
                section_items.append({"name": section_name(data["sections"], item["kind"], start, end),
                                      "size": str(end - start), "fuzzy_match_percent": percent,
                                      "metadata": {"virtual_address": str(start)}})
        unit = {"name": name, "measures": unit_measures, "metadata": metadata,
                "sections": section_items}
        if functions:
            unit["functions"] = functions
        units.append(unit)
    totals = measures(data["files"])
    totals["total_units"] = len(units)
    totals["complete_units"] = sum(u["metadata"]["complete"] for u in units)
    for kind in ("code", "data"):
        complete = sum(int(u["measures"][f"complete_{kind}"]) for u in units)
        size = int(totals[f"total_{kind}"])
        totals[f"complete_{kind}"] = str(complete)
        totals[f"complete_{kind}_percent"] = 100 * complete / size if size else 0
    every = [f for u in units for f in u.get("functions", [])]
    totals["total_functions"] = len(every)
    totals["matched_functions"] = sum(1 for f in every if f["fuzzy_match_percent"] >= 100)
    return {"version": 2, "measures": totals, "units": units}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--analysis-dir", type=Path)
    parser.add_argument("--comparison-report", type=Path)
    parser.add_argument("--source-report", type=Path, default=progress.ROOT / "build/source/report.json")
    parser.add_argument("--output", type=Path, default=progress.ROOT / "build/GN7E69-rev0/report.json")
    args = parser.parse_args()
    args.output.unlink(missing_ok=True)
    data = progress.report(args.dol.read_bytes(), args.revision, args.source_report, args.analysis_dir, args.comparison_report)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(objdiff_report(data), indent=2) + "\n")


if __name__ == "__main__":
    main()
