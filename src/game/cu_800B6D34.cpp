#include "game/Object_80039F5C.h"
#include "game/Input_800B6D34.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"

extern "C" {
int fn_800B5FEC(Object_80039F5C *p);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_800DBC4C(Object_80039F5C *p, int angle, float value);
int fn_800DC080(Object_80039F5C *p);
int fn_800DC21C(Object_80039F5C *p);
void fn_800F177C(int index, Input_800B6D34 *pOut);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801481B0(void);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
void fn_8016DA5C(Object_80039F5C *p);
int fn_80178308(void);
int fn_801784C4(void);
unsigned short fn_801BE648(void *p);
int fn_801C1FEC(const void *pA, const void *pB, int size);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_802270A4(void *pV);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput)
{
    Input_800B6D34 empty;
    unsigned int mask;

    if (p->mUnknown8 != 0xFF) {
        fn_800F177C(p->mUnknown8, pInput);
        fn_801C1F94(&empty, 0, sizeof(empty));
        if (fn_801C1FEC(pInput, &empty, sizeof(empty)) != 0) {
            if (fn_800AD9B4() == 3) {
                mask = 0x7FFF0;
                if (p->mIdBytes[2] == fn_80178308() || fn_8013BA58(fn_801374BC(), 0) != 4) {
                    mask = 0x7FFFF;
                }
                if (pInput->mUnknown4 == 0.0f && pInput->mUnknown8 == 0.0f && (pInput->mUnknown0 & mask) == 0) {
                    return;
                }
            } else if (pInput->mUnknown4 == 0.0f && pInput->mUnknown8 == 0.0f && (pInput->mUnknown0 & 0xF) == 0) {
                return;
            }
            fn_8016DA5C(p);
            if (fn_800B5FEC(p) != 0) {
                p->mFlags |= 0x4000;
            }
        }
    } else {
        fn_801C1F94(pInput, 0, sizeof(*pInput));
    }
}

extern "C" void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput)
{
    Vector_80039F5C stick;
    Vector_80039F5C delta;
    float speed;
    int angle;
    int ballAngle;
    int state;
    int turn;
    Object_80137ABC *pBall;

    if (p->mUnknown9[1] != 0) {
        p->mUnknown9[1]--;
        return;
    }
    stick.mY = 0.0f;
    stick.mX = 0.0f;
    if (pInput->mUnknown4 != 0.0f || pInput->mUnknown8 != 0.0f) {
        stick.mX = pInput->mUnknown4;
        stick.mY = pInput->mUnknown8;
    } else {
        if (pInput->mUnknown0 & 1) {
            stick.mY = 1.0f;
        }
        if (pInput->mUnknown0 & 2) {
            stick.mY = -1.0f;
        }
        if (pInput->mUnknown0 & 4) {
            stick.mX = -1.0f;
        }
        if (pInput->mUnknown0 & 8) {
            stick.mX = 1.0f;
        }
    }
    speed = fn_802270A4(&stick) > 1.0f ? 1.0f : fn_802270A4(&stick);
    if (stick.mY != 0.0f || stick.mX != 0.0f) {
        ballAngle = 0;
        p->mFlags |= 0x400;
        angle = fn_801CFE40(stick.mY, stick.mX) - pInput->mUnknown20;
        if (fn_801784C4() != 0) {
            angle -= 0x800000;
        }
        angle &= 0xFFFFFF;
        if (fn_800DC080(p) == 0) {
            if (fn_800DC21C(p) == 1 && p->mUnknown512.mUnknown15 != 1) {
                speed *= 0.75f;
            }
            pBall = fn_801374BC();
            state = fn_8013BA58(pBall, 0);
            if (fn_80138064(pBall, &delta) != 0) {
                fn_80227690(&delta, &delta, &p->mMotion);
                ballAngle = fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mUnknown32);
            } else {
                state = 0;
            }
            turn = fn_801CFFD0(angle, p->mMotion.mUnknown32);
            if (state == 4 && fn_80137B40() == 0 && turn > 0x671C72 && ballAngle <= 0x18E38D) {
                float top = fn_8016D9F4(p, 1.0f, 1.0f);
                float ratio = top != 0.0f ? p->mMotion.mUnknown28 / top : 0.0f;

                if (ratio < 0.15f) {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = speed;
                    p->mUnknown512.mUnknown4 = angle;
                }
            } else if (p != fn_80137B40() && speed < 0.72f) {
                p->mUnknown512.mUnknown14 = 3;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = speed;
                p->mUnknown512.mUnknown4 = angle;
            } else {
                p->mUnknown512.mUnknown0 = speed;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
            }
            fn_800C89F0(p, angle, 0, 0, 0.5f);
        } else if (fn_801481B0() != 0) {
            fn_800DBC4C(p, angle, speed);
        }
    } else {
        int mode = fn_800DC080(p);

        if (mode == 1) {
            if (fn_801BE648(p->mpUnknown792) != 0x4A && fn_801BE648(p->mpUnknown792) != 0x54
                && fn_801BE648(p->mpUnknown792) != 0xD9 && fn_801BE648(p->mpUnknown792) != 0xDE) {
                p->mUnknown512.mUnknown14 = mode;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.0f;
            } else {
                fn_800DBC4C(p, p->mMotion.mFacing, 0.0f);
            }
        } else if (fn_800DC21C(p) == 1 && fn_801481B0() != 0) {
            fn_800DBC4C(p, p->mMotion.mFacing, 0.0f);
        }
    }
}
