#ifndef ENGINE_PHYSSHAPE_H
#define ENGINE_PHYSSHAPE_H

struct Vector_80039F5C;

/* Collision-shape interface used by queries and debug drawing. */
class CollisionShape {
public:
    virtual ~CollisionShape();
    virtual void vfn_02(void *pBounds);
    virtual float vfn_03(Vector_80039F5C *pPoint, const float matrix[4][4],
                       Vector_80039F5C *pDelta, Vector_80039F5C *pNormal,
                       Vector_80039F5C *pOut, float *pDistance, float length);
    virtual float vfn_04(Vector_80039F5C *pPoint, Vector_80039F5C *pDirection,
                         const float matrix[4][4]);
    virtual void vfn_05(const float matrix[4][4], int red, int green, int blue);

    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
};

#endif
