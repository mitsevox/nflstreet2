/* Rigid-body physics: a body's construction and state-vector interface for the integrator, the
   rebuild of its derived motion (pose matrix, world inverse inertia, velocities), its pose
   setters, and the motion helpers (momentum and velocity setters, forces and impulses at a point,
   point velocity and the motion state), used by the game's physics objects and by the collision
   response. */

#include "engine/rigidbody.h"
#include "engine/physcollection.h"
#include "engine/llmatrix.h"
#include "game/fn_802270D4.h"
#include "libc/string.h"

extern "C" {
void QuatMultiply(Vec4_801DE1E0 *pOut, Vec4_801DE1E0 *pA, Vec4_801DE1E0 *pB);
void QuatScale(Vec4_801DE1E0 *pOut, Vec4_801DE1E0 *pQuat, float scale);
void QuatNormalize(Vec4_801DE1E0 *pOut, Vec4_801DE1E0 *pQuat);
void QuatToMatrix(float *pMatrix, Vec4_801DE1E0 *pQuat);
}

// A body of positive mass starts awake with the inverse of its mass and of its principal inertia
// moments; a body of zero mass is immovable. Pose and momenta start at rest at the origin.
RigidBody::RigidBody(Vec3_801DE1E0 *pInertia, ShapeCollection *pShapes, void *pOwner, float mass,
                     float restLimit)
{
    mRestLimit = restLimit;
    mUnknown04C = 0.0f;
    mUnknown050 = 0.0f;
    mState = (mass <= 0.0f) ? 0 : 2;
    mpShapes = pShapes;
    mUserData = 0;
    mpOwner = pOwner;
    mInvMass = (mass <= 0.0f) ? 0.0f : 1.0f / mass;
    {
        Vec3_801DE1E0 &position = mPosition;
        Vec3_801DE1E0 &linearMomentum = mLinearMomentum;
        Vec3_801DE1E0 &angularMomentum = mAngularMomentum;
        Vec3_801DE1E0 &linearVelocity = mLinearVelocity;
        Vec3_801DE1E0 &angularVelocity = mAngularVelocity;
        Vec3_801DE1E0 &force = mForce;
        Vec3_801DE1E0 &torque = mTorque;
        position.x = position.y = position.z = 0.0f;
        linearMomentum.x = linearMomentum.y = linearMomentum.z = 0.0f;
        angularMomentum.x = angularMomentum.y = angularMomentum.z = 0.0f;
        linearVelocity.x = linearVelocity.y = linearVelocity.z = 0.0f;
        angularVelocity.x = angularVelocity.y = angularVelocity.z = 0.0f;
        force.x = force.y = force.z = 0.0f;
        torque.x = torque.y = torque.z = 0.0f;
    }
    mOrientation.x = 0.0f;
    mOrientation.y = 0.0f;
    mOrientation.z = 0.0f;
    mOrientation.w = 1.0f;
    memset(mInvInertia, 0, sizeof(mInvInertia));
    if (mass > 0.0f) {
        mInvInertia[0][0] = 1.0f / pInertia->x;
        mInvInertia[1][1] = 1.0f / pInertia->y;
        mInvInertia[2][2] = 1.0f / pInertia->z;
    }
    UpdateBodyDerivedState(this);
}

// Releasing a body leaves its shape collection alive.
RigidBody::~RigidBody()
{
}

// The integrator's state vector is the 13 floats from the orientation to the angular momentum.
int RigidBody::GetState(float *pState)
{
    // FAKEMATCH: the size goes through a local so the copy is the target's memcpy library call.
    int count = 13;
    memcpy(pState, &mOrientation, count * sizeof(float));
    return count;
}

// Take an advanced state, rebuild the derived motion and move the shapes with the body.
int RigidBody::SetState(float *pState)
{
    // FAKEMATCH: the size goes through a local so the copy is the target's memcpy library call.
    int count = 13;
    memcpy(&mOrientation, pState, count * sizeof(float));
    UpdateBodyDerivedState(this);
    if (mpShapes) {
        mpShapes->UpdateWorldBounds(mTransform);
    }
    return count;
}

// Rates of the state: orientation spin from the angular velocity, then linear velocity, force and
// torque.
int RigidBody::GetDerivative(void *pStart, float *pRate)
{
    Vec4_801DE1E0 spin;
    Vec4_801DE1E0 rate;
    spin.x = mAngularVelocity.x;
    spin.y = mAngularVelocity.y;
    spin.z = mAngularVelocity.z;
    spin.w = 0.0f;
    QuatMultiply(&rate, &spin, &mOrientation);
    QuatScale(&rate, &rate, 0.5f);
    *(Vec4_801DE1E0 *)pRate = rate;
    pRate += 4;
    *(Vec3_801DE1E0 *)pRate = mLinearVelocity;
    pRate += 3;
    *(Vec3_801DE1E0 *)pRate = mForce;
    pRate += 3;
    *(Vec3_801DE1E0 *)pRate = mTorque;
    return 13;
}

