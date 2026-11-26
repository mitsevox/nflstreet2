/* Rigid-body physics: the collision shapes a body is built from (sphere, capsule and box), their
   local bounds, the point tests used for ground and wall contact, the shape-pair contact tests
   that the collision system dispatches by shape type, and their debug drawing. */

#include <math.h>
#include "engine/physshape.h"
#include "engine/physaabb.h"
#include "engine/llmatrix.h"

extern "C" {
float Vec3Magnitude(void *pV);
void Vec3Sub(void *pOut, void *pA, void *pB);
float MathSinf(float x);
float MathCosf(float x);
void DispatchCollisionDebugLine(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, int red, int green,
                                int blue);
}

typedef int (*ShapeCollideFn)(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                              float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);

CollisionShape::CollisionShape(float friction, float bounce, int type)
    : mFriction(friction), mBounce(bounce), mType(type)
{
}

CollisionShape::~CollisionShape()
{
}

void CollisionShape::GetMaterial(float *pFriction, float *pBounce, float (*)[4], Vec3_801DE1E0 *)
{
    *pFriction = mFriction;
    *pBounce = mBounce;
}

static int _ShapeCollideSphereSphere(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                     float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);
static int _ShapeCollideSphereBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                  float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);
static int _ShapeCollideSphereCapsule(CollisionShape *pA, float (*pMatrixA)[4],
                                      CollisionShape *pB, float (*pMatrixB)[4],
                                      Vec3_801DE1E0 *pContact);
static int _ShapeCollideCapsuleBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                   float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);
static int _ShapeCollideBoxBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                               float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);
static int _ShapeCollideCapsuleCapsule(CollisionShape *pA, float (*pMatrixA)[4],
                                       CollisionShape *pB, float (*pMatrixB)[4],
                                       Vec3_801DE1E0 *pContact);

static ShapeCollideFn _ShapeCollide_apTests[3][3] = {
    { _ShapeCollideSphereSphere, _ShapeCollideSphereCapsule, _ShapeCollideSphereBox },
    { 0, _ShapeCollideCapsuleCapsule, _ShapeCollideCapsuleBox },
    { 0, 0, _ShapeCollideBoxBox },
};

int ShapeCollide(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                 float (*pMatrixB)[4], Vec3_801DE1E0 *pContact)
{
    if (_ShapeCollide_apTests[pA->mType][pB->mType] != 0) {
        return _ShapeCollide_apTests[pA->mType][pB->mType](pA, pMatrixA, pB, pMatrixB, pContact);
    }
    return _ShapeCollide_apTests[pB->mType][pA->mType](pB, pMatrixB, pA, pMatrixA, pContact);
}

float SegmentPointParam(Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pPoint)
{
    Vec3_801DE1E0 toPoint;
    Vec3_801DE1E0 fromEnd;
    Vec3_801DE1E0 toEnd;
    float along;

    Vec3Sub(&toPoint, pPoint, pStart);
    Vec3Sub(&toEnd, pEnd, pStart);
    along = Vec3DotProduct(&toPoint, &toEnd);
    if (along <= 0.0f) {
        return 0.0f;
    }
    Vec3Sub(&fromEnd, pPoint, pEnd);
    if (Vec3DotProduct(&fromEnd, &toEnd) >= 0.0f) {
        return 1.0f;
    }
    return along / Vec3DotProduct(&toEnd, &toEnd);
}

static inline void _ClampSegmentParam(float *pParam, float *pOther, Vec3_801DE1E0 *pStart,
                                      Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pOtherStart,
                                      Vec3_801DE1E0 *pOtherEnd)
{
    int clamped = 0;

    if (*pParam <= 0.0f) {
        *pOther = SegmentPointParam(pOtherStart, pOtherEnd, pStart);
        clamped = 1;
    } else if (*pParam >= 1.0f) {
        *pOther = SegmentPointParam(pOtherStart, pOtherEnd, pEnd);
        clamped = 1;
    }
    if (clamped) {
        Vec3_801DE1E0 point;
        float t = *pOther;

        point.x = (pOtherEnd->x - pOtherStart->x) * t + pOtherStart->x;
        point.y = (pOtherEnd->y - pOtherStart->y) * t + pOtherStart->y;
        point.z = (pOtherEnd->z - pOtherStart->z) * t + pOtherStart->z;
        *pParam = SegmentPointParam(pStart, pEnd, &point);
    }
}

int ClosestLineParams(Vec3_801DE1E0 *pStartA, Vec3_801DE1E0 *pEndA, Vec3_801DE1E0 *pStartB,
                      Vec3_801DE1E0 *pEndB, float *pParamA, float *pParamB);

int ClosestSegmentParams(Vec3_801DE1E0 *pStartA, Vec3_801DE1E0 *pEndA, Vec3_801DE1E0 *pStartB,
                         Vec3_801DE1E0 *pEndB, float *pParamA, float *pParamB)
{
    if (ClosestLineParams(pStartA, pEndA, pStartB, pEndB, pParamA, pParamB)) {
        _ClampSegmentParam(pParamA, pParamB, pStartA, pEndA, pStartB, pEndB);
        _ClampSegmentParam(pParamB, pParamA, pStartB, pEndB, pStartA, pEndA);
        return 1;
    }
    return 0;
}

int ClosestLineParams(Vec3_801DE1E0 *pStartA, Vec3_801DE1E0 *pEndA, Vec3_801DE1E0 *pStartB,
                      Vec3_801DE1E0 *pEndB, float *pParamA, float *pParamB)
{
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 dirB;
    Vec3_801DE1E0 dirA;
    float bb;
    float aa;
    float ab;
    float ob;
    float oa;
    float denom;

    Vec3Sub(&dirB, pEndB, pStartB);
    Vec3Sub(&dirA, pEndA, pStartA);
    Vec3Sub(&offset, pStartA, pStartB);
    bb = Vec3DotProduct(&dirB, &dirB);
    aa = Vec3DotProduct(&dirA, &dirA);
    ab = Vec3DotProduct(&dirB, &dirA);
    ob = Vec3DotProduct(&offset, &dirB);
    oa = Vec3DotProduct(&offset, &dirA);
    denom = aa * bb - ab * ab;
    if (fabsf(denom) < 1e-8f) {
        return 0;
    }
    {
        float s = (ob * ab - oa * bb) / denom;

        *pParamA = s;
        *pParamB = (ab * s + ob) / bb;
    }
    return 1;
}

CapsuleShape::CapsuleShape(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, float friction, float bounce,
                           float radius)
    : CollisionShape(friction, bounce, 1)
{
    Vec3Add(&mCenter, pA, pB);
    Vec3Scale(&mCenter, &mCenter, 0.5f);
    Vec3Sub(&mHalfAxis, pB, &mCenter);
    mRadius = radius;
}

void CapsuleShape::GetBounds(BoundingBox *pBounds)
{
    Vec3_801DE1E0 end;
    Vec3_801DE1E0 start;
    Vec3_801DE1E0 low;
    Vec3_801DE1E0 high;
    Vec3_801DE1E0 radius;

    Vec3Add(&end, &mCenter, &mHalfAxis);
    Vec3Sub(&start, &mCenter, &mHalfAxis);
    radius.x = mRadius;
    radius.y = mRadius;
    radius.z = mRadius;
    Vec3Sub(&low, &end, &radius);
    Vec3Sub(&high, &start, &radius);
    pBounds->SetToPoint(&low);
    pBounds->ExtendToPoint(&high);
    Vec3Add(&low, &end, &radius);
    Vec3Add(&high, &start, &radius);
    pBounds->ExtendToPoint(&low);
    pBounds->ExtendToPoint(&high);
}

