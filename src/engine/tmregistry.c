#include "engine/tmlib.h"

static void fn_8021283C(RegistryEntry_8021283C *pDst, RegistryEntry_8021283C *pSrc)
{
    pDst->mpName = pSrc->mpName;
    pDst->mpData = pSrc->mpData;
}

void fn_80212850(Registry_8021283C *pRegistry, int maxEntries, int bAppend, int bPaths)
{
    pRegistry->mMaxEntries = maxEntries;
    pRegistry->mpEntries = fn_802127D0(maxEntries, sizeof(RegistryEntry_8021283C));
    pRegistry->mbAppend = bAppend;
    pRegistry->mbPaths = bPaths;
    fn_802128DC(pRegistry);
}

void fn_802128A8(Registry_8021283C *pRegistry)
{
    pRegistry->mMaxEntries = 0;
    pRegistry->mNumEntries = 0;
    fn_80212814(pRegistry->mpEntries);
}

void fn_802128DC(Registry_8021283C *pRegistry)
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

void fn_80212940(Registry_8021283C *pRegistry, int index, const char *pName, void *pData)
{
    pRegistry->mpEntries[index].mpName = pName;
    pRegistry->mpEntries[index].mpData = pData;
}

void fn_8021295C(Registry_8021283C *pRegistry, const char *pName, void *pData)
{
    int index;

    index = fn_802129B8(pRegistry, pName);
    if (index == -1) {
        index = pRegistry->mNumEntries++;
    }
    fn_80212940(pRegistry, index, pName, pData);
}

int fn_802129B8(Registry_8021283C *pRegistry, const char *pName)
{
    RegistryEntry_8021283C *pEntries;
    int count;
    int i;

    if ((unsigned int)pName > 0xFEFFFFFF) {
        return (int)pName + 0x01000000;
    }
    count = pRegistry->mNumEntries;
    pEntries = pRegistry->mpEntries;
    for (i = 0; i < count; i++) {
        if (pEntries[i].mpName != 0 && fn_802126C0(pEntries[i].mpName, pName)) {
            return i;
        }
    }
    return -1;
}

void fn_80212A48(Registry_8021283C *pRegistry, int index)
{
    pRegistry->mpEntries[index].mpName = 0;
    pRegistry->mpEntries[index].mpData = 0;
    if (pRegistry->mbAppend) {
        pRegistry->mNumEntries--;
        fn_8021283C(&pRegistry->mpEntries[index], &pRegistry->mpEntries[pRegistry->mNumEntries]);
    }
}

void fn_80212AB0(Registry_8021283C *pRegistry, const char *pName)
{
    int index;

    index = fn_802129B8(pRegistry, pName);
    if (index >= 0) {
        fn_80212A48(pRegistry, index);
    }
}

void *fn_80212AEC(Registry_8021283C *pRegistry, int index)
{
    if (index >= 0 && index < pRegistry->mNumEntries) {
        return pRegistry->mpEntries[index].mpData;
    }
    return 0;
}

void *fn_80212B1C(Registry_8021283C *pRegistry, char **ppNames, int depth, int numNames)
{
    void *pData;
    int i;

    if (depth < numNames) {
        if (!pRegistry->mbPaths) {
            return fn_80212C60(pRegistry, ppNames[depth]);
        }
        for (i = 0; i < pRegistry->mNumEntries; i++) {
            RegistryEntry_8021283C *pEntry = &pRegistry->mpEntries[i];

            if (fn_802126E8(ppNames[depth], pEntry->mpName)) {
                pData = fn_80212B1C(pEntry->mpData, ppNames, depth + 1, numNames);
                if (pData != 0) {
                    return pData;
                }
            }
        }
    }
    return 0;
}

void *fn_80212BDC(Registry_8021283C *pRegistry, const char *pPath)
{
    char aaName[2][64];
    char *apName[2];
    int i;

    if ((unsigned int)pPath > 0xFEFFFFFF) {
        return 0;
    }
    fn_8021272C(pPath, aaName[0], aaName[1]);
    for (i = 0; i < 2; i++) {
        apName[i] = aaName[i];
    }
    return fn_80212B1C(pRegistry, apName, 0, 2);
}

void *fn_80212C60(Registry_8021283C *pRegistry, const char *pName)
{
    int index;

    index = fn_802129B8(pRegistry, pName);
    if (index >= 0) {
        return pRegistry->mpEntries[index].mpData;
    }
    return 0;
}

int fn_80212CAC(Registry_8021283C *pRegistry)
{
    return pRegistry->mNumEntries;
}
