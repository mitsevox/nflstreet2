/* Searches the sorted file and data-entry tables used by quick-load resources. */

#include "engine/bsearch.h"

void *
bsearch (const void *key, const void *base, size_t count, size_t size,
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
