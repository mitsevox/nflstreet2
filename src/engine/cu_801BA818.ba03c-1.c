#include "engine/cu_801BA03C.ba03c-1.h"

typedef struct Def_801BB2D8 {
    int mSize;
    unsigned short mFlags;
    unsigned char mUnknown6[2];
    Object_801BC084 *mpData;
} Def_801BB2D8;

typedef struct Config_801BB2D8 {
    void *mpArchive;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned short mUnknownC;
    unsigned char mUnknownE[2];
    int mUnknown10;
    Def_801BB2D8 *mpBuffers;
} Config_801BB2D8;

typedef struct Request_801BAE08 {
    int mSlot;
    int mUnknown4;
} Request_801BAE08;

typedef struct Query_801BBA18 {
    short mSlot;
    short mStateRef;
} Query_801BBA18;

typedef struct Cache_801BF870 {
    short mUnknown0;
    short mUnknown2;
} Cache_801BF870;

typedef struct Entry_801BAB88 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    void *mpUnknown4;
} Entry_801BAB88;

typedef struct List_801BAB88 {
    unsigned short mCount;
    unsigned short mMax;
    Entry_801BAB88 mEntries[380];
} List_801BAB88;

typedef struct List_801BAC1C {
    unsigned short mCount;
    unsigned short mMax;
    unsigned short mState;
    unsigned char mUnknown6[2];
    Entry_801BAB88 mEntries[8];
} List_801BAC1C;

typedef struct Block_801BC0E8 {
    unsigned char mUnknown0[12];
    char *mpUnknownC;
} Block_801BC0E8;

typedef struct Record_801BC0E8 {
    unsigned char mUnknown0[12];
    Block_801BC0E8 mBlocks[15];
} Record_801BC0E8;

typedef struct Group_801BC0E8 {
    unsigned short mUnknown0;
    unsigned short mCount;
    Record_801BC0E8 *mpRecords;
} Group_801BC0E8;

typedef struct Set_801BC0E8 {
    unsigned short mUnknown0;
    unsigned short mCount;
    Group_801BC0E8 *mpGroups;
} Set_801BC0E8;

typedef struct Info_801BC0E8 {
    unsigned char mUnknown0[13];
    unsigned char mCount;
    unsigned char mUnknownE[2];
    Set_801BC0E8 *mpSets;
} Info_801BC0E8;

typedef struct Part_801BC0E8 {
    unsigned short mUnknown0;
    unsigned short mObjectType;
    int mTag;
    int mSize;
    Object_801BC084 *mpFile;
} Part_801BC0E8;

typedef struct Entry_801BC0E8 {
    Part_801BC0E8 mParts[2];
} Entry_801BC0E8;

typedef struct Big_801BC0E8 {
    unsigned char mUnknown0[12];
    unsigned int mCount;
    Entry_801BC0E8 mEntries[1];
} Big_801BC0E8;

typedef struct Entry_801BC57C {
    unsigned short mUnknown0;
    unsigned short mObjectType;
    int mSize;
    Object_801BC084 mFile;
} Entry_801BC57C;

typedef struct Big_801BC57C {
    unsigned char mUnknown0[12];
    unsigned int mCount;
    Entry_801BC57C mFirst;
} Big_801BC57C;

extern void (*lbl_803ECEB8)(Object_801BC084 *pFile);
extern void *lbl_803EBB88;
extern void (*lbl_803EBB8C)(int slot, int file);
extern void (*lbl_803EBB90)(Object_801BC084 *pFile);
extern unsigned char lbl_803EBB94;
extern int lbl_803ED5F0;
extern int lbl_803ED5F4;
extern int lbl_803ED5F8;
extern Buffer_801BB2D8 *lbl_803ED5FC;
extern int lbl_803ED600;
extern int lbl_803ED604;
extern int lbl_803ED608;
extern Request_801BAE08 *lbl_803ED60C;

int fn_801B9EF8(void);
void *fn_801D2BB0(int heap, int size, int align, int flags);
int fn_801D2BD0(void *p);
int fn_801F0F18(int a);
void fn_801F81AC(void);
int fn_801F7C88(void);
int fn_801F010C(void *pArchive, int id);
Object_801BC084 *fn_801EF390(void *pArchive, int id, int heap);
int fn_801F0C50(void *pArchive, int id);
int fn_801EFF80(void *pArchive, int id, void *pDest);
Object_801BC084 *fn_801EF548(void *pArchive, int id, int heap, int priority,
                             void (*pCallback)(int, int, int, int, Request_801BAE08 *), Request_801BAE08 *pRequest);
int fn_801EFD2C(void *pArchive, int id, int heap, Object_801BC084 *pDest, int priority,
                void (*pCallback)(int, int, int, int, Request_801BAE08 *), Request_801BAE08 *pRequest);
int fn_801CB120(void);
void fn_801CAF24(void);
Cache_801BF870 *fn_801BF870(int objectType, int state);
void fn_801BF7BC(int objectType);
void *fn_801BFD8C(Object_801BC084 *pFile, int a, int b, int index, void *pMotion, int group);