float CapsuleShape::TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                              Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth,
                              float length)
{
    Vec3_801DE1E0 closest;
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 toPoint;
    Vec3_801DE1E0 end;
    Vec3_801DE1E0 start;
    Vec3_801DE1E0 axis;
    float halfLength;
    float axisLength;
    float along;
    float dist;
    float weight;
    int capped;

    *pDepth = 0.0f;
    weight = 0.2f;
    GetWorldSegment(pMatrix, &end, &start, &axis);
    Vec3Normalize(&axis, &axis);
    halfLength = Vec3Magnitude(&mHalfAxis);
    Vec3Sub(&toPoint, pPoint, &start);
    axisLength = halfLength + halfLength;
    along = Vec3DotProduct(&toPoint, &axis);
    Vec3Scale(&closest, &axis, along);
    Vec3Add(&closest, &closest, &start);
    Vec3Sub(&offset, pPoint, &closest);
    dist = Vec3Magnitude(&offset);
    capped = 0;
    if (dist > mRadius) {
        if (along <= 0.0f) {
            closest = start;
            along = 0.0f;
            capped = 1;
            *pDepth = 0.0f;
        }
        if (along >= axisLength) {
            closest = end;
            along = axisLength;
            capped = 1;
            *pDepth = 0.0f;
        }
    } else {
        float depth = mRadius - dist;
        float fromEnd = axisLength - along;

        if (along < depth) {
            *pDepth = along;
            capped = 1;
        }
        if (fromEnd < depth) {
            *pDepth = fromEnd;
            capped = 1;
        }
    }
    if (!capped) {
        if (dist < 1e-8f) {
            Vec3_801DE1E0 turned;

            turned.x = axis.y;
            turned.y = axis.z;
            turned.z = axis.x;
            Vec3CrossProduct(&offset, &turned, &axis);
            Vec3Normalize(&offset, &offset);
            dist = mRadius * 0.05f;
            Vec3Scale(&offset, &offset, dist);
        }
        Vec3Scale(&offset, &offset, mRadius / dist);
        Vec3Add(pContact, &closest, &offset);
        Vec3Normalize(pNormal, &offset);
        *pDepth = mRadius - dist;
        weight = 0.7f;
        if (along < length || axisLength - along < length) {
            weight = 0.2f;
        }
    } else {
        if (dist > mRadius) {
            Vec3Scale(&offset, &offset, mRadius / dist);
            dist = mRadius;
        }
        if (along < halfLength) {
            Vec3Add(pContact, &start, &offset);
            pNormal->x = -axis.x;
            pNormal->y = -axis.y;
            pNormal->z = -axis.z;
        } else {
            Vec3Add(pContact, &end, &offset);
            pNormal->x = axis.x;
            pNormal->y = axis.y;
            pNormal->z = axis.z;
        }
        weight = 1.0f;
        if (mRadius - dist < length) {
            weight = 0.2f;
        }
    }
    if (*pDepth < 0.0f) {
        *pDepth = 0.0f;
    }
    return weight;
}

void CapsuleShape::GetWorldSegment(float (*pMatrix)[4], Vec3_801DE1E0 *pEnd,
                                   Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pHalfAxis)
{
    Vec3_801DE1E0 center;

    MatPush();
    MatLoad((float *)pMatrix);
    Vec3Mat34Mul(&center, &mCenter);
    Vec3Mat33Mul(pHalfAxis, &mHalfAxis);
    MatPop();
    Vec3Add(pEnd, &center, pHalfAxis);
    Vec3Sub(pStart, &center, pHalfAxis);
}

float CapsuleShape::GetSupportWeight(Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pDirection,
                                     float (*pMatrix)[4])
{
    Vec3_801DE1E0 end;
    Vec3_801DE1E0 start;
    Vec3_801DE1E0 axis;

    GetWorldSegment(pMatrix, &end, &start, &axis);
    Vec3Normalize(&axis, &axis);
    if (fabsf(Vec3DotProduct(pDirection, &axis)) < 0.2f) {
        return 1.0f;
    }
    return 0.0f;
}

void CapsuleShape::ClosestSurfacePoint(Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pEnd,
                                       Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pAxis,
                                       Vec3_801DE1E0 *pContact, unsigned char *pOnSide)
{
    Vec3_801DE1E0 closest;
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 toPoint;
    float halfLength;
    float axisLength;
    float along;
    float dist;
    int capped;

    *pOnSide = 1;
    halfLength = Vec3Magnitude(&mHalfAxis);
    Vec3Sub(&toPoint, pPoint, pStart);
    axisLength = halfLength + halfLength;
    along = Vec3DotProduct(&toPoint, pAxis);
    Vec3Scale(&closest, pAxis, along);
    Vec3Add(&closest, &closest, pStart);
    Vec3Sub(&offset, pPoint, &closest);
    dist = Vec3Magnitude(&offset);
    capped = 0;
    if (dist > mRadius) {
        *pOnSide = 0;
        if (along <= 0.0f) {
            closest = *pStart;
            along = 0.0f;
            capped = 1;
        }
        if (along >= axisLength) {
            closest = *pEnd;
            along = axisLength;
            capped = 1;
        }
    } else {
        float depth = mRadius - dist;
        float fromEnd = axisLength - along;

        if (along < depth) {
            capped = 1;
            if (along < 0.0f) {
                *pOnSide = 0;
            }
        }
        if (fromEnd < depth) {
            capped = 1;
            if (fromEnd < 0.0f) {
                *pOnSide = 0;
            }
        }
    }
    if (!capped) {
        if (dist < 1e-8f) {
            Vec3_801DE1E0 turned;

            turned.x = pAxis->y;
            turned.y = pAxis->z;
            turned.z = pAxis->x;
            Vec3CrossProduct(&offset, &turned, pAxis);
            Vec3Normalize(&offset, &offset);
            dist = mRadius * 0.05f;
            Vec3Scale(&offset, &offset, dist);
        }
        Vec3Scale(&offset, &offset, mRadius / dist);
        Vec3Add(pContact, &closest, &offset);
    } else {
        if (dist > mRadius) {
            Vec3Scale(&offset, &offset, mRadius / dist);
        }
        if (along < halfLength) {
            Vec3Add(pContact, pStart, &offset);
        } else {
            Vec3Add(pContact, pEnd, &offset);
        }
    }
}

int CapsuleShape::ProjectsInside(Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pStart,
                                 Vec3_801DE1E0 *pAxis, Vec3_801DE1E0 *pPointB)
{
    Vec3_801DE1E0 toPoint;
    Vec3_801DE1E0 closest;
    Vec3_801DE1E0 offset;
    float axisLength = Vec3Magnitude(&mHalfAxis);
    float along;

    axisLength = axisLength + axisLength;
    Vec3Sub(&toPoint, pPointB, pStart);
    along = Vec3DotProduct(&toPoint, pAxis);
    if (along >= 0.0f && along <= axisLength) {
        Vec3Scale(&closest, pAxis, along);
        Vec3Add(&closest, &closest, pStart);
        Vec3Sub(&offset, pPointB, &closest);
        return Vec3MagnitudeSqr(&offset) <= mRadius * mRadius;
    }
    return 0;
}

