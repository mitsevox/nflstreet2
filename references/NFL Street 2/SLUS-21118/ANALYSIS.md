# Build Analysis: NFL Street 2 (USA Retail PS2) (SLUS-21118)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2
- **Platform**: Sony PlayStation 2
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `SLUS-21118`
- **Disc / Volume ID**: `SLUS_211.18`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build represents the final retail North American PlayStation 2 release of **NFL Street 2**.

* **Main Executable (`SLUS_211.18.elf`)**: 4.34 MB MIPS Emotion Engine executable. Stripped of `.symtab` and DWARF debug sections.
  * Size expanded from 3.26 MB in Street 1 to 4.34 MB, reflecting the new wall-moves, gauntlet mode, and extended play calling systems.
* **Network Subsystem (`ntgui.elf`)**: 4.19 MB standalone Sony Network GUI executable.
* **IOP Modules (`modules/`)**: 62 IRX driver modules extracted across root and `/NETGUI/MODULES/`. Retains 135 symbols in modules like `USBINIT.IRX`.
* **Diagnostic & Host Tooling**:
  * Preserves in-game camera & replay debug editor: `REPLAY.C`, `EDIT MODE: DEFAULT`, `CAMLOCK`, `ADVANCE FOCUS TARGET / GREENSCREEN`, `GREEN SCREEN MODE: ON/OFF`.
  * UIStudio assertions and error callbacks:
    * `"Attempting to load a rate function while it's screen is being unloaded."`
    * References to `UIStudio.c` and `UISEvent.c`.
* **Object Schemas**: 1.39 MB of Tiburon Object Definition File (ODF) XML specifications (`DATA/OBJDEFS.DAT`), comprising 15,872 readable tokens.

---

## Exported Directory Structure

```text
references/NFL Street 2/SLUS-21118/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   └── irx_symbols.tsv        # Symbols extracted from IOP modules
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Engine Feature Parity**: Contains the exact full feature set, animations, and game rules present in `GN7E69`.
2. **UIStudio Stability**: Confirms that UIStudio's internal callbacks and error strings remained identical between the GameCube and PS2 editions of NFL Street 2.
3. **Cross-Architecture Reference**: Functions in `SLUS_211.18.elf` can be decompiled in Ghidra to provide high-level C pseudocode when analyzing difficult PowerPC functions in `GN7E69`.
