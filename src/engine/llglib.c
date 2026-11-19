/* Low-level graphics: video/GX setup, frame-buffer swapping and screen queries. */
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/vi/vifuncs.h>
#include "engine/llglib.h"
#include "game/fn_801D2B7C.h"

/* Bits per texel of each GX texture format, and palette entries of the colour-index formats
   (read by texture.c). */
unsigned char Glib_TexBitsPerPixel[15] = { 4, 8, 8, 16, 16, 16, 32, 0, 4, 8, 16, 8, 0, 0, 4 };
unsigned int Glib_TexPalEntries[15] = { 16, 256, 0, 0, 0, 0, 0, 0, 16, 256, 0, 256, 0, 0, 0 };

/* 480-line progressive NTSC and 574-line double-field PAL modes with this library's vertical filters. */
static GXRenderModeObj GXNtsc480ProgFilt = {
    2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 4, 8, 12, 16, 12, 8, 4 }
};
GXRenderModeObj Pal574IntDfScale = {
    4, 640, 480, 574, 40, 0, 640, 574, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 8, 8, 10, 12, 10, 8, 8 }
};

static unsigned char _Glib_bClear = 1;
static int _Glib_VsyncSwap = 0;
static int _Glib_iDmaFrame = 0;
static void (*_Glib_pCallback)(void) = 0;
static void (*_Glib_pCallbackAfter)(void) = 0;
static void (*_Glib_pDmaCallbackBefore)(void) = 0;
/* Bits per palette entry of each GX TLUT format (read by texture.c). */
unsigned char Glib_PalBitsPerPixel[7] = { 16, 16, 16, 0, 0, 0, 32 };
static unsigned char _Glib_bBreakPoint = 0;
static unsigned char _bVIInt = 1;
static int _Glib_iPass = 0;

static unsigned char garbage[2560];

static short _Glib_ScreenWidthLog2;
static short _Glib_ScreenHeightLog2;
static int _Glib_fbSize;
static unsigned char _Glib_DoubleBuffered;
static unsigned char _Glib_Progressive;
static int _Glib_VsyncField;
static unsigned char _Break;

GlibConfig_t _Glib_LLInitBlock;
GlibState_t _Glib_LLRenderObj;
int _Glib_StartCycle;
int _Glib_Cycle;
int _Glib_BreakCycle;

void *memset();
void *memcpy();
void SysIncVsyncCounter(void);
void GXSetProjection(float (*pMtx)[4], int type);
void GlibRenderBegin(GlibState_t *pMode);
void TMRenderBeginFrame(void);
void TMRenderEndFrame(void);

int GlibVsync(int a);
void GlibClearZBuffer(void);
void GlibSetCopyFilter(GXBool enable);
static void _GlibScissor(void);
static void _GlibSetupScissor(GlibConfig_t *pConfig);

static int _GlibLogBase2(unsigned int value)
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

static void _GlibSnapFrameBuffer(void)
{
}

void GlibSetVsyncCallback(void (*callback)(void))
{
    _Glib_pCallback = callback;
}

void GlibSetVsyncCallbackAfter(void (*callback)(void))
{
    _Glib_pCallbackAfter = callback;
}

void GlibRemoveVsyncCallback(void)
{
    _Glib_pCallback = 0;
}

void GlibSetVsyncFlipEnable(int enable)
{
    _Glib_VsyncSwap = enable;
}

static void _GlibLLDrawDone(void)
{
    _Glib_Cycle = -_Glib_StartCycle;
}

static void _Glib_VIRetraceCallback(u32 retraceCount)
{
    SysIncVsyncCounter();
    if (_Glib_pCallback) {
        _Glib_pCallback();
    }
    if (_Glib_bBreakPoint) {
        GXDisableBreakPt();
    }
    if (_Glib_pCallbackAfter) {
        _Glib_pCallbackAfter();
    }
}

void GlibEnableVIRetraceCallback(int enable)
{
    if (enable) {
        VISetPostRetraceCallback(_Glib_VIRetraceCallback);
    } else {
        VISetPostRetraceCallback(0);
    }
}