#define _CAPSULE_RING_POINT(op, dir)                                                \
    op(&pOut[count], pCenter, dir);                                                \
    if (ProjectsInside(pEnd, pStart, pAxis, &pOut[count])) {                       \
        count++;                                                                   \
        if (count >= max) {                                                        \
            return count;                                                          \
        }                                                                          \
    }

unsigned int CapsuleShape::RingPoints(Vec3_801DE1E0 *pCenter, Vec3_801DE1E0 *pNormal,
                                      Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pStart,
                                      Vec3_801DE1E0 *pAxis, Vec3_801DE1E0 *pOut,
                                      unsigned int max, float radius)
{
    Vec3_801DE1E0 u;
    Vec3_801DE1E0 v;
    Vec3_801DE1E0 sum;
    unsigned int count;

    v.x = pNormal->y;
    v.z = pNormal->x;
    v.y = pNormal->z;
    Vec3CrossProduct(&u, pNormal, &v);
    count = 0;
    Vec3Normalize(&u, &u);
    Vec3CrossProduct(&v, pNormal, &u);
    Vec3Scale(&u, &u, radius);
    Vec3Scale(&v, &v, radius);
    _CAPSULE_RING_POINT(Vec3Add, &u)
    _CAPSULE_RING_POINT(Vec3Sub, &u)
    _CAPSULE_RING_POINT(Vec3Add, &v)
    _CAPSULE_RING_POINT(Vec3Sub, &v)
    Vec3Scale(&u, &u, 0.7071f);
    Vec3Scale(&v, &v, 0.7071f);
    Vec3Add(&sum, &u, &v);
    Vec3Sub(&v, &u, &v);
    u = sum;
    _CAPSULE_RING_POINT(Vec3Add, &u)
    _CAPSULE_RING_POINT(Vec3Sub, &u)
    _CAPSULE_RING_POINT(Vec3Add, &v)
    _CAPSULE_RING_POINT(Vec3Sub, &v)
    return count;
}

SphereShape::SphereShape(Vec3_801DE1E0 *pCenter, float friction, float bounce, float radius)
    : CollisionShape(friction, bounce, 0)
{
    mCenter = *pCenter;
    mRadius = radius;
}

void SphereShape::GetBounds(BoundingBox *pBounds)
{
    Vec3_801DE1E0 low;
    Vec3_801DE1E0 high;
    Vec3_801DE1E0 radius;

    radius.x = mRadius;
    radius.y = mRadius;
    radius.z = mRadius;
    Vec3Sub(&low, &mCenter, &radius);
    Vec3Add(&high, &mCenter, &radius);
    pBounds->SetBounds(&low, &high);
}

float SphereShape::TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                             Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth,
                             float length)
{
    Vec3_801DE1E0 center;
    Vec3_801DE1E0 offset;
    float dist;
    float weight = 0.5f;

    MatPush();
    MatLoad((float *)pMatrix);
    Vec3Mat34Mul(&center, &mCenter);
    MatPop();
    Vec3Sub(&offset, pPoint, &center);
    dist = Vec3Magnitude(&offset);
    *pDepth = (mRadius - dist) * weight;
    if (dist < 1e-8f) {
        dist = mRadius;
        *pDepth = dist * weight;
        offset = *pDelta;
        Vec3Normalize(&offset, &offset);
        Vec3Scale(&offset, &offset, dist);
        weight = 0.01f;
    }
    Vec3Scale(pNormal, &offset, 1.0f / dist);
    Vec3Scale(pContact, pNormal, mRadius);
    Vec3Add(pContact, pContact, &center);
    if (Vec3DotProduct(pDelta, pNormal) < 0.0f) {
        weight = 0.01f;
    }
    if (fabsf(*pDepth) > length) {
        weight *= 0.1f;
    }
    if (*pDepth < 0.0f) {
        *pDepth = 0.0f;
        weight *= 0.1f;
    }
    if (length > mRadius) {
        weight *= 0.01f;
    }
    return weight;
}

BoxShape::BoxShape(Vec3_801DE1E0 *pCenter, float friction, float bounce, float halfX, float halfY,
                   float halfZ)
    : CollisionShape(friction, bounce, 2)
{
    mCenter = *pCenter;
    mHalfSize.x = halfX;
    mHalfSize.y = halfY;
    mHalfSize.z = halfZ;
}

void BoxShape::GetBounds(BoundingBox *pBounds)
{
    Vec3_801DE1E0 low;
    Vec3_801DE1E0 high;

    Vec3Sub(&low, &mCenter, &mHalfSize);
    Vec3Add(&high, &mCenter, &mHalfSize);
    pBounds->SetBounds(&low, &high);
}

#define _CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))

static inline float _Clamp(float value, float low, float high)
{
    return value < low ? low : (value > high ? high : value);
}

float BoxShape::TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                          Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth,
                          float length)
{
    Vec3_801DE1E0 local;
    Vec3_801DE1E0 delta;
    Vec3_801DE1E0 best;
    Vec3_801DE1E0 face;
    Vec3_801DE1E0 origin;
    Vec3_801DE1E0 offset;
    float bestDist;
    float dist;
    float weight;
    int inside;
    int edges;

    best.x = best.y = best.z = 0.0f;
    MatPush();
    inside = 0;
    origin.x = pMatrix[0][3];
    origin.y = pMatrix[1][3];
    origin.z = pMatrix[2][3];
    Vec3Sub(&face, pPoint, &origin);
    MatLoad((float *)pMatrix);
    MatTranspose();
    Vec3Mat33Mul(&local, &face);
    Vec3Mat33Mul(&delta, pDelta);
    Vec3Sub(&local, &local, &mCenter);
    MatPop();
    if (length > 1e-8f && fabsf(local.x) < mHalfSize.x && fabsf(local.y) < mHalfSize.y
        && fabsf(local.z) < mHalfSize.z) {
        Vec3Add(&face, &delta, &local);
        inside = SegmentHits(&local, &face, &best, 1, 0) == 1;
    }
    if (!inside) {
        face.x = _CLAMP(local.x, -mHalfSize.x, mHalfSize.x);
        face.y = _CLAMP(local.y, -mHalfSize.y, mHalfSize.y);
        if (local.z > 0.0f) {
            face.z = mHalfSize.z;
        } else {
            face.z = -mHalfSize.z;
        }
        Vec3Sub(&offset, &local, &face);
        bestDist = Vec3MagnitudeSqr(&offset);
        best = face;
        face.y = _CLAMP(local.y, -mHalfSize.y, mHalfSize.y);
        face.z = _CLAMP(local.z, -mHalfSize.z, mHalfSize.z);
        if (local.x > 0.0f) {
            face.x = mHalfSize.x;
        } else {
            face.x = -mHalfSize.x;
        }
        Vec3Sub(&offset, &local, &face);
        dist = Vec3MagnitudeSqr(&offset);
        if (dist < bestDist) {
            bestDist = dist;
            best = face;
        }
        face.x = _CLAMP(local.x, -mHalfSize.x, mHalfSize.x);
        face.z = _CLAMP(local.z, -mHalfSize.z, mHalfSize.z);
        if (local.y > 0.0f) {
            face.y = mHalfSize.y;
        } else {
            face.y = -mHalfSize.y;
        }
        Vec3Sub(&offset, &local, &face);
        dist = Vec3MagnitudeSqr(&offset);
        if (dist < bestDist) {
            bestDist = dist;
            best = face;
        }
    }
    pNormal->x = 0.0f;
    pNormal->y = 0.0f;
    pNormal->z = 0.0f;
    if (fabsf(fabsf(best.z) - mHalfSize.z) < 1e-8f) {
        pNormal->z = best.z > 0.0f ? 1.0f : -1.0f;
        *pDepth = mHalfSize.z - Vec3DotProduct(pNormal, &local);
    } else if (fabsf(fabsf(best.x) - mHalfSize.x) < 1e-8f) {
        pNormal->x = best.x > 0.0f ? 1.0f : -1.0f;
        *pDepth = mHalfSize.x - Vec3DotProduct(pNormal, &local);
    } else {
        pNormal->y = best.y > 0.0f ? 1.0f : -1.0f;
        *pDepth = mHalfSize.y - Vec3DotProduct(pNormal, &local);
    }
    edges = fabsf(fabsf(best.x) - mHalfSize.x) < length;
    if (fabsf(fabsf(best.y) - mHalfSize.y) < length) {
        edges++;
    }
    if (fabsf(fabsf(best.z) - mHalfSize.z) < length) {
        edges++;
    }
    weight = 1.0f;
    switch (edges) {
    case 2:
        weight = 0.3f;
        break;
    case 3:
        weight = 0.1f;
        break;
    }
    if (fabsf(delta.x) > mHalfSize.x || fabsf(delta.y) > mHalfSize.y
        || fabsf(delta.z) > mHalfSize.z) {
        weight *= 0.1f;
    }
    if (*pDepth > length) {
        weight *= 0.1f;
    }
    if (*pDepth < 0.0f) {
        *pDepth = 0.0f;
    }
    MatPush();
    Vec3Add(&best, &best, &mCenter);
    MatLoad((float *)pMatrix);
    Vec3Mat33Mul(pNormal, pNormal);
    Vec3Mat34Mul(pContact, &best);
    MatPop();
    return weight;
}

