#ifndef _DOLPHIN_GBA_H_
#define _DOLPHIN_GBA_H_

#include <dolphin/os.h>
#include <dolphin/dsp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GBASyncCallback)(s32 chan, int ret);
typedef void (*GBAProcHandler)(s32 chan);

typedef struct GBASecParam {
    u8 opaque[0x40];
} GBASecParam;

typedef struct GBAControl {
    u8 output[5];
    u8 input[5];
    int outputBytes;
    int inputBytes;
    u8* status;
    u8 opaque_18[4];
    GBASyncCallback callback;
    int ret;
    OSThreadQueue threadQueue;
    OSTime delay;
    GBAProcHandler proc;
    u8 opaque_3c[0xbc];
    GBASecParam* param;
} GBAControl;

void GBAInit(void);
BOOL __GBATransfer(s32 chan, u32 outputBytes, u32 inputBytes, GBAProcHandler proc);
int __GBASync(s32 chan);
void __GBASyncCallback(s32 chan, int ret);
int GBAReset(s32 chan, u8* status);
int GBAGetStatus(s32 chan, u8* status);
int GBAResetAsync(s32 chan, u8* status);
int GBAGetStatusAsync(s32 chan, u8* status);

static inline GBAProcHandler getGBAHandler(GBAControl* gba)
{
    return gba->proc;
}

extern GBAControl __GBA[4];
extern BOOL __GBAReset;

#ifdef __cplusplus
}
#endif
#endif
