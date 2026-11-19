#ifndef ENGINE_SNDSYS_H
#define ENGINE_SNDSYS_H

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
    unsigned int m0;
    int m4;
} SndMemEntry_t;

typedef struct SndMemPool_t {
    char *m0;
    SndMemEntry_t *m4;
    int m8;
    unsigned int mC;
    int m10;
    int m14;
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
    int m0;
    unsigned int m4 : 31;
    unsigned int m4b : 1;
    int m8;
    void *mC[6];
} SndPacket_t;

/* One queued packet of a player (32 bytes from +0x7C): its id, the packet's count and flag, the
   channel data pointers. */
typedef struct SndPacketEntry_t {
    int m0;
    int m4 : 31;
    int m4b : 1;
    void *m8[6];
} SndPacketEntry_t;

typedef struct SndPacketPlayer_t {
    // FAKEMATCH: the packet-queue members are volatile for the target's re-reads and access order
    int m0;
    volatile int m4;
    volatile unsigned int m8;
    volatile unsigned int mC;
    volatile unsigned int m10[6];
    volatile short m28[6];
    volatile short m34[6];
    volatile short m40;
    signed char m42;
    unsigned char mUnknown43;
    volatile short m44;
    volatile short m46;
    volatile int m48;
    volatile int m4C;
    void *m50;
    void (*m54)(int value, void *context);
    void (*m58)(int index, int value, void *context);
    void *m5C;
    Info_80274464 m60;
    void *m64[6];
    SndPacketEntry_t m7C[1];
} SndPacketPlayer_t;

/* A patch header (256 bytes; SNDPKTPLAY_start builds one on its stack): channel count +0x3 and the
   render flags +0x18 that SNDI_validrendermode tests; the rest is not established. */
typedef struct SndPatchHeader_t {
    unsigned char mUnknown0[3];
    unsigned char m3;
    unsigned char mUnknown4[0x14];
    unsigned short m18;
    unsigned char mUnknown1A[0xE6];
} SndPatchHeader_t;

typedef struct SndPacketEvent_t {
    unsigned short m0;
    unsigned short m2;
    int m4;
} SndPacketEvent_t;

typedef struct SndPacketPlayers_t {
    int m0;
    SndPacketEvent_t m4[96];
    SndPacketPlayer_t *m304[32];
} SndPacketPlayers_t;

typedef struct Struct_803B53EC {
    unsigned short m0;
    unsigned short m2;
    unsigned int m4;
    unsigned int m8;
    void *mC;
} Struct_803B53EC;

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
extern Struct_803B53EC lbl_803B53EC;
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
int SFILTER_unpackxalf(Node_80279D90 *node, int count, float *a, float *b, int flag);
int SFILTER_unpackxapf(Node_80279D90 *node, int count, float *a, float *b, int flag);
int SFILTER_unpackpf(Node_80279D90 *node, int count, float *a, float *b, int flag);

/* Defined in another file of the library. */
void SNDPKTPLAYI_freeframes(int index, int channel, int value);
void SFILTER_unpackmtpfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpacklfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackmtfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackmtlfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackpfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackxafinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackxalfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackxapfinit(Node_80279D90 *node, Params_80275F80 *params);

}

#endif
