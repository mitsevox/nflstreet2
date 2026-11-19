/* Rigid-body physics: a point constraint that holds two bodies together at an anchor point
   (the game builds one for each "constraint" in an object's physics data). */

#include "engine/rigidbody.h"
#include "game/fn_802270D4.h"

#include "engine/physconstraint.h"
#include "engine/llmatrix.h"

PointConstraint::PointConstraint(RigidBody *pBodyA, RigidBody *pBodyB,
                               Vec3_801DE1E0 *pAnchorA, Vec3_801DE1E0 *pAnchorB)
    : mpBodyA(pBodyA), mAnchorA(*pAnchorA), mpBodyB(pBodyB), mAnchorB(*pAnchorB)
{
}

PointConstraint::~PointConstraint()
{
    mpBodyA = 0;
    mpBodyB = 0;
}

void PointConstraint::Solve(float dt)
{
    Vec3_801DE1E0 pointA;
    Vec3_801DE1E0 pointB;
    Vec3_801DE1E0 velA;
    Vec3_801DE1E0 velB;
    Vec3_801DE1E0 error;
    Vec3_801DE1E0 delta;
    Vec3_801DE1E0 normal;
    Vec3_801DE1E0 armA;
    Vec3_801DE1E0 armB;
    Vec3_801DE1E0 crossA;
    Vec3_801DE1E0 crossB;
    Vec3_801DE1E0 turnA;
    Vec3_801DE1E0 turnB;
    Vec3_801DE1E0 impulse;
    float *pMatrixA;
    float *pMatrixB;
    float *pInertiaA;
    float *pInertiaB;
    float length;
    float invMassA;
    float invMassB;
    float dotA;

    MatPush();
    pMatrixA = mpBodyA->mTransform[0];
    pMatrixB = mpBodyB->mTransform[0];
    MatLoad(pMatrixA);
    fn_80227CC0(&pointA, &mAnchorA);
    MatLoad(pMatrixB);
    fn_80227CC0(&pointB, &mAnchorB);
    GetBodyPointVelocity(mpBodyA, &pointA, &velA);
    GetBodyPointVelocity(mpBodyB, &pointB, &velB);
    fn_802276B4(&error, &velB, &velA);
    fn_802276B4(&delta, &pointB, &pointA);
    fn_80227264(&delta, &delta, 1.0f);
    fn_8022765C(&error, &error, &delta);
    length = fn_802270D4(&error);
    if (!(length <= 1e-06f)) {
        fn_80227264(&normal, &error, 1.0f / length);
        fn_802276B4(&armA, &pointA, &mpBodyA->mPosition);
        fn_802276B4(&armB, &pointB, &mpBodyB->mPosition);
        pInertiaA = mpBodyA->mWorldInvInertia[0];
        pInertiaB = mpBodyB->mWorldInvInertia[0];
        fn_802277DC(&crossA, &armA, &normal);
        fn_802277DC(&crossB, &armB, &normal);
        MatLoad(pInertiaA);
        fn_80227C2C(&turnA, &crossA);
        MatLoad(pInertiaB);
        fn_80227C2C(&turnB, &crossB);
        fn_802277DC(&crossA, &turnA, &armA);
        fn_802277DC(&crossB, &turnB, &armB);
        invMassA = mpBodyA->mInvMass;
        invMassB = mpBodyB->mInvMass;
        dotA = fn_80227704(&normal, &crossA);
        fn_80227264(&impulse, &normal, length / (invMassA + invMassB + dotA + fn_80227704(&normal, &crossB)));
        ApplyBodyImpulseAtPoint(mpBodyA, &impulse, &pointA);
        impulse.x = -impulse.x;
        impulse.y = -impulse.y;
        impulse.z = -impulse.z;
        ApplyBodyImpulseAtPoint(mpBodyB, &impulse, &pointB);
        UpdateBodyDerivedState(mpBodyA);
        UpdateBodyDerivedState(mpBodyB);
    }
    MatPop();
}
