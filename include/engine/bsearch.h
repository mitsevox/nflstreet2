#ifndef ENGINE_BSEARCH_H
#define ENGINE_BSEARCH_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *bsearch(const void *key, const void *base, size_t count, size_t size,
              int (*compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
