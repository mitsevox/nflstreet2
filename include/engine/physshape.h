#ifndef ENGINE_PHYSSHAPE_H
#define ENGINE_PHYSSHAPE_H

#include "engine/vec.h"

class BoundingBox;

/* Collision-shape interface used by queries, contact generation and debug drawing. The shape
   type selects the shape-pair test: 0 sphere, 1 capsule, 2 box. */
class CollisionShape {
public:
    CollisionShape(float friction, float bounce, int type);
    virtual ~CollisionShape();
    virtual void GetBounds(BoundingBox *pBounds) = 0;
    virtual float TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                            Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth,
                            float length) = 0;
    virtual float GetSupportWeight(Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pDirection,
                                   float (*pMatrix)[4]) = 0;
    virtual void Draw(const float pMatrix[4][4], int red, int green, int blue) = 0;
    virtual void GetMaterial(float *pFriction, float *pBounce, float (*pMatrix)[4],
                             Vec3_801DE1E0 *pPoint);

    float mFriction;
    float mBounce;
    int mType;
};

/* Capsule: the segment centre, radius and half axis in body space. */
class CapsuleShape : public CollisionShape {
public:
    CapsuleShape(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, float friction, float bounce, float radius);
    void GetBounds(BoundingBox *pBounds);
    float TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                    Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth, float length);
    float GetSupportWeight(Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pDirection, float (*pMatrix)[4]);
    void Draw(const float pMatrix[4][4], int red, int green, int blue);
    void GetWorldSegment(float (*pMatrix)[4], Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pStart,
                         Vec3_801DE1E0 *pHalfAxis);
    void ClosestSurfacePoint(Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pStart,
                             Vec3_801DE1E0 *pAxis, Vec3_801DE1E0 *pContact,
                             unsigned char *pOnSide);
    int ProjectsInside(Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pAxis,
                       Vec3_801DE1E0 *pPoint);
    unsigned int RingPoints(Vec3_801DE1E0 *pCenter, Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pEnd,
                            Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pAxis, Vec3_801DE1E0 *pOut,
                            unsigned int max, float radius);

    Vec3_801DE1E0 mCenter;
    float mRadius;
    Vec3_801DE1E0 mHalfAxis;
};

/* Sphere: centre and radius in body space. */
class SphereShape : public CollisionShape {
public:
    SphereShape(Vec3_801DE1E0 *pCenter, float friction, float bounce, float radius);
    void GetBounds(BoundingBox *pBounds);
    float TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                    Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth, float length);
    float GetSupportWeight(Vec3_801DE1E0 *, Vec3_801DE1E0 *, float (*)[4]) { return 1.0f; }
    void Draw(const float pMatrix[4][4], int red, int green, int blue);

    Vec3_801DE1E0 mCenter;
    float mRadius;
};

/* Box: centre and half extents in body space. */
class BoxShape : public CollisionShape {
public:
    BoxShape(Vec3_801DE1E0 *pCenter, float friction, float bounce, float halfX, float halfY,
             float halfZ);
    void GetBounds(BoundingBox *pBounds);
    float TestPoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pDelta,
                    Vec3_801DE1E0 *pNormal, Vec3_801DE1E0 *pContact, float *pDepth, float length);
    float GetSupportWeight(Vec3_801DE1E0 *, Vec3_801DE1E0 *, float (*)[4]) { return 0.0f; }
    void Draw(const float pMatrix[4][4], int red, int green, int blue);
    unsigned int SegmentHits(Vec3_801DE1E0 *pStart, Vec3_801DE1E0 *pEnd, Vec3_801DE1E0 *pOut,
                             unsigned int max, int withEnds);
    unsigned int QuadHits(Vec3_801DE1E0 *pQuad, Vec3_801DE1E0 *pOut, unsigned int max);
    void GetCornersIn(float (*pMatrix)[4], BoxShape *pOther, float (*pOtherMatrix)[4],
                      Vec3_801DE1E0 *pCorners);
    float ClosestSurfacePoint(Vec3_801DE1E0 *pPoint, float (*pMatrix)[4], Vec3_801DE1E0 *pLocal,
                              Vec3_801DE1E0 *pOut);

    Vec3_801DE1E0 mCenter;
    Vec3_801DE1E0 mHalfSize;
};

#endif
