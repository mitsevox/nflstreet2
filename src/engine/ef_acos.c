/* Computes the single-precision arccosine used by the game's angle helpers. */
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
#include <math.h>

typedef union FloatArccosineBits_t {
    float value;
    int word;
} FloatArccosineBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatArccosineBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(x, in) do { \
    FloatArccosineBits_t bits; \
    bits.word = (in); \
    (x) = bits.value; \
} while (0)

static float _Acos_fZero = 0.0f;
static float _Acos_fPiRounded = 3.1415927410f;
static float _Acos_fHalfPiRounded = 1.5707963705f;
static float _Acos_fP5 = 3.4793309169e-05f;
static float _Acos_fP4 = 7.9153501429e-04f;
static float _Acos_fP3 = -4.0055535734e-02f;
static float _Acos_fP2 = 2.0121252537e-01f;
static float _Acos_fP1 = -3.2556581497e-01f;
static float _Acos_fP0 = 1.6666667163e-01f;
static float _Acos_fQ4 = 7.7038154006e-02f;
static float _Acos_fQ3 = -6.8828397989e-01f;
static float _Acos_fQ2 = 2.0209457874e+00f;
static float _Acos_fQ1 = -2.4033949375e+00f;
static float _Acos_fOne = 1.0f;
static float _Acos_fHalfPiLow = 7.5497894159e-08f;
static float _Acos_fHalfPiHigh = 1.5707962513e+00f;
static float _Acos_fHalf = 0.5f;
static float _Acos_fPi = 3.1415925026e+00f;

static const float one = 1.0f;
static const float pi = 3.1415925026e+00f;
static const float pio2_hi = 1.5707962513e+00f;
static const float pio2_lo = 7.5497894159e-08f;
static const float pS0 = 1.6666667163e-01f;
static const float pS1 = -3.2556581497e-01f;
static const float pS2 = 2.0121252537e-01f;
static const float pS3 = -4.0055535734e-02f;
static const float pS4 = 7.9153501429e-04f;
static const float pS5 = 3.4793309169e-05f;
static const float qS1 = -2.4033949375e+00f;
static const float qS2 = 2.0209457874e+00f;
static const float qS3 = -6.8828397989e-01f;
static const float qS4 = 7.7038154006e-02f;

float acosf(float x)
{
    float z, p, q, ratio, correction, root, tail, truncated;
    int word, magnitude;

    GET_FLOAT_WORD(word, x);
    magnitude = word & 0x7fffffff;
    if (magnitude == 0x3f800000) {
        float angle = _Acos_fZero;
        if (word <= 0) {
            angle = _Acos_fPiRounded;
        }
        return angle;
    }
    if (magnitude > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (magnitude < 0x3f000000) {
        if (magnitude <= 0x23000000) {
            return _Acos_fHalfPiRounded;
        }
        z = x * x;
        p = z * (_Acos_fP0 + z * (_Acos_fP1 + z * (_Acos_fP2
            + z * (_Acos_fP3 + z * (_Acos_fP4 + z * _Acos_fP5)))));
        q = _Acos_fOne + z * (_Acos_fQ1 + z * (_Acos_fQ2 + z * (_Acos_fQ3 + z * _Acos_fQ4)));
        ratio = p / q;
        return _Acos_fHalfPiHigh - (x - (_Acos_fHalfPiLow - x * ratio));
    }
    if (word < 0) {
        z = (x + _Acos_fOne) * _Acos_fHalf;
        p = z * (_Acos_fP0 + z * (_Acos_fP1 + z * (_Acos_fP2
            + z * (_Acos_fP3 + z * (_Acos_fP4 + z * _Acos_fP5)))));
        q = _Acos_fOne + z * (_Acos_fQ1 + z * (_Acos_fQ2 + z * (_Acos_fQ3 + z * _Acos_fQ4)));
        root = sqrtf(z);
        ratio = p / q;
        correction = ratio * root - _Acos_fHalfPiLow;
        return _Acos_fPi - 2.0f * (root + correction);
    } else {
        int truncatedWord;
        float unit = _Acos_fOne;

        z = (unit - x) * _Acos_fHalf;
        root = sqrtf(z);
        truncated = root;
        GET_FLOAT_WORD(truncatedWord, truncated);
        SET_FLOAT_WORD(truncated, truncatedWord & 0xfffff000);
        tail = (z - truncated * truncated) / (root + truncated);
        p = z * (_Acos_fP0 + z * (_Acos_fP1 + z * (_Acos_fP2
            + z * (_Acos_fP3 + z * (_Acos_fP4 + z * _Acos_fP5)))));
        q = unit + z * (_Acos_fQ1 + z * (_Acos_fQ2 + z * (_Acos_fQ3 + z * _Acos_fQ4)));
        ratio = p / q;
        correction = ratio * root + tail;
        return 2.0f * (truncated + correction);
    }
}
