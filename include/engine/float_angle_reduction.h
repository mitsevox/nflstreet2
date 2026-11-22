#ifndef ENGINE_FLOAT_ANGLE_REDUCTION_H
#define ENGINE_FLOAT_ANGLE_REDUCTION_H

typedef struct FloatAngleReduction_t {
    /* FAKEMATCH: Volatile on the head preserves the sine and cosine callers' stack loads. */
    volatile float head;
    float tail;
} FloatAngleReduction_t;

#ifdef __cplusplus
extern "C" {
#endif

int fn_802616D4(float x, FloatAngleReduction_t *reduced);

#ifdef __cplusplus
}
#endif

#endif
