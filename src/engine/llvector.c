/* 2D and 3D vector operations for gameplay, collision and rendering. Computes lengths and distances,
   projects points onto segments, and scales, rotates, interpolates and transforms vectors. */

#include <math.h>

extern float MathInvSqrt(float x);
extern void MathSinCos(int angle, float *pFirst, float *pSecond);
extern void MathSinCosVec4(int *pAngles, float *pFirst, float *pSecond);
extern void MatStore(float m[4][4]);
extern double fabs(double x);

float Vec2Magnitude(float *p)
{
    return sqrtf(p[0] * p[0] + p[1] * p[1]);
}

float Vec3Magnitude(float *p)
{
    return sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

float Vec2MagnitudeSqr(float *p)
{
    return p[0] * p[0] + p[1] * p[1];
}

float Vec3MagnitudeSqr(float *p)
{
    return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}

float Vec2InvMagnitude(float *p)
{
    return MathInvSqrt(p[0] * p[0] + p[1] * p[1]);
}

float Vec3InvMagnitude(float *p)
{
    return MathInvSqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

void Vec2Normalize(float *pOut, float *p)
{
    float scale = Vec2InvMagnitude(p);

    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
}

void Vec3Normalize(float *pOut, float *p)
{
    float scale = Vec3InvMagnitude(p);

    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
    pOut[2] = p[2] * scale;
}

void Vec2Scale(float *pOut, float *p, float scale)
{
    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
}

void Vec3Scale(float *pOut, float *p, float scale)
{
    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
    pOut[2] = p[2] * scale;
}

void Vec2ScaleLength(float *pOut, float *p, float length)
{
    Vec2Scale(pOut, p, length / Vec2Magnitude(p));
}

void Vec3ScaleLength(float *pOut, float *p, float length)
{
    Vec3Scale(pOut, p, length / Vec3Magnitude(p));
}

void Vec2ScaleAcc(float *pOut, float *p, float scale)
{
    pOut[0] += p[0] * scale;
    pOut[1] += p[1] * scale;
}

void Vec3ScaleAcc(float *pOut, float *p, float scale)
{
    pOut[0] += p[0] * scale;
    pOut[1] += p[1] * scale;
    pOut[2] += p[2] * scale;
}

void Vec2Rotate(float *pOut, float *p, int angle)
{
    float s;
    float c;

    float x;
    float y;

    MathSinCos(angle, &s, &c);
    x = p[0];
    y = p[1];
    pOut[0] = c * x - s * y;
    pOut[1] = c * y + s * x;
}

void Vec3RotateXYZ(float *pOut, float *p, int a, int b, int c)
{
    float first[3];
    float second[3];
    int angles[3];
    float x0;
    float y0;
    float x1;
    float z1;

    angles[0] = a;
    angles[1] = b;
    angles[2] = c;
    MathSinCosVec4(angles, first, second);
    x0 = second[2] * p[0] - first[2] * p[1];
    y0 = first[2] * p[0] + second[2] * p[1];
    x1 = second[1] * x0 + first[1] * p[2];
    z1 = second[1] * p[2] - first[1] * x0;
    pOut[0] = x1;
    pOut[1] = second[0] * y0 - first[0] * z1;
    pOut[2] = first[0] * y0 + second[0] * z1;
}

void Vec3RotateZYX(float *pOut, float *p, int a, int b, int c)
{
    float first[3];
    float second[3];
    int angles[3];
    float y0;
    float z0;
    float x1;
    float z1;

    angles[0] = c;
    angles[1] = b;
    angles[2] = a;
    MathSinCosVec4(angles, first, second);
    y0 = second[0] * p[1] - first[0] * p[2];
    z0 = first[0] * p[1] + second[0] * p[2];
    x1 = second[1] * p[0] + first[1] * z0;
    z1 = second[1] * z0 - first[1] * p[0];
    pOut[0] = second[2] * x1 - first[2] * y0;
    pOut[1] = first[2] * x1 + second[2] * y0;
    pOut[2] = z1;
}

void Vec2FromAngle(float *pOut, int angle, float length)
{
    float first;
    float second;

    MathSinCos(angle, &first, &second);
    pOut[0] = second * length;
    pOut[1] = first * length;
}

int Vec2Equal(float *pA, float *pB, float eps)
{
    float dx = fabs(pA[0] - pB[0]);
    float dy = fabs(pA[1] - pB[1]);

    return dx < eps && dy < eps;
}

int Vec3Equal(float *pA, float *pB, float eps)
{
    float dx = fabs(pA[0] - pB[0]);
    float dy = fabs(pA[1] - pB[1]);
    float dz = fabs(pA[2] - pB[2]);

    return dx < eps && dy < eps && dz < eps;
}

void Vec2Add(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] + pB[0];
    pOut[1] = pA[1] + pB[1];
}

void Vec3Add(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] + pB[0];
    pOut[1] = pA[1] + pB[1];
    pOut[2] = pA[2] + pB[2];
}

