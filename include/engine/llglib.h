#ifndef ENGINE_LLGLIB_H
#define ENGINE_LLGLIB_H

#include <dolphin/gx/GXStruct.h>

/* Display configuration copied in by the low-level init (0x2C bytes at 0x803E91F8). */
typedef struct GlibConfig_t {
    int mWidth;
    int mHeight;
    int mUnk8[3];
    unsigned int mTvMode;
    unsigned char mUnk18[2];
    GXColor mClearColor;
    unsigned char mUnk1E[2];
    int mFifoSize;
    int mUnk24[2];
} GlibConfig_t;

/* Video render mode (the GX layout, 0x3C bytes) followed by the FIFO and frame-buffer state. */
typedef struct GlibState_t {
    GXRenderModeObj mMode;
    int mFifoSize;
    void *mpFifo;
    void *mpFifoBuffer;
    int mUnk48[3];
    void *mpXfb[2];
    short mLog2Width;
    short mLog2Height;
    unsigned char mFrame;
} GlibState_t;

#ifdef __cplusplus
extern "C" {
#endif

void GlibEnableVIRetraceCallback(int enable);
void GlibSetProjection(float (*pMatrix)[4]);
int GlibGetScreenWidth(void);

#ifdef __cplusplus
}
#endif

#endif
