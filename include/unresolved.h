#ifndef UNRESOLVED_H
#define UNRESOLVED_H

#include "types.h"

/* Target functions whose names and source files are not yet established. */

/* Copies n bytes; overlapping ranges are handled. Returns dst. */
void *fn_801C2030(void *dst, const void *src, Uint32 n);

/* Returns a global mode value (0 initially). */
Int32 fn_801CE1E8(void);

#endif
