#include "game/fn_801248D4.h"
#include "game/State_800FDA58.h"
#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/Team_80167A8C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"

/* The word at +0 is also read back by its low byte. */
struct State_80111104 {
    union {
        int mUnknown0;
        unsigned char mUnknown0Bytes[4];
    };
    unsigned short mUnknown4;
    unsigned short mUnknown6;
};

/* View of the payload that fn_801BE60C returns, as fn_8011067C accesses it.
   Partial layout. */
struct Block_8011067C {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

struct State_80111794 {
    union {
        int mUnknown0;
        unsigned char mUnknown0Bytes[4];
    };
    int mUnknown4;
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
    float mUnknown28;
    float mUnknown32;
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

/* The 12 bytes at player +336 as the timer that fn_8010FD94 clears and
   fn_80113498 advances. */
struct Timer_8010FD94 {
    unsigned int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

/* The bytes at player +336 as fn_801108D4 sets them up. */
struct State_801108D4 {
    float mUnknown0;
    int mUnknown4;
    short mUnknown8;
    char mUnknown10[2];
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
};

/* The bytes at player +336 as fn_8010F43C sets them up. */
struct State_8010F43C {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
};

/* A 124-byte entry of the array at player +800, as fn_8010FE40 reads it. */
struct Entry_8010FE40 {
    char mUnknown0[72];
    float mUnknown72;
    Block_801BD6D4 mUnknown76;
    char mUnknown88[36];
};

/* View of player +336 while fn_801113DC's state runs. */
struct State_801113DC {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    unsigned char mUnknown12;
    char mUnknown13[3];
    Object_80039F5C *mpUnknown16;
    char mUnknown20[1];
};

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
int fn_8009FB60(Object_80039F5C *p);
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
int fn_800BA6F8(void);
int fn_800BAA24(void);
int fn_800C4B6C(Object_80039F5C *p);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
float fn_800CA9B4(int kind, Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D4FBC(Object_80039F5C *p, int flag);
void fn_800D5704(Object_80039F5C *p);
void fn_800D6D08(Object_80039F5C *p);
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
int fn_800E815C(Object_80039F5C *p, int a, int b);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_8010D8F4(Object_80039F5C *p);
void fn_8010E59C(Object_80039F5C *p, Object_80039F5C *pOther, State_8010F43C *pState);
void fn_8010EF40(Object_80039F5C *p);
void fn_8010F058(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8010F1F4(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801105B0(Object_80039F5C *p);
unsigned short fn_8011067C(Table_8010B738 *pTable, Object_80039F5C *p, Block_8011067C *pBlock, int angle);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8011F1CC(void);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80156C78(int a, int b);
Object_800670B4 *fn_80168708(int team);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int bit);
Object_80039F5C *fn_8017876C(void);
int fn_801787A0(void);
float fn_80178A08(void);
int fn_80178C9C(void);
int fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d, unsigned short e, void *p, float f);
int fn_801BA568(void *pA, void *pB, int id);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
int fn_801BA6B0(Entry_800EAC9C *pEntry);
void fn_801BA6BC(Entry_800EAC9C *pEntry, int flag);
float fn_801BD690(Block_801BD6D4 *p, int key);
void fn_801BD81C(void *p, float value);
int fn_801CFE40(float y, float x);
float fn_801CFFA0(float value);
int fn_801CFFD0(int a, int b);
void fn_8022732C(void *pPoint, void *pVelocity, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_8022785C(Vector_80039F5C *pA, Vector_80039F5C *pB);
extern float lbl_803EA2C4;
extern unsigned char lbl_803EAF50;
extern unsigned char lbl_803EAF51;
extern float lbl_803ECB08;
unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable);
int fn_80113498(Object_80039F5C *p);
}

extern "C" int fn_8010F43C(Object_80039F5C *p)
{
    State_8010F43C *pState = (State_8010F43C *)&p->mUnknown336;
    int time = p->mpState->mUnknown1;
    float fraction = (time & 0x1F) / 31.0f;

    pState->mUnknown16 = (time >> 5) * 60 + (int)(fraction * 60.0f);
    if (pState->mUnknown16 == 0) {
        pState->mUnknown20 = 0;
    } else {
        pState->mUnknown20 = 1;
    }
    pState->mUnknown21 = 0;
    fn_8010A2DC(p, 0, 0);
    if (!(p->mFlags & 0x4000)) {
        if (!fn_80178C9C() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
            pState->mUnknown12 = fn_802372EC(0, 45) + 45;
        } else {
            pState->mUnknown12 = 0;
        }
        pState->mUnknown8 = p->mMotion.mFacing;
        pState->mUnknown0 = 0.4f;
        pState->mUnknown4 = p->mMotion.mFacing;
        pState->mUnknown21 = 0;
        pState->mUnknown22 = 0;
        if (fn_801787A0()) {
            pState->mUnknown12 = 99999;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pState->mUnknown4;
        p->mUnknown512.mUnknown8 = pState->mUnknown8;
        p->mUnknown512.mUnknown0 = pState->mUnknown0;
    } else {
        pState->mUnknown0 = p->mUnknown528.mUnknown0;
        pState->mUnknown4 = p->mMotion.mFacing;
        pState->mUnknown8 = p->mMotion.mFacing;
        pState->mUnknown21 = 0;
        pState->mUnknown22 = p->mUnknown528.mUnknown15;
        pState->mUnknown12 = 0;
        p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
    }
    if (p->mUnknown1052 != 2 ||
        (p->mUnknown1032 != 4 && p->mUnknown1032 != 7 && p->mUnknown1032 != 2 && p->mUnknown1032 != 3)) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
    }
    return 0;
}

extern "C" int fn_8010F654(Object_80039F5C *p)
{
    int result = 0;
    Object_80137ABC *pBall = fn_801374BC();
    State_8010F43C *pState = (State_8010F43C *)&p->mUnknown336;
    Block_8011E240 *pBlock = &p->mBlock1032;
    Object_80039F5C *pCarrier = fn_80137B40();
    Object_80039F5C *pOther;
    Message_800F01CC message;
    Vector_80039F5C ballPos;
    float minutes;

    if (p == fn_80137B40()) {
        fn_8011E3EC(p, 0);
        result = 1;
        fn_8011E240(p);
        fn_801C1F94(&message, 0, 4);
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
    } else if (fn_8010D8F4(p)) {
        fn_801C1F94(&message, 0, 4);
        message.mId = 90;
        message.mUnknown1[0] = pCarrier->mMotion.mPos.mX > 0.0f ? lbl_803EAF50 : -lbl_803EAF50;
        message.mUnknown1[1] = lbl_803EAF51;
        result = 1;
        fn_800F053C(0, p->mpState, &message, p);
    } else if (fn_8009FB60(p)) {
        result = 1;
    } else {
        if (fn_8013BA58(pBall, 0) == 5 && fn_800AD9B4() == 3) {
            fn_80137D58(fn_801374BC(), &ballPos);
            if (fn_8022785C(&ballPos, &p->mMotion.mPos) < 3.0f) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 57;
                message.mUnknown1[0] = fn_801374D4();
                fn_800F053C(0, p->mpState, &message, p);
                return result;
            }
        }
        if (!fn_801783AC(13) && !fn_801783AC(0) && fn_8011F1CC() && !fn_801787A0() &&
            (pState->mUnknown20 == 0 || pState->mUnknown16 <= 0)) {
            fn_8011E3EC(p, 0);
            result = 0;
            fn_8011E240(p);
            fn_801C1F94(&message, 0, 4);
            message.mId = 31;
            fn_800F053C(0, p->mpState, &message, p);
        } else {
            fn_8010A2DC(p, 0, -1);
            if (fn_801787A0()) {
                if ((pBlock->mUnknown0 != 4 && pBlock->mUnknown0 != 7) || fn_802372EC(0, 100) <= 9) {
                    fn_8011E3EC(p, 0);
                    fn_8011E240(p);
                    pState->mUnknown21 = 1;
                }
            } else if (pBlock->mUnknown0 == 0) {
                fn_8011E240(p);
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 2);
            }
            if (!(p->mFlags & 0x4000)) {
                if (p->mIdBytes[2] == fn_80178320()) {
                    if (fn_801783AC(0)) {
                        fn_8011E3EC(p, 0);
                        result = 1;
                        fn_8011E240(p);
                        fn_801C1F94(&message, 0, 4);
                        message.mId = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                    } else {
                        pState->mUnknown4 = 0x400000;
                        pState->mUnknown8 = 0x400000;
                    }
                } else {
                    pOther = fn_8009BCE8(&pBlock->mUnknown4);
                    if (pBlock->mUnknown0 != 4 && pBlock->mUnknown0 != 7) {
                        fn_8010E59C(p, pOther, pState);
                        fn_8010F058(p, pOther);
                        fn_8010F1F4(p, pOther);
                    } else {
                        pState->mUnknown12 = 0;
                    }
                }
                if (pState->mUnknown21) {
                    p->mUnknown512.mUnknown14 = 10;
                    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.5f;
                } else {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown4 = pState->mUnknown4 & 0xFFFFFF;
                    p->mUnknown512.mUnknown8 = pState->mUnknown8;
                    p->mUnknown512.mUnknown0 = pState->mUnknown0;
                    p->mUnknown512.mUnknown15 = pState->mUnknown22;
                }
                if (pState->mUnknown20) {
                    pState->mUnknown16--;
                    minutes = pState->mUnknown16 / 60.0f;
                    p->mpState->mUnknown1 = (int)(minutes * 32.0f);
                    if (pState->mUnknown16 > 0 && p->mpState->mUnknown1 == 0) {
                        p->mpState->mUnknown1 = 1;
                    }
                    if (pState->mUnknown16 <= 0) {
                        fn_8011E3EC(p, 0);
                        result = 1;
                        fn_8011E240(p);
                    }
                }
                fn_8010EF40(p);
            }
        }
    }
    return result;
}

extern "C" int fn_8010FC40(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    int restart = 1;
    unsigned char key;
    Object_80039F5C *pOther;

    if ((p->mFlags & 0x4000) && mode != 4) {
        return 1;
    }
    key = p->mpState->mUnknown1;
    if (p->mpState->mUnknown2 == 0 && key == fn_801BE648(p->mpUnknown792)) {
        restart = 0;
    }
    if (restart == 1) {
        p->mFlags &= ~4;
        p->mUnknown9[0] = 1;
        p->mUnknown512.mUnknown14 = 0;
        fn_8009BD60(p);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
        if (!(p->mpState->mUnknown3[0] & 0x80)) {
            p->mFlags |= 1 << (p->mpState->mUnknown3[0] & 0x7F);
        }
    } else {
        p->mFlags |= 1 << (p->mpState->mUnknown3[0] & ~0x80);
    }
    if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 7) {
        pOther = fn_8016444C(fn_80168708(fn_80178308()));
        fn_80143E14(p, pOther);
        fn_80143E14(pOther, p);
    }
    return 0;
}

