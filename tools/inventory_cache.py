"""Bind reusable inventory metadata to its generation inputs and environment."""

import hashlib
import json
import platform
import sys
from pathlib import Path

import sdk_map


def inputs(root, context):
    paths = set(sdk_map.analysis_inputs(root))
    paths.update(str(path.relative_to(root)) for path in (root / 'tools').rglob('*.py'))
    paths.update(('config/GN7E69/baseline.json', 'tools/compiler-tools.json'))
    return {'files': {path: hashlib.sha256((root / path).read_bytes()).hexdigest()
                      for path in sorted(paths)},
            'context': context, 'host': platform.system() + '-' + platform.machine(),
            'python': list(sys.version_info[:2])}


def reusable(root, directory, original, context):
    """Reject stale or damaged metadata; callers rebuild on a miss."""
    try:
        summary = json.loads((directory / 'summary.json').read_text())
        if not isinstance(summary, dict):
            return False
        target = json.loads((root / 'config/GN7E69/baseline.json').read_text())
        return (len(original) == target['size']
                and hashlib.sha1(original).hexdigest() == target['sha1']
                and summary.get('target_sha1') == target['sha1']
                and summary.get('complete_relink') == 'identical'
                and summary.get('inventory') == 'provisional'
                and summary.get('inputs') == sdk_map.analysis_inputs(root)
                and summary.get('cache_inputs') == inputs(root, context)
                and summary.get('symbols_sha256') == hashlib.sha256(
                    (directory / 'symbols.txt').read_bytes()).hexdigest())
    except (OSError, ValueError, TypeError, KeyError):
        return False
