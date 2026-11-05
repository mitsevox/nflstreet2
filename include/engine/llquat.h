#ifndef ENGINE_LLQUAT_H
#define ENGINE_LLQUAT_H

/* Quaternion helpers in src/engine/llquat.c used outside it. */

/* The three integer Euler angles QuatToEuler writes. */
typedef struct QuatEulerAngles_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} QuatEulerAngles_t;

#ifdef __cplusplus
extern "C" {
#endif
void QuatToEuler(QuatEulerAngles_t *pOut, float *pRot);
#ifdef __cplusplus
}
#endif

#endif
