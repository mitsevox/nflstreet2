/* Numeric runtime support (math_support.c): supplies rounding, remainder and logarithms
   for conversion of numbers to text by the formatted-output library. */

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

#include "engine/math_support.h"

typedef int int32_t;
typedef unsigned int u_int32_t;

typedef union DoubleWords_t {
    double value;
    struct {
        u_int32_t high;
        u_int32_t low;
    } words;
} DoubleWords_t;

#define EXTRACT_WORDS(hi, lo, x) do { DoubleWords_t bits; bits.value = (x); (hi) = bits.words.high; (lo) = bits.words.low; } while (0)
#define INSERT_WORDS(x, hi, lo) do { DoubleWords_t bits; bits.words.high = (hi); bits.words.low = (lo); (x) = bits.value; } while (0)
#define GET_HIGH_WORD(hi, x) do { DoubleWords_t bits; bits.value = (x); (hi) = bits.words.high; } while (0)
#define SET_HIGH_WORD(x, hi) do { DoubleWords_t bits; bits.value = (x); bits.words.high = (hi); (x) = bits.value; } while (0)

#define SN_HUGE 1.0e300
#define SN_ONE 1.0
#define SN_ZERO 0.0
#define SN_TWO54 1.80143985094819840000e+16
#define SN_LN2_HI 6.93147180369123816490e-01
#define SN_LN2_LO 1.90821492927058770002e-10
#define SN_LG1 6.666666666666735130e-01
#define SN_LG2 3.999999999940941908e-01
#define SN_LG3 2.857142874366239149e-01
#define SN_LG4 2.222219843214978396e-01
#define SN_LG5 1.818357216161805012e-01
#define SN_LG6 1.531383769920937332e-01
#define SN_LG7 1.479819860511658591e-01
#define SN_IVLN10 4.34294481903251816668e-01
#define SN_LOG10_2HI 3.01029995663611771306e-01
#define SN_LOG10_2LO 3.69423907715893078616e-13


