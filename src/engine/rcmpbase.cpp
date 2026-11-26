/* RCMP movie decoder base: the allocator hooks every movie object allocates through, the frame
   decoder that feeds the chosen codec its chunks and asks it for frames, and the chunk and
   chunk-source records the movie player (src/engine/moviercmp.cpp) hands the decoder. */

#include "engine/moviercmp.h"

RcmpSystem gRcmpSystem;

RcmpSystem::RcmpSystem()
{
    mAlloc = 0;
    mFree = 0;
}

RcmpDecoder::RcmpDecoder(const RcmpCodecIData_t *pIData)
{
    mIData = *pIData;
    mpCodec = 0;
    mpChunk = 0;
}

RcmpDecoder::~RcmpDecoder()
{
    FreeChosenCodec();
}

int RcmpDecoder::ChooseCodec(RcmpCodec *pCodec, RcmpChunk_t *pChunk)
{
    mpChunk = pChunk;
    mpCodec = pCodec;
    return pCodec->fn_801D9DA4(this, pChunk);
}

void RcmpDecoder::FreeChosenCodec()
{
    if (mpCodec != 0) {
        delete mpCodec;
        mpCodec = 0;
    }
}

unsigned int RcmpDecoder::GetCurrentFrameNumber()
{
    if (mpCodec == 0) {
        return 0;
    }
    return mpCodec->fn_801D9DC0();
}

RcmpFrame_t *RcmpDecoder::GetFrame(unsigned int frame)
{
    if (mpCodec == 0) {
        if (mpChunk == 0) {
            mIData.mGet(this, mIData.mpStreamer, &mpChunk);
        }
    }
    if (mpCodec == 0) {
        return 0;
    }
    return mpCodec->fn_801DA20C(frame);
}

void RcmpDecoder::ReleaseFrame(RcmpFrame_t *pFrame)
{
    mpCodec->fn_801DA418(pFrame);
}

RcmpChunk_t *RcmpDecoder::GetChunk()
{
    RcmpChunk_t *pChunk;

    if (mpChunk != 0) {
        pChunk = mpChunk;
        mpChunk = 0;
        return pChunk;
    }
    mIData.mGet(this, mIData.mpStreamer, &pChunk);
    return pChunk;
}

void RcmpDecoder::ReleaseChunk(RcmpChunk_t *pChunk)
{
    mIData.mRelease(this, mIData.mpStreamer, pChunk);
}

RcmpChunk_t::RcmpChunk_t()
{
    mpData = 0;
    mSize = 0;
    mpHeader = 0;
}

RcmpCodecIData_t::RcmpCodecIData_t()
{
    mCount = 2;
    mpStreamer = 0;
    mGet = 0;
    mRelease = 0;
}

RcmpCodecIData_t::RcmpCodecIData_t(void *pStreamer, RcmpGetChunkFunc_t get, RcmpReleaseChunkFunc_t release,
                                   unsigned int count)
{
    mCount = count;
    mpStreamer = pStreamer;
    mGet = get;
    mRelease = release;
}
