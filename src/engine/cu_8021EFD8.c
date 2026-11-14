#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include "UIStudio/UIStudio.h"
#include "engine/Resource.h"
#include "engine/llmatrix.h"
#include "engine/cu_8021A438.h"
#include "engine/viewport.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

/* Partial source for the engine range 0x8021EFD8-0x80221314 (neutral file
   name). Functions without a body here keep their original bytes. */

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
extern Color_80223C4C *lbl_803EBF50;
extern Int32 lbl_803EBF54;
extern Int32 lbl_803EBF58;
extern Uint8 lbl_803EBF5C;
extern Float32 lbl_802F9FA0[4][4];
extern Uint32 lbl_803ECFF0;
extern Uint32 lbl_803ECFF4;
extern Int32 lbl_803ECFF8;
extern Int32 lbl_803ECFFC;
extern Int32 lbl_803ED000;
extern Object_8021E688 *lbl_803ED004;
extern Int32 lbl_803ED008;
extern Int32 lbl_803ED00C;

void fn_8021F8DC(Node_80223874 *pNode);
void fn_8021F954(Node_80223874 *pNode);
void fn_8021F984(Node_80223874 *pNode, Int32 Item);
void fn_8021FB30(Node_80223874 *pNode);
void fn_80220310(Node_80223874 *pNode);
void fn_80220988(void);
void fn_80220A08(void);
void fn_80220AD0(Node_80223874 *pNode, Int32 a, Int32 Item);
Int32 fn_80220BFC(Int32 a, Int32 b);
void fn_80220D3C(void);
void GXLoadLightObjImm(GXLightObj *pLight, GXLightID Light);
void TMRenderReset(void);
void fn_80221198(void *p);
void fn_80221294(void *p);

void fn_8021F550(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E2B4(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    fn_8021F8DC(pNode);
}

void fn_8021F5C0(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 2) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
        pObject = fn_8021EA44(1);
        if (fn_8021E924(pObject, pNode->unk_06) & 2) {
            fn_80226320(pObject, pNode->unk_06, pNode->unk_04);
        }
        if (pNode->unk_0C != -1 && pNode->unk_0E != -1 &&
            fn_8021EE10(pObject, pNode->unk_06, pNode->unk_04) == 0) {
            fn_802213F8(pObject, &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        Item = fn_8021EA54(pObject, pNode->unk_06, pNode->unk_04);
    }
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_8021F984(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_8021F71C(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E72C(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    fn_8021F954(pNode);
}

void fn_8021F8DC(Node_80223874 *pNode)
{
    Int32 i;

    if (pNode->Flags & 0x8000) {
        fn_802260B0(&pNode->u.List);
    } else if ((pNode->Flags & 3) == 2) {
        pNode->Flags |= 1;
        for (i = 0; i < 4; i++) {
            pNode->u.v.Colors[i].r = 255;
            pNode->u.v.Colors[i].g = 255;
            pNode->u.v.Colors[i].b = 255;
        }
    }
}

void fn_8021F954(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260C0(&pNode->u.List);
    }
}

void fn_8021F984(Node_80223874 *pNode, Int32 Item)
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
        fn_802218D4(Mode == 2 ? 0 : 1);
        fn_80221924(bTexture);
        lbl_803ECFF8 = Mode;
    }
    GXSetCullMode((Flags & 4) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])fn_801D0444(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (pNode->Flags & 2) {
        lbl_802F9FA0[0][0] = ((Node_802215F0 *)Item)->unk_30;
        lbl_802F9FA0[1][1] = ((Node_802215F0 *)Item)->unk_34;
        GXLoadTexMtxImm(lbl_802F9FA0, GX_TEXMTX0, GX_MTX2x4);
        if (!(pNode->Flags & 0x8000)) {
            fn_80220AD0(pNode, 0, Item);
        }
        bTex = fn_8022179C(Item);
    }
    if (pNode->Flags & 0x8000) {
        fn_802260D0(&pNode->u.List);
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

void fn_80220988(void)
{
    Color_80223C4C *pColor;
    ColorWord_80220988 Mat;
    ColorWord_80220988 Light;

    pColor = fn_80220D34();
    Mat.Color = pColor->unk_20;
    Light.Color = pColor->unk_24;
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

void fn_80220AD0(Node_80223874 *pNode, Int32 a, Int32 Item)
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
    fn_802219F0(First, Second);
}

Int32 fn_80220B4C(Int32 a, Int32 b)
{
    Object_8021E688 *pObject;

    Int32 Result;

    pObject = fn_8021EA44(1);
    Result = 0;
    if (pObject != NULL) {
        if (lbl_803ED008 == 0 || lbl_803ED004 != pObject || lbl_803ECFFC != a || lbl_803ED000 != b) {
            lbl_803ED008 = fn_8021E2B4(pObject, a, b);
            lbl_803ED004 = pObject;
            lbl_803ECFFC = a;
            lbl_803ED000 = b;
        }
        Result = lbl_803ED008;
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
    Object_8021E688 *pObject;

    pObject = fn_8021EA44(1);
    if (pObject == NULL) {
        return 0;
    }
    return fn_8021E2B4(pObject, a, b);
}

void fn_80220C4C(Int32 a, Int32 b, Int32 c)
{
    Int32 p;

    lbl_803EBF48 = fn_80221570((struct Node_802215F0 *)c);
    p = fn_80220BFC(a, b);
    if (p != 0) {
        fn_80221590((struct Node_802215F0 *)c, (unsigned short *)p);
    }
}

void fn_80220CA4(Int32 a, Int32 b, Int32 c)
{
    if (lbl_803EBF48 != NULL) {
        fn_80221590((struct Node_802215F0 *)c, lbl_803EBF48);
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

void fn_80221118(void)
{
    lbl_803ED00C--;
    lbl_803EBF50--;
    fn_80220CFC(0);
}

void fn_80221198(void *p)
{
    Transform_80221198 *pXf = p;
    float aNeg[3];

    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D0C58(pXf->mPosition);
    fn_801D0C58(pXf->mPivot);
    if (fn_80221154(pXf->mRotation) != 0) {
        fn_801D08FC((int)(pXf->mRotation[0] * 46603.38f));
        fn_801D09EC((int)(pXf->mRotation[1] * 46603.38f));
        fn_801D0ADC((int)(pXf->mRotation[2] * 46603.38f));
    }
    fn_801D0D94(pXf->mScale[0], pXf->mScale[1], pXf->mScale[2]);
    aNeg[0] = -pXf->mPivot[0];
    aNeg[1] = -pXf->mPivot[1];
    aNeg[2] = -pXf->mPivot[2];
    fn_801D0C58(aNeg);
    fn_80220DA4(pXf->mMultiply, pXf->mScaleColor);
    fn_80220CFC(0);
}

void fn_80221294(void *p)
{
    fn_801D0470(VptGetMatrixStack());
    fn_801D0544();
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
