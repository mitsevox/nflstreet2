#!/usr/bin/env python3
"""Link compiled source units in place of their configured original ranges and verify the target."""

import argparse
import concurrent.futures
import csv
import hashlib
import json
import os
import platform
import re
import shutil
import struct
import subprocess
import sys
import threading
from pathlib import Path

import baseline
import prodg_cc
import setup_compiler
import sdk_cc


ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build" / "source"
NEUTRAL = re.compile(r"(?:fn|lbl)_([0-9A-F]{8})")
SAFE_PATH = re.compile(r"[A-Za-z0-9_./+-]+")
LINKER_SYMBOLS = {"__start", "_SDA_BASE_", "_SDA2_BASE_"}
LINK_TIMEOUT = 600
# A unit with holdouts compiles each function into its own section, so a holdout's code can be
# left out of the link while every other function keeps its bytes (holdout_object). The flag
# comes from the unit's named profile (owner ruling of 2026-11-20); load_manifest requires it.
FUNCTION_SECTIONS = "-ffunction-sections"
# Build inputs the report is bound to; tools/progress.py rejects reports from other versions.
TRUSTED_TOOLS = ("tools/source_build.py", "tools/prodg_cc.py", "tools/sdk_cc.py", "tools/setup_compiler.py",
                 "tools/baseline.py", "tools/compiler-tools.json", "tools/baseline-tools.json",
                 "tools/diagnostic_object.py", "config/GN7E69-rev0/baseline.json", "config/GN7E69-rev0/analysis.json")

SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB, SHT_NOBITS = 1, 2, 3, 8
SHF_WRITE, SHF_ALLOC, SHF_EXECINSTR = 1, 2, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STB_LOCAL, STB_GLOBAL, STB_WEAK = 0, 1, 2
STT_OBJECT, STT_FUNC, STT_SECTION, STT_FILE = 1, 2, 3, 4


def address(text):
    if not isinstance(text, str) or not re.fullmatch(r"0x[0-9A-F]{8}", text):
        raise ValueError(f"Address must be written as 0xXXXXXXXX in uppercase hexadecimal: {text!r}")
    return int(text, 16)


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


# ELF32 big-endian PowerPC reading and raw-object writing -----------------------------------

