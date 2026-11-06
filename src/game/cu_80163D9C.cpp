#include "engine/viewport.h"

extern "C" {
void fn_80146DC4(int a);
int ObjNewType_(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(void *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
}

static unsigned char lbl_803EB3A8 = 1;
static int lbl_803ECAF0;

extern "C" {
int fn_80163D9C(void *pItem)
{
    if (lbl_803EB3A8 != 0) {
        fn_80146DC4(0);
    }
    return 0;
}

void fn_80163DD0(int handle)
{
    ObjNewType_(26, 20, 1, 0, 0);
    ObjSetListObjFunc(handle, 26, 0, fn_80163D9C);
    lbl_803ECAF0 = ObjNewInList(handle, 26, 0, 0);
    ObjSetPriority(handle, lbl_803ECAF0, 13);
}

void fn_80163E54(int handle)
{
    ObjRemoveFromList(handle, lbl_803ECAF0);
    VptTrashObject(lbl_803ECAF0);
    VptFlushObjectTrashSync();
    ObjDelType(26);
    lbl_803ECAF0 = 0;
}
}
