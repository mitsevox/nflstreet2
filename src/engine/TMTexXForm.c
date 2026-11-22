/* Texture transform tables: pointer relocation after loading and lookup of a transform by name. */

#include "engine/tmlib.h"

extern int stricmp(const char *pA, const char *pB);

/* The transform table TMTexXformFind searches; nothing in this build sets it. */
static TMTexXformDef_t *_TMTexXform_pDef = 0;

void TMTexXformRelocateChunk(TMTexXformDef_t *pDef, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    for (i = 0; i < pDef->mNumEntries; i++) {
        TMTexXformEntry_t *pEntry = &pDef->maEntries[i];

        pEntry->mpName = TMModelResRelocatePtr((void *)pEntry->mpName, pOldBase, pNewBase);
    }
}

int TMTexXformFind(const char *pName)
{
    TMTexXformDef_t *pDef = _TMTexXform_pDef;
    TMTexXformEntry_t *pEntries;
    unsigned int i;

    if (pDef == 0) {
        return -1;
    }
    i = pDef->mNumEntries;
    pEntries = pDef->maEntries;
    while (i-- > 0) {
        if (stricmp(pEntries[i].mpName, pName) == 0) {
            return i;
        }
    }
    return i;
}
