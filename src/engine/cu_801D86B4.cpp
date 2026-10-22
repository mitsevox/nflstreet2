#include <dolphin/os.h>
#include "game/fn_801D2B7C.h"
#include "engine/cu_801D86B4.h"
#include "engine/llmemory.h"

extern "C" {
int fn_801CE1E8(void);
void fn_801CAF24(void);
void fn_801F4B20(void);
void *fn_801F73D4(void *pStream);
void fn_801F74D4(void *pStream, void *pHeader);
int fn_801F7644(void *pStream);
int fn_801F3E28(void);
void fn_8026CA50(void *pConfig);
int fn_8026EE24(int a, int b);
int fn_8026EA80(void *pStream, void *pConfig, int a, int b, void *pBuffer, int size);
int fn_8026EF0C(int voice, int a, int b);
void fn_8026E2A8(int voice);
void fn_8026D0AC(void);
void fn_8026EF88(int handle, void *pStatus);
void fn_8026D0EC(void);
int fn_8026CAA8(void);
Decoder_801D86B4 *fn_801D9654(void *pMem, CodecIData_801D9634 *pIData);
int fn_801DA4F8(int id);
int fn_801DC9E0(int id);
int fn_801DC9C8(int id);
/* Defined with C++ linkage in cu_801D94A0.cpp; referenced here by their neutral labels,
   which are the names the comparison link resolves until that unit is accepted. */
int fn_801D95E4(void *pInfo, void *pChunk);
void fn_801D94A0(Shape_801D94A0 *pShape);
void fn_801D9538(Shape_801D94A0 *pShape, int type);
}


extern Alloc_801D86B4 lbl_80399100;
extern Codec_801D9634 *(*lbl_803EBD44)(void);
extern Codec_801D9634 *(*lbl_803EBD48)(void);

extern "C" void fn_801D8CD8(Audio_801D86B4 *pAudio);

/* Low memory globals: the bus clock is at 0x800000F8. */
typedef struct LowMem_801D86B4 {
    char mPad[0xF8];
    unsigned int mBusClock;
} LowMem_801D86B4;

#define TIMER_CLOCK_801D86B4 (((LowMem_801D86B4 *)0x80000000)->mBusClock / 4)

static inline unsigned int fn_801D86B4_le32(unsigned char *p)
{
    return p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
}

static inline int fn_801D86B4_busy(Decoder_801D86B4 *pDecoder)
{
    return pDecoder->mpCodec != 0;
}

void *fn_801D86B4(const char *pName, int size, int a, int b, int flags)
{
    return fn_801D2B7C(size, 0, 0);
}

int fn_801D86E0(void *pAddr)
{
    fn_801D2BD0(pAddr);
    return 1;
}

void fn_801D8704(Audio_801D86B4 *pAudio)
{
    void *pHeader;

    fn_801CAF24();
    if (pAudio != 0 && pAudio->mActive != 0) {
        if (pAudio->mHandle >= 0) {
            fn_801F4B20();
        } else {
            while ((pHeader = fn_801F73D4(pAudio->mpStream)) != 0) {
                fn_801F74D4(pAudio->mpStream, pHeader);
            }
        }
    }
}

Shape_801D94A0 *fn_801D8770(void *pFrame)
{
    return ((Frame_801D86B4 *)pFrame)->mpShape;
}

void fn_801D8778(Decoder_801D86B4 *pDecoder, Info_801D86B4 **ppStreamer, Chunk_801D86B4 **ppChunk)
{
    Info_801D86B4 *pInfo = *ppStreamer;
    void *pStream = pInfo->mpVideo->mpStream;
    int codec = 0;
    unsigned char *pHeader;
    Chunk_801D86B4 *pChunk;

    *ppChunk = 0;
    do {
        pHeader = (unsigned char *)fn_801F73D4(pStream);
        if (fn_801D95E4(pInfo, pHeader) == 0) {
            return;
        }
        fn_801D8704(pInfo->mpAudio);
        if (pHeader != 0) {
            int id = *(int *)pHeader;

            if (fn_801DA4F8(id) != 0) {
                codec = 2;
            }
            if (fn_801DC9E0(id) != 0) {
                codec = 5;
            }
            if (fn_801DC9C8(id) != 0) {
                codec = 4;
            }
            pInfo->mCodec = codec;
            if (codec != 0) {
                pChunk = fn_801D9958((Chunk_801D86B4 *)lbl_80399100.mAlloc("", sizeof(Chunk_801D86B4), 0, 0, lbl_80399100.mFlags));
                *ppChunk = pChunk;
                pChunk->mpHeader = pHeader;
                if (codec == 2) {
                    pChunk->mSize = fn_801D86B4_le32(pHeader + 4);
                    pChunk->mpData = pHeader;
                } else if (codec == 4 || codec == 5) {
                    pChunk->mSize = fn_801D86B4_le32(pHeader + 4);
                    pChunk->mpData = pHeader;
                } else {
                    pChunk->mSize = fn_801D86B4_le32(pHeader + 4);
                    pChunk->mpData = pHeader + 8;
                }
                if (fn_801D86B4_busy(pDecoder)) {
                    return;
                }
                if (codec == 2 && lbl_803EBD44 != 0) {
                    if (fn_801D9720(pDecoder, lbl_803EBD44(), pChunk) != 2) {
                        fn_801D9768(pDecoder);
                    }
                }
                if (codec == 4 && lbl_803EBD48 != 0) {
                    if (fn_801D9720(pDecoder, lbl_803EBD48(), pChunk) != 2) {
                        fn_801D9768(pDecoder);
                    }
                }
                return;
            }
            fn_801F74D4(pStream, pHeader);
        }
    } while (fn_801F7644(pStream) == 0);
}

