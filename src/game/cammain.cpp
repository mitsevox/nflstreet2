/* The game camera's core. A game camera is built on a free-floating or a
   focus camera; this file follows its focus (the ball, a player or a
   fixed object), places it at an offset from the focus, aims it, applies
   the angle and offset changes the camera modes ask for, mirrors it when
   the field is flipped, and forwards each step to the camera mode. It also
   holds the camera type record and the type list the camera system is
   started with, and the eased vectors and values the scripted cameras use. */

#include "engine/camfocus.h"
#include "engine/viewport.h"
#include "game/GameCamera.h"
#include "game/CamEaseVec.h"
#include "game/Ball.h"
#include "game/cammain.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

/* Object a camera follows for target kinds 3 to 5 (passed as the target
   reference word). */
struct CamFocusTarget_t {
    char mPad00[4];
    Vector_80039F5C mPos;
    char mPad10[0x14];
    int mUnknown24;
};

struct CamTypeDefEntry_t {
    void *mpType;
    int mSize;
    int mUnknown08;
};

extern "C" {
extern char lbl_802F4884[];
extern char lbl_802F4890[];
extern CamTypeDef_t lbl_802CC83C;
extern char lbl_8031BDD4[];

void fn_8009BD2C(Object_80039F5C *p, int *pRef);
CamMode_t *fn_80141054(int id);
void fn_8014106C(int id, int mode, float *pA, float *pB);
int fn_801486A0(void);
void fn_801527B8(void *p, Vector_80039F5C *pOut);
int fn_801784C4(void);
void CamConvertHdrToMatrix(void *p, GameCamera_t *pCamera);
void CamSetZScale(GameCamera_t *pCamera, float value);
void CamFreeFloatAdd(GameCamera_t *pCamera, int a);
void CamFreeFloatDelete(GameCamera_t *pCamera);
void CamFreeFloatProcess(GameCamera_t *pCamera);
void CamFreeClearVelocity(GameCamera_t *pCamera);
void CamFreeFloatUpdate(void *p, GameCamera_t *pCamera);
void CamFreeSetPos(GameCamera_t *pCamera, float x, float y, float z);
void CamFreeMovePos(GameCamera_t *pCamera, float x, float y, float z);
void CamFreeSetAngle(GameCamera_t *pCamera, int a, int b, int c);
void CamFreeMoveAngle(GameCamera_t *pCamera, int a, int b, int c);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
void fn_801D0470(int a);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D08FC(int angle);
void fn_801D0ADC(int angle);
void fn_801D0C58(Vector_80039F5C *pPos);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227CC0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);

void CamInterpUpdateSnap(CamInterp_t *pInterp, int steps);
}

extern "C" {
CamTypeDef_t _CamMain_Type = { CamMainInit, CamMainUninit, CamMainUpdate };

/* Base camera kind for each camera id. */
int _CamMain_BaseTypes[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 0 };

CamTypeDefEntry_t _CamMainTypeDefs[5] = {
    { lbl_802F4890, 0x8C, 0 },
    { lbl_802F4884, 0x94, 0 },
    { &_CamMain_Type, 0xF58, 0 },
    { &lbl_802CC83C, 0xF60, 0 },
    { 0, 0, 0 },
};
}

static inline void ZeroVector(Vector_80039F5C *pVec)
{
    pVec->mX = pVec->mY = pVec->mZ = 0.0f;
}

