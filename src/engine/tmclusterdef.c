#include "engine/tmlib.h"

void fn_80213384(ClusterDef_80213384 *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpEntries = fn_8020EB94(pDef->mpEntries, pOldBase, pNewBase);
}

void fn_802133B8(ClusterDef_80213384 *pDef, short *pRemap)
{
    int i;

    for (i = 0; i < pDef->mNumClusters; i++) {
        ClusterEntry_80213384 *pEntry = &pDef->mpEntries[i];
        int bone = pEntry->mBone;

        while (bone >= 0 && pRemap[bone] == -1) {
            bone--;
        }
        if (bone != -1) {
            pEntry->mBone = pRemap[bone];
        } else {
            pEntry->mBone = 0xFF;
        }
    }
}
