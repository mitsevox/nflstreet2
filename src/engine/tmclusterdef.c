/* Cluster definitions (groups of vertices skinned to one bone) inside loaded model chunks:
   pointer relocation and remapping of their bone indices to another skeleton. */

#include "engine/tmlib.h"

void TMClusterDefRelocateChunk(TMClusterDef_t *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpEntries = TMModelResRelocatePtr(pDef->mpEntries, pOldBase, pNewBase);
}

void TMClusterDefRemap(TMClusterDef_t *pDef, short *pRemap)
{
    int i;

    for (i = 0; i < pDef->mNumClusters; i++) {
        TMClusterDefEntry_t *pEntry = &pDef->mpEntries[i];
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
