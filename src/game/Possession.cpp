/* Ball possession rules: catch, pitch and fumble rolls, giving the ball to a player, spotting the ball and the out-of-bounds check.
   Also holds the game clock stop rules (flag word 'clkr') and the per-drive play log behind the play-by-play summary lines. */
#include "game/fn_8022781C.h"
#include "game/StyleTracker.h"
#include "game/fn_80177FE0.h"
#include "game/fn_800F06F4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/GameModeType.h"
#include "game/AudmonEvent.h"
#include "game/fn_802372EC.h"
#include "game/Object_80039F5C.h"
#include "game/Class_80297C60.h"
#include "game/Point2.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/Message_800F01CC.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Record_8011F4F8.h"
#include "game/cu_8003108C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/Object_8017886C.h"
#include "game/State_803EB098.h"
#include "game/fn_801BE60C.h"
#include <stdio.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"
#include "game/Possession.h"

struct PossBallView_t {
    char mUnknown0[12];
    Vector_80039F5C mUnknownC;
    char mUnknown18[180];
    int mUnknownCC;
    char mUnknownD0[36];
    int mUnknownF4;
};

/* One logged play: its type (DriveLogAddPlay counts type 8 separately), two
 * signed halfword values and two player references from DriveLogGetPlayerNum. */
struct DriveLogPlay_t {
    int mType;
    short mUnknown4;
    short mUnknown6;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
};

/* One block of the log: up to 40 plays and the block state. DriveLogEndDrive
 * copies a finished block into the entry after its +0x1E4 index. */
struct DriveLog_t {
    DriveLogPlay_t mPlays[40];
    int mUnknown1E0;
    unsigned short mUnknown1E4;
    unsigned short mCount;
    unsigned short mUnknown1E8;
    unsigned char mUnknown1EA;
    unsigned char mUnknown1EB;
};

