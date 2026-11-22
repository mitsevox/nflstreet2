/* TM renderer model resources: the list of chunk types (Info, Geom, Matl, Skel ...) a model file
   can hold, relocation of a loaded model file's chunks, and lookup of a chunk by tag. */

#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

/* The chunk type capacity, the chunk definitions and how many are registered. */
static int _TMModelRes_NumChunkTypes;
static TMChunkDef_t *_TMModelRes_pChunkDefList;
static unsigned int _TMModelRes_nChunks;

static TMChunkDef_t *_TMModelResGetChunkDef(int tag)
{
    TMChunkDef_t *pDef;
    unsigned int i;

    pDef = 0;
    for (i = 0; i < _TMModelRes_nChunks; i++) {
        if (_TMModelRes_pChunkDefList[i].mTag == tag) {
            pDef = &_TMModelRes_pChunkDefList[i];
            break;
        }
    }
    return pDef;
}

static void _TMModelResRelocateChunk(TMChunk_t *pChunk, TMChunkDef_t *pDef, TMModelRes_t *pRes)
{
    if (pDef != 0) {
        if (pChunk->mSize != 0) {
            if (pDef->mVersion == pChunk->mVersion) {
                pChunk->mpData = TMModelResRelocatePtr(pChunk->mpData, 0, pRes);
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

void TMModelResInit(int maxChunkTypes)
{
    _TMModelRes_NumChunkTypes = maxChunkTypes;
    _TMModelRes_pChunkDefList = fn_801D2B7C(maxChunkTypes * sizeof(TMChunkDef_t), 0, 0);
    _TMModelRes_nChunks = 0;
}

void TMModelResAddChunkType(int tag, TMChunkRelocFunc_t relocate, int version)
{
    _TMModelRes_pChunkDefList[_TMModelRes_nChunks].mTag = tag;
    _TMModelRes_pChunkDefList[_TMModelRes_nChunks].mVersion = version;
    _TMModelRes_pChunkDefList[_TMModelRes_nChunks].mRelocate = relocate;
    _TMModelRes_nChunks++;
}

void TMModelResShutdown(void)
{
    fn_801D2BD0(_TMModelRes_pChunkDefList);
}

void *TMModelResRelocatePtr(void *p, void *pOldBase, void *pNewBase)
{
    void *pResult;

    pResult = 0;
    if (p != 0) {
        pResult = (char *)p - (int)pOldBase + (int)pNewBase;
    }
    return pResult;
}

void TMModelResRelocate(TMModelRes_t *pRes)
{
    TMChunk_t *pChunks;
    TMChunkDef_t *pDef;
    unsigned int i;

    if (pRes->mbRelocated != 1) {
        pChunks = TMModelResRelocatePtr((void *)(unsigned int)pRes->mChunkOffset, 0, pRes);
        for (i = 0; i < pRes->mNumChunks; i++) {
            pDef = _TMModelResGetChunkDef(pChunks[i].mTag);
            if (pChunks[i].mbRelocated == 0) {
                _TMModelResRelocateChunk(&pChunks[i], pDef, pRes);
                pChunks[i].mbRelocated = 1;
            }
        }
        pRes->mbRelocated = 1;
    }
}

void *TMModelResGetChunk(TMModelRes_t *pRes, int tag, TMChunk_t **ppChunk)
{
    TMChunk_t *pChunks;
    void *pData;
    int i;

    pChunks = TMModelResRelocatePtr((void *)(unsigned int)pRes->mChunkOffset, 0, pRes);
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