unsigned short fn_801BAB24(Object_801BC084 *pFile);
unsigned short fn_801BAD98(void);
int fn_801BAEAC(int slot);
int fn_801BB164(int id, Object_801BC084 *pData, int frameCache, int bigFile);
int fn_801BB544(int id, int frameCache, int bigFile);
unsigned int fn_801BBA18(int state, unsigned short objectType, Query_801BBA18 *pOut, unsigned int max);
unsigned char fn_801BBFE4(int id);
unsigned char fn_801BC044(unsigned short slot);
unsigned char fn_801BC060(unsigned short slot);

void fn_801BA818(Object_801BC084 *pFile)
{
    if (lbl_803ECEB8)
        lbl_803ECEB8(pFile);
}

void fn_801BA848(void (*pFunc)(Object_801BC084 *))
{
    lbl_803ECEB8 = pFunc;
}

void fn_801BA850(Object_801BC084 *pFile)
{
    int i;
    int j;

    if (!(pFile->mFlags & 0x1000)) {
        pFile->mpStates = (States_801BAB48 *)((char *)pFile->mpStates + (int)pFile);
        pFile->mpAnims = (Anims_801BAB34 *)((char *)pFile->mpAnims + (int)pFile);
        pFile->mpMotion = (void **)((char *)pFile->mpMotion + (int)pFile);
        if (pFile->mFlags & 8) {
            pFile->mpGroups = (unsigned int *)((char *)pFile->mpGroups + (int)pFile);
            pFile->mpGroupMotion = (Group_801BACD0 *)((char *)pFile->mpGroupMotion + (int)pFile);
            if (pFile->mFlags & 4) {
                for (i = 0; i < *pFile->mpGroups; i++) {
                    if (pFile->mpGroupMotion[i].mpMotion) {
                        pFile->mpGroupMotion[i].mpMotion =
                            (void **)((char *)pFile->mpGroupMotion[i].mpMotion + (int)pFile);
                        for (j = 0; j < pFile->mpGroupMotion[i].mCount; j++)
                            pFile->mpGroupMotion[i].mpMotion[j] =
                                (char *)pFile->mpGroupMotion[i].mpMotion[j] + (int)pFile;
                    }
                }
            }
        }
        for (i = 0; i < pFile->mMotionCount; i++) {
            if (pFile->mFlags & 4)
                pFile->mpMotion[i] = 0;
            else
                pFile->mpMotion[i] = (char *)pFile->mpMotion[i] + (int)pFile;
        }
        for (i = 0; i < pFile->mpStates->mCount; i++) {
            State_801BAB48 *pState = &pFile->mpStates->mStates[i];
            unsigned short id;

            pState->mpAnims = (StateAnims_801BAB88 *)((char *)pState->mpAnims + (int)pFile);
            if (!(pFile->mFlags & 8)) {
                id = pState->mId;
                pState->mId = pState->mpAnims->mUnknown2;
                pState->mpAnims->mUnknown2 = id;
            }
            for (j = 0; j < pState->mpAnims->mCount; j++) {
                if (pState->mpAnims->mEntries[j].mpAnim)
                    pState->mpAnims->mEntries[j].mpAnim = (char *)pState->mpAnims->mEntries[j].mpAnim + (int)pFile;
            }
            if (pState->mpUnknown8)
                pState->mpUnknown8 = (char *)pState->mpUnknown8 + (int)pFile;
            pState->mpTrans = (StateTrans_801BAC1C *)((char *)pState->mpTrans + (int)pFile);
            for (j = 0; j < pState->mpTrans->mCount; j++) {
                if (pState->mpTrans->mEntries[j].mpUnknownC)
                    pState->mpTrans->mEntries[j].mpUnknownC = (char *)pState->mpTrans->mEntries[j].mpUnknownC + (int)pFile;
            }
        }
        for (i = 0; i < pFile->mpAnims->mCount; i++)
            pFile->mpAnims->mAnims[i] = (Anim_801BAB34 *)((char *)pFile->mpAnims->mAnims[i] + (int)pFile);
        fn_801BA818(pFile);
        pFile->mFlags |= 0x1000;
    }
    if (!(pFile->mFlags & 0x2000))
        fn_801BF7BC(fn_801BAB24(pFile));
}

unsigned short fn_801BAB24(Object_801BC084 *pFile)
{
    return pFile->mObjectType;
}

unsigned short fn_801BAB2C(Object_801BC084 *pFile)
{
    return pFile->mFileNum;
}

Anim_801BAB34 *fn_801BAB34(Object_801BC084 *pFile, int anim)
{
    return pFile->mpAnims->mAnims[anim];
}

int fn_801BAB48(Object_801BC084 *pFile, int state)
{
    unsigned int i;

    for (i = 0; i < pFile->mpStates->mCount; i++) {
        if (pFile->mpStates->mStates[i].mId == state)
            return i;
    }
    return -1;
}