extern "C" {

unsigned char CamMainIsFlipped(GameCamera_t *pCamera)
{
    return ((pCamera->mUnknown94 >> 3) & 1) ^ fn_801784C4();
}

void CamMainFlipPos(Vector_80039F5C *pVec)
{
    pVec->mX = -pVec->mX;
    pVec->mY = -pVec->mY;
}

void CamMainFlipOrient(int *pAngles)
{
    pAngles[2] = (pAngles[2] - 0x800000) & 0xFFFFFF;
}

void _CamMainProcessFollow(GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        if (pCamera->mUnknown94 & 4) {
            CamMainWarpToDest(pCamera);
            pCamera->mUnknown94 &= ~4;
        } else {
            Vector_80039F5C pos;

            _CamMainGetFocusPos(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
            _CamMainCalcFollowPos(pCamera, &pCamera->mUnknownB8, &pos);
            CamFreeMovePos(pCamera, pos.mX, pos.mY, pos.mZ);
        }
        break;
    case 1:
        _CamMainGetFocusPos(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
        CamFocusSetTarget(pCamera, &pCamera->mUnknownB8);
        if (pCamera->mUnknown94 & 4) {
            CamMainWarpToDest(pCamera);
            pCamera->mUnknown94 &= ~4;
        }
        break;
    }
}

void _CamMainCalcFollowPos(GameCamera_t *pCamera, Vector_80039F5C *pTarget, Vector_80039F5C *pOut)
{
    Vector_80039F5C offset;
    Vector_80039F5C target;

    offset.mX = pCamera->mUnknownC4;
    offset.mY = pCamera->mUnknownC8;
    offset.mZ = pCamera->mUnknownCC;
    target.mX = pTarget->mX;
    target.mY = pTarget->mY;
    target.mZ = pTarget->mZ;
    if (CamMainIsFlipped(pCamera)) {
        CamMainFlipPos(&offset);
    }
    target.mZ = 0.0f;
    fn_8022765C(pOut, &target, &offset);
    if (pCamera->mUnknown94 & 0x10) {
        float x[2];
        float y[2];

        fn_8014106C(pCamera->mUnknown9C, pCamera->mUnknownA0, x, y);
        pOut->mX = CLAMP(pOut->mX, x[0], x[1]);
        pOut->mY = CLAMP(pOut->mY, y[0], y[1]);
        pOut->mZ = CLAMP(pOut->mZ, 2.5f, 100.0f);
    }
}

void _CamMainGetCameraPos(GameCamera_t *pCamera, Vector_80039F5C *pOut)
{
    if (pCamera->mUnknown98 == 0) {
        pOut->mX = pCamera->mUnknown2C;
        pOut->mY = pCamera->mUnknown30;
        pOut->mZ = pCamera->mUnknown34;
    }
}

/* Position of a camera target: kind 1 is a ball index, 2 a packed object
   reference, 3 to 5 a CamFocusTarget_t pointer. */
void _CamMainGetFocusPos(int kind, int ref, Vector_80039F5C *pOut)
{
    switch (kind) {
    case 1: {
        Ball_t *pBall = BallGet(ref);
        Object_80039F5C *pObject = BallGetHolder(pBall);

        if (pObject == 0) {
            BallGetPosition(pBall, pOut);
        } else {
            pOut->mX = pObject->mMotion.mPos.mX;
            pOut->mY = pObject->mMotion.mPos.mY;
            pOut->mZ = pObject->mMotion.mPos.mZ;
        }
        if (fn_801784C4()) {
            CamMainFlipPos(pOut);
        }
        break;
    }
    case 2: {
        Object_80039F5C *pObject = fn_8009BCE8(&ref);

        pOut->mX = pObject->mMotion.mPos.mX;
        pOut->mY = pObject->mMotion.mPos.mY;
        pOut->mZ = pObject->mMotion.mPos.mZ;
        if (fn_801784C4()) {
            CamMainFlipPos(pOut);
        }
        break;
    }
    case 3:
        pOut->mX = ((CamFocusTarget_t *)ref)->mPos.mX;
        pOut->mY = ((CamFocusTarget_t *)ref)->mPos.mY;
        pOut->mZ = ((CamFocusTarget_t *)ref)->mPos.mZ;
        break;
    case 4:
    case 5:
        pOut->mX = ((CamFocusTarget_t *)ref)->mPos.mX;
        pOut->mY = ((CamFocusTarget_t *)ref)->mPos.mY;
        pOut->mZ = ((CamFocusTarget_t *)ref)->mPos.mZ;
        break;
    case 0:
        ZeroVector(pOut);
        break;
    case 6:
        break;
    case 7:
        fn_801527B8(lbl_8031BDD4, pOut);
        if (fn_801784C4()) {
            CamMainFlipPos(pOut);
        }
        break;
    }
}

void _CamMainGetFocusOrient(int kind, int ref, int *pAngles)
{
    pAngles[0] = pAngles[1] = pAngles[2] = 0;
    switch (kind) {
    case 1:
        break;
    case 2:
        fn_8009BCE8(&ref);
        break;
    case 3:
        pAngles[2] = ((CamFocusTarget_t *)ref)->mUnknown24;
        break;
    case 4:
    case 5:
        break;
    }
}

void _CamMainGetAngleToFocus(GameCamera_t *pCamera, int *pAngles)
{
    Vector_80039F5C from;
    Vector_80039F5C to;
    int angles[3];
    float dz;
    float c;

    if ((pCamera->mUnknown94 & 0x20) || pCamera->mUnknownA8 == 0) {
        pAngles[0] = pCamera->mUnknownD0;
        pAngles[1] = pCamera->mUnknownD4;
        pAngles[2] = pCamera->mUnknownD8;
        if (CamMainIsFlipped(pCamera)) {
            if (pCamera->mUnknown98 == 0) {
                CamMainFlipOrient(pAngles);
            } else {
                pAngles[1] += 0x800000;
            }
        }
        return;
    }
    if (pCamera->mUnknown98 == 0) {
        _CamMainGetCameraPos(pCamera, &from);
        _CamMainGetFocusPos(pCamera->mUnknownA8, pCamera->mUnknownAC, &to);
        pAngles[2] = fn_801CFE40(to.mX - from.mX, to.mY - from.mY);
        pAngles[2] += pCamera->mUnknownD8;
        pAngles[1] = 0;
        pAngles[1] += pCamera->mUnknownD4;
        dz = to.mZ - from.mZ;
        c = fn_801CFB94(pAngles[2]);
        pAngles[0] = fn_801CFE40(dz, c * (to.mY - from.mY) + fn_801CFB18(pAngles[2]) * (to.mX - from.mX));
        pAngles[0] += pCamera->mUnknownD0;
    } else {
        angles[0] = angles[1] = angles[2] = 0;
        _CamMainGetFocusOrient(pCamera->mUnknownA8, pCamera->mUnknownAC, angles);
        pAngles[0] = angles[0];
        pAngles[1] = angles[2];
        if (CamMainIsFlipped(pCamera)) {
            pAngles[0] += pCamera->mUnknownD0;
            pAngles[1] -= pCamera->mUnknownD4;
        } else {
            pAngles[0] += pCamera->mUnknownD0;
            pAngles[1] += pCamera->mUnknownD4;
        }
    }
    pAngles[0] &= 0xFFFFFF;
}

void _CamMainBaseInit(GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        CamFreeFloatAdd(pCamera, 0);
        pCamera->mUnknown5C = pCamera->mUnknown60 = pCamera->mUnknown64 = 0.1f;
        pCamera->mUnknown68 = pCamera->mUnknown6C = pCamera->mUnknown70 = 0.05f;
        pCamera->mUnknown80 = pCamera->mUnknown84 = pCamera->mUnknown88 = 0x200000;
        pCamera->mUnknown74 = pCamera->mUnknown78 = pCamera->mUnknown7C = 0x400000;
        break;
    case 1:
        CamFocusAdd(pCamera, 0);
        break;
    }
}

void _CamMainBaseUninit(GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        CamFreeFloatDelete(pCamera);
        break;
    case 1:
        CamFocusDelete(pCamera);
        break;
    case 4:
        break;
    }
}

