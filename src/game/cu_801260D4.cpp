#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Team_80167A8C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

/* Partial overlay of the opaque player block at +336. */
struct State_801297F8 {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    signed char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    unsigned char mUnknown16;
    char mUnknown17[3];
    char mUnknown20[20];
    unsigned char mUnknown40;
    unsigned char mUnknown41;
    unsigned char mUnknown42;
};

/* Object whose +12 word table is indexed by the player's +1 byte. */
struct Context_8012886C {
    unsigned char *mpUnknown0;
    unsigned char *mpUnknown4;
    char mUnknown8[4];
    int *mpUnknown12;
    short mUnknown16;
};

extern "C" {
void fn_8009A8D4(void *p);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int fn_800D0B90(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_80110C10(Object_80039F5C *p);
int fn_80110C68(Object_80039F5C *p);
void fn_80111354(Object_80039F5C *p);
int fn_80112C04(Object_80039F5C *p, Object_80137ABC *pBall, int *pAngle, float *pValue);
unsigned int fn_8011E188(void);
int fn_8011F1A4(void);
int fn_8011F32C(void);
unsigned int fn_8011F4C8(void);
int fn_80125F3C(short *pRatings);
int fn_80125FA0(Object_80039F5C *p);
int fn_801260D4(Object_80039F5C *p);
Object_80039F5C *fn_80128B60(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801486A0(void);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
int fn_801783AC(int bit);
int fn_801787A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A5C(void);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_8022710C(void *pV);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" unsigned int lbl_802DB04C[4];
extern "C" unsigned int lbl_803EB0D4;
extern "C" unsigned char lbl_803EB0D8;
extern "C" float lbl_803EB0E0;
extern "C" float lbl_803EB0E4;
extern "C" float lbl_803EB0E8;
extern "C" unsigned char lbl_803EB0EC;
extern "C" unsigned char lbl_803EB0ED;
extern "C" short lbl_803EB0EE;
extern "C" short lbl_803EB0F0;
extern "C" short lbl_803EB0F2;
extern "C" short lbl_803EB0F4;
extern "C" float lbl_803EB0F8;
extern "C" float lbl_803EB0FC;
extern "C" float lbl_803EB100;
extern "C" float lbl_803EB104;
extern "C" float lbl_803EB108;
extern "C" float lbl_803EB10C;
extern "C" unsigned char lbl_803EB110;
extern "C" float lbl_803EB114;
extern "C" float lbl_803ECB08;

extern "C" unsigned int fn_8012623C(Object_80039F5C *p)
{
    unsigned int value = lbl_803EB0D4;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, lbl_802DB04C[i], 0) != 0xFFFF) {
            value >>= 1;
            break;
        }
    }
    return value;
}

extern "C" void fn_80126DD4(Object_80039F5C *p, State_801297F8 *pState, float distance, Object_80039F5C *pOther)
{
    if (p->mUnknown1032 != 4 && pOther != 0 && distance < 4.0f && fn_801BE648(pOther->mpUnknown792) != 69
        && fn_801BE648(pOther->mpUnknown792) != 178
        && (fn_801CFFD0(p->mMotion.mFacing, pOther->mMotion.mFacing) > 0x355555 || fn_800DC080(pOther) != 0)) {
        Point_80167910 delta;
        int angle;

        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(angle, pOther->mMotion.mUnknown32) <= 0x1FFFFF) {
            float scale;

            pState->mUnknown16 = 12;
            scale = 0.65f;
            scale += distance * ((0.7f - 0.65f) / 4.0f);
            scale = CLAMP(scale, 0.0f, 1.0f);
            if (pState->mUnknown0 > scale) {
                pState->mUnknown0 = scale;
            }
        } else if (pState->mUnknown12 == (255 - p->mRatings[5]) >> 4) {
            angle += 0x800000;
            angle &= 0xFFFFFF;
            if (!(p->mFlags & 0x4000) && fn_800DC080(pOther) != 0
                && fn_801CFFD0(p->mMotion.mFacing, pOther->mMotion.mUnknown32) <= 0x1FFFFF) {
                int diff;

                pState->mUnknown16 = 1;
                diff = fn_801CFFD0(angle, pState->mUnknown8);
                if (((angle - pState->mUnknown8) & 0xFFFFFF) > 0x800000) {
                    pState->mUnknown8 -= diff / 2;
                } else {
                    pState->mUnknown8 += diff / 2;
                }
                pState->mUnknown8 &= 0xFFFFFF;
            }
        }
    }
}

