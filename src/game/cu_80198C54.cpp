#include <dolphin/gx/GXPixel.h>
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/CAPPortrait.h"
#include "game/cu_8015D3EC.h"
#include "engine/viewport.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTev.h>

typedef float Matrix_80198C54[4][4];

struct Triple_802EDF8C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
};

/* Argument of fn_802338D4: a halfword-triple table at +0x30 and an output buffer at +0x34. */
struct Object_802338D4 {
    char mUnknown0[48];
    SkeletonJointTriple_t *mpUnknown48;
    Matrix_80198C54 *mpUnknown52;
};

extern "C" {
void fn_801CE95C(void);
void fn_801D03D0(Matrix_80198C54 m);
void fn_801D0470(void);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0664(Matrix_80198C54 m);
void fn_801D06D4(Matrix_80198C54 m);
void fn_801D0BCC(int a, int b, int c);
void C_MTXOrtho(Matrix_80198C54 m, float t, float b, float l, float r, float n, float f);
void fn_801D0C58(Triple_802EDF8C *p);
void fn_801D0CFC(float a);
void fn_801D0F80(Matrix_80198C54 m);
void fn_801D1258(int a, Matrix_80198C54 m);
void fn_801D12BC(int a);
void fn_801D12EC(int a);
void fn_801D131C(int a);
int PortraitGetSkeletonParam(int index);
void TMMaterialListSetMatDefs(ModelPartBinding_t *pObject, void *p);
void TMRenderReset(void);
void TMRenderSetBlendMode(int a);
void TMRenderSetZRange(float a, float b);
void TMTexLibRegistryReset(void);
void TMTexLibRegister(const char *pName, void *p);
void fn_802337D4(void *a, void *b, SkeletonJointTriple_t *pTriples, unsigned int c);
void fn_802338D4(Object_802338D4 *pObject, Skeleton_80041930 *pData, Matrix_80198C54 *pOut);
void fn_80233BB8(SkeletonPose_t *pObject, int a, int b);
void fn_80233BD8(SkeletonPose_t *pObject);
void fn_80233BDC(SkeletonPose_t *pObject, Skeleton_80041930 *pData);
void fn_80233CBC(void *pObject, int a, int b);
void fn_8023465C(ModelPartBinding_t *pObject, Object_8023417C *pModel, ModelTexSlot_t *pDesc);
void fn_8023488C(ModelPartBinding_t *pObject, int a);
void fn_802348AC(ModelPartBinding_t *pObject);
void fn_80234A30(ModelDrawObject_t *pObject, int a);
void fn_80234A90(ModelDrawObject_t *pObject);
void fn_80234A94(ModelDrawObject_t *pObject, void *p);
void fn_80234AD8(ModelDrawObject_t *pObject, void *p);
void fn_80234BF4(int a, ModelDrawObject_t *pObject, int b);
void fn_80234CA4(ModelDrawObject_t *pObject, SkeletonPose_t *p);
void fn_80234CAC(ModelDrawObject_t *pObject, void *p);
void fn_80234CF0(ModelDrawObject_t *pObject, int a, ModelPartBinding_t *p);
void fn_80234DC0(ModelDrawObject_t *pObject, int a);
int fn_80236B98(int a, float x, float y, float z);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
extern "C" void GXInitTexObj(GXTexObj *pObj, void *p, int a, int b, int c, int d, int e, int f);
extern "C" void GXLoadTexObj(GXTexObj *pObj, int a);
void fn_802523A4(Matrix_80198C54 m, int a);
void fn_802524D4(float *p);
void fn_8025251C(Matrix_80198C54 m, int a);
void fn_802525BC(int a);
void fn_802528B0(int a);
}

static Triple_802EDF8C lbl_802EDF8C = {0.0f, -0.7f, -1.6f};
static Triple_802EDF8C lbl_802EDF98 = {0.0f, 0.0f, 0.0f};
static float lbl_803EB770 = 1.0f;
static float lbl_803EB774 = 0.9999f;
static GXTexObj lbl_80365298;
static Matrix_80198C54 lbl_803652B8;
static Matrix_80198C54 lbl_803652F8;
static Matrix_80198C54 lbl_80365338;
static void *lbl_803ECBE4;

