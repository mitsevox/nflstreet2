#include "engine/viewport.h"
#include "game/Glow.h"
#include "game/ParticleTrail.h"
#include "engine/texfile.h"
#include "game/ResLoad.h"
#include "game/GameOptions.h"
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>
#include <math.h>

extern "C" {
void TMRenderReset(void);
void TMRenderSetBlendMode(int);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D131C(int);
void fn_801D12BC(int);
Mtx44Ptr fn_801D0444(void);
void fn_801D0F80(Mtx44);
void GXSetProjection(Mtx44, int);
void GXGetProjectionv(float *);
void fn_8022765C(void *, void *, void *);
float fn_80227704(void *, void *);
void fn_80227904(float *, float *, float *, float);
void fn_80227C2C(Vector_80039F5C *, Vector_80039F5C *);
void fn_80227E40(float *, float *);
float fn_80237260(int);
unsigned char ParticleTrailIsEnabled(void);
GlowTexture_t *GlowGetTexture(int);
void GlowTransformPoint(Vector_80039F5C *, Vector_80039F5C *);
int fn_801CEB4C(void);
int fn_801CEC74(void);
int fn_801CEA14(void);
unsigned int FieldMarkerReadDepth(float, float);
int TexGetNumMaterials(void *);
int TexGetNumPalettes(void *);
void TMTextureTexNew(void *, void *, int, int, int, int, int, int);
void TMTextureClutNew(void *, void *, int, int, int);
void TMTextureTexDelete(void *);
void TMTextureClutDelete(void *);
float fn_80197D08(float *, Vector_80039F5C *);
extern unsigned char lbl_803EB750;
extern float lbl_803EB758[2];
extern GXTexObj lbl_803651B8;
extern GXTlutObj lbl_803651D8;
extern ParticleTrailColor_t gParticleTrail_aPointColors[];
extern float lbl_802EDDF0[][2];
}

static inline float _FxRemap(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

extern "C" {
void fn_80196F48(float scale, void *position)
{
    Vector_80039F5C offset;
    Vector_80039F5C vertex;
    unsigned char color[3] = {255, 125, 25};
    Vector_80039F5C corners[4] = {
        {-3.0f, 3.0f, 0.15f}, {-3.0f, -3.0f, 0.15f},
        {3.0f, -3.0f, 0.15f}, {3.0f, 3.0f, 0.15f}
    };
    TMRenderReset();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    TMRenderSetBlendMode(6);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);
    fn_801D0470(VptGetMatrixStack());
    fn_801D0508();
    fn_801D131C(3);
    GXLoadPosMtxImm(fn_801D0444(), 0);
    fn_801D0544();
    if (lbl_803EB750 == 1) GXLoadTlut(&lbl_803651D8, 0);
    GXLoadTexObj(&lbl_803651B8, GX_TEXMAP0);
    unsigned char alpha = (unsigned char)_FxRemap(scale, 0.05f, 3.0f, 255.0f, 0.0f);
    for (unsigned char i = 0; i <= 3; ++i) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (unsigned char j = 0; j <= 3; ++j) {
            offset.mX = corners[j].mX * scale;
            offset.mY = corners[j].mY * scale;
            fn_8022765C(&vertex, position, &offset);
            GXPosition3f32(vertex.mX, vertex.mY, vertex.mZ);
            GXColor4u8(color[0], color[1], color[2], alpha);
            GXTexCoord2f32(lbl_802EDDF0[j][0], lbl_802EDDF0[j][1]);
        }
    }
    TMRenderSetBlendMode(1);
}

