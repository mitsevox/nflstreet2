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

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

/* The block at player +336 (88 bytes). The same layout is used in
   src/game/cu_80108A94.cpp and cu_80109248.cpp; fields +36 to +64 are
   named as in src/game/cu_80104C9C.cpp, and +0 to +16 hold the pass view
   that fn_80108C34 and fn_80108DF8 read from the other player's block. */
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

/* Output of fn_801076F0. */
struct Result_801076F0 {
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

/* View of the block at player +336 with the mode in the top 3 bits and the
   state in the next 4 bits of the word at +52, and the point at +56. */
struct Block_801096D4 {
    char mUnknown0[52];
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Rest : 25;
    Point_8017886C mUnknown56;
};

extern "C" {
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_800AC324(int team);
void fn_80106A60(Object_80039F5C *p);
void fn_80106C24(Object_80039F5C *p, Block_800F4A74 *pBlock);
void fn_80107680(Points_800F3A6C *pInfo, int index);
void fn_801076F0(Object_80039F5C *pA, Object_80039F5C *pB, Result_801076F0 *pOut, Points_800F3A6C *pInfo);
void fn_801077D8(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74 *pBlock, Result_801076F0 *pResult,
                 Points_800F3A6C *pInfo);
void fn_801079BC(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                 Points_800F3A6C *pInfo);
void fn_80107A9C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                 Result_801076F0 *pResult, Points_800F3A6C *pInfo, float *pScale);
void fn_80107D48(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                 Result_801076F0 *pResult, Points_800F3A6C *pInfo, float *pScale);
void fn_80108074(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                 Points_800F3A6C *pInfo);
void fn_8010810C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                 Points_800F3A6C *pInfo, Result_801076F0 *pResult, float scale);
void fn_80108954(Object_80039F5C *p, Object_80039F5C *pOther, Result_801076F0 *pResult);
void fn_80108A94(Object_80039F5C *p, Points_800F3A6C *pInfo);
void fn_80108DF8(Object_80039F5C *p, Points_800F3A6C *pInfo, int a);
unsigned int fn_8011E188(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_80178308(void);
int fn_801783AC(int bit);
extern float lbl_803EAEF8;
Point_8017886C fn_80177FFC(int team);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803EAF08;
extern float lbl_803EAF0C;
}

extern "C" int fn_80109248(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Points_800F3A6C info;
    int result = 0;

    fn_80107680(&info, pBlock->mUnknown64);
    if (fn_8013BA58(info.mpUnknown0, 0) != 4) {
        Message_800F01CC message;

        pBlock->mUnknown65 = 0;
        fn_801C1F94(&message, 0, 4);
        message.mId = 2;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (fn_800B65A0(fn_80178308()) != 0xFF && (float)fn_8011E188() < lbl_803EAEF8) {
        pBlock->mUnknown58 = 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if ((info.mUnknown16.mX > fn_80178A08() + 3.0f && p->mMotion.mPos.mX > fn_80178A08() - 2.0f) ||
            (info.mUnknown16.mX < -fn_80178A08() - 3.0f && p->mMotion.mPos.mX < 2.0f - fn_80178A08())) {
            return 1;
        }
        int active = 0;

        if (--pBlock->mUnknown58 < 0) {
            float scale = 1.0f;
            Point_8017886C a;
            Point_8017886C b;
            Result_801076F0 res;
            Object_80039F5C *pOther;
            int rush;
            int delay;
            int rating;

            a.mX = a.mY = 0.0f;
            b.mX = b.mY = 0.0f;
            delay = fn_800AC324(p->mIdBytes[2]);
            rating = 0xFF - p->mRatings[8];
            if (rating < 0) {
                rating = 0;
            }
            rush = 0;
            pBlock->mUnknown58 = fn_802372EC(0, (rating >> 5) + delay);
            pBlock->mUnknown52 = 0;
            pBlock->mUnknown53 = 0;
            pBlock->mUnknown54 = 0;
            pBlock->mUnknown55 = 0;
            pBlock->mUnknown61 = 0;
            pBlock->mUnknown63 = 0;
            pBlock->mUnknown48 = 0;
            pBlock->mUnknown60 = 1;
            if (fn_801783AC(11) || fn_801783AC(12)) {
                rush = 1;
            }
            pOther = fn_80137B88(info.mpUnknown0);
            fn_80106A60(p);
            if (pOther != 0) {
                fn_801076F0(p, pOther, &res, &info);
                fn_801077D8(p, pOther, pBlock, &res, &info);
            }
            fn_80106C24(p, pBlock);
            switch (pBlock->mUnknown49) {
            case 0:
                active = 1;
                fn_80108074(p, pOther, &a, &b, &info);
                pBlock->mUnknown60 = 1;
                break;
            case 1:
                active = 1;
                fn_801079BC(p, pOther, &a, &b, &info);
                if (!rush) {
                    active = 0;
                }
                pBlock->mUnknown60 = 1;
                break;
            case 2:
                fn_80107A9C(p, pOther, &a, &b, &res, &info, &scale);
                pBlock->mUnknown60 = 1;
                active = 1;
                break;
            case 3:
                active = 1;
                fn_80107D48(p, pOther, &a, &b, &res, &info, &scale);
                pBlock->mUnknown60 = 1;
                break;
            }
            b.mX = CLAMP(b.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            b.mY = CLAMP(b.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            fn_8010810C(p, pOther, &a, &b, &info, &res, scale);
            fn_80108954(p, pOther, &res);
            if (pBlock->mUnknown54 == 1 && pBlock->mUnknown49 != 0 && !rush) {
                active = 0;
            }
            pBlock->mUnknown66 = active;
        }
        fn_80108A94(p, &info);
    } else {
        pBlock->mUnknown66 = 0;
    }
    if (pBlock->mUnknown66 == 1) {
        fn_80108DF8(p, &info, 0);
    }
    return result;
}

extern "C" void fn_801096D4(Object_80039F5C *p) {
    int turn = 0;
    float x = p->mMotion.mPos.mX;
    float y = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing & 0xFFFFFF;

    if (x > fn_80178A08() - lbl_803EAF0C) {
        if (fn_801CFFD0(facing, 0) <= 0x555554) {
            if (facing <= 0x7FFFFF) {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (x < lbl_803EAF0C - fn_80178A08()) {
        if (fn_801CFFD0(facing, 0x800000) <= 0x555554) {
            if (facing <= 0x7FFFFF) {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (y > fn_80178A44() - lbl_803EAF0C) {
        if (fn_801CFFD0(facing, 0x400000) <= 0x555554) {
            if (fn_801CFFD0(facing, 0) <= 0x3FFFFF) {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (y < lbl_803EAF0C - fn_80178A44()) {
        if (fn_801CFFD0(facing, 0xC00000) <= 0x555554) {
            if (fn_801CFFD0(facing, 0) <= 0x3FFFFF) {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            }
        }
    }
    if (turn != 0 && p->mUnknown512.mUnknown0 > 0.0f) {
        Block_801096D4 *pBlock = (Block_801096D4 *)&p->mUnknown336;

        if (pBlock->mUnknown52Mode == 3) {
            int angle = facing + turn;

            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = angle;
        } else {
            Point_8017886C target;
            Point_8017886C delta;
            int angle;

            target = fn_80177FFC(p->mIdBytes[2]);
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            angle = delta.Heading();
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = angle;
            pBlock->mUnknown52Mode = 0;
            pBlock->mUnknown52State = 5;
            pBlock->mUnknown56 = target;
        }
    }
}
