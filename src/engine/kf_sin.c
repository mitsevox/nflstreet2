/* Evaluate the reduced-angle sine kernel with an optional low correction. */
/* kf_sin.c -- float version of k_sin.c
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

#include "engine/kernel_sinf.h"

typedef union FloatSineBits_t {
    float value;
    int word;
} FloatSineBits_t;

#define GET_FLOAT_WORD(i, d) do { FloatSineBits_t bits; bits.value = (d); (i) = bits.word; } while (0)

static float _SinKernel_fS6 = 1.5896910177e-10;
static float _SinKernel_fS5 = -2.5050759689e-08;
static float _SinKernel_fS4 = 2.7557314297e-06;
static float _SinKernel_fS3 = -1.9841270114e-04;
static float _SinKernel_fS2 = 8.3333337680e-03;
static float _SinKernel_fS1 = -1.6666667163e-01;
static float _SinKernel_fHalf = 5.0000000000e-01;

/* Apply the tail correction when iy is nonzero. */
float __kernel_sinf(float x, float y, int iy)
{
	float z,r,v;
	int ix;
	GET_FLOAT_WORD(ix,x);
	ix &= 0x7fffffff;			/* magnitude bits */
	if(ix<0x32000000)			/* |x| < 2**-27 */
	   {if((int)x==0) return x;}		/* generate inexact */
	z	=  x*x;
	v	=  z*x;
	r	=  _SinKernel_fS2+z*(_SinKernel_fS3+z*(_SinKernel_fS4+z*(_SinKernel_fS5+z*_SinKernel_fS6)));
	if(iy==0) return x+v*(_SinKernel_fS1+z*r);
	else      return x-((z*(y*_SinKernel_fHalf-v*r)-y)-v*_SinKernel_fS1);
}
