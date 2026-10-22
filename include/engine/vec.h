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

/* Vector helpers of src/engine/cu_80226F9C.c, which defines them with float *
   parameters; they are declared with void * here, as game/fn_802270D4.h
   declares fn_802270A4, fn_802270D4 and fn_802276B4 of the same file. */
#ifdef __cplusplus
extern "C" {
#endif
float fn_80227120(void *pV);
void fn_802271F0(void *pOut, void *pV);
void fn_80227264(void *pOut, void *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
float fn_80227704(void *pA, void *pB);
void fn_802277DC(void *pOut, void *pA, void *pB);
void fn_80227930(void *pOut, void *pA, void *pB, float t);
void fn_80227C2C(void *pOut, void *pV);
void fn_80227CC0(void *pOut, void *pV);
#ifdef __cplusplus
}
#endif

#endif
