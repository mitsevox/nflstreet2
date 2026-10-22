#include "engine/tmlib.h"

extern Shader_80211638 *lbl_803EBF08;

void fn_80211638(Shader_80211638 *pShader, ShaderDef_80211638 *pDef)
{
    ShaderParmDef_80211638 *pParm;
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
        pShader->mpConstData = fn_802127D0(pShader->mConstSize, 4);
    }
    fn_8021176C(pShader);
}

void fn_80211730(Shader_80211638 *pShader)
{
    if (pShader->mpConstData != 0) {
        fn_80212814(pShader->mpConstData);
    }
}

void fn_8021175C(Shader_80211638 *pShader, ShaderFunc_80211638 bindFunc)
{
    pShader->mBindFunc = bindFunc;
}

void fn_80211764(Shader_80211638 *pShader, ShaderFunc_80211638 unbindFunc)
{
    pShader->mUnbindFunc = unbindFunc;
}

void fn_8021176C(Shader_80211638 *pShader)
{
    lbl_803EBF08 = pShader;
}