static inline void _SetVec(Vec3_801DE1E0 *pOut, float x, float y, float z)
{
    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
}

#define _BOX_FACE_HITS(AXIS, U, V, PLANE, HALF_U, HALF_V, X, Y, Z)                            \
    if ((pStart->AXIS < PLANE && pEnd->AXIS > PLANE)                                          \
        || (pStart->AXIS > PLANE && pEnd->AXIS < PLANE)) {                                    \
        float t = (PLANE - pStart->AXIS) / (pEnd->AXIS - pStart->AXIS);                       \
        float u = (pEnd->U - pStart->U) * t + pStart->U;                                      \
        float v = (pEnd->V - pStart->V) * t + pStart->V;                                      \
        float x = X;                                                                          \
        float y = Y;                                                                          \
        float z = Z;                                                                          \
        if (fabsf(u) < HALF_U && fabsf(v) < HALF_V) {                                         \
            pOut[count].x = x;                                                                \
            pOut[count].y = y;                                                                \
            pOut[count].z = z;                                                                \
            count++;                                                                          \
            if (count >= max) {                                                               \
                return count;                                                                 \
            }                                                                                 \
        }                                                                                     \
    }

unsigned int BoxShape::SegmentHits(Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pEnd,
                                   Vec3_801DE1E0 *pOut, unsigned int max, int withEnds)
{
    unsigned int count = 0;

    if (max != 0) {
        if (withEnds) {
            if (fabsf(pStart->x) <= mHalfSize.x && fabsf(pStart->y) <= mHalfSize.y
                && fabsf(pStart->z) <= mHalfSize.z) {
                pOut[count] = *pStart;
                count++;
                if (count >= max) {
                    return count;
                }
            }
            if (fabsf(pEnd->x) <= mHalfSize.x && fabsf(pEnd->y) <= mHalfSize.y
                && fabsf(pEnd->z) <= mHalfSize.z) {
                pOut[count] = *pEnd;
                count++;
                if (count >= max) {
                    return count;
                }
            }
        }
        _BOX_FACE_HITS(x, y, z, mHalfSize.x, mHalfSize.y, mHalfSize.z, mHalfSize.x, u, v)
        _BOX_FACE_HITS(x, y, z, -mHalfSize.x, mHalfSize.y, mHalfSize.z, -mHalfSize.x, u, v)
        _BOX_FACE_HITS(y, x, z, mHalfSize.y, mHalfSize.x, mHalfSize.z, u, mHalfSize.y, v)
        _BOX_FACE_HITS(y, x, z, -mHalfSize.y, mHalfSize.x, mHalfSize.z, u, -mHalfSize.y, v)
        _BOX_FACE_HITS(z, x, y, mHalfSize.z, mHalfSize.x, mHalfSize.y, u, v, mHalfSize.z)
        _BOX_FACE_HITS(z, x, y, -mHalfSize.z, mHalfSize.x, mHalfSize.y, u, v, -mHalfSize.z)
    }
    return count;
}

unsigned int BoxShape::QuadHits(Vec3_801DE1E0 *pQuad, Vec3_801DE1E0 *pOut, unsigned int max)
{
    unsigned int count;

    count = SegmentHits(&pQuad[0], &pQuad[1], pOut, max, 1);
    count += SegmentHits(&pQuad[1], &pQuad[2], &pOut[count], max - count, 1);
    count += SegmentHits(&pQuad[2], &pQuad[3], &pOut[count], max - count, 1);
    count += SegmentHits(&pQuad[3], &pQuad[0], &pOut[count], max - count, 1);
    return count;
}

void BoxShape::GetCornersIn(float (*pMatrix)[4], BoxShape *pOther, float (*pOtherMatrix)[4],
                            Vec3_801DE1E0 *pCorners)
{
    Vec3_801DE1E0 corner;
    Vec3_801DE1E0 axisX;
    Vec3_801DE1E0 axisY;
    Vec3_801DE1E0 axisZ;
    Vec3_801DE1E0 origin;

    MatPush();
    Vec3Sub(&corner, &pOther->mCenter, &pOther->mHalfSize);
    MatLoad((float *)pOtherMatrix);
    Vec3Mat34Mul(&corner, &corner);
    origin.x = pMatrix[0][3];
    origin.y = pMatrix[1][3];
    origin.z = pMatrix[2][3];
    Vec3Sub(&corner, &corner, &origin);
    MatLoad((float *)pMatrix);
    MatTranspose();
    Vec3Mat33Mul(&corner, &corner);
    Vec3Sub(&corner, &corner, &mCenter);
    axisX.x = pOtherMatrix[0][0];
    axisX.y = pOtherMatrix[1][0];
    axisX.z = pOtherMatrix[2][0];
    axisY.x = pOtherMatrix[0][1];
    axisY.y = pOtherMatrix[1][1];
    axisY.z = pOtherMatrix[2][1];
    axisZ.x = pOtherMatrix[0][2];
    axisZ.y = pOtherMatrix[1][2];
    axisZ.z = pOtherMatrix[2][2];
    Vec3Mat33Mul(&axisX, &axisX);
    Vec3Mat33Mul(&axisY, &axisY);
    Vec3Mat33Mul(&axisZ, &axisZ);
    MatPop();
    Vec3Scale(&axisX, &axisX, pOther->mHalfSize.x + pOther->mHalfSize.x);
    Vec3Scale(&axisY, &axisY, pOther->mHalfSize.y + pOther->mHalfSize.y);
    Vec3Scale(&axisZ, &axisZ, pOther->mHalfSize.z + pOther->mHalfSize.z);
    pCorners[0] = corner;
    Vec3Add(&pCorners[1], &corner, &axisX);
    Vec3Add(&pCorners[2], &pCorners[1], &axisY);
    Vec3Add(&pCorners[3], &corner, &axisY);
    Vec3Add(&corner, &corner, &axisZ);
    pCorners[4] = corner;
    Vec3Add(&pCorners[5], &corner, &axisX);
    Vec3Add(&pCorners[6], &pCorners[5], &axisY);
    Vec3Add(&pCorners[7], &corner, &axisY);
}

