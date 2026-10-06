# Build Analysis: NFL Street (Europe GameCube) (DOL-GNNP-NOE)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street
- **Platform**: Nintendo GameCube
- **Region**: Europe / Germany (PAL)
- **Serial / Product Code**: `DOL-GNNP-NOE`
- **Disc / Volume ID**: `GNNP69`
- **Revision / Build Number**: Revision 0 (v1.00 Retail Master)
- **Maker Code**: `69` (Electronic Arts)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build represents the European PAL release of NFL Street 1 on Nintendo GameCube.

* **Main Executable (`main.dol`)**: 2.75 MB PowerPC Gekko DOL binary.
  * Entry Point: `0x80003100`
  * Main Text: `0x80003480`
  * BSS Address: `0x802A0200`
  * Total binary size: 2,753,408 bytes (within 1 KB of the North American release).
* **Direct Alignment with US Release (`GNNE69`)**:
  * In the North American GameCube release, `UIStudio.c` is anchored at `0x802639D4`.
  * In this European release, `UIStudio.c` is anchored at `0x80263674`, reflecting an offset shift of only `0x360` bytes between the two regional builds.
* **Dolphin SDK Anchors**: Preserves exact source anchors for Nintendo SDK components:
  * `OSThread.c` (`0x80295f70`), `GXMisc.c` (`0x80297c20`), `GBAKey.c` (`0x8029fd60`), `dvdfs.c` (`0x803a3488`), `dvd.c` (`0x803a349c`), `vi.c` (`0x803a350a`).
* **Object Schemas**: Extracted `objdefs.dat` from the GameCube FST, confirming identical XML ODF object properties and physics definitions.

---

## Exported Directory Structure

```text
references/NFL Street/DOL-GNNP-NOE/
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

## Relevance to Decompilation Projects
1. **Regional Delta Analysis**: The near-exact address alignment with `DOL-GNNE-USA` (< 1 KB difference across 2.75 MB of code) demonstrates that regional PAL modifications for GameCube did not restructure compilation units or object boundaries.
2. **PPC Instruction Matching**: Like the US GameCube build, this DOL compiles to PowerPC Gekko assembly using the exact same CodeWarrior ABI and register allocation rules as our `GN7E69` target.
