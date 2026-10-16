#include "game/Block_8030E6E8.h"
#include "game/Camera_8013F738.h"

extern "C" {
Camera_8013F738 *fn_8013FA04(int index);
int fn_8013F9F8(void);
unsigned char fn_8002FA84(void);
unsigned char fn_80140DB4(void);
int fn_801784C4(void);

extern unsigned char lbl_803EA9F8;
extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" void fn_800A233C(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[1] = 1;
    lbl_8030E6E8.mUnknown8C4 = 9;
}

extern "C" void fn_800A238C(void)
{
    lbl_8030E6E8.mUnknown28 = 15.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.3f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 0;
    lbl_8030E6E8.mUnknown6C[2] = 0;
    lbl_8030E6E8.mUnknown8C4 = 7;
}

extern "C" void fn_800A23F0(void)
{
    lbl_8030E6E8.mUnknown28 = 15.0f;
    lbl_8030E6E8.mUnknown2C = 30.045f;
    lbl_8030E6E8.mUnknown30 = 40.2f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.03f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8B4[4] = 1;
    lbl_8030E6E8.mUnknown8C4 = 2;
}

extern "C" void fn_800A244C(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8B4[4] = 1;
    lbl_8030E6E8.mUnknown8C4 = 5;
}

extern "C" void fn_800A24A0(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 50.0f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 0;
    lbl_8030E6E8.mUnknown6C[2] = 1;
    lbl_8030E6E8.mUnknown8C4 = 6;
}

extern "C" void fn_800A2500(void)
{
    lbl_8030E6E8.mUnknown28 = 20.0f;
    lbl_8030E6E8.mUnknown2C = 40.0f;
    lbl_8030E6E8.mUnknown30 = 49.7f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[3] = 1;
    lbl_8030E6E8.mUnknown6C[6] = 7;
    lbl_8030E6E8.mUnknown6C[7] = 1;
    lbl_8030E6E8.mUnknown8C4 = 10;
}

extern "C" void fn_800A2560(void)
{
    lbl_8030E6E8.mUnknown28 = 17.5f;
    lbl_8030E6E8.mUnknown2C = 30.0f;
    lbl_8030E6E8.mUnknown30 = 40.2f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[6] = 1;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown8C4 = 11;
}

extern "C" void fn_800A25BC(void)
{
    lbl_8030E6E8.mUnknown28 = 17.5f;
    lbl_8030E6E8.mUnknown2C = 30.0f;
    lbl_8030E6E8.mUnknown30 = 39.5f;
    lbl_8030E6E8.mUnknown34 = 1.0f;
    lbl_8030E6E8.mFloat38 = 20.0f;
    lbl_8030E6E8.mUnknown8B4[0] = 1;
    lbl_8030E6E8.mUnknown6C[1] = 7;
    lbl_8030E6E8.mUnknown6C[2] = 1;
    lbl_8030E6E8.mUnknown8C4 = 8;
}

extern "C" int fn_800A262C(void)
{
    if (fn_8013FA04(5)->mHeader.mUnknown04[1] <= 0.5f - lbl_8030E6E8.mUnknown2C && fn_8013F9F8() == 0
        && fn_8002FA84() == 0 && fn_801784C4() == 0 && (fn_801784C4() != 0 || fn_80140DB4() == 0)) {
        lbl_803EA9F8 = 1;
        return 1;
    }
    lbl_803EA9F8 = 0;
    return 0;
}

extern "C" int fn_800A26C4(void)
{
    if (fn_8013FA04(5)->mHeader.mUnknown04[1] > lbl_8030E6E8.mUnknown2C - 0.5f && fn_8013F9F8() == 0
        && fn_8002FA84() == 0 && fn_801784C4() != 0 && (fn_801784C4() == 0 || fn_80140DB4() == 0)) {
        lbl_803EA9F8 = 1;
        return 1;
    }
    lbl_803EA9F8 = 0;
    return 0;
}
