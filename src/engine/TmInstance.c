#include "engine/tmlib.h"

void fn_80215C14(Instance_80215C14 *pInst, void *pOldBase, void *pNewBase)
{
    pInst->mpUnknown8 = TMModelResRelocatePtr(pInst->mpUnknown8, pOldBase, pNewBase);
    pInst->mpUnknown4 = TMModelResRelocatePtr(pInst->mpUnknown4, pOldBase, pNewBase);
    pInst->mpTarget = TMModelResRelocatePtr(pInst->mpTarget, pOldBase, pNewBase);
    pInst->mpTarget->mpData = TMModelResRelocatePtr(pInst->mpTarget->mpData, pOldBase, pNewBase);
    pInst->mpSkel = TMModelResRelocatePtr(pInst->mpSkel, pOldBase, pNewBase);
    fn_80215E5C(pInst->mpSkel, pOldBase, pNewBase);
}

void fn_80215CB0(RenderInst_80215CB0 *pInst, void *pOldBase, void *pNewBase)
{
    unsigned int i;
    unsigned int j;

    pInst->mpEntries = TMModelResRelocatePtr(pInst->mpEntries, pOldBase, pNewBase);
    i = pInst->mNumEntries;
    while (i-- > 0) {
        RenderInstEntry_80215CB0 *pEntry = &pInst->mpEntries[i];

        j = 4;
        while (j-- > 0) {
            if (pEntry->maUsed[j] != 0) {
                pEntry->mapData[j] = TMModelResRelocatePtr(pEntry->mapData[j], pOldBase, pNewBase);
            }
        }
    }
    i = pInst->mNumPointers;
    while (i-- > 0) {
        pInst->mapPointers[i] = TMModelResRelocatePtr(pInst->mapPointers[i], pOldBase, pNewBase);
    }
}
