#!/usr/bin/env python3
"""Validate one progress measurement and write the verified objdiff-shaped report the site's
publish action reads. History and contributor credits live in the data repository, which the
publish action writes on main."""

import argparse
import json
from pathlib import Path

import check_progress_maps
import decomp_report
import files_closed
import progress

ROOT = Path(__file__).resolve().parents[1]


def export(dol, revision, source_report, analysis_dir, comparison_report, closed_rows=None):
    site = progress.report(dol.read_bytes(), revision, source_report,
                           analysis_dir, comparison_report)
    decomp = decomp_report.objdiff_report(site)
    build = json.loads(source_report.read_text())
    check_progress_maps.verify(ROOT, site, decomp, build['units'], site)
    if closed_rows is not None:
        mark_closed(decomp, closed_rows)
    return site, decomp


def mark_closed(decomp, rows):
    """Each unit's metadata.closed: the project's done rule as tools/files_closed.py measures it
    (linked, descriptive file name, every function and label named with evidence). The site shows
    it as its own Closed row on the Files card, beside Exact, Named and Total, which keep their
    meaning; it needs the flag on every unit or none, and a closed unit must be named and complete."""
    closed = {row['source'] for row in rows if row['closed']}
    for unit in decomp['units']:
        unit['metadata']['closed'] = unit['metadata'].get('source_path') in closed
    marked = sum(unit['metadata']['closed'] for unit in decomp['units'])
    if marked != len(closed):
        raise ValueError(f'{len(closed)} files are closed but {marked} report units carry them')


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
                          args.analysis_dir, args.comparison_report, files_closed.survey(args.source_report))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(decomp, indent=2)+'\n')
    m = decomp['measures']
    print(f"Verified the progress maps at {args.revision}: {m['matched_functions']} of "
          f"{m['total_functions']} functions exact, "
          f"{sum(u['metadata']['closed'] for u in decomp['units'])} of {m['total_units']} files closed")


if __name__ == '__main__':
    main()