void Vec2Sub(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] - pB[0];
    pOut[1] = pA[1] - pB[1];
}

void Vec3Sub(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] - pB[0];
    pOut[1] = pA[1] - pB[1];
    pOut[2] = pA[2] - pB[2];
}

float Vec2DotProduct(float *pA, float *pB)
{
    return pA[0] * pB[0] + pA[1] * pB[1];
}

float Vec3DotProduct(float *pA, float *pB)
{
    return pA[0] * pB[0] + pA[1] * pB[1] + pA[2] * pB[2];
}

float Vec3CosAngle(float *pA, float *pB)
{
    float len;
    float inv;

    len = sqrtf(pA[0] * pA[0] + pA[1] * pA[1] + pA[2] * pA[2]);
    len *= sqrtf(pB[0] * pB[0] + pB[1] * pB[1] + pB[2] * pB[2]);
    inv = 1.0f / len;
    return pA[0] * pB[0] * inv + pA[1] * pB[1] * inv + pA[2] * pB[2] * inv;
}

void Vec3CrossProduct(float *pOut, float *pA, float *pB)
{
    float x = pA[1] * pB[2] - pA[2] * pB[1];
    float y = pA[2] * pB[0] - pA[0] * pB[2];
    float z = pA[0] * pB[1] - pA[1] * pB[0];

    pOut[0] = x;
    pOut[1] = y;
    pOut[2] = z;
}

float Vec2Distance(float *pA, float *pB)
{
    float d[2];

    Vec2Sub(d, pA, pB);
    return Vec2Magnitude(d);
}

float Vec3Distance(float *pA, float *pB)
{
    float d[3];

    Vec3Sub(d, pA, pB);
    return Vec3Magnitude(d);
}

float Vec2DistanceSqr(float *pA, float *pB)
{
    float d[2];

    Vec2Sub(d, pA, pB);
    return Vec2MagnitudeSqr(d);
}

float Vec3DistanceSqr(float *pA, float *pB)
{
    float d[3];

    Vec3Sub(d, pA, pB);
    return Vec3MagnitudeSqr(d);
}

void Vec2Lerp(float *pOut, float *pA, float *pB, float t)
{
    float x = pB[0];
    float y = pB[1];

    pOut[0] = (pA[0] - x) * t + x;
    pOut[1] = (pA[1] - y) * t + y;
}

void Vec3Lerp(float *pOut, float *pA, float *pB, float t)
{
    float x = pB[0];
    float y = pB[1];
    float z = pB[2];

    pOut[0] = (pA[0] - x) * t + x;
    pOut[1] = (pA[1] - y) * t + y;
    pOut[2] = (pA[2] - z) * t + z;
}

/* FAKEMATCH: retain the unused angle and blend literals between cosine and segment projection. */
static const float _Vec_afAngleAndBlendLiterals[] = {
    1.0f, 3.1415927f, 6.2831855f, -3.1415927f, 0.0f, 0.5f, 0.0f
};

