/* Animation file manager: the slot table of resident, dynamic and virtual animation files, their
   synchronous and asynchronous loading, unloading and relocation, the per-object state queries
   (with the state cache), and the unpacking of big files into virtual slots. */
#include "engine/animchan.h"
#include "engine/animemot.h"
#include "engine/ResCopyAsyncToBuffer.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"
#include "game/ResLoad.h"

/* 32-byte slot record of the table at _AnimFile_pBufferInfo. */
typedef struct AnimFileBufferInfo_t {
    int mId;
    int mSize;
    int mPart;
    AnimFileFormat_t *mpData;
    unsigned short mFlags;
    unsigned char mStatus;
    unsigned char mUnknown13;
    unsigned short mObjectType;
    unsigned short mParent;
    struct AnimFrameCache_t *mpFrameCache;
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
} AnimFileBufferInfo_t;

typedef struct AnimFileRequest_t {
    int mSlot;
    struct AnimFileBigInfo_t *mpInfo;
} AnimFileRequest_t;

typedef struct AnimFileBigBlock_t {
    unsigned char mUnknown0[12];
    char *mpUnknownC;
} AnimFileBigBlock_t;

typedef struct AnimFileBigRecord_t {
    unsigned char mUnknown0[12];
    AnimFileBigBlock_t mBlocks[15];
} AnimFileBigRecord_t;

typedef struct AnimFileBigGroup_t {
    unsigned short mUnknown0;
    unsigned short mCount;
    AnimFileBigRecord_t *mpRecords;
} AnimFileBigGroup_t;

typedef struct AnimFileBigSet_t {
    unsigned short mUnknown0;
    unsigned short mCount;
    AnimFileBigGroup_t *mpGroups;
} AnimFileBigSet_t;

typedef struct AnimFileBigInfo_t {
    unsigned char mUnknown0[13];
    unsigned char mCount;
    unsigned char mUnknownE[2];
    AnimFileBigSet_t *mpSets;
} AnimFileBigInfo_t;

typedef struct AnimFileNewBigPart_t {
    unsigned short mUnknown0;
    unsigned short mObjectType;
    int mTag;
    int mSize;
    AnimFileFormat_t *mpFile;
} AnimFileNewBigPart_t;

typedef struct AnimFileNewBigEntry_t {
    AnimFileNewBigPart_t mParts[2];
} AnimFileNewBigEntry_t;

typedef struct AnimFileNewBigFile_t {
    unsigned char mUnknown0[12];
    unsigned int mCount;
    AnimFileNewBigEntry_t mEntries[1];
} AnimFileNewBigFile_t;

typedef struct AnimFileBigEntry_t {
    unsigned short mUnknown0;
    unsigned short mObjectType;
    int mSize;
    AnimFileFormat_t mFile;
} AnimFileBigEntry_t;

typedef struct AnimFileBigFile_t {
    unsigned char mUnknown0[12];
    unsigned int mCount;
    AnimFileBigEntry_t mFirst;
} AnimFileBigFile_t;

static void *_AnimFile_ResFile = (void *)0xFEFEFEFE;
static void (*_AnimFile_RelocateBigFileFunc)(int slot, AnimFileBigInfo_t *pInfo) = 0;
static void (*_AnimFile_FreeFunc)(AnimFileFormat_t *pFile) = 0;
static unsigned char _AnimFile_bResSync = 0;
static int _AnimFile_NumResBuffers;
static int _AnimFile_NumDynBuffers;
static int _AnimFile_NumBuffers;
static AnimFileBufferInfo_t *_AnimFile_pBufferInfo;
static int _AnimFile_MemoryHeap;
static int _AnimFile_AsyncPriority;
static int _AnimFile_NumVirtBuffers;
static AnimFileRequest_t *_AnimFile_DefaultUserDataBuffer;

