/* Movie playback for the RCMP movie format (the start-up movies of src/game/Boot.cpp): opens
   the video and audio streams of a movie, feeds the frame decoder its chunks, keeps the picture
   in step with the sound or the clock, and plays a whole movie frame by frame. */

#include <dolphin/os.h>
#include "game/fn_801D2B7C.h"
#include "engine/moviercmp.h"
#include "engine/llmemory.h"

extern "C" {
int GlibGetTvMode(void);
void FileDebugProcess(void);
void SndService(void);
void *fn_801F73D4(void *pStream);
void fn_801F74D4(void *pStream, void *pHeader);
int fn_801F7644(void *pStream);
int SndEnabled(void);
void SNDplaysetdef(void *pConfig);
int SNDSTRM_overheadtap(int a, int b);
int SNDSTRM_createtap(void *pStream, void *pConfig, int a, int b, void *pBuffer, int size);
int SNDSTRM_queuerequestid(int voice, int a, int b);
void fn_8026E2A8(int voice);
void SNDSYS_entercritical(void);
void fn_8026EF88(int handle, void *pStatus);
void SNDSYS_leavecritical(void);
int SNDPROFILE_outputlatency(void);
RcmpDecoder *fn_801D9654(void *pMem, RcmpCodecIData_t *pIData);
}


extern RcmpAllocator_t lbl_80399100;
static RcmpCodec *(*_MovieRcmp_pfnMadCodecCreate)(void) = 0;
static RcmpCodec *(*_MovieRcmp_pfnVp6CodecCreate)(void) = 0;

extern "C" void MovieRcmpResetTime(MovieRcmpAudioInfo_t *pAudio);


void *_MovieRcmpAllocMem(const char *pName, int size, int a, int b, int flags)
{
    return fn_801D2B7C(size, 0, 0);
}

int _MovieRcmpFreeMem(void *pAddr)
{
    fn_801D2BD0(pAddr);
    return 1;
}

void _MovieRcmpProcessAudio(MovieRcmpAudioInfo_t *pAudio)
{
    void *pHeader;

    FileDebugProcess();
    if (pAudio != 0 && pAudio->mActive != 0) {
        if (pAudio->mHandle >= 0) {
            SndService();
        } else {
            while ((pHeader = fn_801F73D4(pAudio->mpStream)) != 0) {
                fn_801F74D4(pAudio->mpStream, pHeader);
            }
        }
    }
}

Shape_t *_MovieRcmpGetShapeFromFrame(void *pFrame)
{
    return ((RcmpFrame_t *)pFrame)->mpShape;
}

void _MovieRcmpGetChunk(RcmpDecoder *pDecoder, MovieRcmpInfo_t **ppStreamer, RcmpChunk_t **ppChunk)
{
    MovieRcmpInfo_t *pInfo = *ppStreamer;
    void *pStream = pInfo->mpVideo->mpStream;
    int codec = 0;
    unsigned char *pHeader;
    RcmpChunk_t *pChunk;

    *ppChunk = 0;
    do {
        pHeader = (unsigned char *)fn_801F73D4(pStream);
        if (MovieRcmpHandleChunk(pInfo, pHeader) == 0) {
            return;
        }
        _MovieRcmpProcessAudio(pInfo->mpAudio);
        if (pHeader != 0) {
            int id = *(int *)pHeader;

            if (MAD_CODEC_is_chunk_for_codec(id) != 0) {
                codec = 2;
            }
            if (VP6_CODEC_is_chunk_for_codec(id) != 0) {
                codec = 5;
            }
            if (VP6_CODEC_is_head_chunk_for_codec(id) != 0) {
                codec = 4;
            }
            pInfo->mCodec = codec;
            if (codec != 0) {
                pChunk = fn_801D9958((RcmpChunk_t *)lbl_80399100.Alloc(sizeof(RcmpChunk_t), ""));
                *ppChunk = pChunk;
                pChunk->mpHeader = pHeader;
                if (codec == 2) {
                    unsigned char *pSize = pHeader + 4;

                    pChunk->mSize = (pSize[3] << 24 | pSize[2] << 16 | pSize[1] << 8 | pSize[0]);
                    pChunk->mpData = pHeader;
                } else if (codec == 4 || codec == 5) {
                    unsigned char *pSize = pHeader + 4;

                    pChunk->mSize = (pSize[3] << 24 | pSize[2] << 16 | pSize[1] << 8 | pSize[0]);
                    pChunk->mpData = pHeader;
                } else {
                    unsigned char *pSize = pHeader + 4;

                    pChunk->mSize = (pSize[3] << 24 | pSize[2] << 16 | pSize[1] << 8 | pSize[0]);
                    pChunk->mpData = pHeader + 8;
                }
                bool hasCodec = pDecoder->mpCodec != 0;

                if (hasCodec) {
                    return;
                }
                if (codec == 2 && _MovieRcmp_pfnMadCodecCreate != 0) {
                    if (fn_801D9720(pDecoder, _MovieRcmp_pfnMadCodecCreate(), pChunk) != 2) {
                        fn_801D9768(pDecoder);
                    }
                }
                if (codec == 4 && _MovieRcmp_pfnVp6CodecCreate != 0) {
                    if (fn_801D9720(pDecoder, _MovieRcmp_pfnVp6CodecCreate(), pChunk) != 2) {
                        fn_801D9768(pDecoder);
                    }
                }
                return;
            }
            fn_801F74D4(pStream, pHeader);
        }
    } while (fn_801F7644(pStream) == 0);
}

