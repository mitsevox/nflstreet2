/* Comparison fragment of src/engine/llvector.c: fn_8022772C and its literal pool. */

#include <math.h>

float fn_8022772C(float *pA, float *pB)
{
    float len;
    float inv;

    len = sqrtf(pA[0] * pA[0] + pA[1] * pA[1] + pA[2] * pA[2]);
    len *= sqrtf(pB[0] * pB[0] + pB[1] * pB[1] + pB[2] * pB[2]);
    inv = 1.0f / len;
    return pA[0] * pB[0] * inv + pA[1] * pB[1] * inv + pA[2] * pB[2] * inv;
}
