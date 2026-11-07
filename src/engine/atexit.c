/* Registers process-exit callbacks in the runtime reentrancy state. */

#include "engine/Reent_802622DC.h"
#include <stddef.h>

extern void *fn_80262440 (size_t size);

int
atexit (void (*fn) (void))
{
  Exit_80262310 *p;

  if ((p = lbl_803EC56C->mUnknown148) == NULL)
    lbl_803EC56C->mUnknown148 = p = &lbl_803EC56C->mUnknown14C;
  if (p->mUnknown4 >= 32)
    {
      if ((p = (Exit_80262310 *) fn_80262440 (sizeof *p)) == NULL)
	return -1;
      p->mUnknown4 = 0;
      p->mUnknown0 = lbl_803EC56C->mUnknown148;
      lbl_803EC56C->mUnknown148 = p;
    }
  p->mUnknown8[p->mUnknown4++] = fn;
  return 0;
}
