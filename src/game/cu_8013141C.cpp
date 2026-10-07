#include <math.h>
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"

struct Control_80132090 {
    int mUnknown0;
    float mValues[8];
    float mUnknown36;
    float mUnknown40;
    int mUnknown44;
    unsigned char mUnknown48;
    signed char mUnknown49;
    char mUnknown50[2];
    unsigned char mUnknown52;
    char mUnknown53[3];
    char mUnknown56[8];
    int mUnknown64;
    int mUnknown68;
    int mUnknown72;
    int mUnknown76;
    unsigned char mUnknown80;
    unsigned char mUnknown81;
    char mUnknown82[6];
};

struct Input_800B6D34 {
    char mUnknown0[93];
    unsigned char mUnknown93;
    char mUnknown94[1];
    unsigned char mUnknown95;
    unsigned char mUnknown96;
    char mUnknown97[7];
};

struct Record_80163E94 {
    char mUnknown0[11];
    unsigned char mUnknownB;
};

extern "C" {
unsigned char *fn_8003AB38(Object_80039F5C *p);
void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
void fn_800B76E8(Object_80039F5C *p);
void fn_800B7CA4(Object_80039F5C *p);
void fn_800B8344(Object_80039F5C *p);
void fn_800D058C(Object_80039F5C *p);
void fn_800D0660(Object_80039F5C *p, unsigned char *pOut);
int fn_800D0694(Object_80039F5C *p);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800D5998(void);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_801067D8(Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
void fn_8011E1BC(Object_80039F5C *p, int a, int b, int c);
void fn_8011E3EC(Object_80039F5C *p, int a);
void fn_8011F45C(int a);
int fn_801231E4(Object_80039F5C *p, int angle);
void fn_8012430C(float *pOut, int kind, Object_80039F5C *p);
int fn_801243E0(float *pValues, int a);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, int a, unsigned char count, float *pOut, int b);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
float fn_8012506C(Object_80039F5C *p, int kind);
int fn_8012510C(float *pValues);
void fn_8012DDCC(Object_80039F5C *p, Control_80132090 *pControl, int a);
void fn_8012F5A0(Object_80039F5C *p, int a, void *pBlock);
void fn_8012F89C(Object_80039F5C *p, Control_80132090 *pControl, int a);
int fn_8012FA64(Object_80039F5C *p);
void fn_80130338(Object_80039F5C *p, Control_80132090 *pControl);
int fn_80132630(Object_80039F5C *p, Vector_80039F5C *pPos, int a);
void fn_8013FA8C(int a);
void fn_80148108(int mode);
Record_80163E94 *fn_80163E94(Object_800670B4 *pObject, unsigned int index, void *pArg);
Object_800670B4 *fn_80168708(int team);
Point_8017886C fn_80177FE0(void);
int fn_80178308(void);
float fn_80178A08(void);
float fn_80178A2C(void);
int fn_801783AC(int bit);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802276E8(Point_8017886C *pA, Point_8017886C *pB);
float fn_80237260(int stream);
}

extern float lbl_803ECB08;

static float lbl_802DB074[2][8] = {
    {20.0f, 12.0f, 3.0f, 0.0f, -1.0f, 3.0f, 30.0f, 25.0f},
    {-1.0f, 0.0f, 3.0f, 12.0f, 20.0f, 25.0f, 30.0f, 5.0f},
};

static float lbl_802DB0B4[2][8] = {
    {-8.0f, -2.0f, -9.0f, -2.0f, 10.0f, 20.0f, 30.0f, 20.0f},
    {10.0f, -2.0f, -9.0f, -2.0f, -8.0f, 20.0f, 30.0f, 20.0f},
};

static int lbl_803EB140 = 0;

extern "C" int fn_8013141C(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;
    int result = 0;

    if (fn_80137C48(p) != 0 && pState->mUnknown4 == 18) {
        result = fn_801783AC(0) == 0;
    }
    return result;
}

extern "C" int fn_80131474(Object_80039F5C *p, int a, int b)
{
    int result = 0;

    if (a != 0) {
        result = 1;
    } else {
        switch (b) {
        case 0:
        case 1:
            if (fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX) > 3.0f) {
                result = 1;
            } else {
                int behind = 0;

                if (fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX) > 1.0f) {
                    behind = p->mMotion.mPos.mY < fn_80177FE0().mY - 5.0f;
                }
                if (behind) {
                    result = 1;
                }
            }
            break;
        }
    }
    return result;
}

