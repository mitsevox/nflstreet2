#include "game/cu_801882B4.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"

struct Entry_801883B0 {
    int mIndex;
    int mRefs;
    int mValue;
    unsigned char mLoaded;
};

struct Entry_80188320 {
    int mKey;
    void *mpData;
    unsigned int mCount;
    int mRefs;
    void *mpEntries;
};

struct Cache_80188688 {
    int mUnknown0;
    unsigned int mCount;
    char *mpName;
    char **mpNames;
    void *mpData;
    void *mpEntries;
};

extern "C" {
int fn_801C6DCC(void *pPool, int a, void *pKey, void *pResult, int (*match)(void *, void *, void **));
void *fn_801C6A20(void *pPool);
void fn_801C6C0C(void *pPool, void *pItem);
void *fn_801D2BB0(int a, int size, int c, int d);
void *fn_801EECD0(void *pData, int a, int b, int c);
int fn_801EF548(void *pData, int index, int a, int b, void (*callback)(void *, int, int, int, Cache_80188688 *), Cache_80188688 *pCache);
int fn_801F02AC(void *pData, int a, int b);
int fn_801F08FC(void *pData);
int fn_801F0D34(void *pData);
int fn_801F1008(void *pData);
}

extern "C" {

int fn_801882B4(void *pItem, void *pKey, void **ppResult)
{
    if (((Entry_80188320 *)pItem)->mKey == ((Entry_80188320 *)pKey)->mKey) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

int fn_801882D8(void *pItem, void *pKey, void **ppResult)
{
    if (((Entry_80188320 *)pItem)->mpData == ((Entry_80188320 *)pKey)->mpData) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

int fn_801882FC(void *pItem, void *pKey, void **ppResult)
{
    if (((Entry_801883B0 *)pItem)->mIndex == ((Entry_801883B0 *)pKey)->mIndex) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

Entry_80188320 *fn_80188320(Cache_80188688 *pCache, int key)
{
    Entry_80188320 match;
    Entry_80188320 *pFound = 0;

    match.mKey = key;
    fn_801C6DCC(pCache->mpEntries, 0, &match, &pFound, fn_801882B4);
    return pFound;
}

Entry_80188320 *fn_80188368(Cache_80188688 *pCache, void *pData)
{
    Entry_80188320 match;
    Entry_80188320 *pFound = 0;

    match.mpData = pData;
    fn_801C6DCC(pCache->mpEntries, 0, &match, &pFound, fn_801882D8);
    return pFound;
}

Entry_801883B0 *fn_801883B0(Entry_80188320 *pEntry, int index)
{
    Entry_801883B0 match;
    Entry_801883B0 *pFound = 0;

    match.mIndex = index;
    fn_801C6DCC(pEntry->mpEntries, 0, &match, &pFound, fn_801882FC);
    return pFound;
}

void fn_801883F8(void *pData, int index, int value, int d, Cache_80188688 *pCache)
{
    Entry_80188320 *pEntry = fn_80188368(pCache, pData);
    if (pEntry) {
        Entry_801883B0 *pItem = fn_801883B0(pEntry, index);
        if (pItem) {
            pItem->mValue = value;
            pItem->mLoaded = 1;
        }
    }
}

void fn_80188458(Cache_80188688 *pCache, int key, int index, int async)
{
    Entry_80188320 *pEntry;
    Entry_801883B0 *pItem;

    if (pCache == 0 || key == -1) {
        return;
    }
    pEntry = fn_80188320(pCache, key);
    if (pEntry == 0) {
        return;
    }
    if (index == -1) {
        fn_801F02AC(pEntry->mpData, 1, 1);
        for (index = 0; index < pEntry->mCount; index++) {
            fn_80188458(pCache, key, index, async);
        }
        return;
    }
    pItem = fn_801883B0(pEntry, index);
    if (pItem == 0) {
        pItem = (Entry_801883B0 *)fn_801C6A20(pEntry->mpEntries);
        pItem->mRefs = 1;
        pItem->mIndex = index;
        fn_801C6AA4(pEntry->mpEntries, pItem, 1);
        if (async && fn_801F1008(pEntry->mpData) == 0) {
            pItem->mLoaded = 0;
            pItem->mValue = fn_801EF548(pEntry->mpData, index, pCache->mUnknown0, 100, fn_801883F8, pCache);
        } else {
            pItem->mLoaded = 1;
            pItem->mValue = fn_801EF390(pEntry->mpData, index, pCache->mUnknown0);
        }
    } else {
        pItem->mRefs++;
    }
}

void fn_801885A4(Cache_80188688 *pCache, int key, int index)
{
    Entry_80188320 *pEntry;
    unsigned int first;
    unsigned int last;
    int single;

    if (pCache == 0 || key == -1) {
        return;
    }
    pEntry = fn_80188320(pCache, key);
    if (pEntry == 0) {
        return;
    }
    if (index == -1) {
        first = 0;
        last = pEntry->mCount;
        single = 0;
    } else {
        first = index;
        last = index + 1;
        single = 1;
    }
    for (index = first; index < last; index++) {
        Entry_801883B0 *pItem = fn_801883B0(pEntry, index);
        if (pItem) {
            pItem->mRefs--;
            if (!single || pItem->mRefs == 0) {
                fn_801F010C(pEntry->mpData, index);
                fn_801C6C0C(pEntry->mpEntries, pItem);
            }
        }
    }
    if (!single) {
        fn_801F08FC(pEntry->mpData);
    }
}

Cache_80188688 *fn_80188688(Desc_80188688 *pDesc)
{
    Cache_80188688 *pCache = 0;

    if (pDesc) {
        pCache = (Cache_80188688 *)fn_801D2BB0(pDesc->mUnknown0, sizeof(Cache_80188688), 0, 0);
        pCache->mUnknown0 = pDesc->mUnknown0;
        pCache->mCount = pDesc->mUnknown4;
        pCache->mpName = pDesc->mUnknown8;
        pCache->mpNames = pDesc->mUnknown12;
        if (pCache->mpName) {
            pCache->mpData = fn_801EEB44(pCache->mpName, 44);
        }
        pCache->mpEntries = fn_801C68FC(pCache->mUnknown0, 0, pCache->mCount, sizeof(Entry_80188320), 0, 0);
    }
    return pCache;
}

void fn_80188728(Cache_80188688 *pCache)
{
    if (pCache) {
        fn_801888A4(pCache, -1);
        if (pCache->mpName) {
            fn_801EEFAC(pCache->mpData);
        }
        fn_801C69E4(pCache->mpEntries);
        fn_801D2BD0(pCache);
    }
}

void fn_80188784(Cache_80188688 *pCache, int key)
{
    Entry_80188320 *pEntry;

    if (pCache == 0) {
        return;
    }
    if (key == -1) {
        for (key = 0; key < pCache->mCount; key++) {
            fn_80188784(pCache, key);
        }
        return;
    }
    pEntry = fn_80188320(pCache, key);
    if (pEntry == 0) {
        pEntry = (Entry_80188320 *)fn_801C6A20(pCache->mpEntries);
        pEntry->mKey = key;
        if (pCache->mpNames && pCache->mpNames[key]) {
            pEntry->mpData = fn_801EEB44(pCache->mpNames[key], 44);
        } else {
            pEntry->mpData = fn_801EECD0(pCache->mpData, key, pCache->mUnknown0, 16);
        }
        pEntry->mCount = fn_801F0D34(pEntry->mpData);
        pEntry->mRefs = 1;
        pEntry->mpEntries = fn_801C68FC(pCache->mUnknown0, 0, pEntry->mCount, sizeof(Entry_801883B0), 0, 0);
        fn_801C6AA4(pCache->mpEntries, pEntry, 1);
    } else {
        pEntry->mRefs++;
    }
}

void fn_801888A4(Cache_80188688 *pCache, int key)
{
    unsigned int first;
    unsigned int last;
    int single;

    if (pCache == 0) {
        return;
    }
    if (key == -1) {
        first = 0;
        last = pCache->mCount;
        single = 0;
    } else {
        first = key;
        last = key + 1;
        single = 1;
    }
    for (key = first; key < last; key++) {
        Entry_80188320 *pEntry = fn_80188320(pCache, key);
        if (pEntry) {
            pEntry->mRefs--;
            if (!single || pEntry->mRefs == 0) {
                fn_801885A4(pCache, key, -1);
                fn_801EEFAC(pEntry->mpData);
                fn_801C69E4(pEntry->mpEntries);
                fn_801C6C0C(pCache->mpEntries, pEntry);
            }
        }
    }
}

void fn_8018897C(Cache_80188688 *pCache, int key, int index, int async)
{
    if (pCache) {
        fn_80188458(pCache, key, index, async);
    }
}

void fn_801889A4(Cache_80188688 *pCache, int key, int index)
{
    if (pCache) {
        fn_801885A4(pCache, key, index);
    }
}

int fn_801889CC(Cache_80188688 *pCache, int key, int index)
{
    int value = 0;

    if (pCache) {
        Entry_80188320 *pEntry = fn_80188320(pCache, key);
        if (pEntry) {
            Entry_801883B0 *pItem = fn_801883B0(pEntry, index);
            if (pItem && pItem->mLoaded) {
                value = pItem->mValue;
            }
        }
    }
    return value;
}

}