def read_elf(data):
    """Return the allocatable sections and the symbols of a relocatable or executable ELF."""
    if data[:7] != b"\x7fELF\x01\x02\x01" or struct.unpack_from(">H", data, 18)[0] != 20:
        raise ValueError("Not a big-endian PowerPC ELF32 file")
    shoff = struct.unpack_from(">I", data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 46)
    headers = []
    for index in range(shnum):
        fields = struct.unpack_from(">IIIIIIIIII", data, shoff + index * shentsize)
        headers.append(dict(zip(("name", "type", "flags", "addr", "offset", "size",
                                 "link", "info", "align", "entsize"), fields)))

    def string(table, offset):
        start = headers[table]["offset"] + offset
        return data[start:data.index(b"\0", start)].decode("ascii")

    sections = []
    for index, header in enumerate(headers):
        header["index"] = index
        header["name"] = string(shstrndx, header["name"]) if index else ""
        if header["type"] == SHT_PROGBITS:
            header["data"] = data[header["offset"]:header["offset"] + header["size"]]
        sections.append(header)
    symbols = []
    for header in sections:
        if header["type"] != SHT_SYMTAB:
            continue
        for index in range(1, header["size"] // 16):
            name, value, size, info, _, shndx = struct.unpack_from(
                ">IIIBBH", data, header["offset"] + index * 16)
            symbols.append({"name": string(header["link"], name), "value": value, "size": size,
                            "bind": info >> 4, "type": info & 15, "shndx": shndx})
    return sections, symbols


def write_object(path, sections, symbols=()):
    """Write a relocatable ELF with the given sections and global symbols; no relocations."""
    names = bytearray(b"\0")

    def intern(table, text):
        offset = len(table)
        table += text.encode("ascii") + b"\0"
        return offset

    strtab = bytearray(b"\0")
    entries = [struct.pack(">IIIBBH", 0, 0, 0, 0, 0, 0),
               struct.pack(">IIIBBH", intern(strtab, Path(path).name), 0, 0, STT_FILE, 0, SHN_ABS)]
    for index in range(len(sections)):
        entries.append(struct.pack(">IIIBBH", 0, 0, 0, STT_SECTION, 0, index + 1))
    local_count = len(entries)
    for symbol in symbols:
        entries.append(struct.pack(">IIIBBH", intern(strtab, symbol["name"]), symbol["value"],
                                   symbol.get("size", 0), (symbol.get("bind", STB_GLOBAL) << 4)
                                   | symbol.get("type", 0), 0, symbol["shndx"]))
    body = bytearray(52)
    headers = [(0,) * 10]
    for section in sections:
        nobits = section["type"] == SHT_NOBITS
        offset = len(body)
        if not nobits:
            body += section["data"]
        body += b"\0" * (-len(body) % 4)
        headers.append((intern(names, section["name"]), section["type"], section["flags"], 0, offset,
                        section["size"], 0, 0, section.get("align", 1), 0))
    symtab_index = len(headers)
    for name, kind, content, link, info, align, entsize in (
            (".symtab", SHT_SYMTAB, b"".join(entries), symtab_index + 1, local_count, 4, 16),
            (".strtab", SHT_STRTAB, bytes(strtab), 0, 0, 1, 0)):
        headers.append((intern(names, name), kind, 0, 0, len(body), len(content), link, info, align, entsize))
        body += content + b"\0" * (-len(content) % 4)
    shstrndx = len(headers)
    name_offset = intern(names, ".shstrtab")
    headers.append((name_offset, SHT_STRTAB, 0, 0, len(body), len(names), 0, 0, 1, 0))
    body += names + b"\0" * (-len(names) % 4)
    struct.pack_into(">16sHHIIIIIHHHHHH", body, 0, b"\x7fELF\x01\x02\x01" + b"\0" * 9, 1, 20, 1, 0, 0,
                     len(body), 0x80000000, 52, 0, 0, 40, len(headers), shstrndx)
    for header in headers:
        body += struct.pack(">IIIIIIIIII", *header)
    Path(path).write_bytes(bytes(body))


# Target and manifest ----------------------------------------------------------------------

def target_sections(binary, target, small_data):
    """Placeholder sections with their target extents, contents and DOL kinds."""
    loaded = {}
    for index in range(18):
        offset, start, size = (struct.unpack_from(">I", binary, base + index * 4)[0]
                               for base in (0x00, 0x48, 0x90))
        if size:
            loaded[start] = {"offset": offset, "size": size, "kind": "code" if index < 7 else "data"}
    bss_start, bss_size = struct.unpack_from(">II", binary, 0xD8)
    starts = [address(value) for value in target["sections"].values()]
    sections = []
    for name, start in zip(target["sections"], starts):
        if start in loaded:
            entry = loaded.pop(start)
            contents = binary[entry["offset"]:entry["offset"] + entry["size"]]
            kind, size = entry["kind"], entry["size"]
        else:
            # Uninitialized placeholders extend to the next placeholder or the DOL BSS end.
            end = min([s for s in starts if s > start] + [bss_start + bss_size])
            if not bss_start <= start < end <= bss_start + bss_size:
                raise ValueError(f"Placeholder {name} is neither loaded nor uninitialized")
            contents, kind, size = None, "bss", end - start
        sections.append({"name": name, "output": small_data.get(name, name), "start": start,
                         "end": start + size, "kind": kind, "contents": contents})
    if loaded:
        raise ValueError("Executable sections are missing from the placeholder configuration")
    return sections


def language_flags(profile):
    """The wrapper's -x option for a profile that sets its language; the flags are then part of
    every unit's flags, so the compile cache key and the report record it."""
    return ["-x", profile["language"]] if "language" in profile else []


def load_manifest(manifest, sections, compiler_version, comparisons=None, evidence=None):
    """Validate the unit manifest; return (units, externals, include directories).

    `comparisons` is the parsed comparisons.json and `evidence` the rows of evidence.tsv (as
    holdout_evidence reads them); each is read from the repository only when a unit declares
    holdouts, which must be registered partials there with a HOLDOUT: evidence row each."""
    if manifest.get("schema") != 1 or manifest.get("target") != "GN7E69-rev0":
        raise ValueError("Unit manifest must use schema 1 for target GN7E69-rev0")
    if manifest.get("compiler") != compiler_version:
        raise ValueError("Unit manifest compiler differs from the pinned compiler")
    allowed = {"schema", "target", "compiler", "include_dirs", "profiles", "externals", "units"}
    if set(manifest) - allowed:
        raise ValueError(f"Unknown manifest fields: {sorted(set(manifest) - allowed)}")
    for directory in manifest.get("include_dirs", []):
        repository_path(directory)
    profiles = manifest.get("profiles", {})
    versions = {}
    for name, profile in profiles.items():
        if set(profile) - {"source_root", "compiler", "compiler_version", "include_dirs", "language"} \
                != {"flags", "evidence"} or not profile["evidence"].strip():
            raise ValueError(f"Profile {name} needs flags, an evidence locator and optionally source_root")
        if "source_root" in profile:
            source_root(profile["source_root"])
        compiler = profile.get("compiler", "prodg")
        if compiler not in {"prodg", "mwcc"}:
            raise ValueError(f"Profile {name} uses an unsupported compiler")
        # An SDK profile may select another pinned CodeWarrior version for a whole library; the
        # versions it may name are listed in tools/compiler-tools.json.
        if compiler == "mwcc":
            default, extra = setup_compiler.sdk_versions()
            versions[name] = profile.get("compiler_version", default)
            if "compiler_version" in profile and profile["compiler_version"] not in extra:
                raise ValueError(f"Profile {name} selects an SDK compiler that is not pinned")
        elif "compiler_version" in profile:
            raise ValueError(f"Profile {name}: compiler_version applies only to SDK profiles")
        else:
            versions[name] = compiler_version
        # "language" sets the front end for every unit of the profile (ProDG -x), for files whose
        # name does not give it, such as a .c file the original build compiled as C++.
        if "language" in profile and (compiler != "prodg" or profile["language"] not in prodg_cc.CPP_LANG):
            raise ValueError(f"Profile {name} language must be c or c++ for the ProDG compiler")
        for directory in profile.get("include_dirs", []):
            repository_path(directory)
        flags = profile["flags"]
        if not all(isinstance(flag, str) for flag in flags) or prodg_cc.OPTIONS & set(flags) \
                or any(flag.startswith("-I") and not (compiler == "mwcc" and flag == "-I-") for flag in flags):
            raise ValueError(f"Profile {name} contains wrapper options or include paths")
        if compiler == "mwcc":
            sdk_cc.validate_flags(flags)
        else:
            prodg_cc.parse(flags + ["--dir", ".", "-c", "unit.c", "-o", "unit.o"])
    externals = {}
    for name, entry in manifest.get("externals", {}).items():
        if NEUTRAL.fullmatch(name) or name in LINKER_SYMBOLS or set(entry) != {"address", "evidence"} \
                or not entry["evidence"].strip():
            raise ValueError(f"External {name} must be a non-neutral name with address and evidence")
        externals[name] = address(entry["address"])
    by_name = {section["name"]: section for section in sections}
    units, ranges, sources, followed = [], [], set(), []
    for unit in manifest.get("units", []):
        if set(unit) - {"link_roots", "folded", "storage", "kept_locals", "holdouts"} \
                != {"source", "profile", "evidence", "sections"} \
                or not unit["evidence"].strip():
            raise ValueError("Each unit needs exactly source, profile, evidence and sections; "
                             "flags belong to a profile")
        source = repository_path(unit["source"])
        if unit["source"] in sources:
            raise ValueError(f"Duplicate unit source {unit['source']}")
        sources.add(unit["source"])
        if unit["profile"] not in profiles:
            raise ValueError(f"Unit {unit['source']} uses unknown profile {unit['profile']}")
        roots = unit.get("link_roots")
        # A holdouts unit's link_roots list only its discarded functions; holdout_functions checks them.
        if roots is not None and "holdouts" not in unit:
            # SDK libraries discard unknown library code; any other unit names each function
            # the linker discards, and retained_layout checks that list exactly. A unit whose
            # roots exist only so the linker drops its folded functions may discard nothing else.
            keys = {"symbols", "evidence"}
            if profiles[unit["profile"]].get("compiler", "prodg") != "mwcc":
                keys = keys | {"discarded"}
            names = link_root_names
            if not isinstance(roots, dict) or set(roots) != keys \
                    or not isinstance(roots["evidence"], str) or not roots["evidence"].strip() \
                    or not names(roots["symbols"]) \
                    or ("discarded" in keys and (not names(roots["discarded"], empty="folded" in unit)
                                                 or set(roots["discarded"]) & set(roots["symbols"]))):
                raise ValueError("link_roots need distinct symbol names and retention evidence"
                                 + ("" if "discarded" not in keys else
                                    ", and a list of the discarded functions"))
        placed = []
        for entry in unit["sections"]:
            if set(entry) - {"follows"} != {"section", "placement", "start", "end"}:
                raise ValueError(f"Unit {unit['source']} section entries need section, placement, start, end "
                                 "and optionally follows")
            target = by_name.get(entry["placement"])
            start, end = address(entry["start"]), address(entry["end"])
            if target is None or not target["start"] <= start < end <= target["end"]:
                raise ValueError(f"{unit['source']} {entry['section']} range is outside {entry['placement']}")
            # A unit with holdouts maps its code section once per linked run between them.
            if any(entry["section"] == other["section"] for other in placed) \
                    and not ("holdouts" in unit and target["kind"] == "code" and "follows" not in entry):
                raise ValueError(f"{unit['source']} maps {entry['section']} more than once")
            follows = entry.get("follows")
            if "follows" in entry and (target["kind"] != "code" or not isinstance(follows, str)):
                raise ValueError(f"{unit['source']} {entry['section']}: follows names the unit's own code "
                                 "section and applies only to data placed in a code section")
            placed.append({"section": entry["section"], "placement": entry["placement"],
                           "start": start, "end": end, "kind": target["kind"], "follows": follows})
            ranges.append((start, end, unit["source"]))
        if not placed:
            raise ValueError(f"Unit {unit['source']} has no configured ranges")
        for entry in placed:
            if entry["follows"] is None:
                continue
            code = followed_code(placed, entry)
            if code is None or code["follows"] is not None or code["placement"] != entry["placement"] \
                    or not code["end"] <= entry["start"]:
                raise ValueError(f"{unit['source']} {entry['section']} must follow another configured section "
                                 f"of the same unit earlier in {entry['placement']}")
            followed.append((code["end"], entry["start"], unit["source"], entry["section"]))
        folded = folded_symbols(unit.get("folded"), placed, unit["source"])
        storage = storage_symbols(unit.get("storage"), sections, unit["source"])
        for name, (start, end) in (storage or {}).items():
            ranges.append((start, end, f"{unit['source']} storage {name}"))
        kept = kept_symbols(unit.get("kept_locals"), placed, unit["source"])
        if folded and kept and set(folded) & set(kept):
            raise ValueError(f"{unit['source']}: a symbol cannot be both folded and kept")
        holdouts = None
        if "holdouts" in unit:
            if comparisons is None:
                comparisons = json.loads((ROOT / "config/GN7E69-rev0/comparisons.json").read_text())
            if evidence is None:
                evidence = holdout_evidence(ROOT)
            holdouts = holdout_functions(unit, placed, comparisons, evidence, by_name)
            for row in holdouts:
                ranges.append((row["start"], row["end"], f"{unit['source']} holdout {row['symbol']}"))
        # Owner ruling of 2026-11-20: -ffunction-sections comes from a named profile, never from
        # the tool. A holdouts unit needs such a ProDG profile, and only a holdouts unit may use one
        # (its code is linked from the derived object's runs, not from per-function sections).
        sectioned = FUNCTION_SECTIONS in profiles[unit["profile"]]["flags"]
        if holdouts and (not sectioned or profiles[unit["profile"]].get("compiler", "prodg") != "prodg"):
            raise ValueError(f"{unit['source']}: holdouts need a named ProDG profile whose flags include "
                             f"{FUNCTION_SECTIONS} (for example game_cpp_holdouts), not {unit['profile']}")
        if sectioned and not holdouts:
            raise ValueError(f"{unit['source']}: profile {unit['profile']} compiles with {FUNCTION_SECTIONS}, "
                             "which only a unit with holdouts may use")
        root =profiles[unit["profile"]].get("source_root")
        compile_path = None
        if root:
            directory, prefix, depth = source_root(root)
            relative = Path(unit["source"]).relative_to(directory) \
                if Path(unit["source"]).is_relative_to(directory) else None
            if relative is None:
                raise ValueError(f"Unit {unit['source']} is outside its profile's source root {directory}")
            compile_path = f"{prefix}/{relative.as_posix()}"
        units.append({"source": unit["source"], "path": source, "profile": unit["profile"],
                      "flags": language_flags(profiles[unit["profile"]]) + profiles[unit["profile"]]["flags"],
                      "sections": placed,
                      "compiler": profiles[unit["profile"]].get("compiler", "prodg"),
                      "compiler_version": versions[unit["profile"]],
                      "include_dirs": profiles[unit["profile"]].get("include_dirs", []),
                      "source_root": root, "compile_path": compile_path, "link_roots": roots,
                      "folded": folded, "storage": storage, "kept_locals": kept, "holdouts": holdouts})
    ranges.sort()
    for left, right in zip(ranges, ranges[1:]):
        if right[0] < left[1]:
            raise ValueError(f"Configured ranges overlap: {left[2]} and {right[2]}")
    for gap_start, gap_end, source, name in followed:
        if any(gap_start < end and start < gap_end for start, end, _ in ranges):
            raise ValueError(f"{source} {name}: another configured range lies between it and the code it follows")
    return units, externals, [directory for directory in manifest.get("include_dirs", [])]


def followed_code(placed, entry):
    """The configured section that data entry `entry` follows, or None. A holdouts unit maps its
    .text once per linked run, so data that follows .text follows the run that ends last."""
    return max((other for other in placed if other["section"] == entry["follows"] and other is not entry),
               key=lambda other: other["end"], default=None)


def link_root_names(values, empty=False):
    """Whether `values` is a list of distinct symbol names link_roots may list (non-empty unless `empty`)."""
    return isinstance(values, list) and (empty or bool(values)) and len(set(values)) == len(values) \
        and all(isinstance(n, str) and re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", n)
                and n not in LINKER_SYMBOLS and not n.startswith("__original_") for n in values)


def folded_symbols(folded, placed, source):
    """Validate a unit's folded local duplicates; return {name: target address} or None.

    `folded` is {"symbols": {name: address}, "evidence": locator}. Each name is a local symbol
    the unit defines that the original linker folded into a byte-identical same-named local
    of another file at that address; fold_object checks the compiled object."""
    if folded is None:
        return None
    if not isinstance(folded, dict) or set(folded) != {"symbols", "evidence"} \
            or not isinstance(folded["evidence"], str) or not folded["evidence"].strip() \
            or not isinstance(folded["symbols"], dict) or not folded["symbols"]:
        raise ValueError(f"{source}: folded needs a non-empty symbols map and evidence")
    result = {}
    for name, value in folded["symbols"].items():
        if not name or NEUTRAL.fullmatch(name) or name in LINKER_SYMBOLS:
            raise ValueError(f"{source}: folded symbol {name!r} must be a descriptive local name")
        result[name] = address(value)
        if any(entry["start"] <= result[name] < entry["end"] for entry in placed):
            raise ValueError(f"{source}: folded symbol {name} targets the unit's own range")
    return result


def storage_symbols(storage, sections, source):
    """Validate a unit's COMMON storage map; return {name: (start, end)} or None.

    `storage` lists {"symbol", "start", "end"} rows. A COMMON symbol has no section, so the
    original linker chose its address: after every file's .bss, or among one file's own
    uninitialized objects. Each row gives one such symbol the target extent an evidenced storage
    map records for it. The extent lies in one uninitialized or initialized data section, outside
    every configured range (load_manifest checks overlaps), and plan() checks it against the
    compiled object; build() checks it against the evidence table."""
    if storage is None:
        return None
    if not isinstance(storage, list) or not storage:
        raise ValueError(f"{source}: storage must list COMMON symbols with their target extents")
    result = {}
    for row in storage:
        if not isinstance(row, dict) or set(row) != {"symbol", "start", "end"} \
                or not isinstance(row["symbol"], str) or not row["symbol"]:
            raise ValueError(f"{source}: storage rows need symbol, start and end")
        name = row["symbol"]
        if NEUTRAL.fullmatch(name) or name in LINKER_SYMBOLS or name.startswith("__original_"):
            raise ValueError(f"{source}: storage symbol {name} must be the compiled COMMON name")
        if name in result:
            raise ValueError(f"{source}: duplicate storage symbol {name}")
        start, end = address(row["start"]), address(row["end"])
        if not any(section["kind"] != "code" and section["start"] <= start < end <= section["end"]
                   for section in sections):
            raise ValueError(f"{source}: storage {name} 0x{start:08X}-0x{end:08X} is not inside one data section")
        result[name] = (start, end)
    return result


def common_object(native, storage, output, source):
    """Model the original linker's allocation of a unit's mapped COMMON symbols.

    Every COMMON symbol of the object must have exactly one storage row, at its compiled size
    and COMMON alignment (the symbol value), and every row must name such a symbol. The derived
    object differs from `native` only in those symbol table entries: each becomes an undefined
    global reference, which the link resolves to the definition plan() places at its storage
    address. Relocations, section bytes and every other symbol are unchanged. (ngcld 3.9.3 links
    a COMMON symbol against such a definition but warns, L0016, when the COMMON is small enough
    for small data and the definition lies outside a small-data section.) Writes `output`."""
    data = bytearray(native)
    sections, symbols = read_elf(bytes(data))
    tables = [section for section in sections if section["type"] == SHT_SYMTAB]
    if len(tables) != 1:
        raise ValueError(f"{source}: COMMON storage requires exactly one symbol table")
    commons = {}
    for index, symbol in enumerate(symbols, 1):
        if symbol["shndx"] != SHN_COMMON:
            continue
        name = symbol["name"]
        if name not in storage:
            raise ValueError(f"{source}: common symbol {name} has no placement")
        start, end = storage[name]
        if name in commons or symbol["bind"] != STB_GLOBAL or end - start != symbol["size"] \
                or start % max(symbol["value"], 1):
            raise ValueError(f"{source}: storage {name} differs from its compiled COMMON size or alignment")
        commons[name] = index
    if set(storage) != set(commons):
        raise ValueError(f"{source}: storage names a symbol that is not a compiled COMMON symbol: "
                         f"{sorted(set(storage) - set(commons))}")
    for index in commons.values():
        at = tables[0]["offset"] + index * 16
        struct.pack_into(">II", data, at + 4, 0, 0)
        struct.pack_into(">H", data, at + 14, SHN_UNDEF)
    Path(output).write_bytes(bytes(data))


def check_storage(units, data, sections):
    """Each storage extent must equal an evidence data row with exact edges, and storage in a
    loaded section must hold zero bytes in the target, as linker-allocated COMMON storage does."""
    for unit in units:
        for name, (start, end) in (unit.get("storage") or {}).items():
            if (start, end) not in data:
                raise ValueError(f"{unit['source']}: storage {name} 0x{start:08X}-0x{end:08X} does not equal "
                                 "an evidence data row with exact edges")
            section = next(s for s in sections if s["start"] <= start < end <= s["end"])
            if section["contents"] is not None \
                    and any(section["contents"][start - section["start"]:end - section["start"]]):
                raise ValueError(f"{unit['source']}: storage {name} 0x{start:08X}-0x{end:08X} is not zero "
                                 "in the target")


def kept_symbols(kept, placed, source):
    """Validate a unit's kept local copies; return {name: address} or None.

    `kept_locals` is {"symbols": {name: address}, "evidence": locator}. Each name is a local
    function (or table) the unit defines at that address in its own code (or data), the one copy
    the original linker kept for the same-named references of other files; keep_object checks the
    compiled object and plan() the placed address."""
    if kept is None:
        return None
    if not isinstance(kept, dict) or set(kept) != {"symbols", "evidence"} \
            or not isinstance(kept["evidence"], str) or not kept["evidence"].strip() \
            or not isinstance(kept["symbols"], dict) or not kept["symbols"]:
        raise ValueError(f"{source}: kept_locals needs a non-empty symbols map and evidence")
    result = {}
    for name, value in kept["symbols"].items():
        if not name or NEUTRAL.fullmatch(name) or name in LINKER_SYMBOLS:
            raise ValueError(f"{source}: kept local {name!r} must be a descriptive name")
        result[name] = address(value)
        if not any(entry["follows"] is None and entry["start"] <= result[name] < entry["end"]
                   for entry in placed):
            raise ValueError(f"{source}: kept local {name} lies outside the unit's sections")
    return result


def keep_object(native, kept, output, aliases=()):
    """Model the original linker keeping one file's local copy for other files' references.

    For each kept name, which must be exactly one local function (in code) or object (in data)
    the compiled object defines, a global symbol with the same name, value, size and section is
    appended, so other units' undefined references to the name resolve to this copy. A name in
    `aliases` is also another unit's folded duplicate of this copy and gets a second global,
    `__folded_<name>`, the name that unit's folded references use. Section bytes, relocations and
    the existing symbols are unchanged. Writes the derived object and returns {name: (symbol, section)}."""
    data = bytearray(native)
    sections, symbols = read_elf(bytes(data))
    tables = [section for section in sections if section["type"] == SHT_SYMTAB]
    if len(tables) != 1:
        raise ValueError("Keeping a local requires exactly one symbol table")
    symtab, strtab = tables[0], sections[tables[0]["link"]]
    result, added, names = {}, [], b""
    for name in kept:
        found = [symbol for symbol in symbols if symbol["name"] == name]
        symbol = found[0] if len(found) == 1 else None
        section = sections[symbol["shndx"]] if symbol and 0 < symbol["shndx"] < len(sections) else None
        if symbol is None or symbol["bind"] != STB_LOCAL or symbol["type"] not in (STT_FUNC, STT_OBJECT) \
                or section is None or section["type"] != SHT_PROGBITS or not section["flags"] & SHF_ALLOC \
                or bool(section["flags"] & SHF_EXECINSTR) != (symbol["type"] == STT_FUNC) \
                or not symbol["size"] or symbol["value"] + symbol["size"] > section["size"]:
            raise ValueError(f"Kept local {name} is not one local function or object defined in the unit")
        result[name] = (symbol, section)
        for alias in [name] + ([folded_reference(name)] if name in aliases else []):
            added.append(struct.pack(">IIIBBH", strtab["size"] + len(names), symbol["value"], symbol["size"],
                                     STB_GLOBAL << 4 | symbol["type"], 0, symbol["shndx"]))
            names += alias.encode("ascii") + b"\0"
    append_symbols(data, symtab, strtab, added, names, output)
    return result


def append_symbols(data, symtab, strtab, added, names, output):
    """Write `data` to `output` with symbol entries `added` and strings `names` appended to its
    symbol and string tables, which move to the end together with a new section header table."""
    shoff = struct.unpack_from(">I", data, 32)[0]
    _, shnum = struct.unpack_from(">HH", data, 46)
    headers = [bytearray(data[shoff + index * 40:shoff + index * 40 + 40]) for index in range(shnum)]
    for header, content in ((symtab, data[symtab["offset"]:symtab["offset"] + symtab["size"]] + b"".join(added)),
                            (strtab, data[strtab["offset"]:strtab["offset"] + strtab["size"]] + names)):
        data += b"\0" * (-len(data) % 4)
        struct.pack_into(">II", headers[header["index"]], 16, len(data), len(content))
        data += content
    data += b"\0" * (-len(data) % 4)
    struct.pack_into(">I", data, 32, len(data))
    data += b"".join(headers)
    Path(output).write_bytes(bytes(data))


def folded_reference(name):
    return f"__folded_{name}"


def fold_object(native, folded, output):
    """Model the original linker folding a unit's local duplicates into another file's copies.

    For each folded name, which must be exactly one defined local function or object, the
    relocations that target it are redirected to a new undefined symbol `__folded_<name>`, which
    the link resolves to the configured address; nothing else changes (ngcld rejects relocations
    against absolute symbols). A reference into a folded extent through any other symbol
    (a section symbol or an alias) is ambiguous and fails, except a branch from inside a folded
    function to its own body, which goes with that body. The folded function's body is left
    unreferenced for the linker's retention to drop; the folded object's bytes stay in place.
    Writes the derived object and returns {name: (symbol, section)}."""
    data = bytearray(native)
    sections, symbols = read_elf(bytes(data))
    tables = [section for section in sections if section["type"] == SHT_SYMTAB]
    if len(tables) != 1:
        raise ValueError("Folding requires exactly one symbol table")
    symtab, strtab = tables[0], sections[tables[0]["link"]]
    folds, added, names = {}, [], b""
    for name in folded:
        if any(symbol["name"] == folded_reference(name) for symbol in symbols):
            raise ValueError(f"Folded reference {folded_reference(name)} is already a symbol of the unit")
        found = [index for index, symbol in enumerate(symbols, 1) if symbol["name"] == name]
        symbol = symbols[found[0] - 1] if len(found) == 1 else None
        section = sections[symbol["shndx"]] if symbol and 0 < symbol["shndx"] < len(sections) else None
        if symbol is None or symbol["bind"] != STB_LOCAL or symbol["type"] not in (STT_OBJECT, STT_FUNC) \
                or section is None or section["type"] != SHT_PROGBITS or not section["flags"] & SHF_ALLOC \
                or bool(section["flags"] & SHF_EXECINSTR) != (symbol["type"] == STT_FUNC) \
                or not symbol["size"] or symbol["value"] + symbol["size"] > section["size"]:
            raise ValueError(f"Folded symbol {name} is not one local function or object defined in the unit")
        folds[found[0]] = (name, symbol, section, len(symbols) + 1 + len(added))
        added.append(struct.pack(">IIIBBH", strtab["size"] + len(names), 0, 0, STB_GLOBAL << 4, 0, SHN_UNDEF))
        names += folded_reference(name).encode("ascii") + b"\0"
    extents = [(symbol["shndx"], symbol["value"], symbol["value"] + symbol["size"])
               for _, symbol, _, _ in folds.values()]
    for index, symbol in enumerate(symbols, 1):
        if index not in folds and symbol["type"] not in (STT_SECTION, STT_FILE) \
                and any(shndx == symbol["shndx"] and start <= symbol["value"] < end
                        for shndx, start, end in extents):
            raise ValueError(f"Symbol {symbol['name']} aliases a folded symbol")
    for section in sections:
        if section["type"] == 9 and sections[section["info"]]["flags"] & SHF_ALLOC:
            raise ValueError("Folding requires explicit-addend relocations")
        if section["type"] != 4:
            continue
        for at in range(section["offset"], section["offset"] + section["size"], 12):
            site, info, addend = struct.unpack_from(">IIi", data, at)
            index = info >> 8
            # A branch inside a folded function's own body goes when the linker drops the body.
            inside = any(symbol["type"] == STT_FUNC and symbol["shndx"] == section["info"]
                         and symbol["value"] <= site < symbol["value"] + symbol["size"]
                         and 0 < index <= len(symbols) and symbols[index - 1]["shndx"] == symbol["shndx"]
                         and symbol["value"] <= symbols[index - 1]["value"] + addend
                         < symbol["value"] + symbol["size"]
                         for _, symbol, _, _ in folds.values())
            if index in folds:
                struct.pack_into(">I", data, at + 4, folds[index][3] << 8 | info & 255)
            elif inside:
                continue
            elif 0 < index <= len(symbols) and any(
                    shndx == symbols[index - 1]["shndx"] and start <= symbols[index - 1]["value"] + addend < end
                    for shndx, start, end in extents):
                raise ValueError("A relocation reaches a folded extent through another symbol")
    append_symbols(data, symtab, strtab, added, names, output)
    return {name: (symbol, section) for name, symbol, section, _ in folds.values()}


# Holdouts ----------------------------------------------------------------------------------
#
# Owner rulings of 2026-11-19 (the two released hulls) and 2026-11-20 (any file, after real
# attempts, with every holdout tracked): a file may be linked as one compiled source with only
# its non-exact functions' code left out. Those functions (the holdouts) stay registered
# partials in comparisons.json and their target ranges keep the original bytes; every data
# section of the file is linked whole, so their literal pools and jump tables must compile
# byte-exact. The unit compiles with -ffunction-sections from its named profile (for example
# game_cpp_holdouts), and the derived link object
# (holdout_object) drops each holdout's code section and redirects every reference to it to
# its target address. Tracking is enforced here: each holdout names its own source-form row in
# evidence.tsv, at its registered range, whose evidence starts with HOLDOUT: (the forms tried
# and the cause); build() refuses an exact holdout, and tools/files_closed.py never closes the file.

HOLDOUT_PREFIX = "HOLDOUT:"
HOLDOUT_LOCATOR = re.compile(r"evidence\.tsv source-form (0x[0-9A-F]{8})-(0x[0-9A-F]{8})")


def holdout_evidence(root):
    """The source-form rows of the target's evidence table: {(start, end): [evidence text]}."""
    path = Path(root) / "config/GN7E69-rev0/evidence.tsv"
    rows = {}
    if path.exists():
        with path.open() as file:
            for row in csv.DictReader(file, delimiter="\t"):
                if row["kind"] == "source-form" and row["start"] != "-" and row["end"] != "-":
                    rows.setdefault((int(row["start"], 16), int(row["end"], 16)), []).append(row["evidence"] or "")
    return rows


def holdout_record(source, symbol, start, end, locator, evidence):
    """Check a holdout's evidence locator: `evidence.tsv source-form 0xSTART-0xEND`, the holdout's
    registered range, naming exactly one row there whose evidence starts with HOLDOUT: and goes
    on to record the forms tried and the cause."""
    match = HOLDOUT_LOCATOR.fullmatch(locator) if isinstance(locator, str) else None
    if not match:
        raise ValueError(f"{source}: holdout {symbol} needs the evidence locator 'evidence.tsv source-form "
                         f"0x{start:08X}-0x{end:08X}' naming its {HOLDOUT_PREFIX} row")
    if (address(match.group(1)), address(match.group(2))) != (start, end):
        raise ValueError(f"{source}: holdout {symbol}'s evidence row {match.group(1)}-{match.group(2)} is not its "
                         f"registered range 0x{start:08X}-0x{end:08X}")
    texts = [text for text in evidence.get((start, end), []) if text.startswith(HOLDOUT_PREFIX)]
    if not texts:
        raise ValueError(f"{source}: holdout {symbol} has no source-form row 0x{start:08X}-0x{end:08X} in "
                         f"evidence.tsv whose evidence starts with {HOLDOUT_PREFIX} (record the forms tried "
                         "and the cause)")
    if len(texts) != 1:
        raise ValueError(f"{source}: holdout {symbol} has more than one {HOLDOUT_PREFIX} row at "
                         f"0x{start:08X}-0x{end:08X}")
    if not texts[0][len(HOLDOUT_PREFIX):].strip():
        raise ValueError(f"{source}: holdout {symbol}'s {HOLDOUT_PREFIX} row records nothing")


def holdout_reference(start):
    """The undefined symbol a derived object's references to the holdout at `start` name."""
    return f"__holdout_{start:08X}"


def holdout_run(start):
    """The derived object's section, and its global marker, for the code run at `start`."""
    return f".text.holdout_run_{start:08X}", f"__holdout_run_{start:08X}"


def holdout_functions(unit, placed, comparisons, evidence, by_name):
    """Validate a unit's holdouts; return [{"symbol", "start", "end", "evidence"}] in address order.

    `holdouts` is {"functions": [{"function": symbol or 0xADDRESS, "evidence": locator}],
    "evidence": locator}. Each entry names one function that comparisons.json registers for the
    same source; its registered extent is the target range that keeps the original bytes, and its
    locator names the HOLDOUT: row of evidence.tsv for that range (holdout_record). Any unit may
    declare holdouts (owner ruling of 2026-11-20). The unit's code entries are the linked runs
    between them: runs and holdouts tile one contiguous code range, with a holdout between any
    two runs. Each run is given the derived object's section that links it (`input`). build()
    checks that none of the holdouts is exact. Read-only data may follow the code (`follows`
    .text), linked whole after the last run, when the code ends with that run.

    The unit may also list, as `link_roots: {"discarded": [...], "evidence": locator}`, file-static
    functions SN's linker discarded (the existing discarded-function practice): compiled, their
    code is dropped like a holdout's, but they have no target range and are never measured.
    Each must not be a function comparisons.json registers or a neutral label; holdout_object
    checks that each is one compiled local function that nothing kept references."""
    source, spec = unit["source"], unit["holdouts"]
    if not isinstance(spec, dict) or set(spec) != {"functions", "evidence"} \
            or not isinstance(spec["evidence"], str) or not spec["evidence"].strip() \
            or not isinstance(spec["functions"], list) or not spec["functions"]:
        raise ValueError(f"{source}: holdouts need a non-empty functions list and evidence")
    roots = unit.get("link_roots")
    # The derived object's run markers are its retention roots, so a holdouts unit's link_roots
    # name no symbols: only the discarded functions holdout_object drops.
    if roots is not None and (not isinstance(roots, dict) or set(roots) != {"discarded", "evidence"}
                              or not isinstance(roots["evidence"], str) or not roots["evidence"].strip()
                              or not link_root_names(roots["discarded"])):
        raise ValueError(f"{source}: a holdouts unit's link_roots are a non-empty list of distinct discarded "
                         "functions and evidence, without symbols")
    for key in ("folded", "kept_locals"):
        if key in unit:
            raise ValueError(f"{source}: holdouts cannot be combined with {key}")
    rows = [row for entry in comparisons.get("units", []) if entry.get("source") == source
            for row in entry.get("functions", [])]
    result = []
    for entry in spec["functions"]:
        if not isinstance(entry, dict) or set(entry) != {"function", "evidence"}:
            raise ValueError(f"{source}: a holdout is {{\"function\": symbol or 0xXXXXXXXX start, \"evidence\": "
                             f"'evidence.tsv source-form 0xSTART-0xEND'}}, not {entry!r}")
        item = entry["function"]
        if not isinstance(item, str) or not item:
            raise ValueError(f"{source}: a holdout is a function symbol or its 0xXXXXXXXX start")
        if re.fullmatch(r"0x[0-9A-Fa-f]{8}", item):
            found = [row for row in rows if address(row["start"]) == address(item)]
        else:
            found = [row for row in rows if row["symbol"] == item]
        if len(found) != 1:
            raise ValueError(f"{source}: holdout {item} is not one function comparisons.json registers for this file")
        symbol, start, end = found[0]["symbol"], address(found[0]["start"]), address(found[0]["end"])
        holdout_record(source, symbol, start, end, entry["evidence"], evidence)
        result.append({"symbol": symbol, "start": start, "end": end, "evidence": entry["evidence"]})
    if len({row["symbol"] for row in result}) != len(result):
        raise ValueError(f"{source}: duplicate holdout")
    for name in (roots or {}).get("discarded", []):
        # A discarded function has no target code: it is neither a holdout nor any registered function.
        if name in {row["symbol"] for row in rows} or NEUTRAL.fullmatch(name):
            raise ValueError(f"{source}: discarded function {name} has a target range; a discarded function is "
                             "not a holdout or a registered function")
    result.sort(key=lambda row: row["start"])
    code = sorted((entry for entry in placed if entry["kind"] == "code" and entry["follows"] is None),
                  key=lambda entry: entry["start"])
    if not code or len({entry["section"] for entry in code}) != 1 \
            or len({entry["placement"] for entry in code}) != 1:
        raise ValueError(f"{source}: holdouts need one code section linked in runs of one placement")
    if code[0]["section"] != ".text":
        raise ValueError(f"{source}: holdouts link code runs of section .text, not {code[0]['section']}")
    target = by_name[code[0]["placement"]]
    pieces = sorted([(entry["start"], entry["end"], "run") for entry in code]
                    + [(row["start"], row["end"], row["symbol"]) for row in result])
    for left, right in zip(pieces, pieces[1:]):
        if right[0] != left[1]:
            raise ValueError(f"{source}: code runs and holdouts must tile one range; 0x{left[1]:08X} is "
                             f"followed by 0x{right[0]:08X}")
        if left[2] == right[2] == "run":
            raise ValueError(f"{source}: two code runs meet at 0x{right[0]:08X} without a holdout between them")
    if not target["start"] <= pieces[0][0] < pieces[-1][1] <= target["end"]:
        raise ValueError(f"{source}: holdouts lie outside {code[0]['placement']}")
    # Read-only data configured to follow the code (follows) is linked whole, from the derived
    # object's unchanged data section, after the last run (followed_code); plan() checks its
    # alignment and the zero padding as for any unit. The code must end with that run: a trailing
    # holdout would lie between the run and the data.
    for entry in placed:
        if entry["follows"] is not None and (entry["follows"] != ".text" or pieces[-1][2] != "run"):
            raise ValueError(f"{source}: {entry['section']} follows the code, so it must follow .text and the "
                             "unit's code must end with a linked run, not a holdout")
    for entry in code:
        entry["input"] = holdout_run(entry["start"])[0]
    return result


def holdout_object(native, unit, output):
    """Write the derived link object of a unit with holdouts; return what it dropped and kept.

    `native` was compiled with -ffunction-sections: each code section holds exactly one function.
    In compiled order, the functions fill the unit's code runs and holdout ranges: a holdout's
    section stands for its registered target range whatever its compiled size, and every other
    function follows the previous one at its section alignment. The derived object
    - merges the function sections of each run, in order, into one section `.text.holdout_run_<start>`
      (zero padding where a function's alignment needs it), with a global marker
      `__holdout_run_<start>` so the linker's retention keeps it; symbols and relocations in it
      move by the function's offset in the run;
    - drops each holdout's code section, its relocations and the symbols defined in it;
    - redirects every relocation that reaches a holdout (through its function, a label in it or
      its section symbol) to a new undefined global `__holdout_<start>`, with the offset into the
      function added to the addend; plan() resolves it to the holdout's target start, inside the
      original bytes there. A global holdout name is reported in `globals`, so other units'
      references to it resolve to the same address;
    - drops each listed discarded function's code section, its relocations and the symbols defined
      in it, without an address: the compiled order skips it. Each must be one compiled local
      function, and a relocation that reaches it from any kept section or a holdout (whose code
      the target has) fails, as the target's linker could not have discarded it then. An
      undefined symbol that only discarded functions reference is dropped too, so plan() need
      not resolve it; one that anything else references stays;
    Data sections and their relocations are unchanged apart from those redirections. The native
    object stays the receipt."""
    source = unit["source"]
    data = bytes(native)
    sections, symbols = read_elf(data)
    tables = [section for section in sections if section["type"] == SHT_SYMTAB]
    if len(tables) != 1:
        raise ValueError(f"{source}: holdouts require exactly one symbol table")
    symtab = tables[0]
    strtab = sections[symtab["link"]]
    for section in sections:
        if section["type"] == 9 and sections[section["info"]]["flags"] & SHF_ALLOC:
            raise ValueError(f"{source}: holdouts require explicit-addend relocations")
    code = [section for section in sections if section["flags"] & SHF_ALLOC and section["flags"] & SHF_EXECINSTR
            and section["size"]]
    owner = {}
    for section in code:
        functions = [symbol for symbol in symbols if symbol["type"] == STT_FUNC and symbol["shndx"] == section["index"]]
        if section["type"] != SHT_PROGBITS or len(functions) != 1 or functions[0]["value"] \
                or functions[0]["size"] != section["size"]:
            raise ValueError(f"{source}: code section {section['name']} is not exactly one function; holdouts "
                             f"need {FUNCTION_SECTIONS}")
        owner[section["index"]] = functions[0]
    names = [symbol["name"] for symbol in owner.values()]
    held = {row["symbol"]: row for row in unit["holdouts"]}
    for name in held:
        if names.count(name) != 1:
            raise ValueError(f"{source}: holdout {name} is not one compiled function of the unit")
    discarded = set((unit.get("link_roots") or {}).get("discarded", ()))
    for name in discarded:
        if names.count(name) != 1 or name in held \
                or next(f for f in owner.values() if f["name"] == name)["bind"] != STB_LOCAL:
            raise ValueError(f"{source}: discarded function {name} is not one compiled local (file-static) "
                             "function of the unit")
    runs = sorted((entry for entry in unit["sections"] if entry.get("input")), key=lambda entry: entry["start"])
    starts = [entry["start"] for entry in runs] + [row["start"] for row in held.values()]
    cursor, end = min(starts), max([entry["end"] for entry in runs] + [row["end"] for row in held.values()])
    members = {entry["start"]: [] for entry in runs}
    dropped, place, linked, gone = [], {}, [], {}
    for section in code:
        function = owner[section["index"]]
        if function["name"] in discarded:
            place[section["index"]] = ("discarded", function["name"])
            gone[function["name"]] = section["size"]
            continue
        if function["name"] in held:
            row = held[function["name"]]
            if cursor != row["start"]:
                raise ValueError(f"{source}: holdout {row['symbol']} 0x{row['start']:08X} is not where the "
                                 f"compiled order reaches (0x{cursor:08X})")
            place[section["index"]] = ("holdout", row["start"])
            dropped.append(dict(row, compiled=section["size"]))
            cursor = row["end"]
            continue
        run = next((entry for entry in runs if entry["start"] <= cursor < entry["end"]), None)
        at = -(-cursor // max(section["align"], 1)) * max(section["align"], 1)
        if run is None or at + section["size"] > run["end"]:
            raise ValueError(f"{source}: compiled function {function['name']} at 0x{at:08X} does not fit a "
                             "configured code run")
        members[run["start"]].append(section)
        linked.append((function["name"], at))
        place[section["index"]] = ("run", run["start"], at - run["start"])
        cursor = at + section["size"]
    if cursor != end or len(dropped) != len(held):
        raise ValueError(f"{source}: the compiled functions end at 0x{cursor:08X}, not at the configured "
                         f"end 0x{end:08X} of the code runs and holdouts")
    # New section table: unchanged sections keep their order; each run's merged section takes the
    # place of its first function; relocation sections follow the section table's other entries.
    new_sections, index_map, run_index = [None], {}, {}
    removed = {".symtab", ".strtab", ".shstrtab"}
    for section in sections[1:]:
        if section["index"] in place:
            kind = place[section["index"]]
            if kind[0] == "run" and kind[1] not in run_index:
                group = members[kind[1]]
                run = next(entry for entry in runs if entry["start"] == kind[1])
                body = bytearray()
                for member in group:
                    offset = place[member["index"]][2]
                    body += bytes(offset - len(body)) + member["data"]
                if len(body) != run["end"] - run["start"]:
                    raise ValueError(f"{source}: code run 0x{run['start']:08X} compiles to {len(body):#x} bytes, "
                                     f"not {run['end'] - run['start']:#x}")
                run_index[kind[1]] = len(new_sections)
                new_sections.append({"name": run["input"], "type": SHT_PROGBITS, "flags": group[0]["flags"],
                                     "data": bytes(body), "size": len(body), "link": 0, "info": 0,
                                     "align": max(max(member["align"], 1) for member in group), "entsize": 0})
            continue
        if section["type"] in (SHT_SYMTAB, 4) or section is strtab or section["index"] == shstrndx(data):
            continue
        if section["name"] in removed:
            continue
        index_map[section["index"]] = len(new_sections)
        content = None if section["type"] == SHT_NOBITS else data[section["offset"]:section["offset"] + section["size"]]
        new_sections.append(dict(section, data=content))
    for start, index in run_index.items():
        for member in members[start]:
            index_map[member["index"]] = index
    # An undefined symbol that only discarded functions' relocations name goes with them: their
    # code and relocations are dropped, so nothing needs it resolved. One that any other section's
    # relocation names (a run's, a holdout's, whose code the target has, or a data section's) stays.
    needed, unneeded = set(), set()
    for section in sections:
        if section["type"] != 4:
            continue
        discarding = place.get(section["info"], ("",))[0] == "discarded"
        for at in range(section["offset"], section["offset"] + section["size"], 12):
            (unneeded if discarding else needed).add(struct.unpack_from(">IIi", data, at)[1] >> 8)
    unneeded = {index for index in unneeded - needed
                if index and symbols[index - 1]["shndx"] == SHN_UNDEF and symbols[index - 1]["name"]}
    # Symbols: same order; run section symbols replace their members' section symbols, symbols
    # in a holdout's or discarded function's section go, as do undefined symbols only discarded
    # functions need, and the holdout references and run markers are appended.
    entries, mapping, run_symbol, first_global = [], {}, {}, None
    symtab_bytes = data[symtab["offset"]:symtab["offset"] + symtab["size"]]
    for index, symbol in enumerate(symbols, 1):
        if index == symtab["info"]:
            first_global = len(entries) + 1
        if index in unneeded:
            continue
        raw = symtab_bytes[index * 16:index * 16 + 16]
        name_offset, value, size, info, other, shndx = struct.unpack(">IIIBBH", raw)
        kind = place.get(shndx)
        if kind and kind[0] in ("holdout", "discarded"):
            mapping[index] = (kind[0], kind[1], value)
            continue
        if kind:
            start, offset = kind[1], kind[2]
            if symbol["type"] == STT_SECTION:
                if start not in run_symbol:
                    run_symbol[start] = len(entries) + 1
                    entries.append(struct.pack(">IIIBBH", 0, 0, 0, STB_LOCAL << 4 | STT_SECTION, 0,
                                               run_index[start]))
                mapping[index] = ("symbol", run_symbol[start], offset)
                continue
            value, shndx = value + offset, run_index[start]
        elif 0 < shndx < 0xFF00:
            if shndx not in index_map:
                raise ValueError(f"{source}: symbol {symbol['name']} is defined in a section holdouts cannot keep")
            shndx = index_map[shndx]
        mapping[index] = ("symbol", len(entries) + 1, 0)
        entries.append(struct.pack(">IIIBBH", name_offset, value, size, info, other, shndx))
    if first_global is None:
        first_global = len(entries) + 1
    strings = bytearray(data[strtab["offset"]:strtab["offset"] + strtab["size"]])
    references = {}
    for row in sorted(held.values(), key=lambda row: row["start"]):
        references[row["start"]] = len(entries) + 1
        entries.append(struct.pack(">IIIBBH", len(strings), 0, 0, STB_GLOBAL << 4, 0, SHN_UNDEF))
        strings += holdout_reference(row["start"]).encode("ascii") + b"\0"
    for start, index in sorted(run_index.items()):
        entries.append(struct.pack(">IIIBBH", len(strings), 0, 0, STB_GLOBAL << 4, 0, index))
        strings += holdout_run(start)[1].encode("ascii") + b"\0"
    # Relocations: a run's members' records merge into one section, moved by each member's offset.
    relocations = {}
    for section in sections:
        if section["type"] != 4:
            continue
        target = place.get(section["info"])
        if target and target[0] == "discarded":
            continue
        if target and target[0] == "holdout":
            # A holdout's code is in the target, so it cannot reach a discarded function either.
            for at in range(section["offset"], section["offset"] + section["size"], 12):
                index = struct.unpack_from(">IIi", data, at)[1] >> 8
                if index and mapping.get(index, ("",))[0] == "discarded":
                    raise ValueError(f"{source}: discarded function {mapping[index][1]} is referenced from "
                                     f"{sections[section['info']]['name']}")
            continue
        key, base = (("run", target[1]), target[2]) if target else (("section", section["info"]), 0)
        records = relocations.setdefault(key, bytearray())
        for at in range(section["offset"], section["offset"] + section["size"], 12):
            site, info, addend = struct.unpack_from(">IIi", data, at)
            index = info >> 8
            if index:
                if index not in mapping:
                    raise ValueError(f"{source}: relocation names an unknown symbol")
                kind, new, delta = mapping[index]
                if kind == "discarded":
                    raise ValueError(f"{source}: discarded function {new} is referenced from "
                                     f"{sections[section['info']]['name']}")
                if kind == "holdout":
                    new, delta = references[new], delta
                index, addend = new, addend + delta
            records += struct.pack(">IIi", site + base, index << 8 | info & 255, addend)
    symtab_index = len(new_sections) + sum(1 for records in relocations.values() if records)
    for (kind, value), records in relocations.items():
        if not records:
            continue
        info = run_index[value] if kind == "run" else index_map.get(value)
        if info is None:
            raise ValueError(f"{source}: relocations for a section holdouts cannot keep")
        new_sections.append({"name": ".rela" + new_sections[info]["name"], "type": 4, "flags": 0,
                             "data": bytes(records), "size": len(records), "link": symtab_index, "info": info,
                             "align": 4, "entsize": 12})
    new_sections.append({"name": ".symtab", "type": SHT_SYMTAB, "flags": 0, "data": bytes(16) + b"".join(entries),
                         "size": 16 * (len(entries) + 1), "link": symtab_index + 1, "info": first_global,
                         "align": 4, "entsize": 16})
    new_sections.append({"name": ".strtab", "type": SHT_STRTAB, "flags": 0, "data": bytes(strings),
                         "size": len(strings), "link": 0, "info": 0, "align": 1, "entsize": 0})
    write_elf(data, new_sections, output)
    return {"dropped": dropped, "discarded": gone,
            "globals": {owner[index]["name"]: kind[1] for index, kind in place.items()
                        if kind[0] == "holdout" and owner[index]["bind"] == STB_GLOBAL},
            "linked": dict(linked)}


def shstrndx(data):
    return struct.unpack_from(">H", data, 50)[0]


def write_elf(original, sections, output):
    """Write a relocatable ELF with the ELF header of `original` and the given sections (index 0 is
    the null section); a section-name string table is appended."""
    names = bytearray(b"\0")
    offsets = []
    for section in sections[1:]:
        offsets.append(len(names))
        names += section["name"].encode("ascii") + b"\0"
    shstr_name = len(names)
    names += b".shstrtab\0"
    body = bytearray(original[:52])
    headers = [(0,) * 10]
    for name, section in zip(offsets, sections[1:]):
        body += bytes(-len(body) % max(4, min(section["align"] or 1, 16)))
        offset = len(body)
        if section["type"] != SHT_NOBITS:
            body += section["data"]
        headers.append((name, section["type"], section["flags"], 0, offset, section["size"], section["link"],
                        section["info"], section["align"], section["entsize"]))
    body += bytes(-len(body) % 4)
    headers.append((shstr_name, SHT_STRTAB, 0, 0, len(body), len(names), 0, 0, 1, 0))
    body += names + bytes(-len(names) % 4)
    struct.pack_into(">I", body, 32, len(body))
    struct.pack_into(">HHH", body, 46, 40, len(headers), len(headers) - 1)
    for header in headers:
        body += struct.pack(">IIIIIIIIII", *header)
    Path(output).write_bytes(bytes(body))


def evidence_rows(root, kind):
    """Bounded rows of one kind in the target's evidence table, as (start, end, subject, edges)."""
    path = Path(root) / "config/GN7E69-rev0/evidence.tsv"
    if not path.exists():
        return []
    with path.open() as file:
        return [(int(row["start"], 16), int(row["end"], 16), row["subject"],
                 (row["start_boundary"], row["end_boundary"]))
                for row in csv.DictReader(file, delimiter="\t")
                if row["kind"] == kind and row["start"] != "-" and row["end"] != "-"]


def function_extents(root):
    """Bounded function extents recorded in the target's evidence table."""
    return [(start, end, subject) for start, end, subject, _ in evidence_rows(root, "function")]


def data_extents(root):
    """Data extents whose both edges the evidence table records as exact."""
    return {(start, end) for start, end, _, edges in evidence_rows(root, "data") if edges == ("exact", "exact")}


def check_data_in_code(spans, functions, data=None):
    """Reject data placed in a code section that is not an exact evidence data block, or that
    overlaps any known function extent.

    `spans` are (start, end, owner) data ranges, `functions` are (start, end, name) extents and
    `data`, when given, the (start, end) extents of exact evidence `data` rows. Data after code
    may only claim a recorded constant block that no function analysis or evidence treats as code."""
    for start, end, owner in spans:
        if data is not None and (start, end) not in data:
            raise ValueError(f"{owner}: data 0x{start:08X}-0x{end:08X} placed after code does not equal "
                             "an evidence data row with exact edges")
        for left, right, name in functions:
            if left < end and start < right:
                raise ValueError(f"{owner}: data 0x{start:08X}-0x{end:08X} placed after code overlaps "
                                 f"function {name} 0x{left:08X}-0x{right:08X}")


def source_root(root):
    """Validate a library-level source root; return (directory, file prefix, build depth).

    Units under `directory` are compiled as `file_prefix/<path below directory>` from a
    staging directory `depth` levels below a `<name>` link to the repository directory,
    so __FILE__ carries the original build's relative spelling."""
    if not isinstance(root, dict) or set(root) != {"directory", "file_prefix", "evidence"} \
            or not isinstance(root["evidence"], str) or not root["evidence"].strip():
        raise ValueError("source_root needs exactly directory, file_prefix and evidence")
    repository_path(root["directory"])
    prefix = root["file_prefix"]
    parts = prefix.split("/") if isinstance(prefix, str) else []
    depth = len(parts) - 1
    if depth < 1 or any(part != ".." for part in parts[:-1]) \
            or not re.fullmatch(r"[A-Za-z0-9_][A-Za-z0-9_.+-]*", parts[-1]):
        raise ValueError("source_root file_prefix must be '../' repeated, then one directory name")
    return Path(root["directory"]), prefix, depth


def repository_path(text):
    if not isinstance(text, str) or not SAFE_PATH.fullmatch(text) or Path(text).is_absolute() \
            or ".." in Path(text).parts:
        raise ValueError(f"Expected a relative repository path: {text!r}")
    return ROOT / text


# Placement plan ---------------------------------------------------------------------------

def plan(sections, units, objects, externals):
    """Resolve placements and symbols. `objects` maps unit source to (sections, symbols)."""
    defined = {}
    for unit in units:
        elf_sections, symbols = objects[unit["source"]]
        # A unit with holdouts links each code run from its own section of the derived object.
        mapped = {entry.get("input", entry["section"]): entry for entry in unit["sections"]}
        for section in elf_sections:
            if not section["flags"] & SHF_ALLOC or (not section["size"] and section["name"] not in mapped):
                continue
            entry = mapped.get(section["name"])
            if entry is None:
                raise ValueError(f"{unit['source']}: compiled section {section['name']} "
                                 f"({section['size']} bytes) has no configured range")
            entry["index"] = section["index"]
            entry["compiled"] = section["size"]
            entry["align"] = max(section["align"], 1)
            expected = {"code": SHT_PROGBITS, "data": SHT_PROGBITS, "bss": SHT_NOBITS}[entry["kind"]]
            executable = bool(section["flags"] & SHF_EXECINSTR)
            entry["executable"] = executable
            # Only read-only initialized data configured to follow the unit's own code may sit
            # inside a code section; everything else keeps the section-kind rule.
            read_only_after_code = entry["kind"] == "code" and entry.get("follows") is not None \
                and not executable and not section["flags"] & SHF_WRITE
            if section["type"] != expected or (executable != (entry["kind"] == "code")
                                               and not read_only_after_code) \
                    or (entry.get("follows") is not None and not read_only_after_code):
                raise ValueError(f"{unit['source']}: {section['name']} cannot be placed in "
                                 f"{entry['kind']} section {entry['placement']}")
            if section["size"] != entry["end"] - entry["start"]:
                raise ValueError(f"{unit['source']}: compiled {section['name']} is {section['size']:#x} "
                                 f"bytes; configured range 0x{entry['start']:08X}-0x{entry['end']:08X} "
                                 f"is {entry['end'] - entry['start']:#x} bytes")
            if entry["start"] % entry["align"]:
                raise ValueError(f"{unit['source']}: {section['name']} alignment {entry['align']} "
                                 f"does not fit 0x{entry['start']:08X}")
        for entry in unit["sections"]:
            if "index" not in entry:
                raise ValueError(f"{unit['source']}: configured section {entry['section']} was not produced")
        for entry in unit["sections"]:
            if entry.get("follows") is None:
                continue
            code = followed_code(unit["sections"], entry)
            if not code["executable"]:
                raise ValueError(f"{unit['source']}: {entry['section']} must follow the unit's own code")
            # The data starts at the first boundary of its own alignment after the code; the
            # linker supplies that padding, which the target must hold as zero bytes.
            aligned = -(-code["end"] // entry["align"]) * entry["align"]
            if entry["start"] != aligned:
                raise ValueError(f"{unit['source']}: {entry['section']} must start at 0x{aligned:08X}, its "
                                 f"{entry['align']}-byte alignment after {code['section']} ends at "
                                 f"0x{code['end']:08X}")
            section = next(s for s in sections if s["name"] == entry["placement"])
            padding = section["contents"][code["end"] - section["start"]:entry["start"] - section["start"]]
            if any(padding):
                raise ValueError(f"{unit['source']}: target padding 0x{code['end']:08X}-0x{entry['start']:08X} "
                                 f"before {entry['section']} is not zero")
        by_index = {entry["index"]: entry for entry in unit["sections"]}
        # Mapped COMMON symbols are undefined references in the link object (common_object), and
        # the unit defines them at their storage addresses.
        for name, (start, _) in (unit.get("storage") or {}).items():
            if name in defined or name in externals:
                raise ValueError(f"{unit['source']}: symbol {name} is already defined elsewhere")
            defined[name] = (start, unit["source"])
        for symbol in symbols:
            if symbol["shndx"] == SHN_COMMON:
                raise ValueError(f"{unit['source']}: common symbol {symbol['name']} has no placement")
            if symbol["bind"] == STB_LOCAL or symbol["shndx"] == SHN_UNDEF:
                continue
            if symbol["shndx"] not in by_index:
                raise ValueError(f"{unit['source']}: {symbol['name']} is defined outside a placed section")
            final = by_index[symbol["shndx"]]["start"] + symbol["value"]
            name = symbol["name"]
            if name in defined or name in externals or name in LINKER_SYMBOLS:
                raise ValueError(f"{unit['source']}: symbol {name} is already defined elsewhere")
            match = NEUTRAL.fullmatch(name)
            if match and int(match[1], 16) != final:
                raise ValueError(f"{unit['source']}: neutral label {name} would be placed at 0x{final:08X}")
            defined[name] = (final, unit["source"])
        for name, value in (unit.get("kept_locals") or {}).items():
            if defined.get(name) != (value, unit["source"]):
                raise ValueError(f"{unit['source']}: kept local {name} is not placed at 0x{value:08X}")
    ranges = sorted((entry["start"], entry["end"], unit["source"], entry)
                    for unit in units for entry in unit["sections"])
    pieces = {section["name"]: [] for section in sections}
    for section in sections:
        cursor = section["start"]
        for start, end, source, entry in ranges:
            if entry["placement"] != section["name"]:
                continue
            # Padding before data that follows its unit's code comes from that data's alignment.
            if start > cursor and entry.get("follows") is None:
                pieces[section["name"]].append({"start": cursor, "end": start, "symbols": []})
            pieces[section["name"]].append({"start": start, "end": end, "unit": source, "entry": entry})
            cursor = end
        if cursor < section["end"]:
            pieces[section["name"]].append({"start": cursor, "end": section["end"], "symbols": []})
    # A mapped COMMON symbol is defined at its storage address by the original-bytes piece that
    # holds it; the unit's COMMON then resolves to that definition, so the linker allocates nothing.
    for unit in units:
        for name, (start, end) in sorted((unit.get("storage") or {}).items(), key=lambda item: item[1]):
            owner = next((piece for section in sections for piece in pieces[section["name"]]
                         if "unit" not in piece and piece["start"] <= start < end <= piece["end"]), None)
            if owner is None:
                raise ValueError(f"{unit['source']}: storage {name} lies inside a source unit's range")
            owner["symbols"].append({"name": name, "value": start - owner["start"]})
    # A global holdout's name resolves to its target address for every unit, as its definition
    # in the original bytes there; references inside its own unit name `__holdout_<start>`.
    held = {}
    for unit in units:
        for name, value in ((unit.get("held") or {}).get("globals") or {}).items():
            if name in defined or name in held or (name in externals and externals[name] != value):
                raise ValueError(f"{unit['source']}: holdout {name} is already defined elsewhere")
            held[name] = value
    resolved = {}
    for unit in units:
        folds = {folded_reference(name): value for name, value in (unit.get("folded") or {}).items()}
        folds.update({holdout_reference(row["start"]): row["start"] for row in unit.get("holdouts") or []})
        for symbol in objects[unit["source"]][1]:
            name = symbol["name"]
            if symbol["shndx"] != SHN_UNDEF or symbol["bind"] == STB_LOCAL or not name:
                continue
            if name in folds:
                value = folds[name]
                if kept_fold(units, unit, name, value, defined, externals):
                    # The copy folded into is another linked unit's kept local; that unit's
                    # object defines the folded reference (keep_object), so the link resolves it.
                    continue
                if name in defined or name in externals or resolved.get(name, value) != value:
                    raise ValueError(f"{unit['source']}: folded reference {name} is ambiguous")
            elif name in defined:
                continue
            elif name in held:
                value = held[name]
            elif name in externals:
                value = externals[name]
            elif NEUTRAL.fullmatch(name):
                value = int(NEUTRAL.fullmatch(name)[1], 16)
            else:
                raise ValueError(f"{unit['source']}: unresolved symbol {name}")
            resolved[name] = value
    for name, value in sorted(resolved.items()):
        owner = None
        for section in sections:
            items = pieces[section["name"]]
            for index, piece in enumerate(items):
                inside = piece["start"] <= value < piece["end"] or (
                    index == len(items) - 1 and value == piece["end"])
                if inside:
                    owner = piece
                    break
            if owner:
                break
        if owner is None:
            if name in externals and outside_image(sections, value):
                # Configured linker-defined addresses before or past the loaded image (e.g. the SDK's
                # _stack_addr) are given to the linker as absolute symbols; see link_script.
                continue
            raise ValueError(f"External {name} at 0x{value:08X} is outside the executable sections")
        if "unit" in owner:
            raise ValueError(f"External {name} at 0x{value:08X} lies inside source unit {owner['unit']}; "
                             "reference that unit's symbol instead")
        owner["symbols"].append({"name": name, "value": value - owner["start"]})
    return pieces, defined, resolved


def kept_fold(units, unit, name, value, defined, externals):
    """Whether folded reference `name` of `unit` resolves to another unit's kept local at `value`."""
    owner = defined.get(name)
    if owner is None or owner[0] != value or owner[1] == unit["source"] or name in externals:
        return False
    other = next(other for other in units if other["source"] == owner[1])
    return (other.get("kept_locals") or {}).get(name[len(folded_reference("")):]) == value


def outside_image(sections, value):
    """Whether an address lies before or after every target section (not in a gap between them)."""
    return value < min(s["start"] for s in sections) or value > max(s["end"] for s in sections)


def link_script(target, sections, pieces, absolute=None):
    lines = ["ENTRY(__start)", "SECTIONS {", f"__start = {target['entry']};",
             f"_SDA_BASE_ = {target['sda_base']};", f"_SDA2_BASE_ = {target['sda2_base']};"]
    lines += [f"{name} = 0x{value:08X};" for name, value in sorted((absolute or {}).items())]
    for section in sections:
        inputs = " ".join(f"*{piece['object'].name}({piece['input']})" for piece in pieces[section["name"]])
        lines.append(f"{section['output']} 0x{section['start']:08X} : {{ {inputs} }}")
    return "\n".join(lines + ["}"]) + "\n"


def check_basenames(paths):
    names = [path.name for path in paths]
    for name in names:
        if not re.fullmatch(r"[A-Za-z0-9_.+-]+", name):
            raise ValueError(f"Object name {name} is not safe for linker patterns")
        if any(other != name and other.endswith(name) for other in names):
            raise ValueError(f"Object name {name} is ambiguous in linker patterns")


def stage(unit):
    """Create the build directory for a source-root unit; return it after checking the mapping."""
    directory, prefix, depth = source_root(unit["source_root"])
    staging = BUILD / "stage" / re.sub(r"[^A-Za-z0-9]+", "_", unit["profile"])
    link = staging / prefix.split("/")[-1]
    workdir = staging.joinpath(*[f"level{index}" for index in range(1, depth + 1)])
    if not link.is_symlink():
        staging.mkdir(parents=True, exist_ok=True)
        link.symlink_to(ROOT / directory, target_is_directory=True)
    workdir.mkdir(parents=True, exist_ok=True)
    if (workdir / unit["compile_path"]).resolve() != unit["path"].resolve():
        raise RuntimeError(f"Compile path {unit['compile_path']} does not reach {unit['source']}")
    return workdir


def dependencies(depfile, base):
    """Map preprocessor dependencies (relative to the compile directory) to repository files."""
    text = depfile.read_text().replace("\\\n", " ")
    items = re.split(r"(?<!\\)\s+", text.split(":", 1)[1].strip()) if ":" in text else []
    result = {}
    for item in filter(None, items):
        path = Path(item.replace("\\ ", " "))
        path = (path if path.is_absolute() else base / path).resolve()
        if not path.is_relative_to(ROOT.resolve()):
            raise ValueError(f"Dependency outside the repository: {path}")
        result[path.relative_to(ROOT.resolve()).as_posix()] = sha256(path)
    return dict(sorted(result.items()))


class CompileCache:
    """Compiler outputs reused by content; only main writes and audits them.

    A unit's lookup key binds its compiler, flags, include path, compile directory,
    source bytes and the pinned compiler and driver files. An entry is used only while
    every dependency the compiler read still has its recorded bytes and no repository
    file with the same name (ignoring case) appeared or vanished, so a new header cannot
    shadow a cached include. In 'use' mode a hit restores the object and depfile; in
    'audit' mode every unit compiles fresh, a cached entry valid for the same inputs must
    hold identical bytes, and the fresh set replaces the cache."""
    TOOLS = ("tools/compiler-tools.json", "tools/prodg_cc.py", "tools/sdk_cc.py", "tools/setup_compiler.py",
             "tools/source_build.py")

    def __init__(self, directory, mode):
        if mode not in ("use", "audit"):
            raise ValueError("Compile cache mode is use or audit")
        self.directory, self.mode = Path(directory), mode
        self.fresh = self.directory.with_name(self.directory.name + ".fresh")
        self.hits = self.misses = self.audited = 0
        self.lock = threading.Lock()
        self.tools = {path: sha256(ROOT / path) for path in self.TOOLS}
        self.digests = {}
        self.names, self.links = {}, []
        for directory_path, directories, files in os.walk(ROOT):
            if Path(directory_path) == ROOT:
                directories[:] = [d for d in directories if d not in (".git", "build")]
            for name in files + directories:
                path = Path(directory_path) / name
                relative = path.relative_to(ROOT).as_posix()
                if path.is_symlink():
                    # A link can make files reachable under new names; any change misses.
                    self.links.append((relative, os.readlink(path)))
                elif name in files:
                    self.names.setdefault(name.lower(), []).append(relative)
        self.links.sort()
        if mode == "audit":
            if self.fresh.exists():
                shutil.rmtree(self.fresh)
            self.fresh.mkdir(parents=True)

    def key(self, unit, includes, workdir, source, comparison):
        material = {"schema": 1, "tools": self.tools, "links": self.links, "comparison": comparison,
                    "source": unit["source"],
                    "source_sha256": sha256(unit["path"]), "compiler": unit["compiler"],
                    "compiler_version": unit.get("compiler_version"), "flags": unit["flags"],
                    "includes": [Path(d).resolve().relative_to(ROOT.resolve()).as_posix() for d in includes],
                    "workdir": Path(workdir).resolve().relative_to(ROOT.resolve()).as_posix(),
                    "compile_source": str(Path(source).relative_to(ROOT)) if Path(source).is_absolute() else source}
        return hashlib.sha256(json.dumps(material, sort_keys=True).encode()).hexdigest()

    def shadows(self, dependencies):
        return {name: sorted(self.names.get(name, []))
                for name in sorted({Path(path).name.lower() for path in dependencies})}

    def valid(self, entry):
        meta = json.loads((entry / "meta.json").read_text())
        return meta if all(self.digest(path) == digest for path, digest in meta["dependencies"].items()) \
            and self.shadows(meta["dependencies"]) == meta["names"] else None

    def digest(self, path):
        if path not in self.digests:
            self.digests[path] = sha256(ROOT / path) if (ROOT / path).is_file() else None
        return self.digests[path]

    def restore(self, key, unit):
        entry = self.directory / key
        if self.mode != "use" or not (entry / "meta.json").is_file() or self.valid(entry) is None:
            with self.lock:
                self.misses += 1
            return False
        shutil.copyfile(entry / "object.o", unit["object"])
        shutil.copyfile(entry / "depfile.d", unit["depfile"])
        with self.lock:
            self.hits += 1
        return True

    def record(self, key, unit):
        if self.mode != "audit":
            return
        meta = {"dependencies": unit["dependencies"], "names": self.shadows(unit["dependencies"])}
        files = {"object.o": unit["object"].read_bytes(), "depfile.d": unit["depfile"].read_bytes()}
        previous = self.directory / key
        if (previous / "meta.json").is_file() and self.valid(previous) is not None:
            if any((previous / name).read_bytes() != data for name, data in files.items()):
                raise ValueError(f"Compile cache disagrees with a fresh compile of {unit['source']}")
            with self.lock:
                self.audited += 1
        entry = self.fresh / key
        entry.mkdir(parents=True, exist_ok=True)
        for name, data in files.items():
            (entry / name).write_bytes(data)
        (entry / "meta.json").write_text(json.dumps(meta, sort_keys=True) + "\n")

    def finish(self):
        if self.mode == "audit":
            if self.directory.exists():
                shutil.rmtree(self.directory)
            self.fresh.rename(self.directory)
        return {"mode": self.mode, "hits": self.hits, "misses": self.misses, "audited": self.audited}


def run(label, command, log):
    """Run a stage; any non-zero exit or warning/error diagnostic fails the build."""
    with log.open("w") as output:
        result = subprocess.run(command, cwd=ROOT, stdout=output, stderr=subprocess.STDOUT,
                                stdin=subprocess.DEVNULL, timeout=LINK_TIMEOUT)
    text = log.read_text(errors="replace")
    if result.returncode or re.search(r"warning|error", text, re.IGNORECASE):
        raise RuntimeError(f"{label} failed or reported diagnostics; see {log}")


def sn_bss_container_size(native, linked, symbols):
    """Recognize SN's word-aligned relocatable BSS tag without source allocation."""
    expected = (native["size"] + 3) & ~3
    if native["name"] != ".bss" or linked["name"] != ".bss" \
            or native["type"] != SHT_NOBITS or linked["type"] != SHT_NOBITS \
            or linked["flags"] != native["flags"] or linked["align"] != native["align"] \
            or linked["size"] != expected or expected == native["size"]:
        raise ValueError("Unrecognized SN BSS container extent")
    owned = [symbol for symbol in symbols if symbol["shndx"] == linked["index"]]
    tags = [symbol for symbol in owned if symbol["name"] == "__sn__bss__tag__"]
    if len(tags) != 1 or tags[0]["value"] != expected or tags[0]["size"] != 0 \
            or tags[0]["type"] != 0 or tags[0]["bind"] != STB_GLOBAL:
        raise ValueError("Unrecognized SN BSS end tag")
    for symbol in owned:
        if symbol is tags[0]:
            continue
        if symbol["value"] > native["size"] \
                or symbol["value"] + symbol["size"] > native["size"]:
            raise ValueError("Retained BSS symbol extends beyond native allocation")
    return expected


def check_retention(unit, native, retained):
    """Check which of the native code functions the retention link kept.

    A folded function's references resolve to the copy it folds into, so its body must go; the
    other functions the linker drops must be exactly the unit's listed discarded ones, if any."""
    folded = set(unit.get("folded") or ())
    if folded & retained:
        raise ValueError(f"{unit['source']}: the linker retained a folded function")
    discarded = unit["link_roots"].get("discarded")
    if discarded is not None and native - retained - folded != set(discarded):
        raise ValueError(f"{unit['source']}: discarded functions differ from link_roots discarded")


def retention_roots(unit):
    """The unit's link_roots symbols, or None: none at all, or a holdouts unit, whose link_roots
    only list discarded functions (holdout_object drops them; its run markers are the roots)."""
    if not unit["link_roots"] or unit.get("holdouts"):
        return None
    return unit["link_roots"]["symbols"]


def link_object(unit, aliases=()):
    """Set the object the unit links: the native object, or its holdouts, folded and/or kept derivative."""
    unit["link_object"], unit["folds"] = unit["object"], {}
    if unit.get("holdouts"):
        unit["link_object"] = unit["object"].with_suffix(".holdouts.o")
        unit["held"] = holdout_object(unit["object"].read_bytes(), unit, unit["link_object"])
    if unit["folded"]:
        unit["link_object"] = unit["object"].with_suffix(".folded.o")
        unit["folds"] = fold_object(unit["object"].read_bytes(), unit["folded"], unit["link_object"])
        if not unit["link_roots"] and any(symbol["type"] == STT_FUNC for symbol, _ in unit["folds"].values()):
            raise ValueError(f"{unit['source']}: a folded function needs link_roots so the linker drops its body")
    if unit.get("storage"):
        derived = unit["object"].with_suffix(".common.o")
        common_object(unit["link_object"].read_bytes(), unit["storage"], derived, unit["source"])
        unit["link_object"] = derived
    if unit.get("kept_locals"):
        derived = unit["link_object"].with_suffix(".kept.o")
        keep_object(unit["link_object"].read_bytes(), unit["kept_locals"], derived, aliases)
        unit["link_object"] = derived
    unit["link_object_sha256"] = sha256(unit["link_object"])


def retained_layout(unit, compiler, wrapper):
    """Inspect SN's retained layout; final linking still consumes the untouched compiler object.

    Static sections retain their native identity and offsets. SN's generated BSS tag
    is linker metadata, absent from the compiler input and excluded from source ownership.
    """
    native = unit["object"]
    sections, symbols = read_elf(native.read_bytes())
    allocated = [section for section in sections if section["flags"] & SHF_ALLOC and section["size"]]
    # Code may sit in .text and, for the SDK's startup routines, in .init; each is laid out
    # by the same strip-unused link and checked the same way.
    code = {".text", ".init"}
    allowed = code | {".rodata", ".data", ".bss", ".sdata", ".sdata2", ".sbss", ".sbss2", ".ctors", ".dtors"}
    native_sections = {section["name"]: section for section in allocated}
    native_text = native_sections.get(".text")
    if native_text is None or not native_text["flags"] & SHF_EXECINSTR \
            or len(native_sections) != len(allocated) or set(native_sections) - allowed:
        raise ValueError(f"{unit['source']}: unsupported native sections for link_roots")
    for section in allocated:
        expected_type = SHT_NOBITS if section["name"] in {".bss", ".sbss", ".sbss2"} else SHT_PROGBITS
        if section["type"] != expected_type \
                or bool(section["flags"] & SHF_EXECINSTR) != (section["name"] in code):
            raise ValueError(f"{unit['source']}: unsupported native section type for link_roots")
    native_code = {section["index"]: section["name"] for section in allocated if section["name"] in code}
    functions = {symbol["name"]: symbol for symbol in symbols if symbol["type"] == 2}
    roots = unit["link_roots"]["symbols"]
    # SDK files define some entry points weak (e.g. OSReport) so a game can replace them;
    # the target kept the SDK copy, so a weak definition is a valid root too.
    if any(name not in functions or functions[name]["bind"] not in (STB_GLOBAL, STB_WEAK)
           or functions[name]["shndx"] not in native_code for name in roots):
        raise ValueError(f"{unit['source']}: retention root is not a defined global function")
    keep = native.with_suffix(".keep")
    keep.write_text("\n".join(roots) + "\n")
    partial = native.with_suffix(".layout.o")
    partial.unlink(missing_ok=True)
    script = native.with_suffix(".layout.ld")
    # A zero SDA anchor underflows SN's range check. These addresses are only for
    # relocatable layout inspection; the final native-object link uses target bases.
    script.write_text("SECTIONS {\n_SDA_BASE_ = 0x8000;\n_SDA2_BASE_ = 0x8000;\n" +
                      "\n".join(f"{name} 0 : {{ *({name}) }}" for name in sorted(allowed)) + "\n}\n")
    before = sha256(native)
    run("Retained-layout link", [str(wrapper), str(compiler / "ngcld.exe"), "-r",
        "-T", str(script), "-strip-unused", "-keep", str(keep), "-o", str(partial), str(native)],
        native.with_suffix(".layout.log"))
    if sha256(native) != before or not partial.is_file() or not partial.stat().st_size:
        raise RuntimeError("Retained-layout linker changed its compiler input or produced no fresh object")
    linked_sections, linked_symbols = read_elf(partial.read_bytes())
    linked_code = {section["name"]: section for section in linked_sections
                   if section["name"] in code and section["flags"] & SHF_ALLOC and section["size"]}
    text = linked_code.get(".text")
    retained = [symbol for symbol in linked_symbols if symbol["type"] == 2]
    if text is None or not retained or not set(roots) <= {symbol["name"] for symbol in retained}:
        raise ValueError("Retained-layout linker omitted required functions")
    for symbol in retained:
        original = functions.get(symbol["name"])
        if original is None or symbol["size"] != original["size"] \
                or original["shndx"] not in native_code \
                or linked_code.get(native_code[original["shndx"]], {}).get("index") != symbol["shndx"]:
            raise ValueError("Retained-layout linker changed a function's identity or size")
    check_retention(unit, {symbol["name"] for symbol in symbols if symbol["type"] == 2
                           and symbol["shndx"] in native_code and symbol["size"] > 0},
                    {symbol["name"] for symbol in retained})
    if set(linked_code) - set(native_sections):
        raise ValueError("Unexpected allocated section from retained-layout linker")
    mapped = list(linked_code.values())
    by_index = {section["index"]: section for section in allocated}
    tag = next((symbol for symbol in linked_symbols
                if symbol["name"] == "__sn__bss__tag__address__"), None)
    for section in linked_sections:
        if not section["flags"] & SHF_ALLOC or not section["size"] or section["name"] in code:
            continue
        original = native_sections.get(section["name"])
        native_size = original["size"] if original else 0
        expected_size = native_size
        if original and section["name"] == ".bss" and section["size"] != native_size:
            expected_size = sn_bss_container_size(original, section, linked_symbols)
        if section["name"] == ".data":
            if tag is None or tag["shndx"] != section["index"] \
                    or tag["value"] != ((native_size + 3) & ~3):
                raise ValueError("Unrecognized generated SN BSS tag")
            expected_size = tag["value"] + 4
        if section["size"] != expected_size or (original is None and section["name"] != ".data"):
            raise ValueError("Unexpected allocated section from retained-layout linker")
        if original:
            if section["type"] != original["type"] or section["flags"] != original["flags"]:
                raise ValueError("Retained-layout linker changed a static section's type or flags")
            section["size"] = native_size
            if "data" in section:
                section["data"] = section["data"][:native_size]
            mapped.append(section)
    if {section["name"] for section in mapped} != set(native_sections):
        raise ValueError("Retained-layout linker omitted a native static section")
    mapped_indices = {section["index"] for section in mapped}
    linked_by_name = {section["name"]: section for section in mapped}
    for symbol in symbols:
        original = by_index.get(symbol["shndx"])
        if original is None or original["name"] in code or symbol["type"] not in {1, 2}:
            continue
        retained_symbol = next((other for other in linked_symbols
                                if other["name"] == symbol["name"]), None)
        if retained_symbol is None or retained_symbol["size"] != symbol["size"] \
                or retained_symbol["value"] != symbol["value"] \
                or retained_symbol["shndx"] != linked_by_name[original["name"]]["index"]:
            raise ValueError("Retained-layout linker changed a static symbol's identity or offset")
    referenced = set()
    linked_bytes = partial.read_bytes()
    for section in linked_sections:
        if section["type"] == 4 and section["info"] in mapped_indices:
            for offset in range(section["offset"], section["offset"] + section["size"], 12):
                at, info = struct.unpack_from(">II", linked_bytes, offset)
                owned = next(entry for entry in mapped if entry["index"] == section["info"])
                if at >= owned["size"]:
                    continue
                index = info >> 8
                if index == 0 or index > len(linked_symbols):
                    raise ValueError("Invalid retained-layout relocation symbol")
                referenced.add(linked_symbols[index - 1]["name"])
    # SN preserves some unused undefined symbol-table entries after removing their relocations.
    generated = {"__sn__bss__tag__address__", "__sn__bss__tag__"}
    used_symbols = [symbol for symbol in linked_symbols if symbol["name"] not in generated
                    and (symbol["shndx"] in mapped_indices or symbol["shndx"] == SHN_COMMON
                         or (symbol["shndx"] == SHN_UNDEF and symbol["name"] in referenced))]
    unit["native_object_sha256"] = before
    return mapped, used_symbols


# Build ------------------------------------------------------------------------------------

def compile_unit(unit, compiler, wrapper, sdk_directory, include_dirs, comparison=False, cache=None):
    if any("DECOMP_COMPARE" in flag for flag in unit["flags"]):
        raise ValueError("DECOMP_COMPARE is a reserved global build mode")
    workdir, source = ROOT, str(unit["path"])
    if unit["compile_path"]:
        workdir, source = stage(unit), unit["compile_path"]
    includes = [ROOT / directory for directory in include_dirs + unit["include_dirs"]]
    key = cache.key(unit, includes, workdir, source, comparison) if cache is not None else None
    if cache is not None and cache.restore(key, unit):
        unit["dependencies"] = dependencies(unit["depfile"], workdir)
        return
    if unit["compiler"] == "mwcc":
        # sdk_directory is setup_compiler.setup_sdks(): one directory per pinned SDK version.
        sdk_cc.compile(sdk_directory[unit["compiler_version"]], wrapper, source, unit["object"], unit["depfile"],
                       unit["flags"], includes, workdir, comparison=comparison)
    else:
        command = [sys.executable, str(ROOT / "tools/prodg_cc.py"), "--dir", str(compiler),
                   "--wrapper", str(wrapper), "--depfile", str(unit["depfile"])]
        for directory in includes:
            command += ["-I", str(directory)]
        if comparison:
            command += ["-DDECOMP_COMPARE=1"]
        command += unit["flags"] + ["-c", source, "-o", str(unit["object"])]
        result = subprocess.run(command, cwd=workdir, stdin=subprocess.DEVNULL)
        if result.returncode or not unit["object"].is_file():
            raise RuntimeError(f"Compilation failed for {unit['source']}")
    unit["dependencies"] = dependencies(unit["depfile"], workdir)
    if cache is not None:
        cache.record(key, unit)


def build(original, manifest_path, report_path, cache=None):
    report_path.unlink(missing_ok=True)
    target = json.loads((ROOT / "config/GN7E69-rev0/baseline.json").read_text())
    binary = original.read_bytes()
    if len(binary) != target["size"] or hashlib.sha1(binary).hexdigest() != target["sha1"]:
        raise RuntimeError("Original executable does not match the configured target")
    small_data = json.loads((ROOT / "config/GN7E69-rev0/analysis.json").read_text())["output_sections"]
    sections = target_sections(binary, target, small_data)
    compiler_lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    manifest_bytes = manifest_path.read_bytes()
    units, externals, include_dirs = load_manifest(json.loads(manifest_bytes), sections,
                                                   compiler_lock["compiler_version"])
    check_data_in_code([(entry["start"], entry["end"], unit["source"]) for unit in units
                        for entry in unit["sections"] if entry["follows"] is not None],
                       function_extents(ROOT), data_extents(ROOT))
    check_storage(units, data_extents(ROOT), sections)
    if BUILD.exists():
        shutil.rmtree(BUILD)
    (BUILD / "obj").mkdir(parents=True)
    (BUILD / "original").mkdir()
    compiler, wrapper = setup_compiler.setup()
    system = baseline_system()
    dtk = baseline.get_tool("dtk", json.loads((ROOT / "tools/baseline-tools.json").read_text()), system)
    objects = {}
    strip_unused = any(unit["link_roots"] is not None for unit in units)
    original_roots = []
    sdk_directory = setup_compiler.setup_sdks(u["compiler_version"] for u in units if u["compiler"] == "mwcc")
    for index, unit in enumerate(units):
        stem = re.sub(r"[^A-Za-z0-9]+", "_", unit["source"]).strip("_")
        unit["object"] = BUILD / "obj" / f"unit{index:03d}_{stem}.o"
        unit["depfile"] = unit["object"].with_suffix(".d")
    # Each compile writes only its own object, depfile and temporary folder, and the shared
    # staging links exist once staged, so compiles run together. Their failures are raised in
    # manifest order, each just before that unit would link, as one compile at a time would.
    failures = {}
    for unit in units:
        if unit["compile_path"]:
            try:
                stage(unit)
            except Exception as error:
                failures[unit["source"]] = error

    def attempt(unit):
        if unit["source"] in failures:
            return
        try:
            compile_unit(unit, compiler, wrapper, sdk_directory, include_dirs, cache=cache)
        except Exception as error:
            failures[unit["source"]] = error
    with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count() or 1) as pool:
        list(pool.map(attempt, units))
    folded_names = {name for unit in units for name in (unit.get("folded") or ())}
    for unit in units:
        if unit["source"] in failures:
            raise failures[unit["source"]]
        unit["native_object_sha256"] = sha256(unit["object"])
        link_object(unit, folded_names & set(unit.get("kept_locals") or ()))
        # A holdouts unit's discarded functions are already gone from its derived object.
        objects[unit["source"]] = (retained_layout(dict(unit, object=unit["link_object"]), compiler, wrapper)
                                   if retention_roots(unit) else read_elf(unit["link_object"].read_bytes()))
    pieces, defined, resolved = plan(sections, units, objects, externals)
    references = {**externals, **resolved, **{name: value for name, (value, _) in defined.items()}}
    for unit in units:
        check_folded_functions(unit, target, sections, binary, references, compiler, wrapper)
        check_holdouts(unit, target, sections, binary, references, compiler, wrapper)
    for section in sections:
        for piece in pieces[section["name"]]:
            if "unit" in piece:
                unit = next(u for u in units if u["source"] == piece["unit"])
                piece["object"] = unit["link_object"]
                piece["input"] = piece["entry"].get("input", piece["entry"]["section"])
                continue
            piece["object"] = BUILD / "original" / f"orig_{section['name'].strip('.')}_{piece['start']:08X}.o"
            piece["input"] = section["output"]
            size = piece["end"] - piece["start"]
            flags = SHF_ALLOC | (SHF_EXECINSTR if section["kind"] == "code" else SHF_WRITE)
            entry = {"name": section["output"], "flags": flags, "size": size, "align": 1,
                     "type": SHT_NOBITS if section["kind"] == "bss" else SHT_PROGBITS}
            if section["kind"] != "bss":
                offset = piece["start"] - section["start"]
                entry["data"] = section["contents"][offset:offset + size]
            symbols = [{"name": s["name"], "value": s["value"], "shndx": 1} for s in piece["symbols"]]
            if strip_unused:
                marker = "__original_" + piece["object"].stem
                original_roots.append(marker)
                symbols.append({"name": marker, "value": 0, "size": size, "shndx": 1})
            write_object(piece["object"], [entry], symbols)
    inputs = [piece["object"] for section in sections for piece in pieces[section["name"]]]
    inputs = list(dict.fromkeys(inputs))
    check_basenames(inputs)
    script = BUILD / "link.ld"
    absolute = {name: value for name, value in resolved.items()
                if name in externals and outside_image(sections, value)}
    script.write_text(link_script(target, sections, pieces, absolute))
    elf, output = BUILD / "main.elf", BUILD / "main.dol"
    linker_flags = []
    if strip_unused:
        roots = set(original_roots)
        for unit in units:
            roots.update(retention_roots(unit) or
                         [symbol["name"] for symbol in objects[unit["source"]][1]
                          if symbol["bind"] == STB_GLOBAL and symbol["shndx"] != SHN_UNDEF])
        keep = BUILD / "keep.txt"
        keep.write_text("\n".join(sorted(roots)) + "\n")
        linker_flags = ["-strip-unused", "-keep", str(keep)]
    arguments = [*linker_flags, "-T", str(script), "-o", str(elf)] + [str(path) for path in inputs]
    response = BUILD / "link.rsp"
    if any(any(character in argument for character in '\0\n\r"') for argument in arguments):
        raise ValueError("Linker argument cannot be represented safely in a response file")
    response.write_text("\n".join('"' + argument + '"' for argument in arguments) + "\n")
    run("ngcld", [str(wrapper), str(compiler / "ngcld.exe"), "@" + str(response)], BUILD / "link.log")
    if not elf.is_file() or not elf.stat().st_size:
        raise RuntimeError("Linker did not produce a fresh ELF")
    if any(sha256(unit["object"]) != unit["native_object_sha256"]
           or sha256(unit["link_object"]) != unit["link_object_sha256"] for unit in units):
        raise RuntimeError("Final linker input no longer equals the native compiler object "
                           "or its derived link object")
    final = {s["name"]: s["value"] for s in read_elf(elf.read_bytes())[1] if s["bind"] != STB_LOCAL}
    for name, (value, source) in defined.items():
        if final.get(name) != value:
            raise RuntimeError(f"{source}: {name} was not linked at its configured address 0x{value:08X}")
    run("elf2dol", [str(dtk), "elf2dol", str(elf), str(output)], BUILD / "convert.log")
    if not output.is_file() or not output.stat().st_size:
        raise RuntimeError("Converter did not produce a fresh DOL")
    result = output.read_bytes()
    for unit in units:
        check_folded_objects(unit, binary, result)
    identical = result == binary and hashlib.sha1(result).hexdigest() == target["sha1"]
    report = measure(target, sections, units, manifest_bytes, result, identical, resolved, objects)
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, indent=2) + "\n")
    if not identical:
        raise RuntimeError(f"Source build differs from the complete target; see {report_path}")
    return report


