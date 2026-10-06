# Build Analysis: GoldenEye: Rogue Agent (USA GameCube) (DOL-GOYE-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: GoldenEye: Rogue Agent
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GOYE-USA`
- **Disc / Volume ID**: `GOYE69`
- **Revision / Build Number**: Development DVD Master (DWARF 1 Debug Build)
- **Developer / Publisher**: EA Los Angeles / EA GAMES
- **Release Year**: 2004
- **Toolchain**: SN Systems ProDG (`ngcld`, GCC 2.95.3)

---

## Executive Summary
This build contains an unstripped development DVD executable with **10.4 MB of DWARF 1 debug data and 32,940 named symbols**.

* **Main Executable (`GE2RDVD.ELF`)**: 18.19 MB (18,189,280 bytes) PowerPC Gekko executable.
* **Symbol Inventory (`symbols/symbols.tsv`)**:
  * 32,940 named functions and variables.
  * Comprehensive C++ types and struct definitions for EAGL graphics, matrix pipelines, and codecs.
* **Cross-Reference Match**:
  * Contributed 3 unique function matches to *NFL Street 2* (`GN7E69`), including melee behavior heuristics and vehicle pathfinding.

---

## Exported Directory Structure

```text
references/GoldenEye - Rogue Agent/DOL-GOYE-USA/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   ├── elf_sections.tsv       # ELF section definitions
│   └── symbols.tsv            # 32,940 symbols (Address, Size, Type, Name)
└── strings/
    └── debug_strings.txt      # Engine asserts, camera scripts, and diagnostics
```
