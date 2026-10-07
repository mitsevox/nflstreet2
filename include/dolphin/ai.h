#ifndef _DOLPHIN_AI_H_
#define _DOLPHIN_AI_H_
#include <dolphin/types.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*AIDCallback)();
AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AIInitDMA(u32 start_addr, u32 length);
void AIStartDMA(void);
void AIStopDMA(void);
#ifdef __cplusplus
}
#endif
#endif
