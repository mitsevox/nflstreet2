/* Camera mode with preset distances and angles per view, plus helpers that apply the
   player's camera setting and report a camera's heading. */

#include "game/GameCamera.h"
#include "game/cammain.h"

struct CamPresetAngles_t {
    int mUnknown0;
    int mUnknown4;
};

/* Read by CamMainSetOffset (the float) and CamMainSetAngle (the two words from +4
   and the shift +0xC). */
struct CamPresetView_t {
    float mUnknown0;
    CamPresetAngles_t mUnknown4;
    int mUnknownC;
};

struct CamPresetEase_t {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    int mUnknownC;
};

extern "C" {
int fn_800A34E0(void);
GameCamera_t *CamGameGetCamera(int index);
void CamGameProcess(void);
void CamGameSetModeAll(int a);
void CamGameChangeType(int index, int id);
int fn_801784C4(void);
int fn_801CFE40(float y, float x);
void fn_80227490(float *pOut, float *pIn, int a0, int a1, int a2);

void CamPresetInit(GameCamera_t *pCamera, CameraDesc_t *pDesc);
void CamPresetUninit(GameCamera_t *pCamera);
void CamPresetProcess(GameCamera_t *pCamera);
void CamPresetMsgFunc(GameCamera_t *pCamera, int msg, int arg);
void CamPresetStart(GameCamera_t *pCamera);
}

static CamPresetView_t _CamPreset_Views[6] = {
    { 8.0f, { -0x38E38E, 0 }, 5 },
    { 10.0f, { -0x2AAAAA, 0 }, 5 },
    { 14.0f, { -0x31C71C, 0 }, 5 },
    { 14.0f, { -0x31C71C, 0 }, 5 },
    { 6.0f, { -0x31C71C, 0x400000 }, 5 },
    { 10.0f, { -0x2AAAAA, 0 }, 5 },
};

static CamPresetAngles_t _CamPreset_Angles[6] = {
    { -0x91A2, 0x369D },
    { 0, 0 },
    { -0xFEDC, 0x7F6E },
    { -0xFEDC, 0x7F6E },
    { 0, 0 },
    { 0, 0 },
};

extern "C" {
CamMode_t CamPresetMode = { CamPresetInit, CamPresetUninit, 0 };
}

static CamPresetEase_t _CamPreset_EaseRates[4] = {
    { 0.1f, 0.05f, 0xAAE60, 0xAAE60 },
    { 0.15f, 0.15f, 0xAAE60, 0xAAE60 },
    { 0.5f, 1.0f, 0xAAE60, 0xAAE60 },
    { 0.1f, 0.01f, 0x55730, 0x55730 },
};

extern "C" {

void CamGameApplyUserCamera(void)
{
    int id = 19;
    int b = 1;
    GameCamera_t *pCamera = CamGameGetCamera(5);
    int next;

    if (pCamera) {
        b = pCamera->mUnknownA0;
        id = pCamera->mUnknown9C;
    }
    next = fn_800A34E0();
    if (next <= 18 && next != id) {
        CamGameChangeType(0, next);
        CamGameSetModeAll(b);
    }
    CamGameProcess();
    CamMainWarpToDest(CamGameGetCamera(5));
}

int CamGameGetSideYaw(void)
{
    CamGameGetCamera(0);
    return fn_801784C4() ? 0x800000 : 0;
}

int CamGameGetHeading(int index)
{
    float dir[3];
    float out[3];
    GameCamera_t *pCamera;

    dir[0] = dir[1] = dir[2] = out[0] = out[1] = out[2] = 0.0f;
    pCamera = CamGameGetCamera(index);
    dir[2] = -1.0f;
    fn_80227490(out, dir, pCamera->mHeader.mUnknown14[2], pCamera->mHeader.mUnknown14[1], pCamera->mHeader.mUnknown14[0]);
    out[1] = -out[1];
    return fn_801CFE40(out[1], out[0]);
}

void CamPresetInit(GameCamera_t *pCamera, CameraDesc_t *pDesc)
{
    pCamera->mUnknownDC = CamPresetMsgFunc;
}

void CamPresetUninit(GameCamera_t *pCamera)
{
}

void CamPresetProcess(GameCamera_t *pCamera)
{
    int *pState = (int *)pCamera->mPadF8;

    CamMainRotate(pCamera, pState[0]);
    CamMainPitch(pCamera, pState[1]);
}

void CamPresetMsgFunc(GameCamera_t *pCamera, int msg, int arg)
{
    switch (msg) {
    case 3:
        CamPresetProcess(pCamera);
        break;
    case 1:
        CamPresetStart(pCamera);
        break;
    case 0:
    case 2:
    case 4:
        break;
    }
}

void CamPresetStart(GameCamera_t *pCamera)
{
    int *pState = (int *)pCamera->mPadF8;

    if (pCamera->mUnknownA0 <= 5) {
        CamMainSetOffset(pCamera, (Vector_80039F5C *)&_CamPreset_Views[pCamera->mUnknownA0]);
        CamMainSetAngle(pCamera, (int *)&_CamPreset_Views[pCamera->mUnknownA0].mUnknown4, _CamPreset_Views[pCamera->mUnknownA0].mUnknownC);
        pState[0] = _CamPreset_Angles[pCamera->mUnknownA0].mUnknown0;
        pState[1] = _CamPreset_Angles[pCamera->mUnknownA0].mUnknown4;
    }
    if (pCamera->mUnknownA0 == 8) {
        CamPresetAngles_t *pSrc = &_CamPreset_Views[0].mUnknown4;
        CamPresetAngles_t angles;

        angles.mUnknown0 = pSrc->mUnknown0;
        angles.mUnknown4 = pSrc->mUnknown4;
        angles.mUnknown4 = fn_801784C4() ? 0x800000 : 0;
        CamMainSetOffset(pCamera, (Vector_80039F5C *)&_CamPreset_Views[0]);
        CamMainSetAngle(pCamera, (int *)&angles, _CamPreset_Views[0].mUnknownC);
        pState[0] = 0;
        pState[1] = 0;
    }
}

void CamPresetSetEaseRates(GameCamera_t *pCamera, int index)
{
    pCamera->mUnknown5C = pCamera->mUnknown60 = pCamera->mUnknown64 = _CamPreset_EaseRates[index].mUnknown0;
    pCamera->mUnknown68 = pCamera->mUnknown6C = pCamera->mUnknown70 = _CamPreset_EaseRates[index].mUnknown4;
    pCamera->mUnknown80 = pCamera->mUnknown84 = pCamera->mUnknown88 = _CamPreset_EaseRates[index].mUnknown8;
    pCamera->mUnknown74 = pCamera->mUnknown78 = pCamera->mUnknown7C = _CamPreset_EaseRates[index].mUnknownC;
}

}
