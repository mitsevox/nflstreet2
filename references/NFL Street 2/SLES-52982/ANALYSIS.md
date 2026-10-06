# Build Analysis: NFL Street 2 (Europe PAL PS2) (SLES-52982)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2
- **Platform**: Sony PlayStation 2
- **Region**: Europe (PAL)
- **Serial / Product Code**: `SLES-52982`
- **Disc / Volume ID**: `SLES_529.82`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2005

---

## Executive Summary
This build represents the retail European PAL release of **NFL Street 2** on PlayStation 2.

* **Main Executable (`SLES_529.82.elf`)**: 3.95 MB MIPS Emotion Engine executable. Stripped of `.symtab` and DWARF debug sections.
  * Notice: Like Street 1 PAL, the European release of Street 2 omits online play and the Sony Network GUI, reducing binary size by ~391 KB compared to the North American edition (`SLUS_211.18`, 4.34 MB).
* **IOP Modules (`modules/`)**: 10 standard Sony IOP drivers extracted from `SYSTEM/` (`LIBSD.IRX`, `MCMAN.IRX`, `PADMAN.IRX`, `SNDDRV.IRX`, etc.).
* **Diagnostic & Host Tooling**:
  * Preserves in-game camera & replay debug editor: `REPLAY.C`, `EDIT MODE: DEFAULT`, `CAMLOCK`, `ADVANCE FOCUS TARGET / GREENSCREEN`, `GREEN SCREEN MODE: ON/OFF`.
  * PAL display palette arrays: `CPAL*` lookup tables and 50Hz/60Hz selector strings.
  * UIStudio assertions and error callbacks:
    * `"Attempting to load a rate function while it's screen is being unloaded."`
    * References to `UIStudio.c` and `UISEvent.c`.
* **Object Schemas**: 1.39 MB of Tiburon Object Definition File (ODF) XML specifications (`DATA/OBJDEFS.DAT`), comprising 15,872 readable tokens.

---

## Exported Directory Structure

```text
references/NFL Street 2/SLES-52982/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   └── irx_symbols.tsv        # IRX module symbol log
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Clean Offline Logic Baseline**: Excising the online subsystem provides a simpler binary for decompiling core gameplay, passing mechanics, and AI routines without network multiplayer hooks.
2. **UIStudio Alignment**: Validates identical UIStudio error handling and state machines across European and North American builds.
