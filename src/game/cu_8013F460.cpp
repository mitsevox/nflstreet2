#include <string.h>
#include "game/Object_80228224.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80238174.h"

/* Leading block of a camera that a saved state restores. */
struct CameraHeader_8013F628 {
    unsigned char mUnknown00;
    unsigned char mType;
    char mPad02[2];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    char mPad20[4];
    float mUnknown24;
};

/* One camera in a saved state; only mHeader is restored. */
struct CameraSave_8013F56C {
    CameraHeader_8013F628 mHeader;
    int mUnknown28;
};

struct Camera_8013F738 {
    CameraHeader_8013F628 mHeader;
    char mPad28[0x6C];
    int mUnknown94;
    char mPad98[0x10];
    int mUnknownA8;
    char mPadAC[4];
    int mUnknownB0;
    int mUnknownB4;
};

/* Argument of fn_801C3610 when it creates a camera. */
struct Desc_8013C340 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
};

struct CameraSet_803ECA00 {
    int mCurrent;
    void *mpCameras[4];
    unsigned char mUnknown14;
};

/* Allocated through fn_80238174 under the id 'camg' (fn_8013F8D4). */
struct State_803ECA00 {
    void *mpObject;
    CameraSet_803ECA00 mSet;
};

typedef void (*CameraFunc_8013F85C)(void *pCamera, int a, int b, int c);

extern "C" {
extern float lbl_803EA2C4;

int fn_8002B2D4(void *pObject, void *pItem, int (*a)(void *, void *), int (*b)(void *, void *));
int fn_8002B3DC(void *pObject, void *pItem);
int fn_8002B494(void *pObject, void *pItem, void *pOther);
void fn_800AD9C0(float value);
int fn_800B65A0(int a);
void fn_8013C2B4(void *pCamera, int a, int b, int c);
void fn_8013C340(Desc_8013C340 *pDesc);
void fn_8013C384(void *pCamera, int a, int b, int c);
void fn_8013C624(void *pCamera, int a, int b, int c);
void fn_8013C680(void *pCamera, int a, int b, int c);
void fn_8013C824(void *pCamera, int msg, int arg);
int fn_8013C854(int id);
void fn_80141164(float value);
int fn_80178308(void);
int fn_80178320(void);
void *fn_801C3610(int a, Desc_8013C340 *pDesc);
void fn_801C3640(void *pCamera);
void *fn_8023816C(void *pHandle);

void fn_8013F7C0(State_803ECA00 *pState, int index, int id);
void fn_8013F820(State_803ECA00 *pState, int index);
Camera_8013F738 *fn_8013FA04(int index);
}

static State_803ECA00 *lbl_803ECA00;

extern "C" {

int fn_8013F460(void *p, int value)
{
    State_803ECA00 *pState = (State_803ECA00 *)p;

    pState->mSet.mpCameras[0] = 0;
    fn_8013F7C0(pState, 0, 0);
    pState->mSet.mpCameras[2] = 0;
    fn_8013F7C0(pState, 2, 12);
    pState->mSet.mpCameras[3] = 0;
    fn_8013F7C0(pState, 3, 17);
    pState->mSet.mCurrent = 0;
    fn_8002B2D4(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent], 0, 0);
    fn_80141164(0.0f);
    return 0;
}

int fn_8013F4F0(void *p, int value)
{
    State_803ECA00 *pState = (State_803ECA00 *)p;
    int i;

    fn_8002B3DC(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent]);
    for (i = 0; i < 4; i++) {
        if (pState->mSet.mpCameras[i] != 0) {
            fn_8013F820(pState, i);
        }
    }
    return 0;
}

int fn_8013F564(void *p, void *q)
{
    return 0;
}

int fn_8013F56C(void *p, char *pBuffer)
{
    State_803ECA00 *pState = (State_803ECA00 *)p;

    memcpy(pBuffer, p, sizeof(State_803ECA00));
    pBuffer += sizeof(State_803ECA00);
    memcpy(pBuffer, pState->mpObject, sizeof(Object_80228224));
    pBuffer += sizeof(Object_80228224);
    for (short i = 0; i < 4; i++) {
        memcpy(pBuffer, pState->mSet.mpCameras[i], sizeof(CameraSave_8013F56C));
        pBuffer += sizeof(CameraSave_8013F56C);
    }
    return 1;
}

/* Restores an object from a saved copy, keeping its word at +72. */
void fn_8013F5F4(Object_80228224 *pObject, char *pBuffer)
{
    int saved = pObject->mUnknown72;
    char *pDst = (char *)pObject;

    for (short n = sizeof(Object_80228224); n > 0; n--) {
        *pDst++ = *pBuffer++;
    }
    pObject->mUnknown72 = saved;
}

int fn_8013F628(void *p, char *pBuffer)
{
    State_803ECA00 *pState = (State_803ECA00 *)p;

    pState->mSet = ((State_803ECA00 *)pBuffer)->mSet;
    pBuffer += sizeof(State_803ECA00);
    fn_8013F5F4((Object_80228224 *)pState->mpObject, pBuffer);
    pBuffer += sizeof(Object_80228224);
    CameraSave_8013F56C *pSaved = (CameraSave_8013F56C *)pBuffer;
    for (short i = 0; i < 4; i++, pSaved++) {
        *(CameraHeader_8013F628 *)pState->mSet.mpCameras[i] = pSaved->mHeader;
    }
    return 1;
}

