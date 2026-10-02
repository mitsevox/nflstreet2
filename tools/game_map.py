"""Project candidate unit evidence into display ranges, without changing build splits."""

import csv
from pathlib import Path

EVIDENCE_PATH = 'config/GN7E69/evidence.tsv'


def load(root, sections, authoritative=()):
    """Keep unique candidate coverage; established ownership takes precedence."""
    path = Path(root) / EVIDENCE_PATH
    if not path.exists():
        return []
    candidates = []
    subjects = set()
    with path.open() as file:
        for row in csv.DictReader(file, delimiter='\t'):
            if row['kind'] != 'unit':
                continue
            if row['start'] == '-' or row['end'] == '-':
                raise ValueError('Unit evidence needs a bounded display range')
            start, end = int(row['start'], 16), int(row['end'], 16)
            if start >= end or not row['subject'] or row['subject'] in subjects:
                raise ValueError('Invalid or duplicate candidate unit')
            subjects.add(row['subject'])
            owners = [s for s in sections if int(s['address'], 16) <= start < end
                      <= int(s['address'], 16) + s['size']]
            if len(owners) != 1:
                raise ValueError('Candidate unit falls outside one executable section')
            if row['start_boundary'] not in ('exact', 'provisional', 'open') \
                    or row['end_boundary'] not in ('exact', 'provisional', 'open'):
                raise ValueError('Candidate unit lacks boundary confidence')
            candidates.append((start, end, row['subject'], owners[0]['kind']))
    blocked = [(int(e['start'], 16), int(e['end'], 16))
               for unit in authoritative for e in unit['sections']]
    result = {}
    for section in sections:
        left = int(section['address'], 16)
        right = left + section['size']
        local = [c for c in candidates if left <= c[0] < c[1] <= right]
        edges = sorted({left, right} | {v for c in local for v in c[:2]}
                       | {max(left, min(right, v)) for b in blocked for v in b})
        for start, end in zip(edges, edges[1:]):
            if any(a < end and start < b for a, b in blocked):
                continue
            owners = [c for c in local if c[0] <= start < end <= c[1]]
            if len(owners) != 1:
                continue
            _, _, subject, kind = owners[0]
            unit = result.setdefault(subject, {'name': 'Candidate / ' + subject,
                                              'candidate': True, 'sections': []})
            extents = unit['sections']
            if extents and extents[-1]['end'] == f'0x{start:08X}':
                extents[-1]['end'] = f'0x{end:08X}'
            else:
                extents.append({'start': f'0x{start:08X}', 'end': f'0x{end:08X}', 'kind': kind})
    return list(result.values())
