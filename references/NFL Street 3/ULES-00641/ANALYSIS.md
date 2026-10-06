# Build Analysis: NFL Street 3 (Europe PSP) (ULES-00641)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 3
- **Platform**: Sony PlayStation Portable (PSP)
- **Region**: Europe (PAL)
- **Serial / Product Code**: `ULES-00641`
- **Disc / Volume ID**: `ULES_00641`
- **Revision / Build Number**: Revision 1.00 (Retail Master, PSP Firmware 2.81)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2006
- **PSP System Firmware Requirement**: 2.81 (`PARAM.SFO`)

---

## Executive Summary
This build represents the retail European PAL PlayStation Portable (PSP) release of **NFL Street 3**.

* **Unencrypted Dev Executable (`BOOT.BIN`)**: 4.91 MB (4,911,020 bytes) MIPS R4000 (Allegrex) 32-bit ELF executable.
  * Like the North American counterpart, the UMD includes the master unencrypted devkit ELF alongside the signed `EBOOT.BIN` (4,911,360 bytes).
  * Contains 59 ELF sections across identical section indices.
* **Exact 64-Byte Data Delta vs. North American Retail (`ULUS-10135`)**:
  * Binary diffing reveals that `BOOT.BIN` differs by only **64 bytes** in total size:
    * North America `.data` size: 281,244 bytes (`0x44a9c`)
    * European `.data` size: 281,180 bytes (`0x44a5c`) (delta: `-64` bytes / `-0x40`)
    * All subsequent section offsets (`.eh_frame`, `.rodata`, `.ctors`, `.dtors`, `.bss`, `.shstrtab`) shift by exactly 64 bytes.
    * Text section (`.text`, 3,227,996 bytes) and all 25 Sony OS stub interfaces (`.sceStub.text.*`) match byte-for-byte in structure.
* **EA Apt Flash Engine Integration**:
  * Uses the same Flash/ActionScript runtime architecture as the North American build:
    * `_global.Glue`, `screens\glue\glue`, `InitScreen`, `ShutScreen`, `SetReturnScreen`, `LoadScreenStrings`
    * Flash UI layouts: `FEFlash`, `_level1.StyleBanner`, `ingame\bighud\bighud`, `ingame\minigamehud\minigamehud`, `ingame\postminigame_topsix\postminigame_topsix`
* **Style Scoring, Trick Prediction & Camera Systems**:
  * Style Point Rules: *"In a Style Point Game, the goal is to rack up as many Style Points as possible..."*, *"Game Modifier: Additional %d style points..."*.
  * Trick mechanics: `StreetPSP_TRICKTEXT`, `StreetPSP_SCORE`, *"Correctly Predicted Trick"*, *"Incorrectly Predicted Trick"*.
  * Cameras: `CamGame`, `CamScript`, `MarketCam-Pass Icons On/Off`.
* **Skeletal Hierarchy & EAGL Graphics Assets (`symbols/eagl_symbols.tsv`)**:
  * Discovered unstripped embedded ELF containers in `EAGL_ANIM.dat`, `OBJMODEL.dat`, and `STATMOD.dat` yielding **44 named C++ symbols**:
    * 29 skeleton bone identifiers (`__Skeleton:::main`, `main.up_torso`, `mid_torso`, `lshoulder`, `rshoulder`, `lelbow`, `relbow`, `lwrist`, `rwrist`, `lhip`, `rhip`, `lknee`, `rknee`, `lankle`, `rankle`, `lball`, `rball`, etc.).
    * EAGL engine symbols: `__EAGL_TOOLLIB_VERSION:::EAGL_TOOLLIB_VERSION-4`, `__MATRIX4:::EAGL::ViewPort::gpModelMatrix`, `__EAGL::Colour:::gColor`.
* **System Modules (`modules/`)**:
  * 18 PRX drivers extracted from `/PSP_GAME/USRDIR/modules/` (cryptographic, compression, font, FPU, and video streaming).
* **Object Schemas (`strings/objdefs_schema.txt`)**:
  * 9,918 lines of Tiburon Object Definition File (ODF) XML specifications from `OBJDEFS.dat`.

---

## Exported Directory Structure

```text
references/NFL Street 3/ULES-00641/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   ├── eagl_symbols.tsv       # 44 EAGL graphics & skeletal bone symbols from asset ELFs
│   ├── elf_sections.tsv       # 59 ELF section definitions (stubs, relocations, text, bss)
│   └── prx_modules.tsv        # 18 PRX module descriptors (sizes, MD5)
└── strings/
    ├── debug_strings.txt      # EA Apt Flash glue, camera scripts, asserts, style rules
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT (9,918 strings)
```

---

## Regional Comparison: Europe (`ULES-00641`) vs. USA (`ULUS-10135`)
1. **Near-Zero Code Divergence**: The minimal 64-byte difference in `.data` indicates that the European PSP release is practically identical to the North American master, differing only in minor localization strings or regional configuration flags.
2. **Identical Engine Features**: Confirms that gameplay logic, Flash ActionScript integration, physics skeletons, and PRX system dependencies are 100% synchronized across regions.
