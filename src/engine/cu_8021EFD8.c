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

/* UI graphics node drawing: loads, updates and draws the image and colour
   nodes of UI Studio screens (textured or flat-shaded quads and strips sent to
   GX in immediate mode), with the material/light colour stack, the palette
   swap for library items and the node transform push/pop callbacks.
   Partial source: functions without a body here keep their original bytes. */

/* A colour that is also compared as one word. */
typedef union ColorWord_80220988 {
    GXColor Color;
    Uint32 Value;
} ColorWord_80220988;

/* Transform record read by fn_80221198; +0x30 is not accessed and the size is not established. */
typedef struct Transform_80221198 {
    Float32 mPosition[3];   /* 0x00 */
    Float32 mPivot[3];      /* 0x0C */
    Float32 mRotation[3];   /* 0x18 */
    Float32 mScale[3];      /* 0x24 */
    Uint8 unk_30[4];        /* 0x30 */
    Float32 mMultiply[4];   /* 0x34 */
    Float32 mScaleColor[4]; /* 0x44 */
} Transform_80221198;

extern GXLightObj lbl_803E9880;
extern unsigned short *lbl_803EBF48;
extern UIGMaterialColorState_t *lbl_803EBF50;
extern Int32 lbl_803EBF54;
extern Int32 lbl_803EBF58;
extern Uint8 lbl_803EBF5C;
extern Float32 lbl_802F9FA0[4][4];
extern Uint32 lbl_803ECFF0;
extern Uint32 lbl_803ECFF4;
extern Int32 lbl_803ECFF8;
extern Int32 lbl_803ECFFC;
extern Int32 lbl_803ED000;
extern UIGLibrary_t *lbl_803ED004;
extern Int32 lbl_803ED008;
extern Int32 lbl_803ED00C;
extern UIGMaterialColorState_t lbl_8039F878[];

