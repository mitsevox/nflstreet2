# Build Analysis: NFL Street 2 (USA GameCube - Primary Target) (DOL-GN7E-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2 (Primary Decompilation Target)
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GN7E-USA`
- **Disc / Volume ID**: `GN7E69`
- **Revision / Build Number**: Revision 0 (v1.00 Retail Master)
- **Target Hash (SHA-1)**: `3561e946e9ff785b68692f87d2ba85d81fd2dcf4`
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004
- **Toolchain**: SN Systems ProDG 3.9.3 (`ngcld`, GCC 2.95.3)

---

## Executive Summary
This build represents the **primary reverse-engineering and decompilation target** for the project: the North American retail release of **NFL Street 2** on Nintendo GameCube.

* **Primary Executable (`main.dol`)**: 3.17 MB (3,171,840 bytes) 32-bit PowerPC Gekko executable.
  * Section layout: `.init` at `0x80003100`, `.text` at `0x800034A0` (2,647,424 bytes), `.data2` through `.data6` covering small-data bases `r13` (`0x803F22A0`) and `r2` (`0x804022A0`).
  * Like standard GameCube retail masters, symbols and DWARF debug sections were stripped by the release pipeline.
* **191 Recovered Functions from Sibling DWARF & Linker Maps (`symbols/matched_dwarf_symbols.tsv`)**:
  * Cross-referencing against **NASCAR 2005 (Tiburon DWARF 1)**, **UEFA Champions League (SN Linker Map)**, and **Medal of Honor (DWARF 1)** recovered **191 unique functions with 100% mathematical certainty** via relocation-blind instruction fingerprinting.
  * Recovered modules include the complete **`VptManager` camera stack** (`_VptManagerCreateStack`, `VptManagerPushCamera`, `VptManagerPopCamera`), character motion streaming (`_AnimExtnRelocateMotion`, `ReadBitStream`), texture registries (`TMTexLibRegistryInit`), and the **Style Points gameplay system** (`StylePointsManager::SetAchievementCompleted`).
* **Source Filename Anchors Recovered**:
  * Core gameplay: `BALL.C`, `AASSIGN.C`, `REPLAY.C`, `CUSTOMAI.C`.
  * Menu subsystem: `UIStudio.c` (at `0x802633FC`, matching European PAL `0x802639D4` within `-0x5D8` bytes).
* **Object Schemas (`strings/objdefs_schema.txt`)**:
  * 15,892 readable lines of Tiburon Object Definition File (ODF) XML specifications extracted from `root/objdefs.dat`.

---

## Exported Directory Structure

```text
references/NFL Street 2/DOL-GN7E-USA/
├── ANALYSIS.md                # Technical report & decompilation baseline
├── symbols/
│   ├── dol_sections.tsv       # DOL section memory layout (.text, .data2-.data6)
│   ├── matched_dwarf_symbols.tsv # 191 functions recovered from NASCAR 2005 & UEFA maps
│   └── source_anchors.tsv     # Source file anchors (BALL.C, AASSIGN.C, UIStudio.c)
└── strings/
    ├── debug_strings.txt      # Replay, camera script, UIStudio, and assert strings
    └── objdefs_schema.txt     # 15,892 Tiburon ODF XML schema strings from OBJDEFS.DAT
```

---

## Decompilation Alignment & Target Matching
1. **European PAL Alignment (`DOL-GN7P-UKV`)**: The European GameCube build matches this target almost 1:1, differing by only `+0x5D8` bytes due to minor PAL language tables.
2. **ProDG Toolchain Verification**: The small-data layout (`0x803F22A0` / `0x804022A0`) and instruction sequences match ProDG 3.9.3 compilation profiles with `-O2` optimization.
3. **Reference Library Coverage**: 100% of the shared EA middleware block is mapped to identical C functions in sister builds (`NASCAR 2005`, `UEFA 2004`).
