# Build Analysis: NFL Street 2 (Europe GameCube) (DOL-GN7P-UKV)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2
- **Platform**: Nintendo GameCube
- **Region**: United Kingdom / Europe (PAL)
- **Serial / Product Code**: `DOL-GN7P-UKV`
- **Disc / Volume ID**: `GN7P69`
- **Revision / Build Number**: Revision 0 (v1.00 Retail Master)
- **Maker Code**: `69` (Electronic Arts)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2005

---

## Executive Summary
This build represents the European PAL release of **NFL Street 2** on Nintendo GameCube. Because our primary project decompilation target is **NFL Street 2 GameCube USA (`GN7E69`)**, this is the single closest official retail binary to our target in existence.

* **Main Executable (`main.dol`)**: 3.17 MB PowerPC Gekko DOL binary.
  * Entry Point: `0x80003100` (matches `GN7E69` exactly)
  * Main Text Base: `0x80003480` (matches `GN7E69` exactly)
  * Total binary size: 3,173,152 bytes.
* **Direct Comparison to Primary Target (`GN7E69`)**:
  * In `GN7E69`, `UIStudio.c` is anchored at `0x802B1DC4`.
  * In this `GN7P69` European binary, `UIStudio.c` is anchored at `0x802B239C`.
  * **Offset Delta**: Exactly `+0x5D8` bytes (1,496 bytes).
  * This confirms that the internal compilation unit boundaries, linker order, and data section alignments are practically identical between the USA and PAL releases of NFL Street 2.
* **Dolphin SDK Anchors**: Preserves exact source anchors:
  * `OSThread.c` (`0x802fc9e0`), `GXMisc.c` (`0x802fe7f8`), `GBAKey.c` (`0x80306980`), `dvdfs.c` (`0x803ec638`), `dvd.c` (`0x803ec64c`), `vi.c` (`0x803ec6bc`).
* **Object Schemas**: Extracted `objdefs.dat` from FST (1.39 MB), containing 15,892 tokens of Street 2 dynamic object specifications.

---

## Exported Directory Structure

```text
references/NFL Street 2/DOL-GN7P-UKV/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── dol_sections.tsv       # Memory map of all text, data, and BSS sections
│   └── source_anchors.tsv     # Source path string anchors in GameCube memory
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Direct Cross-Reference to Primary Target (`GN7E69`)

| Anchor / Section | `GN7E69` (Target) | `GN7P69` (This Build) | Shift / Alignment |
| :--- | :--- | :--- | :--- |
| **Entry Point** | `0x80003100` | `0x80003100` | Exact Match (`0x0`) |
| **`.text` Base** | `0x80003480` | `0x80003480` | Exact Match (`0x0`) |
| **`UIStudio.c`** | `0x802B1DC4` | `0x802B239C` | `+0x5D8` bytes |
| **`UISEvent.c`** | `0x802B1DF0` | `0x802B23C8` | `+0x5D8` bytes |
| **Object Schemas** | Identical | Identical (1.39 MB) | Exact Match |

---

## Value to the Decompilation Effort
Because of the minimal `+0x5D8` delta, this binary can be used in Ghidra / IDA with automatic address remapping to cross-verify function prologues, register spills, and compiler optimizations where `GN7E69` assembly is ambiguous.
