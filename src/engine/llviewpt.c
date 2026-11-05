/*
 * GameCube side of the viewports: builds a viewport's viewport, perspective and orthographic
 * matrices, loads them into GX with the viewport rectangle and scissor before the viewport is drawn,
 * and keeps the object trash can, a list of render objects whose deletion is put off for a couple of
 * frames until the GPU has finished with them. Also sets up the VRAM block table at start-up.
 */
#include <dolphin/mtx.h>
#include "engine/viewport.h"
#include <dolphin/gx/GXTransform.h>
#include "engine/llglib.h"
#include "engine/llmatrix.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

extern void fn_801CEC48(int a, int b, int c, int d);
extern float fn_801CFD28(int angle);
extern int fn_801DCFF0(int a, int b, int c, int d, int e, int f, int g, int h);
extern void fn_801DD0E8(int handle);
extern int fn_801DD200(int handle, int b);
extern void fn_801DD2B8(int a);
extern void fn_801DD3F0(int handle);
extern int fn_801DD474(int handle, int b);
extern void fn_80210608(void);

static int _Vpt_pTrashCan = 0;
static int _Vpt_TrashLatency = 0;

static void _VptSetupScissor(Viewport_t *pObject)
{
    fn_801CEC48((unsigned int)pObject->mUnknown4, (unsigned int)pObject->mUnknown20,
                (unsigned int)pObject->mUnknown8, (unsigned int)pObject->mUnknown24);
}

int VptLLInit(VptInitBlock_t *pInit)
{
    if (pInit->mUnknown8) {
        _Vpt_pTrashCan = fn_801DCFF0(1, pInit->mUnknown8, 0, 0, 0, 1, 3, 1);
    }
    return 0;
}

int VptLLShutdown(void)
{
    if (_Vpt_pTrashCan) {
        fn_801DD0E8(_Vpt_pTrashCan);
    }
    return 0;
}

int VptLLOpen(ViewportDesc_t *pDesc, Viewport_t *pObject)
{
    return 0;
}

int VptLLClose(Viewport_t *pObject)
{
    return 0;
}

void VptViewport(Mtx44 m, float x, float y, float w, float h, float d)
{
    float sx = w * 0.5f, sy = h * 0.5f, sz = d * 0.5f;
    float tx = x + sx, ty = y + sy;
    m[0][0] = sx;   m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
    m[0][1] = 0.0f; m[1][1] = sy;   m[2][1] = 0.0f; m[3][1] = 0.0f;
    m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = -sz;  m[3][2] = 0.0f;
    m[0][3] = tx;   m[1][3] = ty;   m[2][3] = sz;   m[3][3] = 1.0f;
}

void VptFrustum(Mtx44 m, float l, float r, float b, float t, float n, float f, float s)
{
    C_MTXFrustum(m, t, b, l, r, n, f);
}

void VptOrtho(Mtx44 m, float l, float r, float b, float t, float n, float f)
{
    float a = 2.0f / (r - l), bb = 2.0f / (t - b), c = -2.0f / (f - n);
    m[0][0] = a;    m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
    m[0][1] = 0.0f; m[1][1] = bb;   m[2][1] = 0.0f; m[3][1] = 0.0f;
    m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = c;    m[3][2] = 0.0f;
    m[0][3] = -((r + l) / (r - l)); m[1][3] = -((t + b) / (t - b)); m[2][3] = -((f + n) / (f - n)); m[3][3] = 1.0f;
}

void VptPerspective(Mtx44 m, float fovy, float aspect, float n, float f)
{
    float t = n * fn_801CFD28((int)(fovy * 46603.379f) / 2);

    VptFrustum(m, -t * aspect, t * aspect, -t, t, n, f, 1.0f);
}

void VptSetUpRender(Viewport_t *pObject)
{
    Mtx44 viewport;
    Mtx44 projection;
    Mtx44 m;
    float width = fn_801CEA08();
    float height = fn_801CEA14();
    float depth = (float)((1 << fn_801CE93C()) - 1) * 0.0625f;

    VptViewport(viewport, pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown20, pObject->mUnknown24, depth);
    if (pObject->mUnknown28 & 4) {
        VptOrtho(projection, pObject->mUnknown216, pObject->mUnknown220, pObject->mUnknown228,
                    pObject->mUnknown224, -pObject->mUnknown232, -pObject->mUnknown236);
    } else {
        VptFrustum(projection, pObject->mUnknown216, pObject->mUnknown220, pObject->mUnknown228,
                    pObject->mUnknown224, pObject->mUnknown232, pObject->mUnknown236, pObject->mUnknown240);
    }
    fn_801D0424((float *)pObject->mUnknown140, projection[0]);
    fn_801CEA20(projection);
    GXSetViewport(pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown20, pObject->mUnknown24, 0.0f, 1.0f);
    fn_801D1258(2, projection[0]);
    fn_801D1258(1, viewport[0]);
    fn_801D0470(VptGetMatrixStack());
    fn_801D0F80(m[0]);
    fn_801D0508();
    fn_801D0664(m[0]);
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
    _VptSetupScissor(pObject);
    fn_80210608();
}

void VptTrashObject(int handle)
{
    if (_Vpt_pTrashCan) {
        if (fn_801DD474(_Vpt_pTrashCan, 0) == 0) {
            VptFlushObjectTrashSync();
        }
        if (fn_801DD200(_Vpt_pTrashCan, handle)) {
            fn_801DD2B8(handle);
        }
        _Vpt_TrashLatency = 2;
    } else {
        fn_801DD2B8(handle);
    }
}

void VptFlushObjectTrash(void)
{
    if (_Vpt_pTrashCan) {
        if (_Vpt_TrashLatency <= 0) {
            fn_801DD3F0(_Vpt_pTrashCan);
        } else {
            _Vpt_TrashLatency--;
        }
    }
}

void VptFlushObjectTrashSync(void)
{
    fn_801CE910();
    VptFlushObjectTrash();
    VptFlushObjectTrash();
    VptFlushObjectTrash();
}

/* 28-byte pool entry; only the byte at +8 is written here. */
typedef struct VramBlock_t {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9[19];
} VramBlock_t;

static unsigned short _Vram_MaxBlocks = 0;
static VramBlock_t *_Vram_Blocks = 0;
static int _Vram_NextHandle = -1;
static unsigned char _Vram_ModuleActive = 0;

int VramInit(VramInitBlock_t *pDesc)
{
    int err = 0;
    unsigned int i;

    if (_Vram_ModuleActive == 0) {
        _Vram_MaxBlocks = pDesc->mUnknown0;
        _Vram_NextHandle = err;
        _Vram_Blocks = fn_801D2BB0(1, _Vram_MaxBlocks * sizeof(VramBlock_t), 0, 0);
        if (_Vram_Blocks == 0) {
            err = fn_801F7C88();
        } else {
            for (i = 0; i < _Vram_MaxBlocks; i++) {
                _Vram_Blocks[i].mUnknown8 = 0xFF;
            }
            _Vram_ModuleActive = 1;
        }
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int VramShutdown(void)
{
    int err = 0;

    if (_Vram_ModuleActive) {
        _Vram_NextHandle = -1;
        _Vram_MaxBlocks = 0;
        fn_801D2BD0(_Vram_Blocks);
        _Vram_ModuleActive = 0;
        _Vram_Blocks = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}
