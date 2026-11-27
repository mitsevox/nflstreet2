/* State registry: groups of registered state blocks, each a buffer tagged
   with a four-character id and its init, shutdown, compare, save, size and
   load callbacks, so the game's synchronised state (random streams, the game
   clock, event queues) can be checked, saved and restored together. */

#include "engine/SyncStateGroup.h"
#include "engine/EvMonDesc.h"
#include "engine/EvMonAddListener.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct SyncStateBlock_t {
    unsigned int mWords[4];
} SyncStateBlock_t;

void SyncStateCopy(void *pDst, const void *pSrc, unsigned int size);
typedef struct SyncStateHandle_t {
    void **mppOwner;
    int mSize;
    int mPriority;
    unsigned int mId;
    SyncStateFn_t mpInitFn;
    SyncStateFn_t mpShutdownFn;
    SyncStateFn_t mpNotifyFn;
    SyncStateCompareFn_t mpCompareFn;
    SyncStateLoadFn_t mpLoadFn;
    SyncStateSizeFn_t mpSizeFn;
    SyncStateSaveFn_t mpSaveFn;
    void *mpData;
    SyncStateGroup_t *mpGroup;
} SyncStateHandle_t;

typedef struct SyncStateHeapDesc_t {
    int mUnknown0;
    int mUnknown4;
    int mHeap;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
} SyncStateHeapDesc_t;

static SyncStateHeapDesc_t _SyncState_HeapDesc;
void SyncStateRestoreGroup(SyncStateGroup_t *p);
void SyncStateNotifyGroup(SyncStateGroup_t *p);
static DSList_t *_SyncState_pGroups;
extern void MemSetDefaultHeap(int ident);
extern char *MemGetHeapStart(int ident);
extern void MemInitHeap(void *pConfig);
extern void fn_801D2570(int ident);
void SyncStateDetachGroup(SyncStateGroup_t *p);
void SyncStateFreeCopy(SyncStateGroup_t *p);
SyncStateGroup_t *SyncStateFindGroup(int key);
SyncStateHandle_t *SyncStateNewHandle(SyncStateGroup_t *pGroup, void **ppData, int size, int a, unsigned int id);

extern void *SyncStateGetData(void *pHandle);

int SyncStateCompareHandles(SyncStateHandle_t *pA, SyncStateHandle_t *pB)
{
    return pB->mPriority - pA->mPriority;
}

SyncStateHandle_t *SyncStateNewHandle(SyncStateGroup_t *pGroup, void **ppData, int size, int a, unsigned int id)
{
    SyncStateHandle_t *p = DSNewListNode(pGroup->mpHandles);
    memset(p, 0, sizeof(SyncStateHandle_t));
    p->mppOwner = ppData;
    p->mPriority = a;
    p->mId = id;
    p->mSize = size;
    p->mpGroup = pGroup;
    p->mpData = fn_801D2B7C(size, 0, 0);
    memset(p->mpData, 0, size);
    DSAddListNode(pGroup->mpHandles, p, 0);
    return p;
}

void SyncStateAttachHandle(SyncStateHandle_t *p)
{
    *p->mppOwner = p->mpData;
}

void SyncStateDetachHandle(SyncStateHandle_t *p)
{
    *p->mppOwner = 0;
}

void SyncStateNotifyHandle(SyncStateHandle_t *p)
{
    if (p->mpNotifyFn != 0) {
        p->mpNotifyFn(p->mpData, 0);
    }
}

void SyncStateDelHandle(SyncStateHandle_t *p)
{
    SyncStateDetachHandle(p);
    if (p->mpShutdownFn != 0) {
        p->mpShutdownFn(p->mpData, 0);
    }
    fn_801D2BD0(p->mpData);
}

void SyncStateRestoreGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    if (p->mpCopy != 0) {
        SyncStateCopy(MemGetHeapStart(p->mHeap), p->mpCopy, p->mHeapSize);
    }
    pItem = DSGetListNode(p->mpHandles, 0);
    while (pItem != 0) {
        SyncStateAttachHandle(pItem);
        pItem = DSNextListNode(p->mpHandles, pItem);
    }
    p->mState = 2;
    SyncStateNotifyGroup(p);
}

void SyncStateDetachGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    if (p->mState != 1) {
        pItem = DSGetListNode(p->mpHandles, 0);
        while (pItem != 0) {
            SyncStateDetachHandle(pItem);
            pItem = DSNextListNode(p->mpHandles, pItem);
        }
        p->mState = 1;
    }
}

int SyncStateMatchGroup(void *p, void *pKey, void *pOut)
{
    SyncStateGroup_t *pGroup = p;
    int *pValue = pKey;
    SyncStateGroup_t **ppResult = pOut;
    if (pGroup->mKey == *pValue && (pGroup->mState == 2 || pGroup->mState == 0)) {
        *ppResult = pGroup;
        return 0;
    }
    return -1;
}

SyncStateGroup_t *SyncStateAddGroup(int key, int a, int b, int c)
{
    SyncStateGroup_t *p = DSNewListNode(_SyncState_pGroups);
    p->mKey = key;
    p->mNumHandles = a;
    p->mHeap = c;
    p->mHeapSize = b;
    p->mState = 1;
    p->mpCopy = 0;
    DSAddListNode(_SyncState_pGroups, p, 0);
    return p;
}

void SyncStateRemoveGroup(SyncStateGroup_t *p)
{
    SyncStateFreeCopy(p);
    DSDelListNode(_SyncState_pGroups, p);
}

