/* Registers process-exit callbacks in the runtime reentrancy state. */

#include "engine/atexit.h"
#include "engine/Reent_802622DC.h"
#include <stddef.h>

extern void *fn_80262440 (size_t size);

int
atexit (void (*fn) (void))
{
  RuntimeExitBlock_t *p;

  if ((p = lbl_803EC56C->mExitBlock) == NULL)
    lbl_803EC56C->mExitBlock = p = &lbl_803EC56C->mEmbeddedExitBlock;
  if (p->mCount >= 32)
    {
      if ((p = fn_80262440 (sizeof *p)) == NULL)
	return -1;
      p->mCount = 0;
      p->mPrevious = lbl_803EC56C->mExitBlock;
      lbl_803EC56C->mExitBlock = p;
    }
  p->mCallbacks[p->mCount++] = fn;
  return 0;
}
