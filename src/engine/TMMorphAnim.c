#include "engine/tmlib.h"

static void *fn_80215DA4(void *p, void *pOldBase, void *pNewBase)
{
    void *pResult = 0;

    if (p != 0) {
        pResult = (void *)((int)p - (int)pOldBase + (int)pNewBase);
    }
    return pResult;
}

void fn_80215DC0(MorphAnim_80215DA4 *pAnim, void *pOldBase, void *pNewBase)
{
    int numTargets = pAnim->mNumTargets;
    int i;

    for (i = 0; i < numTargets; i++) {
        MorphTarget_80215DA4 *pTarget;
        int numData;
        int j;

        pTarget = pAnim->mapTargets[i] = fn_80215DA4(pAnim->mapTargets[i], pOldBase, pNewBase);
        numData = pTarget->mNumData;
        for (j = 0; j < numData; j++) {
            pTarget->mapData[j] = fn_80215DA4(pTarget->mapData[j], pOldBase, pNewBase);
        }
    }
}
