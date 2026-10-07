#include <string.h>
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/fn_800AD9B4.h"
#include "game/cu_80136B1C.h"
#include "game/Object_8017886C.h"
#include "game/fn_802270D4.h"

/* 24-byte entry of a queue's handler table, indexed by a queued message id. */
struct Handlers_800EFC68 {
    int (*mpUnknown0)(Object_80039F5C *p);
    int (*mpUnknown4)(Object_80039F5C *p);
    int (*mpUnknown8)(Object_80039F5C *p);
    int (*mpUnknown12)(Object_80039F5C *p);
    int (*mpUnknown16)(Object_80039F5C *p, int value);
    void (*mpUnknown20)(Message_800F01CC *pMessage);
};

/* Descriptor registered per queue kind through fn_800EFE0C. */
struct Queue_800EFE0C {
    unsigned short mUnknown0;
    unsigned short mCount;
    Handlers_800EFC68 *mpHandlers;
};

/* 104-byte block held at +8 of each Entry_800F0EFC. */
struct Block_800F177C {
    unsigned int mUnknown0;
    char mUnknown4[100];
};

/* 116-byte entry of the array that Record_803EAE18 points to. */
struct Entry_800F0EFC {
    unsigned int *mpUnknown0;
    void *mpUnknown4;
    Block_800F177C mBlock;
    unsigned char mUnknown112;
    char mUnknown113[3];
};

/* 8-byte record registered through fn_80238174 by fn_800F164C. */
struct Record_803EAE18 {
    unsigned char mCount;
    char mUnknown1[3];
    Entry_800F0EFC *mpEntries;
};

/* Block at +336 of the player object used by fn_800F0C6C and fn_800F0CCC,
   the handlers in entry 52 of the handler table at 0x802DB280. */
struct Block_800F0C6C {
    char mUnknown0[4];
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

/* 88-byte block at +336 of the player object, cleared by fn_800F4A74. */
struct Block_800F4A74 {
    char mUnknown0[36];
    int mUnknown36;
    int mUnknown40;
    char mUnknown44[18];
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    char mUnknown64[24];
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

struct Points_800F3A6C {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[4];
    Point_8017886C mUnknown16;
};

struct Object_800F4E14 {
    char mUnknown0[20];
    int mUnknown20;
};

extern "C" {
extern Queue_800EFE0C **lbl_803EAE14;
extern int lbl_803EC9EC;
extern Record_803EAE18 *lbl_803EAE18;
extern float lbl_803EAE1C;
extern Block_800F177C lbl_802DAAD0;
extern unsigned int *lbl_802EE928[];
extern void *lbl_802EE938[];
extern float lbl_803ECB08;

void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800D6C70(Object_80039F5C *p);
int fn_800DD648(Object_80039F5C *p);
void fn_800EFC68(int a, State_80039F5C *pQueue);
void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p);
void fn_800F0490(int a, State_80039F5C *pQueue, int id);
void fn_800F0960(Object_80039F5C *p, Block_800F0C6C *pBlock);
int fn_800F0B84(Object_80039F5C *p);
void fn_800F0FD0(Block_800F177C *pBlock, int index);
int fn_800F1FDC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800F21E0(Object_80039F5C *p, Object_80039F5C *pOther, float distance);
int fn_800F2920(Object_80039F5C *p);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
float fn_801250B8(int a, int b, int c);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_80178320(void);
unsigned int fn_80178D18(int team);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
void *fn_8023816C(void *pHandle);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
}

extern "C" void fn_800EFC68(int a, State_80039F5C *pQueue) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    memmove(pEntries, pEntries + 1, (lbl_803EAE14[a]->mCount - 1) * 4);
    pEntries[lbl_803EAE14[a]->mCount - 1].mId = 0;
}

extern "C" void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    p->mUnknown3088 = 0;
    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown0(p) == 1 && p->mUnknown3088 == 0) {
        fn_800EFC68(a, pQueue);
        fn_800EFCD0(a, pQueue, p);
    }
    p->mUnknown3088 = 1;
    fn_800D6C70(p);
}

