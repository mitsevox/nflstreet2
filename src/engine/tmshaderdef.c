#include "engine/tmlib.h"

TMShaderParmDef_t *fn_80212CB4(TMShaderDef_t *pDef, const char *pName, int type)
{
    TMShaderParmDef_t *pParms;
    int i;

    pParms = pDef->mParms;
    for (i = 0; i < pDef->mNumParms; i++) {
        if ((type == 0 || pParms[i].mType == type) && TMNameCompareExact(pParms[i].mName, pName)) {
            return &pParms[i];
        }
    }
    return 0;
}
