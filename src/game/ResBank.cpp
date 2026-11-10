/* Resource bank: opens a resource file and its numbered sub-files on
   demand and loads their resources, sync or async, keeping a reference
   count on every open file and loaded resource so callers can share them. */

#include "game/ResBank.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/ResLoad.h"

struct ResBankItem_t {
    int mIndex;
    int mRefs;
    int mValue;
    unsigned char mLoaded;
};

struct ResBankFile_t {
    int mKey;
    void *mpData;
    unsigned int mCount;
    int mRefs;
    void *mpEntries;
};

struct ResBank_t {
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
void *ResOpenRam(void *pData, int a, int b, int c);
int ResLoadAsync(void *pData, int index, int a, int b, void (*callback)(void *, int, int, int, ResBank_t *), ResBank_t *pCache);
int ResLoadAll(void *pData, int a, int b);
int ResUnLoadAll(void *pData);
int ResGetNumResources(void *pData);
int ResIsMemoryBacked(void *pData);
}

extern "C" {

int ResBankMatchFileKey(void *pItem, void *pKey, void **ppResult)
{
    if (((ResBankFile_t *)pItem)->mKey == ((ResBankFile_t *)pKey)->mKey) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

int ResBankMatchFileRes(void *pItem, void *pKey, void **ppResult)
{
    if (((ResBankFile_t *)pItem)->mpData == ((ResBankFile_t *)pKey)->mpData) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

int ResBankMatchItemIndex(void *pItem, void *pKey, void **ppResult)
{
    if (((ResBankItem_t *)pItem)->mIndex == ((ResBankItem_t *)pKey)->mIndex) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

ResBankFile_t *ResBankFindFile(ResBank_t *pCache, int key)
{
    ResBankFile_t match;
    ResBankFile_t *pFound = 0;

    match.mKey = key;
    fn_801C6DCC(pCache->mpEntries, 0, &match, &pFound, ResBankMatchFileKey);
    return pFound;
}

ResBankFile_t *ResBankFindFileByRes(ResBank_t *pCache, void *pData)
{
    ResBankFile_t match;
    ResBankFile_t *pFound = 0;

    match.mpData = pData;
    fn_801C6DCC(pCache->mpEntries, 0, &match, &pFound, ResBankMatchFileRes);
    return pFound;
}

ResBankItem_t *ResBankFindItem(ResBankFile_t *pEntry, int index)
{
    ResBankItem_t match;
    ResBankItem_t *pFound = 0;

    match.mIndex = index;
    fn_801C6DCC(pEntry->mpEntries, 0, &match, &pFound, ResBankMatchItemIndex);
    return pFound;
}

void ResBankLoadDone(void *pData, int index, int value, int d, ResBank_t *pCache)
{
    ResBankFile_t *pEntry = ResBankFindFileByRes(pCache, pData);
    if (pEntry) {
        ResBankItem_t *pItem = ResBankFindItem(pEntry, index);
        if (pItem) {
            pItem->mValue = value;
            pItem->mLoaded = 1;
        }
    }
}

void ResBankLoadEntry(ResBank_t *pCache, int key, int index, int async)
{
    ResBankFile_t *pEntry;
    ResBankItem_t *pItem;

    if (pCache == 0 || key == -1) {
        return;
    }
    pEntry = ResBankFindFile(pCache, key);
    if (pEntry == 0) {
        return;
    }
    if (index == -1) {
        ResLoadAll(pEntry->mpData, 1, 1);
        for (index = 0; index < pEntry->mCount; index++) {
            ResBankLoadEntry(pCache, key, index, async);
        }
        return;
    }
    pItem = ResBankFindItem(pEntry, index);
    if (pItem == 0) {
        pItem = (ResBankItem_t *)fn_801C6A20(pEntry->mpEntries);
        pItem->mRefs = 1;
        pItem->mIndex = index;
        fn_801C6AA4(pEntry->mpEntries, pItem, 1);
        if (async && ResIsMemoryBacked(pEntry->mpData) == 0) {
            pItem->mLoaded = 0;
            pItem->mValue = ResLoadAsync(pEntry->mpData, index, pCache->mUnknown0, 100, ResBankLoadDone, pCache);
        } else {
            pItem->mLoaded = 1;
            pItem->mValue = ResLoad(pEntry->mpData, index, pCache->mUnknown0);
        }
    } else {
        pItem->mRefs++;
    }
}

void ResBankUnloadEntry(ResBank_t *pCache, int key, int index)
{
    ResBankFile_t *pEntry;
    unsigned int first;
    unsigned int last;
    int single;

    if (pCache == 0 || key == -1) {
        return;
    }
    pEntry = ResBankFindFile(pCache, key);
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
        ResBankItem_t *pItem = ResBankFindItem(pEntry, index);
        if (pItem) {
            pItem->mRefs--;
            if (!single || pItem->mRefs == 0) {
                ResUnLoad(pEntry->mpData, index);
                fn_801C6C0C(pEntry->mpEntries, pItem);
            }
        }
    }
    if (!single) {
        ResUnLoadAll(pEntry->mpData);
    }
}

ResBank_t *ResBankCreate(ResBankDesc_t *pDesc)
{
    ResBank_t *pCache = 0;

    if (pDesc) {
        pCache = (ResBank_t *)fn_801D2BB0(pDesc->mUnknown0, sizeof(ResBank_t), 0, 0);
        pCache->mUnknown0 = pDesc->mUnknown0;
        pCache->mCount = pDesc->mUnknown4;
        pCache->mpName = pDesc->mUnknown8;
        pCache->mpNames = pDesc->mUnknown12;
        if (pCache->mpName) {
            pCache->mpData = ResOpenDevice(pCache->mpName, 44);
        }
        pCache->mpEntries = fn_801C68FC(pCache->mUnknown0, 0, pCache->mCount, sizeof(ResBankFile_t), 0, 0);
    }
    return pCache;
}

void ResBankDestroy(ResBank_t *pCache)
{
    if (pCache) {
        ResBankCloseFile(pCache, -1);
        if (pCache->mpName) {
            ResClose(pCache->mpData);
        }
        fn_801C69E4(pCache->mpEntries);
        fn_801D2BD0(pCache);
    }
}

void ResBankOpenFile(ResBank_t *pCache, int key)
{
    ResBankFile_t *pEntry;

    if (pCache == 0) {
        return;
    }
    if (key == -1) {
        for (key = 0; key < pCache->mCount; key++) {
            ResBankOpenFile(pCache, key);
        }
        return;
    }
    pEntry = ResBankFindFile(pCache, key);
    if (pEntry == 0) {
        pEntry = (ResBankFile_t *)fn_801C6A20(pCache->mpEntries);
        pEntry->mKey = key;
        if (pCache->mpNames && pCache->mpNames[key]) {
            pEntry->mpData = ResOpenDevice(pCache->mpNames[key], 44);
        } else {
            pEntry->mpData = ResOpenRam(pCache->mpData, key, pCache->mUnknown0, 16);
        }
        pEntry->mCount = ResGetNumResources(pEntry->mpData);
        pEntry->mRefs = 1;
        pEntry->mpEntries = fn_801C68FC(pCache->mUnknown0, 0, pEntry->mCount, sizeof(ResBankItem_t), 0, 0);
        fn_801C6AA4(pCache->mpEntries, pEntry, 1);
    } else {
        pEntry->mRefs++;
    }
}

void ResBankCloseFile(ResBank_t *pCache, int key)
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
        ResBankFile_t *pEntry = ResBankFindFile(pCache, key);
        if (pEntry) {
            pEntry->mRefs--;
            if (!single || pEntry->mRefs == 0) {
                ResBankUnloadEntry(pCache, key, -1);
                ResClose(pEntry->mpData);
                fn_801C69E4(pEntry->mpEntries);
                fn_801C6C0C(pCache->mpEntries, pEntry);
            }
        }
    }
}

void ResBankLoad(ResBank_t *pCache, int key, int index, int async)
{
    if (pCache) {
        ResBankLoadEntry(pCache, key, index, async);
    }
}

void ResBankUnload(ResBank_t *pCache, int key, int index)
{
    if (pCache) {
        ResBankUnloadEntry(pCache, key, index);
    }
}

int ResBankGetData(ResBank_t *pCache, int key, int index)
{
    int value = 0;

    if (pCache) {
        ResBankFile_t *pEntry = ResBankFindFile(pCache, key);
        if (pEntry) {
            ResBankItem_t *pItem = ResBankFindItem(pEntry, index);
            if (pItem && pItem->mLoaded) {
                value = pItem->mValue;
            }
        }
    }
    return value;
}

}
