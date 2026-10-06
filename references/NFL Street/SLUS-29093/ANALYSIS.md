# Build Analysis: NFL Street (USA) Demo (SLUS-29093)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street (Interactive Demo)
- **Platform**: Sony PlayStation 2
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `SLUS-29093`
- **Disc / Volume ID**: `SLUS_290.93`
- **Revision / Build Number**: Interactive Demo Disc (Public Beta / Demo Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004
- **Internal Tooling**: `G:\BIG\Art\Common\Tools\scripts\ODFSchema.xml`

---

## Executive Summary
This build is a pre-release retail-adjacent demo for NFL Street 1 on PlayStation 2.

* **Main Executable (`SLUS_290.93.elf`)**: The primary Emotion Engine (EE) ELF is **stripped** of its symbol table (`.symtab`), string table (`.strtab`), and DWARF debug sections. While it does not provide function names for core gameplay logic, its `.rodata` preserves developer replay/camera debug modes, host file paths, and diagnostic assertions.
* **Online Overlay (`online.elf`)**: Located inside `DATA/ONLINE.DAT`, this relocatable overlay is **completely unstripped**, containing **2,447 named symbols** covering DirtySDK, SN Systems C runtime, and OpenSSL.
* **IOP Modules (`modules/`)**: 30 of 32 IOP modules retain symbol tables; the three EA modules (`DRTYSCKF.IRX`, `FSVRD.IRX`, `VOIPF.IRX`) contain full `.mdebug` MIPS symbolic debugging tables.

---

## Exported Directory Structure

```text
references/NFL Street/SLUS-29093/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── irx_symbols.tsv        # 677 symbols from DRTYSCKF, FSVRD, and VOIPF IRX modules
│   └── online_symbols.tsv     # 2,447 symbols from online.elf (Addr, Size, Type, Bind, Name)
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, DECI2 host paths, assert messages
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT
```

---

## Key Findings & Toolchain Profile

### 1. Main Executable (`SLUS_290.93.elf`)
- **Architecture**: 32-bit Little-Endian MIPS (R5900 Emotion Engine).
- **Entry Point**: `0x00100008`
- **Compiler Inferred**: SN Systems ProDG for PlayStation 2 (EDG C/C++ frontend).
- **Embedded Diagnostic Tooling**:
  - **Replay / Camera Debug Editor**:
    - Modes: `EDIT MODE: DEFAULT`, `CAMLOCK`, `ADD/DEL`, `TRANS EDIT`, `FOV EDIT`, `PLAY SPEED`, `ROLL`, `ADJUST TARGET POSITIONAL OFFSET`, `ADVANCE FOCUS TARGET / GREENSCREEN`
    - Chroma key testing: `GREEN SCREEN MODE: OFF`, `ON / RED`, `ON / GREEN`, `ON / BLUE`
  - **DevKit File Output**: `host:screen%02d.bmp` (ProDG / DECI2 host communication).
  - **UIStudio Assertions**: Error strings directly corroborating UIStudio library layout:
    - `"Attempting to load a rate function while it's screen is being unloaded."`
    - `"?Attempting to activate screen (Group ID: %d, Screen ID: %d) which is waiting to be unloaded."`
    - References to `UIStudio.c` and `UISEvent.c`.

### 2. Online Overlay (`online.elf`)
Extracted from `DATA/ONLINE.DAT` (offset `0x11800`), this unstripped relocatable module contains:
- **DirtySDK / DirtySock**: Complete function and object symbols (`_DirtyDnasYieldThread`, `_DirtyDnasEncodeUniqueID`, `_DirtyDnasRelInitDnas`, `_SocketOpen`, `_SocketClose`, `_TCPHttpWorkerThread`, `_Utf8DecodeToUCS2`, etc.).
- **SN Systems C Runtime**: Exact ProDG runtime symbols (`sn_floor`, `sn_fmod`, `sn_log10`, `sn_log`, `_malloc_r`, `_sbrk_r`, etc.).
- **Security / Crypto**: Complete OpenSSL / SSLeay symbols (`SSL_*`, `X509_*`, `EVP_*`, `BN_*`, `RSA_*`, `DSA_*`, `ASN1_*`).

### 3. IOP Driver Modules (`modules/`)
- `DRTYSCKF.IRX` (474 symbols, includes `.mdebug`): DirtySock IOP daemon.
- `FSVRD.IRX` (94 symbols, includes `.mdebug`): File Server Daemon.
- `VOIPF.IRX` (109 symbols, includes `.mdebug`): Voice over IP backend.

---

## Relevance to Decompilation Projects
1. **DirtySDK Boundaries & Signatures**: Provides exact function names, sizes, and layout for EA's networking and crypto stack, which can be cross-referenced with GameCube/PS2 builds.
2. **ProDG Runtime Fingerprinting**: Serves as a ground truth reference for SN Systems runtime library signatures and calling conventions.
3. **UIStudio Alignment**: Validates UIStudio control flow, error message strings, and unit boundaries used in Madden/Street series decompilations.
4. **Core Game Code**: Not present in symbol form. Function graphs can be diffed against NFL Street 2 in Ghidra/IDA, but function names must be reconstructed or correlated via external references.
