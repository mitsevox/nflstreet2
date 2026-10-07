#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/cu_8008A274.h"
#include "engine/cu_80227F14.h"
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

typedef float Matrix_80198C54[4][4];

struct Triple_802EDF8C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
};

struct Object_8015E2FC {
    char mUnknown0[24];
    int mUnknown24;
};

/* Argument of fn_802338D4: a halfword-triple table at +0x30 and an output buffer at +0x34. */
struct Object_802338D4 {
    char mUnknown0[48];
    Triple_80198D98 *mpUnknown48;
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
int fn_8008A87C(int index);
void fn_8008B09C(Class_8008B284 *pObject, void *pImage, int width, int height);
void fn_8008B134(Class_8008B284 *pObject, void *pOut, void *p, int *pCount);
int fn_8008B27C(Class_8008B284 *pObject);
void fn_8008B1F0(Class_8008B284 *pObject, void *pImage, int width, int height, void *pOut);
Object_8015E2FC *fn_8015E2FC(int a, int b, int c);
void fn_80210214(Object_8023488C *pObject, int a);
void fn_80210388(void);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_80211FF0(void);
void fn_80212018(const char *pName, void *p);
void fn_802337D4(void *a, void *b, Triple_80198D98 *pTriples, int c);
void fn_802338D4(Object_802338D4 *pObject, Skeleton_80041930 *pData, Matrix_80198C54 *pOut);
void fn_80233BB8(Object_80233BB8 *pObject, int a, int b);
void fn_80233BD8(Object_80233BB8 *pObject);
void fn_80233BDC(Object_80233BB8 *pObject, Skeleton_80041930 *pData);
void fn_80233CBC(void *pObject, int a, int b);
void fn_8023465C(Object_8023488C *pObject, Object_8015E2FC *p, Desc_802347EC *pDesc);
void fn_8023488C(Object_8023488C *pObject, int a);
void fn_802348AC(Object_8023488C *pObject);
void fn_80234A30(Object_80234A30 *pObject, int a);
void fn_80234A90(Object_80234A30 *pObject);
void fn_80234A94(Object_80234A30 *pObject, void *p);
void fn_80234AD8(Object_80234A30 *pObject, void *p);
void fn_80234BF4(int a, Object_80234A30 *pObject, int b);
void fn_80234CA4(Object_80234A30 *pObject, Object_80233BB8 *p);
void fn_80234CAC(Object_80234A30 *pObject, int a);
void fn_80234CF0(Object_80234A30 *pObject, int a, Object_8023488C *p);
void fn_80234DC0(Object_80234A30 *pObject, int a);
int fn_80236B98(int a, float x, float y, float z);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024E450(void);
void fn_8024E63C(unsigned short x, unsigned short y, unsigned int *pColor);
void fn_8024E660(unsigned short x, unsigned short y, unsigned int *pDepth);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_8024FFC4(GXTexObj *pObj, void *p, int a, int b, int c, int d, int e, int f);
void fn_802505A8(GXTexObj *pObj, int a);
void fn_80251604(int a, int b);
void fn_80251A58(int a, int b, int c, int d, int e);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int a, int b, int c, int d);
void fn_802520E0(int a, int b, int c);
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

void fn_80198C54(Object_80234A30 *pObject, unsigned int index)
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
    fn_8024FFC4(&lbl_80365298, lbl_803ECBE4, 128, 128, 6, 0, 0, 0);
}

void fn_80198D60(void **ppBuffer)
{
    fn_801D2BD0(*ppBuffer);
    *ppBuffer = 0;
}

void fn_80198D98(Object_8008A9F8 *pObject)
{
    unsigned int i;
    unsigned int j;
    Skeleton_80041930 *pData0;
    Skeleton_80041930 *pData1;

    for (i = 0; i <= 1; i++) {
        Skeleton_80041930 *pData = fn_8008A84C(i);
        int value = fn_8008A87C(i);

        fn_80233BB8(&pObject->mUnknown588[i], value, 0);
        fn_80233BDC(&pObject->mUnknown588[i], pData);
    }

    pData0 = fn_8008A84C(0);
    memset(pObject->mUnknown1340, 0, sizeof(pObject->mUnknown1340));
    pData1 = fn_8008A84C(1);
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

void fn_80198EE0(Object_8008A9F8 *pObject)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        fn_80233BD8(&pObject->mUnknown588[i]);
    }
}

