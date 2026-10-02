#!/usr/bin/env python3
"""Export verified source-file progress using objdiff's v2 report schema."""

import argparse
import json
from pathlib import Path

import progress


def measures(sections):
    result = {"total_units": len(sections),
              "complete_units": 0}
    total = sum(s["size"] for s in sections)
    matched = sum(s["matched"] for s in sections)
    # No partial instruction similarity is measured: use only verified matched bytes.
    result["fuzzy_match_percent"] = 100 * matched / total if total else 0
    for kind in ("code", "data"):
        selected = [s for s in sections if s["kind"] == kind]
        size = sum(s["size"] for s in selected)
        result[f"total_{kind}"] = str(size)
        for source, field in (("matched", "matched"), ("linked", "complete")):
            count = sum(s[source] for s in selected)
            result[f"{field}_{kind}"] = str(count)
            result[f"{field}_{kind}_percent"] = 100 * count / size if size else 0
    return result


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
        metadata = {"auto_generated": source is None, "complete": False}
        if source:
            metadata["source_path"] = source
        functions = [{"name": child["name"], "size": str(child["size"]),
                      "fuzzy_match_percent": 100 * child["matched"] / child["size"],
                      "metadata": {"virtual_address": str(int(child["address"], 16))}}
                     for item in items for child in item["children"]
                     if child.get("type") == "function"]
        unit = {"name": name, "measures": unit_measures, "metadata": metadata}
        if functions:
            unit["functions"] = functions
        units.append(unit)
    totals = measures(data["files"])
    totals["total_units"] = len(units)
    return {"version": 2, "measures": totals, "units": units}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--analysis-dir", type=Path)
    parser.add_argument("--source-report", type=Path, default=progress.ROOT / "build/source/report.json")
    parser.add_argument("--output", type=Path, default=progress.ROOT / "build/GN7E69/report.json")
    args = parser.parse_args()
    args.output.unlink(missing_ok=True)
    data = progress.report(args.dol.read_bytes(), args.revision, args.source_report, args.analysis_dir)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(objdiff_report(data), indent=2) + "\n")


if __name__ == "__main__":
    main()