extern "C" int fn_80126FD8(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState, Context_8012886C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Point_80167910 delta;
    int target;
    int diff;
    int turn;

    fn_80227690(&delta, &pos, pMotion);
    target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    diff = fn_801CFFD0(angle, target);
    if (pMotion->mPos.mY < pos.mY || distance > 5.5f
        || (pOther != 0 && (pOther->mUnknown528.mUnknown15 == 1 || pOther->mUnknown528.mUnknown15 == 5))) {
        pState->mUnknown16 = 1;
        switch (p->mUnknown2914) {
        case 10:
        case 11:
        case 12: {
            int flag = 0;
            if (pos.mY > fn_80177FE0().mY) {
                flag = fn_8013BA58(fn_801374BC(), 0) == 4;
            }
            if (flag != 0) {
                pState->mUnknown16 = 0;
            }
            break;
        }
        }
        if (pOther != 0 && pContext->mpUnknown12[p->mIdBytes[1]] == 5) {
            if (((angle - target) & 0xFFFFFF) > 0x800000) {
                angle = (angle + diff / 4) & 0xFFFFFF;
            } else {
                angle = (angle - diff / 4) & 0xFFFFFF;
            }
        }
    }
    turn = 0;
    if (pOther != 0) {
        if (pMotion->mPos.mY < fn_80177FE0().mY) {
            if ((pOther->mFlags & 0x200000) || fn_800DC080(pOther) != 0) {
                turn = 1;
            }
        }
    }
    if (turn != 0) {
        if (distance > 3.0f) {
            pState->mUnknown16 = 1;
        }
        if (!(pOther->mFlags & 0x8000) || fn_801BE648(pOther->mpUnknown792) == 69
            || fn_801BE648(pOther->mpUnknown792) == 178) {
            pState->mUnknown16 = 1;
            if (((angle - target) & 0xFFFFFF) > 0x800000) {
                angle = (angle + diff / 2) & 0xFFFFFF;
            } else {
                angle = (angle - diff / 2) & 0xFFFFFF;
            }
        }
        if (fn_801CFFD0(target, pMotion->mFacing) > 0x11C71C) {
            pState->mUnknown16 = 0;
        }
    }
    if (pOther != 0 && pMotion->mPos.mY < pos.mY && fn_801CFFD0(angle2, 0xC00000) <= 0x271C70) {
        fn_80227690(&delta, &pos, pMotion);
        target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        diff = fn_801CFFD0(angle, target);
        if (((angle - target) & 0xFFFFFF) > 0x800000) {
            angle = (angle + diff / 2) & 0xFFFFFF;
        } else {
            angle = (angle - diff / 2) & 0xFFFFFF;
        }
    }
    return angle;
}

extern "C" void fn_80127324(Object_80039F5C *p, int *pAngle, Vector_80039F5C pos, int angle2)
{
    if (fn_801783AC(0) == 0 && fn_8011F1A4() != 0 && fn_8011F4C8() > 3
        && ((fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) == 0 && fn_801CFFD0(*pAngle, 0) <= 0x3FFFFF)
            || (fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) && fn_801CFFD0(*pAngle, 0) > 0x400000))) {
        Point_8017886C point;

        point = fn_80177FE0();
        if (fabsf(point.mX - p->mMotion.mPos.mX) < 5.0f && p->mMotion.mPos.mY - point.mY < 5.0f && pos.mY < point.mY
            && pos.mY > point.mY - 10.0f && fn_801CFFD0(angle2, 0x400000) <= 0x5FFFFF) {
            if (fn_801CFFD0(*pAngle, 0) <= 0x3FFFFF) {
                if ((*pAngle & 0xFFFFFF) > 0x400000) {
                    *pAngle = 0;
                }
            } else if ((*pAngle & 0xFFFFFF) > 0x800000) {
                *pAngle = 0x800000;
            }
        }
    }
}