extern "C" void fn_80131554(Object_80039F5C *p, int index, int side, float *pValues)
{
    float *pA = 0;
    float *pB = 0;
    int i;

    fn_8012430C(pValues, 3, p);
    if (fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX) < 7.0f) {
        pA = lbl_802DB074[index];
    }
    if (fn_80131474(p, side, index)) {
        pB = lbl_802DB0B4[index];
    }
    for (i = 0; i < 8; i++) {
        if (pA != 0) {
            pValues[i] += pA[i];
        }
        if (pB != 0) {
            pValues[i] += pB[i];
        }
    }
}

extern "C" int fn_8013164C(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Object_80039F5C *pFound;
    Point_8017886C delta;
    int result = 1;

    if (fn_80124714(pOther, p, &pFound) == 0 && pFound->mIdBytes[2] == p->mIdBytes[2]) {
        result = 0;
    }
    if (result) {
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mFacing) > 0x400000) {
            result = 0;
        }
    }
    return result;
}

extern "C" Object_80039F5C *fn_801316F0(Object_80039F5C *p, int angle, float maxA, float maxB)
{
    float distance;
    Object_80039F5C *pOther =
        fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), angle, &distance, 1);

    if (pOther != 0) {
        if (distance > maxA || !fn_8013164C(p, pOther)) {
            pOther = 0;
        }
    }
    if (pOther == 0) {
        pOther = fn_801244F0(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), &distance, 1);
        if (distance > maxB || !fn_8013164C(p, pOther)) {
            pOther = 0;
        }
    }
    return pOther;
}

extern "C" int fn_801317F8(Object_80039F5C *p, Control_80132090 *pControl)
{
    int result = 0;

    if (p == fn_80137B40()) {
        Object_80039F5C *pTarget = fn_8009BCE8(&pControl->mUnknown64);
        float own = fn_8012506C(p, 3);
        float target = fn_8012506C(pTarget, 3);
        Object_80039F5C *pOther;

        if (pControl->mUnknown81 == 0 && own < 42.0f && fn_801316F0(p, 0x200000, 5.5f, 0.0f) != 0 &&
            fn_801066D0(p, pTarget, 9) && fn_80132630(p, 0, 0)) {
            float rating = p->mRatings[6] / 255.0f;
            float chance;

            rating *= 0.5f;
            chance = rating * 0.08f + 0.02f;

            if (fn_80237260(0) <= chance && fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0x4E38E2) {
                result = 5;
            }
        }

        pOther = fn_801316F0(p, 0x400000, 2.5f, 1.5f);
        if (pOther != 0) {
            Point_8017886C toOther;
            Point_8017886C toTarget;

            fn_80227690(&toOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
            fn_80227690(&toTarget, &pTarget->mMotion.mPos, &p->mMotion.mPos);
            if (fn_802276E8(&toOther, &toTarget) > 0.0f) {
                result = 4;
            } else if (target < 30.0f && fn_801066D0(p, pTarget, 9) &&
                       fn_80132630(p, &pTarget->mMotion.mPos, 0)) {
                result = 2;
            }
        } else {
            int deep = 0;
            Point_8017886C spot;
            float limit;

            spot = fn_80177FE0();
            limit = fn_80178A2C() - 5.0f;
            if (spot.mY < limit && fn_8013141C(p)) {
                deep = own < 12.0f;
            }
            if (deep) {
                result = 6;
            } else if (own > 65.0f) {
                if (target < 30.0f && fn_801066D0(p, pTarget, 9) &&
                    fn_80132630(p, &pTarget->mMotion.mPos, 0)) {
                    result = 2;
                } else if (fn_801CFFD0(fn_801231E4(p, 0x400000), 0x400000) <= 0x71C70) {
                    result = 4;
                }
            }
        }
    } else {
        result = 1;
        if (pControl->mUnknown76 <= 0) {
            result = 3;
        }
    }
    return result;
}

extern "C" int fn_80131B3C(Object_80039F5C *p, int kind, int arg)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;
    Object_80039F5C *pTarget = fn_8009BCE8(&pControl->mUnknown64);
    int result = 0;
    Object_80039F5C *pBall = fn_80137B40();

    if (pBall == p) {
        if (fn_80105E90(pBall, pTarget, kind)) {
            Message_800F01CC message;

            result = 1;
            fn_800D0BF4(pBall, arg, 25);
            fn_801C1F94(&message, 0, 4);
            message.mId = 25;
            message.mUnknown1[0] = pTarget->mIdBytes[1];
            message.mUnknown1[1] = kind;
            fn_800F00D4(0, pBall->mpState, &message, pBall);
        }
        if (kind == 9) {
            if (pControl->mUnknown68 == 0) {
                fn_8011F45C(13);
            } else {
                fn_8011F45C(12);
            }
        }
    }
    return result;
}

