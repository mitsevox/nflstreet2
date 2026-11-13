/* Collision bounce math used by the ball and the players: bounces one axis or
   one body off a surface, two axes or two bodies off each other (2D and 3D),
   tests whether two movers approach each other, and builds a random scatter
   vector around a surface normal. */
#include "game/CollideBounce.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

extern float gPlyrMoveFwdSpeed;

extern "C" {
int fn_801CFE40(float y, float x);
void MatRotVecToVec(Vector_80039F5C *pFrom, Vector_80039F5C *pTo);
void fn_801D0470(int mode);
void fn_801D0494(void);
void fn_801D0E94(void);
void fn_802271F0(void *pOut, void *pIn);
void fn_80227248(void *pOut, void *pIn, float scale);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_802272DC(void *pOut, void *pIn, float length);
void fn_80227384(void *pOut, void *pIn, int angle);
void fn_8022765C(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227704(void *pA, void *pB);
void fn_802277DC(void *pOut, void *pA, void *pB);
void fn_80227C2C(void *pOut, void *pIn);
float fn_80237260(int stream);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_800B2C48(Object_800B26B0 *pA, Object_800B26B0 *pB, int angle, unsigned char *pHitA, unsigned char *pHitB);
}

extern "C" {

void BounceAxisFixed(BounceAxis_t *pAxis, float restitution)
{
    float delta;

    pAxis->mUnknown4 = -pAxis->mUnknown0 * restitution;
    delta = (pAxis->mUnknown4 - pAxis->mUnknown0) * 335.40372f;
    pAxis->mUnknown8 = pAxis->mUnknownC * delta;
}

void BounceAxisPair(BounceAxis_t *pA, BounceAxis_t *pB, float restitution)
{
    float ratio = pA->mUnknownC / pB->mUnknownC;
    float a = pA->mUnknown0;
    float b = pB->mUnknown0;
    float outA;
    float outB;
    float deltaA;
    float deltaB;

    outA = (a * (ratio - restitution) + b * (restitution + 1.0f)) / (ratio + 1.0f);
    pA->mUnknown4 = outA;
    outB = restitution * (a - b) + outA;
    pB->mUnknown4 = outB;
    deltaA = (outA - a) * 335.40372f;
    pA->mUnknown8 = pA->mUnknownC * deltaA;
    deltaB = (outB - b) * 335.40372f;
    pB->mUnknown8 = pB->mUnknownC * deltaB;
}

int BounceCheckApproach(BounceSegment_t *pA, BounceSegment_t *pB, unsigned char *pHitA, unsigned char *pHitB)
{
    Vector_80039F5C offset;
    Vector_80039F5C move;
    Vector_80039F5C otherMove;

    fn_802276B4(&offset, &pA->mUnknown12, &pB->mUnknown12);
    fn_802276B4(&move, &pA->mUnknown0, &pA->mUnknown12);
    *pHitA = 0;
    if (move.mX != 0.0f || move.mY != 0.0f) {
        if (fn_80227704(&move, &offset) < 0.0f) {
            *pHitA = 1;
        }
    }
    fn_80227264(&offset, &offset, -1.0f);
    fn_802276B4(&otherMove, &pB->mUnknown0, &pB->mUnknown12);
    *pHitB = 0;
    if (otherMove.mX != 0.0f || otherMove.mY != 0.0f) {
        if (fn_80227704(&otherMove, &offset) < 0.0f) {
            *pHitB = 1;
        }
    }
    return *pHitA || *pHitB;
}

static inline int Heading(float *v)
{
    return fn_801CFE40(v[1], v[0]);
}

void BounceBody2D(BounceBody_t *pBody, float *pNormal, float restitution)
{
    BounceAxis_t axis;
    float up[2];
    int angle;

    up[0] = 0.0f;
    up[1] = 1.0f;
    angle = Heading(pNormal);
    angle = (Heading(up) - angle) & 0xFFFFFF;
    fn_80227384(&pBody->mUnknown0, &pBody->mUnknown0, angle);
    pBody->mUnknown12.mX = pBody->mUnknown0.mX;
    pBody->mUnknown24.mX = 0.0f;
    axis.mUnknownC = pBody->mUnknown36;
    axis.mUnknown0 = pBody->mUnknown0.mY;
    BounceAxisFixed(&axis, restitution);
    pBody->mUnknown12.mY = axis.mUnknown4;
    pBody->mUnknown24.mY = axis.mUnknown8;
    angle = -angle & 0xFFFFFF;
    fn_80227384(&pBody->mUnknown12, &pBody->mUnknown12, angle);
    fn_80227384(&pBody->mUnknown24, &pBody->mUnknown24, angle);
}

void BounceBody3D(BounceBody_t *pBody, Vector_80039F5C *pNormal, float restitution)
{
    Vector_80039F5C up;
    BounceAxis_t axis;

    axis.mUnknown8 = 0.0f;
    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_801D0470(3);
    fn_801D0494();
    MatRotVecToVec(pNormal, &up);
    fn_80227C2C(&pBody->mUnknown0, &pBody->mUnknown0);
    pBody->mUnknown12.mX = pBody->mUnknown0.mX * 0.5f;
    pBody->mUnknown12.mY = pBody->mUnknown0.mY * 0.5f;
    pBody->mUnknown24.mX = 0.0f;
    pBody->mUnknown24.mY = 0.0f;
    axis.mUnknown0 = pBody->mUnknown0.mZ;
    axis.mUnknownC = pBody->mUnknown36;
    if (axis.mUnknown0 > 0.0f) {
        axis.mUnknown4 = axis.mUnknown0;
    } else {
        BounceAxisFixed(&axis, restitution);
    }
    pBody->mUnknown12.mZ = axis.mUnknown4;
    pBody->mUnknown24.mZ = axis.mUnknown8;
    fn_801D0E94();
    fn_80227C2C(&pBody->mUnknown12, &pBody->mUnknown12);
    fn_80227C2C(&pBody->mUnknown24, &pBody->mUnknown24);
}

void BounceBodyPair2D(BounceBody_t *pA, BounceBody_t *pB, float *pNormal, float restitution)
{
    BounceAxis_t axisA;
    BounceAxis_t axisB;
    float up[2];
    int angle;

    up[0] = 0.0f;
    up[1] = 1.0f;
    angle = Heading(pNormal);
    angle = (Heading(up) - angle) & 0xFFFFFF;
    fn_80227384(&pA->mUnknown0, &pA->mUnknown0, angle);
    fn_80227384(&pB->mUnknown0, &pB->mUnknown0, angle);
    pA->mUnknown12.mX = pA->mUnknown0.mX;
    pA->mUnknown24.mX = 0.0f;
    pB->mUnknown12.mX = pB->mUnknown0.mX;
    pB->mUnknown24.mX = 0.0f;
    axisA.mUnknownC = pA->mUnknown36;
    axisA.mUnknown0 = pA->mUnknown0.mY;
    axisB.mUnknownC = pB->mUnknown36;
    axisB.mUnknown0 = pB->mUnknown0.mY;
    BounceAxisPair(&axisA, &axisB, restitution);
    pA->mUnknown12.mY = axisA.mUnknown4;
    pA->mUnknown24.mY = axisA.mUnknown8;
    pB->mUnknown12.mY = axisB.mUnknown4;
    pB->mUnknown24.mY = axisB.mUnknown8;
    angle = -angle & 0xFFFFFF;
    fn_80227384(&pA->mUnknown12, &pA->mUnknown12, angle);
    fn_80227384(&pA->mUnknown24, &pA->mUnknown24, angle);
    fn_80227384(&pB->mUnknown12, &pB->mUnknown12, angle);
    fn_80227384(&pB->mUnknown24, &pB->mUnknown24, angle);
}

void BounceBodyPair3D(BounceBody_t *pA, BounceBody_t *pB, Vector_80039F5C *pNormal, float restitution)
{
    Vector_80039F5C up;
    BounceAxis_t axisA;
    BounceAxis_t axisB;

    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_802271F0(pNormal, pNormal);
    fn_801D0470(3);
    fn_801D0494();
    MatRotVecToVec(pNormal, &up);
    fn_80227C2C(&pA->mUnknown0, &pA->mUnknown0);
    fn_80227C2C(&pB->mUnknown0, &pB->mUnknown0);
    pA->mUnknown12.mX = pA->mUnknown0.mX;
    pA->mUnknown24.mX = 0.0f;
    pB->mUnknown12.mX = pB->mUnknown0.mX;
    pB->mUnknown24.mX = 0.0f;
    pA->mUnknown12.mY = pA->mUnknown0.mY;
    pA->mUnknown24.mY = 0.0f;
    pB->mUnknown12.mY = pB->mUnknown0.mY;
    pB->mUnknown24.mY = 0.0f;
    axisA.mUnknownC = pA->mUnknown36;
    axisA.mUnknown0 = pA->mUnknown0.mZ;
    axisB.mUnknownC = pB->mUnknown36;
    axisB.mUnknown0 = pB->mUnknown0.mZ;
    BounceAxisPair(&axisA, &axisB, restitution);
    pA->mUnknown12.mZ = axisA.mUnknown4;
    pA->mUnknown24.mZ = axisA.mUnknown8;
    pB->mUnknown12.mZ = axisB.mUnknown4;
    pB->mUnknown24.mZ = axisB.mUnknown8;
    fn_801D0E94();
    fn_80227C2C(&pA->mUnknown12, &pA->mUnknown12);
    fn_80227C2C(&pA->mUnknown24, &pA->mUnknown24);
    fn_80227C2C(&pB->mUnknown12, &pB->mUnknown12);
    fn_80227C2C(&pB->mUnknown24, &pB->mUnknown24);
}

void BounceScatterVector(Vector_80039F5C *pOut, Vector_80039F5C *pNormal, float scale)
{
    Vector_80039F5C up;
    Vector_80039F5C v;

    up.mX = 0.0f;
    up.mY = 0.0f;
    up.mZ = 1.0f;
    fn_801D0470(3);
    fn_801D0494();
    MatRotVecToVec(pNormal, &up);
    v.mX = fn_80237260(0) - 0.5f;
    v.mY = fn_80237260(0) - 0.5f;
    v.mZ = fn_80237260(0) * 0.5f;
    fn_802272DC(&v, &v, scale);
    fn_801D0E94();
    fn_80227C2C(pOut, &v);
}

}
