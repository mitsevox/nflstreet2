#!/usr/bin/env python3
"""Link compiled source units in place of their configured original ranges and verify the target."""

import argparse
import hashlib
import json
import platform
import re
import shutil
import struct
import subprocess
import sys
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
# Build inputs the report is bound to; tools/progress.py rejects reports from other versions.
TRUSTED_TOOLS = ("tools/source_build.py", "tools/prodg_cc.py", "tools/sdk_cc.py", "tools/setup_compiler.py",
                 "tools/baseline.py", "tools/compiler-tools.json", "tools/baseline-tools.json",
                 "config/GN7E69/baseline.json", "config/GN7E69/analysis.json")

SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB, SHT_NOBITS = 1, 2, 3, 8
SHF_WRITE, SHF_ALLOC, SHF_EXECINSTR = 1, 2, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STB_LOCAL, STB_GLOBAL = 0, 1
STT_FUNC, STT_SECTION, STT_FILE = 2, 3, 4


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


def load_manifest(manifest, sections, compiler_version):
    if manifest.get("schema") != 1 or manifest.get("target") != "GN7E69":
        raise ValueError("Unit manifest must use schema 1 for target GN7E69")
    if manifest.get("compiler") != compiler_version:
        raise ValueError("Unit manifest compiler differs from the pinned compiler")
    allowed = {"schema", "target", "compiler", "include_dirs", "profiles", "externals", "units"}
    if set(manifest) - allowed:
        raise ValueError(f"Unknown manifest fields: {sorted(set(manifest) - allowed)}")
    for directory in manifest.get("include_dirs", []):
        repository_path(directory)
    profiles = manifest.get("profiles", {})
    for name, profile in profiles.items():
        if set(profile) - {"source_root", "compiler", "include_dirs"} != {"flags", "evidence"} or not profile["evidence"].strip():
            raise ValueError(f"Profile {name} needs flags, an evidence locator and optionally source_root")
        if "source_root" in profile:
            source_root(profile["source_root"])
        compiler = profile.get("compiler", "prodg")
        if compiler not in {"prodg", "mwcc"}:
            raise ValueError(f"Profile {name} uses an unsupported compiler")
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
    units, ranges, sources = [], [], set()
    for unit in manifest.get("units", []):
        if set(unit) - {"link_roots"} != {"source", "profile", "evidence", "sections"} or not unit["evidence"].strip():
            raise ValueError("Each unit needs exactly source, profile, evidence and sections; "
                             "flags belong to a profile")
        source = repository_path(unit["source"])
        if unit["source"] in sources:
            raise ValueError(f"Duplicate unit source {unit['source']}")
        sources.add(unit["source"])
        if unit["profile"] not in profiles:
            raise ValueError(f"Unit {unit['source']} uses unknown profile {unit['profile']}")
        roots = unit.get("link_roots")
        if roots is not None:
            if profiles[unit["profile"]].get("compiler", "prodg") != "mwcc" \
                    or not isinstance(roots, dict) or set(roots) != {"symbols", "evidence"} \
                    or not isinstance(roots["evidence"], str) or not roots["evidence"].strip() \
                    or not isinstance(roots["symbols"], list) or not roots["symbols"] \
                    or not all(isinstance(n, str) and re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", n)
                               and n not in LINKER_SYMBOLS and not n.startswith("__original_")
                               for n in roots["symbols"]) \
                    or len(set(roots["symbols"])) != len(roots["symbols"]):
                raise ValueError("SDK link_roots need distinct symbol names and retention evidence")
        placed = []
        for entry in unit["sections"]:
            if set(entry) != {"section", "placement", "start", "end"}:
                raise ValueError(f"Unit {unit['source']} section entries need section, placement, start, end")
            target = by_name.get(entry["placement"])
            start, end = address(entry["start"]), address(entry["end"])
            if target is None or not target["start"] <= start < end <= target["end"]:
                raise ValueError(f"{unit['source']} {entry['section']} range is outside {entry['placement']}")
            if any(entry["section"] == other["section"] for other in placed):
                raise ValueError(f"{unit['source']} maps {entry['section']} more than once")
            placed.append({"section": entry["section"], "placement": entry["placement"],
                           "start": start, "end": end, "kind": target["kind"]})
            ranges.append((start, end, unit["source"]))
        if not placed:
            raise ValueError(f"Unit {unit['source']} has no configured ranges")
        root = profiles[unit["profile"]].get("source_root")
        compile_path = None
        if root:
            directory, prefix, depth = source_root(root)
            relative = Path(unit["source"]).relative_to(directory) \
                if Path(unit["source"]).is_relative_to(directory) else None
            if relative is None:
                raise ValueError(f"Unit {unit['source']} is outside its profile's source root {directory}")
            compile_path = f"{prefix}/{relative.as_posix()}"
        units.append({"source": unit["source"], "path": source, "profile": unit["profile"],
                      "flags": profiles[unit["profile"]]["flags"], "sections": placed,
                      "compiler": profiles[unit["profile"]].get("compiler", "prodg"),
                      "include_dirs": profiles[unit["profile"]].get("include_dirs", []),
                      "source_root": root, "compile_path": compile_path, "link_roots": roots})
    ranges.sort()
    for left, right in zip(ranges, ranges[1:]):
        if right[0] < left[1]:
            raise ValueError(f"Configured ranges overlap: {left[2]} and {right[2]}")
    return units, externals, [directory for directory in manifest.get("include_dirs", [])]


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
        mapped = {entry["section"]: entry for entry in unit["sections"]}
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
            if section["type"] != expected or executable != (entry["kind"] == "code"):
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
        by_index = {entry["index"]: entry for entry in unit["sections"]}
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
    ranges = sorted((entry["start"], entry["end"], unit["source"], entry)
                    for unit in units for entry in unit["sections"])
    pieces = {section["name"]: [] for section in sections}
    for section in sections:
        cursor = section["start"]
        for start, end, source, entry in ranges:
            if entry["placement"] != section["name"]:
                continue
            if start > cursor:
                pieces[section["name"]].append({"start": cursor, "end": start, "symbols": []})
            pieces[section["name"]].append({"start": start, "end": end, "unit": source, "entry": entry})
            cursor = end
        if cursor < section["end"]:
            pieces[section["name"]].append({"start": cursor, "end": section["end"], "symbols": []})
    resolved = {}
    for unit in units:
        for symbol in objects[unit["source"]][1]:
            name = symbol["name"]
            if symbol["shndx"] != SHN_UNDEF or symbol["bind"] == STB_LOCAL or not name or name in defined:
                continue
            if name in externals:
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
            raise ValueError(f"External {name} at 0x{value:08X} is outside the executable sections")
        if "unit" in owner:
            raise ValueError(f"External {name} at 0x{value:08X} lies inside source unit {owner['unit']}; "
                             "reference that unit's symbol instead")
        owner["symbols"].append({"name": name, "value": value - owner["start"]})
    return pieces, defined, resolved