extern "C" void fn_80131C1C(Object_80039F5C *p, float *pValues, Control_80132090 *pControl)
{
    int angle;

    pControl->mUnknown52 = 1;
    pControl->mUnknown40 = 1.0f;
    angle = fn_8012510C(pValues);
    pControl->mUnknown44 = angle;
    pControl->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
    if (pControl->mUnknown76 <= 0 && pControl->mUnknown49 <= 0) {
        pControl->mUnknown49--;
        if ((angle & 0xFFFFFF) <= 0x7FFFFF) {
            angle = fn_801231E4(p, angle);
            pControl->mUnknown44 = angle;
            pControl->mUnknown48 = ((angle + 0x100000) >> 21) & 7;
        }
        fn_8012DDCC(p, pControl, 0);
        pControl->mUnknown0 = fn_8012FA64(p);
        fn_8012F89C(p, pControl, 0);
        fn_800D0694(p);
    }
    fn_800D058C(p);
    fn_800D0660(p, &pControl->mUnknown52);
    p->mUnknown512.mUnknown15 = pControl->mUnknown52;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = pControl->mUnknown44;
    p->mUnknown512.mUnknown4 = pControl->mUnknown44;
    p->mUnknown512.mUnknown0 = pControl->mUnknown40;
    fn_8012F5A0(p, 0, pControl->mUnknown56);
}

extern "C" void fn_80131D48(Object_80039F5C *p, float *pValues, Control_80132090 *pControl)
{
    pControl->mUnknown44 = fn_801243E0(pValues, -1) << 21;
    pControl->mUnknown40 = 0.72f;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = pControl->mUnknown44;
    p->mUnknown512.mUnknown4 = pControl->mUnknown44;
    p->mUnknown512.mUnknown0 = pControl->mUnknown40;
}

extern "C" void fn_80131DB4(Object_80039F5C *p, int a, int b)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    message.mId = 1;
    fn_800F053C(0, p->mpState, &message, p);
}

extern "C" void fn_80131E08(Object_80039F5C *p)
{
    Message_800F01CC message;

    fn_8011E1BC(p, 0, 0, 1);
    fn_8011E3EC(p, 2);
    fn_801C1F94(&message, 0, 4);
    message.mId = 33;
    message.mUnknown1[0] = 0;
    fn_800F053C(0, p->mpState, &message, p);
}

extern "C" void fn_80131E80(Object_80039F5C *p)
{
    fn_8013FA8C(2);
}

extern "C" int fn_80131EA4(Object_80039F5C *p, Control_80132090 *pControl)
{
    int result;

    fn_8009BCE8(&pControl->mUnknown64);
    result = fn_80178A08() - fabsf(p->mMotion.mPos.mX) < 1.5f;
    switch (pControl->mUnknown68) {
    case 0:
        if (p->mMotion.mPos.mX > fn_80177FE0().mX) {
            if (p->mMotion.mFacing < 0x400000 || p->mMotion.mFacing > 0xC00000) {
                result = 1;
            }
        }
        break;
    case 1:
        if (p->mMotion.mPos.mX < fn_80177FE0().mX) {
            if (p->mMotion.mFacing > 0x400000 && p->mMotion.mFacing < 0xC00000) {
                result = 1;
            }
        }
        break;
    }
    return result;
}

extern "C" int fn_80131F90(Object_80039F5C *p, int a)
{
    float y = p->mMotion.mPos.mY;
    int result = 1;
    float spotY = fn_80177FE0().mY;

    if (y > spotY + 10.0f) {
        result = 0;
    } else if (y > spotY + 5.0f) {
        if (p->mMotion.mFacing > 0x200000 && p->mMotion.mFacing < 0x600000) {
            result = 0;
        }
    }
    if (fn_80137B40() != p) {
        result = 0;
    }
    return result;
}

extern "C" void fn_80132038(Object_80039F5C *p, Control_80132090 *pControl)
{
    Object_80039F5C *pTarget = fn_8009BCE8(&pControl->mUnknown64);

    if (pTarget != 0) {
        Point_8017886C delta;

        fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
        fn_801CFE40(delta.mY, delta.mX);
    }
}

