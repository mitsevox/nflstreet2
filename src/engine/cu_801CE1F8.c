/* Low-level graphics: video/GX setup, frame-buffer swapping and screen queries. */
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/vi/vifuncs.h>
#include "engine/cu_801CE1F8.h"
#include "game/fn_801D2B7C.h"

extern GlibConfig_801CE1F8 lbl_803E91F8;
extern GlibState_801CE1F8 lbl_803E9224;
extern unsigned char lbl_803EBC68;
extern int lbl_803EBC6C;
extern void (*lbl_803EBC74)(void);
extern void (*lbl_803EBC78)(void);
extern unsigned char lbl_803EBC87;
extern unsigned char lbl_803EBC88;
extern int lbl_803ECF00;
extern unsigned char lbl_803ECF04;
extern unsigned char lbl_803ECF05;
extern unsigned char lbl_803ECF0C;
extern int lbl_803ED634;
extern int lbl_803ED638;
extern int lbl_803ED63C;
extern GXRenderModeObj lbl_802F7A4C;
extern GXRenderModeObj lbl_802F7A88;

void *fn_801C1F94();
void *fn_801C1FBC();
void fn_801F7B04(void);
void fn_802523A4(float (*pMtx)[4], int type);
void fn_801CED3C(GlibState_801CE1F8 *pMode);
void fn_802103DC(void);
void fn_80210634(void);
extern unsigned char lbl_80383DA0[];

int fn_801CE7D0(int a);
void fn_801CE95C(void);
void fn_801CEA44(GXBool enable);
static void fn_801CEC08(void);
static void fn_801CEC0C(GlibConfig_801CE1F8 *pConfig);

static int fn_801CE1F8(unsigned int value)
{
    int bits = 0;
    unsigned int v;

    for (v = value >> 1; v; v >>= 1) {
        bits++;
    }
    if (value & (value - 1)) {
        bits++;
    }
    return bits;
}

static void fn_801CE228(void)
{
}

void fn_801CE22C(void (*callback)(void))
{
    lbl_803EBC74 = callback;
}

void fn_801CE234(void (*callback)(void))
{
    lbl_803EBC78 = callback;
}

void fn_801CE23C(void)
{
    lbl_803EBC74 = 0;
}

void fn_801CE248(int enable)
{
    lbl_803EBC6C = enable;
}

static void fn_801CE250(void)
{
    lbl_803ED638 = -lbl_803ED634;
}

static void fn_801CE260(u32 retraceCount)
{
    fn_801F7B04();
    if (lbl_803EBC74) {
        lbl_803EBC74();
    }
    if (lbl_803EBC87) {
        GXDisableBreakPt();
    }
    if (lbl_803EBC78) {
        lbl_803EBC78();
    }
}

void fn_801CE2B8(int enable)
{
    if (enable) {
        VISetPostRetraceCallback(fn_801CE260);
    } else {
        VISetPostRetraceCallback(0);
    }
}