void fn_801BAB88(Object_801BC084 *pFile, int slot, int stateRef, List_801BAB88 *pList)
{
    StateAnims_801BAB88 *pAnims;
    unsigned int i;

    if (pFile) {
        pAnims = pFile->mpStates->mStates[stateRef].mpAnims;
        for (i = 0; i < pAnims->mCount; i++) {
            if (pList->mCount >= pList->mMax)
                return;
            pList->mEntries[pList->mCount].mUnknown0 = slot;
            pList->mEntries[pList->mCount].mUnknown2 = pAnims->mEntries[i].mId;
            pList->mEntries[pList->mCount].mpUnknown4 = pAnims->mEntries[i].mpAnim;
            pList->mCount++;
        }
    }
}

void fn_801BAC1C(Object_801BC084 *pFile, int slot, int stateRef, List_801BAC1C *pList)
{
    StateTrans_801BAC1C *pTrans;

    if (pList->mCount < pList->mMax) {
        pTrans = pFile->mpStates->mStates[stateRef].mpTrans;
        if (pTrans && pTrans->mCount) {
            pList->mEntries[pList->mCount].mUnknown0 = slot;
            pList->mEntries[pList->mCount].mUnknown2 = pFile->mFileNum;
            pList->mEntries[pList->mCount].mpUnknown4 = pFile->mpStates->mStates[stateRef].mpTrans;
            pList->mCount++;
        }
    }
}

void *fn_801BAC9C(Object_801BC084 *pFile, int stateRef)
{
    return pFile->mpStates->mStates[stateRef].mpUnknown8;
}

unsigned int fn_801BACB0(Object_801BC084 *pFile)
{
    return pFile->mpStates->mCount;
}

unsigned short fn_801BACBC(Object_801BC084 *pFile, int stateRef)
{
    return pFile->mpStates->mStates[stateRef].mId;
}

void *fn_801BACD0(Object_801BC084 *pFile, int a, int b, unsigned int index, int group)
{
    void *pMotion;

    if (pFile->mFlags & 4) {
        pMotion = pFile->mpGroupMotion[group].mpMotion[index];
        if (pFile->mFlags & 0x200)
            pMotion = fn_801BFD8C(pFile, a, b, index, pMotion, group);
    } else {
        if (index >= pFile->mMotionCount)
            index = 0;
        pMotion = pFile->mpMotion[index];
        if (pFile->mFlags & 0x200)
            pMotion = fn_801BFD8C(pFile, a, b, index, pMotion, 0xFFFF);
    }
    return pMotion;
}

void *fn_801BAD70(Object_801BC084 *pFile, int a, int b, unsigned int index)
{
    return fn_801BACD0(pFile, a, b, index, 0xFFFF);
}

unsigned short fn_801BAD98(void)
{
    unsigned int i;

    for (i = lbl_803ED5F0 + lbl_803ED5F4; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 0)
            return i;
    }
    return 0xFFFF;
}

void fn_801BAE08(int a, int b, int c, int d, Request_801BAE08 *pRequest)
{
    int slot = pRequest->mSlot;

    if (pRequest->mUnknown4) {
        lbl_803EBB8C(slot, pRequest->mUnknown4);
    } else {
        fn_801BA850(lbl_803ED5FC[slot].mpData);
        lbl_803ED5FC[slot].mParent = -1;
        lbl_803ED5FC[slot].mObjectType = fn_801BAB24(fn_801BC084(slot));
    }
    lbl_803ED5FC[slot].mStatus = 1;
}

void fn_801BAEA4(void (*pFunc)(Object_801BC084 *))
{
    lbl_803EBB90 = pFunc;
}

