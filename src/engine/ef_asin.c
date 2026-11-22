/* Computes single-precision arcsine for the game's angle calculations. */
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

typedef union FloatAsinfBits_t {
    float value;
    int word;
} FloatAsinfBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatAsinfBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(out, x) do { \
    FloatAsinfBits_t bits; \
    bits.word = (x); \
    (out) = bits.value; \
} while (0)

static const float one = 1.0f;
static const float huge = 1.0e30f;
static const float pio2_hi = 1.5707962513e+00f;
static const float pio2_lo = 7.5497894159e-08f;
static const float pio4_hi = 7.8539818525e-01f;
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

static float _Asinf_fPio2High = 1.5707962513e+00f;
static float _Asinf_fPio2Low = 7.5497894159e-08f;
static float _Asinf_fHuge = 1.0e30f;
static float _Asinf_fOne = 1.0f;
static float _Asinf_fP5 = 3.4793309169e-05f;
static float _Asinf_fP4 = 7.9153501429e-04f;
static float _Asinf_fP3 = -4.0055535734e-02f;
static float _Asinf_fP2 = 2.0121252537e-01f;
static float _Asinf_fP1 = -3.2556581497e-01f;
static float _Asinf_fP0 = 1.6666667163e-01f;
static float _Asinf_fQ4 = 7.7038154006e-02f;
static float _Asinf_fQ3 = -6.8828397989e-01f;
static float _Asinf_fQ2 = 2.0209457874e+00f;
static float _Asinf_fQ1 = -2.4033949375e+00f;
static float _Asinf_fHalf = 0.5f;
static float _Asinf_fPio4High = 7.8539818525e-01f;

float asinf(float x)
{
    float t, w, p, q, c, r, s;
    int hx, ix;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix == 0x3f800000) {
        return x * _Asinf_fPio2High + x * _Asinf_fPio2Low;
    } else if (ix > 0x3f800000) {
        return (x - x) / (x - x);
    } else if (ix < 0x3f000000) {
        if (ix < 0x32000000) {
            /* Preserve the inexact probe for tiny inputs. */
            if (x + _Asinf_fHuge > _Asinf_fOne) {
                return x;
            }
        } else {
            t = x * x;
        }
        p = t * (_Asinf_fP0 + t * (_Asinf_fP1 + t * (_Asinf_fP2 + t * (_Asinf_fP3 + t * (_Asinf_fP4 + t * _Asinf_fP5)))));
        q = _Asinf_fOne + t * (_Asinf_fQ1 + t * (_Asinf_fQ2 + t * (_Asinf_fQ3 + t * _Asinf_fQ4)));
        w = p / q;
        return x + x * w;
    }

    w = _Asinf_fOne - fabsf(x);
    t = w * _Asinf_fHalf;
    p = t * (_Asinf_fP0 + t * (_Asinf_fP1 + t * (_Asinf_fP2 + t * (_Asinf_fP3 + t * (_Asinf_fP4 + t * _Asinf_fP5)))));
    q = _Asinf_fOne + t * (_Asinf_fQ1 + t * (_Asinf_fQ2 + t * (_Asinf_fQ3 + t * _Asinf_fQ4)));
    s = sqrtf(t);
    if (ix >= 0x3f79999a) {
        w = p / q;
        t = _Asinf_fPio2High - (2.0f * (s + s * w) - _Asinf_fPio2Low);
    } else {
        int iw;
        w = s;
        GET_FLOAT_WORD(iw, w);
        SET_FLOAT_WORD(w, iw & 0xfffff000);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = 2.0f * s * r - (_Asinf_fPio2Low - 2.0f * c);
        q = _Asinf_fPio4High - 2.0f * w;
        t = _Asinf_fPio4High - (p - q);
    }
    if (hx > 0) {
        return t;
    }
    return -t;
}