extern "C" int fn_801274D4(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState, Context_8012886C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    int mode = fn_801486A0();
    Object_800B26B0 *pMotion = &p->mMotion;

    if (pOther != 0) {
        int turn = 0;
        Point_80167910 delta;

        if ((distance > 3.0f && pMotion->mPos.mY < fn_80177FE0().mY && fn_800DC080(pOther) != 0 && mode != 2)
            || (mode == 2 && distance < 8.0f)) {
            turn = 1;
        }
        if (turn != 0) {
            int target;
            int diff;

            fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
            target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            diff = fn_801CFFD0(angle, target);
            if (((angle - target) & 0xFFFFFF) > 0x800000) {
                angle = (angle + diff / 2) & 0xFFFFFF;
            } else {
                angle = (angle - diff / 2) & 0xFFFFFF;
            }
            pState->mUnknown16 = 1;
        } else {
            if (pos.mY < fn_80177FE0().mY + 3.0f && pContext->mpUnknown4[0] != p->mIdBytes[1]
                && pContext->mpUnknown4[pContext->mUnknown16 - 1] != p->mIdBytes[1]) {
                fn_80127324(p, &angle, pos, angle2);
            }
            if (pMotion->mPos.mY < pos.mY || distance > 5.5f || pOther->mUnknown528.mUnknown15 == 1
                || pOther->mUnknown528.mUnknown15 == 5 || fn_801CFFD0(angle, pMotion->mFacing) <= 0x11C71B) {
                pState->mUnknown16 = 1;
            }
            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0xC00000) <= 0x1FFFFF) {
                fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
                angle = fn_801CFE40(delta.mY, delta.mX);
                pState->mUnknown16 = 0;
            }
        }
    }
    return angle;
}

extern "C" int fn_80127758(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState, Context_8012886C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int done = 0;

    if (pOther != 0) {
        Point_80167910 delta;
        int target;
        int turn;
        int flag;
        float dy;

        if (distance > 5.5f && fn_8011F32C() != 0) {
            pState->mUnknown16 = 1;
        }
        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        turn = 0;
        target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        if (distance > 3.0f) {
            if (pMotion->mPos.mY < fn_80177FE0().mY + 2.0f) {
                if ((pOther->mFlags & 0x200000) || fn_800DC080(pOther) != 0) {
                    turn = 1;
                }
            }
        }
        if (turn != 0) {
            int diff = fn_801CFFD0(angle, target);
            if (((angle - target) & 0xFFFFFF) > 0x800000) {
                angle = (angle + diff / 2) & 0xFFFFFF;
            } else {
                angle = (angle - diff / 2) & 0xFFFFFF;
            }
            pState->mUnknown16 = 1;
            done = 1;
        }
        if (fabsf(pOther->mMotion.mPos.mX) > fabsf(pMotion->mPos.mX)) {
            pState->mUnknown16 = 1;
        }
        flag = 0;
        if (pOther->mpState->mId == 35 && fn_80110C68(pOther) != 0) {
            flag = 1;
        }
        dy = pMotion->mPos.mY - pOther->mMotion.mPos.mY;
        if (flag == 0 && done == 0 && dy > 1.0f) {
            float scale;
            if (dy > 35.0f) {
                dy = 35.0f;
            }
            scale = 1.0f - (35.0f - dy) / 35.0f;
            angle &= 0xFFFFFF;
            if (pMotion->mPos.mX > fn_80178A5C()) {
                angle = (angle + (int)(scale * (40.0f * 46603.38f))) & 0xFFFFFF;
            } else if (pMotion->mPos.mX >= -fn_80178A5C() && pMotion->mPos.mX > pOther->mMotion.mPos.mX) {
                angle = (angle + (int)(scale * (40.0f * 46603.38f))) & 0xFFFFFF;
            } else {
                angle = (angle - (int)(scale * (40.0f * 46603.38f))) & 0xFFFFFF;
            }
        }
    }
    if (done == 0 && fn_8011E188() < lbl_803EB0E0) {
        if ((pMotion->mPos.mX > 0.0f && fn_801CFFD0(angle, 0x800000) <= 0x3FFFFF)
            || (pMotion->mPos.mX < 0.0f && fn_801CFFD0(angle, 0) <= 0x3FFFFF)) {
            if (pMotion->mPos.mX > 0.0f) {
                angle = (int)(lbl_803EB0E8 * 46603.38f);
            } else {
                angle = (int)(lbl_803EB0E4 * 46603.38f);
            }
        }
    }
    return angle;
}