int fn_801BAEAC(int slot)
{
    int result = 0;
    unsigned int i;

    if (lbl_803ED5FC[slot].mStatus != 0) {
        if (slot < lbl_803ED5F0) {
            if (lbl_803ED5FC[slot].mStatus == 2) {
                while (fn_801BBFE4(lbl_803ED5FC[slot].mId) != 1) {
                    if (lbl_803EBB94)
                        fn_801F0F18(0);
                    else
                        fn_801F81AC();
                }
            }
        } else if (slot < lbl_803ED5F0 + lbl_803ED5F4) {
            if (lbl_803ED5FC[slot].mStatus == 2) {
                while (fn_801BC044(slot - lbl_803ED5F0) != 1) {
                    if (lbl_803EBB94)
                        fn_801F0F18(0);
                    else
                        fn_801F81AC();
                }
            }
        } else {
            if (lbl_803ED5FC[slot].mStatus == 2) {
                while (fn_801BC060(slot - lbl_803ED5F0 - lbl_803ED5F4) != 1) {
                    if (lbl_803EBB94)
                        fn_801F0F18(0);
                    else
                        fn_801F81AC();
                }
            }
        }
        if (lbl_803ED5FC[slot].mParent == 0xFFFF) {
            if (lbl_803EBB90 && !(lbl_803ED5FC[slot].mObjectType & 0x8000) && lbl_803ED5FC[slot].mId != -3)
                lbl_803EBB90(lbl_803ED5FC[slot].mpData);
            if (slot < lbl_803ED5F0 && lbl_803ED5FC[slot].mId != -1 && lbl_803ED5FC[slot].mId != -3)
                result = fn_801F010C(lbl_803EBB88, lbl_803ED5FC[slot].mId);
            if (slot >= lbl_803ED5F0 + lbl_803ED5F4) {
                lbl_803ED5FC[slot].mpData = 0;
                lbl_803ED5FC[slot].mSize = 0;
            }
        }
        if (lbl_803ED5FC[slot].mObjectType == 0x8000) {
            for (i = lbl_803ED5F0 + lbl_803ED5F4; i < lbl_803ED5F8; i++) {
                if (lbl_803ED5FC[i].mParent == slot) {
                    lbl_803ED5FC[i].mUnknown13 = 0;
                    lbl_803ED5FC[i].mSize = 0;
                    lbl_803ED5FC[i].mpData = 0;
                    lbl_803ED5FC[i].mStatus = 0;
                    lbl_803ED5FC[i].mParent = -1;
                    fn_801BF7BC(lbl_803ED5FC[i].mObjectType & ~0x4000);
                }
            }
        }
        fn_801BF7BC(lbl_803ED5FC[slot].mObjectType);
        lbl_803ED5FC[slot].mUnknown13 = 0;
        lbl_803ED5FC[slot].mStatus = 0;
        lbl_803ED5FC[slot].mObjectType = -1;
        lbl_803ED5FC[slot].mParent = -1;
    }
    return result;
}

int fn_801BB164(int id, Object_801BC084 *pData, int frameCache, int bigFile)
{
    int result = 0;
    int i;

    for (i = 0; i < lbl_803ED5F0; i++) {
        if (lbl_803ED5FC[i].mStatus == 0) {
            lbl_803ED5FC[i].mStatus = 1;
            lbl_803ED5FC[i].mId = id;
            if (pData == 0) {
                lbl_803ED5FC[i].mpData = fn_801EF390(lbl_803EBB88, id, lbl_803ED600);
                result = fn_801F7C88();
            } else {
                lbl_803ED5FC[i].mpData = pData;
            }
            lbl_803ED5FC[i].mFrameCache = frameCache;
            if (frameCache)
                lbl_803ED5FC[i].mpData->mFlags |= 0x200;
            else
                lbl_803ED5FC[i].mpData->mFlags &= ~0x200;
            if (pData == 0) {
                if (bigFile) {
                    lbl_803EBB8C(i, bigFile);
                    break;
                }
                fn_801BA850(lbl_803ED5FC[i].mpData);
            }
            lbl_803ED5FC[i].mParent = -1;
            lbl_803ED5FC[i].mObjectType = fn_801BAB24(fn_801BC084((unsigned short)i));
            break;
        }
    }
    if (i == lbl_803ED5F0)
        result = 0x140003;
    return result;
}

int fn_801BB2D8(Config_801BB2D8 *pConfig)
{
    int i;

    lbl_803ED5F0 = pConfig->mUnknown8;
    lbl_803ED5F4 = pConfig->mUnknownA;
    lbl_803ED608 = pConfig->mUnknownC;
    lbl_803ED5F8 = lbl_803ED5F0 + lbl_803ED5F4 + lbl_803ED608;
    lbl_803EBB88 = pConfig->mpArchive;
    lbl_803ED604 = pConfig->mUnknown10;
    lbl_803ED600 = pConfig->mUnknown4;
    lbl_803ED5FC = fn_801D2BB0(lbl_803ED600, lbl_803ED5F8 * sizeof(Buffer_801BB2D8), 0, 0);
    lbl_803ED60C = fn_801D2BB0(lbl_803ED600, lbl_803ED5F8 * sizeof(Request_801BAE08), 0, 0);
    if (lbl_803ED5FC) {
        for (i = 0; i < lbl_803ED5F8; i++) {
            if (i >= lbl_803ED5F0 && i < lbl_803ED5F0 + lbl_803ED5F4) {
                lbl_803ED5FC[i].mSize = pConfig->mpBuffers[i - lbl_803ED5F0].mSize;
                lbl_803ED5FC[i].mFlags = pConfig->mpBuffers[i - lbl_803ED5F0].mFlags;
                if (pConfig->mpBuffers[i - lbl_803ED5F0].mFlags & 0x8000)
                    lbl_803ED5FC[i].mpData = pConfig->mpBuffers[i - lbl_803ED5F0].mpData;
                else
                    lbl_803ED5FC[i].mpData = fn_801D2BB0(lbl_803ED600, lbl_803ED5FC[i].mSize, 0, 0);
            } else {
                lbl_803ED5FC[i].mFlags = 0;
                lbl_803ED5FC[i].mSize = 0;
                lbl_803ED5FC[i].mpData = 0;
            }
            lbl_803ED5FC[i].mUnknown13 = 0;
            lbl_803ED5FC[i].mStatus = 0;
            lbl_803ED5FC[i].mId = 0;
            lbl_803ED5FC[i].mObjectType = -1;
            lbl_803ED5FC[i].mParent = -1;
        }
        return 0;
    }
    return fn_801F7C88();
}

