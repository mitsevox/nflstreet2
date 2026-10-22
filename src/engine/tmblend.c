#include "engine/tmlib.h"
#include <dolphin/os.h>

extern BlendState_80214718 lbl_8039B600;

static unsigned int fn_80214718(SwapNode_8020ED10 *pNode, int baseIndex, short *pWeights, unsigned int numWeights, BlendItem_80214718 *pItems, unsigned int maxItems)
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

static unsigned int fn_80214814(BlendItem_80214718 *pItems, unsigned int numItems, unsigned int maxItems)
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

static void fn_80214890(void)
{
    fn_80214C04(0);
    fn_80214B44(0);
}

static unsigned int fn_802148BC(Buffer_80214554 *pBuffer, BlendItem_80214718 *pItems, unsigned int numItems)
{
    unsigned int numAttrs = pItems[0].mNumAttrs;
    unsigned int i;

    for (i = 0; i < numAttrs; i++) {
        unsigned int j;
        int size;
        unsigned char *pOutput;

        size = fn_80214DCC(2, pItems[0].mFirstAttr);
        fn_80215694(0, 2);
        pOutput = 0;
        for (j = 1; j < numItems; j++) {
            BlendItem_80214718 *pItem = &pItems[j];

            fn_80214DCC(4, pItem->mFirstAttr);
            pItem->mFirstAttr++;
            fn_80215554(0, 4, pItem->mWeight);
        }
        if (pBuffer != 0) {
            pOutput = fn_80214680(pBuffer, size);
            fn_80214E3C(2, pOutput, size);
        }
        fn_8021574C(2, 0);
        fn_80214EB4(pItems[0].mFirstAttr, pOutput);
        pItems[0].mFirstAttr++;
    }
    return numAttrs;
}

void fn_802149D4(short *pWeights, unsigned int numWeights)
{
    lbl_8039B600.mNumWeights = numWeights;
    lbl_8039B600.mpWeights = pWeights;
}

int fn_802149E8(float *pWeights, unsigned int numWeights)
{
    BlendState_80214718 *pState = &lbl_8039B600;
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
    fn_802149D4(pState->maWeights, numWeights);
    return numActive;
}

void fn_80214A7C(Buffer_80214554 *pBuffer)
{
    BlendState_80214718 *pState = &lbl_8039B600;

    fn_80214890();
    pState->mpBuffer = pBuffer;
    if (pBuffer != 0) {
        pState->mFlushed = pBuffer->mUsed;
    }
    fn_80214ED0();
}

void fn_80214AC8(void)
{
    Buffer_80214554 *pBuffer = lbl_8039B600.mpBuffer;

    if (pBuffer != 0) {
        DCFlushRange(pBuffer->mpData + lbl_8039B600.mFlushed, pBuffer->mUsed - lbl_8039B600.mFlushed);
        lbl_8039B600.mFlushed = pBuffer->mUsed;
    }
}

void fn_80214B20(void)
{
    fn_80214F54();
    fn_80214890();
}

void fn_80214B44(Model_8020F28C *pModel)
{
    fn_80214B6C(0, pModel);
}

void fn_80214B6C(Model_8020F28C *pBase, Model_8020F28C *pModel)
{
    BlendState_80214718 *pState = &lbl_8039B600;

    if (pModel != 0 && pModel->mpGeom != 0) {
        pState->mpGeom = pModel->mpGeom;
        fn_80214E80(pModel->mpGeom->mpAttrs, pBase != 0 ? pBase->mpChannels : 0, pModel->mpChannels, pModel->mpGeom->mNumAttrs);
    } else {
        pState->mpGeom = 0;
        fn_80214E80(0, 0, 0, 0);
    }
    pState->mBaseIndex = 0;
}

void fn_80214C04(unsigned int maxItems)
{
    lbl_8039B600.mMaxItems = maxItems;
}

int fn_80214C10(int nodeIndex)
{
    BlendItem_80214718 aItems[128];
    int result = 0;
    SwapNode_8020ED10 *pNode;
    unsigned int numItems;

    if (lbl_8039B600.mpGeom != 0) {
        pNode = &lbl_8039B600.mpGeom->mpNodes[nodeIndex];
        if (pNode->mNumLods != 0) {
            numItems = fn_80214718(pNode, lbl_8039B600.mBaseIndex, lbl_8039B600.mpWeights, lbl_8039B600.mNumWeights, aItems, 128);
            if (numItems != 0) {
                if (lbl_8039B600.mMaxItems != 0) {
                    numItems = fn_80214814(aItems, numItems, lbl_8039B600.mMaxItems);
                }
                result = fn_802148BC(lbl_8039B600.mpBuffer, aItems, numItems);
            }
        }
    }
    return result;
}

int fn_80214CB4(void)
{
    int total = 0;
    SwapPart_8020ED10 *pGeom = lbl_8039B600.mpGeom;
    int numNodes;
    int i;

    if (pGeom == 0) {
        return 0;
    }
    numNodes = pGeom->mNumNodes;
    for (i = 0; i < numNodes; i++) {
        SwapNode_8020ED10 *pNode = &pGeom->mpNodes[i];

        if (pNode->mNumLods != 0) {
            total += fn_80214C10(i);
            i += pNode->mNumLods;
        }
    }
    return total;
}
