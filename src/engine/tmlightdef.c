#include "engine/tmlib.h"

void fn_802146C8(LightDef_802146C8 *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpUnknown4 = TMModelResRelocatePtr(pDef->mpUnknown4, pOldBase, pNewBase);
    pDef->mpUnknownC = TMModelResRelocatePtr(pDef->mpUnknownC, pOldBase, pNewBase);
}
