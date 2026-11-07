/* Computes single-precision magnitudes for the runtime math library. */

#include <math.h>

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

typedef union
{
    float value;
    unsigned int word;
} FloatBits_t;

#define GET_FLOAT_WORD(i,d) do { FloatBits_t gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { FloatBits_t sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)

float fabsf(float x)
{
	unsigned int ix;
	GET_FLOAT_WORD(ix,x);
	SET_FLOAT_WORD(x,ix&0x7fffffff);
        return x;
}