float BoxShape::ClosestSurfacePoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4],
                                    Vec3_801DE1E0 *pLocal, Vec3_801DE1E0 *pOut)
{
    Vec3_801DE1E0 local;
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 face;
    Vec3_801DE1E0 best;
    Vec3_801DE1E0 relative;
    Vec3_801DE1E0 origin;
    float bestDist;
    float dist;

    MatPush();
    origin.x = pMatrix[0][3];
    origin.y = pMatrix[1][3];
    origin.z = pMatrix[2][3];
    Vec3Sub(&relative, pPoint, &origin);
    MatLoad((float *)pMatrix);
    MatTranspose();
    Vec3Mat33Mul(&local, &relative);
    Vec3Sub(&local, &local, &mCenter);
    *pLocal = local;
    face.x = _CLAMP(local.x, -mHalfSize.x, mHalfSize.x);
    face.y = _CLAMP(local.y, -mHalfSize.y, mHalfSize.y);
    if (local.z > 0.0f) {
        face.z = mHalfSize.z;
    } else {
        face.z = -mHalfSize.z;
    }
    Vec3Sub(&offset, &local, &face);
    bestDist = Vec3MagnitudeSqr(&offset);
    best = face;
    face.y = _CLAMP(local.y, -mHalfSize.y, mHalfSize.y);
    face.z = _CLAMP(local.z, -mHalfSize.z, mHalfSize.z);
    if (local.x > 0.0f) {
        face.x = mHalfSize.x;
    } else {
        face.x = -mHalfSize.x;
    }
    Vec3Sub(&offset, &local, &face);
    dist = Vec3MagnitudeSqr(&offset);
    if (dist < bestDist) {
        bestDist = dist;
        best = face;
    }
    face.x = _CLAMP(local.x, -mHalfSize.x, mHalfSize.x);
    face.z = _CLAMP(local.z, -mHalfSize.z, mHalfSize.z);
    if (local.y > 0.0f) {
        face.y = mHalfSize.y;
    } else {
        face.y = -mHalfSize.y;
    }
    Vec3Sub(&offset, &local, &face);
    dist = Vec3MagnitudeSqr(&offset);
    if (dist < bestDist) {
        bestDist = dist;
        best = face;
    }
    Vec3Add(&best, &best, &mCenter);
    MatLoad((float *)pMatrix);
    Vec3Mat34Mul(pOut, &best);
    bestDist = sqrtf(bestDist);
    MatPop();
    return bestDist;
}

static int _ShapeCollideSphereSphere(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                     float (*pMatrixB)[4], Vec3_801DE1E0 *pContact)
{
    SphereShape *pSphereA = (SphereShape *)pA;
    SphereShape *pSphereB = (SphereShape *)pB;
    Vec3_801DE1E0 centerA;
    Vec3_801DE1E0 centerB;
    Vec3_801DE1E0 offset;
    float distSq;

    MatPush();
    MatLoad((float *)pMatrixA);
    Vec3Mat34Mul(&centerA, &pSphereA->mCenter);
    MatLoad((float *)pMatrixB);
    Vec3Mat34Mul(&centerB, &pSphereB->mCenter);
    MatPop();
    Vec3Sub(&offset, &centerB, &centerA);
    distSq = Vec3MagnitudeSqr(&offset);
    if (distSq < (pSphereA->mRadius + pSphereB->mRadius) * (pSphereA->mRadius + pSphereB->mRadius)) {
        float dist = sqrtf(distSq);

        if (dist > 1e-8f) {
            if (pSphereA->mRadius <= pSphereB->mRadius) {
                Vec3Scale(&offset, &offset, pSphereA->mRadius / dist);
                Vec3Add(pContact, &centerA, &offset);
            } else {
                Vec3Scale(&offset, &offset, -pSphereB->mRadius / dist);
                Vec3Add(pContact, &centerB, &offset);
            }
        } else {
            *pContact = centerA;
        }
        return 1;
    }
    return 0;
}

static int _ShapeCollideSphereBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                  float (*pMatrixB)[4], Vec3_801DE1E0 *pContact)
{
    SphereShape *pSphere = (SphereShape *)pA;
    BoxShape *pBox = (BoxShape *)pB;
    Vec3_801DE1E0 center;
    Vec3_801DE1E0 local;
    Vec3_801DE1E0 surface;

    MatPush();
    MatLoad((float *)pMatrixA);
    Vec3Mat34Mul(&center, &pSphere->mCenter);
    MatPop();
    if (pBox->ClosestSurfacePoint(&center, pMatrixB, &local, &surface) < pSphere->mRadius) {
        *pContact = surface;
        return 1;
    }
    if (local.x >= -pBox->mHalfSize.x && local.x <= pBox->mHalfSize.x
        && local.y >= -pBox->mHalfSize.y && local.y <= pBox->mHalfSize.y
        && local.z >= -pBox->mHalfSize.z && local.z <= pBox->mHalfSize.z) {
        *pContact = center;
        return 1;
    }
    return 0;
}

static int _ShapeCollideSphereCapsule(CollisionShape *pA, float (*pMatrixA)[4],
                                      CollisionShape *pB, float (*pMatrixB)[4],
                                      Vec3_801DE1E0 *pContact)
{
    SphereShape *pSphere = (SphereShape *)pA;
    CapsuleShape *pCapsule = (CapsuleShape *)pB;
    Vec3_801DE1E0 center;
    Vec3_801DE1E0 surface;
    Vec3_801DE1E0 end;
    Vec3_801DE1E0 start;
    Vec3_801DE1E0 axis;
    unsigned char inside;

    MatPush();
    MatLoad((float *)pMatrixA);
    Vec3Mat34Mul(&center, &pSphere->mCenter);
    MatPop();
    inside = 0;
    pCapsule->GetWorldSegment(pMatrixB, &end, &start, &axis);
    Vec3Normalize(&axis, &axis);
    pCapsule->ClosestSurfacePoint(&center, &end, &start, &axis, &surface, &inside);
    if (inside) {
        *pContact = center;
        return 1;
    }
    {
        Vec3_801DE1E0 offset;

        Vec3Sub(&offset, &surface, &center);
        if (Vec3MagnitudeSqr(&offset) < pSphere->mRadius * pSphere->mRadius) {
            *pContact = surface;
            return 1;
        }
    }
    return 0;
}

static int _ShapeCollideCapsuleBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                                   float (*pMatrixB)[4], Vec3_801DE1E0 *pContact)
{
    CapsuleShape *pCapsule = (CapsuleShape *)pA;
    BoxShape *pBox = (BoxShape *)pB;
    Vec3_801DE1E0 end;
    Vec3_801DE1E0 start;
    Vec3_801DE1E0 axis;
    Vec3_801DE1E0 localEnd;
    Vec3_801DE1E0 localStart;
    Vec3_801DE1E0 dir;
    Vec3_801DE1E0 quad[4];
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 side;
    Vec3_801DE1E0 points[12];
    Vec3_801DE1E0 relEnd;
    Vec3_801DE1E0 relStart;
    Vec3_801DE1E0 origin;
    float absX;
    float absY;
    float absZ;
    unsigned int count;
    unsigned int i;

    pCapsule->GetWorldSegment(pMatrixA, &end, &start, &axis);
    MatPush();
    count = 0;
    origin.x = pMatrixB[0][3];
    origin.y = pMatrixB[1][3];
    origin.z = pMatrixB[2][3];
    Vec3Sub(&relEnd, &end, &origin);
    Vec3Sub(&relStart, &start, &origin);
    MatLoad((float *)pMatrixB);
    MatTranspose();
    Vec3Mat33Mul(&localEnd, &relEnd);
    Vec3Mat33Mul(&localStart, &relStart);
    Vec3Sub(&localEnd, &localEnd, &pBox->mCenter);
    Vec3Sub(&localStart, &localStart, &pBox->mCenter);
    MatPop();
    Vec3Sub(&dir, &localEnd, &localStart);
    absX = fabsf(dir.x);
    absY = fabsf(dir.y);
    absZ = fabsf(dir.z);
    if (absX < 1e-8f && absY < 1e-8f) {
        offset.x = pCapsule->mRadius;
        offset.y = 0.0f;
        offset.z = 0.0f;
    } else {
        side.x = dir.y;
        side.y = -dir.x;
        side.z = 0.0f;
        Vec3CrossProduct(&offset, &side, &dir);
        Vec3Scale(&offset, &offset, pCapsule->mRadius / Vec3Magnitude(&offset));
    }
    Vec3Add(&quad[0], &localEnd, &offset);
    Vec3Sub(&quad[1], &localEnd, &offset);
    Vec3Sub(&quad[2], &localStart, &offset);
    Vec3Add(&quad[3], &localStart, &offset);
    count += pBox->QuadHits(quad, &points[count], 12);
    if (absX < 1e-8f && absZ < 1e-8f) {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = pCapsule->mRadius;
    } else {
        side.x = dir.z;
        side.y = 0.0f;
        side.z = -dir.x;
        Vec3CrossProduct(&offset, &side, &dir);
        Vec3Scale(&offset, &offset, pCapsule->mRadius / Vec3Magnitude(&offset));
    }
    Vec3Add(&quad[0], &localEnd, &offset);
    Vec3Sub(&quad[1], &localEnd, &offset);
    Vec3Sub(&quad[2], &localStart, &offset);
    Vec3Add(&quad[3], &localStart, &offset);
    count += pBox->QuadHits(quad, &points[count], 12 - count);
    if (absY < 1e-8f && absZ < 1e-8f) {
        offset.x = 0.0f;
        offset.y = pCapsule->mRadius;
        offset.z = 0.0f;
    } else {
        side.x = 0.0f;
        side.y = dir.z;
        side.z = -dir.y;
        Vec3CrossProduct(&offset, &side, &dir);
        Vec3Scale(&offset, &offset, pCapsule->mRadius / Vec3Magnitude(&offset));
    }
    Vec3Add(&quad[0], &localEnd, &offset);
    Vec3Sub(&quad[1], &localEnd, &offset);
    Vec3Sub(&quad[2], &localStart, &offset);
    Vec3Add(&quad[3], &localStart, &offset);
    count += pBox->QuadHits(quad, &points[count], 12 - count);
    if (count == 0) {
        Vec3Normalize(&axis, &axis);
        pBox->ClosestSurfacePoint(&end, pMatrixB, &side, &points[0]);
        if (pCapsule->ProjectsInside(&end, &start, &axis, &points[0])) {
            count = 1;
        }
        pBox->ClosestSurfacePoint(&start, pMatrixB, &side, &points[count]);
        if (pCapsule->ProjectsInside(&end, &start, &axis, &points[count])) {
            count++;
        }
        Vec3Add(&relEnd, &end, &start);
        Vec3Scale(&relEnd, &relEnd, 0.5f);
        pBox->ClosestSurfacePoint(&relEnd, pMatrixB, &side, &points[count]);
        if (pCapsule->ProjectsInside(&end, &start, &axis, &points[count])) {
            count++;
        }
        if (count != 0) {
            for (i = 1; i < count; i++) {
                Vec3Add(&points[0], &points[0], &points[i]);
            }
            Vec3Scale(pContact, &points[0], 1.0f / (float)count);
            return 1;
        }
    } else {
        unsigned int j;

        for (j = 1; j < count; j++) {
            Vec3Add(&points[0], &points[0], &points[j]);
        }
        Vec3Scale(&points[0], &points[0], 1.0f / (float)count);
        MatPush();
        Vec3Add(&points[0], &points[0], &pBox->mCenter);
        MatLoad((float *)pMatrixB);
        Vec3Mat34Mul(pContact, &points[0]);
        MatPop();
        return 1;
    }
    return 0;
}

#define _BOX_EDGE_HITS(pBox, a, b)                                                            \
    count += pBox->SegmentHits(&corners[a], &corners[b], &points[count], 16 - count, 1)

static int _ShapeCollideBoxBox(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                               float (*pMatrixB)[4], Vec3_801DE1E0 *pContact)
{
    BoxShape *pBoxA = (BoxShape *)pA;
    BoxShape *pBoxB = (BoxShape *)pB;
    Vec3_801DE1E0 corners[8];
    Vec3_801DE1E0 center;
    Vec3_801DE1E0 points[16];
    float (*pMatrix)[4];
    unsigned int count;
    unsigned int i;

    pBoxA->GetCornersIn(pMatrixA, pBoxB, pMatrixB, corners);
    count = pBoxA->SegmentHits(&corners[0], &corners[1], points, 16, 1);
    _BOX_EDGE_HITS(pBoxA, 1, 2);
    _BOX_EDGE_HITS(pBoxA, 2, 3);
    _BOX_EDGE_HITS(pBoxA, 3, 0);
    _BOX_EDGE_HITS(pBoxA, 4, 5);
    _BOX_EDGE_HITS(pBoxA, 5, 6);
    _BOX_EDGE_HITS(pBoxA, 6, 7);
    _BOX_EDGE_HITS(pBoxA, 7, 4);
    _BOX_EDGE_HITS(pBoxA, 0, 4);
    _BOX_EDGE_HITS(pBoxA, 1, 5);
    _BOX_EDGE_HITS(pBoxA, 2, 6);
    _BOX_EDGE_HITS(pBoxA, 3, 7);
    if (count != 0) {
        center = pBoxA->mCenter;
        pMatrix = pMatrixA;
    } else {
        pBoxB->GetCornersIn(pMatrixB, pBoxA, pMatrixA, corners);
        count = pBoxB->SegmentHits(&corners[0], &corners[1], points, 16, 1);
        _BOX_EDGE_HITS(pBoxB, 1, 2);
        _BOX_EDGE_HITS(pBoxB, 2, 3);
        _BOX_EDGE_HITS(pBoxB, 3, 0);
        _BOX_EDGE_HITS(pBoxB, 4, 5);
        _BOX_EDGE_HITS(pBoxB, 5, 6);
        _BOX_EDGE_HITS(pBoxB, 6, 7);
        _BOX_EDGE_HITS(pBoxB, 7, 4);
        _BOX_EDGE_HITS(pBoxB, 0, 4);
        _BOX_EDGE_HITS(pBoxB, 1, 5);
        _BOX_EDGE_HITS(pBoxB, 2, 6);
        _BOX_EDGE_HITS(pBoxB, 3, 7);
        center = pBoxB->mCenter;
        pMatrix = pMatrixB;
    }
    if (count != 0) {
        for (i = 1; i < count; i++) {
            Vec3Add(&points[0], &points[0], &points[i]);
        }
        Vec3Scale(&points[0], &points[0], 1.0f / (float)count);
        MatPush();
        Vec3Add(&points[0], &points[0], &center);
        MatLoad((float *)pMatrix);
        Vec3Mat34Mul(pContact, &points[0]);
        MatPop();
        return 1;
    }
    return 0;
}

