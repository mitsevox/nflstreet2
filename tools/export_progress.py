#!/usr/bin/env python3
"""Validate one progress measurement and write the verified objdiff-shaped report the site's
publish action reads. History and contributor credits live in the data repository, which the
publish action writes on main."""

import argparse
import json
from pathlib import Path

import check_progress_maps
import decomp_report
import progress

ROOT = Path(__file__).resolve().parents[1]


def export(dol, revision, source_report, analysis_dir, comparison_report):
    site = progress.report(dol.read_bytes(), revision, source_report,
                           analysis_dir, comparison_report)
    decomp = decomp_report.objdiff_report(site)
    build = json.loads(source_report.read_text())
    check_progress_maps.verify(ROOT, site, decomp, build['units'], site)
    return site, decomp


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dol', type=Path, required=True)
    parser.add_argument('--revision', required=True)
    parser.add_argument('--source-report', type=Path, default=ROOT/'build/source/report.json')
    parser.add_argument('--analysis-dir', type=Path)
    parser.add_argument('--comparison-report', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT/'build/GN7E69-rev0/report.json')
    args = parser.parse_args()
    # A failed run cannot leave an earlier successful report behind.
    args.output.unlink(missing_ok=True)
    site, decomp = export(args.dol, args.revision, args.source_report,
                          args.analysis_dir, args.comparison_report)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(decomp, indent=2)+'\n')
    m = decomp['measures']
    print(f"Verified the progress maps at {args.revision}: {m['matched_functions']} of "
          f"{m['total_functions']} functions exact")


if __name__ == '__main__':
    main()
