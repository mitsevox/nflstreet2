#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

typedef struct TdbExtParams_8020D0CC {
    int mUnknown00;
    int mUnknown04;
    int mHandle;
    int mUnknown0C;
    int mUnknown10;
    int mUnknown14;
} TdbExtParams_8020D0CC;

typedef struct TdbExtFile_8020D2D0 {
    void *mpStream;
    int mMode;
} TdbExtFile_8020D2D0;

extern unsigned char fn_801D2700(int handle);
extern void fn_801D2130(TdbExtParams_8020D0CC *pParams);
extern void fn_801D2570(int handle);
extern void *fn_801D310C(void *p, unsigned int size, int flags, int d);
extern int fn_801F0F9C(void *pPath);
extern void *fn_801EEB44(void *pPath, int mode);
extern int fn_801F9134(void *pDb, TdbExtFile_8020D2D0 *pFile, int flags, char *pOps);
extern int fn_801EEFAC(void *pStream);

extern TdbExtParams_8020D0CC lbl_8039B498;
extern int lbl_803EBEA8;
extern unsigned char lbl_803EBEAC;
extern unsigned char lbl_803EBEAD;
extern int lbl_803EBEB0;
extern char lbl_802F9BAC[];

void fn_8020D0CC(TdbExtParams_8020D0CC *pParams)
{
    lbl_8039B498 = *pParams;
    lbl_803EBEAD = fn_801D2700(pParams->mHandle);
    if (lbl_803EBEAD == 0) {
        fn_801D2130(&lbl_8039B498);
    }
    lbl_803EBEAC = 1;
    lbl_803EBEA8 = 0;
}

void fn_8020D158(void)
{
    if (lbl_803EBEAD == 0) {
        fn_801D2570(lbl_8039B498.mHandle);
    }
    lbl_803EBEAC = 0;
}

int fn_8020D194(int a, int b, int *pHandle)
{
    *pHandle = lbl_8039B498.mHandle;
    return 0;
}

int fn_8020D1A8(void)
{
    return 0;
}

int fn_8020D1B0(int heap, unsigned int size, unsigned char **ppData)
{
    unsigned char *pData;

    if (lbl_803EBEA8 != 0) {
        heap = lbl_803EBEA8;
    }
    pData = fn_801D2BB0(heap, size, lbl_803EBEB0, 0);
    *ppData = pData;
    return pData ? 0 : 2;
}

int fn_8020D204(int heap, unsigned int size, unsigned char **ppData)
{
    unsigned char *pData;
    int flags = lbl_803EBEB0;

    if (lbl_803EBEA8 != 0) {
        heap = lbl_803EBEA8;
    }
    pData = fn_801D2BB0(heap, size, (flags & ~4) | 2, 0);
    *ppData = pData;
    return pData ? 0 : 2;
}

int fn_8020D260(int heap, unsigned char *pOld, unsigned int oldSize, unsigned int newSize, unsigned char **ppData)
{
    unsigned char *pData = fn_801D310C(pOld, newSize, lbl_803EBEB0, 0);

    *ppData = pData;
    return pData ? 0 : 2;
}

void fn_8020D2AC(int heap, void *pData, unsigned int size)
{
    fn_801D2BD0(pData);
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
        err = fn_801F9134(pDb, &file, flags, lbl_802F9BAC);
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
