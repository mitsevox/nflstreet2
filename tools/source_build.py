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


ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build" / "source"
NEUTRAL = re.compile(r"(?:fn|lbl)_([0-9A-F]{8})")
SAFE_PATH = re.compile(r"[A-Za-z0-9_./+-]+")
LINKER_SYMBOLS = {"__start", "_SDA_BASE_", "_SDA2_BASE_"}
LINK_TIMEOUT = 600
# Build inputs the report is bound to; tools/progress.py rejects reports from other versions.
TRUSTED_TOOLS = ("tools/source_build.py", "tools/prodg_cc.py", "tools/setup_compiler.py",
                 "tools/baseline.py", "tools/compiler-tools.json", "tools/baseline-tools.json",
                 "config/GN7E69/baseline.json", "config/GN7E69/analysis.json")

SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB, SHT_NOBITS = 1, 2, 3, 8
SHF_WRITE, SHF_ALLOC, SHF_EXECINSTR = 1, 2, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STB_LOCAL, STB_GLOBAL = 0, 1
STT_SECTION, STT_FILE = 3, 4


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
        if set(profile) - {"source_root"} != {"flags", "evidence"} or not profile["evidence"].strip():
            raise ValueError(f"Profile {name} needs flags, an evidence locator and optionally source_root")
        if "source_root" in profile:
            source_root(profile["source_root"])
        flags = profile["flags"]
        if not all(isinstance(flag, str) for flag in flags) or prodg_cc.OPTIONS & set(flags) \
                or any(flag.startswith("-I") for flag in flags):
            raise ValueError(f"Profile {name} contains wrapper options or include paths")
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
        if set(unit) != {"source", "profile", "evidence", "sections"} or not unit["evidence"].strip():
            raise ValueError("Each unit needs exactly source, profile, evidence and sections; "
                             "flags belong to a profile")
        source = repository_path(unit["source"])
        if unit["source"] in sources:
            raise ValueError(f"Duplicate unit source {unit['source']}")
        sources.add(unit["source"])
        if unit["profile"] not in profiles:
            raise ValueError(f"Unit {unit['source']} uses unknown profile {unit['profile']}")
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
                      "source_root": root, "compile_path": compile_path})
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
    for index, unit in enumerate(units):
        stem = re.sub(r"[^A-Za-z0-9]+", "_", unit["source"]).strip("_")
        unit["object"] = BUILD / "obj" / f"unit{index:03d}_{stem}.o"
        unit["depfile"] = unit["object"].with_suffix(".d")
        command = [sys.executable, str(ROOT / "tools/prodg_cc.py"), "--dir", str(compiler),
                   "--wrapper", str(wrapper), "--depfile", str(unit["depfile"])]
        for directory in include_dirs:
            command += ["-I", str(ROOT / directory)]
        workdir, source = ROOT, str(unit["path"])
        if unit["compile_path"]:
            workdir, source = stage(unit), unit["compile_path"]
        command += unit["flags"] + ["-c", source, "-o", str(unit["object"])]
        result = subprocess.run(command, cwd=workdir, stdin=subprocess.DEVNULL)
        if result.returncode or not unit["object"].is_file():
            raise RuntimeError(f"Compilation failed for {unit['source']}")
        objects[unit["source"]] = read_elf(unit["object"].read_bytes())
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
            write_object(piece["object"], [entry],
                         [{"name": s["name"], "value": s["value"], "shndx": 1} for s in piece["symbols"]])
    inputs = [piece["object"] for section in sections for piece in pieces[section["name"]]]
    inputs = list(dict.fromkeys(inputs))
    check_basenames(inputs)
    script = BUILD / "link.ld"
    script.write_text(link_script(target, sections, pieces))
    elf, output = BUILD / "main.elf", BUILD / "main.dol"
    run("ngcld", [str(wrapper), str(compiler / "ngcld.exe"), "-T", str(script), "-o", str(elf)]
        + [str(path) for path in inputs], BUILD / "link.log")
    if not elf.is_file() or not elf.stat().st_size:
        raise RuntimeError("Linker did not produce a fresh ELF")
    final = {s["name"]: s["value"] for s in read_elf(elf.read_bytes())[1] if s["bind"] != STB_LOCAL}
    for name, (value, source) in defined.items():
        if final.get(name) != value:
            raise RuntimeError(f"{source}: {name} was not linked at its configured address 0x{value:08X}")
    run("elf2dol", [str(dtk), "elf2dol", str(elf), str(output)], BUILD / "convert.log")
    if not output.is_file() or not output.stat().st_size:
        raise RuntimeError("Converter did not produce a fresh DOL")
    result = output.read_bytes()
    identical = result == binary and hashlib.sha1(result).hexdigest() == target["sha1"]
    report = measure(target, sections, units, manifest_bytes, result, identical, resolved)
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


def measure(target, sections, units, manifest_bytes, result, identical, resolved):
    totals = {kind: {"linked": 0, "matched": 0} for kind in ("code", "data")}
    measured = []
    for unit in units:
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
                         "dependencies": unit["dependencies"],
                         "status": "matched" if identical else "unverified", "sections": entries})
    return {"schema": 1, "target": "GN7E69", "target_sha1": target["sha1"],
            "manifest_sha256": hashlib.sha256(manifest_bytes).hexdigest(),
            "compiler": "ProDG " + json.loads((ROOT / "tools/compiler-tools.json").read_text())["compiler_version"],
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
