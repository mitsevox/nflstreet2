/* State registry: groups of registered state blocks, each a buffer tagged
   with a four-character id and its init, shutdown, compare, save, size and
   load callbacks, so the game's synchronised state (random streams, the game
   clock, event queues) can be checked, saved and restored together. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
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

typedef struct Chunk_80237D5C {
    unsigned int mWords[4];
} Chunk_80237D5C;

void SyncStateCopy(void *pDst, const void *pSrc, unsigned int size);
typedef struct Handle_80237A40 {
    void **mppUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    Callback_80238234 mpUnknown16;
    Callback_80238234 mpUnknown20;
    Callback_80238234 mpUnknown24;
    Callback1C_80238234 mpUnknown28;
    Callback20_80238248 mpUnknown32;
    Callback24_80238248 mpUnknown36;
    Callback28_80238248 mpUnknown40;
    void *mpUnknown44;
    Object_80237EE8 *mpUnknown48;
} Handle_80237A40;

/* 24-byte block copied to 0x803A39FC by 0x80237EE8; only +8 is read here. */
typedef struct Config_80237EE8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
} Config_80237EE8;

extern Config_80237EE8 lbl_803A39FC;
void SyncStateRestoreGroup(Object_80237EE8 *p);
void SyncStateNotifyGroup(Object_80237EE8 *p);
extern DSList_t *lbl_803ED030;
extern void fn_801D277C(int ident);
extern char *fn_801D27B8(int ident);
extern void fn_801D2130(void *pConfig);
extern void fn_801D2570(int ident);
void SyncStateDetachGroup(Object_80237EE8 *p);
void SyncStateFreeCopy(Object_80237EE8 *p);
Object_80237EE8 *SyncStateFindGroup(int key);
Handle_80237A40 *SyncStateNewHandle(Object_80237EE8 *pGroup, void **ppData, int size, int a, unsigned int id);
typedef struct Counter_80237934 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Counter_80237934;

extern void *SyncStateGetData(void *pHandle);

int SyncStateCompareHandles(Counter_80237934 *pA, Counter_80237934 *pB)
{
    return pB->mUnknown8 - pA->mUnknown8;
}

