"""Check source-unit placement, symbol resolution and fail-closed verification on synthetic data."""

import copy
import hashlib
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import source_build as sb


def synthetic_dol():
    """A tiny DOL: one code section, one data section and an uninitialized extent."""
    binary = bytearray(0x100)
    struct.pack_into(">I", binary, 0x00, 0x100)
    struct.pack_into(">I", binary, 0x48, 0x80003100)
    struct.pack_into(">I", binary, 0x90, 0x40)
    struct.pack_into(">I", binary, 0x1C, 0x140)
    struct.pack_into(">I", binary, 0x64, 0x80004000)
    struct.pack_into(">I", binary, 0xAC, 0x20)
    struct.pack_into(">II", binary, 0xD8, 0x80005000, 0x40)
    struct.pack_into(">I", binary, 0xE0, 0x80003100)
    binary += bytes(range(0x40)) + bytes(range(0x80, 0xA0))
    return bytes(binary)


TARGET = {"entry": "0x80003100", "sda_base": "0x80008000", "sda2_base": "0x80010000",
          "sections": {".init": "0x80003100", ".data2": "0x80004000", ".bss": "0x80005000"}}


def compiled(sections, symbols):
    """Read back a synthetic relocatable object built with the tool's own writer."""
    with tempfile.TemporaryDirectory() as temporary:
        path = Path(temporary) / "unit.o"
        sb.write_object(path, sections, symbols)
        return sb.read_elf(path.read_bytes())


def text(size, align=4):
    return {"name": ".text", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC | sb.SHF_EXECINSTR,
            "size": size, "align": align, "data": bytes(size)}


def rodata(size, align=4):
    return {"name": ".rodata", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC, "size": size,
            "align": align, "data": bytes(size)}


class Fixture(unittest.TestCase):
    def setUp(self):
        self.binary = synthetic_dol()
        self.sections = sb.target_sections(self.binary, TARGET, {})
        self.manifest = {
            "schema": 1, "target": "GN7E69-rev0", "compiler": "3.9.3", "include_dirs": [],
            "profiles": {"library": {"flags": ["-O2"], "evidence": "library-level locator"}},
            "externals": {},
            "units": [{"source": "src/unit.c", "profile": "library", "evidence": "unit locator",
                       "sections": [{"section": ".text", "placement": ".init",
                                     "start": "0x80003110", "end": "0x80003118"},
                                    {"section": ".rodata", "placement": ".data2",
                                     "start": "0x80004008", "end": "0x8000400C"}]}]}

    def load(self, manifest=None):
        return sb.load_manifest(manifest or self.manifest, self.sections, "3.9.3")

    def plan(self, objects, manifest=None):
        units, externals, _ = self.load(manifest)
        return sb.plan(self.sections, units, objects, externals)


