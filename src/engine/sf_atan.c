/* Converts a slope to a single-precision angle in radians. */
/* Float conversion by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

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
#include "cmath.h"

typedef union FloatAtanBits_t {
    float value;
    int word;
} FloatAtanBits_t;

/* FAKEMATCH: Place the three const tables in the target's small-data section. */
static const float _Atan_afHigh[] __attribute__((section(".sdata2"))) = {
    4.6364760399e-01f, 7.8539812565e-01f, 9.8279368877e-01f, 1.5707962513e+00f,
};

static const float _Atan_afLow[] __attribute__((section(".sdata2"))) = {
    5.0121582440e-09f, 3.7748947079e-08f, 3.4473217170e-08f, 7.5497894159e-08f,
};

static const float _Atan_afCoefficients[] __attribute__((section(".sdata2"))) = {
    3.3333334327e-01f, -2.0000000298e-01f, 1.4285714924e-01f, -1.1111110449e-01f,
    9.0908870101e-02f, -7.6918758452e-02f, 6.6610731184e-02f, -5.8335702866e-02f,
    4.9768779427e-02f, -3.6531571299e-02f, 1.6285819933e-02f,
};

static const float _Atan_fOneConstant = 1.0f;
static const float _Atan_fHugeConstant = 1.0e30f;

static float _Atan_fHuge = 1.0e30f;
static float _Atan_fOne = 1.0f;
static float _Atan_fTwo = 2.0f;
static float _Atan_fOneAndHalf = 1.5f;
static float _Atan_fNegativeOne = -1.0f;

#define GET_FLOAT_WORD(out, input)  \
    do {                           \
        FloatAtanBits_t bits;       \
        bits.value = (input);       \
        (out) = bits.word;          \
    } while (0)

float atanf(float x)
{
    int word, magnitude, range;
    float z, w, s1, s2;

    GET_FLOAT_WORD(word, x);
    magnitude = word & 0x7fffffff;
    if (magnitude >= 0x50800000) {
        if (magnitude > 0x7f800000) {
            return x + x;
        }
        if (word > 0) {
            return _Atan_afHigh[3] + _Atan_afLow[3];
        }
        return -_Atan_afHigh[3] - _Atan_afLow[3];
    }

    if (magnitude < 0x3ee00000) {
        if (magnitude < 0x31000000 && x + _Atan_fHuge > _Atan_fOne) {
            return x;
        }
        range = -1;
    } else {
        x = fabsf(x);
        if (magnitude < 0x3f980000) {
            if (magnitude < 0x3f300000) {
                range = 0;
                x = ((x + x) - _Atan_fOne) / (x + _Atan_fTwo);
            } else {
                range = 1;
                x = (x - _Atan_fOne) / (x + _Atan_fOne);
            }
        } else if (magnitude < 0x401c0000) {
            range = 2;
            x = (x - _Atan_fOneAndHalf) / (_Atan_fOne + x * _Atan_fOneAndHalf);
        } else {
            range = 3;
            x = _Atan_fNegativeOne / x;
        }
    }

    z = x * x;
    w = z * z;
    /* Evaluate the odd and even powers of the squared argument separately. */
    s1 = z * (_Atan_afCoefficients[0] +
         w * (_Atan_afCoefficients[2] +
         w * (_Atan_afCoefficients[4] +
         w * (_Atan_afCoefficients[6] +
         w * (_Atan_afCoefficients[8] + w * _Atan_afCoefficients[10])))));
    s2 = w * (_Atan_afCoefficients[1] +
         w * (_Atan_afCoefficients[3] +
         w * (_Atan_afCoefficients[5] +
         w * (_Atan_afCoefficients[7] + w * _Atan_afCoefficients[9]))));
    if (range < 0) {
        return x - x * (s1 + s2);
    }
    z = _Atan_afHigh[range] - ((x * (s1 + s2) - _Atan_afLow[range]) - x);
    return word < 0 ? -z : z;
}
