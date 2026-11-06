/*
 * Viewports: the screen rectangles the game draws its 3D views into. Keeps a pool of open viewports
 * with their position, size, erase colour, projection and the camera callback that sets each one's
 * view matrix, plus a priority list of user callbacks called before, during and after a viewport is
 * drawn. Once per frame VptProcessViewports draws every visible viewport in priority order.
 */
#include <dolphin/mtx.h>
#include "engine/viewport.h"
#include "engine/list.h"
#include "engine/llmatrix.h"
#include "game/fn_801C68FC.h"

typedef struct VptCallback_t {
    int mUnknown0;
    int mUnknown4;
    VptCallbackFuncT mUnknown8;
    Viewport_t *mUnknown12;
} VptCallback_t;

typedef struct VptCallbackMatch_t {
    Viewport_t *mUnknown0;
    VptCallbackFuncT mUnknown4;
    int mUnknown8;
} VptCallbackMatch_t;

extern void fn_801CAB30(void);
extern void fn_801CE720(void);
extern void fn_801CE774(void);
extern int fn_801CEA14(void);
extern float fn_801CFD28(int angle);
extern int fn_801D0290(unsigned int a, unsigned int b);
extern int fn_801D0310(unsigned int a);
extern void fn_801DD140(int handle, int a, int b);
extern void fn_801F7BD4(int err);
extern int fn_801F7C88(void);
extern void fn_801F8768(void);

static unsigned char _Vpt_ModuleActive = 0;
static void *_Vpt_ViewportList = 0;
static void *_Vpt_CallbackList = 0;
static unsigned char _Vpt_IsProcessing = 0;
static Viewport_t *_Vpt_pCurrentViewport;
static unsigned char _Vpt_MatrixStackIndex;

