#include "engine/cu_80227F14.h"
#include <dolphin/gx/GXTransform.h>

extern int fn_801CE93C(void);
extern void fn_801CE910(void);
extern int fn_801CEA08(void);
extern int fn_801CEA14(void);
extern void fn_801CEA20(Mtx44 m);
extern float fn_801CFD28(int angle);
extern void fn_801D0424(void *p, Mtx44 m);
extern void fn_801D0470(int a);
extern void fn_801D04C4(void);
extern void fn_801D0508(void);
extern void fn_801D0544(void);
extern void fn_801D0664(Mtx44 m);
extern void fn_801D0F80(Mtx44 m);
extern void fn_801D1258(int a, Mtx44 m);
extern void fn_801D12BC(int a);
extern void fn_801D12EC(int a);
extern void fn_801D131C(int a);
extern int fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
extern void fn_801DD0E8(int handle);
extern int fn_801DD200(int handle, int b);
extern void fn_801DD2B8(int a);
extern void fn_801DD3F0(int handle);
extern int fn_801DD474(int handle, int b);
extern void fn_80210608(void);

static int lbl_803EBFA0 = 0;
static int lbl_803EBFA4 = 0;

int fn_802288F8(Init_802280B0 *pInit)
{
    if (pInit->mUnknown8) {
        lbl_803EBFA0 = fn_801DCFF0(1, pInit->mUnknown8, 0, 0, 0, 1, 3, 1);
    }
    return 0;
}

int fn_80228948(void)
{
    if (lbl_803EBFA0) {
        fn_801DD0E8(lbl_803EBFA0);
    }
    return 0;
}

int fn_80228978(Desc_80228224 *pDesc, Object_80228224 *pObject)
{
    return 0;
}

int fn_80228980(Object_80228224 *pObject)
{
    return 0;
}

void fn_80228988(Mtx44 m, float x, float y, float w, float h, float d)
{
    float sx = w * 0.5f, sy = h * 0.5f, sz = d * 0.5f;
    float tx = x + sx, ty = y + sy, nz = -sz;
    m[0][0] = sx;   m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
    m[0][1] = 0.0f; m[1][1] = sy;   m[2][1] = 0.0f; m[3][1] = 0.0f;
    m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = nz;   m[3][2] = 0.0f;
    m[0][3] = tx;   m[1][3] = ty;   m[2][3] = sz;   m[3][3] = 1.0f;
}

void fn_802289FC(Mtx44 m, float l, float r, float b, float t, float n, float f, float s)
{
    C_MTXFrustum(m, t, b, l, r, n, f);
}

void fn_80228A34(Mtx44 m, float l, float r, float b, float t, float n, float f)
{
    float a = 2.0f / (r - l), bb = 2.0f / (t - b), c = -2.0f / (f - n);
    m[0][0] = a;    m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
    m[0][1] = 0.0f; m[1][1] = bb;   m[2][1] = 0.0f; m[3][1] = 0.0f;
    m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = c;    m[3][2] = 0.0f;
    m[0][3] = -((r + l) / (r - l)); m[1][3] = -((t + b) / (t - b)); m[2][3] = -((f + n) / (f - n)); m[3][3] = 1.0f;
}

void fn_80228AD4(Mtx44 m, float fovy, float aspect, float n, float f)
{
    float t = n * fn_801CFD28((int)(fovy * 46603.379f) / 2);

    fn_802289FC(m, -t * aspect, t * aspect, -t, t, n, f, 1.0f);
}

void fn_80228B74(Object_80228224 *pObject)
{
    Mtx44 viewport;
    Mtx44 projection;
    Mtx44 m;
    float width = fn_801CEA08();
    float height = fn_801CEA14();
    float depth = (float)((1 << fn_801CE93C()) - 1) * 0.0625f;

    fn_80228988(viewport, pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown20, pObject->mUnknown24, depth);
    if (pObject->mUnknown28 & 4) {
        fn_80228A34(projection, pObject->mUnknown216, pObject->mUnknown220, pObject->mUnknown228,
                    pObject->mUnknown224, -pObject->mUnknown232, -pObject->mUnknown236);
    } else {
        fn_802289FC(projection, pObject->mUnknown216, pObject->mUnknown220, pObject->mUnknown228,
                    pObject->mUnknown224, pObject->mUnknown232, pObject->mUnknown236, pObject->mUnknown240);
    }
    fn_801D0424(pObject->mUnknown140, projection);
    fn_801CEA20(projection);
    GXSetViewport(pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown20, pObject->mUnknown24, 0.0f, 1.0f);
    fn_801D1258(2, projection);
    fn_801D1258(1, viewport);
    fn_801D0470(fn_80228668());
    fn_801D0F80(m);
    fn_801D0508();
    fn_801D0664(m);
    fn_801D12EC(3);
    fn_801D0544();
    fn_801D12BC(3);
    fn_801D04C4();
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D12EC(6);
    fn_801D12BC(1);
    fn_801D131C(2);
    fn_801D131C(3);
    fn_801D12EC(5);
    fn_801D12BC(2);
    fn_801D131C(3);
    fn_801D12EC(4);
    fn_801D0544();
    fn_802287D4(pObject);
    fn_80210608();
}

void fn_80228D58(int handle)
{
    if (lbl_803EBFA0) {
        if (fn_801DD474(lbl_803EBFA0, 0) == 0) {
            fn_80228E18();
        }
        if (fn_801DD200(lbl_803EBFA0, handle)) {
            fn_801DD2B8(handle);
        }
        lbl_803EBFA4 = 2;
    } else {
        fn_801DD2B8(handle);
    }
}

void fn_80228DD4(void)
{
    if (lbl_803EBFA0) {
        if (lbl_803EBFA4 <= 0) {
            fn_801DD3F0(lbl_803EBFA0);
        } else {
            lbl_803EBFA4--;
        }
    }
}

void fn_80228E18(void)
{
    fn_801CE910();
    fn_80228DD4();
    fn_80228DD4();
    fn_80228DD4();
}
