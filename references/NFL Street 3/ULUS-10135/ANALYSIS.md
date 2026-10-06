# Build Analysis: NFL Street 3 (USA PSP) (ULUS-10135)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 3
- **Platform**: Sony PlayStation Portable (PSP)
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `ULUS-10135`
- **Disc / Volume ID**: `ULUS_10135`
- **Revision / Build Number**: Revision 1.00 (Retail Master, PSP Firmware 2.81)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2006
- **PSP System Firmware Requirement**: 2.81 (`PARAM.SFO`)

---

## Executive Summary
This build represents the retail North American PlayStation Portable (PSP) release of **NFL Street 3**, the final entry in the *NFL Street* series.

* **Unencrypted Dev Executable (`BOOT.BIN`)**: 4.91 MB (4,911,084 bytes) MIPS R4000 (Allegrex) 32-bit ELF executable.
  * While retail UMDs execute `EBOOT.BIN`, the disc includes the unencrypted `BOOT.BIN` ELF used during devkit mastering.
  * Contains 59 ELF sections, including relocation tables (`.rel.text`, `.rel.data`), Sony OS stub interfaces (`.sceStub.text.*`), exception frames (`.eh_frame`), and module entries.
* **Transition to EA Apt (Flash/ActionScript)**:
  * In contrast to *NFL Street 2: Unleashed* (which relied on `UIStudio`), *NFL Street 3* on PSP mirrors the PS2 release by adopting **EA Apt** / Flash UI:
    * ActionScript bridge: `_global.Glue`
    * C++ glue layer: `screens\glue\glue`, `InitScreen`, `ShutScreen`, `SetReturnScreen`, `LoadScreenStrings`
    * Flash UI movie clip layers: `FEFlash`, `_level1.StyleBanner`, `ingame\bighud\bighud`, `ingame\minigamehud\minigamehud`, `ingame\postminigame_topsix\postminigame_topsix`
* **Street 3 Gameplay & Scoring Systems**:
  * Style Point Rules & Modifiers: *"In a Style Point Game, the goal is to rack up as many Style Points as possible..."*, *"Game Modifier: Additional %d style points when scoring on this possession"*.
  * Trick mechanics & prediction: `StreetPSP_TRICKTEXT`, `StreetPSP_SCORE`, *"Correctly Predicted Trick"*, *"Incorrectly Predicted Trick"*, *"Style Move"*, *"Hat Trick"*, *"Style Grab"*.
* **Camera Subsystem**:
  * `CamGame`, `CamScript`, `MarketCam-Pass Icons On`, `MarketCam-Pass Icons Off`.
* **Skeletal Hierarchy & EAGL Graphics Assets (`symbols/eagl_symbols.tsv`)**:
  * Analysis of compiled asset packs (`EAGL_ANIM.dat`, `OBJMODEL.dat`, `STATMOD.dat`) discovered unstripped embedded ELF containers exposing **44 named C++ symbols**:
    * 29 skeleton bone names: `__Skeleton:::main`, `__Bone:::main.up_torso`, `mid_torso`, `low_torso`, `headend`, `neckhi`, `necklo`, `lshoulder`, `rshoulder`, `lclavicle`, `rclavicle`, `lelbow`, `relbow`, `lforearm`, `rforearm`, `lwrist`, `rwrist`, `lhip`, `rhip`, `lknee`, `rknee`, `lankle`, `rankle`, `lball`, `rball`, `LFOOTBALL`, `RFOOTBALL`.
    * EAGL engine symbols: `__EAGL_TOOLLIB_VERSION:::EAGL_TOOLLIB_VERSION-4`, `__MATRIX4:::EAGL::ViewPort::gpModelMatrix`, `__EAGL::Colour:::gColor`, and primitive pipeline states.
* **System Modules (`modules/`)**:
  * 18 PRX drivers extracted from `/PSP_GAME/USRDIR/modules/`, providing crypto (`libsha1`, `libsha224`, `libsha256`, `libsha512`, `libmd5`, `libbase64`), compression (`libdeflt`, `libadler`), font rendering (`libfont`), floating-point support (`libfpu`), and video playback (`libpsmfplayer`, `psmf`).
* **Object Schemas (`strings/objdefs_schema.txt`)**:
  * 9,918 lines of Tiburon Object Definition File (ODF) XML specifications extracted from `OBJDEFS.dat`, detailing collision bounds, physics mass, skeletons, and dynamic entities.

---

## Exported Directory Structure

```text
references/NFL Street 3/ULUS-10135/
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

## Relevance to Decompilation & Reverse Engineering
1. **Unencrypted 32-bit RISC Target**: Provides an unencrypted MIPS disassembly that pairs with PS2 Emotion Engine and GameCube Gekko PowerPC builds for cross-architecture function matching.
2. **Standardized Skeleton Hierarchy**: The recovered bone labels in `symbols/eagl_symbols.tsv` provide canonical bone indexing for animation matrices across the entire Street series.
3. **Engine Modernization**: Proves that the migration from UIStudio to Flash (EA Apt) occurred concurrently across both console (PS2) and handheld (PSP) branches for the 2006 season.
