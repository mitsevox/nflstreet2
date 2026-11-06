/* Working channels for geometry blending: the scratch memory, input data and output data of
   each attribute being blended. */

#include "engine/tmlib.h"

extern TMBlendChannelSource_t lbl_8039B720;
extern TMBlendChannel_t lbl_8039B730[];
extern unsigned char lbl_8039B7E0[];

static void *_TMBlendChannelGetInData(GeomAttr_8020ED10 *pAttr, int index)
{
    void **ppInputs = lbl_8039B720.mppInputs;

    if (ppInputs != 0 && ppInputs[index] != 0) {
        return ppInputs[index];
    }
    return pAttr->mpData;
}

static unsigned char *_TMBlendChannelSetSpr(int id, unsigned char *pData, int capacity)
{
    TMBlendChannel_t *pChannel = TMBlendChannelGetBuffer(id);

    pChannel->mpBase = pData;
    pChannel->mCapacity = capacity;
    pChannel->mpCursor = pData;
    pChannel->mSize = 0;
    return pData + capacity;
}

TMBlendChannel_t *TMBlendChannelGetBuffer(int id)
{
    return &lbl_8039B730[id];
}

int TMBlendChannelSet(int id, int index)
{
    TMBlendChannel_t *pChannel = TMBlendChannelGetBuffer(id);
    GeomAttr_8020ED10 *pAttr = &lbl_8039B720.mpAttrs[index];
    int size;

    pChannel->mpAttr = pAttr;
    pChannel->mpOutput = _TMBlendChannelGetInData(pAttr, index);
    size = pAttr->mCount * pAttr->mStride;
    pChannel->mpCursor = pChannel->mpOutput;
    pChannel->mOutputSize = size;
    pChannel->mSize = size;
    return size;
}

unsigned char *TMBlendChannelSetMem(int id, unsigned char *pData, int size)
{
    TMBlendChannel_t *pChannel = TMBlendChannelGetBuffer(id);

    pChannel->mpOutput = pData;
    pChannel->mOutputSize = size;
    pChannel->mpCursor = pData;
    return pData + size;
}

void TMBlendChannelSetChannels(GeomAttr_8020ED10 *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs)
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

void TMBlendChannelSetOverride(int index, void *pOutput)
{
    void **ppOutputs = lbl_8039B720.mppOutputs;

    if (ppOutputs != 0) {
        ppOutputs[index] = pOutput;
    }
}

void TMBlendChannelBegin(void)
{
    unsigned char *p;

    TMBlendChannelSetChannels(0, 0, 0, 0);
    p = _TMBlendChannelSetSpr(0, lbl_8039B7E0, 0x1000);
    p = _TMBlendChannelSetSpr(2, p, 0x1000);
    p = _TMBlendChannelSetSpr(3, p, 0);
    p = _TMBlendChannelSetSpr(4, p, 0x1000);
    _TMBlendChannelSetSpr(5, p, 0x1000);
}

void TMBlendChannelEnd(void)
{
}
