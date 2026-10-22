#include "engine/cu_801D86B4.h"
#include "engine/llmemory.h"

/* Intrusive doubly linked list node; a list head is a node that points at itself when empty. */
struct Node_801D9A88 {
    Node_801D9A88 *mpNext;
    Node_801D9A88 *mpPrev;

    void Unlink()
    {
        Node_801D9A88 *pNext = mpNext;
        Node_801D9A88 *pPrev = mpPrev;

        pPrev->mpNext = pNext;
        pNext->mpPrev = pPrev;
    }

    void PushFront(Node_801D9A88 *pNode)
    {
        Node_801D9A88 *pFirst = mpNext;

        mpNext = pNode;
        pFirst->mpPrev = pNode;
        pNode->mpNext = pFirst;
        pNode->mpPrev = this;
    }

};

/* Decoded MAD frame (0x14 bytes; NASCAR 2005 MAD_FRAME): the frame record, a list node at +8
   and a use count. */
struct MadFrame_801D9A88 : public Frame_801D86B4, public Node_801D9A88 {
    int mRefs;
};

/* List of MAD frames linked through their node. */
struct FrameList_801D9A88 : public Node_801D9A88 {
    void PushBack(MadFrame_801D9A88 *pFrame)
    {
        Node_801D9A88 *pNode = pFrame;
        Node_801D9A88 *pLast = mpPrev;

        mpPrev = pNode;
        pLast->mpNext = pNode;
        pNode->mpNext = this;
        pNode->mpPrev = pLast;
    }
};

/* MAD codec state (0x34 bytes; NASCAR 2005 MAD_CODEC_INTERNAL). */
class MadCodec_801D9A88 : public Codec_801D9634 {
public:
    float mFrameRate;
    int mRate;
    int mFirst;
    int mWidth;
    int mHeight;
    MadFrame_801D9A88 *mpLast;
    unsigned int mCurFrame;
    FrameList_801D9A88 mUsed;
    FrameList_801D9A88 mFree;
    Decoder_801D86B4 *mpDecoder;

    virtual ~MadCodec_801D9A88();
    virtual int fn_801D9DA4(Decoder_801D86B4 *pDecoder, Chunk_801D86B4 *pChunk);
    virtual Frame_801D86B4 *fn_801DA20C(unsigned int frame);
    virtual unsigned int fn_801D9DC0();
    virtual float fn_801D9DC8();
    virtual void fn_801DA418(Frame_801D86B4 *pFrame);
    void fn_801D9DD0(Chunk_801D86B4 **ppChunk);
    void fn_801D9E14(Chunk_801D86B4 *pChunk);
    MadFrame_801D9A88 *fn_801D9E40(Chunk_801D86B4 *pChunk);
    MadFrame_801D9A88 *fn_801DA338();
    MadFrame_801D9A88 *fn_801DA3A8();
};

extern "C" {
MadCodec_801D9A88 *fn_801D9BC8(void *pMem);
/* maddec.cpp (C++ linkage there); referenced by neutral label for the comparison link. */
void fn_801DABE0(const unsigned short *pData, int frame, int quant);
void fn_801DAD20(const unsigned char *pRefY, const unsigned char *pRefU, const unsigned char *pRefV,
                 unsigned char *pDstY, unsigned char *pDstU, unsigned char *pDstV, int stride);
}

extern Alloc_801D86B4 lbl_80399100;
extern const char lbl_802AFFA8[];
extern const char lbl_802AFFAC[];

static inline unsigned char *fn_801D9A88_planes(Shape_801D94A0 *pShape)
{
    if (pShape->mFlags & 0x10000000) {
        return (unsigned char *)pShape + pShape->mOffset;
    }
    return (unsigned char *)&pShape->mOffset;
}

static inline unsigned int fn_801D9A88_le32(unsigned char *p)
{
    return p[3] << 24 | p[2] << 16 | p[1] << 8 | p[0];
}

unsigned int fn_801D9A88(Chunk_801D86B4 *pChunk)
{
    if (pChunk != 0) {
        return *(unsigned int *)pChunk->mpData;
    }
    return 0x4D41446B;
}

extern "C" MadFrame_801D9A88 *fn_801D9AA8(MadFrame_801D9A88 *pFrame, unsigned int width, unsigned int height)
{
    pFrame->mRefs = 0;
    pFrame->mUnknown0 = 1;
    pFrame->mpShape = (Shape_801D94A0 *)lbl_80399100.mAlloc(lbl_802AFFAC, width * 3 * height / 2 + 0x10, 0, 0x10,
                                                           lbl_80399100.mFlags);
    fn_801D34D0((char *)pFrame->mpShape, 0x10, 0, 4);
    pFrame->mpShape->mUnknown0[0] = 0x6C;
    pFrame->mpShape->mWidth = width;
    pFrame->mpShape->mHeight = height;
    return pFrame;
}

int MadCodec_801D9A88::fn_801D9DA4(Decoder_801D86B4 *pDecoder, Chunk_801D86B4 *pChunk)
{
    mCurFrame = 0;
    mpDecoder = pDecoder;
    mpLast = 0;
    return 2;
}

unsigned int MadCodec_801D9A88::fn_801D9DC0()
{
    return mCurFrame;
}

float MadCodec_801D9A88::fn_801D9DC8()
{
    return mFrameRate;
}

void MadCodec_801D9A88::fn_801D9DD0(Chunk_801D86B4 **ppChunk)
{
    *ppChunk = fn_801D98CC(mpDecoder);
    mCurFrame++;
}

void MadCodec_801D9A88::fn_801D9E14(Chunk_801D86B4 *pChunk)
{
    if (pChunk != 0) {
        fn_801D9924(mpDecoder, pChunk);
    }
}

