#include <string.h>

#include "game/cu_80181330.h"

extern "C" {
void fn_801C3284(char *pDest, const char *pSource, int size);
}

static char lbl_8036B4A0[20];

extern "C" void fn_80021270(const char *pText)
{
    strcpy(lbl_8036B4A0, pText);
}

extern "C" void fn_8002129C(char *pDest, int length)
{
    fn_801C3284(pDest, lbl_8036B4A0, length + 1);
}

extern "C" int fn_800212C8(int id, Params_80005284 **ppParams, int c, int *pResult)
{
    switch (id) {
    case 0x80000002:
        fn_80021270((*ppParams)->mpText);
        break;
    case 0x80000001:
        *pResult = 1;
        break;
    default:
        return 0;
    }
    return 1;
}
