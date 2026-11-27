/* GCC runtime (libgcc2.c), first run of archive members 0x8025E148-0x8025E80C: the static-
   constructor walk and __main, which the game's main calls first, then the 64-bit left and
   arithmetic right shifts and the signed 64-bit division the compiler calls for long long
   arithmetic, and the two link-time dummy words of L__main and L_exit. Each routine was its
   own libgcc2 object (L__main, L_ashldi3, L_ashrdi3, L_divdi3, L_exit); this file keeps the
   consecutive ones that share no .rodata. __fixsfdi (libgcc2_fixsfdi.c) follows. */

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

typedef void (*func_ptr) (void);

extern func_ptr __CTOR_LIST__[];

void
__do_global_ctors (void)
{
  unsigned long nptrs = (unsigned long) __CTOR_LIST__[0];
  unsigned i;

  if (nptrs == (unsigned long) -1)
    for (nptrs = 0; __CTOR_LIST__[nptrs + 1] != 0; nptrs++);

  for (i = nptrs; i >= 1; i--)
    __CTOR_LIST__[i] ();
}

void
__main (void)
{
  static int initialized;
  if (! initialized)
    {
      initialized = 1;
      __do_global_ctors ();
    }
}

extern int _exit_dummy_decl;
int *_exit_dummy_ref = &_exit_dummy_decl;

DItype
__ashldi3 (DItype u, word_type b)
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
      w.s.low = 0;
      w.s.high = (USItype) uu.s.low << -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.low >> bm;
      w.s.low = (USItype) uu.s.low << b;
      w.s.high = ((USItype) uu.s.high << b) | carries;
    }

  return w.ll;
}

DItype
__ashrdi3 (DItype u, word_type b)
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
      w.s.high = uu.s.high >> (sizeof (SItype) * BITS_PER_UNIT - 1);
      w.s.low = uu.s.high >> -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.high << bm;
      w.s.high = uu.s.high >> b;
      w.s.low = ((USItype) uu.s.low >> b) | carries;
    }

  return w.ll;
}

#define CLZ_TAB __clz_tab_divdi3
#define UDIVMODDI4 __udivmoddi4_divdi3
#include "engine/libgcc2_udivmoddi4.h"
#undef CLZ_TAB
#undef UDIVMODDI4

DItype
__divdi3 (DItype u, DItype v)
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
    c = ~c,
    vv.ll = __negdi2 (vv.ll);

  w = __udivmoddi4_divdi3 (uu.ll, vv.ll, (UDItype *) 0);
  if (c)
    w = __negdi2 (w);

  return w;
}

int _exit_dummy_decl = 0;
