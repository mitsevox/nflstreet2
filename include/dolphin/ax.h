#ifndef _DOLPHIN_AX_H_
#define _DOLPHIN_AX_H_

#include <dolphin/types.h>
#include <dolphin/ax/AXVPB.h>

#define AX_MAX_VOICES 64
#define AX_SRC_TYPE_NONE 0
#define AX_SRC_TYPE_LINEAR 1
#define AX_SRC_TYPE_4TAP_8K 2
#define AX_SRC_TYPE_4TAP_12K 3
#define AX_SRC_TYPE_4TAP_16K 4
#define AX_SYNC_FLAG_COPYALL (1 << 31)
#define AX_SYNC_FLAG_COPYADPCMLOOP (1 << 20)
#define AX_SYNC_FLAG_COPYRATIO (1 << 19)
#define AX_SYNC_FLAG_COPYSRC (1 << 18)
#define AX_SYNC_FLAG_COPYADPCM (1 << 17)
#define AX_SYNC_FLAG_COPYCURADDR (1 << 16)
#define AX_SYNC_FLAG_COPYENDADDR (1 << 15)
#define AX_SYNC_FLAG_COPYLOOPADDR (1 << 14)
#define AX_SYNC_FLAG_COPYLOOP (1 << 13)
#define AX_SYNC_FLAG_COPYADDR (1 << 12)
#define AX_SYNC_FLAG_COPYFIR (1 << 11)
#define AX_SYNC_FLAG_SWAPVOL (1 << 10)
#define AX_SYNC_FLAG_COPYVOL (1 << 9)
#define AX_SYNC_FLAG_COPYDPOP (1 << 8)
#define AX_SYNC_FLAG_COPYUPDATE (1 << 7)
#define AX_SYNC_FLAG_COPYTSHIFT (1 << 6)
#define AX_SYNC_FLAG_COPYITD (1 << 5)
#define AX_SYNC_FLAG_COPYAXPBMIX (1 << 4)
#define AX_SYNC_FLAG_COPYTYPE (1 << 3)
#define AX_SYNC_FLAG_COPYSTATE (1 << 2)
#define AX_SYNC_FLAG_COPYMXRCTRL (1 << 1)
#define AX_SYNC_FLAG_COPYSELECT (1 << 0)
#define AX_PRIORITY_STACKS 32

typedef struct _AXPBITDBUFFER
{
    /* 0x00 */ s16 data[32];
} AXPBITDBUFFER;

typedef struct _AXPBU
{
    /* 0x00 */ u16 data[128];
} AXPBU;

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

typedef struct _AXSPB {
    /* 0x00 */ u16 dpopLHi;
    /* 0x02 */ u16 dpopLLo;
    /* 0x04 */ s16 dpopLDelta;
    /* 0x06 */ u16 dpopRHi;
    /* 0x08 */ u16 dpopRLo;
    /* 0x0A */ s16 dpopRDelta;
    /* 0x0C */ u16 dpopSHi;
    /* 0x0E */ u16 dpopSLo;
    /* 0x10 */ s16 dpopSDelta;
    /* 0x12 */ u16 dpopALHi;
    /* 0x14 */ u16 dpopALLo;
    /* 0x16 */ s16 dpopALDelta;
    /* 0x18 */ u16 dpopARHi;
    /* 0x1A */ u16 dpopARLo;
    /* 0x1C */ s16 dpopARDelta;
    /* 0x1E */ u16 dpopASHi;
    /* 0x20 */ u16 dpopASLo;
    /* 0x22 */ s16 dpopASDelta;
    /* 0x24 */ u16 dpopBLHi;
    /* 0x26 */ u16 dpopBLLo;
    /* 0x28 */ s16 dpopBLDelta;
    /* 0x2A */ u16 dpopBRHi;
    /* 0x2C */ u16 dpopBRLo;
    /* 0x2E */ s16 dpopBRDelta;
    /* 0x30 */ u16 dpopBSHi;
    /* 0x32 */ u16 dpopBSLo;
    /* 0x34 */ s16 dpopBSDelta;
} AXSPB;

typedef struct _AXPROFILE {
    /* 0x00 */ u64 axFrameStart;
    /* 0x08 */ u64 auxProcessingStart;
    /* 0x10 */ u64 auxProcessingEnd;
    /* 0x18 */ u64 userCallbackStart;
    /* 0x20 */ u64 userCallbackEnd;
    /* 0x28 */ u64 axFrameEnd;
    /* 0x30 */ u32 axNumVoices;
} AXPROFILE;

typedef void (*AXCallback)();
AXCallback AXRegisterCallback(AXCallback callback);
void AXSetStepMode(u32 i);
extern AXPROFILE __AXLocalProfile;
extern u16 axDspSlaveLength;
#define AX_DSP_SLAVE_LENGTH 3936
extern u16 axDspSlave[AX_DSP_SLAVE_LENGTH];

void AXSetMode(u32 mode);
u32 AXGetMode(void);
void AXSetCompressor(u32 i);
void AXInitProfile(AXPROFILE* profile, u32 maxProfiles);
u32 AXGetProfile(void);
void AXInit(void);
void AXInitEx(u32 outputBufferMode);
void AXQuit(void);
void AXFreeVoice(AXVPB* p);
AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext);

void AXSetVoiceSrcType(AXVPB* p, u32 type);
void AXSetVoiceState(AXVPB* p, u16 state);
void AXSetVoiceType(AXVPB* p, u16 type);
void AXSetVoiceAddr(AXVPB* p, AXPBADDR* addr);
void AXSetVoiceLoop(AXVPB* p, u16 loop);
void AXSetVoiceLoopAddr(AXVPB* p, u32 addr);
void AXSetVoiceEndAddr(AXVPB* p, u32 addr);
void AXSetVoiceCurrentAddr(AXVPB* p, u32 addr);
void AXSetVoiceAdpcm(AXVPB* p, AXPBADPCM* adpcm);
void AXSetVoiceSrc(AXVPB* p, AXPBSRC* src_);
void AXSetVoiceSrcRatio(AXVPB* p, f32 ratio);
void AXSetVoiceAdpcmLoop(AXVPB* p, AXPBADPCMLOOP* adpcmloop);

#ifdef __cplusplus
}
#endif

#endif
