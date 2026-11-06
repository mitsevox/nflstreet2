/* The football field object: loads the field model layers (base, overlay, lines, wear and shadow)
   and draws them each frame. */
#include "engine/viewport.h"
#include "game/fn_801EF390.h"
#include "engine/tmtexlib.h"
#include "game/Object_80235588.h"

struct FldObjLayerTex_t {
    char mUnknown0[0x30];
};

struct FldObj_t {
    char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mUnknown10[4];
    void *mpUnknown14;
    int mUnknown18[5];
    Object_80235588 mUnknown2C[6];
    int mUnknown4AC[5];
    FldObjLayerTex_t mUnknown4C0[5];
};

struct FldObjLayerDesc_t {
    const char *mpName;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    int mUnknown10;
    float mUnknown14;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
};

struct FldObjLinePass_t {
    float mUnknown0[3];
    float mUnknownC;
};

extern "C" {
void fn_80044114(void);
void *fn_800A336C(void);
int fn_800A3398(void);
void SimpShadowDrawAll(void);
int ConGetCurrentContext(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
int ObjNewType_(int a, int size, int c, void (*pInit)(FldObj_t *, int *),
                void (*pRelease)(FldObj_t *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(FldObj_t *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
void fn_80234DFC(int a, void *pB, int c, int d, const char *pName, int e);
void fn_80234EA0(void *p, int a);
void fn_802353D8(void *p, int flags);
void fn_802353F8(void *p, int a);
void fn_80235588(void *p, int a);
void fn_802355E4(void *p);
void fn_80235630(void *p, int a);
void fn_80235740(void *p, int a);
void fn_80235764(void *p, int a);
void fn_80235B6C(void *p, void *q, int a);
void fn_80235C48(void *p, int a);
void fn_80235C4C(int a, void *p, float b);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235D0C(void *p, int a);
void fn_80235DB8(int a);
}

static FldObjLayerDesc_t _FldObj_aLayers[5] = {
    { "Base", 1, 1, 0.0f, 0x103, 0.51f, 0, 1 },
    { "Overlay", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Lines", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Degradation", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Shadow", 1, 1, 0.0f, 0x40000B, 0.51f, 0, 1 },
};
static FldObjLinePass_t _FldObj_aLinePasses[1] = {
    { { 0.0f, 0.0f, 0.0f }, 1.0f },
};
static TMTexFilterDesc_t _FldObj_TexFilter = { 5, 1, -4.0f, 0, 0, 1 };
static int _FldObj_iItem = 0;
static float _FldObj_fDegradeScale;

extern "C" {
int FldObjLoadModel(void *pData, int index)
{
    int handle = fn_801EF390(pData, index, 1);

    fn_80235DB8(handle);
    return handle;
}

void FldObjInit(FldObj_t *pObject, int *pArgs)
{
    unsigned int i;

    pObject->mUnknownC = pObject->mUnknown8 = pObject->mUnknown4 = 0.0f;
    pObject->mpUnknown14 = (void *)pArgs[0];
    for (i = 0; i < 5; i++) {
        pObject->mUnknown18[i] = pArgs[i + 1];
        pObject->mUnknown4AC[i] = FldObjLoadModel(pObject->mpUnknown14, pObject->mUnknown18[i]);
        fn_80234DFC(pObject->mUnknown4AC[i], &pObject->mUnknown4C0[i], 0, 0, _FldObj_aLayers[i].mpName,
                    _FldObj_aLayers[i].mUnknown4);
        TMTexLibSetFilterParm((TMTexLib_t *)&pObject->mUnknown4C0[i], &_FldObj_TexFilter);
        fn_80235588(&pObject->mUnknown2C[i], 6);
        fn_80235630(&pObject->mUnknown2C[i], pObject->mUnknown4AC[i]);
        fn_80235B6C(&pObject->mUnknown2C[i], &pObject->mUnknown4C0[i], 1);
        fn_802353D8(&pObject->mUnknown2C[i], _FldObj_aLayers[i].mUnknown10);
        fn_80235C48(&pObject->mUnknown2C[i], _FldObj_aLayers[i].mUnknown8);
        fn_80235D0C(&pObject->mUnknown2C[i], _FldObj_aLayers[i].mUnknown18);
        fn_802353F8(&pObject->mUnknown2C[i], 0);
    }
    fn_80235588(&pObject->mUnknown2C[5], 6);
    fn_80235630(&pObject->mUnknown2C[5], pObject->mUnknown4AC[4]);
    fn_80235B6C(&pObject->mUnknown2C[5], &pObject->mUnknown4C0[4], 1);
    fn_80235C48(&pObject->mUnknown2C[5], _FldObj_aLayers[4].mUnknown8);
    fn_802353F8(&pObject->mUnknown2C[5], 0x20000000);
    fn_802353D8(&pObject->mUnknown2C[5], 0x60040B);
    fn_80235D0C(&pObject->mUnknown2C[5], _FldObj_aLayers[4].mUnknown18);
}

void FldObjRelease(FldObj_t *pObject)
{
    unsigned int i;

    for (i = 0; i < 5; i++) {
        fn_802355E4(&pObject->mUnknown2C[i]);
    }
    fn_802355E4(&pObject->mUnknown2C[5]);
    for (i = 0; i < 5; i++) {
        fn_80234EA0(&pObject->mUnknown4C0[i], _FldObj_aLayers[i].mUnknown4);
        fn_801F010C(pObject->mpUnknown14, pObject->mUnknown18[i]);
    }
}

void FldObjDrawLayer(FldObj_t *pObject, int index, void *pPos, float scale)
{
    Object_80235588 *pSub = &pObject->mUnknown2C[index];
    int handle;

    if (pObject->mUnknown4AC[index] != 0 && _FldObj_aLayers[index].mUnknown19 != 0) {
        handle = ConGetCurrentContext();
        if (pPos != 0) {
            fn_801D04C4();
            fn_801D0C58(pPos);
        }
        fn_80235740(pSub, handle);
        fn_80235C90(pSub, handle, 1.0f, 1.0f, 1.0f, scale * _FldObj_aLayers[index].mUnknown14);
        if (_FldObj_aLayers[index].mUnknownC > 0.0f) {
            fn_80235C4C(handle, pSub, _FldObj_aLayers[index].mUnknownC);
        }
        fn_80235764(pSub, handle);
        if (pPos != 0) {
            fn_801D0544();
        }
    }
}

void FldObjDrawShadowPass(FldObj_t *pObject, float scale, void *pPos)
{
    Object_80235588 *pSub = &pObject->mUnknown2C[5];
    int handle;

    if (pObject->mUnknown4AC[4] != 0 && _FldObj_aLayers[4].mUnknown19 != 0) {
        handle = ConGetCurrentContext();
        if (pPos != 0) {
            fn_801D04C4();
            fn_801D0C58(pPos);
        }
        fn_80235740(pSub, handle);
        fn_80235C90(pSub, handle, 0.5f, 0.5f, 0.5f, scale * _FldObj_aLayers[4].mUnknown14);
        if (_FldObj_aLayers[4].mUnknownC > 0.0f) {
            fn_80235C4C(handle, pSub, _FldObj_aLayers[4].mUnknownC);
        }
        fn_80235764(pSub, handle);
        if (pPos != 0) {
            fn_801D0544();
        }
    }
}

int FldObjRender(FldObj_t *pObject)
{
    unsigned int i;

    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown4);
    FldObjDrawLayer(pObject, 0, 0, 1.0f);
    FldObjDrawLayer(pObject, 1, 0, 1.0f);
    for (i = 0; i < sizeof(_FldObj_aLinePasses) / sizeof(_FldObj_aLinePasses[0]); i++) {
        float scale = _FldObj_aLinePasses[i].mUnknownC;
        FldObjDrawLayer(pObject, 2, &_FldObj_aLinePasses[i], scale);
    }
    FldObjDrawLayer(pObject, 3, 0, _FldObj_fDegradeScale);
    fn_80044114();
    FldObjDrawLayer(pObject, 4, 0, 1.0f);
    FldObjDrawShadowPass(pObject, 1.0f, 0);
    fn_801D0544();
    SimpShadowDrawAll();
    return 0;
}

void FldObjAddObjType(int handle)
{
    int args[6];
    unsigned int i;

    _FldObj_fDegradeScale = 1.0f;
    ObjNewType_(7, sizeof(FldObj_t), 1, FldObjInit, FldObjRelease);
    ObjSetListObjFunc(handle, 7, 0, FldObjRender);
    args[0] = (int)fn_800A336C();
    for (i = 0; i < 5; i++) {
        args[i + 1] = fn_800A3398() + i;
    }
    _FldObj_iItem = ObjNewInList(handle, 7, 0, args);
    ObjSetPriority(handle, _FldObj_iItem, 1);
}

void FldObjRemoveObjType(int handle)
{
    if (_FldObj_iItem != 0) {
        ObjRemoveFromList(handle, _FldObj_iItem);
        VptTrashObject(_FldObj_iItem);
    }
    VptFlushObjectTrashSync();
    ObjDelType(7);
    _FldObj_iItem = 0;
}
}
