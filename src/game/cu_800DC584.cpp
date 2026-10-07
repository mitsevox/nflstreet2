#include "game/Object_80039F5C.h"
#include "game/Object_801BBD5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

struct Record_800DDCE4 {
    char mUnknown0[9];
    unsigned char mUnknown9;
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

extern "C" {
int fn_800DA7AC(Object_801BBD5C *pObject, float value);
float fn_800DAA68(int index, void *pA, Object_801BBD5C *pObject, int b, float value);
void fn_8009A260(Object_80039F5C *p);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_8009D1F4(Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AE7F0(int event, int team, Object_80039F5C *p);
void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned int fn_8011E188(void);
int fn_801486A0(void);
void fn_80171DB0(Object_80039F5C *p);
int fn_801BE648(void *p);
int fn_801CFFD0(int a, int b);
}

extern float lbl_803ECB08;

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

extern "C" int fn_800DD830(void *p) {
    return 1;
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

extern "C" int fn_800DF6EC(Object_80039F5C *p)
{
    int result = 0;
    if (p->mFlags & 0x1000) {
        p->mFlags &= ~0x1000;
        result = 1;
    }
    return result;
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