void fn_8019723C(ParticleTrailSet_t *p)
{
    if (!ParticleTrailIsEnabled()) return;
    ParticleTrailColor_t color;
    Mtx44 matrix;
    TMRenderReset();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    fn_801D0F80(matrix);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(matrix, 0);
    if (p->mUnknown23C) TMRenderSetBlendMode(6);
    else TMRenderSetBlendMode(2);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    color = p->mUnknown240;
    for (unsigned int i = 0; i <= 3; ++i) {
        ParticleTrail_t *trail = &p->mTrails[i];
        if (trail->mCount > 1) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (unsigned short)(trail->mCount + 2));
            color.mUnknownC = p->mUnknown240.mUnknownC;
            unsigned char r = (unsigned char)(color.mUnknown0 * 255.0f);
            unsigned char g = (unsigned char)(color.mUnknown4 * 255.0f);
            unsigned char b = (unsigned char)(color.mUnknown8 * 255.0f);
            unsigned char a = (unsigned char)(color.mUnknownC * 255.0f);
            int toggle = trail->mToggle;
            int other = !toggle;
            GXPosition3f32(trail->mSource[toggle].mX, trail->mSource[toggle].mY, trail->mSource[toggle].mZ);
            GXColor4u8(r, g, b, a);
            GXPosition3f32(trail->mSource[other].mX, trail->mSource[other].mY, trail->mSource[other].mZ);
            GXColor4u8(r, g, b, a);
            for (unsigned int j = 0; j < trail->mCount; ++j) {
                if (p->mUnknown23C) {
                    ParticleTrailColor_t *entry = &gParticleTrail_aPointColors[j];
                    color.mUnknown0 = entry->mUnknown0;
                    color.mUnknown4 = entry->mUnknown4;
                    color.mUnknown8 = entry->mUnknown8;
                    color.mUnknownC = (entry->mUnknownC - j * (entry->mUnknownC / trail->mCount)) * p->mUnknown230;
                } else {
                    float alpha = p->mUnknown240.mUnknownC;
                    color.mUnknownC = (alpha - j * (alpha / trail->mCount)) * p->mUnknown230;
                }
                GXPosition3f32(trail->mPoints[trail->mHead].mX, trail->mPoints[trail->mHead].mY, trail->mPoints[trail->mHead].mZ);
                GXColor4u8((unsigned char)(color.mUnknown0 * 255.0f),
                           (unsigned char)(color.mUnknown4 * 255.0f),
                           (unsigned char)(color.mUnknown8 * 255.0f),
                           (unsigned char)(color.mUnknownC * 255.0f));
                trail->mHead++;
                trail->mHead %= 8;
            }
        }
    }
    GXClearVtxDesc();
    TMRenderSetBlendMode(1);
}

static inline void _FxPosition(Vector_80039F5C *v)
{
    GXPosition3f32(v->mX, v->mY, v->mZ);
}

