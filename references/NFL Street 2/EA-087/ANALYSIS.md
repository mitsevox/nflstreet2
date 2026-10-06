# Build Analysis: NFL Street 2 (Xbox) (EA-087)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 2
- **Platform**: Microsoft Xbox
- **Region**: North America (NTSC-U) & Europe (PAL)
- **Serial / Product Code**: `EA-087`
- **Disc / Volume ID**: Title ID `0x45410057` (`EA-087`)
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This directory contains the retail Microsoft Xbox releases of **NFL Street 2** for North America and Europe.

* **Primary Executable (`default_usa.xbe`)**: 4.17 MB x86 PE executable.
* **European Executable (`default_europe.xbe`)**: 2.98 MB x86 PE executable (~1.19 MB smaller due to the omission of the Xbox Live online multiplayer subsystem in Europe).
* **Source Filename Anchors Recovered**:
  * `\Proj\Ll_api\Source\Common\UIStudio\UIStudio.c`: Absolute build path for UIStudio core
  * `\Proj\Ll_api\Source\Common\UIStudio\UISEvent.c`: Absolute build path for UIStudio event logic
  * `f:\usr\local\packages\apt\nflstreet\source\apt\_AptVector.h`: Flash/Apt UI container header
  * `AASSIGN.C`: Animation assignment system
  * `REPLAY.C`: Replay camera and recording framework
* **Replay & Camera Tooling**:
  * Retains internal developer replay and camera editors (`REPLAY MODE: EDIT`, `REPLAY MODE: VIEW`, `EDIT MODE: CAMLOCK`).
* **Object Schemas**: 1.39 MB of Tiburon Object Definition File (ODF) XML specifications (`DATA/OBJDEFS.DAT`), comprising 15,895 readable tokens.

---

## Exported Directory Structure

```text
references/NFL Street 2/EA-087/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── source_anchors.tsv     # Source path string anchors in Xbox memory
│   └── xbe_sections.tsv       # Virtual and raw section layout
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, diagnostic asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Relevance to Decompilation Target (`GN7E69`)
1. **Source File Mapping**: Corroborates the source compilation unit names (`UIStudio.c`, `UISEvent.c`, `AASSIGN.C`, `REPLAY.C`) against our project's unit map.
2. **Online Delta Verification**: The 1.19 MB code size difference between USA and European Xbox binaries isolates the boundary between offline gameplay logic and EA's network multiplayer stack.
