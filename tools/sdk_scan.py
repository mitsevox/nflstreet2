#!/usr/bin/env python3
"""Locate SDK object fingerprints in a target DOL; results are research candidates, not progress."""

import argparse
import hashlib
import json
from pathlib import Path
import struct

from source_build import read_elf

# PowerPC relocation fields, in the instruction word containing r_offset.
MASKS = {1: 0xFFFFFFFF, 4: 0xFFFF, 5: 0xFFFF, 6: 0xFFFF,
         10: 0x03FFFFFC, 11: 0xFFFC, 109: 0x1FFFFF}


def code_sections(binary):
    if len(binary) < 0x100:
        raise ValueError("Truncated DOL header")
    sections = []
    for index in range(7):
        offset, start, size = (struct.unpack_from(">I", binary, base + index * 4)[0] for base in (0, 0x48, 0x90))
        if size:
            if offset < 0x100 or offset + size > len(binary) or size % 4:
                raise ValueError("Invalid DOL executable section")
            sections.append((start, binary[offset:offset + size]))
    return sections


def functions(binary, minimum):
    sections, symbols = read_elf(binary)
    for section in sections:
        if not section["flags"] & 4 or section["type"] != 1:
            continue
        if section["size"] % 4:
            raise ValueError("SDK code section is not word-aligned")
        masks = [0] * (section["size"] // 4)
        for relocations in sections:
            if relocations["type"] != 4 or relocations["info"] != section["index"]:
                continue
            for offset in range(relocations["offset"], relocations["offset"] + relocations["size"], 12):
                address, info, _ = struct.unpack_from(">IIi", binary, offset)
                kind = info & 0xFF
                if kind not in MASKS or address // 4 >= len(masks):
                    raise ValueError(f"Unsupported or invalid SDK relocation {kind}")
                masks[address // 4] |= MASKS[kind]
        for symbol in symbols:
            if symbol["type"] != 2 or symbol["shndx"] != section["index"] or symbol["size"] < minimum:
                continue
            start, size = symbol["value"], symbol["size"]
            if start % 4 or size % 4 or start + size > section["size"]:
                raise ValueError(f"Invalid SDK function extent: {symbol['name']}")
            yield symbol["name"], section["data"][start:start + size], masks[start // 4:(start + size) // 4]


def locate(code, masks, sections):
    """Use the longest unrelocated instruction run as an anchor, then compare every word."""
    runs, start = [], None
    for index, mask in enumerate(masks + [1]):
        if not mask and start is None:
            start = index
        if mask and start is not None:
            runs.append((start, index))
            start = None
    if not runs:
        raise ValueError("SDK fingerprint has no unrelocated instruction anchor")
    low, high = max(runs, key=lambda run: run[1] - run[0])
    anchor = code[low * 4:high * 4]
    words = struct.unpack(f">{len(masks)}I", code)
    hits = []
    for base, contents in sections:
        offset = contents.find(anchor)
        while offset >= 0:
            start = offset - low * 4
            if start >= 0 and start % 4 == 0 and start + len(code) <= len(contents):
                target = struct.unpack_from(f">{len(masks)}I", contents, start)
                if all(((left ^ right) & (~mask & 0xFFFFFFFF)) == 0
                       for left, right, mask in zip(words, target, masks)):
                    hits.append(base + start)
            offset = contents.find(anchor, offset + 1)
    return hits


def scan(original, object_root, minimum=32):
    if minimum < 32 or minimum % 4:
        raise ValueError("SDK screening minimum must be word-aligned and at least 32 bytes")
    binary = original.read_bytes()
    sections = code_sections(binary)
    objects = sorted(object_root.rglob("*.o"))
    if not objects:
        raise ValueError("SDK object directory contains no compiled objects")
    records = []
    for path in objects:
        for name, code, masks in functions(path.read_bytes(), minimum):
            hits = locate(code, masks, sections)
            records.append({"object": path.relative_to(object_root).as_posix(), "function": name,
                            "size": len(code), "addresses": [f"0x{address:08X}" for address in hits],
                            "status": "unique" if len(hits) == 1 else "ambiguous" if hits else "absent"})
    return {"schema": 1, "basis": "relocation-masked SDK candidates; calls, data and unit ownership unverified",
            "target_sha1": hashlib.sha1(binary).hexdigest(), "minimum_size": minimum,
            "counts": {status: sum(record["status"] == status for record in records)
                       for status in ("unique", "ambiguous", "absent")}, "functions": records}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--object-root", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True, help="Local/private research output path")
    args = parser.parse_args()
    try:
        result = scan(args.original, args.object_root)
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, indent=2) + "\n")
        print("SDK candidates: " + ", ".join(f"{count} {status}" for status, count in result["counts"].items()))
    except (ValueError, OSError) as error:
        parser.exit(1, f"sdk_scan: {error}\n")


if __name__ == "__main__":
    main()