extern "C" int fn_80127AD0(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState, Context_8012886C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int turn;

    if (distance > 4.0f && distance < 12.0f && (pMotion->mFacing & 0xFFFFFF) > 0x800000
        && pMotion->mPos.mY > pos.mY && fabsf(p->mMotion.mPos.mX) < fabsf(pos.mX)
        && fabsf(p->mMotion.mPos.mX) < fn_80178A08() - 1.0f) {
        if (angle > 0xC00000) {
            angle -= fn_801CFFD0(0, angle) / 2;
        } else {
            angle += fn_801CFFD0(0x800000, angle) / 2;
        }
    }
    turn = 0;
    if (pOther != 0 && distance > 3.0f) {
        if (pMotion->mPos.mY < fn_80177FE0().mY + 2.0f) {
            if ((pOther->mFlags & 0x200000) || fn_800DC080(pOther) != 0) {
                turn = 1;
            }
        }
    }
    if (turn != 0) {
        Point_80167910 delta;
        int target;
        int diff;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        diff = fn_801CFFD0(angle, target);
        if (((angle - target) & 0xFFFFFF) > 0x800000) {
            angle = (angle + diff / 2) & 0xFFFFFF;
        } else {
            angle = (angle - diff / 2) & 0xFFFFFF;
        }
        pState->mUnknown16 = 1;
    }
    return angle;
}

extern "C" int fn_80127CD4(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState, Context_8012886C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    pState->mUnknown16 = 1;
    if (distance > 10.0f) {
        float width;
        float offset;
        float step;
        unsigned char i;
        Point_80167910 target;
        Point_80167910 dir;

        if (fabsf(pos.mX) > fn_80178A5C() * 2.0f) {
            width = fn_80178A08() * 0.85f;
            offset = fn_80178A08() - width;
            if (pos.mX < 0.0f) {
                offset = -offset;
            }
        } else {
            width = fn_80178A08();
            offset = 0.0f;
        }
        step = width / (fn_80178D18(p->mIdBytes[2]) / 2.0f);
        for (i = 0; i < pContext->mUnknown16 && pContext->mpUnknown0[i] != p->mIdBytes[1]; i++) {
        }
        if (i > pContext->mUnknown16 / 2) {
            i -= pContext->mUnknown16 / 2;
            target.mX = offset + (i * -step + step * 0.5f);
        } else {
            target.mX = offset + (width - i * step - step * 0.5f);
        }
        target.mY = pMotion->mPos.mY - 10.0f;
        fn_80227690(&dir, &target, pMotion);
        angle = fn_801CFE40(dir.mY, dir.mX);
        pState->mUnknown16 = 1;
    }
    return angle;
}

extern "C" void fn_80127EFC(Object_80039F5C *p, State_801297F8 *pState, Object_80039F5C *pOther, Context_8012886C *pContext,
                            int *pAngle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Point_80167910 delta;

    if (pOther != 0 && pMotion->mPos.mY > pos.mY && pContext->mpUnknown12[p->mIdBytes[1]] != 6
        && fn_801CFFD0(angle2, 0x400000) <= 0x31C71B && fabsf(p->mMotion.mPos.mX) < fabsf(pos.mX)
        && fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 1.0f) {
        fn_80227690(&delta, &pos, pMotion);
        if (p->mMotion.mPos.mX > 0.0f) {
            *pAngle -= fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), *pAngle) / 4;
        } else {
            *pAngle += fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), *pAngle) / 4;
        }
    }
    if (pOther != 0) {
        int turn = 0;

        switch (fn_801BE648(pOther->mpUnknown792)) {
        case 67:
        case 225:
        case 227:
            if (fn_801CFFD0(angle2, 0xC00000) <= 0x3FFFFF) {
                turn = 1;
            }
            break;
        }
        if (turn != 0) {
            int angle;
            int diff;

            fn_80227690(&delta, &pos, pMotion);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            diff = fn_801CFFD0(*pAngle, angle);
            if (((*pAngle - angle) & 0xFFFFFF) > 0x800000) {
                *pAngle = (*pAngle + diff / 2) & 0xFFFFFF;
            } else {
                *pAngle = (*pAngle - diff / 2) & 0xFFFFFF;
            }
        }
    }
    if (fabsf(pMotion->mPos.mX) > fn_80178A08()) {
        if (pMotion->mPos.mX > 0.0f) {
            if (*pAngle < 0x800000) {
                *pAngle = 0x600000;
            } else {
                *pAngle = 0xA00000;
            }
        } else {
            if (*pAngle < 0x800000) {
                *pAngle = 0x200000;
            } else {
                *pAngle = 0xE00000;
            }
        }
        pState->mUnknown16 = 0;
        pState->mUnknown0 = 1.0f;
    }
}

