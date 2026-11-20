#include "game/Command_800CEE74.h"
#include "game/PlayBookTeam.h"
#include "game/Ball.h"
#include "game/Block_801BE60C.h"
#include "game/fn_802270D4.h"
#include "game/Item_80097440.h"
#include <math.h>
#include "game/fn_80177FE0.h"

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

extern "C" {
int BallStateGet(Ball_t *pBall, int a);
int fn_801783AC(int bit);
unsigned int fn_802372EC(int stream, int count);
int fn_80178320(void);
int fn_80178308(void);
int fn_800C8BAC(Object_80039F5C *p, int which);
float fn_80178A2C(void);
float fn_80178A68(Vector_80039F5C *pPoint);
void fn_8022713C(void *pVec);
extern Record_80097518 lbl_8030C2B8[];
extern float lbl_803EA92C;
extern unsigned char lbl_803EA93D;
extern float lbl_803EA940;
}

/* Catch search: walks the catch records start[first] .. start[last] + count[last] of the
   record table kind, both mirror halves, and keeps the record whose reach the ball (flown forward
   by the record's time plus delay) passes closest to; the score adds reach, height and direction
   terms. pBlock, when given, holds the best record per side (+0/+4 or +8/+16 by kind). Returns
   the record handle, or 0x1FFFFFFF when none qualifies. */
