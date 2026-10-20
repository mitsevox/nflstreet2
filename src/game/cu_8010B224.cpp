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

/* View of the block at player +336 as the animation callbacks use it. */
struct Block_8010BC90 {
    unsigned char mUnknown0;
    signed char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    char mUnknown4[16];
    int mUnknown20;
    unsigned short mUnknown24;
};

/* Record that fn_8010B738 and fn_8011067C read through each table entry.
   Partial layout. */
struct Record_8010B738 {
    char mUnknown0[4];
    Key_80110630 mUnknown4;
    unsigned char mUnknown7;
    char mUnknown8[4];
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
};

struct Entry_8010B738 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Record_8010B738 *mpRecord;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_8010B738 {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_8010B738 mEntries[1];
};

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
int fn_801486A0(void);
void fn_80171DB0(Object_80039F5C *p);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801BA2A8(void *pData, void *pEntries, unsigned short value, int animation, int key, void *p, float weight);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern unsigned char lbl_802DABBC[];
}

extern "C" int fn_8010B224(Object_80039F5C *p) {
    int result = 1;

    if (fn_801486A0() == 0) {
        result = 0;
    }
    if (p->mFlags & 0x800) {
        result = 0;
    }
    if (p->mpState->mId == 10 || p->mpState->mId == 50) {
        result = 0;
    }
    switch (fn_801BE648(p->mpUnknown792)) {
    case 155:
    case 185:
    case 206:
        result = 0;
        break;
    }
    if (fn_80137B40() != p) {
        int facing = p->mMotion.mFacing;
        Point_8017886C ahead;

        ahead.mX = fn_801CFB94(facing) * 5.0f + p->mMotion.mPos.mX;
        ahead.mY = fn_801CFB18(facing) * 5.0f + p->mMotion.mPos.mY;
        if (fabsf(ahead.mX) > fn_80178A08() || fabsf(ahead.mY) > fn_80178A44()) {
            result = 0;
        }
        if (result) {
            unsigned char team;

            for (team = 0; team <= 1; team++) {
                float distance;

                fn_801245DC(p, team, 0, fn_80178D18(team), 0x400000, &distance, 0);
                if (distance < 2.0f) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther) {
    unsigned char result = 0;

    if (pOther != 0 && p != 0 && pOther != p) {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_802270A4(&delta) <= 5.0f) {
            result = fn_801CFFD0(angle, p->mMotion.mFacing) <= 0xE38E2;
        }
    }
    return result;
}

extern "C" int fn_8010BA90(Object_80039F5C *p) {
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;
    Message_800F01CC message;

    if (pBlock->mUnknown0) {
        p->mFlags &= ~4;
        fn_801C1F94(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 0;
        message.mUnknown1[1] = 0;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (pBlock->mUnknown1 > 0) {
        pBlock->mUnknown1--;
    } else {
        if (fn_801BE648(p->mpUnknown792) != 206) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 206, p, 1.0f);
            if (fn_802372EC(0, 10) <= 4) {
                switch (pBlock->mUnknown2) {
                case 1:
                case 2:
                    fn_800A3B58(p, 9, 0);
                    break;
                case 3:
                case 4:
                    fn_800A3B58(p, 6, 0);
                    break;
                }
            }
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            fn_801C1F94(&message, 0, 4);
            message.mId = 62;
            message.mUnknown1[0] = 0;
            message.mUnknown1[1] = 0;
            fn_800F053C(0, p->mpState, &message, p);
            if (pBlock->mUnknown3 != 255) {
                lbl_802DABBC[pBlock->mUnknown3] = 0;
            }
            return 1;
        }
        if (p->mFlags & 0x1000) {
            if (fn_80137B40() == p) {
                fn_80171DB0(p);
            }
            p->mFlags &= ~0x1000;
        }
    }
    return 0;
}

extern "C" int fn_8010BC90(Table_8010B738 *pTable, unsigned short key, void *pData, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int mode) {
    Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;

    switch (mode) {
    case 0: {
        unsigned char index = fn_8010B738(p, pTable);

        if (index != 255) {
            pBlock->mUnknown3 = index;
            pRecord->mUnknown0Word = fn_801BA2A8(pData, pEntries, pTable->mEntries[index].mUnknown0,
                                                 pTable->mEntries[index].mUnknown2, key, p, 1.0f);
            lbl_802DABBC[index] = 1;
        } else {
            pBlock->mUnknown0 = 1;
        }
        break;
    }
    case 1:
    case 3:
        break;
    }
    return 0;
}