def check_folded_functions(unit, target, sections, binary, references, compiler, wrapper):
    """A folded function has no code of its own in the target. Linked alone at the address it
    folds into, its compiled body must reproduce the target bytes there."""
    import diagnostic_object
    placements = {entry["section"]: entry for entry in unit["sections"]}
    for name, (symbol, section) in unit["folds"].items():
        if symbol["type"] != STT_FUNC:
            continue
        start, size = unit["folded"][name], symbol["size"]
        directory = BUILD / "folded" / re.sub(r"[^A-Za-z0-9]+", "_", f"{unit['source']}_{name}").strip("_")
        directory.mkdir(parents=True)
        fragment = directory / "fragment.o"
        label, objects, script = diagnostic_object.fragment(
            unit["link_object"].read_bytes(), section, symbol["value"], size, start, {}, {}, placements,
            references, fragment, sections)
        (directory / "link.ld").write_text(
            f"SECTIONS {{\n_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n"
            f"{section['name']} 0x{start:08X} : {{ *({section['name']}) }}\n" + "\n".join(script) + "\n}\n")
        output = directory / "linked.elf"
        run("Folded function link", [str(wrapper), str(compiler / "ngcld.exe"), "-T", str(directory / "link.ld"),
            "-o", str(output), str(fragment), *map(str, objects)], directory / "link.log")
        linked_sections, linked_symbols = read_elf(output.read_bytes())
        found = [s for s in linked_symbols if s["name"] == label and s["type"] == STT_FUNC]
        placed = next((s for s in linked_sections if found and s["index"] == found[0]["shndx"]), None)
        actual = placed["data"][start - placed["addr"]:start - placed["addr"] + size] \
            if placed and len(found) == 1 and found[0]["value"] == start else None
        if actual is None or actual != dol_bytes(binary, start, start + size):
            raise ValueError(f"{unit['source']}: folded function {name} differs from the target "
                             f"bytes at 0x{start:08X}")


