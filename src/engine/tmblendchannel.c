#include "engine/tmlib.h"

extern BlendSource_80214E80 lbl_8039B720;
extern BlendChannel_80214D40 lbl_8039B730[];
extern unsigned char lbl_8039B7E0[];

void *fn_80214D40(SwapAttr_8020ED10 *pAttr, int index)
{
    void **ppInputs = lbl_8039B720.mppInputs;

    if (ppInputs != 0 && ppInputs[index] != 0) {
        return ppInputs[index];
    }
    return pAttr->mpData;
}

unsigned char *fn_80214D6C(int id, unsigned char *pData, int capacity)
{
    BlendChannel_80214D40 *pChannel = fn_80214DB8(id);

    pChannel->mpBase = pData;
    pChannel->mCapacity = capacity;
    pChannel->mpCursor = pData;
    pChannel->mSize = 0;
    return pData + capacity;
}

BlendChannel_80214D40 *fn_80214DB8(int id)
{
    return &lbl_8039B730[id];
}

int fn_80214DCC(int id, int index)
{
    BlendChannel_80214D40 *pChannel = fn_80214DB8(id);
    SwapAttr_8020ED10 *pAttr = &lbl_8039B720.mpAttrs[index];
    int size;

    pChannel->mpAttr = pAttr;
    pChannel->mpOutput = fn_80214D40(pAttr, index);
    size = pAttr->mCount * pAttr->mStride;
    pChannel->mpCursor = pChannel->mpOutput;
    pChannel->mOutputSize = size;
    pChannel->mSize = size;
    return size;
}

unsigned char *fn_80214E3C(int id, unsigned char *pData, int size)
{
    BlendChannel_80214D40 *pChannel = fn_80214DB8(id);

    pChannel->mpOutput = pData;
    pChannel->mOutputSize = size;
    pChannel->mpCursor = pData;
    return pData + size;
}

void fn_80214E80(SwapAttr_8020ED10 *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs)
{
    lbl_8039B720.mNumAttrs = numAttrs;
    if (numAttrs != 0) {
        lbl_8039B720.mpAttrs = pAttrs;
        lbl_8039B720.mppInputs = ppInputs;
        lbl_8039B720.mppOutputs = ppOutputs;
    } else {
        lbl_8039B720.mpAttrs = 0;
        lbl_8039B720.mppInputs = 0;
        lbl_8039B720.mppOutputs = 0;
    }
}

void fn_80214EB4(int index, void *pOutput)
{
    void **ppOutputs = lbl_8039B720.mppOutputs;

    if (ppOutputs != 0) {
        ppOutputs[index] = pOutput;
    }
}

void fn_80214ED0(void)
{
    unsigned char *p;

    fn_80214E80(0, 0, 0, 0);
    p = fn_80214D6C(0, lbl_8039B7E0, 0x1000);
    p = fn_80214D6C(2, p, 0x1000);
    p = fn_80214D6C(3, p, 0);
    p = fn_80214D6C(4, p, 0x1000);
    fn_80214D6C(5, p, 0x1000);
}

void fn_80214F54(void)
{
}
