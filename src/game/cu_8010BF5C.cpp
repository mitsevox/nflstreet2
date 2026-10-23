#include "engine/cu_801B9F00.h"
#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/Block_801BE60C.h"

extern "C" {
int fn_8009E180(Object_80039F5C *p);
int fn_8009F0B8(Object_80039F5C *p, int angle);
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
int fn_800A5C04(Object_80039F5C *p, int a, int b);
int fn_800DC21C(Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, short b);
int fn_8011F1CC(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
float fn_8016B938(void);
float fn_8016B974(void);
int fn_80177C38(void);
float fn_80178A08(void);
float fn_80178A2C(void);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803EAF24;
extern float lbl_803EAF28;
extern float lbl_803EAF2C;
extern float lbl_803EAF34;
extern unsigned int lbl_803EAF38;
extern float lbl_803EAF3C;
extern float lbl_803EAF40;
extern float lbl_803EAF44;
}

/* Per-state block at +336 of the player object, as fn_8010BF5C uses it. The
   field roles are read from this one body only. */
struct State_8010BF5C {
    float mUnknown0;
    float mScale;
    int mHeading;
    int mFacing;
    float mReach;
    float mDist;
    float mNear;
    float mOffset;
    float mFar;
    int mTargetAngle;
    Point_8017886C mAim;
    short mTimer;
    char mUnknown50[2];
    unsigned int mTicks;
    unsigned short mTickLimit;
};

/* Partial reconstruction: the control flow, calls and stores follow the
   target 0x8010BF5C-0x8010C864, but the body is not byte-identical
   (0x904 of 0x908 bytes, 135 differing words, mostly block placement of the
   shared give-up exit and the kind tests) and the literal pool does not yet
   compile to the target slice. */
extern "C" int fn_8010BF5C(Object_80039F5C *p)
{
    State_8010BF5C *pState = (State_8010BF5C *)&p->mUnknown336;
    float side = 0.0f;
    int refreshed;
    Object_800B26B0 *pMotion = &p->mMotion;
    float reach = pState->mReach;

    refreshed = 0;
    Point_8017886C ball;
    int result;
    int forced;
    Object_80039F5C *pTarget;
    Message_800F01CC message;
    Vector_80039F5C ballPos;

    ball = fn_80177FE0();
    result = 0;
    forced = 0;
    fn_8016B974();
    fn_8010A2DC(p, 0, -1);
    pState->mTicks++;
    pTarget = fn_80137B40();
    fn_80137D58(fn_801374BC(), &ballPos);

    pState->mTimer = (signed char)(pState->mTimer - 1);
    if (pState->mTimer < 0) {
        int spread = 255 - p->mRatings[8];
        if (spread < 0) {
            spread = 0;
        }
        pState->mTimer = (signed char)(pState->mTimer + 2 + fn_802372EC(0, (unsigned int)spread >> 5));
        if (pTarget != 0 && fn_800B65A0(p->mIdBytes[2]) != 0xFF &&
            fn_800B65A0(pTarget->mIdBytes[2]) == 0xFF && fn_80177C38() == 0) {
            pState->mTimer -= (short)((float)pState->mTimer > pState->mTimer * fn_8016B938()
                                          ? pState->mTimer * fn_8016B938()
                                          : (float)pState->mTimer);
            if (fn_8011F1CC() != 0 && (pTarget->mFlags & 0x8000)) {
                pState->mTimer -= (short)((float)pState->mTimer > pState->mTimer * fn_8016B974()
                                              ? pState->mTimer * fn_8016B974()
                                              : (float)pState->mTimer);
            }
        }
        refreshed = 1;
    }

    if (!(p->mFlags & 0x4000) && refreshed != 0) {
        unsigned int i;
        unsigned int count;
        Point_8017886C aim;
        /* 8 bytes in the target frame (the Point at +0x60 follows it at
           +0x58), so held as a 2D point; inferred from the frame only. */
        Point_8017886C toAim;
        float dist;
        float offset;
        float nearLimit;
        float farLimit;

        if (pTarget == 0) {
            if (fn_8013BA58(fn_801374BC(), 0) == 4) {
                pTarget = fn_80137B64();
            }
        }
        if (pTarget != 0) {
            count = fn_80178D18(p->mIdBytes[2]);
            for (i = 0; i < count; i++) {
                unsigned int id = p->mId;

                if (i != ((id >> 16) & 0xFF)) {
                    Object_80039F5C *pOther = fn_80039F5C((id >> 8) & 0xFF, i);
                    if (pOther->mpState->mId == 85) {
                        if (pOther->mMotion.mPos.mX > p->mMotion.mPos.mX) {
                            side = -lbl_803EAF44;
                        } else {
                            side = lbl_803EAF44;
                        }
                        if (((pTarget->mMotion.mPos.mX > ball.mX && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX) ||
                             (pTarget->mMotion.mPos.mX < ball.mX && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)) &&
                            (pTarget->mFlags & 0x8000)) {
                            goto give_up;
                        }
                    }
                }
            }

            if (pState->mTicks > pState->mTickLimit && pState->mTickLimit != 0) {
                goto give_up;
            }
            if ((pTarget->mFlags & 0x8000) && pState->mTicks > lbl_803EAF38 &&
                ball.mY - pTarget->mMotion.mPos.mY < reach * lbl_803EAF3C) {
                goto give_up;
            }
            if ((float)pState->mTicks > lbl_803EAF34 && (pTarget->mFlags & 0x8000) &&
                ball.mY - pTarget->mMotion.mPos.mY < reach) {
                goto give_up;
            }

            aim.mX = pTarget->mMotion.mPos.mX + side;
            aim.mX = aim.mX < 2.0f - fn_80178A08()
                         ? 2.0f - fn_80178A08()
                         : (aim.mX > fn_80178A08() - 2.0f ? fn_80178A08() - 2.0f : aim.mX);
            aim.mY = ball.mY + lbl_803EAF2C;
            aim.mY = aim.mY > fn_80178A2C() + 2.0f ? fn_80178A2C() + 2.0f : aim.mY;
            fn_80227690(&toAim, &aim, &pMotion->mPos);
            dist = fn_802270A4(&toAim);
            offset = fabsf(pMotion->mPos.mX - aim.mX);
            nearLimit = lbl_803EAF24;
            farLimit = lbl_803EAF28;
            if (pMotion->mUnknown28 != 0.0f) {
                nearLimit *= 0.5f;
                farLimit *= 0.5f;
            }
            pState->mOffset = offset;
            pState->mAim = aim;
            pState->mFar = farLimit;
            pState->mDist = dist;
            pState->mNear = nearLimit;
            pState->mTargetAngle = pTarget->mMotion.mUnknown32;
            {
                unsigned int angle = fn_801CFFD0(pTarget->mMotion.mUnknown32, 0x400000);

                if ((offset > farLimit && (angle > 0x200000 && angle < 0x600000) && fn_800DC21C(pTarget) != 0) ||
                    offset > 2.0f * farLimit || (offset > 0.5f && pState->mScale == 1.0f)) {
                    pState->mHeading = fn_801CFE40(toAim.mY, toAim.mX) & 0xFFFFFF;
                    pState->mFacing = fn_801CFE40(toAim.mY, toAim.mX);
                    pState->mScale = 1.0f;
                } else if (dist > nearLimit || offset > farLimit) {
                    pState->mHeading = fn_801CFE40(toAim.mY, toAim.mX) & 0xFFFFFF;
                    pState->mFacing = 0xC00000;
                    pState->mScale = 0.9f;
                } else {
                    pState->mFacing = 0xC00000;
                    pState->mScale = 0.0f;
                    pState->mHeading = 0xC00000;
                }
            }
        }
    }

    if (fn_800A5C04(p, pState->mHeading, pState->mFacing) != 0) {
        return 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (refreshed != 0) {
            int kind;

            result = fn_8009F7A4(p, 0) == 1;
            kind = fn_8009E180(p);
            if (kind > 2) {
                if (kind == 4) {
                    int pass = 0;
                    Object_80039F5C *pCarrier = fn_80137BEC();

                    if (pCarrier != 0) {
                        if (fabsf(pCarrier->mMotion.mPos.mX - p->mMotion.mPos.mX) < 12.0f) {
                            Object_80137ABC *pBall = fn_801374BC();
                            Vector_80039F5C landing;

                            if (fn_80138064(pBall, &landing) != 0) {
                                Point_8017886C here = fn_80177FE0();

                                if (fabsf(landing.mX - here.mX) > 8.0f) {
                                    pass = fn_802372EC(0, 32) < (unsigned int)((p->mRatings[8] >> 5) + 8);
                                } else {
                                    Vector_80039F5C velocity;

                                    fn_80137EC4(pBall, &velocity);
                                    if ((landing.mY < p->mMotion.mPos.mY + 12.0f &&
                                         fn_802372EC(0, 100) < (unsigned int)((p->mRatings[8] >> 5) + 8)) ||
                                        velocity.mZ < 0.0f) {
                                        pass = 1;
                                    }
                                }
                            }
                        }
                        if (ballPos.mY > p->mMotion.mPos.mY + lbl_803EAF40) {
                            pass = 1;
                            forced = 1;
                        }
                    } else {
                        pass = 1;
                    }
                    if (pass == 1 && (fn_8009F0B8(p, 0x2AAAAA) != 0 || forced != 0)) {
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 24;
                        message.mUnknown1[0] = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                } else if (kind == 6 ||
                           fn_802372EC(0, 255) < (unsigned short)(p->mRatings[8] / 2)) {
                    goto give_up;
                }
            }
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pState->mHeading;
        p->mUnknown512.mUnknown8 = pState->mFacing;
        p->mUnknown512.mUnknown0 = pState->mScale;
        if (pState->mScale == 1.0f) {
            p->mUnknown512.mUnknown15 = 1;
        }
    }
    return result;

give_up:
    fn_801C1F94(&message, 0, 4);
    message.mId = 2;
    message.mUnknown1[0] = 1;
    fn_800F053C(0, p->mpState, &message, p);
    return 1;
}
