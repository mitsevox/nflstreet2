#include "engine/cu_801B9F00.h"
#include "engine/cu_801BA818.h"
#include "engine/fn_801EFD2C.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"

/* 32-byte slot record of the table at lbl_803ED5FC. */
typedef struct Buffer_801BB2D8 {
    int mId;
    int mSize;
    int mPart;
    AnimFileFormat_t *mpData;
    unsigned short mFlags;
    unsigned char mStatus;
    unsigned char mUnknown13;
    unsigned short mObjectType;
    unsigned short mParent;
    struct Cache_801BFCC4 *mpFrameCache;
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
} Buffer_801BB2D8;

typedef struct Request_801BAE08 {
    int mSlot;
    struct Info_801BC0E8 *mpInfo;
} Request_801BAE08;

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
    AnimFileFormat_t *mpFile;
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
    AnimFileFormat_t mFile;
} Entry_801BC57C;

typedef struct Big_801BC57C {
    unsigned char mUnknown0[12];
    unsigned int mCount;
    Entry_801BC57C mFirst;
} Big_801BC57C;

extern void *lbl_803EBB88;
extern void (*lbl_803EBB8C)(int slot, Info_801BC0E8 *pInfo);
extern void (*lbl_803EBB90)(AnimFileFormat_t *pFile);
extern unsigned char lbl_803EBB94;
extern int lbl_803ED5F0;
extern int lbl_803ED5F4;
extern int lbl_803ED5F8;
extern Buffer_801BB2D8 *lbl_803ED5FC;
extern int lbl_803ED600;
extern int lbl_803ED604;
extern int lbl_803ED608;
extern Request_801BAE08 *lbl_803ED60C;

int fn_801F0F18(int a);
void fn_801F81AC(void);
int fn_801F0C50(void *pArchive, int id);
int fn_801EFF80(void *pArchive, int id, void *pDest);
AnimFileFormat_t *fn_801EF548(void *pArchive, int id, int heap, int arg,
                              void (*pCallback)(int, int, int, int, Request_801BAE08 *), Request_801BAE08 *pRequest);
int fn_801CB120(void);
void fn_801CAF24(void);

unsigned short fn_801BAD98(void);
int fn_801BAEAC(int slot);
int fn_801BB164(int id, AnimFileFormat_t *pData, struct Cache_801BFCC4 *pFrameCache, Info_801BC0E8 *pInfo);
int fn_801BB544(int id, struct Cache_801BFCC4 *pFrameCache, Info_801BC0E8 *pInfo);
unsigned int fn_801BBA18(int state, unsigned short objectType, Pair_801BF7BC *pOut, unsigned int max);
unsigned char fn_801BBFE4(int id);
unsigned char fn_801BC044(unsigned short slot);
unsigned char fn_801BC060(unsigned short slot);

unsigned short fn_801BAD98(void)
{
    unsigned short slot = 0xFFFF;
    unsigned int i;

    for (i = lbl_803ED5F0 + lbl_803ED5F4; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 0) {
            slot = i;
            break;
        }
    }
    return slot;
}

void fn_801BAE08(int a, int b, int c, int d, Request_801BAE08 *pRequest)
{
    int slot = pRequest->mSlot;

    if (pRequest->mpInfo) {
        lbl_803EBB8C(slot, pRequest->mpInfo);
    } else {
        fn_801BA850(lbl_803ED5FC[slot].mpData);
        lbl_803ED5FC[slot].mParent = -1;
        lbl_803ED5FC[slot].mObjectType = fn_801BAB24(fn_801BC084(slot));
    }
    lbl_803ED5FC[slot].mStatus = 1;
}

