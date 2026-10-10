#include <math.h>
#include "game/fn_800AD9B4.h"
#include "game/fn_802270D4.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_800DF134.h"

extern "C" {
extern float lbl_803EA2C4;

void fn_800B26D0(Object_800B26B0 *pMotion, int a, int b, float c);
void fn_800B2D88(Object_800B26B0 *pMotion, float scale);
void fn_8016C264(Object_80039F5C *pObject);
void fn_8016C70C(Object_80039F5C *pObject);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
int fn_802275D8(void *pA, void *pB, float epsilon);
void fn_80227690(void *pOut, void *pA, void *pB);
}

static int lbl_803EB418 = 0x5B05B;
static float lbl_803EB41C = 0.6f;
static float lbl_803EB420 = 0.4f;
static float lbl_803EB424 = 0.5f;
static float lbl_803ECAF8 = 0.6f * lbl_803EA2C4;
static float lbl_803ECAFC = 0.5f * lbl_803EA2C4;
static float lbl_803ECB00 = 1.35f * lbl_803EA2C4;

/* Indexed by the byte +15 of the record at +528 in fn_8016C3FC. */
static void (*const lbl_802A4C80[31])(Object_80039F5C *) = {
    fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C70C, fn_8016C70C,
    fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264,
    fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264,
    fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264,
    fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264, fn_8016C264,
    fn_8016C264,
};

extern "C" {
/* True when flag 0x800 is set and the player is on the ground (height 0). */
int fn_8016BD54(Object_80039F5C *pObject)
{
    if ((pObject->mFlags & 0x800) && pObject->mMotion.mPos.mZ == 0.0f) {
        return 1;
    }
    return 0;
}

float fn_8016BD80(Object_80039F5C *pObject)
{
    return fn_802275D8(&pObject->mMotion.mPos, &pObject->mMotion.mUnknown12, 1e-7f) ? 0.9f : 0.7f;
}

void fn_8016BDCC(Object_80039F5C *pObject)
{
    if (fn_8016BD54(pObject)) {
        float scale = fn_8016BD80(pObject);

        fn_800B2D88(&pObject->mMotion, scale);
    }
}

/* Keeps the player turned toward and clear of the player referenced at
   +1036, or, while +545 is set, swings him around the point halfway to that
   player. */
void fn_8016BE10(Object_80039F5C *pObject)
{
    Object_800B26B0 *pMotion = &pObject->mMotion;
    Object_80039F5C *pTarget = fn_8009BCE8(&pObject->mUnknown1036);
    Object_8016D8B0 *pControl = &pObject->mUnknown528;
    Block_8011E240 *pBlock = &pObject->mBlock1032;
    Point_8017886C delta;
    int angle;
    float distance;

    fn_80227690(&delta, &pTarget->mMotion.mPos, pMotion);
    angle = fn_801CFE40(delta.mY, delta.mX);
    distance = fn_802270A4(&delta);
    if (pObject->mUnknown545 == 0) {
        if (pBlock->mUnknown20 != 0) {
            Vector_80039F5C joint;
            Vector_80039F5C extra;
            int facing;

            fn_8009BF5C(pTarget, 11, &joint, &extra);
            fn_80227690(&delta, &joint, pMotion);
            facing = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(facing, pMotion->mFacing) > 0x38E38) {
                if (((facing - pMotion->mFacing) & 0xFFFFFF) > 0x800000) {
                    pMotion->mFacing = (pMotion->mFacing - 0x38E38) & 0xFFFFFF;
                } else {
                    pMotion->mFacing = (pMotion->mFacing + 0x38E38) & 0xFFFFFF;
                }
            } else {
                pMotion->mFacing = facing;
            }
        }
        if (fn_801CFFD0(pMotion->mUnknown32, pControl->mUnknown4) > 0) {
            pMotion->mUnknown52 *= 10.0f;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4, pMotion->mFacing, pMotion->mUnknown52);
        if (distance < 2.95f) {
            int apart = fn_801CFFD0(pTarget->mMotion.mFacing, pMotion->mFacing);
            float limit;

            if (apart > 0x400000) {
                limit = fabsf(fn_801CFB94(apart) * (1.7f - 1.25f)) + 1.25f;
            } else {
                limit = 1.25f;
            }
            if (distance < limit) {
                fn_80227538(&delta, (angle + 0x800000) & 0xFFFFFF, (limit - distance) * 0.2f);
                pMotion->mPos.mX += delta.mX;
                pMotion->mPos.mY += delta.mY;
            }
        }
    } else {
        fn_80227538(&delta, angle, distance * 0.5f);
        if (fn_801CFFD0(pBlock->mUnknown60, pMotion->mFacing) > 0x16C16) {
            Point_8017886C center;
            Point_8017886C turned;

            if (((pBlock->mUnknown60 - pMotion->mFacing) & 0xFFFFFF) > 0x800000) {
                angle = -0x16C16;
            } else {
                angle = 0x16C16;
            }
            angle = (int)(pBlock->mUnknown44 * angle);
            center.mX = pMotion->mPos.mX + delta.mX;
            center.mY = pMotion->mPos.mY + delta.mY;
            delta.mX = pMotion->mPos.mX - center.mX;
            delta.mY = pMotion->mPos.mY - center.mY;
            fn_80227384(&turned, &delta, angle);
            pMotion->mPos.mX = turned.mX + center.mX;
            pMotion->mPos.mY = turned.mY + center.mY;
            turned.mX -= delta.mX;
            turned.mY -= delta.mY;
            pMotion->mFacing = (pMotion->mFacing + angle) & 0xFFFFFF;
            fn_800DF134(pObject, turned, angle, pBlock->mUnknown32);
        }
    }
    pControl->mUnknown0 = pObject->mUnknown512.mUnknown0;
}

