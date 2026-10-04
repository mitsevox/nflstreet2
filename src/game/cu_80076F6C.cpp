#include "game/Object_8017886C.h"

extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

int fn_8006F0D8(void);
int fn_800745BC(int side);
void fn_80075198(int *pResult);
void fn_800753E4(int *pResult);
void fn_80075550(int *pResult, int value);
void fn_80075640(int *pResult);
int fn_80177F70(void);
int fn_80177F7C(void);
int fn_80178194(void);
int fn_80178308(void);
int fn_80178360(void);
int fn_801AE5D4(int a, int b, int c);
int fn_801F7ABC(void);
float fn_80237260(int stream);
void fn_8007732C(int side);
}

static unsigned int lbl_803EA788 = 0;
static float lbl_803EA78C = 0.0f;

extern "C" void fn_80076F6C(int *pResult)
{
    *pResult = 16;
    switch (fn_80177F70()) {
    case 1:
        *pResult |= 1;
        break;
    case 2:
        *pResult |= 2;
        break;
    case 3:
        *pResult |= 4;
        break;
    case 4:
        *pResult |= 8;
        break;
    case 6:
        *pResult |= 32;
        break;
    }
}

extern "C" void fn_80077010(int *pResult)
{
    int value;

    *pResult = 8;
    value = fn_80178194();
    if (value == -1) {
        *pResult |= 4;
    } else if (value <= 5) {
        *pResult |= 1;
    } else if (value > 14) {
        *pResult |= 2;
    }
}

extern "C" void fn_80077080(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (!(p->mUnknown18 & 8)) {
        if (fn_8006F0D8() & 1) {
            *pResult |= 1;
        }
        if (p->mUnknown14 < 0.0f) {
            *pResult |= 2;
        } else if (p->mUnknown14 > 0.0f) {
            *pResult |= 256;
            if (p->mUnknown14 >= 20.0f) {
                if (p->mUnknown18 & 0x10000) {
                    *pResult |= 64;
                } else {
                    *pResult |= 128;
                }
            }
        }
        if ((p->mUnknown18 & 0x1000) && p->mUnknown1D == 0) {
            *pResult |= 8;
        }
        if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
            *pResult |= 32;
        }
    } else if (fn_80177F7C() != 6) {
        *pResult |= 4;
    }
    if (p->mUnknown1D == -2) {
        *pResult |= 16;
    }
}

extern "C" void fn_800771C0(void)
{
    lbl_803EA788 = 0;
    lbl_803EA78C = 0.0f;
}

extern "C" void fn_800771D8(void) {}

extern "C" void fn_800771DC(void)
{
    if (lbl_803EA788 != 0) {
        if ((float)(fn_801F7ABC() - lbl_803EA788) >= lbl_803EA78C * 60.0f) {
            fn_8007732C(fn_80178360());
            lbl_803EA788 = 0;
        }
    }
}

extern "C" void fn_80077258(void)
{
    int result1;
    int result2;
    int result3;

    fn_80076F6C(&result1);
    fn_80077010(&result2);
    if (fn_80178360() == 0) {
        fn_80075550(&result3, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x2002), 3, result1, result2, result3);
    } else {
        fn_80075550(&result3, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4002), 3, result1, result2, result3);
    }
}

extern "C" void fn_8007732C(int side)
{
    int result1;
    int result2;
    int result3;
    int result4;
    int result5;

    if (lbl_803EA788 == 0) {
        lbl_803EA788 = fn_801F7ABC();
        lbl_803EA78C = fn_80237260(1) + 1.0f;
    }
    fn_80077080(&result1);
    fn_80075198(&result2);
    fn_80075550(&result3, fn_800745BC(side));
    fn_80075640(&result4);
    fn_800753E4(&result5);
    if (side == 0) {
        if (fn_80178360() == 0) {
            lbl_803EBB10(fn_801AE5D4(1, 0, 0x2012), 3, result1, result2, result3);
        } else {
            lbl_803EBB10(fn_801AE5D4(1, 0, 0x2003), 5, result1, result2, result3, result4, result5);
        }
    } else if (fn_80178360() == 0) {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4003), 5, result1, result2, result3, result4, result5);
    } else {
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x4012), 3, result1, result2, result3);
    }
}

extern "C" void fn_80077488(void)
{
    int result;

    if (fn_80178360() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x200C), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x400C), 1, result);
    }
}

extern "C" void fn_8007753C(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x201A), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x401A), 1, result);
    }
}