extern "C" int fn_8009817C(Object_80039F5C *p, Vector_80039F5C *pPos, int facing, unsigned char delay,
                           Ball_t *pBall, int first, int last, float range, Block_800997F4 *pBlock, int filter,
                           float *pZone, unsigned char loose, int kind, int side)
{
    Vector_80039F5C velocity;
    Vector_80039F5C ballPos;
    Vector_80039F5C landing;
    Vector_80039F5C reach;
    Vec2_t delta;
    Item_80097440 *pItem = 0;
    int mirror = 0;
    int heading;
    unsigned short end;
    int sideline;
    int team;
    int special = 0;
    int lucky;
    int turning;
    int bestHandle;
    float best;
    int state;
    int found;
    unsigned short i;
    unsigned short start;
    int j;
    float skill;
    float heightLimit;
    float heightScale;
    float edge;

    if (fn_801783AC(11) || fn_801783AC(12)) {
        special = 1;
    }
    lucky = fn_802372EC(0, 100) < 33;
    bestHandle = 0x1FFFFFFF;
    state = BallStateGet(pBall, 0);
    BallGetPosition(pBall, &ballPos);
    BallGetVelocity(pBall, &velocity);
    if (loose != 0 && velocity.mZ < 0.0f) {
        best = -20.0f;
    } else {
        best = 0.0f;
    }
    team = fn_80178320();
    range *= gFrameTimeScale;
    heading = (fn_801CFE40(velocity.mY, velocity.mX) + 0x800000) & 0xFFFFFF;
    if (fn_8009780C(p, pBall) == 0) {
        turning = MathAngleDiff(p->mMotion.mFacing, p->mMotion.mUnknown32) > 0x2AAAAA;
        skill = p->mRatings[1] * (1.0f / 255.0f);
        start = lbl_8030C2B8[kind].mUnknownBEC[first];
        end = lbl_8030C2B8[kind].mUnknownBEC[last] + lbl_8030C2B8[kind].mUnknownBFA[last];
        if (skill > 1.0f) {
            skill = 1.0f;
        }
        heightScale = 1.1f - skill * 1.1f;
        heightLimit = 1.159353f;
        sideline = fn_80097864(p);
        edge = fn_80177FE0().mY + 1.0f;
        if (kind == 1) {
            heightLimit += 0.75f;
        }
        for (i = start; i < end; i++) {
            for (j = 0; j <= 1; j++) {
                int handle;
                int ok;
                int diff;
                float time;
                float reachMax;
                float limit;
                float fall;
                float height;
                float maxDist;
                int angle;
                float dist;
                float score;

                ok = 1;
                switch (j) {
                case 0:
                    mirror = 0;
                    break;
                case 1:
                    mirror = 1;
                    break;
                }
                if (mirror != 0 ? side == 1 : side == 2) {
                    continue;
                }
                handle = (mirror << 31) | (kind << 29) | i;
                pItem = fn_8009A63C(handle);
                if (fn_801783AC(20) && pItem->mUnknown6[0] == 1) {
                    ok = 0;
                }
                if (state == 4 && pItem->mUnknown6[1] == 1) {
                    ok = 0;
                }
                if (lbl_803EA93D != 0 && state == 3 && pItem->mUnknown6[1] == 2 && pItem->mUnknown6[0] != 1 &&
                    p->mIdBytes[2] == fn_80178308()) {
                    ok = 0;
                }
                if (pItem->mUnknown6[0] == 4 && p->mIdBytes[2] == fn_80178308()) {
                    ok = 0;
                }
                if (ok == 0) {
                    continue;
                }
                time = pItem->mUnknown20 + delay;
                if (time > range) {
                    continue;
                }
                if (!(filter == 0 || (filter == 1 && pItem->mUnknown4 != 6 && pItem->mUnknown4 != 7) ||
                      (filter == 2 && (pItem->mUnknown4 == 6 || pItem->mUnknown4 == 7)) || filter == 3)) {
                    continue;
                }
                if (!(pItem->mUnknown5 == 2 || pItem->mUnknown5 == 0 || (pItem->mUnknown5 == 1 && sideline == 1) ||
                      (pItem->mUnknown5 == 4 && sideline == 0))) {
                    continue;
                }
                diff = MathAngleDiff(heading,
                                     (facing + fn_800C8BAC(p, 0) + pItem->mUnknown28 + pItem->mUnknown38) & 0xFFFFFF);
                if ((pItem->mUnknown24 == 2 || pItem->mUnknown4 == 6 || pItem->mUnknown4 == 7) &&
                    pItem->mUnknown4 != 5) {
                    reachMax = 1.3f;
                } else {
                    reachMax = 0.55f;
                }
                reachMax = reachMax < fn_802270A4(&pItem->mUnknown14) ? reachMax : fn_802270A4(&pItem->mUnknown14);
                if (pItem->mUnknown6[0] == 1) {
                    limit = 0.35f;
                    reachMax = 0.75f;
                    if (p->mMotion.mUnknown28 > 0.045f) {
                        continue;
                    }
                } else if (kind == 1) {
                    limit = 0.05f;
                } else {
                    limit = 0.4f;
                }
                if (loose != 0) {
                    limit *= 3.0f;
                } else if (diff >= pItem->mUnknown2C && (pItem->mUnknown6[0] != 1 || pItem->mUnknown20 >= 20.0f)) {
                    continue;
                }
                fall = time * 0.0029814816f;
                landing.mZ = ballPos.mZ + velocity.mZ * time - fall * time * 0.5f;
                height = pItem->mUnknown8.mZ * p->mUnknown768;
                if (pItem->mUnknown14.mZ > heightLimit &&
                    (pItem->mUnknown4 == 3 || pItem->mUnknown4 == 4 || pItem->mUnknown4 == 7)) {
                    height += (pItem->mUnknown14.mZ - heightLimit) * heightScale;
                }
                height = landing.mZ - height;
                if (landing.mZ < 0.0f) {
                    continue;
                }
                if (!((height < 0.0f && height > -limit * 0.5f) || (height >= 0.0f && height < limit))) {
                    continue;
                }
                fall = velocity.mZ - fall;
                if (MathAngleDiff(pItem->mUnknown30, fn_801CFE40(fall, fn_802270A4(&velocity))) >= pItem->mUnknown34) {
                    continue;
                }
                landing.mX = ballPos.mX + velocity.mX * time;
                landing.mY = ballPos.mY + velocity.mY * time;
                if (landing.mY < fn_80178A2C() && pItem->mUnknown4 == 5 && kind == 2) {
                    continue;
                }
                if (kind == 1 && fn_80178A68(&landing) <= 0.75f) {
                    continue;
                }
                fn_80227690(&reach, &pItem->mUnknown8, &pItem->mUnknown14);
                fn_80227248(&reach, &reach, p->mUnknown768);
                fn_80227638(&reach, &reach, &pItem->mUnknown14);
                if (pItem->mUnknown6[0] == 1) {
                    angle = heading;
                } else {
                    angle = facing + fn_800C8BAC(p, 0);
                }
                fn_80227384(&reach, &reach, angle);
                fn_80227638(&reach, &reach, pPos);
                if (pZone != 0 && loose == 0) {
                    if (fabsf(pZone[0] - reach.mX) >= pZone[3]) {
                        continue;
                    }
                    if (fabsf(pZone[1] - reach.mY) >= pZone[3]) {
                        continue;
                    }
                    if (fabsf(height) >= pZone[3]) {
                        continue;
                    }
                }
                fn_80227690(&delta, &landing, &reach);
                if (pItem->mUnknown6[1] != 2 && state == 3) {
                    maxDist = fn_802270A4(&pItem->mUnknown14) * lbl_803EA940 + 0.55f;
                } else {
                    maxDist = fn_802270A4(&pItem->mUnknown14) * 0.25f + reachMax;
                }
                if (special != 0 && lucky != 0 && pItem->mUnknown4 == 5) {
                    maxDist = 4.4f;
                }
                if (loose != 0) {
                    maxDist = 5.0f;
                }
                dist = fn_802270A4(&delta);
                if (dist > maxDist) {
                    continue;
                }
                score = (maxDist - dist) * (0.25f / maxDist);
                if (height > 0.0f) {
                    score += 0.4f - height;
                    if (height < 0.05f) {
                        score += 0.13333334f;
                    }
                } else {
                    score += (height + 0.4f) * 0.5f;
                }
                if (diff >= pItem->mUnknown2C) {
                    score -= (float)(diff - pItem->mUnknown2C) * 1.7881394e-08f;
                }
                if (pItem->mUnknown5 == 1) {
                    score += 0.5f;
                }
                if (state == 3 && pItem->mUnknown6[1] != 2) {
                    score += lbl_803EA92C;
                }
                if (p->mIdBytes[2] == team) {
                    if (pItem->mUnknown4 == 6 || pItem->mUnknown4 == 7) {
                        score += 0.2f;
                    }
                    if (turning != 0 && pItem->mUnknown6[0] == 4) {
                        score += 0.2f;
                    }
                } else {
                    fn_8022713C(&pItem->mUnknown14);
                    if (pItem->mUnknown6[0] == 1 && p->mMotion.mUnknown28 < 0.045f) {
                        score += 0.15f;
                    }
                }
                if (pItem->mUnknown4 == 5) {
                    if (reach.mY < edge && p->mIdBytes[2] != team) {
                        ok = 0;
                    }
                    if (state == 3) {
                        ok = 0;
                    }
                    if (ok != 0 && special != 0 && lucky != 0) {
                        score += dist / maxDist * 0.75f;
                    }
                }
                if (p->mMotion.mUnknown28 < 0.045f && pItem->mUnknown6[0] != 1) {
                    ok = 0;
                }
                if (ok != 0) {
                    if (handle != 0x1FFFFFFF) {
                        if (score > best) {
                            bestHandle = handle;
                            best = score;
                        }
                    } else {
                        bestHandle = handle;
                        best = score;
                    }
                }
            }
        }
        if (pBlock != 0) {
            found = 0;
            if (bestHandle != 0x1FFFFFFF) {
                if ((kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0) != 0x1FFFFFFF) {
                    if (kind == 1 ? best > pBlock->mUnknown16 : best > pBlock->mUnknown4) {
                        (kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0) = bestHandle;
                        (kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) = best;
                    } else if (pItem->mUnknown6[0] != 1) {
                        found = 1;
                    }
                } else {
                    (kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0) = bestHandle;
                    (kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) = best;
                }
                pItem = fn_8009A63C(kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0);
                if (((kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) > 0.5f && pItem->mUnknown4 == 4) ||
                    ((kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) > 0.5f && pItem->mUnknown6[0] == 1) ||
                    ((kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) > 0.5f &&
                     ((unsigned int)bestHandle >> 29 & 3) == 1) ||
                    ((kind == 1 ? pBlock->mUnknown16 : pBlock->mUnknown4) > 0.5f && pItem->mUnknown6[0] != 1)) {
                    found = 1;
                }
            } else if ((kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0) != bestHandle) {
                pItem = fn_8009A63C(kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0);
                found = 1;
            }
            if (found == 1) {
                bestHandle = kind == 1 ? pBlock->mUnknown8 : pBlock->mUnknown0;
            } else {
                bestHandle = 0x1FFFFFFF;
            }
        }
    }
    return bestHandle;
}

