#include <string.h>
#include "game/Class_8008B284.h"

extern "C" {

Pool_801C750C *fn_801C750C(int a, int count, int size, void *pMemory);
int fn_801C75B8(Pool_801C750C *pPool);
void *fn_801C75F0(Pool_801C750C *pPool);
void fn_801C7650(Pool_801C750C *pPool, void *pElement);

/* Byte offset of element (x, y) in a buffer of 8x4-byte tiles laid out
   tilesPerRow to a row. */
unsigned int fn_8008AC40(unsigned int x, unsigned int y, unsigned int tilesPerRow)
{
    return ((y >> 2) * tilesPerRow + (x >> 3)) * 32 + ((y & 3) << 3) + (x & 7);
}

}

void Class_8008B284::fn_8008AC68(Node_8008AF90 **ppNode, unsigned int color, int level, int link)
{
    if (*ppNode == 0) {
        *ppNode = fn_8008AF90(level, link);
    }
    if ((*ppNode)->mIsLeaf == 1) {
        (*ppNode)->mCount++;
        (*ppNode)->mSum12 += (color >> 16) & 0xFF;
        (*ppNode)->mSum16 += (color >> 8) & 0xFF;
        (*ppNode)->mSum20 += color & 0xFF;
    } else {
        fn_8008AC68(&(*ppNode)->mpChildren[fn_8008B054(level, color)], color, level + 1, link);
    }
}

void Class_8008B284::fn_8008AD4C()
{
    Node_8008AF90 *pNode;
    Node_8008AF90 *pNext;
    Node_8008AF90 *pPrev;
    Node_8008AF90 *pChild;
    unsigned int children;
    unsigned int i;
    unsigned int level;

    for (level = 7; level > 0 && mpLists[level] == 0; level--) {
    }

    pNode = fn_8008AF5C(mpLists[level]);
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
            fn_8008B030(pChild);
            pNode->mpChildren[i] = 0;
        }
    }
    pNode->mIsLeaf = 1;
    mLeafCount -= children - 1;
}

unsigned int Class_8008B284::fn_8008AE88(Node_8008AF90 *pNode)
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

void Class_8008B284::fn_8008AED4(unsigned int color, unsigned char *pOut, int level, Node_8008AF90 *pNode)
{
    if (pNode == 0) {
        pNode = mpRoot;
    }
    if (pNode->mIsLeaf == 1) {
        *pOut = pNode->mIndex;
    } else {
        Node_8008AF90 *pChild = pNode->mpChildren[fn_8008B054(level, color)];

        fn_8008AED4(color, pOut, level + 1, pChild);
    }
}

Node_8008AF90 *Class_8008B284::fn_8008AF5C(Node_8008AF90 *pList)
{
    Node_8008AF90 *pBest = pList;
    Node_8008AF90 *pNode;

    for (pNode = pList; pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mCount < pBest->mCount) {
            pBest = pNode;
        }
    }
    return pBest;
}

Node_8008AF90 *Class_8008B284::fn_8008AF90(int level, int link)
{
    Node_8008AF90 *pNode = (Node_8008AF90 *)fn_801C75F0(mpPool);

    memset(pNode, 0, sizeof(Node_8008AF90));
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

void Class_8008B284::fn_8008B030(Node_8008AF90 *pNode)
{
    fn_801C7650(mpPool, pNode);
}

int Class_8008B284::fn_8008B054(int level, unsigned int color)
{
    int shift = 7 - level;
    unsigned char mask = 1 << shift;
    unsigned char c16 = color >> 16;
    unsigned char c8 = color >> 8;
    unsigned char c0 = color;

    return ((c16 & mask) >> shift) << 2 | ((c8 & mask) >> shift) << 1 | (c0 & mask) >> shift;
}

void Class_8008B284::fn_8008B09C(unsigned int *pImage, unsigned int width, unsigned int height)
{
    unsigned int count = width * height;
    unsigned int i;

    for (i = 0; i < count; i++) {
        unsigned int color = pImage[i] | 0xFF000000;

        fn_8008AC68(&mpRoot, color, 0, (color & 0xFF00FF00) != 0xFF00FF00);
        while (mLeafCount > 256) {
            fn_8008AD4C();
        }
    }
}

void Class_8008B284::fn_8008B134(unsigned int *pPalette, Node_8008AF90 *pNode, int *pIndex)
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

        *pEntry = fn_8008AE88(pNode);
        pNode->mIndex = *pIndex;
        (*pIndex)++;
    } else {
        for (i = 0; i < 8; i++) {
            if (pNode->mpChildren[i] != 0) {
                fn_8008B134(pPalette, pNode->mpChildren[i], pIndex);
            }
        }
    }
}

void Class_8008B284::fn_8008B1F0(unsigned int *pImage, unsigned int width, unsigned int height, unsigned char *pOut)
{
    unsigned int count = width * height;
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_8008AED4(pImage[i], pOut + fn_8008AC40(i % width, i / height, width >> 3), 0, 0);
    }
}

int Class_8008B284::fn_8008B27C()
{
    return mLeafCount;
}

Class_8008B284::Class_8008B284()
{
    mpRoot = 0;
    mLeafCount = 0;
    mpPool = 0;
    mpPool = fn_801C750C(1, 1601, sizeof(Node_8008AF90), 0);
    memset(mpLists, 0, sizeof(mpLists));
}

Class_8008B284::~Class_8008B284()
{
    fn_801C75B8(mpPool);
}
