#include "engine/tmlib.h"

ShaderParmDef_80211638 *fn_80212CB4(ShaderDef_80211638 *pDef, const char *pName, int type)
{
    ShaderParmDef_80211638 *pParms;
    int i;

    pParms = pDef->mParms;
    for (i = 0; i < pDef->mNumParms; i++) {
        if ((type == 0 || pParms[i].mType == type) && fn_802126C0(pParms[i].mName, pName)) {
            return &pParms[i];
        }
    }
    return 0;
}
