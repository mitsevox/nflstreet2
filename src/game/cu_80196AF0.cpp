#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

struct Entry_80196B24 {
    void *mpUnknown0;
    int mUnknown4;
};

extern "C" {
int fn_800A34F8(int index);
int fn_801C0BA8(Entry_80196B24 *pEntry, int a);
void fn_801C0CCC(int a);
void fn_801D03D0(Mtx44 m);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0F80(Mtx44 m);
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801EF7BC(void *a, int b, void *p);
int fn_801F0C50(void *a, int b);
void fn_8020FA38(int a, void *b);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FA68(int a, GXColor color);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80251604(int a, int b);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int a, int b, int c, int d);
void fn_802520E0(int a, int b, int c);
void fn_802523A4(Mtx44 m, int a);
void fn_80252448(float *p);
void fn_802524D4(float *p);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
void fn_802528B0(int a);

void fn_80196AF0(void)
{
    fn_801D0508();
    fn_8020FA38(0, 0);
    fn_801D0544();
}

void fn_80196B20(void)
{
}

void fn_80196B24(Entry_80196B24 *pEntries, int *pValues, void *pData)
{
    unsigned char i;

    for (i = 0; i <= 7; i++) {
        pEntries[i].mpUnknown0 = pData;
        if (fn_800A34F8(i)) {
            void *pBuffer = fn_801D2BB0(1, fn_801F0C50(pEntries[i].mpUnknown0, pEntries[i].mUnknown4), 4, 0);

            fn_801EF7BC(pEntries[i].mpUnknown0, pEntries[i].mUnknown4, pBuffer);
            pValues[i] = fn_801C0BA8(&pEntries[i], 0);
            fn_801D2BD0(pBuffer);
        }
    }
}

void fn_80196BD4(int *pValues)
{
    unsigned char i;

    for (i = 0; i <= 7; i++) {
        if (fn_800A34F8(i)) {
            fn_801C0CCC(pValues[i]);
        }
    }
}

void fn_80196C2C(unsigned int color, int mode, float alpha)
{
    Mtx44 view;
    Mtx44 projection;
    GXColor fill = {0, 0, 0, 255};
    GXColor black = {0, 0, 0, 0};
    unsigned int r;
    unsigned int g;
    unsigned int b;

    r = (color & 0xFF) * 2;
    g = ((color >> 8) & 0xFF) * 2;
    b = ((color >> 16) & 0xFF) * 2;
    fill.r = r > 255 ? 255 : r;
    fill.g = g > 255 ? 255 : g;
    fill.b = b > 255 ? 255 : b;
    fill.a = alpha * 255.0f;
    fn_8024FC48(1);
    fn_8024FA68(4, black);
    fn_8024FB58(4, fill);
    fn_8024FC84(4, 0, 0, 0, 1, 0, 2);
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
    switch (mode) {
    case 1:
        fn_80252034(1, 2, 4, 5);
        break;
    case 0:
    default:
        fn_80252034(1, 4, 5, 5);
        break;
    }
    {
        float saved[7];

        fn_802524D4(saved);
        C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
        fn_802523A4(projection, 1);
        fn_801D04C4();
        fn_801D03D0(view);
        fn_8025251C(view, 0);
        fn_802525BC(0);
        fn_801D0544();
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, -1.0f);
        GXPosition3f32(640.0f, 0.0f, -1.0f);
        GXPosition3f32(0.0f, 448.0f, -1.0f);
        GXPosition3f32(640.0f, 448.0f, -1.0f);
        fn_80252448(saved);
    }
    fn_801D0F80(view);
    fn_8025251C(view, 0);
    fn_80252034(0, 0, 0, 5);
    fn_802520E0(1, 3, 1);
    fn_802528B0(0);
}

void fn_80196EF8(int unused, unsigned int color, float alpha)
{
    fn_80196C2C(color, 0, alpha);
}

void fn_80196F20(int unused, unsigned int color, float alpha)
{
    fn_80196C2C(color, 1, alpha);
}
}