extern "C" void fn_800EFD70(int count) {
    if (lbl_803EAE14 == 0) {
        lbl_803EC9EC = count;
        lbl_803EAE14 = (Queue_800EFE0C **)fn_801D2B7C(count * 4, 0, 0);
        for (int i = 0; i < count; i++) {
            lbl_803EAE14[i] = 0;
        }
    }
}

extern "C" void fn_800EFDD8() {
    if (lbl_803EAE14 != 0) {
        fn_801D2BD0(lbl_803EAE14);
        lbl_803EAE14 = 0;
    }
}

extern "C" void fn_800EFE0C(int a, Queue_800EFE0C *pQueue) {
    lbl_803EAE14[a] = pQueue;
}

extern "C" void fn_800EFE1C(int a, State_80039F5C *pQueue) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    for (int i = 0; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
    for (int i = 0; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFEF8(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0].mId = 0;
    }
    for (int i = 1; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFFA0(int a, State_80039F5C *pQueue, Object_80039F5C *p, int flag) {
    int id = pQueue->mId;
    int done = 0;

    if (flag != 0) {
        p->mUnknown3088 = 0;
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown12(p) == 1) {
            if (p->mUnknown3088 == 0) {
                fn_800EFC68(a, pQueue);
                done = 1;
                fn_800EFCD0(a, pQueue, p);
            } else {
                fn_800F0490(a, pQueue, id);
            }
        }
    }
    if (done == 0) {
        p->mUnknown3088 = 0;
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown8(p) == 1) {
            if (p->mUnknown3088 == 0) {
                fn_800EFC68(a, pQueue);
                fn_800EFCD0(a, pQueue, p);
            } else {
                fn_800F0490(a, pQueue, id);
            }
        }
    }
}

extern "C" void fn_800F00D4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        int i;
        int last = lbl_803EAE14[a]->mCount - 2;

        for (i = 0; i < last && pEntries[i].mId != 0; i++) {
        }
        memmove(pEntries + 1, pEntries, (i + 1) * 4);
        pEntries[0] = *pMessage;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
        pEntries[2].mId = 0;
    }
}

extern "C" void fn_800F01CC(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (pEntries[0].mId != 0) {
        int i;
        int last = lbl_803EAE14[a]->mCount - 2;

        for (i = 1; i < last && pEntries[i].mId != 0; i++) {
        }
        memmove(pEntries + 2, pEntries + 1, i * 4);
        pEntries[1] = *pMessage;
    } else {
        fn_800F053C(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F0278(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p, int position) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;
    Queue_800EFE0C *pInfo = lbl_803EAE14[a];

    if (pEntries[pInfo->mCount - 1].mId == 0) {
        if (pEntries[0].mId != 0) {
            int i;

            if (position == 0 && pInfo->mpHandlers[pEntries[0].mId].mpUnknown4(p) != 1) {
                position = 1;
            }
            for (i = 0; i < lbl_803EAE14[a]->mCount && pEntries[i].mId != 0 && i != position; i++) {
            }
            if (i != lbl_803EAE14[a]->mCount) {
                memmove(pEntries + (i + 1), pEntries + i, (lbl_803EAE14[a]->mCount - i - 1) * 4);
                pEntries[i] = *pMessage;
                if (i == 0) {
                    fn_800EFCD0(a, pQueue, p);
                }
            }
        } else {
            fn_800F053C(a, pQueue, pMessage, p);
        }
    }
}

extern "C" void fn_800F03D8(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (pEntries[0].mId != 0) {
        int i;

        for (i = 1; i < lbl_803EAE14[a]->mCount && pEntries[i].mId != 0; i++) {
        }
        if (i != lbl_803EAE14[a]->mCount) {
            pEntries[i++] = *pMessage;
            if (i != lbl_803EAE14[a]->mCount) {
                pEntries[i].mId = 0;
            }
        }
    } else {
        fn_800F053C(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F0490(int a, State_80039F5C *pQueue, int id) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;
    int count = lbl_803EAE14[a]->mCount;

    for (int i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            memmove(&pEntries[i], &pEntries[i + 1], (count - i - 1) * 4);
            pEntries[lbl_803EAE14[a]->mCount - 1].mId = 0;
            break;
        }
    }
}

extern "C" void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0] = *pMessage;
        pEntries[1].mId = 0;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
        pEntries[2].mId = 0;
    }
}

