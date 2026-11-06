/* Light definitions inside loaded model chunks: pointer relocation after loading. */

#include "engine/tmlib.h"

void TMLightDefRelocateChunk(TMLightDef_t *pDef, void *pOldBase, void *pNewBase)
{
    pDef->mpUnknown4 = TMModelResRelocatePtr(pDef->mpUnknown4, pOldBase, pNewBase);
    pDef->mpUnknownC = TMModelResRelocatePtr(pDef->mpUnknownC, pOldBase, pNewBase);
}
