/* Per-frame player movement update: latches the movement request, clamps its speed by move type,
   sets forward, side and backpedal speed and turn rate from the player's ratings, and runs the movement mode handler. */
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/Object_80039F5C.h"

extern "C" {
extern float gFrameTimeScale;

void fn_800B26B0(Object_800B26B0 *pObject);
void fn_800B26E0(Object_800B26B0 *pObject);
void fn_800B2A14(Object_800B26B0 *pObject, unsigned char *a);
void fn_800B2D9C(Object_800B26B0 *pObject);
float fn_800C4914(Object_80039F5C *p, float value);
float fn_800C495C(Object_80039F5C *p, float value);
void fn_800CA8F4(Object_80039F5C *p);
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
int fn_8011E9B4(Object_80039F5C *p);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char b, int angle, float *pOut, int c);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
Object_80039F5C *BallGetCurrentHolder(void);
void PlyrMoveApplyGroundScale(Object_80039F5C *p);
void PlyrMoveModeEngage(Object_80039F5C *p);
void PlyrMoveModeByType(Object_80039F5C *p);
void PlyrMoveSteerByFacing(Object_80039F5C *p);
void PlyrMoveSteerScaled(Object_80039F5C *p);
void fn_8016C70C(Object_80039F5C *p);
void fn_8016CA50(Object_80039F5C *p);
int fn_8016CDD4(Object_80039F5C *p);
void PlyrMoveModeStop(Object_80039F5C *p);
void PlyrMoveModeSpin(Object_80039F5C *p);
int fn_80178308(void);
float fn_801CFB18(int angle);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

static unsigned short _PlyrMove_uHoldFrames = 30;

float gPlyrMoveBaseSpeed = 40.0f / (210.0f / gFrameTimeScale);
float gPlyrMoveFwdSpeed = gPlyrMoveBaseSpeed;
float gPlyrMoveSideSpeed = gPlyrMoveBaseSpeed;
float gPlyrMoveBackSpeed = gPlyrMoveBaseSpeed;
static float _PlyrMove_fSlowSpeed = gPlyrMoveBaseSpeed * 0.15f;
static float _PlyrMove_fTurnRateMax = gFrameTimeScale * 0.0125f;
static float _PlyrMove_fTurnRateMin = gFrameTimeScale * 0.009f;
static float _PlyrMove_fTurnRateSlow = gFrameTimeScale * 0.0036f;

static void (*const _PlyrMove_apModeHandlers[])(Object_80039F5C *) = {
    PlyrMoveModeStop, PlyrMoveModeByType, PlyrMoveSteerByFacing, fn_8016C70C, fn_8016CA50, PlyrMoveModeEngage,
    PlyrMoveModeSpin, PlyrMoveModeSpin, fn_8016C70C, PlyrMoveSteerScaled, PlyrMoveModeByType,
};

