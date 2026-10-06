# Build Analysis: NFL Street 2 - Unleashed (Europe PSP) (ULES-00036)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2: Unleashed
- **Platform**: Sony PlayStation Portable (PSP)
- **Region**: Europe (PAL)
- **Serial / Product Code**: `ULES-00036`
- **Disc / Volume ID**: `ULES_00036`
- **Revision / Build Number**: Revision 1.00 (Retail Master, PSP Firmware 2.00+)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2005

---

## Executive Summary
This build represents the retail European PAL PlayStation Portable (PSP) release of **NFL Street 2: Unleashed**.

* **Unencrypted Dev Executable (`BOOT.BIN`)**: 4.93 MB MIPS R4000 (Allegrex) 32-bit ELF executable (within 1 KB of the North American release).
  * Direct unencrypted ELF binary preserved alongside the signed `EBOOT.BIN`.
  * Preserves 84 section headers, Sony PSP OS stubs, and dynamic relocations.
* **Engine Customizations for Handheld**:
  * Core animation logic: source anchor `AASSIGN.C`.
  * Dedicated PSP mini-game state machines:
    * `MiniGameObstacleCoursePrePlayC`, `MiniGame2MinutePrePlayC`, `MiniGame4On4PrePlayC`, `MiniGameCrushCarrierPrePlayC`, `MiniGameJumpBallPrePlayC`, `MiniGameOpenFieldPrePlayC`, `MiniGameTargetPassingPrePlayC`.
* **Screen State Management**:
  * `screens\glue\glue` glue-layer and UI state functions (`InitScreen`, `ShutScreen`, `LoadScreenStrings`).

---

## Exported Directory Structure

```text
references/NFL Street 2/ULES-00036/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   └── elf_sections.tsv       # 84 ELF section definitions (stubs, relocations, text)
└── strings/
    └── debug_strings.txt      # Mini-game state classes, UI glue handlers, debug strings
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Regional Stability**: Confirms that handheld versions maintained identical unit and module structures between European and North American releases.
2. **Animation Assignment (`AASSIGN.C`)**: Validates the cross-platform nature of the core gameplay modules across all sixth-generation systems and the PSP.