extern "C" int fn_801281A8(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int found = 0;
    int low = (int)(lbl_803EB0EC * 46603.38f);
    int high = (int)(lbl_803EB0ED * 46603.38f);
    Object_80039F5C *pCarrier = fn_80137B40();

    if (p != 0 && pCarrier != 0 && pCarrier->mMotion.mUnknown28 / lbl_803ECB08 > 0.14f) {
        int widen;
        int reach;
        int anim;

        if (p->mUnknown528.mUnknown15 == 4 || p->mUnknown528.mUnknown15 == 5) {
            widen = (int)(lbl_803EB0F2 * 46603.38f);
        } else {
            widen = 0;
        }
        if (p->mUnknown528.mUnknown15 == 4 || p->mUnknown528.mUnknown15 == 5) {
            reach = lbl_803EB0F4;
        } else {
            reach = 0;
        }
        anim = fn_801BE648(pCarrier->mpUnknown792);
        if (pCarrier != 0 && anim != 84 && anim != 69 && anim != 178 && anim != 77
            && (unsigned int)pCarrier->mMotion.mUnknown32 <= 0x800000) {
            Point_80167910 delta;
            int angle;
            float distance;

            fn_80227690(&delta, &p->mMotion.mPos, &pCarrier->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(pCarrier->mMotion.mUnknown32, 0) <= 0x3FFFFF) {
                low = (int)(low - (int)(lbl_803EB0F8 * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
                high = (int)(high - (int)(lbl_803EB0FC * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
            } else {
                low = (int)(low - (int)(lbl_803EB0FC * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
                high = (int)(high - (int)(lbl_803EB0F8 * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
            }
            distance = fn_8022710C(&delta);
            if (angle >= low - widen && angle <= high + widen && distance >= lbl_803EB0EE - reach
                && distance <= lbl_803EB0F0 + reach) {
                found = 1;
            }
        }
    }
    return found;
}

extern "C" void fn_80128590(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState)
{
    if (pState->mUnknown0 > 0.72f || pState->mUnknown16 == 1) {
        pState->mUnknown16 = 5;
    } else {
        pState->mUnknown16 = 4;
    }
}

extern "C" int fn_801285C8(Object_80039F5C *p, Object_80039F5C *pOther, State_801297F8 *pState)
{
    if (pOther != 0 && fn_801281A8(p, pOther) == 1) {
        fn_80128590(p, pOther, pState);
        return 1;
    }
    return 0;
}

extern "C" void fn_80128628(Object_80039F5C *p, State_801297F8 *pState, Object_80039F5C *pOther, int angle, int angle2,
                            float distance)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int diff = fn_801CFFD0(angle, pMotion->mFacing);
    Point_80167910 delta;

    if (diff > 0x177777) {
        if (pOther != 0 && !(pOther->mFlags & 0x200000) && fn_800DC080(pOther) == 0) {
            if (distance < 4.0f) {
                pState->mUnknown0 = fn_801CFB94(diff / 2) * 0.4f;
            } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
                float scale = 0.4f;
                scale += fn_801CFB94(fn_801CFFD0(pMotion->mFacing, angle2) / 2) * (0.72f - 0.4f);
                pState->mUnknown0 = scale * fn_801CFB94(diff / 2);
            }
        } else {
            pState->mUnknown0 = fn_801CFB94(diff / 2) * 0.72f;
        }
        pState->mUnknown16 = 0;
    }
    if (!(p->mFlags & 0x20000) && pOther != 0 && pOther->mpState->mId == 35 && distance < 5.0f
        && pMotion->mPos.mY > pOther->mMotion.mPos.mY
        && fn_801CFFD0(pOther->mMotion.mFacing, 0xC00000) <= 0x3C71C6) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (fn_801CFFD0(pMotion->mUnknown32, fn_801CFE40(delta.mY, delta.mX)) > 0x200000
            && fn_801CFFD0(pMotion->mUnknown32, pOther->mpState->mUnknown2 == 1 ? 0x800000 : 0) > 0x400000) {
            if (pState->mUnknown0 > 0.72f) {
                pState->mUnknown0 = 0.4f;
            }
            pState->mUnknown16 = 4;
        }
    }
}

extern "C" void fn_8012886C(Object_80039F5C *p, State_801297F8 *pState, Context_8012886C *pContext, int angle,
                            Vector_80039F5C pos, float distance, int angle2)
{
    Object_80039F5C *pOther = fn_80128B60();
    int kind = pContext->mpUnknown12[p->mIdBytes[1]];
    Object_80137ABC *pBall = fn_801374BC();

    pState->mUnknown16 = 0;
    pState->mUnknown0 = 1.0f;
    pState->mUnknown41 = fn_801260D4(p);
    switch (pState->mUnknown41) {
    case 1: {
        int newAngle;
        float value = pState->mUnknown0;
        fn_80112C04(p, pBall, &newAngle, &value);
        pState->mUnknown8 = newAngle & 0xFFFFFF;
        pState->mUnknown0 = value;
        break;
    }
    case 0:
        switch (kind) {
        case 0:
        case 5:
            angle = fn_80126FD8(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 2:
            angle = fn_801274D4(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 3:
            angle = fn_80127758(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 4:
            angle = fn_80127AD0(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 6:
            angle = fn_80127CD4(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 7:
            pState->mUnknown0 = 0.4f;
            break;
        }
        break;
    case 2:
        break;
    }
    if (pState->mUnknown41 != 1) {
        fn_80127EFC(p, pState, pOther, pContext, &angle, pos, distance, angle2);
        pState->mUnknown8 = angle & 0xFFFFFF;
        fn_80128628(p, pState, pOther, angle, angle2, distance);
    }
}

extern "C" Object_80039F5C *fn_80128B60(void)
{
    Object_80039F5C *p = fn_80137B40();

    if (p != 0) {
        if (p->mUnknown2914 == 0 && (p->mpState->mId == 25 || p->mpState->mId == 26)) {
            Object_80039F5C *pOther = fn_80137BEC();
            if (pOther != 0) {
                p = pOther;
            }
        }
    } else if (fn_8013BA58(fn_801374BC(), 0) == 3) {
        p = fn_80137BEC();
    }
    return p;
}

extern "C" void fn_80128BE0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_80170374 *pBlock = &p->mUnknown560;
    int found = 0;
    Object_80039F5C *pTarget;
    Point_80167910 delta;

    if (pBlock->mFlags.mBytes[0] != 1) {
        return;
    }
    switch (pBlock->mUnknown54) {
    case 0:
    case 5:
    case 7:
        break;
    default:
        return;
    }
    if (pOther == 0 || !(pOther->mFlags & 0x10000)) {
        return;
    }
    pTarget = fn_8009BCE8(&pBlock->mUnknown40);
    if (pTarget == pOther) {
        found = 1;
    } else {
        pTarget = fn_8009BCE8(&pBlock->mUnknown44);
        if (pTarget != 0 && (pTarget->mpState->mId == 17 || pTarget == pOther)) {
            found = 1;
        }
    }
    if (found == 0) {
        return;
    }
    if (fn_802372EC(0, 100) < 75) {
        fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pTarget->mMotion.mUnknown32) <= 0x3FFFFF) {
            fn_80111354(p);
        }
    } else if (fn_802372EC(0, 100) < 50) {
        fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pTarget->mMotion.mUnknown32) <= 0x3FFFFF) {
            fn_800E96EC(p, pTarget);
        }
    }
}

extern "C" int fn_80128D50(Object_80039F5C *p, State_801297F8 *pState)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier = fn_80137B40();
    int found = 0;
    int value = 0;
    Vector_80039F5C pos;

    if (pCarrier != 0 && (pCarrier->mFlags & 0x10000)) {
        fn_8022781C(&pCarrier->mMotion.mPos, pMotion);
    }
    if (pState->mUnknown40 != 0 || fn_801787A0() != 0) {
        found = 1;
    }
    if (found == 0) {
        value = fn_8013BA58(fn_801374BC(), 0);
        if (value == 4) {
            fn_80138064(fn_801374BC(), &pos);
        }
    } else {
        if (value != 4) {
            if (pState->mUnknown4 == -1.0f) {
                if (fn_802372EC(0, 100) < 5) {
                    pState->mUnknown4 = 0.0f;
                }
                if (pState->mUnknown0 > 0.4f) {
                    pState->mUnknown0 -= (pState->mUnknown0 - 0.4f) * 0.25f;
                }
            } else {
                if (pMotion->mUnknown28 > lbl_803ECB08 * 0.2f) {
                    pState->mUnknown4 = 0.5f;
                } else {
                    pState->mUnknown4 = 0.0f;
                }
                pState->mUnknown0 = 0.2f;
            }
        } else if (pState->mUnknown0 > 0.4f) {
            pState->mUnknown0 -= (pState->mUnknown0 - 0.4f) * 0.25f;
        } else {
            found = 0;
        }
        pState->mUnknown16 = 0;
        if (pCarrier == 0 && value != 4) {
            pState->mUnknown8 = pMotion->mFacing;
        }
    }
    return found;
}

extern "C" void fn_80128EF8(Object_80039F5C *p, Object_80039F5C *pOther, float distance)
{
    Object_800B26B0 *pMotion;
    Point_80167910 delta;
    int angle;
    int flag;
    float scale;

    if (pOther == 0 || p->mUnknown1032 == 4) {
        return;
    }
    pMotion = &p->mMotion;
    flag = 0;
    fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    if (fn_801CFFD0(angle, pMotion->mFacing) > 0x51C71B && distance >= 1.0f) {
        return;
    }
    scale = 0.0f;
    if (pMotion->mPos.mY > pOther->mMotion.mPos.mY) {
        if (distance < 10.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance / 10.0f;
        } else if (distance < 60.0f) {
            flag = 1;
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance / 60.0f;
        }
    } else if (distance < 2.5f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        scale = 1.0f - distance / 2.5f;
    }
    if (scale != 0.0f) {
        fn_800C89F0(p, angle, 2, flag, scale);
    }
}

extern "C" int fn_80129098(Object_800B26B0 *pMotion, int angle, Vector_80039F5C *pTarget, Vector_80039F5C *pOffset)
{
    Point_80167910 dir;

    fn_80227538(&dir, angle, pMotion->mUnknown28);
    if (pMotion->mPos.mY > pTarget->mY) {
        if (fabsf(pTarget->mX) < fn_80178A08()) {
            float dy = pMotion->mPos.mY - pTarget->mY;
            if (dir.mY < 0.0f) {
                dir.mY = -dir.mY;
                dir.mX = dir.mX * (dy / fabsf(dir.mY + pOffset->mY)) + pMotion->mPos.mX;
                if (fabsf(dir.mX) > fn_80178A08() - lbl_803EB100) {
                    dir.mX = CLAMP(dir.mX, lbl_803EB100 - fn_80178A08(), fn_80178A08() - lbl_803EB100);
                    dir.mY = pTarget->mY;
                    fn_80227690(&dir, &dir, pMotion);
                    angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
                }
            }
            if (pTarget->mY < fn_80178A2C() && fn_80137B40() != 0) {
                fn_80227538(&dir, angle, pMotion->mUnknown28);
                if (dir.mX != 0.0f) {
                    dir.mY = dir.mY * fabsf((pMotion->mPos.mX - pTarget->mX) / dir.mX) + pMotion->mPos.mY;
                    if (dir.mY > fn_80178A2C()) {
                        dir.mX = pTarget->mX;
                        dir.mY = fn_80178A2C();
                        fn_80227690(&dir, &dir, pMotion);
                        angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
                    }
                }
            }
        }
    } else if (pTarget->mY < fn_80178A2C() && fn_80137B40() != 0 && pMotion->mPos.mY < fn_80178A2C()
               && dir.mX != 0.0f && dir.mY > 0.0f) {
        dir.mY = dir.mY * fabsf((pMotion->mPos.mX - pTarget->mX) / dir.mX) + pMotion->mPos.mY;
        if (dir.mY > fn_80178A2C()) {
            dir.mX = pTarget->mX;
            dir.mY = fn_80178A2C();
            fn_80227690(&dir, &dir, pMotion);
            angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
        }
    }
    return angle;
}

extern "C" void fn_80129360(Object_800B26B0 *pMotion, Vector_80039F5C target, Vector_80039F5C dir,
                            Vector_80039F5C *pOut)
{
    Object_80039F5C *pCarrier = fn_80137B40();
    float dx;

    pOut->mX = dir.mX;
    pOut->mY = dir.mY;
    pOut->mZ = dir.mZ;
    dx = fabsf(target.mX - pMotion->mPos.mX);
    if (pCarrier != 0 && lbl_803EB0D8 != 0 && fn_800D0B90(pCarrier) == 0 && pMotion->mUnknown44 > 0.0f
        && dx > lbl_803EB10C) {
        int angle = fn_801CFFD0(fn_801CFE40(dir.mY, dir.mX), 0x400000);
        float scale;
        float length;

        if (angle > 0x400000) {
            angle = 0x400000;
        }
        scale = angle / 4194304.0f;
        length = fn_802270A4(&dir);
        if (lbl_803EB110 == 0) {
            scale = 1.0f;
        }
        pOut->mY += length * (dx / lbl_803EB108 * (scale * lbl_803EB104));
    }
}

extern "C" void fn_801294A8(Object_80039F5C *p, Object_80039F5C *pOther, Point_80167910 *pVelocity, int *pAngle,
                            float *pSpeed, Vector_80039F5C *pTarget, float distance)
{
    if (fn_801BE648(pOther->mpUnknown792) == 74) {
        if (distance < 10.0f) {
            Object_800B26B0 *pMotion = &p->mMotion;
            Point_80167910 velocity;
            int diff = fn_801CFFD0(*pAngle, pOther->mUnknown512.mUnknown4);

            if (diff > 0x2E38E3) {
                diff = 0x2E38E3;
            }
            if (pMotion->mPos.mY < pTarget->mY) {
                diff /= 2;
            }
            diff -= (int)(diff * (distance / 10.0f));
            if (((*pAngle - pOther->mUnknown528.mUnknown4) & 0xFFFFFF) > 0x800000) {
                *pAngle += diff;
            } else {
                *pAngle -= diff;
            }
            *pAngle &= 0xFFFFFF;
            if (pOther->mUnknown512.mUnknown0 < 0.4f) {
                float speed = fn_8016D9F4(pOther, 0.4f, 0.98f);
                if (*pSpeed > speed) {
                    *pSpeed = speed;
                    *pAngle = pOther->mUnknown512.mUnknown4;
                }
            }
            fn_80227538(&velocity, *pAngle, *pSpeed);
            pVelocity->mY = velocity.mY;
            pVelocity->mX = velocity.mX;
        }
    } else {
        unsigned char id = pOther->mpState->mId;

        if (id == 35) {
            if (fn_80110C68(pOther) != 0) {
                *pAngle = fn_80110C10(pOther);
            }
        } else if (id == 34) {
            *pAngle = pOther->mMotion.mFacing;
        } else if (id == 26) {
            if (p->mMotion.mPos.mY > fn_80177FE0().mY) {
                Object_80039F5C *pLinked = fn_8009BCE8(&pOther->mUnknown336);
                if (pLinked != 0 && fn_8022781C(&pLinked->mMotion.mPos, &pOther->mMotion.mPos) < lbl_803EB114) {
                    pVelocity->mX = pLinked->mMotion.mUnknown40;
                    pVelocity->mX = pLinked->mMotion.mUnknown44;
                    *pAngle = pLinked->mMotion.mUnknown32;
                    *pSpeed = pLinked->mMotion.mUnknown28;
                }
            }
        }
    }
}

extern "C" int fn_80129704(Object_80039F5C *p)
{
    State_801297F8 *pState = (State_801297F8 *)&p->mUnknown336;

    pState->mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
    pState->mUnknown4 = -1.0f;
    pState->mUnknown16 = 0;
    pState->mUnknown8 = p->mMotion.mFacing;
    pState->mUnknown12 = 0;
    pState->mUnknown13 = fn_80125F3C(p->mRatings);
    pState->mUnknown14 = fn_80125FA0(p);
    pState->mUnknown15 = (int)(p->mRatings[5] / 255.0f * 15.0f + 3.0f);
    pState->mUnknown40 = 0;
    pState->mUnknown42 = p->mpState->mUnknown1;
    fn_8009A8D4(pState->mUnknown20);
    fn_8010A2DC(p, 0, 0);
    return 0;
}

extern "C" int fn_8012A384(void)
{
    return 1;
}

extern "C" int fn_8012A38C(Object_80039F5C *p, int message)
{
    if (message == 1) {
        State_801297F8 *pState = (State_801297F8 *)&p->mUnknown336;
        pState->mUnknown8 = (pState->mUnknown8 + 0x800000) & 0xFFFFFF;
    }
    return 0;
}