extern "C" int fn_8010FD94(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;
    Object_80039F5C *pOther;

    if ((p->mFlags & 0x4000) && mode != 4) {
        return 1;
    }
    pTimer->mUnknown0 = 0;
    pTimer->mUnknown4 = 0.0f;
    pTimer->mUnknown8 = 0;
    if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 7) {
        pOther = fn_8016444C(fn_80168708(fn_80178308()));
        fn_80143E14(p, pOther);
        fn_80143E14(pOther, p);
    }
    return 0;
}

extern "C" int fn_8010FE40(Object_80039F5C *p)
{
    unsigned short key;
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;
    int target;
    Entry_8010FE40 *pEntries;
    int index;

    if ((p->mFlags & 0x4000) && pTimer->mUnknown8 != 0) {
        return 1;
    }
    if (pTimer->mUnknown8 != 0) {
        pTimer->mUnknown4 -= 1.0f;
        if (pTimer->mUnknown4 <= 0.0f) {
            return 1;
        }
        p->mMotion.mFacing += pTimer->mUnknown0;
        p->mpUnknown796->mUnknown8 += pTimer->mUnknown0;
    } else {
        pTimer->mUnknown8 = 1;
        p->mUnknown512.mUnknown14 = 0;
        p->mUnknown9[0] = 1;
        p->mFlags &= ~4;
        if (fn_80137C48(p) == 0) {
            fn_8009BD60(p);
            key = p->mpState->mUnknown1;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
            target = p->mpState->mUnknown2 << 16;
            if (fn_801CFFD0(target, p->mMotion.mFacing) > 0xB60B && fn_801BA568(p->mpUnknown796, p->mpUnknown800, key)) {
                pEntries = (Entry_8010FE40 *)p->mpUnknown800;
                index = fn_801BA5A8(p->mpUnknown796, pEntries, key, 0);
                pTimer->mUnknown4 = pEntries[index].mUnknown72;
                if (pTimer->mUnknown4 == 0.0f) {
                    pTimer->mUnknown4 = fn_801BD690(&pEntries[index].mUnknown76, 0xC004);
                }
                if (pTimer->mUnknown4 != 0.0f) {
                    pTimer->mUnknown4 = pTimer->mUnknown4 > 75.0f ? 75.0f : pTimer->mUnknown4;
                    pTimer->mUnknown0 = (int)(fn_801CFFD0(target, p->mMotion.mFacing) / pTimer->mUnknown4);
                    if (((p->mMotion.mFacing - target) & 0xFFFFFF) <= 0x7FFFFF) {
                        pTimer->mUnknown0 = -pTimer->mUnknown0;
                    }
                }
            }
        }
    }
    return 0;
}

