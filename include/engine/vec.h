#ifndef ENGINE_VEC_H
#define ENGINE_VEC_H

typedef struct Vec3_801DE1E0 {
    float x;
    float y;
    float z;
} Vec3_801DE1E0;

typedef struct Vec4_801DE1E0 {
    float x;
    float y;
    float z;
    float w;
} Vec4_801DE1E0;

/* Vector helpers of src/engine/llvector.c, which defines them with float *
   parameters; they are declared with void * here, as game/Vec3Magnitude.h
   declares Vec2Magnitude, Vec3Magnitude and Vec3Sub of the same file. */
#ifdef __cplusplus
extern "C" {
#endif
float Vec3MagnitudeSqr(void *pV);
void Vec3Normalize(void *pOut, void *pV);
void Vec3Scale(void *pOut, void *pV, float scale);
void Vec3Add(void *pOut, void *pA, void *pB);
float Vec3DotProduct(void *pA, void *pB);
void Vec3CrossProduct(void *pOut, void *pA, void *pB);
void Vec3Lerp(void *pOut, void *pA, void *pB, float t);
void Vec3Mat33Mul(void *pOut, void *pV);
void Vec3Mat34Mul(void *pOut, void *pV);
#ifdef __cplusplus
}
#endif

#endif
