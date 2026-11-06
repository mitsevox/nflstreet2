/* Generic sorting front end: keeps a table of sort algorithms by type and sorts an array of
   elements of any size with the caller's compare and swap callbacks. */

#include "engine/sort.h"
#include "engine/system.h"

typedef struct SortInterface_t {
    SortFunc_t pSort;
    unsigned char bActive;
} SortInterface_t;

extern SortInterface_t lbl_803E943C[2];
extern unsigned char lbl_803EBE20;

static void _SortInitInterface(void)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        lbl_803E943C[i].bActive = 0;
    }
}

int SortInit(void)
{
    int err = 0;

    if (!lbl_803EBE20) {
        _SortInitInterface();
        SortInitBubbleModule();
        SortInitQuickModule();
        lbl_803EBE20 = 1;
    } else {
        err = 0x170001;
    }
    fn_801F7BD4(err);
    return err;
}

int SortShutdown(void)
{
    int err = 0;

    if (lbl_803EBE20) {
        lbl_803EBE20 = 0;
    } else {
        err = 0x170002;
    }
    fn_801F7BD4(err);
    return err;
}

void SortArray(int type, void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                 void (*pSwap)(void *, void *), void *pTemp, int flags)
{
    lbl_803E943C[type].pSort(pBase, count, size, pCompare, pSwap, pTemp, flags);
}

void SortAddSortType(int type, SortFunc_t pSort)
{
    lbl_803E943C[type].pSort = pSort;
    lbl_803E943C[type].bActive = 1;
}
