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

/* Partial source for the engine range 0x80223FF4-0x80225CBC (neutral file
   name): curve strip geometry and the second node update and render set-up
   path (small-data colours 0x803EBF70/0x803EBF74). Functions without a
   body here keep their original bytes. */

typedef void Callback_8022482C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);

extern GXColor lbl_803EBF70;
extern GXColor lbl_803EBF74;
extern GXLightObj lbl_803E9880;
extern Float32 lbl_802F9FE0[4][4];
extern Float32 lbl_803A0400[][2];
extern GXColor lbl_803A1400[];

void TMRenderReset(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);

void fn_80225958(Node_80223874 *pNode, Int32 Item);
void fn_8022482C(Node_80223874 *pNode, Float32 (*pCoords)[2], GXColor *pColors, Int32 *pSize,
                 Int32 Count, Callback_8022482C *pVertex, Callback_8022482C *pEnd);
void fn_80225AAC(Node_80223874 *pNode, Int32 a, Int32 Item);
void fn_80225B50(Uint32 Flags);
void fn_80225CBC(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
void fn_80225D8C(Node_80223874 *pNode, Int32 Index, Float32 *pCoord);
void fn_80225928(Node_80223874 *pNode);
void fn_802258F8(Node_80223874 *pNode);
void fn_80225AE4(void);

void fn_8022479C(Node_80223874 *pNode)
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
    fn_80225928(pNode);
}

void fn_8022480C(Node_80223874 *pNode)
{
    fn_802258F8(pNode);
}

void fn_802254F8(Node_80223874 *pNode)
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
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_80225958(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x100) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_80225654(Node_80223874 *pNode, Uint32 Action, Int32 a, void *pData)
{
    Int16 First;
    Int16 Second;
    Int16 Value;

    switch (Action) {
    case -1:
        fn_8022479C(pNode);
        break;
    case -2:
        fn_802254F8(pNode);
        break;
    case -3:
        fn_8022480C(pNode);
        break;
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

void fn_802258F8(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListUnrelocate(&pNode->u.List);
    }
}

void fn_80225928(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        UIGDispListRelocate(&pNode->u.List);
    }
}

void fn_80225958(Node_80223874 *pNode, Int32 Item)
{
    Int32 bTex = 0;
    Int32 Count;
    Int32 Size;

    fn_80225B50(pNode->Flags);
    if (pNode->Flags & 4) {
        if (Item == 0) {
            return;
        }
        lbl_802F9FE0[0][0] = ((UIGTexNode_t *)Item)->unk_30;
        lbl_802F9FE0[1][1] = ((UIGTexNode_t *)Item)->unk_34;
        GXLoadTexMtxImm(lbl_802F9FE0, GX_TEXMTX0, GX_MTX2x4);
        fn_80225AAC(pNode, 0, Item);
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
        fn_8022482C(pNode, lbl_803A0400, lbl_803A1400, &Size, Count, fn_80225CBC, fn_80225D8C);
    }
    GXSetCullMode(GX_CULL_NONE);
    if (bTex) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

void fn_80225AAC(Node_80223874 *pNode, Int32 a, Int32 Item)
{
    Int32 First = 0;
    Int32 Second = 0;

    if (a != 0) {
        First = 1;
        Second = 1;
    }
    LLUIGSetClamp(First, Second, (Texture_t *)Item);
}

void fn_80225AE4(void)
{
    Color_80223C4C *pColor = fn_80220D34();
    GXColor MatColor = pColor->unk_20;
    GXColor LightColor = pColor->unk_24;

    GXSetChanMatColor(GX_COLOR0A0, MatColor);
    GXInitLightColor(&lbl_803E9880, LightColor);
    GXLoadLightObjImm(&lbl_803E9880, GX_LIGHT7);
    lbl_803EBF70 = MatColor;
    lbl_803EBF74 = LightColor;
}

void fn_80225B50(Uint32 Flags)
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
    fn_80225AE4();
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
