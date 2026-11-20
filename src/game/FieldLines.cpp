/* Field lines: five textured strips drawn across the field at yard positions
   (object type 17). Each frame the update places them from the field getters
   and fades them in or out; the list callback draws each visible strip with a
   pulsing alpha and keeps a minimum on-screen size. */
#include "game/fn_8022781C.h"
#include "game/fn_80177FE0.h"
#include "game/cu_8002B8F8.h"
#include "game/PauseMenu.h"
#include "game/fn_800AD9B4.h"
#include "game/ResLoad.h"
#include "engine/viewport.h"
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXPixel.h>

/* The pool allocates 0x128 bytes. Only observed fields are exposed. */
struct FieldLine_t {
    char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    char mUnknown10[0xC8];
    float mUnknownD8;
    float mUnknownDC;
    float mUnknownE0;
    float mUnknownE4;
    float mUnknownE8;
    float mUnknownEC;
    float mUnknownF0;
    int mUnknownF4;
    char mUnknownF8[0x28];
    int mUnknown120;
    int mUnknown124;
};

/* Projection writes two three-component bounds with 16-byte stride. */
struct FieldLineBounds_t {
    Vector_80039F5C mUnknown0;
    char mUnknownC[4];
    Vector_80039F5C mUnknown10;
    char mUnknown1C[4];
};

extern "C" {
unsigned char fn_8002D060(Type_803EA368 *p);
int fn_800BA6F8(void);
void *fn_800C47C4(void);
int fn_80177F70(void);
Point_8017886C fn_80177FFC(int team);
float fn_80178298(void);
int fn_80178320(void);
int fn_801784C4(void);
float fn_80178A08(void);
float fn_80178A2C(void);
int fn_801486A0(void);
void MatPush(void);
void MatPop(void);
void MatTranslate(void *p);
void MatStore(float (*pMatrix)[4]);
int ObjNewType_(int type, int size, int count, void (*a)(FieldLine_t *), void (*b)(FieldLine_t *));
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*callback)(FieldLine_t *));
FieldLine_t *ObjNewInList(int handle, int type, int a, int *pInit);
void ObjRemoveFromList(int handle, FieldLine_t *p);
void ObjSetPriority(int handle, FieldLine_t *p, int a);
void TMRenderReset(void);
void TMRenderBindTexture(int a, int b, int c);
void TMRenderSetZRange(float a, float b);
void TMTexLibLoad(void *p, int a);
void TMTexLibUnload(void *p);
int TMTexLibGetTexture(void *p, unsigned int key);
int TMTexLibGetClut(void *p, unsigned int key, int a);
void fn_80234D00(FieldLineBounds_t *pIn, FieldLineBounds_t *pOut);
int fn_80236EC0(int a);
void GXSetChanMatColor(int a, GXColor color);
void GXSetNumChans(int a);
void GXSetChanCtrl(int a, int b, int c, int d, int e, int f, int g);
void GXLoadPosMtxImm(float (*matrix)[4], int a);
void GXSetCurrentMtx(int a);

/* Projected by FieldLineGetScale: a vertical segment of +-0.55556 (the factor of the vertex code) around the line position. */
static FieldLineBounds_t _FieldLines_ProjBounds = {{0.0f, -0.55556f, 0.0f}, {0, 0, 0, 0}, {0.0f, 0.55556f, 0.0f}, {0, 0, 0, 0}};
static float _FieldLines_fHeight = 0.72f;
static int _FieldLines_iObjList;
static unsigned char _FieldLines_abForceOn[5];
static unsigned char _FieldLines_abDrawEnable[5];
static FieldLine_t *_FieldLines_apLines[5];

float FieldLineGetScale(FieldLine_t *p)
{
    FieldLineBounds_t bounds;
    float extra = 0.0f;
    MatPush();
    MatTranslate(&p->mUnknown4);
    fn_80234D00(&_FieldLines_ProjBounds, &bounds);
    float distance = fn_8022781C(&bounds.mUnknown10, &bounds.mUnknown0);
    MatPop();
    if (distance < 0.08f) {
        float ratio = 0.08f / distance;
        if (!(ratio < 1.0f)) {
            extra = ((ratio > 20.0f ? 20.0f : ratio) - 1.0f) * 0.5f;
        }
    }
    return extra + 1.0f;
}

