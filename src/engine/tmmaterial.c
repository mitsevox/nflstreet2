#include "engine/tmlib.h"

extern int fn_801C74C8(Pool_801C750C *pPool, int a);

extern Pool_801C750C *lbl_803E96C4[9];
extern Material_8020FAAC *lbl_803EBEE0;

int fn_8020FAAC(Material_8020FAAC *pMaterial, const char *pName)
{
    int index;

    if ((unsigned int)pName > 0xFEFFFFFF) {
        return (int)pName + 0x01000000;
    }
    index = -1;
    if (pMaterial->mpShader->mpDef != 0) {
        ShaderParmDef_80211638 *pParm = fn_80212CB4(pMaterial->mpShader->mpDef, pName, 1);

        if (pParm != 0) {
            index = pParm->mIndex;
        }
    }
    return index;
}

void fn_8020FB14(Material_8020FAAC *pMaterial)
{
    MaterialParm_8020FAAC *pParms = 0;
    int numParms = 0;
    int numTextures = pMaterial->mpShader->mNumTextures;

    if (numTextures == pMaterial->mNumParms) {
        return;
    }
    if (numTextures > 0) {
        for (numParms = numTextures; numParms <= 8; numParms++) {
            if (lbl_803E96C4[numParms] != 0 && fn_801C74C8(lbl_803E96C4[numParms], 0) != 0) {
                break;
            }
        }
        pParms = fn_801C75F0(lbl_803E96C4[numParms]);
        memset(pParms, 0, numParms * sizeof(MaterialParm_8020FAAC));
        if (pMaterial->mNumParms > 0) {
            memcpy(pParms, pMaterial->mpParms,
                   (pMaterial->mNumParms > pMaterial->mpShader->mNumTextures ? pMaterial->mpShader->mNumTextures
                                                                             : pMaterial->mNumParms) *
                       sizeof(MaterialParm_8020FAAC));
        }
    }
    if (pMaterial->mNumParms > 0) {
        fn_801C7650(lbl_803E96C4[pMaterial->mNumParms], pMaterial->mpParms);
    }
    pMaterial->mNumParms = numParms;
    pMaterial->mpParms = pParms;
}

void fn_8020FC1C(int *pPoolSizes)
{
    int i;

    memset(lbl_803E96C4, 0, sizeof(lbl_803E96C4));
    for (i = 0; i <= 8; i++) {
        if (pPoolSizes[i] > 0) {
            lbl_803E96C4[i] = fn_801C750C(1, pPoolSizes[i], (i + 1) * sizeof(MaterialParm_8020FAAC), 0);
        }
    }
}

void fn_8020FCA0(Material_8020FAAC *pMaterial)
{
    int i;

    pMaterial->mpDef = 0;
    pMaterial->mpShader = fn_80211984(0);
    fn_8020FB14(pMaterial);
    for (i = 0; i < pMaterial->mNumParms; i++) {
        pMaterial->mpParms[i].mpTexture = 0;
        pMaterial->mpParms[i].mpClut = 0;
    }
    for (i = 3; i >= 0; i--) {
        pMaterial->maUnknown14[i] = 0;
    }
}

void fn_8020FD40(Material_8020FAAC *pMaterial)
{
    lbl_803EBEE0 = pMaterial;
}

void fn_8020FD48(const char *pName, Texture_80212234 *pTexture, Clut_80212534 *pClut)
{
    Material_8020FAAC *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0) {
        int index = fn_8020FAAC(pMaterial, pName);

        if (index >= 0) {
            pMaterial->mpParms[index].mpTexture = pTexture;
            pMaterial->mpParms[index].mpClut = pClut;
        }
    }
}

void fn_8020FDAC(const char *pName, Clut_80212534 *pClut)
{
    Material_8020FAAC *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0) {
        int index = fn_8020FAAC(pMaterial, pName);

        if (index >= 0) {
            pMaterial->mpParms[index].mpClut = pClut;
        }
    }
}

void fn_8020FE04(const char *pPath)
{
    if (lbl_803EBEE0 != 0) {
        Shader_80211638 *pShader = fn_80211984(pPath);

        if (pShader != 0) {
            fn_8020FE3C(pShader);
        }
    }
}

void fn_8020FE3C(Shader_80211638 *pShader)
{
    Material_8020FAAC *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0 && pShader != 0) {
        pMaterial->mpShader = pShader;
        fn_8020FB14(pMaterial);
    }
}

void fn_8020FE78(MaterialDef_80213228 *pDef)
{
    Material_8020FAAC *pMaterial = lbl_803EBEE0;
    int i;

    if (pMaterial != 0) {
        fn_8020FE04(pDef->mpShaderName);
        for (i = 0; i < pDef->mNumTextures; i++) {
            Texture_80212234 *pTexture = fn_802120E4(0, pDef->mapTextureNames[i]);
            Clut_80212534 *pClut = fn_80212124(0, pDef->mapTextureNames[i], 0);
            int xform = fn_802158A4(pDef->mapTextureNames[i]);

            pMaterial->mpParms[i].mpTexture = pTexture;
            pMaterial->mpParms[i].mpClut = pClut;
            pMaterial->mpParms[i].mXForm = xform;
        }
        pMaterial->mpDef = pDef;
    }
}
