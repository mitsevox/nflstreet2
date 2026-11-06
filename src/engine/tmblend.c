/* Blend-shape (morph target) blending of model geometry: picks the weighted targets of each
   geometry node, blends their vertex attributes and writes the result to an output buffer that
   overrides the model's own data when it is drawn. */

#include "engine/tmlib.h"
#include <dolphin/os.h>

extern TMBlendState_t lbl_8039B600;

static unsigned int _TMBlendBuildTargetList(GeomNode_8020ED10 *pNode, int baseIndex, short *pWeights, unsigned int numWeights, TMBlendTarget_t *pItems, unsigned int maxItems)
{
    unsigned int numItems;
    int i;

    if (numWeights > pNode->mNumLods + 1) {
        numWeights = pNode->mNumLods + 1;
    }
    numItems = 0;
    if (numItems < maxItems) {
        pItems[0].mIndex = baseIndex;
        pItems[0].mWeight = pWeights[baseIndex];
        pItems[0].mFirstAttr = pNode[baseIndex].mFirstAttr;
        pItems[0].mNumAttrs = pNode[baseIndex].mNumAttrs;
        numItems = 1;
    }
    for (i = 0; i < numWeights; i++, pNode++) {
        if (i != baseIndex && pWeights[i] != 0 && numItems < maxItems) {
            pItems[numItems].mIndex = i;
            pItems[numItems].mWeight = pWeights[i];
            pItems[numItems].mFirstAttr = pNode->mFirstAttr;
            pItems[numItems].mNumAttrs = pNode->mNumAttrs;
            numItems++;
            if (pItems[0].mNumAttrs > pNode->mNumAttrs) {
                pItems[0].mNumAttrs = pNode->mNumAttrs;
            }
        }
    }
    if (pItems[0].mNumAttrs > 2) {
        pItems[0].mNumAttrs = 2;
    }
    return numItems;
}

static unsigned int _TMBlendClampTargets(TMBlendTarget_t *pItems, unsigned int numItems, unsigned int maxItems)
{
    while (numItems > maxItems) {
        unsigned int i;
        int minIndex = -1;
        short minWeight = 0x7FFF;

        for (i = 0; i < numItems; i++) {
            if ((unsigned short)pItems[i].mWeight < minWeight) {
                minWeight = pItems[i].mWeight;
                minIndex = i;
            }
        }
        numItems--;
        pItems[minIndex] = pItems[numItems];
    }
    return numItems;
}

static void _TMBlendReset(void)
{
    TMBlendSetMaxActiveTargets(0);
    TMBlendBindModel(0);
}

static unsigned int _TMBlendGeom(TMBuffer_t *pBuffer, TMBlendTarget_t *pItems, unsigned int numItems)
{
    unsigned int numAttrs = pItems[0].mNumAttrs;
    unsigned int i;

    for (i = 0; i < numAttrs; i++) {
        unsigned int j;
        int size;
        unsigned char *pOutput;

        size = TMBlendChannelSet(2, pItems[0].mFirstAttr);
        TMBlendOpExtract(0, 2);
        pOutput = 0;
        for (j = 1; j < numItems; j++) {
            TMBlendTarget_t *pItem = &pItems[j];

            TMBlendChannelSet(4, pItem->mFirstAttr);
            pItem->mFirstAttr++;
            TMBlendOpAccumulate(0, 4, pItem->mWeight);
        }
        if (pBuffer != 0) {
            pOutput = TMBufferAlloc(pBuffer, size);
            TMBlendChannelSetMem(2, pOutput, size);
        }
        TMBlendOpIntract(2, 0);
        TMBlendChannelSetOverride(pItems[0].mFirstAttr, pOutput);
        pItems[0].mFirstAttr++;
    }
    return numAttrs;
}

void TMBlendSetWeights(short *pWeights, unsigned int numWeights)
{
    lbl_8039B600.mNumWeights = numWeights;
    lbl_8039B600.mpWeights = pWeights;
}

