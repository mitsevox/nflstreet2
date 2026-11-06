/* Texture transform tables: pointer relocation after loading and lookup of a transform by name. */

#include "engine/tmlib.h"

extern int fn_801C31B0(const char *pA, const char *pB);

extern TMTexXformDef_t *lbl_803EBF18;

void TMTexXformRelocateChunk(TMTexXformDef_t *pDef, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    for (i = 0; i < pDef->mNumEntries; i++) {
        TMTexXformEntry_t *pEntry = &pDef->maEntries[i];

        pEntry->mpName = fn_8020EB94((void *)pEntry->mpName, pOldBase, pNewBase);
    }
}

int TMTexXformFind(const char *pName)
{
    TMTexXformDef_t *pDef = lbl_803EBF18;
    TMTexXformEntry_t *pEntries;
    unsigned int i;

    if (pDef == 0) {
        return -1;
    }
    i = pDef->mNumEntries;
    pEntries = pDef->maEntries;
    while (i-- > 0) {
        if (fn_801C31B0(pEntries[i].mpName, pName) == 0) {
            return i;
        }
    }
    return i;
}
