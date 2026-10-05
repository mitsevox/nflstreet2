#!/usr/bin/env python3
"""Validate one progress measurement and derive both maps, history and credits."""

import argparse
import json
from pathlib import Path
import shutil

import activity
import check_progress_maps
import decomp_report
import progress

ROOT = Path(__file__).resolve().parents[1]


def export(dol, revision, source_report, analysis_dir, comparison_report,
           previous=None, append=False, fetch_missing=False, squash_base=None):
    if append and previous is None:
        raise ValueError('Main publication requires restored prior deployment history')
    site = progress.report(dol.read_bytes(), revision, source_report,
                           analysis_dir, comparison_report)
    decomp = decomp_report.objdiff_report(site)
    build = json.loads(source_report.read_text())
    check_progress_maps.verify(ROOT, site, decomp, build['units'], site)
    credits = activity._export_verified(ROOT, site, source_report, previous,
                                        append, fetch_missing, squash_base)
    return site, decomp, credits


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dol', type=Path, required=True)
    parser.add_argument('--revision', required=True)
    parser.add_argument('--source-report', type=Path, default=ROOT/'build/source/report.json')
    parser.add_argument('--analysis-dir', type=Path)
    parser.add_argument('--comparison-report', type=Path)
    parser.add_argument('--previous', type=Path)
    parser.add_argument('--append-current', action='store_true')
    parser.add_argument('--fetch-provenance', action='store_true')
    parser.add_argument('--squash-base')
    args = parser.parse_args()
    output = ROOT/'build/site'
    decomp_path = ROOT/'build/GN7E69/report.json'
    # A failed run cannot leave earlier successful reports available for upload.
    for path in (output/'progress.json', output/'activity.json', decomp_path):
        path.unlink(missing_ok=True)
    previous = json.loads(args.previous.read_text()) if args.previous else None
    site, decomp, credits = export(args.dol, args.revision, args.source_report,
                                   args.analysis_dir, args.comparison_report,
                                   previous, args.append_current,
                                   args.fetch_provenance, args.squash_base)
    output.mkdir(parents=True, exist_ok=True)
    decomp_path.parent.mkdir(parents=True, exist_ok=True)
    for name in ('index.html', 'style.css', 'progress.js', 'activity.js', 'cover.jpg', 'logo.png'):
        shutil.copyfile(ROOT/'web'/name, output/name)
    for path, document in ((output/'progress.json', site), (decomp_path, decomp),
                           (output/'activity.json', credits)):
        path.write_text(json.dumps(document, indent=2)+'\n')
    print(f"Verified both maps and {credits['credited_functions']} exact-function credits at {args.revision}")


if __name__ == '__main__':
    main()
