# Build Analysis: NFL Street (USA GameCube) (DOL-GNNE-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GNNE-USA`
- **Disc / Volume ID**: `GNNE69`
- **Revision / Build Number**: Revision 0 (v1.00 Retail Master)
- **Maker Code**: `69` (Electronic Arts)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build is the North American retail release of NFL Street 1 on Nintendo GameCube. Because our primary project decompilation target is **NFL Street 2 GameCube (`GN7E69`)**, this binary is directly comparable in architecture, toolchain, and PowerPC Gekko calling conventions.

* **Main Executable (`main.dol`)**: 2.75 MB PowerPC Gekko DOL binary. 
  * Entry Point: `0x80003100`
  * Main Text: `0x80003480` (length `0x240D40` = 2.36 MB)
  * Constant / Read-Only Data: `0x80244200` & `0x8026A340`
  * BSS Address: `0x802A05C0` (size `0x1045AD` = 1.07 MB)
* **Exact Toolchain Match to Project**:
  * Inferred Compiler: Metrowerks CodeWarrior (MWCC) for Nintendo GameCube (paired with SN Systems ProDG for UIStudio).
  * Direct source path anchors match the project's layout exactly:
    * `0x802639d4`: `../../../Source/Common/UIStudio/UIStudio.c`
    * `0x80263a00`: `../../../Source/Common/UIStudio/UISEvent.c`
* **Dolphin OS / SDK Anchors**: Preserves exact source anchors for Nintendo SDK components:
  * `OSThread.c` (`0x80296330`), `GXMisc.c` (`0x80297fe0`), `GBAKey.c` (`0x802a0120`), `dvdfs.c` (`0x803a3890`), `dvd.c` (`0x803a38a4`), `vi.c` (`0x803a3914`).
* **Object Schemas**: Extracted `objdefs.dat` from the GameCube FST, confirming identical XML ODF object properties and physics definitions.

---

## Exported Directory Structure

```text
references/NFL Street/DOL-GNNE-USA/
├── ANALYSIS.md                # This analysis document
├── Vimm's Lair.txt
├── symbols/
│   ├── dol_sections.tsv       # Memory map of all text, data, and BSS sections
│   └── source_anchors.tsv     # Source path string anchors in GameCube memory
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Direct Cross-Reference to NFL Street 2 (`GN7E69`)

| Feature | NFL Street 1 (`GNNE69`) | NFL Street 2 (`GN7E69`) | Significance |
| :--- | :--- | :--- | :--- |
| **Architecture** | PowerPC 750CL (Gekko 32-bit) | PowerPC 750CL (Gekko 32-bit) | Identical register usage and ABI |
| **Entry Point** | `0x80003100` | `0x80003100` | Identical CRT0 startup |
| **Main Text Base** | `0x80003480` | `0x80003480` | Exact alignment of base executable code |
| **`UIStudio.c` Anchor** | `0x802639D4` | `0x802B1DC4` | Shift of `+0x4DDF0` in GameCube memory space |
| **`UISEvent.c` Anchor**| `0x80263A00` | `0x802B1DF0` | Shift of `+0x4DDF0` in GameCube memory space |
| **SDK Components** | `dvd.c`, `OSThread.c`, `vi.c` | Identical SDK libraries | Enables direct function boundary cross-checking |

---

## Relevance to Decompilation Projects
1. **PPC Gekko Assembly Equivalence**: Unlike the PS2 builds (which use MIPS EE), this DOL uses the exact same PowerPC Gekko instruction set, Metrowerks/ProDG flags, and memory map as `GN7E69`.
2. **Function Boundary Diffing**: Functions between `0x80003480` and `0x802441C0` can be directly mapped to `GN7E69` using Ghidra's Version Tracking or BinExport/BinDiff to identify shared functions.
3. **UIStudio Ground Truth**: Confirms that UIStudio's relative function layout and compiler profiles are directly inherited across Street 1 and Street 2.
