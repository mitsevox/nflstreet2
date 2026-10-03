#ifndef _DOLPHIN_AX_H_
#define _DOLPHIN_AX_H_

#include <dolphin/types.h>
#include <dolphin/ax/AXVPB.h>

#define AX_PRIORITY_STACKS 32

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AX_AUX_DATA {
    s32* l;
    s32* r;
    s32* s;
} AX_AUX_DATA;

typedef struct AX_AUX_DATA_DPL2 {
    s32* l;
    s32* r;
    s32* ls;
    s32* rs;
} AX_AUX_DATA_DPL2;

void AXRegisterAuxACallback(void (*callback)(void*, void*), void* context);
void AXRegisterAuxBCallback(void (*callback)(void*, void*), void* context);

void AXInit(void);
void AXInitEx(u32 outputBufferMode);
void AXQuit(void);
void AXFreeVoice(AXVPB* p);
AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext);

#ifdef __cplusplus
}
#endif

#endif
