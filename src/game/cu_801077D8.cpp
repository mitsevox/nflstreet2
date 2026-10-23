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
float fn_8009F168(Vector_80039F5C *p, void *pVelocity, Vector_80039F5C *pOther, float speed);
int fn_801783AC(int bit);
void fn_80227248(void *pOut, void *pIn, float scale);
extern float lbl_803ECB08;
extern const float lbl_803ED6CC;
float fn_80178A08(void);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" void fn_801077D8(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74 *pBlock, Info_800F3A6C *pInfo,
                            Points_800F3A6C *pPoints) {
    float progress = 0.0f;
    int passing = 0;

    if (pOther->mpState->mId == 28) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        passing = 1;
        progress = (float)pPass->mUnknown0 / (float)pPass->mUnknown16;
    }
    if ((pInfo->mUnknown32 < 2.5f || (passing && progress > 0.6f)) && pPoints->mUnknown28.mZ < 0.0f
        && (pPoints->mUnknown16.mZ < 5.0f || pInfo->mUnknown40 > pInfo->mUnknown36
            || fabsf(p->mMotion.mPos.mX) > fabsf(pOther->mMotion.mPos.mX))) {
        Point_8017886C delta;
        Point_8017886C toTarget;
        int heading;
        int turn;

        fn_80227690(&delta, &pPoints->mUnknown40, &p->mMotion.mPos);
        fn_802270A4(&delta);
        heading = (pInfo->mUnknown20 + 0x800000) & 0xFFFFFF;
        fn_80227690(&toTarget, &pPoints->mUnknown16, &p->mMotion.mPos);
        turn = fn_801CFFD0(heading, fn_801CFE40(toTarget.mY, toTarget.mX));
        if (turn <= 0x18E38D
            || (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.0f && passing && progress > 0.5f && turn <= 0x1FFFFF)) {
            pBlock->mUnknown54 = 1;
        }
    }
}

extern "C" void fn_801079BC(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Points_800F3A6C *pInfo) {
    float x;
    float dx;

    x = pInfo->mUnknown4.mX;
    pA->mX = x;
    pA->mY = pInfo->mUnknown4.mY;
    pB->mX = x;
    pB->mY = pA->mY;
    dx = pInfo->mUnknown4.mX - p->mMotion.mPos.mX;
    if (dx > 0.0f) {
        dx *= 0.33333334f;
        if (dx > 2.0f) {
            dx = 2.0f;
        }
    } else {
        dx *= 0.33333334f;
        if (dx < -2.0f) {
            dx = -2.0f;
        }
    }
    pB->mX = x - dx;
    if (pOther != 0) {
        float y = pOther->mMotion.mPos.mY + 4.0f;
        float low = pInfo->mUnknown4.mY - 1.0f;

        if (y < low) {
            y = low;
        } else {
            float high = pInfo->mUnknown4.mY + 2.0f;

            if (y > high) {
                y = high;
            }
        }
        pB->mY = y;
    }
}

