#include "engine/tmlib.h"

extern int fn_801C31B0(const char *pA, const char *pB);

extern TexXFormDef_80215838 *lbl_803EBF18;

void fn_80215838(TexXFormDef_80215838 *pDef, void *pOldBase, void *pNewBase)
{
    unsigned int i;

    for (i = 0; i < pDef->mNumEntries; i++) {
        TexXFormEntry_80215838 *pEntry = &pDef->maEntries[i];

        pEntry->mpName = fn_8020EB94((void *)pEntry->mpName, pOldBase, pNewBase);
    }
}

int fn_802158A4(const char *pName)
{
    TexXFormDef_80215838 *pDef = lbl_803EBF18;
    TexXFormEntry_80215838 *pEntries;
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
