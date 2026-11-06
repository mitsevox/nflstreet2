/* Quaternion maths for the engine: identity, length, normalise, multiply, inverse, conversion to and
   from rotation matrices and Euler angles, rotating vectors, and spherical interpolation, used by
   animation blending and camera and player orientation. */

#include "engine/Record_800D81C8.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/llquat.h"

typedef struct Quat_t {
    float x;
    float y;
    float z;
    float w;
} Quat_t;

typedef struct QuatMatrix_t {
    float mElements[16];
} QuatMatrix_t;

static const unsigned char Quat_NextTraceIndex[3] = { 1, 2, 0 };

double fabs(double x);
float fn_80260B1C(float x);
void fn_801CFC14(int angle, float *pSin, float *pCos);
void fn_801CFCD0(int *pAngles, float *pSin, float *pCos);
float fn_801CFB74(float x);
float fn_801CFDB0(float x);
int fn_801CFE40(float y, float x);
float fn_801CFF54(float x);
float fn_801CFFA0(float x);
float QuatInvLength(Quat_t *q);
void QuatScale(Quat_t *pOut, Quat_t *q, float scale);

void QuatIdentity(Quat_t *q)
{
    q->x = q->y = q->z = 0.0f;
    q->w = 1.0f;
}

float QuatLength(Quat_t *q)
{
    return fn_80260B1C(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

float QuatInvLength(Quat_t *q)
{
    return fn_801CFF54(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

void QuatNormalize(Quat_t *pOut, Quat_t *q)
{
    QuatScale(pOut, q, QuatInvLength(q));
}

void QuatScale(Quat_t *pOut, Quat_t *q, float scale)
{
    pOut->x = q->x * scale;
    pOut->y = q->y * scale;
    pOut->z = q->z * scale;
    pOut->w = q->w * scale;
}

int QuatIsEqual(Quat_t *pA, Quat_t *pB, float epsilon)
{
    float dx = fabs(pA->x - pB->x);
    float dy = fabs(pA->y - pB->y);
    float dz = fabs(pA->z - pB->z);
    float dw = fabs(pA->w - pB->w);
    int equal = 0;

    if (!(dx >= epsilon) && !(dy >= epsilon) && !(dz >= epsilon)) {
        equal = dw < epsilon;
    }
    return equal;
}

void QuatSubtract(Quat_t *pOut, Quat_t *pA, Quat_t *pB)
{
    pOut->x = pA->x - pB->x;
    pOut->y = pA->y - pB->y;
    pOut->z = pA->z - pB->z;
    pOut->w = pA->w - pB->w;
}

void QuatMultiply(Quat_t *pOut, Quat_t *pA, Quat_t *pB)
{
    Quat_t q;

    q.x = pA->w * pB->x + pA->x * pB->w + pA->y * pB->z - pA->z * pB->y;
    q.y = pA->w * pB->y + pA->y * pB->w + pA->z * pB->x - pA->x * pB->z;
    q.z = pA->w * pB->z + pA->z * pB->w + pA->x * pB->y - pA->y * pB->x;
    q.w = pA->w * pB->w - pA->x * pB->x - pA->y * pB->y - pA->z * pB->z;
    pOut->x = q.x;
    pOut->y = q.y;
    pOut->z = q.z;
    pOut->w = q.w;
}

void QuatInverse(Quat_t *pOut, Quat_t *q)
{
    QuatScale(pOut, q, 1.0f / (q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z));
    pOut->x = -q->x;
    pOut->y = -q->y;
    pOut->z = -q->z;
}

float QuatDot(Quat_t *pA, Quat_t *pB)
{
    return pA->x * pB->x + pA->y * pB->y + pA->z * pB->z + pA->w * pB->w;
}

float QuatNormalizedDot(Quat_t *pA, Quat_t *pB)
{
    return QuatDot(pA, pB) * (QuatInvLength(pA) * QuatInvLength(pB));
}

void QuatToMatrix(float m[4][4], Quat_t *q)
{
    float x2 = q->x + q->x;
    float y2 = q->y + q->y;
    float z2 = q->z + q->z;
    float xx = x2 * q->x;
    float xy = x2 * q->y;
    float xz = x2 * q->z;
    float yy = y2 * q->y;
    float yz = y2 * q->z;
    float zz = z2 * q->z;
    float wx = x2 * q->w;
    float wy = y2 * q->w;
    float wz = z2 * q->w;

    m[0][0] = 1.0f - (yy + zz);
    m[1][0] = xy + wz;
    m[2][0] = xz - wy;
    m[0][1] = xy - wz;
    m[1][1] = 1.0f - (xx + zz);
    m[2][1] = yz + wx;
    m[0][2] = xz + wy;
    m[1][2] = yz - wx;
    m[2][2] = 1.0f - (xx + yy);
}

/* Recover a quaternion from the rotation entries; the small-trace branch
   retains the added third diagonal term. */
void QuatFromMatrix(float *q, QuatMatrix_t *m)
{
    float trace;
    float s;
    int i;
    int j;
    int k;

    trace = m->mElements[0] + m->mElements[5] + m->mElements[10] + 1.0f;
    if (!(trace <= 1e-07f)) {
        s = fn_80260B1C(trace);
        q[3] = s * 0.5f;
        s = 0.5f / s;
        q[0] = (m->mElements[9] - m->mElements[6]) * s;
        q[1] = (m->mElements[2] - m->mElements[8]) * s;
        q[2] = (m->mElements[4] - m->mElements[1]) * s;
    } else {
        i = m->mElements[5] > m->mElements[0];
        if (!(m->mElements[10] <= m->mElements[i * 4 + i])) {
            i = 2;
        }
        j = Quat_NextTraceIndex[i];
        k = Quat_NextTraceIndex[j];
        s = fn_80260B1C(m->mElements[i * 4 + i] - m->mElements[j * 4 + j] + m->mElements[k * 4 + k] + 1.0f);
        q[i] = s * 0.5f;
        s = 0.5f / s;
        q[3] = (m->mElements[k * 4 + j] - m->mElements[j * 4 + k]) * s;
        q[j] = (m->mElements[j * 4 + i] + m->mElements[i * 4 + j]) * s;
        q[k] = (m->mElements[k * 4 + i] + m->mElements[i * 4 + k]) * s;
    }
}

void QuatFromMat(float *q)
{
    QuatMatrix_t m;

    fn_801D0F80(m.mElements);
    QuatFromMatrix(q, &m);
}

void QuatTranslate(Vec3_801DE1E0 *pOut, Vec3_801DE1E0 *v, Quat_t *q)
{
    float x2 = q->x + q->x;
    float y2 = q->y + q->y;
    float z2 = q->z + q->z;
    float xx = x2 * q->x;
    float xy = x2 * q->y;
    float xz = x2 * q->z;
    float yz = y2 * q->z;
    float zz = z2 * q->z;
    float yy = y2 * q->y;
    float wx = x2 * q->w;
    float wy = y2 * q->w;
    float wz = z2 * q->w;

    float rx = v->x * (1.0f - yy - zz) + v->y * (xy - wz) + v->z * (xz + wy);
    float ry = v->x * (xy + wz) + v->y * (1.0f - xx - zz) + v->z * (yz - wx);
    float rz = v->x * (xz - wy) + v->y * (yz + wx) + v->z * (1.0f - xx - yy);

    pOut->x += rx;
    pOut->y += ry;
    pOut->z += rz;
}

void QuatFromAxisAngle(Quat_t *q, Vec3_801DE1E0 *pAxis, int angle)
{
    float s;
    float c;

    fn_801CFC14(angle / 2, &s, &c);
    q->x = pAxis->x * s;
    q->y = pAxis->y * s;
    q->z = pAxis->z * s;
    q->w = c;
}

void QuatToEuler(QuatEulerAngles_t *pOut, float *pRot)
{
    float x = pRot[0];
    float y = pRot[1];
    float z = pRot[2];
    float w = pRot[3];
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float sinY = (x * z - w * y) * -2.0f;
    float cosY = fn_80260B1C(1.0f - sinY * sinY);
    float sinX;
    float cosX;
    float sinZ;
    float cosZ;
    float r;

    if (!((float)fabs(cosY) <= 1e-07f)) {
        r = fn_801CFFA0(cosY);
        r = r + r;
        sinX = (y * z + w * x) * r;
        cosX = (0.5f - xx - yy) * r;
        sinZ = (x * y + w * z) * r;
        cosZ = (0.5f - yy - zz) * r;
    } else {
        sinX = (y * z - w * x) * -2.0f;
        cosX = 1.0f - (xx - zz) * 2.0f;
        sinZ = 0.0f;
        cosZ = 1.0f;
    }
    pOut->mUnknown0 = fn_801CFE40(sinX, cosX);
    pOut->mUnknown4 = fn_801CFE40(sinY, cosY);
    pOut->mUnknown8 = fn_801CFE40(sinZ, cosZ);
}

void QuatToEulerYZX(Triple_801BCA74 *pOut, Quat_t *q)
{
    float x = q->x;
    float y = q->y;
    float z = q->z;
    float w = q->w;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float sinZ = (x * y + w * z) * 2.0f;
    float cosZ = fn_80260B1C(1.0f - sinZ * sinZ);
    float sinX;
    float cosX;
    float sinY;
    float cosY;
    float r;

    if (!((float)fabs(cosZ) <= 1e-07f)) {
        r = fn_801CFFA0(cosZ);
        r = r + r;
        sinX = (w * x - y * z) * r;
        cosX = (0.5f - xx - zz) * r;
        sinY = (w * y - x * z) * r;
        cosY = (0.5f - yy - zz) * r;
    } else {
        sinX = (y * z - w * x) * -2.0f;
        cosX = 1.0f - (xx - zz) * 2.0f;
        sinY = 0.0f;
        cosY = 1.0f;
    }
    pOut->mUnknown0 = fn_801CFE40(sinX, cosX);
    pOut->mUnknown4 = fn_801CFE40(sinY, cosY);
    pOut->mUnknown8 = fn_801CFE40(sinZ, cosZ);
}

void QuatFromEuler(Quat_t *q, int x, int y, int z)
{
    int angles[3];
    float s[3];
    float c[3];
    float cc;
    float sc;
    float ss;
    float cs;

    angles[0] = z >> 1;
    angles[1] = y >> 1;
    angles[2] = x >> 1;
    fn_801CFCD0(angles, s, c);
    cc = c[2] * c[1];
    sc = s[2] * c[1];
    ss = s[2] * s[1];
    cs = c[2] * s[1];
    q->x = s[0] * cc - c[0] * ss;
    q->y = c[0] * cs + s[0] * sc;
    q->z = c[0] * sc - s[0] * cs;
    q->w = c[0] * cc + s[0] * ss;
}

void QuatFromEulerYZX(Quat_t *q, int x, int y, int z)
{
    int angles[3];
    float s[3];
    float c[3];
    float cc;
    float sc;
    float ss;
    float cs;

    angles[0] = z >> 1;
    angles[1] = x >> 1;
    angles[2] = y >> 1;
    fn_801CFCD0(angles, s, c);
    cc = c[2] * c[1];
    sc = s[2] * c[1];
    ss = s[2] * s[1];
    cs = c[2] * s[1];
    q->x = s[0] * cc + c[0] * ss;
    q->y = c[0] * cs + s[0] * sc;
    q->z = c[0] * sc - s[0] * cs;
    q->w = c[0] * cc - s[0] * ss;
}

void QuatSlerp(Quat_t *q, Quat_t *pTo, Quat_t *pFrom, float t)
{
    Quat_t to;
    float cosom;
    float omega;
    float sinom;
    float scale0;
    float scale1;

    cosom = QuatNormalizedDot(pFrom, pTo);
    if (!(cosom >= 0.0f)) {
        cosom = -cosom;
        to.x = -pTo->x;
        to.y = -pTo->y;
        to.z = -pTo->z;
        to.w = -pTo->w;
    } else {
        to.x = pTo->x;
        to.y = pTo->y;
        to.z = pTo->z;
        to.w = pTo->w;
    }
    if (!(cosom > 0.99f)) {
        omega = fn_801CFDB0(cosom);
        sinom = 1.0f / fn_801CFB74(omega);
        scale0 = fn_801CFB74(omega * (1.0f - t)) * sinom;
        scale1 = fn_801CFB74(omega * t) * sinom;
    } else {
        scale0 = 1.0f - t;
        scale1 = t;
    }
    q->x = scale0 * pFrom->x + scale1 * to.x;
    q->y = scale0 * pFrom->y + scale1 * to.y;
    q->z = scale0 * pFrom->z + scale1 * to.z;
    q->w = scale0 * pFrom->w + scale1 * to.w;
}
