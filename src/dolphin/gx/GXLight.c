#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

extern float cosf(float x);
#include <math.h>

// GXLightObj private data
typedef struct
{
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} __GXLightObjInt_struct;

void GXInitLightAttn(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(130, "GXInitLightAttn");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightAttnA(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(144, "GXInitLightAttnA");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func)
{
    f32 a0, a1, a2;
    f32 r;
    f32 d;
    f32 cr;
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(200, "GXInitLightSpot");

    if (cutoff <= 0.0f || cutoff > 90.0f)
        spot_func = GX_SP_OFF;

    r = (3.1415927f * cutoff) / 180.0f;
    cr = cosf(r);

    switch (spot_func)
    {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a1 = 1.0f / (1.0f - cr);
        a0 = -cr * a1;
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a2 = 1.0f / (1.0f - cr);
        a0 = 0.0f;
        a1 = -cr * a2;
        break;
    case GX_SP_SHARP:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = (cr * (cr - 2.0f)) * d;
        a1 = 2.0f * d;
        a2 = -d;
        break;
    case GX_SP_RING1:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a2 = -4.0f * d;
        a0 = a2 * cr;
        a1 = (4.0f * (1.0f + cr)) * d;
        break;
    case GX_SP_RING2:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = 1.0f - ((2.0f * cr * cr) * d);
        a1 = (4.0f * cr) * d;
        a2 = -2.0f * d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXInitLightDistAttn(GXLightObj* lt_obj, f32 ref_dist, f32 ref_br, GXDistAttnFn dist_func)
{
    f32 k0, k1, k2;
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(275, "GXInitLightDistAttn");

    if (ref_dist < 0.0f)
        dist_func = GX_DA_OFF;
    if (ref_br <= 0.0f || ref_br >= 1.0f)
        dist_func = GX_DA_OFF;

    switch (dist_func)
    {
    case GX_DA_GENTLE:
        k0 = 1.0f;
        k1 = (1.0f - ref_br) / (ref_br * ref_dist);
        k2 = 0.0f;
        break;
    case GX_DA_MEDIUM:
        k0 = 1.0f;
        k1 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist);
        k2 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_STEEP:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = (1.0f - ref_br) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_OFF:
    default:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = 0.0f;
        break;
    }

    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(330, "GXInitLightPos");

    obj->lpos[0] = x;
    obj->lpos[1] = y;
    obj->lpos[2] = z;
}

void GXInitLightDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;

    obj->ldir[0] = -nx;
    obj->ldir[1] = -ny;
    obj->ldir[2] = -nz;
}

void GXInitSpecularDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz) {
    f32 mag;
    f32 vx;
    f32 vy;
    f32 vz;
    __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(398, lt_obj != NULL, "Light Object Pointer is null");
    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(399, "GXInitSpecularDir");

    vx = -nx;
    vy = -ny;
    vz = -nz + 1.0f;

    mag = (vx * vx) + (vy * vy) + (vz * vz);
    if (mag != 0.0f) {
        mag = 1.0f / sqrtf(mag);
    }

    obj->ldir[0] = vx * mag;
    obj->ldir[1] = vy * mag;
    obj->ldir[2] = vz * mag;
    obj->lpos[0] = nx * -1000000000000000000.0f;
    obj->lpos[1] = ny * -1000000000000000000.0f;
    obj->lpos[2] = nz * -1000000000000000000.0f;
}


void GXInitLightColor(GXLightObj* lt_obj, GXColor color)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(463, "GXInitLightColor");

    *(u32*)&obj->Color = *(u32*)&color;
}

void GXGetLightColor(const GXLightObj* lt_obj, GXColor* color) {
    __GXLightObjInt_struct* obj;

    ASSERTMSGLINE(476, lt_obj != NULL, "Light Object Pointer is null");
    obj = (__GXLightObjInt_struct*)lt_obj;
    CHECK_GXBEGIN(477, "GXGetLightColor");

    *(u32*)color = *(u32*)&obj->Color;
}
