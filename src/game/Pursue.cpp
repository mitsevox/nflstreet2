/* Player state that pursues the ball: the player runs at the ball carrier (or the pass target or
   the landing ball), leads the target and keeps its heading inside the field, steers by its
   pursuit assignment, avoids other players, plays for a ball in the air and rolls for moves
   against the target when it is close. */

#include "game/PursueState.h"
#include "engine/cu_801B9F00.h"
#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/PlayBookTeam.h"
#include "game/Ball.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800B65A0.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))


extern "C" {
int fn_80099734(Object_80039F5C *p, Ball_t *pBall, int a, int mode, void *pBlock, int b, int c, int d,
                int e, float range);
int fn_80099F04(Object_80039F5C *p, int handle, unsigned char index);
int PlyrRollContestedCatch(Object_80039F5C *p);
void fn_8009A8D4(void *p);
int fn_8009AF00(int team, int value);
int fn_8009F0B8(Object_80039F5C *p, int angle);
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
int fn_8009FB60(Object_80039F5C *p);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_800A5DD0(Object_80039F5C *p);
int fn_800AC980(Object_80039F5C *p, int value);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int PlayerMoveGetKind(Object_80039F5C *p);
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
int fn_800E1584(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_80110C10(Object_80039F5C *p);
int fn_80110C68(Object_80039F5C *p);
void fn_80111354(Object_80039F5C *p);
int fn_80112C04(Object_80039F5C *p, Ball_t *pBall, int *pAngle, float *pValue);
unsigned int fn_8011E188(void);
int fn_8011F1A4(void);
int fn_8011F1CC(void);
int fn_8011F32C(void);
unsigned int fn_8011F4C8(void);
int fn_80120794(Object_800B26B0 *pMotion, Vector_80039F5C *pTarget, Vector_80039F5C *pDir, float speed, float length,
                int angle, float distance);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
int PursueShouldPlayBall(Object_80039F5C *p);
void PursueTryMoves(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C pos, float distance, int forced);
void PursueAvoidPlayers(Object_80039F5C *p, PursueState_t *pState, float distance);
Object_80039F5C *PursueGetTarget(void);
int PursueGetTackleChance(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C pos, float distance, int *pOut);
int BallStateGet(Ball_t *pBall, int *pOut);
int fn_801486A0(void);
float fn_8016B938(void);
float fn_8016B974(void);
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
int PlyrMoveIsFacingHeading(Object_80039F5C *p);
int fn_80177C38(void);
int fn_80178308(void);
int fn_801783AC(int bit);
int fn_801787A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A5C(void);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
float fn_8022710C(void *pV);
void fn_80227538(Vec2_t *pOut, int angle, float length);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" float gPlyrMoveFwdSpeed;

extern "C" {
int BallStateGet(Ball_t *ball, int *pOut);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
float fn_801CFB94(int angle);
int fn_801787A0(void);
int fn_800A7F30(int team);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_801783AC(int bit);
float fn_80178A2C(void);
int fn_800ABDA4(int team);
int PursueGetTackleChance(Object_80039F5C *p, Object_80039F5C *other, Vector_80039F5C pos, float distance, int *pOut);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_8011E88C(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned int fn_8011F4C8(void);
Object_80039F5C *PursueGetTarget(void);
int fn_800E6AC8(Object_80039F5C *p, int mode);
int fn_800F2C1C(Object_80039F5C *p, int a);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
int fn_8011E9B4(Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
float fn_80237260(int stream);
}

extern "C" {
int fn_800A8444(int team);
int fn_800A8408(int team);
float fn_80237260(int stream);
int fn_801486A0(void);
}

static unsigned int _Pursue_auCloseTargetIds[4] = {96, 93, 174, 186};

static float _Pursue_fTackleRange = 5.0f;
static float _Pursue_fNoTackleRange = 4.0f;
static float _Pursue_fBehindTackleRange = 3.0f;
static unsigned int _Pursue_uTackleOdds = 60;
static unsigned int _Pursue_uLaneLineOdds = 100;
static unsigned int _Pursue_uLaneOdds = 60;
static int _Pursue_iTackleChance = 35;
static int _Pursue_iAheadTackleChance = 40;
static int _Pursue_iLaneTackleChance = 50;
static unsigned int _Pursue_uCloseTackleChance = 55;
static unsigned char _Pursue_bLeadTarget = 1;
static float _Pursue_fPlayBallAngleDeg = 90.0f;
static float _Pursue_fKind3SidelineTime = 60.0f;
static float _Pursue_fKind3LeftHeadingDeg = 270.0f;
static float _Pursue_fKind3RightHeadingDeg = 270.0f;
static unsigned char _Pursue_uWindowMinDeg = 60;
static unsigned char _Pursue_uWindowMaxDeg = 120;
static short _Pursue_sWindowMinDist = 4;
static short _Pursue_sWindowMaxDist = 100;
static short _Pursue_sWindowWidenDeg = 10;
static short _Pursue_sWindowReach = 0;
static float _Pursue_fWindowSkewNearDeg = 15.0f;
static float _Pursue_fWindowSkewFarDeg = 30.0f;
static float _Pursue_fSidelineMargin = 1.0f;
static float _Pursue_fLeadScale = 8.0f;
static float _Pursue_fLeadWidth = 20.0f;
static float _Pursue_fLeadMinGap = 5.0f;
static unsigned char _Pursue_bLeadByAngle = 1;
static float _Pursue_fLinkedRange = 4.0f;

static inline short PursueClampRating(const short &value, short low, short high)
{
    return value < low ? low : (value > high ? high : value);
}

static inline short PursueScaleRating(short from, short to, short t, short range)
{
    return from + (to - from) * t / range;
}

extern "C" signed char PursueGetMoveDelay(short *pRatings)
{
    short value = PursueScaleRating(15, 0, PursueClampRating(pRatings[9], 0, 255), 255);
    return value < 0 ? 0 : (value > 15 ? 15 : value);
}

extern "C" signed char PursueGetTackleDelay(Object_80039F5C *p)
{
    short *pRatings = p->mRatings;
    short value;

    if (fn_800A8444(p->mIdBytes[2]) && fn_800A8408(p->mIdBytes[2]) == 1) {
        value = (int)(fn_80237260(0) * 45.0f);
    } else {
        value = PursueScaleRating(126, 0, PursueClampRating(pRatings[5], 0, 255), 255);
    }
    if (fn_801486A0() == 2 && fn_80178D70(p->mIdBytes[2]) == 1) {
        value = (int)(value / 10.0f);
    }
    return value < 0 ? 0 : (value > 126 ? 126 : value);
}

extern "C" int PursueShouldPlayBall(Object_80039F5C *p)
{
    int result = 0;
    Vector_80039F5C position;
    int info;
    float ballDelta[2];
    float playerDelta[2];
    Ball_t *ball = BallGetCurrent();
    if (BallStateGet(ball, &info) == 3) {
        Record_8011F518 *record = fn_8011F518();
        if (record->mUnknown4 == 11 || record->mUnknown4 == 9) {
            Object_80039F5C *other = fn_8009BCE8(&record->mUnknown0);
            BallGetPosition(ball, &position);
            fn_80227690(ballDelta, &position, &other->mMotion.mPos);
            fn_80227690(playerDelta, &p->mMotion.mPos, &other->mMotion.mPos);
            int ballAngle = fn_801CFE40(ballDelta[1], ballDelta[0]);
            float ballDistance = fn_802270A4(ballDelta);
            int playerAngle = fn_801CFE40(playerDelta[1], playerDelta[0]);
            float playerDistance = fn_8022781C(&p->mMotion.mPos, &position);
            short rating = p->mRatings[5] >= p->mRatings[8] ? p->mRatings[5] : p->mRatings[8];
            unsigned int threshold = rating;
            if (fn_802372EC(0, 255) < threshold >> 2 &&
                MathAngleDiff(ballAngle, playerAngle) < (int)(_Pursue_fPlayBallAngleDeg * 46603.37890625f) &&
                !(playerDistance >= ballDistance))
                result = 1;
        }
    }
    return result;
}

extern "C" unsigned int PursueGetCloseTackleChance(Object_80039F5C *p)
{
    unsigned int value = _Pursue_uCloseTackleChance;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, _Pursue_auCloseTargetIds[i], 0) != 0xFFFF) {
            value >>= 1;
            break;
        }
    }
    return value;
}

extern "C" void PursueTryMoves(Object_80039F5C *p, Object_80039F5C *other, Vector_80039F5C position, float distance, int forced)
{
    int chance = 0;
    int attempt = 0;
    if (fn_801787A0()) return;
    Object_800B26B0 *motion = &p->mMotion;
    Block_8011E240 *block = &p->mBlock1032;
    float delta[2];
    fn_80227690(delta, &position, &motion->mPos);
    int heading = fn_801CFE40(delta[1], delta[0]);
    PursueState_t *state = (PursueState_t *)&p->mUnknown336;
    if (!fn_800A7F30((unsigned char)(1 - p->mIdBytes[2])) && fn_800A851C(p->mIdBytes[2], p))
        state->mUnknown13 = 0;
    else state->mUnknown13--;
    state->mUnknown14--;
    int done = 0;
    if (other && ((other->mFlags & 0x8000) || fn_801783AC(0)) &&
        !(fn_8022781C(&motion->mPos, &position) >= 5.0f) &&
        !(fn_80178A2C() - position.mY >= 7.0f)) {
        attempt = 1;
        chance = 100;
    }
    if (state->mUnknown14 <= 0) {
        done = 0;
        state->mUnknown14 = PursueGetTackleDelay(p);
        if (other && !(fn_8022781C(&motion->mPos, &position) >= 5.0f) &&
            (unsigned int)(MathAngleDiff(motion->mFacing, other->mMotion.mUnknown32) - 0x2AAAAB) <= 0x2AAAA9) {
            attempt = 1;
            chance = !fn_800ABDA4(other->mIdBytes[2] == 0) ? 10 : 50;
        }
        if (!attempt) {
            if (MathAngleDiff(heading, motion->mFacing) <= 0x18E38D)
                attempt = PursueGetTackleChance(p, other, position, distance, &chance);
            else chance = 0;
        }
    }
    if (attempt && fn_802372EC(0, 100) < (unsigned int)chance && fn_800E815C(p, 0, 0)) done = 1;
    if (done) return;
    float offset[2];
    Object_80039F5C *reference;
    if (state->mUnknown13 <= 0) {
        state->mUnknown13 = PursueGetMoveDelay(p->mRatings);
        if (block->mUnknown0 == 4 && !fn_8011E88C(p)) {
            int odds = 35;
            if (!fn_801783AC(0)) {
                if (fn_8011F1A4()) {
                    if (!forced) {
                        if (distance < 10.0f || (fn_8011F1A4() && fn_8011F4C8() > 3)) {
                            odds = 80;
                            if (PursueGetTarget() != BallGetCurrentHolder()) odds = 0;
                        } else odds = 0;
                    }
                } else {
                    odds = 70;
                    if (other && (other->mFlags & 0x8000) &&
                        !(fabsf(other->mMotion.mPos.mX) <= fabsf(motion->mPos.mX))) odds = 80;
                }
            } else if (!(distance >= 10.0f) && PursueGetTarget() == BallGetCurrentHolder()) odds = 80;
            if (fn_802372EC(0, 100) < (unsigned int)odds ||
                (!fn_800A7F30((unsigned char)(1 - p->mIdBytes[2])) && fn_800A851C(p->mIdBytes[2], p))) {
                reference = fn_8009BCE8(&block->mUnknown4);
                int mode;
                if (reference->mUnknown1052 == 1) mode = 8;
                else {
                    fn_80227690(offset, &reference->mMotion.mPos, &motion->mPos);
                    mode = !(fn_80237260(0) >= 0.8f) ? 4 : 8;
                }
                if (fn_800E6AC8(p, mode)) done = 1;
                else state->mUnknown13 += 10;
            }
        }
    }
    if (done) return;
    Ball_t *ball = BallGetCurrent();
    if (BallStateGet(ball, 0) == 4) {
        Record_8011F4F8 *record = fn_8011F4F8(BallGetIndex(ball));
        int ballAngle;
        if (other && (fn_801BE648(other->mpUnknown792) == 69 || fn_801BE648(other->mpUnknown792) == 178) &&
            (record->mUnknown1D <= 1 || record->mUnknown1D == 6 || record->mUnknown1D == 7)) {
            position = other->mMotion.mPos;
            position.mZ = 6.0f;
            Object_80039F5C *target = PlyrGet(other->mIdBytes[2], record->mUnknownAByte);
            fn_80227690(offset, &target->mMotion.mPos, &other->mMotion.mPos);
            ballAngle = fn_801CFE40(offset[1], offset[0]);
        } else {
            BallGetPosition(ball, &position);
            Vector_80039F5C velocity;
            BallGetVelocity(ball, &velocity);
            ballAngle = fn_801CFE40(velocity.mY, velocity.mX);
        }
        if (!(position.mZ >= 7.0f) && !(position.mZ <= 1.5f) &&
            !(position.mY >= fn_80177FE0().mY + 2.0f)) {
            if (block->mUnknown0 != 4 && motion->mPos.mY >= fn_80177FE0().mY) return;
            fn_80227690(offset, &position, &motion->mPos);
            if (MathAngleDiff(ballAngle, fn_801CFE40(offset[1], offset[0])) > 0x78E38E) {
                int facing = motion->mFacing;
                if (MathAngleDiff(facing, fn_801CFE40(offset[1], offset[0])) <= 0x3FFFFF &&
                    !(fn_802270A4(offset) >= 6.0f) && fn_802372EC(0, 100) <= 49) fn_800F2C1C(p, 0);
            }
        }
    } else if (block->mUnknown0 == 4 && other) {
        reference = fn_8009BCE8(&block->mUnknown4);
        fn_80227690(delta, &reference->mMotion.mPos, &motion->mPos);
        int angle = MathAngleDiff(heading, fn_801CFE40(delta[1], delta[0]));
        if (angle > 0x471C72) {
            int mode = ((state->mUnknown8 - motion->mFacing) & 0xFFFFFF) > 0x800000;
            if (angle <= 0x5FFFFF) fn_800E6AC8(p, mode);
            else fn_8011E240(reference);
        }
    }
}

extern "C" void PursueAvoidPlayers(Object_80039F5C *p, PursueState_t *state, float unusedDistance)
{
    Object_800B26B0 *motion = &p->mMotion;
    Vector_80039F5C target;
    int b = 0;
    int a = 0;
    int step = 0;
    target.mX = target.mY = target.mZ = 0.0f;
    if (p->mUnknown1032 == 4) return;
    float distance;
    Object_80039F5C *other = fn_80124C28(p, &distance, 0x38E38E, 3.0f, 0.5f, state->mUnknown8);
    if (!other) return;
    float limit = 3.0f;
    if (distance >= limit) return;
    if (other == BallGetCurrentHolder() && !fn_801787A0()) return;
    int inside = 0;
    int mode = fn_8011E9B4(other);
    if (other->mIdBytes[2] == p->mIdBytes[2] && !mode) limit *= 0.5f;
    if (distance >= limit) return;
    float delta[2];
    if (mode) {
        Object_80039F5C *reference = fn_8009BCE8(&other->mUnknown1036);
        target.mX = (other->mMotion.mPos.mX + reference->mMotion.mPos.mX) * 0.5f;
        target.mY = (other->mMotion.mPos.mY + reference->mMotion.mPos.mY) * 0.5f;
        fn_80227690(delta, &other->mMotion.mPos, &motion->mPos);
        a = fn_801CFE40(delta[1], delta[0]);
        fn_80227690(delta, &reference->mMotion.mPos, &motion->mPos);
        b = fn_801CFE40(delta[1], delta[0]);
        int span = (a - b) & 0xFFFFFF;
        if ((span <= 0x7FFFFF && ((state->mUnknown8 - b) & 0xFFFFFF) <= 0x7FFFFF) ||
            (span > 0x800000 && ((state->mUnknown8 - b) & 0xFFFFFF) > 0x800000)) {
            if (MathAngleDiff(a - b, 0) > MathAngleDiff(state->mUnknown8 - b, 0)) inside = 1;
        }
    } else {
        target.mX = other->mMotion.mPos.mX;
        target.mY = other->mMotion.mPos.mY;
        target.mZ = other->mMotion.mPos.mZ;
        target.mX += other->mMotion.mUnknown40 * 15.0f;
        target.mY += other->mMotion.mUnknown44 * 15.0f;
    }
    fn_80227690(delta, &target, &motion->mPos);
    int heading = fn_801CFE40(delta[1], delta[0]);
    float weight = distance * 0.4f;
    if (!(weight <= 1.0f)) weight = 1.0f;
    BallGetCurrentHolder();
    if (MathAngleDiff(heading, state->mUnknown8) <= 0x271C70) {
        if (((heading - state->mUnknown8) & 0xFFFFFF) > 0x800000) {
            step = (int)((1.0f - weight) * 3728270.0f);
            if (mode && inside) {
                if (((a - heading) & 0xFFFFFF) <= 0x7FFFFF) step += MathAngleDiff(a, state->mUnknown8);
                else step += MathAngleDiff(b, state->mUnknown8);
            }
        } else {
            step = (int)(-((1.0f - weight) * 3728270.0f));
            if (mode && inside) {
                if (((a - heading) & 0xFFFFFF) > 0x800000) step -= MathAngleDiff(a, state->mUnknown8);
                else step -= MathAngleDiff(b, state->mUnknown8);
            }
        }
        int difference = MathAngleDiff(state->mUnknown8 + step, motion->mFacing);
        if (difference > 0x11C71C) {
            float scale = fn_801CFB94(difference / 2);
            state->mUnknown16 = 0;
            state->mUnknown0 = scale * 0.72f;
        } else if (!(distance >= 2.1f) && MathAngleDiff(heading, motion->mFacing) <= 0x1FFFFF) {
            state->mUnknown16 = 0;
        }
    }
    state->mUnknown8 = (state->mUnknown8 + step) & 0xFFFFFF;
}

extern "C" void PursueCloseOnTarget(Object_80039F5C *p, PursueState_t *pState, float distance, Object_80039F5C *pOther)
{
    if (p->mUnknown1032 != 4 && pOther != 0 && distance < 4.0f && fn_801BE648(pOther->mpUnknown792) != 69
        && fn_801BE648(pOther->mpUnknown792) != 178
        && (MathAngleDiff(p->mMotion.mFacing, pOther->mMotion.mFacing) > 0x355555 || PlayerActionAnimIsPassReady(pOther) != 0)) {
        Vec2_t delta;
        int angle;

        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(angle, pOther->mMotion.mUnknown32) <= 0x1FFFFF) {
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
            if (!(p->mFlags & 0x4000) && PlayerActionAnimIsPassReady(pOther) != 0
                && MathAngleDiff(p->mMotion.mFacing, pOther->mMotion.mUnknown32) <= 0x1FFFFF) {
                int diff;

                pState->mUnknown16 = 1;
                diff = MathAngleDiff(angle, pState->mUnknown8);
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

extern "C" int PursueSteerKind0(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState, Lookup_8012078C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Vec2_t delta;
    int target;
    int diff;
    int turn;

    fn_80227690(&delta, &pos, pMotion);
    target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    diff = MathAngleDiff(angle, target);
    if (pMotion->mPos.mY < pos.mY || distance > 5.5f
        || (pOther != 0 && (pOther->mUnknown528.mUnknown15 == 1 || pOther->mUnknown528.mUnknown15 == 5))) {
        pState->mUnknown16 = 1;
        switch (p->mUnknown2914) {
        case 10:
        case 11:
        case 12: {
            int flag = 0;
            if (pos.mY > fn_80177FE0().mY) {
                flag = BallStateGet(BallGetCurrent(), 0) == 4;
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
            if ((pOther->mFlags & 0x200000) || PlayerActionAnimIsPassReady(pOther) != 0) {
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
        if (MathAngleDiff(target, pMotion->mFacing) > 0x11C71C) {
            pState->mUnknown16 = 0;
        }
    }
    if (pOther != 0 && pMotion->mPos.mY < pos.mY && MathAngleDiff(angle2, 0xC00000) <= 0x271C70) {
        fn_80227690(&delta, &pos, pMotion);
        target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        diff = MathAngleDiff(angle, target);
        if (((angle - target) & 0xFFFFFF) > 0x800000) {
            angle = (angle + diff / 2) & 0xFFFFFF;
        } else {
            angle = (angle - diff / 2) & 0xFFFFFF;
        }
    }
    return angle;
}

extern "C" void PursueSquareHeading(Object_80039F5C *p, int *pAngle, Vector_80039F5C pos, int angle2)
{
    if (fn_801783AC(0) == 0 && fn_8011F1A4() != 0 && fn_8011F4C8() > 3
        && ((fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) == 0 && MathAngleDiff(*pAngle, 0) <= 0x3FFFFF)
            || (fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) && MathAngleDiff(*pAngle, 0) > 0x400000))) {
        Point_8017886C point;

        point = fn_80177FE0();
        if (fabsf(point.mX - p->mMotion.mPos.mX) < 5.0f && p->mMotion.mPos.mY - point.mY < 5.0f && pos.mY < point.mY
            && pos.mY > point.mY - 10.0f && MathAngleDiff(angle2, 0x400000) <= 0x5FFFFF) {
            if (MathAngleDiff(*pAngle, 0) <= 0x3FFFFF) {
                if ((*pAngle & 0xFFFFFF) > 0x400000) {
                    *pAngle = 0;
                }
            } else if ((*pAngle & 0xFFFFFF) > 0x800000) {
                *pAngle = 0x800000;
            }
        }
    }
}

extern "C" int PursueSteerKind2(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState, Lookup_8012078C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    int mode = fn_801486A0();
    Object_800B26B0 *pMotion = &p->mMotion;

    if (pOther != 0) {
        Vec2_t delta;

        if ((distance > 3.0f && pMotion->mPos.mY < fn_80177FE0().mY && PlayerActionAnimIsPassReady(pOther) != 0 && mode != 2)
            || (mode == 2 && distance < 8.0f)) {
            int target;
            int diff;

            fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
            target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            diff = MathAngleDiff(angle, target);
            if (((angle - target) & 0xFFFFFF) > 0x800000) {
                angle = (angle + diff / 2) & 0xFFFFFF;
            } else {
                angle = (angle - diff / 2) & 0xFFFFFF;
            }
            pState->mUnknown16 = 1;
        } else {
            if (pos.mY < fn_80177FE0().mY + 3.0f) {
                if (pContext->mpUnknown4[0] != p->mIdBytes[1]
                    && pContext->mpUnknown4[pContext->mUnknown16 - 1] != p->mIdBytes[1]) {
                    PursueSquareHeading(p, &angle, pos, angle2);
                }
            }
            if (pMotion->mPos.mY < pos.mY || distance > 5.5f || pOther->mUnknown528.mUnknown15 == 1
                || pOther->mUnknown528.mUnknown15 == 5 || MathAngleDiff(angle, pMotion->mFacing) <= 0x11C71B) {
                pState->mUnknown16 = 1;
            }
            if (MathAngleDiff(pOther->mMotion.mUnknown32, 0xC00000) <= 0x1FFFFF) {
                fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
                angle = fn_801CFE40(delta.mY, delta.mX);
                pState->mUnknown16 = 0;
            }
        }
    }
    return angle;
}

extern "C" int PursueSteerKind3(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState, Lookup_8012078C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int done = 0;

    if (pOther != 0) {
        Vec2_t delta;
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
                if ((pOther->mFlags & 0x200000) || PlayerActionAnimIsPassReady(pOther) != 0) {
                    turn = 1;
                }
            }
        }
        if (turn != 0) {
            int diff = MathAngleDiff(angle, target);
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
    if (done == 0 && fn_8011E188() < _Pursue_fKind3SidelineTime) {
        if ((pMotion->mPos.mX > 0.0f && MathAngleDiff(angle, 0x800000) <= 0x3FFFFF)
            || (pMotion->mPos.mX < 0.0f && MathAngleDiff(angle, 0) <= 0x3FFFFF)) {
            if (pMotion->mPos.mX > 0.0f) {
                angle = (int)(_Pursue_fKind3RightHeadingDeg * 46603.38f);
            } else {
                angle = (int)(_Pursue_fKind3LeftHeadingDeg * 46603.38f);
            }
        }
    }
    return angle;
}

extern "C" int PursueSteerKind4(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState, Lookup_8012078C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int turn;

    if (distance > 4.0f && distance < 12.0f && (pMotion->mFacing & 0xFFFFFF) > 0x800000
        && pMotion->mPos.mY > pos.mY && fabsf(p->mMotion.mPos.mX) < fabsf(pos.mX)
        && fabsf(p->mMotion.mPos.mX) < fn_80178A08() - 1.0f) {
        if (angle > 0xC00000) {
            angle -= MathAngleDiff(0, angle) / 2;
        } else {
            angle += MathAngleDiff(0x800000, angle) / 2;
        }
    }
    turn = 0;
    if (pOther != 0 && distance > 3.0f) {
        if (pMotion->mPos.mY < fn_80177FE0().mY + 2.0f) {
            if ((pOther->mFlags & 0x200000) || PlayerActionAnimIsPassReady(pOther) != 0) {
                turn = 1;
            }
        }
    }
    if (turn != 0) {
        Vec2_t delta;
        int target;
        int diff;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        target = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        diff = MathAngleDiff(angle, target);
        if (((angle - target) & 0xFFFFFF) > 0x800000) {
            angle = (angle + diff / 2) & 0xFFFFFF;
        } else {
            angle = (angle - diff / 2) & 0xFFFFFF;
        }
        pState->mUnknown16 = 1;
    }
    return angle;
}

extern "C" int PursueSteerKind6(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState, Lookup_8012078C *pContext,
                           int angle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;

    pState->mUnknown16 = 1;
    if (distance > 10.0f) {
        float width;
        float offset;
        float step;
        unsigned char i;
        Vec2_t target;
        Vec2_t dir;

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

extern "C" void PursueAdjustHeading(Object_80039F5C *p, PursueState_t *pState, Object_80039F5C *pOther, Lookup_8012078C *pContext,
                            int *pAngle, Vector_80039F5C pos, float distance, int angle2)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Vec2_t delta;

    if (pOther != 0 && pMotion->mPos.mY > pos.mY && pContext->mpUnknown12[p->mIdBytes[1]] != 6
        && MathAngleDiff(angle2, 0x400000) <= 0x31C71B && fabsf(p->mMotion.mPos.mX) < fabsf(pos.mX)
        && fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 1.0f) {
        fn_80227690(&delta, &pos, pMotion);
        if (p->mMotion.mPos.mX > 0.0f) {
            *pAngle -= MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), *pAngle) / 4;
        } else {
            *pAngle += MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), *pAngle) / 4;
        }
    }
    if (pOther != 0) {
        int turn = 0;

        switch (fn_801BE648(pOther->mpUnknown792)) {
        case 67:
        case 225:
        case 227:
            if (MathAngleDiff(angle2, 0xC00000) <= 0x3FFFFF) {
                turn = 1;
            }
            break;
        }
        if (turn != 0) {
            int angle;
            int diff;

            fn_80227690(&delta, &pos, pMotion);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            diff = MathAngleDiff(*pAngle, angle);
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

extern "C" int PursueIsInCarrierWindow(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int found = 0;
    int low = (int)(_Pursue_uWindowMinDeg * 46603.38f);
    int high = (int)(_Pursue_uWindowMaxDeg * 46603.38f);
    Object_80039F5C *pCarrier = BallGetCurrentHolder();

    if (p != 0 && pCarrier != 0 && pCarrier->mMotion.mUnknown28 / gPlyrMoveFwdSpeed > 0.14f) {
        int widen;
        int reach;
        int anim;

        if (p->mUnknown528.mUnknown15 == 4 || p->mUnknown528.mUnknown15 == 5) {
            widen = (int)(_Pursue_sWindowWidenDeg * 46603.38f);
        } else {
            widen = 0;
        }
        if (p->mUnknown528.mUnknown15 == 4 || p->mUnknown528.mUnknown15 == 5) {
            reach = _Pursue_sWindowReach;
        } else {
            reach = 0;
        }
        anim = fn_801BE648(pCarrier->mpUnknown792);
        if (pCarrier != 0 && anim != 84 && anim != 69 && anim != 178 && anim != 77
            && (unsigned int)pCarrier->mMotion.mUnknown32 <= 0x800000) {
            Vec2_t delta;
            int angle;
            float distance;

            fn_80227690(&delta, &p->mMotion.mPos, &pCarrier->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (MathAngleDiff(pCarrier->mMotion.mUnknown32, 0) <= 0x3FFFFF) {
                low = (int)(low - (int)(_Pursue_fWindowSkewNearDeg * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
                high = (int)(high - (int)(_Pursue_fWindowSkewFarDeg * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
            } else {
                low = (int)(low - (int)(_Pursue_fWindowSkewFarDeg * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
                high = (int)(high - (int)(_Pursue_fWindowSkewNearDeg * 46603.38f) * fn_801CFB94(pCarrier->mMotion.mUnknown32));
            }
            distance = fn_8022710C(&delta);
            if (angle >= low - widen && angle <= high + widen && distance >= _Pursue_sWindowMinDist - reach
                && distance <= _Pursue_sWindowMaxDist + reach) {
                found = 1;
            }
        }
    }
    return found;
}

extern "C" void PursueSetCloseGait(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState)
{
    if (pState->mUnknown0 > 0.72f || pState->mUnknown16 == 1) {
        pState->mUnknown16 = 5;
    } else {
        pState->mUnknown16 = 4;
    }
}

extern "C" int PursueCheckCarrierWindow(Object_80039F5C *p, Object_80039F5C *pOther, PursueState_t *pState)
{
    if (pOther != 0 && PursueIsInCarrierWindow(p, pOther) == 1) {
        PursueSetCloseGait(p, pOther, pState);
        return 1;
    }
    return 0;
}

extern "C" void PursueUpdateSpeed(Object_80039F5C *p, PursueState_t *pState, Object_80039F5C *pOther, int angle, int angle2,
                            float distance)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int diff = MathAngleDiff(angle, pMotion->mFacing);
    Vec2_t delta;

    if (diff > 0x177777) {
        if (pOther != 0 && !(pOther->mFlags & 0x200000) && PlayerActionAnimIsPassReady(pOther) == 0) {
            if (distance < 4.0f) {
                pState->mUnknown0 = fn_801CFB94(diff / 2) * 0.4f;
            } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
                float scale = 0.4f;
                scale += fn_801CFB94(MathAngleDiff(pMotion->mFacing, angle2) / 2) * (0.72f - 0.4f);
                pState->mUnknown0 = scale * fn_801CFB94(diff / 2);
            }
        } else {
            pState->mUnknown0 = fn_801CFB94(diff / 2) * 0.72f;
        }
        pState->mUnknown16 = 0;
    }
    if (!(p->mFlags & 0x20000) && pOther != 0 && pOther->mpState->mId == 35 && distance < 5.0f
        && pMotion->mPos.mY > pOther->mMotion.mPos.mY
        && MathAngleDiff(pOther->mMotion.mFacing, 0xC00000) <= 0x3C71C6) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (MathAngleDiff(pMotion->mUnknown32, fn_801CFE40(delta.mY, delta.mX)) > 0x200000
            && MathAngleDiff(pMotion->mUnknown32, pOther->mpState->mUnknown2 == 1 ? 0x800000 : 0) > 0x400000) {
            if (pState->mUnknown0 > 0.72f) {
                pState->mUnknown0 = 0.4f;
            }
            pState->mUnknown16 = 4;
        }
    }
}

extern "C" void PursueChooseHeading(Object_80039F5C *p, PursueState_t *pState, Lookup_8012078C *pContext, int angle,
                            Vector_80039F5C pos, float distance, int angle2)
{
    Object_80039F5C *pOther = PursueGetTarget();
    int kind = pContext->mpUnknown12[p->mIdBytes[1]];
    Ball_t *pBall = BallGetCurrent();

    pState->mUnknown16 = 0;
    pState->mUnknown0 = 1.0f;
    pState->mUnknown41 = PursueShouldPlayBall(p);
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
            angle = PursueSteerKind0(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 2:
            angle = PursueSteerKind2(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 3:
            angle = PursueSteerKind3(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 4:
            angle = PursueSteerKind4(p, pOther, pState, pContext, angle, pos, distance, angle2);
            break;
        case 6:
            angle = PursueSteerKind6(p, pOther, pState, pContext, angle, pos, distance, angle2);
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
        PursueAdjustHeading(p, pState, pOther, pContext, &angle, pos, distance, angle2);
        pState->mUnknown8 = angle & 0xFFFFFF;
        PursueUpdateSpeed(p, pState, pOther, angle, angle2, distance);
    }
}

extern "C" Object_80039F5C *PursueGetTarget(void)
{
    Object_80039F5C *p = BallGetCurrentHolder();

    if (p != 0) {
        if (p->mUnknown2914 == 0 && (p->mpState->mId == 25 || p->mpState->mId == 26)) {
            Object_80039F5C *pOther = BallGetCurrentTarget();
            if (pOther != 0) {
                p = pOther;
            }
        }
    } else if (BallStateGet(BallGetCurrent(), 0) == 3) {
        p = BallGetCurrentTarget();
    }
    return p;
}

extern "C" void PursueTryBlockReaction(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_80170374 *pBlock = &p->mUnknown560;
    int found = 0;
    Object_80039F5C *pTarget;
    Vec2_t delta;

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
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), pTarget->mMotion.mUnknown32) <= 0x3FFFFF) {
            fn_80111354(p);
        }
    } else if (fn_802372EC(0, 100) < 50) {
        fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), pTarget->mMotion.mUnknown32) <= 0x3FFFFF) {
            fn_800E96EC(p, pTarget);
        }
    }
}

extern "C" int PursueUpdateHold(Object_80039F5C *p, PursueState_t *pState, Vector_80039F5C target)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
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
        value = BallStateGet(BallGetCurrent(), 0);
        if (value == 4) {
            BallGetLandingPoint(BallGetCurrent(), &pos);
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
                if (pMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.2f) {
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

extern "C" void PursueAimAtTarget(Object_80039F5C *p, Object_80039F5C *pOther, float distance)
{
    Object_800B26B0 *pMotion;
    Vec2_t delta;
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
    if (MathAngleDiff(angle, pMotion->mFacing) > 0x51C71B && distance >= 1.0f) {
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

extern "C" int PursueClipHeading(Object_800B26B0 *pMotion, int angle, Vector_80039F5C target, Vector_80039F5C offset)
{
    Vec2_t dir;
    float d;
    float s;

    fn_80227538(&dir, angle, pMotion->mUnknown28);
    if (pMotion->mPos.mY > target.mY) {
        if (fabsf(target.mX) < fn_80178A08()) {
            d = pMotion->mPos.mY - target.mY;
            if (dir.mY < 0.0f) {
                dir.mY = -dir.mY;
                s = d / fabsf(dir.mY + offset.mY);
                dir.mX = dir.mX * s + pMotion->mPos.mX;
                if (fabsf(dir.mX) > fn_80178A08() - _Pursue_fSidelineMargin) {
                    dir.mX = CLAMP(dir.mX, _Pursue_fSidelineMargin - fn_80178A08(), fn_80178A08() - _Pursue_fSidelineMargin);
                    dir.mY = target.mY;
                    fn_80227690(&dir, &dir, pMotion);
                    angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
                }
            }
            if (target.mY < fn_80178A2C() && BallGetCurrentHolder() != 0) {
                fn_80227538(&dir, angle, pMotion->mUnknown28);
                if (dir.mX != 0.0f) {
                    d = pMotion->mPos.mX - target.mX;
                    s = d / dir.mX;
                    s = fabsf(s);
                    dir.mY = dir.mY * s + pMotion->mPos.mY;
                    if (dir.mY > fn_80178A2C()) {
                        dir.mX = target.mX;
                        dir.mY = fn_80178A2C();
                        fn_80227690(&dir, &dir, pMotion);
                        angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
                    }
                }
            }
        }
    } else if (target.mY < fn_80178A2C() && BallGetCurrentHolder() != 0 && pMotion->mPos.mY < fn_80178A2C()
               && dir.mX != 0.0f && dir.mY > 0.0f) {
        d = pMotion->mPos.mX - target.mX;
        s = d / dir.mX;
        s = fabsf(s);
        dir.mY = dir.mY * s + pMotion->mPos.mY;
        if (dir.mY > fn_80178A2C()) {
            dir.mX = target.mX;
            dir.mY = fn_80178A2C();
            fn_80227690(&dir, &dir, pMotion);
            angle = fn_801CFE40(dir.mY, dir.mX) & 0xFFFFFF;
        }
    }
    return angle;
}

extern "C" void PursueLeadTarget(Object_800B26B0 *pMotion, Vector_80039F5C target, Vector_80039F5C dir,
                            Vector_80039F5C *pOut)
{
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    float dx;

    pOut->mX = dir.mX;
    pOut->mY = dir.mY;
    pOut->mZ = dir.mZ;
    dx = fabsf(target.mX - pMotion->mPos.mX);
    if (pCarrier != 0 && _Pursue_bLeadTarget != 0 && PlayerMoveGetKind(pCarrier) == 0 && pMotion->mUnknown44 > 0.0f
        && dx > _Pursue_fLeadMinGap) {
        int angle = MathAngleDiff(fn_801CFE40(dir.mY, dir.mX), 0x400000);
        float scale;
        float length;

        if (angle > 0x400000) {
            angle = 0x400000;
        }
        scale = angle / 4194304.0f;
        length = fn_802270A4(&dir);
        if (_Pursue_bLeadByAngle == 0) {
            scale = 1.0f;
        }
        pOut->mY += length * (dx / _Pursue_fLeadWidth * (scale * _Pursue_fLeadScale));
    }
}

extern "C" void PursueMatchTarget(Object_80039F5C *p, Object_80039F5C *pOther, Vec2_t *pVelocity, int *pAngle,
                            float *pSpeed, Vector_80039F5C *pTarget, float distance)
{
    if (fn_801BE648(pOther->mpUnknown792) == 74) {
        if (distance < 10.0f) {
            Object_800B26B0 *pMotion = &p->mMotion;
            Vec2_t velocity;
            int diff = MathAngleDiff(*pAngle, pOther->mUnknown512.mUnknown4);

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
                float speed = PlyrMoveGetRatedSpeed(pOther, 0.4f, 0.98f);
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
                if (pLinked != 0 && fn_8022781C(&pLinked->mMotion.mPos, &pOther->mMotion.mPos) < _Pursue_fLinkedRange) {
                    pVelocity->mX = pLinked->mMotion.mUnknown40;
                    pVelocity->mX = pLinked->mMotion.mUnknown44;
                    *pAngle = pLinked->mMotion.mUnknown32;
                    *pSpeed = pLinked->mMotion.mUnknown28;
                }
            }
        }
    }
}

extern "C" int PursueEnter(Object_80039F5C *p)
{
    PursueState_t *pState = (PursueState_t *)&p->mUnknown336;

    pState->mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
    pState->mUnknown4 = -1.0f;
    pState->mUnknown16 = 0;
    pState->mUnknown8 = p->mMotion.mFacing;
    pState->mUnknown12 = 0;
    pState->mUnknown13 = PursueGetMoveDelay(p->mRatings);
    pState->mUnknown14 = PursueGetTackleDelay(p);
    pState->mUnknown15 = (int)(p->mRatings[5] / 255.0f * 15.0f + 3.0f);
    pState->mUnknown40 = 0;
    pState->mUnknown42 = p->mpState->mUnknown1;
    fn_8009A8D4(pState->mUnknown20);
    fn_8010A2DC(p, 0, 0);
    return 0;
}

extern "C" int PursueUpdate(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion;
    PursueState_t *pState;
    Object_80039F5C *pOther;
    Ball_t *pBall;
    Lookup_8012078C *pLookup;
    Message_800F01CC message;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    Vector_80039F5C dir;
    int angle;
    float speed;
    float distance;
    int result = 0;

    pMotion = &p->mMotion;
    pState = (PursueState_t *)&p->mUnknown336;
    if (fn_801486A0() == 0) {
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 97;
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    }
    if (fn_8009FB60(p) != 0) {
        return 1;
    }
    fn_8010A2DC(p, 0, -1);
    pOther = PursueGetTarget();
    pBall = BallGetCurrent();
    if (pOther != 0) {
        Object_800B26B0 *pOtherMotion = &pOther->mMotion;

        pos.mX = pOtherMotion->mPos.mX;
        pos.mY = pOtherMotion->mPos.mY;
        velocity.mX = pOtherMotion->mUnknown40;
        velocity.mY = pOtherMotion->mUnknown44;
        velocity.mZ = pOtherMotion->mUnknown48;
        speed = pOtherMotion->mUnknown28;
        angle = pOtherMotion->mUnknown32;
        distance = fn_8022781C(pMotion, &pos);
        PursueMatchTarget(p, pOther, (Vec2_t *)&velocity, &angle, &speed, &pos, distance);
    } else {
        if (BallGetLandingPoint(pBall, &pos) != 0) {
            Vector_80039F5C ballPos;
            int high = 0;

            velocity.mX = velocity.mY = velocity.mZ = 0.0f;
            BallGetPosition(pBall, &ballPos);
            if (BallStateGet(pBall, 0) == 4 && ballPos.mY < fn_80177FE0().mY) {
                high = pos.mY > fn_80177FE0().mY;
            }
            if (high) {
                pOther = BallGetCurrentLastHolder();
                if (pOther != 0) {
                    pos.mX = pOther->mMotion.mPos.mX;
                    pos.mY = pOther->mMotion.mPos.mY;
                    velocity.mX = pOther->mMotion.mUnknown40;
                    velocity.mY = pOther->mMotion.mUnknown44;
                    velocity.mZ = pOther->mMotion.mUnknown48;
                    pOther = 0;
                } else {
                    int intercept = 0;
                    Object_80039F5C *pReceiver = BallGetTarget(pBall);

                    if (pReceiver != 0) {
                        float selfDistance = fn_8022781C(&pos, &p->mMotion.mPos);
                        float receiverDistance = fn_8022781C(&pos, &pReceiver->mMotion.mPos);

                        if (selfDistance < 10.0f && receiverDistance > 8.0f && fn_8009F0B8(p, 0x2AAAAA) != 0) {
                            intercept = fn_802372EC(0, 255) < (unsigned int)p->mRatings[8];
                        }
                        if (intercept) {
                            fn_801C1F94(&message, 0, sizeof(message));
                            message.mId = 57;
                            message.mUnknown1[0] = BallGetIndex(pBall);
                            fn_800F053C(0, p->mpState, &message, p);
                            return 1;
                        }
                    }
                }
            }
        } else {
            BallGetPosition(pBall, &pos);
            BallGetVelocity(pBall, &velocity);
        }
        speed = fn_802270D4(&velocity);
        angle = fn_801CFE40(velocity.mY, velocity.mX);
        distance = fn_8022781C(pMotion, &pos);
    }
    pLookup = fn_8012078C();
    if ((p->mFlags & 0x4000) == 0 && (fn_801486A0() != 0 || p->mUnknown8 == 0xFF)) {
        if (fn_800A5DD0(p) == 0 && pOther != 0 && p->mIdBytes[2] == fn_80178308()) {
            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 33;
            fn_800F053C(0, p->mpState, &message, p);
            return 0;
        }
        if (--pState->mUnknown15 <= 0) {
            pState->mUnknown15 = (int)(p->mRatings[5] / 255.0f * 15.0f + 3.0f);
            result = fn_8009F7A4(p, 0) == 1;
        }
        if (--pState->mUnknown12 <= 0) {
            float speed;
            int ok;
            float dirLength;
            int dirAngle;
            int facing;

            pState->mUnknown12 = (255 - p->mRatings[5]) >> 4;
            pState->mUnknown12 = fn_800AC980(p, pState->mUnknown12);
            pState->mUnknown12 = fn_8009AF00(p->mIdBytes[2], pState->mUnknown12);
            if (fn_801486A0() == 2 && fn_80178D70(p->mIdBytes[2]) == 1) {
                pState->mUnknown12 = (int)(pState->mUnknown12 * 0.1f);
            }
            if (pOther != 0 && fn_800B65A0(p->mIdBytes[2]) != 0xFF && fn_800B65A0(pOther->mIdBytes[2]) == 0xFF
                && fn_80177C38() == 0) {
                pState->mUnknown12 -= (signed char)MIN(pState->mUnknown12, pState->mUnknown12 * fn_8016B938());
                if (fn_8011F1CC() != 0 && (pOther->mFlags & 0x8000) != 0) {
                    pState->mUnknown12 -= (signed char)MIN(pState->mUnknown12, pState->mUnknown12 * fn_8016B974());
                }
            }
            speed = pMotion->mUnknown28;
            if (speed < gPlyrMoveFwdSpeed * 0.4f) {
                speed = gPlyrMoveFwdSpeed * 0.4f;
            }
            PursueLeadTarget(pMotion, pos, velocity, &dir);
            ok = 1;
            dirLength = fn_802270A4(&dir);
            dirAngle = fn_801CFE40(dir.mY, dir.mX);
            if (pOther != 0) {
                if (fn_801486A0() == 2) {
                    if (dirLength < PlyrMoveGetRatedSpeed(pOther, 0.4f, 1.0f)) {
                        ok = distance <= 3.0f;
                    }
                } else if (pOther->mpState->mId == 26 || pOther->mpState->mId == 27) {
                    ok = 0;
                }
            }
            if (ok) {
                facing = fn_80120794(pMotion, &pos, &dir, speed, dirLength, dirAngle, distance);
            } else {
                Vec2_t delta;

                fn_80227690(&delta, pMotion, &pOther->mMotion.mPos);
                facing = (fn_801CFE40(delta.mY, delta.mX) - 0x800000) & 0xFFFFFF;
            }
            PursueChooseHeading(p, pState, pLookup, facing, pos, distance, angle & 0xFFFFFF);
            PursueAvoidPlayers(p, pState, distance);
            pState->mUnknown8 = PursueClipHeading(pMotion, pState->mUnknown8, pos, dir);
            if (pState->mUnknown41 == 1 && BallStateGet(pBall, 0) == 3) {
                int handle = fn_80099734(p, pBall, 0, 2, pState->mUnknown20, 1, 0, 0, PlyrRollContestedCatch(p), 120.0f);

                if (handle != 0x1FFFFFFF && fn_80099F04(p, handle, BallGetIndex(pBall)) == 1) {
                    return 0;
                }
            }
            if (fn_800E1584(p) != 0) {
                return 0;
            }
        }
        pState->mUnknown0 = MAX(pState->mUnknown0, 0.0f);
        pState->mUnknown4 = MAX(pState->mUnknown4, 0.0f);
        PursueCheckCarrierWindow(p, pOther, pState);
    }
    if (fn_800A5C04(p, pState->mUnknown8, pState->mUnknown8) != 0) {
        result = 0;
    } else {
        if ((p->mFlags & 0x4000) == 0 && (fn_801486A0() != 0 || p->mUnknown8 == 0xFF)) {
            if (PursueUpdateHold(p, pState, pos) != 0) {
                p->mUnknown512.mUnknown15 = pState->mUnknown16;
                if (pState->mUnknown4 > 0.0f) {
                    if (PlyrMoveIsFacingHeading(p) != 0) {
                        p->mUnknown512.mUnknown14 = 10;
                        p->mUnknown512.mUnknown8 = pState->mUnknown8;
                        p->mUnknown512.mUnknown4 = pState->mUnknown8;
                        p->mUnknown512.mUnknown0 = pState->mUnknown4;
                    } else {
                        p->mUnknown512.mUnknown14 = 1;
                        p->mUnknown512.mUnknown8 = pState->mUnknown8;
                        p->mUnknown512.mUnknown4 = pState->mUnknown8;
                        p->mUnknown512.mUnknown0 = 0.0f;
                    }
                } else {
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = pState->mUnknown8;
                    p->mUnknown512.mUnknown4 = pState->mUnknown8;
                    p->mUnknown512.mUnknown0 = pState->mUnknown0;
                }
            } else {
                PursueCloseOnTarget(p, pState, distance, pOther);
                p->mUnknown512.mUnknown15 = pState->mUnknown16;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pState->mUnknown8;
                p->mUnknown512.mUnknown4 = pState->mUnknown8;
                p->mUnknown512.mUnknown0 = pState->mUnknown0;
            }
            PursueTryMoves(p, pOther, pos, distance, pLookup->mpUnknown12[p->mIdBytes[1]]);
        } else if (p->mUnknown512.mUnknown15 != 1 && p->mUnknown512.mUnknown15 != 4
                   && p->mUnknown512.mUnknown15 != 5) {
            pState->mUnknown16 = 0;
            PursueCloseOnTarget(p, pState, distance, pOther);
            p->mUnknown512.mUnknown15 = pState->mUnknown16;
        }
        if (p->mpState->mId == 2) {
            PursueAimAtTarget(p, pOther, distance);
            PursueTryBlockReaction(p, pOther);
        }
    }
    return result;
}

extern "C" int PursueExit(void)
{
    return 1;
}

extern "C" int PursueNotify(Object_80039F5C *p, int message)
{
    if (message == 1) {
        PursueState_t *pState = (PursueState_t *)&p->mUnknown336;
        pState->mUnknown8 = (pState->mUnknown8 + 0x800000) & 0xFFFFFF;
    }
    return 0;
}

extern "C" int PursueGetTackleChance(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C pos, float distance,
                           int *pOut)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    int result = 0;

    *pOut = _Pursue_iTackleChance;
    if (pOther == 0 || fn_80124714(p, pOther, 0) != 0) {
        if (pOther != 0 && pOther->mIdBytes[2] != p->mIdBytes[2] && (pOther->mFlags & 0x10000) != 0
            && distance < _Pursue_fTackleRange * 0.5f && fn_801486A0() != 0) {
            result = 1;
            *pOut = PursueGetCloseTackleChance(pOther);
        } else if (pOther == 0 || pOther->mIdBytes[2] == p->mIdBytes[2]) {
            result = 0;
        } else {
            float range = _Pursue_fTackleRange;

            if (MathAngleDiff(pOther->mMotion.mFacing, pMotion->mFacing) <= 0x1FFFFF) {
                range = _Pursue_fBehindTackleRange;
            }
            if (distance < range) {
                unsigned int odds = _Pursue_uTackleOdds;
                int boosted = 0;

                if (fn_8011F1CC() != 0 && (pOther->mUnknown2914 == 0 || pOther->mpState->mId == 18)) {
                    odds += (unsigned int)(odds * fn_8016B974());
                    boosted = 1;
                }
                if (fn_802372EC(0, 100) < odds) {
                    result = 1;
                }
                if (pMotion->mPos.mY < pos.mY) {
                    *pOut = _Pursue_iAheadTackleChance;
                    if (fabsf(pMotion->mPos.mX - pos.mX) < fabsf(pMotion->mPos.mY - pos.mY) * 0.5f) {
                        *pOut = _Pursue_iLaneTackleChance;
                        if (pMotion->mPos.mY > fn_80178A2C() - 5.0f) {
                            odds = _Pursue_uLaneLineOdds;
                        } else {
                            odds = _Pursue_uLaneOdds;
                        }
                        if (boosted) {
                            odds += (unsigned int)(odds * fn_8016B974());
                        }
                        if (fn_802372EC(0, 100) < odds) {
                            result = 1;
                        }
                    }
                }
                if ((pOther->mFlags & 0x800) != 0 && distance < _Pursue_fNoTackleRange) {
                    result = 0;
                }
            }
        }
    }
    return result;
}
