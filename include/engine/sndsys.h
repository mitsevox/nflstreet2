#ifndef ENGINE_SNDSYS_H
#define ENGINE_SNDSYS_H

/* Declarations shared by the files of the sound range 0x80276B7C-0x8027CF9C: stretch.c, s3dlow.c,
   sattrdef.c, sbend.c, sclcptch.c, sctlfilt.c, sgetdata.c, sgettag.c, shipass.c, slinklst.c,
   slowpass.c, smemhigh.cpp, SNDI_cos.c, SNDI_sin.c, spktctoh.c, spktplay.c, sreallocbuf.cpp,
   srrange.c, saramman.c, sfft24.c, sfhpffir8.c, sfilter.c, sfir8.c, sfrsf.c, sinit16.c, sinitut.c,
   sinitxa.c, smixc.c, supf.c, suplf.c, supmutf.c, supmutlf.c, supmutpf.c and cu_8027B1F8.cpp. */

#include <string.h>

#include "engine/slinklst.h"

#include "engine/cu_802714A8.h"
#include "engine/sndvoice.h"
#include "engine/cu_8027CF9C.h"

typedef struct Object_80277404 {
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
} Object_80277404;

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

typedef struct SndPacketPlayer_t {
    int m0;
    unsigned char mUnknown4[0x30];
    short m34[6];
    short m40;
    signed char m42;
    unsigned char mUnknown43[5];
    int m48;
    int m4C;
    unsigned char mUnknown50[8];
    void (*m58)(int index, int value, void *context);
    unsigned char mUnknown5C[6];
    unsigned char m62;
} SndPacketPlayer_t;

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
    float m20;
    float m24;
    float m28;
    float m2C;
    float m30;
    unsigned char mUnknown34[8];
} SndFirState_t;

typedef struct SndHpfState_t {
    Node_80279D90 mNode;
    SndFirState_t m1C;
} SndHpfState_t;

typedef struct SndRsfState_t {
    Node_80279D90 mNode;
    int m1C;
} SndRsfState_t;

typedef struct Pair_8027BFDC {
    float m0;
    float m4;
} Pair_8027BFDC;

typedef struct Block_8027BC18 {
    unsigned char mUnknown0[4];
    float m4;
    float m8;
    char *mC;
    unsigned char mUnknown10[4];
} Block_8027BC18;

typedef struct Struct_8027BE24 {
    unsigned char mUnknown0[8];
    int m8;
    int mC;
    unsigned char mUnknown10[0x84];
    Block_8027BC18 m94;
} Struct_8027BE24;

typedef struct Bits_8027C078 {
    unsigned char *m0;
    unsigned int m4;
    int m8;
} Bits_8027C078;

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
    Codec_8027CF9C *m28;
} SndMtSampleUnpackFilter_t;

typedef struct SndMtLoopUnpackFilter_t {
    Node_80279D90 mNode;
    Codec_8027CF9C *m1C;
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
    Codec_8027CF9C *mpCodec;
    unsigned char mChannel;
} SndMtUnpackFilter_t;

typedef struct Decoder_8027B328 {
    Node_80279D90 mNode;
    unsigned char *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    unsigned char m30;
    unsigned char m31;
} Decoder_8027B328;

typedef struct Decoder_8027B464 {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
    char *m20;
    int m24;
    int m28;
} Decoder_8027B464;

typedef struct Decoder_8027B7B0 {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
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
} Decoder_8027B7B0;

typedef struct Decoder_8027BA6C {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
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
extern unsigned int lbl_80301428[];
extern int lbl_803A772C;

void *SNDMEMI_allocz(int size);
void SNDMEMI_free(void *p);
unsigned int iSNDrandom(void);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
void fn_80276B7C(float *a, float *b, float *c, int count, int n);
int SNDPKTPLAYI_voicetopackethandle(int handle);
int fn_80276C98(int count, unsigned char **data, float *value, float scale);
void fn_80279648(void **buffer, int *capacity, int size, int elementSize);
int SNDPKTPLAY_framesoutstanding(int index);
void iSNDcalcpitch(int index);
int SNDI_getb(unsigned char *p, int size);
void *fn_8027BD68(int size);
void fn_8027BD94(void *p);
Struct_8027BE24 *fn_8027BDC0(void *memory);
int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count);
int fn_8027BE24(Struct_8027BE24 *p, float **dst, int count);
void *fn_8027C020(int size);
void fn_8027C04C(void *p);
void SNDI_fir8init(SndFirState_t *state);
void SNDI_fir8(SndFirState_t *state, int count, float *in, float *out);
int fn_8027B4F4(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B888(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B1F8(Node_80279D90 *node, int count, float *a, float *b, int flag);

/* Defined in another file of the library. */
void SNDPKTPLAYI_freeframes(int index, int channel, int value);
void SFILTER_unpackmtpfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpacklfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackmtfinit(Node_80279D90 *node, Params_80275F80 *params);
void SFILTER_unpackmtlfinit(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B328(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B464(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B7B0(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params);

}

#endif