static int _VptInsertByPriorityCallback(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

static int _VptTraverseRemoveCallback(void *pItem, void *pContext, void *pArg)
{
    VptCallback_t *pEntry = pItem;
    VptCallbackMatch_t *pMatch = pContext;

    if (pMatch->mUnknown0 == pEntry->mUnknown12) {
        if (pMatch->mUnknown4 == 0 || pMatch->mUnknown4 == pEntry->mUnknown8) {
            fn_801C6C0C(_Vpt_CallbackList, pEntry);
            return 0;
        }
    }
    return 1;
}

static int _VptTraverseCallCallback(void *pItem, void *pContext, void *pArg)
{
    VptCallback_t *pEntry = pItem;
    VptCallbackMatch_t *pMatch = pContext;

    if (pMatch->mUnknown0 == pEntry->mUnknown12 && pMatch->mUnknown8 == pEntry->mUnknown4) {
        pEntry->mUnknown8(pMatch->mUnknown0);
    }
    return 1;
}

static void _VptCallCallbacks(Viewport_t *pObject, int event)
{
    VptCallbackMatch_t match;

    match.mUnknown0 = pObject;
    match.mUnknown8 = event;
    fn_801C6D34(_Vpt_CallbackList, 0, &match, 0, _VptTraverseCallCallback, 1);
}

static int _VptInsertByPriorityViewport(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

static int _VptTraverseProcessViewport(void *pItem, void *pContext, void *pArg)
{
    Viewport_t *pObject = pItem;

    if (!(pObject->mUnknown28 & 8)) {
        _Vpt_pCurrentViewport = pObject;
        _VptCallCallbacks(pObject, 0);
        if (!pObject->mUnknown68) {
            VptUpdateCamera(pObject);
        }
        VptSetUpRender(pObject);
        _VptCallCallbacks(pObject, 1);
        VptProcessObjectList(pObject);
        pObject->mUnknown68 = 0;
        _VptCallCallbacks(pObject, 2);
        _Vpt_pCurrentViewport = 0;
    }
    return 1;
}

int VptInit(VptInitBlock_t *pInit)
{
    int err;

    if (!_Vpt_ModuleActive) {
        if ((_Vpt_ViewportList = fn_801C68FC(1, 0, pInit->mUnknown0, sizeof(Viewport_t), _VptInsertByPriorityViewport, 0)) != 0
            && (_Vpt_CallbackList = fn_801C68FC(1, 0, pInit->mUnknown4, sizeof(VptCallback_t), _VptInsertByPriorityCallback, 0)) != 0) {
            _Vpt_MatrixStackIndex = pInit->mUnknown10;
            err = fn_801D0290(pInit->mUnknown10, pInit->mUnknown11);
            if (err == 0) {
                err = VptLLInit(pInit);
            }
        } else {
            err = fn_801F7C88();
        }
        _Vpt_pCurrentViewport = 0;
        _Vpt_ModuleActive = 1;
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int VptShutdown(void)
{
    int err = 0;

    if (_Vpt_ModuleActive) {
        VptFlushObjectTrashSync();
        if (_Vpt_ViewportList) {
            fn_801C69E4(_Vpt_ViewportList);
            _Vpt_ViewportList = 0;
        }
        if (_Vpt_CallbackList) {
            fn_801C69E4(_Vpt_CallbackList);
            _Vpt_CallbackList = 0;
        }
        fn_801D0310(_Vpt_MatrixStackIndex);
        err = VptLLShutdown();
        _Vpt_ModuleActive = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}

Viewport_t *VptOpen(ViewportDesc_t *pDesc)
{
    Viewport_t *pObject;
    int err = 0;
    int i;

    pObject = fn_801C6A20(_Vpt_ViewportList);
    if (pObject) {
        pObject->mUnknown0 = pDesc->mUnknown0;
        pObject->mUnknown46 = pObject->mUnknown47 = pDesc->mUnknown3;
        for (i = 0; i < pObject->mUnknown46; i++) {
            pObject->mUnknown48[i] = pDesc->mUnknown4[i];
        }
        pObject->mUnknown4 = 0.0f;
        pObject->mUnknown8 = ((float)fn_801CEA14() - (float)pDesc->mUnknown16) * 0.5f;
        pObject->mUnknown12 = pDesc->mUnknown18;
        pObject->mUnknown16 = pDesc->mUnknown16;
        pObject->mUnknown20 = pDesc->mUnknown18;
        pObject->mUnknown24 = pDesc->mUnknown16;
        pObject->mUnknown28 = 1;
        pObject->mUnknown32 = 0.0f;
        pObject->mUnknown36 = 0.0f;
        pObject->mUnknown40 = 0.0f;
        pObject->mUnknown60 = 0;
        pObject->mUnknown72 = 0;
        pObject->mUnknown68 = 0;
        pObject->mUnknown240 = 1.0f;
        fn_801C6AA4(_Vpt_ViewportList, pObject, 0);
        err = VptLLOpen(pDesc, pObject);
        if (err) {
            fn_801F7BD4(err);
        }
    }
    return pObject;
}

int VptClose(Viewport_t *pObject)
{
    VptCallbackMatch_t match;
    int err;

    err = VptLLClose(pObject);
    if (err) {
        fn_801F7BD4(err);
    }
    match.mUnknown0 = pObject;
    match.mUnknown4 = 0;
    fn_801C6D34(_Vpt_CallbackList, 0, &match, 0, _VptTraverseRemoveCallback, 1);
    fn_801C6C0C(_Vpt_ViewportList, pObject);
    return err;
}

int VptSetCallback(Viewport_t *pObject, int event, VptCallbackFuncT fn, int key)
{
    VptCallback_t *pEntry;
    int err = 0;

    pEntry = fn_801C6A20(_Vpt_CallbackList);
    if (pEntry) {
        pEntry->mUnknown0 = key;
        pEntry->mUnknown4 = event;
        pEntry->mUnknown8 = fn;
        pEntry->mUnknown12 = pObject;
        fn_801C6AA4(_Vpt_CallbackList, pEntry, 0);
    } else {
        err = fn_801F7C88();
    }
    return err;
}

void VptRemoveCallback(Viewport_t *pObject, VptCallbackFuncT fn)
{
    VptCallbackMatch_t match;

    match.mUnknown0 = pObject;
    match.mUnknown4 = fn;
    fn_801C6D34(_Vpt_CallbackList, 0, &match, 0, _VptTraverseRemoveCallback, 1);
}

void VptUpdateCamera(Viewport_t *pObject)
{
    if (pObject->mUnknown60) {
        fn_801D0470(_Vpt_MatrixStackIndex);
        fn_801D0494();
        pObject->mUnknown60(pObject, pObject->mUnknown64);
        pObject->mUnknown68 = 1;
        VptSaveMatrix(pObject);
    }
}

void VptProcessObjectList(Viewport_t *pObject)
{
    if (pObject->mUnknown72) {
        fn_801DD140(pObject->mUnknown72, 1, pObject->mUnknown69);
    }
}

void VptProcessViewports(void)
{
    fn_801CAB30();
    fn_801F8768();
    if (!_Vpt_IsProcessing) {
        fn_801CE720();
        _Vpt_IsProcessing = 1;
        fn_801C6D34(_Vpt_ViewportList, 0, 0, 0, _VptTraverseProcessViewport, 1);
        fn_801CE774();
        VptFlushObjectTrash();
        _Vpt_IsProcessing = 0;
    }
}

int VptIsProcessing(void)
{
    return _Vpt_IsProcessing;
}

Viewport_t *VptGetCurrentViewport(void)
{
    return _Vpt_pCurrentViewport;
}

void VptSetEraseColor(Viewport_t *pObject, float a, float b, float c)
{
    pObject->mUnknown32 = a;
    pObject->mUnknown36 = b;
    pObject->mUnknown40 = c;
}

void VptSetPos(Viewport_t *pObject, float a, float b)
{
    pObject->mUnknown4 = a;
    pObject->mUnknown8 = b;
}

int VptGetMatrixStack(void)
{
    return _Vpt_MatrixStackIndex;
}

void VptSaveMatrix(Viewport_t *pObject)
{
    fn_801D0470(_Vpt_MatrixStackIndex);
    fn_801D0F80(pObject->mUnknown76[0]);
}

void VptSetCamera(Viewport_t *pObject, VptCameraFuncT fn, void *arg)
{
    pObject->mUnknown60 = fn;
    pObject->mUnknown64 = arg;
}

void *VptGetCamera(Viewport_t *pObject)
{
    return pObject->mUnknown64;
}

void VptRemoveCamera(Viewport_t *pObject)
{
    pObject->mUnknown60 = 0;
    pObject->mUnknown64 = 0;
}

void VptSetObjectList(Viewport_t *pObject, int handle, int b)
{
    pObject->mUnknown72 = handle;
    pObject->mUnknown69 = b;
}

void VptSetPerspective(Viewport_t *pObject, float fovy, float aspect, float n, float f)
{
    float t;

    pObject->mUnknown28 = (pObject->mUnknown28 & ~4) | 2;
    pObject->mUnknown204 = fovy;
    pObject->mUnknown208 = aspect;
    pObject->mUnknown232 = n;
    pObject->mUnknown236 = f;
    t = n * fn_801CFD28((int)(fovy * 46603.379f) / 2);
    pObject->mUnknown228 = -t;
    pObject->mUnknown224 = t;
    pObject->mUnknown216 = -t * aspect;
    pObject->mUnknown220 = t * aspect;
}

void VptSetZScale(Viewport_t *pObject, float a)
{
    pObject->mUnknown240 = a * (fn_801CFD28(0x100000) / (pObject->mUnknown224 / pObject->mUnknown232));
}
