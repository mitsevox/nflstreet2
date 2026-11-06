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

extern RenderBin_t *lbl_803EBC90;
extern RenderMark_t *lbl_803EBC98;
extern RenderBin_t *lbl_803EBCA0;
extern int lbl_803EBCA4;


void GlibRenderFlush(void);

void GlibRenderSetBinList(RenderBin_t *pBins, int numBins)
{
    GlibRenderFlush();
    lbl_803EBCA0 = pBins;
    lbl_803EBCA4 = numBins;
}

void GlibRenderSetDefaultBin(void)
{
}

RenderBin_t *GlibRenderGetBin(int index)
{
    return &lbl_803EBCA0[index];
}

RenderMark_t *GlibRenderSelectBin(RenderBin_t *pBin)
{
    RenderBin_t *pCurrent = lbl_803EBC90;

    if (pCurrent != pBin) {
        if (pCurrent) {
            pCurrent->mpMark = lbl_803EBC98++;
        }
        if (pBin && pBin->mpMark) {
            pBin->mpMark = 0;
        }
        lbl_803EBC90 = pBin;
    }
    return lbl_803EBC98;
}

int GlibRenderInit(void)
{
    return 0;
}

int GlibRenderShutdown(void)
{
    return 0;
}

void GlibRenderBegin(GlibState_801CE1F8 *pMode)
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
