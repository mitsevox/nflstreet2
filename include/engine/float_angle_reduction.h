#ifndef ENGINE_FLOAT_ANGLE_REDUCTION_H
#define ENGINE_FLOAT_ANGLE_REDUCTION_H

typedef struct FloatAngleReduction_t {
    /* FAKEMATCH: Volatile on the head preserves the trigonometric wrappers' stack loads. */
    volatile float head;
    float tail;
} FloatAngleReduction_t;

#ifdef __cplusplus
extern "C" {
#endif

int __ieee754_rem_pio2f(float angle, FloatAngleReduction_t *reduced);
int __kernel_rem_pio2f(float *inputChunks, void *result, int chunkExponent,
                     int chunkCount, int precision, const int *twoOverPi);
float __kernel_tanf(float angle, float tail, int mode);

#ifdef __cplusplus
}
#endif

#endif
