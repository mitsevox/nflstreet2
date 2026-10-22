#include "engine/tmlib.h"

extern Pool_801C750C *lbl_803EBF10;
extern Registry_8021283C lbl_8039B52C;
extern Shader_80211638 *lbl_803ECFD0;

static Shader_80211638 *fn_80211774(Registry_8021283C *pLib, ShaderDef_80211638 *pDef)
{
    Shader_80211638 *pShader;

    pShader = fn_801C75F0(lbl_803EBF10);
    fn_80211638(pShader, pDef);
    fn_8021295C(pLib, pDef->mName, pShader);
    return pShader;
}

void fn_802117C8(Registry_8021283C *pLib, int maxShaders)
{
    fn_80212850(pLib, maxShaders, 1, 0);
}

void fn_802117F0(Registry_8021283C *pLib)
{
    Shader_80211638 *pShader;
    int count;
    int i;

    count = fn_80212CAC(pLib);
    for (i = 0; i < count; i++) {
        pShader = fn_80212AEC(pLib, i);
        fn_80211730(pShader);
        fn_801C7650(lbl_803EBF10, pShader);
    }
    fn_802128A8(pLib);
}

Shader_80211638 *fn_80211860(Registry_8021283C *pLib, ShaderDef_80211638 *pDef, ShaderFunc_80211638 bindFunc)
{
    Shader_80211638 *pShader;

    pShader = fn_80211774(pLib, pDef);
    fn_8021175C(pShader, bindFunc);
    return pShader;
}

void fn_8021189C(int maxShaders, int maxLibs)
{
    fn_80212850(&lbl_8039B52C, maxLibs, 1, 1);
    lbl_803EBF10 = fn_801C750C(1, maxShaders, sizeof(Shader_80211638), 0);
}

void fn_802118F0(void)
{
    fn_802128A8(&lbl_8039B52C);
    fn_801C75B8(lbl_803EBF10);
    lbl_803EBF10 = 0;
}

void fn_80211928(const char *pName, Registry_8021283C *pLib)
{
    fn_8021295C(&lbl_8039B52C, pName, pLib);
}

void fn_80211958(const char *pName)
{
    fn_80212AB0(&lbl_8039B52C, pName);
}

Shader_80211638 *fn_80211984(const char *pPath)
{
    if (pPath == 0) {
        return lbl_803ECFD0;
    }
    return fn_80212BDC(&lbl_8039B52C, pPath);
}

void fn_802119BC(Shader_80211638 *pShader)
{
    lbl_803ECFD0 = pShader;
}