extern "C" {
void PlyrMoveModeStop(Object_80039F5C *p)
{
    p->mMotion.mUnknown52 = 0.0f;
    p->mUnknown512.mUnknown0 = 0.0f;
}

void PlyrMoveModeSpin(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    pMotion->mUnknown52 = 0.0f;
    if (p->mUnknown544 != 0 && p->mUnknown545 == 0) {
        pMotion->mFacing = (pMotion->mFacing + p->mUnknown548) & 0xFFFFFF;
    }
}

void PlyrMoveCalcSpeed(Object_80039F5C *p)
{
    int reverse = 0;
    PlyrMoveCmd_t *pInput = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    int turn = MathAngleDiff(pInput->mUnknown4, pInput->mUnknown8);
    float sign = 1.0f;
    float speed;
    float limit;

    if (p->mUnknown1032 == 4) {
        speed = _PlyrMove_fSlowSpeed * p->mUnknown528.mUnknown0;
        limit = _PlyrMove_fSlowSpeed;
    } else if (turn <= 0x2E38E2) {
        speed = gPlyrMoveFwdSpeed * p->mUnknown528.mUnknown0;
        limit = gPlyrMoveFwdSpeed - fn_801CFB18(turn) * (gPlyrMoveFwdSpeed / 2.0f);
        if (pInput->mUnknown4 != p->mUnknown512.mUnknown4) {
            reverse = 1;
        }
        if (fn_800AD9B4() == 3 && p->mUnknown528.mUnknown0 == 0.0f) {
            reverse = 1;
        }
    } else if (PlayerActionAnimIsPassReady(p) == 0) {
        if (turn <= 0x56C16B) {
            speed = gPlyrMoveSideSpeed * p->mUnknown528.mUnknown0;
            limit = gPlyrMoveSideSpeed - fn_801CFB18(0x56C16C - turn) * (gPlyrMoveSideSpeed / 2.0f);
        } else {
            speed = gPlyrMoveBackSpeed * p->mUnknown528.mUnknown0;
            limit = gPlyrMoveBackSpeed - fn_801CFB18(0x80B60C - turn) * (gPlyrMoveBackSpeed / 2.0f);
        }
    } else {
        limit = speed = gPlyrMoveBackSpeed * p->mUnknown528.mUnknown0;
    }
    if (reverse) {
        sign = -sign;
    }
    limit *= 5.0f;
    if (pInput->mUnknown14 == 2 || p->mUnknown1032 == 4) {
        pMotion->mUnknown36 = speed * (191.25f / 255.0f * 0.38f + 0.62f);
        pMotion->mUnknown36 = pMotion->mUnknown36 <= limit ? pMotion->mUnknown36 : limit;
        pMotion->mUnknown52 = _PlyrMove_fTurnRateSlow * (191.25f / 510.0f + 0.5f) * sign;
    } else {
        pMotion->mUnknown36 = speed * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 255.0f * 0.38f + 0.62f);
        pMotion->mUnknown36 = pMotion->mUnknown36 <= limit ? pMotion->mUnknown36 : limit;
        switch (pInput->mUnknown14) {
        case 9:
            pMotion->mUnknown52 = _PlyrMove_fTurnRateMax * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 510.0f + 0.5f) * sign;
            break;
        case 10:
            pMotion->mUnknown36 = gPlyrMoveFwdSpeed;
            pMotion->mUnknown52 = 0.0f;
            pMotion->mUnknown60 = pInput->mUnknown0 * 0.0036f;
            break;
        default:
            pMotion->mUnknown52 = _PlyrMove_fTurnRateMin + (_PlyrMove_fTurnRateMax - _PlyrMove_fTurnRateMin) * pInput->mUnknown0;
            pMotion->mUnknown52 = pMotion->mUnknown52 * (((p->mId & 0xFF) == 1 ? p->mRatings[4] : 191.25f) / 510.0f + 0.5f) * sign;
            break;
        }
    }
    pMotion->mUnknown36 = fn_800C495C(p, pMotion->mUnknown36);
    pMotion->mUnknown52 = fn_800C4914(p, pMotion->mUnknown52);
    if (fn_8016CDD4(p)) {
        float cap = gPlyrMoveFwdSpeed * pInput->mUnknown0;

        pMotion->mUnknown36 = pMotion->mUnknown36 <= cap ? pMotion->mUnknown36 : cap;
        pMotion->mUnknown52 = _PlyrMove_fTurnRateMax;
    }
}

void PlyrMovePickSideType(Object_80039F5C *p)
{
    float delta[2];
    float distance;

    if (MathAngleDiff(0x400000, p->mMotion.mFacing) < 0x355555 && p == BallGetCurrentHolder()) {
        int team = fn_80178308();
        Object_80039F5C *pOther = fn_801245DC(p, team, 0, fn_80178D18(fn_80178308()), 0x355555, &distance, 0);

        if (pOther && distance < 2.0f && !(pOther->mFlags & 0x800) && fn_8011E9B4(pOther)) {
            int angle;

            fn_80227690(delta, &pOther->mMotion, &p->mMotion);
            angle = fn_801CFE40(delta[1], delta[0]);
            if (distance < 2.0f - MathAngleDiff(angle, p->mMotion.mFacing) / 3495253.0f &&
                fn_80124714(p, pOther, 0)) {
                if (((angle - p->mUnknown512.mUnknown4) & 0xFFFFFF) <= 0x7FFFFF) {
                    if (p->mUnknown776 == 2) {
                        p->mUnknown528.mUnknown15 = 3;
                    } else {
                        p->mUnknown528.mUnknown15 = 2;
                    }
                } else {
                    if (p->mUnknown776 == 2) {
                        p->mUnknown528.mUnknown15 = 2;
                    } else {
                        p->mUnknown528.mUnknown15 = 3;
                    }
                }
            }
        }
    }
}