static int _ShapeCollideCapsuleCapsule(CollisionShape *pA, float (*pMatrixA)[4],
                                       CollisionShape *pB, float (*pMatrixB)[4],
                                       Vec3_801DE1E0 *pContact)
{
    CapsuleShape *pCapsuleA = (CapsuleShape *)pA;
    CapsuleShape *pCapsuleB = (CapsuleShape *)pB;
    Vec3_801DE1E0 endA;
    Vec3_801DE1E0 startA;
    Vec3_801DE1E0 endB;
    Vec3_801DE1E0 startB;
    Vec3_801DE1E0 axisA;
    Vec3_801DE1E0 axisB;
    Vec3_801DE1E0 pointA;
    Vec3_801DE1E0 pointB;
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 points[32];
    float paramA;
    float paramB;
    unsigned int count;
    unsigned int i;

    pCapsuleA->GetWorldSegment(pMatrixA, &endA, &startA, &axisA);
    pCapsuleB->GetWorldSegment(pMatrixB, &endB, &startB, &axisB);
    if (ClosestSegmentParams(&endA, &startA, &endB, &startB, &paramA, &paramB)) {
        float distSq;

        pointA.x = (startA.x - endA.x) * paramA + endA.x;
        pointA.y = (startA.y - endA.y) * paramA + endA.y;
        pointA.z = (startA.z - endA.z) * paramA + endA.z;
        pointB.x = (startB.x - endB.x) * paramB + endB.x;
        pointB.y = (startB.y - endB.y) * paramB + endB.y;
        pointB.z = (startB.z - endB.z) * paramB + endB.z;
        Vec3Sub(&offset, &pointB, &pointA);
        distSq = Vec3DotProduct(&offset, &offset);
        if (distSq < (pCapsuleA->mRadius + pCapsuleB->mRadius)
                         * (pCapsuleA->mRadius + pCapsuleB->mRadius)) {
            if (paramA > 0.0f && paramA < 1.0f && paramB > 0.0f && paramB < 1.0f) {
                float dist = sqrtf(distSq);

                if (dist > 1e-8f) {
                    if (pCapsuleA->mRadius < pCapsuleB->mRadius) {
                        Vec3Scale(&offset, &offset, pCapsuleA->mRadius / dist);
                        Vec3Add(pContact, &pointA, &offset);
                    } else {
                        Vec3Scale(&offset, &offset, pCapsuleB->mRadius / dist);
                        Vec3Sub(pContact, &pointB, &offset);
                    }
                } else {
                    *pContact = pointA;
                }
                return 1;
            }
            Vec3Normalize(&axisA, &axisA);
            Vec3Normalize(&axisB, &axisB);
            count = pCapsuleB->RingPoints(&endA, &axisA, &endB, &startB, &axisB, points, 32,
                                          pCapsuleA->mRadius);
            count += pCapsuleB->RingPoints(&startA, &axisA, &endB, &startB, &axisB,
                                           &points[count], 32 - count, pCapsuleA->mRadius);
            count += pCapsuleA->RingPoints(&endB, &axisB, &endA, &startA, &axisA,
                                           &points[count], 32 - count, pCapsuleB->mRadius);
            count += pCapsuleA->RingPoints(&startB, &axisB, &endA, &startA, &axisA,
                                           &points[count], 32 - count, pCapsuleB->mRadius);
            if (count != 0) {
                for (i = 1; i < count; i++) {
                    Vec3Add(&points[0], &points[0], &points[i]);
                }
                Vec3Scale(pContact, &points[0], 1.0f / (float)count);
                return 1;
            }
        }
    } else {
        float along;
        float dist;

        Vec3Normalize(&axisA, &axisA);
        Vec3Sub(&pointA, &startB, &startA);
        along = Vec3DotProduct(&pointA, &axisA);
        Vec3Scale(&pointB, &axisA, along);
        Vec3Add(&pointB, &pointB, &startA);
        Vec3Sub(&offset, &startB, &pointB);
        dist = Vec3Magnitude(&offset);
        if (dist < pCapsuleA->mRadius + pCapsuleB->mRadius) {
            float length = Vec3Magnitude(&pCapsuleA->mHalfAxis);
            float low;
            float high;

            length = length + length;
            Vec3Sub(&pointA, &endB, &startA);
            high = Vec3DotProduct(&pointA, &axisA);
            low = _Clamp(along, 0.0f, length);
            high = _Clamp(high, 0.0f, length);
            if (low != high) {
                Vec3Scale(&pointB, &axisA, (low + high) * 0.5f);
                Vec3Add(&pointB, &pointB, &startA);
                Vec3Scale(&offset, &offset, pCapsuleA->mRadius / dist);
                Vec3Add(pContact, &pointB, &offset);
                return 1;
            }
        }
    }
    return 0;
}

void SphereShape::Draw(const float pMatrix[4][4], int red, int green, int blue)
{
    Vec3_801DE1E0 a;
    Vec3_801DE1E0 b;
    float step = 0.31415927f;
    float angle = step;
    float prevSin = MathSinf(0.0f) * mRadius;
    float prevCos = MathCosf(0.0f) * mRadius;
    float end = angle + 6.2831855f;

    do {
        float s = MathSinf(angle) * mRadius;
        float c = MathCosf(angle) * mRadius;

        angle += step;
        a = mCenter;
        b = mCenter;
        a.x += s;
        a.y += c;
        b.x += prevSin;
        b.y += prevCos;
        MatPush();
        MatLoad((float *)pMatrix);
        Vec3Mat34Mul(&a, &a);
        Vec3Mat34Mul(&b, &b);
        MatPop();
        DispatchCollisionDebugLine(&a, &b, red, green, blue);
        a = mCenter;
        b = mCenter;
        a.x += s;
        a.z += c;
        b.x += prevSin;
        b.z += prevCos;
        MatPush();
        MatLoad((float *)pMatrix);
        Vec3Mat34Mul(&a, &a);
        Vec3Mat34Mul(&b, &b);
        MatPop();
        DispatchCollisionDebugLine(&a, &b, red, green, blue);
        a = mCenter;
        b = mCenter;
        a.y += s;
        a.z += c;
        b.y += prevSin;
        b.z += prevCos;
        prevSin = s;
        prevCos = c;
        MatPush();
        MatLoad((float *)pMatrix);
        Vec3Mat34Mul(&a, &a);
        Vec3Mat34Mul(&b, &b);
        MatPop();
        DispatchCollisionDebugLine(&a, &b, red, green, blue);
    } while (angle <= end);
}

