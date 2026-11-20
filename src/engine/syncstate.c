/* State registry: groups of registered state blocks, each a buffer tagged
   with a four-character id and its init, shutdown, compare, save, size and
   load callbacks, so the game's synchronised state (random streams, the game
   clock, event queues) can be checked, saved and restored together. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct Chunk_80237D5C {
    unsigned int mWords[16];
} Chunk_80237D5C;

void fn_80237D5C(void *pDst, const void *pSrc, unsigned int size);
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
void fn_80237B84(Object_80237EE8 *p);
void fn_80238034(Object_80237EE8 *p);
extern DSList_t *lbl_803ED030;
extern void fn_801D277C(int ident);
extern char *fn_801D27B8(int ident);
extern void fn_801D2130(void *pConfig);
extern void fn_801D2570(int ident);
void fn_80237C0C(Object_80237EE8 *p);
void fn_80237FF4(Object_80237EE8 *p);
Object_80237EE8 *fn_80237E9C(int key);
Handle_80237A40 *fn_80237A40(Object_80237EE8 *pGroup, void **ppData, int size, int a, unsigned int id);
typedef struct Counter_80237934 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Counter_80237934;

extern void *fn_8023816C(void *pHandle);

int fn_80237A30(Counter_80237934 *pA, Counter_80237934 *pB)
{
    return pB->mUnknown8 - pA->mUnknown8;
}

Handle_80237A40 *fn_80237A40(Object_80237EE8 *pGroup, void **ppData, int size, int a, unsigned int id)
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

void fn_80237ADC(Handle_80237A40 *p)
{
    *p->mppUnknown0 = p->mpUnknown44;
}

void fn_80237AEC(Handle_80237A40 *p)
{
    *p->mppUnknown0 = 0;
}

void fn_80237AFC(Handle_80237A40 *p)
{
    if (p->mpUnknown24 != 0) {
        p->mpUnknown24(p->mpUnknown44, 0);
    }
}

void fn_80237B34(Handle_80237A40 *p)
{
    fn_80237AEC(p);
    if (p->mpUnknown20 != 0) {
        p->mpUnknown20(p->mpUnknown44, 0);
    }
    fn_801D2BD0(p->mpUnknown44);
}

void fn_80237B84(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
    if (p->mpUnknown24 != 0) {
        fn_80237D5C(fn_801D27B8(p->mUnknown16), p->mpUnknown24, p->mUnknown12);
    }
    pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        fn_80237ADC(pItem);
        pItem = DSNextListNode(p->mpUnknown20, pItem);
    }
    p->mUnknown4 = 2;
    fn_80238034(p);
}

void fn_80237C0C(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
    if (p->mUnknown4 != 1) {
        pItem = DSGetListNode(p->mpUnknown20, 0);
        while (pItem != 0) {
            fn_80237AEC(pItem);
            pItem = DSNextListNode(p->mpUnknown20, pItem);
        }
        p->mUnknown4 = 1;
    }
}

int fn_80237C78(void *p, void *pKey, void *pOut)
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

Object_80237EE8 *fn_80237CB0(int key, int a, int b, int c)
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

void fn_80237D24(Object_80237EE8 *p)
{
    fn_80237FF4(p);
    DSDelListNode(lbl_803ED030, p);
}

void fn_80237D5C(void *pDst, const void *pSrc, unsigned int size)
{
    char *pOut = pDst;
    const char *pIn = pSrc;
    while (size >= sizeof(Chunk_80237D5C)) {
        *(Chunk_80237D5C *)pOut = *(const Chunk_80237D5C *)pIn;
        pOut += sizeof(Chunk_80237D5C);
        pIn += sizeof(Chunk_80237D5C);
        size -= sizeof(Chunk_80237D5C);
    }
    memcpy(pOut, pIn, size);
}

void fn_80237E3C(int count)
{
    lbl_803ED030 = DSNewList(1, 0, count, sizeof(Object_80237EE8), 0, 0);
}

int fn_80237E78(void)
{
    return DSDelList(lbl_803ED030);
}

Object_80237EE8 *fn_80237E9C(int key)
{
    Object_80237EE8 *pResult;
    if (DSSearchList(lbl_803ED030, 0, &key, &pResult, fn_80237C78) == 2) {
        return pResult;
    }
    return 0;
}

Object_80237EE8 *fn_80237EE8(int key, int count, int size, Config_80237EE8 *pConfig)
{
    Object_80237EE8 *p;

    lbl_803A39FC = *pConfig;
    fn_801D2130(&lbl_803A39FC);
    p = fn_80237CB0(key, count, size, lbl_803A39FC.mUnknown8);
    p->mpUnknown20 = DSNewList(lbl_803A39FC.mUnknown8, 0, count, sizeof(Handle_80237A40),
                                 (int (*)(void *, void *))fn_80237A30, 0);
    return p;
}

void fn_80237F98(Object_80237EE8 *p)
{
    p->mUnknown4 = 0;
}

void fn_80237FA4(Object_80237EE8 *p)
{
    char *pData = fn_801D27B8(p->mUnknown16);
    if (p->mpUnknown24 != 0) {
        fn_80237D5C(p->mpUnknown24, pData, p->mUnknown12);
    }
    fn_80237C0C(p);
}

void fn_80237FF4(Object_80237EE8 *p)
{
    if (p->mpUnknown24 != 0) {
        fn_801D2BD0(p->mpUnknown24);
        p->mpUnknown24 = 0;
    }
}

void fn_80238034(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        fn_80237AFC(pItem);
        pItem = DSNextListNode(p->mpUnknown20, pItem);
    }
}

void fn_8023808C(Object_80237EE8 *p)
{
    Handle_80237A40 *pItem;
    Handle_80237A40 *pNext;

    fn_801D277C(p->mUnknown16);
    pItem = DSGetListNode(p->mpUnknown20, 0);
    while (pItem != 0) {
        fn_80237B34(pItem);
        pNext = DSNextListNode(p->mpUnknown20, pItem);
        DSDelListNode(p->mpUnknown20, pItem);
        pItem = pNext;
    }
    DSDelList(p->mpUnknown20);
    fn_801D277C(1);
    fn_801D2570(p->mUnknown16);
    fn_80237D24(p);
}

Object_80237EE8 *fn_8023811C(Object_80237EE8 *p)
{
    Object_80237EE8 *pFound = fn_80237E9C(p->mUnknown0);
    if (pFound != 0) {
        fn_80237C0C(pFound);
    }
    fn_80237B84(p);
    return pFound;
}

void *fn_8023816C(void *pHandle)
{
    Handle_80237A40 *p = pHandle;
    return p->mpUnknown44;
}

void *fn_80238174(int a, void **ppData, int size, int b, unsigned int id)
{
    Object_80237EE8 *p = fn_80237E9C(a);
    void *pResult = 0;
    if (p != 0) {
        fn_801D277C(p->mUnknown16);
        pResult = fn_80237A40(p, ppData, size, b, id);
    }
    return pResult;
}

void fn_802381E0(void *pHandle)
{
    Handle_80237A40 *p = pHandle;
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16(p->mpUnknown44, 0);
    }
    fn_80237ADC(p);
    fn_801D277C(1);
}

void fn_80238234(void *pHandle, Callback_80238234 pCallback10, Callback_80238234 pCallback14, Callback_80238234 pCallback18, Callback1C_80238234 pCallback1C)
{
    Handle_80237A40 *p = pHandle;
    p->mpUnknown16 = pCallback10;
    p->mpUnknown20 = pCallback14;
    p->mpUnknown24 = pCallback18;
    p->mpUnknown28 = pCallback1C;
}

void fn_80238248(void *pHandle, Callback28_80238248 pCallback28, Callback24_80238248 pCallback24, Callback20_80238248 pCallback20)
{
    Handle_80237A40 *p = pHandle;
    p->mpUnknown32 = pCallback20;
    p->mpUnknown36 = pCallback24;
    p->mpUnknown40 = pCallback28;
}
