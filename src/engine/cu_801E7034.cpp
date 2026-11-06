#include "engine/Collection_801E7034.h"
#include "engine/TibNew.h"

// Reserve pointer slots and start with empty local and world bounds.
Collection_801E7034::Collection_801E7034(unsigned int capacity, int mask)
    : mCount(0), mCapacity(capacity), mMask(mask)
{
    mpShapes = new (0) Shape_801E2CB4 *[capacity];
}

// Releasing the collection leaves its borrowed shapes alive.
Collection_801E7034::~Collection_801E7034()
{
    if (mpShapes) {
        delete[] mpShapes;
    }
    mpShapes = 0;
    mCapacity = 0;
    mCount = 0;
}

// The first shape seeds the bounds; later shapes extend them at both corners.
void Collection_801E7034::AddShape(Shape_801E2CB4 *pShape)
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
Shape_801E2CB4 *Collection_801E7034::GetShape(unsigned int index)
{
    return mpShapes[index];
}

// Keep the world-space box synchronized with the supplied body transform.
void Collection_801E7034::UpdateWorldBounds(float matrix[4][4])
{
    mLocalBounds.TransformBox(matrix, &mWorldBounds);
}

// Each shape supplies its own debug geometry under the body transform.
void Collection_801E7034::DrawShapes(const float matrix[4][4], int red, int green, int blue)
{
    for (unsigned char i = 0; i < mCount; i++) {
        mpShapes[i]->vfn_05(matrix, red, green, blue);
    }
}

// Show the cached world box, or the individual and combined local boxes.
void Collection_801E7034::DrawBounds(int red, int green, int blue, int worldSpace)
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
    if (lbl_803EBD78) {
        lbl_803EBD78(pA, pB, red, green, blue);
    }
}
