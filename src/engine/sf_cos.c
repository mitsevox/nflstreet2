/* Computes the single-precision cosine used by angle math and GX spot lighting. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

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

#include "cmath.h"
#include "engine/float_angle_reduction.h"
#include "engine/kernel_cosf.h"
#include "engine/kernel_sinf.h"

typedef union FloatCosineInputBits_t {
    float value;
    int word;
} FloatCosineInputBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatCosineInputBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

static float _Cos_fZero = 0.0f;
static const float one = 1.0f;

float cosf(float x)
{
    FloatAngleReduction_t reduced;
    float zero = _Cos_fZero;
    int magnitude;
    int quadrant;

    GET_FLOAT_WORD(magnitude, x);
    magnitude &= 0x7fffffff;

    if (magnitude <= 0x3f490fd8) {
        return __kernel_cosf(x, zero);
    }
    if (magnitude >= 0x7f800000) {
        return x - x;
    }

    quadrant = fn_802616D4(x, &reduced);
    switch (quadrant & 3) {
    case 0:
        return __kernel_cosf(reduced.head, reduced.tail);
    case 1:
        return -__kernel_sinf(reduced.head, reduced.tail, 1);
    case 2:
        return -__kernel_cosf(reduced.head, reduced.tail);
    default:
        return __kernel_sinf(reduced.head, reduced.tail, 1);
    }
}
