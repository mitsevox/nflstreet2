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
#include "game/cu_8008E978.h"

/* View of the block at player +336 that holds the animation entry index at
   +50. */
struct Block_80109CA0 {
    char mUnknown0[50];
    short mUnknown50;
};

/* View of the block at player +336 with the packed word at +52 (player
   +388); fn_8010A07C reads the 4-bit field at bit 25. */
struct Block_80109E48 {
    char mUnknown0[52];
    unsigned int mUnknown52 : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Rest : 21;
};

/* View of the block at player +336 that fn_80109F34 updates: the mode in
   the top 3 bits and the state in the next 4 bits of the word at +52, and
   the point at +56. */
struct Block_80109F34 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    char mUnknown3[17];
    float mUnknown20;
    char mUnknown24[4];
    float mUnknown28;
    char mUnknown32[20];
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Rest : 25;
    Point_8017886C mUnknown56;
};

/* The two players fn_80109990 writes. */
struct Pair_80109990 {
    Object_80039F5C *mpUnknown0;
    Object_80039F5C *mpUnknown4;
};

extern "C" {
int fn_800CB580(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int check);
int fn_800CBB00(Object_80039F5C *p, int index, Point_8017886C target, int angle, int beyond);
int fn_800FF094(Object_80039F5C *p);
void fn_800FF598(Block_80109F34 *pBlock, Object_80039F5C *p, Point_8017886C *pPoint, int angle, float value);
void fn_801096D4(Object_80039F5C *p);
int fn_8009274C(unsigned char index);
Object_80039F5C *fn_800963EC(Character_80093BCC *pCharacter);
Object_80039F5C *fn_800963F4(Character_80093BCC *pCharacter);
void fn_8009BD60(Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_80109990(Pair_80109990 *pOut);
int fn_80109A1C(Object_80039F5C *p, Point_8017886C *pOut);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
int fn_80178308(void);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
void fn_80227248(Point_8017886C *pOut, Point_8017886C *pIn, float scale);
extern float lbl_803EAF0C;
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803ECB08;
}

extern "C" int fn_80109968(Object_80039F5C *p, Point_8017886C *pOut) {
    return p->mMotion.mUnknown28 <= lbl_803ECB08 * 0.07f;
}

extern "C" void fn_80109990(Pair_80109990 *pOut) {
    Object_80039F5C *pFirst = 0;
    Object_80039F5C *pSecond = 0;
    int i;

    for (i = 0; i <= 3 && pFirst == 0 && pSecond == 0; i++) {
        if (fn_8009274C(i) != 0) {
            Character_80093BCC *pCharacter = fn_80093BCC(i);

            pFirst = fn_800963EC(pCharacter);
            pSecond = fn_800963F4(pCharacter);
            break;
        }
    }
    pOut->mpUnknown0 = pFirst;
    pOut->mpUnknown4 = pSecond;
}

extern "C" int fn_80109A1C(Object_80039F5C *p, Point_8017886C *pOut) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80137B40();
    float distance;

    if (pTarget != 0 && pTarget != p) {
        distance = fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos);
        result = distance < 1.25f;
    }
    if (!result) {
        Pair_80109990 pair;
        Object_80039F5C *pOther;

        fn_80109990(&pair);
        pTarget = pair.mpUnknown0;
        if (pTarget != 0 && pTarget != p) {
            distance = fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos);
            if (distance < 1.25f) {
                result = 1;
            }
        }
        pOther = pair.mpUnknown4;
        if (pOther != 0 && pOther != p) {
            distance = fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos);
            if (distance < 1.25f) {
                pTarget = pOther;
                result = 1;
            }
        }
        if (!result) {
            int team = p->mIdBytes[2];

            pTarget = fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
            if (pTarget != 0 && pTarget != p) {
                if (distance < 0.75f) {
                    result = 1;
                } else {
                    team = p->mIdBytes[2] ^ 1;
                    pTarget = fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
                    if (pTarget != 0 && pTarget != p && distance < 1.25f) {
                        result = 1;
                    }
                }
            }
        }
    }
    if (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - lbl_803EAF0C ||
        fabsf(p->mMotion.mPos.mY) > fn_80178A44() - lbl_803EAF0C) {
        result = 0;
    }
    if (result) {
        fn_80227690(pOut, &p->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_802270A4(pOut) != 0.0f) {
            fn_80227248(pOut, pOut, 6.0f / fn_802270A4(pOut));
            fn_80227638(pOut, pOut, &p->mMotion.mPos);
        } else {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_80109C7C(Object_80039F5C *p) {
    return p->mMotion.mUnknown28 > lbl_803ECB08 * 0.4f;
}

extern "C" void fn_80109CA0(Object_80039F5C *p, int animation, unsigned char a, unsigned char b, unsigned char c) {
    Block_80109CA0 *pBlock = (Block_80109CA0 *)&p->mUnknown336;

    if (animation != 203) {
        fn_8009BD60(p);
        p->mUnknown1008.mUnknown0 = a;
        p->mUnknown1008.mUnknown1 = b;
        p->mUnknown1008.mUnknown2 = c;
    }
    if (animation != fn_801BE648(p->mpUnknown792)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, p, 1.0f);
        pBlock->mUnknown50 = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, 0);
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags &= ~4;
    } else {
        pBlock->mUnknown50 = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, 0);
    }
}

