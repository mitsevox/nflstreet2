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

/* UI graphics arc node: the menu shape that draws a filled or ring-shaped
   ellipse arc (start and end angle, radii, centre, segment count, two
   colours blended along the arc) as a GX triangle fan or strip, with its
   load, unload, draw and action handlers. */

typedef void UIGArcVertexFunc_t(UIGNode_t *pNode, Int32 Index, Float32 *pCoord);

Float32 _UIGArc_aTexMtx[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
GXColor _UIGArc_cMaterialColor = {0x12, 0x34, 0x56, 0x78};
GXColor _UIGArc_cLightColor = {0x12, 0x34, 0x56, 0x78};
extern GXLightObj LLUIGTexLightObj;
Float32 UIGArcVertexCoords[512][2];
GXColor UIGArcVertexColors[512];

void TMRenderReset(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);

void _UIGArcRender(UIGNode_t *pNode, Int32 Item);
void _UIGArcBuildStrip(UIGNode_t *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, UIGArcVertexFunc_t *pVertex, UIGArcVertexFunc_t *pEnd);
void _UIGArcSetClamp(UIGNode_t *pNode, Int32 a, Int32 Item);
void _UIGArcSetupRender(Uint32 Flags);
void LLUIGVertexSend(UIGNode_t *pNode, Int32 Index, Float32 *pCoord);
void LLUIGVertexEnd(UIGNode_t *pNode, Int32 Index, Float32 *pCoord);
void _UIGArcRelocate(UIGNode_t *pNode);
void _UIGArcUnrelocate(UIGNode_t *pNode);
void _UIGArcSetMaterialColors(void);
void MathSinCos(int angle, float *pSin, float *pCos);

typedef struct UIGArcPalette_t {
    Uint8 mCount;
    Uint8 unk_01[3];
    GXColor mColors[1];
} UIGArcPalette_t;

void _UIGArcBuildFan(UIGNode_t *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, UIGArcVertexFunc_t *pVertex, UIGArcVertexFunc_t *pEnd)
{
    Float32 Start;
    Float32 End;
    Float32 Step;
    GXColor Color0;
    GXColor Color1;
    UIGArcPalette_t *pPalette;
    Int32 i;
    Int32 Vertex;
    Int32 Batch;
    Float32 Sin;
    Float32 Cos;
    Int32 Angle;

    Start = (pNode->Flags & 0x10) ? 0.0f : pNode->u.t.unk_34;
    End = (pNode->Flags & 0x10) ? 360.0f : pNode->u.t.unk_38;
    if (!(Start <= End)) {
        Start -= 360.0f;
    }
    memcpy(&Color0, pNode->u.t.unk_14, sizeof(Color0));
    memcpy(&Color1, pNode->u.t.unk_18, sizeof(Color1));
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGArcPalette_t *)UIGCSGetColorStyle(pNode->unk_0A, pNode->unk_08);
        if (pPalette != 0) {
            if (Color0.r > pPalette->mCount) Color0.r = pPalette->mCount - 1;
            if (Color1.r > pPalette->mCount) Color1.r = pPalette->mCount - 1;
            Color0 = pPalette->mColors[Color0.r];
            Color1 = pPalette->mColors[Color1.r];
        }
    }
    i = 0;
    Vertex = 1;
    Batch = 1;
    pColors->r = Color0.r;
    pColors->g = Color0.g;
    pColors->b = Color0.b;
    pColors->a = Color0.a;
    pColors++;
    (*pCoords)[0] = pNode->u.t.unk_3C[0];
    (*pCoords)[1] = pNode->u.t.unk_3C[1];
    pVertex(pNode, 0, 0);
    pCoords++;
    Step = (End - Start) / (Uint32)pNode->u.t.unk_10;
    for (; i <= pNode->u.t.unk_10; i++) {
        if (pNode->Flags & 0x20) {
            pColors->a = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.a;
            pColors->a += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.a;
            if ((pNode->Flags & 6) != 4) {
                pColors->r = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.r;
                pColors->r += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.r;
                pColors->g = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.g;
                pColors->g += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.g;
                pColors->b = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.b;
                pColors->b += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.b;
            }
        } else {
            pColors->r = Color0.r;
            pColors->g = Color0.g;
            pColors->b = Color0.b;
            pColors->a = Color0.a;
        }
        pColors++;
        if (i == pNode->u.t.unk_10) {
            Angle = (Int32)(End * 46603.378f) & 0xFFFFFF;
        } else {
            Angle = (Int32)((Start + Step * i) * 46603.378f) & 0xFFFFFF;
        }
        Batch++;
        MathSinCos(Angle, &Sin, &Cos);
        (*pCoords)[0] = pNode->u.t.unk_2C[0] * Cos + pNode->u.t.unk_3C[0];
        (*pCoords)[1] = pNode->u.t.unk_2C[1] * Sin + pNode->u.t.unk_3C[1];
        pVertex(pNode, Vertex++, 0);
        pCoords++;
        if (Batch == Count || i == pNode->u.t.unk_10) {
            ((void (*)(UIGNode_t *))pEnd)(pNode);
            if (i < pNode->u.t.unk_10) {
                Batch = 2;
                pVertex(pNode, 0, 0);
                pVertex(pNode, Vertex - 1, 0);
            }
        }
    }
}

