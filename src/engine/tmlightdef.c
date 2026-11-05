/* Light definitions inside loaded model chunks: pointer relocation after loading. */

#include "engine/tmlib.h"

void TMLightDefRelocateChunk(TMLightDef_t *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpUnknown4 = fn_8020EB94(pDef->mpUnknown4, pOldBase, pNewBase);
    pDef->mpUnknownC = fn_8020EB94(pDef->mpUnknownC, pOldBase, pNewBase);
}
