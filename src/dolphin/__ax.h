#ifndef _DOLPHIN_AX_INTERNAL_H_
#define _DOLPHIN_AX_INTERNAL_H_

#include <dolphin/ax.h>

#ifdef __cplusplus
extern "C" {
#endif

AXVPB* __AXGetStackHead(u32 priority);
void __AXServiceCallbackStack(void);
void __AXPushFreeStack(AXVPB* p);
void __AXPushCallbackStack(AXVPB* p);
AXVPB* __AXPopCallbackStack(void);
void __AXRemoveFromStack(AXVPB* p);
void __AXSetPBDefault(AXVPB* p);

void __AXAllocInit(void);
void __AXAllocQuit(void);
void __AXVPBInit(void);
void __AXVPBQuit(void);
u32 __AXGetStudio(void);
void __AXDepopFade(s32* hostSum, s32* dspVolume, s16* dspDelta);
void __AXPrintStudio(void);
void __AXDepopVoice(AXPB* p);

void __AXSPBInit(void);
void __AXSPBQuit(void);
extern u32 __AXClMode;

void __AXGetAuxAInput(u32* p);
void __AXGetAuxAInputDpl2(u32* p);
void __AXGetAuxAOutput(u32* p);
void __AXGetAuxAOutputDpl2R(u32* p);
void __AXGetAuxAOutputDpl2Ls(u32* p);
void __AXGetAuxAOutputDpl2Rs(u32* p);
void __AXGetAuxBInput(u32* p);
void __AXGetAuxBOutput(u32* p);
void __AXGetAuxBForDPL2(u32* p);
void __AXGetAuxBOutputDPL2(u32* p);
void __AXProcessAux(void);
void __AXAuxInit(void);
void __AXAuxQuit(void);
void __AXClInit(void);
void __AXClQuit(void);
void __AXSyncPBs(u32 lessDspCycles);
u32 __AXGetCommandListAddress(void);
u32 __AXGetCommandListCycles(void);
void __AXWriteToCommandList(u16 data);
AXPB* __AXGetPBs(void);
extern u16 __AXCompressorTable[3360];
void __AXNextFrame(void* sbuffer, void* buffer);
u32 __AXGetNumVoices(void);
AXPROFILE* __AXGetCurrentProfile(void);
void __AXOutNewFrame(u32 lessDspCycles);
void __AXOutAiCallback(void);
void __AXOutInitDSP(void);
void __AXOutInit(u32 outputBufferMode);
void __AXOutQuit(void);

#ifdef __cplusplus
}
#endif

#endif