int GlibLLInit(GlibConfig_t *pConfig)
{
    GlibConfig_t *pCfg;
    GlibState_t *pMode;
    GXRenderModeObj *pSrcMode = 0;
    void *pFifo;

    _Glib_LLInitBlock = *pConfig;
    pCfg = &_Glib_LLInitBlock;
    pMode = &_Glib_LLRenderObj;
    _Glib_Progressive = 0;
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
        pSrcMode = &GXNtsc480ProgFilt;
        _Glib_Progressive = 1;
        break;
    case 8:
        pSrcMode = &Pal574IntDfScale;
        break;
    }
    memset(pMode, 0, 0x3C);
    if (pCfg->mTvMode == 7) {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    } else if (pCfg->mTvMode == 8) {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    } else {
        GXAdjustForOverscan(pSrcMode, &pMode->mMode, 0, 16);
    }
    _Glib_fbSize = ((pMode->mMode.fbWidth + 15) & 0xFFF0) * pMode->mMode.xfbHeight * 2;
    pMode->mpXfb[1] = pMode->mpXfb[0] = fn_801D2B7C(_Glib_fbSize, 0, 0);
    pMode->mFrame = 0;
    _Glib_DoubleBuffered = 0;
    VIConfigure(&pMode->mMode);
    VISetNextFrameBuffer(pMode->mpXfb[pMode->mFrame]);
    pMode->mLog2Width = _GlibLogBase2(pCfg->mWidth);
    pMode->mLog2Height = _GlibLogBase2(pCfg->mHeight);
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
    GlibSetCopyFilter(1);
    if (pMode->mMode.aa) {
        GXSetPixelFmt(2, 0);
    } else {
        GXSetPixelFmt(0, 0);
    }
    VISetBlack(1);
    VIFlush();
    GXCopyDisp(pMode->mpXfb[pMode->mFrame], 1);
    VIFlush();
    GXCopyDisp(pMode->mpXfb[pMode->mFrame], 1);
    VIFlush();
    GlibVsync(0);
    if (pMode->mMode.viTVmode & 1) {
        VIWaitForRetrace();
    }
    VISetBlack(0);
    GXSetDrawDoneCallback(_GlibLLDrawDone);
    GlibEnableVIRetraceCallback(1);
    _GlibSetupScissor(pCfg);
    _Glib_bClear = 1;
    return 0;
}

int GlibLLShutdown(void)
{
    return 0;
}

void GlibSetUpRender(void)
{
    void *a;
    void *b;

    if (_Break) {
        GXFlush();
        GXGetFifoPtrs(GXGetCPUFifo(), &a, &b);
        GXEnableBreakPt(b);
    }
    GlibRenderBegin(&_Glib_LLRenderObj);
    TMRenderBeginFrame();
}

/* FAKEMATCH: inline helper chosen for codegen (its argument gives the target stmw r30 / li r30,0); written out in place GlibFinishRender is 0x54 bytes against 0x5C */
static inline void _GlibWaitDrawDone(int count)
{
    GXWaitDrawDone();
    _Glib_BreakCycle = count;
}

void GlibFinishRender(void)
{
    if (!_Glib_bClear) {
        GlibClearZBuffer();
    }
    TMRenderEndFrame();
    GXSetDrawDone();
    GXFlush();
    if (_Break) {
        GXDisableBreakPt();
        _GlibWaitDrawDone(0);
    }
}

int GlibVsync(int a)
{
    VIWaitForRetrace();
    return 0;
}

static void _GlibSetBreakpoint(void)
{
    void *a;
    void *b;

    GXFlush();
    GXGetFifoPtrs(GXGetCPUFifo(), &a, &b);
    GXEnableBreakPt(b);
}

void GlibSwapBuffers(void)
{
    if (_Glib_DoubleBuffered) {
        VISetNextFrameBuffer(_Glib_LLRenderObj.mpXfb[_Glib_LLRenderObj.mFrame]);
        VIFlush();
        VIWaitForRetrace();
        _Glib_LLRenderObj.mFrame ^= 1;
        _GlibScissor();
    } else {
        GXDrawDone();
        _GlibSnapFrameBuffer();
        VISetNextFrameBuffer(_Glib_LLRenderObj.mpXfb[0]);
        VIFlush();
        if (_bVIInt) {
            _GlibSetBreakpoint();
            _Glib_bBreakPoint = 1;
        } else {
            VIWaitForRetrace();
        }
        _Glib_StartCycle = 0;
        GXSetColorUpdate(1);
        GXSetZMode(1, 3, 1);
        GXCopyDisp(_Glib_LLRenderObj.mpXfb[0], _Glib_bClear);
        GXPixModeSync();
        _Glib_LLRenderObj.mFrame = 0;
    }
}

