#include <math.h>
#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802372EC.h"
#include "game/fn_80178D18.h"

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800ABDA4(int team);
int fn_800B65A0(int team);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
void fn_800D5054(Object_80039F5C *p, int a);
void fn_800D5494(Object_80039F5C *p, int a, int b);
void fn_800D5A6C(int a, int b, int c);
void fn_800D5F1C(Object_80039F5C *p, int a, int b);
void fn_800D60BC(Object_80039F5C *p, int a, int b);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
float fn_80124FE0(Object_80039F5C *p, int kind);
int fn_801486A0(void);
void fn_80156C78(int a, int b);
int fn_801783AC(int bit);
int fn_801CFFD0(int a, int b);

extern unsigned char lbl_803EACAB;
extern unsigned char lbl_803EACAC[4];
extern float lbl_803EACB0;
extern float lbl_803EACB4;
extern float lbl_803EACB8;
extern unsigned char lbl_803EACBC;

void fn_800D0660(Object_80039F5C *p, unsigned char *pOut);
int fn_800D0B90(Object_80039F5C *p);
int fn_800D0D1C(Object_80039F5C *p);
}

extern "C" unsigned char fn_800D0474(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_800B6D34(p, &input);
    unsigned char result = p->mUnknown1228.mUnknown4;
    float x = input.mUnknown12;
    if (x != 0.0f || input.mUnknown16 != 0.0f) {
        float y = input.mUnknown16;
        float ax = fabsf(x);
        float ay = fabsf(y);
        if (ax > ay) {
            if (ax > lbl_803EACB0) {
                result = p->mUnknown2923[x > 0.0f ? 1 : 3];
                fn_80156C78(20, 1);
            }
        } else if (ay > lbl_803EACB0) {
            result = p->mUnknown2923[y > 0.0f ? 0 : 2];
            fn_80156C78(20, 1);
        }
    }
    return result;
}

extern "C" unsigned char fn_800D0550(void)
{
    unsigned int i = fn_802372EC(0, 4);

    if (i > 3) {
        i = 3;
    }
    return lbl_803EACAC[i];
}

extern "C" void fn_800D058C(Object_80039F5C *p)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;

    if (pBlock->mUnknown0 == 2) {
        if (pBlock->mUnknown5 == 0) {
            if (fn_800CA5CC(p, 6, 1)) {
                pBlock->mUnknown5 = 1;
            }
        } else if (!fn_800CA5CC(p, 6, 1)) {
            pBlock->mUnknown5 = 0;
        }
    }
    if (p == fn_80137B40()) {
        int active = pBlock->mUnknown0 == 2;
        unsigned char mode;

        fn_800D0660(p, &mode);
        if (pBlock->mUnknown0 == 2) {
            fn_800D5A6C(active, 2, pBlock->mUnknown4);
        }
    }
    fn_800A3B58(p, 6, 0);
}

extern "C" void fn_800D0660(Object_80039F5C *p, unsigned char *pOut)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;

    if (pBlock->mUnknown0 != 2) {
        return;
    }
    if (pBlock->mUnknown5) {
        *pOut = 21;
    } else {
        *pOut = 20;
    }
}