extern "C" void fn_801100E8(Object_80039F5C *p)
{
    unsigned char side;

    fn_800A8954(1, p->mIdBytes[2], p);
    fn_8009BD60(p);
    switch (p->mpState->mUnknown2) {
    case 1:
    default:
        side = 6;
        break;
    case 2:
        side = 3;
        break;
    }
    if (p->mUnknown776 == 1) {
        if (side == 6) {
            side = 3;
        } else {
            side = 6;
        }
    }
    p->mUnknown1008.mUnknown0 = 4;
    p->mUnknown1008.mUnknown1 = side;
    if (fn_800D0B90(p)) {
        p->mUnknown1008.mUnknown2 = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 188, p, 1.0f);
        fn_80156C78(8, 1);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 154, p, 1.0f);
    }
}

extern "C" int fn_801102A4(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    float range;
    Object_80039F5C *pOther = fn_801245DC(p, fn_80178320(), 0, fn_80178D18(fn_80178320()), 0x2E38E3, &range, 1);
    float margin = fn_80178A08() - fabsf(p->mMotion.mPos.mX);
    int result;

    if (pOther != 0 && margin > 3.0f) {
        Point_8017886C ahead;
        float distance;

        ahead.mX = pOther->mMotion.mPos.mX;
        ahead.mY = pOther->mMotion.mPos.mY;
        fn_8022732C(&ahead, &pOther->mMotion.mUnknown40, 15.0f / lbl_803EA2C4);
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        distance = fn_802270A4(&ahead);
        if (!(pOther->mFlags & 0x800)) {
            if (distance < pOther->mMotion.mUnknown28 * (45.0f / lbl_803EA2C4)) {
                Point_8017886C delta;
                int heading = fn_801CFE40(pOther->mMotion.mUnknown44, pOther->mMotion.mUnknown40);

                fn_80227690(&delta, &pMotion->mPos, &pOther->mMotion.mPos);
                if (((heading - fn_801CFE40(delta.mY, delta.mX)) & 0xFFFFFF) > 0x800000) {
                    result = 2;
                } else {
                    result = 1;
                }
            } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
                result = 1;
            } else {
                result = 2;
            }
        } else {
            fn_80227690(&ahead, &pOther->mMotion.mPos, &pMotion->mPos);
            if (((pMotion->mUnknown32 - fn_801CFE40(ahead.mY, ahead.mX)) & 0xFFFFFF) > 0x800000) {
                result = 2;
            } else {
                result = 1;
            }
        }
    } else if (margin < 3.0f) {
        if (pMotion->mPos.mX > 0.0f) {
            if (pMotion->mUnknown32 <= 0x7FFFFF) {
                result = 1;
            } else {
                result = 2;
            }
        } else if (pMotion->mUnknown32 <= 0x7FFFFF) {
            result = 2;
        } else {
            result = 1;
        }
    } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

