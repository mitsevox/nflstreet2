# Build Analysis: NFL Street (Xbox) (EA-072)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street
- **Platform**: Microsoft Xbox
- **Region**: North America (NTSC-U) & Europe (PAL)
- **Serial / Product Code**: `EA-072`
- **Disc / Volume ID**: Title ID `0x45410048` (`EA-072`)
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build contains the Microsoft Xbox retail release of NFL Street 1 (both North American and European editions). Because the original Xbox uses an x86 architecture running an embedded Windows/NT kernel derivative, the binary format is an Xbox Executable (**XBE**, based on PE32).

* **Main Executable (`default.xbe`)**: 2.68 MB x86 PE executable.
  * Base Address: `0x00010000`
  * Main `.text` Virtual Size: `0x001DBCFC` (1.95 MB)
  * Read-only Data (`.rdata`): `0x0022DAE0` (78.9 KB)
  * Sections: Direct Microsoft Xbox static link libraries (`D3D`, `DSOUND`, `WMADEC`, `DOLBY`, `XPP`, `XGRPH`).
* **Source Filename Anchors Recovered**:
  The Xbox binary preserves specific C source files embedded in assertion and error handling routines:
  * `AASSIGN.C`: Animation assignment system
  * `BALL.C`: Ball physics and trajectory logic
  * `CUSTOMAI.C`: AI opponent logic and behavior trees
  * `REPLAY.C`: Replay camera and recording framework
  * `\Proj\Ll_api\Source\Common\UIStudio\UIStudio.c`: Absolute Windows build path for UIStudio core
  * `\Proj\Ll_api\Source\Common\UIStudio\UISEvent.c`: Absolute Windows build path for UIStudio event handler
* **Replay & Camera Tooling**:
  * Preserves identical in-game camera/replay debug edit modes (`REPLAY MODE: EDIT`, `REPLAY MODE: VIEW`, `EDIT MODE: CAMLOCK`).

---

## Exported Directory Structure

```text
references/NFL Street/EA-072/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── source_anchors.tsv     # C source filenames preserved in binary
│   └── xbe_sections.tsv       # Virtual and raw section layout
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Key Revelations from the Xbox Build

### 1. Engine Source Unit Names
While the GameCube and PS2 binaries stripped most game source paths, the Xbox build retains critical compilation unit filenames:
* **`BALL.C`**: Directly identifies the module responsible for football physics, aerodynamics, and bounce logic.
* **`CUSTOMAI.C`**: Directly identifies the AI state machine module.
* **`AASSIGN.C`**: Identifies animation state assignment logic.
* **`REPLAY.C`**: Confirms the replay recording system across all console ports.

### 2. Internal Build Tree Path
The strings `\Proj\Ll_api\Source\Common\UIStudio\UIStudio.c` and `\Proj\Ll_api\Source\Common\UIStudio\UISEvent.c` reveal EA Tiburon's exact internal directory layout on their Windows development servers:
* Root Project: `Proj`
* Middleware / Engine layer: `Ll_api` (*Low Level API*)
* Core UI library: `Source\Common\UIStudio`

---

## Relevance to Decompilation Projects
1. **Module Name Attribution**: `BALL.C`, `CUSTOMAI.C`, and `AASSIGN.C` provide high-confidence filenames to assign to reconstructed compilation units in `nflstreet2`.
2. **UIStudio Structure Validation**: Confirms that UIStudio was part of EA's shared `Ll_api` engine across GameCube, PS2, and Xbox.
3. **Cross-Architecture Disassembly**: Functions matching `BALL.C` or `CUSTOMAI.C` in the x86 disassembly can be cross-referenced with PPC Gekko assembly in GameCube `GN7E69` to resolve ambiguous algorithm logic.