int TMBlendSetWeightsFloat(float *pWeights, unsigned int numWeights)
{
    TMBlendState_t *pState = &lbl_8039B600;
    int numActive = 0;
    unsigned int i;
    float scale = 4096.0f;

    for (i = 0; i < numWeights; i++) {
        int weight = pWeights[i] * scale;

        pState->maWeights[i] = weight;
        if (i != 0 && weight != 0) {
            numActive++;
        }
    }
    TMBlendSetWeights(pState->maWeights, numWeights);
    return numActive;
}

void TMBlendBegin(TMBuffer_t *pBuffer)
{
    TMBlendState_t *pState = &lbl_8039B600;

    _TMBlendReset();
    pState->mpBuffer = pBuffer;
    if (pBuffer != 0) {
        pState->mFlushed = pBuffer->mUsed;
    }
    TMBlendChannelBegin();
}

void TMBlendFlushBuffer(void)
{
    TMBuffer_t *pBuffer = lbl_8039B600.mpBuffer;

    if (pBuffer != 0) {
        DCFlushRange(pBuffer->mpData + lbl_8039B600.mFlushed, pBuffer->mUsed - lbl_8039B600.mFlushed);
        lbl_8039B600.mFlushed = pBuffer->mUsed;
    }
}

void TMBlendEnd(void)
{
    TMBlendChannelEnd();
    _TMBlendReset();
}

void TMBlendBindModel(Model_8020F28C *pModel)
{
    TMBlendBindModel2(0, pModel);
}

void TMBlendBindModel2(Model_8020F28C *pBase, Model_8020F28C *pModel)
{
    TMBlendState_t *pState = &lbl_8039B600;

    if (pModel != 0 && pModel->mpGeom != 0) {
        pState->mpGeom = pModel->mpGeom;
        TMBlendChannelSetChannels(pModel->mpGeom->mpAttrs, pBase != 0 ? pBase->mpChannels : 0, pModel->mpChannels, pModel->mpGeom->mNumAttrs);
    } else {
        pState->mpGeom = 0;
        TMBlendChannelSetChannels(0, 0, 0, 0);
    }
    pState->mBaseIndex = 0;
}

void TMBlendSetMaxActiveTargets(unsigned int maxItems)
{
    lbl_8039B600.mMaxItems = maxItems;
}

int TMBlendGeom(int nodeIndex)
{
    TMBlendTarget_t aItems[128];
    int result = 0;
    GeomNode_8020ED10 *pNode;
    unsigned int numItems;

    if (lbl_8039B600.mpGeom != 0) {
        pNode = &lbl_8039B600.mpGeom->mpNodes[nodeIndex];
        if (pNode->mNumLods != 0) {
            numItems = _TMBlendBuildTargetList(pNode, lbl_8039B600.mBaseIndex, lbl_8039B600.mpWeights, lbl_8039B600.mNumWeights, aItems, 128);
            if (numItems != 0) {
                if (lbl_8039B600.mMaxItems != 0) {
                    numItems = _TMBlendClampTargets(aItems, numItems, lbl_8039B600.mMaxItems);
                }
                result = _TMBlendGeom(lbl_8039B600.mpBuffer, aItems, numItems);
            }
        }
    }
    return result;
}

int TMBlendGeomAll(void)
{
    int total = 0;
    Geom_8020ED10 *pGeom = lbl_8039B600.mpGeom;
    int numNodes;
    int i;

    if (pGeom == 0) {
        return 0;
    }
    numNodes = pGeom->mNumNodes;
    for (i = 0; i < numNodes; i++) {
        GeomNode_8020ED10 *pNode = &pGeom->mpNodes[i];

        if (pNode->mNumLods != 0) {
            total += TMBlendGeom(i);
            i += pNode->mNumLods;
        }
    }
    return total;
}
