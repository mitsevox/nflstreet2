#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "engine/vec.h"

#ifdef __cplusplus
class ShapeCollection;

/* A simulated system seen as a state vector: an integrator reads the state, asks for its rate of
   change and writes the advanced state back. Each call returns the number of state floats. */
class IntegrableSystem {
public:
    virtual int GetState(float *pState) = 0;
    virtual int SetState(float *pState) = 0;
    virtual int GetDerivative(void *pStart, float *pRate) = 0;
};

/* A rigid body: its 13-float state (orientation, position, linear and angular momentum), the
   matrices and velocities derived from it, the accumulated force and torque, its sleep state and
   the collision shapes that follow it. */
class RigidBody : public IntegrableSystem {
public:
    RigidBody(Vec3_801DE1E0 *pInertia, ShapeCollection *pShapes, void *pOwner, float mass,
              float restLimit);
    virtual ~RigidBody();
    virtual int GetState(float *pState);
    virtual int SetState(float *pState);
    virtual int GetDerivative(void *pStart, float *pRate);

    float mInvInertia[4][4];
    float mInvMass;
    float mRestLimit;
    float mUnknown04C;
    float mUnknown050;
    Vec4_801DE1E0 mOrientation;
    Vec3_801DE1E0 mPosition;
    Vec3_801DE1E0 mLinearMomentum;
    Vec3_801DE1E0 mAngularMomentum;
    float mTransform[4][4];
    float mWorldInvInertia[4][4];
    Vec3_801DE1E0 mLinearVelocity;
    Vec3_801DE1E0 mAngularVelocity;
    Vec3_801DE1E0 mForce;
    Vec3_801DE1E0 mTorque;
    int mState;
    ShapeCollection *mpShapes;
    int mUserData;
    void *mpOwner;
};

/* Per-body hooks a body set calls on add, remove and each step. */
class BodyController {
public:
    virtual void AddBody(RigidBody *pBody) = 0;
    virtual void RemoveBody(RigidBody *pBody) = 0;
    virtual void UpdateSleepState(RigidBody *pBody, float dt) = 0;
};

extern "C" {
void UpdateBodyDerivedState(RigidBody *pBody);
void SetBodyPosition(RigidBody *pBody, Vec3_801DE1E0 *pPosition);
void SetBodyOrientation(RigidBody *pBody, Vec4_801DE1E0 *pOrientation);
void SetBodyPose(RigidBody *pBody, Vec3_801DE1E0 *pPosition, Vec4_801DE1E0 *pOrientation);
void SetBodyAngularMomentum(RigidBody *pBody, Vec3_801DE1E0 *pMomentum);
void ApplyBodyImpulseAtPoint(RigidBody *pBody, Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pPoint);
void GetBodyPointVelocity(RigidBody *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pVel);
void SetBodyMotionState(RigidBody *pBody, int state);
}
#endif

#endif
