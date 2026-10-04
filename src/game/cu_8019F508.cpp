#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

/* 48-byte element; fn_8019F508 fills one per entry of the handler set. */
struct Element_8019F508 {
    char mUnknown0[0x28];
    int mUnknown28;
    int mUnknown2C;
};

struct Object_8019F874;

/* Object passed to the per-object handlers; +0x68 selects its handler set. */
struct Object_8019FA8C {
    char mUnknown0[0xC];
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
    char mUnknown18[0x18];
    int mUnknown30;
    float mUnknown34;
    char mUnknown38[0x18];
    Object_8019F874 *mpUnknown50;
    char mUnknown54[0xC];
    Element_8019F508 *mpUnknown60;
    char mUnknown64[4];
    int mUnknown68;
    int mUnknown6C;
};

struct Object_8019F874 {
    char mUnknown0[0xB];
    unsigned char mUnknownB;
};

extern "C" {
int fn_80044528(int index);
int fn_80044544(void);
int fn_80044564(int index, int i);
int fn_801EF390(int a, int b, int c);
void fn_801F010C(int a, int b);
void fn_80211E08(Element_8019F508 *pElement, int a);
void fn_80211EFC(Element_8019F508 *pElement);
int fn_802120E4(Element_8019F508 *pElement, int a);
int fn_80212124(Element_8019F508 *pElement, int a, int b);
void fn_80210388(void);
void fn_80210814(int a, int b, int c);
void fn_80210CC4(float a, float b);
int fn_80236EC0(int a);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80251604(int a, int b);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int a, int b, int c, int d);
void fn_802520E0(int a, int b, int c);
void fn_80252114(int a);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0ADC(int a);
void fn_801D0C58(void *a);
void fn_801D0D94(float x, float y, float z);
void fn_801D0F80(Mtx44 m);
}

static Element_8019F508 *lbl_803ECBF4[1];
static unsigned char lbl_803ECBF8;

extern "C" {
void fn_8019F508(int index)
{
    if (fn_80044528(index) > 0) {
        int i = 0;
        Element_8019F508 *pElement;
        int handle;

        pElement = lbl_803ECBF4[index] = (Element_8019F508 *)fn_801D2B7C(fn_80044528(index) * sizeof(Element_8019F508), 0, 0);
        handle = fn_80044544();
        for (; i < fn_80044528(index); i++) {
            fn_80211E08(pElement, fn_801EF390(handle, fn_80044564(index, i), 1));
            pElement->mUnknown28 = fn_802120E4(pElement, 0xFF000000);
            pElement->mUnknown2C = fn_80212124(pElement, 0xFF000000, 0);
            pElement++;
        }
    }
}

void fn_8019F5D8(int index)
{
    if (fn_80044528(index) > 0) {
        Element_8019F508 *pElements = lbl_803ECBF4[index];
        int i;

        for (i = 0; i < fn_80044528(index); i++) {
            fn_80211EFC(&pElements[i]);
            fn_801F010C(fn_80044544(), fn_80044564(index, i));
        }
        fn_801D2BD0(pElements);
        lbl_803ECBF4[index] = 0;
    }
}

void fn_8019F678(Object_8019FA8C *pObject)
{
    pObject->mpUnknown60 = &lbl_803ECBF4[pObject->mUnknown68][pObject->mUnknown6C];
}

void fn_8019F69C(Object_8019FA8C *pObject)
{
    pObject->mpUnknown60 = 0;
}

void fn_8019F6A8(Object_8019FA8C *pObject)
{
    pObject->mpUnknown60 = &lbl_803ECBF4[pObject->mUnknown68][pObject->mUnknown6C];
}

void fn_8019F6CC(int index)
{
    GXColor color = { 255, 255, 255, 255 };

    fn_80210388();
    lbl_803ECBF8 = fn_80236EC0(1);
    GXSetCullMode(GX_CULL_NONE);
    fn_80252034(1, 4, 5, 5);
    fn_80252114(0);
    fn_802520E0(1, 3, 0);
    fn_80210CC4(0.01f, 0.01f);
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024FB58(4, color);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 0, 1, 2, 1);
    fn_8024CB90(13, 1);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_80251604(0, 0);
    fn_8024DF64(1);
    fn_8024DCE4(0, 1, 4, 60, 0, 125);
    fn_80251CC4(1);
    fn_80251B28(0, 0, 0, 4);
}

void fn_8019F82C(int index)
{
    fn_80210CC4(0.0f, 1.0f);
    fn_802520E0(1, 3, 1);
    fn_80236EC0(lbl_803ECBF8);
}

void fn_8019F874(Object_8019FA8C *pObject)
{
    Mtx44 mtx;
    GXColor color = { 255, 255, 255, 255 };

    if (pObject->mpUnknown50 == 0 || pObject->mpUnknown50->mUnknownB != 0) {
        color.a = pObject->mUnknown34 * 255.0f;
        fn_8024FB58(4, color);
        fn_80210814(0, pObject->mpUnknown60->mUnknown28, pObject->mpUnknown60->mUnknown2C);
        fn_801D04C4();
        fn_801D0C58(pObject);
        fn_801D0ADC(pObject->mUnknown30);
        fn_801D0D94(pObject->mUnknownC, pObject->mUnknown10, pObject->mUnknown14);
        fn_801D0F80(mtx);
        fn_8025251C(mtx, 0);
        fn_802525BC(0);
        fn_801D0544();
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
        GXWGFifo.f32 = -0.16f;
        GXWGFifo.f32 = 0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.16f;
        GXWGFifo.f32 = 0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.16f;
        GXWGFifo.f32 = -0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = 1.0f;
        GXWGFifo.f32 = -0.16f;
        GXWGFifo.f32 = -0.27f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 0.0f;
        GXWGFifo.f32 = 1.0f;
    }
}
}

struct HandlerSet_802F2714 {
    void (*mpUnknown0)(int index);
    void (*mpUnknown4)(int index);
    void (*mpUnknown8)(Object_8019FA8C *pObject);
    void (*mpUnknownC)(Object_8019FA8C *pObject);
    void (*mpUnknown10)(Object_8019FA8C *pObject);
    void (*mpUnknown14)(int index);
    void (*mpUnknown18)(int index);
    void (*mpUnknown1C)(Object_8019FA8C *pObject);
};

static HandlerSet_802F2714 lbl_802F2714[] = {
    { fn_8019F508, fn_8019F5D8, fn_8019F678, fn_8019F69C, fn_8019F6A8, fn_8019F6CC, fn_8019F82C, fn_8019F874 },
};

extern "C" {
void fn_8019F9F0(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(lbl_802F2714) / sizeof(lbl_802F2714[0]); i++) {
        lbl_802F2714[i].mpUnknown0(i);
    }
}

void fn_8019FA3C(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(lbl_802F2714) / sizeof(lbl_802F2714[0]); i++) {
        lbl_802F2714[i].mpUnknown4(i);
    }
}

void fn_8019FA8C(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown8(pObject);
}

void fn_8019FAC8(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknownC(pObject);
}

void fn_8019FB04(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown10(pObject);
}

void fn_8019FB40(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown1C(pObject);
}

void fn_8019FB7C(int index)
{
    lbl_802F2714[index].mpUnknown14(index);
}

void fn_8019FBB4(int index)
{
    lbl_802F2714[index].mpUnknown18(index);
}
}