void CapsuleShape::Draw(const float pMatrix[4][4], int red, int green, int blue)
{
    float step = 0.62831855f;
    Vec3_801DE1E0 side;
    Vec3_801DE1E0 up;
    Vec3_801DE1E0 ring;
    Vec3_801DE1E0 prevRing;
    Vec3_801DE1E0 top;
    Vec3_801DE1E0 prevTop;
    Vec3_801DE1E0 bottom;
    Vec3_801DE1E0 prevBottom;
    Vec3_801DE1E0 sideOffset;
    Vec3_801DE1E0 prevSideOffset;
    Vec3_801DE1E0 upOffset;
    Vec3_801DE1E0 prevUpOffset;
    float angle;

    float prevSin;
    float prevCos;
    float absX;
    float absY;

    side.x = side.y = side.z = 0.0f;
    absX = fabsf(mHalfAxis.x);
    absY = fabsf(mHalfAxis.y);
    if (absX >= absY) {
        if (absX >= fabsf(mHalfAxis.z)) {
            side.y = 1.0f;
        } else {
            side.x = 1.0f;
        }
    } else {
        if (absY >= fabsf(mHalfAxis.z)) {
            side.x = 1.0f;
        } else {
            side.x = 1.0f;
        }
    }
    Vec3CrossProduct(&up, &mHalfAxis, &side);
    angle = step;
    Vec3CrossProduct(&side, &mHalfAxis, &up);
    Vec3Normalize(&side, &side);
    Vec3Normalize(&up, &up);
    prevSin = MathSinf(0.0f) * mRadius;
    prevCos = MathCosf(0.0f) * mRadius;
    while (angle <= step + 6.2831855f) {
        float s = MathSinf(angle) * mRadius;
        float c = MathCosf(angle) * mRadius;

        angle += step;
        Vec3Scale(&sideOffset, &side, s);
        Vec3Scale(&prevSideOffset, &side, prevSin);
        prevSin = s;
        Vec3Scale(&upOffset, &up, c);
        Vec3Scale(&prevUpOffset, &up, prevCos);
        prevCos = c;
        Vec3Add(&ring, &mCenter, &sideOffset);
        Vec3Add(&ring, &ring, &upOffset);
        Vec3Add(&prevRing, &mCenter, &prevSideOffset);
        Vec3Add(&prevRing, &prevRing, &prevUpOffset);
        Vec3Add(&top, &ring, &mHalfAxis);
        Vec3Add(&prevTop, &prevRing, &mHalfAxis);
        Vec3Sub(&bottom, &ring, &mHalfAxis);
        Vec3Sub(&prevBottom, &prevRing, &mHalfAxis);
        MatPush();
        MatLoad((float *)pMatrix);
        Vec3Mat34Mul(&top, &top);
        Vec3Mat34Mul(&prevTop, &prevTop);
        Vec3Mat34Mul(&bottom, &bottom);
        Vec3Mat34Mul(&prevBottom, &prevBottom);
        MatPop();
        DispatchCollisionDebugLine(&top, &prevTop, red, green, blue);
        DispatchCollisionDebugLine(&bottom, &prevBottom, red, green, blue);
        DispatchCollisionDebugLine(&top, &bottom, red, green, blue);
    }
}

void BoxShape::Draw(const float pMatrix[4][4], int red, int green, int blue)
{
    Vec3_801DE1E0 corners[8];

    corners[0].x = -mHalfSize.x;
    corners[0].y = -mHalfSize.y;
    corners[0].z = mHalfSize.z;
    corners[1].x = mHalfSize.x;
    corners[1].y = -mHalfSize.y;
    corners[1].z = mHalfSize.z;
    corners[2].x = mHalfSize.x;
    corners[2].y = mHalfSize.y;
    corners[2].z = mHalfSize.z;
    corners[3].x = -mHalfSize.x;
    corners[3].y = mHalfSize.y;
    corners[3].z = mHalfSize.z;
    corners[4].x = -mHalfSize.x;
    corners[4].y = -mHalfSize.y;
    corners[4].z = -mHalfSize.z;
    corners[5].x = mHalfSize.x;
    corners[5].y = -mHalfSize.y;
    corners[5].z = -mHalfSize.z;
    corners[6].x = mHalfSize.x;
    corners[6].y = mHalfSize.y;
    corners[6].z = -mHalfSize.z;
    corners[7].x = -mHalfSize.x;
    corners[7].y = mHalfSize.y;
    corners[7].z = -mHalfSize.z;

    Vec3Add(&corners[0], &corners[0], &mCenter);
    Vec3Add(&corners[1], &corners[1], &mCenter);
    Vec3Add(&corners[2], &corners[2], &mCenter);
    Vec3Add(&corners[3], &corners[3], &mCenter);
    Vec3Add(&corners[4], &corners[4], &mCenter);
    Vec3Add(&corners[5], &corners[5], &mCenter);
    Vec3Add(&corners[6], &corners[6], &mCenter);
    Vec3Add(&corners[7], &corners[7], &mCenter);
    MatPush();
    MatLoad((float *)pMatrix);
    Vec3Mat34Mul(&corners[0], &corners[0]);
    Vec3Mat34Mul(&corners[1], &corners[1]);
    Vec3Mat34Mul(&corners[2], &corners[2]);
    Vec3Mat34Mul(&corners[3], &corners[3]);
    Vec3Mat34Mul(&corners[4], &corners[4]);
    Vec3Mat34Mul(&corners[5], &corners[5]);
    Vec3Mat34Mul(&corners[6], &corners[6]);
    Vec3Mat34Mul(&corners[7], &corners[7]);
    MatPop();
    DispatchCollisionDebugLine(&corners[0], &corners[1], red, green, blue);
    DispatchCollisionDebugLine(&corners[1], &corners[2], red, green, blue);
    DispatchCollisionDebugLine(&corners[2], &corners[3], red, green, blue);
    DispatchCollisionDebugLine(&corners[3], &corners[0], red, green, blue);
    DispatchCollisionDebugLine(&corners[4], &corners[5], red, green, blue);
    DispatchCollisionDebugLine(&corners[5], &corners[6], red, green, blue);
    DispatchCollisionDebugLine(&corners[6], &corners[7], red, green, blue);
    DispatchCollisionDebugLine(&corners[7], &corners[4], red, green, blue);
    DispatchCollisionDebugLine(&corners[0], &corners[4], red, green, blue);
    DispatchCollisionDebugLine(&corners[1], &corners[5], red, green, blue);
    DispatchCollisionDebugLine(&corners[2], &corners[6], red, green, blue);
    DispatchCollisionDebugLine(&corners[3], &corners[7], red, green, blue);
}
