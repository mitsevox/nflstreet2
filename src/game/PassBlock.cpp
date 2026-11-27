/* Pass-blocking state of an offensive player (entry 31 of the player state handler table).
   Early in the play the blocker drops back toward a spot off the line, facing a defender that
   comes close; it then protects the ball holder, or the nearest receiver still at the line,
   by squaring up to the defender it is assigned to, deciding when to stay in front of it and
   when to cut it off, and without a defender takes a pocket spot by its lineup slot. */

#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Input_800B6D34.h"
#include "game/ScrmGetBallSpot.h"
#include <string.h>
#include "game/Ball.h"

/* Player block at +336 in the pass-blocking state. */
struct PassBlockControl_t {
    float mUnknown0, mUnknown4, mUnknown8;
    int mUnknownC, mUnknown10, mUnknown14;
    unsigned char mUnknown18, mUnknown19, mUnknown1A, mUnknown1B;
};

extern "C" {
void PlyrSteerAroundBlocker(Object_80039F5C *, Object_80039F5C *, PassBlockControl_t *);
int fn_8011E3F4(Object_80039F5C *);
int fn_80124B1C(Object_80039F5C *, Object_80039F5C *, int, float, float);
Object_80039F5C *fn_80124C28(Object_80039F5C *, float *, int, float, float, int);

extern float gPlyrMoveFwdSpeed;
unsigned int fn_8011E188(void);
void fn_8011E3EC(Object_80039F5C *, int);
void fn_8011E1BC(Object_80039F5C *, Object_80039F5C *, int, int);
int ScrmIsNotReplay(void);
int fn_8009FB60(Object_80039F5C *);
int fn_8011F524(void);
int fn_8011F2C4(void);
int PlyrTryQueueMsg62(Object_80039F5C *, int, short);
int ScrmUsesBothTeams(void);
int fn_800BA6F8(void);
int fn_800BAA24(void);
void PassBlockSteer(Object_80039F5C *, Object_80039F5C *, PassBlockControl_t *, FieldPoint_t);
int fn_8011E8A4(Object_80039F5C *);
int fn_800B7E60(Object_80039F5C *);
int fn_800B7F34(Object_80039F5C *);
void fn_800B6E68(Object_80039F5C *, Input_800B6D34 *);

void fn_8011E240(Object_80039F5C *);
float ScrmGetSidelineX(void);
int MathArcTan2(float, float);
int MathAngleDiff(int, int);
float Vec2Distance(void *, void *);
void Vec2Sub(void *, void *, void *);
float Vec2Magnitude(void *);
int fn_80120794(Object_800B26B0 *, Object_800B26B0 *, float *, float, float, int, float);
int fn_8011F32C(void);
Object_80039F5C *BallGetCurrentTarget(void);
Object_80039F5C *BallGetCurrentHolder(void);
int ScrmTestPlayFlag(int);
int fn_8011F2F8(void);
void fn_800C89F0(Object_80039F5C *, int, int, int, float);
int fn_80124714(Object_80039F5C *, Object_80039F5C *, Object_80039F5C **);
int ScrmGetDefenseTeam(void);
unsigned int SyncRandGetRange(unsigned int, unsigned int);
unsigned char PlayBookGetReceiver(int, unsigned char, unsigned char *);

float _PassBlock_fDropDepth = 0.0f;
float _PassBlock_fDropDepthPerWidth = 0.6f;
unsigned char _PassBlock_cFaceOffsetDeg = 0;

static inline int AngleSub(int a, int b) { return (a - b) & 0xFFFFFF; }

void PassBlockDropBack(Object_80039F5C *p, Object_80039F5C *other, PassBlockControl_t *aim, FieldPoint_t point)
{
    Object_800B26B0 *motion = &p->mMotion;
    float delta[2];
    aim->mUnknown8 = 0.4f;
    int fallback = 1;
    if (other) {
        Vec2Sub(delta, &other->mMotion.mPos, &motion->mPos);
        float distance = Vec2Magnitude(delta);
        if (!(distance >= 3.25f)) {
            fallback = 0;
            aim->mUnknown10 = MathArcTan2(delta[1], delta[0]);
            int angle = fn_80120794(motion, &other->mMotion,
                &other->mMotion.mUnknown40, motion->mUnknown28,
                other->mMotion.mUnknown28, other->mMotion.mUnknown32, distance);
            if (AngleSub(motion->mFacing, angle) > 0x800000)
                aim->mUnknownC = (0xC00000 - (int)((float)(int)_PassBlock_cFaceOffsetDeg * 46603.37890625f)) & 0xFFFFFF;
            else
                aim->mUnknownC = (0xC00000 + (int)((float)(int)_PassBlock_cFaceOffsetDeg * 46603.37890625f)) & 0xFFFFFF;
            aim->mUnknown8 = other->mMotion.mUnknown28 != 0.0f ? 1.25f : 0.4f;
        }
    }
    if (fallback) {
        delta[0] = point.mX;
        if (p->mUnknown2914 <= 2)
            delta[0] = !(motion->mPos.mX >= point.mX) ? point.mX - 2.0f : point.mX + 2.0f;
        delta[1] = point.mY - 9.0f;
        Vec2Sub(delta, &motion->mPos, delta);
        aim->mUnknown10 = MathArcTan2(delta[1], delta[0]);
        aim->mUnknownC = AngleSub(aim->mUnknown10, 0x800000);
    }
}

int PassBlockShouldEngage(Object_80039F5C *p, Object_80039F5C *ball, Object_80039F5C *other,
               FieldPoint_t reference, Vector_80039F5C location, int angle, int otherAngle, float distance)
{
    float delta[2];
    int result = 0;
    Vector_80039F5C *pos = &p->mMotion.mPos;
    Vector_80039F5C *otherPos = &other->mMotion.mPos;
    int reverse = (angle + 0x800000) & 0xFFFFFF;
    Vec2Sub(delta, otherPos, pos);
    if (MathAngleDiff(reverse, MathArcTan2(delta[1], delta[0])) > 0x471C72) {
        if (ball && !(ball->mFlags & 0x8000) && !(pos->mY + 1.0f >= location.mY) &&
            !(otherPos->mY + 1.0f >= location.mY) &&
            Vec2Distance(&location, pos) < Vec2Distance(&location, otherPos)) {
            result = 1;
        } else if (!(pos->mY <= reference.mY - 9.0f) && !(pos->mY >= otherPos->mY + 1.0f) &&
                   (otherPos->mY > reference.mY || distance < 3.5f || fn_8011F32C())) {
            if (ball && !(ball->mMotion.mPos.mY <= reference.mY - 3.5f) &&
                (ball->mMotion.mUnknown32 & 0xFFFFFF) > 0x800000) {
                result = 1;
            } else {
                if (!ball) {
                    Object_80039F5C *entry = BallGetCurrentTarget();
                    if (entry) {
                        Vec2Sub(delta, otherPos, &entry->mMotion.mPos);
                        otherAngle = MathArcTan2(delta[1], delta[0]);
                        Vec2Sub(delta, pos, &entry->mMotion.mPos);
                        angle = MathArcTan2(delta[1], delta[0]);
                    }
                }
                int limit = 0x11C71C;
                if (MathAngleDiff(angle, otherAngle) < limit) result = 1;
            }
        }
    }
    return result;
}

void PassBlockFormPocket(Object_80039F5C *p, Object_80039F5C *ball, PassBlockControl_t *s, Vector_80039F5C location, FieldPoint_t point)
{
    Vector_80039F5C *pos = &p->mMotion.mPos;
    if (fn_8011F32C()) {
        s->mUnknown10 = 0x400000;
        s->mUnknown8 = 0.0f;
        return;
    }
    float x;
    if (!(location.mX >= 6.0f - ScrmGetSidelineX()))
        x = 6.0f - ScrmGetSidelineX();
    else if (!(location.mX > ScrmGetSidelineX() - 6.0f))
        x = location.mX;
    else
        x = ScrmGetSidelineX() - 6.0f;
    location.mX = x;
    float target[2];
    int n = p->mUnknown2914;
    if ((unsigned int)(n - 5) <= 4) {
        n -= 7;
        target[0] = x + (float)n * 2.0f;
        int magnitude = n < 0 ? -n : n;
        target[1] = location.mY + (3.0f - (float)magnitude);
        if (!(target[1] <= point.mY) && (ball->mMotion.mUnknown32 & 0xFFFFFF) > 0x800000)
            target[1] = pos->mY;
    } else if (s->mUnknown1B & 1) {
        target[0] = x;
        target[1] = pos->mY;
    } else if (ball && (ball->mFlags & 0x8000)) {
        target[0] = x;
        if (!(pos->mX >= x)) target[0] = x - 2.0f;
        else target[0] = x + 2.0f;
        target[1] = location.mY + 2.0f;
    } else {
        target[0] = point.mX;
        target[1] = point.mY - 4.5f;
        if (!(pos->mX >= point.mX)) {
            if (!(pos->mY <= location.mY + 0.5f)) {
                target[0] -= 0.6666666865348816f;
                target[1] -= 0.5f;
            } else target[0] -= 2.0f;
        } else {
            if (!(pos->mY <= location.mY + 0.5f)) {
                target[0] += 0.6666666865348816f;
                target[1] -= 0.5f;
            } else target[0] += 2.0f;
        }
    }
    s->mUnknown10 = 0x400000;
    Vec2Sub(target, target, pos);
    s->mUnknownC = MathArcTan2(target[1], target[0]) & 0xFFFFFF;
    float distance = Vec2Magnitude(target);
    if (!(distance <= 3.0f)) {
        if (!(distance >= 6.0f))
            s->mUnknown8 = distance * 0.10000000894069672f + 0.4f;
        else s->mUnknown8 = 0.7200000286102295f;
        if (MathAngleDiff(s->mUnknownC, s->mUnknown10) <= 0x6E38E2)
            s->mUnknown10 = s->mUnknownC;
        else s->mUnknown8 = 0.4f;
    } else if (!(distance <= 0.5f)) s->mUnknown8 = 0.5f / distance;
    else s->mUnknown8 = 0.0f;
}

void PassBlockSteer(Object_80039F5C *p, Object_80039F5C *other, PassBlockControl_t *s, FieldPoint_t point)
{
    Object_800B26B0 *motion = &p->mMotion;
    float distance;
    float nearest;
    Object_80039F5C *candidate;
    Vector_80039F5C location;
    s->mUnknown4 = 99999.0f;
    --s->mUnknown19;
    if (!(s->mUnknown19 & 0x80)) return;
    int rating = p->mRatings[7] * 2;
    if (rating > 510) rating = 510;
    signed char scaled = (unsigned int)rating >> 1;
    s->mUnknown19 = (255 - scaled) >> 6;
    Object_80039F5C *ball = BallGetCurrentHolder();
    if (s->mUnknown1B & 1) {
        nearest = 999.0f;
        for (unsigned char i = 0; i <= 2; ++i) {
            unsigned char active;
            unsigned char index = PlayBookGetReceiver(p->mIdBytes[2], i, &active);
            if (index != 255 && active) {
                candidate = PlyrGet(p->mIdBytes[2], index);
                if (candidate->mMotion.mPos.mY < point.mY + 2.5f || candidate == ball) {
                    distance = Vec2Distance(&motion->mPos, &candidate->mMotion.mPos);
                    if (!(distance >= nearest)) {
                        ball = candidate;
                        nearest = distance;
                    }
                }
            }
        }
    }
    float reference[2];
    if (ball) {
        if (ScrmTestPlayFlag(0) || !(ball->mFlags & 0x8000)) {
            location = ball->mMotion.mPos;
            reference[0] = location.mX;
            reference[1] = location.mY;
            if (fn_8011E188() <= 59) reference[1] = point.mY - 8.0f;
        } else {
            if (!(ball->mMotion.mPos.mX >= 0.0f)) location.mX = point.mX - 3.0f;
            else location.mX = point.mX + 3.0f;
            location.mY = point.mY;
            reference[0] = location.mX;
            reference[1] = location.mY;
        }
    } else {
        ball = BallGetCurrentTarget();
        if (ball) location = ball->mMotion.mPos;
        else BallGetPosition(BallGetCurrent(), &location);
        reference[0] = location.mX;
        reference[1] = location.mY;
    }
    if (other && p->mUnknown1032 == 3 &&
        (other->mMotion.mUnknown44 > gPlyrMoveFwdSpeed * 0.5f || other->mMotion.mPos.mY - point.mY > 3.0f ||
         fabsf(s->mUnknown0 - motion->mPos.mX) > 1.5f || (short)p->mUnknown1134 > 60)) {
        if (!fn_8011E3F4(p)) {
            fn_8011E240(p);
            other = 0;
            fn_8011E1BC(p, 0, 0, 1);
        }
    }
    if (other) {
        float delta[2];
        Vec2Sub(delta, &other->mMotion.mPos, &motion->mPos);
        int toward = MathArcTan2(delta[1], delta[0]);
        distance = Vec2Magnitude(delta);
        s->mUnknownC = fn_80120794(motion, &other->mMotion,
            &other->mMotion.mUnknown40, motion->mUnknown28,
            other->mMotion.mUnknown28, other->mMotion.mUnknown32, distance);
        Vec2Sub(delta, &other->mMotion.mPos, reference);
        int otherAngle = MathArcTan2(delta[1], delta[0]);
        Vec2Sub(delta, &motion->mPos, reference);
        int angle = MathArcTan2(delta[1], delta[0]);
        if ((s->mUnknown1B & 1) == 0 && PassBlockShouldEngage(p, ball, other, point, location, angle, otherAngle, distance)) {
            s->mUnknown10 = toward;
            if (other->mUnknown1032 == 4 && MathAngleDiff(toward, motion->mFacing) <= 0x11C71C &&
                MathAngleDiff(other->mMotion.mFacing, motion->mFacing) > 0x71C71B) goto finish;
            if (motion->mPos.mY > other->mMotion.mPos.mY ||
                fabsf(motion->mPos.mX - other->mMotion.mPos.mX) > 0.5f ||
                MathAngleDiff(other->mMotion.mFacing, otherAngle) > 0x6E38E3) {
                int turn;
                if (fn_8011E188() <= 59 && MathAngleDiff(otherAngle, toward) > 0xAAAAA) {
                    Vec2Sub(delta, reference, &motion->mPos);
                    turn = MathArcTan2(delta[1], delta[0]);
                } else turn = s->mUnknownC;
                s->mUnknownC = ((turn - toward) & 0xFFFFFF) <= 0x7FFFFF ? s->mUnknown10 + 0x400000 : s->mUnknown10 - 0x400000;
                if (!(distance >= 3.5f)) {
                    if (other->mMotion.mUnknown28 == 0.0f &&
                        fn_80124B1C(p, other, 0x200000, distance + 1.0f, 0.5f)) {
                        s->mUnknown8 = 0.0f;
                        goto finish;
                    }
                    if (!(other->mMotion.mPos.mY >= motion->mPos.mY) && ball && !(location.mY >= motion->mPos.mY)) {
                        s->mUnknown8 = 1.0f;
                        goto finish;
                    }
                    if (!(other->mMotion.mPos.mY >= point.mY)) s->mUnknown8 = distance * 0.08f + 0.7200000286102295f;
                    else s->mUnknown8 = distance * 0.07428571581840515f + 0.14f;
                    goto finish;
                }
                if (!(other->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.14f)) {
                    s->mUnknown8 = 0.4f;
                    goto finish;
                }
            }
            s->mUnknown8 = 0.0f;
            goto finish;
        }
        float interceptionDistance;
        candidate = fn_80124C28(p, &interceptionDistance, 0x2E38E3, distance, 0.2f, s->mUnknownC);
        if (!candidate || candidate == other) {
            Vec2Sub(delta, &location, &motion->mPos);
            nearest = Vec2Magnitude(delta);
            Vec2Sub(delta, &other->mMotion.mPos, &location);
            s->mUnknown8 = 0.7200000286102295f;
            if (!(distance <= nearest) && !(distance >= Vec2Magnitude(delta)) &&
                MathAngleDiff(otherAngle, angle) <= 0x5FFFFF) {
                int reverse = angle + 0x800000;
                int gap = MathAngleDiff(reverse, toward);
                if (gap < MathAngleDiff(s->mUnknownC, toward)) {
                    if (AngleSub(angle, toward - 0x800000) <= 0x7FFFFF && AngleSub(s->mUnknownC, toward) <= 0x7FFFFF)
                        s->mUnknownC = toward + (MathAngleDiff(reverse, toward) * 3) / 4;
                    else if (AngleSub(angle, toward - 0x800000) > 0x800000 && AngleSub(s->mUnknownC, toward) > 0x800000)
                        s->mUnknownC = toward - (MathAngleDiff(reverse, toward) * 3) / 4;
                }
            }
        } else s->mUnknown8 = 0.4f;
        if (MathAngleDiff(otherAngle, angle) > 0x4E38E3) s->mUnknownC = toward;
        s->mUnknown10 = s->mUnknownC;
        if (!(motion->mUnknown28 <= gPlyrMoveFwdSpeed * 0.14f) &&
            MathAngleDiff(motion->mUnknown32, motion->mFacing) > 0x400000 &&
            MathAngleDiff(motion->mUnknown32, s->mUnknown10) > 0x400000) {
            s->mUnknown10 = toward;
            s->mUnknown8 = 0.0f;
            s->mUnknown19 = 2;
        }
    } else if (ball) {
        PassBlockFormPocket(p, ball, s, location, point);
    }
finish:
    PlyrSteerAroundBlocker(p, ball, s);
}

void PassBlockLeanIntoDefender(Object_80039F5C *p, Object_80039F5C *other)
{
    if (other) {
        float delta[2];
        Vec2Sub(delta, &other->mMotion.mPos, &p->mMotion.mPos);
        float distance = Vec2Magnitude(delta);
        if (!(distance >= 4.0f)) {
            distance -= 1.0f;
            if (!(distance >= 0.0f)) distance = 0.0f;
            float amount = 1.0f - distance * 0.25f;
            int angle = MathArcTan2(delta[1], delta[0]);
            fn_800C89F0(p, angle & 0xFFFFFF, 2, 0, amount);
        }
    }
}

void PlyrSteerAroundBlocker(Object_80039F5C *p, Object_80039F5C *, PassBlockControl_t *aim)
{
    Object_80039F5C *target;
    Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
    if (other) {
        Vector_80039F5C *pos = &p->mMotion.mPos;
        int clear = fn_80124714(p, other, &target);
        if (!clear) {
            float delta[2];
            Vec2Sub(delta, &target->mMotion.mPos, pos);
            float distance = Vec2Magnitude(delta);
            if (!(distance >= 2.25f)) {
                Vector_80039F5C point;
                if (target->mUnknown1032 != 4) {
                    point.mX = target->mMotion.mPos.mX;
                    point.mY = target->mMotion.mPos.mY;
                    point.mZ = target->mMotion.mPos.mZ;
                    point.mX += target->mMotion.mUnknown40 * 5.0f;
                    point.mY += target->mMotion.mUnknown44 * 5.0f;
                } else {
                    Object_80039F5C *linked = fn_8009BCE8(&target->mUnknown1036);
                    point.mX = (target->mMotion.mPos.mX + linked->mMotion.mPos.mX) * 0.5f;
                    point.mY = (target->mMotion.mPos.mY + linked->mMotion.mPos.mY) * 0.5f;
                }
                Vec2Sub(delta, &point, pos);
                int angle = MathArcTan2(delta[1], delta[0]);
                if (MathAngleDiff(angle, aim->mUnknownC) <= 0x271C70) {
                    float amount = distance * 0.4444444477558136f;
                    int turn;
                    if (AngleSub(angle, aim->mUnknownC) > 0x800000)
                        turn = (int)((1.0f - amount) * 3495253.0f);
                    else
                        turn = (int)-((1.0f - amount) * 3495253.0f);
                    aim->mUnknown10 = aim->mUnknownC = (aim->mUnknownC + turn) & 0xFFFFFF;
                }
            }
        }
    }
}

void PassBlockFlagDefenderAtLine(Object_80039F5C *p, Object_80039F5C *other)
{
    if (other && ScrmTestPlayFlag(13) && !ScrmTestPlayFlag(0) && !BallGetCurrentHolder() && fn_8011F2F8()) {
        if (!(other->mMotion.mPos.mY - ScrmGetBallSpot().mY >= 2.5f))
            p->mUnknown1137 = 1;
    }
}

int PassBlockEnter(Object_80039F5C *p)
{
    PassBlockControl_t *s = (PassBlockControl_t *)&p->mUnknown336;
    int *pRole = &p->mUnknown1032;
    int count = p->mpState->mUnknown1;
    float fraction = (float)(count & 31) * 0.032258063554763794f;
    s->mUnknown14 = (count >> 5) * 60;
    s->mUnknown14 += (int)(fraction * 60.0f);
    if (s->mUnknown14 == 0)
        s->mUnknown18 = 0;
    else
        s->mUnknown18 = 1;
    FieldPoint_t values;
    values = ScrmGetBallSpot();
    s->mUnknown0 = p->mMotion.mPos.mX;
    s->mUnknown4 = 99999.0f;
    s->mUnknown8 = p->mUnknown528.mUnknown0;
    s->mUnknownC = p->mMotion.mFacing;
    s->mUnknown10 = p->mMotion.mFacing;
    s->mUnknown19 = 0;
    s->mUnknown1A = 0;
    s->mUnknown1B = p->mpState->mUnknown2;
    if (fn_8011E188() <= 14) {
        s->mUnknown1A = 1;
        if (!(values.mY - p->mMotion.mPos.mY >= 2.0f)) {
            float limit = p->mMotion.mPos.mY - _PassBlock_fDropDepth;
            limit -= fabsf(p->mMotion.mPos.mX - ScrmGetBallSpot().mX) * _PassBlock_fDropDepthPerWidth;
            s->mUnknown4 = limit;
            s->mUnknown10 = p->mMotion.mFacing;
            s->mUnknownC = AngleSub(p->mMotion.mFacing, 0x800000);
        } else {
            if (fn_8011F32C())
                s->mUnknown4 = p->mMotion.mPos.mY;
            else
                s->mUnknown4 = values.mY - 4.0f;
            s->mUnknown10 = p->mMotion.mFacing;
            s->mUnknownC = p->mMotion.mFacing;
        }
        s->mUnknown8 = 0.4f;
        if (!(p->mFlags & 0x4000)) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = s->mUnknownC;
            p->mUnknown512.mUnknown8 = s->mUnknown10;
            p->mUnknown512.mUnknown0 = s->mUnknown8;
        }
    } else if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
    }
    if (ScrmIsNotReplay()) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        return 1;
    }
    if (*pRole != 3) fn_8011E1BC(p, 0, 0, 1);
    fn_8011E3EC(p, 1);
    return 0;
}

