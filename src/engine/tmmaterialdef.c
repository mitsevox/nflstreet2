#include "engine/tmlib.h"

void fn_80213228(MaterialLib_80213228 *pLib, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    pLib->mpMaterials = TMModelResRelocatePtr(pLib->mpMaterials, pOldBase, pNewBase);
    for (i = 0; i < pLib->mNumMaterials; i++) {
        MaterialDef_80213228 *pDef = &pLib->mpMaterials[i];
        int j;

        pDef->mpName = TMModelResRelocatePtr((void *)pDef->mpName, pOldBase, pNewBase);
        pDef->mpShaderName = TMModelResRelocatePtr((void *)pDef->mpShaderName, pOldBase, pNewBase);
        pDef->mpUnknown2C = TMModelResRelocatePtr(pDef->mpUnknown2C, pOldBase, pNewBase);
        for (j = 0; j < pDef->mNumTextures; j++) {
            pDef->mapTextureNames[j] = TMModelResRelocatePtr((void *)pDef->mapTextureNames[j], pOldBase, pNewBase);
        }
    }
}

int fn_8021330C(MaterialLib_80213228 *pLib, const char *pName)
{
    unsigned int i;

    for (i = 0; i < pLib->mNumMaterials; i++) {
        if (TMNameCompareExact(pLib->mpMaterials[i].mpName, pName) != 0) {
            return i;
        }
    }
    return -1;
}
