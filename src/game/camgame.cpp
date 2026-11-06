/* The game camera manager: creates the game's cameras, keeps the current one on the viewport,
   switches and replaces cameras, and saves and restores them with the game state. */

#include <string.h>
#include "engine/viewporttypes.h"
#include "game/fn_800AD9B4.h"
#include "game/GameCamera.h"
#include "game/cu_8013BB18.h"
#include "game/fn_80238174.h"
#include "game/fn_800B65A0.h"

/* One camera in a saved state; only mHeader is restored. */
struct CamGameSave_t {
    CamHdr_t mHeader;
    int mUnknown28;
};

struct CamGameSet_t {
    int mCurrent;
    GameCamera_t *mpCameras[4];
    unsigned char mUnknown14;
};

/* Allocated through fn_80238174 under the id 'camg' (CamGameStart). */
struct CamGameState_t {
    void *mpObject;
    CamGameSet_t mSet;
};

typedef void (*CamGameForAllFunc_t)(GameCamera_t *pCamera, int a, int b, int c);

extern "C" {
extern float gFrameTimeScale;

int VptManagerPushCamera(void *pObject, void *pItem, int (*a)(void *, void *), int (*b)(void *, void *));
int VptManagerPopCamera(void *pObject, void *pItem);
int VptManagerReplaceCamera(void *pObject, void *pItem, void *pOther);
void fn_800AD9C0(float value);
void fn_80141164(float value);
int fn_80178308(void);
int fn_80178320(void);
void *CamCreate(int a, CameraDesc_t *pDesc);
void CamDestroy(void *pCamera);
void *fn_8023816C(void *pHandle);

void _CamGameAdd(CamGameState_t *pState, int index, int id);
void _CamGameDelete(CamGameState_t *pState, int index);
GameCamera_t *CamGameGetCamera(int index);
}

static CamGameState_t *_CamGame_pState;

extern "C" {

int _CamGameCreate(void *p, int value)
{
    CamGameState_t *pState = (CamGameState_t *)p;

    pState->mSet.mpCameras[0] = 0;
    _CamGameAdd(pState, 0, 0);
    pState->mSet.mpCameras[2] = 0;
    _CamGameAdd(pState, 2, 12);
    pState->mSet.mpCameras[3] = 0;
    _CamGameAdd(pState, 3, 17);
    pState->mSet.mCurrent = 0;
    VptManagerPushCamera(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent], 0, 0);
    fn_80141164(0.0f);
    return 0;
}

int _CamGameDestroy(void *p, int value)
{
    CamGameState_t *pState = (CamGameState_t *)p;
    int i;

    VptManagerPopCamera(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent]);
    for (i = 0; i < 4; i++) {
        if (pState->mSet.mpCameras[i] != 0) {
            _CamGameDelete(pState, i);
        }
    }
    return 0;
}

int _CamGameBlockCompare(void *p, void *q)
{
    return 0;
}

int _CamGameBlockSave(void *p, void *pBuffer)
{
    CamGameState_t *pState = (CamGameState_t *)p;

    memcpy(pBuffer, p, sizeof(CamGameState_t));
    pBuffer = (char *)pBuffer + sizeof(CamGameState_t);
    memcpy(pBuffer, pState->mpObject, sizeof(Viewport_t));
    pBuffer = (char *)pBuffer + sizeof(Viewport_t);
    for (short i = 0; i < 4; i++) {
        memcpy(pBuffer, pState->mSet.mpCameras[i], sizeof(CamGameSave_t));
        pBuffer = (char *)pBuffer + sizeof(CamGameSave_t);
    }
    return 1;
}

/* Restores an object from a saved copy, keeping its word at +72. */
void _CamGameRestoreViewport(Viewport_t *pObject, char *pBuffer)
{
    int saved = pObject->mUnknown72;
    char *pDst = (char *)pObject;

    for (short n = sizeof(Viewport_t); n > 0; n--) {
        *pDst++ = *pBuffer++;
    }
    pObject->mUnknown72 = saved;
}

int _CamGameBlockRestore(void *p, void *pBuffer)
{
    CamGameState_t *pState = (CamGameState_t *)p;

    pState->mSet = ((CamGameState_t *)pBuffer)->mSet;
    pBuffer = (char *)pBuffer + sizeof(CamGameState_t);
    _CamGameRestoreViewport((Viewport_t *)pState->mpObject, (char *)pBuffer);
    pBuffer = (char *)pBuffer + sizeof(Viewport_t);
    CamGameSave_t *pSaved = (CamGameSave_t *)pBuffer;
    for (short i = 0; i < 4; i++, pSaved++) {
        pState->mSet.mpCameras[i]->mHeader = pSaved->mHeader;
    }
    return 1;
}

int _CamGameBlockGetSaveSize(void *p)
{
    return sizeof(CamGameState_t) + sizeof(Viewport_t) + 4 * sizeof(CamGameSave_t);
}