extern "C" int fn_80109D70(Object_80039F5C *p, Point_8017886C *pOut) {
    int result = 6;

    if (fn_80137C48(p)) {
        result = 8;
    } else if (fn_80109C7C(p)) {
        result = 1;
    } else if (fn_80109A1C(p, pOut)) {
        result = 3;
    } else if (fn_80109968(p, pOut)) {
        result = 5;
    } else if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.07f) {
        result = 2;
    } else if (fn_802372EC(0, 5) <= 3) {
        result = 4;
    }
    return result;
}

extern "C" int fn_80109E48(Object_80039F5C *p, int kind, int *pOut) {
    Block_80109E48 *pBlock = (Block_80109E48 *)&p->mUnknown336;
    int result;
    Message_800F01CC message;

    *pOut = 0;
    result = 0;
    switch (kind) {
    case 8:
        fn_801C1F94(&message, 0, 4);
        message.mId = 49;
        fn_800F00D4(0, p->mpState, &message, p);
        if (p->mpState->mId == 49) {
            result = 1;
            *pOut = 2;
        }
        break;
    case 9:
        if (p->mMotion.mUnknown28 <= lbl_803ECB08 * 0.5f) {
            fn_80178308();
            pBlock->mUnknown52Count = 0;
        } else {
            pBlock->mUnknown52State = 1;
        }
        break;
    }
    return result;
}

extern "C" int fn_80109F34(Object_80039F5C *p) {
    Block_80109F34 *pBlock = (Block_80109F34 *)&p->mUnknown336;
    int result = 0;
    int state = pBlock->mUnknown52State;

    if (state == 3) {
        Point_8017886C delta;
        float rate;
        int angle;
        int index;

        fn_80227690(&delta, &pBlock->mUnknown56, &p->mMotion.mPos);
        fn_800FF598(pBlock, p, &pBlock->mUnknown56, delta.Heading() & 0xFFFFFF, -1.0f);
        pBlock->mUnknown28 = -1.0f;
        rate = p->mMotion.mUnknown28 / lbl_803ECB08;
        if (rate < 0.14f) {
            rate = 0.14f;
        }
        pBlock->mUnknown2 = state;
        pBlock->mUnknown20 = rate;
        pBlock->mUnknown52Mode = 2;
        result = 1;
        fn_800FF094(p);
        angle = p->mUnknown512.mUnknown4;
        if (fn_800CB580(p, &index, pBlock->mUnknown56, angle, 0) != 0) {
            fn_800CBB00(p, index, pBlock->mUnknown56, angle, 0);
            pBlock->mUnknown52Mode = 6;
        }
        fn_801096D4(p);
    }
    return result;
}
