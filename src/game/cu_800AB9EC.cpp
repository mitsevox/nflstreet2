#include "game/Class_80297B90.h"
#include "game/cu_8008E978.h"

extern "C" {
extern Block_800AACD4 *lbl_803EAA88;
}

extern "C" float fn_800AB9EC(Class_80297B90 *p)
{
    float result = 0.1f;
    Table_800AA80C *pTable = lbl_803EAA88->mpUnknown0;

    if (pTable != 0) {
        result = pTable->mUnknown84;
    }
    return result;
}
