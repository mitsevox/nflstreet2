/* TM renderer materials: binds a shader, textures, palettes (CLUTs) and constants to the selected
   material, sizing each material's texture states from pooled arrays. */

#include "engine/tmlib.h"

extern int fn_801C74C8(Pool_801C750C *pPool, int a);

extern Pool_801C750C *lbl_803E96C4[9];
extern TMMaterial_t *lbl_803EBEE0;

static int _TMMaterialGetTexState(TMMaterial_t *pMaterial, const char *pName)
{
    int index;

    if ((unsigned int)pName > 0xFEFFFFFF) {
        return (int)pName + 0x01000000;
    }
    index = -1;
    if (pMaterial->mpShader->mpDef != 0) {
        TMShaderParmDef_t *pParm = fn_80212CB4(pMaterial->mpShader->mpDef, pName, 1);

        if (pParm != 0) {
            index = pParm->mIndex;
        }
    }
    return index;
}

static void _TMMaterialAllocTexState(TMMaterial_t *pMaterial)
{
    TMMaterialTexState_t *pParms = 0;
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
        memset(pParms, 0, numParms * sizeof(TMMaterialTexState_t));
        if (pMaterial->mNumParms > 0) {
            memcpy(pParms, pMaterial->mpParms,
                   (pMaterial->mNumParms > pMaterial->mpShader->mNumTextures ? pMaterial->mpShader->mNumTextures
                                                                             : pMaterial->mNumParms) *
                       sizeof(TMMaterialTexState_t));
        }
    }
    if (pMaterial->mNumParms > 0) {
        fn_801C7650(lbl_803E96C4[pMaterial->mNumParms], pMaterial->mpParms);
    }
    pMaterial->mNumParms = numParms;
    pMaterial->mpParms = pParms;
}

void TMMaterialInit(int *pPoolSizes)
{
    int i;

    memset(lbl_803E96C4, 0, sizeof(lbl_803E96C4));
    for (i = 0; i <= 8; i++) {
        if (pPoolSizes[i] > 0) {
            lbl_803E96C4[i] = fn_801C750C(1, pPoolSizes[i], (i + 1) * sizeof(TMMaterialTexState_t), 0);
        }
    }
}

void TMMaterialReset(TMMaterial_t *pMaterial)
{
    int i;

    pMaterial->mpDef = 0;
    pMaterial->mpShader = TMShaderLibGetShader(0);
    _TMMaterialAllocTexState(pMaterial);
    for (i = 0; i < pMaterial->mNumParms; i++) {
        pMaterial->mpParms[i].mpTexture = 0;
        pMaterial->mpParms[i].mpClut = 0;
    }
    for (i = 3; i >= 0; i--) {
        pMaterial->maConsts[i].mWord = 0;
    }
}

void TMMaterialSelect(TMMaterial_t *pMaterial)
{
    lbl_803EBEE0 = pMaterial;
}

void TMMaterialBindTextureClut(const char *pName, TMTexture_t *pTexture, TMClut_t *pClut)
{
    TMMaterial_t *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0) {
        int index = _TMMaterialGetTexState(pMaterial, pName);

        if (index >= 0) {
            pMaterial->mpParms[index].mpTexture = pTexture;
            pMaterial->mpParms[index].mpClut = pClut;
        }
    }
}

void TMMaterialBindClut(const char *pName, TMClut_t *pClut)
{
    TMMaterial_t *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0) {
        int index = _TMMaterialGetTexState(pMaterial, pName);

        if (index >= 0) {
            pMaterial->mpParms[index].mpClut = pClut;
        }
    }
}

void TMMaterialBindShaderRef(const char *pPath)
{
    if (lbl_803EBEE0 != 0) {
        TMShader_t *pShader = TMShaderLibGetShader(pPath);

        if (pShader != 0) {
            TMMaterialBindShader(pShader);
        }
    }
}

void TMMaterialBindShader(TMShader_t *pShader)
{
    TMMaterial_t *pMaterial = lbl_803EBEE0;

    if (pMaterial != 0 && pShader != 0) {
        pMaterial->mpShader = pShader;
        _TMMaterialAllocTexState(pMaterial);
    }
}

void TMMaterialSetMatDef(MaterialDef_80213228 *pDef)
{
    TMMaterial_t *pMaterial = lbl_803EBEE0;
    int i;

    if (pMaterial != 0) {
        TMMaterialBindShaderRef(pDef->mpShaderName);
        for (i = 0; i < pDef->mNumTextures; i++) {
            TMTexture_t *pTexture = TMTexLibGetTexture(0, pDef->mapTextureNames[i]);
            TMClut_t *pClut = TMTexLibGetClut(0, pDef->mapTextureNames[i], 0);
            int xform = fn_802158A4(pDef->mapTextureNames[i]);

            pMaterial->mpParms[i].mpTexture = pTexture;
            pMaterial->mpParms[i].mpClut = pClut;
            pMaterial->mpParms[i].mXForm = xform;
        }
        pMaterial->mpDef = pDef;
    }
}
