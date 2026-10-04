#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

struct Args_80020C44 {
    int mUnknown0;
    Params_80005284 *mpUnknown4;
};

static const char *lbl_802F4614[] = {
    "Balanced",
    "Rush Offense",
    "Rush Defense",
    "Pass Offense",
    "Pass Defense",
    "Custom",
};
static int lbl_803EBAA8 = 0;

extern "C" {
char *fn_80020BAC(int action, Params_80005284 **ppParams)
{
    Params_80005284 *pParams = *ppParams;

    switch (action) {
    case 3:
        --lbl_803EBAA8;
        if (lbl_803EBAA8 < 0) {
            lbl_803EBAA8 = 5;
        }
        break;
    case 1:
        ++lbl_803EBAA8;
        if (lbl_803EBAA8 > 5) {
            lbl_803EBAA8 = 0;
        }
        break;
    case -1:
        lbl_803EBAA8 = 0;
        break;
    }
    return fn_801C3284(pParams->mpText, lbl_802F4614[lbl_803EBAA8], pParams->mLength);
}

int fn_80020C44(unsigned int id, Args_80020C44 *pArgs)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
    {
        Params_80005284 *pParams = pArgs->mpUnknown4;
        fn_80020BAC(pArgs->mUnknown0, &pParams);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
