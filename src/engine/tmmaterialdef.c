/* Material definitions inside loaded model chunks: pointer relocation after loading and
   lookup of a material by name. */

#include "engine/tmlib.h"

void TMMaterialDefRelocateChunk(TMMaterialDefList_t *pLib, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    pLib->mpMaterials = fn_8020EB94(pLib->mpMaterials, pOldBase, pNewBase);
    for (i = 0; i < pLib->mNumMaterials; i++) {
        TMMaterialDef_t *pDef = &pLib->mpMaterials[i];
        int j;

        pDef->mpName = fn_8020EB94((void *)pDef->mpName, pOldBase, pNewBase);
        pDef->mpShaderName = fn_8020EB94((void *)pDef->mpShaderName, pOldBase, pNewBase);
        pDef->mpUnknown2C = fn_8020EB94(pDef->mpUnknown2C, pOldBase, pNewBase);
        for (j = 0; j < pDef->mNumTextures; j++) {
            pDef->mapTextureNames[j] = fn_8020EB94((void *)pDef->mapTextureNames[j], pOldBase, pNewBase);
        }
    }
}

int TMMaterialDefGetIndexByName(TMMaterialDefList_t *pLib, const char *pName)
{
    unsigned int i;

    for (i = 0; i < pLib->mNumMaterials; i++) {
        if (fn_802126C0(pLib->mpMaterials[i].mpName, pName) != 0) {
            return i;
        }
    }
    return -1;
}
