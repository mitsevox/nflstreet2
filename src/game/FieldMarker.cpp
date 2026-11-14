/* Draws on-field markers: groups of translucent beams at fixed spots and small arrows over chosen
   positions, plus a Z-buffer read used to test whether an effect is hidden behind scenery. */
#include "engine/viewport.h"
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/gx/GXTev.h>

#include "game/FieldMarker.h"

struct Glow_t;

extern "C" {
void TMRenderReset(void);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_8024FC48(int a);
void TMRenderSetBlendMode(int a);
void TMRenderSetZRange(float a, float b);
void fn_801D0470(int a);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D131C(int a);
Mtx44Ptr fn_801D0444(void);
void GXLoadPosMtxImm(Mtx44 m, int a);
void fn_80227490(float *pOut, float *pIn, int a, int b, int c);
void fn_8022765C(float *pOut, float *pA, float *pB);
int fn_801CEA08(void);
int fn_801CEA14(void);
}

/* The texture of one marker kind: 0x4C bytes of .bss, of which the draw code uses only the
   texture object at +0x20 and the palette object at +0x40. No GameCube code initialises them. */
struct FieldMarkerTexture_t {
    unsigned char mUnknown0[0x20];
    GXTexObj mTexObj;
    GXTlutObj mTlutObj;
};

/* 8 bytes of .sdata per marker kind: the draw code reads only byte +0, which selects the
   palette load when it is 1. */
struct FieldMarkerTextureInfo_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1[7];
};

static FieldMarkerTextureInfo_t _FieldMarker_BeamTextureInfo = {0};
static FieldMarkerTextureInfo_t _FieldMarker_ArrowTextureInfo = {0};
static FieldMarkerTexture_t _FieldMarker_BeamTexture;
static FieldMarkerTexture_t _FieldMarker_ArrowTexture;

static float _FieldMarker_aBeamCorners[4][3] = {
    {-0.5f, 4.0f, 0.0f},
    {-0.5f, -4.0f, 0.0f},
    {0.5f, -4.0f, 0.0f},
    {0.5f, 4.0f, 0.0f},
};

static float _FieldMarker_aBeamUVs[4][2] = {
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 0.0f},
};

static float _FieldMarker_aArrowVerts[15][3] = {
    {-0.15f, 0.15f, 0.0f},
    {0.15f, 0.15f, 0.0f},
    {0.15f, -0.15f, 0.0f},
    {-0.15f, 0.15f, 0.0f},
    {-0.15f, -0.15f, 0.0f},
    {0.15f, -0.15f, 0.0f},
    {-0.075f, 0.075f, 0.15f},
    {0.075f, 0.075f, 0.15f},
    {0.0f, 0.0f, 0.0f},
    {0.075f, 0.075f, 0.15f},
    {0.0f, -0.075f, 0.15f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, -0.075f, 0.15f},
    {-0.075f, 0.075f, 0.15f},
    {0.0f, 0.0f, 0.0f},
};

static float _FieldMarker_aArrowUVs[15][2] = {
    {0.5f, 1.0f},
    {0.5f, 0.0f},
    {0.0f, 0.0f},
    {0.0f, 1.0f},
    {0.5f, 1.0f},
    {0.5f, 0.0f},
    {1.0f, 0.0f},
    {0.5f, 0.0f},
    {0.75f, 1.0f},
    {1.0f, 0.0f},
    {0.5f, 0.0f},
    {0.75f, 1.0f},
    {1.0f, 0.0f},
    {0.5f, 0.0f},
    {0.75f, 1.0f},
};