int ResSync(int a);
void fn_801F81AC(void);
int ResGetSize(void *pArchive, int id);
int ResCopyToBuffer(void *pArchive, int id, void *pDest);
AnimFileFormat_t *ResLoadAsync(void *pArchive, int id, int heap, int arg,
                              void (*pCallback)(int, int, int, int, AnimFileRequest_t *), AnimFileRequest_t *pRequest);
int FileHostCheckActive(void);
void FileDebugProcess(void);

static unsigned short _AnimFileGetFreeVirtualSlot(void);
static int _AnimFileUnloadFileUnloadBySlot(int slot);
static int _AnimFileLoadSeqResident(int id, AnimFileFormat_t *pData, struct AnimFrameCache_t *pFrameCache, AnimFileBigInfo_t *pInfo);
int AnimFileLoadSeqResident(int id, struct AnimFrameCache_t *pFrameCache, AnimFileBigInfo_t *pInfo);
static unsigned int _AnimFileStateQuery(int state, unsigned short objectType, AnimCacheStateInfo_t *pOut, unsigned int max);
unsigned char AnimFileGetResidentLoadStatus(int id);
unsigned char AnimFileGetDynamicLoadStatus(unsigned short slot);
unsigned char AnimFileGetVirtualLoadStatus(unsigned short slot);

static unsigned short _AnimFileGetFreeVirtualSlot(void)
{
    unsigned short slot = 0xFFFF;
    unsigned int i;

    for (i = _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 0) {
            slot = i;
            break;
        }
    }
    return slot;
}

static void _AnimfileResourceCallback(int a, int b, int c, int d, AnimFileRequest_t *pRequest)
{
    int slot = pRequest->mSlot;

    if (pRequest->mpInfo) {
        _AnimFile_RelocateBigFileFunc(slot, pRequest->mpInfo);
    } else {
        AnimFileRelocate(_AnimFile_pBufferInfo[slot].mpData);
        _AnimFile_pBufferInfo[slot].mParent = -1;
        _AnimFile_pBufferInfo[slot].mObjectType = AnimFileGetObjectType(AnimFileGetPtrFromSlot(slot));
    }
    _AnimFile_pBufferInfo[slot].mStatus = 1;
}

void AnimFileSetFreeFunc(void (*pFunc)(AnimFileFormat_t *))
{
    _AnimFile_FreeFunc = pFunc;
}

