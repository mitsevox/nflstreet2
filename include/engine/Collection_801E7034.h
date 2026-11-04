#ifndef ENGINE_COLLECTION_801E7034_H
#define ENGINE_COLLECTION_801E7034_H

#include "engine/Shape_801E2CB4.h"
#include "engine/cu_801EADD8.h"

/* Owns pointer storage; the collision shapes themselves are borrowed. */
class Collection_801E7034 {
public:
    Collection_801E7034(unsigned int capacity, int mask);
    virtual ~Collection_801E7034();
    void AddShape(Shape_801E2CB4 *pShape);
    Shape_801E2CB4 *GetShape(unsigned int index);
    void UpdateWorldBounds(float matrix[4][4]);
    void DrawShapes(const float matrix[4][4], int red, int green, int blue);
    void DrawBounds(int red, int green, int blue, int worldSpace);

    unsigned int mCount;
    unsigned int mCapacity;
    Shape_801E2CB4 **mpShapes;
    int mMask;
    Class_801EADD8 mLocalBounds;
    Class_801EADD8 mWorldBounds;
};

extern "C" {
extern void (*lbl_803EBD78)(Vec3_801DE1E0 *, Vec3_801DE1E0 *, int, int, int);
}

#endif
