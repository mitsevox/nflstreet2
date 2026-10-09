#include "game/Level_80054130.h"
#include "game/fn_802270D4.h"

/* Plane point with the 16-byte stride of the vector routines. */
struct Point_80053DCC {
    float mX;
    float mY;
    float mZ;
    float mW;
};

extern "C" {
float fn_80227704(Point_80053DCC *pA, Point_80053DCC *pB);
void fn_802277DC(Point_80053DCC *pOut, Point_80053DCC *pA, Point_80053DCC *pB);

extern Level_80054130 *lbl_803EA554;

void fn_80053BC8(Level_80054130 *pLevel)
{
}

void fn_80053BCC(Node_80053BCC **ppNode, char **ppCursor)
{
    *ppNode = (Node_80053BCC *)*ppCursor;
    *ppCursor += sizeof(Node_80053BCC);
    if ((*ppNode)->mCount != 0) {
        (*ppNode)->mpIndices = (int *)*ppCursor;
        *ppCursor += (*ppNode)->mCount * sizeof(int);
    } else {
        if ((*ppNode)->mHasLeft) {
            fn_80053BCC(&(*ppNode)->mpLeft, ppCursor);
        }
        if ((*ppNode)->mHasRight) {
            fn_80053BCC(&(*ppNode)->mpRight, ppCursor);
        }
    }
}

void fn_80053C70(Level_80054130 *pLevel)
{
    char *pCursor = (char *)(pLevel + 1);
    pLevel->mUnknown20 = (Vertex_80053C70 *)pCursor;
    pCursor += pLevel->mUnknown16 * sizeof(Vertex_80053C70);
    pLevel->mUnknown28 = (Entry_8005415C *)pCursor;
    pCursor += pLevel->mUnknown24 * sizeof(Entry_8005415C);
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
    pLevel->mUnknown92 = (Entry_80054130 *)pCursor;
    pCursor += pLevel->mUnknown88 * sizeof(Entry_80054130);
    pLevel->mUnknown100 = (Entry_80054130 *)pCursor;
    pCursor += pLevel->mUnknown96 * sizeof(Entry_80054130);
    pLevel->mUnknown108 = (Entry_80054130 *)pCursor;
    pCursor += pLevel->mUnknown104 * sizeof(Entry_80054130);
    pLevel->mUnknown116 = (Entry_80054130 *)pCursor;
    pCursor += pLevel->mUnknown112 * sizeof(Entry_80054130);
    pLevel->mUnknown124 = pCursor;
    pCursor += pLevel->mUnknown120 * 48;
    pLevel->mUnknown132 = pCursor;
    pCursor += pLevel->mUnknown128 * 48;
    pLevel->mUnknown140 = (Record_80054130 *)pCursor;
    pCursor += pLevel->mUnknown136 * sizeof(Record_80054130);
    pLevel->mUnknown148 = (int *)pCursor;
    pCursor += pLevel->mUnknown144 * sizeof(int);
    pLevel->mUnknown156 = (Object_8005438C *)pCursor;
    pCursor += pLevel->mUnknown152 * sizeof(Object_8005438C);
    fn_80053BCC(&pLevel->mUnknown160, &pCursor);
}

/* Nonzero when pPoint lies on the same side of the line through pA and pB
   as pRef, or on the line. */
int fn_80053DCC(Point_80053DCC *pPoint, Point_80053DCC *pRef, Point_80053DCC *pA, Point_80053DCC *pB)
{
    Point_80053DCC edge;
    Point_80053DCC offset;
    Point_80053DCC crossPoint;
    Point_80053DCC crossRef;

    fn_802276B4(&edge, pB, pA);
    fn_802276B4(&offset, pPoint, pA);
    fn_802277DC(&crossPoint, &edge, &offset);
    fn_802276B4(&offset, pRef, pA);
    fn_802277DC(&crossRef, &edge, &offset);
    return fn_80227704(&crossPoint, &crossRef) >= 0.0f;
}

int fn_80053E78(Entry_8005415C *pEntry, Point_80053DCC *pPoint)
{
    Point_80053DCC a;
    Point_80053DCC b;
    Point_80053DCC c;
    Level_80054130 *pLevel = lbl_803EA554;

    a.mX = pLevel->mUnknown20[pEntry->mVertex[0]].mX;
    a.mY = pLevel->mUnknown20[pEntry->mVertex[0]].mY;
    a.mZ = 0.0f;
    b.mX = pLevel->mUnknown20[pEntry->mVertex[1]].mX;
    b.mY = pLevel->mUnknown20[pEntry->mVertex[1]].mY;
    b.mZ = 0.0f;
    c.mX = pLevel->mUnknown20[pEntry->mVertex[2]].mX;
    c.mY = pLevel->mUnknown20[pEntry->mVertex[2]].mY;
    c.mZ = 0.0f;
    if (fn_80053DCC(pPoint, &a, &b, &c) && fn_80053DCC(pPoint, &b, &a, &c) && fn_80053DCC(pPoint, &c, &a, &b)) {
        return 1;
    }
    return 0;
}

Entry_8005415C *fn_80053F8C(float *pPos, int value)
{
    Node_80053BCC *pNode = lbl_803EA554->mUnknown160;
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
        Entry_8005415C *pEntry = &lbl_803EA554->mUnknown28[pNode->mpIndices[i]];
        if (fn_80053E78(pEntry, (Point_80053DCC *)pPos)) {
            return pEntry;
        }
    }
    return 0;
}
}
