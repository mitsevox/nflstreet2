#include "game/Object_80039F5C.h"
#include "game/Object_801BBD5C.h"
#include "game/Block_801BE60C.h"
#include "game/InGame.h"
#include "game/Message_800F01CC.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801EBC18.h"
#include "game/fn_80094488.h"
#include <math.h>

struct Record_800DC584 {
    int mUnknown0;
};

/* Views of the fn_801BE60C record, whose layout depends on the key. */
struct Record_800DD5E4 {
    char mUnknown0[6];
    unsigned char mUnknown6;
};

struct Record_800DD648 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Record_800DD780 {
    unsigned int mUnknown0;
    char mUnknown4[12];
    unsigned char mUnknown16;
};

struct Record_800DDCE4 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    short mUnknown14;
};

struct Record_800E1778 {
    unsigned char mUnknown0;
};

/* Views of the player block at +336, whose layout depends on the state. */
struct Block_800E0188 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_800E0230 {
    float mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

struct Block_800E0E8C {
    char mUnknown0[2];
    unsigned short mUnknown2;
};

struct Block_800E0EF0 {
    unsigned char mUnknown0;
    char mUnknown1[6];
    unsigned char mUnknown7;
    char mUnknown8[8];
    unsigned char mUnknown16;
    char mUnknown17[11];
    unsigned char mUnknown28;
};

/* View of the bytes from +12 of the player block at +1160. */
struct Block_800DF654 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[8];
    float mUnknown20;
    float mUnknown24;
    int mUnknown28;
};