extern "C" int fn_80132090(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;

    pControl->mUnknown68 = p->mpState->mUnknown1;
    pControl->mUnknown64 = 1 | p->mIdBytes[2] << 8 | p->mpState->mUnknown2 << 16;
    pControl->mUnknown80 = 1;
    pControl->mUnknown72 = 0;
    pControl->mUnknown81 = p->mpState->mUnknown3[0];
    fn_80130338(p, pControl);
    if (p == fn_80137B40()) {
        pControl->mUnknown76 = 10;
        lbl_803EB140 = 0;
    } else {
        pControl->mUnknown76 = 20;
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown15 = 10;
    p->mUnknown528.mUnknown15 = 10;
    p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
    p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
    p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
    return 0;
}

extern "C" int fn_80132164(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;

    p->mpState->mUnknown3[0] = pControl->mUnknown81;
    return 1;
}

extern "C" int fn_8013217C(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;
    int done = 0;

    fn_800B8344(p);
    if (fn_8010A2DC(p, 0, -1)) {
        return 0;
    }
    fn_80131554(p, pControl->mUnknown68, pControl->mUnknown81, pControl->mValues);
    if (pControl->mUnknown76 > 0) {
        Object_80137ABC *pBall = fn_80137C48(p);

        if (!(p->mFlags & 0x4000) || pBall == 0) {
            if (pBall != 0) {
                pControl->mUnknown72 = 0;
                fn_80131C1C(p, pControl->mValues, pControl);
            } else {
                pControl->mUnknown72 = 1;
                fn_80131D48(p, pControl->mValues, pControl);
            }
        }
        pControl->mUnknown76--;
    } else if (fn_80131EA4(p, pControl)) {
        if (!fn_8013141C(p)) {
            fn_80131DB4(p, pControl->mUnknown68, pControl->mUnknown80);
        }
        done = 1;
    } else if (!(p->mFlags & 0x4000)) {
        pControl->mUnknown72 = fn_801317F8(p, pControl);
        switch (pControl->mUnknown72) {
        case 5:
            pControl->mUnknown81 = 1;
            fn_80131B3C(p, 10, 0);
            break;
        case 2:
            if (fn_80131B3C(p, 9, fn_801067D8(p))) {
                break;
            }
        case 0:
            fn_80131C1C(p, pControl->mValues, pControl);
            break;
        case 1:
            fn_80131D48(p, pControl->mValues, pControl);
            break;
        case 4:
            fn_80131DB4(p, pControl->mUnknown68, pControl->mUnknown80);
            done = 1;
            break;
        case 3:
            fn_80131E08(p);
            done = 1;
            break;
        case 6:
            fn_80131E80(p);
            done = 1;
            break;
        }
    } else if (fn_800D0694(p)) {
        unsigned char mode;

        fn_800D058C(p);
        fn_800D0660(p, &mode);
        p->mUnknown512.mUnknown15 = mode;
    }

    if (!done) {
        if (pControl->mUnknown80 != 0 && fn_80131F90(p, pControl->mUnknown68)) {
            if (p->mUnknown512.mUnknown15 != 20 && p->mUnknown512.mUnknown15 != 21) {
                if (fn_80137C48(p) != 0) {
                    fn_80132038(p, pControl);
                }
                if (p->mUnknown512.mUnknown15 == 1 || p->mUnknown512.mUnknown15 == 11) {
                    p->mUnknown512.mUnknown15 = 11;
                } else {
                    p->mUnknown512.mUnknown15 = 10;
                }
            }
        } else {
            pControl->mUnknown80 = 0;
        }
    }
    return done;
}

extern "C" int fn_80132440(Object_80039F5C *p)
{
    Control_80132090 *pControl = (Control_80132090 *)&p->mUnknown336;
    int result = 0;
    int flag = 0;

    if (pControl->mUnknown80 == 0) {
        if (*fn_8003AB38(p) == 57) {
            fn_800B7CA4(p);
        } else {
            fn_800B76E8(p);
        }
    } else {
        Input_800B6D34 input;

        fn_800B6D34(p, &input);
        if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10)) {
            flag = 1;
        }
        if (fn_8013141C(p) && (input.mUnknown93 & 0x40)) {
            result = 1;
            fn_80148108(0);
            fn_80131E80(p);
        }
        if (!result) {
            if (input.mUnknown95 & 0x40) {
                if (fn_80131B3C(p, 9, flag)) {
                    p->mFlags |= 0x4000;
                }
            } else if (input.mUnknown96 & 8) {
                if (fn_80131B3C(p, 10, 0)) {
                    p->mFlags |= 0x4000;
                    fn_800D5998();
                }
            } else if (*fn_8003AB38(p) == 57) {
                fn_800B7CA4(p);
            } else {
                fn_800B76E8(p);
            }
        }
    }
    return result;
}

extern "C" void fn_8013258C(Object_80039F5C *p)
{
    unsigned char i;
    Object_800670B4 *pObject;
    unsigned int count;

    switch (p->mIdBytes[1]) {
    case 0:
        p->mIdBytes[1] = 1;
        break;
    case 1:
        p->mIdBytes[1] = 0;
        break;
    }
    i = 0;
    pObject = fn_80168708(fn_80178308());
    count = fn_80178D18(fn_80178308());
    for (; i < count; i++) {
        if (fn_80163E94(pObject, i, 0)->mUnknownB == p->mIdBytes[2]) {
            p->mIdBytes[2] = i;
            break;
        }
    }
}
