/* Pass icons: loads the three palette icon textures and draws one as a
   camera-facing quad above a player the ball can be passed to. */
#include <dolphin/gx/GXPixel.h>
#include "game/PassIconTex.h"
#include "game/ResLoad.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

struct PassIconTexLib {
    char mUnknown0[0x28];
};

struct PassIconTexture {
    char mUnknown0[0x24];
    unsigned short mUnknown24;
    unsigned short mUnknown26;
};

struct PassIconClut {
    char mUnknown0[4];
    char mUnknown4[4];
};

extern "C" {
int fn_800C47C4(void);
Mtx44Ptr fn_801D0444(void);
void TMRenderReset(void);
void TMTexLibLoad(PassIconTexLib *pElement, int a);
void TMTexLibUnload(PassIconTexLib *pElement);
PassIconTexture *TMTexLibGetTexture(PassIconTexLib *pElement, int a);
PassIconClut *TMTexLibGetClut(PassIconTexLib *pElement, int a, int b);
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

static PassIconTexLib _PassIconTex_TexLib;
static PassIconTexture *_PassIconTex_apTextures[3];
static GXTexObj _PassIconTex_aTexObjs[3];
static PassIconClut *_PassIconTex_apCluts[3];
static GXTlutObj _PassIconTex_aTlutObjs[3];
static unsigned char _PassIconTex_bLoaded = 0;
static int _PassIconTex_hTextures = 0;

extern "C" {
void PassIconTexLoad(void)
{
    int i;

    _PassIconTex_hTextures = ResLoad((void *)fn_800C47C4(), 4, 1);
    TMTexLibLoad(&_PassIconTex_TexLib, _PassIconTex_hTextures);
    for (i = 0; i < 3; i++) {
        _PassIconTex_apTextures[i] = TMTexLibGetTexture(&_PassIconTex_TexLib, 0xFF000000 + i);
        GXInitTexObjCI(&_PassIconTex_aTexObjs[i], GXGetTexObjData(_PassIconTex_apTextures[i]), _PassIconTex_apTextures[i]->mUnknown24,
                    _PassIconTex_apTextures[i]->mUnknown26, 9, 0, 0, 0, 0);
    }
    for (i = 0; i < 3; i++) {
        _PassIconTex_apCluts[i] = TMTexLibGetClut(&_PassIconTex_TexLib, 0xFF000000, i);
        GXInitTlutObj(&_PassIconTex_aTlutObjs[i], GXGetTlutObjData(_PassIconTex_apCluts[i]->mUnknown4),
                    GXGetTlutObjFmt(_PassIconTex_apCluts[i]->mUnknown4), GXGetTlutObjNumEntries(_PassIconTex_apCluts[i]->mUnknown4));
    }
    _PassIconTex_bLoaded = 1;
}

void PassIconTexFree(void)
{
    TMTexLibUnload(&_PassIconTex_TexLib);
    _PassIconTex_hTextures = 0;
    ResUnLoad((void *)fn_800C47C4(), 4);
    _PassIconTex_bLoaded = 0;
}

void PassIconTexDraw(PassIconObj_t *pInstance)
{
    int value = fn_80236EC0(0);

    TMRenderReset();
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
    GXLoadTlut(&_PassIconTex_aTlutObjs[pInstance->mUnknown1D], 0);
    GXLoadTexObj(&_PassIconTex_aTexObjs[pInstance->mUnknown1C], 0);
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
