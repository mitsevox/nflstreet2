#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "engine/vec.h"

/* Accessed fields of the rigid body used by motion helpers, joints and sleep control. */
typedef struct RigidBody_t {
    char mUnknown000[0x44];
    float mUnknown044;
    float mUnknown048;
    char mUnknown04C[0x54 - 0x4C];
    Vec4_801DE1E0 mUnknown054;
    Vec3_801DE1E0 mUnknown064;
    Vec3_801DE1E0 mUnknown070;
    Vec3_801DE1E0 mUnknown07C;
    float mUnknown088[4][4];
    float mUnknown0C8[4][4];
    Vec3_801DE1E0 mUnknown108;
    Vec3_801DE1E0 mUnknown114;
    Vec3_801DE1E0 mUnknown120;
    Vec3_801DE1E0 mUnknown12C;
    int mState;
    int mUnknown13C;
    int mUserData;
} RigidBody_t;

#ifdef __cplusplus
extern "C" {
#endif
void fn_801E987C(RigidBody_t *pBody);
void fn_801E9C1C(RigidBody_t *pBody, Vec3_801DE1E0 *pVel);
void fn_801E9D64(RigidBody_t *pBody, Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pPoint);
void fn_801E9E18(RigidBody_t *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pVel);
void fn_801E9F0C(RigidBody_t *pBody, int state);
#ifdef __cplusplus
}
#endif

#endif
