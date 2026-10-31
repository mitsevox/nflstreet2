#ifndef ENGINE_BODY_801E9538_H
#define ENGINE_BODY_801E9538_H

#include "engine/vec.h"

/* Accessed fields of the rigid body used by motion helpers, joints and sleep control. */
typedef struct Body_801E9538 {
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
} Body_801E9538;

#ifdef __cplusplus
extern "C" {
#endif
void fn_801E987C(Body_801E9538 *pBody);
void fn_801E9C1C(Body_801E9538 *pBody, Vec3_801DE1E0 *pVel);
void fn_801E9D64(Body_801E9538 *pBody, Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pPoint);
void fn_801E9E18(Body_801E9538 *pBody, Vec3_801DE1E0 *pPoint, Vec3_801DE1E0 *pVel);
void fn_801E9F0C(Body_801E9538 *pBody, int state);
#ifdef __cplusplus
}
#endif

#endif
