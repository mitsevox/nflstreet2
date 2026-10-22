#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

extern int lbl_803ECFC4;
extern ChunkDef_8020EA18 *lbl_803ECFC8;
extern unsigned int lbl_803ECFCC;

static ChunkDef_8020EA18 *fn_8020EA18(int tag)
{
    ChunkDef_8020EA18 *pDef;
    unsigned int i;

    pDef = 0;
    for (i = 0; i < lbl_803ECFCC; i++) {
        if (lbl_803ECFC8[i].mTag == tag) {
            pDef = &lbl_803ECFC8[i];
            break;
        }
    }
    return pDef;
}

static void fn_8020EA78(Chunk_8020EA18 *pChunk, ChunkDef_8020EA18 *pDef, ModelRes_8020EA18 *pRes)
{
    if (pDef != 0) {
        if (pChunk->mSize != 0) {
            if (pDef->mVersion == pChunk->mVersion) {
                pChunk->mpData = fn_8020EB94(pChunk->mpData, 0, pRes);
                if (pDef->mRelocate != 0) {
                    pDef->mRelocate(pChunk->mpData, 0, pRes);
                }
            } else {
                pChunk->mpData = 0;
            }
        }
    } else {
        pChunk->mpData = 0;
    }
}

void fn_8020EB08(int maxChunkTypes)
{
    lbl_803ECFC4 = maxChunkTypes;
    lbl_803ECFC8 = fn_801D2B7C(maxChunkTypes * sizeof(ChunkDef_8020EA18), 0, 0);
    lbl_803ECFCC = 0;
}

void fn_8020EB48(int tag, ChunkRelocFunc_8020EA18 relocate, int version)
{
    lbl_803ECFC8[lbl_803ECFCC].mTag = tag;
    lbl_803ECFC8[lbl_803ECFCC].mVersion = version;
    lbl_803ECFC8[lbl_803ECFCC].mRelocate = relocate;
    lbl_803ECFCC++;
}

void fn_8020EB70(void)
{
    fn_801D2BD0(lbl_803ECFC8);
}

void *fn_8020EB94(void *p, void *pOldBase, void *pNewBase)
{
    void *pResult;

    pResult = 0;
    if (p != 0) {
        pResult = (char *)p - (int)pOldBase + (int)pNewBase;
    }
    return pResult;
}

void fn_8020EBB0(ModelRes_8020EA18 *pRes)
{
    Chunk_8020EA18 *pChunks;
    ChunkDef_8020EA18 *pDef;
    unsigned int i;

    if (pRes->mbRelocated != 1) {
        pChunks = fn_8020EB94((void *)(unsigned int)pRes->mChunkOffset, 0, pRes);
        for (i = 0; i < pRes->mNumChunks; i++) {
            pDef = fn_8020EA18(pChunks[i].mTag);
            if (pChunks[i].mbRelocated == 0) {
                fn_8020EA78(&pChunks[i], pDef, pRes);
                pChunks[i].mbRelocated = 1;
            }
        }
        pRes->mbRelocated = 1;
    }
}

void *fn_8020EC50(ModelRes_8020EA18 *pRes, int tag, Chunk_8020EA18 **ppChunk)
{
    Chunk_8020EA18 *pChunks;
    void *pData;
    int i;

    pChunks = fn_8020EB94((void *)(unsigned int)pRes->mChunkOffset, 0, pRes);
    pData = 0;
    for (i = 0; i < pRes->mNumChunks; i++) {
        if (pChunks[i].mTag == tag && pChunks[i].mSize != 0) {
            pData = pChunks[i].mpData;
            break;
        }
    }
    if (ppChunk != 0) {
        *ppChunk = &pChunks[i];
    }
    return pData;
}
