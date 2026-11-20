#include "game/PlayBookTeam.h"
#include "game/Ball.h"
#include "game/Block_801BE60C.h"
#include "game/fn_802270D4.h"
#include "game/Item_80097440.h"
#include <math.h>

extern "C" {
int fn_80097160(Object_80039F5C *p, float value);
int fn_801CFE40(float y, float x);
void fn_80227538(Vec2_t *pOut, int angle, float length);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A298(int handle);
void fn_80096E74(Object_80039F5C *p, Vector_80039F5C *pVec, void *pData);
unsigned char *fn_8009CD00(Object_80039F5C *p, void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *),
                           int right, int a, int b);
int fn_8023790C(void);
float fn_80178A08(void);
int MathAngleDiff(int a, int b);
void BallGetVelocity(Ball_t *pBall, Vector_80039F5C *pOut);
void fn_80227384(void *, void *, int);
void fn_80227638(void *, void *, void *);
void fn_80227690(void *pOut, void *pA, void *pB);
void BallGetSpin(Ball_t *pBall, Vector_80039F5C *pOut);
extern Block_80099630 *lbl_803EC92C;
extern float gFrameTimeScale;
}

extern "C" int fn_80097160(Object_80039F5C *p, float duration)
{
    int *pFirst;
    int *pSecond = 0;
    unsigned char firstKind;
    unsigned char secondKind = 3;
    Data_80096E74 *pData = 0;
    unsigned char unknown;
    int handle;
    unsigned int type;

    if (p->mpState->mId == 28) {
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        type = fn_8009A298(handle);
        switch (type) {
        case 0:
            pFirst = &p->mUnknown108;
            firstKind = 0;
            break;
        case 1:
            pFirst = &p->mUnknown200;
            firstKind = 1;
            break;
        case 2:
            pFirst = &p->mUnknown200;
            firstKind = 1;
            pSecond = &p->mUnknown108;
            secondKind = 0;
            break;
        default:
            pSecond = 0;
            pFirst = 0;
            secondKind = 3;
            firstKind = 3;
            break;
        }
        if (pFirst != 0) {
            pData = (Data_80096E74 *)fn_8009CD00(p, fn_80096E74, firstKind, (unsigned int)duration, 2);
            if (pData != 0) {
                pData->mUnknown4 = firstKind;
                pData->mUnknown0 = fn_8023790C() + (unsigned int)duration + 2;
            }
        }
        if (pSecond != 0) {
            pData = (Data_80096E74 *)fn_8009CD00(p, fn_80096E74, secondKind, (unsigned int)duration, 2);
            if (pData != 0) {
                pData->mUnknown4 = secondKind;
                pData->mUnknown0 = fn_8023790C() + (unsigned int)duration + 2;
            }
        }
    }
    return pData != 0;
}

extern "C" int fn_8009780C(Object_80039F5C *p, Ball_t *pBall)
{
    Vector_80039F5C velocity;

    float rate;

    BallGetSpin(pBall, &velocity);
    rate = gFrameTimeScale;
    return __builtin_fabsf(velocity.mZ / rate + 0.0029814816f) > 1e-07f;
}