void _CamMainBaseProcess(GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        CamFreeFloatProcess(pCamera);
        break;
    case 1:
        CamFocusProcess(pCamera);
        break;
    case 4:
        break;
    }
    CamSetZScale(pCamera, 4.0f);
}

void _CamMainBaseMoveAngle(GameCamera_t *pCamera, int *pAngles)
{
    switch (pCamera->mUnknown98) {
    case 0:
        CamFreeMoveAngle(pCamera, pAngles[0], pAngles[1], pAngles[2]);
        break;
    case 1:
        CamFocusMoveAngle(pCamera, pAngles[0], pAngles[1]);
        break;
    case 4:
        break;
    }
}

void CamMainProcess(GameCamera_t *pCamera, int a, int b, int c)
{
    if (pCamera->mUnknown98 == 0 || pCamera->mUnknown98 == 1) {
        _CamMainProcessFollow(pCamera);
    }
    CamMainMsg(pCamera, 3, 0);
    if (pCamera->mUnknown98 == 0 || pCamera->mUnknown98 == 1) {
        int angles[3];

        _CamMainGetAngleToFocus(pCamera, angles);
        _CamMainBaseMoveAngle(pCamera, angles);
    }
    _CamMainBaseProcess(pCamera);
}

void CamMainSetFocus(GameCamera_t *pCamera, int kind, int ref)
{
    pCamera->mUnknownA8 = kind;
    pCamera->mUnknownAC = ref;
    pCamera->mUnknown94 |= 2;
}

