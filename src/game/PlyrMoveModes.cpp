/* Steering handlers for player movement modes: turn the facing toward the requested direction at a capped rate and scale the turn speed,
   keep an engaged player facing and clear of his opponent, and damp a grounded player's motion. */
#include <math.h>
#include "game/fn_800AD9B4.h"
#include "game/fn_802270D4.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_800DF134.h"

extern "C" {
extern float gFrameTimeScale;

void fn_800B26D0(Object_800B26B0 *pMotion, int a, int b, float c);
void fn_800B2D88(Object_800B26B0 *pMotion, float scale);
void PlyrMoveSteerByHeading(Object_80039F5C *pObject);
void PlyrMoveTurnLimited(Object_80039F5C *pObject);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
int fn_802275D8(void *pA, void *pB, float epsilon);
void fn_80227690(void *pOut, void *pA, void *pB);
}

static int _PlyrMoveModes_iTurnStep = 0x5B05B;
static float _PlyrMoveModes_fRatingBase = 0.6f;
static float _PlyrMoveModes_fRatingScale = 0.4f;
static float _PlyrMoveModes_fMode4Scale = 0.5f;
static float _PlyrMoveModes_fTurnBrakeMax = 0.6f * gFrameTimeScale;
static float _PlyrMoveModes_fTurnBrakeMin = 0.5f * gFrameTimeScale;
static float _PlyrMoveModes_fSpeedScale = 1.35f * gFrameTimeScale;

/* Indexed by the byte +15 of the record at +528 in PlyrMoveModeByType. */
static void (*const _PlyrMoveModes_apTypeHandlers[31])(Object_80039F5C *) = {
    PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveTurnLimited, PlyrMoveTurnLimited,
    PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading,
    PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading,
    PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading,
    PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading, PlyrMoveSteerByHeading,
    PlyrMoveSteerByHeading,
};