void _CamGameSetCurrent(CamGameState_t *pState, int index)
{
    if (index != pState->mSet.mCurrent) {
        VptManagerReplaceCamera(pState->mpObject, _CamGame_pState->mSet.mpCameras[_CamGame_pState->mSet.mCurrent], _CamGame_pState->mSet.mpCameras[index]);
        pState->mSet.mCurrent = index;
        fn_8013C824(pState->mSet.mpCameras[index], 4, index);
        fn_8013C2B4(pState->mSet.mpCameras[index], 0, 0, 0);
    }
}

void _CamGameAdd(CamGameState_t *pState, int index, int id)
{
    CameraDesc_t desc;

    fn_8013C340(&desc);
    desc.mUnknown00 = fn_8013C854(id);
    desc.mUnknown04 = id;
    pState->mSet.mpCameras[index] = (GameCamera_t *)CamCreate(2, &desc);
}

void _CamGameDelete(CamGameState_t *pState, int index)
{
    CamDestroy(pState->mSet.mpCameras[index]);
    pState->mSet.mpCameras[index] = 0;
}

/* Calls func on every camera of type 2. */
void _CamGameForAllCamerasDo(CamGameForAllFunc_t func, int a, int b, int c)
{
    for (int i = 0; i < 4; i++) {
        GameCamera_t *pCamera = CamGameGetCamera(i);
        if (pCamera != 0 && pCamera->mHeader.mType == 2) {
            func(pCamera, a, b, c);
        }
    }
}

void CamGameStart(void *pObject)
{
    void *pHandle = fn_80238174(0, (void **)&_CamGame_pState, sizeof(CamGameState_t), 0, 0x63616D67);

    fn_80238234(pHandle, _CamGameCreate, _CamGameDestroy, 0, _CamGameBlockCompare);
    fn_80238248(pHandle, _CamGameBlockSave, _CamGameBlockGetSaveSize, _CamGameBlockRestore);
    CamGameState_t *pState = (CamGameState_t *)fn_8023816C(pHandle);
    pState->mpObject = pObject;
    pState->mSet.mUnknown14 = 0;
    fn_802381E0(pHandle);
}

void CamGameSelectCamera(int index)
{
    _CamGameSetCurrent(_CamGame_pState, index);
    CamGameGetCamera(index);
}

void CamGamePushCurrentCamera(void)
{
    CamGameState_t *pState = _CamGame_pState;

    VptManagerPushCamera(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent], 0, 0);
}

int CamGameGetCurrentSlot(void)
{
    return _CamGame_pState->mSet.mCurrent;
}

/* Index 5 selects the current camera. */
GameCamera_t *CamGameGetCamera(int index)
{
    if (index == 5) {
        index = _CamGame_pState->mSet.mCurrent;
    }
    return _CamGame_pState->mSet.mpCameras[index];
}

void CamGameProcess(void)
{
    _CamGameForAllCamerasDo(fn_8013C2B4, 0, 0, 0);
}

void CamGameSetFocusAll(int a, int b)
{
    _CamGameForAllCamerasDo((CamGameForAllFunc_t)fn_8013C384, a, b, 0);
}

void CamGameSetModeAll(int a)
{
    _CamGameForAllCamerasDo(fn_8013C624, a, 0, 0);
}

void CamGameSuspendAll(void)
{
    CamGameState_t *pState = _CamGame_pState;
    int unassigned = 0;

    if (fn_800B65A0(fn_80178308()) == 0xFF) {
        unassigned = fn_800B65A0(fn_80178320()) == 0xFF;
    }
    if (!unassigned && fn_800AD9B4() == 3) {
        pState->mSet.mUnknown14 = 1;
    }
    _CamGameForAllCamerasDo(fn_8013C680, 0, 0, 0);
}

void CamGameResumeAll(void)
{
    CamGameState_t *pState = _CamGame_pState;

    if (pState != 0 && pState->mSet.mUnknown14 != 0) {
        fn_800AD9C0(gFrameTimeScale * 30.0f);
        pState->mSet.mUnknown14 = 0;
    }
    _CamGameForAllCamerasDo(fn_8013C680, 1, 0, 0);
}

/* Replaces camera index with a new camera of the given id, keeping its settings. */
void CamGameChangeType(int index, int id)
{
    GameCamera_t *pOld = CamGameGetCamera(index);
    int a8 = pOld->mUnknownA8;
    int b0 = pOld->mUnknownB0;
    int b4 = pOld->mUnknownB4;
    int flags = pOld->mUnknown94;

    _CamGameDelete(_CamGame_pState, index);
    _CamGameAdd(_CamGame_pState, index, id);
    GameCamera_t *pNew = CamGameGetCamera(index);
    if (index == _CamGame_pState->mSet.mCurrent) {
        VptManagerReplaceCamera(_CamGame_pState->mpObject, pOld, pNew);
    }
    pNew->mUnknown94 = flags;
    fn_8013C384(pNew, a8, b0, b4);
}
}
