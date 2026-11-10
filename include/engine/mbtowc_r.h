#ifndef ENGINE_MBTOWC_R_H
#define ENGINE_MBTOWC_R_H

#include "engine/Reent_802622DC.h"
#include <stddef.h>

typedef unsigned short RuntimeWideChar_t;

#ifdef __cplusplus
extern "C" {
#endif

int _mbtowc_r(Reent_802622DC *r, RuntimeWideChar_t *pwc, const char *s, size_t n, int *state);

#ifdef __cplusplus
}
#endif

#endif
