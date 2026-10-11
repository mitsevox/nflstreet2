#include "engine/cu_80227F14.h"
#include "game/Effects_80146134.h"
#include "game/Object_80146094.h"
#include "game/Object_8020E52C.h"
#include "game/fn_801EF390.h"
#include "game/fn_8007F828.h"
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>
#include <math.h>

extern "C" {
void fn_80210388(void);
void fn_8024D418(void);
void fn_8024CB90(int, int);
void fn_8024D450(int, int, int, int, int);
void fn_8024FC84(int, int, int, int, int, int, int);
void fn_8024FC48(int);
void fn_8024DF64(int);
void fn_8024DCE4(int, int, int, int, int, int);
void fn_80210BD8(int);
void fn_80251B28(int, int, int, int);
void fn_80251604(int, int);
void fn_80251CC4(int);
void fn_80251A58(int, int, int, int, int);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D131C(int);
void fn_801D12BC(int);
Mtx44Ptr fn_801D0444(void);
void fn_801D0F80(Mtx44);
void fn_8025251C(Mtx44, int);
void fn_802525BC(int);
void fn_802523A4(Mtx44, int);
void fn_802524D4(float *);
void fn_80252448(float *);
void fn_8024FB58(int, GXColor);
void fn_8022765C(void *, void *, void *);
float fn_80227704(void *, void *);
void fn_80227904(float *, float *, float *, float);
void fn_80227C2C(Vector_80146134 *, Vector_80146134 *);
void fn_80227E40(float *, float *);
float fn_80237260(int);
unsigned char fn_80147900(void);
Resource_80146E64 *fn_80146E64(int);
void fn_80146B40(Vector_80146134 *, Vector_80146134 *);
int fn_801CEB4C(void);
int fn_801CEC74(void);
int fn_801CEA14(void);
unsigned int fn_80198B24(float, float);
int fn_8020E51C(void *);
int fn_8020E524(void *);
void fn_8021239C(void *, void *, int, int, int, int, int, int);
void fn_80212534(void *, void *, int, int, int);
void fn_80212530(void *);
void fn_80212654(void *);
float fn_80197D08(float *, Vector_80146134 *);
extern unsigned char lbl_803EB750;
extern float lbl_803EB758[2];
extern GXTexObj lbl_803651B8;
extern GXTlutObj lbl_803651D8;
extern Color_802DD68C lbl_802DD72C[];
extern float lbl_802EDDF0[][2];
}

extern "C" {
void fn_80196F48(void *position, float scale)
{
    Vector_80146134 offset;
    Vector_80146134 vertex;
    unsigned char color[3] = {255, 125, 25};
    Vector_80146134 corners[4] = {
        {-3.0f, 3.0f, 0.15f}, {-3.0f, -3.0f, 0.15f},
        {3.0f, -3.0f, 0.15f}, {3.0f, 3.0f, 0.15f}
    };
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
    fn_80210BD8(6);
    fn_80251B28(0, 0, 0, 4);
    fn_80251604(0, 0);
    fn_80251CC4(1);
    fn_801D0470(fn_80228668());
    fn_801D0508();
    fn_801D131C(3);
    fn_8025251C(fn_801D0444(), 0);
    fn_801D0544();
    if (lbl_803EB750 == 1) GXLoadTlut(&lbl_803651D8, 0);
    GXLoadTexObj(&lbl_803651B8, GX_TEXMAP0);
    unsigned char alpha = (unsigned char)(((scale - 0.05f) * (0.0f - 255.0f)) / (3.0f - 0.05f) + 255.0f);
    for (unsigned char i = 0; i <= 3; ++i) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (unsigned char j = 0; j <= 3; ++j) {
            offset.x = corners[j].x * scale;
            offset.y = corners[j].y * scale;
            fn_8022765C(&vertex, position, &offset);
            GXPosition3f32(vertex.x, vertex.y, vertex.z);
            GXColor4u8(color[0], color[1], color[2], alpha);
            GXTexCoord2f32(lbl_802EDDF0[j][0], lbl_802EDDF0[j][1]);
        }
    }
    fn_80210BD8(1);
}