extern "C" {

void FieldMarkerInitEffect(Glow_t *p)
{
}

void _FieldMarkerDrawBeam(FieldMarkerBeam_t *p, float *position, int angle)
{
    float vertex[3];
    float transformed[3];
    GXColor color = {255, 255, 255, 255};
    color.a = (unsigned char)(p->mUnknown4 * 255.0f);

    vertex[0] = _FieldMarker_aBeamCorners[0][0] + p->mUnknown8;
    vertex[1] = _FieldMarker_aBeamCorners[0][1];
    vertex[2] = _FieldMarker_aBeamCorners[0][2];
    fn_80227490(vertex, vertex, angle, 0, 0);
    fn_8022765C(transformed, position, vertex);
    GXPosition3f32(transformed[0], transformed[1], transformed[2]);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(_FieldMarker_aBeamUVs[0][0], _FieldMarker_aBeamUVs[0][1]);

    vertex[0] = _FieldMarker_aBeamCorners[1][0] + p->mUnknown8;
    vertex[1] = _FieldMarker_aBeamCorners[1][1];
    vertex[2] = _FieldMarker_aBeamCorners[1][2];
    fn_80227490(vertex, vertex, angle, 0, 0);
    fn_8022765C(transformed, position, vertex);
    GXPosition3f32(transformed[0], transformed[1], transformed[2]);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(_FieldMarker_aBeamUVs[1][0], _FieldMarker_aBeamUVs[1][1]);

    vertex[0] = _FieldMarker_aBeamCorners[2][0] * p->mUnknown0 + p->mUnknown8;
    vertex[1] = _FieldMarker_aBeamCorners[2][1];
    vertex[2] = _FieldMarker_aBeamCorners[2][2];
    fn_80227490(vertex, vertex, angle, 0, 0);
    fn_8022765C(transformed, position, vertex);
    GXPosition3f32(transformed[0], transformed[1], transformed[2]);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(_FieldMarker_aBeamUVs[2][0], _FieldMarker_aBeamUVs[2][1]);

    vertex[0] = _FieldMarker_aBeamCorners[3][0] * p->mUnknown0 + p->mUnknown8;
    vertex[1] = _FieldMarker_aBeamCorners[3][1];
    vertex[2] = _FieldMarker_aBeamCorners[3][2];
    fn_80227490(vertex, vertex, angle, 0, 0);
    fn_8022765C(transformed, position, vertex);
    GXPosition3f32(transformed[0], transformed[1], transformed[2]);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(_FieldMarker_aBeamUVs[3][0], _FieldMarker_aBeamUVs[3][1]);
}

void FieldMarkerDrawBeams(void)
{
    TMRenderReset();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    fn_8024FC84(4, 0, 1, 1, 0, 0, 2);
    fn_8024FC48(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    TMRenderSetBlendMode(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
    fn_801D0470(VptGetMatrixStack());
    fn_801D0508();
    fn_801D131C(3);
    GXLoadPosMtxImm(fn_801D0444(), 0);
    fn_801D0544();
    if (_FieldMarker_BeamTextureInfo.mUnknown0 == 1)
        GXLoadTlut(&_FieldMarker_BeamTexture.mTlutObj, 0);
    GXLoadTexObj(&_FieldMarker_BeamTexture.mTexObj, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 180);
    for (unsigned int i = 0; i < 15; i++) {
        FieldMarkerBeamSet_t *record = &gFieldMarkerBeamSets[i];
        for (unsigned int j = 0; j < 3; j++) {
            _FieldMarkerDrawBeam(&record->mUnknown10[j], record->mPosition,
                        (int)(record->mUnknownC * 46603.379f));
        }
    }
    TMRenderSetBlendMode(1);
}

void FieldMarkerDrawArrows(void)
{
    GXColor color = {128, 128, 128, 128};
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
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    TMRenderSetBlendMode(6);
    GXSetNumTevStages(1);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    TMRenderSetZRange(0.0f, 0.9999f);
    fn_801D0470(VptGetMatrixStack());
    fn_801D0508();
    fn_801D131C(3);
    GXLoadPosMtxImm(fn_801D0444(), 0);
    fn_801D0544();
    if (_FieldMarker_ArrowTextureInfo.mUnknown0 == 1)
        GXLoadTlut(&_FieldMarker_ArrowTexture.mTlutObj, 0);
    GXLoadTexObj(&_FieldMarker_ArrowTexture.mTexObj, GX_TEXMAP0);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, gFieldMarkerArrowCount * 15);
    for (unsigned int i = 0; i < gFieldMarkerArrowCount; i++) {
        for (unsigned int j = 0; j < 15; j++) {
            float vertex[3];
            vertex[0] = gFieldMarkerArrows[i].mUnknownC * _FieldMarker_aArrowVerts[j][0];
            vertex[1] = gFieldMarkerArrows[i].mUnknownC * _FieldMarker_aArrowVerts[j][1];
            if (j > 5)
                vertex[2] = gFieldMarkerArrows[i].mUnknownC * _FieldMarker_aArrowVerts[j][2];
            else
                vertex[2] = _FieldMarker_aArrowVerts[j][2];
            fn_8022765C(vertex, vertex, gFieldMarkerArrows[i].mPosition);
            unsigned char alpha = (unsigned char)((unsigned int)color.a * gFieldMarkerArrows[i].mUnknown10);
            GXPosition3f32(vertex[0], vertex[1], vertex[2]);
            GXColor4u8(color.r, color.g, color.b, alpha);
            GXTexCoord2f32(_FieldMarker_aArrowUVs[j][0], _FieldMarker_aArrowUVs[j][1]);
        }
    }
    TMRenderSetBlendMode(1);
}

unsigned int FieldMarkerReadDepth(float x, float y)
{
    u32 depth = 0;
    if (x <= -1.0f || y <= -1.0f || x >= 1.0f || y >= 1.0f)
        return depth;
    unsigned short screenX = (unsigned short)((x + 1.0f) * fn_801CEA08() * 0.5f);
    unsigned short screenY = (unsigned short)((1.0f - y) * fn_801CEA14() * 0.5f);
    GXPeekZ(screenX, screenY, &depth);
    return depth;
}

}