int fn_801CE2F4(GlibConfig_801CE1F8 *pConfig)
{
    GlibConfig_801CE1F8 *pCfg;
    GlibState_801CE1F8 *pMode;
    GXRenderModeObj *pSrcMode = 0;
    void *pFifo;

    lbl_803E91F8 = *pConfig;
    pCfg = &lbl_803E91F8;
    pMode = &lbl_803E9224;
    lbl_803ECF05 = 0;
    switch (pCfg->mTvMode) {
    case 0:
        pSrcMode = &GXNtsc240Ds;
        break;
    case 1:
        pSrcMode = &GXNtsc240DsAa;
        break;
    case 2:
        pSrcMode = &GXNtsc240Int;
        break;
    case 3:
        pSrcMode = &GXNtsc240IntAa;
        break;
    case 4:
        pSrcMode = &GXNtsc480IntDf;
        break;
    case 5:
        pSrcMode = &GXNtsc480Int;
        break;
    case 6:
        pSrcMode = &GXNtsc480IntAa;
        break;
    case 7:
        pSrcMode = &lbl_802F7A4C;
        lbl_803ECF05 = 1;
        break;
    case 8:
        pSrcMode = &lbl_802F7A88;
        break;
    }
    fn_801C1F94(pMode, 0, 0x3C);
    if (pCfg->mTvMode == 7) {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    } else if (pCfg->mTvMode == 8) {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    } else {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    }
    lbl_803ECF00 = ((pMode->mMode.fbWidth + 15) & 0xFFF0) * pMode->mMode.xfbHeight * 2;
    pMode->mpXfb[1] = pMode->mpXfb[0] = fn_801D2B7C(lbl_803ECF00, 0, 0);
    pMode->mFrame = 0;
    lbl_803ECF04 = 0;
    VIConfigure(&pMode->mMode);
    VISetNextFrameBuffer(pMode->mpXfb[pMode->mFrame]);
    pMode->mLog2Width = fn_801CE1F8(pCfg->mWidth);
    pMode->mLog2Height = fn_801CE1F8(pCfg->mHeight);
    pFifo = fn_801D2B7C(pCfg->mFifoSize, 0, 0);
    DCInvalidateRange(pFifo, pCfg->mFifoSize);
    pMode->mpFifoBuffer = pFifo;
    pMode->mpFifo = GXInit(pFifo, pCfg->mFifoSize);
    pMode->mFifoSize = pCfg->mFifoSize;
    GXSetCopyClear(pCfg->mClearColor, 0xFFFFFF);
    GXSetViewport(0.0f, 0.0f, (unsigned int)pMode->mMode.fbWidth, (unsigned int)pMode->mMode.xfbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, pMode->mMode.fbWidth, pMode->mMode.efbHeight);
    GXSetDispCopySrc(0, 0, pMode->mMode.fbWidth, pMode->mMode.efbHeight);
    GXSetDispCopyDst(pMode->mMode.fbWidth, pMode->mMode.xfbHeight);
    GXSetDispCopyYScale((float)(unsigned int)pMode->mMode.xfbHeight / (float)(unsigned int)pMode->mMode.efbHeight);
    fn_801CEA44(1);
    if (pMode->mMode.aa) {
        GXSetPixelFmt(2, 0);
    } else {
        GXSetPixelFmt(0, 0);
    }
    VISetBlack(1);
    VIFlush();
    GXCopyDisp(lbl_803E9224.mpXfb[pMode->mFrame], 1);
    VIFlush();
    GXCopyDisp(lbl_803E9224.mpXfb[pMode->mFrame], 1);
    VIFlush();
    fn_801CE7D0(0);
    if (pMode->mMode.viTVmode & 1) {
        VIWaitForRetrace();
    }
    VISetBlack(0);
    GXSetDrawDoneCallback(fn_801CE250);
    fn_801CE2B8(1);
    fn_801CEC0C(pCfg);
    lbl_803EBC68 = 1;
    return 0;
}

int fn_801CE718(void)
{
    return 0;
}

void fn_801CE720(void)
{
    void *a;
    void *b;

    if (lbl_803ECF0C) {
        GXFlush();
        GXGetFifoPtrs(GXGetCPUFifo(), &a, &b);
        GXEnableBreakPt(b);
    }
    fn_801CED3C(&lbl_803E9224);
    fn_802103DC();
}

static inline void sync_801CE774(int count)
{
    GXWaitDrawDone();
    lbl_803ED63C = count;
}

void fn_801CE774(void)
{
    if (!lbl_803EBC68) {
        fn_801CE95C();
    }
    fn_80210634();
    GXSetDrawDone();
    GXFlush();
    if (lbl_803ECF0C) {
        GXDisableBreakPt();
        sync_801CE774(0);
    }
}

int fn_801CE7D0(int a)
{
    VIWaitForRetrace();
    return 0;
}

static void fn_801CE7F4(void)
{
    void *a;
    void *b;

    GXFlush();
    GXGetFifoPtrs(GXGetCPUFifo(), &a, &b);
    GXEnableBreakPt(b);
}

void fn_801CE82C(void)
{
    if (lbl_803ECF04) {
        VISetNextFrameBuffer(lbl_803E9224.mpXfb[lbl_803E9224.mFrame]);
        VIFlush();
        VIWaitForRetrace();
        lbl_803E9224.mFrame ^= 1;
        fn_801CEC08();
    } else {
        GXDrawDone();
        fn_801CE228();
        VISetNextFrameBuffer(lbl_803E9224.mpXfb[0]);
        VIFlush();
        if (lbl_803EBC88) {
            fn_801CE7F4();
            lbl_803EBC87 = 1;
        } else {
            VIWaitForRetrace();
        }
        lbl_803ED634 = 0;
        GXSetColorUpdate(1);
        GXSetZMode(1, 3, 1);
        GXCopyDisp(lbl_803E9224.mpXfb[0], lbl_803EBC68);
        GXPixModeSync();
        lbl_803E9224.mFrame = 0;
    }
}

