/* Raises a single-precision value to a power for angle and decimal calculations. */

/*
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 *
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
#include "engine/scalbnf.h"
#include <math.h>

typedef union FloatPowerBits_t {
    float value;
    int word;
} FloatPowerBits_t;

#define GET_FLOAT_WORD(out, x) do { \
    FloatPowerBits_t bits; \
    bits.value = (x); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(x, in) do { \
    FloatPowerBits_t bits; \
    bits.word = (in); \
    (x) = bits.value; \
} while (0)

/* The rows hold the log reduction centers, then the leading and correcting offsets. */
/* FAKEMATCH: Group the rows in read-only small data to preserve their indexed loads. */
static const float _Pow_afLogIntervals[3][2] __attribute__((section(".sdata2"))) = {
    {1.0f, 1.5f}, {0.0f, 5.84960938e-01f}, {0.0f, 1.56322085e-06f}
};
static const float _Pow_fZero = 0.0f;
static const float _Pow_fOne = 1.0f;
static const float _Pow_fTwo = 2.0f;
static const float _Pow_fSubnormalScale = 16777216.0f;
static const float _Pow_fOverflowScale = 1.0e30f;
static const float _Pow_fUnderflowScale = 1.0e-30f;
static const float _Pow_fLogCoefficient1 = 6.0000002384e-01f;
static const float _Pow_fLogCoefficient2 = 4.2857143283e-01f;
static const float _Pow_fLogCoefficient3 = 3.3333334327e-01f;
static const float _Pow_fLogCoefficient4 = 2.7272811532e-01f;
static const float _Pow_fLogCoefficient5 = 2.3066075146e-01f;
static const float _Pow_fLogCoefficient6 = 2.0697501302e-01f;
static const float _Pow_fExpCoefficient1 = 1.6666667163e-01f;
static const float _Pow_fExpCoefficient2 = -2.7777778450e-03f;
static const float _Pow_fExpCoefficient3 = 6.6137559770e-05f;
static const float _Pow_fExpCoefficient4 = -1.6533901999e-06f;
static const float _Pow_fExpCoefficient5 = 4.1381369442e-08f;
static const float _Pow_fLnTwo = 6.9314718246e-01f;
static const float _Pow_fLnTwoHead = 6.93145752e-01f;
static const float _Pow_fLnTwoTail = 1.42860654e-06f;
static const float _Pow_fOverflowTail = 4.2995665694e-08f;
static const float _Pow_fTwoOverThreeLnTwo = 9.6179670095e-01f;
static const float _Pow_fTwoOverThreeLnTwoHead = 9.6179199219e-01f;
static const float _Pow_fTwoOverThreeLnTwoTail = 4.7017383622e-06f;
static const float _Pow_fInverseLnTwo = 1.4426950216e+00f;
static const float _Pow_fInverseLnTwoHead = 1.4426879883e+00f;
static const float _Pow_fInverseLnTwoTail = 7.0526075433e-06f;

