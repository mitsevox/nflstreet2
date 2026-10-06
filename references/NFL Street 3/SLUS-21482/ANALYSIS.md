# Build Analysis: NFL Street 3 (USA) (SLUS-21482)

> [!NOTE]
> **Legal Compliance & Clean-Room Preservation**:
> All proprietary executables, disc images, and copyrighted archive containers have been permanently stripped from this reference directory. Only clean-room reverse-engineered metadata, symbol tables, section memory layouts, and diagnostic strings are preserved.

## Build & Disc Metadata
- **Game Title**: NFL Street 3
- **Platform**: Sony PlayStation 2
- **Region**: North America (NTSC-U)
- **Serial / Product Code**: `SLUS-21482`
- **Disc / Volume ID**: `SLUS_214.82`
- **Revision / Build Number**: Revision 1.00 (Retail Master)
- **Developer / Publisher**: EA Tiburon / EA SPORTS BIG
- **Release Year**: 2006

---

## Executive Summary
NFL Street 3 is the final installment of the NFL Street series on PlayStation 2. Comparing its binary and data layouts to earlier builds shows significant architectural evolution in EA Tiburon's engine between 2003 and 2006.

* **Main Executable (`SLUS_214.82.elf`)**: 4.62 MB MIPS Emotion Engine executable. The binary is stripped of its `.symtab` and DWARF debug sections, but retains detailed error diagnostics, C++ panic assertions (`Alerts::STATUS_PANIC_ASSERTION`), source filenames (`REPLAY.C`), and extensive logging from the newly introduced **EA Apt (Flash/ActionScript)** UI runtime.
* **Network GUI Subsystem (`ntgui.elf`)**: A dedicated 4.19 MB standalone ELF executable used for managing the online network GUI and configuration.
* **Online Overlay (`online.elf`)**: Embedded inside `DATA/ONLINE.DAT` (offset `0x11800`), this module is **completely unstripped**, containing **3,733 named symbols** (over 1,200 more symbols than NFL Street 1). It provides a full map of EA's DirtySDK, DNAS2 glue, and OpenSSL crypto suite.
* **IOP Modules (`modules/`)**: 26 IRX modules extracted from `SYSTEM/`. Unlike earlier builds, the IRX modules in this 2006 master image have had their symbol tables stripped.

---

## Exported Directory Structure

```text
references/NFL Street 3/SLUS-21482/
├── ANALYSIS.md                # This analysis document
├── symbols/
│   ├── irx_symbols.tsv        # IRX module symbol log
│   └── online_symbols.tsv     # 3,733 symbols from online.elf (Addr, Size, Type, Bind, Name)
└── strings/
    ├── debug_strings.txt      # EA Apt ActionScript warnings, asserts, replay, camera strings
    └── objdefs_schema.txt     # Expanded Tiburon ODF schemas from OBJDEFS.DAT (15,700+ strings)
```

---

## Key Findings & Toolchain Evolution

### 1. Main Executable (`SLUS_214.82.elf`)
- **Size & Code Expansion**: 4.62 MB (vs. ~3.18 MB in Street 1), with multiple segmented `.rodata` and `.text` sections.
- **UI Engine Transition (UIStudio → EA Apt)**:
  - Street 1 and Street 2 relied entirely on `UIStudio` (compiled C code and `.DAT` packs).
  - Street 3 integrates the **EA Apt** Flash/ActionScript VM runtime. The binary contains active bytecode engine warnings:
    - `<WARNING> Actionscript un-caught exception encountered during "%s"`
    - `--AptWarning-- Actionscript is attempting to use invalid objects in Extends Opcode.`
    - `Error! Defining Function from Unloaded CIH Context!!!`
- **C++ Diagnostic Classes**:
  - `Alerts::STATUS_PANIC_ASSERTION`
  - `ScoutReport::STATUS_PANIC_ASSERTION`
- **Replay / Camera Subsystems**:
  - Source file anchor: `REPLAY.C`
  - Subsystems: `SndgReplay`, `CamScript`, `ReplayFrame`, `Replay Particles`

### 2. Online Overlay (`online.elf`)
Extracted from `DATA/ONLINE.DAT` (offset `0x11800`), containing **3,733 symbols**:
- **Expanded DirtySDK / Net Glue (646 `NET_*` symbols, 34 `GLUE_*` symbols)**:
  - `NET_PROXY_Body`, `NET_TIMEOUT_Body`, `NET_SSL_Body`, `NET_DNS_HOST_NOT_FOUND_Body`, `NET_ECONNREFUSED_Body`, `NET_ECONNRESET_Body`, `GLUE_ABORT_Body`, etc.
- **Sony DNAS2 Protocol Layer (544 `sceDNAS2_*` symbols)**:
  - Complete request/response protocol descriptors, session timeouts, and state machines.
- **Cryptographic Engine**:
  - Full OpenSSL / SSLeay suite (`SSL_*`, `X509_*`, `EVP_*`, `BN_*`, `RSA_*`, `DSA_*`).

### 3. Object Definitions & Schemas (`OBJDEFS.DAT`)
- Contains 1.44 MB of Tiburon Object Definition File (ODF) XML specifications (over 15,700 readable tokens).
- Defines game dynamic objects, physics properties (`mass`, `moi`, `iVel`, `iAngVel`, `dThres`), and collision boxes across expanded Street 3 fields.

---

## Relevance to Decompilation Projects
1. **DirtySDK Evolution**: Provides a modern, expanded symbol map for EA's networking stack that bridges the gap between early 2004 Street builds and late-generation PS2/GameCube network code.
2. **Architecture Comparison**: Demonstrates where the codebase transitioned from UIStudio to Apt, confirming that UIStudio decompile work in Street 2 remains clean and distinct from the Flash-based tooling introduced in Street 3.
3. **Core Gameplay & Replay**: `REPLAY.C` and camera script names provide clear module boundaries for binary diffing against earlier Street engine releases.