Handle_80237A40 *SyncStateNewHandle(Object_80237EE8 *pGroup, void **ppData, int size, int a, unsigned int id)
{
    Handle_80237A40 *p = DSNewListNode(pGroup->mpUnknown20);
    memset(p, 0, sizeof(Handle_80237A40));
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

void SyncStateAttachHandle(Handle_80237A40 *p)
{
    *p->mppUnknown0 = p->mpUnknown44;
}

void SyncStateDetachHandle(Handle_80237A40 *p)
{
    *p->mppUnknown0 = 0;
}

void SyncStateNotifyHandle(Handle_80237A40 *p)
{
    if (p->mpUnknown24 != 0) {
        p->mpUnknown24(p->mpUnknown44, 0);
    }
}

void SyncStateDelHandle(Handle_80237A40 *p)
{
    SyncStateDetachHandle(p);
    if (p->mpUnknown20 != 0) {
        p->mpUnknown20(p->mpUnknown44, 0);
    }
    fn_801D2BD0(p->mpUnknown44);
}

void SyncStateRestoreGroup(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
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

void SyncStateDetachGroup(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
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
    Object_80237EE8 *pGroup = p;
    int *pValue = pKey;
    Object_80237EE8 **ppResult = pOut;
    if (pGroup->mUnknown0 == *pValue && (pGroup->mUnknown4 == 2 || pGroup->mUnknown4 == 0)) {
        *ppResult = pGroup;
        return 0;
    }
    return -1;
}

Object_80237EE8 *SyncStateAddGroup(int key, int a, int b, int c)
{
    Object_80237EE8 *p = DSNewListNode(lbl_803ED030);
    p->mUnknown0 = key;
    p->mUnknown8 = a;
    p->mUnknown16 = c;
    p->mUnknown12 = b;
    p->mUnknown4 = 1;
    p->mpUnknown24 = 0;
    DSAddListNode(lbl_803ED030, p, 0);
    return p;
}

void SyncStateRemoveGroup(Object_80237EE8 *p)
{
    SyncStateFreeCopy(p);
    DSDelListNode(lbl_803ED030, p);
}

void SyncStateCopy(void *pDst, const void *pSrc, unsigned int size)
{
    while (size >= 64) {
        ((Chunk_80237D5C *)pDst)[0] = ((const Chunk_80237D5C *)pSrc)[0];
        ((Chunk_80237D5C *)pDst)[1] = ((const Chunk_80237D5C *)pSrc)[1];
        ((Chunk_80237D5C *)pDst)[2] = ((const Chunk_80237D5C *)pSrc)[2];
        ((Chunk_80237D5C *)pDst)[3] = ((const Chunk_80237D5C *)pSrc)[3];
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
    lbl_803ED030 = DSNewList(1, 0, count, sizeof(Object_80237EE8), 0, 0);
}

int SyncStateShutdown(void)
{
    return DSDelList(lbl_803ED030);
}

Object_80237EE8 *SyncStateFindGroup(int key)
{
    Object_80237EE8 *pResult;
    if (DSSearchList(lbl_803ED030, 0, &key, &pResult, SyncStateMatchGroup) == 2) {
        return pResult;
    }
    return 0;
}

Object_80237EE8 *SyncStateNewGroup(int key, int count, int size, Config_80237EE8 *pConfig)
{
    Object_80237EE8 *p;

    lbl_803A39FC = *pConfig;
    fn_801D2130(&lbl_803A39FC);
    p = SyncStateAddGroup(key, count, size, lbl_803A39FC.mUnknown8);
    p->mpUnknown20 = DSNewList(lbl_803A39FC.mUnknown8, 0, count, sizeof(Handle_80237A40),
                                 (int (*)(void *, void *))SyncStateCompareHandles, 0);
    return p;
}

void SyncStateOpenGroup(Object_80237EE8 *p)
{
    p->mUnknown4 = 0;
}

void SyncStateSaveGroup(Object_80237EE8 *p)
{
    char *pData = fn_801D27B8(p->mUnknown16);
    if (p->mpUnknown24 != 0) {
        SyncStateCopy(p->mpUnknown24, pData, p->mUnknown12);
    }
    SyncStateDetachGroup(p);
}

void SyncStateFreeCopy(Object_80237EE8 *p)
{
    if (p->mpUnknown24 != 0) {
        fn_801D2BD0(p->mpUnknown24);
        p->mpUnknown24 = 0;
    }
}

void SyncStateNotifyGroup(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        SyncStateNotifyHandle(pItem);
        pItem = DSNextListNode(p->mpUnknown20, pItem);
    }
}

void SyncStateDelGroup(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
    Handle_80237A40 *pNext;

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

Object_80237EE8 *SyncStateEndGroup(Object_80237EE8 *p)
{
    // FAKEMATCH: dead initial copy of p, the second register copy of p (mr r30,r31) the target keeps
    Object_80237EE8 *pFound = p;
    pFound = SyncStateFindGroup(p->mUnknown0);
    if (pFound != 0) {
        SyncStateDetachGroup(pFound);
    }
    SyncStateRestoreGroup(p);
    return pFound;
}

void *SyncStateGetData(void *pHandle)
{
    Handle_80237A40 *p = pHandle;
    return p->mpUnknown44;
}

void *SyncStateRegister(int a, void **ppData, int size, int b, unsigned int id)
{
    void *pResult = 0;
    Object_80237EE8 *p = SyncStateFindGroup(a);
    if (p != 0) {
        fn_801D277C(p->mUnknown16);
        pResult = SyncStateNewHandle(p, ppData, size, b, id);
    }
    return pResult;
}

void SyncStateCommit(void *pHandle)
{
    Handle_80237A40 *p = pHandle;
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16(p->mpUnknown44, 0);
    }
    SyncStateAttachHandle(p);
    fn_801D277C(1);
}

void SyncStateSetCallbacks(void *pHandle, Callback_80238234 pCallback10, Callback_80238234 pCallback14, Callback_80238234 pCallback18, Callback1C_80238234 pCallback1C)
{
    Handle_80237A40 *p = pHandle;
    p->mpUnknown16 = pCallback10;
    p->mpUnknown20 = pCallback14;
    p->mpUnknown24 = pCallback18;
    p->mpUnknown28 = pCallback1C;
}

void SyncStateSetSaveCallbacks(void *pHandle, Callback28_80238248 pCallback28, Callback24_80238248 pCallback24, Callback20_80238248 pCallback20)
{
    Handle_80237A40 *p = pHandle;
    p->mpUnknown32 = pCallback20;
    p->mpUnknown36 = pCallback24;
    p->mpUnknown40 = pCallback28;
}
