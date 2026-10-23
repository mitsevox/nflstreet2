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

/* View of the block at player +336 as fn_8010CB58 runs its states. */
struct Block_8010CB58 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
};

extern "C" {
void fn_800B8344(Object_80039F5C *p);
int fn_800FD580(Object_80039F5C *p);
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8009BD60(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float e, void *pRecord);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
}

extern "C" int fn_8010C8F8(Object_80039F5C *p) {
    int result = 0;
    float range = 1.0f;
    Object_80137ABC *pBall;
    Vector_80039F5C pos;
    Point_8017886C delta;

    fn_80137B40();
    pBall = fn_80137CD0(p);
    if (pBall == 0) {
        pBall = fn_801374BC();
        range = 1.5f;
    }
    fn_80137D58(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion.mPos);
    if (fn_802270A4(&delta) < range) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8010C98C(Object_80039F5C *p) {
    int pick = 1;
    Object_80137ABC *pBall;
    Vector_80039F5C pos;
    int index;

    pBall = fn_80137CD0(p);
    if (pBall == 0) {
        pBall = fn_801374BC();
    }
    fn_80137D58(pBall, &pos);
    fn_8009BD60(p);
    index = fn_800F06F4(0, p->mpState, 26, 0xFFFF);
    if (index != 0xFFFF) {
        switch (p->mpState[index].mUnknown2) {
        case 2:
        case 3:
            p->mUnknown1008.mUnknown0 = 1;
            pick = 0;
            break;
        case 4:
        case 5:
            p->mUnknown1008.mUnknown0 = 2;
            pick = 0;
            break;
        default:
            pick = 1;
            break;
        }
    }
    if (pick) {
        if (fn_8011F1A4()) {
            if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        } else {
            Point_8017886C delta;

            fn_80227690(&delta, &pos, &p->mMotion.mPos);
            if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 78, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" int fn_8010CB58(Object_80039F5C *p) {
    int result = 0;
    Block_8010CB58 *pBlock = (Block_8010CB58 *)&p->mUnknown336;
    int animation;

    fn_800B8344(p);
    animation = fn_801BE648(p->mpUnknown792);
    switch (pBlock->mUnknown20) {
    case 0:
        if ((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200) {
            p->mUnknown512.mUnknown14 = 0;
            pBlock->mUnknown20 = 1;
        } else {
            Object_80039F5C *pCarrier;

            result = fn_800FD580(p);
            pCarrier = fn_80137B40();
            if (pCarrier != 0 && pCarrier->mpState->mId == 18 && (p->mFlags & 0x4000)) {
                result = 1;
            }
            if (fn_8010C8F8(p)) {
                fn_8010C98C(p);
                pBlock->mUnknown20 = 1;
            }
        }
        break;
    case 1:
        if (fn_80137B40() == p && animation == 74) {
            pBlock->mUnknown20 = 2;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pBlock->mUnknown24 = 20;
            pBlock->mUnknown20 = 2;
        } else if (!((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200)) {
            if (animation == 78) {
                p->mUnknown512.mUnknown14 = 0;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        }
        break;
    case 2: {
        int has18 = fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF;
        int has26 = fn_800F06F4(0, p->mpState, 26, 0xFFFF) != 0xFFFF;
        int has25 = fn_800F06F4(0, p->mpState, 25, 0xFFFF) != 0xFFFF;

        if (p == fn_80137B40() && !has18 && !has26 && !has25) {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = 0.72f;
        } else if (!has18) {
            if (--pBlock->mUnknown24 < 0) {
                result = 1;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            result = 1;
        }
        break;
    }
    }
    return result;
}