void fn_80197680(Glow_t *p)
{
    float projected[4];
    float saved[7];
    Vector_80039F5C corners[4];
    Vector_80039F5C facing;
    Vector_80039F5C axis = {0.0f, 0.0f, -1.0f};
    Vector_80039F5C position;
    Mtx44 projection;
    float screen[2], center[2];
    float angle = 1.0f;
    float size = 0.0f;
    GXGetProjectionv(saved);
    float visibility = fn_80197D08(projected, &p->mUnknown18);
    screen[0] = projected[0];
    screen[1] = projected[1];
    if (p->mUnknown4 == 1) {
        fn_801D0470(VptGetMatrixStack());
        fn_801D04C4();
        fn_801D12BC(3);
        fn_80227C2C(&facing, &p->mUnknown24);
        angle = fn_80227704(&facing, &axis);
        if (angle < 0.0f) angle = 0.0f;
        fn_801D0544();
    }
    if (p->mUnknown34) {
        if (++p->mUnknown35 >= p->mUnknown34) {
            p->mUnknown35 = 0;
            GlowElement_t *record = p->mUnknown0;
            float value = fn_80237260(1) * (p->mUnknown30 + p->mUnknown30) - p->mUnknown30 + 1.0f;
            if (value > p->mUnknown0->mUnknown14) value = p->mUnknown0->mUnknown14;
            else value = fn_80237260(1) * (p->mUnknown30 + p->mUnknown30) - p->mUnknown30 + 1.0f;
            record->mUnknown14 = value;
        }
    }
    if (p->mUnknown11) p->mUnknown14 += p->mUnknown38;
    else p->mUnknown14 -= p->mUnknown38;
    p->mUnknown14 = p->mUnknown14 < 0.0f ? 0.0f : (p->mUnknown14 > 1.0f ? 1.0f : p->mUnknown14);
    if (p->mUnknown14 != 0.0f) {
        float alpha = p->mUnknown0->mUnknown14 * (angle * 0.95f + 0.050000011920928955f) * visibility * p->mUnknown14;
        alpha = alpha < 0.0f ? 0.0f : (alpha > 1.0f ? 1.0f : alpha);
        int previous = -1;
        for (unsigned int i = 0; i <= p->mUnknown36; ++i) {
            GlowElement_t *record;
            if (i == p->mUnknown36) {
                record = p->mUnknown0;
                fn_80227904(center, screen, lbl_803EB758, 1.0f);
            } else {
                record = p->mUnknown3C[i].mUnknown0;
                fn_80227904(center, screen, lbl_803EB758, p->mUnknown3C[i].mUnknown4);
            }
            GlowTexImage_t *image = &GlowGetTexture(record->mUnknown0)->mUnknown10;
            if (record->mUnknown0 != previous) {
                if (image->mUnknown54) {
                    GXLoadTlut((GXTlutObj *)(image->mUnknown2C + 4), 0);
                    GXInitTexObjTlut((GXTexObj *)image->mUnknown0, 0);
                }
                GXLoadTexObj((GXTexObj *)image->mUnknown0, GX_TEXMAP0);
            }
            previous = record->mUnknown0;
            switch (p->mUnknownC) {
            case 2:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                break;
            case 1:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
                break;
            default:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
                break;
            }
            size = (angle * 0.45f + 0.55f) * record->mUnknown4;
            float halfSize = size * 0.5f;
            if (p->mUnknown8 == 1 && i == p->mUnknown36) {
                GXSetProjectionv(saved);
                GlowTransformPoint(&position, &p->mUnknown18);
                corners[3].mX = position.mX + halfSize;
                corners[3].mY = position.mY + halfSize;
                corners[3].mZ = position.mZ;
                corners[0].mX = position.mX - halfSize;
                corners[0].mY = position.mY - halfSize;
                corners[0].mZ = position.mZ;
                corners[1].mX = position.mX - halfSize;
                corners[1].mY = position.mY + halfSize;
                corners[1].mZ = position.mZ;
                corners[2].mX = position.mX + halfSize;
                corners[2].mY = position.mY - halfSize;
                corners[2].mZ = position.mZ;
            } else {
                C_MTXOrtho(projection, 240.0f, -240.0f, -320.0f, 320.0f, 1.0f, 1250.0f);
                projection[0][3] = 0.0f;
                projection[1][3] = 0.0f;
                projection[2][3] = 0.0f;
                GXSetProjection(projection, 1);
                center[0] *= 320.0f;
                center[1] *= 240.0f;
                corners[0].mX = center[0] - size;
                corners[0].mY = center[1] - size;
                corners[0].mZ = 250.0f;
                corners[1].mX = center[0] - size;
                corners[1].mY = center[1] + size;
                corners[1].mZ = 250.0f;
                corners[2].mX = center[0] + size;
                corners[2].mY = center[1] - size;
                corners[2].mZ = 250.0f;
                corners[3].mX = center[0] + size;
                corners[3].mY = center[1] + size;
                corners[3].mZ = 250.0f;
            }
            GXColor color;
            color.r = (unsigned char)(record->mUnknown8 * 255.0f);
            color.g = (unsigned char)(record->mUnknownC * 255.0f);
            color.b = (unsigned char)(record->mUnknown10 * 255.0f);
            color.a = (unsigned char)(alpha * 255.0f);
            GXSetChanMatColor(GX_COLOR0A0, color);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            _FxPosition(&corners[0]);
            GXTexCoord2f32(0.0f, 0.0f);
            _FxPosition(&corners[1]);
            GXTexCoord2f32(1.0f, 0.0f);
            _FxPosition(&corners[2]);
            GXTexCoord2f32(0.0f, 1.0f);
            _FxPosition(&corners[3]);
            GXTexCoord2f32(1.0f, 1.0f);
        }
    }
    GXSetProjectionv(saved);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
}