extern "C" {
/* True when flag 0x800 is set and the player is on the ground (height 0). */
int PlyrMoveIsFlaggedGrounded(Object_80039F5C *pObject)
{
    if ((pObject->mFlags & 0x800) && pObject->mMotion.mPos.mZ == 0.0f) {
        return 1;
    }
    return 0;
}

float PlyrMoveGetGroundScale(Object_80039F5C *pObject)
{
    return fn_802275D8(&pObject->mMotion.mPos, &pObject->mMotion.mUnknown12, 1e-7f) ? 0.9f : 0.7f;
}

void PlyrMoveApplyGroundScale(Object_80039F5C *pObject)
{
    if (PlyrMoveIsFlaggedGrounded(pObject)) {
        float scale = PlyrMoveGetGroundScale(pObject);

        fn_800B2D88(&pObject->mMotion, scale);
    }
}

/* Keeps the player turned toward and clear of the player referenced at
   +1036, or, while +545 is set, swings him around the point halfway to that
   player. */
void PlyrMoveModeEngage(Object_80039F5C *pObject)
{
    Object_800B26B0 *pMotion = &pObject->mMotion;
    Object_80039F5C *pTarget = fn_8009BCE8(&pObject->mUnknown1036);
    PlyrMoveCmd_t *pControl = &pObject->mUnknown528;
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
            if (MathAngleDiff(facing, pMotion->mFacing) > 0x38E38) {
                if (((facing - pMotion->mFacing) & 0xFFFFFF) > 0x800000) {
                    pMotion->mFacing = (pMotion->mFacing - 0x38E38) & 0xFFFFFF;
                } else {
                    pMotion->mFacing = (pMotion->mFacing + 0x38E38) & 0xFFFFFF;
                }
            } else {
                pMotion->mFacing = facing;
            }
        }
        if (MathAngleDiff(pMotion->mUnknown32, pControl->mUnknown4) > 0) {
            pMotion->mUnknown52 *= 10.0f;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4, pMotion->mFacing, pMotion->mUnknown52);
        if (distance < 2.95f) {
            int apart = MathAngleDiff(pTarget->mMotion.mFacing, pMotion->mFacing);
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
        if (MathAngleDiff(pBlock->mUnknown60, pMotion->mFacing) > 0x16C16) {
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

/* Angles are 24-bit: MathAngleDiff returns the difference of two angles modulo
   0x1000000, folded to at most 0x800000. Moves current toward target by at
   most step. */
int PlyrMoveStepAngle(int current, int target, int step)
{
    if (MathAngleDiff(target, current) > step) {
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
int PlyrMoveStepFacing(Object_80039F5C *pObject, Object_800B26B0 *pMotion, int target, int step)
{
    int direction;

    if (pMotion->mUnknown28 != 0.0f && pMotion->mUnknown36 != 0.0f) {
        if (MathAngleDiff(pMotion->mFacing, pMotion->mUnknown32) > 0x2E38E3) {
            direction = target;
        } else {
            direction = pMotion->mUnknown32;
        }
    } else {
        direction = target;
    }
    return PlyrMoveStepAngle(pMotion->mFacing, direction, step);
}

/* The handlers below scale +52 of the motion block by _PlyrMoveModes_fSpeedScale - k, where
   k grows with the angle to the direction +4 of the record at +512 and with the
   ratio of +28 to +36, and then turn the facing through PlyrMoveStepFacing by at most
   _PlyrMoveModes_iTurnStep. */
void PlyrMoveSteerByHeading(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        PlyrMoveCmd_t *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = MathAngleDiff(pMotion->mUnknown32, pControl->mUnknown4);
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
            weight = (_PlyrMoveModes_fTurnBrakeMax - _PlyrMoveModes_fTurnBrakeMin)
                * (_PlyrMoveModes_fRatingBase
                   + _PlyrMoveModes_fRatingScale * (((pObject->mId & 0xFF) == 1 ? pObject->mRatings[0] : 191.25f) / 255.0f));
            weight += _PlyrMoveModes_fTurnBrakeMin;
            factor = turn * ratio * weight;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = _PlyrMoveModes_fSpeedScale - factor;
        pMotion->mUnknown52 *= factor;
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    PlyrMoveStepFacing(pObject, pMotion, pControl->mUnknown8, _PlyrMoveModes_iTurnStep), pMotion->mUnknown52);
    }
}

void PlyrMoveModeByType(Object_80039F5C *pObject)
{
    _PlyrMoveModes_apTypeHandlers[pObject->mUnknown528.mUnknown15](pObject);
}

void PlyrMoveSteerByFacing(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        PlyrMoveCmd_t *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = MathAngleDiff(pMotion->mFacing, pControl->mUnknown4);
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
            factor = turn * ratio * _PlyrMoveModes_fTurnBrakeMax;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = _PlyrMoveModes_fSpeedScale - factor;
        pMotion->mUnknown52 *= factor;
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    PlyrMoveStepFacing(pObject, pMotion, pControl->mUnknown8, _PlyrMoveModes_iTurnStep), pMotion->mUnknown52);
    }
}

void PlyrMoveSteerScaled(Object_80039F5C *pObject)
{
    if (pObject->mUnknown545 == 0) {
        PlyrMoveCmd_t *pControl = &pObject->mUnknown512;
        Object_800B26B0 *pMotion = &pObject->mMotion;
        int angle = MathAngleDiff(pMotion->mFacing, pControl->mUnknown4);
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
            factor = turn * ratio * _PlyrMoveModes_fTurnBrakeMax;
            if (factor > 1.0f) {
                factor = 1.0f;
            }
        }
        factor = _PlyrMoveModes_fSpeedScale - factor;
        pMotion->mUnknown52 *= factor;
        if (fn_800AD9B4() == 4) {
            pMotion->mUnknown52 *= _PlyrMoveModes_fMode4Scale * pControl->mUnknown0;
        }
        fn_800B26D0(pMotion, pControl->mUnknown4,
                    PlyrMoveStepFacing(pObject, pMotion, pControl->mUnknown8, _PlyrMoveModes_iTurnStep), pMotion->mUnknown52);
    }
}
}