void _UIGArcLoad(UIGNode_t *pNode)
{
    UIGLibrary_t *pObject;

    if (pNode->Flags & 4) {
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            UIGLibraryLoadItem(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    _UIGArcRelocate(pNode);
}

void _UIGArcUnload(UIGNode_t *pNode)
{
    _UIGArcUnrelocate(pNode);
}

void _UIGArcBuildStrip(UIGNode_t *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, UIGArcVertexFunc_t *pVertex, UIGArcVertexFunc_t *pEnd)
{
    Float32 aTex[4][2];
    GXColor Color0;
    GXColor Color1;
    Float32 Sin;
    Float32 Cos;
    Float32 aInner[2];
    UIGArcPalette_t *pPalette;
    Float32 Start;
    Float32 End;
    Float32 Step;
    Int32 Vertex = 0;
    Int32 i;
    Int32 bFlip;
    Int32 bSwap;
    Int32 Angle;
    Uint16 Flags = pNode->Flags;

    if (!(Flags & 5)) {
        _UIGArcBuildFan(pNode, pCoords, pColors, pSize, Count, pVertex, pEnd);
        return;
    }
    if (Flags & 4) {
        bFlip = (pNode->u.t.unk_12 >> 1) & 1;
        bSwap = pNode->u.t.unk_12 & 1;
        aTex[0][0] = bFlip + pNode->u.t.unk_1C[0];
        aTex[0][1] = pNode->u.t.unk_1C[1];
        if (bSwap == bFlip) {
            aTex[0][1] = pNode->u.t.unk_1C[1] + 1.0f;
        }
        aTex[1][0] = (bSwap ^ bFlip) + pNode->u.t.unk_1C[0];
        aTex[1][1] = (bSwap ^ bFlip) + pNode->u.t.unk_1C[1];
        aTex[2][0] = pNode->u.t.unk_1C[0];
        if (bSwap == bFlip) {
            aTex[2][0] = pNode->u.t.unk_1C[0] + 1.0f;
        }
        aTex[2][1] = pNode->u.t.unk_1C[1];
        if (bFlip == 0) {
            aTex[2][1] = pNode->u.t.unk_1C[1] + 1.0f;
        }
        aTex[3][0] = pNode->u.t.unk_1C[0];
        if (bFlip == 0) {
            aTex[3][0] = pNode->u.t.unk_1C[0] + 1.0f;
        }
        aTex[3][1] = (bSwap ^ bFlip) + pNode->u.t.unk_1C[1];
    }
    Start = (Flags & 0x10) ? 0.0f : pNode->u.t.unk_34;
    End = (Flags & 0x10) ? 360.0f : pNode->u.t.unk_38;
    if (!(Start <= End)) {
        Start -= 360.0f;
    }
    if (Flags & 1) {
        aInner[0] = pNode->u.t.unk_24[0] * pNode->u.t.unk_2C[0];
        aInner[1] = pNode->u.t.unk_24[1] * pNode->u.t.unk_2C[1];
    } else {
        aInner[0] = aInner[1] = 0.0f;
    }
    memcpy(&Color0, pNode->u.t.unk_14, sizeof(Color0));
    memcpy(&Color1, pNode->u.t.unk_18, sizeof(Color1));
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGArcPalette_t *)UIGCSGetColorStyle(pNode->unk_0A, pNode->unk_08);
        if (pPalette != 0) {
            if (Color0.r >= pPalette->mCount) Color0.r = pPalette->mCount - 1;
            if (Color1.r >= pPalette->mCount) Color1.r = pPalette->mCount - 1;
            Color0 = pPalette->mColors[Color0.r];
            Color1 = pPalette->mColors[Color1.r];
        }
    }
    Step = (End - Start) / (Uint32)pNode->u.t.unk_10;
    for (i = 0; i < pNode->u.t.unk_10;) {
        if (i == 0) {
            if (Flags & 0x20) {
                pColors->a = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.a;
                pColors->a += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.a;
                if ((Flags & 6) != 4) {
                    pColors->r = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.r;
                    pColors->r += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.r;
                    pColors->g = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.g;
                    pColors->g += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.g;
                    pColors->b = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.b;
                    pColors->b += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.b;
                }
            } else if (Flags & 2) {
                pColors->r = Color0.r;
                pColors->g = Color0.g;
                pColors->b = Color0.b;
                pColors->a = Color0.a;
            } else {
                pColors->r = 0xFF;
                pColors->g = 0xFF;
                pColors->b = 0xFF;
                pColors->a = Color0.a;
            }
            pColors++;
            Angle = (Int32)(Start * 46603.378f) & 0xFFFFFF;
            MathSinCos(Angle, &Sin, &Cos);
            (*pCoords)[0] = aInner[0] * Cos + pNode->u.t.unk_3C[0];
            (*pCoords)[1] = aInner[1] * Sin + pNode->u.t.unk_3C[1];
            *pColors = pColors[-1];
            pColors++;
            pCoords++;
            (*pCoords)[0] = pNode->u.t.unk_2C[0] * Cos + pNode->u.t.unk_3C[0];
            (*pCoords)[1] = pNode->u.t.unk_2C[1] * Sin + pNode->u.t.unk_3C[1];
            pCoords++;
        }
        i++;
        pVertex(pNode, Vertex++, aTex[0]);
        pVertex(pNode, Vertex++, aTex[1]);
        if (Flags & 0x20) {
            pColors->a = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.a;
            pColors->a += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.a;
            if ((Flags & 6) != 4) {
                pColors->r = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.r;
                pColors->r += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.r;
                pColors->g = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.g;
                pColors->g += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.g;
                pColors->b = (Float32)(pNode->u.t.unk_10 - i) / (Uint32)pNode->u.t.unk_10 * (Uint32)Color0.b;
                pColors->b += (Float32)i / (Uint32)pNode->u.t.unk_10 * (Uint32)Color1.b;
            }
        } else if (Flags & 2) {
            pColors->r = Color0.r;
            pColors->g = Color0.g;
            pColors->b = Color0.b;
            pColors->a = Color0.a;
        } else {
            pColors->r = 0xFF;
            pColors->g = 0xFF;
            pColors->b = 0xFF;
            pColors->a = Color0.a;
        }
        pColors++;
        if (i == pNode->u.t.unk_10) {
            Angle = (Int32)(End * 46603.378f) & 0xFFFFFF;
        } else {
            Angle = (Int32)((Start + Step * i) * 46603.378f) & 0xFFFFFF;
        }
        MathSinCos(Angle, &Sin, &Cos);
        (*pCoords)[0] = aInner[0] * Cos + pNode->u.t.unk_3C[0];
        (*pCoords)[1] = aInner[1] * Sin + pNode->u.t.unk_3C[1];
        pVertex(pNode, Vertex++, aTex[2]);
        pCoords++;
        *pColors = pColors[-1];
        pColors++;
        (*pCoords)[0] = pNode->u.t.unk_2C[0] * Cos + pNode->u.t.unk_3C[0];
        (*pCoords)[1] = pNode->u.t.unk_2C[1] * Sin + pNode->u.t.unk_3C[1];
        pVertex(pNode, Vertex++, aTex[3]);
        Vertex -= 2;
        pCoords++;
        ((void (*)(UIGNode_t *))pEnd)(pNode);
    }
}

