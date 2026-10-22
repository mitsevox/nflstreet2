/* Render bins: bin list registration and per-frame viewport setup. */
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/vi/vifuncs.h>
#include "engine/cu_801CE1F8.h"
#include "engine/cu_801CEC90.h"

typedef struct RenderMark_801CEC90 {
    int mWords[4];
} RenderMark_801CEC90;

extern RenderBin_801CEC90 *lbl_803EBC90;
extern RenderMark_801CEC90 *lbl_803EBC98;
extern RenderBin_801CEC90 *lbl_803EBCA0;
extern int lbl_803EBCA4;


void fn_801CEE50(void);

void fn_801CEC90(RenderBin_801CEC90 *pBins, int numBins)
{
    fn_801CEE50();
    lbl_803EBCA0 = pBins;
    lbl_803EBCA4 = numBins;
}

void fn_801CECC8(void)
{
}

RenderBin_801CEC90 *fn_801CECCC(int index)
{
    return &lbl_803EBCA0[index];
}

RenderMark_801CEC90 *fn_801CECDC(RenderBin_801CEC90 *pBin)
{
    RenderBin_801CEC90 *pCurrent = lbl_803EBC90;

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

int fn_801CED2C(void)
{
    return 0;
}

int fn_801CED34(void)
{
    return 0;
}

void fn_801CED3C(GlibState_801CE1F8 *pMode)
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

void fn_801CEE50(void)
{
}
