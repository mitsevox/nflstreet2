# Build Analysis: NFL Street (USA Retail) (SLUS-20841)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street
- **Platform**: Sony PlayStation 2
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `SLUS-20841`
- **Disc / Volume ID**: `SLUS_208.41`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2004

---

## Executive Summary
This build represents the final retail North American PlayStation 2 release of NFL Street 1.

* **Main Executable (`SLUS_208.41.elf`)**: 3.26 MB MIPS Emotion Engine executable. Stripped of `.symtab` and DWARF debug sections. Compared to the pre-release demo (`SLUS_290.93`, 3.18 MB), the retail binary includes full final game modes, UI flows, and retail master linking.
* **Network GUI Subsystem (`ntgui.elf`)**: A dedicated 4.19 MB standalone ELF executable located at `/NETGUI/NTGUI.ELF` for managing online configuration and Sony Network GUI setups.
* **Online Overlay (`online.elf`)**: Embedded inside `DATA/ONLINE.DAT` (offset `0x11800`), this module is **completely unstripped**, containing **2,447 named symbols** identical in layout to the demo build (DirtySDK, SN Systems C runtime, and OpenSSL).
* **IOP Modules (`modules/`)**: 32 IRX modules extracted from `SYSTEM/`. The three EA modules (`DRTYSCKF.IRX`, `FSVRD.IRX`, `VOIPF.IRX`) retain full **`.mdebug`** MIPS symbolic debugging tables with 677 symbols.

---

## Exported Directory Structure

```text
references/NFL Street/SLUS-20841/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── irx_symbols.tsv        # 677 symbols from DRTYSCKF, FSVRD, and VOIPF IRX modules
│   └── online_symbols.tsv     # 2,447 symbols from online.elf (Addr, Size, Type, Bind, Name)
└── strings/
    ├── debug_strings.txt      # Replay/camera/edit modes, DECI2 host paths, assert messages
    └── objdefs_schema.txt     # Tiburon ODF XML schemas & parameters from OBJDEFS.DAT (10,600+ strings)
```

---

## Key Findings & Subsystem Analysis

### 1. Main Executable (`SLUS_208.41.elf`)
- **Architecture**: 32-bit Little-Endian MIPS (R5900 Emotion Engine).
- **Entry Point**: `0x00100008`
- **Compiler Inferred**: SN Systems ProDG for PlayStation 2.
- **Embedded Diagnostic Tooling**:
  - **DevKit File Output**: `host:screen%02d.bmp` (framebuffer capture to host).
  - **Replay / Camera Debug Editor**:
    - Source file anchor: `REPLAY.C`
    - Modes: `REPLAY MODE: EDIT`, `REPLAY MODE: VIEW`, `EDIT MODE: DEFAULT`, `CAMLOCK`, `ADD/DEL`, `TRANS EDIT`, `FOV EDIT`, `PLAY SPEED`, `ROLL`, `ADJUST TARGET POSITIONAL OFFSET`, `ADVANCE FOCUS TARGET / GREENSCREEN`
    - Chroma key: `GREEN SCREEN MODE: OFF`, `ON / RED`, `ON / GREEN`, `ON / BLUE`
  - **UIStudio Assertions**: Error strings directly corroborating UIStudio library layout:
    - `"Attempting to load a rate function while it's screen is being unloaded."`
    - `"?Attempting to activate screen (Group ID: %d, Screen ID: %d) which is waiting to be unloaded."`
    - References to `UIStudio.c` and `UISEvent.c`.

### 2. Online Overlay (`online.elf`)
Extracted from `DATA/ONLINE.DAT` (offset `0x11800`), containing **2,447 symbols**:
- **DirtySDK / DirtySock**: Complete function and object symbols (`_DirtyDnasYieldThread`, `_DirtyDnasEncodeUniqueID`, `_DirtyDnasRelInitDnas`, `_SocketOpen`, `_SocketClose`, `_TCPHttpWorkerThread`, `_Utf8DecodeToUCS2`, etc.).
- **SN Systems C Runtime**: Exact ProDG runtime symbols (`sn_floor`, `sn_fmod`, `sn_log10`, `sn_log`, `_malloc_r`, `_sbrk_r`, etc.).
- **Security / Crypto**: Complete OpenSSL / SSLeay symbols (`SSL_*`, `X509_*`, `EVP_*`, `BN_*`, `RSA_*`, `DSA_*`, `ASN1_*`).

### 3. IOP Driver Modules (`modules/`)
- `DRTYSCKF.IRX` (474 symbols, includes `.mdebug`): DirtySock IOP daemon.
- `FSVRD.IRX` (94 symbols, includes `.mdebug`): File Server Daemon.
- `VOIPF.IRX` (109 symbols, includes `.mdebug`): Voice over IP backend.

---

## Relevance to Decompilation Projects
1. **Direct Pre- vs. Post-Release Comparison**: Validates that the symbols in `online.elf` and the `.mdebug` tables in `DRTYSCKF.IRX`/`FSVRD.IRX`/`VOIPF.IRX` remained stable between demo and retail master.
2. **Retail Code Alignment**: Confirms UIStudio and ODF object schemas were identical between North American retail and European PAL releases.
