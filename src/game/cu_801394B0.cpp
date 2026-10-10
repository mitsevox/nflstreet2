#include <math.h>

#include "game/cu_80136B1C.h"
#include "game/Object_80040818.h"
#include "game/Object_8017886C.h"
#include "game/Record_800B15FC.h"
#include "game/cu_80067C10.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801BE60C.h"
#include "game/fn_80227638.h"
#include "game/fn_801EBC18.h"
#include "game/fn_802270D4.h"

/* One of the four 100-byte records that the player object's +792 pointer
   holds (see include/game/fn_801BE60C.h). */
struct Record_801BE648 {
    char mUnknown0[4];
    unsigned short mKey;
    unsigned short mState;
    char mUnknown8[92];
};

/* Returned by fn_800400C4 for the ball's block. */
struct Object_800400C4 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mUnknown10[16];
    int mUnknown20;
};

extern float lbl_803EA2C4;

extern "C" {
Object_800400C4 *fn_800400C4(Block_80170E64 *pBlock);
Object_80040818 *fn_80040F18(int index);
float fn_800A33D0(void);
int fn_800A33DC(void);
void fn_800B1508(void);
int fn_800B65A0(int team);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800D782C(Object_80039F5C *p);
void fn_800EBA48(int index);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pA);
int fn_80170E64(Object_80137ABC *pBall, Object_80039F5C *p, int a);
void fn_80170F40(void);
int fn_80171068(Object_80137ABC *pBall, Object_80039F5C *p, unsigned int type);
int fn_801712D0(Object_80137ABC *pBall, Object_80039F5C *p, unsigned int type);
void fn_80171E30(void);
void fn_801720B4(Object_80039F5C *p);
void fn_80172F9C(void);
void fn_80172FB0(Object_80137ABC *pBall);
void fn_801736AC(void);
int fn_80178308(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
int fn_801787A0(void);
int fn_801486A0(void);
int fn_801CFFD0(int a, int b);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D08FC(int a);
void fn_801D09EC(int a);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0FB8(float *p);
void fn_801EBA64(Quat_801EB488 *pRot);
void fn_80227248(void *pOut, void *p, float scale);
void fn_8022732C(void *pPoint, void *pVelocity, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
unsigned int fn_8023790C(void);
float fn_80260B1C(float x);
void fn_8013B9C0(Object_80137ABC *pBall, int state, int arg);
int fn_8013BA58(Object_80137ABC *pBall, int *pArg);
int fn_800A3444(void);
int fn_801784C4(void);
float fn_80237260(int stream);
int fn_801CFE40(float y, float x);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_802271F0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227490(Vector_80039F5C *pOut, Vector_80039F5C *pIn, int a, int b, int c);
void fn_801EB488(Quat_801EB488 *pRot);
float fn_801EB4AC(Quat_801EB488 *pRot);
void fn_801EB52C(Quat_801EB488 *pOut, Quat_801EB488 *pIn);
void fn_801EB660(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB);
void fn_801EB61C(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB);
void fn_801EB700(Quat_801EB488 *pOut, Quat_801EB488 *pIn);
void fn_801EBBA4(Quat_801EB488 *pOut, Vector_80039F5C *pAxis, int angle);
void fn_801EBEF8(Quat_801EB488 *pOut, int a, int b, int c);
void fn_801EC048(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
int fn_8013AD78(Object_80137ABC *pBall);
void fn_8013AD9C(Object_80137ABC *pBall, int a);
void fn_8013AB24(Object_80137ABC *pBall);
void fn_800423F8(void *pObject, Vector_80039F5C *pPos, Quat_801EB488 *pRot);
int fn_80054138(Vector_80039F5C *pPos);
void fn_8009BFD0(Object_80039F5C *p, Vector_80039F5C *pPos, Quat_801EB488 *pRot);
void fn_802272DC(Vector_80039F5C *pOut, Vector_80039F5C *pIn, float length);
int fn_802275D8(Vector_80039F5C *pA, Vector_80039F5C *pB, float eps);
void fn_8013B8C0(Object_80137ABC *pBall, float dt);
void fn_8013B900(Object_80137ABC *pBall, float dt);
void fn_80139294(Object_80137ABC *pBall, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80139308(Vector_80039F5C *pPos, Quat_801EB488 *pRot, int index, Vector_80039F5C *pOut);
void fn_80139370(Object_80137ABC *pBall);
void fn_80139400(Object_80137ABC *pBall, Vector_80039F5C *pOut, int *pIndex);
}

float lbl_803EB1B0 = 0.35f;
float lbl_803EB1B4 = 0.8f;
float lbl_803EB1B8 = 1.4f;
float lbl_803EB1BC = 1.25f;
float lbl_803EB1C0 = 1.25f;

static inline void ClearVector(Vector_80039F5C *pV)
{
    pV->mX = pV->mY = pV->mZ = 0.0f;
}

extern "C" {

float fn_8013A2A4(Object_80137ABC *pBall, int index);
float fn_8013A2D8(Object_80137ABC *pBall, int index);

int fn_801394B0(Object_80137ABC *pBall)
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

int fn_80139630(Object_80137ABC *pBall)
{
    int result = 0;

    if (pBall->mState.mUnknown94.mZ <= 0.0f && pBall->mState.mUnknown54.mZ <= 0.0f && fn_801394B0(pBall)) {
        result = 1;
    }
    return result;
}

int fn_8013968C(Object_80137ABC *pBall)
{
    int result = 1;

    if (pBall->mState.mUnknown94.mZ <= 0.0f) {
        result = fn_801394B0(pBall) == 0;
    }
    return result;
}

void fn_801396D0(Object_80137ABC *pBall, float value)
{
    Vector_80039F5C v;

    v.mX = 0.0f;
    v.mY = 0.0f;
    v.mZ = value * -0.875f;
    fn_80139294(pBall, &v, &pBall->mState.mPos);
}

void fn_80139718(Object_80137ABC *pBall, unsigned int time)
{
    Vector_80039F5C v;
    Vector_80039F5C dir;
    Vector_80039F5C pos;
    float range;

    if (fabsf(pBall->mState.mUnknownE0) > 0.0f) {
        fn_80137EC4(pBall, &dir);
        fn_80137D58(pBall, &pos);
        range = 0.1788889f;
        fn_802270A4(&dir);
        if (fabsf(dir.mZ) < range) {
            v.mX = pBall->mState.mUnknownE0 * (range - fabsf(dir.mZ)) / range;
            v.mY = -fabsf(v.mX) * 0.5f;
            v.mZ = 0.0f;
            pos.mY += 1.0f;
            fn_80139294(pBall, &v, &pos);
        }
    }
}

void fn_801397FC(Object_80137ABC *pBall, Vector_80039F5C *pOut)
{
    float scale = fn_8013A2A4(pBall, pBall->mState.mUnknownA0);

    pOut->mY = pOut->mX = 0.0f;
    scale = (scale + 1.0f) * -293.47824f;
    pOut->mZ = pBall->mState.mUnknown54.mZ * scale;
}

void fn_80139864(Vector_80039F5C *pV, float scale)
{
    Vector_80039F5C delta;

    if (pV) {
        float x = pV->mX;
        float y = pV->mY;
        float z = pV->mZ;

        delta.mX = x * scale;
        delta.mY = y * scale;
        delta.mZ = z * scale;
        fn_8022765C(pV, pV, &delta);
    }
}

void fn_801398BC(Vector_80039F5C *pV, float scale)
{
    Vector_80039F5C delta;
    float size = fn_802270D4(pV) * scale;

    delta.mX = size * (fn_80237260(0) - 0.5f);
    delta.mY = size * (fn_80237260(0) - 0.5f);
    delta.mZ = size * (fn_80237260(0) - 0.5f);
    fn_8022765C(pV, pV, &delta);
}

void fn_80139954(Object_80137ABC *pBall, float dt)
{
    Vector_80039F5C pos;
    Quat_801EB488 rot;
    Vector_80039F5C point;
    Vector_80039F5C force;
    Vector_80039F5C dir;
    Vector_80039F5C v;
    float size;

    if (!fn_8013968C(pBall)) {
        pos.mX = pBall->mState.mUnknown28.mX;
        pos.mY = pBall->mState.mUnknown28.mY;
        pos.mZ = pBall->mState.mUnknown28.mZ;
        rot.mX = pBall->mState.mUnknown34.mX;
        rot.mY = pBall->mState.mUnknown34.mY;
        rot.mZ = pBall->mState.mUnknown34.mZ;
        rot.mW = pBall->mState.mUnknown34.mW;
        fn_80139308(&pos, &rot, pBall->mState.mUnknownA0, &point);
        dir.mX = pBall->mState.mUnknown94.mX - point.mX;
        dir.mY = pBall->mState.mUnknown94.mY - point.mY;
        dir.mZ = 0.0f;
        v.mX = -dir.mX * 293.47824f;
        v.mY = -dir.mY * 293.47824f;
        v.mZ = 0.0f;
        size = fn_802270D4(&v);
        size *= -fn_8013A2D8(pBall, pBall->mState.mUnknownA0);
        fn_802271F0(&dir, &dir);
        fn_80227264(&force, &dir, size);
        fn_80139294(pBall, &force, &pBall->mState.mUnknown94);
    }
}

void fn_80139A80(Vector_80039F5C *pV, Quat_801EB488 *pRot)
{
    Vector_80039F5C axis;
    int angle = (int)(fn_802270D4(pV) * 2670176.75f);

    fn_802271F0(&axis, pV);
    fn_801EBBA4(pRot, &axis, angle);
    fn_801EB52C(pRot, pRot);
}

void fn_80139AF0(Object_80137ABC *pBall, float dt)
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
        fn_80227490(&v, &v, -angles[2], 0, 0);
        angles[0] = fn_801CFE40(v.mZ, v.mY);
        fn_801EBEF8(&pBall->mState.mUnknown18, angles[2], 0, angles[0]);
        if (pBall->mState.mUnknownD0 == 2) {
            fn_801EBEF8(&tilt, 0, 0xFFC00000, 0x400000);
        } else {
            fn_801EBEF8(&tilt, 0, 0xFFC00000, 0xFFC00000);
        }
        fn_801EB660(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &tilt);
        pBall->mState.mUnknownD8 = (pBall->mState.mUnknownD8 + pBall->mState.mUnknownD4) & 0xFFFFFF;
        v.mX = 0.0f;
        v.mY = pBall->mState.mUnknownDC * 0.5f;
        v.mZ = 1.0f;
        fn_802271F0(&v, &v);
        fn_801EBBA4(&roll, &v, pBall->mState.mUnknownD8);
        fn_801EB660(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &roll);
        fn_801EB700(&tilt, &pBall->mState.mUnknown34);
        fn_801EB660(&pBall->mState.mUnknown60, &pBall->mState.mUnknown18, &tilt);
        break;
    case 3: {
        float tiltAngle;

        v.mX = pBall->mState.mUnknown54.mX;
        v.mY = pBall->mState.mUnknown54.mY;
        v.mZ = pBall->mState.mUnknown54.mZ;
        angles[2] = fn_801CFE40(v.mY, v.mX) + 0x400000;
        fn_801EBEF8(&pBall->mState.mUnknown18, angles[2], 0, 0);
        tiltAngle = (int)(pBall->mState.mUnknownDC * 466033.0f) - 0x400000;
        fn_801EBEF8(&tilt, 0, 0x400000, (int)tiltAngle);
        fn_801EB660(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &tilt);
        pBall->mState.mUnknownD8 = (pBall->mState.mUnknownD8 + pBall->mState.mUnknownD4) & 0xFFFFFF;
        v.mX = pBall->mState.mUnknownDC * 0.5f;
        v.mY = 1.0f;
        v.mZ = 0.0f;
        fn_802271F0(&v, &v);
        fn_801EBBA4(&roll, &v, pBall->mState.mUnknownD8);
        fn_801EB660(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18, &roll);
        fn_801EB700(&tilt, &pBall->mState.mUnknown34);
        fn_801EB660(&pBall->mState.mUnknown60, &pBall->mState.mUnknown18, &tilt);
        break;
    }
    case 0:
    default:
        fn_80227264(&pBall->mState.mUnknown88, &pBall->mState.mUnknown88, 0.30666667f);
        fn_80139A80(&pBall->mState.mUnknown88, &spin);
        fn_801EB660(&pBall->mState.mUnknown60, &spin, &pBall->mState.mUnknown60);
        fn_801EB488(&rest);
        fn_801EB61C(&rest, &rest, &pBall->mState.mUnknown60);
        size = fn_801EB4AC(&rest);
        if (size > 0.5f) {
            fn_801EB488(&rest);
            fn_801EC048(&pBall->mState.mUnknown60, &pBall->mState.mUnknown60, &rest, (size - 0.5f) / size);
        }
        if (fn_80139630(pBall)) {
            fn_801EB488(&rest);
            fn_801EC048(&pBall->mState.mUnknown60, &pBall->mState.mUnknown60, &rest, 0.8f);
        }
        tilt.mX = pBall->mState.mUnknown18.mX;
        tilt.mY = pBall->mState.mUnknown18.mY;
        tilt.mZ = pBall->mState.mUnknown18.mZ;
        tilt.mW = pBall->mState.mUnknown18.mW;
        fn_801EB660(&tilt, &pBall->mState.mUnknown60, &tilt);
        fn_801EB52C(&tilt, &tilt);
        pBall->mState.mUnknown18.mX = tilt.mX;
        pBall->mState.mUnknown18.mY = tilt.mY;
        pBall->mState.mUnknown18.mZ = tilt.mZ;
        pBall->mState.mUnknown18.mW = tilt.mW;
        break;
    }
}

void fn_80139F28(Object_80137ABC *pBall)
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

void fn_8013A00C(Vector_80039F5C *pOut, Vector_80039F5C *pIn, int flip)
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

void fn_8013A048(Quat_801EB488 *pOut, Quat_801EB488 *pIn, int flip)
{
    Quat_801EB488 turn;
    Quat_801EB488 rot;

    if (flip) {
        fn_801EBEF8(&turn, 0x800000, 0, 0);
        fn_801EB660(pOut, &turn, pIn);
    } else {
        pOut->mX = pIn->mX;
        pOut->mY = pIn->mY;
        pOut->mZ = pIn->mZ;
        pOut->mW = pIn->mW;
    }
    fn_801EBEF8(&rot, 0x400000, 0, 0x400000);
    fn_801EB660(pOut, pOut, &rot);
}

void fn_8013A0EC(Object_80137ABC *pBall, float dt)
{
    if (fn_80139630(pBall)) {
        float limit = dt * 0.0025f;

        if (fabsf(pBall->mState.mUnknown54.mZ) < limit && fabsf(pBall->mState.mUnknown60.mW) >= 0.9999f &&
            pBall->mState.mPos.mZ <= 0.097261354f && fabsf(pBall->mState.mUnknown54.mX) < limit &&
            fabsf(pBall->mState.mUnknown54.mY) < limit) {
            ClearVector(&pBall->mState.mUnknown54);
            ClearVector(&pBall->mState.mUnknown70);
            fn_801EB488(&pBall->mState.mUnknown60);
            ClearVector(&pBall->mState.mUnknown88);
            ClearVector(&pBall->mState.mUnknown7C);
        }
    }
    fn_80139718(pBall, (unsigned int)dt);
    fn_80227264(&pBall->mState.mUnknown70, &pBall->mState.mUnknown7C, 0.0034074076f);
    fn_8022765C(&pBall->mState.mUnknown54, &pBall->mState.mUnknown54, &pBall->mState.mUnknown70);
    fn_80227350(&pBall->mState.mPos, &pBall->mState.mUnknown54, dt);
    fn_80139F28(pBall);
    fn_80139AF0(pBall, dt);
    if (fn_8013AD78(pBall)) {
        fn_8013AB24(pBall);
    }
}

float fn_8013A2A4(Object_80137ABC *pBall, int index)
{
    float value = lbl_803EB1B0;

    if (index == 0 || index == 5) {
        value *= 0.85f;
    }
    if (pBall) {
        value *= pBall->mState.mUnknownEC;
    }
    return value;
}

float fn_8013A2D8(Object_80137ABC *pBall, int index)
{
    float value = 0.24f;

    if (pBall) {
        value = pBall->mState.mUnknownE8 * value;
    }
    return value;
}

void fn_8013A2F4(Object_80137ABC *pBall, int mode, float spin, float rate)
{
    Angles_801EBC18 angles;

    fn_8013AD9C(pBall, mode);
    pBall->mState.mUnknownE0 = 0.0f;
    if (mode) {
        pBall->mState.mUnknownDC = spin;
        pBall->mState.mUnknownD4 = -(int)(rate * 279620.28f);
        if (mode == 3) {
            fn_801EBC18(&angles, &pBall->mState.mUnknown18.mX);
            pBall->mState.mUnknownD8 = angles.mUnknown0;
        } else {
            pBall->mState.mUnknownD8 = 0x800000;
        }
    }
    if (pBall->mState.mState == 4) {
        fn_80067DB8(0x20, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
    }
}

void fn_8013A3BC(Object_80137ABC *pBall)
{
    Block_80170E64 *pBlock = pBall->mpUnknown00;
    int flip;

    if (fn_802270D4(&pBall->mState.mUnknown54) > 0.3f && pBlock->mUnknown152 == 0) {
        flip = fn_801784C4();
        fn_8013A00C(&pBlock->mUnknown124, &pBall->mState.mPos, flip);
        fn_8013A048(&pBlock->mUnknown136, &pBall->mState.mUnknown18, flip);
        pBlock->mUnknown152 = 1;
    }
}

void fn_8013A440(Object_80137ABC *pBall)
{
    Block_80170E64 *pBlock = pBall->mpUnknown00;
    int flip = fn_801784C4();

    fn_8013A00C(&pBlock->mUnknown4, &pBall->mState.mPos, flip);
    fn_8013A048(&pBlock->mUnknown108, &pBall->mState.mUnknown18, flip);
}

void fn_8013A494(Object_80137ABC *pBall, float dt)
{
    Vector_80039F5C force;
    Vector_80039F5C jitter;
    float size;

    fn_801397FC(pBall, &force);
    size = fn_802270D4(&force);
    if (size > 20.0f && fn_80237260(0) < 0.4f) {
        jitter.mX = fn_80237260(0) - 0.5f;
        jitter.mY = fn_80237260(0);
        jitter.mZ = 0.0f;
        if (pBall->mState.mUnknown54.mY > 0.0f) {
            jitter.mY = -jitter.mY;
        }
        fn_802272DC(&jitter, &jitter, size * 0.5f);
        fn_8022765C(&force, &force, &jitter);
    }
    if (pBall->mState.mStateArg == 1 && (pBall->mState.mFlags & 0x40)) {
        fn_80139864(&force, 0.2f);
    }
    pBall->mState.mFlags &= ~0x40;
    fn_801398BC(&force, 0.05f);
    fn_80139294(pBall, &force, &pBall->mState.mUnknown94);
    pBall->mState.mPos.mZ -= pBall->mState.mUnknown94.mZ;
    pBall->mState.mUnknownE0 = 0.0f;
    fn_80067DB8(0x1F, &pBall->mState.mPos, (unsigned int)(force.mZ * 65536.0f), 0, 0);
}

void fn_8013A64C(Object_80137ABC *pBall, float dt)
{
    fn_80139370(pBall);
    fn_8013B8C0(pBall, dt);
    fn_801396D0(pBall, dt);
    fn_80139954(pBall, dt);
}

void fn_8013A6A8(Object_80137ABC *pBall, float dt)
{
    fn_80139370(pBall);
    if (fn_80139630(pBall)) {
        if (!fn_802275D8(&pBall->mState.mUnknown28, &pBall->mState.mPos, 1e-07f)) {
            fn_8013B900(pBall, dt);
        }
        fn_80139370(pBall);
        fn_8013AD9C(pBall, 0);
    }
}

void fn_8013A72C(Object_80137ABC *pBall, float dt)
{
    Quat_801EB488 rot;
    Quat_801EB488 turn;
    Object_80039F5C *pHolder = fn_8009BCE8(&pBall->mState.mUnknownB4);
    Block_80170E64 *pHolderBlock = pHolder->mpUnknown4;
    Block_80170E64 *pBlock = fn_8013825C(pBall);

    fn_8009BFD0(pHolder, &pBall->mState.mPos, &rot);
    fn_801EBEF8(&turn, 0, 0, 0xFFC00000);
    fn_801EB660(&rot, &rot, &turn);
    fn_801EB52C(&rot, &rot);
    fn_801EBEF8(&turn, 0xFFC00000, 0, 0);
    fn_801EB660(&pBall->mState.mUnknown18, &rot, &turn);
    fn_801EB52C(&pBall->mState.mUnknown18, &pBall->mState.mUnknown18);
    fn_800423F8(pHolderBlock, &pBlock->mUnknown4, &pBlock->mUnknown108);
    fn_802276B4(&pBall->mState.mUnknown54, &pBall->mState.mPos, &pBall->mState.mUnknown28);
    if (dt != 0.0f) {
        fn_80227264(&pBall->mState.mUnknown54, &pBall->mState.mUnknown54, 1.0f / dt);
    }
}

void fn_8013A844(Object_80137ABC *pBall, float dt)
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
    if (!fn_80137AD0(pBall)) {
        fn_8013A0EC(pBall, dt);
    } else {
        fn_8013A72C(pBall, dt);
    }
    ClearVector(&pBall->mState.mUnknown7C);
    ClearVector(&pBall->mState.mUnknown88);
    pBlock->mUnknown660 = fn_80054138(&pBlock->mUnknown4);
}

void fn_8013A910(Object_80137ABC *pBall, int *pAngles)
{
    Vector_80039F5C low;
    int index;

    fn_801EBEF8(&pBall->mState.mUnknown18, pAngles[2], pAngles[1], pAngles[0]);
    pBall->mState.mPos.mZ = 0.0f;
    fn_80139400(pBall, &low, &index);
    pBall->mState.mPos.mZ = -low.mZ;
    ClearVector(&pBall->mState.mUnknown54);
    ClearVector(&pBall->mState.mUnknown70);
    fn_801EB488(&pBall->mState.mUnknown60);
    pBall->mState.mUnknown28 = pBall->mState.mPos;
    pBall->mState.mUnknown34 = pBall->mState.mUnknown18;
}

void fn_8013A9F0(Object_80137ABC *pBall)
{
    pBall->mState.mFlags &= ~8;
}

void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding)
{
    Point_8017886C pos;
    float vz = pBall->mState.mUnknown54.mZ;
    float t = (pBall->mState.mPos.mZ - height) * 0.005962963f + vz * vz;

    t *= 112495.65f;
    t = t < 0.0f ? 0.0f : t;
    t = vz * 335.40372f + fn_80260B1C(t);
    if (t > 0.0f) {
        fn_80227248(&pos, &pBall->mState.mUnknown70, 0.5f * t * t);
        fn_8022732C(&pos, &pBall->mState.mUnknown54, t);
        fn_80227638(&pos, &pos, &pBall->mState.mPos);
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

void fn_8013AB24(Object_80137ABC *pBall)
{
    fn_8013AA00(pBall, lbl_803EB1C0, &pBall->mState.mUnknown44, &pBall->mState.mUnknown48);
    pBall->mState.mUnknown48.mZ = lbl_803EB1C0;
}

float fn_8013AB64(Object_80137ABC *pBall, float t)
{
    Vector_80039F5C vel;
    Vector_80039F5C pos;
    float g = 0.0029814816f;

    fn_80137EC4(pBall, &vel);
    fn_80137D58(pBall, &pos);
    return (pos.mZ + t * vel.mZ) - t * g * t * 0.5f;
}

void fn_8013ABE0(Object_80137ABC *pBall)
{
    fn_800A33DC();
    fn_800A33D0();
    pBall->mState.mUnknownE8 = 1.2f;
    pBall->mState.mUnknownEC = 1.35f;
}

void fn_8013AC28(Object_80137ABC *pBall, Vector_80039F5C *pTarget, int mode, float speed, float spin, float rate)
{
    Vector_80039F5C delta;
    float time;

    pBall->mState.mUnknown48.mX = pTarget->mX;
    pBall->mState.mUnknown48.mY = pTarget->mY;
    pBall->mState.mUnknown48.mZ = pTarget->mZ;
    fn_802276B4(&delta, pTarget, &pBall->mState.mPos);
    time = fn_802270A4(&delta) / speed * lbl_803EA2C4;
    delta.mZ += 0.0029814816f * time * time * 0.5f;
    fn_80227264(&pBall->mState.mUnknown54, &delta, 1.0f / time);
    fn_8013A2F4(pBall, mode, spin, rate);
}

void fn_8013AD04(Object_80137ABC *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate)
{
    pBall->mState.mUnknown54.mX = pVelocity->mX;
    pBall->mState.mUnknown54.mY = pVelocity->mY;
    pBall->mState.mUnknown54.mZ = pVelocity->mZ;
    fn_8013AB24(pBall);
    fn_8013A2F4(pBall, mode, spin, rate);
}

int fn_8013AD78(Object_80137ABC *pBall)
{
    return pBall->mState.mUnknown94.mZ > 0.0f;
}

int fn_8013AD94(Object_80137ABC *pBall)
{
    return pBall->mState.mUnknownD0;
}

void fn_8013AD9C(Object_80137ABC *pBall, int mode)
{
    pBall->mState.mUnknownD0 = mode;
}

int fn_8013ADA4(Object_80039F5C *p)
{
    Record_801BE648 *pRecords = (Record_801BE648 *)p->mpUnknown792;
    unsigned char i;
    int result = 1;

    for (i = 0; i < 4; i++) {
        Record_801BE648 *pRecord = &pRecords[i];

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

int fn_8013AE1C(Object_80137ABC *pBall, Object_80039F5C *p, unsigned int type, int facing)
{
    Point_8017886C delta;
    unsigned short state = fn_8013BA58(pBall, 0);
    int result = 0;

    switch (type) {
    case 1:
    case 2:
    case 10:
        if (state == 3 || state == 4) {
            result = 1;
        } else {
            if (fn_80170E64(pBall, p, 0)) {
                result = 1;
            }
            if (!fn_8013ADA4(p)) {
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
            if (fn_80170E64(pBall, p, 1)) {
                result = 1;
            }
            if (!fn_8013ADA4(p)) {
                result = 0;
            }
        }
        break;
    default:
        if (facing && (type == 0 || type == 7 || type == 5 || type == 1 || type == 3)) {
            fn_80227690(&delta, &pBall->mState.mPos, &p->mMotion.mPos);
            if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing) <= 0x3FFFFF) {
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

void fn_8013AF88(Object_80137ABC *pBall)
{
    Block_80170E64 *pBlock = fn_8013825C(pBall);

    pBall->mState.mUnknownBC = 0;
    pBall->mState.mUnknownC4 = 1;
    fn_8013A9F0(pBall);
    pBlock->mUnknown20 |= 2;
    pBall->mState.mFlags &= ~0x20;
}

void fn_8013AFE8(Object_80137ABC *pBall)
{
    fn_80172F9C();
    pBall->mState.mFlags = (pBall->mState.mFlags | 8) & ~0x10;
}

void fn_8013B024(Object_80137ABC *pBall)
{
    fn_8013A9F0(pBall);
    fn_80067DB8(0x22, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
}

void fn_8013B068(Object_80137ABC *pBall)
{
    if (pBall == fn_801374BC() && pBall->mState.mStateArg != 0) {
        fn_800EBA48(fn_801374E0(pBall));
    }
}

void fn_8013B0B4(Object_80137ABC *pBall, float dt)
{
    Vector_80039F5C pos;
    int counting = 1;
    Object_80039F5C *pHolder = fn_80137AD0(pBall);

    fn_8013A64C(pBall, dt);
    pBall->mState.mUnknownC0 = fn_8023790C();
    if (fn_801BE648(pHolder->mpUnknown792) == 0xE1) {
        fn_8009BF5C(pHolder, 0, &pos, 0);
        counting = pos.mZ <= 2.25f;
    }
    if (counting) {
        pBall->mState.mUnknownBC += (unsigned int)dt;
    }
}

void fn_8013B198(Object_80137ABC *pBall, float dt)
{
    if (fn_802270D4(&pBall->mState.mUnknown54) != 0.0f) {
        pBall->mState.mUnknown54.mX = pBall->mState.mUnknown54.mY = pBall->mState.mUnknown54.mZ = 0.0f;
    }
}

void fn_8013B1E4(Object_80137ABC *pBall, float dt)
{
    fn_8013A64C(pBall, dt);
    fn_80067DB8(0x21, &pBall->mState.mPos, (int)pBall, 0, pBall->mState.mIndex);
    fn_80172FB0(pBall);
}

void fn_8013B230(Object_80137ABC *pBall)
{
    fn_801736AC();
}

void fn_8013B250(Object_80137ABC *pBall)
{
    Block_80170E64 *pBlock = fn_8013825C(pBall);

    pBlock->mUnknown20 &= ~2;
    pBall->mState.mUnknownC0 = fn_8023790C();
    pBall->mState.mUnknownBC = 0;
    pBall->mState.mUnknownCC = pBall->mState.mUnknownB4;
}

void fn_8013B2A0(Object_80137ABC *pBall, float dt)
{
    if (fn_800AD9B4() == 3 && (fn_801374BC() == pBall || fn_801486A0() == 1)) {
        if (!fn_801783AC(1)) {
            fn_8013B9C0(pBall, 5, 0);
            fn_80170F40();
        } else {
            fn_80171E30();
        }
    }
    fn_8013A494(pBall, dt);
}

void fn_8013B330(Object_80137ABC *pBall, float dt)
{
    fn_8013A494(pBall, dt);
}

void fn_8013B350(Object_80137ABC *pBall, float dt)
{
    fn_80137BC0(pBall, 0);
    if (fn_801374BC() == pBall && !fn_801787A0()) {
        if (fn_801783AC(1) || !fn_801486A0()) {
            fn_80171E30();
        } else {
            fn_80170F40();
        }
    } else {
        fn_8013B9C0(pBall, 5, 0);
    }
    fn_8013A494(pBall, dt);
}

int fn_8013B3EC(Object_80137ABC *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    int mode;
    Record_800B15FC *pRecord;
    int port;

    if (pBall == fn_801374BC() && fn_80137B88(pBall) == p) {
        switch (type) {
        case 0:
        case 5:
        case 7:
            mode = fn_800AD9B4();
            fn_80137BC0(pBall, 0);
            fn_80137A04(pBall, p);
            fn_800D782C(p);
            fn_80138398(pBall, 0);
            if (mode == 3) {
                pRecord = fn_800B15FC();
                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = p->mMotion.mPos.mX;
                pRecord->mUnknown10 = p->mMotion.mPos.mY;
                pRecord->mUnknown14 = 8;
                fn_800B1508();
                fn_80067E3C(0x1E, &p->mMotion.mPos, p->mId, 1, 1, 0);
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

int fn_8013B52C(Object_80137ABC *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    int arg;
    int result = 0;
    int mode = fn_800AD9B4();

    fn_8013BA58(pBall, &arg);
    if (mode == 3 && arg == 1) {
        if (fn_8013AE1C(pBall, p, type, 0) &&
            (fn_80137F90(pBall) + 60 < fn_8023790C() || fn_801BE648(p->mpUnknown792) == 0x30)) {
            result = 1;
            fn_801720B4(p);
        } else {
            pBall->mState.mFlags |= 0x40;
        }
    }
    return result;
}

int fn_8013B5EC(Object_80137ABC *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    Vector_80039F5C vel;
    int result = 0;

    if (fn_8013AE1C(pBall, p, type, 0)) {
        fn_80137EC4(pBall, &vel);
        if (p->mIdBytes[2] == fn_80178308() && pBall->mState.mUnknownC0 + 5 >= fn_8023790C()) {
            result = 1;
        } else {
            result = fn_80171068(pBall, p, type);
        }
    }
    if (!result) {
        fn_801783D0(0xB, 1);
        fn_8013AD9C(pBall, 3);
    }
    return result;
}

int fn_8013B6A0(Object_80137ABC *pBall, void *pData, unsigned int type)
{
    Object_80039F5C *p = (Object_80039F5C *)pData;
    int result;

    if (fn_8009BCE8(&pBall->mState.mUnknownB8) == p && pBall->mState.mUnknownC0 + 5 >= fn_8023790C()) {
        result = 1;
    } else if (fn_8013AE1C(pBall, p, type, 1)) {
        result = fn_801712D0(pBall, p, type);
    } else {
        result = 0;
    }
    return result;
}

void fn_8013B730(Object_80137ABC *pBall, float dt)
{
}

void fn_8013B734(Object_80137ABC *pBall, float dt)
{
    Vector_80039F5C pos;
    int angles[3];
    Quat_801EB488 turn;
    Object_800400C4 *pPlace = fn_800400C4(fn_8013825C(fn_801374BC()));
    Object_80040818 *pObject = fn_80040F18(pPlace->mUnknown4);
    short *pRot = pObject->mpUnknown220;

    angles[0] = pRot[0] << 8;
    angles[1] = pRot[1] << 8;
    angles[2] = pRot[2] << 8;
    fn_801D0508();
    pos.mX = pPlace->mUnknown8;
    pos.mY = pPlace->mUnknownC;
    pos.mZ = 0.0f;
    fn_801D0C58(&pos);
    fn_801D0ADC((pPlace->mUnknown20 + 0x400000) & 0xFFFFFF);
    fn_801D08FC(0x400000);
    fn_801D0C58(pObject->mUnknown180);
    fn_801D09EC(pObject->mUnknown204);
    fn_801D0ADC(angles[2]);
    fn_801D08FC((angles[0] + 0x400000) & 0xFFFFFF);
    fn_801D0FB8(&pBall->mState.mPos.mX);
    fn_801EBA64(&pBall->mState.mUnknown18);
    fn_801D0544();
    if (fn_801784C4()) {
        pBall->mState.mPos.mX = -pBall->mState.mPos.mX;
        pBall->mState.mPos.mY = -pBall->mState.mPos.mY;
        fn_801EBEF8(&turn, 0x800000, 0, 0);
        fn_801EB660(&pBall->mState.mUnknown18, &turn, &pBall->mState.mUnknown18);
    }
}

int fn_8013B86C(Object_80137ABC *pBall, void *pData, unsigned int type)
{
    return 1;
}

}