extern "C" {
extern float gPlyrMoveFwdSpeed;

double fabs(double);

void fn_8003AB08(Object_80039F5C *p, int a);
unsigned char CheatFlagsIsSet(int index);
void fn_80053A70(Object_80039F5C *p);
void fn_8006F0B8(int a);
void fn_80071458(Object_80039F5C *p, void *pBall);
void fn_80071540(Object_80039F5C *p, void *pBall);
void fn_80093C3C(int a, short b, Object_80039F5C *p);
void fn_80097028(Object_80039F5C *p);
int fn_8009704C(Object_80039F5C *p);
int fn_8009A298(int handle);
int fn_8009A2EC(int handle);
int fn_8009A578(int handle);
int fn_8009A5D4(int handle);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009AD38(int team, int value);
void fn_8009BD2C(Object_80039F5C *p, int *pOut);
void fn_8009BFF8(Object_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, int a);
int fn_8009D86C(void);
void fn_8009E458(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800A7EB8(int team);
int fn_800A7EE0(int team);
int fn_800A7F44(int team);
int fn_800A851C(int team, Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
unsigned int fn_800ABDA4(int team);
float fn_800AC44C(Object_80039F5C *p, float value);
float fn_800AC504(int team, float value);
float fn_800AC6BC(int team, float value);
float fn_800AC734(Object_80039F5C *p, float value);
float fn_800AC7E0(int team, float value);
void fn_800ACE90(Object_80039F5C *p, unsigned int *pValue);
void fn_800B1698(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800B6714(Object_80039F5C *p, int port);
int PlayerMoveGetKind(Object_80039F5C *p);
void fn_800D782C(Object_80039F5C *p);
int fn_800E0EF0(Object_80039F5C *p);
int fn_800E0F40(Object_80039F5C *p);
void fn_801039D8(Object_80039F5C *p);
int fn_8011E9B4(Object_80039F5C *p);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
void *BallGetCurrent(void);
int BallGetIndex(void *pBall);
void BallRelease(void *pBall, int a, int b);
void BallGiveToPlayer(void *pBall, Object_80039F5C *p);
Object_80039F5C *BallGetHolder(void *pBall);
Object_80039F5C *BallGetLastHolder(void *pBall);
Object_80039F5C *BallGetCurrentHolder(void);
Object_80039F5C *BallGetCurrentLastHolder(void);
Object_80039F5C *BallGetTarget(void *pBall);
void BallSetTarget(void *pBall, int a);
void BallSetCurrentTarget(int a);
void *BallFindHeldBy(Object_80039F5C *p);
void BallGetPosition(void *pBall, Vector_80039F5C *pOut);
void BallGetVelocity(void *pBall, Vector_80039F5C *pOut);
void BallSetVelocity(void *pBall, Vector_80039F5C *pVelocity);
unsigned int BallGetStateFrames(void *pBall);
void BallSetTransferKind(void *pBall, int a);
int BallGetTransferKind(void *pBall);
int BallGetLastToucher(void *pBall);
void BallKickUp(void *pBall, int a);
void fn_8013AD04(void *pBall, Vector_80039F5C *pVelocity, int a, float b, float c);
int fn_8013AD78(void *pBall);
void fn_8013AD9C(void *pBall, int a);
void BallStateChange(void *pBall, int a, int b);
int BallStateGet(void *pBall, int *pOut);
int BallStateGetPrev(void *pBall, int *pOut);
void CamGameSetModeAll(int a);
void CamGameResumeAll(void);
void PassIconsHide(void);
void PassIconsClearReplayFlag(void);
int fn_801485D4(void);
int fn_801486A0(void);
int fn_80156704(void);
void fn_80156C78(int a, int b);
float fn_8016FAB4(void);
void DriveLogEndDrive(void);
void DriveLogAddPlay(int a, short b, short c, int d, int e);
void DriveLogStampTime(void);
void fn_80177C50(int a);
int fn_80177F70(void);
void fn_80178264(Point2_t pos);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
int fn_80178508(void *pPos, float *pOut, int a);
void fn_80178718(Object_80039F5C *p);
Object_80039F5C *fn_8017876C(void);
int fn_801787A0(void);
float fn_80178A08(void);
float fn_80178A2C(void);
float fn_80178A68(Point2_t *pPos);
void BannerClear(int a);
int BannerIsActive(int a);
void BannerSetText(int a, int b, const char *pText);
void HudShowAlert(const char *pText);
void HudShowCallout(const char *pText);
int CharSkelGetJointByName(void *p, const char *pName);
int fn_801CFE40(float y, float x);
int MathAngleDiff(int a, int b);
void fn_80227538(Point2_t *pOut, int angle, float length);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802278D0(Vector_80039F5C *pA, Vector_80039F5C *pB);
float fn_80237260(int stream);

int PossIsCatchInBounds(Object_80039F5C *p);
int PossCanFumble(Object_80039F5C *p);
float PossCalcHitFactor(Object_80039F5C *p);
void PossFumble(Object_80039F5C *p);
void PossReleaseBall(Object_80039F5C *p);
void PossStartFumble(void);
void PossGiveBall(Object_80039F5C *p, void *pBall);
void PossLogBallResult(Object_80039F5C *p);
int PossCheckDownedBall(Object_80039F5C *p);
int fn_8016EB50(Object_80039F5C *p, Vector_80039F5C *pPos);
int fn_8009A5A0(int handle);
float fn_80178A44(void);
int BallIsClearOfHands(void *pBall);
int ChallengeIsActive(void);
void ChallengePostOutcome(void);
Object_80039F5C *fn_8009BCE8(int *pRef);
int fn_8009D558(int a);
void fn_8009D818(int state);
void fn_8009D888(int index, int a);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
int fn_8009D9A8(int index);
int fn_8009D9D8(int index);
void fn_800AD910(int a, float b);
int fn_800B232C(int a);
int fn_800B2624(void);
int fn_800B9A90(void *pHandle);
void fn_800B9B9C(void *pHandle);
int fn_800BA6F8(void);
void fn_8016E498(void);
int fn_8016E764(void);
int fn_801787DC(int team);
int fn_80178AE0(void);
int fn_80178C24(void);
void *fn_8023816C(void *pHandle);
void ClockRuleSetFlags(unsigned int mask);
unsigned int ClockRuleTestFlags(unsigned int mask);
void ClockRuleClearFlags(unsigned int mask);
void ClockRuleSetStopMode(void);
int ClockRuleCanEndPeriod(void);
unsigned char ClockRuleIsEndHeld(void);
void DriveLogClearSaved(void);
int DriveLogGetElapsed(void);
int DriveLogGetPlayerNum(int id);
int fn_80177C38(void);
void fn_8017C298(unsigned short a, short b);
void fn_8017C2F0(unsigned short a);
int fn_8022DDB4(int tag, void *data);
}

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

float _Poss_fSpotPad = 0.075f;
float _Poss_fSpotPadHandoff = 0.12f;
int _Poss_aiSpotJoints[11] = {6, 2, 5, 1, 24, 18, 22, 16, 21, 15, 26};

unsigned char _Poss_bAllowCatch = 1;
unsigned char _Poss_bMissArmed = 0;
int _Poss_iMissedCatchId = 0;

extern "C" {
void PossCalcBallSpot(Object_80039F5C *p, void *pBall, Point2_t *pOut, int a)
{
    Vector_80039F5C ballPos;
    unsigned char unknown;
    int handle;

    BallGetPosition(pBall, &ballPos);
    pOut->mX = ballPos.mX;
    pOut->mY = ballPos.mY;
    if (p == 0) {
        return;
    }
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
    if (!(p->mMotion.mPos.mZ > 0.0f)) {
        Vector_80039F5C left;
        Vector_80039F5C right;
        Vector_80039F5C joint;
        Vector_80039F5C extra;
        float onSide;
        float limit;
        int leftDown;
        int rightDown;
        int handoff;
        unsigned char i;

        pOut->mX = 0.0f;
        pOut->mY = p->mMotion.mPos.mY;
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lball"), &left, 0);
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rball"), &right, 0);
        if (a == 0) {
            limit = p->mUnknown768 * 0.1275f;
        } else {
            limit = 10.0f;
        }
        if (p->mpState->mId == 0x1C && fn_8009A5A0(handle) == 1) {
            limit += 0.03f;
        }
        if (!(left.mZ > limit)) {
            pOut->mX = left.mX;
            pOut->mY = left.mY;
            leftDown = 1;
        } else {
            leftDown = 0;
        }
        if (!(right.mZ > limit)) {
            rightDown = 1;
            if (fabsf(right.mX) > fabsf(pOut->mX)) {
                pOut->mX = right.mX;
            }
            if (fabsf(right.mY) > fabsf(pOut->mY)) {
                pOut->mY = right.mY;
            }
        } else {
            rightDown = 0;
        }
        if (!leftDown && !rightDown) {
            pOut->mX = p->mMotion.mPos.mX;
            pOut->mY = p->mMotion.mPos.mY;
        }
        handoff = BallGetTransferKind(pBall);
        if (handoff != 0 && handoff != 4) {
            int leftHit;
            int result;
            int region;

            if (!leftDown && !rightDown) {
                pOut->mX = 0.0f;
                pOut->mY = CLAMP(pOut->mY, -fn_80178A44(), fn_80178A44());
            }
            leftHit = leftDown || handoff == 2;
            rightDown = rightDown || handoff == 3;
            if (leftHit || rightDown) {
                handoff = 4;
            } else {
                fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lknee"), &left, 0);
                fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rknee"), &right, 0);
                if (left.mZ <= 0.18f) {
                    handoff = 4;
                    if (fabsf(left.mX) > fabsf(pOut->mX)) {
                        pOut->mX = left.mX;
                    }
                    if (fabsf(left.mY) > fabsf(pOut->mY)) {
                        pOut->mY = left.mY;
                    }
                }
                if (right.mZ <= 0.18f) {
                    handoff = 4;
                    if (fabsf(right.mX) > fabsf(pOut->mX)) {
                        pOut->mX = right.mX;
                    }
                    if (fabsf(right.mY) > fabsf(pOut->mY)) {
                        pOut->mY = right.mY;
                    }
                }
            }
            if (pOut->mX < 0.0f) {
                pOut->mX -= _Poss_fSpotPadHandoff;
            } else {
                pOut->mX += _Poss_fSpotPadHandoff;
            }
            if (pOut->mY < 0.0f) {
                pOut->mY -= _Poss_fSpotPadHandoff;
            } else {
                pOut->mY += _Poss_fSpotPadHandoff;
            }
            result = fn_80178508(pOut, (float *)&region, 0);
            if (result == 3) {
                result = fn_80178508(pOut, (float *)&region, 0);
            }
            if (result == 2 || result == 0 || result == 1) {
                BallSetTransferKind(pBall, handoff);
                if (handoff == 4) {
                    BallGetPosition(BallGetCurrent(), &joint);
                    if (joint.mY > fn_80178A2C() && p->mIdBytes[2] == fn_80178308()) {
                        p->mFlags |= 0x800000;
                    }
                }
            }
            return;
        }
        if (pOut->mX < 0.0f) {
            pOut->mX -= _Poss_fSpotPad;
        } else {
            pOut->mX += _Poss_fSpotPad;
        }
        if (pOut->mY < 0.0f) {
            pOut->mY -= _Poss_fSpotPad;
        } else {
            pOut->mY += _Poss_fSpotPad;
        }
        if (leftDown || rightDown) {
            return;
        }
        if (fabsf(pOut->mX) < fn_80178A08()) {
            return;
        }
        if (fabsf(ballPos.mX) >= fn_80178A08()) {
            return;
        }
        onSide = right.mZ;
        if (onSide > left.mZ) {
            onSide = left.mZ;
        }
        for (i = 0; i <= 10; i++) {
            fn_8009BF5C(p, _Poss_aiSpotJoints[i], &joint, &extra);
            if (joint.mZ < onSide) {
                onSide = joint.mZ;
            }
        }
        if (onSide <= p->mUnknown768 * 0.165f) {
            return;
        }
        if (fabsf(ballPos.mX) < fabsf(pOut->mX)) {
            pOut->mX = ballPos.mX;
        }
        if (ballPos.mY > pOut->mY) {
            pOut->mY = ballPos.mY;
        }
    } else if (fabsf(p->mMotion.mPos.mX) < fabsf(pOut->mX)) {
        pOut->mX = p->mMotion.mPos.mX;
    }
}


int PossTestCarrierBall(Object_80039F5C *p)
{
    int result = 0;

    if (p == BallGetCurrentHolder()) {
        Vector_80039F5C pos;

        BallGetPosition(BallGetCurrent(), &pos);
        result = fn_8016EB50(p, &pos);
    }
    return result;
}

int PossIsCatchInBounds(Object_80039F5C *p)
{
    float zoneInfo;
    Point2_t point;

    if (!fn_800A7F44(p->mId >> 8 & 0xFF)) {
        return 0;
    }
    if (fn_800A7F44(p->mId >> 8 & 0xFF) == 2) {
        return 1;
    }
    if (fn_80178508(&p->mMotion.mPos, &zoneInfo, 0) > 2) {
        return 0;
    }
    fn_80227538(&point, p->mMotion.mFacing, 4.0f);
    fn_80227638(&point, &point, &p->mMotion.mPos);
    if (fn_80178508(&point, &zoneInfo, 0) > 2) {
        return 0;
    }
    fn_80227538(&point, p->mMotion.mUnknown32, 4.0f);
    fn_80227638(&point, &point, &p->mMotion.mPos);
    return fn_80178508(&point, &zoneInfo, 0) <= 2;
}

int PossCanFumble(Object_80039F5C *p)
{
    int allowed = 1;
    void *pBall = BallFindHeldBy(p);
    int handoff = BallGetTransferKind(pBall);

    if (BallStateGetPrev(pBall, 0) == 4) {
        if (!handoff) {
            if (fn_80178360() == (p->mId >> 8 & 0xFF)) {
                allowed = BallGetStateFrames(pBall) > 0x13;
            }
        } else {
            allowed = 0;
        }
    }
    if (fn_800A7EB8(p->mId >> 8 & 0xFF) == 2) {
        allowed = 0;
    }
    if (fn_801BE648(p->mpUnknown792) == 0xEA) {
        allowed = 0;
    }
    if ((p->mId >> 8 & 0xFF) == fn_80178308() && p == BallGetCurrentHolder() && p->mMotion.mPos.mY >= fn_80178A2C()) {
        allowed = 0;
    }
    return allowed;
}

float PossCalcHitFactor(Object_80039F5C *p)
{
    float factor = 0.0f;
    float timing;
    void *pBall = BallGetCurrent();
    unsigned int frames;
    Block_80170374 *pBlock;
    int unknown;
    int handle;
    int slot;

    if (BallGetHolder(pBall)) {
        frames = BallGetStateFrames(pBall);
    } else {
        frames = 0;
    }
    if (frames < 10) {
        timing = (10 - frames) * 0.1f;
        timing = timing * 0.85f + 0.15f;
    } else {
        timing = 0.0f;
    }
    pBlock = &p->mUnknown560;
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
    slot = handle;
    if (p->mpState->mId == 0x1C) {
        fn_8009A298(slot);
    }
    if (p->mUnknown560.mFlags.mBytes[0]) {
        switch (pBlock->mUnknown54) {
        case 0:
            factor = 0.2f;
            break;
        case 1:
        case 3:
            factor = 0.45f;
            break;
        case 2:
        case 4:
        case 9:
        case 10:
            factor = 0.65f;
            break;
        default:
            factor = 0.0f;
            break;
        }
    }
    factor *= p->mUnknown560.mUnknown28 / (gPlyrMoveFwdSpeed * 100621.117f) * 0.85f + 0.15f;
    if (pBlock->mFlags.mAll & 0xC0000) {
        factor = 0.87f;
    } else if (pBlock->mFlags.mBytes[1] & 1 || pBlock->mFlags.mBytes[1] & 2) {
        factor = 0.7f;
    } else if (pBlock->mFlags.mAll & 0x300000) {
        factor = 0.5f;
    }
    return factor * timing;
}

void PossClassifyCatch(Object_80039F5C *p, int *pFlags, int *pAngle, int move, int handle)
{
    Vector_80039F5C velocity;

    BallGetVelocity(BallGetCurrent(), &velocity);
    *pAngle = 0;
    *pFlags = 0;
    switch (fn_801BE648(p->mpUnknown792)) {
    case 0x43:
    case 0xE1:
    case 0xE3:
        if (p->mpState->mId == 0x1C) {
            int kind = fn_8009A578(handle);

            if (kind != 6 && kind != 7) {
                if (fn_8009A298(handle) != 2
                    && ((fn_8009A298(handle) == 0 && (move == 9 || move == 4 || move == 3))
                        || (fn_8009A298(handle) == 1 && (move == 10 || move == 2 || move == 1)))) {
                    *pFlags = 0x100;
                } else {
                    *pFlags = 0;
                }
            } else {
                *pFlags = 0x100;
                if (kind == 7) {
                    fn_80031328(lbl_803EA368, 0x2A);
                }
            }
            int ballAngle = fn_801CFE40(velocity.mY, velocity.mX);
            int backAngle = p->mMotion.mFacing - 0x800000;

            *pAngle = ballAngle - backAngle;
            *pAngle += fn_8009A2EC(handle);
            *pAngle = MathAngleDiff(*pAngle, 0);
        } else {
            *pFlags = 0x100;
        }
        break;
    case 0x44:
        if ((fn_80178320() != (p->mId >> 8 & 0xFF) || fn_801783AC(0)) && p->mpState->mUnknown2 == 1) {
            *pFlags = 0x10;
            *pAngle = MathAngleDiff(fn_801CFE40(velocity.mY, velocity.mX) + 0x800000, p->mMotion.mFacing);
        } else {
            *pFlags = 0x100;
        }
        break;
    case 0x46:
        *pFlags = 0x10;
        break;
    default:
        *pFlags = 0x100;
        break;
    }
    if (_Poss_bAllowCatch == 0) {
        *pFlags = 0x100;
    }
}

void PossCalcBallTerms(Object_80039F5C *p, float *pA, float *pB, int angle)
{
    Vector_80039F5C velocity;

    *pB = 0.0f;
    *pA = 0.0f;
    BallGetVelocity(BallGetCurrent(), &velocity);
    *pB = (fn_802270A4(&velocity) - 0.19f) * 3.3333333f;
    *pB = *pB < 0.0f ? 0.0f : (*pB > 1.0f ? 1.0f : *pB);
    *pA = (angle - 0x200000) / 6291456.0f;
    *pA = *pA < 0.0f ? 0.0f : (*pA > 1.0f ? 1.0f : *pA);
}

unsigned short PossApplyCoverage(Object_80039F5C *p, float *pChance)
{
    float pressure = 0.0f;
    unsigned short count = 0;
    unsigned short i = 0;
    unsigned int n = fn_80178D18((p->mId >> 8 & 0xFF) ^ 1);

    for (; i < n && count <= 3; i++) {
        Object_80039F5C *pOther = fn_80039F5C((p->mId >> 8 & 0xFF) ^ 1, i);

        if (fn_8022781C(&pOther->mMotion.mPos, &p->mMotion.mPos) < 2.5f && !fn_8011E9B4(pOther)) {
            short *pRatings = pOther->mRatings;
            float value = (pRatings[8] + pRatings[5] / 2) / 382.0f;
            unsigned int state;

            switch (pOther->mUnknown2916) {
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
                break;
            default:
                value *= 0.5f;
                break;
            }
            value *= 0.1f;
            state = pOther->mpState->mId;
            if (pOther->mFlags & 0x4000) {
                state = 0x18;
            }
            switch (state) {
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x28:
            case 0x55:
            case 0x5C:
                value *= 0.75f;
            case 5:
            case 0xC:
            case 0x17:
            case 0x18:
            case 0x1C:
            case 0x58:
                count++;
                break;
            default:
                value = 0.0f;
                break;
            }
            pressure += value;
        }
    }
    if (count > 1) {
        pressure *= count * 0.5f - 0.5f + 1.0f;
    }
    *pChance -= *pChance * pressure;
    if (count == 0) {
        if ((p->mId >> 8 & 0xFF) == fn_80178348()) {
            *pChance += 0.7f;
        } else {
            *pChance += p->mRatings[8] / 255.0f * 0.1f;
        }
    }
    return count;
}

float PossCalcCatchChance(Object_80039F5C *p, Object_80039F5C *pReceiver, int flags, int angle)
{
    int offense = fn_80178308() == (p->mId >> 8 & 0xFF);
    Vector_80039F5C velocity;
    float a;
    float b;
    int rating;
    float scale;
    float chance;

    BallGetVelocity(BallGetCurrent(), &velocity);
    PossCalcBallTerms(p, &a, &b, angle);
    if (fn_801486A0() == 1) {
        rating = p->mRatings[8] >= p->mRatings[3] ? p->mRatings[8] : p->mRatings[3];
    } else if ((p->mId >> 8 & 0xFF) == fn_80178308()) {
        rating = p->mRatings[3];
    } else {
        rating = p->mRatings[8];
    }
    scale = rating;
    scale /= 255.0f;
    if (offense || fn_801486A0() == 1) {
        chance = 0.3f + (1.05f - 0.3f) * scale;
    } else if ((fn_801783AC(0xB) || fn_801783AC(0xC)) && velocity.mZ < 0.0f) {
        chance = 0.25f + 0.55f * scale;
    } else {
        chance = 0.25f + 0.25f * scale;
    }
    if (rating >= 191.25f) {
        chance += 0.1f;
    }
    if (fn_800E0EF0(p)) {
        chance += 0.15f;
    }
    PossApplyCoverage(p, &chance);
    chance -= PossCalcHitFactor(p) * 0.3f;
    if (offense ? fn_800A7EE0(p->mId >> 8 & 0xFF) == 2 && fn_800A851C(p->mId >> 8 & 0xFF, p)
                : fn_800A7F44(p->mId >> 8 & 0xFF) == 2 && fn_800A851C(p->mId >> 8 & 0xFF, p)) {
        chance = chance < 1.0f ? 1.0f : chance;
    }
    if (fn_801486A0() == 1) {
        chance = fn_800AC734(p, chance);
    } else if (offense) {
        chance = fn_800AC6BC(p->mId >> 8 & 0xFF, chance);
    } else {
        chance = fn_800AC44C(p, chance);
    }
    if (fn_800B65A0(p->mId >> 8 & 0xFF) != 0xFF && fn_80156704() && !fn_801485D4()) {
        chance = 1.0f;
    }
    chance = chance < 0.0f ? 0.0f : (chance > 1.0f ? 1.0f : chance);
    return chance;
}

int PossIsWristNearJoint(void *pUnused, Object_80039F5C *p, int right)
{
    int result = 1;
    Vector_80039F5C wrist;
    Vector_80039F5C a;
    Vector_80039F5C b;

    if (right) {
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rwrist"), &wrist, 0);
        fn_8009BFF8(p, &a, &b, 0x12);
    } else {
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lwrist"), &wrist, 0);
        fn_8009BFF8(p, &a, &b, 0x18);
    }
    if (fn_802278D0(&wrist, &a) > 0.09f) {
        result = 0;
    }
    return result;
}

void PossEndIncompletePass(void)
{
    if (fn_800AD9B4() == 3) {
        void *pBall = BallGetCurrent();
        Vector_80039F5C pos;
        Object_80039F5C *pReceiver;
        Record_800B15FC *pRecord;

        BallGetPosition(pBall, &pos);
        pReceiver = BallGetTarget(pBall);
        pRecord = fn_800B15FC();
        pRecord->mUnknown14 = 0x15;
        pRecord->mUnknownC = pos.mX;
        pRecord->mUnknown10 = pos.mY;
        if (pReceiver) {
            pRecord->mUnknown4 = pReceiver->mMotion.mPos.mX;
            pRecord->mUnknown8 = pReceiver->mMotion.mPos.mY;
            if (pReceiver->mMotion.mPos.mY < pos.mY && !fn_801783AC(0xC) && !fn_801783AC(0xB)) {
                fn_8006F0B8(0x20);
            }
        } else {
            pRecord->mUnknown4 = pos.mX;
            pRecord->mUnknown8 = pos.mY;
        }
        pRecord->mUnknown0 = BallGetLastToucher(pBall);
        fn_800B1508();
        BallSetCurrentTarget(0);
        fn_80178370();
    }
}

int PossTryCatch(void *pBall, Object_80039F5C *p, unsigned int move)
{
    int handle = 0xFFFF;
    int unknown;
    Object_80039F5C *pReceiver = 0;
    int caught = 0;
    int flags;
    int angle;
    Vector_80039F5C pos;

    if (pBall == BallGetCurrent() || fn_801486A0() == 1) {
        if ((p->mId & 0xFF) == 1) {
            float chance;

            if (p->mpState->mId == 0x1C) {
                fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
            }
            if (BallStateGet(pBall, 0) == 4 && !fn_801783AC(0xB) && !fn_801783AC(0xC)) {
                pReceiver = BallGetLastHolder(pBall);
            }
            PossClassifyCatch(p, &flags, &angle, move, handle);
            if (flags <= 0xFF) {
                chance = PossCalcCatchChance(p, pReceiver, flags, angle);
                if (fn_80178308() == (p->mId >> 8 & 0xFF)) {
                    if (fn_800E0F40(p)) {
                        chance = 0.0f;
                        if (fn_8009704C(p)) {
                            fn_80097028(p);
                        }
                    }
                    if (fn_80237260(0) < chance) {
                        caught = 1;
                    } else {
                        _Poss_iMissedCatchId = p->mId;
                    }
                } else if (PossIsCatchInBounds(p) == 1 && fn_80237260(0) < chance) {
                    caught = 1;
                } else {
                    _Poss_iMissedCatchId = p->mId;
                }
            } else if (fn_80178320() == (p->mId >> 8 & 0xFF)) {
                switch (move) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 9:
                case 10:
                    switch (p->mpState->mId) {
                    case 5:
                    case 0xC:
                    case 0x1C:
                    case 0x5E:
                        _Poss_iMissedCatchId = p->mId;
                        break;
                    }
                    break;
                }
            }
        }
    } else {
        caught = _Poss_bAllowCatch;
    }
    if (caught == 1) {
        fn_80071458(p, pBall);
        PossGiveBall(p, pBall);
        BallSetTarget(pBall, 0);
        if (handle == 0xFFFF || !fn_8009A5D4(handle)) {
            BallGetPosition(pBall, &pos);
        }
        CamGameSetModeAll(1);
    } else {
        fn_80071540(p, pBall);
    }
    return caught;
}

int PossTryReceivePitch(void *pBall, Object_80039F5C *p)
{
    int caught = 0;
    Record_8011F518 *pPitch = fn_8011F518();

    if (pBall == BallGetCurrent() && !fn_801787A0()) {
        Object_80039F5C *pReceiver = BallGetTarget(pBall);

        if (pReceiver == p || (p->mId >> 8 & 0xFF) == fn_80178320()) {
            if (p->mpState->mId == 0x1C || p->mpState->mId == 0x44
                || (pPitch->mUnknown4 != 0xB && pPitch->mUnknown4 != 9 && (p->mId >> 8 & 0xFF) == fn_80178308())) {
                caught = 1;
                fn_800A3B58(p, 8, 0);
            }
        } else if (pReceiver && (pReceiver->mId >> 8 & 0xFF) == (p->mId >> 8 & 0xFF)) {
            return 1;
        }
    } else if (BallGetTarget(pBall) == p) {
        caught = 1;
    } else if (fn_801787A0() && (p->mId & 0xFF) == 1) {
        return 1;
    }
    if (caught == 1) {
        fn_80071458(p, pBall);
        Object_80039F5C *pPasser = BallGetCurrentLastHolder();

        AudmonEventPostId(0x1E, &p->mMotion.mPos, p->mId, 0, (p->mId >> 8 & 0xFF) == (pPasser->mId >> 8 & 0xFF), 0);
        PossGiveBall(p, pBall);
        PossLogBallResult(p);
    } else {
        fn_80071540(p, pBall);
    }
    return caught;
}

void PossTryJarBall(Object_80039F5C *p)
{
    void *pBall = 0;
    float chance = 0.0f;
    int hit = 0;
    Object_80039F5C *pHitter = 0;
    int contact;
    float ratingScale;

    switch (fn_801BE648(p->mpUnknown792)) {
    case 0x5F:
    case 0xA4:
    case 0xAC:
    case 0xAD:
    case 0xAE:
    case 0xAF:
    case 0xB5:
        hit = 1;
    case 0xC4:
    case 0xC5:
        contact = 1;
        break;
    default:
        contact = 0;
        break;
    }
    if (!fn_801787A0() && fn_80178348() == (p->mId >> 8 & 0xFF)) {
        pBall = BallFindHeldBy(p);
        if (BallStateGetPrev(pBall, 0) == 4 && contact) {
            chance = 0.1f;
            ratingScale = p->mRatings[3];
            ratingScale /= 255.0f;
            ratingScale *= 0.75f;
            chance -= ratingScale * chance;
            if (p->mUnknown1160.mUnknown53) {
                chance = fn_800AC504(p->mId >> 8 & 0xFF, chance);
            }
            if (p->mUnknown1160.mUnknown54) {
                chance *= 1.5f;
            }
            if (hit && (pHitter = fn_8009BCE8(&p->mUnknown336)) != 0) {
                float hitterScale = pHitter->mRatings[5];

                hitterScale *= 0.5f;
                hitterScale /= 127.5f;
                hitterScale *= 0.75f;
                chance += chance * hitterScale;
                if (fn_801BE648(p->mpUnknown792) == 0x5F && pHitter->mUnknown1218 == 2) {
                    Vector_80039F5C toBall;
                    Point2_t toHitter;
                    int ballAngle;

                    fn_80227690(&toHitter, &pHitter->mMotion.mPos, &p->mMotion.mPos);
                    BallGetPosition(pBall, &toBall);
                    toBall.mZ = 0.0f;
                    fn_80227690(&toBall, &toBall, &p->mMotion.mPos);
                    ballAngle = fn_801CFE40(toBall.mY, toBall.mX);
                    if (MathAngleDiff(ballAngle, fn_801CFE40(toHitter.mY, toHitter.mX)) <= 0x300000) {
                        chance *= 3.0f;
                    }
                }
            }
            chance = fn_800AC7E0(p->mId >> 8 & 0xFF, chance);
            if (BallGetStateFrames(pBall) <= 0x13) {
                unsigned int frames = 20 - BallGetStateFrames(pBall);
                float perFrame = chance * 0.05f;

                chance = perFrame * frames;
            } else {
                chance = 0.0f;
            }
        }
    }
    if ((fn_800A7EE0(p->mId >> 8 & 0xFF) != 2 && chance != 0.0f && fn_80237260(0) < chance)
        || (pHitter && !fn_800A7EB8(p->mId >> 8 & 0xFF) && fn_800A851C(pHitter->mId >> 8 & 0xFF, pHitter))) {
        int unknown;
        int state = BallStateGetPrev(pBall, &unknown);

        PossReleaseBall(p);
        if (state == 4 && !fn_801783AC(0xB) && !fn_801783AC(0xC)) {
            Record_800B15FC *pRecord;

            fn_801783D0(0xC, 1);
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 0x24;
            pRecord->mUnknown4 = 1;
            fn_800B1508();
        }
        BallStateChange(pBall, state, unknown);
        BallKickUp(pBall, 1);
        fn_8013AD9C(pBall, 3);
    }
}

void PossFumble(Object_80039F5C *p)
{
    int cleared = 0;

    PossReleaseBall(p);
    if ((p->mFlags & 0x10000) || p->mpState->mId == 0x10) {
        StyleTrackerOnFumble(p, fn_80178320());
    }
    if ((p->mFlags & 0x10800) == 0x10000) {
        if (!fn_8017876C()) {
            fn_80178718(fn_8009BCE8(&p->mUnknown560.mUnknown48));
        }
        cleared = 1;
        fn_800B1698(p, fn_8017876C());
        p->mFlags &= ~0x10000;
    }
    PossStartFumble();
    if (cleared) {
        fn_80178718(0);
    }
}

void PossTryFumble(Object_80039F5C *p, Object_80039F5C *pTackler)
{
    unsigned int chance = 0;
    Block_801718E8 *pBlock = 0;
    int forced = 0;

    if (fn_801486A0() == 0 && BallGetCurrentHolder() == p && !fn_801787A0()
        && ((p->mFlags & 0x10000) || p->mpState->mId == 0x10) && !p->mUnknown1219) {
        forced = 1;
    }
    if (CheatFlagsIsSet(0x17) && !GameModeTypeGet()) {
        forced = 1;
    }
    if (!fn_800A7EB8(p->mId >> 8 & 0xFF) && pTackler && fn_800A851C(pTackler->mId >> 8 & 0xFF, pTackler)) {
        forced = 1;
    }
    if (!PossCheckDownedBall(p) && !fn_801787A0() && PossCanFumble(p)) {
        int eligible = 1;
        void *pBall = BallFindHeldBy(p);
        int handoff = BallGetTransferKind(pBall);
        int unknown;
        int state;

        if (p->mpState->mId == 0x10) {
            unsigned char result = p->mUnknown392;

            if (result != 0 && result != 3) {
                eligible = result == 5;
            }
            if (p->mUnknown1219) {
                eligible = 0;
            }
        }
        if (CheatFlagsIsSet(0x18) && !GameModeTypeGet()) {
            forced = 0;
            eligible = 0;
        }
        if (eligible) {
            int style;
            unsigned char styling;

            chance = 0;
            if (p->mpState->mId == 0x10 && pTackler == fn_8009BCE8(&p->mUnknown336) && pTackler->mUnknown1218 == 2) {
                Vector_80039F5C toBall;
                Point2_t toTackler;
                int ballAngle;
                int angle;

                fn_80227690(&toTackler, &pTackler->mMotion.mPos, &p->mMotion.mPos);
                BallGetPosition(pBall, &toBall);
                toBall.mZ = 0.0f;
                fn_80227690(&toBall, &toBall, &p->mMotion.mPos);
                ballAngle = fn_801CFE40(toBall.mY, toBall.mX);
                angle = MathAngleDiff(ballAngle, fn_801CFE40(toTackler.mY, toTackler.mX));
            }
            style = PlayerMoveGetKind(p);
            styling = style == 1 || style == 2;
            if (!styling && p->mpState->mId == 0x10) {
                styling = p->mUnknown360;
            }
            if (styling && fn_801BE648(p->mpUnknown792) == 0xE3) {
                styling = 0;
            }
            if (styling) {
                if (fn_800ABDA4(!(p->mId >> 8 & 0xFF)) == 0) {
                    chance += 5;
                } else {
                    chance += 65;
                }
            }
            if (pTackler) {
                pBlock = &pTackler->mUnknown1160;
            }
            if (pBlock && pBlock->mUnknown52) {
                int behind = 0;

                if (p->mMotion.mPos.mY < fn_80177FE0().mY) {
                    behind = 1;
                } else if (MathAngleDiff(p->mMotion.mFacing, pTackler->mMotion.mFacing) > 0x200000) {
                    behind = 1;
                }
                if (behind) {
                    chance += 30;
                }
                if (pTackler->mFlags & 0x400) {
                    fn_80156C78(0x29, 1);
                }
                pBlock->mUnknown52 = 0;
            }
            if (p->mFlags & 0x10000000) {
                if (p->mMotion.mPos.mY < fn_80177FE0().mY) {
                    if (p->mpState->mId == 0x10 && !p->mUnknown1219
                        && MathAngleDiff(p->mMotion.mFacing, pTackler->mMotion.mFacing) <= 0x2AAAA9) {
                        chance += 10;
                    }
                }
            }
            chance = fn_8009AD38(p->mId >> 8 & 0xFF, chance);
            fn_800ACE90(p, &chance);
            chance = chance > 95 ? 95 : chance;
        }
        if (forced || fn_802372EC(0, 100) < chance) {
            Record_8011F4F8 *pRequest;

            state = BallStateGetPrev(pBall, &unknown);
            pRequest = fn_8011F4F8(BallGetIndex(pBall));
            if (handoff == 0 && (p->mFlags & 0x2000) && pRequest->mUnknownB) {
                fn_801039D8(p);
            } else if (handoff == 0) {
                PossFumble(p);
            } else {
                if (state == 4 && !fn_801783AC(0xB) && !fn_801783AC(0xC)) {
                    Record_800B15FC *pRecord;

                    fn_801783D0(0xC, 1);
                    pRecord = fn_800B15FC();
                    fn_8009BD2C(p, &pRecord->mUnknown0);
                    pRecord->mUnknownC = p->mMotion.mPos.mX;
                    pRecord->mUnknown10 = p->mMotion.mPos.mY;
                    pRecord->mUnknown14 = 0x24;
                    fn_800B1508();
                }
                BallStateChange(pBall, state, unknown);
            }
        }
    }
}

void PossReleaseBall(Object_80039F5C *p)
{
    void *pBall = BallFindHeldBy(p);
    Vector_80039F5C velocity;

    BallRelease(pBall, 0, 0);
    BallGetVelocity(pBall, &velocity);
    if (fn_802270D4(&velocity) > 0.2f) {
        fn_80227264(&velocity, &velocity, 0.5f);
        BallSetVelocity(pBall, &velocity);
    }
}

void PossStartFumble(void)
{
    void *pBall = BallGetCurrent();
    Object_80039F5C *pCarrier = BallGetCurrentLastHolder();
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    Record_800B15FC *pRecord;
    Object_80039F5C *pForcer;
    int anim;

    BallGetPosition(pBall, &pos);
    pRecord = fn_800B15FC();
    pRecord->mUnknown14 = 0x12;
    pRecord->mUnknownC = pos.mX;
    pRecord->mUnknown10 = pos.mY;
    pForcer = fn_8017876C();
    fn_8009BD2C(pForcer, &pRecord->mUnknown0);
    if (pForcer) {
        pRecord->mUnknown4 = (pForcer->mFlags & 0x400) != 0;
        fn_800A8954(0x10, pForcer->mId >> 8 & 0xFF, pForcer);
    }
    fn_800B1508();
    AudmonEventPostId(0x68, &pos, pCarrier->mId, 0, 0, 0);
    fn_800A8954(0xE, pCarrier->mId >> 8 & 0xFF, pCarrier);
    fn_801783D0(0x14, 1);
    BallStateChange(pBall, 5, 1);
    BallGetVelocity(pBall, &velocity);
    velocity.mX = velocity.mX < -0.2f ? -0.2f : (velocity.mX > 0.2f ? 0.2f : velocity.mX);
    velocity.mY = velocity.mY < -0.1f ? -0.1f : (velocity.mY > 0.15f ? 0.15f : velocity.mY);
    velocity.mZ = velocity.mZ < -0.1f ? -0.1f : (velocity.mZ > 0.15f ? 0.15f : velocity.mZ);
    BallSetVelocity(pBall, &velocity);
    fn_8013AD04(pBall, &velocity, 1, 2.0f, 1.0f);
    CamGameSetModeAll(1);
    anim = fn_801BE648(pForcer ? pForcer->mpUnknown792 : pCarrier->mpUnknown792);
    if (fn_801486A0() == 0) {
        switch (anim) {
        case 0xEA:
            HudShowCallout("Gimme That!");
            break;
        case 0xEE:
            HudShowCallout("Mine!");
            break;
        default:
            HudShowCallout("Fumble");
            break;
        }
    } else {
        switch (anim) {
        case 0xEA:
            HudShowAlert("Gimme That!");
            break;
        case 0xEE:
            HudShowAlert("Mine!");
            break;
        default:
            HudShowAlert("Fumble");
            break;
        }
    }
    PassIconsHide();
    PassIconsClearReplayFlag();
}

void PossGrabBall(Object_80039F5C *p)
{
    AudmonEventPostId(0x69, &p->mMotion.mPos, p->mId, (p->mId >> 8 & 0xFF) == fn_80178308(), 0, 0);
    if (!fn_801787A0() && (p->mId >> 8 & 0xFF) == fn_80178320()) {
        fn_800A8954(0xF, p->mId >> 8 & 0xFF, p);
    }
    PossGiveBall(p, BallGetCurrent());
    PossLogBallResult(p);
}

void PossGiveBall(Object_80039F5C *p, void *pBall)
{
    int stolen;
    int resolved;
    int result;
    int status;
    Message_800F01CC message;
    Point2_t pos;

    BallGiveToPlayer(pBall, p);
    stolen = 0;
    BallSetTarget(pBall, 0);
    resolved = 0;
    if ((p->mId & 0xFF) == 1) {
        fn_800D782C(p);
    }
    p->mFlags = (p->mFlags | 0x2000000) & ~0x800000;
    result = BallStateGetPrev(pBall, &status);
    if ((p->mId >> 8 & 0xFF) == fn_80178308()) {
        if (result == 4) {
            int special = fn_801BE648(p->mpUnknown792) == 0xE1;
            StyleTrackerSetCatchFlags(fn_800E0EF0(p), special, PlayerMoveGetKind(p));
            fn_800A8954(7, p->mId >> 8 & 0xFF, p);
        }
        if (result == 3 && fn_8011F518()) {
            StyleTrackerFinishPitch(fn_80178308(), 0, 0);
        }
        if (result == 5 && status == 1) {
            StyleTrackerOnFumbleRecovery(p);
            fn_80177F70();
            fn_8009D86C();
            fn_801783D0(4, 0);
            PossCalcBallSpot(p, pBall, &pos, 0);
            PossCheckBallOut(pBall, &pos);
        }
    } else {
        stolen = 1;
        if (result == 5 && status == 1) {
            PossCalcBallSpot(p, pBall, &pos, 0);
            if (!PossCheckBallOut(pBall, &pos)) {
                stolen = 0;
            }
        }
        if (stolen) {
            if (result == 4) {
                if (fn_801486A0() != 1) {
                    if (fn_800E0EF0(p)) {
                        HudShowAlert("User Pick");
                        StyleTrackerOnInterception(1, p);
                    } else {
                        HudShowAlert("Interception");
                        StyleTrackerOnInterception(0, p);
                    }
                }
                fn_800A8954(9, p->mId >> 8 & 0xFF, p);
                if (fn_801BE648(p->mpUnknown792) == 0xE1) {
                    AudmonEventPostId(0x37, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
                }
                PossLogBallResult(p);
            } else if (result == 3) {
                if (fn_800E0EF0(p)) {
                    HudShowAlert("User Steal");
                    StyleTrackerFinishPitch(p->mId >> 8 & 0xFF, 1, 1);
                    fn_800310C0(lbl_803EA368, 0x35, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                } else {
                    StyleTrackerFinishPitch(p->mId >> 8 & 0xFF, 1, 0);
                    HudShowAlert("Stolen Pitch");
                }
                fn_800A8954(0xF, p->mId >> 8 & 0xFF, p);
                PossLogBallResult(p);
            } else {
                int offense;
                StyleTrackerOnFumbleRecovery(p);
                offense = fn_80178348();
                if (BannerIsActive(3)) {
                    BannerClear(5);
                    if ((p->mId >> 8 & 0xFF) == offense) {
                        BannerSetText(5, 0, "Offense Recovers");
                    } else {
                        BannerSetText(5, 0, "Defense Recovers");
                    }
                } else {
                    BannerClear(3);
                    if ((p->mId >> 8 & 0xFF) == offense) {
                        BannerSetText(3, 0, "Offense Recovers");
                    } else {
                        BannerSetText(3, 0, "Defense Recovers");
                    }
                }
            }
            fn_801783D0(4, 0);
            fn_80177C50(1);
        }
    }
    if (result != 3) {
        if (result != 2) {
            resolved = 1;
        }
    } else {
        Record_8011F518 *pPitch = fn_8011F518();
        if (pPitch->mUnknown4 == 0xB || pPitch->mUnknown4 == 9 || stolen) {
            resolved = 1;
        }
    }
    if (fn_801486A0() == 1) {
        resolved = 0;
        if (fn_800F06F4(0, p->mpState, 0x5F, 0xFFFF) == 0xFFFF) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 0x5F;
            if (p->mpState->mId == 0x1C) {
                fn_800F01CC(0, p->mpState, &message, p);
            } else {
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
    }
    if (resolved) {
        int i;
        int count;
        for (i = 0, count = fn_80178D70(p->mId >> 8 & 0xFF); i < count; i++) {
            Object_80039F5C *pMate = fn_80039F5C(p->mId >> 8 & 0xFF, i);
            fn_8003AB08(pMate, 0);
            fn_801C1F94(&message, 0, 4);
            if (pMate == p) {
                message.mId = 1;
            } else if (fn_801486A0()) {
                message.mId = 0x21;
            }
            switch (pMate->mpState->mId) {
            case 0x1F:
            case 0x21:
                if (pMate->mUnknown1032 != 4) {
                    fn_800F053C(0, pMate->mpState, &message, pMate);
                }
                break;
            case 0x20:
                if (pMate->mpState[1].mId == 0x21 || pMate->mpState[1].mId == 0x1F) {
                    break;
                }
            case 0x1C:
                fn_800F01CC(0, pMate->mpState, &message, pMate);
                break;
            default:
                fn_800F053C(0, pMate->mpState, &message, pMate);
                break;
            }
        }
    }
    if (!(p->mFlags & 0x400) && fn_801486A0() && fn_801486A0() != 1) {
        int port = fn_800B65A0(p->mId >> 8 & 0xFF);
        if (port != 0xFF) {
            fn_800B6714(p, port);
        }
    }
    CamGameResumeAll();
    if (resolved) {
        fn_8009E458();
    }
}

void PossLogBallResult(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    void *pBall;
    int unknown;
    int handle = 0xFFFF;
    int done = 0;

    if (mode == 3 && (pBall = BallFindHeldBy(p)) != 0) {
        Vector_80039F5C pos;
        Vector_80039F5C target;
        int status;
        int team;
        Record_800B15FC *pRecord;

        if (p->mpState->mId == 0x1C) {
            fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        }
        team = fn_80178308();
        BallGetPosition(pBall, &pos);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = pos.mX;
        pRecord->mUnknown10 = pos.mY;
        pRecord->mUnknown14 = 2;
        BallSetTransferKind(pBall, 0);
        switch (BallStateGetPrev(pBall, &status)) {
        case 4:
            if (team == (p->mId >> 8 & 0xFF)) {
                target.mX = p->mMotion.mPos.mX;
                target.mY = p->mMotion.mPos.mY;
                target.mZ = p->mMotion.mUnknown32;
                fn_800310C0(lbl_803EA368, 3, p, &target, &p->mMotion.mFacing);
                pRecord->mUnknown14 = 6;
                if (p->mpState->mId == 0x1C) {
                    pRecord->mUnknown4 = fn_8009A578(handle);
                } else {
                    pRecord->mUnknown4 = 2;
                }
            } else {
                Object_80039F5C *pReceiver;
                fn_800310C0(lbl_803EA368, 4, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                pReceiver = BallGetLastHolder(pBall);
                if (pReceiver) {
                    fn_800A3B58(pReceiver, 0xA, 0);
                }
                fn_801783D0(0x13, 1);
                pRecord->mUnknown14 = 0x14;
                if (p->mpState->mId == 0x1C) {
                    pRecord->mUnknown4 = fn_8009A578(handle);
                } else {
                    pRecord->mUnknown4 = 2;
                }
                DriveLogAddPlay(4, 0, 0, 0, 0);
                DriveLogEndDrive();
            }
            break;
        case 3:
            pRecord->mUnknown14 = 8;
            break;
        case 2:
            break;
        case 5:
            if (status == 1) {
                pRecord->mUnknown14 = 0x13;
                DriveLogStampTime();
            }
            break;
        }
        if (pRecord->mUnknown14 == 6 && fn_801783AC(1)) {
            pRecord->mUnknown14 = 8;
        }
        {
            unsigned short kind = pRecord->mUnknown14;
            if (kind == 0x14 && handle != 0xFFFF && fn_8009A5D4(handle)) {
                fn_80177FE0();
                pRecord = fn_800B15FC();
                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = pos.mX;
                pRecord->mUnknown10 = pos.mY;
                pRecord->mUnknown14 = kind;
            }
        }
        if (pRecord->mUnknown14 != 2) {
            fn_800B1508();
            if (pRecord->mUnknown14 == 6) {
                StyleTrackerAwardCatch(p);
                fn_80156C78(0x2B, 1);
            }
            fn_80053A70(p);
        }
    }
    if (done) {
        fn_80178370();
    }
}

int PossCheckBallOut(void *pBall, Point2_t *pPos)
{
    Object_80039F5C *pCarrier = 0;
    int done = 0;

    if (pBall == BallGetCurrent()) {
        Vector_80039F5C pos;
        int unknown;
        float zoneInfo;
        int state;
        int zone;
        Record_800B15FC *pRecord;

        state = BallStateGet(pBall, &unknown);
        zone = fn_80178508(pPos, &zoneInfo, state == 5);
        if (zone > 2) {
            done = fn_80178A68(pPos) <= -2.0f;
            done |= !fn_8013AD78(pBall);
            switch (state) {
            case 4:
                if (!fn_801783AC(3) && fn_801783AC(1)) {
                    PossStartFumble();
                }
                break;
            case 1: {
                int mode = fn_800AD9B4();
                pCarrier = BallGetHolder(pBall);
                if (mode == 3) {
                    if (BallGetTransferKind(pBall) == 4) {
                        PossLogBallResult(pCarrier);
                        if (pPos->mY > fn_80178A2C() && fabs(pPos->mX) >= fn_80178A08()) {
                            pPos->mX = 0.0f;
                        }
                    } else if (BallGetTransferKind(pBall)) {
                        if (BallStateGetPrev(pBall, 0) == 4) {
                            BallGetPosition(pBall, &pos);
                            pRecord = fn_800B15FC();
                            pRecord->mUnknown14 = 0x36;
                            pRecord->mUnknownC = pos.mX;
                            pRecord->mUnknown10 = pos.mY;
                            if (pCarrier) {
                                pRecord->mUnknown4 = pCarrier->mMotion.mPos.mX;
                                pRecord->mUnknown8 = pCarrier->mMotion.mPos.mY;
                            } else {
                                pRecord->mUnknown4 = pos.mX;
                                pRecord->mUnknown8 = pos.mY;
                            }
                            pRecord->mUnknown0 = BallGetLastToucher(pBall);
                            fn_800B1508();
                            pRecord = fn_800B15FC();
                            pRecord->mUnknown14 = 0x15;
                            pRecord->mUnknownC = pos.mX;
                            pRecord->mUnknown10 = pos.mY;
                            if (pCarrier) {
                                pRecord->mUnknown4 = pCarrier->mMotion.mPos.mX;
                                pRecord->mUnknown8 = pCarrier->mMotion.mPos.mY;
                            } else {
                                pRecord->mUnknown4 = pos.mX;
                                pRecord->mUnknown8 = pos.mY;
                            }
                            pRecord->mUnknown0 = BallGetLastToucher(pBall);
                            fn_800B1508();
                        }
                    } else {
                        if (pPos->mY < fn_80178A2C() && fabs(pPos->mX) >= fn_80178A08()) {
                            pPos->mY = fn_8016FAB4();
                        }
                        if (pCarrier && pCarrier->mFlags & 0x10000000) {
                            int below = 0;
                            if (pPos->mY < fn_80177FE0().mY) {
                                below = !fn_801783AC(0);
                            }
                            if (below) {
                                Record_800B15FC *pEntry;
                                Object_80039F5C *pOpponent;
                                int other;
                                float dist;

                                pEntry = fn_800B15FC();
                                pEntry->mUnknown14 = 0x3C;
                                other = (pCarrier->mId >> 8 & 0xFF) ^ 1;
                                pOpponent = fn_801244F0(pCarrier, other, 0, fn_80178D18(other), &dist, 0);
                                fn_8009BD2C(pOpponent, &pEntry->mUnknown0);
                                if (pOpponent) {
                                    pEntry->mUnknown4 = pOpponent->mUnknown8 != 0xFF;
                                }
                                fn_8009BD2C(pCarrier, &pEntry->mUnknown8);
                                fn_800B1508();
                            }
                        }
                    }
                }
                done = 1;
                break;
            }
            case 5:
                break;
            }
            if (!fn_801783AC(3)) {
                fn_801783D0(3, 1);
                fn_80178264(*pPos);
            }
            if (done) {
                pRecord = fn_800B15FC();
                if (pCarrier && !BallGetTransferKind(pBall)) {
                    fn_8009BD2C(pCarrier, &pRecord->mUnknown0);
                    if (pCarrier->mMotion.mPos.mY > -fn_80178A2C() && pCarrier->mMotion.mPos.mY < fn_80178A2C()) {
                        AudmonEventPostId(0x2A, &pCarrier->mMotion.mPos, pCarrier->mId, 0, 0, 0);
                    }
                } else {
                    fn_8009BD2C(0, &pRecord->mUnknown0);
                }
                pRecord->mUnknownC = fn_8017827C().mX;
                pRecord->mUnknown10 = fn_8017827C().mY;
                pRecord->mUnknown14 = 0x16;
                fn_8009BD2C(pCarrier, &pRecord->mUnknown4);
                fn_800B1508();
                if (pCarrier) {
                    StyleTrackerOnCarrierStopped(fn_8017827C().mY);
                }
                if (state != 1) {
                    BallStateChange(pBall, 5, 0);
                }
            }
        } else {
            fn_801783D0(3, 0);
            if (state == 1) {
                pCarrier = BallGetHolder(pBall);
                if (pCarrier && zone == 2 && (pCarrier->mId >> 8 & 0xFF) == fn_80178360()
                    && (pCarrier->mpState->mId == 0x1C || pCarrier->mpState->mId == 0x39)) {
                    fn_801783D0(2, 0);
                } else if (zone) {
                    if (pCarrier) {
                        BallGetPosition(pBall, &pos);
                        if (fn_80178508(&pos, &zoneInfo, 0)) {
                            fn_801783D0(2, 1);
                        }
                    } else {
                        fn_801783D0(2, 1);
                    }
                }
            }
        }
        if (done) {
            fn_80178370();
        }
    }
    return !done;
}

void PossResetMissedCatch(void)
{
    _Poss_bMissArmed = 0;
    _Poss_iMissedCatchId = 0;
}

void PossUpdateMissedCatch(PossBallView_t *pEvent)
{
    if (!_Poss_bMissArmed) {
        if (_Poss_iMissedCatchId) {
            _Poss_bMissArmed = 1;
        }
    } else if (!_Poss_iMissedCatchId) {
        Object_80039F5C *pTackler = fn_8009BCE8(&pEvent->mUnknownCC);
        Record_800B15FC *pRecord;

        _Poss_bMissArmed = 0;
        if ((pEvent->mUnknownCC >> 8 & 0xFF) == fn_80178308()) {
            if (!fn_801783AC(0xB) && !fn_801783AC(0xC)) {
                fn_801783D0(0xC, 1);
                fn_801783D0(0xB, 1);
                fn_80093C3C(1, 0xA, pTackler);
                pRecord = fn_800B15FC();
                fn_8009BD2C(pTackler, &pRecord->mUnknown0);
                pRecord->mUnknownC = pTackler->mMotion.mPos.mX;
                pRecord->mUnknown10 = pTackler->mMotion.mPos.mY;
                pRecord->mUnknown14 = 0x24;
                fn_800B1508();
            }
            AudmonEventPostId(0x2F, &pEvent->mUnknownC, pEvent->mUnknownCC, 0, 0, pEvent->mUnknownF4);
            fn_800A8954(8, pEvent->mUnknownCC >> 8 & 0xFF, fn_8009BCE8(&pEvent->mUnknownCC));
        } else {
            if (!fn_801783AC(0xB) && !fn_801783AC(0xC)) {
                fn_801783D0(0xB, 1);
                pRecord = fn_800B15FC();
                fn_8009BD2C(pTackler, &pRecord->mUnknown0);
                pRecord->mUnknownC = pTackler->mMotion.mPos.mX;
                pRecord->mUnknown10 = pTackler->mMotion.mPos.mY;
                pRecord->mUnknown14 = 0x23;
                fn_800B1508();
                fn_800310C0(lbl_803EA368, 0x26, pTackler, &pTackler->mMotion.mPos, &pTackler->mMotion.mFacing);
            }
            AudmonEventPostId(0x2F, &pEvent->mUnknownC, pEvent->mUnknownCC, 0, 0, pEvent->mUnknownF4);
            fn_800A8954(8, pEvent->mUnknownCC >> 8 & 0xFF, fn_8009BCE8(&pEvent->mUnknownCC));
            StyleTrackerOnCarrierContact(pTackler);
        }
    }
    _Poss_iMissedCatchId = 0;
}
}

extern "C" {
int PossCheckDownedBall(Object_80039F5C *p)
{
    int result = 0;
    int down = 0;
    int handoff;

    if (p->mIdBytes[2] == fn_80178308() && p == BallGetCurrentHolder() && p->mMotion.mPos.mY >= fn_80178A2C()) {
        return 0;
    }
    handoff = BallGetTransferKind(BallGetCurrent());
    if (CheatFlagsIsSet(0x18) && !GameModeTypeGet()) {
        return 0;
    }
    if (PlayerMoveGetKind(p)) {
        down = 1;
    }
    if (down && fn_800A7EB8(p->mIdBytes[2]) != 2 && !fn_801787A0() && BallGetCurrentHolder() == p && handoff == 0) {
        result = BallIsClearOfHands(BallGetCurrent());
    }
    if (result) {
        PossFumble(p);
    }
    return result;
}
}

/* Clock-stop rule flags, allocated under the id 'clkr'. */
static unsigned int *_ClockRule_puFlags;

extern "C" {

void ClockRuleDbSetTimeouts(int a, int b)
{
    fn_801FCE10(0, "update 'FNIG' set 'OTHG' = \x82 and 'OTAG' = \x82\n", a, b);
}

void ClockRuleInit(void)
{
    void *pHandle = fn_80238174(0, (void **)&_ClockRule_puFlags, sizeof(*_ClockRule_puFlags), 0, 0x636C6B72);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}

void ClockRuleShutdown(void)
{
}

void ClockRuleUpdate(unsigned int a)
{
    int flags;

    if (fn_8009D86C() != 6) {
        flags = fn_8009D558(a);
    } else {
        flags = 0;
    }
    if (flags & 2) {
        if (fn_8016E764()) {
            fn_8016E498();
        }
    }
    if (flags & 1) {
        if (!ClockRuleTestFlags(0x10) && ClockRuleCanEndPeriod() && !ClockRuleIsEndHeld() && fn_800AD9B4() != 3) {
            fn_8009D8CC(1);
            fn_8009D8CC(0);
            ClockRuleSetFlags(1);
            fn_80178370();
            ClockRuleSetFlags(0x10);
            ClockRuleClearFlags(0x100);
            fn_800B9B9C(lbl_803EAB84);
            if (ChallengeIsActive()) {
                ChallengePostOutcome();
            }
        }
    }
}

void ClockRuleNextPeriod(void)
{
    int state;

    fn_8009D8CC(1);
    fn_801787DC(0);
    fn_801787DC(1);
    state = fn_8009D86C();
    switch (state) {
    case 0:
        state = 4;
        ClockRuleDbSetTimeouts(0, 0);
        break;
    case 2:
        ClockRuleDbSetTimeouts(3, 3);
    case 1:
    case 3:
        state++;
        fn_800AD910(6, 0.0f);
        break;
    case 4:
        GameModeTypeGet();
        if (fn_80178AE0() == 2 && !ChallengeIsActive()) {
            ClockRuleSetFlags(0x40);
            state = 5;
            ClockRuleDbSetTimeouts(2, 2);
            fn_801FCE10(0, "update 'FNIG' set 'TOFG' = \x83\n", 1);
        } else {
            state = 6;
        }
        fn_800AD910(7, 0.0f);
        break;
    case 5:
        state = 6;
        fn_800AD910(6, 0.0f);
        break;
    }
    if (state != 6) {
        fn_8009D964(1, fn_8009D9A8(1));
    }
    if (state == 1 || state == 3 || state == 5) {
        fn_8017886C()->mUnknown1D = 0;
    }
    fn_8009D818(state);
    ClockRuleClearFlags(4);
    ClockRuleClearFlags(0x80);
    if (fn_8009D990(1) <= 120 && !fn_800BA6F8()) {
        ClockRuleSetFlags(4);
        ClockRuleSetFlags(0x80);
    }
}

void ClockRuleSetFlags(unsigned int mask)
{
    *_ClockRule_puFlags |= mask;
}

unsigned int ClockRuleTestFlags(unsigned int mask)
{
    return *_ClockRule_puFlags & mask;
}

void ClockRuleClearFlags(unsigned int mask)
{
    *_ClockRule_puFlags &= ~mask;
}

unsigned char ClockRuleIsOvertime(void)
{
    return ClockRuleTestFlags(0x40);
}

void ClockRuleSnap(void)
{
    int allow;

    ClockRuleClearFlags(0x32B);
    if (fn_8009D9D8(0) == 1) {
        fn_8009D8CC(0);
    }
    if (fn_8009D9D8(1) == 0) {
        allow = 1;
        if (!fn_80178C24()) {
            allow = 0;
        }
        if (fn_80177F70() == 6 || fn_80177F70() == 0) {
            allow = 0;
        }
        if (allow) {
            fn_8009D888(1, 0);
        }
    }
}

void ClockRuleRestartOnReady(void)
{
    int allow;
    int mode;

    if (fn_8009D9D8(1) == 0 && !ClockRuleTestFlags(1) && ClockRuleTestFlags(2)) {
        allow = 1;
        switch (fn_8009D86C()) {
        case 2:
            if (fn_8009D990(1) <= 119 && !ClockRuleTestFlags(0x100)) {
                allow = 0;
            }
            break;
        case 4:
        case 5:
            if (fn_8009D990(1) <= 299 && !ClockRuleTestFlags(0x100)) {
                allow = 0;
            }
            break;
        }
        mode = fn_80177F70();
        if (mode == 0 || mode == 6) {
            allow = 0;
        }
        if (!fn_80178C24()) {
            allow = 0;
        }
        if (allow) {
            fn_8009D888(1, 0);
        }
    }
}

void ClockRuleApplyPlayEvents(void)
{
    unsigned int count = fn_800B15D4();
    int found = 0;
    int seen3 = 0;
    int check = 0;
    unsigned short i;

    for (i = 0; i < count; i++) {
        Record_800B15FC *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3:
            seen3 = 1;
            break;
        case 11:
        case 13:
        case 20:
        case 21:
        case 30:
            found = 1;
            ClockRuleSetFlags(1);
            break;
        case 25:
            found = 1;
            ClockRuleClearFlags(0x100);
            if (seen3) {
                switch (fn_8009D86C()) {
                case 2:
                    if (pRecord->mUnknown18 <= 119) {
                        ClockRuleSetFlags(1);
                    } else {
                        ClockRuleSetFlags(2);
                    }
                    break;
                case 4:
                case 5:
                    if (pRecord->mUnknown18 <= 299) {
                        ClockRuleSetFlags(1);
                    } else {
                        ClockRuleSetFlags(2);
                    }
                    break;
                default:
                    ClockRuleSetFlags(2);
                    break;
                }
                if (fn_800B232C(0) == 2) {
                    check = 1;
                }
            } else {
                check = 1;
            }
            if (check) {
                switch (fn_8009D86C()) {
                case 2:
                case 4:
                case 5:
                    if (fn_8009D9D8(1) && fn_8009D990(1) <= 44 && fn_800B2624()) {
                        Object_80039F5C *p = fn_8009BCE8(&pRecord->mUnknown0);
                        int score = fn_801787DC(p->mId >> 8 & 0xFF);

                        if (score < fn_801787DC((p->mId >> 8 & 0xFF) ^ 1)) {
                            ClockRuleClearFlags(1);
                            ClockRuleSetFlags(0x100);
                            ClockRuleSetFlags(2);
                        }
                    }
                    break;
                }
            }
            break;
        case 22:
        case 39:
            found = 1;
            if (seen3) {
                if (pRecord->mUnknown0) {
                    ClockRuleSetStopMode();
                } else {
                    ClockRuleSetFlags(1);
                }
            }
            break;
        }
    }
    if (found) {
        fn_8009D8CC(1);
    }
    fn_8009D8CC(0);
}

void ClockRuleSetStopMode(void)
{
    switch (fn_8009D86C()) {
    case 2:
        if (fn_8009D990(1) <= 119) {
            ClockRuleSetFlags(1);
        } else {
            ClockRuleSetFlags(2);
        }
        break;
    case 4:
    case 5:
        if (fn_8009D990(1) <= 299) {
            ClockRuleSetFlags(1);
        } else {
            ClockRuleSetFlags(2);
        }
        break;
    default:
        ClockRuleSetFlags(2);
        break;
    }
}

void ClockRuleStopGameClock(void)
{
    fn_8009D8CC(1);
    ClockRuleSetFlags(1);
    fn_8009D964(0, 10);
}

int ClockRuleCanEndPeriod(void)
{
    int allow = 1;
    int mode = fn_800AD9B4();
    int state = fn_8009D86C();

    if (fn_800BA6F8() || mode == 3 || (!(unsigned char)fn_800B9A90(lbl_803EAB84) && mode != 2)) {
        allow = 0;
    }
    if (fn_801486A0() == 3 && fn_8009D990(1) != 0) {
        allow = 0;
    }
    if (state == 2 || state == 4 || state == 5) {
        if (fn_800B2624() && !ClockRuleTestFlags(0x100)) {
            ClockRuleSetFlags(0x20);
            allow = 0;
        } else {
            ClockRuleClearFlags(0x20);
        }
    }
    return allow;
}

unsigned char ClockRuleIsEndHeld(void)
{
    return ClockRuleTestFlags(0x20);
}

void ClockRuleEndPeriod(void)
{
    fn_8009D8CC(0);
    ClockRuleSetFlags(1);
    fn_8009D8CC(1);
    ClockRuleNextPeriod();
    ClockRuleClearFlags(0x10);
}

void ClockRuleSetTwoMinuteFlags(void)
{
    ClockRuleSetFlags(4);
    ClockRuleSetFlags(0x80);
}

void ClockRuleSetTwoMinuteFlag(void)
{
    ClockRuleSetFlags(4);
}

void ClockRuleResetFlags(void)
{
    *_ClockRule_puFlags = 0;
}

/* Player-name lookup ("select 'ANLP' into ... from 'AGLP' where 'DIGP' = ...")
 * It has no code in the GameCube target. */
void GetPlayerName(unsigned short id, char *pName)
{
    if (id != 0xFFFF) {
        fn_801FCE10(0, "select 'ANLP' into \x88 from 'AGLP' where 'DIGP' = \x84\n", pName, id);
    } else {
        pName[0] = ' ';
        pName[1] = 0;
    }
}

}

int _DriveLog_iCurrent;
DriveLog_t _DriveLog_aLogs[3];
int _DriveLog_aiElapsed[3];

extern "C" {
void DriveLogInit(void)
{
    int resume = 0;

    _DriveLog_iCurrent = 0;
    fn_801C1F94(_DriveLog_aLogs, 0, sizeof(_DriveLog_aLogs));
    if (resume) {
        int found;

        fn_801FCE10(0, "select 'PNIG' into \x82 from 'FNIG'\n", &found);
        resume = found;
    }
    DriveLogClearSaved();
    if (resume) {
        fn_801FCE10(0, "select 'MSDG' into \x89 from 'NIBG'\n", &_DriveLog_aLogs[_DriveLog_iCurrent]);
    }
}

void DriveLogClearSaved(void)
{
    fn_801C1F94(&_DriveLog_aLogs[1], 0, sizeof(DriveLog_t));
    fn_801C1F94(&_DriveLog_aLogs[2], 0, sizeof(DriveLog_t));
}

int DriveLogGetElapsed(void)
{
    unsigned int count = fn_8009D86C();

    count = count ? count : 1;
    if (count > 5) {
        count = 5;
    }
    return count * fn_8009D9A8(1) - fn_8009D990(1);
}

void DriveLogEndDrive(void)
{
    DriveLog_t *pLog = &_DriveLog_aLogs[_DriveLog_iCurrent];
    int value;

    if (pLog->mUnknown1E4 <= 1) {
        _DriveLog_aLogs[pLog->mUnknown1E4 + 1] = *pLog;
    }
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E4 = 0xFFFF;
    _DriveLog_aLogs[_DriveLog_iCurrent].mCount = 0;
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E8 = 0;
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EA = 0;
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EB = 0;
    value = DriveLogGetElapsed();
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E0 = value;
    _DriveLog_aiElapsed[_DriveLog_iCurrent] = value;
    fn_8022DDB4(0x4D534447, &_DriveLog_aLogs[_DriveLog_iCurrent]);
}

void DriveLogUpdateTeam(void)
{
    int team = fn_80178308();
    DriveLog_t *pLog = &_DriveLog_aLogs[_DriveLog_iCurrent];

    if (pLog->mUnknown1E4 != team && pLog->mUnknown1EB == 0) {
        DriveLogEndDrive();
        _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E4 = team;
        fn_8017C298(team, (short)fn_80177FE0().mY);
    }
    fn_8022DDB4(0x4D534447, &_DriveLog_aLogs[_DriveLog_iCurrent]);
}

void DriveLogAddPlay(int type, short a, short b, int c, int d)
{
    DriveLog_t *pLog = &_DriveLog_aLogs[_DriveLog_iCurrent];

    if (pLog->mCount < 40) {
        _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[pLog->mCount].mType = type;
        _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[pLog->mCount].mUnknown4 = a;
        _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[pLog->mCount].mUnknown6 = b;
        _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[_DriveLog_aLogs[_DriveLog_iCurrent].mCount].mUnknown8 = DriveLogGetPlayerNum(c);
        _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[_DriveLog_aLogs[_DriveLog_iCurrent].mCount].mUnknownA = DriveLogGetPlayerNum(d);
        if (_DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EA == 0 && (float)a >= 30.0f && fn_80177C38() == 0) {
            _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EA = 1;
            fn_8017C2F0(_DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E4);
        }
        if (type == 8) {
            _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E8++;
        }
        _DriveLog_aLogs[_DriveLog_iCurrent].mCount++;
        fn_8022DDB4(0x4D534447, &_DriveLog_aLogs[_DriveLog_iCurrent]);
    }
}

void DriveLogStampTime(void)
{
    _DriveLog_aiElapsed[_DriveLog_iCurrent] = DriveLogGetElapsed();
}

/* Returns one field of play [index] of the current drive. No code in the
 * GameCube target. */
int GetPlayField(int index, int field)
{
    switch (field) {
    case 0:
        return _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[index].mType;
    case 1:
        return _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[index].mUnknown4;
    case 2:
        return _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[index].mUnknown6;
    case 3:
        return _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[index].mUnknown8;
    case 4:
        return _DriveLog_aLogs[_DriveLog_iCurrent].mPlays[index].mUnknownA;
    }
    return 0;
}

/* Writes the play-by-play line for a play. No code in the GameCube target;
 * its strings remain in this unit's .rodata. */
void FormatPlay(int type, short yards, unsigned short player, unsigned short other, char *pOut)
{
    char name[16];
    char otherName[16];

    GetPlayerName(player, name);
    switch (type) {
    case 0:
        if (other != 0xFFFF) {
            GetPlayerName(other, otherName);
            sprintf(pOut, "%d yard pass from %s to %s", yards, name, otherName);
        } else {
            sprintf(pOut, "Incomplete pass by %s", name);
        }
        break;
    case 1:
        sprintf(pOut, "%d yard run by %s", yards, name);
        break;
    case 5:
        sprintf(pOut, "%d yard field goal by %s", yards, name);
        break;
    case 4:
        sprintf(pOut, "%d yard interception return by %s", yards, name);
        break;
    case 3:
        sprintf(pOut, "%d yard fumble return by %s", yards, name);
        break;
    case 2:
        sprintf(pOut, "Punt by %s", name);
        break;
    case 6:
        sprintf(pOut, "%d yard kick return by %s", yards, name);
        break;
    case 7:
        sprintf(pOut, "%d yard punt return by %s", yards, name);
        break;
    case 8:
        sprintf(pOut, "%d yard penalty", yards);
        break;
    case 9:
        sprintf(pOut, "Safety");
        break;
    case 10:
        sprintf(pOut, "%s missed extra point", name);
        break;
    case 11:
        sprintf(pOut, "2pt conversion by %s failed", name);
        break;
    case 12:
        sprintf(pOut, "%s was sacked for a %d yard loss", name, -yards);
        break;
    default:
        strcpy(pOut, "");
        break;
    }
}

/* Writes the scoring-play suffix. No code in the GameCube target; its
 * strings remain in this unit's .rodata. */
void FormatPlaySuffix(int type, short yards, unsigned short player, unsigned short other, char *pOut)
{
    char name[16];
    char otherName[16];

    GetPlayerName(player, name);
    switch (type) {
    case 0:
        if (other != 0xFFFF) {
            GetPlayerName(other, otherName);
            sprintf(pOut, " (%s Pass to %s)", name, otherName);
        } else {
            strcpy(pOut, "");
        }
        break;
    case 1:
        sprintf(pOut, " (%s Run)", name);
        break;
    case 5:
        sprintf(pOut, " (%s Kick)", name);
        break;
    case 10:
        sprintf(pOut, " (Extra Point failed)");
        break;
    case 11:
        sprintf(pOut, " (Conversion failed)");
        break;
    case 8:
        sprintf(pOut, " (%s Penalty)", name);
        break;
    default:
        strcpy(pOut, "");
        break;
    }
}

int DriveLogHasLongPlay(void)
{
    return _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EA;
}

void DriveLogSetHold(int value)
{
    DriveLog_t *pLog = &_DriveLog_aLogs[_DriveLog_iCurrent];

    if (pLog->mUnknown1EB == 0) {
        pLog->mUnknown1EB = value;
        fn_8022DDB4(0x4D534447, pLog);
    }
}

int DriveLogGetPlayerNum(int id)
{
    if (id != 0 && (id & 0xFF) == 1) {
        return fn_80039F5C(id >> 8 & 0xFF, id >> 16 & 0xFF)->mUnknown2908;
    }
    return 0xFFFF;
}

unsigned char DriveLogGetTeam(void)
{
    return _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1E4;
}

void DriveLogSetLongPlay(void)
{
    _DriveLog_aLogs[_DriveLog_iCurrent].mUnknown1EA = 1;
}
}

/* Player joint names, read in this order by another unit. */
const char *gPossJointNames[5] = {"headend", "rwrist", "lwrist", "lball", "rball"};
