/* Render bins: bin list registration and per-frame viewport setup. */
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/vi/vifuncs.h>
#include "engine/llglib.h"
#include "engine/llrender.h"

typedef struct RenderMark_t {
    int mWords[4];
} RenderMark_t;

static RenderBin_t *_GlibRender_pCurrentBin = 0;
static int _GlibRender_iUnused0 = 0;
RenderMark_t *gGlibRenderMarkCursor = 0;
static int _GlibRender_iUnused1 = 0;
static RenderBin_t *_GlibRender_pBinList = 0;
static int _GlibRender_iNumBins = 0;


void GlibRenderFlush(void);

void GlibRenderSetBinList(RenderBin_t *pBins, int numBins)
{
    GlibRenderFlush();
    _GlibRender_pBinList = pBins;
    _GlibRender_iNumBins = numBins;
}

void GlibRenderSetDefaultBin(void)
{
}

RenderBin_t *GlibRenderGetBin(int index)
{
    return &_GlibRender_pBinList[index];
}

RenderMark_t *GlibRenderSelectBin(RenderBin_t *pBin)
{
    RenderBin_t *pCurrent = _GlibRender_pCurrentBin;

    if (pCurrent != pBin) {
        if (pCurrent) {
            pCurrent->mpMark = gGlibRenderMarkCursor++;
        }
        if (pBin && pBin->mpMark) {
            pBin->mpMark = 0;
        }
        _GlibRender_pCurrentBin = pBin;
    }
    return gGlibRenderMarkCursor;
}

int GlibRenderInit(void)
{
    return 0;
}

int GlibRenderShutdown(void)
{
    return 0;
}

void GlibRenderBegin(GlibState_t *pMode)
{
    float width;
    float height;

    GXInvalidateTexAll();
    if (pMode->mMode.field_rendering) {
        width = (unsigned int)pMode->mMode.fbWidth;
        height = (unsigned int)pMode->mMode.xfbHeight;
        GXSetViewportJitter(0.0f, 0.0f, width, height, 0.0f, 1.0f, VIGetNextField());
    } else {
        GXSetViewport(0.0f, 0.0f, (unsigned int)pMode->mMode.fbWidth, (unsigned int)pMode->mMode.xfbHeight, 0.0f, 1.0f);
    }
    GXInvalidateVtxCache();
}

void GlibRenderFlush(void)
{
}