/* The simpler catch search fn_80099AD0 and fn_80099C80 use: same record walk and ball flight as
   fn_8009817C, scored on reach distance and height error only. */
extern "C" int fn_80098EAC(Object_80039F5C *p, Vector_80039F5C *pPos, int facing, unsigned char delay,
                           Ball_t *pBall, int first, int last, int filter, unsigned char loose, int kind, int side)
{
    float best = -15.0f;
    int bestHandle = 0x1FFFFFFF;
    Vector_80039F5C velocity;
    Vector_80039F5C ballPos;
    Vector_80039F5C landing;
    Vector_80039F5C reach;
    Vec2_t delta;
    unsigned short end;
    int mirror;
    int heading;
    int sideline;
    unsigned short i;
    unsigned short start;
    int j;
    float skill;
    float heightLimit;
    float heightScale;

    BallGetPosition(pBall, &ballPos);
    mirror = 0;
    BallGetVelocity(pBall, &velocity);
    heading = (fn_801CFE40(velocity.mY, velocity.mX) + 0x800000) & 0xFFFFFF;
    if (filter != 3) {
        loose = 0;
    }
    if (fn_8009780C(p, pBall) == 0) {
        skill = p->mRatings[1] * (1.0f / 255.0f);
        end = lbl_8030C2B8[kind].mUnknownBEC[last] + lbl_8030C2B8[kind].mUnknownBFA[last];
        start = lbl_8030C2B8[kind].mUnknownBEC[first];
        if (skill > 1.0f) {
            skill = 1.0f;
        }
        heightScale = 1.1f - skill * 1.1f;
        heightLimit = 1.159353f;
        sideline = fn_80097864(p);
        if (kind == 1) {
            heightLimit += 0.75f;
        }
        for (i = start; i < end; i++) {
            for (j = 0; j <= 1; j++) {
                Item_80097440 *pItem;
                int handle;
                int diff;
                int angle;
                float limit;
                float time;
                float fall;
                float error;
                float dist;
                float reachMax;
                float score;

                switch (j) {
                case 0:
                    mirror = 0;
                    break;
                case 1:
                    mirror = 1;
                    break;
                }
                if (mirror != 0 ? side == 1 : side == 2) {
                    continue;
                }
                handle = (mirror << 31) | (kind << 29) | i;
                pItem = fn_8009A63C(handle);
                if (BallStateGet(pBall, 0) == 4 && pItem->mUnknown6[1] == 1) {
                    continue;
                }
                if (!(filter == 0 || (filter == 1 && pItem->mUnknown4 != 6 && pItem->mUnknown4 != 7) ||
                      (filter == 2 && (pItem->mUnknown4 == 6 || pItem->mUnknown4 == 7)) || filter == 3)) {
                    continue;
                }
                if (!(pItem->mUnknown5 == 2 || pItem->mUnknown5 == 0 || (pItem->mUnknown5 == 1 && sideline == 1) ||
                      (pItem->mUnknown5 == 4 && sideline == 0))) {
                    continue;
                }
                diff = MathAngleDiff(heading, (facing + pItem->mUnknown28 + pItem->mUnknown38) & 0xFFFFFF);
                if (pItem->mUnknown6[0] == 1) {
                    limit = 0.3f;
                    if (p->mMotion.mUnknown28 > 0.045f) {
                        continue;
                    }
                } else {
                    limit = 0.75f;
                }
                if (diff >= pItem->mUnknown2C) {
                    continue;
                }
                time = pItem->mUnknown20 + delay;
                fall = time * 0.0029814816f;
                landing.mZ = ballPos.mZ + velocity.mZ * time - fall * time * 0.5f;
                error = pItem->mUnknown8.mZ * p->mUnknown768;
                if (pItem->mUnknown14.mZ > heightLimit &&
                    (pItem->mUnknown4 == 3 || pItem->mUnknown4 == 4 || pItem->mUnknown4 == 7)) {
                    error += (pItem->mUnknown14.mZ - heightLimit) * heightScale;
                }
                error = fabsf(landing.mZ - error);
                if (loose == 0 && error >= limit) {
                    continue;
                }
                fall = velocity.mZ - fall;
                angle = fn_801CFE40(fall, fn_802270A4(&velocity));
                if (loose == 0 && MathAngleDiff(pItem->mUnknown30, angle) >= pItem->mUnknown34) {
                    continue;
                }
                landing.mX = ballPos.mX + velocity.mX * time;
                landing.mY = ballPos.mY + velocity.mY * time;
                if (kind == 1 && fn_80178A68(&landing) <= 0.75f) {
                    continue;
                }
                fn_80227690(&reach, &pItem->mUnknown8, &pItem->mUnknown14);
                fn_80227248(&reach, &reach, p->mUnknown768);
                fn_80227638(&reach, &reach, &pItem->mUnknown14);
                fn_80227384(&reach, &reach, facing);
                fn_80227638(&reach, &reach, pPos);
                fn_80227690(&delta, &landing, &reach);
                dist = fn_802270A4(&delta);
                reachMax = fn_802270A4(&pItem->mUnknown14) * 0.5f;
                if (reachMax < 0.3f) {
                    reachMax = 0.3f;
                }
                if (dist >= reachMax) {
                    continue;
                }
                score = (fn_802270A4(&pItem->mUnknown14) * 0.5f - dist) * 0.33333334f;
                if (score > 0.8f) {
                    score = 0.8f;
                }
                if (landing.mZ - pItem->mUnknown8.mZ > 0.0f && error < 0.3f) {
                    score += (0.75f - error) * 2.0f;
                } else {
                    score += 0.75f - error;
                }
                if (diff >= pItem->mUnknown2C) {
                    score -= (float)(diff - pItem->mUnknown2C) * 1.7881394e-08f;
                }
                if (pItem->mUnknown5 == 1) {
                    score += 0.5f;
                }
                if (score > best) {
                    best = score;
                    bestHandle = handle;
                }
            }
        }
    }
    return bestHandle;
}