extern "C" void fn_801104BC(Object_80039F5C *p, Block_8011067C *pBlock)
{
    pBlock->mUnknown8 = -1;
    pBlock->mUnknown12 = 1.0f;
    pBlock->mUnknown16 = 1.0f;
    pBlock->mUnknown24 = 0;
    pBlock->mUnknown28 = 0;
}

extern "C" void fn_801104E4(Object_80039F5C *p, Block_8011067C *pBlock)
{
    float scale = 0.4f;
    short rating;

    if (fn_800CA5CC(p, 1, 1)) {
        scale *= fn_800CA9B4(3, p);
        fn_800CA9B4(2, p);
    }
    pBlock->mUnknown16 = 1.0f;
    pBlock->mUnknown20 = 1.0f;
    if (p->mRatings[0] > 127) {
        rating = p->mRatings[0] - 127;
        pBlock->mUnknown16 = 1.0f + rating * (scale / 128.0f);
    }
}

extern "C" int fn_801108D4(Object_80039F5C *p)
{
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;
    unsigned char kind = p->mpState->mUnknown1;
    Input_800B6D34 input;
    short value;

    if (kind == 0) {
        fn_800B6D34(p, &input);
        pState->mUnknown12 = kind;
        pState->mUnknown4 = 8;
        pState->mUnknown0 = 0.0f;
        pState->mUnknown13 = input.mUnknown72[0] != 0.0f;
    } else {
        pState->mUnknown12 = 1;
        pState->mUnknown4 = -1;
    }
    pState->mUnknown14 = 0;
    pState->mUnknown8 = p->mRatings[2];
    value = pState->mUnknown8 + 15;
    p->mRatings[2] = value > 255 ? 255 : value;
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
    return 0;
}

