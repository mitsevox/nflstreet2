#include <math.h>

#include "game/cu_80136B1C.h"
#include "game/cu_80067C10.h"
#include "game/fn_801EBC18.h"
#include "game/fn_802270D4.h"

extern "C" {
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
void fn_80139294(Object_80137ABC *pBall, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80139308(Vector_80039F5C *pPos, Quat_801EB488 *pRot, int index, Vector_80039F5C *pOut);
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

void fn_80139954(Object_80137ABC *pBall)
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

}
