/* Connects T3DB to the game: gives the database its own memory heap and allocation functions, and
   loads databases such as rosters, stats and saves from resource files. */

#include "engine/tdbext.h"
#include "engine/TDbLoad.h"
#include "engine/tdbiores.h"
#include "engine/t3db_table.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/MemPoolDesc.h"

typedef struct TDbExtResRef_t {
    void *mpStream;
    int mMode;
} TDbExtResRef_t;

extern unsigned char fn_801D2700(int handle);
extern int fn_801D2130(MemPoolDesc_t *pParams);
extern int fn_801D2570(int handle);
extern void *fn_801D310C(void *p, int size, int flags, int d);
extern int ResIsOpen(void *pPath);

/* A heap that replaces the one each allocation names, when set. */
static void *_TDbExt_pOverrideHeap = 0;

/* Set by TDbExtInit and cleared by TDbExtShutdown. */
static unsigned char _TDbExt_bInitialized = 0;

/* Whether the database heap was already active at TDbExtInit (then it is not created or destroyed here). */
static unsigned char _TDbExt_bHeapActive = 0;

/* The allocation flags of the database's memory. */
static int _TDbExt_uMemFlags = 0;

/* The database heap's description, copied at TDbExtInit. */
static MemPoolDesc_t _TDbExt_HeapDesc;

void TDbExtInit(MemPoolDesc_t *pParams)
{
    _TDbExt_HeapDesc = *pParams;
    _TDbExt_bHeapActive = fn_801D2700(pParams->mUnknown8);
    if (_TDbExt_bHeapActive == 0) {
        fn_801D2130(&_TDbExt_HeapDesc);
    }
    _TDbExt_bInitialized = 1;
    _TDbExt_pOverrideHeap = 0;
}

void TDbExtShutdown(void)
{
    if (_TDbExt_bHeapActive == 0) {
        fn_801D2570(_TDbExt_HeapDesc.mUnknown8);
    }
    _TDbExt_bInitialized = 0;
}

int TDbExtMemInit(int a, int b, int *pHandle)
{
    *pHandle = _TDbExt_HeapDesc.mUnknown8;
    return 0;
}

int TDbExtMemShutdown(void)
{
    return 0;
}

int TDbExtMemAlloc(void *pHeap, int size, void *ppMem)
{
    void *pMem;

    if (_TDbExt_pOverrideHeap != 0) {
        pHeap = _TDbExt_pOverrideHeap;
    }
    pMem = fn_801D2BB0((int)pHeap, size, _TDbExt_uMemFlags, 0);
    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

int TDbExtMemAllocTemp(void *pHeap, int size, void *ppMem)
{
    void *pMem;
    int flags = _TDbExt_uMemFlags;

    if (_TDbExt_pOverrideHeap != 0) {
        pHeap = _TDbExt_pOverrideHeap;
    }
    pMem = fn_801D2BB0((int)pHeap, size, (flags & ~4) | 2, 0);
    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

int TDbExtMemRealloc(void *pHeap, void *pOld, int oldSize, int newSize, void *ppMem)
{
    void *pMem = fn_801D310C(pOld, newSize, _TDbExt_uMemFlags, 0);

    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

void TDbExtMemFree(void *pHeap, void *pMem, int size)
{
    fn_801D2BD0(pMem);
}

int TDbExtLoadFromResource(int db, void *pPath, int mode, int flags)
{
    TDbExtResRef_t file;
    int isOpen;
    int err;

    isOpen = ResIsOpen(pPath);
    file.mMode = mode;
    file.mpStream = ResOpenDevice(pPath, 0x2C);
    if (file.mpStream != 0) {
        err = TDbLoad(db, (int)&file, flags, (int)&tdbioresCallback);
        if (isOpen == 0) {
            if (err == 0) {
                if (ResClose(file.mpStream)) {
                    err = 0x27;
                }
            } else {
                ResClose(file.mpStream);
            }
        }
    } else {
        err = 0x26;
    }
    return err;
}
