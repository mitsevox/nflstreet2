// Screen transitions: the timed fades between screens. A transition either
// fades a flat colour in or out over the picture (modes 5 and 6), or copies
// the last frame into a texture and fades it out (modes 1-4; modes 2-4
// compute grow, slide and shrink bounds that the draw does not use) or
// splits it apart (mode 7) while the next screen draws underneath. One
// transition runs at a time; each frame the update steps it and calls an
// optional notify callback with its progress.
#include <dolphin/gx/GXFrameBuffer.h>
#include "game/ScreenTransition.h"
#include "engine/viewport.h"
#include "game/GameOptions.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXCull.h>

struct ScreenTrans_t {
    int mMode;
    unsigned int mTicks, mDuration;
    Viewport_t *mpViewport;
    unsigned char mUnknown10[4];
    unsigned int mColor;
    float mAlpha, mSplitOffset;
    ScreenTransNotifyFn mpNotify;
};
typedef int (*ScreenTransModeFn)(ScreenTrans_t *, unsigned int, unsigned int);
extern "C" {
int _ScreenTransDissolve(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransGrow(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransSlide(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransShrink(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransFadeFromColor(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransFadeToColor(ScreenTrans_t *state, unsigned int event, unsigned int color);
int _ScreenTransSplit(ScreenTrans_t *state, unsigned int event, unsigned int color);

static ScreenTrans_t _ScreenTrans_State = {0};
static ScreenTransModeFn _ScreenTrans_apModeFns[8] = {
    0,
    _ScreenTransDissolve,
    _ScreenTransGrow,
    _ScreenTransSlide,
    _ScreenTransShrink,
    _ScreenTransFadeFromColor,
    _ScreenTransFadeToColor,
    _ScreenTransSplit,
};
static void *_ScreenTrans_pCapture = 0;
static Mtx44 _ScreenTrans_afSavedProjection;
static GXTexObj _ScreenTrans_TexObj;
static unsigned int _ScreenTrans_uOnceColor;
static float _ScreenTrans_fOnceAlpha;
static int _ScreenTrans_bDrawOnce;

void fn_801CEA44(int);
int fn_801CEC74(void);
void fn_8024FC48(int);
void fn_8024FB58(int, GXColor);
void fn_8024FC84(int, int, int, int, int, int, int);
void GXSetClipMode(int);
extern "C" void GXLoadTexObj(GXTexObj *, int);
void GXGetProjectionv(float *);
void GXSetProjection(Mtx44, int);
void fn_801D03D0(Mtx44);
void GXLoadPosMtxImm(Mtx44, int);
void GXSetCurrentMtx(int);
void *fn_801D2BB0(int, int, int, int);
extern "C" void GXInitTexObj(GXTexObj *, void *, int, int, int, int, int, int);
void _ScreenTransSetupDraw(int, unsigned int, float);
void _ScreenTransRestoreDraw(void);
void ScreenTransUpdate(void);
void ScreenTransFinish(void);
int ScreenTransCanCapture(int);

int _ScreenTransCaptureFrame(void) {
    if (!_ScreenTrans_pCapture)
        return 0;
    GXSetTexCopySrc(0, 0, 640, 448);
    GXSetTexCopyDst(320, 224, GX_TF_RGB565, GX_TRUE);
    GXSetCopyFilter(0, 0, 0, 0);
    GXCopyTex(_ScreenTrans_pCapture, 0);
    GXPixModeSync();
    fn_801CEA44(1);
    return 1;
}
void _ScreenTransDrawFrame(ScreenTrans_t *state, unsigned int mode) {
    float adjust = 0.0f, amount = 1.0f - state->mAlpha;
    int left = -320, lower = -224, upper = 224;
    switch (mode) {
    case 1:
    case 7:
        break;
    case 2:
        left = (int)((float)left + amount * (float)left);
        lower = (int)((float)lower + amount * (float)lower);
        upper = (int)((float)upper + amount * (float)upper);
        break;
    case 3:
        left = (int)((float)left + amount * 640.0f);
        break;
    case 4:
        left = (int)((float)left - amount * (float)left);
        lower = (int)((float)lower - amount * (float)lower);
        upper = (int)((float)upper - amount * (float)upper);
        break;
    default:
        break;
    }
    if (GameOptionsGet(6) == 1) {
        const float height = 448.0f;
        adjust = (float)((448 - fn_801CEC74()) / 2) / height;
    }
    if (_ScreenTrans_pCapture) {
        _ScreenTransSetupDraw(1, 0, state->mAlpha);
        if (mode == 7) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32((float)(left + 320) - state->mSplitOffset, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.0f, adjust);
            GXPosition3f32(320.0f - state->mSplitOffset, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.5f, adjust);
            GXPosition3f32((float)(left + 320) - state->mSplitOffset, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.0f, 1.0f - adjust);
            GXPosition3f32(320.0f - state->mSplitOffset, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.5f, 1.0f - adjust);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32(state->mSplitOffset + 320.0f, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.5f, adjust);
            GXPosition3f32(state->mSplitOffset + 640.0f, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(1.0f, adjust);
            GXPosition3f32(state->mSplitOffset + 320.0f, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.5f, 1.0f - adjust);
            GXPosition3f32(state->mSplitOffset + 640.0f, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(1.0f, 1.0f - adjust);
        } else {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 0.0f, -1.0f);
            GXTexCoord2f32(0.0f, adjust);
            GXPosition3f32(640.0f, 0.0f, -1.0f);
            GXTexCoord2f32(1.0f, adjust);
            GXPosition3f32(0.0f, 448.0f, -1.0f);
            GXTexCoord2f32(0.0f, 1.0f - adjust);
            GXPosition3f32(640.0f, 448.0f, -1.0f);
            GXTexCoord2f32(1.0f, 1.0f - adjust);
        }
        _ScreenTransRestoreDraw();
    }
}
void _ScreenTransDrawColor(unsigned int color, float alpha) {
    _ScreenTransSetupDraw(0, color, alpha);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -1.0f);
    GXPosition3f32(640.0f, 0.0f, -1.0f);
    GXPosition3f32(0.0f, 448.0f, -1.0f);
    GXPosition3f32(640.0f, 448.0f, -1.0f);
    _ScreenTransRestoreDraw();
}
int _ScreenTransFadeFromColor(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        break;
    case 2:
        _ScreenTransDrawColor(color, state->mAlpha);
        break;
    case 1:
        state->mAlpha = 1.0f - (float)state->mTicks / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransFadeToColor(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        break;
    case 2:
        _ScreenTransDrawColor(color, state->mAlpha);
        break;
    case 1:
        state->mAlpha = (float)(state->mTicks + 1) / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransDissolve(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!_ScreenTransCaptureFrame())
            return 0;
        break;
    case 2:
        _ScreenTransDrawFrame(state, 1);
        break;
    case 1:
        state->mAlpha = 1.0f - (float)state->mTicks / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransGrow(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!_ScreenTransCaptureFrame())
            return 0;
        break;
    case 2:
        _ScreenTransDrawFrame(state, 2);
        break;
    case 1:
        state->mAlpha = 1.0f - (float)state->mTicks / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransSlide(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!_ScreenTransCaptureFrame())
            return 0;
        break;
    case 2:
        _ScreenTransDrawFrame(state, 3);
        break;
    case 1:
        state->mAlpha = 1.0f - (float)state->mTicks / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransShrink(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!_ScreenTransCaptureFrame())
            return 0;
        break;
    case 2:
        _ScreenTransDrawFrame(state, 4);
        break;
    case 1:
        state->mAlpha = 1.0f - (float)state->mTicks / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
int _ScreenTransSplit(ScreenTrans_t *state, unsigned int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!_ScreenTransCaptureFrame())
            return 0;
        break;
    case 2:
        _ScreenTransDrawFrame(state, 7);
        break;
    case 1:
        state->mAlpha = 1.0f;
        state->mSplitOffset = (float)state->mTicks * 320.0f / (float)state->mDuration;
        break;
    case 3:
        state->mMode = 0;
        break;
    default:
        break;
    }
    return 1;
}
void _ScreenTransSetupDraw(int textured, unsigned int value, float alpha) {
    Mtx44 view, projection;
    GXColor color = {0, 0, 0, 255};
    if (textured) {
        color.b = color.g = color.r = 255;
    } else {
        unsigned int red = (value & 255) * 2;
        unsigned int green = ((value >> 8) & 255) * 2;
        unsigned int blue = ((value >> 16) & 255) * 2;
        color.r = red > 255 ? 255 : red;
        color.g = green > 255 ? 255 : green;
        color.b = blue > 255 ? 255 : blue;
    }
    color.a = (int)(alpha * 255.0f);
    fn_8024FC48(1);
    fn_8024FB58(4, color);
    fn_8024FC84(4, 0, 0, 0, 1, 0, 2);
    if (textured) {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 4);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetCullMode(GX_CULL_NONE);
        GXSetClipMode(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXLoadTexObj(&_ScreenTrans_TexObj, 0);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumTexGens(0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 4);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetCullMode(GX_CULL_NONE);
        GXSetClipMode(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
    GXGetProjectionv(_ScreenTrans_afSavedProjection[0]);
    C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    GXSetProjection(projection, 1);
    fn_801D03D0(view);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
}
void _ScreenTransRestoreDraw(void) {
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    GXSetProjection(_ScreenTrans_afSavedProjection, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetClipMode(0);
}
void _ScreenTransDrawCallback(Viewport_t *) {
    ScreenTransModeFn callback = _ScreenTrans_apModeFns[_ScreenTrans_State.mMode];
    if (callback)
        callback(&_ScreenTrans_State, 2, _ScreenTrans_State.mColor);
}
void _ScreenTransDrawOnceCallback(Viewport_t *) {
    ScreenTrans_t *state = &_ScreenTrans_State;
    _ScreenTransDrawColor(_ScreenTrans_uOnceColor, _ScreenTrans_fOnceAlpha);
    VptRemoveCallback(state->mpViewport, _ScreenTransDrawOnceCallback);
}
void ScreenTransStart(int mode, unsigned int duration, unsigned int color, void (*notify)(int, float)) {
    ScreenTransFinish();
    switch (mode) {
    case 5:
    case 6:
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        if (!ScreenTransCanCapture(0x23000))
            return;
        break;
    }
    _ScreenTrans_State.mMode = mode;
    _ScreenTrans_State.mTicks = 0;
    _ScreenTrans_State.mDuration = duration;
    _ScreenTrans_State.mColor = color;
    _ScreenTrans_State.mpNotify = notify;
}
void ScreenTransUpdate(void) {
    ScreenTrans_t *state = &_ScreenTrans_State;
    if (_ScreenTrans_bDrawOnce) {
        VptSetCallback(state->mpViewport, 2, _ScreenTransDrawOnceCallback, 0);
        _ScreenTrans_bDrawOnce = 0;
    }
    ScreenTransModeFn callback = _ScreenTrans_apModeFns[state->mMode];
    if (callback) {
        if (!state->mTicks) {
            if (!callback(state, 0, state->mColor)) {
                state->mMode = 0;
                return;
            }
            if (state->mpNotify)
                state->mpNotify(0, 0.0f);
            VptSetCallback(state->mpViewport, 2, _ScreenTransDrawCallback, 0);
        }
        if (state->mTicks < state->mDuration) {
            callback(state, 1, state->mColor);
            if (state->mpNotify)
                state->mpNotify(1, (float)state->mTicks / (float)state->mDuration);
            ++state->mTicks;
        } else {
            VptRemoveCallback(state->mpViewport, _ScreenTransDrawCallback);
            callback(state, 3, state->mColor);
            if (state->mpNotify)
                state->mpNotify(3, 1.0f);
        }
    }
}
void ScreenTransFinish(void) {
    if (_ScreenTrans_State.mMode) {
        _ScreenTrans_State.mTicks = _ScreenTrans_State.mDuration;
        ScreenTransUpdate();
    }
    _ScreenTrans_bDrawOnce = 0;
}
void ScreenTransInit(Viewport_t *object) {
    _ScreenTrans_State.mTicks = 0;
    _ScreenTrans_State.mDuration = 0;
    _ScreenTrans_State.mpViewport = object;
    _ScreenTrans_State.mMode = 0;
    _ScreenTrans_bDrawOnce = 0;
    if (!_ScreenTrans_pCapture) {
        _ScreenTrans_pCapture = fn_801D2BB0(1, 0x23000, 0, 0);
        GXInitTexObj(&_ScreenTrans_TexObj, _ScreenTrans_pCapture, 320, 224, 4, 0, 0, 0);
    }
}
void ScreenTransShutdown(void) {
    ScreenTransFinish();
    if (_ScreenTrans_pCapture) {
        fn_801D2BD0(_ScreenTrans_pCapture);
        _ScreenTrans_pCapture = 0;
    }
}
int ScreenTransCanCapture(int size) {
    return _ScreenTrans_pCapture && size <= 0x23000;
}
int ScreenTransGetMode(void) {
    return _ScreenTrans_State.mMode;
}
int ScreenTransIsActive(void) {
    return ScreenTransGetMode() != 0 && _ScreenTrans_State.mTicks < _ScreenTrans_State.mDuration;
}
}
