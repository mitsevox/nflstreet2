#ifndef ENGINE_SNDSYS_H
#define ENGINE_SNDSYS_H

#include "engine/saramman.h"

/* Declarations shared by the files of the sound range 0x80276B7C-0x8027D3AC: stretch.c, s3dlow.c,
   sattrdef.c, sbend.c, sclcptch.c, sctlfilt.c, sgetdata.c, sgettag.c, shipass.c, slinklst.c,
   slowpass.c, smemhigh.cpp, SNDI_cos.c, SNDI_sin.c, spktctoh.c, spktplay.c, sreallocbuf.cpp,
   srender.c, srrange.c, saramman.c, sfft24.c, sfhpffir8.c, sfilter.c, sfir.c, sfir8.c, sflpf.c, sfrsf.c, sinit16.c, sinitut.c,
   sinitxa.c, smixc.c, supf.c, suplf.c, supmutf.c, supmutlf.c, supmutpf.c, suppf.c, supxaf.cpp,
   supxalf.cpp, supxapf.cpp, eaxadecf.cpp and mtdecf.cpp. */

#include <string.h>

#include "engine/slinklst.h"

#include "engine/cu_802714A8.h"
#include "engine/sndvoice.h"
#include "engine/mtdecf.h"
#include "engine/eaxadecf.h"

typedef struct TIMESTRETCHSTATE {
    Node_80279D90 mNode;
    unsigned char *m1C;
    int m20;
    float m24;
    float m28;
    int m2C;
    int m30;
    int m34;
    int m38;
    int m3C;
    float m40[510];
    float m838[1020];
    float *m1828;
    int m182C;
    int m1830;
} TIMESTRETCHSTATE;

typedef struct SndMemEntry_t {
    unsigned int mOffset;
    int mSize;
} SndMemEntry_t;

typedef struct SndMemPool_t {
    char *mBase;
    SndMemEntry_t *mEntries;
    int mHeapSize;
    unsigned int mFreeEndOffset;
    int mLowWaterFreeBytes;
    int mNegativeEntryCount;
} SndMemPool_t;

typedef struct Parser_8027823C {
    unsigned char *m0;
    int m4;
    int m8;
    unsigned char *mC;
    unsigned int m10;
} Parser_8027823C;

/* A submitted packet: its frame count (31 bits) and last flag, and one data pointer per channel. */
typedef struct SndPacket_t {
    int unk_0x0;
    unsigned int mFrames : 31;
    unsigned int mLast : 1;
    int unk_0x8;
    void *mChannelData[6];
} SndPacket_t;

/* One queued packet of a player (32 bytes from +0x7C): its id, the packet's count and flag, the
   channel data pointers. */
typedef struct SndPacketEntry_t {
    int mPacketId;
    int mFrames : 31;
    int mLast : 1;
    void *mChannelData[6];
} SndPacketEntry_t;

typedef void (*SndPacketReleaseFn_t)(void *buffer, void *context);
typedef void (*SndPacketFramesDoneFn_t)(int index, unsigned int frames, void *context);

typedef struct SndPacketPlayer_t {
    // FAKEMATCH: the packet-queue members are volatile for the target's re-reads and access order
    int mVoiceHandle;
    volatile int mNextPacketId;
    volatile unsigned int mRetiredPackets;
    volatile unsigned int mConsumedPackets;
    volatile unsigned int mChannelConsumedPackets[6];
    volatile short mChannelReadIndex[6];
    volatile short mChannelQueuedPackets[6];
    volatile short mQueueCapacity;
    signed char mHighChannel;
    unsigned char unk_0x43;
    volatile short mRetireIndex;
    volatile short mWriteIndex;
    volatile int mQueuedFrames;
    volatile int mActiveFrames;
    void *mVoiceMemory;
    SndPacketReleaseFn_t mReleaseCallback;
    SndPacketFramesDoneFn_t mFramesDoneCallback;
    void *mCallbackContext;
    SndPacketFormat_t mFormat;
    void *mChannelBuffers[6];
    SndPacketEntry_t mEntries[1];
} SndPacketPlayer_t;

typedef struct SndPacketEvent_t {
    unsigned short mKind;
    unsigned short mPlayerIndex;
    union {
        void *mpBuffer;
        unsigned int mFrames;
    } mPayload;
} SndPacketEvent_t;

typedef struct SndPacketPlayers_t {
    int mEventCount;
    SndPacketEvent_t mEvents[96];
    SndPacketPlayer_t *mPlayers[32];
} SndPacketPlayers_t;


typedef struct SndFirState_t {
    float m0[8];
    float m20[5];
    float m34;
    float m38;
} SndFirState_t;

