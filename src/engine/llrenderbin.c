/* Render bin initialisation and chunk lookup. */
#include "engine/llrender.h"

typedef struct Chunk_t {
    int mType;
    int mSize;
} Chunk_t;

void GlibBinAlloc(RenderBin_t *pBin)
{
    pBin->mActive = 1;
    pBin->mUnk28 = 0;
    pBin->mUnk30 = 0;
    pBin->mpNext = 0;
    pBin->mpMark = 0;
    pBin->mUnk38 = 0;
    pBin->mUnk44 = 0;
    pBin->mUnk3C = 0;
    pBin->mUnk48 = 0;
}

void GlibBinAllocList(RenderBin_t *pBins, unsigned int numBins)
{
    unsigned int i;

    for (i = 0; i < numBins; i++) {
        GlibBinAlloc(&pBins[i]);
        pBins[i].mpNext = &pBins[i + 1];
    }
    pBins[i - 1].mpNext = 0;
}

Chunk_t *GlibFindChunk(Chunk_t *pChunk, int type, int endType, int index)
{
    int count = 0;
    Chunk_t *pFound = 0;

    while (pChunk->mType != endType) {
        if (pChunk->mType == type) {
            if (count == index) {
                pFound = pChunk;
                break;
            }
            count++;
        }
        pChunk = (Chunk_t *)((char *)pChunk + pChunk->mSize);
    }
    return pFound;
}