void fn_801BB480(void)
{
    int i;

    fn_801F0F18(0);
    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1)
            fn_801BAEAC(i);
        if (i >= lbl_803ED5F0 && i < lbl_803ED5F0 + lbl_803ED5F4 && !(lbl_803ED5FC[i].mFlags & 0x8000))
            fn_801D2BD0(lbl_803ED5FC[i].mpData);
    }
    lbl_803EBB88 = (void *)0xFEFEFEFE;
    fn_801D2BD0(lbl_803ED5FC);
    fn_801D2BD0(lbl_803ED60C);
}

int fn_801BB544(int id, int frameCache, int bigFile)
{
    return fn_801BB164(id, 0, frameCache, bigFile);
}

Object_801BC084 *fn_801BB570(int id, int heap, int align, int frameCache)
{
    Object_801BC084 *pFile = fn_801D2BB0(heap, fn_801F0C50(lbl_803EBB88, id), align, 0);

    if (pFile) {
        fn_801EFF80(lbl_803EBB88, id, pFile);
        if (frameCache)
            pFile->mFlags |= 0x200;
        else
            pFile->mFlags &= ~0x200;
        fn_801BA850(pFile);
    }
    return pFile;
}

int fn_801BB608(Object_801BC084 *pData, int frameCache)
{
    return fn_801BB164(-3, pData, frameCache, 0);
}

int fn_801BB638(int id, int frameCache)
{
    return fn_801BB544(id, frameCache, 0);
}

int fn_801BB65C(int id, int frameCache)
{
    int result = 0;
    int i;

    for (i = 0; i < lbl_803ED5F0; i++) {
        if (lbl_803ED5FC[i].mStatus == 0) {
            lbl_803ED5FC[i].mStatus = 2;
            lbl_803ED5FC[i].mId = id;
            lbl_803ED5FC[i].mUnknown1C = 1;
            lbl_803ED5FC[i].mFrameCache = frameCache;
            lbl_803ED60C[i].mSlot = i;
            lbl_803ED60C[i].mUnknown4 = 0;
            lbl_803ED5FC[i].mpData =
                fn_801EF548(lbl_803EBB88, id, lbl_803ED600, lbl_803ED604, fn_801BAE08, &lbl_803ED60C[i]);
            result = fn_801F7C88();
            break;
        }
    }
    if (i == lbl_803ED5F0)
        result = 0x140003;
    return result;
}

int fn_801BB74C(unsigned short slot, int id, int bigFile)
{
    unsigned short index = slot + lbl_803ED5F0;

    if (lbl_803ED5FC[index].mId == id && lbl_803ED5FC[index].mStatus != 0)
        return 0;
    switch (lbl_803ED5FC[index].mStatus) {
    case 2:
        while (fn_801BC044(slot) != 1) {
            if (lbl_803EBB94)
                fn_801F0F18(0);
            else
                fn_801F81AC();
            if (fn_801CB120())
                fn_801CAF24();
        }
    case 1:
        fn_801BAEAC(index);
    }
    lbl_803ED5FC[index].mStatus = 2;
    lbl_803ED5FC[index].mUnknown1C = 1;
    lbl_803ED5FC[index].mId = id;
    lbl_803ED60C[index].mSlot = index;
    lbl_803ED60C[index].mUnknown4 = bigFile;
    fn_801EFD2C(lbl_803EBB88, id, lbl_803ED600, lbl_803ED5FC[index].mpData, lbl_803ED604, fn_801BAE08,
                &lbl_803ED60C[index]);
    return fn_801F7C88();
}

unsigned short fn_801BB878(int id, Object_801BC084 *pData, int size, int bigFile, int flag)
{
    unsigned short slot = fn_801BAD98();

    if (slot != 0xFFFF) {
        lbl_803ED5FC[slot].mStatus = 2;
        lbl_803ED5FC[slot].mId = id;
        lbl_803ED5FC[slot].mUnknown1C = flag;
        lbl_803ED5FC[slot].mpData = pData;
        lbl_803ED5FC[slot].mSize = size;
        lbl_803ED60C[slot].mSlot = slot;
        lbl_803ED60C[slot].mUnknown4 = bigFile;
        fn_801EFD2C(lbl_803EBB88, id, lbl_803ED600, lbl_803ED5FC[slot].mpData, lbl_803ED604, fn_801BAE08,
                    &lbl_803ED60C[slot]);
    }
    return slot - lbl_803ED5F0 - lbl_803ED5F4;
}

int fn_801BB948(unsigned int slot)
{
    if (slot >= lbl_803ED608)
        return 0x140004;
    return fn_801BAEAC(slot + lbl_803ED5F0 + lbl_803ED5F4);
}

int fn_801BB994(int id)
{
    int result = 0;
    int i;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mId == id) {
            result = fn_801BAEAC(i);
            break;
        }
    }
    if (i == lbl_803ED5F8)
        result = 0x140004;
    return result;
}

