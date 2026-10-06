# Build Analysis: Medal of Honor: European Assault (USA GameCube) (DOL-GONE-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: Medal of Honor: European Assault
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GONE-USA`
- **Disc / Volume ID**: `GONE69`
- **Revision / Build Number**: Development DVD Master (DWARF 1 Debug Build)
- **Developer / Publisher**: EA Los Angeles / EA GAMES
- **Release Year**: 2005
- **Toolchain**: SN Systems ProDG (`ngcld`, GCC 2.95.3)

---

## Executive Summary
This build contains an unstripped development DVD executable with **10.7 MB of DWARF 1 debug data and 26,789 named symbols**.

* **Main Executable (`MOH4RDVD.ELF`)**: 17.88 MB (17,877,216 bytes) PowerPC Gekko executable.
* **Symbol Inventory (`symbols/symbols.tsv`)**:
  * 26,789 named functions and variables.
  * Deep coverage of EA system libraries (file I/O, memory card, sound drivers).
* **Cross-Reference Match**:
  * Contributed 9 unique function matches to *NFL Street 2* (`GN7E69`), including `BuildMatrix__Q24EAGL9TransformPC7MATRIX4` (`EAGL::Transform::BuildMatrix`).

---

## Exported Directory Structure

```text
references/Medal of Honor - European Assault/DOL-GONE-USA/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   ├── elf_sections.tsv       # ELF section definitions
│   └── symbols.tsv            # 26,789 symbols (Address, Size, Type, Name)
└── strings/
    └── debug_strings.txt      # Engine asserts, camera scripts, and diagnostics
```
