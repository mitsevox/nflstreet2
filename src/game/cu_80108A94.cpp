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

/* The block at player +336 (88 bytes), defined identically in each
   cu_800EFC68 fragment that uses it. +0 to +16 hold the pass view that
   fn_80108C34 and fn_80108DF8 read from the other player's block. */
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

struct Sphere_80108DF8 {
    Vector_80039F5C mCenter;
    float mRadius;
};

/* Ball, three positions, the landing point and the time filled by
   fn_80107680. */
struct Points_800F3A6C {
    Object_80137ABC *mpUnknown0;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    Vector_80039F5C mUnknown28;
    Point_8017886C mUnknown40;
    float mUnknown48;
};

extern "C" {
int fn_800997F4(Object_80039F5C *p, Object_80137ABC *pBall, float range, void *pBlock, int a, int b, int c, int *pOutA,
                int *pOutB);
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float range);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, int index);
int fn_8009A6EC(Object_80039F5C *p);
int fn_8009A77C(Object_80039F5C *p);
void fn_8009A8D4(void *p);
int fn_80168E00(int team, int index, unsigned char *pOut);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
int fn_80178308(void);
int fn_801783AC(int bit);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8009F0B8(Object_80039F5C *p, int angle);
float fn_800ACB8C(int team);
void fn_801074B4(Object_80039F5C *p, Points_800F3A6C *pInfo);
int fn_801CFFD0(int a, int b);
extern float lbl_803ECB08;
}

extern "C" void fn_80108A94(Object_80039F5C *p, Points_800F3A6C *pInfo) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;

    if (pBlock->mUnknown44 != 0.0f) {
        if (pBlock->mUnknown52 == 1 && pBlock->mUnknown36 == pBlock->mUnknown40) {
            pBlock->mUnknown48 = 12;
        }
        if (pBlock->mUnknown60 == 1 && pBlock->mUnknown44 >= 0.72f && pBlock->mUnknown36 == pBlock->mUnknown40 &&
            fn_801CFFD0(p->mMotion.mFacing, pBlock->mUnknown36) <= 0xE38E2 &&
            fn_801CFFD0(p->mMotion.mUnknown32, pBlock->mUnknown36) <= 0xE38E2) {
            pBlock->mUnknown48 = 1;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown48;
    if (pBlock->mUnknown40 == pBlock->mUnknown36 && p->mMotion.mUnknown28 > lbl_803ECB08 * 0.05f &&
        fn_801CFFD0(p->mMotion.mUnknown32, pBlock->mUnknown40) > 0x2E38E3 &&
        fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
        pBlock->mUnknown44 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
        pBlock->mUnknown58 = 2;
    }
    if (pBlock->mUnknown53 == 1) {
        fn_801074B4(p, pInfo);
    }
}

extern "C" int fn_80108C34(Object_80039F5C *p, Block_800F4A74 *pBlock, Points_800F3A6C *pInfo,
                           Object_80039F5C *pOther) {
    int result = 0;

    if (pBlock->mUnknown62 != 0 || p->mUnknown2914 == 17 || p->mUnknown2914 == 18 || p->mUnknown2914 == 16 ||
        fn_8009F0B8(p, 0x400000) == 1 || pBlock->mUnknown49 == 0) {
        result = 1;
    } else if (pOther != 0 && pOther->mpState->mId == 28 && fn_80137B40() != pOther) {
        Block_800F4A74 *pOtherBlock = (Block_800F4A74 *)&pOther->mUnknown336;

        if (fn_800ACB8C(p->mIdBytes[2]) < (float)pOtherBlock->mUnknown0 / (float)pOtherBlock->mUnknown16 &&
            fn_802372EC(0, 0xFF) < (unsigned short)(p->mRatings[8] / 3)) {
            result = 1;
        }
    } else if (pInfo->mUnknown28.mZ < 0.0f && fn_802372EC(0, 0xFF) < (unsigned short)(p->mRatings[8] / 5)) {
        result = 1;
    }
    if (pOther != 0) {
        switch (fn_801BE648(pOther->mpUnknown792)) {
        case 0xE0:
        case 0xE1:
            if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
                result = 0;
            }
            break;
        }
    }
    return result;
}

extern "C" void fn_80108DF8(Object_80039F5C *p, Points_800F3A6C *pInfo, int quick) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    int outA = -1;
    int outB = 0;
    int handle = 0x1FFFFFFF;
    int mode;
    float range;
    float height;
    Object_80039F5C *pOther;

    if (fn_80108C34(p, pBlock, pInfo, fn_80137B88(pInfo->mpUnknown0)) == 0) {
        return;
    }
    mode = 1;
    if (!(p->mFlags & 0x4000)) {
        mode = 3;
    }
    if (p->mUnknown8 == 0xFF) {
        range = 120.0f;
    } else {
        range = 17.0f;
    }
    if (quick == 0 && !fn_801783AC(11)) {
        unsigned char i;

        for (i = 0; i <= 2; i++) {
            int index = fn_80168E00(fn_80178308(), i, 0);

            if (index != 0xFF) {
                Object_80039F5C *pMate = fn_80039F5C(fn_80178308(), index);
                float mateTime = fn_8022781C(&pMate->mMotion.mPos, &pInfo->mUnknown40) / fn_8016D9F4(pMate, 1.0f, 1.0f);
                float time = fn_8022781C(&p->mMotion.mPos, &pInfo->mUnknown40) / fn_8016D9F4(p, 1.0f, 1.0f);

                if (time > mateTime - 45.0f || pInfo->mUnknown48 > mateTime - 45.0f) {
                    break;
                }
            }
        }
    }
    pOther = fn_80137B88(pInfo->mpUnknown0);
    if (pOther != 0 && pOther->mpState->mId == 28 && !fn_801783AC(11)) {
        Point_8017886C toTarget;
        Point_8017886C toPlayer;

        fn_80227690(&toTarget, &pInfo->mUnknown16, &pOther->mMotion.mPos);
        fn_80227690(&toPlayer, &p->mMotion.mPos, &pOther->mMotion.mPos);
        if (fn_801CFFD0(toPlayer.Heading(), toTarget.Heading()) > 0x355555) {
            Block_800F4A74 *pOtherBlock = (Block_800F4A74 *)&pOther->mUnknown336;

            if (pOtherBlock->mUnknown0 < pOtherBlock->mUnknown16 && pBlock->mUnknown49 == 3) {
                /* Built but never read in the target. */
                Sphere_80108DF8 sphere;

                sphere.mCenter.mX = pOtherBlock->mUnknown4.mX;
                sphere.mCenter.mY = pOtherBlock->mUnknown4.mY;
                sphere.mCenter.mZ = pOtherBlock->mUnknown4.mZ;
                sphere.mRadius = 0.4f;
                fn_8009A8D4(pBlock);
            }
        }
    }
    fn_801380AC(fn_80137ABC(pBlock->mUnknown64), &height);
    if (fn_8009A6EC(p) != 0) {
        handle = fn_800997F4(p, fn_80137ABC(pBlock->mUnknown64), range, pBlock, 3, 0, 0, &outA, &outB);
    }
    if (handle == 0x1FFFFFFF) {
        handle = fn_80099734(p, fn_80137ABC(pBlock->mUnknown64), 0, mode, pBlock, 1, 0, 0, fn_8009A77C(p), range);
        if (handle == 0x1FFFFFFF) {
            return;
        }
    }
    if (((handle >> 29) & 3) == 1) {
        fn_8009A1A8(p, handle, outA, outB, pBlock->mUnknown64);
    } else {
        fn_80099F04(p, handle, pBlock->mUnknown64);
    }
}
