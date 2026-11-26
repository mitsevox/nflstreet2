/* Registers process-exit callbacks in the runtime reentrancy state. */

#include "engine/atexit.h"
#include "engine/Reent_802622DC.h"
#include <stddef.h>

extern void *malloc (size_t size);

int
atexit (void (*fn) (void))
{
  RuntimeExitBlock_t *p;

  if ((p = _impure_ptr->mExitBlock) == NULL)
    _impure_ptr->mExitBlock = p = &_impure_ptr->mEmbeddedExitBlock;
  if (p->mCount >= 32)
    {
      if ((p = malloc (sizeof *p)) == NULL)
	return -1;
      p->mCount = 0;
      p->mPrevious = _impure_ptr->mExitBlock;
      _impure_ptr->mExitBlock = p;
    }
  p->mCallbacks[p->mCount++] = fn;
  return 0;
}