int FieldLineDraw(FieldLine_t *p)
{
    if (fn_80177F70() && !fn_800BA6F8() && !fn_8002D060(lbl_803EA368) &&
        _FieldLines_abDrawEnable[p->mUnknownF4] == 1 && !PauseIsOpen() && fn_800AD9B4() != 7) {
        float zero = 0.0f;
        if (p->mUnknownE4 > zero) {
            float scale = FieldLineGetScale(p);
            float matrix[4][4];
            TMRenderReset();
            int state = fn_80236EC0(0);
            GXSetCullMode(GX_CULL_NONE);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            GXSetZCompLoc(GX_FALSE);
            GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            TMRenderSetZRange(zero, 1.0f);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetChanMatColor(4, (GXColor){(unsigned char)(int)(p->mUnknownD8 * 255.0f), (unsigned char)(int)(p->mUnknownDC * 255.0f),
                             (unsigned char)(int)(p->mUnknownE0 * 255.0f), (unsigned char)(int)(p->mUnknownE4 * 255.0f)});
            GXSetNumChans(1);
            GXSetChanCtrl(4, 0, 0, 0, 1, 2, 1);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
            GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            TMRenderBindTexture(0, p->mUnknown120, p->mUnknown124);
            MatPush();
            MatTranslate(&p->mUnknown4);
            MatStore(matrix);
            GXLoadPosMtxImm(matrix, 0);
            GXSetCurrentMtx(0);
            MatPop();
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            {
                float x = fn_80178A08();
                float y = (1.0f - _FieldLines_fHeight) * 0.55556f;
                GXPosition3f32(x, scale * y, zero);
            }
            GXTexCoord2f32(0.9f, 1.0f - _FieldLines_fHeight * 0.5f);
            {
                float x = fn_80178A08();
                float y = (1.0f - _FieldLines_fHeight) * -0.55556f;
                GXPosition3f32(x, scale * y, zero);
            }
            GXTexCoord2f32(0.9f, _FieldLines_fHeight * 0.5f);
            {
                float x = -fn_80178A08();
                float y = (1.0f - _FieldLines_fHeight) * 0.55556f;
                GXPosition3f32(x, scale * y, zero);
            }
            GXTexCoord2f32(0.1f, 1.0f - _FieldLines_fHeight * 0.5f);
            {
                float x = -fn_80178A08();
                float y = (1.0f - _FieldLines_fHeight) * -0.55556f;
                GXPosition3f32(x, scale * y, zero);
            }
            GXTexCoord2f32(0.1f, _FieldLines_fHeight * 0.5f);
            fn_80236EC0(state);
        }
        p->mUnknownE4 += p->mUnknownE8;
        if ((p->mUnknownE8 > zero && p->mUnknownE4 > p->mUnknownF0) ||
            (p->mUnknownE8 < zero && p->mUnknownE4 < p->mUnknownEC)) {
            p->mUnknownE8 = -p->mUnknownE8;
        }
    }
    return 0;
}

void FieldLineSetVisible(FieldLine_t *p, int enabled)
{
    if (enabled) {
        p->mUnknownEC = 0.5f;
        p->mUnknownF0 = 0.8f;
    } else {
        p->mUnknownEC = -0.1f;
        p->mUnknownE4 = 0.0f;
        p->mUnknownF0 = -0.1f;
    }
}

void FieldLinesCreate(int handle)
{
    _FieldLines_iObjList = handle;
    ObjNewType_(17, 0x128, 5, 0, 0);
    ObjSetListObjFunc(_FieldLines_iObjList, 17, 0, FieldLineDraw);
    for (unsigned int i = 0; i <= 4; ++i) {
        _FieldLines_abDrawEnable[i] = 1;
        FieldLine_t *p = ObjNewInList(_FieldLines_iObjList, 17, 0, 0);
        _FieldLines_apLines[i] = p;
        switch (i) {
        case 0:
            p->mUnknownD8 = 1.0f;
            p->mUnknownDC = 1.0f;
            p->mUnknownE0 = 0.0f;
            break;
        case 1:
            p->mUnknownD8 = 1.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 0.0f;
            break;
        case 2:
            p->mUnknownD8 = 1.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 0.0f;
            break;
        case 3:
            p->mUnknownD8 = 0.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 1.0f;
            break;
        case 4:
            p->mUnknownD8 = 0.0f;
            p->mUnknownDC = 0.0f;
            p->mUnknownE0 = 1.0f;
            break;
        }

        p->mUnknownF4 = i;
        p->mUnknownE8 = 0.005f;
        p->mUnknownE4 = 0.0f;
        p->mUnknownEC = 0.0f;
        p->mUnknownF0 = 0.0f;
        _FieldLines_abForceOn[i] = 0;
        TMTexLibLoad(p->mUnknownF8, ResLoad(fn_800C47C4(), 17, 1));
        p->mUnknown120 = TMTexLibGetTexture(p->mUnknownF8, 0xFF000000);
        p->mUnknown124 = TMTexLibGetClut(p->mUnknownF8, 0xFF000000, 0);
        ObjSetPriority(handle, p, 3);
    }
}