extern "C" void fn_800F05E4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0] = *pMessage;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F067C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
    pEntries[0] = *pMessage;
    fn_800EFCD0(a, pQueue, p);
}

extern "C" int fn_800F06F4(int a, void *pRecord, int id, int value) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pRecord;
    int result = 0xFFFF;
    unsigned int i;

    if (value == 0xFFFF) {
        i = 0;
    } else {
        i = value;
    }
    if ((pEntries[i].mId & 0x7F) == 0) {
        return 0xFFFF;
    }
    for (; i < lbl_803EAE14[a]->mCount && (pEntries[i].mId & ~0x80) != 0; i++) {
        if ((pEntries[i].mId & ~0x80) == id) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int fn_800F0770(int a, State_80039F5C *pQueue, int which, int value, Object_80039F5C *p) {
    int result = 0;

    switch (which) {
    case 0:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown0(p);
        break;
    case 1:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
        break;
    case 2:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown8(p);
        break;
    case 3:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown12(p);
        break;
    case 4:
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown16 != 0) {
            result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown16(p, value);
        }
        break;
    }
    if (result == 1) {
        fn_800EFC68(a, pQueue);
        fn_800EFCD0(a, pQueue, p);
    }
    return result;
}

extern "C" int fn_800F08F8() {
    return 0;
}

extern "C" int fn_800F0900() {
    return 1;
}

extern "C" int fn_800F0908() {
    return 0;
}

extern "C" void fn_800F0910(int a, Message_800F01CC *pMessage) {
    void (*pHandler)(Message_800F01CC *) = lbl_803EAE14[a]->mpHandlers[pMessage->mId].mpUnknown20;

    if (pHandler != 0) {
        pHandler(pMessage);
    }
}

extern "C" void fn_800F0BF8(Object_80039F5C *p, int a, int angle) {
    if (fn_800F0B84(p) != 0) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 52;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = angle >> 17 & 0x7F;
        fn_800F00D4(0, p->mpState, &message, p);
    }
}

extern "C" int fn_800F0C6C(Object_80039F5C *p) {
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;

    pBlock->mUnknown4 = (p->mpState->mUnknown2 & 0x7F) << 17;
    pBlock->mUnknown8 = 0;
    if (fn_800F0B84(p) != 0) {
        pBlock->mUnknown9 = 0;
    } else {
        pBlock->mUnknown9 = 1;
    }
    return 0;
}

extern "C" int fn_800F0CCC(Object_80039F5C *p) {
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;
    Object_800B26B0 *pMotion = &p->mMotion;

    if (pBlock->mUnknown9 != 0) {
        return 1;
    }
    if (pBlock->mUnknown8 == 0) {
        fn_800F0960(p, pBlock);
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags &= ~4;
        pBlock->mUnknown8 = 1;
    }
    if (fn_8013BA58(fn_801374BC(), 0) == 4 && p == fn_80137B88(fn_801374BC())) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 23;
        message.mUnknown1[0] = fn_801374E0(fn_801374BC());
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        fn_800A5A8C(9, p, p);
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pMotion->mFacing;
        p->mUnknown512.mUnknown4 = pMotion->mFacing;
        p->mUnknown512.mUnknown0 = pMotion->mUnknown28 / lbl_803ECB08;
        return 1;
    }
    return 0;
}

extern "C" void fn_800F0E10(Message_800F01CC *pMessage) {
    pMessage->mUnknown1[1] = (0x800000 - (pMessage->mUnknown1[1] << 17)) >> 17 & 0x7F;
}

