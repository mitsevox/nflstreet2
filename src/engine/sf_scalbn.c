/* Scale a binary32 value by an integral power of two, including subnormal results. */
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

#include "engine/scalbnf.h"

typedef union FloatScaleBits_t {
    float value;
    int word;
} FloatScaleBits_t;

#define GET_FLOAT_WORD(i, d) do { FloatScaleBits_t bits; bits.value = (d); (i) = bits.word; } while (0)
#define SET_FLOAT_WORD(d, i) do { FloatScaleBits_t bits; bits.word = (i); (d) = bits.value; } while (0)

static float _Scalbn_fTwo25 = 3.355443200e+07f;
static float _Scalbn_fTiny = 1.0e-30f;
static float _Scalbn_fHuge = 1.0e+30f;
static float _Scalbn_fTwoMinus25 = 2.9802322388e-08f;

/* Normalize subnormals before changing the exponent, then round on rescaling. */
float scalbnf(float x, int n)
{
	int k,ix;
	GET_FLOAT_WORD(ix,x);
        k = (ix&0x7f800000)>>23;		/* extract exponent */
        if (k==0) {				/* 0 or subnormal x */
            if ((ix&0x7fffffff)==0) return x; /* +-0 */
	    x *= _Scalbn_fTwo25;
	    GET_FLOAT_WORD(ix,x);
	    k = ((ix&0x7f800000)>>23) - 25;
            if (n< -50000) return _Scalbn_fTiny*x; 	/*underflow*/
	    }
        if (k==0xff) return x+x;		/* NaN or Inf */
        k = k+n;
        if (k >  0xfe) return copysignf(_Scalbn_fHuge,x)*_Scalbn_fHuge; /* overflow  */
        if (k > 0) 				/* normal result */
	    {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
        if (k <= -25)
            if (n > 50000) 	/* in case integer overflow in n+k */
		return copysignf(_Scalbn_fHuge,x)*_Scalbn_fHuge;	/*overflow*/
	    else return copysignf(_Scalbn_fTiny,x)*_Scalbn_fTiny;	/*underflow*/
        k += 25;				/* subnormal result */
	SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
        return x*_Scalbn_fTwoMinus25;
}