def check_folded_objects(unit, binary, result):
    """A folded object keeps its bytes in place, unreferenced; as linked they must equal the
    target bytes of the object it folds into."""
    placements = {entry["section"]: entry for entry in unit["sections"]}
    for name, (symbol, section) in unit["folds"].items():
        if symbol["type"] != STT_OBJECT:
            continue
        here = placements[section["name"]]["start"] + symbol["value"]
        there = unit["folded"][name]
        copy = dol_bytes(result, here, here + symbol["size"])
        if copy is None or copy != dol_bytes(binary, there, there + symbol["size"]):
            raise ValueError(f"{unit['source']}: folded object {name} at 0x{here:08X} differs from the "
                             f"target bytes at 0x{there:08X}")


def check_holdouts(unit, target, sections, binary, references, compiler, wrapper):
    """A holdout must not be exact. Linked alone at its target start, as the comparisons measure
    it, a holdout of the target's size must differ from the original bytes there; a holdout of
    another size differs already. An exact function is linked, not held out."""
    if not unit.get("holdouts"):
        return
    native = unit["object"].read_bytes()
    elf_sections, symbols = read_elf(native)
    functions = {symbol["name"]: symbol for symbol in symbols
                 if symbol["type"] == STT_FUNC and symbol["shndx"] != SHN_UNDEF and symbol["size"]}
    for row in unit["holdouts"]:
        if functions[row["symbol"]]["size"] != row["end"] - row["start"]:
            continue
        actual = link_holdout(unit, row, native, elf_sections, symbols, functions, target, sections, references,
                              compiler, wrapper)
        if actual == dol_bytes(binary, row["start"], row["end"]):
            raise ValueError(f"{unit['source']}: holdout {row['symbol']} 0x{row['start']:08X} is exact; link it "
                             "instead of holding it out")