int fn_8013F730(void *p)
{
    return sizeof(State_803ECA00) + sizeof(Object_80228224) + 4 * sizeof(CameraSave_8013F56C);
}

void fn_8013F738(State_803ECA00 *pState, int index)
{
    if (index != pState->mSet.mCurrent) {
        fn_8002B494(pState->mpObject, lbl_803ECA00->mSet.mpCameras[lbl_803ECA00->mSet.mCurrent], lbl_803ECA00->mSet.mpCameras[index]);
        pState->mSet.mCurrent = index;
        fn_8013C824(pState->mSet.mpCameras[index], 4, index);
        fn_8013C2B4(pState->mSet.mpCameras[index], 0, 0, 0);
    }
}

void fn_8013F7C0(State_803ECA00 *pState, int index, int id)
{
    Desc_8013C340 desc;

    fn_8013C340(&desc);
    desc.mUnknown00 = fn_8013C854(id);
    desc.mUnknown04 = id;
    pState->mSet.mpCameras[index] = fn_801C3610(2, &desc);
}

void fn_8013F820(State_803ECA00 *pState, int index)
{
    fn_801C3640(pState->mSet.mpCameras[index]);
    pState->mSet.mpCameras[index] = 0;
}

/* Calls func on every camera of type 2. */
void fn_8013F85C(CameraFunc_8013F85C func, int a, int b, int c)
{
    for (int i = 0; i < 4; i++) {
        Camera_8013F738 *pCamera = fn_8013FA04(i);
        if (pCamera != 0 && pCamera->mHeader.mType == 2) {
            func(pCamera, a, b, c);
        }
    }
}

void fn_8013F8D4(void *pObject)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803ECA00, sizeof(State_803ECA00), 0, 0x63616D67);

    fn_80238234(pHandle, fn_8013F460, fn_8013F4F0, 0, fn_8013F564);
    fn_80238248(pHandle, fn_8013F56C, fn_8013F730, fn_8013F628);
    State_803ECA00 *pState = (State_803ECA00 *)fn_8023816C(pHandle);
    pState->mpObject = pObject;
    pState->mSet.mUnknown14 = 0;
    fn_802381E0(pHandle);
}

void fn_8013F97C(int index)
{
    fn_8013F738(lbl_803ECA00, index);
    fn_8013FA04(index);
}

void fn_8013F9B8(void)
{
    State_803ECA00 *pState = lbl_803ECA00;

    fn_8002B2D4(pState->mpObject, pState->mSet.mpCameras[pState->mSet.mCurrent], 0, 0);
}

int fn_8013F9F8(void)
{
    return lbl_803ECA00->mSet.mCurrent;
}

/* Index 5 selects the current camera. */
Camera_8013F738 *fn_8013FA04(int index)
{
    if (index == 5) {
        index = lbl_803ECA00->mSet.mCurrent;
    }
    return (Camera_8013F738 *)lbl_803ECA00->mSet.mpCameras[index];
}

void fn_8013FA24(void)
{
    fn_8013F85C(fn_8013C2B4, 0, 0, 0);
}

void fn_8013FA58(int a, int b)
{
    fn_8013F85C(fn_8013C384, a, b, 0);
}

void fn_8013FA8C(int a)
{
    fn_8013F85C(fn_8013C624, a, 0, 0);
}

void fn_8013FAC0(void)
{
    State_803ECA00 *pState = lbl_803ECA00;
    int unassigned = 0;

    if (fn_800B65A0(fn_80178308()) == 0xFF) {
        unassigned = fn_800B65A0(fn_80178320()) == 0xFF;
    }
    if (!unassigned && fn_800AD9B4() == 3) {
        pState->mSet.mUnknown14 = 1;
    }
    fn_8013F85C(fn_8013C680, 0, 0, 0);
}

void fn_8013FB44(void)
{
    State_803ECA00 *pState = lbl_803ECA00;

    if (pState != 0 && pState->mSet.mUnknown14 != 0) {
        fn_800AD9C0(lbl_803EA2C4 * 30.0f);
        pState->mSet.mUnknown14 = 0;
    }
    fn_8013F85C(fn_8013C680, 1, 0, 0);
}

/* Replaces camera index with a new camera of the given id, keeping its settings. */
void fn_8013FBB4(int index, int id)
{
    Camera_8013F738 *pOld = fn_8013FA04(index);
    int a8 = pOld->mUnknownA8;
    int b0 = pOld->mUnknownB0;
    int b4 = pOld->mUnknownB4;
    int flags = pOld->mUnknown94;

    fn_8013F820(lbl_803ECA00, index);
    fn_8013F7C0(lbl_803ECA00, index, id);
    Camera_8013F738 *pNew = fn_8013FA04(index);
    if (index == lbl_803ECA00->mSet.mCurrent) {
        fn_8002B494(lbl_803ECA00->mpObject, pOld, pNew);
    }
    pNew->mUnknown94 = flags;
    fn_8013C384(pNew, a8, b0, b4);
}
}