unsigned int fn_801BBA18(int state, unsigned short objectType, Query_801BBA18 *pOut, unsigned int max)
{
    unsigned int count = 0;
    Cache_801BF870 *pCache = fn_801BF870(objectType, state);
    int i;
    int stateRef;

    if (pCache && !(pCache->mUnknown0 & 0x8000) && pCache->mUnknown2 >= 0) {
        pOut[0].mSlot = pCache->mUnknown0;
        count = 1;
        pOut[0].mStateRef = pCache->mUnknown2;
    } else {
        for (i = 0; i < lbl_803ED5F8; i++) {
            if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType) {
                stateRef = fn_801BAB48(fn_801BC084(i), state);
                if (stateRef != -1 && count < max) {
                    pOut[count].mStateRef = stateRef;
                    pOut[count].mSlot = i;
                    count++;
                }
            }
        }
        if (pCache) {
            if (count == 1) {
                pCache->mUnknown0 = pOut[0].mSlot;
                pCache->mUnknown2 = pOut[0].mStateRef;
            } else {
                pCache->mUnknown0 = -1;
                pCache->mUnknown2 = -1;
            }
        }
    }
    return count;
}

void fn_801BBB54(int objectType)
{
    int i;
    int j;
    int count;
    Cache_801BF870 *pCache;

    fn_801BF7BC(objectType);
    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType) {
            count = fn_801BACB0(fn_801BC084(i));
            for (j = 0; j < count; j++) {
                pCache = fn_801BF870(objectType, fn_801BACBC(fn_801BC084(i), j));
                if (pCache) {
                    if (pCache->mUnknown0 == -1) {
                        pCache->mUnknown0 = i;
                        pCache->mUnknown2 = j;
                    } else {
                        pCache->mUnknown2 = -1;
                        pCache->mUnknown0 = -2;
                    }
                }
            }
        }
    }
}

void fn_801BBC3C(int objectType, int state, List_801BAB88 *pList)
{
    Query_801BBA18 query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 380;
    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        fn_801BAB88(fn_801BC084(query[i].mSlot), query[i].mSlot, query[i].mStateRef, pList);
}

int fn_801BBCC8(int state, unsigned short slot)
{
    Query_801BBA18 query[32];
    unsigned int count;
    unsigned int i;
    Object_801BC084 *pFile = fn_801BC084(slot);
    unsigned short objectType;

    if (pFile == 0)
        return -1;
    objectType = pFile->mObjectType;
    if (!(state & 0x8000)) {
        count = fn_801BBA18(state, objectType, query, 32);
        for (i = 0; i < count; i++) {
            if (query[i].mSlot == slot)
                return i;
        }
    }
    return -1;
}

void *fn_801BBD5C(unsigned short state, unsigned short objectType)
{
    Query_801BBA18 query[32];
    unsigned int count;
    unsigned int i;
    void *pResult = 0;

    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        pResult = fn_801BAC9C(fn_801BC084(query[i].mSlot), query[i].mStateRef);
    return pResult;
}

void fn_801BBDCC(int objectType, int state, List_801BAC1C *pList)
{
    Query_801BBA18 query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 8;
    pList->mState = state;
    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        fn_801BAC1C(fn_801BC084(query[i].mSlot), query[i].mSlot, query[i].mStateRef, pList);
}

int fn_801BBE5C(int objectType, int fileNum)
{
    int i;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType &&
            lbl_803ED5FC[i].mpData->mFileNum == fileNum)
            return i;
    }
    return 0xFFFFFF;
}

int fn_801BBEC0(int slot, int mask)
{
    unsigned short parent = lbl_803ED5FC[slot].mParent;
    int part = lbl_803ED5FC[slot].mPart;
    int i;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mParent == parent && lbl_803ED5FC[i].mPart == part &&
            (lbl_803ED5FC[i].mpData->mFlags & mask) && slot != i)
            return i;
    }
    return 0xFFFFFF;
}

unsigned short fn_801BBF44(int objectType)
{
    int i;
    int j;
    Object_801BC084 *pFile;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType) {
            pFile = lbl_803ED5FC[i].mpData;
            for (j = 0; j < (unsigned short)pFile->mpStates->mCount; j++) {
                if ((pFile->mpStates->mStates[j].mId & 0x4000) && (pFile->mFlags & 8))
                    return pFile->mpStates->mStates[j].mId;
            }
        }
    }
    return 0xFFFF;
}

unsigned char fn_801BBFE4(int id)
{
    unsigned char status = 0;
    int i;

    for (i = 0; i < lbl_803ED5F0; i++) {
        if (lbl_803ED5FC[i].mId == id) {
            status = lbl_803ED5FC[i].mStatus;
            break;
        }
    }
    return status;
}

unsigned char fn_801BC044(unsigned short slot)
{
    return lbl_803ED5FC[(unsigned short)(slot + lbl_803ED5F0)].mStatus;
}

