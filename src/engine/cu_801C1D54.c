#include <dolphin/ar.h>

extern u32 lbl_803ECEC4;

u32 fn_801C1D54(void)
{
    ARInit(&lbl_803ECEC4, 1);
    ARQInit();
    return ARGetBaseAddress();
}