typedef struct SndHpfState_t {
    Node_80279D90 mNode;
    SndFirState_t m1C;
} SndHpfState_t;

typedef struct SndRcState_t {
    float m0;
    float m4;
    float m8;
} SndRcState_t;

typedef struct SndLpfState_t {
    Node_80279D90 mNode;
    SndRcState_t m1C;
} SndLpfState_t;

typedef struct SndRsfState_t {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    void (*m24)(int count, float *src, float *dst, int *pos, void *phase, unsigned int stepHi,
                unsigned int stepLo);
    short m28;
    short m2A;
    float m2C[4];
} SndRsfState_t;

typedef struct SndPcmUnpackFilter_t {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    int m28;
} SndPcmUnpackFilter_t;

typedef struct SndPcmLoopUnpackFilter_t {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    unsigned int m28;
    int m2C;
} SndPcmLoopUnpackFilter_t;

typedef struct SndMtSampleUnpackFilter_t {
    Node_80279D90 mNode;
    unsigned int m1C;
    unsigned int m20;
    int m24;
    Snd::CMTBLKDecf *m28;
} SndMtSampleUnpackFilter_t;

typedef struct SndMtLoopUnpackFilter_t {
    Node_80279D90 mNode;
    Snd::CMTBLKDecf *m1C;
    int m20;
    int m24;
    int m28;
    unsigned char *m2C;
} SndMtLoopUnpackFilter_t;

typedef struct SndMtUnpackFilter_t {
    Node_80279D90 mNode;
    unsigned char *mpPacket;
    int mPacketCount;
    int mStream;
    int mPendingCount;
    unsigned short mPacketPosition;
    unsigned char unk_0x2E[2];
    int mMode;
    Snd::CMTBLKDecf *mpCodec;
    unsigned char mChannel;
} SndMtUnpackFilter_t;

typedef struct SndPcmPacketUnpackFilter_t {
    Node_80279D90 mNode;
    unsigned char *mpPacket;
    int mPacketLength;
    int mPosition;
    int mStream;
    int mPendingCount;
    unsigned char mConvert;
    unsigned char mChannel;
} SndPcmPacketUnpackFilter_t;

typedef struct SndXaUnpackFilter_t {
    Node_80279D90 mNode;
    Snd::CEAXABLKDecf *mpDecoder;
    char *mpData;
    int mFrameCount;
    int mFramePosition;
} SndXaUnpackFilter_t;

typedef struct Decoder_8027B7B0 {
    Node_80279D90 mNode;
    Snd::CEAXABLKDecf *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    int m30;
    int m34;
    int m38;
    int m3C;
    int m40;
    int m44;
    int m48;
    float m4C;
    float m50;
} Decoder_8027B7B0;

typedef struct Decoder_8027BA6C {
    Node_80279D90 mNode;
    Snd::CEAXABLKDecf *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    int m30;
    int m34;
    unsigned char m38;
} Decoder_8027BA6C;

extern "C" {

extern SndPacketPlayers_t sndpps;
extern unsigned char sndcents[];
extern int lbl_803A772C;

void *SNDMEMI_allocz(int size);
void SNDMEMI_free(void *p);
unsigned int iSNDrandom(void);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
void crossfade(float *a, float *b, float *c, int count, int n);
int SNDPKTPLAYI_voicetopackethandle(int handle);
int determineaction(int count, unsigned char **data, float *value, float scale);
int SNDPKTPLAY_framesoutstanding(int index);
void iSNDcalcpitch(int index);
int SNDI_getb(unsigned char *p, int size);
float SNDI_cos(float x);
float SNDI_sin(float x);
void calcFIRCoeffs(SndFirState_t *state, int type);
void SNDI_fir8init(SndFirState_t *state);
void SNDI_fir8(SndFirState_t *state, int count, float *in, float *out);
int SFILTER_createLPFRC(Node_80279D90 *node);
void SFILTER_modifyLPFRC(Node_80279D90 *node, int *params);
int SFILTER_unpackxalf(Node_80279D90 *node, int count, float *a, float *b, int flag);
int SFILTER_unpackxapf(Node_80279D90 *node, int count, float *a, float *b, int flag);
int SFILTER_unpackpf(Node_80279D90 *node, int count, float *a, float *b, int flag);

/* Defined in another file of the library. */
void SNDPKTPLAYI_freeframes(int index, int channel, int value);
void SFILTER_unpackmtpfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpacklfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackmtfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackmtlfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackpfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackxafinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackxalfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);
void SFILTER_unpackxapfinit(Node_80279D90 *node, SndUnpackInitParams_t *params);

}

#endif