extern "C" {

void fn_80198C54(ModelDrawObject_t *pObject, unsigned int index)
{
    if (pObject->mpUnknown12 != 0) {
        switch (index) {
        case 0:
            fn_80233CBC(pObject->mUnknown20, 1, 0);
            fn_80233CBC(pObject->mUnknown20, 2, 0);
            fn_80233CBC(pObject->mUnknown20, 3, 0);
            break;
        case 1:
            fn_80233CBC(pObject->mUnknown20, 4, 0);
        case 2:
            fn_80233CBC(pObject->mUnknown20, 0, 0);
            break;
        }
    }
}

void fn_80198CFC(void **ppBuffer)
{
    *ppBuffer = fn_801D2B7C(0x80000, 0x100, 0);
    GXInitTexObj(&lbl_80365298, lbl_803ECBE4, 128, 128, 6, 0, 0, 0);
}

void fn_80198D60(void **ppBuffer)
{
    fn_801D2BD0(*ppBuffer);
    *ppBuffer = 0;
}

void fn_80198D98(PortraitJob_t *pObject)
{
    unsigned int i;
    unsigned int j;
    Skeleton_80041930 *pData0;
    Skeleton_80041930 *pData1;

    for (i = 0; i <= 1; i++) {
        Skeleton_80041930 *pData = PortraitGetSkeleton(i);
        int value = PortraitGetSkeletonParam(i);

        fn_80233BB8(&pObject->mUnknown588[i], value, 0);
        fn_80233BDC(&pObject->mUnknown588[i], pData);
    }

    pData0 = PortraitGetSkeleton(0);
    memset(pObject->mUnknown1340, 0, sizeof(pObject->mUnknown1340));
    pData1 = PortraitGetSkeleton(1);
    memset(pObject->mUnknown1520, 0, sizeof(pObject->mUnknown1520));
    for (j = 0; j < pData0->mUnknown6; j++) {
        pObject->mUnknown1340[j].mUnknown0 = pData0->mUnknown1040[j][0];
        pObject->mUnknown1340[j].mUnknown2 = pData0->mUnknown1040[j][1];
        pObject->mUnknown1340[j].mUnknown4 = pData0->mUnknown1040[j][2];
    }
    for (j = 0; j < 19; j++) {
        pObject->mUnknown1520[j].mUnknown0 = pData1->mUnknown1040[j][0];
        pObject->mUnknown1520[j].mUnknown2 = pData1->mUnknown1040[j][1];
        pObject->mUnknown1520[j].mUnknown4 = pData1->mUnknown1040[j][2];
    }
}

void fn_80198EE0(PortraitJob_t *pObject)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        fn_80233BD8(&pObject->mUnknown588[i]);
    }
}

void fn_80198F24(PortraitJob_t *pObject)
{
    Object_8023417C *pResult = fn_8015E2FC(0, 0, 0);
    ModelPartBinding_t *pUnknown612 = &pObject->mUnknown612;
    void *pElement = pObject->mUnknown384[0].mpUnknown24;
    ModelTexSlot_t *pDescs = pObject->mUnknown384;

    TMTexLibRegistryReset();
    TMTexLibRegister("capport", pElement);
    fn_8023488C(pUnknown612, 0x38);
    TMMaterialListSetMatDefs(pUnknown612, pResult->mpUnknown18);
    fn_8023465C(pUnknown612, pResult, pDescs);
    TMTexLibRegistryReset();
}

void fn_80198FAC(PortraitJob_t *pObject)
{
    fn_802348AC(&pObject->mUnknown612);
}

void fn_80198FD0(PortraitJob_t *pObject)
{
    unsigned int i;

    for (i = 0; i <= 2; i++) {
        fn_80234A30(&pObject->mUnknown620[i], 0x100);
    }
}

void fn_80199018(PortraitJob_t *pObject)
{
    unsigned int i;

    for (i = 0; i <= 2; i++) {
        fn_80234A90(&pObject->mUnknown620[i]);
    }
}