extern "C" float fn_80178A2C(void);
extern unsigned char lbl_803EA944;
extern "C" int BallGetLandingPoint(Ball_t *pBall, Vector_80039F5C *pOut);

extern "C" {
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_80178320(void);
int fn_80099510(Object_80039F5C *p);
int fn_80099734(Object_80039F5C *p, Ball_t *pBall, int a, int mode, float range, Block_800997F4 *pBlock, int b, float *c, unsigned char d, unsigned char e);
void fn_800CEE74(Command_800CEE74 *pOut, Object_80039F5C *pA, Object_80039F5C *pB, void *pData, int angle, int key, int mirror);
void fn_800CEED8(unsigned short key, int index, Command_800CEE74 *pRecord, Object_80039F5C *pPlayer, Vector_80039F5C *pPoint, int angle, Vector_80039F5C *pOut, int *pAngle, unsigned char *pValue);
}

extern "C" int fn_800997F4(Object_80039F5C *p, Ball_t *pBall, float range, Block_800997F4 *pBlock, int a,
                           float *b, unsigned char c, int *pOutA, int *pOutB)
{
    Command_800CEE74 command;
    unsigned char order[3] = { 1, 2, 3 };
    Vector_80039F5C end;
    unsigned char key;
    int extra = 0;
    int index;
    int angle;
    int value = -1;
    int result = 0x1FFFFFFF;
    int last = 0x1FFFFFFF;
    unsigned char i;
    unsigned char j;

    if (fn_80099510(p) != 0) {
        *pOutA = value;
        if (__builtin_fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 5.0f) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (p->mIdBytes[2] == fn_80178320()) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        }
        if (pBlock != 0) {
            last = pBlock->mUnknown8;
        }
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 1; j++) {
                unsigned char flags;
                int kind;

                p->mUnknown1008.mUnknown0 = order[i];
                if (j == 1) {
                    fn_800CEE74(&command, p, 0, 0, 0, 0xE0, 1);
                } else {
                    fn_800CEE74(&command, p, 0, 0, 0, 0xE0, 0);
                }
                value = fn_800C3BEC(p, &command, &extra, &index);
                if (value == -1) {
                    continue;
                }
                fn_800CEED8(0xE0, index, &command, p, (Vector_80039F5C *)&p->mUnknown1160.mUnknown16,
                            p->mUnknown1160.mUnknown12Word, &end, &angle, &key);
                flags = 1;
                if (command.mUnknown62 != 0) {
                    flags = 2;
                }
                switch (p->mUnknown1008.mUnknown0) {
                case 2:
                    kind = 5;
                    break;
                case 3:
                    kind = 6;
                    break;
                case 1:
                    kind = 4;
                    break;
                default:
                    kind = 4;
                    break;
                }
                result = fn_8009817C(p, &end, angle, key + lbl_803EA944, pBall, kind, kind, range, pBlock, a, b, c, 1,
                                     flags);
                if (pBlock != 0) {
                    if (pBlock->mUnknown8 == last) {
                        value = pBlock->mUnknown12;
                    } else {
                        pBlock->mUnknown12 = value;
                        last = pBlock->mUnknown8;
                    }
                }
                if (result != 0x1FFFFFFF) {
                    break;
                }
            }
            if (result != 0x1FFFFFFF) {
                break;
            }
        }
        if (result != 0x1FFFFFFF) {
            *pOutB = extra;
            *pOutA = value;
        }
    }
    return result;
}