void _UIGArcDraw(UIGNode_t *pNode)
{
    UIGLibrary_t *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 4) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
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
    if (Item != 0 && (pNode->Flags & 0x100) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        UIGCSSwapPalette(pNode->unk_0A, pNode->unk_08, Item);
    }
    _UIGArcRender(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x100) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        UIGCSRestorePalette(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void UIGArcObjAction(UIGNode_t *pNode, Uint32 Action, Int32 a, void *pData)
{
    Int16 First;
    Int16 Second;
    Int16 Value;

    switch (Action) {
    case -1:
        _UIGArcLoad(pNode);
        break;
    case -2:
        _UIGArcDraw(pNode);
        break;
    case -3:
        _UIGArcUnload(pNode);
        break;
    /* FAKEMATCH: the empty case -4 leaves no compare in the target; it only roots the decision
       tree at -2 as in the target (cmpwi r30,-2 at 0x80225670; without it 97.44%) */
    case -4:
        break;
    }
    if (!(pNode->Flags & 0x8000)) {
        switch (Action) {
        case 0:
            pNode->u.t.unk_3C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_3C[1] = ((Float32 *)pData)[1];
            break;
        case 1:
            pNode->u.t.unk_24[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_24[1] = ((Float32 *)pData)[1];
            break;
        case 2:
            pNode->u.t.unk_2C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_2C[1] = ((Float32 *)pData)[1];
            break;
        case 3:
            pNode->u.t.unk_34 = ((Float32 *)pData)[0];
            break;
        case 4:
            pNode->u.t.unk_38 = ((Float32 *)pData)[0];
            break;
        case 5:
            pNode->u.t.unk_1C[0] = ((Float32 *)pData)[0];
            pNode->u.t.unk_1C[1] = ((Float32 *)pData)[1];
            break;
        case 6:
            pNode->u.t.unk_14[0] = ((Int32 *)pData)[0];
            pNode->u.t.unk_14[1] = ((Int32 *)pData)[1];
            pNode->u.t.unk_14[2] = ((Int32 *)pData)[2];
            pNode->u.t.unk_14[3] = ((Int32 *)pData)[3];
            break;
        case 7:
            pNode->u.t.unk_18[0] = ((Int32 *)pData)[0];
            pNode->u.t.unk_18[1] = ((Int32 *)pData)[1];
            pNode->u.t.unk_18[2] = ((Int32 *)pData)[2];
            pNode->u.t.unk_18[3] = ((Int32 *)pData)[3];
            break;
        case 8:
            pNode->u.t.unk_10 = ((Int32 *)pData)[0];
            break;
        case 9:
            Value = ((Int16 *)pData)[0];
            pNode->unk_0E = Value;
            pNode->unk_0C = ((Int16 *)pData)[1];
            if (Value == 0) {
                pNode->unk_0E = pNode->unk_06;
            }
            if (pNode->unk_0E == -1) {
                pNode->unk_0E = pNode->unk_06;
            }
            if (pNode->unk_0C == -1) {
                pNode->unk_0C = pNode->unk_04;
            }
            if (pNode->unk_0C != pNode->unk_04 || pNode->unk_0E != pNode->unk_06) {
                UIGTexNodeSwap(UIGLibraryGetGlobal(1), &pNode->unk_06, &pNode->unk_04, pNode->unk_0E,
                            pNode->unk_0C);
            }
            break;
        case 10:
            if (pNode->unk_02 != ((Int32 *)pData)[0]) {
                UIGTexNodeUpdate(UIGLibraryGetGlobal(1), pNode->unk_06, pNode->unk_04,
                            (Int16)((Int32 *)pData)[0]);
            }
            break;
        case 11:
            First = ((Int16 *)pData)[0];
            Second = ((Int16 *)pData)[1];
            if ((pNode->Flags & 0x100) || (First != -1 && Second != -1)) {
                pNode->unk_08 = Second;
                pNode->unk_0A = First;
            }
            break;
        case 12:
            pNode->u.t.unk_14[0] = ((Int32 *)pData)[0];
            break;
        case 13:
            pNode->u.t.unk_18[0] = ((Int32 *)pData)[0];
            break;
        }
    }
}

void _UIGArcUnrelocate(UIGNode_t *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListUnrelocate(&pNode->u.List);
    }
}

void _UIGArcRelocate(UIGNode_t *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListRelocate(&pNode->u.List);
    }
}