void fn_80198F24(Object_8008A9F8 *pObject)
{
    Object_8015E2FC *pResult = fn_8015E2FC(0, 0, 0);
    Object_8023488C *pUnknown612 = &pObject->mUnknown612;
    void *pElement = pObject->mUnknown384[0].mpUnknown24;
    Desc_802347EC *pDescs = pObject->mUnknown384;

    fn_80211FF0();
    fn_80212018("capport", pElement);
    fn_8023488C(pUnknown612, 0x38);
    fn_80210214(pUnknown612, pResult->mUnknown24);
    fn_8023465C(pUnknown612, pResult, pDescs);
    fn_80211FF0();
}

void fn_80198FAC(Object_8008A9F8 *pObject)
{
    fn_802348AC(&pObject->mUnknown612);
}

void fn_80198FD0(Object_8008A9F8 *pObject)
{
    unsigned int i;

    for (i = 0; i <= 2; i++) {
        fn_80234A30(&pObject->mUnknown620[i], 0x100);
    }
}

void fn_80199018(Object_8008A9F8 *pObject)
{
    unsigned int i;

    for (i = 0; i <= 2; i++) {
        fn_80234A90(&pObject->mUnknown620[i]);
    }
}

void fn_8019905C(Object_8008A9F8 *pObject)
{
    Object_802338D4 desc;
    Matrix_80198C54 matrices[40];
    Triple_80198D98 triples[19];
    Skeleton_80041930 *pData0;
    Skeleton_80041930 *pData1;
    unsigned int i;
    Object_8023488C *pUnknown612 = &pObject->mUnknown612;

    fn_801D0508();
    fn_801D0C58(&lbl_802EDF8C);
    fn_801D0BCC((int)(lbl_802EDF98.mUnknown8 * 46603.379f), (int)(lbl_802EDF98.mUnknown4 * 46603.379f),
                (int)(lbl_802EDF98.mUnknown0 * 46603.379f));
    fn_801D0CFC(lbl_803EB770);
    fn_801D0F80(lbl_803652B8);
    fn_8025251C(lbl_803652B8, 0);
    fn_802525BC(0);
    fn_801D0544();

    pData0 = fn_8008A84C(0);
    pData1 = fn_8008A84C(1);
    for (i = 0; i <= 2; i++) {
        Object_80234A30 *pElement = &pObject->mUnknown620[i];
        Object_80233BB8 *pUnknown588 = 0;

        switch (i) {
        case 0:
            pUnknown588 = &pObject->mUnknown588[0];
            fn_80234AD8(pElement, fn_8008A808(pObject, 0));
            break;
        case 1:
            pUnknown588 = &pObject->mUnknown588[0];
            fn_80234AD8(pElement, fn_8008A808(pObject, 0));
            break;
        case 2:
            pUnknown588 = &pObject->mUnknown588[1];
            fn_80234A94(pElement, fn_8008A808(pObject, 1));
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

void fn_8019930C(Object_8008A9F8 *pObject)
{
    unsigned int *pOut;
    unsigned int y;
    unsigned int x;
    unsigned int color;
    unsigned int depth;

    fn_8024E450();
    pOut = (unsigned int *)lbl_803ECBE4;
    for (y = 160; y < 288; y++) {
        for (x = 256; x < 384; x++) {
            fn_8024E63C(x, y, &color);
            fn_8024E660(x, y, &depth);
            if (depth > 0xFF0000) {
                color = 0xFF00FF00;
            }
            *pOut++ = color;
        }
    }
    fn_8024E450();
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
        fn_80251CC4(1);
        fn_80251B28(0, 0, 0, 4);
        fn_80251604(0, 0);
        fn_8024DF64(1);
        fn_8024DCE4(0, 0, 4, 60, 0, 125);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024CB90(13, 1);
        fn_8024D450(0, 9, 1, 4, 4);
        fn_8024D450(0, 13, 1, 4, 0);
        fn_802520E0(0, 7, 0);
        GXSetCullMode(GX_CULL_NONE);
        fn_802528B0(1);
        fn_80252034(1, 4, 5, 5);
        fn_802505A8(pTexture, 0);
    } else {
        fn_80251CC4(1);
        fn_80251B28(0, 0, 0, 4);
        fn_80251604(0, 4);
        fn_8024DF64(0);
        fn_8024DCE4(0, 0, 4, 60, 0, 125);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024D450(0, 9, 1, 4, 4);
        fn_802520E0(0, 7, 0);
        GXSetCullMode(GX_CULL_NONE);
        fn_802528B0(1);
        fn_80252034(1, 4, 5, 5);
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
    fn_80252034(0, 0, 0, 5);
    fn_802523A4(lbl_80365338, 0);
    fn_802520E0(1, 3, 1);
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
    fn_80228AD4(lbl_803652F8, 45.0f, 4.0f / 3.0f, 1.0f, 200.0f);
    fn_802523A4(lbl_803652F8, 0);
    fn_80228668();
    fn_801D0470();
    fn_801D04C4();
    fn_801D1258(2, lbl_803652F8);
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D12EC(6);
    fn_801D0544();
}

void fn_80199838(Object_8008A9F8 *pObject)
{
    int mask;

    fn_8019979C();
    fn_80210388();
    GXColor white = {255, 255, 255, 255};
    mask = fn_80236B98(2, 1.0f, 1.0f, 1.0f);
    fn_8024FB58(4, white);
    fn_8024FC48(1);
    fn_8024FC84(4, 1, 0, 0, mask, 2, 2);
    fn_80251A58(7, 0, 0, 7, 0);
    GXSetCullMode(GX_CULL_FRONT);
    fn_80210BD8(1);
    fn_80234BF4(0, &pObject->mUnknown620[0], 0);
    fn_80251A58(4, 0, 0, 7, 0);
    fn_80210BD8(2);
    fn_80210CC4(0.0f, lbl_803EB774);
    fn_80234BF4(0, &pObject->mUnknown620[1], 0);
    fn_80234BF4(0, &pObject->mUnknown620[2], 0);
    fn_8019969C();
}

void fn_80199968(Object_8008A9F8 *pObject)
{
    fn_80198CFC(&lbl_803ECBE4);
    fn_80198D98(pObject);
    fn_80198F24(pObject);
    fn_80198FD0(pObject);
}

void fn_801999B0(Object_8008A9F8 *pObject)
{
    fn_80199018(pObject);
    fn_80198FAC(pObject);
    fn_80198EE0(pObject);
    fn_80198D60(&lbl_803ECBE4);
}

void fn_801999F4(Object_8008A9F8 *pObject)
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

void fn_80199BD4(Object_8008A9F8 *pObject)
{
    void **ppImage = &lbl_803ECBE4;
    unsigned char (*pColors)[4];
    int count;

    fn_8008B09C(pObject->mpUnknown1636, *ppImage, 128, 128);
    pColors = (unsigned char (*)[4])fn_801D2B7C(0x400, 0, 0);
    memset(pColors, 0, 0x400);
    fn_8008B134(pObject->mpUnknown1636, pColors, 0, 0);
    count = fn_8008B27C(pObject->mpUnknown1636);
    memset(pObject->mpUnknown8, 0, 0x400);
    fn_80199B68(pColors, (unsigned short *)pObject->mpUnknown8, count);
    fn_801D2BD0(pColors);
    fn_8008B1F0(pObject->mpUnknown1636, *ppImage, 128, 128, pObject->mpUnknown4);
}
#endif
}
