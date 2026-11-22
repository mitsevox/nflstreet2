/* Computes tangent or negative cotangent after the game math reduces an angle. */

/* kf_tan.c -- float version of k_tan.c
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <math.h>

#include "engine/float_angle_reduction.h"

typedef union FloatTangentKernelBits_t {
    float value;
    int word;
} FloatTangentKernelBits_t;

#define GET_FLOAT_WORD(out, input) do { \
    FloatTangentKernelBits_t bits; \
    bits.value = (input); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(out, input) do { \
    FloatTangentKernelBits_t bits; \
    bits.word = (input); \
    (out) = bits.value; \
} while (0)

static const float _TanKernel_fOne = 1.0f;
static const float _TanKernel_fPiOverFour = 7.8539812565e-01f;
static const float _TanKernel_fPiOverFourTail = 3.7748947079e-08f;

/* FAKEMATCH: Keep the coefficient array in the target's small-data pool. */
static const float _TanKernel_afCoefficients[] __attribute__((section(".sdata2"))) = {
    3.3333334327e-01f, 1.3333334029e-01f, 5.3968254477e-02f,
    2.1869488060e-02f, 8.8632395491e-03f, 3.5920790397e-03f,
    1.4562094584e-03f, 5.8804126456e-04f, 2.4646313977e-04f,
    7.8179444245e-05f, 7.1407252108e-05f, -1.8558637748e-05f,
    2.5907305826e-05f,
};

float __kernel_tanf(float angle, float tail, int mode)
{
    int angleWord;
    int magnitude;
    float angleHead, correction, even, sum, cubic;

    GET_FLOAT_WORD(angleWord, angle);
    magnitude = angleWord & 0x7fffffff;

    if (magnitude < 0x31800000) {
        if ((int)angle == 0) {
            if ((magnitude | (mode + 1)) == 0) {
                return _TanKernel_fOne / fabsf(angle);
            } else {
                return mode == 1 ? angle : -_TanKernel_fOne / angle;
            }
        }
    }

    if (magnitude >= 0x3f2ca140) {
        if (angleWord < 0) {
            angle = -angle;
            tail = -tail;
        }
        angleHead = _TanKernel_fPiOverFour - angle;
        sum = _TanKernel_fPiOverFourTail - tail;
        angle = angleHead + sum;
        tail = 0.0f;
    }

    angleHead = angle * angle;
    sum = angleHead * angleHead;
    /* Evaluate the odd and even coefficient chains in parallel. */
    correction = _TanKernel_afCoefficients[1] + sum * (_TanKernel_afCoefficients[3]
        + sum * (_TanKernel_afCoefficients[5] + sum * (_TanKernel_afCoefficients[7]
        + sum * (_TanKernel_afCoefficients[9] + sum * _TanKernel_afCoefficients[11]))));
    even = angleHead * (_TanKernel_afCoefficients[2] + sum * (_TanKernel_afCoefficients[4]
        + sum * (_TanKernel_afCoefficients[6] + sum * (_TanKernel_afCoefficients[8]
        + sum * (_TanKernel_afCoefficients[10] + sum * _TanKernel_afCoefficients[12])))));
    cubic = angleHead * angle;
    correction = tail + angleHead * (cubic * (correction + even) + tail);
    correction += _TanKernel_afCoefficients[0] * cubic;
    sum = angle + correction;

    if (magnitude >= 0x3f2ca140) {
        even = (float)mode;
        return (float)(1 - ((angleWord >> 30) & 2)) *
            (even - 2.0f * (angle - (sum * sum / (sum + even) - correction)));
    }

    if (mode == 1) {
        return sum;
    } else {
        /* Split the tangent and reciprocal to correct the rounded division. */
        int word;
        float reciprocal, reciprocalHead;
        angleHead = sum;
        GET_FLOAT_WORD(word, angleHead);
        SET_FLOAT_WORD(angleHead, word & 0xfffff000);
        even = correction - (angleHead - angle);
        reciprocalHead = reciprocal = -1.0f / sum;
        GET_FLOAT_WORD(word, reciprocalHead);
        SET_FLOAT_WORD(reciprocalHead, word & 0xfffff000);
        cubic = 1.0f + reciprocalHead * angleHead;
        return reciprocalHead + reciprocal * (cubic + reciprocalHead * even);
    }
}
