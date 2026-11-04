#include "engine/Body_801E9538.h"
#include "engine/cu_801D03D0.h"
#include "game/fn_802270D4.h"

extern "C" {

// Supply the quaternion pose to callers that synchronize the visible object.
void GetBodyOrientation(Body_801E9538 *pBody, Vec4_801DE1E0 *pOrientation)
{
    *pOrientation = pBody->mUnknown054;
}

// Rebuild derived motion after replacing linear momentum.
void SetBodyLinearMomentum(Body_801E9538 *pBody, Vec3_801DE1E0 *pMomentum)
{
    pBody->mUnknown070 = *pMomentum;
    fn_801E987C(pBody);
}

// Rebuild derived motion after replacing angular momentum.
void SetBodyAngularMomentum(Body_801E9538 *pBody, Vec3_801DE1E0 *pMomentum)
{
    pBody->mUnknown07C = *pMomentum;
    fn_801E987C(pBody);
}

// A body with zero inverse mass cannot acquire linear momentum this way.
void SetBodyLinearVelocity(Body_801E9538 *pBody, Vec3_801DE1E0 *pVelocity)
{
    if (pBody->mUnknown044 != 0.0f) {
        pBody->mUnknown108 = *pVelocity;
        fn_80227264(&pBody->mUnknown070, pVelocity, 1.0f / pBody->mUnknown044);
    }
}

// Clear the accumulated force and torque for the next integration step.
void ClearBodyForces(Body_801E9538 *pBody)
{
    Vec3_801DE1E0 &force = pBody->mUnknown120;
    Vec3_801DE1E0 &torque = pBody->mUnknown12C;
    force.x = force.y = force.z = 0.0f;
    torque.x = torque.y = torque.z = 0.0f;
}

// A force away from the body origin also contributes torque.
void AddBodyForceAtPoint(Body_801E9538 *pBody, Vec3_801DE1E0 *pForce, Vec3_801DE1E0 *pPoint)
{
    Vec3_801DE1E0 offset;
    Vec3_801DE1E0 torque;
    fn_802276B4(&offset, pPoint, &pBody->mUnknown064);
    fn_802277DC(&torque, &offset, pForce);
    fn_8022765C(&pBody->mUnknown120, &pBody->mUnknown120, pForce);
    fn_8022765C(&pBody->mUnknown12C, &pBody->mUnknown12C, &torque);
}

// Only states above one accept impulse changes to linear and angular momentum.
void ApplyBodyImpulseAtPoint(Body_801E9538 *pBody, Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pPoint)
{
    if ((unsigned int)pBody->mState > 1) {
        Vec3_801DE1E0 offset;
        Vec3_801DE1E0 angularImpulse;
        fn_802276B4(&offset, pPoint, &pBody->mUnknown064);
        fn_802277DC(&angularImpulse, &offset, pImpulse);
        fn_8022765C(&pBody->mUnknown070, &pBody->mUnknown070, pImpulse);
        fn_8022765C(&pBody->mUnknown07C, &pBody->mUnknown07C, &angularImpulse);
    }
}

// Apply a pure angular impulse under the same state gate as a point impulse.
void ApplyBodyAngularImpulse(Body_801E9538 *pBody, Vec3_801DE1E0 *pImpulse)
{
    if ((unsigned int)pBody->mState > 1) {
        fn_8022765C(&pBody->mUnknown07C, &pBody->mUnknown07C, pImpulse);
    }
}

// Point velocity combines translation with rotation about the body origin.
void GetBodyPointVelocity(Body_801E9538 *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pVelocity)
{
    Vec3_801DE1E0 offset;
    fn_802276B4(&offset, pPoint, &pBody->mUnknown064);
    fn_802277DC(pVelocity, &pBody->mUnknown114, &offset);
    fn_8022765C(pVelocity, pVelocity, &pBody->mUnknown108);
}

// Evaluate the rotational contribution along a direction at a world-space point.
float ComputeBodyRotationalResponse(Body_801E9538 *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pDirection)
{
    float rotationalResponse;
    if (pBody->mState != 0) {
        Vec3_801DE1E0 offset;
        Vec3_801DE1E0 response;
        fn_802276B4(&offset, pPoint, &pBody->mUnknown064);
        fn_802277DC(&response, &offset, pDirection);
        fn_801D04C4();
        fn_801D06D4(&pBody->mUnknown0C8[0][0]);
        fn_80227C2C(&response, &response);
        fn_801D0544();
        fn_802277DC(&response, &response, &offset);
        rotationalResponse = fn_80227704(pDirection, &response);
    } else {
        rotationalResponse = 0.0f;
    }
    return rotationalResponse;
}

// Entering the sleeping state clears both momenta and their derived velocities.
void SetBodyMotionState(Body_801E9538 *pBody, int state)
{
    if (state != pBody->mState) {
        pBody->mState = state;
        if (state == 3) {
            Vec3_801DE1E0 &linearVelocity = pBody->mUnknown108;
            Vec3_801DE1E0 &angularVelocity = pBody->mUnknown114;
            Vec3_801DE1E0 &linearMomentum = pBody->mUnknown070;
            Vec3_801DE1E0 &angularMomentum = pBody->mUnknown07C;
            linearVelocity.x = linearVelocity.y = linearVelocity.z = 0.0f;
            angularVelocity.x = angularVelocity.y = angularVelocity.z = 0.0f;
            linearMomentum.x = linearMomentum.y = linearMomentum.z = 0.0f;
            angularMomentum.x = angularMomentum.y = angularMomentum.z = 0.0f;
        }
    }
}

}
