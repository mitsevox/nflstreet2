#ifndef ENGINE_PHYSCONSTRAINT_H
#define ENGINE_PHYSCONSTRAINT_H

#include "engine/vec.h"

struct RigidBody_t;

/* Interface of a body constraint: one solve step. */
class Constraint {
public:
    virtual void Solve() = 0;
};

/* Point-to-point joint between two bodies. */
class PointConstraint : public Constraint {
public:
    PointConstraint(RigidBody_t *pBodyA, RigidBody_t *pBodyB, Vec3_801DE1E0 *pAnchorA,
                   Vec3_801DE1E0 *pAnchorB);
    virtual void Solve();
    virtual ~PointConstraint();

    RigidBody_t *mpBodyA;
    Vec3_801DE1E0 mAnchorA;
    RigidBody_t *mpBodyB;
    Vec3_801DE1E0 mAnchorB;
};

#endif
