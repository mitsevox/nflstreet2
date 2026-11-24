#ifndef ENGINE_FSASYNC_H
#define ENGINE_FSASYNC_H

#include <dolphin/types.h>

typedef void (*FSCallback_t)(int result);

#ifdef __cplusplus
extern "C" {
#endif
int PCreadAsyncInit(int handle, u8 *buf, u32 size, FSCallback_t callback, int offset, int mode);
#ifdef __cplusplus
}
#endif

#endif
