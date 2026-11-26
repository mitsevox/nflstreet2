/* MAD movie codec: decodes the MAD video chunks of an RCMP movie (key frames, motion frames and
   their extra frames) into a small pool of YUV frame images that the movie player shows. */

#include "engine/moviercmp.h"
#include "engine/llmemory.h"
#include "engine/maddec.h"

/* Intrusive doubly linked list node; a list head is a node that points at itself when empty. */
struct MadListNode {
    MadListNode *mpNext;
    MadListNode *mpPrev;

    void Unlink()
    {
        MadListNode *pNext = mpNext;
        MadListNode *pPrev = mpPrev;

        pPrev->mpNext = pNext;
        pNext->mpPrev = pPrev;
    }

    void PushFront(MadListNode *pNode)
    {
        MadListNode *pFirst = mpNext;

        mpNext = pNode;
        pFirst->mpPrev = pNode;
        pNode->mpNext = pFirst;
        pNode->mpPrev = this;
    }
};

/* Decoded MAD frame (0x14 bytes): the frame record, a list node at +8
   and a use count. */
struct MadFrame : public RcmpFrame_t, public MadListNode {
    int mRefs;

    MadFrame(unsigned int width, unsigned int height);
    ~MadFrame();

    void *operator new(unsigned int size)
    {
        return gRcmpSystem.mAlloc("", size, 0, 0, gRcmpSystem.mFlags);
    }
    void operator delete(void *p)
    {
        gRcmpSystem.mFree(p);
    }
};

/* List of MAD frames linked through their node; it deletes the frames still in it. */
struct MadFrameList : public MadListNode {
    void DeleteAll()
    {
        while (mpNext != this) {
            MadListNode *pNode = mpNext;

            MadFrame *pFrame;

            pNode->Unlink();
            pFrame = static_cast<MadFrame *>(pNode);
            delete pFrame;
        }
    }

    MadFrameList()
    {
        mpNext = this;
        mpPrev = this;
    }

    ~MadFrameList()
    {
        DeleteAll();
    }

    void PushBack(MadFrame *pFrame)
    {
        MadListNode *pNode = pFrame;
        MadListNode *pLast = mpPrev;

        mpPrev = pNode;
        pLast->mpNext = pNode;
        pNode->mpNext = this;
        pNode->mpPrev = pLast;
    }

};

/* MAD codec state (0x34 bytes): frame rate, picture size, current frame, the used and free frame
   lists and the decoder that feeds it chunks. */
class MadCodec : public RcmpCodec {
public:
    float mFrameRate;
    int mRate;
    int mFirst;
    int mWidth;
    int mHeight;
    MadFrame *mpLast;
    unsigned int mCurFrame;
    MadFrameList mUsed;
    MadFrameList mFree;
    RcmpDecoder *mpDecoder;

    MadCodec();
    virtual ~MadCodec();
    virtual int Init(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk);
    virtual RcmpFrame_t *GetFrame(unsigned int frame);
    virtual unsigned int GetCurrentFrameNumber();
    virtual float GetFrameRate();
    virtual void ReleaseFrame(RcmpFrame_t *pFrame);
    void GetNextChunk(RcmpChunk_t **ppChunk);
    void ReleaseChunk(RcmpChunk_t *pChunk);
    MadFrame *DecodeChunk(RcmpChunk_t *pChunk);
    MadFrame *CreateKorM();
    MadFrame *CreateE();

    void *operator new(unsigned int size)
    {
        return gRcmpSystem.mAlloc("", size, 0, 0, gRcmpSystem.mFlags);
    }
};

unsigned int GetChunkType(RcmpChunk_t *pChunk)
{
    if (pChunk != 0) {
        return *(unsigned int *)pChunk->mpData;
    }
    return 0x4D41446B;
}

MadFrame::MadFrame(unsigned int width, unsigned int height)
{
    mRefs = 0;
    mUnknown0 = 1;
    mpShape = (Shape_t *)gRcmpSystem.mAlloc("MAD_FRAME::m_Shape", width * 3 * height / 2 + 0x10, 0, 0x10,
                                            gRcmpSystem.mFlags);
    MemFill((char *)mpShape, 0x10, 0, 4);
    mpShape->mUnknown0[0] = 0x6C;
    mpShape->mWidth = width;
    mpShape->mHeight = height;
}

MadFrame::~MadFrame()
{
    if (mpShape != 0) {
        gRcmpSystem.mFree(mpShape);
        mpShape = 0;
    }
}

MadCodec::MadCodec()
{
    mFirst = 1;
}

MadCodec::~MadCodec()
{
    while (mUsed.mpNext != &mUsed) {
        MadListNode *pNode = mUsed.mpNext;
        MadFrame *pFrame;

        pNode->Unlink();
        pFrame = static_cast<MadFrame *>(pNode);
        delete pFrame;
    }
    while (mFree.mpNext != &mFree) {
        MadListNode *pNode = mFree.mpNext;
        MadFrame *pFrame;

        pNode->Unlink();
        pFrame = static_cast<MadFrame *>(pNode);
        delete pFrame;
    }
}

int MadCodec::Init(RcmpDecoder *pDecoder, RcmpChunk_t *pChunk)
{
    mCurFrame = 0;
    mpDecoder = pDecoder;
    mpLast = 0;
    return 2;
}

unsigned int MadCodec::GetCurrentFrameNumber()
{
    return mCurFrame;
}

float MadCodec::GetFrameRate()
{
    return mFrameRate;
}

void MadCodec::GetNextChunk(RcmpChunk_t **ppChunk)
{
    *ppChunk = mpDecoder->GetChunk();
    mCurFrame++;
}