float fn_80197D08(float *out, Vector_80039F5C *position)
{
    float clip[4];
    float normalized[3];
    float point[4];
    float result;
    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D12BC(4);
    point[0] = position->mX;
    point[1] = position->mY;
    point[2] = position->mZ;
    point[3] = result = 1.0f;
    fn_80227E40(clip, point);
    float reciprocal = 1.0f / clip[3];
    normalized[0] = clip[0] * reciprocal;
    normalized[1] = clip[1] * reciprocal;
    normalized[2] = clip[2];
    if (!(normalized[2] < -clip[3] || normalized[0] < -2.5f || normalized[0] > 2.5f || normalized[1] < -2.5f || normalized[1] > 2.5f)) {
        normalized[2] *= reciprocal;
        out[0] = normalized[0];
        out[1] = normalized[1];
        out[2] = normalized[2];
        out[3] = 1.0f;
        float x = fabsf(normalized[0]);
        float y = fabsf(normalized[1]);
        if (x > y) {
            if (!(x < 1.3f)) result = 1.0f - (x - 1.3f) * 0.8333333134651184f;
        } else {
            if (!(y < 1.3f)) result = 1.0f - (y - 1.3f) * 0.8333333134651184f;
        }
    } else {
        result = 0.0f;
    }
    fn_801D0544();
    return result;
}

void fn_80197E64(void) {}
void fn_80197E68(void) {}

void fn_80197E6C(GlowTexture_t *p)
{
    GlowTexImage_t *texture = &p->mUnknown10;
    void *data = (void *)ResLoad(p->mUnknown0, p->mUnknown4, 1);
    p->mUnknown8 = (int)data;
    TexMipmapRelocate(data);
    TexGetNumMaterials(data);
    int count = TexGetNumPalettes(data);
    TexFileImage_t *image = TexGetTextureByIndex(data, 0);
    GXInvalidateTexAll();
    DCFlushRange(image->mpUnknownC, image->mWidth * image->mHeight * 4);
    TMTextureTexNew(texture->mUnknown0, image->mpUnknownC, image->mWidth, image->mHeight, image->mFormat, 0, image->mWidth * image->mHeight * 4, 0);
    if (count > 0) {
        int entries = 16;
        if (image->mFormat == 9) entries = 256;
        TexFilePalette_t *palette = TexGetPaletteByIndex(data, 0);
        int bytes = entries + entries;
        DCFlushRange(palette->mpUnknown8, bytes);
        TMTextureClutNew(p->mUnknown10.mUnknown2C, palette->mpUnknown8, palette->mUnknown2, entries, bytes);
        texture->mUnknown54 = 1;
    } else texture->mUnknown54 = 0;
}

void fn_80197F84(GlowTexture_t *p)
{
    TMTextureTexDelete(p->mUnknown10.mUnknown0);
    if (p->mUnknown10.mUnknown54) {
        TMTextureClutDelete(p->mUnknown10.mUnknown2C);
        p->mUnknown10.mUnknown54 = 0;
    }
    ResUnLoad(p->mUnknown0, p->mUnknown4);
}

void fn_80197FDC(void *unused, Glow_t *p)
{
    float projected[4];
    float visibility = fn_80197D08(projected, &p->mUnknown18);
    if (p->mUnknownC == 1) {
        float depth = projected[2] + 1.0f;
        depth = depth < 0.0f ? 0.0f : (depth > 1.0f ? 1.0f : depth);
        unsigned int value = (unsigned int)(depth * 16777215.0f);
        if (!(projected[0] <= -1.0f || projected[0] >= 1.0f || projected[1] <= -1.0f || projected[1] >= 1.0f)) {
            if (GameOptionsGet(6) == 1 || fn_801CEB4C() == 1) {
                int height = fn_801CEC74();
                projected[1] *= (float)height / (float)fn_801CEA14();
            }
            if (value > FieldMarkerReadDepth(projected[0], projected[1]) || !GlowIsOnScreen((Vector_80039F5C *)projected)) p->mUnknown11 = 0;
            else p->mUnknown11 = 1;
        } else {
            p->mUnknown11 = 0;
        }
    } else if (p->mUnknownC == 0 || p->mUnknownC == 2) p->mUnknown11 = 1;
    if (visibility > 0.0f) fn_80197680(p);
    else p->mUnknown11 = 0;
}
}