void fn_801D89D4(Decoder_801D86B4 *pDecoder, Info_801D86B4 **ppStreamer, Chunk_801D86B4 *pChunk)
{
    fn_801F74D4((*ppStreamer)->mpVideo->mpStream, pChunk->mpHeader);
    if (pChunk != 0) {
        lbl_80399100.mFree(pChunk);
    }
}

extern "C" {

void fn_801D8A2C(Info_801D86B4 *pInfo, void *pStream)
{
    Video_801D86B4 *pVideo;
    Audio_801D86B4 *pAudio;
    CodecIData_801D9634 iData;

    lbl_80399100.mAlloc = fn_801D86B4;
    lbl_80399100.mFree = fn_801D86E0;
    lbl_80399100.mFlags = 1;
    pVideo = (Video_801D86B4 *)fn_801D2B7C(sizeof(Video_801D86B4), 0, 0);
    pAudio = (Audio_801D86B4 *)fn_801D2B7C(sizeof(Audio_801D86B4), 0, 0);
    pInfo->mpVideo = pVideo;
    pInfo->mpAudio = pAudio;
    fn_801D34D0((char *)pVideo, sizeof(Video_801D86B4), 0, 4);
    pVideo->mpStream = pStream;
    pVideo->mCurFrame = 0;
    pVideo->mGoalFrame = 0;
    fn_801D34D0((char *)pAudio, sizeof(Audio_801D86B4), 0, 4);
    pAudio->mSync = 0;
    pAudio->mActive = 0;
    pAudio->mHandle = -1;
    fn_801D8CD8(pAudio);
    pVideo->mpInfo = pInfo;
    fn_801D9990(&iData, &pVideo->mpInfo, (GetChunkFunc_801D9634)fn_801D8778, (ReleaseChunkFunc_801D9634)fn_801D89D4, 2);
    pVideo->mpDecoder = fn_801D9654(lbl_80399100.mAlloc("", 0x1C, 0, 0, lbl_80399100.mFlags), &iData);
}

void fn_801D8B54(Info_801D86B4 *pInfo)
{
    Video_801D86B4 *pVideo = pInfo->mpVideo;

    delete pVideo->mpDecoder;
    pVideo->mpDecoder = 0;
    fn_801D2BD0(pInfo->mpAudio);
    pInfo->mpAudio = 0;
    fn_801D2BD0(pVideo);
    pInfo->mpVideo = 0;
}

int fn_801D8BC8(Info_801D86B4 *pInfo, void *pStream, int volume)
{
    Audio_801D86B4 *pAudio = pInfo->mpAudio;
    int handle;
    int config[6];

    pAudio->mpStream = pStream;
    if (fn_801F3E28() != 0) {
        int size;

        fn_8026CA50(config);
        size = fn_8026EE24(1, 0x1E);
        pAudio->mpBuffer = fn_801D2B7C(size, 0, 0);
        pAudio->mVoice = fn_8026EA80(pAudio->mpStream, config, 1, 0x1E, pAudio->mpBuffer, size);
        handle = fn_8026EF0C(pAudio->mVoice, 0, volume);
    } else {
        handle = -1;
    }
    pAudio->mHandle = handle;
    pAudio->mActive = 1;
    fn_801D8CD8(pAudio);
    return handle;
}

void fn_801D8C84(Info_801D86B4 *pInfo)
{
    Audio_801D86B4 *pAudio = pInfo->mpAudio;

    if (pAudio->mHandle >= 0) {
        fn_8026E2A8(pAudio->mVoice);
    }
    if (pAudio->mpBuffer != 0) {
        fn_801D2BD0(pAudio->mpBuffer);
        pAudio->mpBuffer = 0;
    }
}

void fn_801D8CD8(Audio_801D86B4 *pAudio)
{
    pAudio->mSync = pAudio->mHandle >= 0;
    switch (fn_801CE1E8()) {
    case 1:
        pAudio->mStartTime = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 50;
        break;
    case 0:
    default:
        pAudio->mStartTime = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 60;
        break;
    }
    pAudio->mDrift = pAudio->mLastTime = 0;
}

int fn_801D8DE8(Info_801D86B4 *pInfo)
{
    Audio_801D86B4 *pAudio = pInfo->mpAudio;
    int now;
    int time;
    int status[4];

    switch (fn_801CE1E8()) {
    case 1:
        now = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 50;
        break;
    case 0:
    default:
        now = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 60;
        break;
    }
    time = now - pAudio->mStartTime;

    if (pAudio->mSync != 0) {
        int played;

        fn_8026D0AC();
        fn_8026EF88(pAudio->mHandle, status);
        fn_8026D0EC();
        played = status[1] - fn_8026CAA8();
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
    switch (fn_801CE1E8()) {
    case 1:
        return (int)((time + 40) * (1.0f / 40.0f));
    case 0:
    default:
        return (int)((time + 33) * (1.0f / 33.3667f));
    }
}

int fn_801D900C(Info_801D86B4 *pInfo)
{
    unsigned int goal = fn_801D8DE8(pInfo);

    if (pInfo->mpAudio->mSync != 0) {
        if (goal > pInfo->mpVideo->mCurFrame + 2) {
            switch (fn_801CE1E8()) {
            case 1:
                pInfo->mpAudio->mStartTime = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 50 - pInfo->mpAudio->mLastTime;
                break;
            case 0:
            default:
                pInfo->mpAudio->mStartTime = OSGetTime() * 60 / (TIMER_CLOCK_801D86B4) * 1000 / 60 - pInfo->mpAudio->mLastTime;
                break;
            }
            goal = fn_801D8DE8(pInfo);
        }
    } else {
        if (goal > pInfo->mpVideo->mCurFrame + 2) {
            switch (fn_801CE1E8()) {
            case 1:
                pInfo->mpAudio->mStartTime += (int)((goal - (pInfo->mpVideo->mCurFrame + 2)) * 40.0f);
                break;
            case 0:
            default:
                pInfo->mpAudio->mStartTime += (int)((goal - (pInfo->mpVideo->mCurFrame + 2)) * 33.3667f);
                break;
            }
            goal = fn_801D8DE8(pInfo);
        }
    }
    pInfo->mpVideo->mGoalFrame = goal;
    return goal >= pInfo->mpVideo->mCurFrame + 1;
}

unsigned int fn_801D9224(Info_801D86B4 *pInfo)
{
    return pInfo->mpVideo->mGoalFrame;
}

unsigned int fn_801D9230(Info_801D86B4 *pInfo)
{
    return pInfo->mpVideo->mCurFrame;
}

Frame_801D86B4 *fn_801D923C(Info_801D86B4 *pInfo, unsigned int frame)
{
    Frame_801D86B4 *pFrame = fn_801D9808(pInfo->mpVideo->mpDecoder, frame);

    if (pFrame != 0) {
        pInfo->mpVideo->mCurFrame = fn_801D97C0(pInfo->mpVideo->mpDecoder);
    }
    return pFrame;
}

void fn_801D9290(Info_801D86B4 *pInfo, Frame_801D86B4 *pFrame)
{
    fn_801D9894(pInfo->mpVideo->mpDecoder, pFrame);
}

void fn_801D92B8(Frame_801D86B4 *pFrame, unsigned char **ppY, unsigned char **ppU, unsigned char **ppV)
{
    Shape_801D94A0 *pShape = pFrame->mpShape;
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

void fn_801D9320(Frame_801D86B4 *pFrame, int *pWidth, int *pHeight)
{
    Shape_801D94A0 *pShape = fn_801D8770(pFrame);

    *pWidth = pShape->mWidth;
    *pHeight = pShape->mHeight;
}

void fn_801D9360(void *pStream, void *pAudioStream, int volume, int (*pCallback)(void *), void *pContext)
{
    Info_801D86B4 info;
    Frame_801D86B4 *pFrame;

    fn_801D8A2C(&info, pStream);
    pFrame = fn_801D923C(&info, 0);
    if (pFrame != 0) {
        Shape_801D94A0 *pShape = fn_801D8770(pFrame);

        fn_801D94A0(pShape);
        fn_801D9538(pShape, info.mCodec);
        fn_801D9290(&info, pFrame);
        fn_801D8BC8(&info, pAudioStream, volume);
        do {
            if (fn_801D900C(&info) != 0) {
                pFrame = fn_801D923C(&info, fn_801D9224(&info));
                if (pFrame != 0) {
                    fn_801D9538(fn_801D8770(pFrame), info.mCodec);
                    fn_801D9290(&info, pFrame);
                }
            }
            if (pCallback != 0 && pCallback(pContext) == 0) {
                pFrame = 0;
            }
        } while (pFrame != 0);
        fn_801D8C84(&info);
    } else if (pCallback != 0) {
        pCallback(pContext);
    }
    fn_801D8B54(&info);
}

int fn_801D9494(Codec_801D9634 *(*pCodec)(void))
{
    lbl_803EBD44 = pCodec;
    return 1;
}

}
