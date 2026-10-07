#include "game/fn_80178D18.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

extern "C" {
extern void (*lbl_803EBB10)(int, int, ...);

int fn_8006F0D8(void);
void fn_80074398(int handle);
int fn_80074490(int side);
int fn_800745BC(int side);
void fn_80075198(int *pResult);
void fn_800753E4(int *pResult);
void fn_80075550(int *pResult, int value);
int fn_800A21A8(int bit);
int fn_80177F7C(void);
Point_8017886C fn_80177FE0(void);
float fn_801782A4(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
int fn_801783AC(int bit);
int fn_80179138(void);
int fn_801AE5D4(int a, int b, int c);
int fn_801F7ABC(void);
float fn_80237260(int stream);

void fn_80076228(void);
int fn_80076D54(void);
void fn_80076D5C(int id);
int fn_80076D64(void);
int fn_80076DA4(void);
}

static unsigned int lbl_803EA758 = 0;
static float lbl_803EA75C = 0.0f;
static unsigned char lbl_803EA760 = 0;
static int lbl_803EA764 = 0;
static int lbl_803EA768 = 0;
static int lbl_803EA76C = 0;
static int lbl_803EA770 = 0;
static int lbl_803EA774 = 0;
static int lbl_803EA778 = 0;
static int lbl_803EA77C = 0;

extern "C" int fn_800756E8(void)
{
    int result = fn_80178320();
    Object_8017886C *p = fn_8017886C();

    if (p->mUnknown18 & 8) {
        if (fn_80177F7C() == 6) {
            if (p->mUnknown1D == 0) {
                result = fn_80178360();
            } else {
                result = ((lbl_803EA778 >> 8) & 0xFF) ^ 1;
            }
        } else if (p->mUnknown18 & 0x400) {
            result = fn_80178348();
        } else if (p->mUnknown18 & 0x200) {
            result = fn_80178348();
        } else if (p->mUnknown1D == -2) {
            result = fn_80178360();
        } else if (p->mUnknown18 & 0x800) {
            result = fn_80178360();
        }
    }
    return result;
}

extern "C" int fn_80075794(void)
{
    Object_8017886C *p = fn_8017886C();

    if (p->mUnknown1D != 0) {
        fn_80074398(fn_80076DA4());
        return 1;
    }
    if (fn_80177F7C() == 6) {
        return 2;
    }
    if ((p->mUnknown18 & 8) && fn_80177F7C() != 6) {
        return 3;
    }
    if (fn_80177F7C() == 4 && (p->mUnknown18 & 0x1000)) {
        return 4;
    }
    if (fn_8006F0D8() & 1) {
        return 5;
    }
    if (fn_8006F0D8() & 2) {
        return 6;
    }
    if (fn_800A21A8(2)) {
        return 14;
    }
    if (fn_800A21A8(0)) {
        if (p->mUnknown18 & 0x10000) {
            return 13;
        }
        fn_80074398(fn_80076D64());
        return 12;
    }
    if (p->mUnknown18 & 0x8000) {
        if (fn_800A21A8(1)) {
            fn_80074398(fn_80076D64());
            if (p->mUnknown18 & 0x10000) {
                return 11;
            }
            return 12;
        }
        fn_80074398(fn_80076D64());
        if (p->mUnknown18 & 0x10000) {
            return 7;
        }
        return 8;
    }
    if (fn_8006F0D8() & 0x40) {
        fn_80074398(lbl_803EA77C);
        return 10;
    }
    return 9;
}

extern "C" void fn_80075914(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        *pResult = 1;
    }
    if (p->mUnknown14 > 0.0f) {
        if (p->mUnknown18 & 0x10000) {
            if (p->mUnknown14 >= 20.0f) {
                *pResult |= 64;
            } else if (p->mUnknown14 >= 10.0f) {
                *pResult |= 32;
            } else {
                *pResult |= 16;
            }
        } else {
            if (p->mUnknown14 >= 20.0f) {
                *pResult |= 8;
            } else if (p->mUnknown14 >= 10.0f) {
                *pResult |= 4;
            } else {
                *pResult |= 2;
            }
        }
    }
}

extern "C" void fn_80075A14(int *pResult)
{
    Object_8017886C *p;
    int team;
    int side;

    *pResult = 0;
    p = fn_8017886C();
    team = fn_80178348();
    side = (lbl_803EA778 >> 8) & 0xFF;
    if (p->mUnknown1D == -2) {
        *pResult = 2;
    } else if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        if (team == side) {
            *pResult = 1;
        } else {
            *pResult = 2;
        }
    } else if (p->mUnknown1D == 2) {
        if (team == side) {
            *pResult = 1;
        } else {
            *pResult = 2;
        }
    }
}