void _MovieRcmpReleaseChunk(RcmpDecoder *pDecoder, MovieRcmpInfo_t **ppStreamer, RcmpChunk_t *pChunk)
{
    fn_801F74D4((*ppStreamer)->mpVideo->mpStream, pChunk->mpHeader);
    if (pChunk != 0) {
        lbl_80399100.mFree(pChunk);
    }
}

extern "C" {

void MovieRcmpInitVideo(MovieRcmpInfo_t *pInfo, void *pStream)
{
    MovieRcmpVideoInfo_t *pVideo;
    MovieRcmpAudioInfo_t *pAudio;
    RcmpCodecIData_t iData;

    lbl_80399100.mAlloc = _MovieRcmpAllocMem;
    lbl_80399100.mFree = _MovieRcmpFreeMem;
    lbl_80399100.mFlags = 1;
    pVideo = (MovieRcmpVideoInfo_t *)fn_801D2B7C(sizeof(MovieRcmpVideoInfo_t), 0, 0);
    pAudio = (MovieRcmpAudioInfo_t *)fn_801D2B7C(sizeof(MovieRcmpAudioInfo_t), 0, 0);
    pInfo->mpVideo = pVideo;
    pInfo->mpAudio = pAudio;
    MemFill((char *)pVideo, sizeof(MovieRcmpVideoInfo_t), 0, 4);
    pVideo->mpStream = pStream;
    pVideo->mCurFrame = 0;
    pVideo->mGoalFrame = 0;
    MemFill((char *)pAudio, sizeof(MovieRcmpAudioInfo_t), 0, 4);
    pAudio->mSync = 0;
    pAudio->mActive = 0;
    pAudio->mHandle = -1;
    MovieRcmpResetTime(pAudio);
    pVideo->mpInfo = pInfo;
    fn_801D9990(&iData, &pVideo->mpInfo, (RcmpGetChunkFunc_t)_MovieRcmpGetChunk, (RcmpReleaseChunkFunc_t)_MovieRcmpReleaseChunk, 2);
    pVideo->mpDecoder = fn_801D9654(lbl_80399100.Alloc(0x1C, ""), &iData);
}

void MovieRcmpShutdownVideo(MovieRcmpInfo_t *pInfo)
{
    MovieRcmpVideoInfo_t *pVideo = pInfo->mpVideo;

    delete pVideo->mpDecoder;
    pVideo->mpDecoder = 0;
    fn_801D2BD0(pInfo->mpAudio);
    pInfo->mpAudio = 0;
    fn_801D2BD0(pVideo);
    pInfo->mpVideo = 0;
}

int MovieRcmpInitAudio(MovieRcmpInfo_t *pInfo, void *pStream, int volume)
{
    MovieRcmpAudioInfo_t *pAudio = pInfo->mpAudio;
    int handle;
    int config[6];

    pAudio->mpStream = pStream;
    if (SndEnabled() != 0) {
        int size;

        SNDplaysetdef(config);
        size = SNDSTRM_overheadtap(1, 0x1E);
        pAudio->mpBuffer = fn_801D2B7C(size, 0, 0);
        pAudio->mVoice = SNDSTRM_createtap(pAudio->mpStream, config, 1, 0x1E, pAudio->mpBuffer, size);
        handle = SNDSTRM_queuerequestid(pAudio->mVoice, 0, volume);
    } else {
        handle = -1;
    }
    pAudio->mHandle = handle;
    pAudio->mActive = 1;
    MovieRcmpResetTime(pAudio);
    return handle;
}

void MovieRcmpShutdownAudio(MovieRcmpInfo_t *pInfo)
{
    MovieRcmpAudioInfo_t *pAudio = pInfo->mpAudio;

    if (pAudio->mHandle >= 0) {
        fn_8026E2A8(pAudio->mVoice);
    }
    if (pAudio->mpBuffer != 0) {
        fn_801D2BD0(pAudio->mpBuffer);
        pAudio->mpBuffer = 0;
    }
}

void MovieRcmpResetTime(MovieRcmpAudioInfo_t *pAudio)
{
    pAudio->mSync = pAudio->mHandle >= 0;
    switch (GlibGetTvMode()) {
    case 1:
        pAudio->mStartTime = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 50;
        break;
    case 0:
    default:
        pAudio->mStartTime = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 60;
        break;
    }
    pAudio->mDrift = pAudio->mLastTime = 0;
}

int MovieRcmpGetTime(MovieRcmpInfo_t *pInfo)
{
    MovieRcmpAudioInfo_t *pAudio = pInfo->mpAudio;
    int now;
    int time;
    int status[4];

    switch (GlibGetTvMode()) {
    case 1:
        now = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 50;
        break;
    case 0:
    default:
        now = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 60;
        break;
    }
    time = now - pAudio->mStartTime;

    if (pAudio->mSync != 0) {
        int played;

        SNDSYS_entercritical();
        fn_8026EF88(pAudio->mHandle, status);
        SNDSYS_leavecritical();
        played = status[1] - SNDPROFILE_outputlatency();
        if (played > pAudio->mLastTime) {
            int delta = played - time;

            pAudio->mLastTime = played;
            pAudio->mDrift = pAudio->mDrift - pAudio->mDrift / 8 + delta;
            if ((pAudio->mDrift < 0 ? -pAudio->mDrift : pAudio->mDrift) > 0x108) {
                pAudio->mStartTime -= pAudio->mDrift / 8;
                pAudio->mDrift = 0;
                time = now - pAudio->mStartTime;
            }
        }
    }
    switch (GlibGetTvMode()) {
    case 1:
        return (int)((time + 40) * (1.0f / 40.0f));
    case 0:
    default:
        return (int)((time + 33) * (1.0f / 33.3667f));
    }
}

int MovieRcmpIsDecodeTime(MovieRcmpInfo_t *pInfo)
{
    unsigned int goal = MovieRcmpGetTime(pInfo);

    if (pInfo->mpAudio->mSync != 0) {
        if (goal > pInfo->mpVideo->mCurFrame + 2) {
            switch (GlibGetTvMode()) {
            case 1:
                pInfo->mpAudio->mStartTime = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 50 - pInfo->mpAudio->mLastTime;
                break;
            case 0:
            default:
                pInfo->mpAudio->mStartTime = OSGetTime() * 60 / OS_TIMER_CLOCK * 1000 / 60 - pInfo->mpAudio->mLastTime;
                break;
            }
            goal = MovieRcmpGetTime(pInfo);
        }
    } else {
        if (goal > pInfo->mpVideo->mCurFrame + 2) {
            switch (GlibGetTvMode()) {
            case 1:
                pInfo->mpAudio->mStartTime += (int)((goal - (pInfo->mpVideo->mCurFrame + 2)) * 40.0f);
                break;
            case 0:
            default:
                pInfo->mpAudio->mStartTime += (int)((goal - (pInfo->mpVideo->mCurFrame + 2)) * 33.3667f);
                break;
            }
            goal = MovieRcmpGetTime(pInfo);
        }
    }
    pInfo->mpVideo->mGoalFrame = goal;
    return goal >= pInfo->mpVideo->mCurFrame + 1;
}

unsigned int MovieRcmpGetGoalFrame(MovieRcmpInfo_t *pInfo)
{
    return pInfo->mpVideo->mGoalFrame;
}

unsigned int MovieRcmpGetCurFrame(MovieRcmpInfo_t *pInfo)
{
    return pInfo->mpVideo->mCurFrame;
}

RcmpFrame_t *MovieRcmpGetFrame(MovieRcmpInfo_t *pInfo, unsigned int frame)
{
    RcmpFrame_t *pFrame = fn_801D9808(pInfo->mpVideo->mpDecoder, frame);

    if (pFrame != 0) {
        pInfo->mpVideo->mCurFrame = fn_801D97C0(pInfo->mpVideo->mpDecoder);
    }
    return pFrame;
}

void MovieRcmpReleaseFrame(MovieRcmpInfo_t *pInfo, RcmpFrame_t *pFrame)
{
    fn_801D9894(pInfo->mpVideo->mpDecoder, pFrame);
}

void MovieRcmpGetDataFromFrame(RcmpFrame_t *pFrame, unsigned char **ppY, unsigned char **ppU, unsigned char **ppV)
{
    Shape_t *pShape = pFrame->mpShape;
    unsigned char *pData;

    if (pShape->mFlags & 0x10000000) {
        pData = (unsigned char *)pShape + pShape->mOffset;
    } else {
        pData = (unsigned char *)&pShape->mOffset;
    }
    *ppY = pData;
    *ppU = pData + pShape->mWidth * pShape->mHeight;
    *ppV = *ppU + (pShape->mWidth / 2) * (pShape->mHeight / 2);
}

void MovieRcmpGetSizeFromFrame(RcmpFrame_t *pFrame, int *pWidth, int *pHeight)
{
    Shape_t *pShape = _MovieRcmpGetShapeFromFrame(pFrame);

    *pWidth = pShape->mWidth;
    *pHeight = pShape->mHeight;
}

void MovieRcmpPlay(void *pStream, void *pAudioStream, int volume, int (*pCallback)(void *), void *pContext)
{
    MovieRcmpInfo_t info;
    RcmpFrame_t *pFrame;

    MovieRcmpInitVideo(&info, pStream);
    pFrame = MovieRcmpGetFrame(&info, 0);
    if (pFrame != 0) {
        Shape_t *pShape = _MovieRcmpGetShapeFromFrame(pFrame);

        MovieRcmpRenderInit(pShape);
        MovieRcmpRenderShape(pShape, info.mCodec);
        MovieRcmpReleaseFrame(&info, pFrame);
        MovieRcmpInitAudio(&info, pAudioStream, volume);
        do {
            if (MovieRcmpIsDecodeTime(&info) != 0) {
                pFrame = MovieRcmpGetFrame(&info, MovieRcmpGetGoalFrame(&info));
                if (pFrame != 0) {
                    MovieRcmpRenderShape(_MovieRcmpGetShapeFromFrame(pFrame), info.mCodec);
                    MovieRcmpReleaseFrame(&info, pFrame);
                }
            }
            if (pCallback != 0 && pCallback(pContext) == 0) {
                pFrame = 0;
            }
        } while (pFrame != 0);
        MovieRcmpShutdownAudio(&info);
    } else if (pCallback != 0) {
        pCallback(pContext);
    }
    MovieRcmpShutdownVideo(&info);
}

int MovieRcmpInstallMADCOWCodec(RcmpCodec *(*pCodec)(void))
{
    _MovieRcmp_pfnMadCodecCreate = pCodec;
    return 1;
}

}
