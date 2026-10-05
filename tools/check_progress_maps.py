#!/usr/bin/env python3
"""Reject published maps that omit current candidate evidence or grant it source credit."""

import argparse
import json
from pathlib import Path

import game_map
import decomp_report
import sdk_map

ROOT = Path(__file__).resolve().parents[1]


def verify(root, site, decomp, source_units, comparison_site=None, *, authenticated_comparisons=False):
    if comparison_site is not None:
        for key in ("sections", "files", "measures", "functions", "comparison"):
            if site.get(key) != comparison_site.get(key):
                raise ValueError("Public map differs from validated source comparisons")
    sdk_units = sdk_map.load(root)
    candidates = game_map.load(root, site['sections'], sdk_units + source_units)
    expected = {u['name']: sum(int(e['end'], 16) - int(e['start'], 16)
                              for e in u['sections']) for u in candidates}
    expected_extents = {(u["name"], kind): sorted((e["start"], e["end"])
                        for e in u["sections"] if e["kind"] == kind)
                        for u in candidates for kind in {e["kind"] for e in u["sections"]}}
    for unit in sdk_units:
        for extent in unit["sections"]:
            start, end = int(extent["start"], 16), int(extent["end"], 16)
            container = next(s for s in site["sections"] if int(s["address"], 16) <= start < end
                             <= int(s["address"], 16) + s["size"])
            expected_extents.setdefault((unit["name"], container["kind"]), []).append(
                (extent["start"], extent["end"]))
    expected_extents = {key: sorted(value) for key, value in expected_extents.items()}
    actual_extents = {}
    actual = {}
    for item in site['files']:
        key = (item["name"], item["kind"])
        if key in expected_extents:
            actual_extents[key] = sorted(
                (e["start"], e["end"]) for e in item.get("mapped_extents", []))
        if item.get('scope') != 'candidate-ranges':
            continue
        if item.get('source') or item['linked'] or (comparison_site is None and not authenticated_comparisons and item['matched']):
            raise ValueError('Candidate mapping received source credit')
        actual[item['name']] = actual.get(item['name'], 0) + item['size']
    if actual != expected or actual_extents != expected_extents:
        raise ValueError('Public map omits or changes current unit mapping')
    if decomp != decomp_report.objdiff_report(site):
        raise ValueError('decomp.dev report differs from the current public map')
    units = {u['name']: u for u in decomp['units']}
    for name, size in expected.items():
        unit = units.get(name)
        if unit is None:
            raise ValueError('decomp.dev map omits a candidate grouping')
        m = unit['measures']
        if sum(int(m['total_' + k]) for k in ('code', 'data')) != size \
                or any(int(m[f'{field}_{k}']) for k in ('code', 'data')
                       for field in (('matched', 'complete') if comparison_site is None and not authenticated_comparisons else ('complete',))) \
                or not unit['metadata'].get('auto_generated') \
                or unit['metadata'].get('source_path'):
            raise ValueError('decomp.dev candidate coverage or source credit differs')
    for kind in ('code', 'data'):
        for exported, measured in (('total', 'total'), ('matched', 'matched'), ('complete', 'linked')):
            if int(decomp['measures'][exported + '_' + kind]) != site['measures'][kind][measured]:
                raise ValueError('Published maps disagree on executable progress')
    return len(expected)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--site', type=Path, default=ROOT / 'build/site/progress.json')
    parser.add_argument('--decomp', type=Path, default=ROOT / 'build/GN7E69/report.json')
    parser.add_argument('--source-report', type=Path, default=ROOT / 'build/source/report.json')
    parser.add_argument('--comparison-report', type=Path)
    args = parser.parse_args()
    comparison_site = None
    if args.comparison_report is not None:
        import progress
        comparison_site = progress.report(
            (args.source_report.parent / 'main.dol').read_bytes(),
            json.loads(args.site.read_text())['revision'], args.source_report,
            ROOT / 'build/analysis', args.comparison_report)
    count = verify(ROOT, json.loads(args.site.read_text()), json.loads(args.decomp.read_text()),
                   json.loads(args.source_report.read_text())['units'], comparison_site)
    print(f'Both progress maps cover {count} current candidate groupings; source credit is unchanged.')


if __name__ == '__main__':
    main()