void fn_8021F8DC(UIGNode_t *pNode);
void fn_8021F954(UIGNode_t *pNode);
void fn_8021F984(UIGNode_t *pNode, Int32 Item);
void fn_8021FB30(UIGNode_t *pNode);
void fn_80220310(UIGNode_t *pNode);
void fn_80220988(void);
void fn_80220A08(void);
void fn_80220AD0(UIGNode_t *pNode, Int32 a, Int32 Item);
Int32 fn_80220BFC(Int32 a, Int32 b);
void fn_80220D3C(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);
void TMRenderReset(void);
void fn_80221198(void *p);
void fn_80221294(void *p);
void fn_8021F550(UIGNode_t *pNode);
void fn_8021F5C0(UIGNode_t *pNode);
void fn_8021F71C(UIGNode_t *pNode);
Uint8 fn_8021F77C(Uint32 a, Uint32 b, Uint32 c, Uint32 d, Float32 s, Float32 t);
Int16 fn_8021F82C(Int16 a, Int16 b, Int16 c, Int16 d, Float32 s, Float32 t);
Int32 fn_80220B4C(Int32 a, Int32 b);

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
    Float32 Value;

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
        i = ((Int32 *)pData)[0];
        pNode->u.v.Pos[i][0] = ((Float32 *)pData)[1] * 16.0f;
        pNode->u.v.Pos[i][1] = ((Float32 *)pData)[2] * 16.0f;
        pNode->u.v.Pos[i][2] = ((Float32 *)pData)[3] * 16.0f;
        break;
    case 1:
        i = ((Int32 *)pData)[0];
        pNode->u.v.Coords[i][0] = ((Float32 *)pData)[1] * 256.0f;
        pNode->u.v.Coords[i][1] = ((Float32 *)pData)[2] * 256.0f;
        break;
    case 2:
        if (((Int32 *)pData)[0] == -1) {
            for (i = 0; i < 4; i++) {
                pNode->u.v.Colors[i].r = ((Int32 *)pData)[1];
                pNode->u.v.Colors[i].g = ((Int32 *)pData)[2];
                pNode->u.v.Colors[i].b = ((Int32 *)pData)[3];
            }
        } else {
            i = ((Int32 *)pData)[0];
            pNode->u.v.Colors[i].r = ((Int32 *)pData)[1];
            pNode->u.v.Colors[i].g = ((Int32 *)pData)[2];
            pNode->u.v.Colors[i].b = ((Int32 *)pData)[3];
        }
        break;
    case 3:
        if (((Int32 *)pData)[0] == -1) {
            for (i = 0; i < 4; i++) {
                pNode->u.v.Colors[i].a = ((Int32 *)pData)[1];
            }
        } else {
            pNode->u.v.Colors[((Int32 *)pData)[0]].a = ((Int32 *)pData)[1];
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
            pNode->unk_0E = -1;
            pNode->unk_0C = -1;
        }
        break;
    case 6:
        Value = ((Float32 *)pData)[0];
        if (Value > 1.0f) {
            Value = 1.0f;
        }
        if (Value < 0.0f) {
            Value = 0.0f;
        }
        pNode->u.v.Scale[0] = Value * 65535.0f;
        Value = ((Float32 *)pData)[1];
        if (Value > 1.0f) {
            Value = 1.0f;
        }
        if (Value < 0.0f) {
            Value = 0.0f;
        }
        pNode->u.v.Scale[1] = Value * 65535.0f;
        break;
    case 7:
        if ((pNode->Flags & 0x10) || (((Int16 *)pData)[0] != -1 && ((Int16 *)pData)[1] != -1)) {
            pNode->unk_08 = ((Int16 *)pData)[1];
            pNode->unk_0A = ((Int16 *)pData)[0];
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
        if (((Int32 *)pData)[0] == -1) {
            for (i = 0; i < 4; i++) {
                pNode->u.v.Colors[i].r = ((Int32 *)pData)[1];
            }
        } else {
            pNode->u.v.Colors[((Int32 *)pData)[0]].r = ((Int32 *)pData)[1];
        }
        break;
    case 11:
        pObject = UIGLibraryGetGlobal(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            *(Int32 *)pOut = UIGLibraryIsItemLoading(pObject, pNode->unk_06, pNode->unk_04) == 0;
        } else {
            *(Int32 *)pOut = 0;
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
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_8021F984(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
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
            pNode->u.v.Colors[i].r = 255;
            pNode->u.v.Colors[i].g = 255;
            pNode->u.v.Colors[i].b = 255;
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
    Float32 Value;
    Float32 S;
    Float32 T;
    Int32 i;

    fn_80220D34();
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGNodePalette_t *)fn_80220B4C(pNode->unk_0A, pNode->unk_08);
    }
    for (i = 0; i < 4; i++) {
        aVtx[i].Color = pNode->u.v.Colors[i];
        if (pPalette != NULL && !(pNode->Flags & 0x10)) {
            if (aVtx[i].Color.r > pPalette->Count) {
                aVtx[i].Color.r = pPalette->Count - 1;
            }
            aVtx[i].Color = pPalette->Colors[aVtx[i].Color.r];
        }
        Value = aVtx[i].Color.r;
        aVtx[i].Color.r = Value;
        Value = aVtx[i].Color.g;
        aVtx[i].Color.g = Value;
        Value = aVtx[i].Color.b;
        aVtx[i].Color.b = Value;
        Value = aVtx[i].Color.a;
        aVtx[i].Color.a = Value;
        aVtx[i].St[0] = pNode->u.v.Coords[i][0];
        aVtx[i].St[1] = pNode->u.v.Coords[i][1];
        aVtx[i].Pos[0] = pNode->u.v.Pos[i][0];
        aVtx[i].Pos[1] = pNode->u.v.Pos[i][1];
        aVtx[i].Pos[2] = pNode->u.v.Pos[i][2];
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
    Float32 Value;
    Float32 S;
    Float32 T;
    Int32 i;

    fn_80220D34();
    if (pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        pPalette = (UIGNodePalette_t *)fn_80220B4C(pNode->unk_0A, pNode->unk_08);
    }
    for (i = 0; i < 4; i++) {
        aVtx[i].Color = pNode->u.v.Colors[i];
        if (pPalette != NULL) {
            if (aVtx[i].Color.r > pPalette->Count) {
                aVtx[i].Color.r = pPalette->Count - 1;
            }
            aVtx[i].Color = pPalette->Colors[aVtx[i].Color.r];
        }
        Value = aVtx[i].Color.r;
        aVtx[i].Color.r = Value;
        Value = aVtx[i].Color.g;
        aVtx[i].Color.g = Value;
        Value = aVtx[i].Color.b;
        aVtx[i].Color.b = Value;
        Value = aVtx[i].Color.a;
        aVtx[i].Color.a = Value;
        aVtx[i].Pos[0] = pNode->u.v.Pos[i][0];
        aVtx[i].Pos[1] = pNode->u.v.Pos[i][1];
        aVtx[i].Pos[2] = pNode->u.v.Pos[i][2];
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

    pColor = fn_80220D34();
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
            if (pNode->u.v.Coords[i][0] > 256) {
                First = 1;
            }
            if (pNode->u.v.Coords[i][1] > 256) {
                Second = 1;
            }
        }
    }
    LLUIGSetClamp(First, Second, (Texture_t *)Item);
}

