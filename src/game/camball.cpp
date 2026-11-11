/* Ball-following camera: the message function installed by CamBallInit and
   its start and per-frame handlers. Each frame it picks a source position and
   a target (the ball, or the ball holder's body between two joints) for the
   current view, aims the camera at the target and eases its angles and field
   of view toward the new values. View 2 also clears the banner once and keeps
   a frame-driven offset for its source position. */

#include "game/Object_8017886C.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"

struct BallCameraState_t {
    char mPad00[0x18];
    float mUnknown18[3];
    int mUnknown24[3];
    float mUnknown30;
    float mUnknown34;
    float mUnknown38;
    char mPad3C[4];
    float mUnknown40;
    float mUnknown44;
    char mPad48[8];
    int mUnknown50;
    float mUnknown54[3];
    char mPad60[8];
    Point_8017886C mUnknown68;
    float mUnknown70;
    int mUnknown74;
};

struct BallCamera_t {
    char mPad00[4];
    float mUnknown04[3];
    char mPad10[4];
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    char mPad20[4];
    float mUnknown24;
    char mPad28[0x28];
    int mUnknown50;
    int mUnknown54;
    int mUnknown58;
    char mPad5C[0x18];
    int mUnknown74;
    int mUnknown78;
    int mUnknown7C;
    int mUnknown80;
    int mUnknown84;
    int mUnknown88;
    char mPad8C[0x14];
    int mUnknownA0;
    char mPadA4[0x54];
    BallCameraState_t mUnknownF8;
};

struct BallCameraJoint_t {
    float mUnknown0;
    int mUnknown4;
};

extern "C" {
int BallStateGet(Ball_t *pBall, int *pOut);
float CamCalcLookAngles(float *pFrom, float *pTo, int *pAngles);
int fn_80177F70(void);
Point_8017886C fn_80177FE0(void);
float fn_80178298(void);
int fn_801784C4(void);
void BannerClear(int a);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
int CamRLerp(int *pValue, int *pVel, int target, int a, int b);
int CamLerp(float *pValue, float *pVel, float target, float a, float b);
void CamSetFieldOfView(BallCamera_t *pCamera, float a, float b);
int fn_801CFE40(float y, float x);

void CamBallStart(BallCamera_t *pCamera);
void CamBallProcess(BallCamera_t *pCamera);
void CamBallUpdateFov(BallCamera_t *pCamera, int smooth);
void CamBallGetHolderTarget(Object_80039F5C *pPlayer, Vector_80039F5C *pOut, float t);
void CamBallSetAngles(BallCamera_t *pCamera, int *pAngles, int smooth);
float CamBallCalcFov(BallCamera_t *pCamera, float a, float b);
}

static int _CamBall_iCleared = 0;
static unsigned char _CamBall_bRestart = 0;
static int _CamBall_iDriftFrames = 0;
static int _CamBall_iReplayHoldFrames = 175;
static float _CamBall_fDriftRateX = 0.0015f;
static float _CamBall_fDriftRateY = 0.0f;
static float _CamBall_fDriftRateZ = 0.0005f;
static unsigned char _CamBall_bBannerCleared = 0;
static unsigned char _CamBall_bFastReturn = 0;

static float _CamBall_vDriftOffset[3];

static BallCameraJoint_t _CamBall_aHolderJoints[2] = {
    { 10.0f, 0 },
    { 0.0f, 26 },
};

