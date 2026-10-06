# Build Analysis: UEFA Champions League 2004-2005 (Europe GameCube) (DOL-GUCP-EUR)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: UEFA Champions League 2004-2005
- **Platform**: Nintendo GameCube
- **Region**: Europe (PAL)
- **Serial / Product Code**: `DOL-GUCP-EUR`
- **Disc / Volume ID**: `GUCP69`
- **Revision / Build Number**: Development Master (SN Systems Linker Map Debug Build)
- **Developer / Publisher**: EA Canada / EA SPORTS
- **Release Year**: 2004
- **Toolchain**: SN Systems ProDG (`ngcld`, `gc-sn-release`)

---

## Executive Summary
This build provides the **definitive link-order map for shared EA 2004 GameCube middleware**.

* **Main Executable (`fifa_z.elf`)**: 4.19 MB PowerPC Gekko executable.
* **Full Linker Map (`symbols/fifa_z.map`)**:
  * 20,409 lines of complete SN Systems linker map output.
  * Documents every object file (`.o` / `.obj`), link-order address, size, and demangled C++ symbol across EA's core library blocks:
    * `libsndgc`: 180+ functions
    * `libeaglSN`: 171+ functions
    * `libvp6decode`: 127+ functions
    * `librealfile`: 52+ functions
    * `librealmemcard`: 39+ functions
    * `librcmp*`: 53+ functions
    * `libspch`: 21+ functions

---

## Exported Directory Structure

```text
references/UEFA Champions League 2004-2005/DOL-GUCP-EUR/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   └── fifa_z.map             # Full SN linker map (20,409 lines)
└── strings/
    └── debug_strings.txt      # Engine asserts, camera scripts, and diagnostics
```