float powf(float x, float y)
{
    float z, ax, z_h, z_l, p_h, p_l;
    float y1, t1, t2, r, s, t, u, v, w;
    int i, j, k, yisint, n;
    int hx, hy, ix, iy, word;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;

    if (iy == 0)
        return _Pow_fOne;
    if (ix > 0x7f800000 || iy > 0x7f800000)
        return x + y;

    /* For a negative base, classify the exponent as nonintegral, odd or even. */
    yisint = 0;
    if (hx < 0) {
        if (iy >= 0x4b800000) {
            yisint = 2;
        } else if (iy >= 0x3f800000) {
            k = (iy >> 23) - 127;
            j = iy >> (23 - k);
            if ((j << (23 - k)) == iy)
                yisint = 2 - (j & 1);
        }
    }

    if (iy == 0x7f800000) {
        if (ix == 0x3f800000)
            return y - y;
        if (ix > 0x3f800000)
            return hy >= 0 ? y : _Pow_fZero;
        return hy < 0 ? -y : _Pow_fZero;
    }
    if (iy == 0x3f800000) {
        if (hy < 0)
            return _Pow_fOne / x;
        return x;
    }
    if (hy == 0x40000000)
        return x * x;
    if (hy == 0x3f000000 && hx >= 0)
        return sqrtf(x);

    ax = fabsf(x);
    if (ix == 0x7f800000 || ix == 0 || ix == 0x3f800000) {
        z = ax;
        if (hy < 0)
            z = _Pow_fOne / z;
        if (hx < 0) {
            if (((ix - 0x3f800000) | yisint) == 0)
                z = (z - z) / (z - z);
            else if (yisint == 1)
                z = -z;
        }
        return z;
    }

    if (((((unsigned int)hx >> 31) - 1) | yisint) == 0)
        return (x - x) / (x - x);

    if (iy > 0x4d000000) {
        if (ix < 0x3f7ffff8)
            return hy < 0 ? _Pow_fOverflowScale * _Pow_fOverflowScale : _Pow_fUnderflowScale * _Pow_fUnderflowScale;
        if (ix > 0x3f800007)
            return hy > 0 ? _Pow_fOverflowScale * _Pow_fOverflowScale : _Pow_fUnderflowScale * _Pow_fUnderflowScale;

        /* Near one, use the first four terms of the logarithm directly. */
        t = x - _Pow_fOne;
        w = (t * t) * (0.5f - t * (0.333333333333f - t * 0.25f));
        u = _Pow_fInverseLnTwoHead * t;
        v = t * _Pow_fInverseLnTwoTail - w * _Pow_fInverseLnTwo;
        t1 = u + v;
        GET_FLOAT_WORD(word, t1);
        SET_FLOAT_WORD(t1, word & 0xfffff000);
        t2 = v - (t1 - u);
    } else {
        float s2, s_h, s_l, t_h, t_l;

        n = 0;
        if (ix < 0x00800000) {
            ax *= _Pow_fSubnormalScale;
            n -= 24;
            GET_FLOAT_WORD(ix, ax);
        }
        n += (ix >> 23) - 127;
        j = ix & 0x007fffff;
        ix = j | 0x3f800000;
        if (j <= 0x1cc471) {
            k = 0;
        } else if (j < 0x5db3d7) {
            k = 1;
        } else {
            k = 0;
            n++;
            ix -= 0x00800000;
        }
        SET_FLOAT_WORD(ax, ix);

        /* Reduce the mantissa about 1 or 1.5 and keep the correction term. */
        u = ax - _Pow_afLogIntervals[0][k];
        v = _Pow_fOne / (ax + _Pow_afLogIntervals[0][k]);
        s = u * v;
        s_h = s;
        GET_FLOAT_WORD(word, s_h);
        SET_FLOAT_WORD(s_h, word & 0xfffff000);
        SET_FLOAT_WORD(t_h, ((ix >> 1) | 0x20000000) + 0x0040000 + (k << 21));
        t_l = ax - (t_h - _Pow_afLogIntervals[0][k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = s * s;
        r = s2 * s2 * (_Pow_fLogCoefficient1 + s2 * (_Pow_fLogCoefficient2 +
            s2 * (_Pow_fLogCoefficient3 + s2 * (_Pow_fLogCoefficient4 +
            s2 * (_Pow_fLogCoefficient5 + s2 * _Pow_fLogCoefficient6)))));
        r += s_l * (s_h + s);
        s2 = s_h * s_h;
        t_h = 3.0f + s2 + r;
        GET_FLOAT_WORD(word, t_h);
        SET_FLOAT_WORD(t_h, word & 0xfffff000);
        t_l = r - ((t_h - 3.0f) - s2);
        u = s_h * t_h;
        v = s_l * t_h + t_l * s;
        p_h = u + v;
        GET_FLOAT_WORD(word, p_h);
        SET_FLOAT_WORD(p_h, word & 0xfffff000);
        p_l = v - (p_h - u);
        z_h = _Pow_fTwoOverThreeLnTwoHead * p_h;
        z_l = _Pow_fTwoOverThreeLnTwoTail * p_h + p_l * _Pow_fTwoOverThreeLnTwo + _Pow_afLogIntervals[2][k];

        t = (float)n;
        t1 = ((z_h + z_l) + _Pow_afLogIntervals[1][k]) + t;
        GET_FLOAT_WORD(word, t1);
        SET_FLOAT_WORD(t1, word & 0xfffff000);
        t2 = z_l - (((t1 - t) - _Pow_afLogIntervals[1][k]) - z_h);
    }

    s = _Pow_fOne;
    if (((((unsigned int)hx >> 31) - 1) | (yisint - 1)) == 0)
        s = -_Pow_fOne;

    /* Multiply the split logarithm by the split exponent. */
    GET_FLOAT_WORD(word, y);
    SET_FLOAT_WORD(y1, word & 0xfffff000);
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    GET_FLOAT_WORD(j, z);
    if (j > 0x43000000)
        return s * _Pow_fOverflowScale * _Pow_fOverflowScale;
    else if (j == 0x43000000) {
        if (p_l + _Pow_fOverflowTail > z - p_h)
            return s * _Pow_fOverflowScale * _Pow_fOverflowScale;
    } else if ((j & 0x7fffffff) > 0x43160000) {
        return s * _Pow_fUnderflowScale * _Pow_fUnderflowScale;
    } else if (j == (int)0xc3160000) {
        if (p_l <= z - p_h)
            return s * _Pow_fUnderflowScale * _Pow_fUnderflowScale;
    }

    /* Evaluate the exponential on the fractional part, then scale by 2^n. */
    i = j & 0x7fffffff;
    k = (i >> 23) - 127;
    n = 0;
    if (i > 0x3f000000) {
        n = j + (0x00800000 >> (k + 1));
        k = ((n & 0x7fffffff) >> 23) - 127;
        SET_FLOAT_WORD(t, n & ~(0x007fffff >> k));
        n = ((n & 0x007fffff) | 0x00800000) >> (23 - k);
        if (j < 0)
            n = -n;
        p_h -= t;
    }
    t = p_l + p_h;
    GET_FLOAT_WORD(word, t);
    SET_FLOAT_WORD(t, word & 0xfffff000);
    u = t * _Pow_fLnTwoHead;
    v = (p_l - (t - p_h)) * _Pow_fLnTwo + t * _Pow_fLnTwoTail;
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * (_Pow_fExpCoefficient1 + t * (_Pow_fExpCoefficient2 +
         t * (_Pow_fExpCoefficient3 + t * (_Pow_fExpCoefficient4 + t * _Pow_fExpCoefficient5))));
    r = (z * t1) / (t1 - _Pow_fTwo) - (w + z * w);
    z = _Pow_fOne - (r - z);
    GET_FLOAT_WORD(j, z);
    j += (unsigned int)n << 23;
    if ((j >> 23) <= 0)
        z = scalbnf(z, n);
    else
        SET_FLOAT_WORD(z, j);
    return s * z;
}