static int _AnimFileUnloadFileUnloadBySlot(int slot)
{
    int result = 0;
    unsigned int i;

    if (_AnimFile_pBufferInfo[slot].mStatus != 0) {
        if (slot < _AnimFile_NumResBuffers) {
            if (_AnimFile_pBufferInfo[slot].mStatus == 2) {
                while (AnimFileGetResidentLoadStatus(_AnimFile_pBufferInfo[slot].mId) != 1) {
                    if (_AnimFile_bResSync)
                        ResSync(0);
                    else
                        fn_801F81AC();
                }
            }
        } else if (slot < _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers) {
            if (_AnimFile_pBufferInfo[slot].mStatus == 2) {
                while (AnimFileGetDynamicLoadStatus(slot - _AnimFile_NumResBuffers) != 1) {
                    if (_AnimFile_bResSync)
                        ResSync(0);
                    else
                        fn_801F81AC();
                }
            }
        } else {
            if (_AnimFile_pBufferInfo[slot].mStatus == 2) {
                while (AnimFileGetVirtualLoadStatus(slot - _AnimFile_NumResBuffers - _AnimFile_NumDynBuffers) != 1) {
                    if (_AnimFile_bResSync)
                        ResSync(0);
                    else
                        fn_801F81AC();
                }
            }
        }
        if (_AnimFile_pBufferInfo[slot].mParent == 0xFFFF) {
            if (_AnimFile_FreeFunc && !(_AnimFile_pBufferInfo[slot].mObjectType & 0x8000) && _AnimFile_pBufferInfo[slot].mId != -3)
                _AnimFile_FreeFunc(_AnimFile_pBufferInfo[slot].mpData);
            if (slot < _AnimFile_NumResBuffers && _AnimFile_pBufferInfo[slot].mId != -1 && _AnimFile_pBufferInfo[slot].mId != -3)
                result = ResUnLoad(_AnimFile_ResFile, _AnimFile_pBufferInfo[slot].mId);
            if (slot >= _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers) {
                _AnimFile_pBufferInfo[slot].mSize = 0;
                _AnimFile_pBufferInfo[slot].mpData = 0;
            }
        }
        if (_AnimFile_pBufferInfo[slot].mObjectType == 0x8000) {
            for (i = _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers; i < _AnimFile_NumBuffers; i++) {
                if (_AnimFile_pBufferInfo[i].mParent == slot) {
                    _AnimFile_pBufferInfo[i].mSize = 0;
                    _AnimFile_pBufferInfo[i].mpData = 0;
                    _AnimFile_pBufferInfo[i].mUnknown13 = 0;
                    _AnimFile_pBufferInfo[i].mStatus = 0;
                    _AnimFile_pBufferInfo[i].mParent = -1;
                    AnimCacheInvalidate(_AnimFile_pBufferInfo[i].mObjectType & ~0x4000);
                }
            }
        }
        AnimCacheInvalidate(_AnimFile_pBufferInfo[slot].mObjectType);
        _AnimFile_pBufferInfo[slot].mUnknown13 = 0;
        _AnimFile_pBufferInfo[slot].mStatus = 0;
        _AnimFile_pBufferInfo[slot].mParent = -1;
        _AnimFile_pBufferInfo[slot].mObjectType = -1;
    }
    return result;
}

static int _AnimFileLoadSeqResident(int id, AnimFileFormat_t *pData, struct AnimFrameCache_t *pFrameCache, AnimFileBigInfo_t *pInfo)
{
    int result = 0;
    int i;

    for (i = 0; i < _AnimFile_NumResBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 0) {
            _AnimFile_pBufferInfo[i].mStatus = 1;
            _AnimFile_pBufferInfo[i].mId = id;
            if (pData == 0) {
                _AnimFile_pBufferInfo[i].mpData = (void *)ResLoad(_AnimFile_ResFile, id, _AnimFile_MemoryHeap);
                result = fn_801F7C88();
            } else {
                _AnimFile_pBufferInfo[i].mpData = pData;
            }
            _AnimFile_pBufferInfo[i].mpFrameCache = pFrameCache;
            if (pFrameCache)
                _AnimFile_pBufferInfo[i].mpData->flags |= 0x200;
            else
                _AnimFile_pBufferInfo[i].mpData->flags &= ~0x200;
            // FAKEMATCH: the parent/type pair is written in both arms (duplicated) to give the target's hoisted -1
            if (pData == 0) {
                if (pInfo) {
                    _AnimFile_RelocateBigFileFunc(i, pInfo);
                } else {
                    AnimFileRelocate(_AnimFile_pBufferInfo[i].mpData);
                    _AnimFile_pBufferInfo[i].mParent = -1;
                    _AnimFile_pBufferInfo[i].mObjectType = AnimFileGetObjectType(AnimFileGetPtrFromSlot((unsigned short)i));
                }
            } else {
                _AnimFile_pBufferInfo[i].mParent = -1;
                _AnimFile_pBufferInfo[i].mObjectType = AnimFileGetObjectType(AnimFileGetPtrFromSlot((unsigned short)i));
            }
            break;
        }
    }
    if (i == _AnimFile_NumResBuffers)
        result = 0x140003;
    return result;
}

