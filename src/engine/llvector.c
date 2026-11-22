/* Low-level vector math: 2D/3D vector length, normalise, scale, rotate, compare, add, subtract, dot and
   cross products, distance, interpolation and matrix transforms on float arrays. */

#include <math.h>

extern float MathInvSqrt(float x);
extern void fn_801CFC14(int angle, float *pFirst, float *pSecond);
extern void fn_801CFCD0(int *pAngles, float *pFirst, float *pSecond);
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

    fn_801CFC14(angle, &s, &c);
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
    fn_801CFCD0(angles, first, second);
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
    fn_801CFCD0(angles, first, second);
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

    fn_801CFC14(angle, &first, &second);
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

#if defined(DECOMP_COMPARE)

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

#endif
