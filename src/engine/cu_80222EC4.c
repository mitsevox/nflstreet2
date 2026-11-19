#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXDispList.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include "engine/MovieRcmpInfo.h"
#include <string.h>
#include "engine/Font.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* Partial source for the engine range 0x80222EC4-0x80223B00 (neutral file
   name): curve helpers and the first node update path. Functions without a
   body here keep their original bytes. */

extern float fn_80260B1C(float x);

extern Point_80222EC4 lbl_8039FDB8[];
extern Point_80222EC4 lbl_803A00D8[];

void fn_80223AA0(Node_80223874 *pNode);
void fn_80223AD0(Node_80223874 *pNode);
void fn_80223B00(Node_80223874 *pNode, Int32 a);

void fn_80222EC4(Point_80222EC4 *pPoints, int count, float t, Point_80222EC4 *pOut)
{
    int i;
    int j;

    for (j = 0; j < count; j++) {
        lbl_8039FDB8[j] = pPoints[j];
    }
    for (i = 1; i < count; i++) {
        for (j = 0; j < count - i; j++) {
            lbl_8039FDB8[j].mX = (1.0f - t) * lbl_8039FDB8[j].mX + t * lbl_8039FDB8[j + 1].mX;
            lbl_8039FDB8[j].mY = (1.0f - t) * lbl_8039FDB8[j].mY + t * lbl_8039FDB8[j + 1].mY;
        }
    }
    *pOut = lbl_8039FDB8[0];
}


void fn_80222F8C(Point_80222EC4 *pPoints, int count, Point_80222EC4 *pOut, int numOut)
{
    float step;
    float t;
    int i;

    step = 1.0f / (numOut - 1);
    t = step;
    pOut[0] = pPoints[0];
    for (i = 1; i < numOut - 1; i++, t += step) {
        fn_80222EC4(pPoints, count, t, &pOut[i]);
    }
    pOut[numOut - 1] = pPoints[count - 1];
}

void fn_8022306C(Point_80222EC4 *pA, Point_80222EC4 *pB, Point_80222EC4 *pLeft, Point_80222EC4 *pRight,
                 Point_80222EC4 *pDir, int useDir, float width)
{
    Point_80222EC4 normal;
    Point_80222EC4 offset;
    float len;
    float dx;
    float dy;

    dy = pA->mY - pB->mY;
    dx = pA->mX - pB->mX;
    normal.mX = dy;
    normal.mY = dx;
    len = fn_80260B1C(dy * dy + dx * dx);
    if (len != 0.0f) {
        normal.mX /= len;
        normal.mY /= len;
    }
    width *= 0.25f;
    if (pDir != 0 && useDir != 0) {
        offset.mX = (pDir->mX + normal.mX) * 0.5f;
        offset.mY = (pDir->mY + normal.mY) * 0.5f;
        len = fn_80260B1C(offset.mX * offset.mX + offset.mY * offset.mY);
        if (len != 0.0f) {
            offset.mX /= len;
            offset.mY /= len;
        }
    } else {
        offset.mX = normal.mX;
        offset.mY = normal.mY;
    }
    offset.mX *= width;
    offset.mY *= width;
    pLeft->mX = pA->mX - offset.mX;
    pLeft->mY = pA->mY + offset.mY;
    pRight->mX = pA->mX + offset.mX;
    pRight->mY = pA->mY - offset.mY;
    if (pDir != 0) {
        pDir->mX = normal.mX;
        pDir->mY = normal.mY;
    }
}


void fn_80223224(int numPoints, Point_80222EC4 *pPoints, float *pWidths, Point_80222EC4 *pOut, int numOut)
{
    Point_80222EC4 dir;
    float stepA;
    float stepB;
    float width;
    int half;
    int i;
    int j;

    half = numOut / 2;
    stepB = (pWidths[2] - pWidths[1]) / half;
    stepA = (pWidths[1] - pWidths[0]) / half;
    fn_80222F8C(pPoints, numPoints, lbl_803A00D8, numOut);
    lbl_803A00D8[numOut].mX = lbl_803A00D8[numOut - 2].mX;
    lbl_803A00D8[numOut].mY = lbl_803A00D8[numOut - 2].mY;
    fn_8022306C(&lbl_803A00D8[0], &lbl_803A00D8[1], &pOut[0], &pOut[1], &dir, 0, pWidths[0]);
    width = pWidths[0];
    j = 2;
    for (i = 1; i < numOut - 1; i++) {
        if (i <= half) {
            width += stepA;
        } else {
            width += stepB;
        }
        fn_8022306C(&lbl_803A00D8[i], &lbl_803A00D8[i + 1], &pOut[j], &pOut[j + 1], &dir, 1, width);
        j += 2;
    }
    fn_8022306C(&lbl_803A00D8[numOut - 1], &lbl_803A00D8[numOut], &pOut[j], &pOut[j + 1], 0, 0, pWidths[2]);
}

Point_80222EC4 fn_802233DC(Point_80222EC4 *pPoints, int unused, int index)
{
    Point_80222EC4 result;

    if (index == 1) {
        result.mX = ((pPoints[0].mX + pPoints[2].mX) * 0.5f + pPoints[1].mX) * 0.5f;
        result.mY = ((pPoints[0].mY + pPoints[2].mY) * 0.5f + pPoints[1].mY) * 0.5f;
        return result;
    }
    return pPoints[index];
}

void fn_80223874(Node_80223874 *pNode)
{
    UIGLibrary_t *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 2) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
        pObject = UIGLibraryGetGlobal(1);
        if (UIGLibraryGetType(pObject, pNode->unk_06) & 2) {
            UIGFmvUpdate(pObject, pNode->unk_06, pNode->unk_04);
        }
        if (pNode->unk_0C != -1 && pNode->unk_0E != -1 &&
            UIGLibraryIsItemLoading(pObject, pNode->unk_06, pNode->unk_04) == 0) {
            UIGTexNodeSwap(pObject, &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        Item = UIGLibraryIsItemDataAvailable(pObject, pNode->unk_06, pNode->unk_04);
    }
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_80223B00(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_802239D0(Node_80223874 *pNode)
{
    UIGLibrary_t *pObject;

    if (pNode->Flags & 2) {
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            UIGLibraryLoadItem(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    fn_80223AA0(pNode);
}

void fn_80223A40(Node_80223874 *pNode)
{
    UIGLibrary_t *pObject;

    if (pNode->Flags & 2) {
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            UIGLibraryUnLoadItem(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    fn_80223AD0(pNode);
}

void fn_80223AA0(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListRelocate(&pNode->u.List);
    }
}

void fn_80223AD0(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListUnrelocate(&pNode->u.List);
    }
}