int AnimFileStart(AnimFileConfig_t *pConfig)
{
    int i;

    _AnimFile_ResFile = pConfig->mpArchive;
    _AnimFile_MemoryHeap = pConfig->mUnknown4;
    _AnimFile_AsyncPriority = pConfig->mUnknown10;
    _AnimFile_NumResBuffers = pConfig->mUnknown8;
    _AnimFile_NumDynBuffers = pConfig->mUnknownA;
    _AnimFile_NumVirtBuffers = pConfig->mUnknownC;
    _AnimFile_NumBuffers = _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers + _AnimFile_NumVirtBuffers;
    _AnimFile_pBufferInfo = fn_801D2BB0(_AnimFile_MemoryHeap, _AnimFile_NumBuffers * sizeof(AnimFileBufferInfo_t), 0, 0);
    _AnimFile_DefaultUserDataBuffer = fn_801D2BB0(_AnimFile_MemoryHeap, _AnimFile_NumBuffers * sizeof(AnimFileRequest_t), 0, 0);
    if (_AnimFile_pBufferInfo) {
        for (i = 0; i < _AnimFile_NumBuffers; i++) {
            if (i >= _AnimFile_NumResBuffers && i < _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers) {
                _AnimFile_pBufferInfo[i].mSize = pConfig->mpBuffers[i - _AnimFile_NumResBuffers].mSize;
                _AnimFile_pBufferInfo[i].mFlags = pConfig->mpBuffers[i - _AnimFile_NumResBuffers].mFlags;
                if (pConfig->mpBuffers[i - _AnimFile_NumResBuffers].mFlags & 0x8000)
                    _AnimFile_pBufferInfo[i].mpData = pConfig->mpBuffers[i - _AnimFile_NumResBuffers].mpData;
                else
                    _AnimFile_pBufferInfo[i].mpData = fn_801D2BB0(_AnimFile_MemoryHeap, _AnimFile_pBufferInfo[i].mSize, 0, 0);
            } else {
                _AnimFile_pBufferInfo[i].mSize = 0;
                _AnimFile_pBufferInfo[i].mpData = 0;
                _AnimFile_pBufferInfo[i].mFlags = 0;
            }
            _AnimFile_pBufferInfo[i].mUnknown13 = 0;
            _AnimFile_pBufferInfo[i].mStatus = 0;
            _AnimFile_pBufferInfo[i].mId = 0;
            _AnimFile_pBufferInfo[i].mParent = -1;
            _AnimFile_pBufferInfo[i].mObjectType = -1;
        }
        return 0;
    }
    return fn_801F7C88();
}

void AnimFileStop(void)
{
    int i;

    ResSync(0);
    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1)
            _AnimFileUnloadFileUnloadBySlot(i);
        if (i >= _AnimFile_NumResBuffers && i < _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers && !(_AnimFile_pBufferInfo[i].mFlags & 0x8000))
            fn_801D2BD0(_AnimFile_pBufferInfo[i].mpData);
    }
    _AnimFile_ResFile = (void *)0xFEFEFEFE;
    fn_801D2BD0(_AnimFile_pBufferInfo);
    fn_801D2BD0(_AnimFile_DefaultUserDataBuffer);
}

int AnimFileLoadSeqResident(int id, struct AnimFrameCache_t *pFrameCache, AnimFileBigInfo_t *pInfo)
{
    return _AnimFileLoadSeqResident(id, 0, pFrameCache, pInfo);
}

AnimFileFormat_t *AnimFileLoadAllocated(int id, int heap, int align, int frameCache)
{
    AnimFileFormat_t *pFile = fn_801D2BB0(heap, ResGetSize(_AnimFile_ResFile, id), align, 0);

    if (pFile) {
        ResCopyToBuffer(_AnimFile_ResFile, id, pFile);
        if (frameCache)
            pFile->flags |= 0x200;
        else
            pFile->flags &= ~0x200;
        AnimFileRelocate(pFile);
    }
    return pFile;
}

int AnimFileLoadResidentData(AnimFileFormat_t *pData, struct AnimFrameCache_t *pFrameCache)
{
    return _AnimFileLoadSeqResident(-3, pData, pFrameCache, 0);
}