extern "C" {

// Rebuild the pose matrix, the world inverse inertia and both velocities from the state.
void UpdateBodyDerivedState(RigidBody *pBody)
{
    float transpose[4][4];
    QuatNormalize(&pBody->mOrientation, &pBody->mOrientation);
    QuatToMatrix(&pBody->mTransform[0][0], &pBody->mOrientation);
    pBody->mTransform[3][3] = 1.0f;
    pBody->mTransform[3][0] = 0.0f;
    pBody->mTransform[3][1] = 0.0f;
    pBody->mTransform[3][2] = 0.0f;
    pBody->mTransform[0][3] = 0.0f;
    pBody->mTransform[1][3] = 0.0f;
    pBody->mTransform[2][3] = 0.0f;
    fn_80227264(&pBody->mLinearVelocity, &pBody->mLinearMomentum, pBody->mInvMass);
    MatPush();
    transpose[0][0] = pBody->mTransform[0][0];
    transpose[0][1] = pBody->mTransform[1][0];
    transpose[0][2] = pBody->mTransform[2][0];
    transpose[0][3] = pBody->mTransform[3][0];
    transpose[1][0] = pBody->mTransform[0][1];
    transpose[1][1] = pBody->mTransform[1][1];
    transpose[1][2] = pBody->mTransform[2][1];
    transpose[1][3] = pBody->mTransform[3][1];
    transpose[2][0] = pBody->mTransform[0][2];
    transpose[2][1] = pBody->mTransform[1][2];
    transpose[2][2] = pBody->mTransform[2][2];
    transpose[2][3] = pBody->mTransform[3][2];
    transpose[3][0] = pBody->mTransform[0][3];
    transpose[3][1] = pBody->mTransform[1][3];
    transpose[3][2] = pBody->mTransform[2][3];
    transpose[3][3] = pBody->mTransform[3][3];
    MatLoad(&pBody->mTransform[0][0]);
    MatCat(&pBody->mInvInertia[0][0]);
    MatCat(&transpose[0][0]);
    MatStore(&pBody->mWorldInvInertia[0][0]);
    fn_80227C2C(&pBody->mAngularVelocity, &pBody->mAngularMomentum);
    MatPop();
    pBody->mTransform[0][3] = pBody->mPosition.x;
    pBody->mTransform[1][3] = pBody->mPosition.y;
    pBody->mTransform[2][3] = pBody->mPosition.z;
}

// Place the body and move its shapes with it.
void SetBodyPosition(RigidBody *pBody, Vec3_801DE1E0 *pPosition)
{
    pBody->mPosition = *pPosition;
    pBody->mTransform[0][3] = pBody->mPosition.x;
    pBody->mTransform[1][3] = pBody->mPosition.y;
    pBody->mTransform[2][3] = pBody->mPosition.z;
    if (pBody->mpShapes) {
        pBody->mpShapes->UpdateWorldBounds(pBody->mTransform);
    }
}

// Turn the body and move its shapes with it.
void SetBodyOrientation(RigidBody *pBody, Vec4_801DE1E0 *pOrientation)
{
    pBody->mOrientation = *pOrientation;
    QuatToMatrix(&pBody->mTransform[0][0], &pBody->mOrientation);
    pBody->mTransform[0][3] = pBody->mPosition.x;
    pBody->mTransform[1][3] = pBody->mPosition.y;
    pBody->mTransform[2][3] = pBody->mPosition.z;
    pBody->mTransform[3][3] = 1.0f;
    pBody->mTransform[3][0] = 0.0f;
    pBody->mTransform[3][1] = 0.0f;
    pBody->mTransform[3][2] = 0.0f;
    if (pBody->mpShapes) {
        pBody->mpShapes->UpdateWorldBounds(pBody->mTransform);
    }
}

// Place and turn the body in one step.
void SetBodyPose(RigidBody *pBody, Vec3_801DE1E0 *pPosition, Vec4_801DE1E0 *pOrientation)
{
    pBody->mPosition = *pPosition;
    pBody->mOrientation = *pOrientation;
    QuatToMatrix(&pBody->mTransform[0][0], &pBody->mOrientation);
    pBody->mTransform[0][3] = pBody->mPosition.x;
    pBody->mTransform[1][3] = pBody->mPosition.y;
    pBody->mTransform[2][3] = pBody->mPosition.z;
    pBody->mTransform[3][3] = 1.0f;
    pBody->mTransform[3][0] = 0.0f;
    pBody->mTransform[3][1] = 0.0f;
    pBody->mTransform[3][2] = 0.0f;
    if (pBody->mpShapes) {
        pBody->mpShapes->UpdateWorldBounds(pBody->mTransform);
    }
}

// Supply the quaternion pose to callers that synchronize the visible object.
void GetBodyOrientation(RigidBody *pBody, Vec4_801DE1E0 *pOrientation)
{
    *pOrientation = pBody->mOrientation;
}

// Rebuild derived motion after replacing linear momentum.
void SetBodyLinearMomentum(RigidBody *pBody, Vec3_801DE1E0 *pMomentum)
{
    pBody->mLinearMomentum = *pMomentum;
    UpdateBodyDerivedState(pBody);
}

// Rebuild derived motion after replacing angular momentum.
void SetBodyAngularMomentum(RigidBody *pBody, Vec3_801DE1E0 *pMomentum)
{
    pBody->mAngularMomentum = *pMomentum;
    UpdateBodyDerivedState(pBody);
}

// A body with zero inverse mass cannot acquire linear momentum this way.
void SetBodyLinearVelocity(RigidBody *pBody, Vec3_801DE1E0 *pVelocity)
{
    if (pBody->mInvMass != 0.0f) {
        pBody->mLinearVelocity = *pVelocity;
        fn_80227264(&pBody->mLinearMomentum, pVelocity, 1.0f / pBody->mInvMass);
    }
}

// Clear the accumulated force and torque for the next integration step.
void ClearBodyForces(RigidBody *pBody)
{
    Vec3_801DE1E0 &force = pBody->mForce;
    Vec3_801DE1E0 &torque = pBody->mTorque;
    force.x = force.y = force.z = 0.0f;
    torque.x = torque.y = torque.z = 0.0f;
}

// A force away from the body origin also contributes torque.
void AddBodyForceAtPoint(RigidBody *pBody, Vec3_801DE1E0 *pForce, Vec3_801DE1E0 *pPoint)
{
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 torque;
    fn_802276B4(&offset, pPoint, &pBody->mPosition);
    fn_802277DC(&torque, &offset, pForce);
    fn_8022765C(&pBody->mForce, &pBody->mForce, pForce);
    fn_8022765C(&pBody->mTorque, &pBody->mTorque, &torque);
}

// Only states above one accept impulse changes to linear and angular momentum.
void ApplyBodyImpulseAtPoint(RigidBody *pBody, Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pPoint)
{
    if ((unsigned int)pBody->mState > 1) {
        Vec3_801DE1E0 offset;
        Vec3_801DE1E0 angularImpulse;
        fn_802276B4(&offset, pPoint, &pBody->mPosition);
        fn_802277DC(&angularImpulse, &offset, pImpulse);
        fn_8022765C(&pBody->mLinearMomentum, &pBody->mLinearMomentum, pImpulse);
        fn_8022765C(&pBody->mAngularMomentum, &pBody->mAngularMomentum, &angularImpulse);
    }
}

// Apply a pure angular impulse under the same state gate as a point impulse.
void ApplyBodyAngularImpulse(RigidBody *pBody, Vec3_801DE1E0 *pImpulse)
{
    if ((unsigned int)pBody->mState > 1) {
        fn_8022765C(&pBody->mAngularMomentum, &pBody->mAngularMomentum, pImpulse);
    }
}

// Point velocity combines translation with rotation about the body origin.
void GetBodyPointVelocity(RigidBody *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pVelocity)
{
    Vec3_801DE1E0 offset;
    fn_802276B4(&offset, pPoint, &pBody->mPosition);
    fn_802277DC(pVelocity, &pBody->mAngularVelocity, &offset);
    fn_8022765C(pVelocity, pVelocity, &pBody->mLinearVelocity);
}

// Evaluate the rotational contribution along a direction at a world-space point.
float ComputeBodyRotationalResponse(RigidBody *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pDirection)
{
    float rotationalResponse;
    if (pBody->mState != 0) {
        Vec3_801DE1E0 offset;
        Vec3_801DE1E0 response;
        fn_802276B4(&offset, pPoint, &pBody->mPosition);
        fn_802277DC(&response, &offset, pDirection);
        MatPush();
        MatLoad(&pBody->mWorldInvInertia[0][0]);
        fn_80227C2C(&response, &response);
        MatPop();
        fn_802277DC(&response, &response, &offset);
        rotationalResponse = fn_80227704(pDirection, &response);
    } else {
        rotationalResponse = 0.0f;
    }
    return rotationalResponse;
}

// Entering the sleeping state clears both momenta and their derived velocities.
void SetBodyMotionState(RigidBody *pBody, int state)
{
    if (state != pBody->mState) {
        pBody->mState = state;
        if (state == 3) {
            Vec3_801DE1E0 &linearVelocity = pBody->mLinearVelocity;
            Vec3_801DE1E0 &angularVelocity = pBody->mAngularVelocity;
            Vec3_801DE1E0 &linearMomentum = pBody->mLinearMomentum;
            Vec3_801DE1E0 &angularMomentum = pBody->mAngularMomentum;
            linearVelocity.x = linearVelocity.y = linearVelocity.z = 0.0f;
            angularVelocity.x = angularVelocity.y = angularVelocity.z = 0.0f;
            linearMomentum.x = linearMomentum.y = linearMomentum.z = 0.0f;
            angularMomentum.x = angularMomentum.y = angularMomentum.z = 0.0f;
        }
    }
}

// The body's kinetic energy of translation, zero for an immovable body.
float GetBodyKineticEnergy(RigidBody *pBody)
{
    if (pBody->mInvMass != 0.0f) {
        return fn_80227120(&pBody->mLinearVelocity) * (1.0f / pBody->mInvMass) * 0.5f;
    }
    return 0.0f;
}

}
