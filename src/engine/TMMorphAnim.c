/* Morph animation resources: pointer relocation of their morph targets after loading. */

#include "engine/tmlib.h"

void *TMMorphAnimResRelocatePtr(void *p, void *pOldBase, void *pNewBase)
{
    void *pResult = 0;

    if (p != 0) {
        pResult = (void *)((int)p - (int)pOldBase + (int)pNewBase);
    }
    return pResult;
}

void TMMorphAnimRelocate(TMMorphAnim_t *pAnim, void *pOldBase, void *pNewBase)
{
    int numTargets = pAnim->mNumTargets;
    int i;

    for (i = 0; i < numTargets; i++) {
        TMMorphTarget_t *pTarget;
        int numData;
        int j;

        pTarget = pAnim->mapTargets[i] = TMMorphAnimResRelocatePtr(pAnim->mapTargets[i], pOldBase, pNewBase);
        numData = pTarget->mNumData;
        for (j = 0; j < numData; j++) {
            pTarget->mapData[j] = TMMorphAnimResRelocatePtr(pTarget->mapData[j], pOldBase, pNewBase);
        }
    }
}
