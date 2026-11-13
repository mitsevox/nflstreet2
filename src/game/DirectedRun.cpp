/* Player state 30: a player runs along the heading and for the distance given by the
   message that started the state, with rating-based chances to break off for the ball
   carrier or play a pass that is in the air. */

#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Ball.h"
#include "game/fn_80177FE0.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/fn_800B65A0.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

struct DirectedRunState_t {
    Point_8017886C mUnknown0;
    float mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
};

extern "C" {
int fn_800ABDA4(int team);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8011F1CC(void);
int DirectedRunEnter(Object_80039F5C *p);
int DirectedRunUpdate(Object_80039F5C *p);
int fn_80177C38(void);
int BallStateGet(Ball_t *p, int *pOut);
int fn_8009FB60(Object_80039F5C *p);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
float fn_8016B938(void);
float fn_8016B974(void);
int fn_800E1584(Object_80039F5C *p);
int fn_8009E180(Object_80039F5C *p);
int fn_800F2C1C(Object_80039F5C *p, int a);
int fn_800E6AC8(Object_80039F5C *p, int a);
}

extern "C" int DirectedRunEnter(Object_80039F5C *p)
{
    DirectedRunState_t *state = (DirectedRunState_t *)&p->mUnknown336;

    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_8011F1CC()
        && fn_800ABDA4(p->mIdBytes[2]) == 0) {
        switch (p->mUnknown2914) {
        case 10:
        case 11:
        case 12:
            break;
        default: {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 85;
            message.mUnknown1[0] = 96;
            message.mUnknown1[1] = 180;
            fn_800F00D4(0, p->mpState, &message, p);
            return 1;
        }
        }
    }
    state->mUnknown0.mX = p->mMotion.mPos.mX;
    state->mUnknown0.mY = p->mMotion.mPos.mY;
    state->mUnknown8 = (p->mpState->mUnknown1 >> 3)
                      + (p->mpState->mUnknown1 & 7) * (1.0f / 7.0f);
    state->mUnknown12 = (p->mpState->mUnknown2 << 17) & 0xFFFFFF;
    state->mUnknown16 = 0;
    state->mUnknown20 = 0;
    p->mUnknown512.mUnknown0 = 0.0f;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    return 0;
}

extern "C" int DirectedRunUpdate(Object_80039F5C *p)
{
    DirectedRunState_t *state = (DirectedRunState_t *)&p->mUnknown336;
    Point_8017886C ball;
    Block_8011E240 *pBlock = &p->mBlock1032;
    Object_80039F5C *carrier;
    Message_800F01CC message;

    ball = fn_80177FE0();
    carrier = BallGetCurrentHolder();
    if (fn_8009FB60(p)) {
        return 1;
    }
    fn_8010A2DC(p, 0, -1);
    if (fn_800A5C04(p, state->mUnknown12, state->mUnknown12) || (p->mFlags & 0x4000)) {
        return 0;
    }
    if (--state->mUnknown16 < 0) {
        int rating = 255 - p->mRatings[5];
        if (rating < 0) {
            rating = 0;
        }
        state->mUnknown16 = state->mUnknown16 + fn_802372EC(0, rating >> 4) + (rating >> 5);
        if (carrier && fn_800B65A0(p->mIdBytes[2]) != 255
            && fn_800B65A0(carrier->mIdBytes[2]) == 255 && !fn_80177C38()) {
            state->mUnknown16 -= (int)MIN((float)state->mUnknown16,
                                          (float)state->mUnknown16 * fn_8016B938());
            if (fn_8011F1CC() && (carrier->mFlags & 0x8000)) {
                state->mUnknown16 -= (int)MIN((float)state->mUnknown16,
                                              (float)state->mUnknown16 * fn_8016B974());
            }
        }
        if (fn_800E1584(p)) {
            return 0;
        }
        int kind = fn_8009E180(p);
        unsigned int chance;
        if (kind > 1) {
            if (kind != 4) {
                chance = p->mRatings[5] >> 3;
                if (pBlock->mUnknown0 == 4) {
                    chance += chance;
                }
                if (!(p->mMotion.mPos.mY >= ball.mY - 1.0f)) {
                    chance <<= 2;
                }
                if (fn_802372EC(0, 100) < chance) {
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            } else {
                chance = p->mRatings[5] >> 3;
                if (pBlock->mUnknown0 == 4) {
                    chance += chance;
                }
                if (!(p->mMotion.mPos.mY >= ball.mY - 1.0f)) {
                    chance <<= 2;
                }
                if (fn_802372EC(0, 100) < chance) {
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            }
        } else if (pBlock->mUnknown0 == 4
            && fn_8009BCE8(&pBlock->mUnknown4)->mUnknown1052 == 1) {
            chance = p->mRatings[5] >> 2;
            if (fn_802372EC(0, 100) < chance) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 2;
                fn_800F053C(0, p->mpState, &message, p);
                return 1;
            }
        }
    }
    {
        Vector_80039F5C delta;

        fn_80227690(&delta, &p->mMotion.mPos, &state->mUnknown0);
        if (fn_802270A4(&delta) > state->mUnknown8) {
            return 1;
        }
    }
    if (MathAngleDiff(p->mMotion.mFacing, state->mUnknown12) <= 0x11C71B) {
        p->mUnknown512.mUnknown15 = 1;
    } else {
        p->mUnknown512.mUnknown15 = 0;
    }
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = state->mUnknown12;
    p->mUnknown512.mUnknown4 = state->mUnknown12;
    p->mUnknown512.mUnknown0 = 1.0f;
    Ball_t *pBall = BallGetCurrent();
    if (BallStateGet(pBall, 0) == 4) {
        Vector_80039F5C position;

        BallGetPosition(pBall, &position);
        if (!(position.mZ >= 3.3f)) {
            Vector_80039F5C direction;
            BallGetVelocity(pBall, &direction);
            fn_80227690(&position, &p->mMotion.mPos, &position);
            int directionAngle = fn_801CFE40(direction.mY, direction.mX);
            int deltaAngle = fn_801CFE40(position.mY, position.mX);
            if (MathAngleDiff(directionAngle, deltaAngle) <= 0x155554
                && fn_802372EC(0, 100) <= 4 && fn_800F2C1C(p, 0)) {
                return 0;
            }
        }
    }
    if (--state->mUnknown20 <= 0) {
        int ratings = p->mRatings[5] + p->mRatings[9];
        if (ratings > 510) {
            ratings = 510;
        }
        state->mUnknown20 = 31 - ratings / 32;
        if (fn_802372EC(0, 100) <= 24 && pBlock->mUnknown0 == 4) {
            fn_8009BCE8(&pBlock->mUnknown4);
            if (fn_800E6AC8(p, 8)) {
                return 0;
            }
        }
    }
    return 0;
}

