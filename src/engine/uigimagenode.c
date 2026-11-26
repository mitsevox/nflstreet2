#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include "UIStudio/UIStudio.h"
#include "engine/Resource.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* UI image and colour nodes: the node type of UI Studio screens that draws a
   quad (or a ten-vertex strip) with per-corner colours, positions and, for
   image nodes, texture coordinates of a library texture. Handles the node's
   load, update, draw and unload steps and its property messages, sets up the
   GX vertex formats and colour channel, and sends the vertices to GX in
   immediate mode. Three draw functions are documented holdouts and keep their
   original bytes. */

/* A colour that is also compared as one word. */
typedef union ColorWord_80220988 {
    GXColor Color;
    Uint32 Value;
} ColorWord_80220988;

extern GXLightObj lbl_803E9880;

static Float32 lbl_802F9FA0[4][4] = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
};
static Uint32 lbl_803ECFF0;
static Uint32 lbl_803ECFF4;
static Int32 lbl_803ECFF8;

void fn_8021F8DC(UIGNode_t *pNode);
void fn_8021F954(UIGNode_t *pNode);
void fn_8021F984(UIGNode_t *pNode, Int32 Item);
void fn_8021FB30(UIGNode_t *pNode);
void fn_80220310(UIGNode_t *pNode);
void fn_80220988(void);
void fn_80220A08(void);
void fn_80220AD0(UIGNode_t *pNode, Int32 a, Int32 Item);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);
void TMRenderReset(void);
void fn_8021F550(UIGNode_t *pNode);
void fn_8021F5C0(UIGNode_t *pNode);
void fn_8021F71C(UIGNode_t *pNode);
Uint8 fn_8021F77C(Uint32 a, Uint32 b, Uint32 c, Uint32 d, Float32 s, Float32 t);
Int16 fn_8021F82C(Int16 a, Int16 b, Int16 c, Int16 d, Float32 s, Float32 t);

/* Colour table of a palette library item: a count, then the colours. */
typedef struct UIGNodePalette_t {
    Uint8 Count;            /* 0x00 */
    Uint8 unk_01[3];
    GXColor Colors[1];      /* 0x04 */
} UIGNodePalette_t;

/* One vertex as the node renderers send it to GX. */
typedef struct UIGNodeVertex_t {
    GXColor Color;          /* 0x00 */
    Int16 St[2];            /* 0x04 */
    Int16 Pos[3];           /* 0x08 */
} UIGNodeVertex_t;

