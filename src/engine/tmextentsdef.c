#include "engine/tmlib.h"

void fn_80215804(ExtentsDef_80215804 *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpExtents = TMModelResRelocatePtr(pDef->mpExtents, pOldBase, pNewBase);
}
