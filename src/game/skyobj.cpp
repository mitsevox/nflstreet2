/* The stadium sky: loads the level's sky model and keeps one sky object in the object
   list that draws it each frame. */

#include "engine/viewport.h"
#include "game/fn_801EF390.h"
#include "game/skyobj.h"

extern "C" {
void *fn_800A336C(void);
int fn_800A338C(void);
int ObjNewType_(int type, int size, int count, void *pCreate, void *pDestroy);
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*pCallback)(EnvSkyObj_t *, int));
int ObjNewInList(int handle, int type, int a, void *pInit);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
void fn_80234DFC(int a, void *pB, int c, int d, const char *pName, int e);
void fn_80234EA0(void *p, int a);
void fn_802355E4(void *p);
void fn_80235DB8(int a);

static EnvSkyObj_t *_EnvSkyObj_pSky = 0;

int EnvSkyObjIsActive(void)
{
    return _EnvSkyObj_pSky != 0 && _EnvSkyObj_pSky->mUnknown1CC != 0;
}

int EnvSkyObjDraw(EnvSkyObj_t *pInstance, int a)
{
    if (EnvSkyObjIsActive()) {
        EnvSkyDraw(pInstance, a);
    }
    return 0;
}

void EnvSkyObjLoadModel(EnvSkyObj_t *pInstance)
{
    int handle = fn_801EF390(fn_800A336C(), pInstance->mUnknown1C8, 1);

    fn_80235DB8(handle);
    pInstance->mUnknown14 = handle;
    fn_80234DFC(handle, pInstance->mUnknown18, 0, 0, "SkyObj", 1);
}

void EnvSkyObjFreeModel(EnvSkyObj_t *pInstance)
{
    fn_802355E4(&pInstance->mUnknown48);
    fn_802355E4(&pInstance->mUnknown108);
    fn_80234EA0(pInstance->mUnknown18, 1);
    pInstance->mUnknown14 = 0;
}

void EnvSkyObjCreate(void *pOwner)
{
    EnvSkyObj_t *pItem;

    if (_EnvSkyObj_pSky != 0) {
        return;
    }
    pItem = 0;
    if (ObjNewType_(13, sizeof(EnvSkyObj_t), 1, 0, 0) == 0) {
        ObjSetListObjFunc((int)pOwner, 13, 0, EnvSkyObjDraw);
        pItem = (EnvSkyObj_t *)ObjNewInList((int)pOwner, 13, 0, 0);
        if (pItem != 0) {
            ObjSetPriority((int)pOwner, (int)pItem, 0);
            pItem->mUnknown1CC = 1;
            pItem->mUnknown4.mZ = pItem->mUnknown4.mY = pItem->mUnknown4.mX = 0.0f;
            pItem->mUnknown1C8 = fn_800A338C();
            EnvSkyObjLoadModel(pItem);
            EnvSkyInit(pItem);
        }
    }
    _EnvSkyObj_pSky = pItem;
}

void EnvSkyObjDestroy(void *pOwner)
{
    EnvSkyObj_t *pItem = _EnvSkyObj_pSky;

    if (pItem != 0) {
        EnvSkyShutdown(pItem);
        EnvSkyObjFreeModel(_EnvSkyObj_pSky);
        ObjRemoveFromList((int)pOwner, (int)pItem);
        VptTrashObject((int)pItem);
        VptFlushObjectTrashSync();
        ObjDelType(13);
        _EnvSkyObj_pSky = 0;
    }
}
}