/* Keep signed zero and nonfinite values while clearing fractional significand bits. */
double sn_floor(double x)
{
    int32_t i0,i1,j0;
    u_int32_t i,j;
    EXTRACT_WORDS(i0,i1,x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {
        if(SN_HUGE+x>0.0) {
            if(i0>=0) {i0=i1=0;}
            else if(((i0&0x7fffffff)|i1)!=0)
            { i0=0xbff00000;i1=0;}
        }
        } else {
        i = (0x000fffff)>>j0;
        if(((i0&i)|i1)==0) return x;
        if(SN_HUGE+x>0.0) {
            if(i0<0) i0 += (0x00100000)>>j0;
            i0 &= (~i); i1=0;
        }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;
        else return x;
    } else {
        i = ((u_int32_t)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x;
        if(SN_HUGE+x>0.0) {
        if(i0<0) {
            if(j0==20) i0+=1;
            else {
            j = i1+(1<<(52-j0));
            if(j<i1) i0 +=1 ;
            i1=j;
            }
        }
        i1 &= (~i);
        }
    }
    INSERT_WORDS(x,i0,i1);
    return x;
}

static const double _MathSupport_adSignedZero[2] = {0.0, -0.0};

/* Significand subtraction preserves the dividend sign, including an exact zero result. */
double sn_fmod(double x, double y)
{
    int32_t n,hx,hy,hz,ix,iy,sx,i;
    u_int32_t lx,ly,lz;

    EXTRACT_WORDS(hx,lx,x);
    EXTRACT_WORDS(hy,ly,y);
    sx = hx&0x80000000;
    hx ^=sx;
    hy &= 0x7fffffff;


    if((hy|ly)==0||(hx>=0x7ff00000)||
      ((hy|((ly|-ly)>>31))>0x7ff00000))
        return (x*y)/(x*y);
    if(hx<=hy) {
        if((hx<hy)||(lx<ly)) return x;
        if(lx==ly)
        return _MathSupport_adSignedZero[(u_int32_t)sx>>31];
    }


    if(hx<0x00100000) {
        if(hx==0) {
        for (ix = -1043, i=lx; i>0; i<<=1) ix -=1;
        } else {
        for (ix = -1022,i=(hx<<11); i>0; i<<=1) ix -=1;
        }
    } else ix = (hx>>20)-1023;


    if(hy<0x00100000) {
        if(hy==0) {
        for (iy = -1043, i=ly; i>0; i<<=1) iy -=1;
        } else {
        for (iy = -1022,i=(hy<<11); i>0; i<<=1) iy -=1;
        }
    } else iy = (hy>>20)-1023;


    if(ix >= -1022)
        hx = 0x00100000|(0x000fffff&hx);
    else {
        n = -1022-ix;
        if(n<=31) {
            hx = (hx<<n)|(lx>>(32-n));
            lx <<= n;
        } else {
        hx = lx<<(n-32);
        lx = 0;
        }
    }
    if(iy >= -1022)
        hy = 0x00100000|(0x000fffff&hy);
    else {
        n = -1022-iy;
        if(n<=31) {
            hy = (hy<<n)|(ly>>(32-n));
            ly <<= n;
        } else {
        hy = ly<<(n-32);
        ly = 0;
        }
    }


    n = ix - iy;
    while(n--) {
        hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
        if(hz<0){hx = hx+hx+(lx>>31); lx = lx+lx;}
        else {
            if((hz|lz)==0)
            return _MathSupport_adSignedZero[(u_int32_t)sx>>31];
            hx = hz+hz+(lz>>31); lx = lz+lz;
        }
    }
    hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
    if(hz>=0) {hx=hz;lx=lz;}


    if((hx|lx)==0)
        return _MathSupport_adSignedZero[(u_int32_t)sx>>31];
    while(hx<0x00100000) {
        hx = hx+hx+(lx>>31); lx = lx+lx;
        iy -= 1;
    }
    if(iy>= -1022) {
        hx = ((hx-0x00100000)|((iy+1023)<<20));
        INSERT_WORDS(x,hx|sx,lx);
    } else {
        n = -1022 - iy;
        if(n<=20) {
        lx = (lx>>n)|((u_int32_t)hx<<(32-n));
        hx >>= n;
        } else if (n<=31) {
        lx = (hx<<(32-n))|(lx>>n); hx = sx;
        } else {
        lx = hx>>(n-32); hx = sx;
        }
        INSERT_WORDS(x,hx|sx,lx);
        x *= SN_ONE;
    }
    return x;
}

/* Split the binary exponent from a significand near one before the logarithm expansion. */
double sn_log(double x)
{
    double hfsq,f,s,z,R,w,t1,t2,dk;
    int32_t k,hx,i,j;
    u_int32_t lx;

    EXTRACT_WORDS(hx,lx,x);

    k=0;
    if (hx < 0x00100000) {
        if (((hx&0x7fffffff)|lx)==0)
        return -SN_TWO54/SN_ZERO;
        if (hx<0) return (x-x)/SN_ZERO;
        k -= 54; x *= SN_TWO54;
        GET_HIGH_WORD(hx,x);
    }
    if (hx >= 0x7ff00000) return x+x;
    k += (hx>>20)-1023;
    hx &= 0x000fffff;
    i = (hx+0x95f64)&0x100000;
    SET_HIGH_WORD(x,hx|(i^0x3ff00000));
    k += (i>>20);
    f = x-1.0;
    if((0x000fffff&(2+hx))<3) {
        if(f==SN_ZERO) if(k==0) return SN_ZERO;  else {dk=(double)k;
                 return dk*SN_LN2_HI+dk*SN_LN2_LO;}
        R = f*f*(0.5-0.33333333333333333*f);
        if(k==0) return f-R; else {dk=(double)k;
                 return dk*SN_LN2_HI-((R-dk*SN_LN2_LO)-f);}
    }
    s = f/(2.0+f);
    dk = (double)k;
    z = s*s;
    i = hx-0x6147a;
    w = z*z;
    j = 0x6b851-hx;
    t1= w*(SN_LG2+w*(SN_LG4+w*SN_LG6));
    t2= z*(SN_LG1+w*(SN_LG3+w*(SN_LG5+w*SN_LG7)));
    i |= j;
    R = t2+t1;
    if(i>0) {
        hfsq=0.5*f*f;
        if(k==0) return f-(hfsq-s*(hfsq+R)); else
             return dk*SN_LN2_HI-((hfsq-(s*(hfsq+R)+dk*SN_LN2_LO))-f);
    } else {
        if(k==0) return f-s*(f-R); else
             return dk*SN_LN2_HI-((s*(f-R)-dk*SN_LN2_LO)-f);
    }
}

/* Move the binary exponent into the split base-ten conversion term. */
double sn_log10(double x)
{
    double y,z;
    int32_t i,k,hx;
    u_int32_t lx;

    EXTRACT_WORDS(hx,lx,x);

        k=0;
        if (hx < 0x00100000) {
            if (((hx&0x7fffffff)|lx)==0)
                return -SN_TWO54/SN_ZERO;
            if (hx<0) return (x-x)/SN_ZERO;
            k -= 54; x *= SN_TWO54;
        GET_HIGH_WORD(hx,x);
        }
    if (hx >= 0x7ff00000) return x+x;
    k += (hx>>20)-1023;
    i  = ((u_int32_t)k&0x80000000)>>31;
        hx = (hx&0x000fffff)|((0x3ff-i)<<20);
        y  = (double)(k+i);
    SET_HIGH_WORD(x,hx);
    z  = y*SN_LOG10_2LO + SN_IVLN10*sn_log(x);
    return  z+y*SN_LOG10_2HI;
}