void CamMainInitDesc(CameraDesc_t *pDesc)
{
    pDesc->mUnknown00 = 0;
    pDesc->mUnknown04 = 0;
    fn_8009BD2C(0, &pDesc->mUnknown08);
    pDesc->mUnknown0C = 0;
}

void CamMainFollow(GameCamera_t *pCamera, unsigned int kind, int ref, int arg)
{
    if (fn_801486A0() == 1 && (kind == 1 || kind == 4)) {
        kind = 7;
    }
    pCamera->mUnknownA8 = kind;
    switch (kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
        pCamera->mUnknown94 |= 1;
        pCamera->mUnknownB0 = ref;
        pCamera->mUnknownB4 = arg;
        CamMainSetFocus(pCamera, kind, ref);
        break;
    case 0:
        pCamera->mUnknown94 &= ~1;
        pCamera->mUnknownB0 = 0;
        pCamera->mUnknownB4 = 0;
        break;
    }
}

void CamMainFollowBall(GameCamera_t *pCamera)
{
    CamMainFollow(pCamera, 1, BallGetCurrentIndex(), 0);
}

void CamMainSetOffset(GameCamera_t *pCamera, Vector_80039F5C *pOffset)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownC4 = pOffset->mX;
        pCamera->mUnknownC8 = pOffset->mY;
        pCamera->mUnknownCC = pOffset->mZ;
        break;
    case 1:
        pCamera->mUnknown30 = pOffset->mX;
        break;
    }
}

void CamMainSetAngle(GameCamera_t *pCamera, int *pAngles, int bit)
{
    pCamera->mUnknown94 = (pCamera->mUnknown94 & ~0x60) | (1 << bit);
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD0 = pAngles[0];
        pCamera->mUnknownD4 = pAngles[1];
        pCamera->mUnknownD8 = pAngles[2];
        pCamera->mUnknownD0 &= 0xFFFFFF;
        pCamera->mUnknownD4 &= 0xFFFFFF;
        pCamera->mUnknownD8 &= 0xFFFFFF;
        break;
    case 1:
        pCamera->mUnknownD0 = pAngles[0];
        pCamera->mUnknownD4 = pAngles[1];
        pCamera->mUnknownD0 &= 0xFFFFFF;
        pCamera->mUnknownD4 &= 0xFFFFFF;
        break;
    }
}

void CamMainRotate(GameCamera_t *pCamera, int angle)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD8 += angle;
        break;
    case 1:
        pCamera->mUnknownD4 += angle;
        break;
    }
}

