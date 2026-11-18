/* Rigid-body physics: a body's collection of collision shapes, which keeps their combined local
   and world bounding boxes and draws the shapes and boxes for collision debugging. */

#include "engine/physcollection.h"
#include "engine/TibNew.h"

extern "C" {
void (*Collision_pDebugLineProc)(Vec3_801DE1E0 *, Vec3_801DE1E0 *, int, int, int) = 0;
}

// Reserve pointer slots and start with empty local and world bounds.
ShapeCollection::ShapeCollection(unsigned int capacity, int mask)
    : mCount(0), mCapacity(capacity), mMask(mask)
{
    mpShapes = new (0) CollisionShape *[capacity];
}

// Releasing the collection leaves its borrowed shapes alive.
ShapeCollection::~ShapeCollection()
{
    if (mpShapes) {
        delete[] mpShapes;
    }
    mpShapes = 0;
    mCapacity = 0;
    mCount = 0;
}

// The first shape seeds the bounds; later shapes extend them at both corners.
void ShapeCollection::AddShape(CollisionShape *pShape)
{
    BoundingBox bounds;
    pShape->vfn_02(&bounds);
    mpShapes[mCount] = pShape;
    mCount++;
    if (mCount == 1) {
        mLocalBounds.SetBounds(&bounds.mMin, &bounds.mMax);
    } else {
        mLocalBounds.ExtendToPoint(&bounds.mMin);
        mLocalBounds.ExtendToPoint(&bounds.mMax);
    }
}

// Callers provide an index within the populated pointer slots.
CollisionShape *ShapeCollection::GetShape(unsigned int index)
{
    return mpShapes[index];
}

// Keep the world-space box synchronized with the supplied body transform.
void ShapeCollection::UpdateWorldBounds(float matrix[4][4])
{
    mLocalBounds.TransformBox(matrix, &mWorldBounds);
}

// Each shape supplies its own debug geometry under the body transform.
void ShapeCollection::DrawShapes(const float matrix[4][4], int red, int green, int blue)
{
    for (unsigned char i = 0; i < mCount; i++) {
        mpShapes[i]->vfn_05(matrix, red, green, blue);
    }
}

// Show the cached world box, or the individual and combined local boxes.
void ShapeCollection::DrawBounds(int red, int green, int blue, int worldSpace)
{
    if (worldSpace) {
        mWorldBounds.DrawDebug(red, green, blue);
    } else {
        for (unsigned char i = 0; i < mCount; i++) {
            BoundingBox bounds;
            mpShapes[i]->vfn_02(&bounds);
            bounds.DrawDebug(red, green, blue);
        }
        mLocalBounds.DrawDebug(red, green, blue);
    }
}

// Debug edges are optional when no line renderer is installed.
extern "C" void DispatchCollisionDebugLine(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB,
                                           int red, int green, int blue)
{
    if (Collision_pDebugLineProc) {
        Collision_pDebugLineProc(pA, pB, red, green, blue);
    }
}