extern "C" void fn_80107A9C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown64);
    Point_8017886C ballToOther;
    Point_8017886C offset;
    Point_8017886C delta;

    pA->mX = pInfo->mUnknown40.mX;
    ballToOther.mX = ballToOther.mY = 0.0f;
    pA->mY = pInfo->mUnknown40.mY;
    pB->mX = pA->mX;
    pB->mY = pA->mY;
    if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) != 0) {
        fn_80227690(&ballToOther, &pOther->mMotion.mPos, &pBall->mState.mPos);
    }
    if (fn_80178A08() - fabsf(pA->mX) < 5.0f && !fn_801783AC(12) && !fn_801783AC(11)) {
        pA->mY -= 6.0f;
    }
    if (pOther->mpState->mId == 28 && fn_80137B40() != pOther) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        fn_80227538(&offset, ballToOther.Heading(), 0.5f);
        if (pPass->mUnknown0 < pPass->mUnknown16) {
            pB->mX = pPass->mUnknown4.mX;
            pB->mY = pPass->mUnknown4.mY;
            fn_80227690(pB, pB, &offset);
        }
    } else {
        pBlock->mUnknown55 = 1;
        pBlock->mUnknown58 = 0;
        fn_80227538(&offset, ballToOther.Heading(), 1.5f);
        fn_80227690(pB, pA, &offset);
        fn_80227690(&delta, pB, &p->mMotion.mPos);
        if (fn_801CFFD0(delta.Heading(), p->mMotion.mUnknown32) > 0x471C72) {
            int turn = fn_801CFFD0(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);

            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) > 35.0f && pOther->mMotion.mUnknown28 > 0.0f) {
                if (turn <= 0x155554) {
                    fn_80227538(&delta, pOther->mMotion.mUnknown32, 0.5f);
                    fn_80227638(pB, &p->mMotion.mPos, &delta);
                }
            } else {
                pB->mX = pInfo->mUnknown40.mX;
                pB->mY = pInfo->mUnknown40.mY;
                pBlock->mUnknown55 = 0;
            }
        }
    }
}

extern "C" void fn_80107D48(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Point_8017886C offset;

    pA->mX = pInfo->mUnknown4.mX;
    pA->mY = pInfo->mUnknown4.mY;
    if (pInfo->mUnknown16.mZ > 3.0f && fn_801CFFD0(pResult->mUnknown24, 0x400000) <= 0x11C71B &&
        (p->mMotion.mPos.mY < pInfo->mUnknown40.mY || p->mMotion.mPos.mY > pInfo->mUnknown4.mY)) {
        pA->mX = pInfo->mUnknown40.mX;
        pA->mY = pInfo->mUnknown40.mY;
        fn_80227690(&offset, pA, &pOther->mMotion.mPos);
        fn_80227538(&offset, offset.Heading(), 2.5f);
        fn_80227638(pA, pA, &offset);
    }
    if (pOther->mpState->mId == 28 && fn_80137B40() != pOther) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;
        int angle;

        if (pPass->mUnknown0 < pPass->mUnknown16) {
            pA->mX = pPass->mUnknown4.mX;
            pA->mY = pPass->mUnknown4.mY;
            angle = pOther->mMotion.mUnknown32;
            if (angle <= 0x38E38D) {
                angle += 0x71C71;
            } else if (angle > 0x471C72) {
                angle -= 0x71C71;
            }
            fn_80227538(&offset, angle, 1.0f);
            fn_80227638(pA, pA, &offset);
        } else {
            pA->mX = pOther->mMotion.mPos.mX;
            pA->mY = pOther->mMotion.mPos.mY;
            angle = pOther->mMotion.mUnknown32;
            if (angle <= 0x38E38D) {
                angle += 0x71C71;
            } else if (angle > 0x471C72) {
                angle -= 0x71C71;
            }
            fn_80227538(&offset, angle, 1.0f);
            fn_80227638(pA, pA, &offset);
        }
    }
    pB->mX = pA->mX;
    pB->mY = pA->mY;
    if (pOther != 0) {
        if (fn_801CFFD0(p->mMotion.mUnknown32, pOther->mMotion.mUnknown32) <= 0x155554) {
            pBlock->mUnknown61 = 1;
        } else if (pResult->mUnknown32 < 10.0f && pOther->mpState->mId != 28 && pResult->mUnknown36 < 5.0f) {
            float time = fn_8009F168(&pOther->mMotion.mPos, &pOther->mMotion.mUnknown40, &p->mMotion.mPos,
                                     lbl_803ECB08 * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f))) -
                         0.25f;

            if (time < 0.1f) {
                time = 0.1f;
            }
            fn_80227248(pB, &pOther->mMotion.mUnknown40, time);
            fn_80227638(pB, pB, &pOther->mMotion.mPos);
        }
    }
}
