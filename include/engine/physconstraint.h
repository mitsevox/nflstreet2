#ifndef ENGINE_PHYSCONSTRAINT_H
#define ENGINE_PHYSCONSTRAINT_H

#include "engine/vec.h"

class RigidBody;

/* Interface of a body constraint: one solve step. */
class Constraint {
public:
    virtual void Solve(float dt) = 0;
};

/* Point-to-point joint between two bodies. */
class PointConstraint : public Constraint {
public:
    PointConstraint(RigidBody *pBodyA, RigidBody *pBodyB, Vec3_801DE1E0 *pAnchorA,
                   Vec3_801DE1E0 *pAnchorB);
    virtual void Solve(float dt);
    virtual ~PointConstraint();

    RigidBody *mpBodyA;
    Vec3_801DE1E0 mAnchorA;
    RigidBody *mpBodyB;
    Vec3_801DE1E0 mAnchorB;
};

#endif