extern "C" int fn_800D0694(Object_80039F5C *p)
{
    int result = 0;
    Object_800B26B0 *pMotion = &p->mMotion;
    fn_80177FE0();
    Block_800D0B90 *pBlock = &p->mUnknown1228;
    unsigned char enable = 0;
    int held = 0;
    unsigned char id = p->mpState->mId;

    if ((id == 1 || id == 91) && p == fn_80137B40()) {
        int c = p->mUnknown528.mUnknown15;
        int special = 0;
        if (c <= 21) {
            special = c >= 20;
        }
        if (p->mFlags & 0x4000) {
            Input_800B6D34 input;
            fn_800B6D34(p, &input);
            if (input.mUnknown96 & 1) {
                enable = 2;
            }
            if (enable) {
                result = 1;
                if (enable == 2) {
                    if (special) {
                        unsigned char value = fn_800D0474(p);
                        if (value != pBlock->mUnknown4) {
                            if (!fn_800D0D1C(p)) {
                                pBlock->mUnknown11 = lbl_803EACAB;
                            }
                            pBlock->mUnknown10 = value;
                        } else if (!fn_800D0D1C(p)) {
                            pBlock->mUnknown4 = value;
                        }
                    } else {
                        pBlock->mUnknown4 = fn_800D0550();
                        pBlock->mUnknown4 = fn_800D0474(p);
                    }
                    pBlock->mUnknown0 = 2;
                    pBlock->mUnknown8 = p->mpState->mId;
                }
                pBlock->mUnknown5 = 0;
                p->mFlags |= 0x4000;
                if (!special) {
                    fn_80067E3C(39, &p->mMotion.mPos, p->mId, 0, 0, 0);
                }
            } else {
                pBlock->mUnknown0 = 0;
                pBlock->mUnknown9 = 255;
                pBlock->mUnknown11 = 0;
                pBlock->mUnknown8 = 0;
            }
        } else {
            float distance;
            if (fn_801486A0() == 2 && fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, 7, 0x471C72, &distance, 0)) {
                return 0;
            }
            if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                int ok = 0;
                if (special || (pMotion->mUnknown28 != 0.0f && fn_801CFFD0(pMotion->mUnknown32, 0x400000) <= 0x3FFFFF)) {
                    ok = 1;
                }
                enable = ok & fn_801783AC(0);
                if (fn_801486A0() == 0) {
                    enable = 1;
                }
                if (enable) {
                    int state;
                    unsigned char value;
                    float range = fn_80124FE0(p, 6);
                    switch (p->mUnknown528.mUnknown15) {
                    case 21:
                        p->mUnknown528.mUnknown15--;
                        held = 1;
                    case 20:
                        state = pBlock->mUnknown0;
                        special = 1;
                        value = pBlock->mUnknown4;
                        break;
                    default:
                        if (p->mUnknown528.mUnknown15 == 1) {
                            held = 1;
                        }
                        state = 2;
                        value = fn_800D0550();
                        break;
                    }
                    if (special) {
                        if (!(range < lbl_803EACB4 * lbl_803EACB8)) {
                            enable = 0;
                            if (fn_800ABDA4(p->mIdBytes[2]) == 0) {
                                enable = fn_802372EC(0, 100) < lbl_803EACBC;
                            }
                        }
                    } else if (!(range < lbl_803EACB4)) {
                        enable = 0;
                    }
                    if (enable) {
                        if (state == 2) {
                            pBlock->mUnknown4 = value;
                        }
                        if (held) {
                            pBlock->mUnknown5 = 1;
                        } else {
                            pBlock->mUnknown5 = 0;
                        }
                        pBlock->mUnknown0 = state;
                        pBlock->mUnknown8 = p->mpState->mId;
                        if (!special) {
                            fn_80067E3C(39, &p->mMotion.mPos, p->mId, 0, 0, 0);
                        }
                    }
                }
                if (!enable) {
                    pBlock->mUnknown0 = 0;
                    pBlock->mUnknown8 = 0;
                    pBlock->mUnknown9 = 255;
                }
            }
        }
    }
    return result;
}

extern "C" void fn_800D0A38(void)
{
    for (unsigned char team = 0; team <= 1; team++) {
        unsigned int count = fn_80178D18(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, i);
            Block_800D0B90 *pBlock = &pPlayer->mUnknown1228;
            if (pBlock->mUnknown11 != 0) {
                if (--pBlock->mUnknown11 == 0 && pBlock->mUnknown0 == 2) {
                    pBlock->mUnknown4 = pBlock->mUnknown10;
                }
            }
            if (pPlayer->mpState->mId != pBlock->mUnknown8) {
                pBlock->mUnknown0 = 0;
                pBlock->mUnknown8 = 0;
                pBlock->mUnknown9 = 255;
                pBlock->mUnknown11 = 0;
            }
        }
    }
}

extern "C" void fn_800D0B08(void)
{
    for (unsigned char team = 0; team <= 1; team++) {
        unsigned int count = fn_80178D18(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, i);
            Block_800D0B90 *pBlock = &pPlayer->mUnknown1228;
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown8 = 0;
            pBlock->mUnknown9 = 255;
            pBlock->mUnknown11 = 0;
        }
    }
}

extern "C" int fn_800D0B90(Object_80039F5C *p)
{
    return p->mUnknown1228.mUnknown0;
}

extern "C" int fn_800D0B98(Object_80039F5C *p)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;

    if (!fn_800D0D1C(p)) {
        unsigned char id = p->mpState->mId;
        if (id == 1 || id == 91) {
            return pBlock->mUnknown4;
        }
    }
    return 32;
}

extern "C" void fn_800D0BF4(Object_80039F5C *p, int a, int b)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;

    pBlock->mUnknown0 = a;
    pBlock->mUnknown8 = b;
    pBlock->mUnknown9 = 255;
}

extern "C" void fn_800D0C0C(Object_80039F5C *p, int a)
{
    unsigned char value = 255;

    if (p) {
        Block_800D0B90 *pBlock = &p->mUnknown1228;
        if (a != 0) {
            value = a - 1;
        }
        switch (p->mpState->mId) {
        case 12:
            if (fn_800D0B90(p) != 4) {
                fn_800D5F1C(p, fn_800D0B90(p), value);
            }
            break;
        case 36:
            fn_800D60BC(p, fn_800D0B90(p), value);
            break;
        case 34:
            fn_800D5054(p, fn_800D0B90(p));
            break;
        case 35:
            fn_800D5494(p, fn_800D0B90(p), value);
            break;
        }
        pBlock->mUnknown9 = value;
    }
}

extern "C" void fn_800D0D00(Object_80039F5C *p)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;

    pBlock->mUnknown0 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown9 = 255;
}

extern "C" int fn_800D0D1C(Object_80039F5C *p)
{
    Block_800D0B90 *pBlock = &p->mUnknown1228;
    int result = 0;

    if (pBlock->mUnknown0 == 2 && pBlock->mUnknown11 != 0) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800D0D48(void)
{
}