MadFrame_801D9A88 *MadCodec_801D9A88::fn_801D9E40(Chunk_801D86B4 *pChunk)
{
    MadFrame_801D9A88 *pFrame = 0;
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
        pRefY = fn_801D9A88_planes(mpLast->mpShape);
        pRefU = pRefY + mWidth * mHeight;
        pRefV = pRefY + mWidth * 5 * mHeight / 4;
    }
    if (mFirst != 0) {
        int i;
        int count;

        mRate = fn_801D9A88_le32(pHeader + 0xC);
        mFrameRate = 1000.0f / (mRate * 1.5259022e-05f);
        mWidth = pHeader[0x11] << 8 | pHeader[0x10];
        mHeight = pHeader[0x13] << 8 | pHeader[0x12];
        count = mpDecoder->mIData.mCount + 1;
        for (i = 0; i < count; i++) {
            int width = mWidth;
            int height = mHeight;
            void *pMem = lbl_80399100.mAlloc(lbl_802AFFA8, sizeof(MadFrame_801D9A88), 0, 0, lbl_80399100.mFlags);

            mFree.PushFront(fn_801D9AA8((MadFrame_801D9A88 *)pMem, width, height));
        }
        mFirst = 0;
    }
    if (fn_801D9A88(pChunk) == 0x4D41446B) {
        if (mpLast != 0) {
            fn_801DA418(mpLast);
        }
        mpLast = 0;
        pFrame = fn_801DA338();
        fn_801DABE0((const unsigned short *)(pHeader + 0x18), 0, (signed char)pHeader[0x15]);
    } else if (fn_801D9A88(pChunk) == 0x4D41446D) {
        pFrame = fn_801DA338();
        fn_801DABE0((const unsigned short *)(pHeader + 0x18), 1, (signed char)pHeader[0x15]);
    } else if (fn_801D9A88(pChunk) == 0x4D414465) {
        pFrame = fn_801DA3A8();
        fn_801DABE0((const unsigned short *)(pHeader + 0x18), 1, (signed char)pHeader[0x15]);
    }
    pY = fn_801D9A88_planes(pFrame->mpShape);
    pU = pY + mWidth * mHeight;
    pV = pY + mWidth * 5 * mHeight / 4;
    for (y = 0; y < mHeight; y += 16) {
        for (x = 0; x < mWidth; x += 16) {
            int offset = y * mWidth + x;
            int chroma = y * mWidth / 4 + x / 2;

            fn_801DAD20(pRefY + offset, pRefU + chroma, pRefV + chroma, pY + offset, pU + chroma, pV + chroma, mWidth);
        }
    }
    if (fn_801D9A88(pChunk) == 0x4D41446D) {
        if (mpLast != 0) {
            fn_801DA418(mpLast);
        }
        mpLast = pFrame;
    } else if (fn_801D9A88(pChunk) == 0x4D41446B) {
        mpLast = pFrame;
    }
    return pFrame;
}

Frame_801D86B4 *MadCodec_801D9A88::fn_801DA20C(unsigned int frame)
{
    Chunk_801D86B4 *pChunk;

    fn_801D9DD0(&pChunk);
    if (mFirst == 0) {
        int skip = frame - mCurFrame;

        if (skip > 2) {
            do {
                fn_801D9E14(pChunk);
                fn_801D9DD0(&pChunk);
            } while (fn_801D9A88(pChunk) != 0x4D41446B);
        } else if (skip > 0) {
            int i;

            for (i = 0; i < skip; i++) {
                if (fn_801D9A88(pChunk) == 0x4D414465) {
                    fn_801D9E14(pChunk);
                    fn_801D9DD0(&pChunk);
                }
            }
        }
    }
    if (pChunk != 0) {
        MadFrame_801D9A88 *pFrame = fn_801D9E40(pChunk);

        fn_801D9E14(pChunk);
        return pFrame;
    }
    if (mpLast != 0) {
        fn_801DA418(mpLast);
        mpLast = 0;
    }
    return 0;
}

MadFrame_801D9A88 *MadCodec_801D9A88::fn_801DA338()
{
    Node_801D9A88 *pNode;
    MadFrame_801D9A88 *pFrame;

    if (mFree.mpNext != &mFree) {
        pNode = mFree.mpNext;
        pNode->Unlink();
        pFrame = static_cast<MadFrame_801D9A88 *>(pNode);
        mUsed.PushBack(pFrame);
        pFrame->mRefs = 2;
        return pFrame;
    }
    return 0;
}

MadFrame_801D9A88 *MadCodec_801D9A88::fn_801DA3A8()
{
    Node_801D9A88 *pNode;
    MadFrame_801D9A88 *pFrame;

    if (mFree.mpNext != &mFree) {
        pNode = mFree.mpNext;
        pNode->Unlink();
        pFrame = static_cast<MadFrame_801D9A88 *>(pNode);
        mUsed.PushBack(pFrame);
        pFrame->mRefs = 1;
        return pFrame;
    }
    return 0;
}

void MadCodec_801D9A88::fn_801DA418(Frame_801D86B4 *pFrame)
{
    MadFrame_801D9A88 *pMadFrame = (MadFrame_801D9A88 *)pFrame;

    if (--pMadFrame->mRefs > 0) {
        return;
    }
    pMadFrame->Unlink();
    mFree.PushBack(pMadFrame);
}

Codec_801D9634 *fn_801DA46C()
{
    return fn_801D9BC8(lbl_80399100.mAlloc(lbl_802AFFA8, sizeof(MadCodec_801D9A88), 0, 0, lbl_80399100.mFlags));
}
