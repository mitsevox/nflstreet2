#ifndef ENGINE_CU_801D86B4_H
#define ENGINE_CU_801D86B4_H

#include "engine/Info_801D86B4.h"

/* Movie player records shared by 0x801D86B4-0x801D94A0 (NASCAR 2005 moviercmp.cpp)
   and 0x801D94A0-0x801D9634 (llmoviercmp.cpp). */

/* Decoded frame image: a header followed by the Y, U and V planes. */
typedef struct Shape_801D94A0 {
    char mUnknown0[4];
    short mWidth;
    short mHeight;
    char mUnknown8[4];
    unsigned int mFlags;
    int mOffset;
} Shape_801D94A0;

/* Video state (0x14 bytes). */
typedef struct Video_801D86B4 {
    void *mpStream;
    struct Info_801D86B4 *mpInfo;
    class Decoder_801D86B4 *mpDecoder;
    unsigned int mCurFrame;
    unsigned int mGoalFrame;
} Video_801D86B4;

/* Audio state (0x24 bytes). */
typedef struct Audio_801D86B4 {
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
} Audio_801D86B4;

/* Chunk handed to the decoder (0xC bytes). */
typedef struct Chunk_801D86B4 {
    void *mpHeader;
    void *mpData;
    unsigned int mSize;
} Chunk_801D86B4;

/* Frame returned by the decoder. */
typedef struct Frame_801D86B4 {
    int mUnknown0;
    Shape_801D94A0 *mpShape;
} Frame_801D86B4;

class Decoder_801D86B4;

typedef void (*GetChunkFunc_801D9634)(Decoder_801D86B4 *pDecoder, void *pStreamer, Chunk_801D86B4 **ppChunk);
typedef void (*ReleaseChunkFunc_801D9634)(Decoder_801D86B4 *pDecoder, void *pStreamer, Chunk_801D86B4 *pChunk);

/* Chunk source handed to a decoder (0x10 bytes; NASCAR 2005 RCMP::CODEC_IDATA). */
struct CodecIData_801D9634 {
    void *mpStreamer;
    GetChunkFunc_801D9634 mGet;
    ReleaseChunkFunc_801D9634 mRelease;
    int mCount;
};

/* Codec interface (NASCAR 2005 RCMP::CODEC). The slots follow the MAD codec's table at
   0x802AFFD0, so the methods carry the labels of the MAD implementations. */
class Codec_801D9634 {
public:
    virtual ~Codec_801D9634();
    virtual int fn_801D9DA4(Decoder_801D86B4 *pDecoder, Chunk_801D86B4 *pChunk);
    virtual Frame_801D86B4 *fn_801DA20C(unsigned int frame);
    virtual unsigned int fn_801D9DC0();
    virtual float fn_801D9DC8();
    virtual void fn_801DA418(Frame_801D86B4 *pFrame);
};

/* Frame decoder (0x1C bytes; NASCAR 2005 RCMP::DECODER); its virtual table pointer follows
   the data at +0x18. */
class Decoder_801D86B4 {
public:
    Chunk_801D86B4 *mpChunk;
    CodecIData_801D9634 mIData;
    Codec_801D9634 *mpCodec;

    virtual ~Decoder_801D86B4();
};

/* Decoder operations (src/engine/cu_801D9634.cpp; NASCAR 2005 RCMP::DECODER methods ChooseCodec,
   FreeChosenCodec, GetCurrentFrameNumber, GetFrame, ReleaseFrame, GetChunk, ReleaseChunk). */
extern "C" {
int fn_801D9720(Decoder_801D86B4 *pDecoder, Codec_801D9634 *pCodec, Chunk_801D86B4 *pChunk);
void fn_801D9768(Decoder_801D86B4 *pDecoder);
unsigned int fn_801D97C0(Decoder_801D86B4 *pDecoder);
Frame_801D86B4 *fn_801D9808(Decoder_801D86B4 *pDecoder, unsigned int frame);
void fn_801D9894(Decoder_801D86B4 *pDecoder, Frame_801D86B4 *pFrame);
Chunk_801D86B4 *fn_801D98CC(Decoder_801D86B4 *pDecoder);
void fn_801D9924(Decoder_801D86B4 *pDecoder, Chunk_801D86B4 *pChunk);
}

/* Constructors of the chunk and chunk-source records (src/engine/cu_801D9634.cpp); they return
   the object. */
extern "C" {
Chunk_801D86B4 *fn_801D9958(Chunk_801D86B4 *pChunk);
CodecIData_801D9634 *fn_801D9970(CodecIData_801D9634 *pIData);
CodecIData_801D9634 *fn_801D9990(CodecIData_801D9634 *pIData, void *pStreamer, GetChunkFunc_801D9634 get,
                                 ReleaseChunkFunc_801D9634 release, int count);
}

/* llmoviercmp.cpp (src/engine/cu_801D94A0.cpp). */
int fn_801D95E4(void *pInfo, void *pChunk);
void fn_801D94A0(Shape_801D94A0 *pShape);
void fn_801D9538(Shape_801D94A0 *pShape, int type);

/* Chunk-type tests of rcmp_mad_codec_chunk_types.cpp and rcmp_vp6_codec_chunk_types.cpp. */
int fn_801DA4F8(int id);
int fn_801DC9C8(int id);
int fn_801DC9E0(int id);

/* Allocator hooks at 0x80399100. */
typedef struct Alloc_801D86B4 {
    void *(*mAlloc)(const char *pName, int size, int a, int b, int flags);
    int (*mFree)(void *pAddr);
    int mFlags;
} Alloc_801D86B4;

#endif
