#ifndef ENGINE_MOVIERCMP_H
#define ENGINE_MOVIERCMP_H

#include "engine/MovieRcmpInfo.h"

/* Movie player records shared by 0x801D86B4-0x801D94A0 (moviercmp.cpp)
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

/* Allocator hooks every RCMP object allocates through (0x10 bytes);
   MovieRcmpInitVideo installs them in the single instance gRcmpSystem. */
class RcmpSystem {
public:
    void *(*mAlloc)(const char *pName, int size, int a, int b, int flags);
    int (*mFree)(void *pAddr);
    int mFlags;

    RcmpSystem();
    virtual ~RcmpSystem() {}

    /* Allocates through the installed hook with the stored flags. */
    void *Alloc(int size, const char *pName)
    {
        return mAlloc(pName, size, 0, 0, mFlags);
    }
};

extern RcmpSystem gRcmpSystem;

/* Placement form the movie code constructs its objects in RCMP-allocated memory with. */
inline void *operator new(unsigned int size, void *p)
{
    return p;
}

/* Chunk handed to the decoder (0xC bytes). */
typedef struct RcmpChunk_t {
    void *mpHeader;
    void *mpData;
    unsigned int mSize;

    RcmpChunk_t();
} RcmpChunk_t;

/* Frame returned by the decoder. */
typedef struct RcmpFrame_t {
    int mUnknown0;
    Shape_t *mpShape;
} RcmpFrame_t;

class RcmpDecoder;

typedef void (*RcmpGetChunkFunc_t)(RcmpDecoder *pDecoder, void *pStreamer, RcmpChunk_t **ppChunk);
typedef void (*RcmpReleaseChunkFunc_t)(RcmpDecoder *pDecoder, void *pStreamer, RcmpChunk_t *pChunk);

/* Chunk source handed to a decoder (0x10 bytes). */
struct RcmpCodecIData_t {
    void *mpStreamer;
    RcmpGetChunkFunc_t mGet;
    RcmpReleaseChunkFunc_t mRelease;
    unsigned int mCount;

    RcmpCodecIData_t();
    RcmpCodecIData_t(void *pStreamer, RcmpGetChunkFunc_t get, RcmpReleaseChunkFunc_t release, unsigned int count);
};

/* Codec interface: a decoder for one movie format, chosen by the
   decoder from a movie's first chunk. Its table holds the destructor and five pure functions. */
class RcmpCodec {
public:
    void operator delete(void *p)
    {
        gRcmpSystem.mFree(p);
    }

    virtual ~RcmpCodec() {}
    virtual int Init(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk) = 0;
    virtual RcmpFrame_t *GetFrame(unsigned int frame) = 0;
    virtual unsigned int GetCurrentFrameNumber() = 0;
    virtual float GetFrameRate() = 0;
    virtual void ReleaseFrame(RcmpFrame_t *pFrame) = 0;
};

/* Frame decoder (0x1C bytes): hands the codec chosen for a movie its
   chunks and passes frame requests on to it. Its virtual table pointer follows the data at +0x18. */
class RcmpDecoder {
public:
    RcmpChunk_t *mpChunk;
    RcmpCodecIData_t mIData;
    RcmpCodec *mpCodec;

    RcmpDecoder(const RcmpCodecIData_t *pIData);
    virtual ~RcmpDecoder();

    int ChooseCodec(RcmpCodec *pCodec, RcmpChunk_t *pChunk);
    void FreeChosenCodec();
    unsigned int GetCurrentFrameNumber();
    RcmpFrame_t *GetFrame(unsigned int frame);
    void ReleaseFrame(RcmpFrame_t *pFrame);
    RcmpChunk_t *GetChunk();
    void ReleaseChunk(RcmpChunk_t *pChunk);

    void operator delete(void *p)
    {
        gRcmpSystem.mFree(p);
    }
};

/* llmoviercmp.cpp (src/engine/llmoviercmp.cpp). */
int MovieRcmpHandleChunk(void *pInfo, void *pChunk);
void MovieRcmpRenderInit(Shape_t *pShape);
void MovieRcmpRenderShape(Shape_t *pShape, int type);

/* Creates the MAD codec (src/engine/rcmp_mad_codec.cpp); Boot installs it as the MAD codec hook. */
RcmpCodec *MAD_CODEC_create();

/* Chunk-type tests of rcmp_mad_codec_chunk_types.cpp and rcmp_vp6_codec_chunk_types.cpp. */
int MAD_CODEC_is_chunk_for_codec(int id);
int VP6_CODEC_is_head_chunk_for_codec(int id);
int VP6_CODEC_is_chunk_for_codec(int id);

#endif
