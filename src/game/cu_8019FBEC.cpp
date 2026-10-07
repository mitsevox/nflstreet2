#include <dolphin/gx/GXPixel.h>
#include "game/cu_8019FBEC.h"
#include "game/fn_801EF390.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>

struct Element_8019FBEC {
    char mUnknown0[0x28];
};

struct Texture_80365470 {
    char mUnknown0[0x24];
    unsigned short mUnknown24;
    unsigned short mUnknown26;
};

struct Palette_803654DC {
    char mUnknown0[4];
    char mUnknown4[4];
};

extern "C" {
int fn_800C47C4(void);
Mtx44Ptr fn_801D0444(void);
void fn_80210388(void);
void fn_80211E08(Element_8019FBEC *pElement, int a);
void fn_80211EFC(Element_8019FBEC *pElement);
Texture_80365470 *fn_802120E4(Element_8019FBEC *pElement, int a);
Palette_803654DC *fn_80212124(Element_8019FBEC *pElement, int a, int b);
int fn_80236EC0(int a);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
extern "C" void GXInitTexObjCI(GXTexObj *pObject, void *pData, int width, int height, int a, int b, int c, int d, int e);
extern "C" void *GXGetTexObjData(void *p);
extern "C" void GXLoadTexObj(GXTexObj *pObject, int a);
extern "C" void GXInitTlutObj(GXTlutObj *pObject, int a, int b, int c);
extern "C" int GXGetTlutObjData(void *p);
extern "C" int GXGetTlutObjFmt(void *p);
extern "C" int GXGetTlutObjNumEntries(void *p);
extern "C" void GXLoadTlut(GXTlutObj *pObject, int a);
void fn_80251604(int a, int b);
void fn_80251A58(int a, int b, int c, int d, int e);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_8025251C(Mtx44 m, int a);
}

static Element_8019FBEC lbl_80365448;
static Texture_80365470 *lbl_80365470[3];
static GXTexObj lbl_8036547C[3];
static Palette_803654DC *lbl_803654DC[3];
static GXTlutObj lbl_803654E8[3];
static unsigned char lbl_803EB7D0 = 0;
static int lbl_803EB7D4 = 0;

extern "C" {
void fn_8019FBEC(void)
{
    int i;

    lbl_803EB7D4 = fn_801EF390((void *)fn_800C47C4(), 4, 1);
    fn_80211E08(&lbl_80365448, lbl_803EB7D4);
    for (i = 0; i < 3; i++) {
        lbl_80365470[i] = fn_802120E4(&lbl_80365448, 0xFF000000 + i);
        GXInitTexObjCI(&lbl_8036547C[i], GXGetTexObjData(lbl_80365470[i]), lbl_80365470[i]->mUnknown24,
                    lbl_80365470[i]->mUnknown26, 9, 0, 0, 0, 0);
    }
    for (i = 0; i < 3; i++) {
        lbl_803654DC[i] = fn_80212124(&lbl_80365448, 0xFF000000, i);
        GXInitTlutObj(&lbl_803654E8[i], GXGetTlutObjData(lbl_803654DC[i]->mUnknown4),
                    GXGetTlutObjFmt(lbl_803654DC[i]->mUnknown4), GXGetTlutObjNumEntries(lbl_803654DC[i]->mUnknown4));
    }
    lbl_803EB7D0 = 1;
}

void fn_8019FD38(void)
{
    fn_80211EFC(&lbl_80365448);
    lbl_803EB7D4 = 0;
    fn_801F010C((void *)fn_800C47C4(), 4);
    lbl_803EB7D0 = 0;
}

void fn_8019FD80(Instance_80159F10 *pInstance)
{
    int value = fn_80236EC0(0);

    fn_80210388();
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024CB90(11, 1);
    fn_8024CB90(13, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
    fn_8024FC48(1);
    fn_8024DF64(1);
    fn_8024DCE4(0, 1, 4, 60, 0, 125);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    fn_80251B28(0, 0, 0, 4);
    fn_80251604(0, 0);
    fn_80251CC4(1);
    fn_8025251C(fn_801D0444(), 0);
    GXSetZCompLoc(GX_DISABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    fn_80251A58(4, 32, 0, 4, 32);
    GXLoadTlut(&lbl_803654E8[pInstance->mUnknown1D], 0);
    GXLoadTexObj(&lbl_8036547C[pInstance->mUnknown1C], 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.8f, 0.0f, -0.8f);
    GXColor4u8(255, 255, 255, pInstance->mUnknown20 * 255.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.8f, 0.0f, -0.8f);
    GXColor4u8(255, 255, 255, pInstance->mUnknown20 * 255.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.8f, 0.0f, 0.8f);
    GXColor4u8(255, 255, 255, pInstance->mUnknown20 * 255.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.8f, 0.0f, 0.8f);
    GXColor4u8(255, 255, 255, pInstance->mUnknown20 * 255.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    fn_80251A58(7, 0, 0, 7, 0);
    GXSetZCompLoc(GX_ENABLE);
    fn_80236EC0(value);
}
}