void fn_8019905C(PortraitJob_t *pObject)
{
    Object_802338D4 desc;
    Matrix_80198C54 matrices[40];
    SkeletonJointTriple_t triples[19];
    Skeleton_80041930 *pData0;
    Skeleton_80041930 *pData1;
    unsigned int i;
    ModelPartBinding_t *pUnknown612 = &pObject->mUnknown612;

    fn_801D0508();
    fn_801D0C58(&lbl_802EDF8C);
    fn_801D0BCC((int)(lbl_802EDF98.mUnknown8 * 46603.379f), (int)(lbl_802EDF98.mUnknown4 * 46603.379f),
                (int)(lbl_802EDF98.mUnknown0 * 46603.379f));
    fn_801D0CFC(lbl_803EB770);
    fn_801D0F80(lbl_803652B8);
    fn_8025251C(lbl_803652B8, 0);
    fn_802525BC(0);
    fn_801D0544();

    pData0 = PortraitGetSkeleton(0);
    pData1 = PortraitGetSkeleton(1);
    for (i = 0; i <= 2; i++) {
        ModelDrawObject_t *pElement = &pObject->mUnknown620[i];
        SkeletonPose_t *pUnknown588 = 0;

        switch (i) {
        case 0:
            pUnknown588 = &pObject->mUnknown588[0];
            fn_80234AD8(pElement, PortraitGetModel(pObject, 0));
            break;
        case 1:
            pUnknown588 = &pObject->mUnknown588[0];
            fn_80234AD8(pElement, PortraitGetModel(pObject, 0));
            break;
        case 2:
            pUnknown588 = &pObject->mUnknown588[1];
            fn_80234A94(pElement, PortraitGetModel(pObject, 1));
            break;
        }
        fn_80234CAC(pElement, 0);
        fn_80234CA4(pElement, pUnknown588);
        fn_80234CF0(pElement, 0, pUnknown612);
        fn_80234DC0(pElement, 15);
        fn_80198C54(pElement, i);
    }

    pObject->mUnknown1340[13].mUnknown0 = 0xF342;
    desc.mpUnknown48 = pObject->mUnknown1340;
    desc.mpUnknown52 = matrices;
    fn_801D0508();
    fn_802338D4(&desc, pData0, 0);
    fn_801D0544();

    fn_801D0508();
    fn_801D06D4(lbl_803652B8);
    if (pObject->mUnknown620[0].mpUnknown12 != 0) {
        fn_801D04C4();
        fn_802337D4(pObject->mUnknown620[0].mpUnknown12, pObject->mUnknown588,
                    pObject->mUnknown1340, 0xE0000000);
        fn_801D0544();
    }
    if (pObject->mUnknown620[2].mpUnknown12 != 0) {
        fn_801D04C4();
        fn_801D0664(matrices[13]);
        memcpy(triples, pData1->mUnknown1040, sizeof(triples));
        triples[0].mUnknown0 = pObject->mUnknown1340[13].mUnknown0;
        triples[0].mUnknown2 = pObject->mUnknown1340[13].mUnknown2;
        triples[0].mUnknown4 = pObject->mUnknown1340[13].mUnknown4;
        fn_802337D4(pObject->mUnknown620[2].mpUnknown12, pObject->mUnknown620[2].mpUnknown224,
                    triples, 0xE0000000);
        fn_801D0544();
    }
    fn_801D0544();
}

void fn_8019930C(PortraitJob_t *pObject)
{
    unsigned int *pOut;
    unsigned int y;
    unsigned int x;
    u32 color;
    u32 depth;

    GXDrawDone();
    pOut = (unsigned int *)lbl_803ECBE4;
    for (y = 160; y < 288; y++) {
        for (x = 256; x < 384; x++) {
            GXPeekARGB(x, y, &color);
            GXPeekZ(x, y, &depth);
            if (depth > 0xFF0000) {
                color = 0xFF00FF00;
            }
            *pOut++ = color;
        }
    }
    GXDrawDone();
}

