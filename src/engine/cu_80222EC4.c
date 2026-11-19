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
                 float width, Point_80222EC4 *pDir, int useDir)
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
    int i;
    int j;

    stepA = (pWidths[1] - pWidths[0]) / (numOut / 2);
    stepB = (pWidths[2] - pWidths[1]) / (numOut / 2);
    fn_80222F8C(pPoints, numPoints, lbl_803A00D8, numOut);
    lbl_803A00D8[numOut].mX = lbl_803A00D8[numOut - 2].mX;
    lbl_803A00D8[numOut].mY = lbl_803A00D8[numOut - 2].mY;
    fn_8022306C(&lbl_803A00D8[0], &lbl_803A00D8[1], &pOut[0], &pOut[1], pWidths[0], &dir, 0);
    width = pWidths[0];
    j = 2;
    for (i = 1; i < numOut - 1; i++, j += 2) {
        if (i <= numOut / 2) {
            width += stepA;
        } else {
            width += stepB;
        }
        fn_8022306C(&lbl_803A00D8[i], &lbl_803A00D8[i + 1], &pOut[j], &pOut[j + 1], width, &dir, 1);
    }
    fn_8022306C(&lbl_803A00D8[numOut - 1], &lbl_803A00D8[numOut], &pOut[j + 1], &pOut[j], pWidths[2], 0, 0);
}

Point_80222EC4 fn_802233DC(Point_80222EC4 *pPoints, int unused, int index)
{
    Point_80222EC4 result;

    if (index == 1) {
        result.mX = ((pPoints[index - 1].mX + pPoints[index + 1].mX) * 0.5f + pPoints[index].mX) * 0.5f;
        result.mY = ((pPoints[index - 1].mY + pPoints[index + 1].mY) * 0.5f + pPoints[index].mY) * 0.5f;
        return result;
    }
    return pPoints[index];
}

typedef union NodeArg_80223460 {
    Int32 i;
    Float32 f;
    void *p;
    Int16 s[2];
} NodeArg_80223460;

void fn_80223874(Node_80223874 *pNode);
void fn_802239D0(Node_80223874 *pNode);
void fn_80223A40(Node_80223874 *pNode);

void fn_80223460(Node_80223874 *pNode, Uint32 msg, int nArgs, NodeArg_80223460 *pArgs)
{
    switch (msg) {
    case -1:
        fn_802239D0(pNode);
        break;
    case -2:
        fn_80223874(pNode);
        break;
    case -3:
        fn_80223A40(pNode);
        break;
    case -4:
        break;
    case 13: {
        Uint32 index = pArgs[0].i;
        Float32 value = pArgs[1].f;

        if (index <= 2) {
            pNode->u.c.unk_38[index] = value;
        }
        break;
    }
    case 14: {
        Uint32 index = pArgs[0].i;

        if (index <= 2) {
            *(Float32 *)pArgs[1].p = pNode->u.c.unk_38[index];
        }
        break;
    }
    case 0: {
        Uint32 index = pArgs[0].i;
        Float32 x = pArgs[1].f;
        Float32 y = pArgs[2].f;

        if (index <= 2) {
            if (index == 1) {
                pNode->u.c.unk_18[1].mX = (x + x) - (pNode->u.c.unk_18[0].mX + pNode->u.c.unk_18[2].mX) * 0.5f;
                pNode->u.c.unk_18[1].mY = (y + y) - (pNode->u.c.unk_18[0].mY + pNode->u.c.unk_18[2].mY) * 0.5f;
            } else {
                pNode->u.c.unk_18[index].mX = x;
                pNode->u.c.unk_18[index].mY = y;
            }
        }
        break;
    }
    case 1: {
        Uint32 index = pArgs[0].i;

        if (index <= 2 && nArgs == 4) {
            Point_80222EC4 pt = fn_802233DC(pNode->u.c.unk_18, 3, index);

            *(Float32 *)pArgs[1].p = pt.mX;
            *(Float32 *)pArgs[2].p = pt.mY;
            *(Float32 *)pArgs[3].p = 0.0f;
        }
        break;
    }
    case 2:
        pNode->u.c.unk_30.mX = pArgs[0].f;
        pNode->u.c.unk_30.mY = pArgs[1].f;
        break;
    case 3:
        if (nArgs == 2) {
            *(Float32 *)pArgs[0].p = pNode->u.c.unk_30.mX;
            *(Float32 *)pArgs[1].p = pNode->u.c.unk_30.mY;
        }
        break;
    case 4:
        pNode->u.c.unk_14[0] = pArgs[0].i;
        pNode->u.c.unk_14[1] = pArgs[1].i;
        pNode->u.c.unk_14[2] = pArgs[2].i;
        break;
    case 5:
        if (nArgs == 3) {
            *(Int32 *)pArgs[0].p = pNode->u.c.unk_14[0];
            *(Int32 *)pArgs[1].p = pNode->u.c.unk_14[1];
            *(Int32 *)pArgs[2].p = pNode->u.c.unk_14[2];
        }
        break;
    case 11:
        pNode->u.c.unk_10 = (signed char)pArgs[0].i;
        if (pNode->u.c.unk_10 > 100) {
            pNode->u.c.unk_10 = 100;
        } else if (pNode->u.c.unk_10 < 2) {
            pNode->u.c.unk_10 = 2;
        }
        break;
    case 12:
        if (nArgs == 1) {
            *(Int32 *)pArgs[0].p = pNode->u.c.unk_10;
        }
        break;
    case 6:
        pNode->u.c.unk_14[3] = pArgs[0].i;
        break;
    case 7:
        if (nArgs == 1) {
            *(Int32 *)pArgs[0].p = pNode->u.c.unk_14[3];
        }
        break;
    case 8:
        pNode->unk_02 = pArgs[0].i;
        break;
    case 9:
        if (nArgs == 1) {
            *(Int32 *)pArgs[0].p = pNode->unk_02;
        }
        break;
    case 10: {
        Int16 lib = pArgs[0].s[0];

        pNode->unk_0E = lib;
        pNode->unk_0C = pArgs[0].s[1];
        if (lib == 0) {
            pNode->unk_0E = pNode->unk_06;
        }
        if (pNode->unk_0E == -1) {
            pNode->unk_0E = pNode->unk_06;
        }
        if (pNode->unk_0C == -1) {
            pNode->unk_0C = pNode->unk_04;
        }
        if (*(Int32 *)&pNode->unk_0C != *(Int32 *)&pNode->unk_04) {
            UIGTexNodeSwap(UIGLibraryGetGlobal(1), &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
        }
        break;
    }
    case 15: {
        Int16 lib = pArgs[0].s[0];
        Int16 item = pArgs[0].s[1];

        if ((pNode->Flags & 0x10) || (lib != -1 && item != -1)) {
            pNode->unk_08 = item;
            pNode->unk_0A = lib;
        }
        break;
    }
    case 16:
        pNode->u.c.unk_14[0] = pArgs[0].i;
        break;
    }
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