int AnimFileLoadResident(int id, struct AnimFrameCache_t *pFrameCache)
{
    return AnimFileLoadSeqResident(id, pFrameCache, 0);
}

int AnimFileLoadResidentAsync(int id, struct AnimFrameCache_t *pFrameCache)
{
    int result = 0;
    int i;
    AnimFileRequest_t *pReq;

    for (i = 0; i < _AnimFile_NumResBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 0) {
            _AnimFile_pBufferInfo[i].mStatus = 2;
            _AnimFile_pBufferInfo[i].mId = id;
            _AnimFile_pBufferInfo[i].mpFrameCache = pFrameCache;
            _AnimFile_pBufferInfo[i].mUnknown1C = 1;
            pReq = &_AnimFile_DefaultUserDataBuffer[i];
            pReq->mSlot = i;
            pReq->mpInfo = 0;
            _AnimFile_pBufferInfo[i].mpData = ResLoadAsync(_AnimFile_ResFile, id, _AnimFile_MemoryHeap, _AnimFile_AsyncPriority, _AnimfileResourceCallback, pReq);
            result = fn_801F7C88();
            break;
        }
    }
    if (i == _AnimFile_NumResBuffers)
        result = 0x140003;
    return result;
}

int AnimFileLoadSeqDynamicAsync(unsigned short slot, int id, AnimFileBigInfo_t *pInfo)
{
    unsigned short index = slot + _AnimFile_NumResBuffers;
    int result = 0;
    AnimFileRequest_t *pReq;

    if (_AnimFile_pBufferInfo[index].mId != id || _AnimFile_pBufferInfo[index].mStatus == 0) {
        switch (_AnimFile_pBufferInfo[index].mStatus) {
        case 2:
            while (AnimFileGetDynamicLoadStatus(slot) != 1) {
                if (_AnimFile_bResSync)
                    ResSync(0);
                else
                    fn_801F81AC();
                if (FileHostCheckActive())
                    FileDebugProcess();
            }
        case 1:
            _AnimFileUnloadFileUnloadBySlot(index);
        }
        _AnimFile_pBufferInfo[index].mStatus = 2;
        _AnimFile_pBufferInfo[index].mUnknown1C = 1;
        _AnimFile_pBufferInfo[index].mId = id;
        pReq = &_AnimFile_DefaultUserDataBuffer[index];
        pReq->mSlot = index;
        pReq->mpInfo = pInfo;
        ResCopyAsyncToBuffer(_AnimFile_ResFile, id, _AnimFile_MemoryHeap, _AnimFile_pBufferInfo[index].mpData, _AnimFile_AsyncPriority, _AnimfileResourceCallback, pReq);
        result = fn_801F7C88();
    }
    return result;
}

unsigned short AnimFileLoadSeqVirtualAsync(int id, AnimFileFormat_t *pData, int size, AnimFileBigInfo_t *pInfo, int flag)
{
    unsigned short slot = _AnimFileGetFreeVirtualSlot();
    AnimFileRequest_t *pReq;

    if (slot != 0xFFFF) {
        _AnimFile_pBufferInfo[slot].mStatus = 2;
        _AnimFile_pBufferInfo[slot].mId = id;
        _AnimFile_pBufferInfo[slot].mpData = pData;
        _AnimFile_pBufferInfo[slot].mSize = size;
        _AnimFile_pBufferInfo[slot].mUnknown1C = flag;
        pReq = &_AnimFile_DefaultUserDataBuffer[slot];
        pReq->mSlot = slot;
        pReq->mpInfo = pInfo;
        ResCopyAsyncToBuffer(_AnimFile_ResFile, id, _AnimFile_MemoryHeap, _AnimFile_pBufferInfo[slot].mpData, _AnimFile_AsyncPriority, _AnimfileResourceCallback, pReq);
    }
    return slot - _AnimFile_NumResBuffers - _AnimFile_NumDynBuffers;
}