void SyncStateCopy(void *pDst, const void *pSrc, unsigned int size)
{
    while (size >= 64) {
        ((SyncStateBlock_t *)pDst)[0] = ((const SyncStateBlock_t *)pSrc)[0];
        ((SyncStateBlock_t *)pDst)[1] = ((const SyncStateBlock_t *)pSrc)[1];
        ((SyncStateBlock_t *)pDst)[2] = ((const SyncStateBlock_t *)pSrc)[2];
        ((SyncStateBlock_t *)pDst)[3] = ((const SyncStateBlock_t *)pSrc)[3];
        pDst = (char *)pDst + 64;
        pSrc = (const char *)pSrc + 64;
        size -= 64;
    }
    // FAKEMATCH: __builtin_memcpy for the tail; the file is -fno-builtin (its memset calls are plain), but the
    // target calls memcpy through the block-move library call (crclr cr1eq at 0x80237E24).
    __builtin_memcpy(pDst, pSrc, size);
}

void SyncStateInit(int count)
{
    _SyncState_pGroups = DSNewList(1, 0, count, sizeof(SyncStateGroup_t), 0, 0);
}

int SyncStateShutdown(void)
{
    return DSDelList(_SyncState_pGroups);
}

SyncStateGroup_t *SyncStateFindGroup(int key)
{
    SyncStateGroup_t *pResult;
    if (DSSearchList(_SyncState_pGroups, 0, &key, &pResult, SyncStateMatchGroup) == 2) {
        return pResult;
    }
    return 0;
}

SyncStateGroup_t *SyncStateNewGroup(int key, int count, int size, SyncStateHeapDesc_t *pConfig)
{
    SyncStateGroup_t *p;

    _SyncState_HeapDesc = *pConfig;
    MemInitHeap(&_SyncState_HeapDesc);
    p = SyncStateAddGroup(key, count, size, _SyncState_HeapDesc.mHeap);
    p->mpHandles = DSNewList(_SyncState_HeapDesc.mHeap, 0, count, sizeof(SyncStateHandle_t),
                                 (int (*)(void *, void *))SyncStateCompareHandles, 0);
    return p;
}

void SyncStateOpenGroup(SyncStateGroup_t *p)
{
    p->mState = 0;
}

void SyncStateSaveGroup(SyncStateGroup_t *p)
{
    char *pData = MemGetHeapStart(p->mHeap);
    if (p->mpCopy != 0) {
        SyncStateCopy(p->mpCopy, pData, p->mHeapSize);
    }
    SyncStateDetachGroup(p);
}

void SyncStateFreeCopy(SyncStateGroup_t *p)
{
    if (p->mpCopy != 0) {
        fn_801D2BD0(p->mpCopy);
        p->mpCopy = 0;
    }
}

void SyncStateNotifyGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem = DSGetListNode(p->mpHandles, 0);
    while (pItem != 0) {
        SyncStateNotifyHandle(pItem);
        pItem = DSNextListNode(p->mpHandles, pItem);
    }
}

void SyncStateDelGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    SyncStateHandle_t *pNext;

    MemSetDefaultHeap(p->mHeap);
    pItem = DSGetListNode(p->mpHandles, 0);
    while (pItem != 0) {
        SyncStateDelHandle(pItem);
        pNext = DSNextListNode(p->mpHandles, pItem);
        DSDelListNode(p->mpHandles, pItem);
        pItem = pNext;
    }
    DSDelList(p->mpHandles);
    MemSetDefaultHeap(1);
    fn_801D2570(p->mHeap);
    SyncStateRemoveGroup(p);
}

SyncStateGroup_t *SyncStateActivateGroup(SyncStateGroup_t *p)
{
    // FAKEMATCH: dead initial copy of p, the second register copy of p (mr r30,r31) the target keeps
    SyncStateGroup_t *pFound = p;
    pFound = SyncStateFindGroup(p->mKey);
    if (pFound != 0) {
        SyncStateDetachGroup(pFound);
    }
    SyncStateRestoreGroup(p);
    return pFound;
}

void *SyncStateGetData(void *pHandle)
{
    SyncStateHandle_t *p = pHandle;
    return p->mpData;
}

void *SyncStateRegister(int a, void **ppData, int size, int b, unsigned int id)
{
    void *pResult = 0;
    SyncStateGroup_t *p = SyncStateFindGroup(a);
    if (p != 0) {
        MemSetDefaultHeap(p->mHeap);
        pResult = SyncStateNewHandle(p, ppData, size, b, id);
    }
    return pResult;
}

void SyncStateCommit(void *pHandle)
{
    SyncStateHandle_t *p = pHandle;
    if (p->mpInitFn != 0) {
        p->mpInitFn(p->mpData, 0);
    }
    SyncStateAttachHandle(p);
    MemSetDefaultHeap(1);
}

void SyncStateSetCallbacks(void *pHandle, SyncStateFn_t pCallback10, SyncStateFn_t pCallback14, SyncStateFn_t pCallback18, SyncStateCompareFn_t pCallback1C)
{
    SyncStateHandle_t *p = pHandle;
    p->mpInitFn = pCallback10;
    p->mpShutdownFn = pCallback14;
    p->mpNotifyFn = pCallback18;
    p->mpCompareFn = pCallback1C;
}

void SyncStateSetSaveCallbacks(void *pHandle, SyncStateSaveFn_t pCallback28, SyncStateSizeFn_t pCallback24, SyncStateLoadFn_t pCallback20)
{
    SyncStateHandle_t *p = pHandle;
    p->mpLoadFn = pCallback20;
    p->mpSizeFn = pCallback24;
    p->mpSaveFn = pCallback28;
}
