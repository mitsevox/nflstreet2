/* Rounds a binary32 value toward positive infinity for the runtime math library. */
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

typedef union FloatCeilingBits_t {
    float value;
    int word;
} FloatCeilingBits_t;

#define GET_FLOAT_WORD(i, d) do { FloatCeilingBits_t bits; bits.value = (d); (i) = bits.word; } while (0)
#define SET_FLOAT_WORD(d, i) do { FloatCeilingBits_t bits; bits.word = (i); (d) = bits.value; } while (0)

static float _Ceilf_fHuge = 1.0e30f;
static float _Ceilf_fZero = 0.0f;

float ceilf(float x)
{
    int word, exponent;
    int mask;

    GET_FLOAT_WORD(word, x);
    exponent = ((word >> 23) & 0xff) - 0x7f;
    if (exponent < 23) {
        if (exponent < 0) {
            /* The addition raises inexact for a nonzero fractional value. */
            if (x + _Ceilf_fHuge > _Ceilf_fZero) {
                if (word < 0) {
                    word = 0x80000000;
                } else if (word != 0) {
                    word = 0x3f800000;
                }
            }
        } else {
            mask = 0x007fffff >> exponent;
            if ((word & mask) == 0) {
                return x;
            }
            if (x + _Ceilf_fHuge > _Ceilf_fZero) {
                if (word > 0) {
                    word += 0x00800000 >> exponent;
                }
                word &= ~mask;
            }
        }
    } else {
        if (exponent == 0x80) {
            return x + x;
        }
        return x;
    }
    SET_FLOAT_WORD(x, word);
    return x;
}