extern "C" void fn_80075AA4(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if ((p->mUnknown18 & 8) && fn_80177F7C() != 6) {
        *pResult = 16;
        if (p->mUnknown18 & 0x400) {
            *pResult = 17;
        }
        if (p->mUnknown18 & 0x200) {
            *pResult |= 2;
        }
        if (p->mUnknown1D == -2) {
            *pResult |= 4;
        }
        if (p->mUnknown18 & 0x800) {
            *pResult |= 8;
        }
    }
}

extern "C" void fn_80075B5C(int *pResult)
{
    float value;

    if (fn_8017886C()->mUnknown18 & 0x10000) {
        *pResult = 1;
    } else {
        *pResult = 2;
    }
    value = fn_801782A4();
    if (fn_80177FE0().mY - value < 2.0f) {
        *pResult |= 4;
    }
}

extern "C" void fn_80075BE4(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 8;
    if (p->mUnknown14 < 0.0f) {
        *pResult = 9;
    }
    if (fn_8006F0D8() & 4) {
        *pResult |= 2;
    }
    if (fn_8006F0D8() & 8) {
        *pResult |= 4;
    }
}

extern "C" void fn_80075C68(int *pResult)
{
    *pResult = 4;
    if (fn_801783AC(12)) {
        *pResult |= 1;
    }
    if (fn_801783AC(11)) {
        *pResult |= 2;
    }
    if (fn_801783AC(23)) {
        *pResult |= 8;
    }
    if (fn_8006F0D8() & 0x10) {
        *pResult |= 16;
    }
    if (fn_8006F0D8() & 0x20) {
        *pResult |= 32;
    }
}

extern "C" void fn_80075D1C(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        if (fn_80178308() == fn_80178348()) {
            *pResult |= 1;
        } else {
            *pResult |= 2;
        }
    } else if (p->mUnknown1D == -2) {
        *pResult |= 4;
    } else if (p->mUnknown1D == 2) {
        if (fn_80179138() == 2) {
            *pResult |= 8;
        } else {
            *pResult |= 32;
        }
    } else if (p->mUnknown1D == 1) {
        *pResult |= 32;
    }
    if (*pResult != 0) {
        *pResult |= 16;
    }
}

extern "C" void fn_80075DF4(int *pResult)
{
    if (fn_8017886C()->mUnknown18 & 0x8000) {
        *pResult |= 1;
    } else {
        *pResult |= 2;
    }
}

extern "C" void fn_80075E44(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D != 0) {
        *pResult = 2;
    } else {
        *pResult = 1;
    }
}

extern "C" void fn_80075E90(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402B), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402B), 1, result);
    }
}

extern "C" void fn_80075F44(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402C), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402C), 1, result);
    }
}

extern "C" void fn_80075FF8(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402D), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402D), 1, result);
    }
}

extern "C" void fn_800760AC(void)
{
    int result;

    if (fn_80178308() == 0) {
        fn_80075550(&result, fn_800745BC(0));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402E), 1, result);
    } else {
        fn_80075550(&result, fn_800745BC(1));
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x402E), 1, result);
    }
}

extern "C" void fn_80076160(void)
{
    lbl_803EA758 = 0;
    lbl_803EA75C = 0.0f;
    lbl_803EA760 = 0;
}

extern "C" void fn_8007617C(void)
{
    if (lbl_803EA758 != 0) {
        fn_80076228();
        lbl_803EA758 = 0;
    }
}

extern "C" void fn_800761B0(void)
{
    if (lbl_803EA758 != 0) {
        if ((float)(fn_801F7ABC() - lbl_803EA758) >= lbl_803EA75C * 60.0f) {
            fn_80076228();
            lbl_803EA758 = 0;
        }
    }
}

