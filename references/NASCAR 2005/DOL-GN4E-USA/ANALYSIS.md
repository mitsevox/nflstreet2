# Build Analysis: NASCAR 2005: Chase for the Cup (USA GameCube) (DOL-GN4E-USA)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NASCAR 2005: Chase for the Cup
- **Platform**: Nintendo GameCube
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `DOL-GN4E-USA`
- **Disc / Volume ID**: `GN4E69`
- **Revision / Build Number**: Development DVD Master (DWARF 1 Debug Build)
- **Developer / Publisher**: EA Tiburon / EA SPORTS
- **Release Year**: 2004
- **Toolchain**: SN Systems ProDG 3.9.3 (`ngcld`, GCC 2.95.3)

---

## Executive Summary
This build represents the **most significant reference build in the entire 6th-generation EA ecosystem** for reverse engineering *NFL Street 2* (`GN7E69`). 

* **Developer & Era Parity**: Developed by **EA Tiburon** in **2004** on **Nintendo GameCube** using the exact same ProDG toolchain.
* **Master Dev Executable (`NASCAR05.ELF`)**: 18.29 MB (18,293,344 bytes) 32-bit PowerPC Gekko executable.
* **Unstripped DWARF 1 Debug Sections**:
  * `.debug`: 13.86 MB (13,865,492 bytes) of raw DWARF 1 debug records.
  * `.line`: 547.9 KB (547,950 bytes) of source line mapping.
  * `.debug_sfnames`: 22.5 KB (22,580 bytes) containing 315 canonical source file paths (`Adapt.cpp`, `AdaptRenderUnit.h`, `AptSharedPtr.h`, `small_object_allocator.h`).
* **Complete Symbol Table (`symbols/symbols.tsv`)**:
  * **20,766 named symbols** providing full demangled C++ function prototypes, member variables, and virtual method tables.
* **172 Direct Instruction Fingerprint Matches with NFL Street 2 (`GN7E69`)**:
  * Identifies the complete `VptManager` camera stack (`_VptManagerCreateStack`, `VptManagerPushCamera`, `VptManagerPopCamera`), character motion streaming (`_AnimExtnRelocateMotion`, `ReadBitStream`), texture registries (`TMTexLibRegistryInit`), and the **Style Points gameplay system** (`StylePointsManager::SetAchievementCompleted`).

---

## Exported Directory Structure

```text
references/NASCAR 2005/DOL-GN4E-USA/
├── ANALYSIS.md                # Complete technical report
├── symbols/
│   ├── elf_sections.tsv       # 21 ELF section headers (.text, .debug, .line, etc.)
│   └── symbols.tsv            # 20,766 symbols (Address, Size, Type, Name)
└── strings/
    ├── debug_strings.txt      # Engine asserts, camera scripts, and diagnostics
    └── source_files.txt       # 315 source paths extracted from .debug_sfnames
```

---

## Relevance to NFL Street 2 Decompilation (`GN7E69`)
1. **Studio-Internal Architecture**: Gives direct visibility into EA Tiburon's proprietary C++ framework and memory allocators (`SmallObjectAllocator`, `Adapt`, `Apt`) shared between NASCAR and Street 2.
2. **Deterministic Fingerprint Matching**: Enabled 172 functions in `GN7E69` to be resolved without ambiguity.