void _UIGArcRender(UIGNode_t *pNode, Int32 Item)
{
    Int32 bTex = 0;
    Int32 Count;
    Int32 Size;

    _UIGArcSetupRender(pNode->Flags);
    if (pNode->Flags & 4) {
        if (Item == 0) {
            return;
        }
        _UIGArc_aTexMtx[0][0] = ((UIGTexNode_t *)Item)->unk_30;
        _UIGArc_aTexMtx[1][1] = ((UIGTexNode_t *)Item)->unk_34;
        GXLoadTexMtxImm(_UIGArc_aTexMtx, GX_TEXMTX0, GX_MTX2x4);
        _UIGArcSetClamp(pNode, 0, Item);
        bTex = LLUIGTexNodeRegisterObj((Texture_t *)Item);
    }
    if (pNode->Flags & 0x8000) {
        UIGDispListCall(&pNode->u.List);
    } else {
        Size = 512;
        if (!(pNode->Flags & 4) && !(pNode->Flags & 1)) {
            Count = pNode->u.t.unk_10 + 2;
            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, Count);
        } else {
            Count = pNode->u.t.unk_10 * 4;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, Count);
        }
        _UIGArcBuildStrip(pNode, UIGArcVertexCoords, UIGArcVertexColors, &Size, Count, LLUIGVertexSend, LLUIGVertexEnd);
    }
    GXSetCullMode(GX_CULL_NONE);
    if (bTex) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

