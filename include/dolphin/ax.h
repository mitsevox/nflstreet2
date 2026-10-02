#ifndef _DOLPHIN_AX_H_
#define _DOLPHIN_AX_H_

#include <dolphin/types.h>
#include <dolphin/ax/AXVPB.h>

#define AX_PRIORITY_STACKS 32

#ifdef __cplusplus
extern "C" {
#endif

void AXInit(void);
void AXInitEx(u32 outputBufferMode);
void AXQuit(void);
void AXFreeVoice(AXVPB* p);
AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext);

#ifdef __cplusplus
}
#endif

#endif
