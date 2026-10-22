#include "engine/tmlib.h"

void fn_802146C8(LightDef_802146C8 *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpUnknown4 = fn_8020EB94(pDef->mpUnknown4, pOldBase, pNewBase);
    pDef->mpUnknownC = fn_8020EB94(pDef->mpUnknownC, pOldBase, pNewBase);
}
