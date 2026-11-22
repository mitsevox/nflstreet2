/* Ball flight and bounce physics: gravity, wind, spin and spirals, bounces and ground friction, landing
   prediction for throws, and the per-state handlers that decide what happens when a thrown, pitched or
   loose ball hits the ground or touches a player (catch, fumble, incomplete pass). */

#include <math.h>

#include "game/Ball.h"
#include "game/BigObj.h"
#include "game/BigObjInst.h"
#include "game/Object_8017886C.h"
#include "game/Record_800B15FC.h"
#include "game/AudmonEvent.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801BE60C.h"
#include "game/Vec2Add.h"
#include "engine/llquat.h"
#include "game/Vec3Magnitude.h"

/* One of the four 100-byte records that the player object's +792 pointer
   holds (see include/game/fn_801BE60C.h). */
struct PlyrAnimRecord_t {
    char unk_0x0[4];
    unsigned short mKey;
    unsigned short mState;
    char unk_0x8[92];
};

extern float gFrameTimeScale;

extern "C" {
BigObjInst *BallModelGetLinkedObj(Block_80170E64 *pBlock);
BigObj_t *BigObjGet(int index);
float fn_800A33D0(void);
int fn_800A33DC(void);
void fn_800B1508(void);
int fn_800B65A0(int team);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800D782C(Object_80039F5C *p);
void LooseBallBroadcast(int index);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pA);
int PossIsWristNearJoint(Ball_t *pBall, Object_80039F5C *p, int a);
void PossEndIncompletePass(void);
int PossTryCatch(Ball_t *pBall, Object_80039F5C *p, unsigned int type);
int PossTryReceivePitch(Ball_t *pBall, Object_80039F5C *p, unsigned int type);
void PossStartFumble(void);
void PossGrabBall(Object_80039F5C *p);
void PossResetMissedCatch(void);
void PossUpdateMissedCatch(Ball_t *pBall);
void ClockRuleRestartOnReady(void);
int fn_80178308(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
int fn_801787A0(void);
int fn_801486A0(void);
int MathAngleDiff(int a, int b);
void MatPushUnit(void);
void MatPop(void);
void MatRotX(int a);
void MatRotY(int a);
void MatRotZ(int a);
void MatTranslate(void *a);
void MatGetPos(float *p);
void QuatFromMat(Quat_801EB488 *pRot);
void Vec2Scale(void *pOut, void *p, float scale);
void Vec2ScaleAcc(void *pPoint, void *pVelocity, float scale);
void Vec2Sub(void *pOut, void *pA, void *pB);
unsigned int SyncTimeGetGameTime(void);
void BallStateChange(Ball_t *pBall, int state, int arg);
int BallStateGet(Ball_t *pBall, int *pArg);
int fn_800A3444(void);
int fn_801784C4(void);
float SyncRandGetFloat(int stream);
int fn_801CFE40(float y, float x);
void Vec3Add(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void Vec3Normalize(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void Vec3Scale(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void Vec3RotateZYX(Vector_80039F5C *pOut, Vector_80039F5C *pIn, int a, int b, int c);
void QuatIdentity(Quat_801EB488 *pRot);
float QuatLength(Quat_801EB488 *pRot);
void QuatNormalize(Quat_801EB488 *pOut, Quat_801EB488 *pIn);
void QuatMultiply(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB);
void QuatSubtract(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB);
void QuatInverse(Quat_801EB488 *pOut, Quat_801EB488 *pIn);
void QuatFromAxisAngle(Quat_801EB488 *pOut, Vector_80039F5C *pAxis, int angle);
void QuatFromEuler(Quat_801EB488 *pOut, int a, int b, int c);
void QuatSlerp(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
void Vec3ScaleAcc(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
int BallIsContactRaised(Ball_t *pBall);
void BallSetSpinMode(Ball_t *pBall, int a);
void BallPredictLanding(Ball_t *pBall);
void PlyrPoseGetAttachTransform(void *pObject, Vector_80039F5C *pPos, Quat_801EB488 *pRot);
void fn_8009BFD0(Object_80039F5C *p, Vector_80039F5C *pPos, Quat_801EB488 *pRot);
void Vec3ScaleLength(Vector_80039F5C *pOut, Vector_80039F5C *pIn, float length);
int Vec3Equal(Vector_80039F5C *pA, Vector_80039F5C *pB, float eps);
void BallStatePreUpdate(Ball_t *pBall, float dt);
void BallStateHitGround(Ball_t *pBall, float dt);
void BallApplyImpulse(Ball_t *pBall, Vector_80039F5C *pA, Vector_80039F5C *pB);
void WeatherGetWindVector(Vector_80039F5C *pOut);
void BallTransformShapePoint(Vector_80039F5C *pPos, Quat_801EB488 *pRot, int index, Vector_80039F5C *pOut);
void BallUpdateGroundPoint(Ball_t *pBall);
void BallFindLowestPoint(Ball_t *pBall, Vector_80039F5C *pOut, int *pIndex);
}

float _BallPhys_fBounce = 0.35f;
float _BallPhys_fWindTail = 0.8f;
float _BallPhys_fWindHead = 1.4f;
float _BallPhys_fWobbleLift = 1.25f;
float _BallPhys_fCatchHeight = 1.25f;

static inline void ClearVector(Vector_80039F5C *pV)
{
    pV->mX = pV->mY = pV->mZ = 0.0f;
}

extern "C" {

float BallGetRestitution(Ball_t *pBall, int index);
float BallGetFriction(Ball_t *pBall, int index);

int BallIsOverField(Ball_t *pBall)
{
    Vector_80039F5C pos;
    int result = 1;

    if (fn_800A3444() == 1) {
        pos.mX = pBall->mState.mPos.mX;
        pos.mY = pBall->mState.mPos.mY;
        pos.mZ = pBall->mState.mPos.mZ;
        if (fn_801784C4()) {
            pos.mX = -pos.mX;
            pos.mY = -pos.mY;
        }
        if (pos.mX > 18.0f || pos.mY > 40.5f) {
            result = 0;
        }
    } else if (fn_800A3444() == 0) {
        pos.mX = pBall->mState.mPos.mX;
        pos.mY = pBall->mState.mPos.mY;
        pos.mZ = pBall->mState.mPos.mZ;
        if (fn_801784C4()) {
            pos.mX = -pos.mX;
            pos.mY = -pos.mY;
        }
        if (pos.mY < -51.4f || pos.mY > 71.4f) {
            result = 0;
        }
        if (pos.mX > 20.5f) {
            if (pos.mY > 41.378f || pos.mY < -25.52f) {
                result = 0;
            } else if (pos.mY < 28.971 && pos.mY > -13.124f) {
                result = 0;
            }
        }
    }
    return result;
}

int BallIsOnGround(Ball_t *pBall)
{
    int result = 0;

    if (pBall->mState.mUnknown94.mZ <= 0.0f && pBall->mState.mUnknown54.mZ <= 0.0f && BallIsOverField(pBall)) {
        result = 1;
    }
    return result;
}

int BallIsUnsupported(Ball_t *pBall)
{
    int result = 1;

    if (pBall->mState.mUnknown94.mZ <= 0.0f) {
        result = BallIsOverField(pBall) == 0;
    }
    return result;
}

void BallApplyGravity(Ball_t *pBall, float value)
{
    Vector_80039F5C v;

    v.mX = 0.0f;
    v.mY = 0.0f;
    v.mZ = value * -0.875f;
    BallApplyImpulse(pBall, &v, &pBall->mState.mPos);
}

void BallApplySideSpin(Ball_t *pBall, unsigned int time)
{
    Vector_80039F5C v;
    Vector_80039F5C dir;
    Vector_80039F5C pos;
    float range;

    if (fabsf(pBall->mState.mUnknownE0) > 0.0f) {
        BallGetVelocity(pBall, &dir);
        BallGetPosition(pBall, &pos);
        range = 0.1788889f;
        Vec2Magnitude(&dir);
        if (fabsf(dir.mZ) < range) {
            v.mX = pBall->mState.mUnknownE0 * (range - fabsf(dir.mZ)) / range;
            v.mY = -fabsf(v.mX) * 0.5f;
            v.mZ = 0.0f;
            pos.mY += 1.0f;
            BallApplyImpulse(pBall, &v, &pos);
        }
    }
}

void BallGetBounceForce(Ball_t *pBall, Vector_80039F5C *pOut)
{
    float scale = BallGetRestitution(pBall, pBall->mState.mUnknownA0);

    pOut->mY = pOut->mX = 0.0f;
    scale = (scale + 1.0f) * -293.47824f;
    pOut->mZ = pBall->mState.mUnknown54.mZ * scale;
}

void BallVecAddScaled(Vector_80039F5C *pV, float scale)
{
    Vector_80039F5C delta;

    if (pV) {
        float x = pV->mX;
        float y = pV->mY;
        float z = pV->mZ;

        delta.mX = x * scale;
        delta.mY = y * scale;
        delta.mZ = z * scale;
        Vec3Add(pV, pV, &delta);
    }
}

void BallVecJitter(Vector_80039F5C *pV, float scale)
{
    Vector_80039F5C delta;
    float size = Vec3Magnitude(pV) * scale;

    delta.mX = size * (SyncRandGetFloat(0) - 0.5f);
    delta.mY = size * (SyncRandGetFloat(0) - 0.5f);
    delta.mZ = size * (SyncRandGetFloat(0) - 0.5f);
    Vec3Add(pV, pV, &delta);
}

void BallApplyGroundFriction(Ball_t *pBall, float dt)
{
    Vector_80039F5C pos;
    Quat_801EB488 rot;
    Vector_80039F5C point;
    Vector_80039F5C force;
    Vector_80039F5C dir;
    Vector_80039F5C v;
    float size;

    if (!BallIsUnsupported(pBall)) {
        pos.mX = pBall->mState.mUnknown28.mX;
        pos.mY = pBall->mState.mUnknown28.mY;
        pos.mZ = pBall->mState.mUnknown28.mZ;
        rot.mX = pBall->mState.mUnknown34.mX;
        rot.mY = pBall->mState.mUnknown34.mY;
        rot.mZ = pBall->mState.mUnknown34.mZ;
        rot.mW = pBall->mState.mUnknown34.mW;
        BallTransformShapePoint(&pos, &rot, pBall->mState.mUnknownA0, &point);
        dir.mX = pBall->mState.mUnknown94.mX - point.mX;
        dir.mY = pBall->mState.mUnknown94.mY - point.mY;
        dir.mZ = 0.0f;
        v.mX = -dir.mX * 293.47824f;
        v.mY = -dir.mY * 293.47824f;
        v.mZ = 0.0f;
        size = Vec3Magnitude(&v);
        size *= -BallGetFriction(pBall, pBall->mState.mUnknownA0);
        Vec3Normalize(&dir, &dir);
        Vec3Scale(&force, &dir, size);
        BallApplyImpulse(pBall, &force, &pBall->mState.mUnknown94);
    }
}

void BallSpinToQuat(Vector_80039F5C *pV, Quat_801EB488 *pRot)
{
    Vector_80039F5C axis;
    int angle = (int)(Vec3Magnitude(pV) * 2670176.75f);

    Vec3Normalize(&axis, pV);
    QuatFromAxisAngle(pRot, &axis, angle);
    QuatNormalize(pRot, pRot);
}

void BallUpdateRotation(Ball_t *pBall, float dt)
{
    Quat_801EB488 spin;
    Quat_801EB488 rest;
    Quat_801EB488 tilt;
    Quat_801EB488 roll;
    int angles[3];
    Vector_80039F5C v;
    float size;

    switch (pBall->mState.mUnknownD0) {
    case 1:
    case 2:
        v.mX = pBall->mState.mUnknown54.mX;
        v.mY = pBall->mState.mUnknown54.mY;
        v.mZ = pBall->mState.mUnknown54.mZ;
        angles[2] = fn_801CFE40(v.mY, v.mX) + 0x400000;
        Vec3RotateZYX(&v, &v, -angles[2], 0, 0);
        angles[0] = fn_801CFE40(v.mZ, v.mY);
        QuatFromEuler(&pBall->mState.mUnknown18, angles[2], 0, angles[0]);
        if (pBall->mState.mUnknownD0 == 2) {
            QuatFromEuler(&tilt, 0, 0xFFC00000, 0x400000);
        } else {
            QuatFromEuler(&tilt, 0, 0xFFC00000, 0xFFC00000);
        }
        QuatMultiply(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &tilt);
        pBall->mState.mUnknownD8 = (pBall->mState.mUnknownD8 + pBall->mState.mUnknownD4) & 0xFFFFFF;
        v.mX = 0.0f;
        v.mY = pBall->mState.mUnknownDC * 0.5f;
        v.mZ = 1.0f;
        Vec3Normalize(&v, &v);
        QuatFromAxisAngle(&roll, &v, pBall->mState.mUnknownD8);
        QuatMultiply(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &roll);
        QuatInverse(&tilt, &pBall->mState.mUnknown34);
        QuatMultiply(&pBall->mState.mUnknown60, &pBall->mState.mUnknown18, &tilt);
        break;
    case 3: {
        float tiltAngle;

        v.mX = pBall->mState.mUnknown54.mX;
        v.mY = pBall->mState.mUnknown54.mY;
        v.mZ = pBall->mState.mUnknown54.mZ;
        angles[2] = fn_801CFE40(v.mY, v.mX) + 0x400000;
        QuatFromEuler(&pBall->mState.mUnknown18, angles[2], 0, 0);
        tiltAngle = (int)(pBall->mState.mUnknownDC * 466033.0f) - 0x400000;
        QuatFromEuler(&tilt, 0, 0x400000, (int)tiltAngle);
        QuatMultiply(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &tilt);
        pBall->mState.mUnknownD8 = (pBall->mState.mUnknownD8 + pBall->mState.mUnknownD4) & 0xFFFFFF;
        v.mX = pBall->mState.mUnknownDC * 0.5f;
        v.mY = 1.0f;
        v.mZ = 0.0f;
        Vec3Normalize(&v, &v);
        QuatFromAxisAngle(&roll, &v, pBall->mState.mUnknownD8);
        QuatMultiply(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &roll);
        QuatInverse(&tilt, &pBall->mState.mUnknown34);
        QuatMultiply(&pBall->mState.mUnknown60, &pBall->mState.mUnknown18, &tilt);
        break;
    }
    case 0:
    default:
        Vec3Scale(&pBall->mState.mUnknown88, &pBall->mState.mUnknown88, 0.30666667f);
        BallSpinToQuat(&pBall->mState.mUnknown88, &spin);
        QuatMultiply(&pBall->mState.mUnknown60, &spin, &pBall->mState.mUnknown60);
        QuatIdentity(&rest);
        QuatSubtract(&rest, &rest, &pBall->mState.mUnknown60);
        size = QuatLength(&rest);
        if (size > 0.5f) {
            QuatIdentity(&rest);
            QuatSlerp(&pBall->mState.mUnknown60, &pBall->mState.mUnknown60, &rest, (size - 0.5f) / size);
        }
        if (BallIsOnGround(pBall)) {
            QuatIdentity(&rest);
            QuatSlerp(&pBall->mState.mUnknown60, &pBall->mState.mUnknown60, &rest, 0.8f);
        }
        tilt.mX = pBall->mState.mUnknown18.mX;
        tilt.mY = pBall->mState.mUnknown18.mY;
        tilt.mZ = pBall->mState.mUnknown18.mZ;
        tilt.mW = pBall->mState.mUnknown18.mW;
        QuatMultiply(&tilt, &pBall->mState.mUnknown60, &tilt);
        QuatNormalize(&tilt, &tilt);
        pBall->mState.mUnknown18.mX = tilt.mX;
        pBall->mState.mUnknown18.mY = tilt.mY;
        pBall->mState.mUnknown18.mZ = tilt.mZ;
        pBall->mState.mUnknown18.mW = tilt.mW;
        break;
    }
}

void BallClampToWorld(Ball_t *pBall)
{
    if (fabsf(pBall->mState.mPos.mX) > 42.0f) {
        pBall->mState.mUnknown54.mX = 0.0f;
    }
    if (fabsf(pBall->mState.mPos.mY) > 75.0f) {
        pBall->mState.mUnknown54.mY = 0.0f;
    }
    pBall->mState.mPos.mX = pBall->mState.mPos.mX < -42.0f ? -42.0f : pBall->mState.mPos.mX;
    pBall->mState.mPos.mX = pBall->mState.mPos.mX > 42.0f ? 42.0f : pBall->mState.mPos.mX;
    pBall->mState.mPos.mY = pBall->mState.mPos.mY < -75.0f ? -75.0f : pBall->mState.mPos.mY;
    pBall->mState.mPos.mY = pBall->mState.mPos.mY > 75.0f ? 75.0f : pBall->mState.mPos.mY;
    pBall->mState.mPos.mZ = pBall->mState.mPos.mZ > 30.0f ? 30.0f : pBall->mState.mPos.mZ;
}

void BallFlipPosition(Vector_80039F5C *pOut, Vector_80039F5C *pIn, int flip)
{
    if (flip) {
        pOut->mX = -pIn->mX;
        pOut->mY = -pIn->mY;
        pOut->mZ = pIn->mZ;
    } else {
        pOut->mX = pIn->mX;
        pOut->mY = pIn->mY;
        pOut->mZ = pIn->mZ;
    }
}

void BallFlipRotation(Quat_801EB488 *pOut, Quat_801EB488 *pIn, int flip)
{
    Quat_801EB488 turn;
    Quat_801EB488 rot;

    if (flip) {
        QuatFromEuler(&turn, 0x800000, 0, 0);
        QuatMultiply(pOut, &turn, pIn);
    } else {
        pOut->mX = pIn->mX;
        pOut->mY = pIn->mY;
        pOut->mZ = pIn->mZ;
        pOut->mW = pIn->mW;
    }
    QuatFromEuler(&rot, 0x400000, 0, 0x400000);
    QuatMultiply(pOut, pOut, &rot);
}

void BallStepFree(Ball_t *pBall, float dt)
{
    if (BallIsOnGround(pBall)) {
        float limit = dt * 0.0025f;

        if (fabsf(pBall->mState.mUnknown54.mZ) < limit && fabsf(pBall->mState.mUnknown60.mW) >= 0.9999f &&
            pBall->mState.mPos.mZ <= 0.097261354f && fabsf(pBall->mState.mUnknown54.mX) < limit &&
            fabsf(pBall->mState.mUnknown54.mY) < limit) {
            ClearVector(&pBall->mState.mUnknown54);
            ClearVector(&pBall->mState.mUnknown70);
            QuatIdentity(&pBall->mState.mUnknown60);
            ClearVector(&pBall->mState.mUnknown88);
            ClearVector(&pBall->mState.mUnknown7C);
        }
    }
    BallApplySideSpin(pBall, (unsigned int)dt);
    Vec3Scale(&pBall->mState.mUnknown70, &pBall->mState.mUnknown7C, 0.0034074076f);
    Vec3Add(&pBall->mState.mUnknown54, &pBall->mState.mUnknown54, &pBall->mState.mUnknown70);
    Vec3ScaleAcc(&pBall->mState.mPos, &pBall->mState.mUnknown54, dt);
    BallClampToWorld(pBall);
    BallUpdateRotation(pBall, dt);
    if (BallIsContactRaised(pBall)) {
        BallPredictLanding(pBall);
    }
}

float BallGetRestitution(Ball_t *pBall, int index)
{
    float value = _BallPhys_fBounce;

    if (index == 0 || index == 5) {
        value *= 0.85f;
    }
    if (pBall) {
        value *= pBall->mState.mUnknownEC;
    }
    return value;
}

float BallGetFriction(Ball_t *pBall, int index)
{
    float value = 0.24f;

    if (pBall) {
        value = pBall->mState.mUnknownE8 * value;
    }
    return value;
}

void BallStartSpin(Ball_t *pBall, int mode, float spin, float rate)
{
    QuatEulerAngles_t angles;

    BallSetSpinMode(pBall, mode);
    pBall->mState.mUnknownE0 = 0.0f;
    if (mode) {
        pBall->mState.mUnknownDC = spin;
        pBall->mState.mUnknownD4 = -(int)(rate * 279620.28f);
        if (mode == 3) {
            QuatToEuler(&angles, &pBall->mState.mUnknown18.mX);
            pBall->mState.mUnknownD8 = angles.mUnknown0;
        } else {
            pBall->mState.mUnknownD8 = 0x800000;
        }
    }
    if (pBall->mState.mState == 4) {
        AudmonEventPostArgs(0x20, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
    }
}

void BallRecordBounce(Ball_t *pBall)
{
    Block_80170E64 *pBlock = pBall->mpUnknown00;
    int flip;

    if (Vec3Magnitude(&pBall->mState.mUnknown54) > 0.3f && pBlock->mUnknown152 == 0) {
        flip = fn_801784C4();
        BallFlipPosition(&pBlock->mUnknown124, &pBall->mState.mPos, flip);
        BallFlipRotation(&pBlock->mUnknown136, &pBall->mState.mUnknown18, flip);
        pBlock->mUnknown152 = 1;
    }
}

void BallSyncModel(Ball_t *pBall)
{
    Block_80170E64 *pBlock = pBall->mpUnknown00;
    int flip = fn_801784C4();

    BallFlipPosition(&pBlock->mUnknown4, &pBall->mState.mPos, flip);
    BallFlipRotation(&pBlock->mUnknown108, &pBall->mState.mUnknown18, flip);
}

static void BallGetWindDrift(Vector_80039F5C *pAccel, Vector_80039F5C *pOut, float t)
{
    Vector_80039F5C wind;

    WeatherGetWindVector(&wind);
    Vec3Scale(pAccel, &wind, 0.0f);
    Vec3Scale(pOut, pAccel, 0.5f * t * t);
}

static void BallApplyWindForce(Ball_t *pBall, float scale)
{
    Vector_80039F5C wind;
    Vector_80039F5C force;

    WeatherGetWindVector(&wind);
    wind.mY *= wind.mY > 0.0f ? _BallPhys_fWindTail : _BallPhys_fWindHead;
    Vec3Scale(&force, &wind, scale * 0.93913037f);
    BallApplyImpulse(pBall, &force, &pBall->mState.mPos);
}

static void BallApplyWindForceDamped(Ball_t *pBall, float scale)
{
    Vector_80039F5C wind;
    Vector_80039F5C force;

    WeatherGetWindVector(&wind);
    if (wind.mY > 0.0f) {
        wind.mY *= _BallPhys_fWindTail;
    }
    Vec3Scale(&force, &wind, scale * 0.93913037f);
    BallApplyImpulse(pBall, &force, &pBall->mState.mPos);
}

void BallApplyContactForce(Ball_t *pBall, float dt)
{
    Vector_80039F5C force;
    Vector_80039F5C jitter;
    float size;

    BallGetBounceForce(pBall, &force);
    size = Vec3Magnitude(&force);
    if (size > 20.0f && SyncRandGetFloat(0) < 0.4f) {
        jitter.mX = SyncRandGetFloat(0) - 0.5f;
        jitter.mY = SyncRandGetFloat(0);
        jitter.mZ = 0.0f;
        if (pBall->mState.mUnknown54.mY > 0.0f) {
            jitter.mY = -jitter.mY;
        }
        Vec3ScaleLength(&jitter, &jitter, size * 0.5f);
        Vec3Add(&force, &force, &jitter);
    }
    if (pBall->mState.mStateArg == 1 && (pBall->mState.mFlags & 0x40)) {
        BallVecAddScaled(&force, 0.2f);
    }
    pBall->mState.mFlags &= ~0x40;
    BallVecJitter(&force, 0.05f);
    BallApplyImpulse(pBall, &force, &pBall->mState.mUnknown94);
    pBall->mState.mPos.mZ -= pBall->mState.mUnknown94.mZ;
    pBall->mState.mUnknownE0 = 0.0f;
    AudmonEventPostArgs(0x1F, &pBall->mState.mPos, (unsigned int)(force.mZ * 65536.0f), 0, 0);
}

static void BallApplyWobble(Ball_t *pBall)
{
    Vector_80039F5C *pVel = &pBall->mState.mUnknown54;
    Vector_80039F5C force;
    Vector_80039F5C point;
    int count = ++pBall->mState.mUnknownE4;

    if ((pBall->mState.mFlags & 0x20) && count == 3) {
        pBall->mState.mUnknownE4 = 0;
        if (Vec2Magnitude(pVel) > pVel->mZ + pVel->mZ && SyncRandGetFloat(0) < 0.6f) {
            force.mX = -pVel->mX * 440.21735f;
            force.mY = -pVel->mY * 440.21735f;
            force.mZ = (Vec3Magnitude(pVel) - pVel->mZ) * _BallPhys_fWobbleLift * 293.47824f;
            Vec3Scale(&force, &force, BallGetRestitution(pBall, pBall->mState.mUnknownA0));
            Vec3Sub(&point, &pBall->mState.mPos, &pBall->mState.mUnknown94);
            Vec3Add(&point, &point, &pBall->mState.mPos);
            if (force.mZ > 20.543476f) {
                pBall->mState.mFlags |= 8;
            }
            BallApplyImpulse(pBall, &force, &point);
            pBall->mState.mFlags &= ~0x20;
        }
    }
}

void BallStepDefault(Ball_t *pBall, float dt)
{
    BallUpdateGroundPoint(pBall);
    BallStatePreUpdate(pBall, dt);
    BallApplyGravity(pBall, dt);
    BallApplyGroundFriction(pBall, dt);
}

void BallStepGroundContact(Ball_t *pBall, float dt)
{
    BallUpdateGroundPoint(pBall);
    if (BallIsOnGround(pBall)) {
        if (!Vec3Equal(&pBall->mState.mUnknown28, &pBall->mState.mPos, 1e-07f)) {
            BallStateHitGround(pBall, dt);
        }
        BallUpdateGroundPoint(pBall);
        BallSetSpinMode(pBall, 0);
    }
}

void BallFollowHolder(Ball_t *pBall, float dt)
{
    Quat_801EB488 rot;
    Quat_801EB488 turn;
    Object_80039F5C *pHolder = fn_8009BCE8(&pBall->mState.mUnknownB4);
    Block_80170E64 *pHolderBlock = pHolder->mpUnknown4;
    Block_80170E64 *pBlock = BallGetModel(pBall);

    fn_8009BFD0(pHolder, &pBall->mState.mPos, &rot);
    QuatFromEuler(&turn, 0, 0, 0xFFC00000);
    QuatMultiply(&rot, &rot, &turn);
    QuatNormalize(&rot, &rot);
    QuatFromEuler(&turn, 0xFFC00000, 0, 0);
    QuatMultiply(&pBall->mState.mUnknown18, &rot, &turn);
    QuatNormalize(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18);
    PlyrPoseGetAttachTransform(pHolderBlock, &pBlock->mUnknown4, &pBlock->mUnknown108);
    Vec3Sub(&pBall->mState.mUnknown54, &pBall->mState.mPos, &pBall->mState.mUnknown28);
    if (dt != 0.0f) {
        Vec3Scale(&pBall->mState.mUnknown54, &pBall->mState.mUnknown54, 1.0f / dt);
    }
}

void BallStepMotion(Ball_t *pBall, float dt)
{
    Block_80170E64 *pBlock;

    pBall->mState.mUnknown28.mX = pBall->mState.mPos.mX;
    pBall->mState.mUnknown28.mY = pBall->mState.mPos.mY;
    pBall->mState.mUnknown28.mZ = pBall->mState.mPos.mZ;
    pBall->mState.mUnknown34.mX = pBall->mState.mUnknown18.mX;
    pBall->mState.mUnknown34.mY = pBall->mState.mUnknown18.mY;
    pBall->mState.mUnknown34.mZ = pBall->mState.mUnknown18.mZ;
    pBall->mState.mUnknown34.mW = pBall->mState.mUnknown18.mW;
    pBlock = pBall->mpUnknown00;
    if (!BallGetHolder(pBall)) {
        BallStepFree(pBall, dt);
    } else {
        BallFollowHolder(pBall, dt);
    }
    ClearVector(&pBall->mState.mUnknown7C);
    ClearVector(&pBall->mState.mUnknown88);
    pBlock->mUnknown660 = LevelFindArea(&pBlock->mUnknown4.mX);
}

void BallRestAtAngles(Ball_t *pBall, int *pAngles)
{
    Vector_80039F5C low;
    int index;

    QuatFromEuler(&pBall->mState.mUnknown18, pAngles[2], pAngles[1], pAngles[0]);
    pBall->mState.mPos.mZ = 0.0f;
    BallFindLowestPoint(pBall, &low, &index);
    pBall->mState.mPos.mZ = -low.mZ;
    ClearVector(&pBall->mState.mUnknown54);
    ClearVector(&pBall->mState.mUnknown70);
    QuatIdentity(&pBall->mState.mUnknown60);
    pBall->mState.mUnknown28 = pBall->mState.mPos;
    pBall->mState.mUnknown34 = pBall->mState.mUnknown18;
}

static void BallAddClampedE0(Ball_t *pBall, float delta)
{
    float value = pBall->mState.mUnknownE0 + delta;

    if (value < -1.0f) {
        pBall->mState.mUnknownE0 = -1.0f;
    } else if (value > 1.0f) {
        pBall->mState.mUnknownE0 = 1.0f;
    } else {
        pBall->mState.mUnknownE0 = value;
    }
}

void BallClearPassFlag(Ball_t *pBall)
{
    pBall->mState.mFlags &= ~8;
}

void BallSolveFallToHeight(Ball_t *pBall, float height, float *pTime, Vector_80039F5C *pLanding)
{
    Point_8017886C pos;
    float vz = pBall->mState.mUnknown54.mZ;
    float t = (pBall->mState.mPos.mZ - height) * 0.005962963f + vz * vz;

    t *= 112495.65f;
    t = t < 0.0f ? 0.0f : t;
    t = sqrtf(t);
    t = vz * 335.40372f + t;
    if (t > 0.0f) {
        Vec2Scale(&pos, &pBall->mState.mUnknown70, 0.5f * t * t);
        Vec2ScaleAcc(&pos, &pBall->mState.mUnknown54, t);
        Vec2Add(&pos, &pos, &pBall->mState.mPos);
        pLanding->mY = pos.mY;
        pLanding->mX = pos.mX;
        if (pTime) {
            *pTime = t;
        }
    } else {
        if (pTime) {
            *pTime = 0.0f;
        }
        pLanding->mX = pBall->mState.mPos.mX;
        pLanding->mY = pBall->mState.mPos.mY;
    }
}

void BallPredictLanding(Ball_t *pBall)
{
    BallSolveFallToHeight(pBall, _BallPhys_fCatchHeight, &pBall->mState.mUnknown44, &pBall->mState.mUnknown48);
    pBall->mState.mUnknown48.mZ = _BallPhys_fCatchHeight;
}

float BallGetHeightAtTime(Ball_t *pBall, float t)
{
    Vector_80039F5C vel;
    Vector_80039F5C pos;
    float g = 0.0029814816f;

    BallGetVelocity(pBall, &vel);
    BallGetPosition(pBall, &pos);
    return (pos.mZ + t * vel.mZ) - t * g * t * 0.5f;
}

void BallResetPhysics(Ball_t *pBall)
{
    fn_800A33DC();
    fn_800A33D0();
    // FAKEMATCH: The overwritten zero store recovers the register allocation for both scales.
    pBall->mState.mUnknownE8 = 0.0f;
    pBall->mState.mUnknownE8 = 1.2f;
    pBall->mState.mUnknownEC = 1.35f;
}

void BallLaunchToTarget(Ball_t *pBall, Vector_80039F5C *pTarget, int mode, float speed, float spin, float rate)
{
    Vector_80039F5C delta;
    float time;

    pBall->mState.mUnknown48.mX = pTarget->mX;
    pBall->mState.mUnknown48.mY = pTarget->mY;
    pBall->mState.mUnknown48.mZ = pTarget->mZ;
    Vec3Sub(&delta, pTarget, &pBall->mState.mPos);
    time = Vec2Magnitude(&delta) / speed * gFrameTimeScale;
    delta.mZ += 0.0029814816f * time * time * 0.5f;
    Vec3Scale(&pBall->mState.mUnknown54, &delta, 1.0f / time);
    BallStartSpin(pBall, mode, spin, rate);
}

void BallLaunchWithVelocity(Ball_t *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate)
{
    pBall->mState.mUnknown54.mX = pVelocity->mX;
    pBall->mState.mUnknown54.mY = pVelocity->mY;
    pBall->mState.mUnknown54.mZ = pVelocity->mZ;
    BallPredictLanding(pBall);
    BallStartSpin(pBall, mode, spin, rate);
}

static int BallIsSettled(Ball_t *pBall)
{
    if (BallGetHolder(pBall)) {
        return 0;
    }
    if (pBall->mState.mUnknown94.mZ > 0.0f) {
        return 0;
    }
    if (pBall->mState.mUnknown54.mZ > 0.0f) {
        return 0;
    }
    return Vec3Magnitude(&pBall->mState.mUnknown54) <= 0.01f;
}

int BallIsContactRaised(Ball_t *pBall)
{
    return pBall->mState.mUnknown94.mZ > 0.0f;
}

int BallGetSpinMode(Ball_t *pBall)
{
    return pBall->mState.mUnknownD0;
}

void BallSetSpinMode(Ball_t *pBall, int mode)
{
    pBall->mState.mUnknownD0 = mode;
}

int BallPlayerHandsFree(Object_80039F5C *p)
{
    PlyrAnimRecord_t *pRecords = (PlyrAnimRecord_t *)p->mpUnknown792;
    unsigned char i;
    int result = 1;

    for (i = 0; i < 4; i++) {
        PlyrAnimRecord_t *pRecord = &pRecords[i];

        if (pRecord->mState == 3 || pRecord->mState == 1) {
            switch (pRecord->mKey) {
            case 0xB5:
            case 0xBA:
            case 0xC3:
            case 0xC4:
            case 0xC5:
            case 0xD2:
                result = 0;
                break;
            }
        }
        if (!result) {
            break;
        }
    }
    return result;
}

int BallCanPlayerTouch(Ball_t *pBall, Object_80039F5C *p, unsigned int type, int facing)
{
    Point_8017886C delta;
    unsigned short state = BallStateGet(pBall, 0);
    int result = 0;

    switch (type) {
    case 1:
    case 2:
    case 10:
        if (state == 3 || state == 4) {
            result = 1;
        } else {
            if (PossIsWristNearJoint(pBall, p, 0)) {
                result = 1;
            }
            if (!BallPlayerHandsFree(p)) {
                result = 0;
            }
        }
        break;
    case 3:
    case 4:
    case 9:
        if (state == 3 || state == 4) {
            result = 1;
        } else {
            if (PossIsWristNearJoint(pBall, p, 1)) {
                result = 1;
            }
            if (!BallPlayerHandsFree(p)) {
                result = 0;
            }
        }
        break;
    default:
        if (facing && (type == 0 || type == 7 || type == 5 || type == 1 || type == 3)) {
            Vec2Sub(&delta, &pBall->mState.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x3FFFFF) {
                result = 1;
            }
        }
        break;
    }
    if ((p->mFlags & 0x800) && !fn_801486A0() && (unsigned int)(p->mpState->mId - 10) <= 1) {
        result = 0;
    }
    return result;
}

void BallStateHeldEnter(Ball_t *pBall)
{
    Block_80170E64 *pBlock = BallGetModel(pBall);

    pBall->mState.mUnknownBC = 0;
    pBall->mState.mUnknownC4 = 1;
    BallClearPassFlag(pBall);
    pBlock->mUnknown20 |= 2;
    pBall->mState.mFlags &= ~0x20;
}

void BallStatePassEnter(Ball_t *pBall)
{
    PossResetMissedCatch();
    pBall->mState.mFlags = (pBall->mState.mFlags | 8) & ~0x10;
}

void BallStatePassExit(Ball_t *pBall)
{
    BallClearPassFlag(pBall);
    AudmonEventPostArgs(0x22, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
}

void BallStateLooseExit(Ball_t *pBall)
{
    if (pBall == BallGetCurrent() && pBall->mState.mStateArg != 0) {
        LooseBallBroadcast(BallGetIndex(pBall));
    }
}

void BallStateStepTimed(Ball_t *pBall, float dt)
{
    Vector_80039F5C pos;
    int counting = 1;
    Object_80039F5C *pHolder = BallGetHolder(pBall);

    BallStepDefault(pBall, dt);
    pBall->mState.mUnknownC0 = SyncTimeGetGameTime();
    if (fn_801BE648(pHolder->mpUnknown792) == 0xE1) {
        fn_8009BF5C(pHolder, 0, &pos, 0);
        counting = pos.mZ <= 2.25f;
    }
    if (counting) {
        pBall->mState.mUnknownBC += (unsigned int)dt;
    }
}

void BallStateStopVelocity(Ball_t *pBall, float dt)
{
    if (Vec3Magnitude(&pBall->mState.mUnknown54) != 0.0f) {
        pBall->mState.mUnknown54.mX = pBall->mState.mUnknown54.mY = pBall->mState.mUnknown54.mZ = 0.0f;
    }
}

void BallStatePassMove(Ball_t *pBall, float dt)
{
    BallStepDefault(pBall, dt);
    AudmonEventPostArgs(0x21, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
    PossUpdateMissedCatch(pBall);
}

void BallStateDeadEnter(Ball_t *pBall)
{
    ClockRuleRestartOnReady();
}

void BallStateHeldExit(Ball_t *pBall)
{
    Block_80170E64 *pBlock = BallGetModel(pBall);

    pBlock->mUnknown20 &= ~2;
    pBall->mState.mUnknownC0 = SyncTimeGetGameTime();
    pBall->mState.mUnknownBC = 0;
    pBall->mState.mUnknownCC = pBall->mState.mUnknownB4;
}

void BallStatePassHitGround(Ball_t *pBall, float dt)
{
    if (fn_800AD9B4() == 3 && (BallGetCurrent() == pBall || fn_801486A0() == 1)) {
        if (!fn_801783AC(1)) {
            BallStateChange(pBall, 5, 0);
            PossEndIncompletePass();
        } else {
            PossStartFumble();
        }
    }
    BallApplyContactForce(pBall, dt);
}

void BallStateLooseHitGround(Ball_t *pBall, float dt)
{
    BallApplyContactForce(pBall, dt);
}

void BallStatePitchHitGround(Ball_t *pBall, float dt)
{
    BallSetTarget(pBall, 0);
    if (BallGetCurrent() == pBall && !fn_801787A0()) {
        if (fn_801783AC(1) || !fn_801486A0()) {
            PossStartFumble();
        } else {
            PossEndIncompletePass();
        }
    } else {
        BallStateChange(pBall, 5, 0);
    }
    BallApplyContactForce(pBall, dt);
}

int BallStateHandoffTouch(Ball_t *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    int mode;
    Record_800B15FC *pRecord;
    int port;

    if (pBall == BallGetCurrent() && BallGetTarget(pBall) == p) {
        switch (type) {
        case 0:
        case 5:
        case 7:
            mode = fn_800AD9B4();
            BallSetTarget(pBall, 0);
            BallGiveToPlayer(pBall, p);
            fn_800D782C(p);
            BallSetTransferKind(pBall, 0);
            if (mode == 3) {
                pRecord = fn_800B15FC();
                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = p->mMotion.mPos.mX;
                pRecord->mUnknown10 = p->mMotion.mPos.mY;
                pRecord->mUnknown14 = 8;
                fn_800B1508();
                AudmonEventPostId(0x1E, &p->mMotion.mPos, p->mId, 1, 1, 0);
                port = fn_800B65A0(p->mIdBytes[2]);
                if (port != 0xFF && !(p->mFlags & 0x400) && fn_801486A0() != 0 && fn_801486A0() != 1) {
                    fn_800B6714(p, port);
                }
            }
            break;
        }
    }
    return 1;
}

int BallStateLooseTouch(Ball_t *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    int arg;
    int result = 0;
    int mode = fn_800AD9B4();

    BallStateGet(pBall, &arg);
    if (mode == 3 && arg == 1) {
        if (BallCanPlayerTouch(pBall, p, type, 0) &&
            (BallGetStateStartTick(pBall) + 60 < SyncTimeGetGameTime() || fn_801BE648(p->mpUnknown792) == 0x30)) {
            result = 1;
            PossGrabBall(p);
        } else {
            pBall->mState.mFlags |= 0x40;
        }
    }
    return result;
}

int BallStatePassTouch(Ball_t *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    Vector_80039F5C vel;
    int result = 0;

    if (BallCanPlayerTouch(pBall, p, type, 0)) {
        BallGetVelocity(pBall, &vel);
        if (p->mIdBytes[2] == fn_80178308() && pBall->mState.mUnknownC0 + 5 >= SyncTimeGetGameTime()) {
            result = 1;
        } else {
            result = PossTryCatch(pBall, p, type);
        }
    }
    if (!result) {
        fn_801783D0(0xB, 1);
        BallSetSpinMode(pBall, 3);
    }
    return result;
}

int BallStatePitchTouch(Ball_t *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    // FAKEMATCH: redundant zero initializer, only to keep the target branch layout
    int result = 0;

    if (fn_8009BCE8(&pBall->mState.mUnknownB8) == p && pBall->mState.mUnknownC0 + 5 >= SyncTimeGetGameTime()) {
        result = 1;
    } else if (BallCanPlayerTouch(pBall, p, type, 1)) {
        result = PossTryReceivePitch(pBall, p, type);
    } else {
        result = 0;
    }
    return result;
}

void BallStatePlacedMove(Ball_t *pBall, float dt)
{
}

void BallStatePlacedUpdate(Ball_t *pBall, float dt)
{
    Vector_80039F5C pos;
    int angles[3];
    Quat_801EB488 turn;
    BigObjInst *pPlace = BallModelGetLinkedObj(BallGetModel(BallGetCurrent()));
    BigObj_t *pObject = BigObjGet(pPlace->mUnknown4);
    short *pRot = pObject->mpUnknown220;

    angles[0] = pRot[0] << 8;
    angles[1] = pRot[1] << 8;
    angles[2] = pRot[2] << 8;
    MatPushUnit();
    pos.mX = pPlace->mState.mUnknown0;
    pos.mY = pPlace->mState.mUnknown4;
    pos.mZ = 0.0f;
    MatTranslate(&pos);
    MatRotZ((pPlace->mState.mUnknown24 + 0x400000) & 0xFFFFFF);
    MatRotX(0x400000);
    MatTranslate(pObject->mUnknown180);
    MatRotY(pObject->mUnknown204);
    MatRotZ(angles[2]);
    MatRotX((angles[0] + 0x400000) & 0xFFFFFF);
    MatGetPos(&pBall->mState.mPos.mX);
    QuatFromMat(&pBall->mState.mUnknown18);
    MatPop();
    if (fn_801784C4()) {
        pBall->mState.mPos.mX = -pBall->mState.mPos.mX;
        pBall->mState.mPos.mY = -pBall->mState.mPos.mY;
        QuatFromEuler(&turn, 0x800000, 0, 0);
        QuatMultiply(&pBall->mState.mUnknown18, &turn, &pBall->mState.mUnknown18);
    }
}

int BallStatePlacedTouch(Ball_t *pBall, void *pData, unsigned int type)
{
    return 1;
}

}
