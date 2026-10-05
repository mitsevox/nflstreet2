"""Validate curated SDK ownership independently of reconstructed-source credit."""

import hashlib
import json
from pathlib import PurePosixPath
import re


MAP_PATH = "config/GN7E69/sdk.json"
BASE_INPUTS = ("tools/analyze.py", "tools/sdk_map.py", "tools/source_build.py",
               "tools/baseline-tools.json", "config/GN7E69/analysis.json")


def unit_input_digest(root):
    path = root / "config/GN7E69/units.json"
    if not path.exists():
        return hashlib.sha256(b"").hexdigest()
    try:
        data = json.loads(path.read_text())
        if isinstance(data, dict) and "units" in data:
            extents = sorted(
                (unit.get("source"), extent.get("placement"), extent.get("start"), extent.get("end"))
                for unit in data.get("units", [])
                for extent in unit.get("sections", [])
                if extent.get("placement") not in (".text", ".init")
            )
            return hashlib.sha256(json.dumps(extents).encode()).hexdigest()
        return hashlib.sha256(path.read_bytes()).hexdigest()
    except (OSError, ValueError, TypeError):
        return hashlib.sha256(path.read_bytes()).hexdigest()


def analysis_inputs(root):
    paths = BASE_INPUTS
    if (root / MAP_PATH).exists():
        paths += (MAP_PATH,)
    result = {path: hashlib.sha256((root / path).read_bytes()).hexdigest() for path in paths}
    if (root / "config/GN7E69/units.json").exists():
        result["config/GN7E69/units.json"] = unit_input_digest(root)
    return result


def address(value):
    if not isinstance(value, str) or not re.fullmatch(r"0x[0-9A-F]{8}", value):
        raise ValueError("SDK addresses must be uppercase 0xXXXXXXXX")
    return int(value, 16)


def load(root, sections=None):
    path = root / MAP_PATH
    if not path.exists():
        return []
    data = json.loads(path.read_text())
    target = json.loads((root / "config/GN7E69/baseline.json").read_text())
    if data.get("schema") != 1 or data.get("target_sha1") != target["sha1"]:
        raise ValueError("SDK map belongs to a different target")
    units = data.get("units")
    if not isinstance(units, list) or not units:
        raise ValueError("SDK map requires an explicit unit partition")
    names, ranges = set(), []
    for unit in units:
        name = unit.get("name")
        source = unit.get("source")
        if not isinstance(name, str) or not re.fullmatch(r"[A-Za-z0-9_./+-]+", name) \
                or PurePosixPath(name).is_absolute() or ".." in PurePosixPath(name).parts or name in names:
            raise ValueError("SDK unit names must be distinct safe relative paths")
        names.add(name)
        if source is not None and (source != name or not source.startswith("src/dolphin/")):
            raise ValueError("SDK source ownership requires its repository-relative unit name")
        if not unit.get("library") or not unit.get("evidence") or not unit.get("sections"):
            raise ValueError("SDK units require library, evidence and extents")
        for extent in unit["sections"]:
            start, end = address(extent["start"]), address(extent["end"])
            section = extent["section"]
            if not isinstance(section, str) or not re.fullmatch(r"\.[A-Za-z][A-Za-z0-9_]*", section):
                raise ValueError("SDK section names must be safe object section identifiers")
            if "object_seed" in extent and (type(extent["object_seed"]) is not bool
                    or section in (".text", ".init")):
                raise ValueError("SDK object seeds require explicit boolean data extents")
            if start >= end or (section in (".text", ".init") and (start % 4 or end % 4)):
                raise ValueError("SDK extent is empty or splits an instruction")
            if extent.get("start_boundary") not in ("exact", "provisional") \
                    or extent.get("end_boundary") not in ("exact", "provisional") or not extent.get("evidence"):
                raise ValueError("SDK extent requires independently described boundaries")
            if sections is not None:
                container = next((s for s in sections if s["name"] == section), None)
                if container is None or not container["start"] <= start < end <= container["end"]:
                    raise ValueError("SDK extent is outside its executable section")
            ranges.append((section, start, end, name))
    ordered = sorted(ranges)
    if any(a[0] == b[0] and b[1] < a[2] for a, b in zip(ordered, ordered[1:])):
        raise ValueError("SDK unit extents overlap")
    for coverage in data.get("coverage", []):
        section = coverage["section"]
        start, end = address(coverage["start"]), address(coverage["end"])
        selected = [(left, right) for kind, left, right, _ in ordered
                    if kind == section and start <= left < right <= end]
        cursor = start
        for left, right in selected:
            if left != cursor:
                raise ValueError("SDK coverage has an unassigned gap")
            cursor = right
        if cursor != end or start >= end:
            raise ValueError("SDK coverage is not completely partitioned")
    return units


def split_text(units):
    return "".join("\n" + unit["name"] + ":\n" + "".join(
        f"\t{extent['section']} start:{extent['start']} end:{extent['end']}\n"
        for extent in unit["sections"]) for unit in units)


def object_units(units):
    """Lower separated file-owned extents into private objects without owning gaps."""
    result = []
    for unit in units:
        sections = {}
        for extent in unit["sections"]:
            sections.setdefault(extent["section"], []).append(extent)
        count = max(map(len, sections.values()))
        if count == 1:
            result.append(unit)
            continue
        path = PurePosixPath(unit["name"])
        for index in range(count):
            name = str(path.with_name(f"{path.stem}.__part{index + 1:03}{path.suffix}"))
            result.append({**unit, "name": name, "sections": [
                extents[index] for extents in sections.values() if index < len(extents)]})
    names = [unit["name"] for unit in result]
    if len(set(names)) != len(names):
        raise ValueError("SDK fragment object names collide with a recorded unit")
    return result
