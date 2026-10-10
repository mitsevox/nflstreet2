#ifndef GAME_FRAME_8019D3B8_H
#define GAME_FRAME_8019D3B8_H

#include "game/Object_8003DEC4.h"
#include "game/Record_8019D8AC.h"

/* Encoded frame blocks start with a count byte whose top two bits flag the
   optional vectors, then a flags byte and four header words. */
struct Block_8019D3B8 {
    unsigned int mWords[7];
};

/* Frame header decoded by fn_8019D3B8 from an encoded sample block. */
struct Frame_8019D3B8 {
    unsigned char count;
    unsigned char flags;
    short word2;
    short word4;
    short word6;
    short word8;
    short vectorA[3];
    short vector10[3];
};

/* 44-byte entry of a blend description: a weight, flags (bit 0 selects
   fn_8019D994 over fn_8019E00C), the vector and planar values those two
   decoders write back, two halfwords copied by fn_80042530, the
   frame-decoding context and the entry's data (an encoded frame for the
   pose decoders, a halfword list for fn_8019F318). */
struct BlendEntry_8019EDDC {
    char mUnknown0[4];
    float mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12[3];
    float mUnknown24[2];
    unsigned short mUnknown32;
    unsigned short mUnknown34;
    Record_8019D8AC *mpUnknown36;
    void *mpUnknown40;
};

/* Blend description: an entry count and the entries. */
struct Blend_8019EDDC {
    unsigned short mUnknown0;
    char mUnknown2[2];
    BlendEntry_8019EDDC mUnknown4[24];
    char mUnknown1060[4];
};

extern "C" {
void fn_8019D2EC(Pose_80041930 *pPose, BlendEntry_8019EDDC *pEntry, int mirrored);
short *fn_8019D3B8(Frame_8019D3B8 *header, void *encoded);
int fn_8019D4EC(unsigned char *encoded);
void fn_8019D514(short *destination, short *source, Record_8019D8AC *context, int mirrored);
void fn_8019D994(Pose_80041930 *pPose, BlendEntry_8019EDDC *pEntry, int mode, float scale, Record_8019D8AC *pContext,
                 int unused);
void fn_8019E00C(Pose_80041930 *pPose, BlendEntry_8019EDDC *pEntry, int mode, float scale, Record_8019D8AC *pContext,
                 int unused);
void fn_8019ED4C(unsigned char *pDestination, unsigned char *pSource, Record_8019D8AC *pContext, int mirrored);
void fn_8019F404(float *pValues, Blend_8019EDDC *pBlend);
}

#endif