void fn_8021EFD8(UIGNode_t *pNode, Uint32 Msg, Int32 Unused, void *pData, void *pOut)
{
    UIGLibrary_t *pObject;
    Int32 i;
    Uint16 Index;
    Uint16 Item;

    switch (Msg) {
    case -1:
        fn_8021F550(pNode);
        break;
    case -2:
        fn_8021F5C0(pNode);
        return;
    case -3:
        fn_8021F71C(pNode);
        break;
    case -4:
        if (pNode->Flags & 2) {
            pObject = UIGLibraryGetGlobal(1);
            if (UIGLibraryGetType(pObject, pNode->unk_06) & 2) {
                if (*(Int32 *)pData != 0) {
                    if (pNode->unk_06 != -1 && pNode->unk_04 != -1 &&
                        UIGLibraryReferenceCount(pObject, pNode->unk_06, pNode->unk_04) == 0) {
                        UIGLibraryLoadItem(pObject, pNode->unk_06, pNode->unk_04);
                    }
                } else if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
                    UIGLibraryUnLoadItem(pObject, pNode->unk_06, pNode->unk_04);
                }
            }
        }
        break;
    case 0:
        {
            Float32 x = ((Float32 *)pData)[1] * 16.0f;
            Float32 y = ((Float32 *)pData)[2] * 16.0f;
            Float32 z = ((Float32 *)pData)[3] * 16.0f;

            i = ((Int32 *)pData)[0];
            pNode->u.v.Quad.Pos[i][0] = x;
            pNode->u.v.Quad.Pos[i][1] = y;
            pNode->u.v.Quad.Pos[i][2] = z;
        }
        break;
    case 1:
        {
            Float32 s = ((Float32 *)pData)[1] * 256.0f;
            Float32 t = ((Float32 *)pData)[2] * 256.0f;

            i = ((Int32 *)pData)[0];
            pNode->u.v.Quad.Coords[i][0] = s;
            pNode->u.v.Quad.Coords[i][1] = t;
        }
        break;
    case 2:
        {
        Uint8 b = ((Int32 *)pData)[3];
        Uint8 r = ((Int32 *)pData)[1];
        Uint8 g = ((Int32 *)pData)[2];

        if (((Int32 *)pData)[0] == -1) {
            for (i = 3; i >= 0; i--) {
                pNode->u.v.Quad.Colors[i].r = r;
                pNode->u.v.Quad.Colors[i].g = g;
                pNode->u.v.Quad.Colors[i].b = b;
            }
        } else {
            i = ((Int32 *)pData)[0];
            pNode->u.v.Quad.Colors[i].r = r;
            pNode->u.v.Quad.Colors[i].g = g;
            pNode->u.v.Quad.Colors[i].b = b;
        }
        }
        break;
    case 3:
        {
        Uint8 a = ((Int32 *)pData)[1];

        if (((Int32 *)pData)[0] == -1) {
            for (i = 3; i >= 0; i--) {
                pNode->u.v.Quad.Colors[i].a = a;
            }
        } else {
            pNode->u.v.Quad.Colors[((Int32 *)pData)[0]].a = a;
        }
        }
        break;
    case 4:
        if (pNode->unk_02 != ((Int32 *)pData)[0]) {
            UIGTexNodeUpdate(UIGLibraryGetGlobal(1), pNode->unk_06, pNode->unk_04, (Int16)((Int32 *)pData)[0]);
        }
        break;
    case 5:
        Index = ((Uint16 *)pData)[0];
        Item = ((Uint16 *)pData)[1];
        if (Index == 0) {
            Index = pNode->unk_06;
        }
        if (Index == 0xFFFF) {
            Index = pNode->unk_06;
        }
        pObject = UIGLibraryGetGlobal(1);
        if (!(pNode->Flags & 2)) {
            UIGTexNodeSwap(pObject, &pNode->unk_06, &pNode->unk_04, Index, Item);
            pNode->Flags |= 2;
        } else {
            if (Index != pNode->unk_06 || Item != pNode->unk_04) {
                if (UIGLibraryIsItemLoading(pObject, pNode->unk_06, pNode->unk_04) != 0) {
                    pNode->unk_0C = Item;
                    pNode->unk_0E = Index;
                    break;
                }
                UIGTexNodeSwap(pObject, &pNode->unk_06, &pNode->unk_04, Index, Item);
            }
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        break;
    case 6:
        {
        Float32 x = ((Float32 *)pData)[0];
        Float32 y = ((Float32 *)pData)[1];

        if (!(x <= 1.0f)) {
            x = 1.0f;
        }
        if (!(x >= 0.0f)) {
            x = 0.0f;
        }
        pNode->u.v.Scale[0] = x * 65535.0f;
        if (!(y <= 1.0f)) {
            y = 1.0f;
        }
        if (!(y >= 0.0f)) {
            y = 0.0f;
        }
        pNode->u.v.Scale[1] = y * 65535.0f;
        }
        break;
    case 7:
        {
            Int16 Lib = ((Int16 *)pData)[0];
            Int16 Entry = ((Int16 *)pData)[1];

            if ((pNode->Flags & 0x10) || (Lib != -1 && Entry != -1)) {
                pNode->unk_08 = Entry;
                pNode->unk_0A = Lib;
            }
        }
        break;
    case 8:
        pObject = UIGLibraryGetGlobal(1);
        if (UIGLibraryGetType(pObject, pNode->unk_06) & 2) {
            UIGFmvStart(pObject, pNode->unk_06, pNode->unk_04);
        }
        break;
    case 9:
        pObject = UIGLibraryGetGlobal(1);
        if (UIGLibraryGetType(pObject, pNode->unk_06) & 2) {
            UIGFmvStop(pObject, pNode->unk_06, pNode->unk_04);
        }
        break;
    case 10:
        {
        Uint8 r = ((Int32 *)pData)[1];

        if (((Int32 *)pData)[0] == -1) {
            for (i = 3; i >= 0; i--) {
                pNode->u.v.Quad.Colors[i].r = r;
            }
        } else {
            pNode->u.v.Quad.Colors[((Int32 *)pData)[0]].r = r;
        }
        }
        break;
    case 11:
        {
            UIGLibrary_t *pLib = UIGLibraryGetGlobal(1);

            if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
                *(Int32 *)pOut = UIGLibraryIsItemLoading(pLib, pNode->unk_06, pNode->unk_04) == 0;
            } else {
                *(Int32 *)pOut = 0;
            }
        }
        break;
    }
    pNode->Flags |= 0x4000;
}

