#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

/* Per-condition counters passed to the condition callbacks. */
struct Pair_800A554C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
float fn_80227890(void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_800A46D8(Object_80039F5C *p, Object_80039F5C *pTarget, int flag);
int fn_800A4790(Object_80039F5C *p, Object_80039F5C *pTarget);
int fn_8011F1A4(void);
int fn_8011F4C8(void);
Object_80039F5C *fn_80137B40(void);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_80227638(void *pOut, void *pA, void *pB);
float fn_802270A4(void *pV);

extern unsigned int lbl_803EAA14;
}

extern "C" int fn_800A54F4(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    return fn_80227890(&p->mMotion.mPos, &pTarget->mMotion.mPos) < (float)lbl_803EAA14;
}

extern "C" int fn_800A55D0(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    Point_8017886C delta;
    int angle;

    fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = angle;
    p->mUnknown512.mUnknown4 = angle;
    p->mUnknown512.mUnknown0 = 1.0f;
    return 1;
}

extern "C" int fn_800A563C(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int angle = fn_800A46D8(p, pTarget, 0);

    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = angle;
    p->mUnknown512.mUnknown4 = angle;
    p->mUnknown512.mUnknown0 = 1.0f;
    return 1;
}

extern "C" int fn_800A5690(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int result = 1;

    if (*pState == -1) {
        if (pTarget->mpState->mId != 34) {
            result = 0;
        } else {
            *pState = fn_800A4790(p, pTarget);
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = *pState;
    p->mUnknown512.mUnknown4 = *pState;
    p->mUnknown512.mUnknown0 = 1.0f;
    return result;
}

extern "C" int fn_800A5718(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int result = 1;

    if (*pState == -1) {
        if (pTarget->mpState->mId != 35) {
            result = 0;
        } else {
            *pState = fn_800A46D8(p, pTarget, 0);
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = *pState;
    p->mUnknown512.mUnknown4 = *pState;
    p->mUnknown512.mUnknown0 = 1.0f;
    return result;
}

extern "C" int fn_800A57A4(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int result = 1;

    if (*pState == -1) {
        if (pTarget->mpState->mId != 52) {
            result = 0;
        } else {
            if (fn_8011F1A4() != 0 && (fn_8011F4C8() & 1)) {
                *pState = 0;
            } else {
                *pState = 0x800000;
            }
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = *pState;
    p->mUnknown512.mUnknown4 = *pState;
    p->mUnknown512.mUnknown0 = 1.0f;
    return result;
}

extern "C" int fn_800A5844(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int angle;
    Point_8017886C delta;

    if (p->mUnknown1144 == -1) {
        if (p->mpState->mId == 2 || p->mpState->mId == 30) {
            Object_80039F5C *pCarrier = fn_80137B40();

            if (pCarrier != 0) {
                fn_80227690(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
                angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            } else {
                angle = 0xC00000;
            }
            p->mUnknown1144 = angle;
        } else {
            Point_8017886C lead;
            float speed = fn_8016D9F4(pTarget, 1.0f, 1.0f) * p->mUnknown1152;

            fn_80227538(&lead, pTarget->mMotion.mUnknown32, speed);
            fn_80227638(&lead, &lead, &pTarget->mMotion.mPos);
            fn_80227690(&delta, &lead, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            p->mUnknown1144 = angle;
            speed = fn_8016D9F4(p, 1.0f, 1.0f) * p->mUnknown1152;
            p->mUnknown1148 = fn_802270A4(&delta) / speed;
            p->mUnknown1148 = p->mUnknown1148 > 1.0f ? 1.0f : p->mUnknown1148;
            p->mUnknown1148 = p->mUnknown1148 < 1e-7f ? 1e-7f : p->mUnknown1148;
        }
    } else {
        angle = p->mUnknown1144;
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = angle;
    p->mUnknown512.mUnknown4 = angle;
    p->mUnknown512.mUnknown0 = p->mUnknown1148;
    return 1;
}

extern "C" int fn_800A5A04(Object_80039F5C *p, Object_80039F5C *pTarget, int *pState)
{
    int result = 1;

    if (*pState == -1) {
        if (pTarget->mpState->mId != 20) {
            result = 0;
        } else {
            *pState = pTarget->mMotion.mUnknown32;
        }
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = *pState;
    p->mUnknown512.mUnknown4 = *pState;
    p->mUnknown512.mUnknown0 = 1.0f;
    return result;
}
