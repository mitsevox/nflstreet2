#ifndef ENGINE_BODY_801E9538_H
#define ENGINE_BODY_801E9538_H

#include "engine/vec.h"

/* Rigid body of the unit at 0x801E9538 (not drafted); only the fields the
   joint and sleep-controller code use are named. */
typedef struct Body_801E9538 {
    char mUnknown000[0x44];
    float mUnknown044;
    float mUnknown048;
    char mUnknown04C[0x64 - 0x4C];
    Vec3_801DE1E0 mUnknown064;
    char mUnknown070[0x7C - 0x70];
    Vec3_801DE1E0 mUnknown07C;
    float mUnknown088[4][4];
    float mUnknown0C8[4][4];
    Vec3_801DE1E0 mUnknown108;
    Vec3_801DE1E0 mUnknown114;
    char mUnknown120[0x138 - 0x120];
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