extern "C" int fn_80097864(Object_80039F5C *p)
{
    if (__builtin_fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 4.0f) {
        Point_8017886C direction;

        direction.mX = p->mMotion.mPos.mX;
        direction.mY = 0.0f;
        if (MathAngleDiff(direction.Heading(), p->mMotion.mUnknown32) <= 0x355554) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_800978F8(Object_80039F5C *p, Item_80097440 *pItem, Vec2_t *pTarget, Vector_80039F5C *pPos,
                            float time, int *pTurn, Ball_t *pBall)
{
    Vector_80039F5C ballPos;
    Vec2_t target;
    Vec2_t offset;
    Vec2_t start;
    Vec2_t velocity;
    Vec2_t delta;
    int angle;
    int facing;

    if (p == 0 || pItem == 0 || pTurn == 0 || pBall == 0) {
        return;
    }
    BallGetVelocity(pBall, &ballPos);
    angle = (fn_801CFE40(ballPos.mY, ballPos.mX) + 0x800000) & 0xFFFFFF;
    target.mX = pTarget->mX;
    target.mY = pTarget->mY;
    fn_80227384(&offset, pPos, angle);
    fn_80227638(&start, &p->mMotion.mPos, &offset);
    fn_80227690(&velocity, &target, &start);
    lbl_803EC92C->mUnknown4.mUnknownC = time;
    lbl_803EC92C->mUnknown4.mUnknown18 = velocity.mX / time;
    lbl_803EC92C->mUnknown4.mUnknown1C = velocity.mY / time;
    fn_80227690(&delta, pPos, &pItem->mUnknown14);
    facing = p->mMotion.mFacing & 0xFFFFFF;
    *pTurn = MathAngleDiff(angle, facing);
    if (((angle - facing) & 0xFFFFFF) > 0x800000) {
        *pTurn = -*pTurn;
    }
    if (fn_802270A4(&velocity) > 2.0f) {
        fn_80227538(&velocity, fn_801CFE40(velocity.mY, velocity.mX), 2.0f);
        lbl_803EC92C->mUnknown4.mUnknown18 = velocity.mX / time;
        lbl_803EC92C->mUnknown4.mUnknown1C = velocity.mY / time;
    }
}

extern "C" {
float fn_80237260(int a);
Item_80097440 *fn_8009A63C(int handle);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80227248(void *pOut, void *pIn, float scale);
void fn_80227638(void *pOut, void *pA, void *pB);
void BallGetPosition(Ball_t *pBall, Vector_80039F5C *pOut);
void BallGetVelocity(Ball_t *pBall, Vector_80039F5C *pOut);
void BallGetSpin(Ball_t *pBall, Vector_80039F5C *pOut);
float fn_80260B1C(float value);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_80227350(void *pOut, void *pIn, float scale);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_802276B4(void *pOut, void *pA, void *pB);
float fn_802270A4(void *pVec);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
float fn_801CFB18(int angle);
int fn_801CFDD0(float value);
float fn_801CFB94(int angle);
extern Block_80099630 *lbl_803EC92C;
}

/* Catch timing for player p and the catch record of handle against the ball:
   a skill factor from ratings 0 and 3 (with a random part) scales the
   record's reach, the ball is flown forward to the record's time (and that
   time is stretched or shrunk, within skill-based limits, so the ball meets
   the reach height), and from the ball's spot relative to p the playback
   speed and the turn are worked out. *pScale gets the time ratio, *pTurn 0;
   the time, the absolute facing and the turn per unit time go to
   lbl_803EC92C. Returns the playback speed. */
extern "C" float fn_80097A88(Object_80039F5C *p, int handle, Ball_t *pBall, float *pScale, int *pTurn)
{
    float ratio = 0.0f;
    float speed = 1.0f;
    unsigned int low = 222;
    unsigned int high = 445;
    unsigned int rating = p->mRatings[3] + p->mRatings[0] / 2 + p->mRatings[3] / 4;
    float skill;
    Item_80097440 *pItem;
    Vector_80039F5C reach;
    Vector_80039F5C ballPos;
    Vector_80039F5C startPos;
    Vector_80039F5C velocity;
    Vector_80039F5C spin;
    Vector_80039F5C drift;
    Vector_80039F5C landing;
    Vector_80039F5C toReach;
    Vector_80039F5C toBall;
    int turn;
    float time;
    float reachLength;
    float ballLength;
    int angle;

    if (rating < low) {
        rating = low;
    }
    skill = (speed - (float)(rating - low) / (float)(high - low)) * 0.65f;
    skill = speed - fn_80237260(0) * skill;
    pItem = fn_8009A63C(handle);
    reach = pItem->mUnknown8;
    fn_80227690(&reach, &reach, &pItem->mUnknown14);
    fn_80227248(&reach, &reach, p->mUnknown768);
    fn_80227638(&reach, &reach, &pItem->mUnknown14);
    reach.mZ *= p->mUnknown768;
    time = pItem->mUnknown20;
    *pScale = speed;
    BallGetPosition(pBall, &ballPos);
    startPos = ballPos;
    BallGetVelocity(pBall, &velocity);
    BallGetSpin(pBall, &spin);
    ballPos.mZ += velocity.mZ * time - 0.0029814816f * time * time * 0.5f;
    if (velocity.mY != ratio && velocity.mZ != ratio) {
        float height = ballPos.mZ - reach.mZ;

        if (!(fabsf(height) <= 0.03f)) {
            float target = height >= 0.0f ? reach.mZ + 0.03f : reach.mZ - 0.03f;
            float t = ((startPos.mZ - target) * 0.005962963f + velocity.mZ * velocity.mZ) * 112495.65f;

            t = fn_80260B1C(t >= 0.0f ? t : 0.0f);
            t = velocity.mZ * 335.40372f + t;
            float longest;
            float shortest;

            if (((unsigned int)handle >> 29 & 3) == 1) {
                longest = 1.15f;
                shortest = 0.95f;
            } else {
                longest = 1.15f;
                shortest = 0.95f;
            }
            longest = time * (longest + skill * 0.25f);
            shortest = time * (shortest - skill * 0.15f);
            t = t <= longest ? t : longest;
            t = t >= shortest ? t : shortest;
            *pScale = t / time;
            time = t;
        }
    }
    fn_80227264(&drift, &spin, time * (time * 0.5f));
    fn_80227350(&drift, &velocity, time);
    ballPos.mX += drift.mX;
    ballPos.mY += drift.mY;
    landing = ballPos;
    fn_80227690(&ballPos, &ballPos, &p->mMotion.mPos);
    fn_80227384(&ballPos, &ballPos, -p->mMotion.mFacing);
    fn_802276B4(&toReach, &reach, &pItem->mUnknown14);
    reachLength = fn_802270A4(&toReach);
    fn_80227690(&toBall, &pItem->mUnknown8, &ballPos);
    ballLength = fn_802270A4(&ballPos);
    MathAngleDiff((fn_801CFE40(velocity.mY, velocity.mX) + 0x800000) & 0xFFFFFF,
                  (p->mMotion.mFacing + pItem->mUnknown28 + pItem->mUnknown38) & 0xFFFFFF);
    *pTurn = 0;
    angle = ((fn_801CFE40(toReach.mY, toReach.mX) + 0x800000) - fn_801CFE40(pItem->mUnknown14.mY, pItem->mUnknown14.mX)) &
            0xFFFFFF;
    if (pItem->mUnknown6[0] == 1) {
        fn_800978F8(p, pItem, (Vec2_t *)&landing, &reach, time, &turn, pBall);
        speed = 1.0f;
    } else {
        int bend;

        ratio = reachLength * fn_801CFB18(0x800000 - angle) / ballLength;
        if (ratio > 1.0f) {
            bend = 0x400000;
        } else if (ratio < -1.0f) {
            bend = 0xC00000;
        } else {
            bend = fn_801CFDD0(ratio);
        }
        speed = fn_801CFB94(bend);
        speed = (speed * ballLength + fn_801CFB94(angle) * reachLength) / fn_802270A4(&pItem->mUnknown14);
        turn = bend - (fn_801CFE40(pItem->mUnknown14.mY, pItem->mUnknown14.mX) - fn_801CFE40(reach.mY, reach.mX));
        turn = (turn + (fn_801CFE40(ballPos.mY, ballPos.mX) - fn_801CFE40(reach.mY, reach.mX))) & 0xFFFFFF;
        if (turn > 0x800000) {
            turn -= 0x1000000;
        }
    }
    if (pItem->mUnknown6[0] != 1) {
        if (pItem->mUnknown6[1] != 1) {
            float minSpeed;
            float maxSpeed;

            if (((unsigned int)handle >> 29 & 3) == 1) {
                maxSpeed = 1.33f;
                minSpeed = 0.66f;
            } else {
                maxSpeed = 1.33f;
                minSpeed = 0.66f;
            }
            maxSpeed += skill * 0.66f;
            minSpeed -= skill * 0.61f;
            speed = speed < minSpeed ? minSpeed : (speed > maxSpeed ? maxSpeed : speed);
            if (!(fabsf((float)turn) <= 4194304.0f)) {
                float limit = (float)turn * 2.1457672e-05f < 0.0f ? -90.0f : 90.0f;

                turn = (int)(limit * 46603.38f);
            }
        } else {
            speed = speed < 0.33f ? 0.33f : (speed > 3.0f ? 3.0f : speed);
        }
    }
    lbl_803EC92C->mUnknown4.mUnknown8 = time;
    lbl_803EC92C->mUnknown4.mUnknown0 = (p->mMotion.mFacing + turn) & 0xFFFFFF;
    lbl_803EC92C->mUnknown4.mUnknown14 = (int)((float)turn / time);
    return speed;
}