extern "C" int fn_800F0E2C(void *p, void *q) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;
    Record_803EAE18 *pOther = (Record_803EAE18 *)q;
    int result;

    if (pOther != 0) {
        result = 0;
        result |= pRecord->mCount != pOther->mCount;
        result |= fn_80238258(pRecord->mpEntries, pOther->mpEntries, pRecord->mCount * 116);
    } else {
        result = fn_80238278(pRecord, 8, 0);
        result = fn_80238278(pRecord->mpEntries, pRecord->mCount * 116, result);
    }
    return result;
}

extern "C" int fn_800F0EC0(void *p, int value) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    fn_801D2BD0(pRecord->mpEntries);
    pRecord->mpEntries = 0;
    return 0;
}

extern "C" int fn_800F0EFC(void *p, int value) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    pRecord->mpEntries = (Entry_800F0EFC *)fn_801D2B7C(pRecord->mCount * 116, 0, 0);
    memset(pRecord->mpEntries, 0, pRecord->mCount * 116);
    for (int i = 0; i < pRecord->mCount; i++) {
        pRecord->mpEntries[i].mpUnknown0 = lbl_802EE928[0];
        pRecord->mpEntries[i].mpUnknown4 = lbl_802EE938[0];
    }
    return 0;
}

extern "C" int fn_800F0FA0(Block_800F177C *pBlock, unsigned int *pMasks, int index) {
    int result = 0;

    if (pMasks != 0 && (pBlock->mUnknown0 & pMasks[index]) == pMasks[index]) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800F15B0(void *p, void *pBuffer) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    memcpy(pBuffer, pRecord, 8);
    memcpy((char *)pBuffer + 8, pRecord->mpEntries, pRecord->mCount * 116);
    return 1;
}

extern "C" int fn_800F1604(void *p, void *pBuffer) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    memcpy(pRecord->mpEntries, (char *)pBuffer + 8, pRecord->mCount * 116);
    return 1;
}

extern "C" int fn_800F1638(void *p) {
    return lbl_803EAE18->mCount * 116 + 8;
}

extern "C" void fn_800F164C(int count) {
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAE18, 8, 0, 0x6173736A);
    Record_803EAE18 *pRecord;

    fn_80238234(pHandle, fn_800F0EFC, fn_800F0EC0, 0, fn_800F0E2C);
    fn_80238248(pHandle, fn_800F15B0, fn_800F1638, fn_800F1604);
    pRecord = (Record_803EAE18 *)fn_8023816C(pHandle);
    pRecord->mCount = count;
    pRecord->mpEntries = 0;
    fn_802381E0(pHandle);
}

extern "C" void fn_800F16F4() {
    lbl_803EAE18 = 0;
}

extern "C" void fn_800F1700() {
    for (unsigned char i = 0; i < lbl_803EAE18->mCount; i++) {
        fn_800F0FD0(&lbl_803EAE18->mpEntries[i].mBlock, i);
        lbl_803EAE18->mpEntries[i].mUnknown112 = 0;
    }
}

extern "C" void fn_800F177C(int index, Block_800F177C *pOut) {
    Block_800F177C *pSource;

    if (lbl_803EAE18->mpEntries[index].mUnknown112 == 0) {
        pSource = &lbl_803EAE18->mpEntries[index].mBlock;
    } else {
        pSource = &lbl_802DAAD0;
    }
    *pOut = *pSource;
}

extern "C" void fn_800F1800(int index) {
    lbl_803EAE18->mpEntries[index].mUnknown112 = 1;
}

extern "C" void fn_800F181C(int index, int which) {
    lbl_803EAE18->mpEntries[index].mpUnknown0 = lbl_802EE928[which];
    lbl_803EAE18->mpEntries[index].mpUnknown4 = lbl_802EE938[which];
}