extern "C" int fn_801109A4(Object_80039F5C *p)
{
    int result = 0;
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;

    switch (pState->mUnknown12) {
    case 0:
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
        break;
    case 1:
        fn_801100E8(p);
        p->mUnknown512.mUnknown14 = 0;
        fn_80067E3C(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
        pState->mUnknown12 = 3;
        break;
    case 2:
        if (p->mFlags & 0x40000000) {
            p->mFlags &= ~0x40000000;
            fn_800D5704(p);
        }
        if (p->mFlags & 4) {
            p->mRatings[2] = pState->mUnknown8;
            p->mUnknown512.mUnknown15 = 0;
            p->mUnknown512.mUnknown0 = 0.72f;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown14 = 1;
            p->mFlags &= ~4;
            result = 1;
        } else if (p->mFlags & 1) {
            p->mFlags &= ~1;
            pState->mUnknown14 = 1;
            fn_800A5A8C(5, p, p);
        }
        break;
    case 3:
        if (fn_800C4B6C(p)) {
            result = 1;
        } else {
            pState->mUnknown12 = 2;
        }
        break;
    }
    return result;
}

extern "C" int fn_80110B00(Object_80039F5C *p)
{
    int done = 0;
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;
    Input_800B6D34 input;

    if (pState->mUnknown12 == 0) {
        pState->mUnknown4 = (short)(pState->mUnknown4 - 1);
        if (pState->mUnknown4 > 0) {
            fn_800B6D34(p, &input);
            if (input.mUnknown4 < 0.0f) {
                p->mpState->mUnknown2 = 1;
            } else if (input.mUnknown4 > 0.0f) {
                p->mpState->mUnknown2 = 2;
            } else if (input.mUnknown0 & 4) {
                p->mpState->mUnknown2 = 1;
            } else if (input.mUnknown0 & 8) {
                p->mpState->mUnknown2 = 2;
            }
            if (pState->mUnknown13) {
                if (input.mUnknown72[0] == 1.0f || input.mUnknown72[0] < pState->mUnknown0) {
                    done = 1;
                } else {
                    pState->mUnknown0 = input.mUnknown72[0];
                }
            } else if (!(input.mUnknown93 & 2)) {
                done = 1;
            }
        } else {
            done = 1;
        }
        if (done == 1) {
            p->mpState->mUnknown1 = 2;
            pState->mUnknown12 = done;
        }
    }
    return 0;
}

extern "C" int fn_80110C70(Table_8010B738 *pTable, unsigned short key, void *pA, Entry_800EAC9C *pEntries,
                           Object_80039F5C *p, int mode)
{
    Block_8011067C *pBlock = (Block_8011067C *)fn_801BE60C(p->mpUnknown792, key);
    int angle;
    unsigned char side;
    unsigned int index;
    Entry_800EAC9C *pEntry;
    Record_8010B738 *pRecord;

    switch (mode) {
    case 0:
        fn_801BE760(p->mpUnknown792, key, 1);
        angle = fn_801105B0(p);
        side = p->mUnknown1008.mUnknown1;
        fn_801104BC(p, pBlock);
        fn_801104E4(p, pBlock);
        index = fn_8011067C(pTable, p, pBlock, angle);
        pBlock->mUnknown8 = fn_801BA2A8(pA, pEntries, pTable->mEntries[index].mUnknown0,
                                        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        if (p->mUnknown776 == 1) {
            pEntry = &pEntries[pBlock->mUnknown8];
            fn_801BA6BC(pEntry, fn_801BA6B0(pEntry) == 0);
            if (side == 6) {
                side = 3;
            } else {
                side = 6;
            }
        }
        if (side == 6) {
            pBlock->mUnknown32 = (p->mMotion.mFacing - angle) & 0xFFFFFF;
        } else {
            pBlock->mUnknown32 = (p->mMotion.mFacing + angle) & 0xFFFFFF;
        }
        fn_801BD81C(&pEntries[pBlock->mUnknown8].mUnknown4C, fn_801CFFA0(pBlock->mUnknown16));
        pEntries[pBlock->mUnknown8].mUnknown44 = pBlock->mUnknown20;
        pBlock->mUnknown28 = (int)(pBlock->mUnknown24 / pBlock->mUnknown12);
        pRecord = pTable->mEntries[index].mpRecord;
        pBlock->mUnknown0 = pRecord->mUnknown28;
        pBlock->mUnknown4 = pRecord->mUnknown32;
        p->mFlags &= ~4;
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown28) & 0xFFFFFF;
            pEntries[pBlock->mUnknown8].mUnknownC = (pEntries[pBlock->mUnknown8].mUnknownC + pBlock->mUnknown28) & 0xFFFFFF;
            if (p->mFlags & 4) {
                pBlock->mUnknown28 = 0;
            }
        }
        break;
    }
    return 0;
}

