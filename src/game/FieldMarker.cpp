/* Draws on-field markers: groups of translucent beams at fixed spots and small arrows over chosen
   positions, plus a Z-buffer read used to test whether an effect is hidden behind scenery. */
#include "engine/cu_80227F14.h"
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/mtx.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/gx/GXTev.h>

struct Entry_80146C4C;

struct FieldMarkerBeam_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    unsigned char mUnknownC[8];
};

struct FieldMarkerBeamSet_t {
    float mPosition[3];
    float mUnknownC;
    FieldMarkerBeam_t mUnknown10[3];
};

struct FieldMarkerArrow_t {
    float mPosition[3];
    float mUnknownC;
    float mUnknown10;
    unsigned char mUnknown14[4];
};

extern "C" {
void fn_80210388(void);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_8024FC48(int a);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_801D0470(int a);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D131C(int a);
Mtx44Ptr fn_801D0444(void);
void fn_8025251C(Mtx44 m, int a);
void fn_80227490(float *pOut, float *pIn, int a, int b, int c);
void fn_8022765C(float *pOut, float *pA, float *pB);
int fn_801CEA08(void);
int fn_801CEA14(void);

extern FieldMarkerBeamSet_t lbl_802DD7AC[15];
extern unsigned char lbl_803EB760;
extern unsigned char lbl_803EB768;
extern GXTexObj lbl_80365220;
extern GXTlutObj lbl_80365240;
extern GXTexObj lbl_8036526C;
extern GXTlutObj lbl_8036528C;
extern FieldMarkerArrow_t *lbl_803EB284;
extern unsigned int lbl_803ECA18;
}

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

void FieldMarkerInitEffect(Entry_80146C4C *p)
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
    fn_80210388();
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
    fn_80210BD8(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
    fn_801D0470(fn_80228668());
    fn_801D0508();
    fn_801D131C(3);
    fn_8025251C(fn_801D0444(), 0);
    fn_801D0544();
    if (lbl_803EB760 == 1)
        GXLoadTlut(&lbl_80365240, 0);
    GXLoadTexObj(&lbl_80365220, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 180);
    for (unsigned int i = 0; i < 15; i++) {
        FieldMarkerBeamSet_t *record = &lbl_802DD7AC[i];
        for (unsigned int j = 0; j < 3; j++) {
            _FieldMarkerDrawBeam(&record->mUnknown10[j], record->mPosition,
                        (int)(record->mUnknownC * 46603.379f));
        }
    }
    fn_80210BD8(1);
}

void FieldMarkerDrawArrows(void)
{
    GXColor color = {128, 128, 128, 128};
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
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    fn_80210BD8(6);
    GXSetNumTevStages(1);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    fn_80210CC4(0.0f, 0.9999f);
    fn_801D0470(fn_80228668());
    fn_801D0508();
    fn_801D131C(3);
    fn_8025251C(fn_801D0444(), 0);
    fn_801D0544();
    if (lbl_803EB768 == 1)
        GXLoadTlut(&lbl_8036528C, 0);
    GXLoadTexObj(&lbl_8036526C, GX_TEXMAP0);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, lbl_803ECA18 * 15);
    for (unsigned int i = 0; i < lbl_803ECA18; i++) {
        for (unsigned int j = 0; j < 15; j++) {
            float vertex[3];
            vertex[0] = lbl_803EB284[i].mUnknownC * _FieldMarker_aArrowVerts[j][0];
            vertex[1] = lbl_803EB284[i].mUnknownC * _FieldMarker_aArrowVerts[j][1];
            if (j > 5)
                vertex[2] = lbl_803EB284[i].mUnknownC * _FieldMarker_aArrowVerts[j][2];
            else
                vertex[2] = _FieldMarker_aArrowVerts[j][2];
            fn_8022765C(vertex, vertex, lbl_803EB284[i].mPosition);
            unsigned char alpha = (unsigned char)((unsigned int)color.a * lbl_803EB284[i].mUnknown10);
            GXPosition3f32(vertex[0], vertex[1], vertex[2]);
            GXColor4u8(color.r, color.g, color.b, alpha);
            GXTexCoord2f32(_FieldMarker_aArrowUVs[j][0], _FieldMarker_aArrowUVs[j][1]);
        }
    }
    fn_80210BD8(1);
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