void FieldLinesDestroy(void)
{
    for (unsigned int i = 0; i <= 4; ++i) {
        TMTexLibUnload(_FieldLines_apLines[i]->mUnknownF8);
        ObjRemoveFromList(_FieldLines_iObjList, _FieldLines_apLines[i]);
        VptTrashObject((int)_FieldLines_apLines[i]);
        _FieldLines_apLines[i] = 0;
    }
    VptFlushObjectTrashSync();
    ObjDelType(17);
    _FieldLines_iObjList = 0;
}

// FAKEMATCH: an inline compare helper; inlined at RTL level its bound stays `>= 2` (a direct `mode >= 2` folds to `> 1`).
static inline int AtLeast(int value, int lo)
{
    return value >= lo;
}

void FieldLinesUpdate(void)
{
    for (unsigned int i = 0; i <= 4; ++i) {
        FieldLine_t *p = _FieldLines_apLines[i];
        // FAKEMATCH: enabled is reused for the range gate and then the readiness result (keeps it in r28 across the calls)
        int enabled = 0;
        int mode = fn_800AD9B4();
        if (mode <= 3) {
            enabled = AtLeast(mode, 2);
        }
        int ready = 0;
        if (enabled && fn_80177F70() && !fn_800BA6F8()) {
            ready = !fn_8002D060(lbl_803EA368);
        }
        enabled = ready;
        // FAKEMATCH: each case writes y through a local copy qN of the line pointer, loaded before the getter calls
        switch ((unsigned int)p->mUnknownF4) {
        case 0: {
            _FieldLines_apLines[i]->mUnknown4.mX = 0.0f;
            FieldLine_t *q0 = _FieldLines_apLines[i];
            q0->mUnknown4.mY = fn_801784C4() ? -fn_80178298() : fn_80178298();
            _FieldLines_apLines[i]->mUnknown4.mZ = 0.0f;
            if (!(fn_80178298() < fn_80178A2C()) || !(fn_80178298() > -fn_80178A2C())) {
                enabled = 0;
            }
            break;
        }
        case 1: {
            _FieldLines_apLines[i]->mUnknown4.mX = 0.0f;
            FieldLine_t *q1 = _FieldLines_apLines[i];
            q1->mUnknown4.mY = fn_801784C4() ? -fn_80178A2C() : fn_80178A2C();
            _FieldLines_apLines[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 2: {
            _FieldLines_apLines[i]->mUnknown4.mX = 0.0f;
            FieldLine_t *q2 = _FieldLines_apLines[i];
            q2->mUnknown4.mY = fn_801784C4() ? fn_80178A2C() : -fn_80178A2C();
            _FieldLines_apLines[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 3: {
            _FieldLines_apLines[i]->mUnknown4.mX = 0.0f;
            FieldLine_t *q3 = _FieldLines_apLines[i];
            q3->mUnknown4.mY = fn_801784C4() ? -fn_80177FE0().mY : fn_80177FE0().mY;
            _FieldLines_apLines[i]->mUnknown4.mZ = 0.0f;
            break;
        }
        case 4: {
            _FieldLines_apLines[i]->mUnknown4.mX = 0.0f;
            FieldLine_t *q4 = _FieldLines_apLines[i];
            q4->mUnknown4.mY = fn_801784C4() ? -fn_80177FFC(fn_80178320()).mY : fn_80177FFC(fn_80178320()).mY;
            _FieldLines_apLines[i]->mUnknown4.mZ = 0.0f;
            if (fn_800AD9B4() != 2) {
                enabled = 0;
            }
            switch (fn_801486A0()) {
            case 3:
            case 4:
                break;
            default:
                enabled = 0;
                break;
            }
            break;
        }
        }
        if (_FieldLines_abForceOn[p->mUnknownF4]) {
            enabled = 1;
        }
        FieldLineSetVisible(p, enabled);
    }
}

void FieldLinesEnable(unsigned char enabled)
{
    for (unsigned char i = 0; i <= 4; ++i) {
        _FieldLines_abDrawEnable[i] = enabled;
    }
}
}