void MadCodec::ReleaseChunk(RcmpChunk_t *pChunk)
{
    if (pChunk != 0) {
        mpDecoder->ReleaseChunk(pChunk);
    }
}

MadFrame *MadCodec::DecodeChunk(RcmpChunk_t *pChunk)
{
    MadFrame *pFrame = 0;
    unsigned char *pHeader = (unsigned char *)pChunk->mpData;
    unsigned char *pRefY = 0;
    unsigned char *pRefU = 0;
    unsigned char *pRefV = 0;
    unsigned char *pY;
    unsigned char *pU;
    unsigned char *pV;
    int x;
    int y;

    if (mpLast != 0) {
        Shape_t *pShape = mpLast->mpShape;

        if (pShape->mFlags & 0x10000000) {
            pRefY = (unsigned char *)pShape + pShape->mOffset;
        } else {
            pRefY = (unsigned char *)&pShape->mOffset;
        }
        pRefU = pRefY + mWidth * mHeight;
        pRefV = pRefY + mWidth * 5 * mHeight / 4;
    }
    if (mFirst != 0) {
        int count;
        unsigned char *pRate = pHeader + 0xC;

        mRate = (pRate[3] << 24 | pRate[2] << 16 | pRate[1] << 8 | pRate[0]);
        mFrameRate = 1000.0f / (mRate * 1.5259022e-05f);
        mWidth = pHeader[0x11] << 8 | pHeader[0x10];
        mHeight = pHeader[0x13] << 8 | pHeader[0x12];
        count = mpDecoder->mIData.mCount + 1;
        for (y = 0; y < count; y++) {
            int width = mWidth;
            int height = mHeight;

            mFree.PushFront(new MadFrame(width, height));
        }
        mFirst = 0;
    }
    if (GetChunkType(pChunk) == 0x4D41446B) {
        if (mpLast != 0) {
            ReleaseFrame(mpLast);
        }
        mpLast = 0;
        pFrame = CreateKorM();
        MAD_initdecode((const unsigned short *)(pHeader + 0x18), 0, (signed char)pHeader[0x15]);
    } else if (GetChunkType(pChunk) == 0x4D41446D) {
        pFrame = CreateKorM();
        MAD_initdecode((const unsigned short *)(pHeader + 0x18), 1, (signed char)pHeader[0x15]);
    } else if (GetChunkType(pChunk) == 0x4D414465) {
        pFrame = CreateE();
        MAD_initdecode((const unsigned short *)(pHeader + 0x18), 1, (signed char)pHeader[0x15]);
    }
    if (pFrame->mpShape->mFlags & 0x10000000) {
        pY = (unsigned char *)pFrame->mpShape + pFrame->mpShape->mOffset;
    } else {
        pY = (unsigned char *)&pFrame->mpShape->mOffset;
    }
    pU = pY + mWidth * mHeight;
    pV = pY + mWidth * 5 * mHeight / 4;
    for (y = 0; y < mHeight; y += 16) {
        for (x = 0; x < mWidth; x += 16) {
            int offset = y * mWidth + x;
            int chroma = y * mWidth / 4 + x / 2;

            MAD_decodemacroblock(pRefY + offset, pRefU + chroma, pRefV + chroma, pY + offset, pU + chroma, pV + chroma, mWidth);
        }
    }
    if (GetChunkType(pChunk) == 0x4D41446D) {
        if (mpLast != 0) {
            ReleaseFrame(mpLast);
        }
        mpLast = pFrame;
    } else if (GetChunkType(pChunk) == 0x4D41446B) {
        mpLast = pFrame;
    }
    return pFrame;
}

RcmpFrame_t *MadCodec::GetFrame(unsigned int frame)
{
    RcmpChunk_t *pChunk;

    GetNextChunk(&pChunk);
    if (mFirst == 0) {
        int skip = frame - mCurFrame;

        if (skip > 2) {
            do {
                ReleaseChunk(pChunk);
                GetNextChunk(&pChunk);
            } while (GetChunkType(pChunk) != 0x4D41446B);
        } else if (skip > 0) {
            int i;

            for (i = 0; i < skip; i++) {
                if (GetChunkType(pChunk) == 0x4D414465) {
                    ReleaseChunk(pChunk);
                    GetNextChunk(&pChunk);
                }
            }
        }
    }
    if (pChunk != 0) {
        MadFrame *pFrame = DecodeChunk(pChunk);

        ReleaseChunk(pChunk);
        return pFrame;
    }
    if (mpLast != 0) {
        ReleaseFrame(mpLast);
        mpLast = 0;
    }
    return 0;
}

MadFrame *MadCodec::CreateKorM()
{
    MadListNode *pNode;
    MadFrame *pFrame;

    if (mFree.mpNext != &mFree) {
        pNode = mFree.mpNext;
        pNode->Unlink();
        pFrame = static_cast<MadFrame *>(pNode);
        mUsed.PushBack(pFrame);
        pFrame->mRefs = 2;
        return pFrame;
    }
    return 0;
}

MadFrame *MadCodec::CreateE()
{
    MadListNode *pNode;
    MadFrame *pFrame;

    if (mFree.mpNext != &mFree) {
        pNode = mFree.mpNext;
        pNode->Unlink();
        pFrame = static_cast<MadFrame *>(pNode);
        mUsed.PushBack(pFrame);
        pFrame->mRefs = 1;
        return pFrame;
    }
    return 0;
}

void MadCodec::ReleaseFrame(RcmpFrame_t *pFrame)
{
    MadFrame *pMadFrame = (MadFrame *)pFrame;

    if (--pMadFrame->mRefs > 0) {
        return;
    }
    pMadFrame->Unlink();
    mFree.PushBack(pMadFrame);
}

RcmpCodec *MAD_CODEC_create()
{
    return new MadCodec;
}