void CamMainPitch(GameCamera_t *pCamera, int angle)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 4:
        pCamera->mUnknownD0 += angle;
        if (pCamera->mUnknown94 & 0x20) {
            pCamera->mUnknownD0 = CLAMP(pCamera->mUnknownD0, 0x805B06, 0xFFA4FB);
        } else {
            pCamera->mUnknownD0 &= 0xFFFFFF;
        }
        break;
    case 1:
        pCamera->mUnknownD0 += angle;
        if (pCamera->mUnknown94 & 0x20) {
            pCamera->mUnknownD0 = CLAMP(pCamera->mUnknownD0, 0x805B06, 0xFFA4FB);
        } else {
            pCamera->mUnknownD0 &= 0xFFFFFF;
        }
        break;
    }
}

void CamMainZoom(GameCamera_t *pCamera, float zoom)
{
    switch (pCamera->mUnknown98) {
    case 0:
    case 1:
        pCamera->mUnknown30 += zoom;
        if (pCamera->mUnknown30 <= 0.5f) {
            pCamera->mUnknown30 = 0.5f;
        }
        break;
    }
}

void CamMainSetMode(GameCamera_t *pCamera, int id, int a, int b)
{
    CamMainMsg(pCamera, 0, 0);
    pCamera->mUnknownA4 = pCamera->mUnknownA0;
    pCamera->mUnknownA0 = id;
    CamMainMsg(pCamera, 1, 0);
}

int CamMainGetMode(GameCamera_t *pCamera)
{
    return pCamera->mUnknownA0;
}

void CamMainSetActive(GameCamera_t *pCamera, int on, int a, int b)
{
    if (on) {
        if (pCamera->mUnknown94 & 8) {
            CamMainMsg(pCamera, 5, 0);
            pCamera->mUnknown94 &= ~8;
        }
    } else {
        CamMainMsg(pCamera, 2, 0);
        pCamera->mUnknown94 ^= 8;
    }
}

void CamMainWarpToDest(GameCamera_t *pCamera)
{
    Vector_80039F5C pos;
    int angles[3];

    switch (pCamera->mUnknown98) {
    case 0:
        _CamMainGetFocusPos(pCamera->mUnknownA8, pCamera->mUnknownAC, &pCamera->mUnknownB8);
        _CamMainCalcFollowPos(pCamera, &pCamera->mUnknownB8, &pos);
        CamFreeSetPos(pCamera, pos.mX, pos.mY, pos.mZ);
        _CamMainGetAngleToFocus(pCamera, angles);
        CamFreeSetAngle(pCamera, angles[0], angles[1], angles[2]);
        CamFreeClearVelocity(pCamera);
        CamMainMsg(pCamera, 11, 0);
        break;
    case 1:
        _CamMainGetAngleToFocus(pCamera, angles);
        CamFocusMoveAngle(pCamera, angles[0], angles[1]);
        CamFocusWarpToDest(pCamera);
        break;
    case 4:
        break;
    }
}

void CamMainStop(GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        CamFreeClearVelocity(pCamera);
        break;
    case 1: {
        GameCameraKind1_t *pBase = (GameCameraKind1_t *)pCamera;

        ZeroVector(&pBase->mUnknown4C);
        pBase->mUnknown58 = 0.0f;
        pBase->mUnknown5C = 0;
        pBase->mUnknown60 = 0;
        break;
    }
    case 4:
        break;
    }
}

void CamMainMsg(GameCamera_t *pCamera, int msg, int arg)
{
    if (pCamera->mUnknownDC) {
        pCamera->mUnknownDC(pCamera, msg, arg);
    }
}

int CamMainGetBaseType(int id)
{
    return _CamMain_BaseTypes[id];
}

void CamMainInit(GameCamera_t *pCamera, CameraDesc_t *pDesc)
{
    pCamera->mUnknown98 = pDesc->mUnknown00;
    _CamMainBaseInit(pCamera);
    pCamera->mUnknown94 = 0;
    pCamera->mUnknown9C = pDesc->mUnknown04;
    pCamera->mUnknownA0 = -1;
    pCamera->mUnknownDC = 0;
    fn_80141054(pCamera->mUnknown9C)->mUnknown00(pCamera, pDesc);
    CamMainSetMode(pCamera, 1, 0, 0);
    CamMainFollow(pCamera, 0, 0, 0);
    pCamera->mUnknown94 |= 4;
}