int PassBlockUpdate(Object_80039F5C *p)
{
    int apply = 0;
    Object_80039F5C *ball = BallGetCurrentHolder();
    PassBlockControl_t *s = (PassBlockControl_t *)&p->mUnknown336;
    Block_8011E240 *block = &p->mBlock1032;
    int result = 0;
    Message_800F01CC message;
    if (p == ball) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        memset(&message, 0, 4);
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (fn_8009FB60(p)) return 1;
    if (p->mIdBytes[2] == ScrmGetDefenseTeam()) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        memset(&message, 0, 4);
        message.mId = 2;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if ((fn_8011F524() && !fn_8011F2C4()) || ScrmTestPlayFlag(0) || ScrmIsNotReplay()) {
        if (block->mUnknown0 != 4 && block->mUnknown0 != 7) {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
        }
        memset(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (ScrmIsNotReplay()) {
        if ((block->mUnknown0 != 4 && block->mUnknown0 != 7) || SyncRandGetRange(0, 100) <= 9) {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
        }
    } else if (!block->mUnknown0) {
        fn_8011E240(p);
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 1);
    }
    PlyrTryQueueMsg62(p, 0, -1);
    if (!(p->mFlags & 0x4000)) {
        FieldPoint_t point;
        point = ScrmGetBallSpot();
        Object_80039F5C *other = fn_8009BCE8(&block->mUnknown4);
        if (block->mUnknown0 != 4 && block->mUnknown0 != 7) {
            if (ball && (ball->mFlags & 0x8000)) s->mUnknown1A = 0;
            if (s->mUnknown1A && !(p->mMotion.mPos.mY <= s->mUnknown4))
                PassBlockDropBack(p, other, s, point);
            else if (!ScrmUsesBothTeams() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
                s->mUnknown8 = 0.0f;
                s->mUnknown10 = s->mUnknownC = p->mMotion.mFacing;
            } else
                PassBlockSteer(p, other, s, point);
            PassBlockLeanIntoDefender(p, other);
            PassBlockFlagDefenderAtLine(p, other);
        } else
            s->mUnknown4 = 99999.0f;
        if ((unsigned int)(p->mUnknown2914 - 1) <= 1 && block->mUnknown0 == 2) {
            if (!(fabsf(other->mMotion.mPos.mY - p->mMotion.mPos.mY) >= 5.0f)) apply = 1;
        } else apply = 1;
        if (apply) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = s->mUnknownC & 0xFFFFFF;
            p->mUnknown512.mUnknown8 = s->mUnknown10;
            p->mUnknown512.mUnknown0 = s->mUnknown8;
        }
    } else if (p->mpState[1].mId == 19) {
        fn_8011E3EC(p, 0);
        result = 1;
        fn_8011E240(p);
    }
    if (s->mUnknown18) {
        --s->mUnknown14;
        float seconds = (float)s->mUnknown14 / 60.0f;
        p->mpState->mUnknown1 = (int)(seconds * 32.0f);
        if (s->mUnknown14 > 0 && !p->mpState->mUnknown1) p->mpState->mUnknown1 = 1;
        if (s->mUnknown14 <= 0 ||
            ((p->mFlags & 0x4000) && !(p->mMotion.mPos.mY <= ScrmGetBallSpot().mY))) {
            fn_8011E3EC(p, 0);
            result = 1;
            fn_8011E240(p);
        }
    }
    return result;
}

int PassBlockExit(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

int PassBlockInput(Object_80039F5C *p)
{
    int result = 0;
    if (fn_8011E8A4(p))
        result = fn_800B7E60(p);
    else {
        Block_8011E240 *block = &p->mBlock1032;
        if (p->mUnknown1032 == 4 || p->mUnknown1032 == 7) {
            Input_800B6D34 input;
            fn_800B6D34(p, &input);
            fn_800B6E68(p, &input);
            Object_80039F5C *other = fn_8009BCE8(&p->mUnknown1036);
            float delta[2];
            Vec2Sub(delta, &other->mMotion.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(p->mUnknown512.mUnknown4, MathArcTan2(delta[1], delta[0])) > 0x600000) {
                fn_8011E3EC(p, 0);
                fn_8011E240(p);
                goto done;
            }
            if (input.mUnknown92 & 1) block->mUnknown105 = 1;
        }
        result = fn_800B7F34(p);
    }
done:
    return result;
}
}
