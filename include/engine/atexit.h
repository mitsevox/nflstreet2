#ifndef ENGINE_ATEXIT_H
#define ENGINE_ATEXIT_H

#ifdef __cplusplus
extern "C" {
#endif

int atexit (void (*fn) (void));

#ifdef __cplusplus
}
#endif

#endif