Int32 fn_80220B4C(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    Int32 Result;

    pObject = UIGLibraryGetGlobal(1);
    Result = 0;
    if (pObject != NULL) {
        // FAKEMATCH: cache word read into Result first and stored last (same logic as reading lbl_803ED008 after the if)
        Result = lbl_803ED008;
        if (Result == 0 || lbl_803ED004 != pObject || lbl_803ECFFC != a || lbl_803ED000 != b) {
            Result = UIGLibraryLoadItem(pObject, a, b);
            lbl_803ED004 = pObject;
            lbl_803ECFFC = a;
            lbl_803ED000 = b;
            lbl_803ED008 = Result;
        }
    }
    return Result;
}

void fn_80220BE0(void)
{
    lbl_803ED008 = 0;
    lbl_803ECFFC = -1;
    lbl_803ED004 = NULL;
    lbl_803ED000 = -1;
}

Int32 fn_80220BFC(Int32 a, Int32 b)
{
    UIGLibrary_t *pObject;

    pObject = UIGLibraryGetGlobal(1);
    if (pObject == NULL) {
        return 0;
    }
    return UIGLibraryLoadItem(pObject, a, b);
}

void fn_80220C4C(Int32 a, Int32 b, Int32 c)
{
    Int32 p;

    lbl_803EBF48 = UIGTexNodeGetPalette((struct UIGTexNode_t *)c);
    p = fn_80220BFC(a, b);
    if (p != 0) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, (unsigned short *)p);
    }
}

void fn_80220CA4(Int32 a, Int32 b, Int32 c)
{
    if (lbl_803EBF48 != NULL) {
        UIGTexNodeSetPalette((struct UIGTexNode_t *)c, lbl_803EBF48);
    }
    lbl_803EBF48 = NULL;
}

void fn_80220CDC(Int32 a)
{
    lbl_803EBF54 = a;
}

Int32 fn_80220CE4(void)
{
    if (lbl_803EBF5C == 0) {
        return 0;
    }
    return lbl_803EBF54;
}

void fn_80220CFC(Int32 a)
{
    lbl_803EBF58 = a;
}

void fn_80220D04(void)
{
    fn_80220D3C();
    fn_80220CDC(0);
    fn_80220CFC(0);
}

void *fn_80220D34(void)
{
    return lbl_803EBF50;
}

void fn_80220D3C(void)
{
    lbl_803ED00C = 0;
    lbl_8039F878[0].unk_00[0] = 1.0f;
    lbl_8039F878[0].unk_00[1] = 1.0f;
    lbl_8039F878[0].unk_00[2] = 1.0f;
    lbl_8039F878[0].unk_00[3] = 1.0f;
    lbl_8039F878[0].unk_00[4] = 0.0f;
    lbl_8039F878[0].unk_00[5] = 0.0f;
    lbl_8039F878[0].unk_00[6] = 0.0f;
    lbl_8039F878[0].unk_00[7] = 0.0f;
    lbl_803EBF50 = lbl_8039F878;
    fn_80220CFC(0);
}