def link_holdout(unit, row, native, elf_sections, symbols, functions, target, sections, references, compiler, wrapper):
    """Link one holdout's compiled body alone at its target start; return the linked bytes."""
    import diagnostic_object
    targets = {name: (at, at + functions[name]["size"]) for name, at in unit["held"]["linked"].items()}
    targets.update({row["symbol"]: (row["start"], row["end"]) for row in unit["holdouts"]})
    placements = {entry["section"]: entry for entry in unit["sections"] if not entry.get("input")}
    storage = None
    if any(symbol["shndx"] == SHN_COMMON for symbol in symbols):
        # Mapped COMMON symbols, and then each uninitialized object, resolve one by one.
        nobits = {s["index"]: s["name"] for s in elf_sections if s["type"] == SHT_NOBITS and s["flags"] & SHF_ALLOC}
        storage = {}
        for index, symbol in enumerate(symbols):
            if symbol["shndx"] == SHN_COMMON and symbol["name"] in (unit.get("storage") or {}):
                storage[index] = unit["storage"][symbol["name"]][0]
            elif symbol["shndx"] in nobits and symbol["size"] and nobits[symbol["shndx"]] in placements:
                storage[index] = placements[nobits[symbol["shndx"]]]["start"] + symbol["value"]
    symbol = functions[row["symbol"]]
    section = next(s for s in elf_sections if s["index"] == symbol["shndx"])
    directory = BUILD / "holdouts" / re.sub(r"[^A-Za-z0-9]+", "_", f"{unit['source']}_{row['symbol']}").strip("_")
    directory.mkdir(parents=True)
    fragment = directory / "fragment.o"
    label, objects, script = diagnostic_object.fragment(
        native, dict(section, name=".text"), symbol["value"], symbol["size"], row["start"], functions, targets,
        placements, references, fragment, sections, storage)
    (directory / "link.ld").write_text(
        f"SECTIONS {{\n_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n"
        f".text 0x{row['start']:08X} : {{ *(.text) }}\n" + "\n".join(script) + "\n}\n")
    output = directory / "linked.elf"
    run("Holdout link", [str(wrapper), str(compiler / "ngcld.exe"), "-T", str(directory / "link.ld"),
        "-o", str(output), str(fragment), *map(str, objects)], directory / "link.log")
    linked_sections, linked_symbols = read_elf(output.read_bytes())
    found = [s for s in linked_symbols if s["name"] == label and s["type"] == STT_FUNC]
    placed = next((s for s in linked_sections if found and s["index"] == found[0]["shndx"]), None)
    if not placed or len(found) != 1 or found[0]["value"] != row["start"]:
        raise ValueError(f"{unit['source']}: holdout {row['symbol']} could not be linked alone at 0x{row['start']:08X}")
    return placed["data"][row["start"] - placed["addr"]:row["start"] - placed["addr"] + symbol["size"]]


