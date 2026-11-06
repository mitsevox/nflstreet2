#include "engine/viewport.h"
#include "game/fn_801EF390.h"

/* 228-byte object allocated through ObjNewType_ by ReplayCursorCreate; a single
   instance is kept in sObject. */
struct ReplayCursor_t {
    int mUnknown0;
    float mUnknown4[3];
    int mUnknown16;
    void *mUnknown20;
    int mUnknown24;
    unsigned char mUnknown28[192];
    int mUnknown220;
    unsigned char mUnknown224;
};

extern "C" {
int fn_800C47C4(void);
int ConGetCurrentContext(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
int ObjNewType_(int a, int size, int c, void (*pInit)(ReplayCursor_t *, int *),
                void (*pRelease)(ReplayCursor_t *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(ReplayCursor_t *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, ReplayCursor_t *pObject);
void ObjSetPriority(int handle, ReplayCursor_t *pObject, int b);
void TMRenderBindTexture(int a, int b, int c);
void fn_802353D8(void *p, int flags);
void fn_80235588(void *p, int a);
void fn_802355E4(void *p);
void fn_80235630(void *p, int a);
void fn_80235740(void *p, int a);
void fn_80235764(void *p, int a);
void fn_80235C48(void *p, int a);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235DB8(int a);
}

static ReplayCursor_t *sObject = 0;

extern "C" {
void ReplayCursorObjInit(ReplayCursor_t *pObject, int *pArgs)
{
    pObject->mUnknown4[0] = 0.0f;
    pObject->mUnknown4[1] = 0.0f;
    pObject->mUnknown4[2] = 0.01f;
    pObject->mUnknown224 = 0;
    pObject->mUnknown20 = (void *)pArgs[0];
    pObject->mUnknown24 = pArgs[1];
    pObject->mUnknown220 = fn_801EF390(pObject->mUnknown20, pObject->mUnknown24, 1);
    fn_80235DB8(pObject->mUnknown220);
    fn_80235588(pObject->mUnknown28, 6);
    fn_80235630(pObject->mUnknown28, pObject->mUnknown220);
    fn_80235C48(pObject->mUnknown28, 3);
    fn_802353D8(pObject->mUnknown28, 0x400008);
}

void ReplayCursorObjRelease(ReplayCursor_t *pObject)
{
    fn_802355E4(pObject->mUnknown28);
    if (pObject->mUnknown220 != 0) {
        if (fn_801F0DB8(pObject->mUnknown20, pObject->mUnknown24)) {
            fn_801F010C(pObject->mUnknown20, pObject->mUnknown24);
        }
    }
}

int ReplayCursorObjDraw(ReplayCursor_t *pObject)
{
    float v[3];

    if (pObject->mUnknown220 != 0 && pObject->mUnknown224 == 1) {
        fn_801D0470(VptGetMatrixStack());
        fn_801D04C4();
        v[0] = pObject->mUnknown4[0];
        v[1] = pObject->mUnknown4[1];
        v[2] = 0.0f;
        fn_801D0C58(v);
        fn_80235740(pObject->mUnknown28, ConGetCurrentContext());
        fn_801D0470(VptGetMatrixStack());
        fn_801D0544();
        fn_80235C90(pObject->mUnknown28, ConGetCurrentContext(), 0.25f, 0.25f, 0.75f, 1.0f);
        TMRenderBindTexture(0, 0, 0);
        fn_80235764(pObject->mUnknown28, ConGetCurrentContext());
    }
    return 0;
}

void ReplayCursorCreate(int handle)
{
    int desc[2];

    ObjNewType_(10, sizeof(ReplayCursor_t), 1, ReplayCursorObjInit, ReplayCursorObjRelease);
    ObjSetListObjFunc(handle, 10, 0, ReplayCursorObjDraw);
    desc[0] = fn_800C47C4();
    desc[1] = 7;
    sObject = (ReplayCursor_t *)ObjNewInList(handle, 10, 0, desc);
    ObjSetPriority(handle, sObject, 3);
}

void ReplayCursorDestroy(int handle)
{
    if (sObject != 0) {
        ObjRemoveFromList(handle, sObject);
        VptTrashObject((int)sObject);
    }
    VptFlushObjectTrashSync();
    ObjDelType(10);
}

void ReplayCursorSetPos(const float *pValue, int)
{
    ReplayCursor_t *pObject = sObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown4[0] = pValue[0];
    pObject->mUnknown4[1] = pValue[1];
    pObject->mUnknown4[2] = pValue[2];
}

void ReplayCursorSetVisible(unsigned char value)
{
    ReplayCursor_t *pObject = sObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown224 = value;
}

int ReplayCursorGetPos(float *pValue)
{
    ReplayCursor_t *pObject = sObject;
    int result = 0;

    if (pObject->mUnknown224 != 0) {
        result = 1;
        pValue[0] = pObject->mUnknown4[0];
        pValue[1] = pObject->mUnknown4[1];
        pValue[2] = pObject->mUnknown4[2];
    }
    return result;
}
}