static inline unsigned char fn_80220DA4_ToByte(Float32 v)
{
    Float32 f;

    if (!(v < 0.0f)) {
        f = v;
        if (!(f <= 255.0f)) {
            f = 255.0f;
        }
        return (int)f;
    }
    return 0;
}

void fn_80220DA4(Float32 *pMul, Float32 *pScale)
{
    UIGMaterialColorState_t *pCur;
    UIGMaterialColorState_t *pNext;

    pCur = &lbl_8039F878[lbl_803ED00C];
    pNext = pCur + 1;
    pNext->unk_00[0] = pCur->unk_00[0] * pMul[0];
    pNext->unk_00[1] = pCur->unk_00[1] * pMul[1];
    pNext->unk_00[2] = pCur->unk_00[2] * pMul[2];
    pNext->unk_00[3] = pCur->unk_00[3] * pMul[3];
    pNext->unk_00[4] = pCur->unk_00[4] * pScale[0];
    pNext->unk_00[5] = pCur->unk_00[5] * pScale[1];
    pNext->unk_00[6] = pCur->unk_00[6] * pScale[2];
    pNext->unk_00[7] = pCur->unk_00[7] * pScale[3];
    if (!(pNext->unk_00[3] < 1.0f)) {
        pNext->unk_00[3] = 1.0f;
    }
    if (!(pNext->unk_00[3] > 0.0f)) {
        pNext->unk_00[3] = 0.0f;
    }
    pNext->mMaterialColor.r = fn_80220DA4_ToByte(pNext->unk_00[0] * 255.0f);
    pNext->mMaterialColor.g = fn_80220DA4_ToByte(pNext->unk_00[1] * 255.0f);
    pNext->mMaterialColor.b = fn_80220DA4_ToByte(pNext->unk_00[2] * 255.0f);
    pNext->mMaterialColor.a = fn_80220DA4_ToByte(pNext->unk_00[3] * 255.0f);
    pNext->mLightColor.r = fn_80220DA4_ToByte(pNext->unk_00[4] * 255.0f);
    pNext->mLightColor.g = fn_80220DA4_ToByte(pNext->unk_00[5] * 255.0f);
    pNext->mLightColor.b = fn_80220DA4_ToByte(pNext->unk_00[6] * 255.0f);
    pNext->mLightColor.a = fn_80220DA4_ToByte(pNext->unk_00[7] * 255.0f);
    lbl_803ED00C++;
    lbl_803EBF50++;
    fn_80220CFC(0);
}

void fn_80221118(void)
{
    lbl_803ED00C--;
    lbl_803EBF50--;
    fn_80220CFC(0);
}

long long fn_80221154(Float32 *pV)
{
    long long result = 0;

    if (pV[0] != 0.0f || pV[1] != 0.0f || pV[2] != 0.0f) {
        result = 1;
    }
    return result;
}

void fn_80221198(void *p)
{
    Transform_80221198 *pXf = p;
    float aNeg[3];

    MatSetStack(VptGetMatrixStack());
    MatPush();
    MatTranslate(pXf->mPosition);
    MatTranslate(pXf->mPivot);
    if (fn_80221154(pXf->mRotation) != 0) {
        MatRotX((int)(pXf->mRotation[0] * 46603.38f));
        MatRotY((int)(pXf->mRotation[1] * 46603.38f));
        MatRotZ((int)(pXf->mRotation[2] * 46603.38f));
    }
    MatScaleCol(pXf->mScale[0], pXf->mScale[1], pXf->mScale[2]);
    aNeg[0] = -pXf->mPivot[0];
    aNeg[1] = -pXf->mPivot[1];
    aNeg[2] = -pXf->mPivot[2];
    MatTranslate(aNeg);
    fn_80220DA4(pXf->mMultiply, pXf->mScaleColor);
    fn_80220CFC(0);
}

void fn_80221294(void *p)
{
    MatSetStack(VptGetMatrixStack());
    MatPop();
    fn_80221118();
    fn_80220CFC(0);
}

void fn_802212C8(Uint32 Type, void *p)
{
    switch (Type) {
    case 0:
        break;
    case 1:
        fn_80221198(p);
        break;
    case 2:
        fn_80221294(p);
        break;
    }
}
