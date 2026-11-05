/* Partial source for vprintf.c (C library): formatted output to the standard output stream. */

#include "engine/Reent_802622DC.h"
#include <stdarg.h>

int fn_80262B5C (File_80262B5C *fp, const char *fmt, va_list ap);

int
vprintf (const char *fmt, va_list ap)
{
  return fn_80262B5C (lbl_803EC56C->mUnknown8, fmt, ap);
}
