/* PATH library servicing (pathserv.c): the millisecond clock, switching between and sorting the
   loaded music projects, and the per-tick service task and timer that drive them. */

#include "engine/pathlib.h"

extern "C" unsigned int fn_801B343C(void)
{
    unsigned int result = 0;
    if (lbl_803EBB60)
        result = lbl_803EBB60->vfn_05();
    return result;
}

extern "C" unsigned int fn_801B3480(unsigned int index, unsigned int flags)
{
    if (index <= 3 && lbl_802F47D0[index] && lbl_802F47D0[index]->mUnknown18) {
        unsigned int value = lbl_802F47D0[index]->mUnknown14;
        unsigned int mask = flags & 0xF0000000;
        if ((!mask || (value & mask)) && ((flags & 0x0F000000) & value)) {
            lbl_803EBB28 = lbl_802F47D0[index];
            return value;
        }
    }
    return 0;
}

extern "C" int fn_801B34DC(unsigned int flags)
{
    int i = 0;
    int hasMask = (flags & 0x0F000000) != 0;
    for (; i < 4; ++i) {
        unsigned int mask = 0;
        if (!hasMask)
            mask = 0x01000000 << i;
        if (fn_801B3480(i, flags | mask))
            return 1;
    }
    return 0;
}

extern "C" int fn_801B3568(void)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (lbl_802F47D0[i]) {
            for (int j = i + 1; j < 4; ++j) {
                if (lbl_802F47D0[j] && lbl_802F47D0[i]->mUnknown14 > lbl_802F47D0[j]->mUnknown14) {
                    Bank_801B3480 temp = *lbl_802F47D0[i];
                    *lbl_802F47D0[i] = *lbl_802F47D0[j];
                    *lbl_802F47D0[j] = temp;
                }
            }
        }
    }
    return i;
}

extern "C" void fn_801B39B8(int mode)
{
    if (!lbl_803EBB39) {
        int acquired;
        if (++lbl_803EBB24 == 1 && lbl_803EBB38)
            acquired = 1;
        else {
            --lbl_803EBB24;
            acquired = 0;
        }
        if (acquired) {
            lbl_803EBB3B = mode;
            lbl_803EBB3C = fn_801B343C();
            fn_801B43CC(0);
            for (unsigned char i = 0; i < 4; ++i) {
                if (fn_801B3480(i, 0xFFFFFFFF)) {
                    fn_801B421C();
                    fn_801B3724();
                }
            }
            fn_801B43CC(1);
            lbl_803EBB28 = 0;
            --lbl_803EBB24;
        }
    }
}

extern "C" void fn_801B3A88(void)
{ fn_801B39B8(32); }

extern "C" void fn_801B3AAC(void)
{ fn_801B39B8(66); }
