/* Replay camera cursor: the marker drawn at the point the free replay
   camera looks at. The replay code moves it and shows or hides it, and
   the sound code reads its position while it is shown. */
#include "engine/cu_80227F14.h"
#include "game/fn_801EF390.h"

/* 228-byte object allocated through fn_801DCF0C by ReplayCursorCreate; the
   single instance is kept in _ReplayCursor_pObject. */
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
int fn_801C657C(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(ReplayCursor_t *, int *),
                void (*pRelease)(ReplayCursor_t *));
int fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(ReplayCursor_t *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, ReplayCursor_t *pObject);
void fn_801DD3AC(int handle, ReplayCursor_t *pObject, int b);
void fn_80210814(int a, int b, int c);
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

static ReplayCursor_t *_ReplayCursor_pObject = 0;

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
        fn_801D0470(fn_80228668());
        fn_801D04C4();
        v[0] = pObject->mUnknown4[0];
        v[1] = pObject->mUnknown4[1];
        v[2] = 0.0f;
        fn_801D0C58(v);
        fn_80235740(pObject->mUnknown28, fn_801C657C());
        fn_801D0470(fn_80228668());
        fn_801D0544();
        fn_80235C90(pObject->mUnknown28, fn_801C657C(), 0.25f, 0.25f, 0.75f, 1.0f);
        fn_80210814(0, 0, 0);
        fn_80235764(pObject->mUnknown28, fn_801C657C());
    }
    return 0;
}

void ReplayCursorCreate(int handle)
{
    int desc[2];

    fn_801DCF0C(10, sizeof(ReplayCursor_t), 1, ReplayCursorObjInit, ReplayCursorObjRelease);
    fn_801DD0C8(handle, 10, 0, ReplayCursorObjDraw);
    desc[0] = fn_800C47C4();
    desc[1] = 7;
    _ReplayCursor_pObject = (ReplayCursor_t *)fn_801DD268(handle, 10, 0, desc);
    fn_801DD3AC(handle, _ReplayCursor_pObject, 3);
}

void ReplayCursorDestroy(int handle)
{
    if (_ReplayCursor_pObject != 0) {
        fn_801DD320(handle, _ReplayCursor_pObject);
        fn_80228D58((int)_ReplayCursor_pObject);
    }
    fn_80228E18();
    fn_801DCF8C(10);
}

void ReplayCursorSetPos(const float *pValue, int)
{
    ReplayCursor_t *pObject = _ReplayCursor_pObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown4[0] = pValue[0];
    pObject->mUnknown4[1] = pValue[1];
    pObject->mUnknown4[2] = pValue[2];
}

void ReplayCursorSetVisible(unsigned char value)
{
    ReplayCursor_t *pObject = _ReplayCursor_pObject;

    if (pObject == 0) {
        return;
    }
    pObject->mUnknown224 = value;
}

int ReplayCursorGetPos(float *pValue)
{
    ReplayCursor_t *pObject = _ReplayCursor_pObject;
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
