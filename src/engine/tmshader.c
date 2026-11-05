/* TM renderer shaders: builds a shader from its definition (texture and constant parameters) and
   holds its bind and unbind callbacks. */

#include "engine/tmlib.h"

extern TMShader_t *lbl_803EBF08;

void TMShaderNew(TMShader_t *pShader, TMShaderDef_t *pDef)
{
    TMShaderParmDef_t *pParm;
    int i;

    pShader->mpDef = pDef;
    pShader->mBindFunc = 0;
    pShader->mUnbindFunc = 0;
    pShader->mUnknownC = 0;
    pShader->mNumTextures = 0;
    pShader->mNumConsts = 0;
    pShader->mpFirstConst = 0;
    pShader->mConstSize = 0;
    pShader->mpConstData = 0;
    for (i = 0; i < pDef->mNumParms; i++) {
        pParm = &pDef->mParms[i];
        if (pParm->mType == 1) {
            if (pParm->mIndex >= pShader->mNumTextures) {
                pShader->mNumTextures = pParm->mIndex + 1;
            }
        } else {
            if (pShader->mpFirstConst == 0) {
                pShader->mpFirstConst = pParm;
            }
            pShader->mConstSize += fn_80213214(pParm->mType);
            pShader->mNumConsts++;
        }
    }
    if (pDef->mbAllocConsts == 1) {
        pShader->mpConstData = TMMemAllocArray(pShader->mConstSize, 4);
    }
    TMShaderSelect(pShader);
}

void TMShaderDelete(TMShader_t *pShader)
{
    if (pShader->mpConstData != 0) {
        TMMemFreeArray(pShader->mpConstData);
    }
}

void TMShaderSetBindFunc(TMShader_t *pShader, TMShaderFunc_t bindFunc)
{
    pShader->mBindFunc = bindFunc;
}

void TMShaderSetUnbindFunc(TMShader_t *pShader, TMShaderFunc_t unbindFunc)
{
    pShader->mUnbindFunc = unbindFunc;
}

void TMShaderSelect(TMShader_t *pShader)
{
    lbl_803EBF08 = pShader;
}
