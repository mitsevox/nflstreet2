/* Quicksort algorithm registered with the sorting front end as sort type 1. */

#include "engine/sort.h"
#include "game/fn_801D2B7C.h"

static void _QuickSwapEl(void *pA, void *pB, void *pTemp, int size);

static void _SortQuickSort(char *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                        void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    char *pStore;
    char *p;
    unsigned int i;
    unsigned int nLess;
    int result;
    int reverse;

    if (count <= 1) {
        return;
    }
    pStore = pBase + ((count - 1) >> 1) * size;
    if (pSwap) {
        pSwap(pBase, pStore);
    } else {
        _QuickSwapEl(pBase, pStore, pTemp, size);
    }
    pStore = pBase;
    nLess = 0;
    reverse = flags & 1;
    for (i = 1, p = pStore + size; i < count; i++, p += size) {
        if (reverse) {
            result = pCompare(p, pBase);
        } else {
            result = pCompare(pBase, p);
        }
        if (result < 0) {
            pStore += size;
            nLess++;
            if (pStore != p) {
                if (pSwap) {
                    pSwap(pStore, p);
                } else {
                    _QuickSwapEl(pStore, p, pTemp, size);
                }
            }
        }
    }
    if (pBase != pStore) {
        if (pSwap) {
            pSwap(pBase, pStore);
        } else {
            _QuickSwapEl(pBase, pStore, pTemp, size);
        }
    }
    if (nLess > 1) {
        _SortQuickSort(pBase, nLess, size, pCompare, pSwap, pTemp, flags);
    }
    if (nLess + 1 < count) {
        _SortQuickSort(pStore + size, count - (nLess + 1), size, pCompare, pSwap, pTemp, flags);
    }
}

static void _SortQuickSortWrapper(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                        void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    void *pBuffer = 0;

    if (pSwap == 0 && size != 4) {
        pBuffer = fn_801D2BB0(1, size, 0, 0);
    }
    _SortQuickSort(pBase, count, size, pCompare, pSwap, pBuffer, flags);
    if (pBuffer) {
        fn_801D2BD0(pBuffer);
    }
}

static void _QuickSwapEl(void *pA, void *pB, void *pTemp, int size)
{
    if (size == 4) {
        int temp = *(int *)pA;
        *(int *)pA = *(int *)pB;
        *(int *)pB = temp;
    } else {
        memcpy(pTemp, pA, size);
        memcpy(pA, pB, size);
        memcpy(pB, pTemp, size);
    }
}

void SortInitQuickModule(void)
{
    SortAddSortType(1, _SortQuickSortWrapper);
}
