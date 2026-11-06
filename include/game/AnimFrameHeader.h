#ifndef GAME_ANIMFRAMEHEADER_H
#define GAME_ANIMFRAMEHEADER_H

#include "game/Object_8003DEC4.h"
#include "game/AnimQuantContext.h"

/* Encoded frame blocks start with a count byte whose top two bits flag the
   optional vectors, then a flags byte and four header words. */
struct AnimFrameHeaderCopy {
    unsigned int mWords[7];
};

/* Frame header decoded by AnimReadFrameHeader from an encoded sample block. */
struct AnimFrameHeader {
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
   pose decoders, a halfword list for AnimReadWeights). */
struct AnimBlendEntry {
    char mUnknown0[4];
    float mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12[3];
    float mUnknown24[2];
    unsigned short mUnknown32;
    unsigned short mUnknown34;
    AnimQuantContext *mpUnknown36;
    void *mpUnknown40;
};

/* Blend description: an entry count and the entries. */
struct AnimBlendList {
    unsigned short mUnknown0;
    char mUnknown2[2];
    AnimBlendEntry mUnknown4[24];
    char mUnknown1060[4];
};

extern "C" {
void AnimCopyRawFrame(Pose_80041930 *pPose, AnimBlendEntry *pEntry, int mirrored);
short *AnimReadFrameHeader(AnimFrameHeader *header, void *encoded);
int AnimGetFrameHeaderSize(unsigned char *encoded);
void AnimUnpackFrameBits(short *destination, short *source, AnimQuantContext *context, int mirrored);
void fn_8019D994(Pose_80041930 *pPose, AnimBlendEntry *pEntry, int mode, float scale, AnimQuantContext *pContext,
                 int unused);
void fn_8019E00C(Pose_80041930 *pPose, AnimBlendEntry *pEntry, int mode, float scale, AnimQuantContext *pContext,
                 int unused);
void AnimDecompressFrame(unsigned char *pDestination, unsigned char *pSource, AnimQuantContext *pContext, int mirrored);
void AnimBlendWeights(float *pValues, AnimBlendList *pBlend);
}

#endif
