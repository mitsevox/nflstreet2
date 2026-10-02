#ifndef _DOLPHIN_AX_INTERNAL_H_
#define _DOLPHIN_AX_INTERNAL_H_

#include <dolphin/ax.h>

#ifdef __cplusplus
extern "C" {
#endif

void __AXAllocInit(void);
void __AXAllocQuit(void);
void __AXVPBInit(void);
void __AXVPBQuit(void);
void __AXSPBInit(void);
void __AXSPBQuit(void);
void __AXAuxInit(void);
void __AXAuxQuit(void);
void __AXClInit(void);
void __AXClQuit(void);
void __AXOutInit(u32 outputBufferMode);
void __AXOutQuit(void);

#ifdef __cplusplus
}
#endif

#endif