void Vec3ClosestPointOnSegment(float *pA, float *pB, float *pP, float *pOut, float *pDistSq, float *pT)
{
    float dx;
    float dy;
    float dz;
    float ex;
    float ey;
    float ez;

    if (pA[0] == pB[0] && pA[1] == pB[1] && pA[2] == pB[2]) {
        *pT = 0.0f;
        pOut[0] = pA[0];
        pOut[1] = pA[1];
        pOut[2] = pA[2];
    } else {
        ex = pA[0] - pB[0];
        ey = pA[1] - pB[1];
        ez = pA[2] - pB[2];
        *pT = ((pA[0] - pP[0]) * ex + (pA[1] - pP[1]) * ey + (pA[2] - pP[2]) * ez) / (ex * ex + ey * ey + ez * ez);
        if (*pT < 0.0f) {
            *pT = 0.0f;
            pOut[0] = pA[0];
            pOut[1] = pA[1];
            pOut[2] = pA[2];
        } else if (*pT > 1.0f) {
            *pT = 1.0f;
            pOut[0] = pB[0];
            pOut[1] = pB[1];
            pOut[2] = pB[2];
        } else {
            pOut[0] = pA[0] + *pT * (pB[0] - pA[0]);
            pOut[1] = pA[1] + *pT * (pB[1] - pA[1]);
            pOut[2] = pA[2] + *pT * (pB[2] - pA[2]);
        }
    }
    dx = pOut[0] - pP[0];
    dy = pOut[1] - pP[1];
    dz = pOut[2] - pP[2];
    *pDistSq = dx * dx + dy * dy + dz * dz;
}

float Vec3DistanceSqrToSegment(float *pA, float *pB, float *pP)
{
    float aPoint[3];
    float ex;
    float ey;
    float ez;
    float t;
    float dx;
    float dy;
    float dz;

    if (pA[0] == pB[0] && pA[1] == pB[1] && pA[2] == pB[2]) {
        aPoint[0] = pA[0];
        aPoint[1] = pA[1];
        aPoint[2] = pA[2];
    } else {
        float lengthSquared;

        ex = pA[0] - pB[0];
        ey = pA[1] - pB[1];
        ez = pA[2] - pB[2];
        lengthSquared = ex * ex + ey * ey + ez * ez;
        t = ((pA[0] - pP[0]) * ex + (pA[1] - pP[1]) * ey + (pA[2] - pP[2]) * ez) / lengthSquared;
        if (t > 1.0f) {
            t = 1.0f;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        aPoint[0] = pA[0] + t * (pB[0] - pA[0]);
        aPoint[1] = pA[1] + t * (pB[1] - pA[1]);
        aPoint[2] = pA[2] + t * (pB[2] - pA[2]);
    }
    dx = aPoint[0] - pP[0];
    dy = aPoint[1] - pP[1];
    dz = aPoint[2] - pP[2];
    return dx * dx + dy * dy + dz * dz;
}

/* FAKEMATCH: retain the unused blend literals between segment distance and matrix transforms. */
static const float _Vec_afBlendLiterals[] = {
    1.0f, 0.0f, 0.5f, 0.0f, 1.0f
};

void Vec3Mat33Mul(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;

    MatStore(m);
    x = p[0];
    y = p[1];
    z = p[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z;
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z;
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z;
}

void Vec3Mat34Mul(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;

    MatStore(m);
    x = p[0];
    y = p[1];
    z = p[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
}

void Vec3Mat44Mul(float *pOut, float *pV)
{
    float m[4][4];
    float x;
    float y;
    float z;

    MatStore(m);
    x = pV[0];
    y = pV[1];
    z = pV[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    pOut[3] = m[3][0] * x + m[3][1] * y + m[3][2] * z + 1.0f;
}

void Vec4Mat44Mul(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;
    float w;

    MatStore(m);
    x = p[0];
    y = p[1];
    z = p[2];
    w = p[3];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3] * w;
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3] * w;
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3] * w;
    pOut[3] = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3] * w;
}
