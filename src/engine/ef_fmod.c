/* Computes the single-precision remainder used to wrap animation channel time. */
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

#include <math.h>

typedef union FloatRemainderBits_t {
    float value;
    int word;
} FloatRemainderBits_t;

#define GET_FLOAT_WORD(out, input) do { \
    FloatRemainderBits_t bits; \
    bits.value = (input); \
    (out) = bits.word; \
} while (0)

#define SET_FLOAT_WORD(out, input) do { \
    FloatRemainderBits_t bits; \
    bits.word = (input); \
    (out) = bits.value; \
} while (0)

static const float _Fmod_fOne = 1.0f;
/* FAKEMATCH: Place the signed-zero table in the target's read-only small-data section. */
static const float _Fmod_afSignedZero[] __attribute__((section(".sdata2"))) = {0.0f, -0.0f};

float fmodf(float x, float y)
{
    int n, hx, hy, delta, exponentX, exponentY, signX, bits;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    signX = hx & 0x80000000;
    hx ^= signX;
    hy &= 0x7fffffff;

    if (hy == 0 || hx >= 0x7f800000 || hy > 0x7f800000) {
        return (x * y) / (x * y);
    }
    if (hx < hy) {
        return x;
    }
    if (hx == hy) {
        return _Fmod_afSignedZero[(unsigned int)signX >> 31];
    }

    if (hx < 0x00800000) {
        for (exponentX = -126, bits = (int)((unsigned int)hx << 8);
             bits > 0; bits = (int)((unsigned int)bits << 1)) {
            exponentX -= 1;
        }
    } else {
        exponentX = (hx >> 23) - 127;
    }
    if (hy < 0x00800000) {
        for (exponentY = -126, bits = (int)((unsigned int)hy << 8);
             bits >= 0; bits = (int)((unsigned int)bits << 1)) {
            exponentY -= 1;
        }
    } else {
        exponentY = (hy >> 23) - 127;
    }

    if (exponentX >= -126) {
        hx = 0x00800000 | (0x007fffff & hx);
    } else {
        n = -126 - exponentX;
        hx <<= n;
    }
    if (exponentY >= -126) {
        hy = 0x00800000 | (0x007fffff & hy);
    } else {
        n = -126 - exponentY;
        hy <<= n;
    }

    /* Subtract the divisor significand one bit at a time. */
    n = exponentX - exponentY;
    for (;;) {
        int remaining = n--;
        if (remaining == 0) {
            break;
        }
        delta = hx - hy;
        if (delta < 0) {
            hx += hx;
        } else {
            if (delta == 0) {
                return _Fmod_afSignedZero[(unsigned int)signX >> 31];
            }
            hx = delta + delta;
        }
    }
    delta = hx - hy;
    if (delta >= 0) {
        hx = delta;
    }
    if (hx == 0) {
        return _Fmod_afSignedZero[(unsigned int)signX >> 31];
    }

    while (hx < 0x00800000) {
        hx += hx;
        exponentY -= 1;
    }
    if (exponentY >= -126) {
        hx = (hx - 0x00800000) | ((exponentY + 127) << 23);
        SET_FLOAT_WORD(x, hx | signX);
    } else {
        n = -126 - exponentY;
        hx >>= n;
        SET_FLOAT_WORD(x, hx | signX);
        x *= _Fmod_fOne;
    }
    return x;
}
