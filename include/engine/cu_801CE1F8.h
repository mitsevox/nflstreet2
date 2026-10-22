#ifndef ENGINE_CU_801CE1F8_H
#define ENGINE_CU_801CE1F8_H

#include <dolphin/gx/GXStruct.h>

/* Display configuration copied in by the low-level init (0x2C bytes at 0x803E91F8). */
typedef struct GlibConfig_801CE1F8 {
    int mWidth;
    int mHeight;
    int mUnk8[3];
    unsigned int mTvMode;
    unsigned char mUnk18[2];
    GXColor mClearColor;
    unsigned char mUnk1E[2];
    int mFifoSize;
    int mUnk24[2];
} GlibConfig_801CE1F8;

/* Video render mode (the GX layout, 0x3C bytes) followed by the FIFO and frame-buffer state. */
typedef struct GlibState_801CE1F8 {
    unsigned int mViTvMode;
    unsigned short mFbWidth;
    unsigned short mEfbHeight;
    unsigned short mXfbHeight;
    unsigned short mViXOrigin;
    unsigned short mViYOrigin;
    unsigned short mViWidth;
    unsigned short mViHeight;
    unsigned int mXfbMode;
    unsigned char mFieldRendering;
    unsigned char mAa;
    unsigned char mSamplePattern[12][2];
    unsigned char mVFilter[7];
    int mFifoSize;
    void *mpFifo;
    void *mpFifoBuffer;
    int mUnk48[3];
    void *mpXfb[2];
    short mLog2Width;
    short mLog2Height;
    unsigned char mFrame;
} GlibState_801CE1F8;

#endif