def baseline_system():
    system = f"{platform.system().lower()}-{platform.machine().lower()}"
    return {"darwin-arm64": "macos-arm64", "linux-amd64": "linux-x86_64"}.get(system, system)


def dol_bytes(binary, start, end):
    """Bytes of a loaded address range in a DOL, or None if it is not loaded contiguously."""
    for index in range(18):
        offset, base, size = (struct.unpack_from(">I", binary, b + index * 4)[0] for b in (0, 0x48, 0x90))
        if size and base <= start and end <= base + size:
            return binary[offset + start - base:offset + end - base]
    return None


def compiled_functions(unit, obj):
    """Inventory retained compiler functions, including local and generated symbols."""
    placements = {entry["index"]: entry for entry in unit["sections"]}
    functions, seen = [], set()
    for symbol in obj[1]:
        if symbol["type"] != STT_FUNC or symbol["shndx"] == SHN_UNDEF or symbol["size"] <= 0:
            continue
        # A kept local's global copy (keep_object) names the same function once more, and its
        # alias for another unit's folded references (`__folded_<name>`) once again.
        identity = (symbol["name"], symbol["shndx"], symbol["value"], symbol["size"])
        if identity in seen or symbol["name"].startswith(folded_reference("")):
            continue
        seen.add(identity)
        entry = placements.get(symbol["shndx"])
        if entry is None or entry["kind"] != "code" or entry.get("executable") is False:
            raise ValueError(f"{unit['source']}: compiler function {symbol['name']} has no code placement")
        if not symbol["name"] or symbol["value"] < 0 or symbol["value"] + symbol["size"] > entry["compiled"]:
            raise ValueError(f"{unit['source']}: compiler function {symbol['name']} exceeds its section")
        functions.append({"symbol": symbol["name"],
                          "address": f"0x{entry['start'] + symbol['value']:08X}",
                          "size": symbol["size"]})
    return sorted(functions, key=lambda function: (function["address"], function["symbol"]))