unsigned char fn_801BC060(unsigned short slot)
{
    return lbl_803ED5FC[(unsigned short)(slot + (lbl_803ED5F0 + lbl_803ED5F4))].mStatus;
}

Object_801BC084 *fn_801BC084(unsigned int slot)
{
    if (slot < lbl_803ED5F8 && lbl_803ED5FC[slot].mObjectType != 0x8000)
        return lbl_803ED5FC[slot].mpData;
    return 0;
}

int fn_801BC0C0(unsigned int slot)
{
    if (slot < lbl_803ED5F8)
        return lbl_803ED5FC[slot].mFrameCache;
    return 0;
}

void fn_801BC0E8(int slot, Info_801BC0E8 *pInfo)
{
    char *pBase = 0;
    Big_801BC0E8 *pBig = 0;
    Record_801BC0E8 *pRecord;
    Group_801BC0E8 *pGroup;
    Set_801BC0E8 *pSet;
    Part_801BC0E8 *pPart;
    Object_801BC084 *pFile;
    Buffer_801BB2D8 *pBuffer;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned int n;
    unsigned short m;
    int standalone;

    if (fn_801B9EF8() == 1) {
        pBase = (char *)lbl_803ED5FC[slot].mpData;
        pBig = (Big_801BC0E8 *)(pBase + *(int *)pBase + 4);
    } else if (fn_801B9EF8() == 2) {
        pBig = (Big_801BC0E8 *)lbl_803ED5FC[slot].mpData;
    }
    pRecord = (Record_801BC0E8 *)(pBase + 4);
    pBase = (char *)lbl_803ED5FC[slot].mpData;
    if (fn_801B9EF8() == 1) {
        for (i = 0; i < pInfo->mCount; i++) {
            pSet = &pInfo->mpSets[i];
            for (j = 0; j < pSet->mCount; j++) {
                pGroup = &pSet->mpGroups[j];
                pGroup->mpRecords = pRecord;
                for (k = 0; k < pGroup->mCount; k++) {
                    Record_801BC0E8 *pEntry = &pGroup->mpRecords[k];

                    pRecord++;
                    pEntry->mBlocks[0].mpUnknownC = pBase + (int)pEntry->mBlocks[0].mpUnknownC;
                    pEntry->mBlocks[1].mpUnknownC = pBase + (int)pEntry->mBlocks[1].mpUnknownC;
                    pEntry->mBlocks[2].mpUnknownC = pBase + (int)pEntry->mBlocks[2].mpUnknownC;
                    pEntry->mBlocks[3].mpUnknownC = pBase + (int)pEntry->mBlocks[3].mpUnknownC;
                    pEntry->mBlocks[4].mpUnknownC = pBase + (int)pEntry->mBlocks[4].mpUnknownC;
                    pEntry->mBlocks[5].mpUnknownC = pBase + (int)pEntry->mBlocks[5].mpUnknownC;
                    pEntry->mBlocks[6].mpUnknownC = pBase + (int)pEntry->mBlocks[6].mpUnknownC;
                    pEntry->mBlocks[7].mpUnknownC = pBase + (int)pEntry->mBlocks[7].mpUnknownC;
                    pEntry->mBlocks[8].mpUnknownC = pBase + (int)pEntry->mBlocks[8].mpUnknownC;
                    pEntry->mBlocks[9].mpUnknownC = pBase + (int)pEntry->mBlocks[9].mpUnknownC;
                    pEntry->mBlocks[10].mpUnknownC = pBase + (int)pEntry->mBlocks[10].mpUnknownC;
                    pEntry->mBlocks[11].mpUnknownC = pBase + (int)pEntry->mBlocks[11].mpUnknownC;
                    pEntry->mBlocks[12].mpUnknownC = pBase + (int)pEntry->mBlocks[12].mpUnknownC;
                    pEntry->mBlocks[13].mpUnknownC = pBase + (int)pEntry->mBlocks[13].mpUnknownC;
                    pEntry->mBlocks[14].mpUnknownC = pBase + (int)pEntry->mBlocks[14].mpUnknownC;
                }
            }
        }
    }
    lbl_803ED5FC[slot].mParent = -1;
    lbl_803ED5FC[slot].mObjectType = 0x8000;
    for (n = 0; n < pBig->mCount; n++) {
        for (m = 0; m <= 1; m++) {
            pPart = &pBig->mEntries[n].mParts[m];
            standalone = 1;
            if (pPart->mSize) {
                pPart->mpFile = (Object_801BC084 *)(pBase + (int)pPart->mpFile);
                switch (m) {
                case 0:
                    if (pPart->mTag == 0x4246434D)
                        pPart->mpFile->mFlags |= 0x800;
                    break;
                case 1:
                    standalone = 0;
                    if (pPart->mTag == 0x4246464D)
                        pPart->mpFile->mFlags |= 0x400;
                    break;
                }
                pFile = pPart->mpFile;
                pFile->mObjectType = pPart->mObjectType;
                if (lbl_803ED5FC[slot].mUnknown1C)
                    pFile->mFlags &= ~0x2000;
                else
                    pFile->mFlags |= 0x2000;
                fn_801BA850(pFile);
                pBuffer = &lbl_803ED5FC[fn_801BAD98()];
                pBuffer->mpData = pFile;
                pBuffer->mSize = pPart->mSize;
                pBuffer->mPart = n;
                pBuffer->mParent = slot;
                pBuffer->mObjectType = fn_801BAB24(pFile);
                if (standalone)
                    pBuffer->mObjectType |= 0x4000;
                pBuffer->mStatus = 1;
                pPart->mpFile->mFlags |= 0x100;
            }
        }
    }
}

