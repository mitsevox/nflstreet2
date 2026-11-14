/* Low-level sound bank memory: moves or trims a loaded sound bank into the sound heap and selects
   the sound driver memory range for a bank. */

#include "engine/sound.h"
#include "game/fn_801D2B7C.h"

extern void *fn_801D310C(void *pAddr, int size, int ident, int flags);
extern int SNDbankheadercopy(void *pDest, int handle);
extern int SNDbankheadersize(int handle);
extern void SNDmemlimits(int a, int b);

extern int lbl_803EBE18;

void SndllResolveBank(SndBankInfo_t *pBank, int move)
{
    void *pData;

    if (move) {
        pData = fn_801D2BB0(lbl_803EBE18, SNDbankheadersize(pBank->mHandle), 0, 0);
        SNDbankheadercopy(pData, pBank->mHandle);
        fn_801D2BD0(pBank->pData);
    } else {
        pData = fn_801D310C(pBank->pData, SNDbankheadersize(pBank->mHandle), 0, 0);
        pBank->pData = pData;
    }
    pBank->pData = pData;
}

void SndSetHeap(SndBankHeap_t *pEntries, int index)
{
    SNDmemlimits(pEntries[index].mUnk4, pEntries[index].mUnk8);
}

void SndSetAllocHeap(int heap)
{
    lbl_803EBE18 = heap;
}
