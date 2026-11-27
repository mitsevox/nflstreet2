/* GCC runtime (libgcc2.c), last run of archive members 0x8025FABC-0x8025FBD4: the signed 64-bit
   comparison the compiler calls from __fixunssfdi, then the exception-handling support of L_eh:
   the default terminate handler (calls abort), the terminate entry that calls through the
   handler pointer (what __pure_virtual calls) and the per-program exception context, set up on
   first use. Each was its own libgcc2 object (L_cmpdi2, L_eh). */

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

#include <string.h>

#include "engine/libgcc2.h"

struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};

extern void abort (void) __attribute__ ((__noreturn__));

word_type
__cmpdi2 (DItype a, DItype b)
{
  DIunion au, bu;

  au.ll = a, bu.ll = b;

  if (au.s.high < bu.s.high)
    return 0;
  else if (au.s.high > bu.s.high)
    return 2;
  if ((USItype) au.s.low < (USItype) bu.s.low)
    return 0;
  else if ((USItype) au.s.low > (USItype) bu.s.low)
    return 2;
  return 1;
}

void
__default_terminate (void)
{
  abort ();
}

void (*__terminate_func) (void) = __default_terminate;

void
__terminate (void)
{
  (*__terminate_func) ();
}

static struct eh_context *eh_context_initialize (void);
static struct eh_context *eh_context_static (void);

static struct eh_context *(*get_eh_context) (void) = eh_context_initialize;

static struct eh_context *
eh_context_initialize (void)
{
  get_eh_context = eh_context_static;
  return (*get_eh_context) ();
}

static struct eh_context *
eh_context_static (void)
{
  static struct eh_context eh;
  static int initialized;
  static void *top_elt[2];

  if (! initialized)
    {
      initialized = 1;
      memset (&eh, 0, sizeof eh);
      eh.dynamic_handler_chain = top_elt;
    }
  return &eh;
}
