#include "engine/cu_801D86B4.h"

extern "C" {

int fn_801D9720(Decoder_801D86B4 *pDecoder, Codec_801D9634 *pCodec, Chunk_801D86B4 *pChunk)
{
    pDecoder->mpChunk = pChunk;
    pDecoder->mpCodec = pCodec;
    return pCodec->fn_801D9DA4(pDecoder, pChunk);
}

void fn_801D9768(Decoder_801D86B4 *pDecoder)
{
    if (pDecoder->mpCodec != 0) {
        delete pDecoder->mpCodec;
        pDecoder->mpCodec = 0;
    }
}

unsigned int fn_801D97C0(Decoder_801D86B4 *pDecoder)
{
    if (pDecoder->mpCodec == 0) {
        return 0;
    }
    return pDecoder->mpCodec->fn_801D9DC0();
}

Frame_801D86B4 *fn_801D9808(Decoder_801D86B4 *pDecoder, unsigned int frame)
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

void fn_801D9894(Decoder_801D86B4 *pDecoder, Frame_801D86B4 *pFrame)
{
    pDecoder->mpCodec->fn_801DA418(pFrame);
}

Chunk_801D86B4 *fn_801D98CC(Decoder_801D86B4 *pDecoder)
{
    Chunk_801D86B4 *pChunk;

    if (pDecoder->mpChunk != 0) {
        pChunk = pDecoder->mpChunk;
        pDecoder->mpChunk = 0;
        return pChunk;
    }
    pDecoder->mIData.mGet(pDecoder, pDecoder->mIData.mpStreamer, &pChunk);
    return pChunk;
}

void fn_801D9924(Decoder_801D86B4 *pDecoder, Chunk_801D86B4 *pChunk)
{
    pDecoder->mIData.mRelease(pDecoder, pDecoder->mIData.mpStreamer, pChunk);
}

Chunk_801D86B4 *fn_801D9958(Chunk_801D86B4 *pChunk)
{
    pChunk->mpData = 0;
    pChunk->mSize = 0;
    pChunk->mpHeader = 0;
    return pChunk;
}

CodecIData_801D9634 *fn_801D9970(CodecIData_801D9634 *pIData)
{
    pIData->mCount = 2;
    pIData->mpStreamer = 0;
    pIData->mGet = 0;
    pIData->mRelease = 0;
    return pIData;
}

CodecIData_801D9634 *fn_801D9990(CodecIData_801D9634 *pIData, void *pStreamer, GetChunkFunc_801D9634 get,
                                 ReleaseChunkFunc_801D9634 release, int count)
{
    pIData->mCount = count;
    pIData->mpStreamer = pStreamer;
    pIData->mGet = get;
    pIData->mRelease = release;
    return pIData;
}

}
