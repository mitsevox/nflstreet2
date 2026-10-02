# Credits

The Nintendo SDK reconstruction is reused from [MVP 2005](https://github.com/mitsevox/mvp2005), revision `1a61d5adf81a14bef749c0b2b7e803aabc2f98b3`. Its upstream sources are [emoose/re4](https://github.com/emoose/re4), revision `feb6805b`, based on [doldecomp/dolsdk2004](https://github.com/doldecomp/dolsdk2004), revision `2328b416`.

| Imported source | Upstream source |
| --- | --- |
| `src/dolphin/si/SISamplingRate.c` | re4 `src/lib/SISamplingRate.c` |
| `src/dolphin/card/{CARDBlock,CARDCheck,CARDCreate,CARDDelete,CARDDir,CARDFormat,CARDRdwr,CARDRead,CARDStat,CARDWrite}.c` | Corresponding re4 `src/lib/` CARD units |
| `src/dolphin/dvd/{dvdqueue,dvderror}.c`, `src/dolphin/__dvd.h` | Corresponding re4 `src/lib/` DVD sources and internal declarations |
| `src/dolphin/mtx/mtxvec.c`, `include/dolphin/mtx.h` | re4 `src/lib/mtxvec.c`; used matrix/vector declarations; original paired-single SDK assembly corroborated by dolsdk2004 `src/mtx/mtxvec.c` |
| `src/dolphin/ar/arq.c`, `src/dolphin/__ar.h` | re4 `src/lib/arq.c` and `src/lib/__ar.h`; target release version string restored |
| `src/dolphin/pad/Padclamp.c` | re4 `src/lib/Padclamp.c` |
| `include/libc/math.h` | MVP/re4 CodeWarrior `sqrtf` inline subset used by the reference clamp file; unrelated APIs and the reference’s fake float `sqrt` alias omitted |
| `src/dolphin/__card.h` | re4 `src/lib/__card.h` |
| `src/dolphin/ax/AX.c` | re4 `src/lib/AX.c`; release version string restored to target April 2003 build |
| `include/dolphin/ax.h`, `src/dolphin/__ax.h` | Used declarations from re4 AX public and internal headers |
| `src/dolphin/ax/AXAlloc.c`, `include/dolphin/ax/AXVPB.h` | [bfbbdecomp/bfbb](https://github.com/bfbbdecomp/bfbb/tree/8fb1c232addcacf44932c10c4cede41b43f98f40/src/dolphin); source and shared parameter-block structures; redundant pointer conversions omitted |
| `src/dolphin/dsp/dsp_task.c`, `src/dolphin/__dsp.h` | Same pinned BFBB revision; four retained task helpers and diagnostic data; interrupt handler and global storage remain unreconstructed |
| `src/dolphin/os/OSSemaphore.c` | [doldecomp/dolsdk2004](https://github.com/doldecomp/dolsdk2004/blob/2328b4164b1a98422a2255d83ce9a5a7548990cc/src/os/OSSemaphore.c); existing shared semaphore/thread-queue declarations; umbrella include narrowed and redundant wait-loop self-assignment omitted |
| `src/dolphin/os/OSSync.c` | re4 `src/lib/OSSync.c` |
| `include/dolphin/`, `include/libc/`, `include/cmath.h` | MVP's SDK header dependency closure, credited to re4/dolsdk2004 |
| `src/dolphin/__os.h` | The used declaration from re4 `src/lib/__os.h` |

Only headers needed by these units are included. Unused umbrella includes were narrowed, and provenance/process comments were moved here. Copyright and license notices in imported files remain intact. The sampling-rate table's second NTSC entry is restored to Street's target values `(15, 18)`; MVP's later SDK uses `(14, 19)`. The system-call exception stub and paired-single matrix-vector routines retain the assembly forms present in the upstream SDK reconstruction. The matrix unit does not use the reference’s `fake_tgmath.h` include, which is omitted.

These are public reverse-engineered SDK reconstructions. Their Nintendo symbol names are reference-derived; they are not recovered target debug symbols. The target SDK's April 2003 build strings differ from MVP's April/May 2004 strings. The ARQ release string is restored to April 17 2003 12:33:56; its debug configuration remains reference-only. The clamp circle routines are retained in source and discarded by SN linking; their native constant pool remains loaded, as in the target. No circle or square-root routine contributes matched code.

Validation covers the imported release code and used declarations, not every declaration or debug configuration in the reference headers. See `config/GN7E69/evidence.tsv` for target addresses, ownership and compiler evidence.

`CARDRdwr.c` restores the target’s fixed 128-byte write pages instead of the later reference’s variable page-size behavior. The earlier source form is corroborated by [doldecomp/dolsdk2001](https://github.com/doldecomp/dolsdk2001/blob/eb1234c45e6df75757c652c835507ca89674f9a8/src/card/CARDRdwr.c), revision `eb1234c45e6df75757c652c835507ca89674f9a8`. Compiler objects remain unchanged; SN linker retention removes unused functions as part of linking.

AXAlloc validation establishes the accessed fields and complete native allocated sections. Other AXVPB/AXPB fields remain reference declarations. DSP task timing fields and volatile qualifiers are reference-derived; retained code establishes the accessed offsets, not every declaration. The unused handler local is omitted; the handler and original DSP global storage receive no source progress. Related SDK file attribution remains provisional.
