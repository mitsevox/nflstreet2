#ifndef ENGINE_PHYSAABB_H
#define ENGINE_PHYSAABB_H

#include "engine/vec.h"

/* Axis-aligned box. */
class BoundingBox {
public:
    BoundingBox();
    virtual ~BoundingBox();
    void SetBounds(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax);
    void SetToPoint(Vec3_801DE1E0 *pPoint);
    void ExtendToPoint(Vec3_801DE1E0 *pPoint);
    void TransformBox(float (*m)[4], BoundingBox *pOut);
    void DrawDebug(int a, int b, int c);

    Vec3_801DE1E0 mMin;
    Vec3_801DE1E0 mMax;
};

#endif
