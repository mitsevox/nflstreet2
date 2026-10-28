#ifndef ENGINE_CU_801E8478_H
#define ENGINE_CU_801E8478_H

#include "engine/vec.h"

struct Body_801E9538;

/* Constraint interface. */
class Class_801E850C {
public:
    virtual void vfn_01() = 0;
};

/* Point-to-point joint between two bodies. */
class Class_801E8478 : public Class_801E850C {
public:
    Class_801E8478(Body_801E9538 *pBodyA, Body_801E9538 *pBodyB, Vec3_801DE1E0 *pAnchorA,
                   Vec3_801DE1E0 *pAnchorB);
    virtual void vfn_01();
    virtual ~Class_801E8478();

    Body_801E9538 *mpBodyA;
    Vec3_801DE1E0 mAnchorA;
    Body_801E9538 *mpBodyB;
    Vec3_801DE1E0 mAnchorB;
};

#endif