void fn_8019723C(Object_80146094 *p)
{
    if (!fn_80147900()) return;
    Mtx44 matrix;
    fn_80210388();
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024CB90(11, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_80251CC4(1);
    fn_80251B28(0, 255, 255, 4);
    fn_80251604(0, 4);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 1, 2, 1);
    fn_8024DF64(1);
    fn_8024DCE4(0, 0, 4, 60, 0, 125);
    fn_801D0F80(matrix);
    fn_802525BC(0);
    fn_8025251C(matrix, 0);
    if (p->mUnknown23C) fn_80210BD8(6);
    else fn_80210BD8(2);
    fn_80251A58(7, 0, 0, 7, 0);
    GXSetCullMode(GX_CULL_NONE);
    Color_802DD68C color = p->mUnknown240;
    for (unsigned int i = 0; i <= 3; ++i) {
        Trail_80146FDC *trail = &p->mTrails[i];
        if (trail->mCount > 1) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (unsigned short)(trail->mCount + 2));
            color.mUnknownC = p->mUnknown240.mUnknownC;
            GXColor rgba = {(unsigned char)(color.mUnknown0 * 255.0f),
                            (unsigned char)(color.mUnknown4 * 255.0f),
                            (unsigned char)(color.mUnknown8 * 255.0f),
                            (unsigned char)(color.mUnknownC * 255.0f)};
            Point_80146FDC *point = &trail->mSource[trail->mToggle];
            GXPosition3f32(point->x, point->y, point->z);
            GXColor4u8(rgba.r, rgba.g, rgba.b, rgba.a);
            point = &trail->mSource[!trail->mToggle];
            GXPosition3f32(point->x, point->y, point->z);
            GXColor4u8(rgba.r, rgba.g, rgba.b, rgba.a);
            for (unsigned int j = 0; j < trail->mCount; ++j) {
                if (p->mUnknown23C) {
                    color = lbl_802DD72C[j];
                    color.mUnknownC = (color.mUnknownC - j * (color.mUnknownC / trail->mCount)) * p->mUnknown230;
                } else {
                    float alpha = p->mUnknown240.mUnknownC;
                    color.mUnknownC = (alpha - j * (alpha / trail->mCount)) * p->mUnknown230;
                }
                point = &trail->mPoints[trail->mHead];
                GXPosition3f32(point->x, point->y, point->z);
                GXColor4u8((unsigned char)(color.mUnknown0 * 255.0f),
                           (unsigned char)(color.mUnknown4 * 255.0f),
                           (unsigned char)(color.mUnknown8 * 255.0f),
                           (unsigned char)(color.mUnknownC * 255.0f));
                trail->mHead = (trail->mHead + 1) % 8;
            }
        }
    }
    fn_8024D418();
    fn_80210BD8(1);
}

void fn_80197680(Entry_80146C4C *p)
{
    float projected[4];
    float saved[7];
    Vector_80146134 corners[4];
    Vector_80146134 facing;
    Vector_80146134 axis = {0.0f, 0.0f, -1.0f};
    Vector_80146134 position;
    Mtx44 projection;
    float screen[2], center[2];
    float angle = 1.0f;
    float size = 0.0f;
    fn_802524D4(saved);
    float visibility = fn_80197D08(projected, &p->mUnknown18);
    screen[0] = projected[0];
    screen[1] = projected[1];
    if (p->mUnknown4 == 1) {
        fn_801D0470(fn_80228668());
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
            Subrecord_80146134 *record = p->mUnknown0;
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
            Subrecord_80146134 *record;
            if (i == p->mUnknown36) {
                record = p->mUnknown0;
                fn_80227904(center, screen, lbl_803EB758, 1.0f);
            } else {
                Slot_80146A6C *slot = &((Slot_80146A6C *)p->mUnknown3C)[i];
                record = slot->mUnknown0;
                fn_80227904(center, screen, lbl_803EB758, slot->mUnknown4);
            }
            Resource_80146E64 *resource = fn_80146E64(record->mUnknown0);
            if (record->mUnknown0 != previous) {
                if (resource->mUnknown64) {
                    GXLoadTlut((GXTlutObj *)(resource->mUnknown3C + 4), 0);
                    GXInitTexObjTlut((GXTexObj *)resource->mUnknown10, 0);
                }
                GXLoadTexObj((GXTexObj *)resource->mUnknown10, GX_TEXMAP0);
            }
            previous = record->mUnknown0;
            switch (p->mUnknownC) {
            case 1:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
                break;
            case 2:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                break;
            default:
                GXSetZCompLoc(GX_DISABLE);
                GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_DISABLE);
                break;
            }
            size = (angle * 0.45f + 0.55f) * record->mUnknown4;
            float halfSize = size * 0.5f;
            if (p->mUnknown8 == 1 && i == p->mUnknown36) {
                fn_80252448(saved);
                fn_80146B40(&position, &p->mUnknown18);
                corners[3].x = position.x + halfSize;
                corners[3].y = position.y + halfSize;
                corners[3].z = position.z;
                corners[0].x = position.x - halfSize;
                corners[0].y = position.y - halfSize;
                corners[0].z = position.z;
                corners[1].x = position.x - halfSize;
                corners[1].y = position.y + halfSize;
                corners[1].z = position.z;
                corners[2].x = position.x + halfSize;
                corners[2].y = position.y - halfSize;
                corners[2].z = position.z;
            } else {
                C_MTXOrtho(projection, 240.0f, -240.0f, -320.0f, 320.0f, 1.0f, 1250.0f);
                projection[0][3] = projection[1][3] = projection[2][3] = 0.0f;
                fn_802523A4(projection, 1);
                center[0] *= 320.0f;
                center[1] *= 240.0f;
                corners[0].x = center[0] - size;
                corners[0].y = center[1] - size;
                corners[0].z = 250.0f;
                corners[1].x = center[0] - size;
                corners[1].y = center[1] + size;
                corners[1].z = 250.0f;
                corners[2].x = center[0] + size;
                corners[2].y = center[1] - size;
                corners[2].z = 250.0f;
                corners[3].x = center[0] + size;
                corners[3].y = center[1] + size;
                corners[3].z = 250.0f;
            }
            GXColor color = {(unsigned char)(record->mUnknown8 * 255.0f),
                             (unsigned char)(record->mUnknownC * 255.0f),
                             (unsigned char)(record->mUnknown10 * 255.0f),
                             (unsigned char)(alpha * 255.0f)};
            fn_8024FB58(4, color);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32(corners[0].x, corners[0].y, corners[0].z);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(corners[1].x, corners[1].y, corners[1].z);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(corners[2].x, corners[2].y, corners[2].z);
            GXTexCoord2f32(0.0f, 1.0f);
            GXPosition3f32(corners[3].x, corners[3].y, corners[3].z);
            GXTexCoord2f32(1.0f, 1.0f);
        }
    }
    fn_80252448(saved);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
}