def link_script(target, sections, pieces):
    lines = ["ENTRY(__start)", "SECTIONS {", f"__start = {target['entry']};",
             f"_SDA_BASE_ = {target['sda_base']};", f"_SDA2_BASE_ = {target['sda2_base']};"]
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


def run(label, command, log):
    """Run a stage; any non-zero exit or warning/error diagnostic fails the build."""
    with log.open("w") as output:
        result = subprocess.run(command, cwd=ROOT, stdout=output, stderr=subprocess.STDOUT,
                                stdin=subprocess.DEVNULL, timeout=LINK_TIMEOUT)
    text = log.read_text(errors="replace")
    if result.returncode or re.search(r"warning|error", text, re.IGNORECASE):
        raise RuntimeError(f"{label} failed or reported diagnostics; see {log}")


def retained_layout(unit, compiler, wrapper):
    """Inspect SN's retained layout; final linking still consumes the untouched compiler object.

    Static sections retain their native identity and offsets. SN's generated BSS tag
    is linker metadata, absent from the compiler input and excluded from source ownership.
    """
    native = unit["object"]
    sections, symbols = read_elf(native.read_bytes())
    allocated = [section for section in sections if section["flags"] & SHF_ALLOC and section["size"]]
    allowed = {".text", ".rodata", ".data", ".bss", ".sdata", ".sdata2", ".sbss", ".sbss2"}
    native_sections = {section["name"]: section for section in allocated}
    native_text = native_sections.get(".text")
    if native_text is None or not native_text["flags"] & SHF_EXECINSTR \
            or len(native_sections) != len(allocated) or set(native_sections) - allowed:
        raise ValueError(f"{unit['source']}: unsupported native SDK sections")
    for section in allocated:
        expected_type = SHT_NOBITS if section["name"] in {".bss", ".sbss", ".sbss2"} else SHT_PROGBITS
        if section["type"] != expected_type \
                or bool(section["flags"] & SHF_EXECINSTR) != (section["name"] == ".text"):
            raise ValueError(f"{unit['source']}: unsupported native SDK section type")
    functions = {symbol["name"]: symbol for symbol in symbols if symbol["type"] == 2}
    roots = unit["link_roots"]["symbols"]
    if any(name not in functions or functions[name]["bind"] != STB_GLOBAL
           or functions[name]["shndx"] != native_text["index"] for name in roots):
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
    run("SDK retained-layout link", [str(wrapper), str(compiler / "ngcld.exe"), "-r",
        "-T", str(script), "-strip-unused", "-keep", str(keep), "-o", str(partial), str(native)],
        native.with_suffix(".layout.log"))
    if sha256(native) != before or not partial.is_file() or not partial.stat().st_size:
        raise RuntimeError("Retained-layout linker changed its compiler input or produced no fresh object")
    linked_sections, linked_symbols = read_elf(partial.read_bytes())
    text = next((section for section in linked_sections if section["name"] == ".text"), None)
    retained = [symbol for symbol in linked_symbols if symbol["type"] == 2]
    if text is None or not retained or not set(roots) <= {symbol["name"] for symbol in retained}:
        raise ValueError("Retained-layout linker omitted required functions")
    for symbol in retained:
        original = functions.get(symbol["name"])
        if original is None or symbol["size"] != original["size"] \
                or symbol["shndx"] != text["index"]:
            raise ValueError("Retained-layout linker changed a function's identity or size")
    mapped = [text]
    by_index = {section["index"]: section for section in allocated}
    tag = next((symbol for symbol in linked_symbols
                if symbol["name"] == "__sn__bss__tag__address__"), None)
    for section in linked_sections:
        if not section["flags"] & SHF_ALLOC or not section["size"] or section is text:
            continue
        original = native_sections.get(section["name"])
        native_size = original["size"] if original else 0
        expected_size = native_size
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
        if original is None or original["name"] == ".text" or symbol["type"] not in {1, 2}:
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
                    and (symbol["shndx"] in mapped_indices
                         or (symbol["shndx"] == SHN_UNDEF and symbol["name"] in referenced))]
    unit["native_object_sha256"] = before
    return mapped, used_symbols