extern "C" int fn_800F1EE0(Object_80039F5C *p) {
    int result = 0;
    int mode = fn_800AD9B4();

    if (fn_80137C48(p) == 0) {
        return 0;
    }
    if (mode == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 25:
        case 26:
        case 27:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (!(p->mFlags & 0x4000) && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) > 0x38E38E) {
            result = 0;
        }
        if ((p->mUnknown528.mUnknown15 >= 4 && p->mUnknown528.mUnknown15 <= 19) || p->mUnknown528.mUnknown15 > 21) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800F22D8(Object_80039F5C *p, int a, int b, int c) {
    int result = 0;

    if (fn_800F1EE0(p) != 0) {
        Message_800F01CC message;

        if (b == 0 || a == 1) {
            float distance;
            int team = fn_80178320();
            Object_80039F5C *pOther = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), 0x2E38E3, &distance, 0);

            if (b == 0) {
                b = fn_800F1FDC(p, pOther);
            }
            if (a == 1) {
                a = fn_800F21E0(p, pOther, distance);
            }
        }
        fn_800D0BF4(p, c, 34);
        result = 1;
        memset(&message, 0, 4);
        message.mId = 34;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_800F2828(int a, int b) {
    return fn_801250B8(a, b, 6) < lbl_803EAE1C;
}

extern "C" int fn_800F285C(Object_80039F5C *p) {
    if (fn_800AD9B4() != 3) {
        return 0;
    }
    switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 32:
        case 34:
        case 35:
        case 36:
        case 43:
        case 51:
        case 91:
        return 0;
    }
    return 1;
}

extern "C" int fn_800F2A40(Object_80039F5C *p) {
    Object_80039F5C *pOther = fn_80137B40();

    if (pOther != 0) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
    }
    return 1;
}

extern "C" int fn_800F2C14() {
    return 0;
}

extern "C" int fn_800F2C1C(Object_80039F5C *p, int a) {
    if (fn_800F285C(p) != 0) {
        if ((p->mId & 0xFF) == 1 && p->mUnknown1032 == 4) {
            return fn_800F2920(p);
        } else {
            Message_800F01CC message;

            memset(&message, 0, 4);
            message.mId = 5;
            message.mUnknown1[0] = a;
            fn_800F00D4(0, p->mpState, &message, p);
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_800F3A6C(Object_80039F5C *pA, Object_80039F5C *pB, Info_800F3A6C *pInfo, Points_800F3A6C *pPoints) {
    Point_8017886C delta;

    fn_80227690(&pInfo->mUnknown0, &pPoints->mUnknown16, &pB->mMotion.mPos);
    pInfo->mUnknown16 = fn_801CFE40(pInfo->mUnknown0.mY, pInfo->mUnknown0.mX);
    fn_80227690(&pInfo->mUnknown8, &pA->mMotion.mPos, &pB->mMotion.mPos);
    pInfo->mUnknown20 = fn_801CFE40(pInfo->mUnknown8.mY, pInfo->mUnknown8.mX);
    pInfo->mUnknown32 = fn_802270A4(&pInfo->mUnknown8);
    fn_80227690(&delta, &pPoints->mUnknown4, &pB->mMotion.mPos);
    pInfo->mUnknown24 = fn_801CFE40(delta.mY, delta.mX);
    pInfo->mUnknown36 = fn_802270A4(&delta);
    fn_80227690(&delta, &pPoints->mUnknown4, &pA->mMotion.mPos);
    pInfo->mUnknown28 = fn_801CFE40(delta.mY, delta.mX);
    pInfo->mUnknown40 = fn_802270A4(&delta);
}

extern "C" int fn_800F4A74(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;

    memset(pBlock, 0, 88);
    pBlock->mUnknown62 = fn_801374E0(fn_801374BC());
    pBlock->mUnknown63 = 0;
    pBlock->mUnknown36 = 0;
    pBlock->mUnknown40 = 0xC00000;
    return 0;
}

extern "C" int fn_800F4E14(Object_80039F5C *p, Object_800F4E14 *pInfo) {
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) == 86) {
        fn_800F0BF8(p, 4, pInfo->mUnknown20);
        result = 1;
    } else if (fn_801BE648(p->mpUnknown792) == 85) {
        fn_800DD648(p);
    }
    return result;
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_80125508() {
    return 0;
}