void fn_8021F550(UIGNode_t *pNode)
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
    fn_8021F8DC(pNode);
}

void fn_8021F5C0(UIGNode_t *pNode)
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
        UIGRenderSwapPalette(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_8021F984(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        UIGRenderRestorePalette(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_8021F71C(UIGNode_t *pNode)
{
    UIGLibrary_t *pObject;

    if (pNode->Flags & 2) {
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            UIGLibraryUnLoadItem(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    fn_8021F954(pNode);
}

Uint8 fn_8021F77C(Uint32 a, Uint32 b, Uint32 c, Uint32 d, Float32 s, Float32 t)
{
    Float32 lo = a + (Int32)(b - a) * s;
    Float32 hi = d + (Int32)(c - d) * s;

    return lo + (hi - lo) * t;
}

Int16 fn_8021F82C(Int16 a, Int16 b, Int16 c, Int16 d, Float32 s, Float32 t)
{
    Float32 lo = a + (b - a) * s;
    Float32 hi = d + (c - d) * s;

    return lo + (hi - lo) * t;
}

void fn_8021F8DC(UIGNode_t *pNode)
{
    Int32 i;

    if (pNode->Flags & 0x8000) {
        UIGDispListRelocate(&pNode->u.List);
    } else if ((pNode->Flags & 3) == 2) {
        pNode->Flags |= 1;
        for (i = 0; i < 4; i++) {
            pNode->u.v.Quad.Colors[i].r = 255;
            pNode->u.v.Quad.Colors[i].g = 255;
            pNode->u.v.Quad.Colors[i].b = 255;
        }
    }
}

void fn_8021F954(UIGNode_t *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListUnrelocate(&pNode->u.List);
    }
}

void fn_8021F984(UIGNode_t *pNode, Int32 Item)
{
    Uint16 Flags;
    Int32 Mode;
    Int32 bTex = 0;
    Int32 bTexture;

    if ((pNode->Flags & 2) && Item == 0) {
        return;
    }
    Flags = pNode->Flags;
    TMRenderReset();
    Mode = Flags & 3;
    fn_80220A08();
    lbl_803ECFF8 = -1;
    fn_80220988();
    if (Mode != lbl_803ECFF8) {
        bTexture = Flags & 2;
        LLUIGSetColorChannel(Mode == 2 ? 0 : 1);
        LLUIGSetTexturing(bTexture);
        lbl_803ECFF8 = Mode;
    }
    GXSetCullMode((Flags & 4) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])MatGetCurMatrixPtr(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (pNode->Flags & 2) {
        lbl_802F9FA0[0][0] = ((UIGTexNode_t *)Item)->unk_30;
        lbl_802F9FA0[1][1] = ((UIGTexNode_t *)Item)->unk_34;
        GXLoadTexMtxImm(lbl_802F9FA0, GX_TEXMTX0, GX_MTX2x4);
        if (!(pNode->Flags & 0x8000)) {
            fn_80220AD0(pNode, 0, Item);
        }
        bTex = LLUIGTexNodeRegisterObj((Texture_t *)Item);
    }
    if (pNode->Flags & 0x8000) {
        UIGDispListCall(&pNode->u.List);
    } else {
        if (pNode->Flags & 8) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
        } else {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        }
        if (pNode->Flags & 2) {
            fn_8021FB30(pNode);
        } else {
            fn_80220310(pNode);
        }
    }
    GXSetCullMode(GX_CULL_NONE);
    if (bTex) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

static inline void SendTexVertex(UIGNodeVertex_t *pV)
{
    GXPosition3s16(pV->Pos[0], pV->Pos[1], pV->Pos[2]);
    GXColor4u8(pV->Color.r, pV->Color.g, pV->Color.b, pV->Color.a);
    GXTexCoord2s16(pV->St[0], pV->St[1]);
}

static inline void SendColorVertex(UIGNodeVertex_t *pV)
{
    GXPosition3s16(pV->Pos[0], pV->Pos[1], pV->Pos[2]);
    GXColor4u8(pV->Color.r, pV->Color.g, pV->Color.b, pV->Color.a);
}

void fn_8021FB30(UIGNode_t *pNode)
{
    UIGNodeVertex_t aVtx[8];
    Float32 aS[4];
    Float32 aT[4];
    UIGNodePalette_t *pPalette = NULL;
    Float32 S;
    Float32 T;
    Int32 i;
    UIGNodeQuad_t *pQuad;

    UIGRenderGetColorState();
    pQuad = &pNode->u.v.Quad;
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGNodePalette_t *)fn_80220B4C(pNode->unk_0A, pNode->unk_08);
    }
    for (i = 0; i < 4; i++) {
        aVtx[i].Color = pQuad->Colors[i];
        if (pPalette != NULL && !(pNode->Flags & 0x10)) {
            if (aVtx[i].Color.r > pPalette->Count) {
                aVtx[i].Color.r = pPalette->Count - 1;
            }
            aVtx[i].Color = pPalette->Colors[aVtx[i].Color.r];
        }
        aVtx[i].Color.r = (Float32)aVtx[i].Color.r;
        aVtx[i].Color.g = (Float32)aVtx[i].Color.g;
        aVtx[i].Color.b = (Float32)aVtx[i].Color.b;
        aVtx[i].Color.a = (Float32)aVtx[i].Color.a;
        aVtx[i].St[0] = pQuad->Coords[i][0];
        aVtx[i].St[1] = pQuad->Coords[i][1];
        aVtx[i].Pos[0] = pQuad->Pos[i][0];
        aVtx[i].Pos[1] = pQuad->Pos[i][1];
        aVtx[i].Pos[2] = pQuad->Pos[i][2];
    }
    if (pNode->Flags & 8) {
        S = pNode->u.v.Scale[0] * (1.0f / 131070.0f);
        T = pNode->u.v.Scale[1] * (1.0f / 131070.0f);
        aS[0] = 0.5f - S;
        aS[1] = S + 0.5f;
        aS[2] = S + 0.5f;
        aS[3] = 0.5f - S;
        aT[0] = 0.5f - T;
        aT[1] = 0.5f - T;
        aT[2] = T + 0.5f;
        aT[3] = T + 0.5f;
        for (i = 0; i < 4; i++) {
            aVtx[i + 4].Color.r = fn_8021F77C(aVtx[0].Color.r, aVtx[1].Color.r, aVtx[2].Color.r, aVtx[3].Color.r, aS[i], aT[i]);
            aVtx[i + 4].Color.g = fn_8021F77C(aVtx[0].Color.g, aVtx[1].Color.g, aVtx[2].Color.g, aVtx[3].Color.g, aS[i], aT[i]);
            aVtx[i + 4].Color.b = fn_8021F77C(aVtx[0].Color.b, aVtx[1].Color.b, aVtx[2].Color.b, aVtx[3].Color.b, aS[i], aT[i]);
            aVtx[i + 4].Color.a = fn_8021F77C(aVtx[0].Color.a, aVtx[1].Color.a, aVtx[2].Color.a, aVtx[3].Color.a, aS[i], aT[i]);
            aVtx[i + 4].St[0] = fn_8021F82C(aVtx[0].St[0], aVtx[1].St[0], aVtx[2].St[0], aVtx[3].St[0], aS[i], aT[i]);
            aVtx[i + 4].St[1] = fn_8021F82C(aVtx[0].St[1], aVtx[1].St[1], aVtx[2].St[1], aVtx[3].St[1], aS[i], aT[i]);
            aVtx[i + 4].Pos[0] = fn_8021F82C(aVtx[0].Pos[0], aVtx[1].Pos[0], aVtx[2].Pos[0], aVtx[3].Pos[0], aS[i], aT[i]);
            aVtx[i + 4].Pos[1] = fn_8021F82C(aVtx[0].Pos[1], aVtx[1].Pos[1], aVtx[2].Pos[1], aVtx[3].Pos[1], aS[i], aT[i]);
            aVtx[i + 4].Pos[2] = fn_8021F82C(aVtx[0].Pos[2], aVtx[1].Pos[2], aVtx[2].Pos[2], aVtx[3].Pos[2], aS[i], aT[i]);
        }
    }
    if (pNode->Flags & 8) {
        SendTexVertex(&aVtx[0]);
        SendTexVertex(&aVtx[4]);
        SendTexVertex(&aVtx[1]);
        SendTexVertex(&aVtx[5]);
        SendTexVertex(&aVtx[2]);
        SendTexVertex(&aVtx[6]);
        SendTexVertex(&aVtx[3]);
        SendTexVertex(&aVtx[7]);
        SendTexVertex(&aVtx[0]);
        SendTexVertex(&aVtx[4]);
    } else {
        SendTexVertex(&aVtx[0]);
        SendTexVertex(&aVtx[1]);
        SendTexVertex(&aVtx[2]);
        SendTexVertex(&aVtx[3]);
    }
}

void fn_80220310(UIGNode_t *pNode)
{
    UIGNodeVertex_t aVtx[8];
    Float32 aS[4];
    Float32 aT[4];
    UIGNodePalette_t *pPalette = NULL;
    Float32 S;
    Float32 T;
    Int32 i;
    UIGNodeQuad_t *pQuad;

    UIGRenderGetColorState();
    pQuad = &pNode->u.v.Quad;
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGNodePalette_t *)fn_80220B4C(pNode->unk_0A, pNode->unk_08);
    }
    for (i = 0; i < 4; i++) {
        aVtx[i].Color = pQuad->Colors[i];
        if (pPalette != NULL) {
            if (aVtx[i].Color.r > pPalette->Count) {
                aVtx[i].Color.r = pPalette->Count - 1;
            }
            aVtx[i].Color = pPalette->Colors[aVtx[i].Color.r];
        }
        aVtx[i].Color.r = (Float32)aVtx[i].Color.r;
        aVtx[i].Color.g = (Float32)aVtx[i].Color.g;
        aVtx[i].Color.b = (Float32)aVtx[i].Color.b;
        aVtx[i].Color.a = (Float32)aVtx[i].Color.a;
        aVtx[i].Pos[0] = pQuad->Pos[i][0];
        aVtx[i].Pos[1] = pQuad->Pos[i][1];
        aVtx[i].Pos[2] = pQuad->Pos[i][2];
    }
    if (pNode->Flags & 8) {
        S = pNode->u.v.Scale[0] * (1.0f / 131070.0f);
        T = pNode->u.v.Scale[1] * (1.0f / 131070.0f);
        aS[0] = 0.5f - S;
        aS[1] = S + 0.5f;
        aS[2] = S + 0.5f;
        aS[3] = 0.5f - S;
        aT[0] = 0.5f - T;
        aT[1] = 0.5f - T;
        aT[2] = T + 0.5f;
        aT[3] = T + 0.5f;
        for (i = 0; i < 4; i++) {
            aVtx[i + 4].Color.r = fn_8021F77C(aVtx[0].Color.r, aVtx[1].Color.r, aVtx[2].Color.r, aVtx[3].Color.r, aS[i], aT[i]);
            aVtx[i + 4].Color.g = fn_8021F77C(aVtx[0].Color.g, aVtx[1].Color.g, aVtx[2].Color.g, aVtx[3].Color.g, aS[i], aT[i]);
            aVtx[i + 4].Color.b = fn_8021F77C(aVtx[0].Color.b, aVtx[1].Color.b, aVtx[2].Color.b, aVtx[3].Color.b, aS[i], aT[i]);
            aVtx[i + 4].Color.a = fn_8021F77C(aVtx[0].Color.a, aVtx[1].Color.a, aVtx[2].Color.a, aVtx[3].Color.a, aS[i], aT[i]);
            aVtx[i + 4].Pos[0] = fn_8021F82C(aVtx[0].Pos[0], aVtx[1].Pos[0], aVtx[2].Pos[0], aVtx[3].Pos[0], aS[i], aT[i]);
            aVtx[i + 4].Pos[1] = fn_8021F82C(aVtx[0].Pos[1], aVtx[1].Pos[1], aVtx[2].Pos[1], aVtx[3].Pos[1], aS[i], aT[i]);
            aVtx[i + 4].Pos[2] = fn_8021F82C(aVtx[0].Pos[2], aVtx[1].Pos[2], aVtx[2].Pos[2], aVtx[3].Pos[2], aS[i], aT[i]);
        }
    }
    if (pNode->Flags & 8) {
        SendColorVertex(&aVtx[0]);
        SendColorVertex(&aVtx[4]);
        SendColorVertex(&aVtx[1]);
        SendColorVertex(&aVtx[5]);
        SendColorVertex(&aVtx[2]);
        SendColorVertex(&aVtx[6]);
        SendColorVertex(&aVtx[3]);
        SendColorVertex(&aVtx[7]);
        SendColorVertex(&aVtx[0]);
        SendColorVertex(&aVtx[4]);
    } else {
        SendColorVertex(&aVtx[0]);
        SendColorVertex(&aVtx[1]);
        SendColorVertex(&aVtx[2]);
        SendColorVertex(&aVtx[3]);
    }
}

