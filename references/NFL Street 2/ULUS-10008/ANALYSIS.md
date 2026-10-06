# Build Analysis: NFL Street 2 - Unleashed (USA PSP) (ULUS-10008)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2: Unleashed
- **Platform**: Sony PlayStation Portable (PSP)
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `ULUS-10008`
- **Disc / Volume ID**: `ULUS_10008`
- **Revision / Build Number**: Revision 1.00 (Retail Master, PSP Firmware 2.00+)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2005

---

## Executive Summary
This build represents the retail North American PlayStation Portable (PSP) release of **NFL Street 2: Unleashed**.

* **Unencrypted Dev Executable (`BOOT.BIN`)**: 4.93 MB MIPS R4000 (Allegrex) 32-bit ELF executable.
  * Unlike standard retail PSP games where code is encrypted under `~PSP` signatures in `EBOOT.BIN`, the UMD disc includes the complete unencrypted `BOOT.BIN` ELF used by devkits.
  * Contains 84 ELF sections, including relocations (`.rel.text`), Sony OS stub interfaces (`.sceStub.text.*`), and module tables.
* **Engine Customizations for Handheld**:
  * Retains core animation logic: source anchor `AASSIGN.C`.
  * Dedicated PSP mini-game state machines:
    * `MiniGameObstacleCoursePrePlayC` (Obstacle Course)
    * `MiniGame2MinutePrePlayC` (2-Minute Drill)
    * `MiniGame4On4PrePlayC` (4 on 4 mode)
    * `MiniGameCrushCarrierPrePlayC` (Crush the Carrier)
    * `MiniGameJumpBallPrePlayC` (Jump Ball)
    * `MiniGameOpenFieldPrePlayC` (Open Field Showdown)
    * `MiniGameTargetPassingPrePlayC` (Target Passing)
* **Screen State Management**:
  * Employs the `screens\glue\glue` glue-layer and UI state functions (`InitScreen`, `ShutScreen`, `LoadScreenStrings`).

---

## Exported Directory Structure

```text
references/NFL Street 2/ULUS-10008/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   └── elf_sections.tsv       # 84 ELF section definitions (stubs, relocations, text)
└── strings/
    └── debug_strings.txt      # Mini-game state classes, UI glue handlers, debug strings
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Unencrypted 32-bit MIPS Codebase**: Offers another clean, unencrypted RISC disassembly of the NFL Street 2 engine to cross-reference against PowerPC Gekko routines.
2. **Animation Assignment (`AASSIGN.C`)**: Re-confirms that the animation assignment system was standardized across GameCube, PS2, Xbox, and PSP.