void CamMainUninit(GameCamera_t *pCamera)
{
    fn_80141054(pCamera->mUnknown9C)->mUnknown04(pCamera);
    _CamMainBaseUninit(pCamera);
}

void CamMainUpdate(void *p, GameCamera_t *pCamera)
{
    switch (pCamera->mUnknown98) {
    case 0:
        CamFreeFloatUpdate(p, pCamera);
        break;
    case 1:
        CamFocusUpdate(p, pCamera);
        break;
    case 4:
        CamConvertHdrToMatrix(p, pCamera);
        break;
    }
}

void CamEaseVecStart(CamEaseVec_t *pEase, Vector_80039F5C *pBase, Vector_80039F5C *pFrom,
                 Vector_80039F5C *pTo, float fromScale, float toScale, CamInterpFunc_t update,
                 float time)
{
    pEase->mBase.mX = pBase->mX;
    pEase->mBase.mY = pBase->mY;
    pEase->mBase.mZ = pBase->mZ;
    CamInterpInit(&pEase->mX, pFrom->mX);
    CamInterpSetTarget(&pEase->mX, pTo->mX, update, time);
    CamInterpInit(&pEase->mY, pFrom->mY);
    CamInterpSetTarget(&pEase->mY, pTo->mY, update, time);
    CamInterpInit(&pEase->mZ, pFrom->mZ);
    CamInterpSetTarget(&pEase->mZ, pTo->mZ, update, time);
    CamInterpInit(&pEase->mScale, fromScale);
    CamInterpSetTarget(&pEase->mScale, toScale, update, time);
}

void CamEaseVecUpdate(CamEaseVec_t *pEase, int steps)
{
    Vector_80039F5C offset;
    int angles[3];

    pEase->mX.mUpdate(&pEase->mX, steps);
    pEase->mY.mUpdate(&pEase->mY, steps);
    pEase->mZ.mUpdate(&pEase->mZ, steps);
    pEase->mScale.mUpdate(&pEase->mScale, steps);
    angles[0] = (int)(pEase->mX.mValue * 46603.37890625f);
    angles[1] = (int)(pEase->mY.mValue * 46603.37890625f);
    angles[2] = (int)(pEase->mZ.mValue * 46603.37890625f);
    fn_801D0470(VptGetMatrixStack());
    fn_801D0508();
    fn_801D0C58(&pEase->mBase);
    fn_801D0ADC(-angles[2]);
    fn_801D08FC(-angles[0]);
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = pEase->mScale.mValue;
    fn_80227CC0(&pEase->mResult, &offset);
    fn_801D0544();
}

/* Negates the base x and y and turns the z angle by 180 degrees. */
void CamEaseVecFlip(CamEaseVec_t *pEase)
{
    if (pEase) {
        pEase->mZ.mValue += 180.0f;
        pEase->mZ.mTarget += 180.0f;
        pEase->mZ.mStart += 180.0f;
        pEase->mBase.mX = -pEase->mBase.mX;
        pEase->mBase.mY = -pEase->mBase.mY;
    }
}

void CamInterpInit(CamInterp_t *pInterp, float value)
{
    pInterp->mStart = pInterp->mValue = pInterp->mTarget = value;
    pInterp->mTime = pInterp->mRate = 0.0f;
    pInterp->mUpdate = CamInterpUpdateSnap;
}

void CamInterpSetTarget(CamInterp_t *pInterp, float target, CamInterpFunc_t update, float time)
{
    if (target != pInterp->mStart) {
        pInterp->mUpdate = update;
        pInterp->mStart = pInterp->mValue;
        pInterp->mTarget = target;
        pInterp->mTime = 0.0f;
        pInterp->mRate = 1.0f / time;
    }
}
}
