#include "game/Block_800B3660.h"
#include "game/fn_80096A58.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include "game/fn_800B65A0.h"

extern "C" {
int fn_801F0F18(int a);
int fn_800BA6F8(void);

extern int lbl_803EAB30;
}

extern "C" void fn_800B34BC(void)
{
    Params_80096A58 params;
    int pick = lbl_803EAB30;

    lbl_803EAB34->mUnknown14 = -1;
    fn_801C1F94(&params, 0, sizeof(params));
    params.mUnknown40 = 0xFFFF;
    params.mUnknown42 = 0xFFFF;
    params.mUnknown20 = 2;
    params.mUnknown0 = 27;
    params.mUnknown24 = 0;
    while (lbl_803EAB30 == pick) {
        pick = fn_802372EC(1, 11);
        params.mUnknown28 = pick;
    }
    if (fn_802372EC(0, 2) != 0) {
        params.mUnknown12 |= 0x100;
    } else {
        params.mUnknown12 |= 0x200;
    }
    lbl_803EAB30 = pick;
    params.mUnknown32 = 60.0f;
    lbl_803EAB34->mUnknown14 = fn_80096A58(&params);
    fn_801F0F18(0);
    if ((fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF || fn_800BA6F8() != 0)
        && lbl_803EAB34->mUnknown14 != -1) {
        fn_80096B1C(lbl_803EAB34->mUnknown14);
    }
}