/* Angles are 24-bit: fn_801CFFD0 returns the difference of two angles modulo
   0x1000000, folded to at most 0x800000. Moves current toward target by at
   most step. */
int fn_8016C170(int current, int target, int step)
{
    if (fn_801CFFD0(target, current) > step) {
        if (((target - current) & 0xFFFFFF) > 0x800000) {
            target = (current - step) & 0xFFFFFF;
        } else {
            target = (current + step) & 0xFFFFFF;
        }
    }
    return target;
}

/* Turns the facing toward +32 when +28 and +36 are nonzero and +32 is within
   0x2E38E3 of the facing, otherwise toward target. */
int fn_8016C1DC(Object_80039F5C *pObject, Object_800B26B0 *pMotion, int target, int step)
{
    int direction;

    if (pMotion->mUnknown28 != 0.0f && pMotion->mUnknown36 != 0.0f) {
        if (fn_801CFFD0(pMotion->mFacing, pMotion->mUnknown32) > 0x2E38E3) {
            direction = target;
        } else {
            direction = pMotion->mUnknown32;
        }
    } else {
        direction = target;
    }
    return fn_8016C170(pMotion->mFacing, direction, step);
}

/* The handlers below scale +52 of the motion block by lbl_803ECB00 - k, where
   k grows with the angle to the direction +4 of the record at +512 and with the
   ratio of +28 to +36, and then turn the facing through fn_8016C1DC by at most
   lbl_803EB418. */
void fn_8016C264(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        Object_8016D8B0 *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = fn_801CFFD0(pMotion->mUnknown32, pControl->mUnknown4);
        float factor = 0.0f;

        if (angle > 0) {
            float turn;
            float ratio;
            float weight;

            if (angle <= 0x3FFFFF) {
                turn = fn_801CFB18(angle);
            } else {
                turn = 1.0f;
            }
            if (pMotion->mUnknown36 != 0.0f) {
                ratio = pMotion->mUnknown28 / pMotion->mUnknown36;
                if (ratio > 1.0f) {
                    ratio = 1.0f;
                }
            } else {
                ratio = 0.0f;
            }
            weight = (lbl_803ECAF8 - lbl_803ECAFC)
                * (lbl_803EB41C
                   + lbl_803EB420 * (((pObject->mId & 0xFF) == 1 ? pObject->mRatings[0] : 191.25f) / 255.0f));
            weight += lbl_803ECAFC;
            factor = turn * ratio * weight;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = lbl_803ECB00 - factor;
        pMotion->mUnknown52 *= factor;
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    fn_8016C1DC(pObject, pMotion, pControl->mUnknown8, lbl_803EB418), pMotion->mUnknown52);
    }
}

void fn_8016C3FC(Object_80039F5C *pObject)
{
    lbl_802A4C80[pObject->mUnknown528.mUnknown15](pObject);
}

void fn_8016C434(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        Object_8016D8B0 *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = fn_801CFFD0(pMotion->mFacing, pControl->mUnknown4);
        float factor = 0.0f;

        if (angle > 0) {
            float turn;
            float ratio;

            if (angle <= 0x3FFFFF) {
                turn = fn_801CFB18(angle);
            } else {
                turn = 1.0f;
            }
            if (pMotion->mUnknown36 != 0.0f) {
                ratio = pMotion->mUnknown28 / pMotion->mUnknown36;
                if (ratio > 1.0f) {
                    ratio = 1.0f;
                }
            } else {
                ratio = 0.0f;
            }
            factor = turn * ratio * lbl_803ECAF8;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = lbl_803ECB00 - factor;
        pMotion->mUnknown52 *= factor;
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    fn_8016C1DC(pObject, pMotion, pControl->mUnknown8, lbl_803EB418), pMotion->mUnknown52);
    }
}

void fn_8016C550(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        Object_8016D8B0 *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = fn_801CFFD0(pMotion->mFacing, pControl->mUnknown4);
        float factor = 0.0f;

        if (angle > 0) {
            float turn;
            float ratio;

            if (angle <= 0x3FFFFF) {
                turn = fn_801CFB18(angle);
            } else {
                turn = 1.0f;
            }
            if (pMotion->mUnknown36 != 0.0f) {
                ratio = pMotion->mUnknown28 / pMotion->mUnknown36;
                if (ratio > 1.0f) {
                    ratio = 1.0f;
                }
            } else {
                ratio = 0.0f;
            }
            factor = turn * ratio * lbl_803ECAF8;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = lbl_803ECB00 - factor;
        pMotion->mUnknown52 *= factor;
        if (fn_800AD9B4() == 4) {
            pMotion->mUnknown52 *= lbl_803EB424 * pControl->mUnknown0;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    fn_8016C1DC(pObject, pMotion, pControl->mUnknown8, lbl_803EB418), pMotion->mUnknown52);
    }
}
}
