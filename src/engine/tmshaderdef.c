/* Shader definitions of the TM model renderer: finds a named parameter in a shader definition. */

#include "engine/tmlib.h"

TMShaderParmDef_t *TMShaderDefGetParmByName(TMShaderDef_t *pDef, const char *pName, int type)
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
