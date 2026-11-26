/* Builds the curved ribbons in UI screens and manages their curve-node messages,
   library resources and display-list references. */

#include <math.h>

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
#include "engine/uigcurve.h"
#include "engine/uigcurverender.h"
#include "engine/viewport.h"
#include "engine/sound.h"
#include "engine/texture.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"



UIGCurvePoint_t _UIGCurve_aControlPoints[100];
UIGCurvePoint_t _UIGCurve_aSamples[101];

void _UIGCurveRelocate(UIGNode_t *pNode);
void _UIGCurveUnrelocate(UIGNode_t *pNode);

void _UIGCurveEvaluate(UIGCurvePoint_t *pPoints, int count, float t, UIGCurvePoint_t *pOut)
{
    int i;
    int j;

    for (j = 0; j < count; j++) {
        _UIGCurve_aControlPoints[j] = pPoints[j];
    }
    for (i = 1; i < count; i++) {
        for (j = 0; j < count - i; j++) {
            _UIGCurve_aControlPoints[j].mX = (1.0f - t) * _UIGCurve_aControlPoints[j].mX + t * _UIGCurve_aControlPoints[j + 1].mX;
            _UIGCurve_aControlPoints[j].mY = (1.0f - t) * _UIGCurve_aControlPoints[j].mY + t * _UIGCurve_aControlPoints[j + 1].mY;
        }
    }
    *pOut = _UIGCurve_aControlPoints[0];
}


void _UIGCurveSample(UIGCurvePoint_t *pPoints, int count, UIGCurvePoint_t *pOut, int numOut)
{
    float step;
    float t;
    int i;

    step = 1.0f / (numOut - 1);
    t = step;
    pOut[0] = pPoints[0];
    for (i = 1; i < numOut - 1; i++, t += step) {
        _UIGCurveEvaluate(pPoints, count, t, &pOut[i]);
    }
    pOut[numOut - 1] = pPoints[count - 1];
}

void _UIGCurveBuildOffset(UIGCurvePoint_t *pA, UIGCurvePoint_t *pB, UIGCurvePoint_t *pLeft, UIGCurvePoint_t *pRight,
                 float width, UIGCurvePoint_t *pDir, int useDir)
{
    UIGCurvePoint_t normal;
    UIGCurvePoint_t offset;
    float len;
    float dx;
    float dy;

    dy = pA->mY - pB->mY;
    dx = pA->mX - pB->mX;
    normal.mX = dy;
    normal.mY = dx;
    len = sqrtf(dy * dy + dx * dx);
    if (len != 0.0f) {
        normal.mX /= len;
        normal.mY /= len;
    }
    width *= 0.25f;
    if (pDir != 0 && useDir != 0) {
        offset.mX = (pDir->mX + normal.mX) * 0.5f;
        offset.mY = (pDir->mY + normal.mY) * 0.5f;
        len = sqrtf(offset.mX * offset.mX + offset.mY * offset.mY);
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


void UIGCurveBuildStrip(int numPoints, UIGCurvePoint_t *pPoints, float *pWidths, UIGCurvePoint_t *pOut, int numOut)
{
    UIGCurvePoint_t dir;
    float stepA;
    float stepB;
    float width;
    int i;
    int j;

    stepA = (pWidths[1] - pWidths[0]) / (numOut / 2);
    stepB = (pWidths[2] - pWidths[1]) / (numOut / 2);
    _UIGCurveSample(pPoints, numPoints, _UIGCurve_aSamples, numOut);
    _UIGCurve_aSamples[numOut].mX = _UIGCurve_aSamples[numOut - 2].mX;
    _UIGCurve_aSamples[numOut].mY = _UIGCurve_aSamples[numOut - 2].mY;
    _UIGCurveBuildOffset(&_UIGCurve_aSamples[0], &_UIGCurve_aSamples[1], &pOut[0], &pOut[1], pWidths[0], &dir, 0);
    width = pWidths[0];
    j = 2;
    for (i = 1; i < numOut - 1; i++, j += 2) {
        if (i <= numOut / 2) {
            width += stepA;
        } else {
            width += stepB;
        }
        _UIGCurveBuildOffset(&_UIGCurve_aSamples[i], &_UIGCurve_aSamples[i + 1], &pOut[j], &pOut[j + 1], width, &dir, 1);
    }
    _UIGCurveBuildOffset(&_UIGCurve_aSamples[numOut - 1], &_UIGCurve_aSamples[numOut], &pOut[j + 1], &pOut[j], pWidths[2], 0, 0);
}

UIGCurvePoint_t UIGCurveGetPoint(UIGCurvePoint_t *pPoints, int unused, int index)
{
    UIGCurvePoint_t result;

    if (index == 1) {
        result.mX = ((pPoints[index - 1].mX + pPoints[index + 1].mX) * 0.5f + pPoints[index].mX) * 0.5f;
        result.mY = ((pPoints[index - 1].mY + pPoints[index + 1].mY) * 0.5f + pPoints[index].mY) * 0.5f;
        return result;
    }
    return pPoints[index];
}



void _UIGCurveDraw(UIGNode_t *pNode);
void _UIGCurveLoad(UIGNode_t *pNode);
void _UIGCurveUnload(UIGNode_t *pNode);

void UIGCurveObjAction(UIGNode_t *pNode, Uint32 msg, int nArgs, UIGCurveArg_t *pArgs)
{
    switch (msg) {
    case -1:
        _UIGCurveLoad(pNode);
        break;
    case -2:
        _UIGCurveDraw(pNode);
        break;
    case -3:
        _UIGCurveUnload(pNode);
        break;
    /* FAKEMATCH: the empty case -4 leaves no compare in the target; it only moves the decision
       tree's root to 10 as in the target */
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
            UIGCurvePoint_t pt = UIGCurveGetPoint(pNode->u.c.unk_18, 3, index);

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

void _UIGCurveDraw(UIGNode_t *pNode)
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
        UIGCSSwapPalette(pNode->unk_0A, pNode->unk_08, Item);
    }
    UIGCurveRender(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        UIGCSRestorePalette(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void _UIGCurveLoad(UIGNode_t *pNode)
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
    _UIGCurveRelocate(pNode);
}

void _UIGCurveUnload(UIGNode_t *pNode)
{
    UIGLibrary_t *pObject;

    if (pNode->Flags & 2) {
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            UIGLibraryUnLoadItem(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    _UIGCurveUnrelocate(pNode);
}

void _UIGCurveRelocate(UIGNode_t *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListRelocate(&pNode->u.List);
    }
}

void _UIGCurveUnrelocate(UIGNode_t *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListUnrelocate(&pNode->u.List);
    }
}