extern "C" {

#if defined(DECOMP_COMPARE)
void CamBallStart(BallCamera_t *pCamera)
{
    BallCameraState_t *pState = &pCamera->mUnknownF8;
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C ballPos;
    int info[2];

    BallGetPosition(pBall, &ballPos);
    BallStateGet(pBall, info);
    pState->mUnknown68 = fn_80177FE0();
    pState->mUnknown70 = fn_80178298();
    pState->mUnknown74 = fn_80177F70();
    pState->mUnknown38 = 0.0f;
    switch (pCamera->mUnknownA0) {
    case 0:
        break;
    case 1:
        if (pState->mUnknown68.mY > 30.0f) {
            pState->mUnknown44 = 30.0f;
        } else {
            pState->mUnknown44 = pState->mUnknown68.mY < 30.0f ? -30.0f : 50.0f;
        }
        _CamBall_bRestart = 1;
        break;
    case 2:
        break;
    }
}
#endif

void CamBallProcess(BallCamera_t *pCamera)
{
    BallCameraState_t *pState = &pCamera->mUnknownF8;
    int a = 0;
    int replay = fn_800AD9B4() == 3;
    int changed;
    Ball_t *pBall;
    Object_80039F5C *pPlayer;
    Vector_80039F5C ballPos;
    Vector_80039F5C mirrored;
    int info[2];
    int mode;
    float speed;
    float lag;
    int *pAngles;
    float *pFrom;

    pBall = BallGetCurrent();
    BallStateGet(pBall, info);
    pPlayer = BallGetHolder(pBall);
    fn_80177F70();
    BallGetPosition(pBall, &ballPos);
    _CamBall_iCleared = a;
    changed = 0;
    mode = 0;
    pState->mUnknown18[0] = 45.0f;
    pState->mUnknown18[1] = pState->mUnknown44;
    pState->mUnknown18[2] = 20.0f;
    speed = 24.0f;
    lag = 0.0f;
    switch (pCamera->mUnknownA0) {
    case 0:
        break;
    case 1:
        if (pPlayer) {
            CamBallGetHolderTarget(pPlayer, (Vector_80039F5C *)&pCamera->mUnknownF8.mUnknown54, pState->mUnknown30);
        } else {
            pState->mUnknown54[0] = ballPos.mX;
            pState->mUnknown54[1] = ballPos.mY;
            pState->mUnknown54[2] = ballPos.mZ;
        }
        mode = 0;
        speed = 8.0f;
        break;
    case 2:
        a = 0;
        if (_CamBall_bBannerCleared == 0 && fn_800AD9B4() != 1) {
            _CamBall_bBannerCleared = 1;
            BannerClear(7);
        }
        if (replay && (_CamBall_iReplayHoldFrames-- < 0 || a == 0)) {
            if (pPlayer) {
                CamBallGetHolderTarget(pPlayer, (Vector_80039F5C *)&pState->mUnknown54, pState->mUnknown30);
            } else {
                pState->mUnknown54[0] = ballPos.mX;
                pState->mUnknown54[1] = ballPos.mY;
                pState->mUnknown54[2] = ballPos.mZ;
            }
        } else {
            float t;
            _CamBall_iDriftFrames = _CamBall_iDriftFrames + 1;
            t = (float)_CamBall_iDriftFrames;
            _CamBall_vDriftOffset[0] = t * _CamBall_fDriftRateX + 8.0f;
            _CamBall_vDriftOffset[1] = t * _CamBall_fDriftRateY;
            _CamBall_vDriftOffset[2] = t * _CamBall_fDriftRateZ + 0.5f;
            if (a != 0) {
                mode = 4;
                pState->mUnknown18[0] = _CamBall_vDriftOffset[0] + fn_80177FE0().mX;
                pState->mUnknown18[1] = _CamBall_vDriftOffset[1] + fn_80177FE0().mY;
                pState->mUnknown18[2] = _CamBall_vDriftOffset[2];
                if (fn_801784C4()) {
                    pState->mUnknown18[0] = -pState->mUnknown18[0];
                    pState->mUnknown18[1] = -pState->mUnknown18[1];
                }
            } else {
                mode = 0;
            }
            lag = 8.0f;
            pState->mUnknown54[0] = pState->mUnknown68.mX;
            pState->mUnknown54[1] = pState->mUnknown68.mY;
            pState->mUnknown54[2] = 1.3f;
        }
        _CamBall_bFastReturn = 0;
        speed = 24.0f;
        break;
    case 3:
    case 4:
    default:
        _CamBall_iReplayHoldFrames = 75;
        _CamBall_iDriftFrames = 0;
        _CamBall_bBannerCleared = 0;
        pState->mUnknown54[0] = ballPos.mX;
        pState->mUnknown54[1] = ballPos.mY;
        pState->mUnknown54[2] = ballPos.mZ;
        if (_CamBall_bFastReturn) {
            mode = 0;
            speed = 50.0f;
        }
        break;
    }
    if (pState->mUnknown50 != mode || _CamBall_bRestart) {
        _CamBall_bRestart = 0;
        changed = 1;
    }
    mirrored.mX = pState->mUnknown54[0];
    mirrored.mY = pState->mUnknown54[1];
    mirrored.mZ = pState->mUnknown54[2];
    pState->mUnknown50 = mode;
    if (fn_801784C4()) {
        mirrored.mX = -mirrored.mX;
        mirrored.mY = -mirrored.mY;
    }
    pCamera->mUnknown04[0] = pState->mUnknown18[0];
    pCamera->mUnknown04[1] = pState->mUnknown18[1];
    pCamera->mUnknown04[2] = pState->mUnknown18[2];
    pAngles = pState->mUnknown24;
    pFrom = pState->mUnknown18;
    pState->mUnknown40 = CamCalcLookAngles(pFrom, &mirrored.mX, pAngles);
    pState->mUnknown34 = CamBallCalcFov(pCamera, speed, pState->mUnknown40);
    pState->mUnknown40 = CamCalcLookAngles(pFrom, &mirrored.mX, pAngles);
    CamBallSetAngles(pCamera, pAngles, !changed);
    if (changed) {
        pState->mUnknown30 = pState->mUnknown34 + lag;
    }
    CamBallUpdateFov(pCamera, 1);
}

void CamBallUpdateFov(BallCamera_t *pCamera, int smooth)
{
    BallCameraState_t *pState = &pCamera->mUnknownF8;
    float a;
    float b;

    if (fn_800AD9B4() == 3) {
        a = 0.04f;
        b = 0.03f;
    } else {
        a = 0.01f;
        b = 0.007f;
    }
    if (!smooth || (pState->mUnknown30 != pState->mUnknown34
        && CamLerp(&pState->mUnknown30, &pState->mUnknown38, pState->mUnknown34, a, b))) {
        pState->mUnknown30 = pState->mUnknown34;
    }
    CamSetFieldOfView(pCamera, pState->mUnknown30, pCamera->mUnknown24);
}

void CamBallGetHolderTarget(Object_80039F5C *pPlayer, Vector_80039F5C *pOut, float t)
{
    Vector_80039F5C a;
    Vector_80039F5C b;

    if (t <= _CamBall_aHolderJoints[0].mUnknown0) {
        BallCameraJoint_t *pEnd = &_CamBall_aHolderJoints[1];
        float f;

        fn_8009BF5C(pPlayer, _CamBall_aHolderJoints[0].mUnknown4, &a, 0);
        fn_8009BF5C(pPlayer, pEnd->mUnknown4, &b, 0);
        f = (t - _CamBall_aHolderJoints[0].mUnknown0) / (_CamBall_aHolderJoints[1].mUnknown0 - _CamBall_aHolderJoints[0].mUnknown0);
        if (_CamBall_aHolderJoints[1].mUnknown0 - _CamBall_aHolderJoints[0].mUnknown0 == 0.0f) {
            f = 0.0f;
        }
        fn_80227930(pOut, &b, &a, f);
    } else {
        fn_8009BF5C(pPlayer, _CamBall_aHolderJoints[0].mUnknown4, pOut, 0);
    }
}

void CamBallSetAngles(BallCamera_t *pCamera, int *pAngles, int smooth)
{
    pAngles[0] &= 0xFFFFFF;
    pAngles[1] &= 0xFFFFFF;
    pAngles[2] &= 0xFFFFFF;
    if (smooth) {
        CamRLerp(&pCamera->mUnknown14, &pCamera->mUnknown50, pAngles[0], pCamera->mUnknown74, pCamera->mUnknown80);
        CamRLerp(&pCamera->mUnknown18, &pCamera->mUnknown54, pAngles[1], pCamera->mUnknown78, pCamera->mUnknown84);
        CamRLerp(&pCamera->mUnknown1C, &pCamera->mUnknown58, pAngles[2], pCamera->mUnknown7C, pCamera->mUnknown88);
    } else {
        pCamera->mUnknown14 = pAngles[0];
        pCamera->mUnknown18 = pAngles[1];
        pCamera->mUnknown1C = pAngles[2];
    }
}

float CamBallCalcFov(BallCamera_t *pCamera, float a, float b)
{
    return 2.0f * ((float)fn_801CFE40(a / (pCamera->mUnknown24 + pCamera->mUnknown24), b + b) * (360.0f / 16777216.0f));
}

void CamBallMsgFunc(BallCamera_t *pCamera, int msg)
{
    BallCameraState_t *pState = &pCamera->mUnknownF8;

    switch (msg) {
    case 3:
        CamBallProcess(pCamera);
        break;
    case 1:
        CamBallStart(pCamera);
        break;
    case 4:
        _CamBall_bRestart = 1;
        pState->mUnknown44 = 30.0f;
        pState->mUnknown34 = 45.0f;
        CamBallUpdateFov(pCamera, 0);
        CamBallStart(pCamera);
        break;
    }
}

void CamBallRequestRestart(void)
{
    _CamBall_bRestart = 1;
}

}
