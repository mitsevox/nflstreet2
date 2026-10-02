#!/usr/bin/env python3
"""Export verified section-byte progress using objdiff's v2 report schema."""

import argparse
import json
from pathlib import Path

import progress


def measures(sections):
    result = {"total_units": len(sections),
              "complete_units": sum(s["linked"] == s["size"] for s in sections)}
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
    """Encode the validated Pages report; section placeholders are not source units."""
    sections = data["sections"]
    return {"version": 2, "measures": measures(sections),
            "units": [{"name": "Executable sections/" + section["name"],
                       "measures": measures([section]),
                       "metadata": {"auto_generated": True,
                                    "complete": section["linked"] == section["size"]}}
                      for section in sections]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--source-report", type=Path, default=progress.ROOT / "build/source/report.json")
    parser.add_argument("--output", type=Path, default=progress.ROOT / "build/GN7E69/report.json")
    args = parser.parse_args()
    args.output.unlink(missing_ok=True)
    data = progress.report(args.dol.read_bytes(), args.revision, args.source_report)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(objdiff_report(data), indent=2) + "\n")


if __name__ == "__main__":
    main()
