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
    void **mppUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    SyncStateFn_t mpUnknown16;
    SyncStateFn_t mpUnknown20;
    SyncStateFn_t mpUnknown24;
    SyncStateCompareFn_t mpUnknown28;
    SyncStateLoadFn_t mpUnknown32;
    SyncStateSizeFn_t mpUnknown36;
    SyncStateSaveFn_t mpUnknown40;
    void *mpUnknown44;
    SyncStateGroup_t *mpUnknown48;
} SyncStateHandle_t;

/* 24-byte block copied to 0x803A39FC by 0x80237EE8; only +8 is read here. */
typedef struct SyncStateHeapDesc_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
} SyncStateHeapDesc_t;

extern SyncStateHeapDesc_t _SyncState_HeapDesc;
void SyncStateRestoreGroup(SyncStateGroup_t *p);
void SyncStateNotifyGroup(SyncStateGroup_t *p);
extern DSList_t *_SyncState_pGroups;
extern void fn_801D277C(int ident);
extern char *fn_801D27B8(int ident);
extern void fn_801D2130(void *pConfig);
extern void fn_801D2570(int ident);
void SyncStateDetachGroup(SyncStateGroup_t *p);
void SyncStateFreeCopy(SyncStateGroup_t *p);
SyncStateGroup_t *SyncStateFindGroup(int key);
SyncStateHandle_t *SyncStateNewHandle(SyncStateGroup_t *pGroup, void **ppData, int size, int a, unsigned int id);

extern void *SyncStateGetData(void *pHandle);

int SyncStateCompareHandles(SyncStateHandle_t *pA, SyncStateHandle_t *pB)
{
    return pB->mUnknown8 - pA->mUnknown8;
}

SyncStateHandle_t *SyncStateNewHandle(SyncStateGroup_t *pGroup, void **ppData, int size, int a, unsigned int id)
{
    SyncStateHandle_t *p = DSNewListNode(pGroup->mpUnknown20);
    memset(p, 0, sizeof(SyncStateHandle_t));
    p->mppUnknown0 = ppData;
    p->mUnknown8 = a;
    p->mUnknown12 = id;
    p->mUnknown4 = size;
    p->mpUnknown48 = pGroup;
    p->mpUnknown44 = fn_801D2B7C(size, 0, 0);
    memset(p->mpUnknown44, 0, size);
    DSAddListNode(pGroup->mpUnknown20, p, 0);
    return p;
}

void SyncStateAttachHandle(SyncStateHandle_t *p)
{
    *p->mppUnknown0 = p->mpUnknown44;
}

void SyncStateDetachHandle(SyncStateHandle_t *p)
{
    *p->mppUnknown0 = 0;
}

void SyncStateNotifyHandle(SyncStateHandle_t *p)
{
    if (p->mpUnknown24 != 0) {
        p->mpUnknown24(p->mpUnknown44, 0);
    }
}

void SyncStateDelHandle(SyncStateHandle_t *p)
{
    SyncStateDetachHandle(p);
    if (p->mpUnknown20 != 0) {
        p->mpUnknown20(p->mpUnknown44, 0);
    }
    fn_801D2BD0(p->mpUnknown44);
}

void SyncStateRestoreGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    if (p->mpUnknown24 != 0) {
        SyncStateCopy(fn_801D27B8(p->mUnknown16), p->mpUnknown24, p->mUnknown12);
    }
    pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        SyncStateAttachHandle(pItem);
        pItem = DSNextListNode(p->mpUnknown20, pItem);
    }
    p->mUnknown4 = 2;
    SyncStateNotifyGroup(p);
}

void SyncStateDetachGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    if (p->mUnknown4 != 1) {
        pItem = DSGetListNode(p->mpUnknown20, 0);
        while (pItem != 0) {
            SyncStateDetachHandle(pItem);
            pItem = DSNextListNode(p->mpUnknown20, pItem);
        }
        p->mUnknown4 = 1;
    }
}

int SyncStateMatchGroup(void *p, void *pKey, void *pOut)
{
    SyncStateGroup_t *pGroup = p;
    int *pValue = pKey;
    SyncStateGroup_t **ppResult = pOut;
    if (pGroup->mUnknown0 == *pValue && (pGroup->mUnknown4 == 2 || pGroup->mUnknown4 == 0)) {
        *ppResult = pGroup;
        return 0;
    }
    return -1;
}

