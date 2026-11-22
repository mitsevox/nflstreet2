/* Rigid-body physics: a point constraint that holds two bodies together at an anchor point
   (the game builds one for each "constraint" in an object's physics data). */

#include "engine/rigidbody.h"
#include "game/Vec3Magnitude.h"

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
    Vec3Mat34Mul(&pointA, &mAnchorA);
    MatLoad(pMatrixB);
    Vec3Mat34Mul(&pointB, &mAnchorB);
    GetBodyPointVelocity(mpBodyA, &pointA, &velA);
    GetBodyPointVelocity(mpBodyB, &pointB, &velB);
    Vec3Sub(&error, &velB, &velA);
    Vec3Sub(&delta, &pointB, &pointA);
    Vec3Scale(&delta, &delta, 1.0f);
    Vec3Add(&error, &error, &delta);
    length = Vec3Magnitude(&error);
    if (!(length <= 1e-06f)) {
        Vec3Scale(&normal, &error, 1.0f / length);
        Vec3Sub(&armA, &pointA, &mpBodyA->mPosition);
        Vec3Sub(&armB, &pointB, &mpBodyB->mPosition);
        pInertiaA = mpBodyA->mWorldInvInertia[0];
        pInertiaB = mpBodyB->mWorldInvInertia[0];
        Vec3CrossProduct(&crossA, &armA, &normal);
        Vec3CrossProduct(&crossB, &armB, &normal);
        MatLoad(pInertiaA);
        Vec3Mat33Mul(&turnA, &crossA);
        MatLoad(pInertiaB);
        Vec3Mat33Mul(&turnB, &crossB);
        Vec3CrossProduct(&crossA, &turnA, &armA);
        Vec3CrossProduct(&crossB, &turnB, &armB);
        invMassA = mpBodyA->mInvMass;
        invMassB = mpBodyB->mInvMass;
        dotA = Vec3DotProduct(&normal, &crossA);
        Vec3Scale(&impulse, &normal, length / (invMassA + invMassB + dotA + Vec3DotProduct(&normal, &crossB)));
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