void fn_801993B8(int textured, unsigned int color, GXTexObj *pTexture, float alpha)
{
    Matrix_80198C54 view;
    Matrix_80198C54 projection;
    GXColor fill = {0, 0, 0, 255};
    unsigned int r;
    unsigned int g;
    unsigned int b;

    if (textured) {
        fill.r = 255;
        fill.g = 255;
        fill.b = 255;
    } else {
        r = color & 0xFF;
        g = (color >> 8) & 0xFF;
        b = (color >> 16) & 0xFF;
        fill.r = r > 255 ? 255 : r;
        fill.g = g > 255 ? 255 : g;
        fill.b = b > 255 ? 255 : b;
    }
    fill.a = alpha * 255.0f;
    fn_8024FC48(1);
    fn_8024FB58(4, fill);
    fn_8024FC84(4, 0, 0, 0, 1, 0, 2);
    if (textured) {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
        GXSetCullMode(GX_CULL_NONE);
        fn_802528B0(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXLoadTexObj(pTexture, 0);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumTexGens(0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 4);
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
        GXSetCullMode(GX_CULL_NONE);
        fn_802528B0(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
    fn_802524D4(lbl_80365338[0]);
    C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    fn_802523A4(projection, 1);
    fn_801D03D0(view);
    fn_8025251C(view, 0);
    fn_802525BC(0);
}

void fn_8019969C(void)
{
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    fn_802523A4(lbl_80365338, 0);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    fn_802528B0(0);
}

void fn_801996F4(void)
{
    fn_801993B8(0, 0, 0, 1.0f);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(256.0f, 160.0f, -1.0f);
    GXPosition3f32(384.0f, 160.0f, -1.0f);
    GXPosition3f32(256.0f, 288.0f, -1.0f);
    GXPosition3f32(384.0f, 288.0f, -1.0f);
    fn_8019969C();
}

void fn_80199798(void)
{
}

void fn_8019979C(void)
{
    fn_802524D4(lbl_80365338[0]);
    VptPerspective(lbl_803652F8, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
    fn_802523A4(lbl_803652F8, 0);
    VptGetMatrixStack();
    fn_801D0470();
    fn_801D04C4();
    fn_801D1258(2, lbl_803652F8);
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D12EC(6);
    fn_801D0544();
}

void fn_80199838(PortraitJob_t *pObject)
{
    int mask;

    fn_8019979C();
    TMRenderReset();
    GXColor white = {255, 255, 255, 255};
    mask = fn_80236B98(2, 1.0f, 1.0f, 1.0f);
    fn_8024FB58(4, white);
    fn_8024FC48(1);
    fn_8024FC84(4, 1, 0, 0, mask, 2, 2);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_FRONT);
    TMRenderSetBlendMode(1);
    fn_80234BF4(0, &pObject->mUnknown620[0], 0);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    TMRenderSetBlendMode(2);
    TMRenderSetZRange(0.0f, lbl_803EB774);
    fn_80234BF4(0, &pObject->mUnknown620[1], 0);
    fn_80234BF4(0, &pObject->mUnknown620[2], 0);
    fn_8019969C();
}

void fn_80199968(PortraitJob_t *pObject)
{
    fn_80198CFC(&lbl_803ECBE4);
    fn_80198D98(pObject);
    fn_80198F24(pObject);
    fn_80198FD0(pObject);
}

void fn_801999B0(PortraitJob_t *pObject)
{
    fn_80199018(pObject);
    fn_80198FAC(pObject);
    fn_80198EE0(pObject);
    fn_80198D60(&lbl_803ECBE4);
}

void fn_801999F4(PortraitJob_t *pObject)
{
    fn_8019905C(pObject);
    fn_801996F4();
    fn_80199838(pObject);
    fn_8019930C(pObject);
    fn_80199798();
    fn_801CE95C();
}

void fn_80199A3C(unsigned char (*pColors)[4], int index, unsigned char *pR, unsigned char *pG,
                 unsigned char *pB, unsigned char *pA)
{
    unsigned char *pColor = pColors[index];

    *pR = pColor[3];
    *pG = pColor[2];
    *pB = pColor[1];
    *pA = pColor[0];
}

#if defined(DECOMP_COMPARE)
/* Converts up to 16 colours starting at start into RGB5A3 texels, padding the block of 16
   with zeros; returns the next output position. */
unsigned short *fn_80199A68(unsigned char (*pColors)[4], unsigned int count, unsigned int start,
                            unsigned short *pDst)
{
    unsigned int n = count - start;
    unsigned int i;
    unsigned short *pOut;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    unsigned int texel;

    if (n > 16) {
        n = 16;
    }
    pOut = pDst;
    for (i = 0; i < n; i++) {
        fn_80199A3C(pColors, start + i, &r, &g, &b, &a);
        if (a > 0xDF) {
            texel = ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3) | 0x8000;
        } else {
            texel = ((a >> 5) << 12) | ((r >> 4) << 8) | ((g >> 4) << 4) | (b >> 4);
        }
        *pOut = texel;
        pOut++;
    }
    for (; i < 16; i++) {
        *pOut++ = 0;
    }
    return pOut;
}

void fn_80199B68(unsigned char (*pColors)[4], unsigned short *pOut, unsigned int count)
{
    unsigned int blocks = (count + 15) >> 4;
    unsigned int i;

    for (i = 0; i < blocks; i++) {
        pOut = fn_80199A68(pColors, count, i * 16, pOut);
    }
}

void fn_80199BD4(PortraitJob_t *pObject)
{
    void **ppImage = &lbl_803ECBE4;
    unsigned char (*pColors)[4];
    int count;

    pObject->mpUnknown1636->AddImage((unsigned int *)*ppImage, 128, 128);
    pColors = (unsigned char (*)[4])fn_801D2B7C(0x400, 0, 0);
    memset(pColors, 0, 0x400);
    pObject->mpUnknown1636->BuildPalette((unsigned int *)pColors, 0, 0);
    count = pObject->mpUnknown1636->GetLeafCount();
    memset(pObject->mpUnknown8, 0, 0x400);
    fn_80199B68(pColors, (unsigned short *)pObject->mpUnknown8, count);
    fn_801D2BD0(pColors);
    pObject->mpUnknown1636->MapImage((unsigned int *)*ppImage, 128, 128, (unsigned char *)pObject->mpUnknown4);
}
#endif
}
