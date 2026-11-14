/* Evaluate the reduced-angle cosine kernel with a low-part correction. */
/* kf_cos.c -- float version of k_cos.c
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

#include "engine/kernel_cosf.h"

typedef union FloatCosineBits_t {
    float value;
    int word;
} FloatCosineBits_t;

#define GET_FLOAT_WORD(i, d) do { FloatCosineBits_t bits; bits.value = (d); (i) = bits.word; } while (0)
#define SET_FLOAT_WORD(d, i) do { FloatCosineBits_t bits; bits.word = (i); (d) = bits.value; } while (0)

static float _CosKernel_fOne = 1.0000000000e+00;
static float _CosKernel_fC6 = -1.1359647598e-11;
static float _CosKernel_fC5 = 2.0875723372e-09;
static float _CosKernel_fC4 = -2.7557314297e-07;
static float _CosKernel_fC3 = 2.4801587642e-05;
static float _CosKernel_fC2 = -1.3888889225e-03;
static float _CosKernel_fC1 = 4.1666667908e-02;
static float _CosKernel_fHalf = 5.0000000000e-01;
static float _CosKernel_fLargeOffset = 0.28125;

/* Keep the subtraction from one accurate by selecting an intermediate offset. */
float __kernel_cosf(float x, float y)
{
    float a, hz, z, r, qx;
    int ix;
    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if ((int)x == 0) return _CosKernel_fOne;
    }
    z = x*x;
    r = z*(_CosKernel_fC1+z*(_CosKernel_fC2+z*(_CosKernel_fC3+z*(_CosKernel_fC4+z*(_CosKernel_fC5+z*_CosKernel_fC6)))));
    if (ix < 0x3e99999a)
        return _CosKernel_fOne - (z*_CosKernel_fHalf - (z*r - x*y));
    else {
        if (ix > 0x3f480000) {
            qx = _CosKernel_fLargeOffset;
        } else {
            SET_FLOAT_WORD(qx, ix-0x01000000);
        }
        hz = z*_CosKernel_fHalf-qx;
        a = _CosKernel_fOne-qx;
        return a - (hz - (z*r-x*y));
    }
}
