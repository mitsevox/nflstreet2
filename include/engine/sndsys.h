#ifndef ENGINE_SNDSYS_H
#define ENGINE_SNDSYS_H

/* Declarations shared by the files of the sound range 0x80276DE4-0x8027CF9C: cu_80276DE4.cpp,
   slinklst.c, cu_8027882C.cpp, saramman.c, cu_80279BC0.cpp, supmutpf.c and cu_8027B1F8.cpp. */

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

typedef struct Struct_80278894 {
    unsigned char mUnknown0[8];
    int m8;
    unsigned char mUnknownC[4];
    int m10;
} Struct_80278894;

typedef struct Parser_8027823C {
    unsigned char *m0;
    int m4;
    int m8;
    unsigned char *mC;
    unsigned int m10;
} Parser_8027823C;

typedef struct Stream_803B5364 {
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
} Stream_803B5364;

typedef struct Event_803B5064 {
    unsigned short m0;
    unsigned short m2;
    int m4;
} Event_803B5064;

typedef struct Struct_803B5060 {
    int m0;
    Event_803B5064 m4[96];
    Stream_803B5364 *m304[32];
} Struct_803B5060;

typedef struct Struct_803B53EC {
    unsigned short m0;
    unsigned short m2;
    unsigned int m4;
    unsigned int m8;
    void *mC;
} Struct_803B53EC;

typedef struct State_8027A248 {
    float m0[8];
    float m20;
    float m24;
    float m28;
    float m2C;
    float m30;
    unsigned char mUnknown34[8];
} State_8027A248;

typedef struct Struct_80279C38 {
    Node_80279D90 mNode;
    State_8027A248 m1C;
} Struct_80279C38;

typedef struct Struct_8027A4C0 {
    Node_80279D90 mNode;
    int m1C;
} Struct_8027A4C0;

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

typedef struct Decoder_8027A9FC {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    int m28;
} Decoder_8027A9FC;

typedef struct Decoder_8027AB00 {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    unsigned int m28;
    int m2C;
} Decoder_8027AB00;

typedef struct Decoder_8027AC08 {
    Node_80279D90 mNode;
    unsigned int m1C;
    unsigned int m20;
    int m24;
    Codec_8027CF9C *m28;
} Decoder_8027AC08;

typedef struct Decoder_8027AE04 {
    Node_80279D90 mNode;
    Codec_8027CF9C *m1C;
    int m20;
    int m24;
    int m28;
    unsigned char *m2C;
} Decoder_8027AE04;

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

extern Struct_803B5060 lbl_803B5060;
extern Struct_803B53EC lbl_803B53EC;
extern unsigned char lbl_80300EDC[];
extern unsigned int lbl_80301428[];
extern int lbl_803A772C;

void *fn_8026B5D4(int size);
void fn_8026B7D8(void *p);
unsigned int fn_8026CB14(void);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
void fn_80276B7C(float *a, float *b, float *c, int count, int n);
int fn_802789E0(int handle);
int fn_80276C98(int count, unsigned char **data, float *value, float scale);
void fn_80279648(void **buffer, int *capacity, int size, int elementSize);
int fn_802791D0(int index);
void fn_80277EC4(int index);
void *fn_8027BD68(int size);
void fn_8027BD94(void *p);
Struct_8027BE24 *fn_8027BDC0(void *memory);
int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count);
int fn_8027BE24(Struct_8027BE24 *p, float **dst, int count);
void *fn_8027C020(int size);
void fn_8027C04C(void *p);
void fn_8027A21C(State_8027A248 *state);
void fn_8027A248(State_8027A248 *state, int count, float *in, float *out);
int fn_8027B4F4(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B888(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B1F8(Node_80279D90 *node, int count, float *a, float *b, int flag);

/* Defined in another file of the library. */
void fn_8027952C(int index, int channel, int value);
void SFILTER_unpackmtpfinit(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B328(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B464(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B7B0(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params);

}

#endif
