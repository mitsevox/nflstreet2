/* Render bins: bin list registration, per-frame viewport setup and bin initialisation. */
#include "engine/cu_801CE1F8.h"

typedef struct RenderBin_801CEC90 {
    unsigned char mUnk0[0x24];
    unsigned char mActive;
    int mUnk28;
    int mUnk2C;
    int mUnk30;
    struct RenderBin_801CEC90 *mpNext;
    int mUnk38;
    int mUnk3C;
    void *mpMark;
    int mUnk44;
    int mUnk48;
    unsigned char mUnk4C[0x30];
} RenderBin_801CEC90;

typedef struct RenderMark_801CEC90 {
    int mWords[4];
} RenderMark_801CEC90;

typedef struct Chunk_801CEC90 {
    int mType;
    int mSize;
} Chunk_801CEC90;

extern RenderBin_801CEC90 *lbl_803EBC90;
extern RenderMark_801CEC90 *lbl_803EBC98;
extern RenderBin_801CEC90 *lbl_803EBCA0;
extern int lbl_803EBCA4;

void fn_8024DCD4(void);
void fn_8025089C(void);
int fn_80244AC4(void);
void fn_80252734(float left, float top, float width, float height, float nearZ, float farZ, int field);
void fn_8025278C(float left, float top, float width, float height, float nearZ, float farZ);

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

    fn_8025089C();
    if (pMode->mFieldRendering) {
        width = (unsigned int)pMode->mFbWidth;
        height = (unsigned int)pMode->mXfbHeight;
        fn_80252734(0.0f, 0.0f, width, height, 0.0f, 1.0f, fn_80244AC4());
    } else {
        fn_8025278C(0.0f, 0.0f, (unsigned int)pMode->mFbWidth, (unsigned int)pMode->mXfbHeight, 0.0f, 1.0f);
    }
    fn_8024DCD4();
}

void fn_801CEE50(void)
{
}

static void fn_801CEE54(RenderBin_801CEC90 *pBin)
{
    pBin->mUnk28 = 0;
    pBin->mUnk30 = 0;
    pBin->mpNext = 0;
    pBin->mpMark = 0;
    pBin->mUnk38 = 0;
    pBin->mUnk44 = 0;
    pBin->mUnk3C = 0;
    pBin->mUnk48 = 0;
    pBin->mActive = 1;
}

void fn_801CEE84(RenderBin_801CEC90 *pBins, unsigned int numBins)
{
    unsigned int i;

    for (i = 0; i < numBins; i++) {
        fn_801CEE54(&pBins[i]);
        pBins[i].mpNext = &pBins[i + 1];
    }
    pBins[i - 1].mpNext = 0;
}

Chunk_801CEC90 *fn_801CEEF4(Chunk_801CEC90 *pChunk, int type, int endType, int index)
{
    int count = 0;
    Chunk_801CEC90 *pFound = 0;

    while (pChunk->mType != endType) {
        if (pChunk->mType == type) {
            if (count == index) {
                pFound = pChunk;
                break;
            }
            count++;
        }
        pChunk = (Chunk_801CEC90 *)((char *)pChunk + pChunk->mSize);
    }
    return pFound;
}
