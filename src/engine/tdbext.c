#include "engine/tdbiores.h"
#include "engine/t3db_table.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/Record_802CC680.h"

typedef struct TdbExtFile_8020D2D0 {
    void *mpStream;
    int mMode;
} TdbExtFile_8020D2D0;

extern unsigned char fn_801D2700(int handle);
extern int fn_801D2130(Record_802CC680 *pParams);
extern int fn_801D2570(int handle);
extern void *fn_801D310C(void *p, int size, int flags, int d);
extern int fn_801F0F9C(void *pPath);
extern int fn_801F9134(void *pDb, TdbExtFile_8020D2D0 *pFile, int flags, void *pOps);

extern Record_802CC680 lbl_8039B498;
extern void *lbl_803EBEA8;
extern unsigned char lbl_803EBEAC;
extern unsigned char lbl_803EBEAD;
extern int lbl_803EBEB0;

void fn_8020D0CC(Record_802CC680 *pParams)
{
    lbl_8039B498 = *pParams;
    lbl_803EBEAD = fn_801D2700(pParams->mUnknown8);
    if (lbl_803EBEAD == 0) {
        fn_801D2130(&lbl_8039B498);
    }
    lbl_803EBEAC = 1;
    lbl_803EBEA8 = 0;
}

void fn_8020D158(void)
{
    if (lbl_803EBEAD == 0) {
        fn_801D2570(lbl_8039B498.mUnknown8);
    }
    lbl_803EBEAC = 0;
}

int fn_8020D194(int a, int b, int *pHandle)
{
    *pHandle = lbl_8039B498.mUnknown8;
    return 0;
}

int fn_8020D1A8(void)
{
    return 0;
}

int fn_8020D1B0(void *pHeap, int size, void *ppMem)
{
    void *pMem;

    if (lbl_803EBEA8 != 0) {
        pHeap = lbl_803EBEA8;
    }
    pMem = fn_801D2BB0((int)pHeap, size, lbl_803EBEB0, 0);
    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

int fn_8020D204(void *pHeap, int size, void *ppMem)
{
    void *pMem;
    int flags = lbl_803EBEB0;

    if (lbl_803EBEA8 != 0) {
        pHeap = lbl_803EBEA8;
    }
    pMem = fn_801D2BB0((int)pHeap, size, (flags & ~4) | 2, 0);
    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

int fn_8020D260(void *pHeap, void *pOld, int oldSize, int newSize, void *ppMem)
{
    void *pMem = fn_801D310C(pOld, newSize, lbl_803EBEB0, 0);

    *(void **)ppMem = pMem;
    return pMem ? 0 : 2;
}

void fn_8020D2AC(void *pHeap, void *pMem, int size)
{
    fn_801D2BD0(pMem);
}

int fn_8020D2D0(void *pDb, void *pPath, int mode, int flags)
{
    TdbExtFile_8020D2D0 file;
    int isOpen;
    int err;

    isOpen = fn_801F0F9C(pPath);
    file.mMode = mode;
    file.mpStream = fn_801EEB44(pPath, 0x2C);
    if (file.mpStream != 0) {
        err = fn_801F9134(pDb, &file, flags, &lbl_802F9BAC);
        if (isOpen == 0) {
            if (err == 0) {
                if (fn_801EEFAC(file.mpStream)) {
                    err = 0x27;
                }
            } else {
                fn_801EEFAC(file.mpStream);
            }
        }
    } else {
        err = 0x26;
    }
    return err;
}