struct Block_800E1438 {
    char mUnknown0[6];
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

struct Block_800E1778 {
    char mUnknown0[24];
    unsigned char mUnknown24;
    char mUnknown25[5];
    unsigned short mUnknown30;
};

struct Block_800E13E4 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

struct Block_800E11C0 {
    char mUnknown0[16];
    Vector_80039F5C mUnknown16;
    char mUnknown28[4];
    Vector_80039F5C mUnknown32;
};

/* Object that the player's word +3092 points to. */
struct Object_800E11C0 {
    char mUnknown0[32];
    Block_800E11C0 *mpUnknown32;
};

extern "C" {
void fn_800DD994(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                 Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask);
int fn_800DA7AC(Object_801BBD5C *pObject, float value);
float fn_800DAA68(int index, void *pA, Object_801BBD5C *pObject, int b, float value);
void fn_8009A260(Object_80039F5C *p);
int fn_8009B9A8(int a);
float fn_8009BB54(int a);
void fn_8009BD60(Object_80039F5C *p);
void fn_8009BFD0(Object_80039F5C *p, Vector_80039F5C *pPos, float *pRot);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_8009D1F4(Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AE7F0(int event, int team, Object_80039F5C *p);
void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock);
int fn_800E8898(Object_80039F5C *p, int *pValue);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned int fn_8011E188(void);
int fn_80120794(Object_800B26B0 *pA, Object_800B26B0 *pB, float *pC, float e, float f, int d, float g);
int fn_801486A0(void);
Object_800670B4 *fn_80168708(int team);
void fn_80171DB0(Object_80039F5C *p);
int fn_80178308(void);
int fn_801CFE08(float value);
int fn_801CFFD0(int a, int b);
void fn_802271A4(Vector_80039F5C *pOut, Vector_80039F5C *p);
void fn_80227248(void *pOut, void *p, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227B04(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
}

extern float lbl_803ECB08;

extern "C" int fn_800DC584(Object_80039F5C *p, Record_800DC584 *pRecord)
{
    Object_8016D8B0 *pBlock = &p->mUnknown512;
    int delta = fn_801CFFD0(pBlock->mUnknown4, pBlock->mUnknown8);
    int angle;
    int result;
    if (((pBlock->mUnknown4 - pBlock->mUnknown8) & 0xFFFFFF) > 0x800000) {
        angle = pBlock->mUnknown8 + (0x400000 - delta);
        result = 1;
    } else {
        angle = pBlock->mUnknown8 - (0x400000 - delta);
        result = 2;
    }
    pBlock->mUnknown8 &= 0xFFFFFF;
    p->mpUnknown800[pRecord->mUnknown0].mUnknown12 = angle;
    return result;
}

extern "C" float fn_800DC61C(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    float value = p->mMotion.mUnknown28;
    if (fn_801CFFD0((p->mMotion.mUnknown32 - p->mMotion.mFacing) & 0xFFFFFF, pObject->mUnknown20) > 0x400000) {
        value = -value;
    }
    return value;
}

extern "C" int fn_800DC674(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    return fn_800DA7AC(pObject, fn_800DC61C(pObject, p));
}

extern "C" float fn_800DC6A8(Object_801BBD5C *pObject, Object_80039F5C *p, int index, void *pA, int b)
{
    return fn_800DAA68(index, pA, pObject, b, fn_800DC61C(pObject, p));
}

extern "C" int fn_800DD5E4(Object_80039F5C *p)
{
    int result = 0;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        result = ((Record_800DD5E4 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown6 == 1;
    }
    return result;
}

extern "C" int fn_800DD648(Object_80039F5C *p)
{
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        return ((Record_800DD648 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown4;
    }
    return 0;
}

extern "C" int fn_800DD780(Object_80039F5C *p, int value, unsigned short key)
{
    int result = 1;
    if (fn_8002894C()) {
        unsigned char i;
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
            if (pOther != p) {
                Record_800DD780 *pRecord = (Record_800DD780 *)fn_801BE60C(pOther->mpUnknown792, key);
                if (pRecord && pRecord->mUnknown16 == value && pRecord->mUnknown0 <= 59) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800DD830(void *p) {
    return 1;
}

extern "C" int fn_800DD838(Object_80039F5C *p)
{
    int result = p->mUnknown1008Word;
    if (result == -1) {
        result = 2;
        switch (fn_800AD9B4()) {
        case 5:
            result = 30;
            if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 0 && p->mIdBytes[1] == 0) {
                result = 94;
            } else {
                result |= 32;
            }
            if (fn_80137C48(p)) {
                result &= ~8;
            }
            break;
        case 1:
        case 10:
            result |= 12;
            break;
        case 2:
            result = 2;
            break;
        case 4:
        case 9:
            result |= 28;
            if (p->mUnknown2914 == 19 || p->mUnknown2914 == 20 || fn_80137C48(p)) {
                result &= ~8;
            }
            break;
        }
    }
    return result;
}

extern "C" void fn_800DD92C(Table_80089904 *pTable, unsigned short a, unsigned char value)
{
    unsigned char values[4];
    values[0] = value;
    values[1] = 255;
    values[2] = 255;
    values[3] = 255;
    fn_801BBC3C(a, pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF, pTable);
}

extern "C" void fn_800DDCE4(Object_80039F5C *p, Record_800DDCE4 *pRecord)
{
    if (p->mIdBytes[3] == 1) {
        if (pRecord->mUnknown9) {
            fn_8009D1F4(p);
        } else {
            fn_8009D1AC(p);
        }
    }
}

extern "C" int fn_800DDD24(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode)
{
    Record_800DDCE4 *pRecord = (Record_800DDCE4 *)fn_801BE60C(p->mpUnknown792, key);
    int mask;
    pRecord->mUnknown13 = 0;
    mask = pRecord->mUnknown4;
    switch (mode) {
    case 0:
        pRecord->mUnknown0 = 0;
        pRecord->mUnknown14 = -1;
        pRecord->mUnknown8 = 0;
        pRecord->mUnknown10 = 0;
        pRecord->mUnknown12 = 1;
        mask = pRecord->mUnknown4 = fn_800DD838(p);
        fn_801BE760(p->mpUnknown792, key, 1);
        pRecord->mUnknown13 = 1;
        break;
    case 1:
        break;
    case 2:
        pRecord->mUnknown0++;
        if (key == fn_801BE648(p->mpUnknown792) && (p->mFlags & 4)) {
            pRecord->mUnknown13 = 1;
        }
        fn_800DDCE4(p, pRecord);
        break;
    case 3:
        if (p->mIdBytes[3] == 1) {
            fn_8009D1AC(p);
        }
        break;
    }
    if (pRecord->mUnknown13) {
        fn_800DD994(pTable, p, key, pA, pB, p, pRecord, mask);
    }
    return 0;
}

extern "C" void fn_800DDE6C(Object_80039F5C *p)
{
    fn_8009BD60(p);
    if (p->mIdBytes[3] != 1 && fn_80137C48(p)) {
        p->mUnknown1008.mUnknown0 = 1;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    if (p->mIdBytes[3] == 1) {
        if (p->mUnknown512.mUnknown14 == 7) {
            p->mUnknown1008.mUnknown1 = 3;
        } else {
            p->mUnknown1008.mUnknown1 = 2;
        }
    }
}

extern "C" int fn_800DDEE4(unsigned char *pA, unsigned char *pB)
{
    unsigned char i;
    int result = 1;
    for (i = 0; i < 2; i++) {
        if (pB[i] != 255 && pA[i] != pB[i]) {
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int fn_800DE364(unsigned int id)
{
    int result = 1;
    switch (id) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
    case 173:
        result = 0;
    }
    return result;
}

extern "C" void fn_800DF134(Object_80039F5C *p, Pair_802270A4 *pOffset, int angle, int key)
{
    Pair_802270A4 offset = *pOffset;
    if (key == fn_801BE648(p->mpUnknown792)) {
        Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
        if (pRecord) {
            if (pRecord->mUnknown1C) {
                pRecord->mUnknown4 += offset.mUnknown0;
                pRecord->mUnknown14 = (pRecord->mUnknown14 + angle) & 0xFFFFFF;
                pRecord->mUnknown8 += offset.mUnknown4;
            }
            p->mpUnknown800[pRecord->mUnknown1D].mUnknown12 =
                (p->mpUnknown800[pRecord->mUnknown1D].mUnknown12 + angle) & 0xFFFFFF;
        }
    }
}

extern "C" void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord)
{
    Block_800DF654 *pBlock = (Block_800DF654 *)p->mUnknown1160.mUnknown12;
    pRecord->mUnknown4 = -pRecord->mUnknown4;
    pRecord->mUnknown8 = -pRecord->mUnknown8;
    pRecord->mUnknownC = -pRecord->mUnknownC;
    pRecord->mUnknown10 = -pRecord->mUnknown10;
    pRecord->mUnknown14 = (pRecord->mUnknown14 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown0 = (pBlock->mUnknown0 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown4 = -pBlock->mUnknown4;
    pBlock->mUnknown8 = -pBlock->mUnknown8;
    pBlock->mUnknown20 = -pBlock->mUnknown20;
    pBlock->mUnknown24 = -pBlock->mUnknown24;
    pBlock->mUnknown28 = (pBlock->mUnknown28 + 0x800000) & 0xFFFFFF;
}

extern "C" int fn_800DF6EC(Object_80039F5C *p)
{
    int result = 0;
    if (p->mFlags & 0x1000) {
        p->mFlags &= ~0x1000;
        result = 1;
    }
    return result;
}

extern "C" void fn_800DF710(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, Angles_801EBC18 *pAngles)
{
    float rot[4];
    fn_8009BFD0(p, pPos, rot);
    fn_801EBC18(pAngles, rot);
}

extern "C" void fn_800DF750(Object_80137ABC *pBall, Vector_80039F5C *pPos, int *pAngles)
{
    Vector_80039F5C old;
    Vector_80039F5C delta;
    fn_80137D58(pBall, &old);
    fn_802276B4(&delta, pPos, &old);
    fn_80137E74(pBall, &old);
    fn_80137D74(pBall, pPos);
    fn_80137E90(pBall, pAngles);
    fn_80137EE0(pBall, &delta);
}

extern "C" void fn_800DF9FC(Object_80039F5C *p, void *pRecord, unsigned int value) {
}

extern "C" int fn_800E0188(Object_80039F5C *p, float *pA, float *pB)
{
    if (p->mIdBytes[3] == 1 && p->mpState->mId == 50) {
        Block_800E0188 *pBlock = (Block_800E0188 *)&p->mUnknown336;
        if (pA) {
            *pA = pBlock->mUnknown0;
        }
        if (pB) {
            *pB = pBlock->mUnknown4;
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a)
{
    if (p == fn_80137B40() && fn_801BE648(p->mpUnknown792) == 74 && fn_801486A0()) {
        fn_80171DB0(p);
    }
}

extern "C" void fn_800E0230(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (fn_802372EC(0, 100) <= 64) {
        pBlock->mUnknown9 = 0;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    } else {
        pBlock->mUnknown9 = 1;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    }
}

extern "C" int fn_800E0574(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (fn_80137C48(p) == 0) {
        return 1;
    }
    fn_800E034C(p, pBlock);
    return 0;
}

extern "C" int fn_800E05C0(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (fn_80137C48(p) == 0) {
        return 1;
    }
    unsigned char state = pBlock->mUnknown8;
    switch (state) {
    case 0:
        fn_800E04C8(p, pBlock);
        break;
    case 1:
        if (p->mFlags & 0x1000) {
            p->mFlags &= ~0x1000;
            fn_800E0438(p, pBlock);
        }
        if (p->mFlags & 4) {
            fn_800E0438(p, pBlock);
            p->mUnknown512.mUnknown14 = state;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            return 1;
        }
        break;
    }
    return 0;
}

extern "C" int fn_800E068C(Object_80039F5C *p) {
    return 0;
}

extern "C" void fn_800E0818(int a, Vector_80039F5C *pOut, unsigned char *pIndex)
{
    fn_80137D58(fn_80137ABC(*pIndex), pOut);
}

extern "C" int fn_800E0E8C(Object_80039F5C *p)
{
    Block_800E0E8C *pBlock = (Block_800E0E8C *)&p->mUnknown336;
    if (pBlock->mUnknown2 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 8);
        pBlock->mUnknown2 = 0;
    }
    fn_8009A260(p);
    p->mFlags &= ~8;
    return 1;
}

extern "C" int fn_800E0EF0(Object_80039F5C *p)
{
    int result = 0;
    unsigned char id = p->mpState->mId;
    if (id == 28) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown28;
    } else if (id == 5) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown0;
    } else if (id == 12) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown16;
    } else if (id == 94) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown7;
    }
    return result;
}

extern "C" int fn_800E0F40(Object_80039F5C *p) {
    return 0;
}

extern "C" int fn_800E0F48(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);
    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f) ||
        (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget)
{
    int result = 0;
    if (fn_8009B9A8(0) && fn_80094488() > 1) {
        Vector_80039F5C end;
        Vector_80039F5C start;
        unsigned short i;
        fn_80227690(&end, pTarget, &p->mMotion.mPos);
        fn_802271A4(&end, &end);
        fn_80227248(&end, &end, p->mMotion.mUnknown28 * fn_8009BB54(0));
        fn_80227638(&end, &end, &p->mMotion.mPos);
        end.mZ = 0.0f;
        start = p->mMotion.mPos;
        start.mZ = 0.0f;
        for (i = 0; i < fn_80094488() - 1; i++) {
            if (fn_800E0F48(&p->mMotion.mPos, &end, fn_80094490(i), fn_80094490(i + 1)) ||
                fn_80227B04(&start, &end, fn_80094490(i)) < 4.0f ||
                fn_80227B04(&start, &end, fn_80094490(i + 1)) < 4.0f) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" int fn_800E11C0(Object_80039F5C *p)
{
    int result = 0;
    Block_800E11C0 *pBlock = p->mpUnknown3092->mpUnknown32;
    float distance = fn_8022781C(&pBlock->mUnknown32, &pBlock->mUnknown16);
    if (distance > 0.0f) {
        result = fn_801CFE08(fabsf(pBlock->mUnknown32.mZ - pBlock->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int fn_800E1248(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    if (p && pOther) {
        result = fn_80120794(&p->mMotion, &pOther->mMotion, &pOther->mMotion.mUnknown40, 0.2f,
                             pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                             fn_8022781C(&pOther->mMotion, &p->mMotion));
    }
    return result;
}

extern "C" int fn_800E12D4(Object_80039F5C *p)
{
    int result = 1;
    switch (p->mpState->mId) {
    case 16:
    case 17:
    case 28:
        result = 0;
        break;
    default:
        if (p->mUnknown1032 == 4 || p->mUnknown1032 == 6 || p->mUnknown1032 == 5) {
            result = 0;
        }
        break;
    }
    if (fn_8011E188() <= 30) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800E1350(Object_80039F5C *p)
{
    int result = 0;
    if (p && fn_800E12D4(p)) {
        Message_800F01CC message;
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 94;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_800AE7F0(13, p->mIdBytes[2], p);
        fn_800A8954(11, p->mIdBytes[2], p);
    }
    return result;
}

extern "C" int fn_800E13E4(Object_80039F5C *p)
{
    Block_800E13E4 *pBlock = (Block_800E13E4 *)&p->mUnknown336;
    pBlock->mUnknown4 = 30;
    pBlock->mUnknown5 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown6 = 0;
    p->mUnknown1160.mUnknown52 = 1;
    pBlock->mUnknown0 = p->mUnknown512.mUnknown8;
    pBlock->mUnknown12 = 0;
    if (p->mFlags & 0x4000) {
        pBlock->mUnknown7 = 1;
    } else {
        pBlock->mUnknown7 = 0;
    }
    return 0;
}

extern "C" int fn_800E1438(Object_80039F5C *p)
{
    int result = 0;
    Block_801718E8 *pBlock1160 = &p->mUnknown1160;
    Block_800E1438 *pBlock = (Block_800E1438 *)&p->mUnknown336;
    if (fn_801BE648(p->mpUnknown792) != 70) {
        p->mUnknown1008.mUnknown0 = 2;
        p->mUnknown1008.mUnknown1 = 2;
        p->mUnknown1008.mUnknown2 = 10;
        p->mUnknown1011 = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 70, p, 1.0f);
    }
    if (pBlock->mUnknown8 == 0) {
        pBlock->mUnknown8 = fn_800E11C0(p);
    }
    if (pBlock->mUnknown6 == 0) {
        pBlock->mUnknown6 = fn_800E8898(p, &pBlock->mUnknown12);
    }
    if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 11;
        message.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &message, p);
        pBlock1160->mUnknown52 = 0;
        result = 1;
    }
    return result;
}

extern "C" int fn_800E1544(Object_80039F5C *p)
{
    return ((Block_800E13E4 *)&p->mUnknown336)->mUnknown8 == 0;
}

extern "C" int fn_800E1554(Object_80039F5C *p)
{
    int result = 0;
    if (p && p->mpState->mId == 94) {
        result = ((Block_800E13E4 *)&p->mUnknown336)->mUnknown5 == 0;
    }
    return result;
}

extern "C" int fn_800E1778(Object_80039F5C *p)
{
    Block_800E1778 *pBlock = (Block_800E1778 *)&p->mUnknown336;
    unsigned int chance = 0;
    Record_800E1778 *pRecord;
    switch (p->mUnknown2914) {
    case 13:
    case 15:
        chance = 15;
        break;
    case 14:
        chance = 10;
        break;
    }
    Object_800670B4 *pObject = fn_80168708(p->mIdBytes[2]);
    if (pObject->mUnknown8.mUnknownF == 0) {
        pRecord = (Record_800E1778 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = fn_80163E94(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = (Record_800E1778 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if ((pRecord->mUnknown0 & ~0x80) == 85) {
        chance = 0;
    }
    if (chance != 0 && fn_802372EC(0, 100) < chance) {
        pBlock->mUnknown24 = 1;
        pBlock->mUnknown30 = 0;
    }
    return 0;
}
