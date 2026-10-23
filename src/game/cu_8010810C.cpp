#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
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

struct Block_800F4A74 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

struct Info_800F3A6C {
    Point_8017886C mUnknown0;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
};

/* Object pointer, three positions, a pair and a float filled by fn_800F39FC
   and passed to fn_800F2EC8, fn_800F30AC, fn_800F3284, fn_800F3838,
   fn_800F3A6C, fn_800F3B54, fn_800F3D38, fn_800F3F90 and fn_800F4038. Only
   the accessed prefix is declared; the size is unknown. */
struct Points_800F3A6C {
    Object_80137ABC *mpUnknown0;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    Vector_80039F5C mUnknown28;
    Point_8017886C mUnknown40;
    float mUnknown48;
};

/* View of another player's +336 block read by fn_800F3344 while that player
   is in state 28. Only the accessed prefix is declared; the size is unknown. */
struct Block_800F3344 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
};
extern "C" {
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801783AC(int bit);
float fn_801CFB94(int angle);
int fn_801CFFD0(int a, int b);
void fn_802271A4(Point_8017886C *pOut, Point_8017886C *pIn);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);
extern float lbl_803ECB08;
extern const float lbl_803ED6CC;
}

extern "C" void fn_8010810C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Points_800F3A6C *pInfo, Info_800F3A6C *pResult, float scale) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Point_8017886C toTarget;
    Point_8017886C ballToSpot;
    Point_8017886C otherToSpot = {0.0f, 0.0f};
    Point_8017886C meToOther;
    float otherTime = 0.0f;
    float ballTime;
    float myTime;
    float time;
    float ratio;
    float factor;
    int blocked = 0;

    fn_80227690(&toTarget, pB, &p->mMotion.mPos);
    fn_80227690(&ballToSpot, pA, &pInfo->mUnknown16);
    ballTime = fn_802270A4(&ballToSpot) / fn_802270A4(&pInfo->mUnknown28);
    myTime = fn_802270A4(&toTarget) /
             (lbl_803ECB08 * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f)));
    if (pOther != 0) {
        fn_80227690(&otherToSpot, pA, &pOther->mMotion.mPos);
        fn_80227690(&meToOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
        otherTime = fn_802270A4(&otherToSpot) /
                    (lbl_803ECB08 * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f)));
    } else {
        otherToSpot.mX = otherToSpot.mY = 0.0f;
        meToOther.mX = meToOther.mY = 0.0f;
    }
    if (pOther != 0 && pOther->mpState->mId == 28) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;
        Point_8017886C toPass;

        ballTime = (float)(pPass->mUnknown16 - pPass->mUnknown0);
        fn_80227690(&toPass, &pPass->mUnknown4, &p->mMotion.mPos);
        myTime = fn_802270A4(&toPass) /
                 (lbl_803ECB08 * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f)));
    }
    switch (pBlock->mUnknown49) {
    case 1:
        time = myTime;
        if (myTime < 4.0f) {
            time = myTime * 2.0f;
        }
        break;
    case 3:
        time = ballTime * scale;
        break;
    case 2:
        if (myTime < otherTime && fn_802270A4(&meToOther) < 2.0f && fn_802270A4(&toTarget) < fn_802270A4(&otherToSpot)) {
            time = myTime * (2.0f / 3.0f);
        } else {
            time = ballTime;
            if (pBlock->mUnknown55 != 0) {
                time = myTime;
            }
        }
        time *= scale;
        break;
    default:
        time = ballTime;
        break;
    }
    pBlock->mUnknown28 = pB->mX;
    pBlock->mUnknown32 = pB->mY;
    if (time > 0.0f) {
        ratio = fn_802270A4(&toTarget) / time;
    } else {
        ratio = 0.0f;
    }
    if (ratio > p->mMotion.mUnknown36) {
        factor = 1.0f;
    } else if (p->mMotion.mUnknown36 != 0.0f) {
        factor = ratio / p->mMotion.mUnknown36;
    } else {
        factor = 0.0f;
    }
    if (fn_801783AC(11) == 1 || fn_801783AC(12) == 1) {
        if (fn_80237260(0) > p->mRatings[3] / 255.0f && fn_8022781C(&pInfo->mUnknown16, &p->mMotion.mPos) > 6.0f) {
            factor /= 3.0f;
        }
    }
    pBlock->mUnknown36 = toTarget.Heading() & 0xFFFFFF;
    if (pBlock->mUnknown63 != 0) {
        pBlock->mUnknown40 = (pResult->mUnknown20 + 0x800000) & 0xFFFFFF;
        if (fn_801CFFD0(pBlock->mUnknown40, p->mMotion.mFacing) > 0x5FFFFF) {
            int heading = p->mMotion.mFacing;

            if (fn_801CFFD0(heading, 0x400000) <= 0x1FFFFF && pInfo->mUnknown16.mY < p->mMotion.mPos.mY &&
                fn_8013BA58(pInfo->mpUnknown0, 0) == 4) {
                Point_8017886C toBall;

                fn_80227690(&toBall, &pInfo->mUnknown16, &p->mMotion.mPos);
                heading = toBall.Heading();
            }
            if (((heading - pBlock->mUnknown40) & 0xFFFFFF) <= 0x7FFFFF) {
                pBlock->mUnknown40 = (p->mMotion.mFacing - 0x5F49F5) & 0xFFFFFF;
            } else {
                pBlock->mUnknown40 = (p->mMotion.mFacing + 0x5F49F5) & 0xFFFFFF;
            }
        }
    } else {
        if (pOther != 0) {
            if (myTime < ballTime - 2.5f || (myTime < 12.0f && ballTime < 12.0f) ||
                p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f) {
                if (fn_802270A4(&toTarget) < 7.0f) {
                    blocked = 1;
                }
            }
            if (fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 && factor > 0.9f &&
                fn_802270A4(&meToOther) < 5.0f && p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + 5.0f &&
                fn_801CFFD0(pBlock->mUnknown40, 0x400000) <= 0x1C71C6) {
                blocked = 0;
            }
            if (blocked != 0 && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 &&
                (fn_802270A4(&meToOther) > 10.0f ||
                 fn_801CFFD0(pOther->mMotion.mUnknown32, otherToSpot.Heading()) > 0x155555)) {
                blocked = 0;
            }
        }
        if (pOther != 0 && blocked != 0) {
            Point_8017886C toBall;
            Point_8017886C toOtherPlayer;
            Point_8017886C sum;

            fn_80227690(&toBall, &pInfo->mUnknown16, &p->mMotion.mPos);
            fn_80227690(&toOtherPlayer, &pOther->mMotion.mPos, &p->mMotion.mPos);
            fn_802271A4(&toBall, &toBall);
            fn_802271A4(&toOtherPlayer, &toOtherPlayer);
            if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0x18E38D && pBlock->mUnknown49 != 0) {
                toBall.mX *= 0.35f;
                toBall.mY = 0.0f;
                toOtherPlayer.mX *= 0.65f;
                toOtherPlayer.mY *= 0.65f;
            } else {
                switch (pBlock->mUnknown49) {
                case 0:
                case 2:
                    toOtherPlayer.mX = 0.0f;
                    toOtherPlayer.mY = 0.0f;
                    break;
                case 1:
                case 3:
                    toBall.mX = 0.0f;
                    toBall.mY = 0.0f;
                    break;
                }
            }
            fn_80227638(&sum, &toBall, &toOtherPlayer);
            pBlock->mUnknown40 = sum.Heading();
        } else {
            int turn;

            pBlock->mUnknown40 = pBlock->mUnknown36;
            turn = fn_801CFFD0(pBlock->mUnknown40, p->mMotion.mFacing);
            if (turn > 0x400000) {
                factor = fn_801CFB94(turn / 2) * 0.72f;
                pBlock->mUnknown60 = 0;
            }
        }
    }
    if (factor < 1e-7f) {
        factor = 0.0f;
    }
    pBlock->mUnknown44 = factor;
}