extern "C" void fn_80076228(void)
{
    if (lbl_803EA758 == 0) {
        lbl_803EA758 = fn_801F7ABC();
        lbl_803EA75C = fn_80237260(1) + 1.0f;
        lbl_803EA760 = fn_800756E8();
    }

    switch (fn_80075794()) {
    case 0:
        break;
    case 1:
    case 2: {
        int result1;
        int result2;
        int result3;
        int result4;
        int result5;
        int result6;
        int result7;

        fn_80075198(&result1);
        fn_800753E4(&result2);
        fn_80075A14(&result3);
        fn_80075D1C(&result4);
        fn_80075DF4(&result5);
        fn_80075E44(&result6);
        if (lbl_803EA760 == 0) {
            if ((result3 & 1) && fn_80178348() == 0) {
                if (lbl_803EA778 != 0) {
                    fn_80075550(&result7, lbl_803EA778);
                } else {
                    fn_80075550(&result7, fn_800745BC(0));
                }
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2008), 7, result1, result2, result3, result4, result7, result5, result6);
            } else {
                fn_80075550(&result7, fn_800745BC(0));
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2016), 4, result1, result3, result4, result7);
            }
        } else {
            if ((result3 & 1) && fn_80178348() == 0) {
                fn_80075550(&result7, fn_800745BC(1));
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4016), 4, result1, result3, result4, result7);
            } else {
                if (lbl_803EA778 != 0) {
                    fn_80075550(&result7, lbl_803EA778);
                } else {
                    fn_80075550(&result7, fn_800745BC(1));
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4008), 7, result1, result2, result3, result4, result7, result5, result6);
            }
        }
        break;
    }
    case 3: {
        int result1;
        int result2;
        int result3;
        int result4;

        fn_80075198(&result1);
        fn_80075AA4(&result2);
        fn_800753E4(&result3);
        if (lbl_803EA760 == 0) {
            if (fn_80178348() == 0) {
                fn_80075550(&result4, fn_800745BC(lbl_803EA760));
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x200B), 3, result2, result1, result4);
            } else {
                if (lbl_803EA774 != 0) {
                    fn_80075550(&result4, lbl_803EA774);
                } else {
                    fn_80075550(&result4, fn_800745BC(0));
                }
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2017), 4, result2, result1, result3, result4);
            }
        } else {
            if (fn_80178348() == 0) {
                if (lbl_803EA774 != 0) {
                    fn_80075550(&result4, lbl_803EA774);
                } else {
                    fn_80075550(&result4, fn_800745BC(1));
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4017), 4, result2, result1, result3, result4);
            } else {
                fn_80075550(&result4, fn_800745BC(lbl_803EA760));
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x400B), 3, result2, result1, result4);
            }
        }
        break;
    }
    case 4: {
        int result1;
        int result2;

        fn_80075B5C(&result1);
        fn_80075550(&result2, fn_800745BC(lbl_803EA760));
        if (lbl_803EA760 == 0) {
            if (fn_80178348() == 0) {
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2009), 2, result1, result2);
            } else {
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2018), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4018), 2, result1, result2);
            } else {
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4009), 2, result1, result2);
            }
        }
        break;
    }
    case 5: {
        int result;

        fn_80075550(&result, fn_80076D54());
        if (lbl_803EA760 == 0) {
            if (fn_80178360() == 0) {
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2010), 1, result);
            }
        } else {
            if (fn_80178360() == 1) {
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4010), 1, result);
            }
        }
        break;
    }
    case 6: {
        int result1;
        int result2;

        fn_80075BE4(&result1);
        if (lbl_803EA764 != 0) {
            fn_80075550(&result2, lbl_803EA764);
        } else {
            fn_80075550(&result2, fn_800745BC(fn_80178360()));
        }
        if (lbl_803EA760 == 0) {
            if (fn_80178360() == 0) {
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x200F), 2, result1, result2);
            }
        } else {
            if (fn_80178360() == 1) {
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x400F), 2, result1, result2);
            }
        }
        break;
    }
    case 14:
        if (fn_80178348() == lbl_803EA760) {
            fn_800760AC();
        }
        break;
    case 13:
        if (fn_80178348() == lbl_803EA760) {
            fn_80075FF8();
        }
        break;
    case 11:
        if (fn_80178348() == lbl_803EA760) {
            fn_80075E90();
        }
        break;
    case 12:
        if (fn_80178348() == lbl_803EA760) {
            fn_80075F44();
        }
        break;
    case 7: {
        int result1;
        int result2;

        fn_80075914(&result1);
        if (lbl_803EA760 == 0) {
            if (fn_80178348() == 0) {
                fn_80075550(&result2, lbl_803EA76C);
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2005), 2, result1, result2);
            } else {
                if (lbl_803EA764 != 0) {
                    fn_80075550(&result2, lbl_803EA764);
                } else {
                    fn_80075550(&result2, fn_800745BC(0));
                }
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2013), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (lbl_803EA764 != 0) {
                    fn_80075550(&result2, lbl_803EA764);
                } else {
                    fn_80075550(&result2, fn_800745BC(1));
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4013), 2, result1, result2);
            } else {
                fn_80075550(&result2, lbl_803EA76C);
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4005), 2, result1, result2);
            }
        }
        break;
    }
    case 8: {
        int result1;
        int result2;

        fn_80075C68(&result1);
        if (lbl_803EA760 == 0) {
            if (fn_80178348() == 0) {
                if (result1 & 0x20) {
                    unsigned short i;
                    unsigned int count = fn_80178D18(0);

                    for (i = 0; i < count; i++) {
                        Object_80039F5C *player = fn_80039F5C(0, i);

                        if (player->mFlags & 0x10000000) {
                            fn_80076D5C(player->mId);
                            break;
                        }
                    }
                }
                if (lbl_803EA768 != 0) {
                    fn_80075550(&result2, lbl_803EA768);
                    lbl_803EBB10(fn_801AE5D4(1, 0, 0x2006), 2, result1, result2);
                }
            } else {
                if (lbl_803EA768 != 0 && fn_80074490(0) != 0) {
                    fn_80075550(&result2, fn_80074490(0));
                } else {
                    fn_80075550(&result2, fn_800745BC(0));
                }
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2014), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (lbl_803EA768 != 0 && fn_80074490(1) != 0) {
                    fn_80075550(&result2, fn_80074490(1));
                } else {
                    fn_80075550(&result2, fn_800745BC(1));
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4014), 2, result1, result2);
            } else {
                if (result1 & 0x20) {
                    unsigned short i;
                    unsigned int count = fn_80178D18(1);

                    for (i = 0; i < count; i++) {
                        Object_80039F5C *player = fn_80039F5C(1, i);

                        if (player->mFlags & 0x10000000) {
                            fn_80076D5C(player->mId);
                            break;
                        }
                    }
                }
                if (lbl_803EA768 != 0) {
                    fn_80075550(&result2, lbl_803EA768);
                    lbl_803EBB10(fn_801AE5D4(2, 0, 0x4006), 2, result1, result2);
                }
            }
        }
        break;
    }
    case 10: {
        int team = fn_80178360();

        if (lbl_803EA760 == team) {
            int result;

            if (fn_80178360() == 0) {
                fn_80075550(&result, fn_80074490(0));
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2019), 1, result);
            } else {
                fn_80075550(&result, fn_80074490(1));
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4019), 1, result);
            }
            break;
        }
        /* Otherwise handled as case 9. */
    }
    case 9: {
        int result1;
        int result2;

        fn_80075914(&result1);
        if (lbl_803EA760 == 0) {
            if (fn_80178348() == 0) {
                fn_80075550(&result2, lbl_803EA770);
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2007), 2, result1, result2);
            } else {
                if (lbl_803EA764 != 0) {
                    fn_80075550(&result2, lbl_803EA764);
                } else {
                    fn_80075550(&result2, fn_800745BC(0));
                }
                lbl_803EBB10(fn_801AE5D4(1, 0, 0x2015), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (lbl_803EA764 != 0) {
                    fn_80075550(&result2, lbl_803EA764);
                } else {
                    fn_80075550(&result2, fn_800745BC(1));
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4015), 2, result1, result2);
            } else {
                if (lbl_803EA770 != 0) {
                    fn_80075550(&result2, lbl_803EA770);
                }
                lbl_803EBB10(fn_801AE5D4(2, 0, 0x4007), 2, result1, result2);
            }
        }
        break;
    }
    }
    lbl_803EA760 = !lbl_803EA760;
}

extern "C" void fn_80076D4C(int id)
{
    lbl_803EA764 = id;
}

extern "C" int fn_80076D54(void)
{
    return lbl_803EA764;
}

extern "C" void fn_80076D5C(int id)
{
    lbl_803EA768 = id;
}

extern "C" int fn_80076D64(void)
{
    return lbl_803EA768;
}

extern "C" void fn_80076D6C(int id)
{
    lbl_803EA76C = id;
}

extern "C" int fn_80076D74(void)
{
    return lbl_803EA76C;
}

extern "C" void fn_80076D7C(int id)
{
    lbl_803EA770 = id;
}

extern "C" int fn_80076D84(void)
{
    return lbl_803EA770;
}

extern "C" void fn_80076D8C(int id)
{
    lbl_803EA774 = id;
}

extern "C" int fn_80076D94(void)
{
    return lbl_803EA774;
}

extern "C" void fn_80076D9C(int id)
{
    lbl_803EA778 = id;
}

extern "C" int fn_80076DA4(void)
{
    return lbl_803EA778;
}

extern "C" void fn_80076DAC(int id)
{
    lbl_803EA77C = id;
}
