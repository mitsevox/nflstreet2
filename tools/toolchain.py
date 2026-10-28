#!/usr/bin/env python3
"""Tools the pinned build image already holds. `python3 build.py configure --dtk ... --objdiff ...`
records their paths in build/toolchain.json, and the scripts use a recorded tool instead of
downloading it. Without the file (a local checkout) they download and checksum the versions pinned
in tools/*-tools.json, as before. The image is pinned by digest, so its tools need no checksum here."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RECORD = ROOT / "build/toolchain.json"
# name -> what the recorded path must be: an executable file or a directory.
KINDS = {"dtk": "file", "binutils": "directory", "compilers": "directory", "wibo": "file", "objdiff": "file"}


def recorded(name):
    """The recorded path of one tool, or None when it is not recorded."""
    if name not in KINDS:
        raise ValueError(f"Unknown tool {name}")
    if not RECORD.exists():
        return None
    value = json.loads(RECORD.read_text()).get(name)
    return Path(value) if value else None


def record(paths):
    """Check and record {name: path}; every name must be known and every path present."""
    result = {}
    for name, value in paths.items():
        if value is None:
            continue
        path = Path(value).resolve()
        kind = KINDS.get(name)
        if kind is None:
            raise ValueError(f"Unknown tool {name}")
        if not (path.is_file() if kind == "file" else path.is_dir()):
            raise ValueError(f"{name}: {path} is not a {kind}")
        result[name] = str(path)
    RECORD.parent.mkdir(parents=True, exist_ok=True)
    RECORD.write_text(json.dumps(result, indent=1, sort_keys=True) + "\n")
    return result
