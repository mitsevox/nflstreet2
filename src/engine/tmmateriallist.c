/* TM renderer material lists: reference-counted materials from a pool, gathered in per-model
   lists that are filled from a model's material definitions. */

#include "engine/tmlib.h"

extern Pool_801C750C *lbl_803EBEE8;

static TMMaterial_t *_TMMaterialListAllocNode(TMMaterial_t *pMaterial)
{
    if (pMaterial == 0) {
        pMaterial = fn_801C75F0(lbl_803EBEE8);
        pMaterial->mRefCount = 0;
        pMaterial->mNumParms = 0;
        pMaterial->mpParms = 0;
        TMMaterialReset(pMaterial);
    }
    pMaterial->mRefCount++;
    return pMaterial;
}

static void _TMMaterialListFreeNode(TMMaterial_t *pMaterial)
{
    if (pMaterial != 0) {
        if (--pMaterial->mRefCount <= 0) {
            TMMaterialReset(pMaterial);
            fn_801C7650(lbl_803EBEE8, pMaterial);
        }
    }
}

void TMMaterialListInit(int maxMaterials)
{
    lbl_803EBEE8 = fn_801C750C(1, maxMaterials, sizeof(TMMaterial_t), 0);
    TMMaterialSelect(0);
}

void TMMaterialListShutdown(void)
{
    TMMaterialSelect(0);
    fn_801C75B8(lbl_803EBEE8);
    lbl_803EBEE8 = 0;
}

void TMMaterialListAlloc(TMMaterialList_t *pList, unsigned int numMaterials)
{
    unsigned int i;

    pList->mNumMaterials = numMaterials;
    pList->mppMaterials = TMMemAllocArray(numMaterials, 4);
    for (i = 0; i < numMaterials; i++) {
        pList->mppMaterials[i] = 0;
    }
}

void TMMaterialListAllocDefs(TMMaterialList_t *pList, MaterialLib_80213228 *pLib)
{
    if (pLib != 0) {
        TMMaterialListAlloc(pList, pLib->mNumMaterials);
        TMMaterialListSetMatDefs(pList, pLib);
    } else {
        TMMaterialListAlloc(pList, 0);
    }
}

void TMMaterialListFree(TMMaterialList_t *pList)
{
    unsigned int i;

    for (i = 0; i < pList->mNumMaterials; i++) {
        _TMMaterialListFreeNode(pList->mppMaterials[i]);
    }
    TMMemFreeArray(pList->mppMaterials);
    pList->mppMaterials = 0;
    pList->mNumMaterials = 0;
}

TMMaterial_t *TMMaterialListGetMaterial(TMMaterialList_t *pList, int index)
{
    if (index >= 0 && index < pList->mNumMaterials) {
        return pList->mppMaterials[index];
    }
    return 0;
}

void TMMaterialListSelect(TMMaterialList_t *pList, int index)
{
    TMMaterial_t **ppMaterials = pList->mppMaterials;

    if (index < pList->mNumMaterials) {
        if (ppMaterials[index] == 0) {
            ppMaterials[index] = _TMMaterialListAllocNode(0);
        }
        TMMaterialSelect(ppMaterials[index]);
    } else {
        TMMaterialSelect(0);
    }
}

void TMMaterialListSetMatDefs(TMMaterialList_t *pList, MaterialLib_80213228 *pLib)
{
    unsigned int i;
    unsigned int count;

    if (pLib != 0) {
        count = pList->mNumMaterials;
        if (pLib->mNumMaterials < count) {
            count = pLib->mNumMaterials;
        }
        for (i = 0; i < count; i++) {
            TMMaterialListSelect(pList, i);
            TMMaterialSetMatDef(&pLib->mpMaterials[i]);
        }
        TMMaterialSelect(0);
    }
}