extern "C" int fn_801111E8(Object_80039F5C *p)
{
    State_80111104 *pState = (State_80111104 *)&p->mUnknown336;

    pState->mUnknown6 = (signed char)(pState->mUnknown6 - 1);
    if ((short)pState->mUnknown6 < 0) {
        p->mRatings[2] = pState->mUnknown4;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown15 = 0;
        fn_800D4FBC(p, 0);
        return 1;
    }
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
    } else if (p->mMotion.mUnknown28 / lbl_803ECB08 < 0.65f) {
        p->mUnknown512.mUnknown0 = 0.65f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
    }
    return 0;
}

extern "C" int fn_801112D8(Object_80039F5C *p)
{
    p->mRatings[2] = p->mUnknown340;
    p->mUnknown512.mUnknown0 = 0.72f;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

extern "C" int fn_801113DC(Object_80039F5C *p)
{
    State_801113DC *pState;
    State_80039F5C *pMessage;

    p->mUnknown9[0] = 1;
    fn_800D6D08(p);
    pState = (State_801113DC *)&p->mUnknown336;
    pState->mUnknown0 = 255;
    pState->mUnknown4 = 0.0f;
    pState->mUnknown12 = fn_80137C48(p) != 0;
    pState->mpUnknown16 = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    fn_800DB520(pState->mUnknown20, p, fn_8017876C(), pState->mUnknown4);
    fn_8009BD60(p);
    pMessage = p->mpState;
    if ((pMessage->mUnknown3[0] >> 4) > 1) {
        p->mUnknown1008.mUnknown0 = pMessage->mUnknown1;
        p->mUnknown1008.mUnknown1 = pMessage->mUnknown2;
        p->mUnknown1008.mUnknown2 = pMessage->mUnknown3[0] >> 4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 193, p, 1.0f);
    } else {
        p->mUnknown1008.mUnknown2 = pMessage->mUnknown1 & 15;
        p->mUnknown1011 = pMessage->mUnknown1 >> 4;
        p->mUnknown1008.mUnknown1 = pMessage->mUnknown3[0];
        p->mUnknown1008.mUnknown0 = pMessage->mUnknown2;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 44, p, 1.0f);
    }
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" int fn_801115C0(Object_80039F5C *p)
{
    int result = 0;
    float limit;
    float x;

    if (p->mpState->mId == 59) {
        limit = 0.5f;
    } else {
        limit = 0.4f;
    }
    x = fabsf(p->mMotion.mPos.mX);
    if (x > fn_80178A08()) {
        if (x - fn_80178A08() < limit) {
            result = 1;
        }
    } else if (fn_80178A08() - x < limit) {
        result = 1;
    }
    return result;
}