void PlyrMoveLatchRequest(Object_80039F5C *p)
{
    PlyrMoveCmd_t *pRequest = &p->mUnknown512;
    PlyrMoveCmd_t *pInput = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    float limit;

    p->mUnknown512.mUnknown0 = p->mUnknown512.mUnknown0 >= 0.0f ? p->mUnknown512.mUnknown0 : 0.0f;
    pInput->mUnknown15 = 0;
    fn_800CA8F4(p);
    if (pRequest->mUnknown15 == 0 || pInput->mUnknown12 == _PlyrMove_uHoldFrames) {
        if (p->mFlags & 0x4000) {
            if (pInput->mUnknown12 != 0) {
                if (MathAngleDiff(pMotion->mUnknown32, pRequest->mUnknown4) <= 0x11C71B) {
                    pInput->mUnknown12--;
                    pRequest->mUnknown15 = 1;
                } else {
                    pInput->mUnknown12 = 0;
                }
            }
        } else {
            pInput->mUnknown12 = 0;
        }
    } else {
        pInput->mUnknown12 = 0;
    }
    switch (pRequest->mUnknown15) {
    case 28:
        pInput->mUnknown15 = 28;
        pInput->mUnknown0 = pRequest->mUnknown0 <= 0.25f ? pRequest->mUnknown0 : 0.25f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 29:
        pInput->mUnknown15 = 29;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 23:
        pInput->mUnknown15 = 23;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.98f ? pInput->mUnknown0 : 0.98f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 1:
    case 5:
    case 11:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        if (p == BallGetCurrentHolder()) {
            pInput->mUnknown0 = pInput->mUnknown0 <= 0.98f ? pInput->mUnknown0 : 0.98f;
            pRequest->mUnknown0 = pInput->mUnknown0;
            if (pInput->mUnknown15 == 1) {
                PlyrMovePickSideType(p);
            }
        }
        break;
    case 8:
    case 9:
        limit = pRequest->mUnknown15 == 8 ? 0.65f : 0.92f;
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= limit ? pInput->mUnknown0 : limit;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 6:
    case 7:
        limit = pRequest->mUnknown15 == 6 ? 0.65f : 0.92f;
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= limit ? pInput->mUnknown0 : limit;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 13:
    case 14:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.7f ? pInput->mUnknown0 : 0.7f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 24:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.8f ? pInput->mUnknown0 : 0.8f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 25:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 12:
        pInput->mUnknown15 = 12;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.7f ? pInput->mUnknown0 : 0.7f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 15:
    case 16:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 20:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.65f ? pInput->mUnknown0 : 0.65f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 21:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.92f ? pInput->mUnknown0 : 0.92f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 26:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.55f ? pInput->mUnknown0 : 0.55f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 27:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 0:
    case 10:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        if (pRequest->mUnknown15 == 0) {
            PlyrMovePickSideType(p);
        }
        break;
    case 30:
        pInput->mUnknown15 = pRequest->mUnknown15;
        pInput->mUnknown0 = pInput->mUnknown0 <= 1.0f ? pInput->mUnknown0 : 1.0f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    case 2:
    case 3:
    case 4:
    case 18:
    case 19:
    case 22:
        pInput->mUnknown15 = pRequest->mUnknown15;
    default:
        pInput->mUnknown0 = pInput->mUnknown0 <= 0.72f ? pInput->mUnknown0 : 0.72f;
        pRequest->mUnknown0 = pInput->mUnknown0;
        break;
    }
    pRequest->mUnknown15 = 0;
}

void PlyrMoveCmdClear(PlyrMoveCmd_t *pObject)
{
    fn_801C1F94(pObject, 0, sizeof(*pObject));
    pObject->mUnknown14 = 0;
    pObject->mUnknown15 = 0;
}

void PlyrMoveUpdate(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    fn_800B26B0(pMotion);
    PlyrMoveLatchRequest(p);
    if (_PlyrMove_apModeHandlers[p->mUnknown528.mUnknown14] != PlyrMoveModeStop) {
        PlyrMoveCalcSpeed(p);
    }
    _PlyrMove_apModeHandlers[p->mUnknown528.mUnknown14](p);
    if (p->mUnknown545 == 0) {
        PlyrMoveApplyGroundScale(p);
        fn_800B26E0(pMotion);
    } else {
        fn_800B2A14(pMotion, &p->mUnknown544);
    }
    if (p->mFlags & 0x100) {
        p->mFlags &= ~0x100;
        fn_800B2D9C(&p->mMotion);
    }
    p->mUnknown528.mUnknown14 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
}

void PlyrMoveCmdReverse(PlyrMoveCmd_t *pObject)
{
    pObject->mUnknown4 = (pObject->mUnknown4 + 0x800000) & 0xFFFFFF;
    pObject->mUnknown8 = (pObject->mUnknown8 + 0x800000) & 0xFFFFFF;
}

float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b)
{
    float speed = a <= b ? a : b;

    speed *= gPlyrMoveFwdSpeed;
    return speed * (p->mRatings[4] / 255.0f * 0.38f + 0.62f);
}

void PlyrMoveStartHold(Object_80039F5C *p)
{
    if (!(p->mFlags & 0x4000) && (p->mUnknown528.mUnknown15 == 1 || p->mUnknown512.mUnknown15 == 1) &&
        p->mUnknown528.mUnknown12 == 0) {
        p->mUnknown528.mUnknown12 = _PlyrMove_uHoldFrames;
    }
}

void PlyrMoveClearHold(Object_80039F5C *p)
{
    p->mUnknown528.mUnknown12 = 0;
}

int PlyrMoveIsFacingHeading(Object_80039F5C *p)
{
    return MathAngleDiff(p->mMotion.mFacing, p->mMotion.mUnknown32) <= 0x200000;
}
}
