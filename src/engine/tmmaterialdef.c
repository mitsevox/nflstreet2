#include "engine/tmlib.h"

void fn_80213228(MaterialLib_80213228 *pLib, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    pLib->mpMaterials = fn_8020EB94(pLib->mpMaterials, pOldBase, pNewBase);
    for (i = 0; i < pLib->mNumMaterials; i++) {
        MaterialDef_80213228 *pDef = &pLib->mpMaterials[i];
        int j;

        pDef->mpName = fn_8020EB94((void *)pDef->mpName, pOldBase, pNewBase);
        pDef->mpShaderName = fn_8020EB94((void *)pDef->mpShaderName, pOldBase, pNewBase);
        pDef->mpUnknown2C = fn_8020EB94(pDef->mpUnknown2C, pOldBase, pNewBase);
        for (j = 0; j < pDef->mNumTextures; j++) {
            pDef->mapTextureNames[j] = fn_8020EB94((void *)pDef->mapTextureNames[j], pOldBase, pNewBase);
        }
    }
}

int fn_8021330C(MaterialLib_80213228 *pLib, const char *pName)
{
    unsigned int i;

    for (i = 0; i < pLib->mNumMaterials; i++) {
        if (fn_802126C0(pLib->mpMaterials[i].mpName, pName) != 0) {
            return i;
        }
    }
    return -1;
}
