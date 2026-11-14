#include "engine/moviercmp.h"

extern "C" {

int fn_801D9720(RcmpDecoder *pDecoder, RcmpCodec *pCodec, RcmpChunk_t *pChunk)
{
    pDecoder->mpChunk = pChunk;
    pDecoder->mpCodec = pCodec;
    return pCodec->fn_801D9DA4(pDecoder, pChunk);
}

void fn_801D9768(RcmpDecoder *pDecoder)
{
    if (pDecoder->mpCodec != 0) {
        delete pDecoder->mpCodec;
        pDecoder->mpCodec = 0;
    }
}

unsigned int fn_801D97C0(RcmpDecoder *pDecoder)
{
    if (pDecoder->mpCodec == 0) {
        return 0;
    }
    return pDecoder->mpCodec->fn_801D9DC0();
}

RcmpFrame_t *fn_801D9808(RcmpDecoder *pDecoder, unsigned int frame)
{
    if (pDecoder->mpCodec == 0) {
        if (pDecoder->mpChunk == 0) {
            pDecoder->mIData.mGet(pDecoder, pDecoder->mIData.mpStreamer, &pDecoder->mpChunk);
        }
    }
    if (pDecoder->mpCodec == 0) {
        return 0;
    }
    return pDecoder->mpCodec->fn_801DA20C(frame);
}

void fn_801D9894(RcmpDecoder *pDecoder, RcmpFrame_t *pFrame)
{
    pDecoder->mpCodec->fn_801DA418(pFrame);
}

RcmpChunk_t *fn_801D98CC(RcmpDecoder *pDecoder)
{
    RcmpChunk_t *pChunk;

    if (pDecoder->mpChunk != 0) {
        pChunk = pDecoder->mpChunk;
        pDecoder->mpChunk = 0;
        return pChunk;
    }
    pDecoder->mIData.mGet(pDecoder, pDecoder->mIData.mpStreamer, &pChunk);
    return pChunk;
}

void fn_801D9924(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk)
{
    pDecoder->mIData.mRelease(pDecoder, pDecoder->mIData.mpStreamer, pChunk);
}

RcmpChunk_t *fn_801D9958(RcmpChunk_t *pChunk)
{
    pChunk->mpData = 0;
    pChunk->mSize = 0;
    pChunk->mpHeader = 0;
    return pChunk;
}

RcmpCodecIData_t *fn_801D9970(RcmpCodecIData_t *pIData)
{
    pIData->mCount = 2;
    pIData->mpStreamer = 0;
    pIData->mGet = 0;
    pIData->mRelease = 0;
    return pIData;
}

RcmpCodecIData_t *fn_801D9990(RcmpCodecIData_t *pIData, void *pStreamer, RcmpGetChunkFunc_t get,
                                 RcmpReleaseChunkFunc_t release, int count)
{
    pIData->mCount = count;
    pIData->mpStreamer = pStreamer;
    pIData->mGet = get;
    pIData->mRelease = release;
    return pIData;
}

}
