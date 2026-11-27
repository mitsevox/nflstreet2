/* GCC runtime (libgcc2.c), second run of archive members 0x8025E850-0x8025FA24: the float to
   unsigned 64-bit conversion, the signed 64-bit to double and to float conversions, the 64-bit
   logical right shift, the signed 64-bit remainder, the pure-virtual stub that C++ vtables point
   at, and the unsigned 64-bit division and remainder. Each routine was its own libgcc2 object
   (L_fixunssfdi, L_floatdidf, L_floatdisf, L_lshrdi3, L_moddi3, L_pure, L_udivdi3, L_umoddi3);
   this file keeps the consecutive ones up to the register save and restore routines of
   eabi.c. */

/* From GCC 2.95.3 libgcc2.c:
   Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

#include "engine/libgcc2.h"

void __terminate (void);

UDItype
__fixunssfdi (SFtype original_a)
{
  DFtype a = original_a;
  DFtype b;
  UDItype v;

  if (a < 0)
    return 0;

  b = (a / HIGH_WORD_COEFF);
  v = (USItype) b;
  v <<= WORD_SIZE;
  a -= (DFtype) v;
  if (a < 0)
    v -= (USItype) (- a);
  else
    v += (USItype) a;
  return v;
}

DFtype
__floatdidf (DItype u)
{
  DFtype d;

  d = (SItype) (u >> WORD_SIZE);
  d *= HIGH_HALFWORD_COEFF;
  d *= HIGH_HALFWORD_COEFF;
  d += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return d;
}

#define DI_SIZE (sizeof (DItype) * BITS_PER_UNIT)
#define DF_SIZE 53
#define SF_SIZE 24

SFtype
__floatdisf (DItype u)
{
  DFtype f;

  if (DF_SIZE < DI_SIZE
      && DF_SIZE > (DI_SIZE - DF_SIZE + SF_SIZE))
    {
#define REP_BIT ((USItype) 1 << (DI_SIZE - DF_SIZE))
      if (! (- ((DItype) 1 << DF_SIZE) < u
	     && u < ((DItype) 1 << DF_SIZE)))
	{
	  if ((USItype) u & (REP_BIT - 1))
	    u |= REP_BIT;
	}
    }
  f = (SItype) (u >> WORD_SIZE);
  f *= HIGH_HALFWORD_COEFF;
  f *= HIGH_HALFWORD_COEFF;
  f += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return (SFtype) f;
}

DItype
__lshrdi3 (DItype u, word_type b)
{
  DIunion w;
  word_type bm;
  DIunion uu;

  if (b == 0)
    return u;

  uu.ll = u;

  bm = (sizeof (SItype) * BITS_PER_UNIT) - b;
  if (bm <= 0)
    {
      w.s.high = 0;
      w.s.low = (USItype) uu.s.high >> -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.high << bm;
      w.s.high = (USItype) uu.s.high >> b;
      w.s.low = ((USItype) uu.s.low >> b) | carries;
    }

  return w.ll;
}

#define CLZ_TAB __clz_tab_moddi3
#define UDIVMODDI4 __udivmoddi4_moddi3
#include "engine/libgcc2_udivmoddi4.h"
#undef CLZ_TAB
#undef UDIVMODDI4

DItype
__moddi3 (DItype u, DItype v)
{
  word_type c = 0;
  DIunion uu, vv;
  DItype w;

  uu.ll = u;
  vv.ll = v;

  if (uu.s.high < 0)
    c = ~c,
    uu.ll = __negdi2 (uu.ll);
  if (vv.s.high < 0)
    vv.ll = __negdi2 (vv.ll);

  (void) __udivmoddi4_moddi3 (uu.ll, vv.ll, &w);
  if (c)
    w = __negdi2 (w);

  return w;
}

void
__pure_virtual (void)
{
  __terminate ();
}

#define CLZ_TAB __clz_tab_udivdi3
#define UDIVMODDI4 __udivmoddi4_udivdi3
#include "engine/libgcc2_udivmoddi4.h"
#undef CLZ_TAB
#undef UDIVMODDI4

UDItype
__udivdi3 (UDItype n, UDItype d)
{
  return __udivmoddi4_udivdi3 (n, d, (UDItype *) 0);
}

#define CLZ_TAB __clz_tab_umoddi3
#define UDIVMODDI4 __udivmoddi4_umoddi3
#include "engine/libgcc2_udivmoddi4.h"
#undef CLZ_TAB
#undef UDIVMODDI4

UDItype
__umoddi3 (UDItype u, UDItype v)
{
  UDItype w;

  (void) __udivmoddi4_umoddi3 (u, v, &w);

  return w;
}