# Build ------------------------------------------------------------------------------------

def build(original, manifest_path, report_path):
    report_path.unlink(missing_ok=True)
    target = json.loads((ROOT / "config/GN7E69/baseline.json").read_text())
    binary = original.read_bytes()
    if len(binary) != target["size"] or hashlib.sha1(binary).hexdigest() != target["sha1"]:
        raise RuntimeError("Original executable does not match the configured target")
    small_data = json.loads((ROOT / "config/GN7E69/analysis.json").read_text())["output_sections"]
    sections = target_sections(binary, target, small_data)
    compiler_lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    manifest_bytes = manifest_path.read_bytes()
    units, externals, include_dirs = load_manifest(json.loads(manifest_bytes), sections,
                                                   compiler_lock["compiler_version"])
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
    sdk_directory = setup_compiler.setup_sdk() if any(u["compiler"] == "mwcc" for u in units) else None
    for index, unit in enumerate(units):
        stem = re.sub(r"[^A-Za-z0-9]+", "_", unit["source"]).strip("_")
        unit["object"] = BUILD / "obj" / f"unit{index:03d}_{stem}.o"
        unit["depfile"] = unit["object"].with_suffix(".d")
        workdir, source = ROOT, str(unit["path"])
        if unit["compile_path"]:
            workdir, source = stage(unit), unit["compile_path"]
        includes = [ROOT / directory for directory in include_dirs + unit["include_dirs"]]
        if unit["compiler"] == "mwcc":
            sdk_cc.compile(sdk_directory, wrapper, source, unit["object"], unit["depfile"],
                           unit["flags"], includes, workdir)
        else:
            command = [sys.executable, str(ROOT / "tools/prodg_cc.py"), "--dir", str(compiler),
                       "--wrapper", str(wrapper), "--depfile", str(unit["depfile"])]
            for directory in includes:
                command += ["-I", str(directory)]
            command += unit["flags"] + ["-c", source, "-o", str(unit["object"])]
            result = subprocess.run(command, cwd=workdir, stdin=subprocess.DEVNULL)
            if result.returncode or not unit["object"].is_file():
                raise RuntimeError(f"Compilation failed for {unit['source']}")
        unit["native_object_sha256"] = sha256(unit["object"])
        objects[unit["source"]] = (retained_layout(unit, compiler, wrapper) if unit["link_roots"]
                                   else read_elf(unit["object"].read_bytes()))
        unit["dependencies"] = dependencies(unit["depfile"], workdir)
    pieces, defined, resolved = plan(sections, units, objects, externals)
    for section in sections:
        for piece in pieces[section["name"]]:
            if "unit" in piece:
                unit = next(u for u in units if u["source"] == piece["unit"])
                piece["object"], piece["input"] = unit["object"], piece["entry"]["section"]
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
    script.write_text(link_script(target, sections, pieces))
    elf, output = BUILD / "main.elf", BUILD / "main.dol"
    linker_flags = []
    if strip_unused:
        roots = set(original_roots)
        for unit in units:
            roots.update(unit["link_roots"]["symbols"] if unit["link_roots"] else
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
    if any(sha256(unit["object"]) != unit["native_object_sha256"] for unit in units):
        raise RuntimeError("Final linker input no longer equals the native compiler object")
    final = {s["name"]: s["value"] for s in read_elf(elf.read_bytes())[1] if s["bind"] != STB_LOCAL}
    for name, (value, source) in defined.items():
        if final.get(name) != value:
            raise RuntimeError(f"{source}: {name} was not linked at its configured address 0x{value:08X}")
    run("elf2dol", [str(dtk), "elf2dol", str(elf), str(output)], BUILD / "convert.log")
    if not output.is_file() or not output.stat().st_size:
        raise RuntimeError("Converter did not produce a fresh DOL")
    result = output.read_bytes()
    identical = result == binary and hashlib.sha1(result).hexdigest() == target["sha1"]
    report = measure(target, sections, units, manifest_bytes, result, identical, resolved, objects)
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, indent=2) + "\n")
    if not identical:
        raise RuntimeError(f"Source build differs from the complete target; see {report_path}")
    return report


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
    functions = []
    for symbol in obj[1]:
        if symbol["type"] != STT_FUNC or symbol["shndx"] == SHN_UNDEF or symbol["size"] <= 0:
            continue
        entry = placements.get(symbol["shndx"])
        if entry is None or entry["kind"] != "code":
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
    compilers = {}
    for unit in units:
        family = unit["compiler"]
        version = lock["sdk_compiler_version"] if family == "mwcc" else lock["compiler_version"]
        compilers[family] = version
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
        measured.append({"source": unit["source"], "compile_path": unit["compile_path"],
                         "source_sha256": sha256(unit["path"]),
                         "profile": unit["profile"], "flags": unit["flags"],
                         "compiler": {"family": family, "version": version},
                         "dependencies": unit["dependencies"],
                         "link_roots": unit.get("link_roots"),
                         "native_object_sha256": unit.get("native_object_sha256"),
                         "status": "matched" if identical else "unverified", "sections": entries,
                         "functions": compiled_functions(unit, objects[unit["source"]])})
    return {"schema": 1, "target": "GN7E69", "target_sha1": target["sha1"],
            "manifest_sha256": hashlib.sha256(manifest_bytes).hexdigest(),
            "compilers": dict(sorted(compilers.items())),
            "linker": "ngcld (ProDG) via wibo", "complete": "identical" if identical else "mismatch",
            "output_sha1": hashlib.sha1(result).hexdigest(),
            "tools": {path: sha256(ROOT / path) if (ROOT / path).is_file() else None
                      for path in TRUSTED_TOOLS},
            "externals": {name: f"0x{value:08X}" for name, value in sorted(resolved.items())},
            "units": measured, "totals": totals}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, default=ROOT / "config/GN7E69/units.json")
    parser.add_argument("--report", type=Path, default=BUILD / "report.json")
    args = parser.parse_args()
    report = build(args.original.resolve(), args.manifest.resolve(), args.report.resolve())
    code, data = report["totals"]["code"], report["totals"]["data"]
    print(f"Source build verified: {len(report['units'])} unit(s), output SHA-1 {report['output_sha1']}")
    print(f"Source code bytes linked/matched: {code['linked']}/{code['matched']}; "
          f"data: {data['linked']}/{data['matched']}")


if __name__ == "__main__":
    try:
        main()
    except (ValueError, RuntimeError) as error:
        sys.exit(f"source_build: {error}")
