/*
 * GameCube side of the viewports: builds a viewport's viewport, perspective and orthographic
 * matrices, loads them into GX with the viewport rectangle and scissor before the viewport is drawn,
 * and keeps the object trash can, a list of render objects whose deletion is put off for a couple of
 * frames until the GPU has finished with them.
 */
#include <dolphin/mtx.h>
#include "engine/viewport.h"
#include <dolphin/gx/GXTransform.h>
#include "engine/llglib.h"
#include "engine/llmatrix.h"

extern void fn_801CEC48(int a, int b, int c, int d);
extern float fn_801CFD28(int angle);
extern int ObjNewList(int a, int b, int c, int d, int e, int f, int g, int h);
extern void ObjDelList(int handle);
extern int ObjAddToList(int handle, int b);
extern void ObjDel(int a);
extern void ObjClearList(int handle);
extern int ObjGetListInfo(int handle, int b);
extern void TMRenderBeginViewport(void);

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
        _Vpt_pTrashCan = ObjNewList(1, pInit->mUnknown8, 0, 0, 0, 1, 3, 1);
    }
    return 0;
}

int VptLLShutdown(void)
{
    if (_Vpt_pTrashCan) {
        ObjDelList(_Vpt_pTrashCan);
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
    TMRenderBeginViewport();
}

void VptTrashObject(int handle)
{
    if (_Vpt_pTrashCan) {
        if (ObjGetListInfo(_Vpt_pTrashCan, 0) == 0) {
            VptFlushObjectTrashSync();
        }
        if (ObjAddToList(_Vpt_pTrashCan, handle)) {
            ObjDel(handle);
        }
        _Vpt_TrashLatency = 2;
    } else {
        ObjDel(handle);
    }
}

void VptFlushObjectTrash(void)
{
    if (_Vpt_pTrashCan) {
        if (_Vpt_TrashLatency <= 0) {
            ObjClearList(_Vpt_pTrashCan);
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
