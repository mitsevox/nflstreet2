/* 3D models shown in the user interface screens: loads them from the UIS libraries,
   swaps in their textures and draws them at a given position, rotation and scale. */

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXCull.h>
#include "engine/viewport.h"
#include "game/ResBank.h"
#include "game/UISModel.h"

extern "C" {
ResBank_t *_UISModel_pLibCache = 0;
extern char *lbl_802EAD10[];
int FELoopIsMainFEActive(void);
int ConGetCurrentContext(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D08FC(int);
void fn_801D09EC(int);
void fn_801D0ADC(int);
void fn_801D0C58(void *);
void fn_801D0D94(float, float, float);
int ObjNewType_(int, int, int, void (*)(UISModel_t *, UISModelDesc_t *), void (*)(UISModel_t *));
int ObjDelType(int);
int ObjSetListObjFunc(void *, int, int, int (*)(UISModel_t *, int));
void fn_80234DFC(int, void *, int, int, const char *, int);
void fn_80234EA0(void *, int);
void fn_80234EEC(void *, int, void *, unsigned char);
void fn_80234F74(void *, int, void *, unsigned char, int);
void fn_802353D8(void *, int);
void fn_802353E8(void *, int);
void fn_80235588(void *, int);
void fn_802355E4(void *);
void fn_80235630(void *, int);
void fn_80235740(void *, int);
void fn_80235764(void *, int);
void fn_80235788(void *, int, int);
void fn_80235C24(void *, void *);
void fn_80235C90(void *, int, float, float, float, float);
void fn_80235D10(void *, float);
void fn_80235D74(void *, int);
int fn_80235D9C(int);
void fn_80235DB8(int);
int fn_80236B4C(int);

void UISModelBind(UISModel_t *pObject, UISModelDesc_t *pDesc)
{
    int data = ResBankGetData(_UISModel_pLibCache, pDesc->mUnknown00, pDesc->mUnknown02);
    pObject->mUnknown198 |= 1;
    if (pObject->mUnknown198 & 1) {
        pObject->mUnknown14 = data;
        fn_80235DB8(data);
        if (fn_80235D9C(pObject->mUnknown14) == 0) {
            pObject->mUnknown14 = 0;
        }
        fn_80235588(&pObject->mUnknown48, 6);
        fn_80235630(&pObject->mUnknown48, pObject->mUnknown14);
        fn_80234DFC(pObject->mUnknown14, pObject->mUnknown18, 0, 0, "UISModel", 0);
        fn_80235C24(&pObject->mUnknown48, pObject->mUnknown18);
        if (FELoopIsMainFEActive()) {
            if (pObject->mUnknown1CE == 26) {
                fn_80235D10(&pObject->mUnknown48, 15000.0f);
                fn_802353E8(&pObject->mUnknown48, 0x4000);
            } else {
                fn_80235D10(&pObject->mUnknown48, 0.0f);
            }
        } else {
            fn_80235D10(&pObject->mUnknown48, 20000.0f);
        }
    }
}

void UISModelInit(UISModel_t *pObject, UISModelDesc_t *pDesc)
{
    pObject->mUnknown04 = 0.0f;
    pObject->mUnknown08 = 0.0f;
    pObject->mUnknown0C = 0.0f;
    pObject->mUnknown1CC = pDesc->mUnknown00;
    pObject->mUnknown1CE = pDesc->mUnknown02;
    pObject->mUnknown19C = pDesc->mUnknown04;
    pObject->mUnknown1B4 = pDesc->mUnknown1C;
    pObject->mUnknown1C0 = pDesc->mUnknown28;
    pObject->mUnknown1A8 = (int)(pDesc->mUnknown10.mX * 46603.37890625f);
    pObject->mUnknown1AC = (int)(pDesc->mUnknown10.mY * 46603.37890625f);
    pObject->mUnknown1B0 = (int)(pDesc->mUnknown10.mZ * 46603.37890625f);
    pObject->mUnknown1D4 = 0;
    pObject->mUnknown1D0 = 0.0f;
    pObject->mUnknown1DC = pObject->mUnknown1DA = pObject->mUnknown1D8 = -1;
    pObject->mUnknown1DE = 0;
    pObject->mUnknown198 = 0;
    pObject->mUnknown1E4 = 255;
    ResBankOpenFile(_UISModel_pLibCache, pDesc->mUnknown00);
    ResBankLoad(_UISModel_pLibCache, pDesc->mUnknown00, pDesc->mUnknown02, 0);
    UISModelBind(pObject, pDesc);
}

void UISModelFree(UISModel_t *pObject)
{
    if (pObject->mUnknown198 & 1) {
        fn_802355E4(&pObject->mUnknown48);
        fn_80234EA0(pObject->mUnknown18, 0);
    }
    ResBankUnload(_UISModel_pLibCache, pObject->mUnknown1CC, pObject->mUnknown1CE);
    ResBankCloseFile(_UISModel_pLibCache, pObject->mUnknown1CC);
}

int UISModelDraw(UISModel_t *pObject, int value)
{
    int context = ConGetCurrentContext();
    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown19C);
    fn_801D08FC(pObject->mUnknown1A8);
    fn_801D09EC(pObject->mUnknown1AC);
    fn_801D0ADC(pObject->mUnknown1B0);
    fn_801D0D94(pObject->mUnknown1C0.mX, pObject->mUnknown1C0.mY, pObject->mUnknown1C0.mZ);
    if (pObject->mUnknown198 & 1) {
        if (pObject->mUnknown1E4 == 255) {
            fn_80235740(&pObject->mUnknown48, context);
            if (pObject->mUnknown1D4) {
                fn_802353E8(&pObject->mUnknown48, 0x20000);
            }
            fn_80235788(&pObject->mUnknown48, context, fn_80236B4C(5));
        } else {
            GXSetCullMode(GX_CULL_FRONT);
            fn_80235C90(&pObject->mUnknown48, context, 0.5f, 0.5f, 0.5f, 0.0f);
            fn_80235740(&pObject->mUnknown48, context);
            fn_80235764(&pObject->mUnknown48, context);
            fn_802353D8(&pObject->mUnknown48, 0x100);
            fn_80235C90(&pObject->mUnknown48, context, 0.5f, 0.5f, 0.5f, 0.2f);
            fn_802353D8(&pObject->mUnknown48, 2);
            fn_80235740(&pObject->mUnknown48, context);
            fn_80235764(&pObject->mUnknown48, context);
            fn_802353E8(&pObject->mUnknown48, 0x100);
            GXSetCullMode(GX_CULL_NONE);
        }
        fn_801D0470(VptGetMatrixStack());
        fn_801D0544();
    }
    return 0;
}

void UISModelCopyTexture(UISModel_t *pObject, void *pData, int index, int component)
{
    if (pObject->mUnknown198 & 1) {
        UISModelRender_t *pState = &pObject->mUnknown48;
        unsigned char part = component;
        fn_80234EEC(pState, index, pData, part);
        fn_80234F74(pState->mpUnknown58, index, pData, part, 0);
    }
}

void UISModelApplyTextures(UISModel_t *pObject, void *pData)
{
    UISModelCopyTexture(pObject, pData, 4, 0);
    UISModelCopyTexture(pObject, pData, 5, 1);
    UISModelCopyTexture(pObject, pData, 3, 2);
    ResBankUnload(_UISModel_pLibCache, pObject->mUnknown1D8, pObject->mUnknown1DA);
    ResBankCloseFile(_UISModel_pLibCache, pObject->mUnknown1D8);
    pObject->mUnknown1DE &= ~1;
}

int UISModelUpdateTextures(UISModel_t *pObject)
{
    int result = 1;
    if (pObject->mUnknown1DE & 1) {
        void *pData = (void *)ResBankGetData(_UISModel_pLibCache, pObject->mUnknown1D8, pObject->mUnknown1DA);
        if (pData) {
            UISModelApplyTextures(pObject, pData);
        } else {
            result = 0;
        }
    }
    return result;
}

int UISModelRegister(void *pHandle, int count)
{
    int result = ObjNewType_(19, sizeof(UISModel_t), count, UISModelInit, UISModelFree);
    if (pHandle) {
        result = ObjSetListObjFunc(pHandle, 19, 0, UISModelDraw);
    }
    if (!_UISModel_pLibCache) {
        ResBankDesc_t desc;
        desc.mUnknown0 = 1;
        desc.mUnknown4 = 21;
        desc.mUnknown12 = lbl_802EAD10;
        desc.mUnknown8 = 0;
        _UISModel_pLibCache = ResBankCreate(&desc);
        result = (int)_UISModel_pLibCache;
    }
    return result;
}

void UISModelUnregister(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(19);
    ResBankDestroy(_UISModel_pLibCache);
    _UISModel_pLibCache = 0;
}

void UISModelDrawReady(UISModel_t *pObject, int value)
{
    if ((pObject->mUnknown198 & 1) && pObject->mUnknown14 && UISModelUpdateTextures(pObject)) {
        UISModelDraw(pObject, value);
    }
}

void UISModelSetDrawMode(UISModel_t *pObject, unsigned char value)
{
    pObject->mUnknown1E4 = value;
    if (pObject->mUnknown198 & 1) {
        fn_80235D74(&pObject->mUnknown48, value >> 2);
    }
}
}