void fn_801CE908(unsigned char enable)
{
    lbl_803EBC88 = enable;
}

void fn_801CE910(void)
{
    GXDrawDone();
}

unsigned char fn_801CE930(void)
{
    return lbl_803E9224.mFrame;
}

int fn_801CE93C(void)
{
    return 0;
}

void *fn_801CE944(int frame)
{
    return lbl_803E9224.mpXfb[frame];
}

void fn_801CE95C(void)
{
    GlibState_801CE1F8 *pMode = &lbl_803E9224;

    GXSetColorUpdate(0);
    GXSetZMode(0, 0, 1);
    GXSetDispCopyDst(0, 0);
    GXCopyDisp(lbl_80383DA0, 1);
    GXSetColorUpdate(1);
    GXSetZMode(1, 3, 1);
    GXSetDispCopyDst(pMode->mMode.fbWidth, pMode->mMode.xfbHeight);
}

void fn_801CE9E0(GXBool enable)
{
    GXSetZMode(enable, 3, 1);
}

int fn_801CEA08(void)
{
    return lbl_803E91F8.mWidth;
}

int fn_801CEA14(void)
{
    return lbl_803E91F8.mHeight;
}

void fn_801CEA20(float (*pMatrix)[4])
{
    fn_802523A4(pMatrix, 0);
}

void fn_801CEA44(GXBool enable)
{
    GXSetCopyFilter(lbl_803E9224.mMode.aa, lbl_803E9224.mMode.sample_pattern, enable, lbl_803E9224.mMode.vfilter);
}

void fn_801CEA7C(unsigned char clear)
{
    lbl_803EBC68 = clear;
}

void fn_801CEA84(void)
{
    GlibState_801CE1F8 *pMode = &lbl_803E9224;

    VISetNextFrameBuffer(pMode->mpXfb[0]);
    VIFlush();
    VIWaitForRetrace();
    fn_801D2BD0(pMode->mpXfb[1]);
    lbl_803ECF04 = 0;
    pMode->mFrame = 0;
    pMode->mpXfb[1] = pMode->mpXfb[0];
}

void fn_801CEADC(int skipSwap)
{
    if (!skipSwap) {
        fn_801CE82C();
        fn_801CE82C();
    }
    lbl_803E9224.mpXfb[1] = fn_801D2B7C(lbl_803ECF00, 0, 0);
    fn_801C1FBC(lbl_803E9224.mpXfb[1], lbl_803E9224.mpXfb[0], lbl_803ECF00);
    lbl_803ECF04 = 1;
}

int fn_801CEB40(void)
{
    return 0xFFFF;
}

int fn_801CEB4C(void)
{
    return 0xFFFF;
}

void fn_801CEB58(int progressive)
{
    if (lbl_803ECF05 != progressive) {
        lbl_803ECF05 = progressive;
        VISetBlack(1);
        if (progressive) {
            GXAdjustForOverscan(&lbl_802F7A4C, &lbl_803E9224.mMode, 0, 16);
        } else {
            GXAdjustForOverscan(&GXNtsc480IntDf, &lbl_803E9224.mMode, 0, 16);
        }
        VIConfigure(&lbl_803E9224.mMode);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VISetBlack(0);
        VIFlush();
        VIWaitForRetrace();
    }
}

static void fn_801CEC08(void)
{
}

static void fn_801CEC0C(GlibConfig_801CE1F8 *pConfig)
{
    GXSetScissor(0, 0, pConfig->mWidth - 1, pConfig->mHeight - 1);
}

void fn_801CEC48(int left, int width, int top, int height)
{
    GXSetScissor(left, top, width, height);
}

int fn_801CEC74(void)
{
    return 0x150;
}

int fn_801CEC7C(void)
{
    return 0x280;
}

unsigned short fn_801CEC84(void)
{
    return lbl_803E9224.mMode.xfbHeight;
}
