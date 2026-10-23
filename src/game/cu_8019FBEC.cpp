#include <dolphin/gx/GXPixel.h>
#include "game/cu_8019FBEC.h"
#include "game/fn_801EF390.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

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
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
    fn_8024FC48(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
    fn_8025251C(fn_801D0444(), 0);
    GXSetZCompLoc(GX_DISABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetAlphaCompare(GX_GREATER, 32, GX_AOP_AND, GX_GREATER, 32);
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
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_ENABLE);
    fn_80236EC0(value);
}
}