void fn_801BAEA4(void (*pFunc)(AnimFileFormat_t *))
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
                lbl_803ED5FC[slot].mSize = 0;
                lbl_803ED5FC[slot].mpData = 0;
            }
        }
        if (lbl_803ED5FC[slot].mObjectType == 0x8000) {
            for (i = lbl_803ED5F0 + lbl_803ED5F4; i < lbl_803ED5F8; i++) {
                if (lbl_803ED5FC[i].mParent == slot) {
                    lbl_803ED5FC[i].mSize = 0;
                    lbl_803ED5FC[i].mpData = 0;
                    lbl_803ED5FC[i].mUnknown13 = 0;
                    lbl_803ED5FC[i].mStatus = 0;
                    lbl_803ED5FC[i].mParent = -1;
                    fn_801BF7BC(lbl_803ED5FC[i].mObjectType & ~0x4000);
                }
            }
        }
        fn_801BF7BC(lbl_803ED5FC[slot].mObjectType);
        lbl_803ED5FC[slot].mUnknown13 = 0;
        lbl_803ED5FC[slot].mStatus = 0;
        lbl_803ED5FC[slot].mParent = -1;
        lbl_803ED5FC[slot].mObjectType = -1;
    }
    return result;
}

int fn_801BB164(int id, AnimFileFormat_t *pData, struct Cache_801BFCC4 *pFrameCache, Info_801BC0E8 *pInfo)
{
    int result = 0;
    int i;

    for (i = 0; i < lbl_803ED5F0; i++) {
        if (lbl_803ED5FC[i].mStatus == 0) {
            lbl_803ED5FC[i].mStatus = 1;
            lbl_803ED5FC[i].mId = id;
            if (pData == 0) {
                lbl_803ED5FC[i].mpData = (void *)fn_801EF390(lbl_803EBB88, id, lbl_803ED600);
                result = fn_801F7C88();
            } else {
                lbl_803ED5FC[i].mpData = pData;
            }
            lbl_803ED5FC[i].mpFrameCache = pFrameCache;
            if (pFrameCache)
                lbl_803ED5FC[i].mpData->flags |= 0x200;
            else
                lbl_803ED5FC[i].mpData->flags &= ~0x200;
            if (pData == 0) {
                if (pInfo) {
                    lbl_803EBB8C(i, pInfo);
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

    lbl_803EBB88 = pConfig->mpArchive;
    lbl_803ED600 = pConfig->mUnknown4;
    lbl_803ED604 = pConfig->mUnknown10;
    lbl_803ED5F0 = pConfig->mUnknown8;
    lbl_803ED5F4 = pConfig->mUnknownA;
    lbl_803ED608 = pConfig->mUnknownC;
    lbl_803ED5F8 = lbl_803ED5F0 + lbl_803ED5F4 + lbl_803ED608;
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
                lbl_803ED5FC[i].mSize = 0;
                lbl_803ED5FC[i].mpData = 0;
                lbl_803ED5FC[i].mFlags = 0;
            }
            lbl_803ED5FC[i].mUnknown13 = 0;
            lbl_803ED5FC[i].mStatus = 0;
            lbl_803ED5FC[i].mId = 0;
            lbl_803ED5FC[i].mParent = -1;
            lbl_803ED5FC[i].mObjectType = -1;
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

int fn_801BB544(int id, struct Cache_801BFCC4 *pFrameCache, Info_801BC0E8 *pInfo)
{
    return fn_801BB164(id, 0, pFrameCache, pInfo);
}

AnimFileFormat_t *fn_801BB570(int id, int heap, int align, int frameCache)
{
    AnimFileFormat_t *pFile = fn_801D2BB0(heap, fn_801F0C50(lbl_803EBB88, id), align, 0);

    if (pFile) {
        fn_801EFF80(lbl_803EBB88, id, pFile);
        if (frameCache)
            pFile->flags |= 0x200;
        else
            pFile->flags &= ~0x200;
        fn_801BA850(pFile);
    }
    return pFile;
}

int fn_801BB608(AnimFileFormat_t *pData, struct Cache_801BFCC4 *pFrameCache)
{
    return fn_801BB164(-3, pData, pFrameCache, 0);
}

int fn_801BB638(int id, struct Cache_801BFCC4 *pFrameCache)
{
    return fn_801BB544(id, pFrameCache, 0);
}

int fn_801BB65C(int id, struct Cache_801BFCC4 *pFrameCache)
{
    int result = 0;
    int i;

    for (i = 0; i < lbl_803ED5F0; i++) {
        if (lbl_803ED5FC[i].mStatus == 0) {
            lbl_803ED5FC[i].mStatus = 2;
            lbl_803ED5FC[i].mId = id;
            lbl_803ED5FC[i].mpFrameCache = pFrameCache;
            lbl_803ED5FC[i].mUnknown1C = 1;
            lbl_803ED60C[i].mSlot = i;
            lbl_803ED60C[i].mpInfo = 0;
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

int fn_801BB74C(unsigned short slot, int id, Info_801BC0E8 *pInfo)
{
    unsigned short index = slot + lbl_803ED5F0;
    int result = 0;

    if (lbl_803ED5FC[index].mId != id || lbl_803ED5FC[index].mStatus == 0) {
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
        lbl_803ED60C[index].mpInfo = pInfo;
        fn_801EFD2C(lbl_803EBB88, id, lbl_803ED600, lbl_803ED5FC[index].mpData, lbl_803ED604, fn_801BAE08,
                    &lbl_803ED60C[index]);
        result = fn_801F7C88();
    }
    return result;
}

unsigned short fn_801BB878(int id, AnimFileFormat_t *pData, int size, Info_801BC0E8 *pInfo, int flag)
{
    unsigned short slot = fn_801BAD98();

    if (slot != 0xFFFF) {
        lbl_803ED5FC[slot].mStatus = 2;
        lbl_803ED5FC[slot].mId = id;
        lbl_803ED5FC[slot].mpData = pData;
        lbl_803ED5FC[slot].mSize = size;
        lbl_803ED5FC[slot].mUnknown1C = flag;
        lbl_803ED60C[slot].mSlot = slot;
        lbl_803ED60C[slot].mpInfo = pInfo;
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

unsigned int fn_801BBA18(int state, unsigned short objectType, Pair_801BF7BC *pOut, unsigned int max)
{
    unsigned int count = 0;
    Pair_801BF7BC *pCache = fn_801BF870(objectType, state);
    int i;
    int stateRef;

    if (pCache && !(pCache->mUnknown0 & 0x8000) && pCache->mUnknown2 >= 0) {
        pOut[0].mUnknown0 = pCache->mUnknown0;
        count = 1;
        pOut[0].mUnknown2 = pCache->mUnknown2;
    } else {
        for (i = 0; i < lbl_803ED5F8; i++) {
            if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType) {
                stateRef = fn_801BAB48(fn_801BC084(i), state);
                if (stateRef != -1 && count < max) {
                    pOut[count].mUnknown2 = stateRef;
                    pOut[count].mUnknown0 = i;
                    count++;
                }
            }
        }
        if (pCache) {
            if (count == 1) {
                pCache->mUnknown0 = pOut[0].mUnknown0;
                pCache->mUnknown2 = pOut[0].mUnknown2;
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
    Pair_801BF7BC *pCache;

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
    Pair_801BF7BC query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 380;
    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        fn_801BAB88(fn_801BC084(query[i].mUnknown0), query[i].mUnknown0, query[i].mUnknown2, pList);
}

int fn_801BBCC8(int state, unsigned int slot)
{
    Pair_801BF7BC query[32];
    unsigned int count;
    unsigned int i;
    AnimFileFormat_t *pFile = fn_801BC084(slot);
    unsigned short objectType;

    if (pFile == 0)
        return -1;
    objectType = pFile->objectType;
    if (!(state & 0x8000)) {
        count = fn_801BBA18(state, objectType, query, 32);
        for (i = 0; i < count; i++) {
            if (query[i].mUnknown0 == slot)
                return i;
        }
    }
    return -1;
}

void *fn_801BBD5C(unsigned short state, unsigned short objectType)
{
    Pair_801BF7BC query[32];
    unsigned int count;
    unsigned int i;
    void *pResult = 0;

    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        pResult = fn_801BAC9C(fn_801BC084(query[i].mUnknown0), query[i].mUnknown2);
    return pResult;
}

void fn_801BBDCC(int objectType, int state, List_801BAC1C *pList)
{
    Pair_801BF7BC query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 8;
    pList->mState = state;
    count = fn_801BBA18(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        fn_801BAC1C(fn_801BC084(query[i].mUnknown0), query[i].mUnknown0, query[i].mUnknown2, pList);
}

int fn_801BBE5C(int objectType, int fileNum)
{
    int i;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType &&
            lbl_803ED5FC[i].mpData->fileNum == fileNum)
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
            (lbl_803ED5FC[i].mpData->flags & mask) && slot != i)
            return i;
    }
    return 0xFFFFFF;
}

unsigned short fn_801BBF44(int objectType)
{
    int i;
    int j;
    AnimFileFormat_t *pFile;

    for (i = 0; i < lbl_803ED5F8; i++) {
        if (lbl_803ED5FC[i].mStatus == 1 && lbl_803ED5FC[i].mObjectType == objectType) {
            pFile = lbl_803ED5FC[i].mpData;
            for (j = 0; j < (unsigned short)pFile->states->mCount; j++) {
                if ((pFile->states->mStates[j].mId & 0x4000) && (pFile->flags & 8))
                    return pFile->states->mStates[j].mId;
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

AnimFileFormat_t *fn_801BC084(unsigned int slot)
{
    if (slot < lbl_803ED5F8 && lbl_803ED5FC[slot].mObjectType != 0x8000)
        return lbl_803ED5FC[slot].mpData;
    return 0;
}

struct Cache_801BFCC4 *fn_801BC0C0(unsigned int slot)
{
    if (slot < lbl_803ED5F8)
        return lbl_803ED5FC[slot].mpFrameCache;
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
    AnimFileFormat_t *pFile;
    Buffer_801BB2D8 *pBuffer;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned int n;
    unsigned short m;
    int setTypeBit;

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
            setTypeBit = 1;
            if (pPart->mSize) {
                pPart->mpFile = (AnimFileFormat_t *)(pBase + (int)pPart->mpFile);
                switch (m) {
                case 0:
                    if (pPart->mTag == 0x4246434D)
                        pPart->mpFile->flags |= 0x800;
                    break;
                case 1:
                    setTypeBit = 0;
                    if (pPart->mTag == 0x4246464D)
                        pPart->mpFile->flags |= 0x400;
                    break;
                }
                pFile = pPart->mpFile;
                pFile->objectType = pPart->mObjectType;
                if (lbl_803ED5FC[slot].mUnknown1C)
                    pFile->flags &= ~0x2000;
                else
                    pFile->flags |= 0x2000;
                fn_801BA850(pFile);
                pBuffer = &lbl_803ED5FC[fn_801BAD98()];
                pBuffer->mpData = pFile;
                pBuffer->mSize = pPart->mSize;
                pBuffer->mPart = n;
                pBuffer->mParent = slot;
                pBuffer->mObjectType = fn_801BAB24(pFile);
                if (setTypeBit)
                    pBuffer->mObjectType |= 0x4000;
                pBuffer->mStatus = 1;
                pPart->mpFile->flags |= 0x100;
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

void fn_801BC57C(int slot, Info_801BC0E8 *pInfo)
{
    Big_801BC57C *pBig = (Big_801BC57C *)lbl_803ED5FC[slot].mpData;
    Entry_801BC57C *pEntry = &pBig->mFirst;
    AnimFileFormat_t *pFile;
    Buffer_801BB2D8 *pBuffer;
    unsigned int i;

    lbl_803ED5FC[slot].mParent = -1;
    lbl_803ED5FC[slot].mObjectType = 0x8000;
    for (i = 0; i < pBig->mCount; i++) {
        pFile = &pEntry->mFile;
        pFile->objectType = pEntry->mObjectType;
        fn_801BA850(pFile);
        pBuffer = &lbl_803ED5FC[fn_801BAD98()];
        pBuffer->mpData = pFile;
        pBuffer->mSize = pEntry->mSize;
        pBuffer->mPart = i;
        pBuffer->mParent = slot;
        pBuffer->mObjectType = fn_801BAB24(pFile) | 0x4000;
        pBuffer->mStatus = 1;
        pEntry = (Entry_801BC57C *)((char *)pFile + pEntry->mSize);
        pEntry->mFile.flags |= 0x100;
    }
}

void fn_801BC64C(void (*pFunc)(int, Info_801BC0E8 *))
{
    lbl_803EBB8C = pFunc;
}

void *fn_801BC654(void)
{
    return lbl_803EBB88;
}