extern "C" void fn_80099AD0(Object_80039F5C *p, Ball_t *pBall, int a, int mode, int b, unsigned char d, unsigned char e)
{
    unsigned char flags = 0;
    int facing;
    int angle;
    Vector_80039F5C delta;

    if (e != 0) {
        flags = 2;
    }
    if (fn_80098EAC(p, &p->mMotion.mPos, p->mMotion.mFacing, 0, pBall, a, mode, b, d, flags, 0) != 0x1FFFFFFF) {
        return;
    }
    facing = p->mMotion.mFacing;
    BallGetLandingPoint(pBall, &delta);
    fn_80227690(&delta, &delta, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (MathAngleDiff(p->mMotion.mFacing, angle) <= 0xAAAA9) {
        p->mMotion.mFacing = angle & 0xFFFFFF;
    } else {
        angle = (angle - p->mMotion.mFacing) & 0xFFFFFF;
        if (angle <= 0x7FFFFF) {
            p->mMotion.mFacing = (p->mMotion.mFacing + 0xAAAAA) & 0xFFFFFF;
        } else {
            p->mMotion.mFacing = (p->mMotion.mFacing - 0xAAAAA) & 0xFFFFFF;
        }
    }
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
    if (fn_80098EAC(p, &p->mMotion.mPos, p->mMotion.mFacing, 0, pBall, a, mode, b, d, flags, 0) == 0x1FFFFFFF) {
        p->mMotion.mFacing = facing;
        p->mpUnknown796->mUnknown8 = facing;
        fn_80099734(p, pBall, a, mode, 120.0f, 0, b, 0, d, e);
    }
}

extern "C" int fn_80099C80(Object_80039F5C *p, Ball_t *pBall, unsigned char b, int *pOutA, int *pOutB)
{
    Command_800CEE74 command;
    unsigned char order[3] = { 1, 2, 3 };
    Vector_80039F5C end;
    unsigned char key;
    int extra = 0;
    int index;
    int angle;
    int value = -1;
    int result = 0x1FFFFFFF;
    unsigned char i;
    unsigned char j;

    *pOutA = value;
    if (__builtin_fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 5.0f) {
        order[0] = 2;
        order[1] = 1;
        order[2] = 3;
    } else if (p->mIdBytes[2] == fn_80178320()) {
        order[0] = 3;
        order[1] = 2;
        order[2] = 1;
    }
    for (i = 0; i <= 2; i++) {
        for (j = 0; j <= 1; j++) {
            unsigned char flags;
            int kind;

            fn_800CEE74(&command, p, 0, 0, 0, 0xE0, j == 1);
            p->mUnknown1008.mUnknown0 = order[i];
            value = fn_800C3BEC(p, &command, &extra, &index);
            if (value == -1) {
                continue;
            }
            fn_800CEED8(0xE0, index, &command, p, (Vector_80039F5C *)&p->mUnknown1160.mUnknown16,
                        p->mUnknown1160.mUnknown12Word, &end, &angle, &key);
            flags = 1;
            if (command.mUnknown62 != 0) {
                flags = 2;
            }
            switch (p->mUnknown1008.mUnknown0) {
            case 2:
                kind = 5;
                break;
            case 3:
                kind = 6;
                break;
            case 1:
                kind = 4;
                break;
            default:
                kind = 4;
                break;
            }
            result = fn_80098EAC(p, &end, angle, key + lbl_803EA944, pBall, kind, kind, 3, b, 1, flags);
            if (result != 0x1FFFFFFF) {
                break;
            }
        }
        if (result != 0x1FFFFFFF) {
            break;
        }
    }
    if (result == 0x1FFFFFFF) {
        result = fn_800997F4(p, pBall, 120.0f, 0, 3, 0, b, &value, &extra);
    }
    if (result != 0x1FFFFFFF) {
        *pOutA = value;
        *pOutB = extra;
    }
    return result;
}
