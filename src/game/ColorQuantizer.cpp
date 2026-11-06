/* Octree colour quantizer: reduces a 32-bit image to a palette of at most 256 colours and
   writes the 8-bit tiled image, used for create-a-player portraits. */

#include <string.h>
#include "game/ColorQuantizer.h"

extern "C" {

Pool_801C750C *DSNewNodeHandler(int a, int count, int size, void *pMemory);
int DSDelNodeHandler(Pool_801C750C *pPool);
void *DSNewNode(Pool_801C750C *pPool);
void DSDelNode(Pool_801C750C *pPool, void *pElement);

/* Byte offset of element (x, y) in a buffer of 8x4-byte tiles laid out
   tilesPerRow to a row. */
unsigned int ColorQuantizerTexelOffset(unsigned int x, unsigned int y, unsigned int tilesPerRow)
{
    return ((y >> 2) * tilesPerRow + (x >> 3)) * 32 + ((y & 3) << 3) + (x & 7);
}

}

void ColorQuantizer::AddColor(ColorQuantizerNode_t **ppNode, unsigned int color, int level, int link)
{
    if (*ppNode == 0) {
        *ppNode = NewNode(level, link);
    }
    if ((*ppNode)->mIsLeaf == 1) {
        (*ppNode)->mCount++;
        (*ppNode)->mSum12 += (color >> 16) & 0xFF;
        (*ppNode)->mSum16 += (color >> 8) & 0xFF;
        (*ppNode)->mSum20 += color & 0xFF;
    } else {
        AddColor(&(*ppNode)->mpChildren[GetChildIndex(level, color)], color, level + 1, link);
    }
}

void ColorQuantizer::ReduceTree()
{
    ColorQuantizerNode_t *pNode;
    ColorQuantizerNode_t *pNext;
    ColorQuantizerNode_t *pPrev;
    ColorQuantizerNode_t *pChild;
    unsigned int children;
    unsigned int i;
    unsigned int level;

    for (level = 7; level > 0 && mpLists[level] == 0; level--) {
    }

    pNode = FindSmallestNode(mpLists[level]);
    pPrev = pNode->mpPrev;
    pNext = pNode->mpNext;
    if (pNode == mpLists[level]) {
        mpLists[level] = pNext;
    } else {
        if (pNext != 0) {
            pNext->mpPrev = pPrev;
        }
        if (pPrev != 0) {
            pPrev->mpNext = pNext;
        }
    }

    children = 0;
    for (i = 0; i < 8; i++) {
        pChild = pNode->mpChildren[i];
        if (pChild != 0) {
            children++;
            pNode->mSum12 += pChild->mSum12;
            pNode->mSum16 += pChild->mSum16;
            pNode->mSum20 += pChild->mSum20;
            pNode->mCount += pChild->mCount;
            FreeNode(pChild);
            pNode->mpChildren[i] = 0;
        }
    }
    pNode->mIsLeaf = 1;
    mLeafCount -= children - 1;
}

unsigned int ColorQuantizer::GetNodeColor(ColorQuantizerNode_t *pNode)
{
    unsigned int c12 = pNode->mSum12 / pNode->mCount;
    unsigned int c16 = pNode->mSum16 / pNode->mCount;
    unsigned int c20 = pNode->mSum20 / pNode->mCount;
    unsigned int color = c20 << 16 | c16 << 8 | c12 | 0xFF000000;

    if ((color & 0xFF00FF00) == 0xFF00FF00) {
        color = 0;
    }
    return color;
}

void ColorQuantizer::FindPaletteIndex(unsigned int color, unsigned char *pOut, int level, ColorQuantizerNode_t *pNode)
{
    if (pNode == 0) {
        pNode = mpRoot;
    }
    if (pNode->mIsLeaf == 1) {
        *pOut = pNode->mIndex;
    } else {
        ColorQuantizerNode_t *pChild = pNode->mpChildren[GetChildIndex(level, color)];

        FindPaletteIndex(color, pOut, level + 1, pChild);
    }
}

ColorQuantizerNode_t *ColorQuantizer::FindSmallestNode(ColorQuantizerNode_t *pList)
{
    ColorQuantizerNode_t *pBest = pList;
    ColorQuantizerNode_t *pNode;

    for (pNode = pList; pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mCount < pBest->mCount) {
            pBest = pNode;
        }
    }
    return pBest;
}

ColorQuantizerNode_t *ColorQuantizer::NewNode(int level, int link)
{
    ColorQuantizerNode_t *pNode = (ColorQuantizerNode_t *)DSNewNode(mpPool);

    memset(pNode, 0, sizeof(ColorQuantizerNode_t));
    if (level == 7) {
        pNode->mIsLeaf = 1;
        mLeafCount++;
    } else {
        pNode->mIsLeaf = 0;
        if (link) {
            if (mpLists[level] != 0) {
                mpLists[level]->mpPrev = pNode;
            }
            pNode->mpNext = mpLists[level];
            mpLists[level] = pNode;
        }
    }
    return pNode;
}

void ColorQuantizer::FreeNode(ColorQuantizerNode_t *pNode)
{
    DSDelNode(mpPool, pNode);
}

int ColorQuantizer::GetChildIndex(int level, unsigned int color)
{
    int shift = 7 - level;
    unsigned char mask = 1 << shift;
    unsigned char c16 = color >> 16;
    unsigned char c8 = color >> 8;
    unsigned char c0 = color;

    return ((c16 & mask) >> shift) << 2 | ((c8 & mask) >> shift) << 1 | (c0 & mask) >> shift;
}

void ColorQuantizer::AddImage(unsigned int *pImage, unsigned int width, unsigned int height)
{
    unsigned int count = width * height;
    unsigned int i;

    for (i = 0; i < count; i++) {
        unsigned int color = pImage[i] | 0xFF000000;

        AddColor(&mpRoot, color, 0, (color & 0xFF00FF00) != 0xFF00FF00);
        while (mLeafCount > 256) {
            ReduceTree();
        }
    }
}

void ColorQuantizer::BuildPalette(unsigned int *pPalette, ColorQuantizerNode_t *pNode, int *pIndex)
{
    int index = 0;
    unsigned int i;

    if (pNode == 0) {
        pNode = mpRoot;
    }
    if (pIndex == 0) {
        pIndex = &index;
    }
    if (pNode->mIsLeaf == 1) {
        unsigned int *pEntry = &pPalette[*pIndex];

        *pEntry = GetNodeColor(pNode);
        pNode->mIndex = *pIndex;
        (*pIndex)++;
    } else {
        for (i = 0; i < 8; i++) {
            if (pNode->mpChildren[i] != 0) {
                BuildPalette(pPalette, pNode->mpChildren[i], pIndex);
            }
        }
    }
}

void ColorQuantizer::MapImage(unsigned int *pImage, unsigned int width, unsigned int height, unsigned char *pOut)
{
    unsigned int count = width * height;
    unsigned int i;

    for (i = 0; i < count; i++) {
        FindPaletteIndex(pImage[i], pOut + ColorQuantizerTexelOffset(i % width, i / height, width >> 3), 0, 0);
    }
}

int ColorQuantizer::GetLeafCount()
{
    return mLeafCount;
}

ColorQuantizer::ColorQuantizer()
{
    mpRoot = 0;
    mLeafCount = 0;
    mpPool = 0;
    mpPool = DSNewNodeHandler(1, 1601, sizeof(ColorQuantizerNode_t), 0);
    memset(mpLists, 0, sizeof(mpLists));
}

ColorQuantizer::~ColorQuantizer()
{
    DSDelNodeHandler(mpPool);
}