void _UIGArcSetClamp(UIGNode_t *pNode, Int32 a, Int32 Item)
{
    Int32 First = 0;
    Int32 Second = 0;

    if (a != 0) {
        First = 1;
        Second = 1;
    }
    LLUIGSetClamp(First, Second, (Texture_t *)Item);
}

void _UIGArcSetMaterialColors(void)
{
    UIGMaterialColorState_t *pColor = UIGRenderGetColorState();
    GXColor MatColor = pColor->mMaterialColor;
    GXColor LightColor = pColor->mLightColor;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&LLUIGTexLightObj, LightColor);
    GXLoadLightObjImm(&LLUIGTexLightObj, GX_LIGHT7);
    _UIGArc_cMaterialColor = MatColor;
    _UIGArc_cLightColor = LightColor;
}

void _UIGArcSetupRender(Uint32 Flags)
{
    Int32 bColor = 1;
    Int32 bTex;

    if ((Flags & 6) == 4) {
        bColor = 0;
    }
    TMRenderReset();
    bTex = Flags & 4;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    LLUIGSetColorChannel(bColor);
    LLUIGSetTexturing(bTex);
    _UIGArcSetMaterialColors();
    if (Flags & 0x8000) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    } else {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }
    GXSetCullMode(!(Flags & 8) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])MatGetCurMatrixPtr(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
}
