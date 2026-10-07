#include "engine/cu_80227F14.h"
#include "game/fn_8007F828.h"
#include "game/fn_801D2B7C.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXVert.h>

struct State_80194FE8 {
    int mUnknown0;
    unsigned int mUnknown4, mUnknown8;
    Object_80228224 *mUnknownC;
    unsigned char mUnknown10[4];
    unsigned int mUnknown14;
    float mUnknown18, mUnknown1C;
    void (*mUnknown20)(int, float);
};
typedef int (*Callback_80195E64)(State_80194FE8 *, int, unsigned int);
extern "C" {
extern State_80194FE8 lbl_802EDCD0;
extern Callback_80195E64 lbl_802EDCF4[];
extern void *lbl_803EB738;
extern Mtx44 lbl_80365128;
extern GXTexObj lbl_80365168;
extern unsigned int lbl_803ECBB0;
extern float lbl_803ECBB4;
extern int lbl_803ECBB8;
void fn_8024ED60(int, int, int, int);
void fn_8024EE10(int, int, int, int);
void fn_8024F100(int, int, int, int);
void fn_8024F484(void *, int);
void fn_8024E4D0(void);
void fn_801CEA44(int);
int fn_801CEC74(void);
void fn_8024FC48(int);
void fn_8024FB58(int, GXColor);
void fn_8024FC84(int, int, int, int, int, int, int);
void fn_80251CC4(int);
void fn_80251B28(int, int, int, int);
void fn_80251604(int, int);
void fn_8024DF64(int);
void fn_8024DCE4(int, int, int, int, int, int);
void fn_8024D418(void);
void fn_8024CB90(int, int);
void fn_8024D450(int, int, int, int, int);
void fn_802520E0(int, int, int);
void fn_8024EB28(int);
void fn_802528B0(int);
void fn_80252034(int, int, int, int);
void fn_802505A8(GXTexObj *, int);
void fn_802524D4(float *);
void fn_8024AC28(Mtx44, float, float, float, float, float, float);
void fn_802523A4(Mtx44, int);
void fn_801D03D0(Mtx44);
void fn_8025251C(Mtx44, int);
void fn_802525BC(int);
void *fn_801D2BB0(int, int, int, int);
void fn_8024FFC4(GXTexObj *, void *, int, int, int, int, int, int);
void fn_80195B28(int, unsigned int, float);
void fn_80195E0C(void);
void fn_80195F80(void);
void fn_80196130(void);
int fn_8019623C(int);

int fn_80194FE8(void) {
    if (!lbl_803EB738)
        return 0;
    fn_8024ED60(0, 0, 640, 448);
    fn_8024EE10(320, 224, 4, 1);
    fn_8024F100(0, 0, 0, 0);
    fn_8024F484(lbl_803EB738, 0);
    fn_8024E4D0();
    fn_801CEA44(1);
    return 1;
}
void fn_80195068(State_80194FE8 *state, int mode) {
    float adjust = 0.0f, amount = 1.0f - state->mUnknown18;
    int left = -320, lower = -224, upper = 224;
    switch (mode) {
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
    if (fn_8007F828(6) == 1)
        adjust = (float)((448 - fn_801CEC74()) / 2) * 0.002232143f;
    if (lbl_803EB738) {
        fn_80195B28(1, 0, state->mUnknown18);
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
        fn_80195E0C();
    }
}
void fn_80195558(unsigned int color, float alpha) {
    fn_80195B28(0, color, alpha);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -1.0f);
    GXPosition3f32(640.0f, 0.0f, -1.0f);
    GXPosition3f32(0.0f, 448.0f, -1.0f);
    GXPosition3f32(640.0f, 448.0f, -1.0f);
    fn_80195E0C();
}
int fn_801955E8(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195558(color, state->mUnknown18);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_8019569C(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 1:
        state->mUnknown18 = (float)(state->mUnknown4 + 1) / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195558(color, state->mUnknown18);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_80195748(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!fn_80194FE8())
            return 0;
        break;
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195068(state, 1);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_8019580C(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!fn_80194FE8())
            return 0;
        break;
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195068(state, 2);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_801958D0(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!fn_80194FE8())
            return 0;
        break;
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195068(state, 3);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_80195994(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!fn_80194FE8())
            return 0;
        break;
    case 1:
        state->mUnknown18 = 1.0f - (float)state->mUnknown4 / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195068(state, 4);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
int fn_80195A58(State_80194FE8 *state, int event, unsigned int color) {
    switch (event) {
    case 0:
        if (!fn_80194FE8())
            return 0;
        break;
    case 1:
        state->mUnknown18 = 1.0f;
        state->mUnknown1C = (float)state->mUnknown4 * 320.0f / (float)state->mUnknown8;
        break;
    case 2:
        fn_80195068(state, 7);
        break;
    case 3:
        state->mUnknown0 = 0;
        break;
    default:
        break;
    }
    return 1;
}
void fn_80195B28(int textured, unsigned int value, float alpha) {
    GXColor color = {0, 0, 0, 255};
    if (textured) {
        color.r = color.g = color.b = 255;
    } else {
        unsigned int red = (value & 255) * 2, green = ((value >> 8) & 255) * 2,
                     blue = ((value >> 16) & 255) * 2;
        if (red > 255)
            red = 255;
        if (green > 255)
            green = 255;
        if (blue > 255)
            blue = 255;
        color.r = red;
        color.g = green;
        color.b = blue;
    }
    color.a = (int)(alpha * 255.0f);
    fn_8024FC48(1);
    fn_8024FB58(4, color);
    fn_8024FC84(4, 0, 0, 0, 1, 0, 2);
    if (textured) {
        fn_80251CC4(1);
        fn_80251B28(0, 0, 0, 4);
        fn_80251604(0, 0);
        fn_8024DF64(1);
        fn_8024DCE4(0, 0, 4, 60, 0, 125);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024CB90(13, 1);
        fn_8024D450(0, 9, 1, 4, 4);
        fn_8024D450(0, 13, 1, 4, 0);
        fn_802520E0(0, 7, 0);
        fn_8024EB28(0);
        fn_802528B0(1);
        fn_80252034(1, 4, 5, 5);
        fn_802505A8(&lbl_80365168, 0);
    } else {
        fn_80251CC4(1);
        fn_80251B28(0, 0, 0, 4);
        fn_80251604(0, 4);
        fn_8024DF64(0);
        fn_8024DCE4(0, 0, 4, 60, 0, 125);
        fn_8024D418();
        fn_8024CB90(9, 1);
        fn_8024D450(0, 9, 1, 4, 4);
        fn_802520E0(0, 7, 0);
        fn_8024EB28(0);
        fn_802528B0(1);
        fn_80252034(1, 4, 5, 5);
    }
    fn_802524D4(lbl_80365128[0]);
    Mtx44 projection, view;
    fn_8024AC28(projection, 0.0f, 448.0f, 0.0f, 640.0f, 1.0f, 2.0f);
    fn_802523A4(projection, 1);
    fn_801D03D0(view);
    fn_8025251C(view, 0);
    fn_802525BC(0);
}
void fn_80195E0C(void) {
    fn_80252034(0, 0, 0, 5);
    fn_802523A4(lbl_80365128, 0);
    fn_802520E0(1, 3, 1);
    fn_802528B0(0);
}
void fn_80195E64(Object_80228224 *) {
    Callback_80195E64 callback = lbl_802EDCF4[lbl_802EDCD0.mUnknown0];
    if (callback)
        callback(&lbl_802EDCD0, 2, lbl_802EDCD0.mUnknown14);
}
void fn_80195EB4(Object_80228224 *) {
    fn_80195558(lbl_803ECBB0, lbl_803ECBB4);
    fn_802284EC(lbl_802EDCD0.mUnknownC, fn_80195EB4);
}
void fn_80195EFC(int mode, unsigned int duration, unsigned int color, void (*notify)(int, float)) {
    fn_80196130();
    if ((mode >= 5 && mode <= 6) || fn_8019623C(0x23000)) {
        lbl_802EDCD0.mUnknown0 = mode;
        lbl_802EDCD0.mUnknown20 = notify;
        lbl_802EDCD0.mUnknown4 = 0;
        lbl_802EDCD0.mUnknown8 = duration;
        lbl_802EDCD0.mUnknown14 = color;
    }
}
void fn_80195F80(void) {
    State_80194FE8 *state = &lbl_802EDCD0;
    if (lbl_803ECBB8) {
        fn_80228474(state->mUnknownC, 2, fn_80195EB4, 0);
        lbl_803ECBB8 = 0;
    }
    Callback_80195E64 callback = lbl_802EDCF4[state->mUnknown0];
    if (callback) {
        if (!state->mUnknown4) {
            if (!callback(state, 0, state->mUnknown14)) {
                state->mUnknown0 = 0;
                return;
            }
            if (state->mUnknown20)
                state->mUnknown20(0, 0.0f);
            fn_80228474(state->mUnknownC, 2, fn_80195E64, 0);
        }
        if (state->mUnknown4 < state->mUnknown8) {
            callback(state, 1, state->mUnknown14);
            if (state->mUnknown20)
                state->mUnknown20(1, (float)state->mUnknown4 / (float)state->mUnknown8);
            ++state->mUnknown4;
        } else {
            fn_802284EC(state->mUnknownC, fn_80195E64);
            callback(state, 3, state->mUnknown14);
            if (state->mUnknown20)
                state->mUnknown20(3, 1.0f);
        }
    }
}
void fn_80196130(void) {
    if (lbl_802EDCD0.mUnknown0) {
        lbl_802EDCD0.mUnknown4 = lbl_802EDCD0.mUnknown8;
        fn_80195F80();
    }
    lbl_803ECBB8 = 0;
}
void fn_80196174(Object_80228224 *object) {
    lbl_802EDCD0.mUnknownC = object;
    lbl_802EDCD0.mUnknown0 = 0;
    lbl_803ECBB8 = 0;
    lbl_802EDCD0.mUnknown4 = lbl_802EDCD0.mUnknown8 = 0;
    if (!lbl_803EB738) {
        lbl_803EB738 = fn_801D2BB0(1, 0x23000, 0, 0);
        fn_8024FFC4(&lbl_80365168, lbl_803EB738, 320, 224, 4, 0, 0, 0);
    }
}
void fn_80196204(void) {
    fn_80196130();
    if (lbl_803EB738) {
        fn_801D2BD0(lbl_803EB738);
        lbl_803EB738 = 0;
    }
}
int fn_8019623C(int size) {
    return lbl_803EB738 && size <= 0x23000;
}
int fn_8019626C(void) {
    return lbl_802EDCD0.mUnknown0;
}
int fn_80196278(void) {
    return fn_8019626C() != 0 && lbl_802EDCD0.mUnknown4 < lbl_802EDCD0.mUnknown8;
}
}
