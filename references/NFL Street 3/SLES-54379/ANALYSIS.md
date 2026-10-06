# Build Analysis: NFL Street 3 (Europe, Australia PS2) (SLES-54379)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 3
- **Platform**: Sony PlayStation 2
- **Region**: Europe & Australia (PAL)
- **Serial / Product Code**: `SLES-54379`
- **Disc / Volume ID**: `SLES_543.79`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2006

---

## Executive Summary
This build represents the retail European and Australian PAL release of **NFL Street 3** on PlayStation 2.

* **Main Executable (`SLES_543.79.elf`)**: 4.06 MB MIPS Emotion Engine executable. Stripped of `.symtab` and DWARF debug sections.
  * Size is ~560 KB smaller than the North American retail release (`SLUS_214.82`, 4.62 MB) because online multiplayer and networking libraries were stripped for PAL distribution.
* **EA Apt Flash Engine Active**:
  * Like the North American release, contains active Flash/ActionScript diagnostic messages:
    * `<WARNING> Actionscript un-caught exception encountered during "%s"`
    * `--AptWarning-- Actionscript is attempting to use invalid objects in Extends Opcode.`
* **C++ Assertions & Replay Anchors**:
  * `Alerts::STATUS_PANIC_ASSERTION`
  * `ScoutReport::STATUS_PANIC_ASSERTION`
  * `REPLAY.C`, `SndgReplay`, `CamScript`, `ReplayFrame`
* **IOP Modules (`modules/`)**: 8 standard Sony IOP drivers (`LIBSD.IRX`, `MCMAN.IRX`, `PADMAN.IRX`, etc.).
* **Object Schemas**: 1.44 MB of Tiburon Object Definition File (ODF) XML specifications (`DATA/OBJDEFS.DAT`), comprising 15,709 readable tokens.

---

## Exported Directory Structure

```text
references/NFL Street 3/SLES-54379/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   └── irx_symbols.tsv        # IRX module symbol log
└── strings/
    ├── debug_strings.txt      # EA Apt warnings, replay/camera modes, asserts
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Regional Comparison to US Release (`SLUS-21482`)
1. **Network Layer Excision**: By dropping online matchmaking, the binary isolates offline Street 3 gameplay logic from DirtySDK and DNAS2 protocols.
2. **Identical Engine Features**: Confirms that EA Apt bytecode handling, camera scripts, and collision geometry definitions are identical across North American and European distributions.
