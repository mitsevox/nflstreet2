/* Render bin initialisation and chunk lookup. */
#include "engine/cu_801CEC90.h"

typedef struct Chunk_801CEE54 {
    int mType;
    int mSize;
} Chunk_801CEE54;

void fn_801CEE54(RenderBin_801CEC90 *pBin)
{
    pBin->mActive = 1;
    pBin->mUnk28 = 0;
    pBin->mUnk30 = 0;
    pBin->mpNext = 0;
    pBin->mUnk38 = 0;
    pBin->mUnk3C = 0;
    pBin->mpMark = 0;
    pBin->mUnk44 = 0;
    pBin->mUnk48 = 0;
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

Chunk_801CEE54 *fn_801CEEF4(Chunk_801CEE54 *pChunk, int type, int endType, int index)
{
    int count = 0;
    Chunk_801CEE54 *pFound = 0;

    while (pChunk->mType != endType) {
        if (pChunk->mType == type) {
            if (count == index) {
                pFound = pChunk;
                break;
            }
            count++;
        }
        pChunk = (Chunk_801CEE54 *)((char *)pChunk + pChunk->mSize);
    }
    return pFound;
}
