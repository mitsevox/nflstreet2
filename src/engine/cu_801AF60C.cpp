/* Speech library start-up (neutral file name): installs the callbacks, starts the library and
   shuts it down. */

#include "engine/spchlib.h"

extern "C" {

void fn_801AF60C(void)
{
    lbl_8037E0A0.mUnknown0 = 0;
    lbl_8037E0A0.mUnknown4 = 0;
    lbl_8037E0A0.mUnknown8 = 0;
    lbl_8037E0A0.mCallback = 0;
    lbl_8037E0A0.mUnknown10 = 0;
}

void fn_801AF630(int (*callback)(Key_801AE658 *key))
{
    if (lbl_803EBAFC == 0x01789A34) {
        lbl_8037E0A0.mCallback = callback;
    }
}

int fn_801AF650(int a, int b, int c)
{
    int i;

    lbl_802F4794[0] = 'S';
    if (lbl_803EBAF8 != 0) {
        fn_801AF60C();
        lbl_803ECEA4 = c;
        lbl_8037E0A0.mUnknown0 = a;
        lbl_803EBB10 = fn_801AEC58;
        lbl_803ECEA0 = b;
        iSPCH_InitRandom(b);
        fn_801B118C();
        fn_801B192C(0);
        for (i = 0; i <= 7; i++) {
            lbl_8037E274[i] = 0;
        }
        fn_801AE808();
        fn_801AF544();
        fn_801B2450();
        fn_801AE8DC();
        lbl_803EBAFC = 0x01789A34;
        return 1;
    }
    return 0;
}

void fn_801AF718(void)
{
    if (lbl_803EBAFC == 0x01789A34) {
        lbl_803EBAFC = 0;
        fn_801AF60C();
        fn_801B2468();
        fn_801AE808();
    }
}

}
