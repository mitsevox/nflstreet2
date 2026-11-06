/* Model instance and instance-region definitions inside loaded chunks: pointer relocation
   after loading. */

#include "engine/tmlib.h"

void TMInstanceDefRelocateChunk(TMInstanceDef_t *pInst, void *pOldBase, void *pNewBase)
{
    pInst->mpUnknown8 = TMModelResRelocatePtr(pInst->mpUnknown8, pOldBase, pNewBase);
    pInst->mpUnknown4 = TMModelResRelocatePtr(pInst->mpUnknown4, pOldBase, pNewBase);
    pInst->mpTarget = TMModelResRelocatePtr(pInst->mpTarget, pOldBase, pNewBase);
    pInst->mpTarget->mpData = TMModelResRelocatePtr(pInst->mpTarget->mpData, pOldBase, pNewBase);
    pInst->mpSkel = TMModelResRelocatePtr(pInst->mpSkel, pOldBase, pNewBase);
    TMSkelRelocateChunk(pInst->mpSkel, pOldBase, pNewBase);
}

void TMInstanceRegionDefRelocateChunk(TMInstanceRegionDef_t *pInst, void *pOldBase, void *pNewBase)
{
    unsigned int i;
    unsigned int j;

    pInst->mpEntries = TMModelResRelocatePtr(pInst->mpEntries, pOldBase, pNewBase);
    i = pInst->mNumEntries;
    while (i-- > 0) {
        TMInstanceRegionEntry_t *pEntry = &pInst->mpEntries[i];

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
