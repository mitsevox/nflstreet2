#ifndef ENGINE_MOVIERCMP_H
#define ENGINE_MOVIERCMP_H

#include "engine/MovieRcmpInfo.h"

/* Movie player records shared by 0x801D86B4-0x801D94A0 (NASCAR 2005 moviercmp.cpp)
   and 0x801D94A0-0x801D9634 (llmoviercmp.cpp). */

/* Decoded frame image: a header followed by the Y, U and V planes. */
typedef struct Shape_t {
    char mUnknown0[4];
    short mWidth;
    short mHeight;
    char mUnknown8[4];
    unsigned int mFlags;
    int mOffset;
} Shape_t;

/* Video state (0x14 bytes). */
typedef struct MovieRcmpVideoInfo_t {
    void *mpStream;
    struct MovieRcmpInfo_t *mpInfo;
    class RcmpDecoder *mpDecoder;
    unsigned int mCurFrame;
    unsigned int mGoalFrame;
} MovieRcmpVideoInfo_t;

/* Audio state (0x24 bytes). */
typedef struct MovieRcmpAudioInfo_t {
    void *mpStream;
    void *mpBuffer;
    int mHandle;
    int mVoice;
    unsigned char mSync;
    char mPad11[3];
    int mStartTime;
    int mLastTime;
    int mDrift;
    unsigned char mActive;
    char mPad21[3];
} MovieRcmpAudioInfo_t;

/* Chunk handed to the decoder (0xC bytes). */
typedef struct RcmpChunk_t {
    void *mpHeader;
    void *mpData;
    unsigned int mSize;
} RcmpChunk_t;

/* Frame returned by the decoder. */
typedef struct RcmpFrame_t {
    int mUnknown0;
    Shape_t *mpShape;
} RcmpFrame_t;

class RcmpDecoder;

typedef void (*RcmpGetChunkFunc_t)(RcmpDecoder *pDecoder, void *pStreamer, RcmpChunk_t **ppChunk);
typedef void (*RcmpReleaseChunkFunc_t)(RcmpDecoder *pDecoder, void *pStreamer, RcmpChunk_t *pChunk);

/* Chunk source handed to a decoder (0x10 bytes; NASCAR 2005 RCMP::CODEC_IDATA). */
struct RcmpCodecIData_t {
    void *mpStreamer;
    RcmpGetChunkFunc_t mGet;
    RcmpReleaseChunkFunc_t mRelease;
    int mCount;
};

/* Codec interface (NASCAR 2005 RCMP::CODEC). The slots follow the MAD codec's table at
   0x802AFFD0, so the methods carry the labels of the MAD implementations. */
class RcmpCodec {
public:
    virtual ~RcmpCodec();
    virtual int fn_801D9DA4(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk);
    virtual RcmpFrame_t *fn_801DA20C(unsigned int frame);
    virtual unsigned int fn_801D9DC0();
    virtual float fn_801D9DC8();
    virtual void fn_801DA418(RcmpFrame_t *pFrame);
};

/* Frame decoder (0x1C bytes; NASCAR 2005 RCMP::DECODER); its virtual table pointer follows
   the data at +0x18. */
class RcmpDecoder {
public:
    RcmpChunk_t *mpChunk;
    RcmpCodecIData_t mIData;
    RcmpCodec *mpCodec;

    virtual ~RcmpDecoder();
};

/* Decoder operations (src/engine/cu_801D9634.cpp; NASCAR 2005 RCMP::DECODER methods ChooseCodec,
   FreeChosenCodec, GetCurrentFrameNumber, GetFrame, ReleaseFrame, GetChunk, ReleaseChunk). */
extern "C" {
int fn_801D9720(RcmpDecoder *pDecoder, RcmpCodec *pCodec, RcmpChunk_t *pChunk);
void fn_801D9768(RcmpDecoder *pDecoder);
unsigned int fn_801D97C0(RcmpDecoder *pDecoder);
RcmpFrame_t *fn_801D9808(RcmpDecoder *pDecoder, unsigned int frame);
void fn_801D9894(RcmpDecoder *pDecoder, RcmpFrame_t *pFrame);
RcmpChunk_t *fn_801D98CC(RcmpDecoder *pDecoder);
void fn_801D9924(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk);
}

/* Constructors of the chunk and chunk-source records (src/engine/cu_801D9634.cpp); they return
   the object. */
extern "C" {
RcmpChunk_t *fn_801D9958(RcmpChunk_t *pChunk);
RcmpCodecIData_t *fn_801D9970(RcmpCodecIData_t *pIData);
RcmpCodecIData_t *fn_801D9990(RcmpCodecIData_t *pIData, void *pStreamer, RcmpGetChunkFunc_t get,
                                 RcmpReleaseChunkFunc_t release, int count);
}

/* llmoviercmp.cpp (src/engine/llmoviercmp.cpp). */
int MovieRcmpHandleChunk(void *pInfo, void *pChunk);
void MovieRcmpRenderInit(Shape_t *pShape);
void MovieRcmpRenderShape(Shape_t *pShape, int type);

/* Chunk-type tests of rcmp_mad_codec_chunk_types.cpp and rcmp_vp6_codec_chunk_types.cpp. */
int MAD_CODEC_is_chunk_for_codec(int id);
int VP6_CODEC_is_head_chunk_for_codec(int id);
int VP6_CODEC_is_chunk_for_codec(int id);

/* Allocator hooks at 0x80399100, installed by MovieRcmpInitVideo. */
typedef struct RcmpAllocator_t {
    void *(*mAlloc)(const char *pName, int size, int a, int b, int flags);
    int (*mFree)(void *pAddr);
    int mFlags;

    /* Allocates through the installed hook with the stored flags. */
    void *Alloc(int size, const char *pName)
    {
        return mAlloc(pName, size, 0, 0, mFlags);
    }
} RcmpAllocator_t;

#endif
