# Build Analysis: NFL Street 2 (Xbox Prototype)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2 (Xbox Development Prototype)
- **Platform**: Microsoft Xbox
- **Region**: North America (NTSC-U Development)
- **Serial / Product Code**: `EA-087`
- **Disc / Volume ID**: Title ID `0x45410057` (`EA-087`)
- **Revision / Build Number**: Pre-Release Development Prototype (Master Date: Aug 28, 2004 / Target: Oct 2004)
- **Primary Executable**: `NFLBig.xbe` (6.51 MB x86 Xbox Executable with uncompressed symbols)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This folder contains an internal Xbox development prototype for **NFL Street 2**.

* **Primary Binary (`NFLBig.xbe`)**: 6.51 MB executable containing complete pre-release game code and uncompressed diagnostic symbols.
* **Internal Server Source Paths**:
  * `\dev\cg\Proj\Ll_api\Source\Common\UIStudio\UIStudio.c`
  * `\dev\cg\Proj\Ll_api\Source\Common\UIStudio\UISEvent.c`
  * `f:\usr\local\packages\apt\nflstreet\source\apt\_AptVector.h`
* **Compilation Units Recovered**:
  * `AASSIGN.C` (Animation assignment)
  * `REPLAY.C` (Replay framework)
* **Shared Engine Lineage**: The presence of `Madden05/Madden05.xbe` inside the build tree directly substantiates the project's use of Madden 2003–2005 STABS for unit recovery in `units.json`.
* **ODF Schema Definitions**: `DATA/OBJDEFS.DAT` retains over 15,800 tokens of Tiburon Object Definition File (ODF) XML specifications tailored for Street 2's new wall-running and field mechanics.

---

## Exported Directory Structure

```text
references/NFL Street 2/prototype/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── source_anchors.tsv     # Source path string anchors in Xbox memory
│   └── xbe_sections.tsv       # Virtual and raw section layout
├── strings/
│   ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
│   └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
└── DATA/
    └── STARTUP.TXT
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Source Tree Structure**: Confirms that on EA's build machines, `UIStudio.c` lived under `\dev\cg\Proj\Ll_api\Source\Common\UIStudio\`, validating the `../../../Source` relative path prefix in `units.json`.
2. **ActionScript / Apt Integration**: Discloses the package root `f:\usr\local\packages\apt\nflstreet\source\apt\` for UI development.
3. **Engine Cross-Referencing**: `NFLBig.xbe` serves as an uncompressed x86 companion to the GameCube `main.dol` in `GN7E69`.
