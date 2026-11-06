/* TM renderer registries: fixed-size name-to-data tables, optionally nested and searched by
   wildcard path, behind the shader and texture libraries. */

#include "engine/tmlib.h"

static void _TMRegistryCopyEntry(TMRegistryEntry_t *pDst, TMRegistryEntry_t *pSrc)
{
    pDst->mpName = pSrc->mpName;
    pDst->mpData = pSrc->mpData;
}

void TMRegistryAlloc(TMRegistry_t *pRegistry, int maxEntries, int bAppend, int bPaths)
{
    pRegistry->mMaxEntries = maxEntries;
    pRegistry->mpEntries = TMMemAllocArray(maxEntries, sizeof(TMRegistryEntry_t));
    pRegistry->mbAppend = bAppend;
    pRegistry->mbPaths = bPaths;
    TMRegistryReset(pRegistry);
}

void TMRegistryFree(TMRegistry_t *pRegistry)
{
    pRegistry->mMaxEntries = 0;
    pRegistry->mNumEntries = 0;
    TMMemFreeArray(pRegistry->mpEntries);
}

void TMRegistryReset(TMRegistry_t *pRegistry)
{
    int i;

    for (i = 0; i < pRegistry->mMaxEntries; i++) {
        pRegistry->mpEntries[i].mpName = 0;
        pRegistry->mpEntries[i].mpData = 0;
    }
    if (pRegistry->mbAppend) {
        pRegistry->mNumEntries = 0;
    } else {
        pRegistry->mNumEntries = pRegistry->mMaxEntries;
    }
}

void TMRegistrySetEntry(TMRegistry_t *pRegistry, int index, const char *pName, void *pData)
{
    pRegistry->mpEntries[index].mpName = pName;
    pRegistry->mpEntries[index].mpData = pData;
}

void TMRegistryAddEntry(TMRegistry_t *pRegistry, const char *pName, void *pData)
{
    int index;

    index = TMRegistryGetIndexByName(pRegistry, pName);
    if (index == -1) {
        index = pRegistry->mNumEntries++;
    }
    TMRegistrySetEntry(pRegistry, index, pName, pData);
}

int TMRegistryGetIndexByName(TMRegistry_t *pRegistry, const char *pName)
{
    TMRegistryEntry_t *pEntries;
    int count;
    int i;

    if ((unsigned int)pName > 0xFEFFFFFF) {
        return (int)pName + 0x01000000;
    }
    count = pRegistry->mNumEntries;
    pEntries = pRegistry->mpEntries;
    for (i = 0; i < count; i++) {
        if (pEntries[i].mpName != 0 && TMNameCompareExact(pEntries[i].mpName, pName)) {
            return i;
        }
    }
    return -1;
}

void TMRegistryRemoveEntryByIndex(TMRegistry_t *pRegistry, int index)
{
    pRegistry->mpEntries[index].mpName = 0;
    pRegistry->mpEntries[index].mpData = 0;
    if (pRegistry->mbAppend) {
        pRegistry->mNumEntries--;
        _TMRegistryCopyEntry(&pRegistry->mpEntries[index], &pRegistry->mpEntries[pRegistry->mNumEntries]);
    }
}

void TMRegistryRemoveEntryByName(TMRegistry_t *pRegistry, const char *pName)
{
    int index;

    index = TMRegistryGetIndexByName(pRegistry, pName);
    if (index >= 0) {
        TMRegistryRemoveEntryByIndex(pRegistry, index);
    }
}

void *TMRegistryGetDataByIndex(TMRegistry_t *pRegistry, int index)
{
    if (index >= 0 && index < pRegistry->mNumEntries) {
        return pRegistry->mpEntries[index].mpData;
    }
    return 0;
}

void *TMRegistrySearch(TMRegistry_t *pRegistry, char **ppNames, int depth, int numNames)
{
    void *pData;
    int i;

    if (depth < numNames) {
        if (!pRegistry->mbPaths) {
            return TMRegistryGetDataByName(pRegistry, ppNames[depth]);
        }
        for (i = 0; i < pRegistry->mNumEntries; i++) {
            TMRegistryEntry_t *pEntry = &pRegistry->mpEntries[i];

            if (TMNameCompareWildcard(ppNames[depth], pEntry->mpName)) {
                pData = TMRegistrySearch(pEntry->mpData, ppNames, depth + 1, numNames);
                if (pData != 0) {
                    return pData;
                }
            }
        }
    }
    return 0;
}

void *TMRegistrySearchPath(TMRegistry_t *pRegistry, const char *pPath)
{
    char aaName[2][64];
    char *apName[2];
    int i;

    if ((unsigned int)pPath > 0xFEFFFFFF) {
        return 0;
    }
    TMNameSplitPath(pPath, aaName[0], aaName[1]);
    for (i = 0; i < 2; i++) {
        apName[i] = aaName[i];
    }
    return TMRegistrySearch(pRegistry, apName, 0, 2);
}

void *TMRegistryGetDataByName(TMRegistry_t *pRegistry, const char *pName)
{
    int index;

    index = TMRegistryGetIndexByName(pRegistry, pName);
    if (index >= 0) {
        return pRegistry->mpEntries[index].mpData;
    }
    return 0;
}

int TMRegistryGetNumEntries(TMRegistry_t *pRegistry)
{
    return pRegistry->mNumEntries;
}
