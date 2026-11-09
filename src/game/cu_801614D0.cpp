#include "engine/viewport.h"
#include "game/ResLoad.h"
#include "game/Instance_801614D0.h"

extern "C" {
void *fn_800A336C(void);
int fn_800A338C(void);
int ObjNewType_(int type, int size, int count, void *pCreate, void *pDestroy);
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*pCallback)(Instance_801614D0 *, int));
int ObjNewInList(int handle, int type, int a, void *pInit);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
void fn_80234DFC(int a, void *pB, int c, int d, const char *pName, int e);
void fn_80234EA0(void *p, int a);
void fn_802355E4(void *p);
void fn_80235DB8(int a);

static Instance_801614D0 *lbl_803EB380 = 0;

int fn_801614D0(void)
{
    return lbl_803EB380 != 0 && lbl_803EB380->mUnknown1CC != 0;
}

int fn_801614F4(Instance_801614D0 *pInstance, int a)
{
    if (fn_801614D0()) {
        EnvSkyDraw(pInstance, a);
    }
    return 0;
}

void fn_8016153C(Instance_801614D0 *pInstance)
{
    int handle = ResLoad(fn_800A336C(), pInstance->mUnknown1C8, 1);

    fn_80235DB8(handle);
    pInstance->mUnknown14 = handle;
    fn_80234DFC(handle, pInstance->mUnknown18, 0, 0, "SkyObj", 1);
}

void fn_801615A0(Instance_801614D0 *pInstance)
{
    fn_802355E4(&pInstance->mUnknown48);
    fn_802355E4(&pInstance->mUnknown108);
    fn_80234EA0(pInstance->mUnknown18, 1);
    pInstance->mUnknown14 = 0;
}

void fn_801615EC(void *pOwner)
{
    Instance_801614D0 *pItem;

    if (lbl_803EB380 != 0) {
        return;
    }
    pItem = 0;
    if (ObjNewType_(13, sizeof(Instance_801614D0), 1, 0, 0) == 0) {
        ObjSetListObjFunc((int)pOwner, 13, 0, fn_801614F4);
        pItem = (Instance_801614D0 *)ObjNewInList((int)pOwner, 13, 0, 0);
        if (pItem != 0) {
            ObjSetPriority((int)pOwner, (int)pItem, 0);
            pItem->mUnknown1CC = 1;
            pItem->mUnknown4.mZ = pItem->mUnknown4.mY = pItem->mUnknown4.mX = 0.0f;
            pItem->mUnknown1C8 = fn_800A338C();
            fn_8016153C(pItem);
            EnvSkyInit(pItem);
        }
    }
    lbl_803EB380 = pItem;
}

void fn_801616C0(void *pOwner)
{
    Instance_801614D0 *pItem = lbl_803EB380;

    if (pItem != 0) {
        EnvSkyShutdown(pItem);
        fn_801615A0(lbl_803EB380);
        ObjRemoveFromList((int)pOwner, (int)pItem);
        VptTrashObject((int)pItem);
        VptFlushObjectTrashSync();
        ObjDelType(13);
        lbl_803EB380 = 0;
    }
}
}
