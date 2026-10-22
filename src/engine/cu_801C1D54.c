#include <dolphin/ar.h>

extern u32 lbl_803ECEC4;
extern volatile int lbl_803ECEC8;

u32 fn_801C1D54(void)
{
    ARInit(&lbl_803ECEC4, 1);
    ARQInit();
    return ARGetBaseAddress();
}

void fn_801C1D84(void)
{
}

void fn_801C1D88(unsigned int request)
{
    lbl_803ECEC8--;
}
