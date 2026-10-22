#include "engine/tmlib.h"

extern Pool_801C750C *lbl_803EBEE8;

Material_8020FAAC *fn_8020FF34(Material_8020FAAC *pMaterial)
{
    if (pMaterial == 0) {
        pMaterial = fn_801C75F0(lbl_803EBEE8);
        pMaterial->mRefCount = 0;
        pMaterial->mNumParms = 0;
        pMaterial->mpParms = 0;
        fn_8020FCA0(pMaterial);
    }
    pMaterial->mRefCount++;
    return pMaterial;
}

void fn_8020FF90(Material_8020FAAC *pMaterial)
{
    if (pMaterial != 0) {
        if (--pMaterial->mRefCount <= 0) {
            fn_8020FCA0(pMaterial);
            fn_801C7650(lbl_803EBEE8, pMaterial);
        }
    }
}

void fn_8020FFE4(int maxMaterials)
{
    lbl_803EBEE8 = fn_801C750C(1, maxMaterials, sizeof(Material_8020FAAC), 0);
    fn_8020FD40(0);
}

void fn_80210020(void)
{
    fn_8020FD40(0);
    fn_801C75B8(lbl_803EBEE8);
    lbl_803EBEE8 = 0;
}

void fn_80210054(MaterialList_8020FF34 *pList, unsigned int numMaterials)
{
    unsigned int i;

    pList->mNumMaterials = numMaterials;
    pList->mppMaterials = fn_802127D0(numMaterials, 4);
    for (i = 0; i < numMaterials; i++) {
        pList->mppMaterials[i] = 0;
    }
}

void fn_802100C0(MaterialList_8020FF34 *pList, MaterialLib_80213228 *pLib)
{
    if (pLib != 0) {
        fn_80210054(pList, pLib->mNumMaterials);
        fn_80210214(pList, pLib);
    } else {
        fn_80210054(pList, 0);
    }
}

void fn_80210114(MaterialList_8020FF34 *pList)
{
    unsigned int i;

    for (i = 0; i < pList->mNumMaterials; i++) {
        fn_8020FF90(pList->mppMaterials[i]);
    }
    fn_80212814(pList->mppMaterials);
    pList->mppMaterials = 0;
    pList->mNumMaterials = 0;
}

Material_8020FAAC *fn_80210184(MaterialList_8020FF34 *pList, int index)
{
    if (index >= 0 && index < pList->mNumMaterials) {
        return pList->mppMaterials[index];
    }
    return 0;
}

void fn_802101B0(MaterialList_8020FF34 *pList, int index)
{
    Material_8020FAAC **ppMaterials = pList->mppMaterials;

    if (index < pList->mNumMaterials) {
        if (ppMaterials[index] == 0) {
            ppMaterials[index] = fn_8020FF34(0);
        }
        fn_8020FD40(ppMaterials[index]);
    } else {
        fn_8020FD40(0);
    }
}

void fn_80210214(MaterialList_8020FF34 *pList, MaterialLib_80213228 *pLib)
{
    unsigned int i;
    unsigned int count;

    if (pLib != 0) {
        count = pList->mNumMaterials;
        if (pLib->mNumMaterials < count) {
            count = pLib->mNumMaterials;
        }
        for (i = 0; i < count; i++) {
            fn_802101B0(pList, i);
            fn_8020FE78(&pLib->mpMaterials[i]);
        }
        fn_8020FD40(0);
    }
}