void fn_801BC440(Info_801BC0E8 *pDest, Info_801BC0E8 *pSource)
{
    unsigned short i;
    unsigned short j;
    unsigned short k;
    Set_801BC0E8 *pSourceSet;
    Set_801BC0E8 *pDestSet;
    Group_801BC0E8 *pSourceGroup;
    Group_801BC0E8 *pDestGroup;
    Record_801BC0E8 *pSourceRecord;
    Record_801BC0E8 *pDestRecord;

    for (i = 0; i < pSource->mCount; i++) {
        pSourceSet = &pSource->mpSets[i];
        pDestSet = &pDest->mpSets[i];
        for (j = 0; j < pSourceSet->mCount; j++) {
            pSourceGroup = &pSourceSet->mpGroups[j];
            pDestGroup = &pDestSet->mpGroups[j];
            pDestGroup->mpRecords = pSourceGroup->mpRecords;
            for (k = 0; k < pSourceGroup->mCount; k++) {
                pSourceRecord = &pSourceGroup->mpRecords[k];
                pDestRecord = &pDestGroup->mpRecords[k];
                pDestRecord->mBlocks[0].mpUnknownC = pSourceRecord->mBlocks[0].mpUnknownC;
                pDestRecord->mBlocks[1].mpUnknownC = pSourceRecord->mBlocks[1].mpUnknownC;
                pDestRecord->mBlocks[2].mpUnknownC = pSourceRecord->mBlocks[2].mpUnknownC;
                pDestRecord->mBlocks[3].mpUnknownC = pSourceRecord->mBlocks[3].mpUnknownC;
                pDestRecord->mBlocks[4].mpUnknownC = pSourceRecord->mBlocks[4].mpUnknownC;
                pDestRecord->mBlocks[5].mpUnknownC = pSourceRecord->mBlocks[5].mpUnknownC;
                pDestRecord->mBlocks[6].mpUnknownC = pSourceRecord->mBlocks[6].mpUnknownC;
                pDestRecord->mBlocks[7].mpUnknownC = pSourceRecord->mBlocks[7].mpUnknownC;
                pDestRecord->mBlocks[8].mpUnknownC = pSourceRecord->mBlocks[8].mpUnknownC;
                pDestRecord->mBlocks[9].mpUnknownC = pSourceRecord->mBlocks[9].mpUnknownC;
                pDestRecord->mBlocks[10].mpUnknownC = pSourceRecord->mBlocks[10].mpUnknownC;
                pDestRecord->mBlocks[11].mpUnknownC = pSourceRecord->mBlocks[11].mpUnknownC;
                pDestRecord->mBlocks[12].mpUnknownC = pSourceRecord->mBlocks[12].mpUnknownC;
                pDestRecord->mBlocks[13].mpUnknownC = pSourceRecord->mBlocks[13].mpUnknownC;
                pDestRecord->mBlocks[14].mpUnknownC = pSourceRecord->mBlocks[14].mpUnknownC;
            }
        }
    }
}

void fn_801BC57C(int slot)
{
    Big_801BC57C *pBig = (Big_801BC57C *)lbl_803ED5FC[slot].mpData;
    Entry_801BC57C *pEntry = &pBig->mFirst;
    Object_801BC084 *pFile;
    Buffer_801BB2D8 *pBuffer;
    unsigned int i;

    lbl_803ED5FC[slot].mParent = -1;
    lbl_803ED5FC[slot].mObjectType = 0x8000;
    for (i = 0; i < pBig->mCount; i++) {
        pFile = &pEntry->mFile;
        pFile->mObjectType = pEntry->mObjectType;
        fn_801BA850(pFile);
        pBuffer = &lbl_803ED5FC[fn_801BAD98()];
        pBuffer->mpData = pFile;
        pBuffer->mSize = pEntry->mSize;
        pBuffer->mPart = i;
        pBuffer->mParent = slot;
        pBuffer->mObjectType = fn_801BAB24(pFile) | 0x4000;
        pBuffer->mStatus = 1;
        pEntry = (Entry_801BC57C *)((char *)pFile + pEntry->mSize);
        pEntry->mFile.mFlags |= 0x100;
    }
}

void fn_801BC64C(void (*pFunc)(int, int))
{
    lbl_803EBB8C = pFunc;
}

void *fn_801BC654(void)
{
    return lbl_803EBB88;
}
