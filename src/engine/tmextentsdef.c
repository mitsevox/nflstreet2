/* Extents definitions inside loaded model chunks: pointer relocation after loading. */

#include "engine/tmlib.h"

void TMExtentsDefRelocateChunk(TMExtentsDef_t *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpExtents = fn_8020EB94(pDef->mpExtents, pOldBase, pNewBase);
}
