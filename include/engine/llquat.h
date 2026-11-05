#ifndef ENGINE_LLQUAT_H
#define ENGINE_LLQUAT_H

/* Quaternion helpers in src/engine/llquat.c used outside it. */

/* The three integer Euler angles QuatToEuler writes. */
typedef struct Angles_801EBC18 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} Angles_801EBC18;

#ifdef __cplusplus
extern "C" {
#endif
void QuatToEuler(Angles_801EBC18 *pOut, float *pRot);
#ifdef __cplusplus
}
#endif

#endif
