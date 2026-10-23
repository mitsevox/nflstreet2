/* Partial source for the floating-point range 0x80260B1C-0x802622DC (neutral file name). */

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

typedef int int32_t;
typedef unsigned int u_int32_t;

typedef union
{
  float value;
  u_int32_t word;
} ieee_float_shape_type;

#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)

static const float one = 1.0, tiny = 1.0e-30;

float fn_80260B1C(float x)
{
	float z;
	int32_t sign = (int)0x80000000;
	int32_t ix,s,q,m,t,i;
	u_int32_t r;

	GET_FLOAT_WORD(ix,x);

	if((ix&0x7f800000)==0x7f800000) {
	    return x*x+x;
	}
	if(ix<=0) {
	    if((ix&(~sign))==0) return x;
	    else if(ix<0)
		return (x-x)/(x-x);
	}
	m = (ix>>23);
	if(m==0) {
	    for(i=0;(ix&0x00800000)==0;i++) ix<<=1;
	    m -= i-1;
	}
	m -= 127;
	ix = (ix&0x007fffff)|0x00800000;
	if(m&1)
	    ix += ix;
	m >>= 1;

	ix += ix;
	q = s = 0;
	r = 0x01000000;

	while(r!=0) {
	    t = s+r;
	    if(t<=ix) {
		s    = t+r;
		ix  -= t;
		q   += r;
	    }
	    ix += ix;
	    r>>=1;
	}

	if(ix!=0) {
	    z = one-tiny;
	    if (z>=one) {
	        z = one+tiny;
		if (z>one)
		    q += 2;
		else
		    q += (q&1);
	    }
	}
	ix = (q>>1)+0x3f000000;
	ix += (m <<23);
	SET_FLOAT_WORD(z,ix);
	return z;
}

float fn_80260FC4(float x)
{
	u_int32_t ix;
	GET_FLOAT_WORD(ix,x);
	SET_FLOAT_WORD(x,ix&0x7fffffff);
        return x;
}

float fn_80261A24(float x, float y)
{
	u_int32_t ix,iy;
	GET_FLOAT_WORD(ix,x);
	GET_FLOAT_WORD(iy,y);
	SET_FLOAT_WORD(x,(ix&0x7fffffff)|(iy&0x80000000));
        return x;
}