int AnimFileUnloadSlotVirtual(unsigned int slot)
{
    if (slot >= _AnimFile_NumVirtBuffers)
        return 0x140004;
    return _AnimFileUnloadFileUnloadBySlot(slot + _AnimFile_NumResBuffers + _AnimFile_NumDynBuffers);
}

int AnimFileUnloadFile(int id)
{
    int result = 0;
    int i;

    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mId == id) {
            result = _AnimFileUnloadFileUnloadBySlot(i);
            break;
        }
    }
    if (i == _AnimFile_NumBuffers)
        result = 0x140004;
    return result;
}

static unsigned int _AnimFileStateQuery(int state, unsigned short objectType, AnimCacheStateInfo_t *pOut, unsigned int max)
{
    unsigned int count = 0;
    AnimCacheStateInfo_t *pCache = AnimCacheGetStateInfo(objectType, state);
    int i;
    int stateRef;

    if (pCache && !(pCache->mUnknown0 & 0x8000) && pCache->mUnknown2 >= 0) {
        pOut[0].mUnknown0 = pCache->mUnknown0;
        count = 1;
        pOut[0].mUnknown2 = pCache->mUnknown2;
    } else {
        for (i = 0; i < _AnimFile_NumBuffers; i++) {
            if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mObjectType == objectType) {
                stateRef = AnimFileGetStateRef(AnimFileGetPtrFromSlot(i), state);
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

void AnimFileBuildStateCache(int objectType)
{
    int i;
    int j;
    int count;
    AnimCacheStateInfo_t *pCache;

    AnimCacheInvalidate(objectType);
    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mObjectType == objectType) {
            count = AnimFileGetNumStates(AnimFileGetPtrFromSlot(i));
            for (j = 0; j < count; j++) {
                pCache = AnimCacheGetStateInfo(objectType, AnimFileGetStateIdByStateRef(AnimFileGetPtrFromSlot(i), j));
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

void AnimFileGetStateAnimList(int objectType, int state, AnimStateAnimList_t *pList)
{
    AnimCacheStateInfo_t query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 380;
    count = _AnimFileStateQuery(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        AnimFileGetStateAnimListByStateRef(AnimFileGetPtrFromSlot(query[i].mUnknown0), query[i].mUnknown0, query[i].mUnknown2, pList);
}

int AnimFileGetStateQueryIndex(int state, unsigned int slot)
{
    AnimCacheStateInfo_t query[32];
    unsigned int count;
    unsigned int i;
    AnimFileFormat_t *pFile = AnimFileGetPtrFromSlot(slot);
    unsigned short objectType;

    if (pFile == 0)
        return -1;
    objectType = pFile->objectType;
    if (!(state & 0x8000)) {
        count = _AnimFileStateQuery(state, objectType, query, 32);
        for (i = 0; i < count; i++) {
            if (query[i].mUnknown0 == slot)
                return i;
        }
    }
    return -1;
}

void *AnimFileGetStateData(unsigned short state, unsigned short objectType)
{
    AnimCacheStateInfo_t query[32];
    unsigned int count;
    unsigned int i;
    void *pResult = 0;

    count = _AnimFileStateQuery(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        pResult = AnimFileGetStateDataByStateRef(AnimFileGetPtrFromSlot(query[i].mUnknown0), query[i].mUnknown2);
    return pResult;
}

void AnimFileGetTransList(int objectType, int state, AnimStateTransList_t *pList)
{
    AnimCacheStateInfo_t query[32];
    unsigned int count;
    unsigned int i;

    pList->mCount = 0;
    pList->mMax = 8;
    pList->mState = state;
    count = _AnimFileStateQuery(state, objectType, query, 32);
    for (i = 0; i < count; i++)
        AnimFileGetStateTransListByStateRef(AnimFileGetPtrFromSlot(query[i].mUnknown0), query[i].mUnknown0, query[i].mUnknown2, pList);
}

int AnimFileGetSlotFromFileNum(int objectType, int fileNum)
{
    int i;

    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mObjectType == objectType &&
            _AnimFile_pBufferInfo[i].mpData->fileNum == fileNum)
            return i;
    }
    return 0xFFFFFF;
}

int AnimFileGetSiblingSlot(int slot, int mask)
{
    unsigned short parent = _AnimFile_pBufferInfo[slot].mParent;
    int part = _AnimFile_pBufferInfo[slot].mPart;
    int i;

    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mParent == parent && _AnimFile_pBufferInfo[i].mPart == part &&
            (_AnimFile_pBufferInfo[i].mpData->flags & mask) && slot != i)
            return i;
    }
    return 0xFFFFFF;
}

unsigned short AnimFileGetTransitionStateFromObjType(int objectType)
{
    int i;
    int j;
    AnimFileFormat_t *pFile;

    for (i = 0; i < _AnimFile_NumBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mStatus == 1 && _AnimFile_pBufferInfo[i].mObjectType == objectType) {
            pFile = _AnimFile_pBufferInfo[i].mpData;
            for (j = 0; j < (unsigned short)pFile->states->mCount; j++) {
                if ((pFile->states->mStates[j].mId & 0x4000) && (pFile->flags & 8))
                    return pFile->states->mStates[j].mId;
            }
        }
    }
    return 0xFFFF;
}

unsigned char AnimFileGetResidentLoadStatus(int id)
{
    unsigned char status = 0;
    int i;

    for (i = 0; i < _AnimFile_NumResBuffers; i++) {
        if (_AnimFile_pBufferInfo[i].mId == id) {
            status = _AnimFile_pBufferInfo[i].mStatus;
            break;
        }
    }
    return status;
}

unsigned char AnimFileGetDynamicLoadStatus(unsigned short slot)
{
    return _AnimFile_pBufferInfo[(unsigned short)(slot + _AnimFile_NumResBuffers)].mStatus;
}

unsigned char AnimFileGetVirtualLoadStatus(unsigned short slot)
{
    return _AnimFile_pBufferInfo[(unsigned short)(slot + (_AnimFile_NumResBuffers + _AnimFile_NumDynBuffers))].mStatus;
}

AnimFileFormat_t *AnimFileGetPtrFromSlot(unsigned int slot)
{
    if (slot < _AnimFile_NumBuffers && _AnimFile_pBufferInfo[slot].mObjectType != 0x8000)
        return _AnimFile_pBufferInfo[slot].mpData;
    return 0;
}

struct AnimFrameCache_t *AnimFileGetFrameCacheFromSlot(unsigned int slot)
{
    if (slot < _AnimFile_NumBuffers)
        return _AnimFile_pBufferInfo[slot].mpFrameCache;
    return 0;
}

void AnimFileNewProcessBigFile(int slot, AnimFileBigInfo_t *pInfo)
{
    char *pBase = 0;
    AnimFileNewBigFile_t *pBig = 0;
    AnimFileBigRecord_t *pRecord;
    AnimFileBigGroup_t *pGroup;
    AnimFileBigSet_t *pSet;
    AnimFileNewBigPart_t *pPart;
    AnimFileFormat_t *pFile;
    AnimFileBufferInfo_t *pBuffer;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned int n;
    unsigned short m;
    int setTypeBit;

    if (AnimGetSeqVersion() == 1) {
        pBase = (char *)_AnimFile_pBufferInfo[slot].mpData;
        pBig = (AnimFileNewBigFile_t *)(pBase + *(int *)pBase + 4);
    } else if (AnimGetSeqVersion() == 2) {
        pBig = (AnimFileNewBigFile_t *)_AnimFile_pBufferInfo[slot].mpData;
    }
    pRecord = (AnimFileBigRecord_t *)(pBase + 4);
    pBase = (char *)_AnimFile_pBufferInfo[slot].mpData;
    if (AnimGetSeqVersion() == 1) {
        for (i = 0; i < pInfo->mCount; i++) {
            pSet = &pInfo->mpSets[i];
            for (j = 0; j < pSet->mCount; j++) {
                pGroup = &pSet->mpGroups[j];
                pGroup->mpRecords = pRecord;
                for (k = 0; k < pGroup->mCount; k++) {
                    AnimFileBigRecord_t *pEntry = &pGroup->mpRecords[k];

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
    _AnimFile_pBufferInfo[slot].mParent = -1;
    _AnimFile_pBufferInfo[slot].mObjectType = 0x8000;
    for (n = 0; n < pBig->mCount; n++) {
        for (m = 0; m <= 1; m++) {
            // FAKEMATCH: integer address sum (offset first) found by search; the same address as &pBig->mEntries[n]
            pPart = &((AnimFileNewBigEntry_t *)(n * sizeof(AnimFileNewBigEntry_t) + (int)pBig->mEntries))->mParts[m];
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
                if (_AnimFile_pBufferInfo[slot].mUnknown1C)
                    pFile->flags &= ~0x2000;
                else
                    pFile->flags |= 0x2000;
                AnimFileRelocate(pFile);
                pBuffer = &_AnimFile_pBufferInfo[_AnimFileGetFreeVirtualSlot()];
                pBuffer->mpData = pFile;
                pBuffer->mSize = pPart->mSize;
                pBuffer->mPart = n;
                pBuffer->mParent = slot;
                pBuffer->mObjectType = AnimFileGetObjectType(pFile);
                if (setTypeBit)
                    pBuffer->mObjectType |= 0x4000;
                pBuffer->mStatus = 1;
                pPart->mpFile->flags |= 0x100;
            }
        }
    }
}

void AnimFileCopyBigFileInfo(AnimFileBigInfo_t *pDest, AnimFileBigInfo_t *pSource)
{
    unsigned short i;
    unsigned short j;
    unsigned short k;
    AnimFileBigSet_t *pSourceSet;
    AnimFileBigSet_t *pDestSet;
    AnimFileBigGroup_t *pSourceGroup;
    AnimFileBigGroup_t *pDestGroup;
    AnimFileBigRecord_t *pSourceRecord;
    AnimFileBigRecord_t *pDestRecord;

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

void AnimFileProcessBigFile(int slot, AnimFileBigInfo_t *pInfo)
{
    AnimFileBigFile_t *pBig = (AnimFileBigFile_t *)_AnimFile_pBufferInfo[slot].mpData;
    AnimFileBigEntry_t *pEntry = &pBig->mFirst;
    AnimFileFormat_t *pFile;
    AnimFileBufferInfo_t *pBuffer;
    unsigned int i;

    _AnimFile_pBufferInfo[slot].mParent = -1;
    _AnimFile_pBufferInfo[slot].mObjectType = 0x8000;
    for (i = 0; i < pBig->mCount; i++) {
        pFile = &pEntry->mFile;
        pFile->objectType = pEntry->mObjectType;
        AnimFileRelocate(pFile);
        pBuffer = &_AnimFile_pBufferInfo[_AnimFileGetFreeVirtualSlot()];
        pBuffer->mpData = pFile;
        pBuffer->mSize = pEntry->mSize;
        pBuffer->mPart = i;
        pBuffer->mParent = slot;
        pBuffer->mObjectType = AnimFileGetObjectType(pFile) | 0x4000;
        pBuffer->mStatus = 1;
        pEntry = (AnimFileBigEntry_t *)((char *)pFile + pEntry->mSize);
        pEntry->mFile.flags |= 0x100;
    }
}

void AnimFileSetRelocateBigFileFunc(void (*pFunc)(int, AnimFileBigInfo_t *))
{
    _AnimFile_RelocateBigFileFunc = pFunc;
}

void *AnimFileGetResFile(void)
{
    return _AnimFile_ResFile;
}
