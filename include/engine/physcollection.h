#ifndef ENGINE_PHYSCOLLECTION_H
#define ENGINE_PHYSCOLLECTION_H

#include "engine/physshape.h"
#include "engine/physaabb.h"

/* Owns pointer storage; the collision shapes themselves are borrowed. */
class ShapeCollection {
public:
    ShapeCollection(unsigned int capacity, int mask);
    virtual ~ShapeCollection();
    void AddShape(CollisionShape *pShape);
    CollisionShape *GetShape(unsigned int index);
    void UpdateWorldBounds(float matrix[4][4]);
    void DrawShapes(const float matrix[4][4], int red, int green, int blue);
    void DrawBounds(int red, int green, int blue, int worldSpace);

    unsigned int mCount;
    unsigned int mCapacity;
    CollisionShape **mpShapes;
    int mMask;
    BoundingBox mLocalBounds;
    BoundingBox mWorldBounds;
};

/* Optional line renderer for collision debug drawing; the game installs it at physics setup. */
extern "C" {
extern void (*Collision_pDebugLineProc)(Vec3_801DE1E0 *, Vec3_801DE1E0 *, int, int, int);
}

#endif