void GlibSetVIInt(unsigned char enable)
{
    _bVIInt = enable;
}

void GlibSyncFrame(void)
{
    GXDrawDone();
}

unsigned char GlibGetFrame(void)
{
    return _Glib_LLRenderObj.mFrame;
}

int GlibGetZDepthBits(void)
{
    return 0;
}

void *GlibGetFrameBufferAddr(int frame)
{
    return _Glib_LLRenderObj.mpXfb[frame];
}

void GlibClearZBuffer(void)
{
    GlibState_t *pMode = &_Glib_LLRenderObj;

    GXSetColorUpdate(0);
    GXSetZMode(0, 0, 1);
    GXSetDispCopyDst(0, 0);
    GXCopyDisp(garbage, 1);
    GXSetColorUpdate(1);
    GXSetZMode(1, 3, 1);
    GXSetDispCopyDst(pMode->mMode.fbWidth, pMode->mMode.xfbHeight);
}

void GlibSetZBufferEnable(GXBool enable)
{
    GXSetZMode(enable, 3, 1);
}

int GlibGetScreenWidth(void)
{
    return _Glib_LLInitBlock.mWidth;
}

int GlibGetScreenHeight(void)
{
    return _Glib_LLInitBlock.mHeight;
}

void GlibSetProjection(float (*pMatrix)[4])
{
    GXSetProjection(pMatrix, 0);
}

void GlibSetCopyFilter(GXBool enable)
{
    GXSetCopyFilter(_Glib_LLRenderObj.mMode.aa, _Glib_LLRenderObj.mMode.sample_pattern, enable, _Glib_LLRenderObj.mMode.vfilter);
}

void GlibSetClear(unsigned char clear)
{
    _Glib_bClear = clear;
}

void GlibSwitchToSingle(void)
{
    GlibState_t *pMode = &_Glib_LLRenderObj;

    VISetNextFrameBuffer(pMode->mpXfb[0]);
    VIFlush();
    VIWaitForRetrace();
    fn_801D2BD0(pMode->mpXfb[1]);
    _Glib_DoubleBuffered = 0;
    pMode->mFrame = 0;
    pMode->mpXfb[1] = pMode->mpXfb[0];
}

void GlibSwitchToDouble(int skipSwap)
{
    if (!skipSwap) {
        GlibSwapBuffers();
        GlibSwapBuffers();
    }
    _Glib_LLRenderObj.mpXfb[1] = fn_801D2B7C(_Glib_fbSize, 0, 0);
    memcpy(_Glib_LLRenderObj.mpXfb[1], _Glib_LLRenderObj.mpXfb[0], _Glib_fbSize);
    _Glib_DoubleBuffered = 1;
}

int GlibGetLetterBoxMode(void)
{
    return 0xFFFF;
}

int GlibGetWidescreenMode(void)
{
    return 0xFFFF;
}

void GlibToggleProgressive(int progressive)
{
    if (_Glib_Progressive != progressive) {
        _Glib_Progressive = progressive;
        VISetBlack(1);
        if (progressive) {
            GXAdjustForOverscan(&GXNtsc480ProgFilt, &_Glib_LLRenderObj.mMode, 0, 16);
        } else {
            GXAdjustForOverscan(&GXNtsc480IntDf, &_Glib_LLRenderObj.mMode, 0, 16);
        }
        VIConfigure(&_Glib_LLRenderObj.mMode);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VISetBlack(0);
        VIFlush();
        VIWaitForRetrace();
    }
}

static void _GlibScissor(void)
{
}

static void _GlibSetupScissor(GlibConfig_t *pConfig)
{
    GXSetScissor(0, 0, pConfig->mWidth - 1, pConfig->mHeight - 1);
}

void GlibSetScissor(int left, int width, int top, int height)
{
    GXSetScissor(left, top, width, height);
}

int GlibGetScreenLetterBoxHeight(void)
{
    return 0x150;
}

int GlibGetScreenLetterBoxWidth(void)
{
    return 0x280;
}

unsigned short GlibGetXFBHeight(void)
{
    return _Glib_LLRenderObj.mMode.xfbHeight;
}
