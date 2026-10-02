#ifndef _DOLPHIN_AX_H_
#define _DOLPHIN_AX_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void AXInit(void);
void AXInitEx(u32 outputBufferMode);
void AXQuit(void);

#ifdef __cplusplus
}
#endif

#endif