float fn_80197D08(float *out, Vector_80146134 *position)
{
    float clip[4];
    float normalized[3];
    float point[4];
    float result;
    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D12BC(4);
    point[0] = position->x;
    point[1] = position->y;
    point[2] = position->z;
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

void fn_80197E6C(Resource_80146E64 *p)
{
    void *data = (void *)fn_801EF390(p->mUnknown0, p->mUnknown4, 1);
    p->mUnknown8 = (int)data;
    fn_8020E2B0(data);
    fn_8020E51C(data);
    int count = fn_8020E524(data);
    Object_8020E560 *image = fn_8020E560(data, 0);
    GXInvalidateTexAll();
    DCFlushRange(image->mpUnknownC, image->mWidth * image->mHeight * 4);
    fn_8021239C(p->mUnknown10, image->mpUnknownC, image->mWidth, image->mHeight, image->mFormat, 0, image->mWidth * image->mHeight * 4, 0);
    if (count > 0) {
        int entries = 16;
        if (image->mFormat == 9) entries = 256;
        Object_8020E5F8 *palette = fn_8020E5F8(data, 0);
        int bytes = entries + entries;
        DCFlushRange(palette->mpUnknown8, bytes);
        fn_80212534(p->mUnknown3C, palette->mpUnknown8, palette->mUnknown2, entries, bytes);
        p->mUnknown64 = 1;
    } else p->mUnknown64 = 0;
}

void fn_80197F84(Resource_80146E64 *p)
{
    fn_80212530(p->mUnknown10);
    if (p->mUnknown64) {
        fn_80212654(p->mUnknown3C);
        p->mUnknown64 = 0;
    }
    fn_801F010C(p->mUnknown0, p->mUnknown4);
}

void fn_80197FDC(void *unused, Entry_80146C4C *p)
{
    float projected[4];
    float visibility = fn_80197D08(projected, &p->mUnknown18);
    if (p->mUnknownC == 1) {
        float depth = projected[2] + 1.0f;
        depth = depth < 0.0f ? 0.0f : (depth > 1.0f ? 1.0f : depth);
        unsigned int value = (unsigned int)(depth * 16777215.0f);
        if (!(projected[0] <= -1.0f || projected[0] >= 1.0f || projected[1] <= -1.0f || projected[1] >= 1.0f)) {
            if (fn_8007F828(6) == 1 || fn_801CEB4C() == 1) {
                int height = fn_801CEC74();
                projected[1] *= (float)height / (float)fn_801CEA14();
            }
            if (value > fn_80198B24(projected[0], projected[1]) || !fn_80146BA8((Vector_80146134 *)projected)) p->mUnknown11 = 0;
            else p->mUnknown11 = 1;
        } else {
            p->mUnknown11 = 0;
        }
    } else if (p->mUnknownC == 0 || p->mUnknownC == 2) p->mUnknown11 = 1;
    if (visibility > 0.0f) fn_80197680(p);
    else p->mUnknown11 = 0;
}
}
