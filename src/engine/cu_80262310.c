/* Partial source for the C library range 0x80262310-0x8026247C (neutral file name): atexit,
   a binary search and the allocation helper atexit uses. */

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

void *
fn_802623A8 (const void *key, const void *base, size_t count, size_t size,
	     int (*compare) (const void *, const void *))
{
  void *p;
  size_t lo = 0;
  size_t hi = count;
  size_t mid;
  int cmp;

  if (count == 0 || size == 0)
    return NULL;
  while (lo < hi)
    {
      mid = (lo + hi) / 2;
      p = (void *) ((char *) base + mid * size);
      cmp = compare (key, p);
      if (cmp < 0)
	hi = mid;
      else if (cmp > 0)
	lo = mid + 1;
      else
	return p;
    }
  return NULL;
}