def measure(target, sections, units, manifest_bytes, result, identical, resolved, objects):
    totals = {kind: {"linked": 0, "matched": 0} for kind in ("code", "data")}
    measured = []
    lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    compilers, profile_compilers = {}, {}
    for unit in units:
        family = unit["compiler"]
        pinned = lock["sdk_compiler_version"] if family == "mwcc" else lock["compiler_version"]
        # A unit's own version is its profile's (an SDK profile may select another pinned one).
        version = unit.get("compiler_version") or pinned
        compilers[family] = pinned
        if version != pinned:
            profile_compilers[unit["profile"]] = version
        entries = []
        for entry in unit["sections"]:
            size = entry["end"] - entry["start"]
            if entry["kind"] == "bss":
                same = identical
            else:
                section = next(s for s in sections if s["name"] == entry["placement"])
                offset = entry["start"] - section["start"]
                expected = section["contents"][offset:offset + size]
                same = dol_bytes(result, entry["start"], entry["end"]) == expected
            status = "matched" if identical else ("range-identical" if same else "differs")
            kind = "code" if entry["kind"] == "code" else "data"
            totals[kind]["linked"] += size
            totals[kind]["matched"] += size if identical else 0
            entries.append({"section": entry["section"], "placement": entry["placement"], "kind": kind,
                            "start": f"0x{entry['start']:08X}", "end": f"0x{entry['end']:08X}",
                            "compiled": entry["compiled"], "linked": size,
                            "matched": size if identical else 0, "status": status})
            if entry.get("follows") is not None:
                entries[-1]["follows"] = entry["follows"]
        measured.append({"source": unit["source"], "compile_path": unit["compile_path"],
                         "source_sha256": sha256(unit["path"]),
                         "profile": unit["profile"], "flags": unit["flags"],
                         "compiler": {"family": family, "version": version},
                         "dependencies": unit["dependencies"],
                         "link_roots": unit.get("link_roots"),
                         "folded": {name: f"0x{value:08X}" for name, value in unit["folded"].items()}
                         if unit.get("folded") else None,
                         "storage": {name: f"0x{start:08X}" for name, (start, _) in unit["storage"].items()}
                         if unit.get("storage") else None,
                         "kept_locals": {name: f"0x{value:08X}" for name, value in unit["kept_locals"].items()}
                         if unit.get("kept_locals") else None,
                         # What the derived object dropped: each holdout's target range keeps the
                         # original bytes, and its compiled size and HOLDOUT: row are recorded.
                         "holdouts": [{"symbol": row["symbol"], "start": f"0x{row['start']:08X}",
                                       "end": f"0x{row['end']:08X}", "compiled": row["compiled"],
                                       "evidence": row["evidence"]}
                                      for row in unit["held"]["dropped"]] if unit.get("holdouts") else None,
                         "native_object_sha256": unit.get("native_object_sha256"),
                         "link_object_sha256": unit.get("link_object_sha256"),
                         "status": "matched" if identical else "unverified", "sections": entries,
                         "functions": compiled_functions(unit, objects[unit["source"]])})
    return {"schema": 1, "target": "GN7E69-rev0", "target_sha1": target["sha1"],
            "manifest_sha256": hashlib.sha256(manifest_bytes).hexdigest(),
            "compilers": dict(sorted(compilers.items())),
            "profile_compilers": dict(sorted(profile_compilers.items())),
            "linker": "ngcld (ProDG) via wibo", "complete": "identical" if identical else "mismatch",
            "output_sha1": hashlib.sha1(result).hexdigest(),
            "tools": {path: sha256(ROOT / path) if (ROOT / path).is_file() else None
                      for path in TRUSTED_TOOLS},
            "externals": {name: f"0x{value:08X}" for name, value in sorted(resolved.items())},
            "units": measured, "totals": totals}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, default=ROOT / "config/GN7E69-rev0/units.json")
    parser.add_argument("--report", type=Path, default=BUILD / "report.json")
    parser.add_argument("--compile-cache", type=Path, help="Compiler output cache directory (written only by main)")
    parser.add_argument("--cache-mode", choices=("use", "audit"),
                        help="use: reuse cached objects; audit: compile fresh, verify and replace the cache")
    args = parser.parse_args()
    if (args.compile_cache is None) != (args.cache_mode is None):
        parser.error("--compile-cache and --cache-mode go together")
    cache = CompileCache(args.compile_cache.resolve(), args.cache_mode) if args.cache_mode else None
    report = build(args.original.resolve(), args.manifest.resolve(), args.report.resolve(), cache)
    if cache is not None:
        stats = cache.finish()
        (BUILD / "compile-cache.json").write_text(json.dumps(stats) + "\n")
        print(f"Compile cache ({stats['mode']}): {stats['hits']} reused, {stats['misses']} compiled, "
              f"{stats['audited']} audited against fresh objects")
    code, data = report["totals"]["code"], report["totals"]["data"]
    for unit in report["units"]:
        if unit.get("holdouts"):
            held = sum(int(row["end"], 16) - int(row["start"], 16) for row in unit["holdouts"])
            print(f"Holdouts: {unit['source']} links {sum(s['kind'] == 'code' and not s.get('follows') for s in unit['sections'])} code run(s); "
                  f"{len(unit['holdouts'])} function(s), {held} bytes, keep the original bytes: "
                  + ", ".join(row["symbol"] for row in unit["holdouts"]))
    print(f"Source build verified: {len(report['units'])} unit(s), output SHA-1 {report['output_sha1']}")
    print(f"Source code bytes linked/matched: {code['linked']}/{code['matched']}; "
          f"data: {data['linked']}/{data['matched']}")


if __name__ == "__main__":
    try:
        main()
    except (ValueError, RuntimeError) as error:
        sys.exit(f"source_build: {error}")
