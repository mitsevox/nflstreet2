/* Computes the tangent of a single-precision angle for game math. */

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

/* Float versions: conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include "cmath.h"
#include "engine/float_angle_reduction.h"

typedef union FloatTangentBits_t {
    float value;
    int word;
} FloatTangentBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatTangentBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

static float _Tan_fZero = 0.0f;

float tanf(float x)
{
    FloatAngleReduction_t reduced;
    float zero = _Tan_fZero;
    int magnitude;
    int quadrant;

    GET_FLOAT_WORD(magnitude, x);
    magnitude &= 0x7fffffff;

    if (magnitude <= 0x3f490fda) {
        return __kernel_tanf(x, zero, 1);
    }
    if (magnitude >= 0x7f800000) {
        return x - x;
    }

    quadrant = __ieee754_rem_pio2f(x, &reduced);
    return __kernel_tanf(reduced.head, reduced.tail, 1 - ((quadrant & 1) << 1));
}
