/* Simple shadows (SimpShadow module): a pool of textured blob shadows under
   objects, added by position, shown or hidden, and drawn in one pass. */
#include <dolphin/gx/GXPixel.h>
#include "engine/cu_80227F14.h"
#include "game/Object_80039F5C.h"
#include "game/Object_80193F84.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>

struct SimpShadowEntry {
    int mUnknown0;
    Vector_80039F5C *mpUnknown4;
    float mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
};

extern "C" {
int fn_800C47C4(void);
int fn_801CECCC(int index);
int fn_801CECDC(int a);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0D94(float x, float y, float z);
void fn_801D0F80(Mtx44 m);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_80210388(void);
void fn_802271A4(Vector_80039F5C *pOut, Vector_80039F5C *p);
void fn_80227384(Vector_80039F5C *pOut, Vector_80039F5C *p, int a);
void *fn_80236384(int a);
void fn_80236408(int a, Vector_80039F5C *pOut);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
extern "C" void GXInitTexObj(GXTexObj *pObj, void *p, int a, int b, int c, int d, int e, int f);
extern "C" void GXLoadTexObj(GXTexObj *pObj, int a);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
}

extern int lbl_803EBC98;

static SimpShadowEntry *_SimpShadow_apEntries[96];
static Object_80193F84 _SimpShadow_aTextures[1];
static GXTexObj _SimpShadow_TexObj;
static int _SimpShadow_aiTextureIds[1] = { 0 };
static unsigned short _SimpShadow_uCount = 0;
static SimpShadowEntry *_SimpShadow_pPool = 0;
static unsigned char _SimpShadow_bInit = 0;
static unsigned char _SimpShadow_bEnabled;

