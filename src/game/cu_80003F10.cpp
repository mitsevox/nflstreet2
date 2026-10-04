#include "game/cu_80003F10.h"

static unsigned char lbl_803EB8E8 = 0;

extern "C" void fn_80003F10(unsigned char value)
{
    lbl_803EB8E8 = value;
}

extern "C" bool fn_80003F18(void)
{
    return lbl_803EB8E8 != 0;
}
