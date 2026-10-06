# Build Analysis: FIFA Soccer 2005 (USA GameCube) (DOL-GF5E-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: FIFA Soccer 2005
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GF5E-USA`
- **Disc / Volume ID**: `GF5E69`
- **Revision / Build Number**: Development Master (SN Systems Linker Map Debug Build)
- **Developer / Publisher**: EA Canada / EA SPORTS
- **Release Year**: 2004
- **Toolchain**: SN Systems ProDG (`ngcld`, `gc-sn-release`)

---

## Executive Summary
This build provides the North American counterpart linker map to *UEFA Champions League 2004-2005*.

* **Main Executable (`fifa_z.elf`)**: 4.19 MB PowerPC Gekko executable.
* **Full Linker Map (`symbols/fifa_z.map`)**:
  * 18,477 lines of SN Systems linker map output.
  * Cross-verifies object link orders for `libeaglSN`, `libsndgc`, `librealmemcard`, and `librealfile`.

---

## Exported Directory Structure

```text
references/FIFA Soccer 2005/DOL-GF5E-USA/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   └── fifa_z.map             # Full SN linker map (18,477 lines)
└── strings/
    └── debug_strings.txt      # Engine asserts, camera scripts, and diagnostics
```
