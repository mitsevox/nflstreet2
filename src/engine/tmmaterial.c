/* TM renderer materials: binds a shader, textures, palettes (CLUTs) and constants to the selected
   material, sizing each material's texture states from pooled arrays. */

#include "engine/tmlib.h"

extern int DSGetNodeHandlerStat(Pool_801C750C *pPool, int a);

Pool_801C750C *_TMMaterial_pTexNodes[9];
/* The material selected last. */
static TMMaterial_t *_TMMaterial_pSelect = 0;

static int _TMMaterialGetTexState(TMMaterial_t *pMaterial, const char *pName)
{
    int index;

    if ((unsigned int)pName > 0xFEFFFFFF) {
        return (int)pName + 0x01000000;
    }
    index = -1;
    if (pMaterial->mpShader->mpDef != 0) {
        TMShaderParmDef_t *pParm = TMShaderDefGetParmByName(pMaterial->mpShader->mpDef, pName, 1);

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
            if (_TMMaterial_pTexNodes[numParms] != 0 && DSGetNodeHandlerStat(_TMMaterial_pTexNodes[numParms], 0) != 0) {
                break;
            }
        }
        pParms = DSNewNode(_TMMaterial_pTexNodes[numParms]);
        memset(pParms, 0, numParms * sizeof(TMMaterialTexState_t));
        if (pMaterial->mNumParms > 0) {
            memcpy(pParms, pMaterial->mpParms,
                   (pMaterial->mNumParms > pMaterial->mpShader->mNumTextures ? pMaterial->mpShader->mNumTextures
                                                                             : pMaterial->mNumParms) *
                       sizeof(TMMaterialTexState_t));
        }
    }
    if (pMaterial->mNumParms > 0) {
        DSDelNode(_TMMaterial_pTexNodes[pMaterial->mNumParms], pMaterial->mpParms);
    }
    pMaterial->mNumParms = numParms;
    pMaterial->mpParms = pParms;
}

void TMMaterialInit(int *pPoolSizes)
{
    int i;

    memset(_TMMaterial_pTexNodes, 0, sizeof(_TMMaterial_pTexNodes));
    for (i = 0; i <= 8; i++) {
        if (pPoolSizes[i] > 0) {
            _TMMaterial_pTexNodes[i] = DSNewNodeHandler(1, pPoolSizes[i], (i + 1) * sizeof(TMMaterialTexState_t), 0);
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
    _TMMaterial_pSelect = pMaterial;
}

void TMMaterialBindTextureClut(const char *pName, TMTexture_t *pTexture, TMClut_t *pClut)
{
    TMMaterial_t *pMaterial = _TMMaterial_pSelect;

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
    TMMaterial_t *pMaterial = _TMMaterial_pSelect;

    if (pMaterial != 0) {
        int index = _TMMaterialGetTexState(pMaterial, pName);

        if (index >= 0) {
            pMaterial->mpParms[index].mpClut = pClut;
        }
    }
}

void TMMaterialBindShaderRef(const char *pPath)
{
    if (_TMMaterial_pSelect != 0) {
        TMShader_t *pShader = TMShaderLibGetShader(pPath);

        if (pShader != 0) {
            TMMaterialBindShader(pShader);
        }
    }
}

void TMMaterialBindShader(TMShader_t *pShader)
{
    TMMaterial_t *pMaterial = _TMMaterial_pSelect;

    if (pMaterial != 0 && pShader != 0) {
        pMaterial->mpShader = pShader;
        _TMMaterialAllocTexState(pMaterial);
    }
}

void TMMaterialSetMatDef(TMMaterialDef_t *pDef)
{
    TMMaterial_t *pMaterial = _TMMaterial_pSelect;
    int i;

    if (pMaterial != 0) {
        TMMaterialBindShaderRef(pDef->mpShaderName);
        for (i = 0; i < pDef->mNumTextures; i++) {
            TMTexture_t *pTexture = TMTexLibGetTexture(0, pDef->mapTextureNames[i]);
            TMClut_t *pClut = TMTexLibGetClut(0, pDef->mapTextureNames[i], 0);
            int xform = TMTexXformFind(pDef->mapTextureNames[i]);

            pMaterial->mpParms[i].mpTexture = pTexture;
            pMaterial->mpParms[i].mpClut = pClut;
            pMaterial->mpParms[i].mXForm = xform;
        }
        pMaterial->mpDef = pDef;
    }
}
