/* C library: forwards formatted game diagnostics to the standard output stream. */

#include "engine/Reent_802622DC.h"
#include <stdarg.h>

int vfprintf (RuntimeFile_t *fp, const char *fmt, va_list ap);

int
vprintf (const char *fmt, va_list ap)
{
  return vfprintf (lbl_803EC56C->mUnknown8, fmt, ap);
}