extern "C" int fn_8011165C(Object_80039F5C *p)
{
    float x = p->mMotion.mPos.mX;

    if (p->mUnknown776 == 1) {
        x = -x;
    }
    if (x > 0.0f) {
        return 13;
    }
    return 14;
}

extern "C" int fn_8011168C(Object_80039F5C *p)
{
    int result = 0;
    Object_800B26B0 *pMotion = &p->mMotion;
    int angle;
    Message_800F01CC message;

    if (pMotion->mUnknown28 > lbl_803ECB08 * 0.4f && pMotion->mUnknown44 > 0.0f && fn_801115C0(p)) {
        if (p->mMotion.mPos.mX > 0.0f) {
            angle = (pMotion->mUnknown32 - 0x400000) & 0xFFFFFF;
            result = angle > 0xF8E38F;
        } else {
            angle = (pMotion->mUnknown32 - 0x400000) & 0xFFFFFF;
            if (angle <= 0x71C70) {
                result = 1;
            }
        }
    }
    if (result) {
        fn_801C1F94(&message, 0, 4);
        message.mId = 59;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_801117F8(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;
    int angle;

    if (--pState->mUnknown4 < 0 || !fn_801115C0(p)) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown15 = 0;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        return 1;
    }
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    if (!(p->mFlags & 0x4000)) {
        angle = p->mMotion.mFacing;
        if (pState->mUnknown4 <= 34) {
            if (pState->mUnknown0 == 14) {
                angle -= (int)(p->mRatings[0] * 913.78827f);
            } else {
                angle += (int)(p->mRatings[0] * 913.78827f);
            }
        }
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle & 0xFFFFFF;
        p->mUnknown512.mUnknown14 = 1;
    }
    return 0;
}

extern "C" int fn_80111974(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;
    Input_800B6D34 input;
    int b;

    fn_800B6D34(p, &input);
    b = 0;
    if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10)) {
        b = 1;
    }
    if ((input.mUnknown92 & 1) && fn_800E815C(p, 0, b)) {
        return 0;
    }
    if (pState->mUnknown4 <= 34) {
        fn_800B6E68(p, &input);
    } else {
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
    }
    return 0;
}