void fn_80220988(void)
{
    UIGMaterialColorState_t *pColor;
    ColorWord_80220988 Mat;
    ColorWord_80220988 Light;

    pColor = UIGRenderGetColorState();
    Mat.Color = pColor->mMaterialColor;
    Light.Color = pColor->mLightColor;
    if (Mat.Value != lbl_803ECFF0 || Light.Value != lbl_803ECFF4) {
        GXSetChanMatColor(GX_COLOR0A0, Mat.Color);
        GXInitLightColor(&lbl_803E9880, Light.Color);
        GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
        lbl_803ECFF0 = Mat.Value;
        lbl_803ECFF4 = Light.Value;
    }
}

void fn_80220A08(void)
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    lbl_803ECFF4 = lbl_803ECFF0 = 0x12345678;
}

void fn_80220AD0(UIGNode_t *pNode, Int32 a, Int32 Item)
{
    Int32 First = 0;
    Int32 Second = 0;
    Int32 i;

    if (a != 0) {
        First = 1;
        Second = 1;
    } else {
        for (i = 0; i < 4; i++) {
            if (pNode->u.v.Quad.Coords[i][0] > 256) {
                First = 1;
            }
            if (pNode->u.v.Quad.Coords[i][1] > 256) {
                Second = 1;
            }
        }
    }
    LLUIGSetClamp(First, Second, (Texture_t *)Item);
}
