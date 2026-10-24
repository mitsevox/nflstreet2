#include "engine/sound.h"
#include "game/fn_801D2B7C.h"

extern void *fn_801D310C(void *pAddr, int size, int ident, int flags);
extern int fn_8026A980(void *pDest, int handle);
extern int fn_8026A9F4(int handle);
extern void fn_8026B4D8(int a, int b);

extern int lbl_803EBE18;

void fn_801F5034(SndBankInfo_801F3524 *pBank, int move)
{
    void *pData;

    if (move) {
        pData = fn_801D2BB0(lbl_803EBE18, fn_8026A9F4(pBank->mHandle), 0, 0);
        fn_8026A980(pData, pBank->mHandle);
        fn_801D2BD0(pBank->pData);
    } else {
        pData = fn_801D310C(pBank->pData, fn_8026A9F4(pBank->mHandle), 0, 0);
        pBank->pData = pData;
    }
    pBank->pData = pData;
}

void fn_801F50C8(SndBankEntry_801F50C8 *pEntries, int index)
{
    fn_8026B4D8(pEntries[index].mUnk4, pEntries[index].mUnk8);
}

void fn_801F50F8(int heap)
{
    lbl_803EBE18 = heap;
}