SyncStateGroup_t *SyncStateAddGroup(int key, int a, int b, int c)
{
    SyncStateGroup_t *p = DSNewListNode(_SyncState_pGroups);
    p->mUnknown0 = key;
    p->mUnknown8 = a;
    p->mUnknown16 = c;
    p->mUnknown12 = b;
    p->mUnknown4 = 1;
    p->mpUnknown24 = 0;
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
    fn_801D2130(&_SyncState_HeapDesc);
    p = SyncStateAddGroup(key, count, size, _SyncState_HeapDesc.mUnknown8);
    p->mpUnknown20 = DSNewList(_SyncState_HeapDesc.mUnknown8, 0, count, sizeof(SyncStateHandle_t),
                                 (int (*)(void *, void *))SyncStateCompareHandles, 0);
    return p;
}

void SyncStateOpenGroup(SyncStateGroup_t *p)
{
    p->mUnknown4 = 0;
}

void SyncStateSaveGroup(SyncStateGroup_t *p)
{
    char *pData = fn_801D27B8(p->mUnknown16);
    if (p->mpUnknown24 != 0) {
        SyncStateCopy(p->mpUnknown24, pData, p->mUnknown12);
    }
    SyncStateDetachGroup(p);
}

void SyncStateFreeCopy(SyncStateGroup_t *p)
{
    if (p->mpUnknown24 != 0) {
        fn_801D2BD0(p->mpUnknown24);
        p->mpUnknown24 = 0;
    }
}

void SyncStateNotifyGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        SyncStateNotifyHandle(pItem);
        pItem = DSNextListNode(p->mpUnknown20, pItem);
    }
}

void SyncStateDelGroup(SyncStateGroup_t *p)
{
    SyncStateHandle_t *pItem;
    SyncStateHandle_t *pNext;

    fn_801D277C(p->mUnknown16);
    pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        SyncStateDelHandle(pItem);
        pNext = DSNextListNode(p->mpUnknown20, pItem);
        DSDelListNode(p->mpUnknown20, pItem);
        pItem = pNext;
    }
    DSDelList(p->mpUnknown20);
    fn_801D277C(1);
    fn_801D2570(p->mUnknown16);
    SyncStateRemoveGroup(p);
}

SyncStateGroup_t *SyncStateEndGroup(SyncStateGroup_t *p)
{
    // FAKEMATCH: dead initial copy of p, the second register copy of p (mr r30,r31) the target keeps
    SyncStateGroup_t *pFound = p;
    pFound = SyncStateFindGroup(p->mUnknown0);
    if (pFound != 0) {
        SyncStateDetachGroup(pFound);
    }
    SyncStateRestoreGroup(p);
    return pFound;
}

void *SyncStateGetData(void *pHandle)
{
    SyncStateHandle_t *p = pHandle;
    return p->mpUnknown44;
}

void *SyncStateRegister(int a, void **ppData, int size, int b, unsigned int id)
{
    void *pResult = 0;
    SyncStateGroup_t *p = SyncStateFindGroup(a);
    if (p != 0) {
        fn_801D277C(p->mUnknown16);
        pResult = SyncStateNewHandle(p, ppData, size, b, id);
    }
    return pResult;
}

void SyncStateCommit(void *pHandle)
{
    SyncStateHandle_t *p = pHandle;
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16(p->mpUnknown44, 0);
    }
    SyncStateAttachHandle(p);
    fn_801D277C(1);
}

void SyncStateSetCallbacks(void *pHandle, SyncStateFn_t pCallback10, SyncStateFn_t pCallback14, SyncStateFn_t pCallback18, SyncStateCompareFn_t pCallback1C)
{
    SyncStateHandle_t *p = pHandle;
    p->mpUnknown16 = pCallback10;
    p->mpUnknown20 = pCallback14;
    p->mpUnknown24 = pCallback18;
    p->mpUnknown28 = pCallback1C;
}

void SyncStateSetSaveCallbacks(void *pHandle, SyncStateSaveFn_t pCallback28, SyncStateSizeFn_t pCallback24, SyncStateLoadFn_t pCallback20)
{
    SyncStateHandle_t *p = pHandle;
    p->mpUnknown32 = pCallback20;
    p->mpUnknown36 = pCallback24;
    p->mpUnknown40 = pCallback28;
}
