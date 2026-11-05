/* The level's ground mesh: relocates the loaded level data and finds the triangle area under a
   position through its area tree. */
#include "game/LevelData.h"
#include "game/fn_802270D4.h"

/* Plane point with the 16-byte stride of the vector routines. */
struct LevelPoint_t {
    float mX;
    float mY;
    float mZ;
    float mW;
};

extern "C" {
float fn_80227704(LevelPoint_t *pA, LevelPoint_t *pB);
void fn_802277DC(LevelPoint_t *pOut, LevelPoint_t *pA, LevelPoint_t *pB);

extern LevelData_t *_Level_pData;

void LevelMeshPostLoad(LevelData_t *pLevel)
{
}

void LevelMeshRelocateTree(LevelAreaNode_t **ppNode, char **ppCursor)
{
    *ppNode = (LevelAreaNode_t *)*ppCursor;
    *ppCursor += sizeof(LevelAreaNode_t);
    if ((*ppNode)->mCount != 0) {
        (*ppNode)->mpIndices = (int *)*ppCursor;
        *ppCursor += (*ppNode)->mCount * sizeof(int);
    } else {
        if ((*ppNode)->mHasLeft) {
            LevelMeshRelocateTree(&(*ppNode)->mpLeft, ppCursor);
        }
        if ((*ppNode)->mHasRight) {
            LevelMeshRelocateTree(&(*ppNode)->mpRight, ppCursor);
        }
    }
}

void LevelMeshRelocate(LevelData_t *pLevel)
{
    char *pCursor = (char *)(pLevel + 1);
    pLevel->mUnknown20 = (LevelVertex_t *)pCursor;
    pCursor += pLevel->mUnknown16 * sizeof(LevelVertex_t);
    pLevel->mUnknown28 = (LevelArea_t *)pCursor;
    pCursor += pLevel->mUnknown24 * sizeof(LevelArea_t);
    pLevel->mUnknown36 = pCursor;
    pCursor += pLevel->mUnknown32 * 24;
    pLevel->mUnknown44 = pCursor;
    pCursor += pLevel->mUnknown40 * 24;
    pLevel->mUnknown52 = pCursor;
    pCursor += pLevel->mUnknown48 * 24;
    pLevel->mUnknown60 = pCursor;
    pCursor += pLevel->mUnknown56 * 24;
    pLevel->mUnknown68 = pCursor;
    pCursor += pLevel->mUnknown64 * 24;
    pLevel->mUnknown76 = pCursor;
    pCursor += pLevel->mUnknown72 * 24;
    pLevel->mUnknown84 = pCursor;
    pCursor += pLevel->mUnknown80 * 56;
    pLevel->mUnknown92 = (LevelPlacement_t *)pCursor;
    pCursor += pLevel->mUnknown88 * sizeof(LevelPlacement_t);
    pLevel->mUnknown100 = (LevelPlacement_t *)pCursor;
    pCursor += pLevel->mUnknown96 * sizeof(LevelPlacement_t);
    pLevel->mUnknown108 = (LevelPlacement_t *)pCursor;
    pCursor += pLevel->mUnknown104 * sizeof(LevelPlacement_t);
    pLevel->mUnknown116 = (LevelPlacement_t *)pCursor;
    pCursor += pLevel->mUnknown112 * sizeof(LevelPlacement_t);
    pLevel->mUnknown124 = pCursor;
    pCursor += pLevel->mUnknown120 * 48;
    pLevel->mUnknown132 = pCursor;
    pCursor += pLevel->mUnknown128 * 48;
    pLevel->mUnknown140 = (LevelWall_t *)pCursor;
    pCursor += pLevel->mUnknown136 * sizeof(LevelWall_t);
    pLevel->mUnknown148 = (int *)pCursor;
    pCursor += pLevel->mUnknown144 * sizeof(int);
    pLevel->mUnknown156 = (LevelMarker_t *)pCursor;
    pCursor += pLevel->mUnknown152 * sizeof(LevelMarker_t);
    LevelMeshRelocateTree(&pLevel->mUnknown160, &pCursor);
}

/* Nonzero when pPoint lies on the same side of the line through pA and pB
   as pRef, or on the line. */
int LevelMeshSameSide(LevelPoint_t *pPoint, LevelPoint_t *pRef, LevelPoint_t *pA, LevelPoint_t *pB)
{
    LevelPoint_t edge;
    LevelPoint_t offset;
    LevelPoint_t crossPoint;
    LevelPoint_t crossRef;

    fn_802276B4(&edge, pB, pA);
    fn_802276B4(&offset, pPoint, pA);
    fn_802277DC(&crossPoint, &edge, &offset);
    fn_802276B4(&offset, pRef, pA);
    fn_802277DC(&crossRef, &edge, &offset);
    return fn_80227704(&crossPoint, &crossRef) >= 0.0f;
}

int LevelMeshInArea(LevelArea_t *pEntry, LevelPoint_t *pPoint)
{
    LevelPoint_t a;
    LevelPoint_t b;
    LevelPoint_t c;
    LevelData_t *pLevel = _Level_pData;

    a.mX = pLevel->mUnknown20[pEntry->mVertex[0]].mX;
    a.mY = pLevel->mUnknown20[pEntry->mVertex[0]].mY;
    a.mZ = 0.0f;
    b.mX = pLevel->mUnknown20[pEntry->mVertex[1]].mX;
    b.mY = pLevel->mUnknown20[pEntry->mVertex[1]].mY;
    b.mZ = 0.0f;
    c.mX = pLevel->mUnknown20[pEntry->mVertex[2]].mX;
    c.mY = pLevel->mUnknown20[pEntry->mVertex[2]].mY;
    c.mZ = 0.0f;
    if (LevelMeshSameSide(pPoint, &a, &b, &c) && LevelMeshSameSide(pPoint, &b, &a, &c) && LevelMeshSameSide(pPoint, &c, &a, &b)) {
        return 1;
    }
    return 0;
}

LevelArea_t *LevelMeshFindArea(float *pPos, int value)
{
    LevelAreaNode_t *pNode = _Level_pData->mUnknown160;
    while (pNode->mCount == 0) {
        if (pNode->mAxis == 0) {
            if (pPos[0] > pNode->mSplit) {
                pNode = pNode->mpLeft;
            } else {
                pNode = pNode->mpRight;
            }
        } else {
            if (pPos[1] > pNode->mSplit) {
                pNode = pNode->mpLeft;
            } else {
                pNode = pNode->mpRight;
            }
        }
    }
    for (unsigned int i = 0; i < pNode->mCount; i++) {
        LevelArea_t *pEntry = &_Level_pData->mUnknown28[pNode->mpIndices[i]];
        if (LevelMeshInArea(pEntry, (LevelPoint_t *)pPos)) {
            return pEntry;
        }
    }
    return 0;
}
}
