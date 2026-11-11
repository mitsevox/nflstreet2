// Screen transitions: the timed fades between screens. A transition either
// fades a flat colour in or out over the picture, or copies the last frame
// into a texture and dissolves, wipes or splits it away while the next
// screen draws underneath. One transition runs at a time; each frame the
// update steps it and calls an optional notify callback with its progress.
#include <dolphin/gx/GXFrameBuffer.h>
#include "game/ScreenTransition.h"
#include "engine/viewport.h"
#include "game/fn_8007F828.h"
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
    int mUnknown0;
    unsigned int mUnknown4, mUnknown8;
    Viewport_t *mUnknownC;
    unsigned char mUnknown10[4];
    unsigned int mUnknown14;
    float mUnknown18, mUnknown1C;
    void (*mUnknown20)(int, float);
};
typedef int (*ScreenTransModeFn)(ScreenTrans_t *, unsigned int, unsigned int);
extern "C" {
extern ScreenTrans_t lbl_802EDCD0;
extern ScreenTransModeFn lbl_802EDCF4[];
extern void *lbl_803EB738;
extern Mtx44 lbl_80365128;
extern GXTexObj lbl_80365168;
extern unsigned int lbl_803ECBB0;
extern float lbl_803ECBB4;
extern int lbl_803ECBB8;
void fn_801CEA44(int);
int fn_801CEC74(void);
void fn_8024FC48(int);
void fn_8024FB58(int, GXColor);
void fn_8024FC84(int, int, int, int, int, int, int);
void fn_802528B0(int);
extern "C" void GXLoadTexObj(GXTexObj *, int);
void fn_802524D4(float *);
void fn_802523A4(Mtx44, int);
void fn_801D03D0(Mtx44);
void fn_8025251C(Mtx44, int);
void fn_802525BC(int);
void *fn_801D2BB0(int, int, int, int);
extern "C" void GXInitTexObj(GXTexObj *, void *, int, int, int, int, int, int);
void _ScreenTransSetupDraw(int, unsigned int, float);
void _ScreenTransRestoreDraw(void);
void ScreenTransUpdate(void);
void ScreenTransFinish(void);
int ScreenTransCanCapture(int);

int _ScreenTransCaptureFrame(void) {
    if (!lbl_803EB738)
        return 0;
    GXSetTexCopySrc(0, 0, 640, 448);
    GXSetTexCopyDst(320, 224, GX_TF_RGB565, GX_TRUE);
    GXSetCopyFilter(0, 0, 0, 0);
    GXCopyTex(lbl_803EB738, 0);
    GXPixModeSync();
    fn_801CEA44(1);
    return 1;
}
void _ScreenTransDrawFrame(ScreenTrans_t *state, unsigned int mode) {
    float adjust = 0.0f, amount = 1.0f - state->mUnknown18;
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
    if (fn_8007F828(6) == 1) {
        const float height = 448.0f;
        adjust = (float)((448 - fn_801CEC74()) / 2) / height;
    }
    if (lbl_803EB738) {
        _ScreenTransSetupDraw(1, 0, state->mUnknown18);
        if (mode == 7) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32((float)(left + 320) - state->mUnknown1C, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.0f, adjust);
            GXPosition3f32(320.0f - state->mUnknown1C, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.5f, adjust);
            GXPosition3f32((float)(left + 320) - state->mUnknown1C, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.0f, 1.0f - adjust);
            GXPosition3f32(320.0f - state->mUnknown1C, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.5f, 1.0f - adjust);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32(state->mUnknown1C + 320.0f, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(0.5f, adjust);
            GXPosition3f32(state->mUnknown1C + 640.0f, (float)(lower + 224), -1.0f);
            GXTexCoord2f32(1.0f, adjust);
            GXPosition3f32(state->mUnknown1C + 320.0f, (float)(upper + 224), -1.0f);
            GXTexCoord2f32(0.5f, 1.0f - adjust);
            GXPosition3f32(state->mUnknown1C + 640.0f, (float)(upper + 224), -1.0f);
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
        _ScreenTransDrawColor(color, state->mUnknown18);
        break;
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        _ScreenTransDrawColor(color, state->mUnknown18);
        break;
    case 1:
        state->mUnknown18 = (float)(state->mUnknown4 + 1) / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        state->mUnknown18 = 1.0f;
        state->mUnknown1C = (float)state->mUnknown4 * 320.0f / (float)state->mUnknown8;
        break;
    case 3:
        state->mUnknown0 = 0;
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
        fn_802528B0(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXLoadTexObj(&lbl_80365168, 0);
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
        fn_802528B0(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
    fn_802524D4(lbl_80365128[0]);
    C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    fn_802523A4(projection, 1);
    fn_801D03D0(view);
    fn_8025251C(view, 0);
    fn_802525BC(0);
}
void _ScreenTransRestoreDraw(void) {
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    fn_802523A4(lbl_80365128, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    fn_802528B0(0);
}
void _ScreenTransDrawCallback(Viewport_t *) {
    ScreenTransModeFn callback = lbl_802EDCF4[lbl_802EDCD0.mUnknown0];
    if (callback)
        callback(&lbl_802EDCD0, 2, lbl_802EDCD0.mUnknown14);
}
void _ScreenTransDrawOnceCallback(Viewport_t *) {
    ScreenTrans_t *state = &lbl_802EDCD0;
    _ScreenTransDrawColor(lbl_803ECBB0, lbl_803ECBB4);
    VptRemoveCallback(state->mUnknownC, _ScreenTransDrawOnceCallback);
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
    lbl_802EDCD0.mUnknown0 = mode;
    lbl_802EDCD0.mUnknown4 = 0;
    lbl_802EDCD0.mUnknown8 = duration;
    lbl_802EDCD0.mUnknown14 = color;
    lbl_802EDCD0.mUnknown20 = notify;
}
void ScreenTransUpdate(void) {
    ScreenTrans_t *state = &lbl_802EDCD0;
    if (lbl_803ECBB8) {
        VptSetCallback(state->mUnknownC, 2, _ScreenTransDrawOnceCallback, 0);
        lbl_803ECBB8 = 0;
    }
    ScreenTransModeFn callback = lbl_802EDCF4[state->mUnknown0];
    if (callback) {
        if (!state->mUnknown4) {
            if (!callback(state, 0, state->mUnknown14)) {
                state->mUnknown0 = 0;
                return;
            }
            if (state->mUnknown20)
                state->mUnknown20(0, 0.0f);
            VptSetCallback(state->mUnknownC, 2, _ScreenTransDrawCallback, 0);
        }
        if (state->mUnknown4 < state->mUnknown8) {
            callback(state, 1, state->mUnknown14);
            if (state->mUnknown20)
                state->mUnknown20(1, (float)state->mUnknown4 / (float)state->mUnknown8);
            ++state->mUnknown4;
        } else {
            VptRemoveCallback(state->mUnknownC, _ScreenTransDrawCallback);
            callback(state, 3, state->mUnknown14);
            if (state->mUnknown20)
                state->mUnknown20(3, 1.0f);
        }
    }
}
void ScreenTransFinish(void) {
    if (lbl_802EDCD0.mUnknown0) {
        lbl_802EDCD0.mUnknown4 = lbl_802EDCD0.mUnknown8;
        ScreenTransUpdate();
    }
    lbl_803ECBB8 = 0;
}
void ScreenTransInit(Viewport_t *object) {
    lbl_802EDCD0.mUnknown4 = 0;
    lbl_802EDCD0.mUnknown8 = 0;
    lbl_802EDCD0.mUnknownC = object;
    lbl_802EDCD0.mUnknown0 = 0;
    lbl_803ECBB8 = 0;
    if (!lbl_803EB738) {
        lbl_803EB738 = fn_801D2BB0(1, 0x23000, 0, 0);
        GXInitTexObj(&lbl_80365168, lbl_803EB738, 320, 224, 4, 0, 0, 0);
    }
}
void ScreenTransShutdown(void) {
    ScreenTransFinish();
    if (lbl_803EB738) {
        fn_801D2BD0(lbl_803EB738);
        lbl_803EB738 = 0;
    }
}
int ScreenTransCanCapture(int size) {
    return lbl_803EB738 && size <= 0x23000;
}
int ScreenTransGetMode(void) {
    return lbl_802EDCD0.mUnknown0;
}
int ScreenTransIsActive(void) {
    return ScreenTransGetMode() != 0 && lbl_802EDCD0.mUnknown4 < lbl_802EDCD0.mUnknown8;
}
}
