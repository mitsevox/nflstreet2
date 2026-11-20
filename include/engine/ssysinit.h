#ifndef ENGINE_SSYSINIT_H
#define ENGINE_SSYSINIT_H

/* The sound system options (ssysinit.c): the first 0xCC bytes of the sound state 0x803A6C24,
   read and written whole by SNDSYS_getopts and SNDSYS_setopts. */

#include "engine/cu_802714A8.h"

/* The memory callbacks of the options (+0xB8): the allocator and the release function. */
typedef struct SndSysMemOpts_t {
    void *(*mpAlloc)(int size);
    void (*mpFree)(void *p);
    unsigned char unk_0x8[0xC];
} SndSysMemOpts_t;

typedef struct SNDSYSOPTS {
    unsigned char unk_0x0[0x1C];
    Params_803A6C40 mParams;
    SndSysMemOpts_t mMem;
} SNDSYSOPTS;

#ifdef __cplusplus
extern "C" {
#endif

int SNDSYS_getopts(SNDSYSOPTS *opts);
int SNDSYS_setopts(SNDSYSOPTS *opts);
int SNDSYSI_init(void *memory, int size, int unused);
int SNDSYS_restore(void);
int SNDSYSI_chanpubinit(void);

#ifdef __cplusplus
}
#endif

#endif