class TargetAndManifest(Fixture):
    def test_target_sections_follow_the_executable_header(self):
        names = [(s["name"], s["kind"], hex(s["start"]), hex(s["end"])) for s in self.sections]
        self.assertEqual(names, [(".init", "code", "0x80003100", "0x80003140"),
                                 (".data2", "data", "0x80004000", "0x80004020"),
                                 (".bss", "bss", "0x80005000", "0x80005040")])
        with self.assertRaisesRegex(ValueError, "missing"):
            sb.target_sections(self.binary, {"sections": {".init": "0x80003100", ".bss": "0x80005000"}}, {})

    def test_valid_manifest(self):
        units, externals, includes = self.load()
        self.assertEqual(units[0]["flags"], ["-O2"])
        self.assertEqual(externals, {})

    def test_flags_belong_to_an_evidenced_profile(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["flags"] = ["-O1"]
        with self.assertRaisesRegex(ValueError, "profile"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["profiles"]["library"]["evidence"] = " "
        with self.assertRaisesRegex(ValueError, "evidence"):
            self.load(manifest)
        for flags in (["-o", "x.o"], ["-Iinclude"], ["--wrapper", "x"]):
            manifest = copy.deepcopy(self.manifest)
            manifest["profiles"]["library"]["flags"] = flags
            with self.subTest(flags=flags), self.assertRaises(ValueError):
                self.load(manifest)

    def test_profile_language_sets_the_front_end(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["profiles"]["library"]["language"] = "c++"
        units, _, _ = self.load(manifest)
        self.assertEqual(units[0]["flags"], ["-x", "c++", "-O2"])
        for profile in ({"language": "c++ "}, {"language": "objc"}, {"language": "c", "compiler": "mwcc"}):
            manifest = copy.deepcopy(self.manifest)
            manifest["profiles"]["library"].update(profile)
            with self.subTest(profile=profile), self.assertRaisesRegex(ValueError, "language"):
                self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["profiles"]["library"]["flags"] = ["-x", "c++", "-O2"]
        with self.assertRaisesRegex(ValueError, "wrapper options"):
            self.load(manifest)

    def test_ranges_must_fit_and_not_overlap(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0]["end"] = "0x80003148"
        with self.assertRaisesRegex(ValueError, "outside"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        other = copy.deepcopy(manifest["units"][0])
        other["source"] = "src/other.c"
        other["sections"] = [{"section": ".text", "placement": ".init",
                              "start": "0x80003114", "end": "0x80003120"}]
        manifest["units"].append(other)
        with self.assertRaisesRegex(ValueError, "overlap"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0]["start"] = "0x8000311a"
        with self.assertRaisesRegex(ValueError, "0xXXXXXXXX"):
            self.load(manifest)

    def test_source_root_maps_units_to_relative_compile_paths(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["source"] = "src/Common/Lib/unit.c"
        manifest["profiles"]["library"]["source_root"] = {
            "directory": "src", "file_prefix": "../../../Source", "evidence": "target path strings"}
        units, _, _ = self.load(manifest)
        self.assertEqual(units[0]["compile_path"], "../../../Source/Common/Lib/unit.c")
        for prefix in ("Source", "../Source/Extra", "../../x/Source", "/abs/Source", "../../"):
            bad = copy.deepcopy(manifest)
            bad["profiles"]["library"]["source_root"]["file_prefix"] = prefix
            with self.subTest(prefix=prefix), self.assertRaisesRegex(ValueError, "file_prefix"):
                self.load(bad)
        bad = copy.deepcopy(manifest)
        bad["units"][0]["source"] = "other/unit.c"
        with self.assertRaisesRegex(ValueError, "outside its profile's source root"):
            self.load(bad)
        bad = copy.deepcopy(manifest)
        del bad["profiles"]["library"]["source_root"]["evidence"]
        with self.assertRaisesRegex(ValueError, "evidence"):
            self.load(bad)

    def test_staged_compile_directory_reaches_repository_source(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "src/Common").mkdir(parents=True)
            (root / "src/Common/unit.c").write_text("int unit;\n")
            (root / "include").mkdir()
            (root / "include/unit.h").write_text("extern int unit;\n")
            unit = {"profile": "library", "path": root / "src/Common/unit.c",
                    "source": "src/Common/unit.c", "compile_path": "../../../Source/Common/unit.c",
                    "source_root": {"directory": "src", "file_prefix": "../../../Source",
                                    "evidence": "x"}}
            with patch.object(sb, "ROOT", root), patch.object(sb, "BUILD", root / "build/source"):
                workdir = sb.stage(unit)
                self.assertEqual(workdir.relative_to(root / "build/source/stage/library"),
                                 Path("level1/level2/level3"))
                depfile = root / "unit.d"
                depfile.write_text(f"unit.o: ../../../Source/Common/unit.c \\\n {root}/include/unit.h\n")
                self.assertEqual(sorted(sb.dependencies(depfile, workdir)),
                                 ["include/unit.h", "src/Common/unit.c"])
                unit["compile_path"] = "../../../Source/Common/other.c"
                with self.assertRaisesRegex(RuntimeError, "does not reach"):
                    sb.stage(unit)

    def test_manifest_identity_and_paths(self):
        with self.assertRaisesRegex(ValueError, "pinned compiler"):
            sb.load_manifest(self.manifest, self.sections, "3.9.4")
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["source"] = "../outside.c"
        with self.assertRaisesRegex(ValueError, "relative repository path"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"fn_80003104": {"address": "0x80003104", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "non-neutral"):
            self.load(manifest)


class Placement(Fixture):
    def objects(self, text_size=8, rodata_size=4, symbols=None, extra=()):
        symbols = symbols if symbols is not None else [
            {"name": "Unit_Function", "value": 0, "shndx": 1, "type": 2},
            {"name": "fn_80003104", "value": 0, "shndx": 0},
            {"name": "lbl_80005010", "value": 0, "shndx": 0}]
        return {"src/unit.c": compiled([text(text_size), rodata(rodata_size), *extra], symbols)}

    def test_original_pieces_surround_units_and_define_externals(self):
        pieces, defined, resolved = self.plan(self.objects())
        layout = [(hex(p["start"]), hex(p["end"]), p.get("unit")) for p in pieces[".init"]]
        self.assertEqual(layout, [("0x80003100", "0x80003110", None),
                                  ("0x80003110", "0x80003118", "src/unit.c"),
                                  ("0x80003118", "0x80003140", None)])
        self.assertEqual(pieces[".init"][0]["symbols"], [{"name": "fn_80003104", "value": 4}])
        self.assertEqual(pieces[".bss"][0]["symbols"], [{"name": "lbl_80005010", "value": 0x10}])
        self.assertEqual(defined, {"Unit_Function": (0x80003110, "src/unit.c")})
        self.assertEqual(resolved, {"fn_80003104": 0x80003104, "lbl_80005010": 0x80005010})

    def test_compiled_sizes_must_equal_configured_ranges(self):
        with self.assertRaisesRegex(ValueError, "compiled .text is 0xc bytes"):
            self.plan(self.objects(text_size=12))
        with self.assertRaisesRegex(ValueError, "compiled .rodata"):
            self.plan(self.objects(rodata_size=8))

    def test_every_allocated_section_needs_a_range(self):
        data = {"name": ".data", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC | sb.SHF_WRITE,
                "size": 4, "align": 4, "data": bytes(4)}
        with self.assertRaisesRegex(ValueError, "no configured range"):
            self.plan(self.objects(extra=[data]))
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"].append(
            {"section": ".sdata", "placement": ".data2", "start": "0x80004010", "end": "0x80004014"})
        with self.assertRaisesRegex(ValueError, "was not produced"):
            self.plan(self.objects(), manifest)

    def test_section_kind_and_alignment(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0].update(placement=".data2", start="0x80004000", end="0x80004008")
        with self.assertRaisesRegex(ValueError, "cannot be placed"):
            self.plan(self.objects(), manifest)
        with self.assertRaisesRegex(ValueError, "alignment"):
            self.plan({"src/unit.c": compiled([text(8, align=32), rodata(4)], [])})

    def test_symbols_must_resolve_explicitly(self):
        with self.assertRaisesRegex(ValueError, "unresolved symbol Helper"):
            self.plan(self.objects(symbols=[{"name": "Helper", "value": 0, "shndx": 0}]))
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"Helper": {"address": "0x80004004", "evidence": "name evidence"}}
        pieces, _, resolved = self.plan(
            self.objects(symbols=[{"name": "Helper", "value": 0, "shndx": 0}]), manifest)
        self.assertEqual(resolved, {"Helper": 0x80004004})
        self.assertEqual(pieces[".data2"][0]["symbols"], [{"name": "Helper", "value": 4}])

    def test_references_cannot_bypass_a_source_unit(self):
        with self.assertRaisesRegex(ValueError, "inside source unit"):
            self.plan(self.objects(symbols=[{"name": "fn_80003114", "value": 0, "shndx": 0}]))
        with self.assertRaisesRegex(ValueError, "outside the executable"):
            self.plan(self.objects(symbols=[{"name": "lbl_80004800", "value": 0, "shndx": 0}]))
        # Only a configured external before or past the whole image may be linker-defined (absolute).
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"_stack_addr": {"address": "0x80006000", "evidence": "x"},
                                 "_low": {"address": "0x80000010", "evidence": "x"},
                                 "Gap": {"address": "0x80004800", "evidence": "x"}}
        _, _, resolved = self.plan(self.objects(symbols=[{"name": "_stack_addr", "value": 0, "shndx": 0}]),
                                   manifest)
        self.assertEqual(resolved["_stack_addr"], 0x80006000)
        _, _, resolved = self.plan(self.objects(symbols=[{"name": "_low", "value": 0, "shndx": 0}]), manifest)
        self.assertEqual(resolved["_low"], 0x80000010)
        self.assertIn("_stack_addr = 0x80006000;",
                      sb.link_script(TARGET, self.sections, {s["name"]: [] for s in self.sections},
                                     {"_stack_addr": 0x80006000}))
        for name in ("Gap", "lbl_80006000"):
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, "outside the executable"):
                self.plan(self.objects(symbols=[{"name": name, "value": 0, "shndx": 0}]), manifest)
        # A section's end address is still attributable to its final original piece.
        pieces, _, _ = self.plan(self.objects(symbols=[{"name": "lbl_80004020", "value": 0, "shndx": 0}]))
        self.assertEqual(pieces[".data2"][-1]["symbols"], [{"name": "lbl_80004020", "value": 0x14}])

    def test_definitions_cannot_collide_or_misstate_addresses(self):
        with self.assertRaisesRegex(ValueError, "neutral label fn_80003100"):
            self.plan(self.objects(symbols=[{"name": "fn_80003100", "value": 0, "shndx": 1}]))
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"Unit_Function": {"address": "0x80003104", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(), manifest)
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(symbols=[{"name": "_SDA_BASE_", "value": 0, "shndx": 1}]))
        with self.assertRaisesRegex(ValueError, "common symbol"):
            self.plan(self.objects(symbols=[{"name": "shared", "value": 4, "shndx": sb.SHN_COMMON}]))

    def test_link_script_and_object_names(self):
        pieces, _, _ = self.plan(self.objects())
        for name, items in pieces.items():
            for index, piece in enumerate(items):
                piece["object"] = Path(f"/build/{name.strip('.')}_{index}.o")
                piece["input"] = name
        script = sb.link_script(TARGET, self.sections, pieces)
        self.assertIn(".init 0x80003100 : { *init_0.o(.init) *init_1.o(.init) *init_2.o(.init) }", script)
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            sb.check_basenames([Path("a/unit.o"), Path("b/myunit.o")])
        with self.assertRaisesRegex(ValueError, "not safe"):
            sb.check_basenames([Path("a/unit (1).o")])


def with_relocations(path, target, entries):
    """Append one SHT_RELA section for section `target` to an object from sb.write_object;
    entries are (offset, symbol index, type, addend)."""
    data = bytearray(Path(path).read_bytes())
    shoff = struct.unpack_from(">I", data, 32)[0]
    count = struct.unpack_from(">H", data, 48)[0]
    headers = [bytes(data[shoff + index * 40:shoff + index * 40 + 40]) for index in range(count)]
    data = data[:shoff]
    symtab = next(index for index, header in enumerate(headers) if struct.unpack_from(">I", header, 4)[0] == 2)
    offset = len(data)
    data += b"".join(struct.pack(">IIi", at, index << 8 | kind, addend) for at, index, kind, addend in entries)
    headers.append(struct.pack(">IIIIIIIIII", 0, 4, 0, 0, offset, len(entries) * 12, symtab, target, 4, 12))
    struct.pack_into(">I", data, 32, len(data))
    struct.pack_into(">H", data, 48, len(headers))
    Path(path).write_bytes(bytes(data) + b"".join(headers))


def relocations(data):
    sections, symbols = sb.read_elf(data)
    return [(at, symbols[(info >> 8) - 1]["name"], info & 255, addend)
            for section in sections if section["type"] == 4
            for at, info, addend in struct.iter_unpack(">IIi", data[section["offset"]:
                                                                     section["offset"] + section["size"]])]


class FoldedDuplicates(Fixture):
    """Local duplicates the original linker folded into another file's identical copies."""

    # Object symbol indices: 0 null, 1 file, 2 and 3 the .text and .rodata section symbols.
    SYMBOLS = [{"name": "Unit_Function", "value": 0, "size": 4, "shndx": 1, "type": sb.STT_FUNC},
               {"name": "Destroy", "value": 4, "size": 4, "shndx": 1, "type": sb.STT_FUNC, "bind": sb.STB_LOCAL},
               {"name": "Table", "value": 0, "size": 4, "shndx": 2, "type": sb.STT_OBJECT, "bind": sb.STB_LOCAL}]

    def native(self, symbols=None, text_relocations=((0, 6, 6, 0),), rodata_relocations=((0, 5, 1, 0),)):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        path = Path(temporary.name) / "unit.o"
        sb.write_object(path, [dict(text(8), data=bytes(range(8))), rodata(4)],
                        self.SYMBOLS if symbols is None else symbols)
        with_relocations(path, 1, text_relocations)
        with_relocations(path, 2, rodata_relocations)
        return path.read_bytes(), Path(temporary.name) / "folded.o"

    def folded_manifest(self, symbols=None, evidence="linker evidence"):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["folded"] = {"symbols": {"Destroy": "0x80003124", "Table": "0x80004010"}
                                          if symbols is None else symbols,
                                          "evidence": evidence}
        return manifest

    def test_manifest_folds_need_evidence_and_foreign_addresses(self):
        units, _, _ = self.load(self.folded_manifest())
        self.assertEqual(units[0]["folded"], {"Destroy": 0x80003124, "Table": 0x80004010})
        self.assertIsNone(self.load()[0][0]["folded"])
        with self.assertRaisesRegex(ValueError, "symbols map and evidence"):
            self.load(self.folded_manifest(evidence=" "))
        with self.assertRaisesRegex(ValueError, "symbols map and evidence"):
            self.load(self.folded_manifest(symbols={}))
        with self.assertRaisesRegex(ValueError, "descriptive local name"):
            self.load(self.folded_manifest(symbols={"fn_80003124": "0x80003124"}))
        with self.assertRaisesRegex(ValueError, "the unit's own range"):
            self.load(self.folded_manifest(symbols={"Destroy": "0x80003114"}))
        with self.assertRaisesRegex(ValueError, "uppercase hexadecimal"):
            self.load(self.folded_manifest(symbols={"Destroy": "0x80003124a"}))

    def test_folding_unit_may_discard_nothing_else(self):
        # Roots that only make the linker drop folded bodies may list no other discarded function.
        roots = {"symbols": ["Unit_Function"], "discarded": [], "evidence": "linker evidence"}
        manifest = self.folded_manifest()
        manifest["units"][0]["link_roots"] = roots
        units, _, _ = self.load(manifest)
        self.assertEqual(units[0]["link_roots"]["discarded"], [])
        # Without folds an empty list is still refused.
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["link_roots"] = roots
        with self.assertRaisesRegex(ValueError, "a list of the discarded functions"):
            self.load(manifest)

    def test_only_relocations_to_folded_symbols_change(self):
        native, output = self.native()
        folds = sb.fold_object(native, {"Destroy": 0x80003124, "Table": 0x80004010}, output)
        self.assertEqual({name: (symbol["value"], section["name"]) for name, (symbol, section) in folds.items()},
                         {"Destroy": (4, ".text"), "Table": (0, ".rodata")})
        derived = output.read_bytes()
        self.assertEqual(relocations(derived), [(0, "__folded_Table", 6, 0), (0, "__folded_Destroy", 1, 0)])
        sections, symbols = sb.read_elf(derived)
        before_sections, before_symbols = sb.read_elf(native)
        self.assertEqual([s.get("data") for s in sections], [s.get("data") for s in before_sections])
        self.assertEqual(symbols[:len(before_symbols)], before_symbols)
        self.assertEqual([(s["name"], s["bind"], s["shndx"]) for s in symbols[len(before_symbols):]],
                         [("__folded_Destroy", sb.STB_GLOBAL, sb.SHN_UNDEF),
                          ("__folded_Table", sb.STB_GLOBAL, sb.SHN_UNDEF)])

    def test_folded_names_must_be_unique_local_definitions(self):
        native, output = self.native()
        for name in ("Missing", "Unit_Function"):
            with self.assertRaisesRegex(ValueError, "not one local function or object"):
                sb.fold_object(native, {name: 0x80003124}, output)
        twice = self.SYMBOLS + [dict(self.SYMBOLS[1], value=0)]
        with self.assertRaisesRegex(ValueError, "not one local function or object"):
            sb.fold_object(self.native(twice)[0], {"Destroy": 0x80003124}, output)
        # A function must be code and an object must be data.
        swapped = [self.SYMBOLS[0], dict(self.SYMBOLS[1], type=sb.STT_OBJECT), self.SYMBOLS[2]]
        with self.assertRaisesRegex(ValueError, "not one local function or object"):
            sb.fold_object(self.native(swapped)[0], {"Destroy": 0x80003124}, output)
        clash = self.SYMBOLS + [{"name": "__folded_Destroy", "value": 0, "shndx": 0}]
        with self.assertRaisesRegex(ValueError, "already a symbol"):
            sb.fold_object(self.native(clash)[0], {"Destroy": 0x80003124}, output)
        self.assertFalse(output.exists())

    def test_references_by_section_or_alias_are_ambiguous(self):
        native, output = self.native(rodata_relocations=((0, 2, 1, 4),))
        with self.assertRaisesRegex(ValueError, "through another symbol"):
            sb.fold_object(native, {"Destroy": 0x80003124}, output)
        # So does a named symbol whose addend reaches into the folded extent.
        with self.assertRaisesRegex(ValueError, "through another symbol"):
            sb.fold_object(self.native(rodata_relocations=((0, 4, 1, 6),))[0], {"Destroy": 0x80003124}, output)
        sb.fold_object(self.native(rodata_relocations=((0, 4, 1, 0),))[0], {"Destroy": 0x80003124}, output)
        # The same section relocation outside the folded extent is unaffected.
        sb.fold_object(self.native(rodata_relocations=((0, 2, 1, 0),))[0], {"Destroy": 0x80003124}, output)
        # A branch inside the folded function to its own body goes with the body; the same
        # section reference from another function still fails.
        sb.fold_object(self.native(text_relocations=((4, 2, 11, 6),))[0], {"Destroy": 0x80003124}, output)
        with self.assertRaisesRegex(ValueError, "through another symbol"):
            sb.fold_object(self.native(text_relocations=((0, 2, 11, 6),))[0], {"Destroy": 0x80003124}, output)
        alias = self.SYMBOLS + [{"name": "Alias", "value": 6, "size": 0, "shndx": 1, "bind": sb.STB_LOCAL}]
        with self.assertRaisesRegex(ValueError, "aliases a folded symbol"):
            sb.fold_object(self.native(alias)[0], {"Destroy": 0x80003124}, output)

    def test_folded_functions_must_leave_the_retained_layout(self):
        unit = {"source": "src/unit.c", "folded": {"Destroy": 0x80003124},
                "link_roots": {"symbols": ["Unit_Function"], "discarded": ["Unused"]}}
        native = {"Unit_Function", "Destroy", "Unused"}
        sb.check_retention(unit, native, {"Unit_Function"})
        with self.assertRaisesRegex(ValueError, "retained a folded function"):
            sb.check_retention(unit, native, {"Unit_Function", "Destroy"})
        # A folded function is not a discarded one, and every other dropped function is listed.
        for discarded in (["Unused", "Destroy"], ["Destroy"]):
            with self.assertRaisesRegex(ValueError, "discarded functions differ"):
                sb.check_retention(dict(unit, link_roots={"symbols": [], "discarded": discarded}),
                                   native, {"Unit_Function"})
        with self.assertRaisesRegex(ValueError, "discarded functions differ"):
            sb.check_retention(unit, native, {"Unit_Function", "Unused"})

    def test_folded_function_needs_link_roots(self):
        native, output = self.native()
        path = output.with_name("native.o")
        path.write_bytes(native)
        unit = {"source": "src/unit.c", "object": path, "link_roots": None,
                "folded": {"Destroy": 0x80003124, "Table": 0x80004010}}
        with self.assertRaisesRegex(ValueError, "folded function needs link_roots"):
            sb.link_object(unit)
        # Folding only an object needs no retention link; the native object stays untouched.
        unit["folded"] = {"Table": 0x80004010}
        sb.link_object(unit)
        self.assertEqual(unit["link_object"], path.with_suffix(".folded.o"))
        self.assertEqual(unit["link_object_sha256"], sb.sha256(unit["link_object"]))
        self.assertEqual(path.read_bytes(), native)
        unit["folded"] = None
        sb.link_object(unit)
        self.assertEqual((unit["link_object"], unit["folds"]), (path, {}))

    def test_folded_references_resolve_to_their_configured_address(self):
        symbols = [{"name": "Unit_Function", "value": 0, "shndx": 1, "type": 2},
                   {"name": "__folded_Table", "value": 0, "shndx": 0}]
        objects = {"src/unit.c": compiled([text(8), rodata(4)], symbols)}
        pieces, _, resolved = self.plan(objects, self.folded_manifest())
        self.assertEqual(resolved, {"__folded_Table": 0x80004010})
        self.assertEqual(pieces[".data2"][-1]["symbols"], [{"name": "__folded_Table", "value": 4}])
        # Without the fold the name is unknown; a definition elsewhere makes it ambiguous.
        with self.assertRaisesRegex(ValueError, "unresolved symbol __folded_Table"):
            self.plan(objects)
        manifest = self.folded_manifest()
        manifest["externals"] = {"__folded_Table": {"address": "0x80004010", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "folded reference __folded_Table is ambiguous"):
            self.plan(objects, manifest)

    def test_folded_object_copy_must_equal_the_target_bytes(self):
        units, _, _ = self.load(self.folded_manifest(symbols={"Table": "0x80003120"}))
        unit = units[0]
        unit["folds"] = {"Table": ({"type": sb.STT_OBJECT, "value": 0, "size": 4}, {"name": ".rodata"})}
        # The copy at 0x80004008 holds 0x88-0x8B; the target holds 0x20-0x23 at 0x80003120.
        with self.assertRaisesRegex(ValueError, "folded object Table at 0x80004008 differs"):
            sb.check_folded_objects(unit, self.binary, self.binary)
        binary = bytearray(self.binary)
        binary[0x120:0x124] = bytes(range(0x88, 0x8C))
        sb.check_folded_objects(unit, bytes(binary), bytes(binary))


class CommonStorage(Fixture):
    """COMMON symbols that an evidenced storage map places at their target addresses."""

    COMMON = [{"name": "Unit_Function", "value": 0, "shndx": 1, "type": sb.STT_FUNC, "size": 8},
              {"name": "g_Shared", "value": 4, "size": 8, "shndx": sb.SHN_COMMON},
              {"name": "g_Flag", "value": 4, "size": 4, "shndx": sb.SHN_COMMON}]

    def storage_manifest(self, rows=None):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["storage"] = rows if rows is not None else [
            {"symbol": "g_Shared", "start": "0x80005010", "end": "0x80005018"},
            {"symbol": "g_Flag", "start": "0x80005020", "end": "0x80005024"}]
        return manifest

    def objects(self, symbols=None):
        return {"src/unit.c": compiled([text(8), rodata(4)], symbols if symbols is not None else self.COMMON)}

    def storage(self, manifest=None):
        return self.load(manifest or self.storage_manifest())[0][0]["storage"]

    def common_object(self, storage, symbols=None):
        """Derive the link object of a synthetic native object; return (native, derived) symbols."""
        with tempfile.TemporaryDirectory() as temporary:
            native = Path(temporary) / "unit.o"
            sb.write_object(native, [text(8), rodata(4)], symbols if symbols is not None else self.COMMON)
            derived = Path(temporary) / "unit.common.o"
            sb.common_object(native.read_bytes(), storage, derived, "src/unit.c")
            return sb.read_elf(native.read_bytes())[1], sb.read_elf(derived.read_bytes())[1], \
                native.read_bytes(), derived.read_bytes()

    def test_without_a_map_a_common_symbol_fails(self):
        units, _, _ = self.load()
        self.assertIsNone(units[0]["storage"])
        with self.assertRaisesRegex(ValueError, "common symbol g_Shared has no placement"):
            self.plan(self.objects())
        # A map that leaves one COMMON symbol out still fails for that symbol.
        storage = self.storage(self.storage_manifest([{"symbol": "g_Shared", "start": "0x80005010",
                                                       "end": "0x80005018"}]))
        with self.assertRaisesRegex(ValueError, "common symbol g_Flag has no placement"):
            self.common_object(storage)

    def test_mapped_common_symbols_become_undefined_references_only(self):
        native, derived, native_bytes, derived_bytes = self.common_object(self.storage())
        self.assertEqual([(s["name"], s["shndx"], s["value"], s["size"]) for s in derived if s["name"].startswith("g_")],
                         [("g_Shared", sb.SHN_UNDEF, 0, 0), ("g_Flag", sb.SHN_UNDEF, 0, 0)])
        self.assertEqual([s for s in native if not s["name"].startswith("g_")],
                         [s for s in derived if not s["name"].startswith("g_")])
        # Only the two symbol table entries differ; section headers and contents are the same bytes.
        self.assertEqual(sb.read_elf(native_bytes)[0], sb.read_elf(derived_bytes)[0])
        table = next(s for s in sb.read_elf(native_bytes)[0] if s["type"] == sb.SHT_SYMTAB)
        changed = {(at - table["offset"]) // 16 for at, (a, b) in enumerate(zip(native_bytes, derived_bytes)) if a != b}
        self.assertEqual(len(native_bytes), len(derived_bytes))
        self.assertEqual(changed, {index for index, s in enumerate(native, 1) if s["name"].startswith("g_")})

    def test_map_must_agree_with_the_compiled_common_symbols(self):
        cases = [
            ("differs from its compiled COMMON size", [{"symbol": "g_Shared", "start": "0x80005010", "end": "0x80005014"},
                                                      {"symbol": "g_Flag", "start": "0x80005020", "end": "0x80005024"}]),
            ("differs from its compiled COMMON size", [{"symbol": "g_Shared", "start": "0x80005012", "end": "0x8000501A"},
                                                      {"symbol": "g_Flag", "start": "0x80005020", "end": "0x80005024"}]),
            ("not a compiled COMMON symbol", [{"symbol": "g_Shared", "start": "0x80005010", "end": "0x80005018"},
                                             {"symbol": "g_Flag", "start": "0x80005020", "end": "0x80005024"},
                                             {"symbol": "g_Other", "start": "0x80005030", "end": "0x80005034"}]),
        ]
        for message, rows in cases:
            with self.subTest(message=message), self.assertRaisesRegex(ValueError, message):
                self.common_object(self.storage(self.storage_manifest(rows)))

    def test_mapped_symbols_are_defined_by_the_original_piece_that_holds_them(self):
        undefined = [self.COMMON[0], {"name": "g_Shared", "value": 0, "shndx": 0}, {"name": "g_Flag", "value": 0, "shndx": 0}]
        pieces, defined, resolved = self.plan(self.objects(undefined), self.storage_manifest())
        self.assertEqual(defined["g_Shared"], (0x80005010, "src/unit.c"))
        self.assertEqual(defined["g_Flag"], (0x80005020, "src/unit.c"))
        self.assertEqual(pieces[".bss"], [{"start": 0x80005000, "end": 0x80005040, "symbols": [
            {"name": "g_Shared", "value": 0x10}, {"name": "g_Flag", "value": 0x20}]}])
        self.assertEqual(resolved, {})
        # Without the map the same references are unresolved.
        with self.assertRaisesRegex(ValueError, "unresolved symbol g_Shared"):
            self.plan(self.objects(undefined))
        # Another unit's reference resolves to the definition, not to an external.
        manifest = self.storage_manifest()
        manifest["units"].append({"source": "src/other.c", "profile": "library", "evidence": "x", "sections": [
            {"section": ".text", "placement": ".init", "start": "0x80003120", "end": "0x80003128"}]})
        objects = self.objects(undefined)
        objects["src/other.c"] = compiled([text(8)], [{"name": "g_Flag", "value": 0, "shndx": 0}])
        _, _, resolved = self.plan(objects, manifest)
        self.assertNotIn("g_Flag", resolved)
        # A mapped name cannot also be an external or another definition.
        manifest = self.storage_manifest()
        manifest["externals"] = {"g_Flag": {"address": "0x80005020", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(undefined), manifest)
        clash = undefined[:2] + [{"name": "g_Flag", "value": 0, "shndx": 2}]
        with self.assertRaisesRegex(ValueError, "already defined"):
            self.plan(self.objects(clash), self.storage_manifest())

    def test_map_rows_are_checked_when_the_manifest_loads(self):
        cases = [
            ("rows need symbol, start and end",[{"symbol": "g_Shared", "start": "0x80005010"}]),
            ("compiled COMMON name", [{"symbol": "lbl_80005010", "start": "0x80005010", "end": "0x80005018"}]),
            ("duplicate storage symbol", [{"symbol": "g_Shared", "start": "0x80005010", "end": "0x80005018"},
                                          {"symbol": "g_Shared", "start": "0x80005020", "end": "0x80005028"}]),
            ("not inside one data section", [{"symbol": "g_Shared", "start": "0x80003120", "end": "0x80003128"}]),
            ("overlap", [{"symbol": "g_Shared", "start": "0x80004008", "end": "0x80004010"}]),
            ("overlap", [{"symbol": "g_Shared", "start": "0x80005010", "end": "0x80005018"},
                         {"symbol": "g_Flag", "start": "0x80005014", "end": "0x80005018"}]),
            ("must list", []),
        ]
        for message, rows in cases:
            with self.subTest(rows=rows), self.assertRaisesRegex(ValueError, message):
                self.load(self.storage_manifest(rows))

    def test_storage_needs_exact_evidence_and_zero_target_bytes(self):
        units, _, _ = self.load(self.storage_manifest())
        evidence = {(0x80005010, 0x80005018), (0x80005020, 0x80005024)}
        sb.check_storage(units, evidence, self.sections)
        with self.assertRaisesRegex(ValueError, "storage g_Flag 0x80005020-0x80005024 does not equal an evidence"):
            sb.check_storage(units, {(0x80005010, 0x80005018)}, self.sections)
        # Storage in a loaded data section must hold zeros there in the target.
        units, _, _ = self.load(self.storage_manifest([{"symbol": "g_Flag", "start": "0x80004010", "end": "0x80004014"}]))
        with self.assertRaisesRegex(ValueError, "is not zero in the target"):
            sb.check_storage(units, {(0x80004010, 0x80004014)}, self.sections)
        binary = bytearray(self.binary)
        binary[0x150:0x154] = bytes(4)  # .data2 0x80004010-0x80004014
        sb.check_storage(units, {(0x80004010, 0x80004014)}, sb.target_sections(bytes(binary), TARGET, {}))


class KeptLocals(Fixture):
    """A local copy the original linker kept for other files' same-named references."""

    SYMBOLS = [{"name": "Unit_Function", "value": 0, "size": 4, "shndx": 1, "type": sb.STT_FUNC},
               {"name": "Inline", "value": 4, "size": 4, "shndx": 1, "type": sb.STT_FUNC, "bind": sb.STB_LOCAL},
               {"name": "Table", "value": 0, "size": 4, "shndx": 2, "type": sb.STT_OBJECT, "bind": sb.STB_LOCAL}]

    def setUp(self):
        super().setUp()
        self.manifest["units"].append(
            {"source": "src/other.c", "profile": "library", "evidence": "other locator",
             "sections": [{"section": ".text", "placement": ".init", "start": "0x80003120", "end": "0x80003124"}]})

    def kept_manifest(self, symbols=None, evidence="linker evidence"):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["kept_locals"] = {"symbols": {"Inline": "0x80003114"} if symbols is None else symbols,
                                               "evidence": evidence}
        return manifest

    def native(self, symbols=None):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        path = Path(temporary.name) / "unit.o"
        sb.write_object(path, [dict(text(8), data=bytes(range(8))), rodata(4)],
                        self.SYMBOLS if symbols is None else symbols)
        with_relocations(path, 2, ((0, 4, 1, 0),))
        return path.read_bytes(), Path(temporary.name) / "kept.o"

    def test_manifest_kept_locals_need_evidence_and_own_code(self):
        units, _, _ = self.load(self.kept_manifest())
        self.assertEqual(units[0]["kept_locals"], {"Inline": 0x80003114})
        self.assertIsNone(self.load()[0][0]["kept_locals"])
        with self.assertRaisesRegex(ValueError, "symbols map and evidence"):
            self.load(self.kept_manifest(evidence=" "))
        with self.assertRaisesRegex(ValueError, "symbols map and evidence"):
            self.load(self.kept_manifest(symbols={}))
        with self.assertRaisesRegex(ValueError, "descriptive name"):
            self.load(self.kept_manifest(symbols={"fn_80003114": "0x80003114"}))
        # Another file's code is not a kept copy; the unit's own data may hold a kept table.
        with self.assertRaisesRegex(ValueError, "outside the unit's sections"):
            self.load(self.kept_manifest(symbols={"Inline": "0x80003120"}))
        units, _, _ = self.load(self.kept_manifest(symbols={"Table": "0x80004008"}))
        self.assertEqual(units[0]["kept_locals"], {"Table": 0x80004008})
        manifest = self.kept_manifest()
        manifest["units"][0]["folded"] = {"symbols": {"Inline": "0x80003124"}, "evidence": "x"}
        with self.assertRaisesRegex(ValueError, "both folded and kept"):
            self.load(manifest)

    def test_only_a_global_copy_of_the_kept_symbol_is_added(self):
        native, output = self.native()
        kept = sb.keep_object(native, {"Inline": 0x80003114}, output)
        self.assertEqual({name: (symbol["value"], section["name"]) for name, (symbol, section) in kept.items()},
                         {"Inline": (4, ".text")})
        derived = output.read_bytes()
        self.assertEqual(relocations(derived), relocations(native))
        sections, symbols = sb.read_elf(derived)
        before_sections, before_symbols = sb.read_elf(native)
        self.assertEqual([s.get("data") for s in sections], [s.get("data") for s in before_sections])
        self.assertEqual(symbols[:len(before_symbols)], before_symbols)
        self.assertEqual(symbols[len(before_symbols):],
                         [{"name": "Inline", "value": 4, "size": 4, "bind": sb.STB_GLOBAL,
                           "type": sb.STT_FUNC, "shndx": 1}])

    def test_kept_names_must_be_unique_local_functions(self):
        native, output = self.native()
        for name in ("Missing", "Unit_Function"):
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, "not one local function"):
                sb.keep_object(native, {name: 0x80003114}, output)
        twice = self.SYMBOLS + [dict(self.SYMBOLS[1], value=0)]
        with self.assertRaisesRegex(ValueError, "not one local function"):
            sb.keep_object(self.native(twice)[0], {"Inline": 0x80003114}, output)
        # A function must be code and a table must be data.
        swapped = [self.SYMBOLS[0], self.SYMBOLS[1], dict(self.SYMBOLS[2], type=sb.STT_FUNC)]
        with self.assertRaisesRegex(ValueError, "not one local function or object"):
            sb.keep_object(self.native(swapped)[0], {"Table": 0x80004008}, output)
        self.assertFalse(output.exists())

    def test_a_kept_table_and_a_folded_alias_are_added(self):
        native, output = self.native()
        sb.keep_object(native, {"Inline": 0x80003114, "Table": 0x80004008}, output, aliases={"Table"})
        _, symbols = sb.read_elf(output.read_bytes())
        self.assertEqual([(s["name"], s["type"], s["shndx"], s["value"]) for s in symbols[-3:]],
                         [("Inline", sb.STT_FUNC, 1, 4), ("Table", sb.STT_OBJECT, 2, 0),
                          ("__folded_Table", sb.STT_OBJECT, 2, 0)])
        # The inventory lists a kept function once, not again under its folded alias.
        sb.keep_object(native, {"Inline": 0x80003114}, output, aliases={"Inline"})
        units, _, _ = self.load(self.kept_manifest())
        units[0]["sections"][0].update(index=1, compiled=8, executable=True)
        units[0]["sections"][1].update(index=2, compiled=4, executable=False)
        functions = sb.compiled_functions(units[0], sb.read_elf(output.read_bytes()))
        self.assertEqual([f["symbol"] for f in functions], ["Unit_Function", "Inline"])

    def test_a_fold_into_another_units_kept_copy_resolves_to_it(self):
        native, output = self.native()
        sb.keep_object(native, {"Inline": 0x80003114}, output, aliases={"Inline"})
        other = compiled([text(4)], [{"name": "__folded_Inline", "value": 0, "shndx": 0}])
        objects = {"src/unit.c": sb.read_elf(output.read_bytes()), "src/other.c": other}
        manifest = self.kept_manifest()
        manifest["units"][1]["folded"] = {"symbols": {"Inline": "0x80003114"}, "evidence": "x"}
        _, defined, resolved = self.plan(objects, manifest)
        self.assertEqual(defined["__folded_Inline"], (0x80003114, "src/unit.c"))
        self.assertNotIn("__folded_Inline", resolved)
        # Without kept_locals the copy is not published, and a fold elsewhere is still refused.
        plain = dict(objects, **{"src/unit.c": sb.read_elf(native)})
        manifest["units"][0].pop("kept_locals")
        with self.assertRaisesRegex(ValueError, "inside source unit"):
            self.plan(plain, manifest)
        manifest = self.kept_manifest()
        manifest["units"][1]["folded"] = {"symbols": {"Inline": "0x80003110"}, "evidence": "x"}
        with self.assertRaisesRegex(ValueError, "ambiguous|inside source unit"):
            self.plan(objects, manifest)

    def test_other_units_resolve_to_the_kept_copy_only_with_kept_locals(self):
        native, output = self.native()
        sb.keep_object(native, {"Inline": 0x80003114}, output)
        other = compiled([text(4)], [{"name": "Inline", "value": 0, "shndx": 0}])
        objects = {"src/unit.c": sb.read_elf(output.read_bytes()), "src/other.c": other}
        _, defined, resolved = self.plan(objects, self.kept_manifest())
        self.assertEqual(defined["Inline"], (0x80003114, "src/unit.c"))
        self.assertNotIn("Inline", resolved)
        # Without the kept copy the local cannot be reached: by name it is unresolved, and an
        # external at its address lies inside the source unit.
        plain = {"src/unit.c": sb.read_elf(native), "src/other.c": other}
        with self.assertRaisesRegex(ValueError, "unresolved symbol Inline"):
            self.plan(plain)
        manifest = copy.deepcopy(self.manifest)
        manifest["externals"] = {"Inline": {"address": "0x80003114", "evidence": "x"}}
        with self.assertRaisesRegex(ValueError, "inside source unit"):
            self.plan(plain, manifest)
        # The configured address must be where the copy is placed.
        with self.assertRaisesRegex(ValueError, "kept local Inline is not placed at 0x80003110"):
            self.plan(objects, self.kept_manifest(symbols={"Inline": "0x80003110"}))

    def test_kept_link_object_and_inventory(self):
        native, output = self.native()
        path = output.with_name("native.o")
        path.write_bytes(native)
        unit = {"source": "src/unit.c", "object": path, "link_roots": None, "folded": None,
                "kept_locals": {"Inline": 0x80003114}}
        sb.link_object(unit)
        self.assertEqual(unit["link_object"], path.with_suffix(".kept.o"))
        self.assertEqual(unit["link_object_sha256"], sb.sha256(unit["link_object"]))
        self.assertEqual(path.read_bytes(), native)
        # The inventory lists the kept function once.
        units, _, _ = self.load(self.kept_manifest())
        units[0]["sections"][0].update(index=1, compiled=8, executable=True)
        units[0]["sections"][1].update(index=2, compiled=4, executable=False)
        functions = sb.compiled_functions(units[0], sb.read_elf(unit["link_object"].read_bytes()))
        self.assertEqual(functions, [{"symbol": "Unit_Function", "address": "0x80003110", "size": 4},
                                     {"symbol": "Inline", "address": "0x80003114", "size": 4}])


class ReadOnlyDataAfterCode(Fixture):
    """A unit's read-only data may be configured directly after its own code in a code section."""

    def setUp(self):
        super().setUp()
        binary = bytearray(self.binary)
        binary[0x11C:0x120] = bytes(4)  # zero padding 0x8000311C-0x80003120 in .init
        self.sections = sb.target_sections(bytes(binary), TARGET, {})
        self.manifest["units"][0]["sections"] = [
            {"section": ".text", "placement": ".init", "start": "0x80003110", "end": "0x8000311C"},
            {"section": ".rodata", "placement": ".init", "start": "0x80003120", "end": "0x80003128",
             "follows": ".text"}]

    def objects(self, data=None):
        symbols = [{"name": "Unit_Function", "value": 0, "shndx": 1, "type": sb.STT_FUNC, "size": 12},
                   {"name": "Unit_Table", "value": 0, "shndx": 2, "type": 1, "size": 8}]
        return {"src/unit.c": compiled([text(12), data or rodata(8, align=8)], symbols)}

    def test_configured_read_only_data_follows_its_code(self):
        units, externals, _ = self.load()
        objects = self.objects()
        pieces, defined, _ = sb.plan(self.sections, units, objects, externals)
        layout = [(hex(p["start"]), hex(p["end"]), p.get("unit")) for p in pieces[".init"]]
        # No original piece covers the padding: the data's own alignment produces it.
        self.assertEqual(layout, [("0x80003100", "0x80003110", None),
                                  ("0x80003110", "0x8000311c", "src/unit.c"),
                                  ("0x80003120", "0x80003128", "src/unit.c"),
                                  ("0x80003128", "0x80003140", None)])
        self.assertEqual(defined, {"Unit_Function": (0x80003110, "src/unit.c"),
                                   "Unit_Table": (0x80003120, "src/unit.c")})
        functions = sb.compiled_functions(units[0], objects["src/unit.c"])
        self.assertEqual([f["symbol"] for f in functions], ["Unit_Function"])
        function = {"name": "Misplaced", "value": 0, "shndx": 2, "type": sb.STT_FUNC, "size": 4}
        with self.assertRaisesRegex(ValueError, "no code placement"):
            sb.compiled_functions(units[0], ([], [function]))

    def test_data_in_code_needs_an_explicit_read_only_configuration(self):
        manifest = copy.deepcopy(self.manifest)
        del manifest["units"][0]["sections"][1]["follows"]
        with self.assertRaisesRegex(ValueError, "cannot be placed in code section .init"):
            self.plan(self.objects(), manifest)
        writable = {"name": ".rodata", "type": sb.SHT_PROGBITS, "flags": sb.SHF_ALLOC | sb.SHF_WRITE,
                    "size": 8, "align": 8, "data": bytes(8)}
        with self.assertRaisesRegex(ValueError, "cannot be placed in code section .init"):
            self.plan(self.objects(writable))
        uninitialized = {"name": ".rodata", "type": sb.SHT_NOBITS, "flags": sb.SHF_ALLOC,
                         "size": 8, "align": 8}
        with self.assertRaisesRegex(ValueError, "cannot be placed in code section .init"):
            self.plan(self.objects(uninitialized))
        executable = dict(rodata(8, align=8), flags=sb.SHF_ALLOC | sb.SHF_EXECINSTR)
        with self.assertRaisesRegex(ValueError, "cannot be placed in code section .init"):
            self.plan(self.objects(executable))

    def test_follows_names_earlier_code_of_the_same_unit(self):
        cases = [(1, {"follows": ".missing"}, "must follow another configured section"),
                 (1, {"follows": ".rodata"}, "must follow another configured section"),
                 (1, {"follows": 1}, "applies only to data placed in a code section"),
                 (0, {"start": "0x80003128", "end": "0x80003134"}, "must follow another configured section"),
                 (1, {"placement": ".data2", "start": "0x80004000", "end": "0x80004008"},
                  "applies only to data placed in a code section")]
        for index, change, message in cases:
            manifest = copy.deepcopy(self.manifest)
            manifest["units"][0]["sections"][index].update(change)
            if index == 0:
                manifest["units"][0]["sections"][1].update(start="0x80003110", end="0x80003118")
            with self.subTest(change=change), self.assertRaisesRegex(ValueError, message):
                self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["units"].append({"source": "src/other.c", "profile": "library", "evidence": "x",
                                  "sections": [{"section": ".text", "placement": ".init",
                                                "start": "0x8000311C", "end": "0x80003120"}]})
        with self.assertRaisesRegex(ValueError, "lies between it and the code it follows"):
            self.load(manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][0]["follows"] = ".rodata"
        with self.assertRaisesRegex(ValueError, "must follow another configured section"):
            self.load(manifest)

    def test_data_must_start_at_its_alignment_after_the_code(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][1].update(start="0x80003128", end="0x80003130")
        with self.assertRaisesRegex(ValueError, "must start at 0x80003120, its 8-byte alignment"):
            self.plan(self.objects(), manifest)
        manifest = copy.deepcopy(self.manifest)
        manifest["units"][0]["sections"][1].update(start="0x8000311C", end="0x80003124")
        with self.assertRaisesRegex(ValueError, "alignment 8 does not fit"):
            self.plan(self.objects(), manifest)
        # With 4-byte alignment the data would start directly after the code.
        with self.assertRaisesRegex(ValueError, "must start at 0x8000311C, its 4-byte alignment"):
            self.plan(self.objects(rodata(8, align=4)))

    def test_padding_before_the_data_must_be_zero_in_the_target(self):
        self.sections = sb.target_sections(self.binary, TARGET, {})
        with self.assertRaisesRegex(ValueError, "padding 0x8000311C-0x80003120 before .rodata is not zero"):
            self.plan(self.objects())


class Build(unittest.TestCase):
    """Drive the complete build with mocked tool stages."""

    def run_build(self, output_bytes, link=True, units=True, mutate_native=False, extra=(), evidence=None):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        root = Path(temporary.name)
        binary = synthetic_dol()
        target = dict(TARGET, size=len(binary), sha1=hashlib.sha1(binary).hexdigest())
        (root / "config/GN7E69-rev0").mkdir(parents=True)
        (root / "tools").mkdir()
        (root / "src").mkdir()
        (root / "config/GN7E69-rev0/baseline.json").write_text(json.dumps(target))
        (root / "config/GN7E69-rev0/analysis.json").write_text(json.dumps({"output_sections": {}}))
        (root / "tools/compiler-tools.json").write_text(json.dumps({"compiler_version": "3.9.3"}))
        (root / "tools/baseline-tools.json").write_text("{}")
        (root / "src/unit.c").write_text("int unit;\n")
        manifest = {"schema": 1, "target": "GN7E69-rev0", "compiler": "3.9.3", "include_dirs": [],
                    "profiles": {"library": {"flags": ["-O2"], "evidence": "locator"}}, "externals": {},
                    "units": [{"source": "src/unit.c", "profile": "library", "evidence": "locator",
                               "sections": [{"section": ".text", "placement": ".init",
                                             "start": "0x80003110", "end": "0x80003118"}, *extra]}]
                    if units else []}
        manifest_path = root / "config/GN7E69-rev0/units.json"
        manifest_path.write_text(json.dumps(manifest))
        if evidence:
            (root / "config/GN7E69-rev0/evidence.tsv").write_text(evidence)
        original = root / "main.dol"
        original.write_bytes(binary)
        build = root / "build/source"
        report = build / "report.json"

        def stage(command, **kwargs):
            if command[-1].startswith("@"):
                import shlex
                command = command[:2] + shlex.split(Path(command[-1][1:]).read_text())
            if "-c" in command:
                obj = Path(command[command.index("-o") + 1])
                sb.write_object(obj, [text(8)], [{"name": "Unit_Function", "value": 0, "shndx": 1}])
                Path(command[command.index("--depfile") + 1]).write_text(
                    f"unit.o: {root / 'src/unit.c'}\n")
            elif "-T" in command and link:
                sb.write_object(Path(command[command.index("-o") + 1]), [text(4)],
                                [{"name": "Unit_Function", "value": 0x80003110, "shndx": sb.SHN_ABS}])
                if mutate_native:
                    native = next((build / "obj").glob("*.o"))
                    with native.open("ab") as output:
                        output.write(b"changed by tool")
            elif "elf2dol" in command:
                Path(command[-1]).write_bytes(output_bytes(binary))
            return type("Result", (), {"returncode": 0})()

        with patch.object(sb, "ROOT", root), patch.object(sb, "BUILD", build), \
                patch.object(sb.setup_compiler, "setup", return_value=(root / "cc", root / "wibo")), \
                patch.object(sb.baseline, "get_tool", return_value=root / "dtk"), \
                patch.object(sb.subprocess, "run", side_effect=stage):
            try:
                return sb.build(original, manifest_path, report), report
            except RuntimeError as error:
                return error, report

    def test_identical_output_reports_matched_unit_bytes(self):
        result, path = self.run_build(lambda binary: binary)
        self.assertEqual(result["complete"], "identical")
        self.assertEqual(result["totals"], {"code": {"linked": 8, "matched": 8},
                                            "data": {"linked": 0, "matched": 0}})
        self.assertEqual(result["units"][0]["dependencies"], {"src/unit.c": result["units"][0]["source_sha256"]})
        self.assertEqual(json.loads(path.read_text()), result)

    def test_zero_units_still_verify_the_complete_target(self):
        result, _ = self.run_build(lambda binary: binary, units=False)
        self.assertEqual(result["units"], [])
        self.assertEqual(result["totals"]["code"], {"linked": 0, "matched": 0})

    def test_mismatching_output_never_claims_matched_bytes(self):
        def corrupt(binary):
            changed = bytearray(binary)
            changed[0x100 + 0x30] ^= 0xFF
            return bytes(changed)
        error, path = self.run_build(corrupt)
        self.assertIsInstance(error, RuntimeError)
        report = json.loads(path.read_text())
        self.assertEqual(report["complete"], "mismatch")
        self.assertEqual(report["totals"]["code"], {"linked": 8, "matched": 0})
        self.assertEqual(report["units"][0]["sections"][0]["status"], "range-identical")

    def test_changed_native_linker_input_is_rejected_before_progress(self):
        error, path = self.run_build(lambda binary: binary, mutate_native=True)
        self.assertRegex(str(error), "native compiler object")
        self.assertFalse(path.exists())

    def test_linker_must_produce_a_fresh_elf(self):
        error, path = self.run_build(lambda binary: binary, link=False)
        self.assertRegex(str(error), "fresh ELF")
        self.assertFalse(path.exists())

    def test_data_after_code_cannot_cover_an_evidence_function(self):
        # Review of PR #78: target instruction words compiled as a const array must not be
        # credited as matched data after code where evidence records a function.
        follower = {"section": ".rodata", "placement": ".init", "start": "0x80003118", "end": "0x80003120",
                    "follows": ".text"}
        header = "kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
        block = "data\t0x80003118\t0x80003120\tdata_80003118\ttarget\texact\texact\tfixture\n"
        function = "function\t0x8000311C\t0x80003124\tfn_8000311C\ttarget\texact\texact\tfixture\n"
        with self.assertRaisesRegex(ValueError, "overlaps function fn_8000311C 0x8000311C-0x80003124"):
            self.run_build(lambda binary: binary, extra=[follower], evidence=header + block + function)

    def test_data_after_code_must_be_an_exact_evidence_data_block(self):
        # Hostile recheck of PR #78: code with no inventory candidate and no evidence row must not
        # be claimable as data after code.
        follower = {"section": ".rodata", "placement": ".init", "start": "0x80003118", "end": "0x80003120",
                    "follows": ".text"}
        header = "kind\tstart\tend\tsubject\torigin\tstart_boundary\tend_boundary\tevidence\n"
        for rows in ("", "data\t0x80003118\t0x8000311C\tdata_80003118\ttarget\texact\texact\tfixture\n",
                     "data\t0x80003118\t0x80003120\tdata_80003118\ttarget\texact\tprovisional\tfixture\n"):
            with self.subTest(rows=rows), \
                    self.assertRaisesRegex(ValueError, "does not equal an evidence data row with exact edges"):
                self.run_build(lambda binary: binary, extra=[follower], evidence=header + rows)
        # An exact data row passes the evidence gate; this mocked compiler then emits no .rodata.
        block = "data\t0x80003118\t0x80003120\tdata_80003118\ttarget\texact\texact\tfixture\n"
        with self.assertRaisesRegex(ValueError, "configured section .rodata was not produced"):
            self.run_build(lambda binary: binary, extra=[follower], evidence=header + block)




class CompilerFunctionCoverageTests(unittest.TestCase):
    def unit(self):
        return {"source": "src/game/example.cpp", "sections": [
            {"index": 1, "kind": "code", "start": 0x80003100, "compiled": 16}]}

    def test_local_generated_and_mangled_functions_are_resolved_from_placements(self):
        symbols = [{"name": name, "type": sb.STT_FUNC, "bind": bind,
                    "shndx": 1, "value": index * 4, "size": 4}
                   for index, (name, bind) in enumerate([
                       ("Update__8UIScreenFv", sb.STB_GLOBAL),
                       ("I.src_game_example_cpp", sb.STB_LOCAL),
                       ("D.src_game_example_cpp", sb.STB_LOCAL),
                       ("fn_8000310C", sb.STB_GLOBAL)])]
        symbols += [{"name": "external", "type": sb.STT_FUNC, "bind": sb.STB_GLOBAL,
                     "shndx": sb.SHN_UNDEF, "value": 0, "size": 4},
                    {"name": "zero", "type": sb.STT_FUNC, "bind": sb.STB_LOCAL,
                     "shndx": 1, "value": 0, "size": 0}]
        functions = sb.compiled_functions(self.unit(), ([], symbols))
        self.assertEqual([function["address"] for function in functions],
                         [f"0x{0x80003100 + index * 4:08X}" for index in range(4)])
        self.assertEqual([function["symbol"] for function in functions],
                         [symbol["name"] for symbol in symbols[:4]])

    def test_defined_functions_outside_placed_code_are_rejected(self):
        for shndx, value, size in ((2, 0, 4), (1, 14, 4), (1, -4, 4)):
            with self.subTest(shndx=shndx, value=value, size=size):
                symbol = {"name": "Example", "type": sb.STT_FUNC, "shndx": shndx,
                          "value": value, "size": size}
                with self.assertRaises(ValueError):
                    sb.compiled_functions(self.unit(), ([], [symbol]))



class SNBssContainerTests(unittest.TestCase):
    def setUp(self):
        self.native = {"name": ".bss", "type": sb.SHT_NOBITS, "flags": 3,
                       "size": 54, "align": 32, "index": 1}
        self.linked = {**self.native, "size": 56}
        self.object = {"name": "studio", "shndx": 1, "value": 0,
                       "size": 54, "type": 1}
        self.tag = {"name": "__sn__bss__tag__", "shndx": 1, "value": 56,
                    "size": 0, "type": 0, "bind": sb.STB_GLOBAL}

    def check(self, native=None, linked=None, symbols=None):
        return sb.sn_bss_container_size(native or self.native, linked or self.linked,
                                       symbols if symbols is not None else [self.object, self.tag])

    def test_recognizes_only_container_and_does_not_mutate_native_allocation(self):
        for size in (9, 10, 11, 13, 14, 15, 54):
            with self.subTest(size=size):
                native = {**self.native, "size": size}
                linked = {**self.linked, "size": (size + 3) & ~3}
                symbols = [{**self.object, "size": size},
                           {**self.tag, "value": linked["size"]}]
                self.assertEqual(self.check(native, linked, symbols), linked["size"])
                self.assertEqual(native["size"], size)

    def test_rejects_extra_padding_or_shortening(self):
        for size in (52, 55, 57, 64):
            with self.subTest(size=size), self.assertRaises(ValueError):
                self.check(linked={**self.linked, "size": size})

    def test_rejects_initialized_data_and_changed_flags_or_alignment(self):
        for changes in ({"type": sb.SHT_PROGBITS}, {"name": ".data"},
                        {"flags": 1}, {"align": 4}):
            with self.subTest(changes=changes), self.assertRaises(ValueError):
                self.check(linked={**self.linked, **changes})

    def test_requires_exact_unique_zero_size_end_tag(self):
        for symbols in ([self.object], [self.object, self.tag, self.tag],
                        [self.object, {**self.tag, "value": 54}],
                        [self.object, {**self.tag, "size": 2}],
                        [self.object, {**self.tag, "type": 1}],
                        [self.object, {**self.tag, "bind": sb.STB_LOCAL}]):
            with self.subTest(symbols=symbols), self.assertRaises(ValueError):
                self.check(symbols=symbols)

    def test_rejects_owned_symbols_in_container_tail(self):
        for symbol in ({**self.object, "size": 56},
                       {**self.object, "value": 1},
                       {**self.object, "name": "padding", "value": 54, "size": 2},
                       {**self.object, "name": "end", "value": 55, "size": 0}):
            with self.subTest(symbol=symbol), self.assertRaises(ValueError):
                self.check(symbols=[symbol, self.tag])

    def test_rejects_aligned_native_size_as_a_rounding_exception(self):
        with self.assertRaises(ValueError):
            self.check(native={**self.native, "size": 56})

if __name__ == "__main__":
    unittest.main()
