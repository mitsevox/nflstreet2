/* Working channels for geometry blending: the scratch memory, input data and output data of
   each attribute being blended. */

#include "engine/tmlib.h"

typedef struct TMBlendChannelState_t {
    TMBlendChannelSource_t mSource;
    TMBlendChannel_t maChannels[6];
} TMBlendChannelState_t;

/* The attribute bindings and the six working channels. */
static TMBlendChannelState_t _TMBlendChannel_State;

/* Scratch memory that TMBlendChannelBegin splits between the channels. */
static unsigned char _TMBlendChannel_Scratchpad[0x4000] __attribute__((aligned(32)));

static void *_TMBlendChannelGetInData(TMGeomAttr_t *pAttr, int index)
{
    void **ppInputs = _TMBlendChannel_State.mSource.mppInputs;

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
    return &_TMBlendChannel_State.maChannels[id];
}

int TMBlendChannelSet(int id, int index)
{
    TMBlendChannel_t *pChannel = TMBlendChannelGetBuffer(id);
    TMGeomAttr_t *pAttr = &_TMBlendChannel_State.mSource.mpAttrs[index];
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

void TMBlendChannelSetChannels(TMGeomAttr_t *pAttrs, void **ppInputs, void **ppOutputs, int numAttrs)
{
    _TMBlendChannel_State.mSource.mNumAttrs = numAttrs;
    if (numAttrs != 0) {
        _TMBlendChannel_State.mSource.mpAttrs = pAttrs;
        _TMBlendChannel_State.mSource.mppInputs = ppInputs;
        _TMBlendChannel_State.mSource.mppOutputs = ppOutputs;
    } else {
        _TMBlendChannel_State.mSource.mpAttrs = 0;
        _TMBlendChannel_State.mSource.mppInputs = 0;
        _TMBlendChannel_State.mSource.mppOutputs = 0;
    }
}

void TMBlendChannelSetOverride(int index, void *pOutput)
{
    void **ppOutputs = _TMBlendChannel_State.mSource.mppOutputs;

    if (ppOutputs != 0) {
        ppOutputs[index] = pOutput;
    }
}

void TMBlendChannelBegin(void)
{
    unsigned char *p;

    TMBlendChannelSetChannels(0, 0, 0, 0);
    p = _TMBlendChannelSetSpr(0, _TMBlendChannel_Scratchpad, 0x1000);
    p = _TMBlendChannelSetSpr(2, p, 0x1000);
    p = _TMBlendChannelSetSpr(3, p, 0);
    p = _TMBlendChannelSetSpr(4, p, 0x1000);
    _TMBlendChannelSetSpr(5, p, 0x1000);
}

void TMBlendChannelEnd(void)
{
}
