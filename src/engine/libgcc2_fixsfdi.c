/* GCC runtime (libgcc2.c), the archive member L_fixsfdi at 0x8025E80C: __fixsfdi, the float to
   signed 64-bit conversion the compiler calls for a float converted to long long. It converts
   the magnitude with __fixunssfdi and negates the result for a negative input. Its own object:
   its float 0.0 (.rodata 0x802B7264) sits four bytes before the 8-aligned doubles of
   __fixunssfdi (libgcc2_fixunssfdi.c), which one object with both could not place. */

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

DItype
__fixsfdi (SFtype a)
{
  if (a < 0)
    return - __fixunssfdi (-a);
  return __fixunssfdi (a);
}
