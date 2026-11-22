#ifndef ENGINE_SNDSAMPLE_H
#define ENGINE_SNDSAMPLE_H

/* The sample records shared by the sound bank and stream files: a patch or stream format and its
   sample attributes. */

/* The sample-format record of a patch or stream: sample rate, channel count and codec. */
typedef struct SndSampleFormat_t {
    unsigned short mRate;
    unsigned char mChannels;
    unsigned char mCodec;
} SndSampleFormat_t;

/* The sample-attribute record of a patch: header fields +0x0..+0x9, six per-channel halfwords +0xC,
   per-channel buffers +0x18 and their sizes +0x30, two four-word tables +0x48 and +0x58. */
typedef struct SndSampleAttr_t {
    unsigned short m0;
    unsigned char m2;
    unsigned char m3;
    unsigned char m4;
    unsigned char m5;
    unsigned char m6;
    unsigned char m7;
    unsigned short m8;
    unsigned char mUnknownA[2];
    short mC[6];
    void *m18[6];
    int m30[6];
    unsigned char *mDataBlocks[4];
    unsigned int mDataBlockSizes[4];
} SndSampleAttr_t;

typedef struct SndSampleDesc_t {
    unsigned int mFrames;
    unsigned int mChannelData[6];
} SndSampleDesc_t;

#endif
