# Build Analysis: NFL Street (Europe) (SLES-52025)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street
- **Platform**: Sony PlayStation 2
- **Region**: Europe (PAL)
- **Serial / Product Code**: `SLES-52025`
- **Disc / Volume ID**: `SLES_520.25`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build represents the final retail European PAL release of NFL Street 1 on PlayStation 2.

* **Main Executable (`SLES_520.25.elf`)**: 3.05 MB MIPS Emotion Engine executable. The binary is stripped of `.symtab` and DWARF debug sections. Compared to the US Demo (`SLUS_290.93`, 3.18 MB), this executable is ~138 KB smaller because all online matchmaking and network logic was removed for the European release.
* **Absence of Online Modules**: Unlike the North American builds, the European release completely omits `DATA/ONLINE.DAT` and network IOP drivers.
* **Embedded Diagnostics & Host Paths**:
  * ProDG / DECI2 host filesystem calls: `host:screen%02d.bmp` (screenshot capture) and `host:memory.log` (memory allocation tracking).
  * In-game camera & replay debug editor: `REPLAY.C`, `EDIT MODE: DEFAULT`, `CAMLOCK`, `FOV EDIT`, `GREEN SCREEN MODE: ON/OFF`, etc.
  * PAL display adaptations: `CPAL*` color palette lookup tables and `moviepal.dat`.
* **IOP Modules (`modules/`)**: 10 standard Sony IOP drivers extracted from `SYSTEM/`. All EA networking IOP daemons (`DRTYSCKF.IRX`, `FSVRD.IRX`, `VOIPF.IRX`) were removed from the disc mastering image.

---

## Exported Directory Structure

```text
references/NFL Street/SLES-52025/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── irx_symbols.tsv        # IRX module symbol log
│   └── online_symbols.tsv     # N/A (Online networking omitted in PAL build)
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, DECI2 host paths, assert messages
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT (10,600+ strings)
```

---

## Key Findings & Regional Comparison

### 1. Main Executable (`SLES_520.25.elf`)
- **Architecture**: 32-bit Little-Endian MIPS (R5900 Emotion Engine).
- **Entry Point**: `0x00100008`
- **Compiler Inferred**: SN Systems ProDG for PlayStation 2.
- **Embedded Diagnostic Tooling**:
  - **Host Filesystem Hooks**:
    - `host:memory.log` (internal heap/memory tracking dump)
    - `host:screen%02d.bmp` (framebuffer capture to host)
  - **Replay / Camera Debug Editor**:
    - Source file anchor: `REPLAY.C`
    - Modes: `REPLAY MODE: EDIT`, `REPLAY MODE: VIEW`, `EDIT MODE: DEFAULT`, `CAMLOCK`, `ADD/DEL`, `TRANS EDIT`, `FOV EDIT`, `PLAY SPEED`, `ROLL`, `ADJUST TARGET POSITIONAL OFFSET`, `ADVANCE FOCUS TARGET / GREENSCREEN`
    - Chroma key: `GREEN SCREEN MODE: OFF`, `ON / RED`, `ON / GREEN`, `ON / BLUE`
  - **PAL Display Customizations**:
    - Palette structures: `CPALCPLI`, `CPALCPRD`, `CPALCPGR`, `CPALCPBU`, `CPALCSRD`, `CPALCSGR`, `CPALCSBU`, `CPALCMRD`, `CPALCMGR`, `CPALCMBL`, `CPALCHRD`, `CPALCHGR`, `CPALCHBL`.
    - Dedicated PAL video stream container: `moviepal.dat` (1.01 GB).

### 2. Comparison with US Demo (`SLUS-29093`)
- **Code Size**: `.text` section is reduced by ~122 KB (`0x0025ee70` vs `0x0027cd40` in US Demo).
- **Dead Code Stripping**: Because the online multiplayer subsystem was excised, the binary is a cleaner baseline for single-player gameplay, AI, physics, and rendering logic.
- **Shared Topologies**: Function graphs for offline gameplay are nearly identical to `SLUS-29093`, confirming that the core game engine underwent minimal changes outside the removal of network dependencies.

### 3. Object Definitions & Schemas (`OBJDEFS.DAT`)
- Contains 882 KB of Tiburon Object Definition File (ODF) XML specifications (over 10,600 readable tokens).
- Retains internal XML comments: *`"Copyright (C) 2002-2003 Electronic Arts - Tiburon"`* with dynamic object definitions and physics bounding boxes.

---

## Relevance to Decompilation Projects
1. **Clean Gameplay Baseline**: For analyzing offline gameplay mechanics (player controls, AI, ball physics, collision geometry), this binary eliminates noise from online matchmaking and DirtySDK networking callbacks.
2. **Runtime Memory Profiling Clues**: The presence of `host:memory.log` in `.rodata` confirms that EA Tiburon used dedicated host-level logging hooks during ProDG development.
3. **Engine Consistency**: Confirms that UIStudio (`UIStudio.c`, `UISEvent.c`) and ODF object schemas were maintained identically across regional PS2 releases.