extern "C" {
int SimpShadowDrawQuad(int a, SimpShadowEntry *pEntry, Vector_80039F5C *pScale)
{
    Vector_80039F5C pts[4];
    Vector_80039F5C *pPos = pEntry->mpUnknown4;
    float dx = pEntry->mUnknown8 * pScale->mX;
    float dy = pEntry->mUnknown8 * pScale->mY;
    float z;

    pts[0].mX = pPos->mX + dx;
    pts[0].mY = pPos->mY + dy;
    pts[0].mZ = 0.0f;
    pts[1].mX = pPos->mX - dy;
    pts[1].mY = pPos->mY + dx;
    pts[1].mZ = 0.0f;
    pts[2].mX = pPos->mX - dx;
    pts[2].mY = pPos->mY - dy;
    pts[2].mZ = 0.0f;
    pts[3].mX = pPos->mX + dy;
    pts[3].mY = pPos->mY - dx;
    pts[3].mZ = 0.0f;
    z = pPos->mZ;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[0].mX, pts[0].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(pts[1].mX, pts[1].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(pts[2].mX, pts[2].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(pts[3].mX, pts[3].mY, z);
    GXColor4u8(pEntry->mUnknownC, pEntry->mUnknownE, pEntry->mUnknownD, pEntry->mUnknownF);
    GXTexCoord2f32(0.0f, 0.0f);
    return a;
}

void SimpShadowInit(void)
{
    unsigned short i;

    _SimpShadow_pPool = (SimpShadowEntry *)fn_801D2B7C(96 * sizeof(SimpShadowEntry), 0, 0);
    fn_801D34D0(_SimpShadow_pPool, 96 * sizeof(SimpShadowEntry), 0, 1);
    for (i = 0; i < 96; i++) {
        _SimpShadow_apEntries[i] = &_SimpShadow_pPool[i];
    }
    for (i = 0; i < 1; i++) {
        fn_80193F84(&_SimpShadow_aTextures[i]);
        fn_80193EF0(&_SimpShadow_aTextures[i], 0, fn_800C47C4(), _SimpShadow_aiTextureIds[i], "LLSimpShadow");
    }
    _SimpShadow_uCount = 0;
    _SimpShadow_bInit = 1;
    _SimpShadow_bEnabled = 1;
    GXInitTexObj(&_SimpShadow_TexObj, _SimpShadow_aTextures[0].mTexture.mpImage, _SimpShadow_aTextures[0].mTexture.mWidth,
                _SimpShadow_aTextures[0].mTexture.mHeight, _SimpShadow_aTextures[0].mTexture.mFormat, 0, 0, 0);
}

void SimpShadowShutdown(void)
{
    unsigned short i;

    for (i = 0; i < 1; i++) {
        if (_SimpShadow_aTextures[i].mUnknown28 != 0) {
            fn_80193F2C(&_SimpShadow_aTextures[i]);
        }
    }
    for (i = 0; i < 96; i++) {
        _SimpShadow_apEntries[i] = 0;
    }
    fn_801D2BD0(_SimpShadow_pPool);
    _SimpShadow_pPool = 0;
    _SimpShadow_bInit = 0;
    _SimpShadow_uCount = 0;
    _SimpShadow_bEnabled = 0;
}

void SimpShadowAdd(int a, Vector_80039F5C *p, float b, float *pColor)
{
    SimpShadowEntry *pEntry = _SimpShadow_apEntries[_SimpShadow_uCount];

    pEntry->mUnknown0 = a;
    pEntry->mpUnknown4 = p;
    pEntry->mUnknown8 = b;
    pEntry->mUnknownC = (unsigned char)(pColor[0] * 255.0f);
    pEntry->mUnknownE = (unsigned char)(pColor[1] * 255.0f);
    pEntry->mUnknownD = (unsigned char)(pColor[2] * 255.0f);
    pEntry->mUnknownF = (unsigned char)(pColor[3] * 255.0f);
    pEntry->mUnknown10 = 1;
    _SimpShadow_uCount++;
}

void SimpShadowDrawAll(void)
{
    Mtx44 mtx;
    Vector_80039F5C scale;
    GXColor color = { 128, 128, 128, 255 };

    if (_SimpShadow_bEnabled != 0) {
        unsigned short i;
        int cursor = fn_801CECDC(fn_801CECCC(2));

        fn_80210388();
        GXSetCullMode(GX_CULL_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetZCompLoc(GX_DISABLE);
        GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        fn_8024FC48(1);
        fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        fn_801D0470(fn_80228668());
        GXLoadTexObj(&_SimpShadow_TexObj, 0);
        fn_801D04C4();
        fn_801D0664((float (*)[4])fn_80236384(0));
        fn_80236408(0, &scale);
        scale.mZ = 0.0f;
        fn_80227384(&scale, &scale, 0x200000);
        fn_802271A4(&scale, &scale);
        fn_801D0F80(mtx);
        fn_8025251C(mtx, 0);
        fn_802525BC(0);
        fn_801D0544();
        for (i = 0; i < _SimpShadow_uCount; i++) {
            if (_SimpShadow_apEntries[i]->mUnknown10 != 0 && _SimpShadow_apEntries[i]->mUnknown0 == 0) {
                cursor = SimpShadowDrawQuad(cursor, _SimpShadow_apEntries[i], &scale);
            }
        }
        fn_801D04C4();
        fn_801D0D94(1.0f, 1.0f, 0.0f);
        fn_801D0F80(mtx);
        fn_8025251C(mtx, 0);
        fn_802525BC(0);
        fn_801D0544();
        scale.mY = scale.mX = 0.5f;
        for (i = 0; i < _SimpShadow_uCount; i++) {
            if (_SimpShadow_apEntries[i]->mUnknown10 != 0 && _SimpShadow_apEntries[i]->mUnknown0 == 1) {
                cursor = SimpShadowDrawQuad(cursor, _SimpShadow_apEntries[i], &scale);
            }
        }
        lbl_803EBC98 = cursor;
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
        fn_8024FB58(4, color);
    }
}

void SimpShadowSetVisible(void *p, int value)
{
    unsigned int i;

    for (i = 0; i < _SimpShadow_uCount; i++) {
        if (_SimpShadow_apEntries[i]->mpUnknown4 == p) {
            _SimpShadow_apEntries[i]->mUnknown10 = value;
        }
    }
}
}
