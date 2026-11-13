#include <dolphin/gx/GXPixel.h>
#include "engine/viewport.h"
#include "game/Object_80039F5C.h"
#include "game/PlayBookTeam.h"
#include "game/bitstream.h"
#include "game/ResLoad.h"
#include "game/fn_802270D4.h"
#include <math.h>
#include "game/fn_800B65A0.h"

struct Object_801618D8 {
    unsigned char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[4];
    int mUnknown14;
    float mUnknown18, mUnknown1C;
    unsigned int mUnknown20;
    void *mUnknown24;
    unsigned int mUnknown28;
    int mUnknown2C, mUnknown30, mUnknown34;
    float mUnknown38;
    unsigned char mUnknown3C[192];
    int mUnknownFC;
    Object_80039F5C *mUnknown100;
    int mUnknown104;
};
struct Desc_801618D8 {
    void *mUnknown0;
    int mUnknown4, mUnknown8;
    Object_801618D8 *mUnknownC;
};
extern "C" {
static Object_801618D8 *lbl_802E9780[9] = {0};
static Object_801618D8 *lbl_802E97A4[9] = {0};
static Object_801618D8 *lbl_802E97C8[9] = {0};
static float lbl_802E97EC[10][4] = {
    {0.2734375f, 0.0f, 0.0f, 1.0f},        {0.0f, 0.0f, 0.390625f, 1.0f},
    {0.2734375f, 0.390625f, 0.0f, 1.0f},   {0.390625f, 0.19921875f, 0.0f, 1.0f},
    {0.19921875f, 0.0f, 0.2734375f, 1.0f}, {0.3515625f, 0.3515625f, 0.0f, 1.0f},
    {0.0f, 0.2734375f, 0.390625f, 1.0f},   {0.0f, 0.19921875f, 0.0f, 1.0f},
    {0.390625f, 0.390625f, 0.390625f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f},
};
static Object_801618D8 *lbl_8031D2A4[5];
static unsigned char lbl_803EB388 = 1;
static unsigned char lbl_803EB389 = 1;
static unsigned char lbl_803EB38A = 1;
static unsigned char lbl_803EB38B = 1;
static Object_801618D8 *lbl_803EB38C = 0;
static Object_801618D8 *lbl_803EB390 = 0;
static unsigned char lbl_803EB394 = 1;
static unsigned char lbl_803EB395 = 1;
static unsigned char lbl_803EB396 = 0;
static unsigned char lbl_803EB397 = 1;
static Object_80039F5C *lbl_803EB398 = 0;
static int lbl_803ECAEC;
Object_80039F5C *BallGetCurrentHolder(void);
Object_80039F5C *fn_800B6544(int);
int GameTextGetPadPlayer(int);
int ConGetCurrentContext(void);
void fn_801D0470(int);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0558(void);
void fn_801D08FC(int);
void fn_801D0ADC(int);
void fn_801D0C58(void *);
void fn_801D0CFC(float);
void fn_801D0D94(float, float, float);
void fn_801D12BC(int);
int fn_801CFE40(float, float);
void fn_80227E40(void *, void *);
void TMRenderBindTexture(int, int, int);
void TMRenderSetZRange(float, float);
void fn_802353D8(void *, int);
void fn_80235588(void *, int);
void fn_802355E4(void *);
void fn_80235630(void *, int);
void fn_8023570C(void *, const char *);
void fn_80235740(void *, int);
void fn_80235764(void *, int);
void fn_80235C48(void *, int);
void fn_80235C90(void *, int, float, float, float, float);
void fn_80235D74(void *, int);
void fn_80235DB8(int);
int fn_80039F8C(Object_80039F5C *);
int fn_801784C4(void);
int ObjNewType_(int, int, int, void (*)(Object_801618D8 *, Desc_801618D8 *), void (*)(Object_801618D8 *));
int ObjDelType(int);
int ObjSetListObjFunc(void *, int, int, int (*)(Object_801618D8 *));
int ObjNewInList(void *, int, int, void *);
void ObjSetPriority(void *, int, int);
void ObjRemoveFromList(void *, int);
void *fn_800C47C4(void);
void fn_80030ACC(void (*)(BitStream_t *),
                 void (*)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float), int,
                 const char *);
int fn_8016295C(Vector_80039F5C *, Vector_80039F5C *, int *, float *);
void fn_80162F28(Object_801618D8 *);
void fn_80163020(void);

Object_80039F5C *fn_8016174C(int index, unsigned char *enabled) {
    Object_801618D8 *item = lbl_802E9780[index];
    Object_80039F5C *current = BallGetCurrentHolder(), *player = 0;
    if (item && (fn_800B65A0(0) != 255 || fn_800B65A0(1) != 255)) {
        if (index != 8) {
            if (item->mUnknown2C != -1) {
                if (!(item->mUnknown20 & 4)) {
                    player = fn_800B6544(item->mUnknown2C);
                    if (player && (player->mpUnknown4->mUnknown20 & 1) && !(player->mFlags & 0x400))
                        player = 0;
                } else {
                    Object_80039F5C *linked = fn_8009BCE8(&item->mUnknown104);
                    if (linked->mFlags & 0x400) {
                        player = fn_800B6544(item->mUnknown2C);
                        if (player && (player->mpUnknown4->mUnknown20 & 1) && !(player->mFlags & 0x400))
                            player = 0;
                    } else if (linked->mpUnknown4->mUnknown20 & 1)
                        player = linked;
                }
            }
        } else {
            if (lbl_803EB397) {
                if (!(item->mUnknown20 & 4)) {
                    if (current && (current->mpUnknown4->mUnknown20 & 1) && (current->mId & 255) == 1 &&
                        !(current->mFlags & 0x400) && fn_800B65A0((current->mId >> 8) & 255) == 255)
                        player = current;
                } else {
                    Object_80039F5C *linked = fn_8009BCE8(&item->mUnknown104);
                    if (linked->mpUnknown4->mUnknown20 & 1)
                        player = linked;
                }
            }
            lbl_803EB398 = player;
        }
    }
    if (player)
        *enabled = 1;
    else
        *enabled = 0;
    return player;
}
void fn_801618D8(Object_801618D8 *item, Desc_801618D8 *desc) {
    int kind = desc->mUnknown8;
    item->mUnknown34 = kind;
    item->mUnknown4.mX = 0.0f;
    item->mUnknown4.mY = 0.0f;
    item->mUnknown4.mZ = 0.0f;
    item->mUnknown14 = 0;
    item->mUnknown38 = 1.0f;
    item->mUnknown20 = 18;
    item->mUnknown1C = 1.0f;
    if (kind == 8) {
        item->mUnknown30 = kind;
        item->mUnknown2C = -1;
    } else {
        item->mUnknown2C = kind;
        item->mUnknown30 = GameTextGetPadPlayer(kind) % 10;
    }
    item->mUnknown100 = 0;
    item->mUnknown24 = desc->mUnknown0;
    item->mUnknown28 = desc->mUnknown4;
    if (!desc->mUnknownC) {
        item->mUnknownFC = 0;
        item->mUnknownFC = ResLoad(item->mUnknown24, item->mUnknown28, 1);
        fn_80235DB8(item->mUnknownFC);
    } else {
        item->mUnknown20 |= 1;
        item->mUnknownFC = desc->mUnknownC->mUnknownFC;
    }
    fn_80235588(item->mUnknown3C, 6);
    fn_80235630(item->mUnknown3C, item->mUnknownFC);
    fn_80235C48(item->mUnknown3C, 3);
    fn_80235D74(item->mUnknown3C, 128);
    fn_802353D8(item->mUnknown3C, 0x401002);
    fn_8023570C(item->mUnknown3C, "Flat");
}
void fn_80161A34(Object_801618D8 *item) {
    fn_802355E4(item->mUnknown3C);
    if ((item->mUnknown20 & 1) == 0 && item->mUnknownFC)
        ResUnLoad(item->mUnknown24, item->mUnknown28);
}
void fn_80161A88(Object_801618D8 *out, Object_801618D8 *in) {
    out->mUnknown14 = in->mUnknown14;
    out->mUnknown18 = in->mUnknown18;
    out->mUnknown1C = in->mUnknown1C;
    out->mUnknown20 = in->mUnknown20;
    out->mUnknown2C = in->mUnknown2C;
    out->mUnknown30 = in->mUnknown30;
    out->mUnknown38 = in->mUnknown38;
    out->mUnknown100 = in->mUnknown100;
    out->mUnknown104 = in->mUnknown104;
}
void fn_80161AD4(void *render, int index) {
    int context = ConGetCurrentContext();
    fn_80235C90(render, context, lbl_802E97EC[index][0], lbl_802E97EC[index][1], lbl_802E97EC[index][2],
                lbl_802E97EC[index][3]);
}
int fn_80161B38(Object_801618D8 *item) {
    Object_801618D8 *extra = 0;
    int draw = 1, valid = 1;
    if (item->mUnknownFC && (item->mUnknown20 & 2)) {
        fn_801D0470(VptGetMatrixStack());
        fn_801D04C4();
        switch (item->mUnknown28) {
        case 5:
            if (lbl_803EB394 == 1) {
                float scale = item->mUnknown1C;
                fn_801D0C58(&item->mUnknown4);
                fn_801D0ADC(item->mUnknown14);
                fn_801D0D94(scale, scale, 1.0f);
                fn_80161AD4(item->mUnknown3C, item->mUnknown30);
                if (!lbl_803EB388)
                    draw = 0;
                if (lbl_803EB389) {
                    extra = lbl_802E97A4[item->mUnknown34];
                    fn_80161AD4(extra->mUnknown3C, 9);
                }
            } else
                valid = 0;
            break;
        case 6:
            if (lbl_803EB395 && item->mUnknown34 != 8) {
                Vector_80039F5C point;
                float scale;
                if (fn_8016295C(&item->mUnknown4, &point, &item->mUnknown14, &scale)) {
                    fn_801D0558();
                    scale = (scale + item->mUnknown18) * 0.5f;
                    item->mUnknown18 = scale;
                    fn_801D0C58(&point);
                    fn_801D0ADC(item->mUnknown14);
                    fn_801D08FC(0x400000);
                    fn_801D0CFC(item->mUnknown18);
                    fn_80161AD4(item->mUnknown3C, item->mUnknown30);
                } else {
                    valid = 0;
                    item->mUnknown18 = 0.25f;
                }
            } else {
                valid = 0;
                item->mUnknown18 = 0.25f;
            }
            break;
        case 7:
            if (lbl_803EB395 == 1) {
                float scale = item->mUnknown1C * item->mUnknown18;
                fn_801D0C58(&item->mUnknown4);
                fn_801D0ADC(item->mUnknown14);
                fn_801D0D94(scale, scale, 1.0f);
                fn_80161AD4(item->mUnknown3C, item->mUnknown30);
                if (!lbl_803EB38A)
                    draw = 0;
                if (lbl_803EB38B) {
                    extra = lbl_803EB390;
                    fn_80161AD4(extra->mUnknown3C, 9);
                }
            } else
                valid = 0;
            break;
        default:
            valid = 0;
            break;
        }
        if (valid == 1) {
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
            TMRenderBindTexture(0, 0, 0);
            if (item->mUnknown28 == 6) {
                fn_80235740(item->mUnknown3C, ConGetCurrentContext());
                TMRenderSetZRange(0.0f, 0.0f);
                fn_801D0470(VptGetMatrixStack());
                fn_801D0544();
                fn_80235764(item->mUnknown3C, ConGetCurrentContext());
                TMRenderSetZRange(0.0f, 1.0f);
            } else {
                if (extra)
                    fn_80235740(extra->mUnknown3C, ConGetCurrentContext());
                if (draw)
                    fn_80235740(item->mUnknown3C, ConGetCurrentContext());
                fn_801D0470(VptGetMatrixStack());
                fn_801D0544();
                if (extra)
                    fn_80235764(extra->mUnknown3C, ConGetCurrentContext());
                if (draw)
                    fn_80235764(item->mUnknown3C, ConGetCurrentContext());
            }
        } else {
            fn_801D0470(VptGetMatrixStack());
            fn_801D0544();
        }
    }
    return 0;
}
void fn_80161E7C(Object_801618D8 *item, Vec2_t *point, int flip) {
    item->mUnknown4.mX = point->mX;
    item->mUnknown4.mY = point->mY;
    item->mUnknown4.mZ = 0.0f;
    item->mUnknown14 = (item->mUnknown14 + 0x16C16) & 0xFFFFFF;
    if (flip) {
        item->mUnknown4.mX = -item->mUnknown4.mX;
        item->mUnknown4.mY = -item->mUnknown4.mY;
    }
    item->mUnknown20 |= 2;
}
int fn_80161ED4(void) {
    return 6;
}
void fn_80161EDC(Object_801618D8 *item, BitStream_t *stream) {
    if (item) {
        unsigned char active = (item->mUnknown20 >> 1) & 1;
        fn_80191068(stream, active, 1);
        fn_80191068(stream, fn_80039F8C(item->mUnknown100), 5);
    } else
        fn_80191068(stream, 0, 6);
}
void fn_80161F5C(Object_801618D8 *item, BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d,
                 float blend) {
    ReadBitStream(a, 6);
    if (d)
        ReadBitStream(d, 6);
    if (c)
        ReadBitStream(c, 6);
    if (item) {
        unsigned char active = ReadBitStream(b, 1);
        if (active == 1)
            item->mUnknown20 |= 2;
        else
            item->mUnknown20 &= ~2;
        int id = (int)ReadBitStream(b, 5);
        if (active && id <= 13) {
            Object_80039F5C *player = fn_80039F5C((unsigned char)(id / 7), (unsigned short)(id % 7));
            fn_80161E7C(item, (Vec2_t *)&player->mpUnknown4->mUnknown4, 0);
        }
    } else
        ReadBitStream(b, 6);
}
void fn_80162074(BitStream_t *stream) {
    for (unsigned char i = 0; i < 9; ++i)
        fn_80161EDC(lbl_802E9780[i], stream);
    fn_80161EDC(lbl_803EB38C, stream);
}
void fn_801620D4(BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d, float blend) {
    for (unsigned char i = 0; i < 9; ++i)
        fn_80161F5C(lbl_802E9780[i], a, b, c, d, blend);
    fn_80161F5C(lbl_803EB38C, a, b, c, d, blend);
}
Object_801618D8 *fn_8016216C(void) {
    unsigned int i = 0;
    Object_801618D8 *item;
    while ((item = lbl_8031D2A4[i])->mUnknown100) {
        if (++i >= 5)
            return 0;
    }
    return item;
}
float fn_801621AC(Object_801618D8 *item) {
    return 2.5f;
}
void fn_801621B8(void) {
    for (unsigned int i = 0; i < 5; ++i) {
        Object_801618D8 *item = lbl_8031D2A4[i];
        if (item->mUnknown20 & 2) {
            if (item->mUnknown20 & 4) {
                if (!(item->mUnknown18 <= 1.0f))
                    item->mUnknown18 *= 0.88f;
                else {
                    item->mUnknown18 = 1.0f;
                    item->mUnknown100 = 0;
                }
            }
            if (item->mUnknown20 & 8) {
                item->mUnknown18 *= 1.13f;
                if (!(item->mUnknown18 <= 8.0f)) {
                    item->mUnknown100 = 0;
                    item->mUnknown20 &= ~2;
                }
            }
            if (item->mUnknown20 & 0x20) {
                item->mUnknown18 *= 1.1f;
                fn_80161E7C(item, (Vec2_t *)&item->mUnknown100->mMotion.mPos, fn_801784C4());
                if (!(item->mUnknown18 <= item->mUnknown38)) {
                    item->mUnknown18 = item->mUnknown38;
                    item->mUnknown20 = (item->mUnknown20 & ~0x20) | 0x40;
                }
            }
            if (item->mUnknown20 & 0x40) {
                fn_80161E7C(item, (Vec2_t *)&item->mUnknown100->mMotion.mPos, fn_801784C4());
                if (!(item->mUnknown18 <= 1.0f))
                    item->mUnknown18 *= 0.9f;
                else {
                    item->mUnknown18 = 1.0f;
                    item->mUnknown20 &= ~0x40;
                    item->mUnknown100 = 0;
                    item->mUnknown20 &= ~2;
                }
            }
            if (item->mUnknown20 & 0x10)
                item->mUnknown14 = (item->mUnknown14 + 0x16C16) & 0xFFFFFF;
        }
    }
}
void fn_8016239C(void *arg) {
    ObjNewType_(8, 264, 34, fn_801618D8, fn_80161A34);
    ObjSetListObjFunc(arg, 8, 0, fn_80161B38);
    lbl_803EB398 = 0;
}
void fn_80162404(void) {
    VptFlushObjectTrashSync();
    ObjDelType(8);
    lbl_803EB398 = 0;
}
Object_801618D8 *fn_80162434(void *arg, int index, Object_801618D8 *shared, void *data, int mode) {
    Desc_801618D8 desc;
    desc.mUnknown0 = data;
    desc.mUnknownC = shared;
    desc.mUnknown8 = index;
    desc.mUnknown4 = mode;
    int handle = ObjNewInList(arg, 8, 0, &desc);
    ObjSetPriority(arg, handle, 3);
    return (Object_801618D8 *)handle;
}
void fn_80162494(void *arg, Object_801618D8 *item) {
    if (item) {
        ObjRemoveFromList(arg, (int)item);
        VptTrashObject((int)item);
    }
}
void fn_801624D0(void *arg) {
    void *data = fn_800C47C4();
    fn_8016239C(arg);
    Object_801618D8 *shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        Object_801618D8 *item = fn_80162434(arg, i, shared, data, 6);
        item->mUnknown18 = 0.25f;
        lbl_802E97C8[i] = item;
        if (!i)
            shared = item;
    }
    lbl_803EB38C = fn_80162434(arg, 9, 0, data, 7);
    lbl_803EB38C->mUnknown18 = 1.0f;
    for (unsigned int i = 0; i < 5; ++i) {
        Object_801618D8 *item = fn_80162434(arg, i, lbl_803EB38C, data, 7);
        item->mUnknown18 = 1.0f;
        item->mUnknown20 &= ~2;
        lbl_8031D2A4[i] = item;
    }
    lbl_803EB390 = fn_80162434(arg, 9, 0, data, 12);
    lbl_803EB390->mUnknown18 = 1.0f;
    shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        Object_801618D8 *item = fn_80162434(arg, i, shared, data, 5);
        item->mUnknown18 = 1.0f;
        lbl_802E9780[i] = item;
        if (!i)
            shared = item;
    }
    shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        Object_801618D8 *item = fn_80162434(arg, i, shared, data, 11);
        item->mUnknown18 = 1.0f;
        lbl_802E97A4[i] = item;
        if (!i)
            shared = item;
    }
}
void fn_801626A4(void *arg) {
    unsigned int i;
    for (i = 0; i < 9; ++i) {
        fn_80162494(arg, lbl_802E9780[i]);
        lbl_802E9780[i] = 0;
        fn_80162494(arg, lbl_802E97A4[i]);
        lbl_802E9780[i] = 0;
        fn_80162494(arg, lbl_802E97C8[i]);
        lbl_802E97C8[i] = 0;
    }
    for (i = 0; i < 5; ++i) {
        fn_80162494(arg, lbl_8031D2A4[i]);
        lbl_8031D2A4[i] = 0;
    }
    fn_80162494(arg, lbl_803EB38C);
    fn_80162494(arg, lbl_803EB390);
    fn_80162404();
}
void fn_80162780(unsigned char a, unsigned char b) {
    lbl_803EB394 = a;
    lbl_803EB395 = b;
}
unsigned char fn_8016278C(void) {
    return lbl_803EB394;
}
void fn_80162794(void) {
    Object_80039F5C *current = BallGetCurrentHolder();
    lbl_803EB38C->mUnknown20 &= ~2;
    for (unsigned char i = 0; i < 9; ++i) {
        Object_801618D8 *item = lbl_802E9780[i], *other = lbl_802E97C8[i];
        unsigned char active = 0;
        if (item) {
            if (fn_800B65A0(0) != 255 || fn_800B65A0(1) != 255)
                item->mUnknown100 = fn_8016174C(i, &active);
            if (active == 1) {
                Object_80039F5C *player = item->mUnknown100;
                if (player->mFlags & 0x2000000) {
                    fn_80162F28(item);
                    player->mFlags &= ~0x2000000;
                }
                fn_80161E7C(item, (Vec2_t *)&player->mMotion.mPos, fn_801784C4());
                other->mUnknown20 |= 2;
                other->mUnknown4.mX = item->mUnknown4.mX;
                other->mUnknown4.mY = item->mUnknown4.mY;
                other->mUnknown4.mZ = item->mUnknown4.mZ;
                if (player == current) {
                    lbl_803EB396 = (unsigned char)item->mUnknown2C;
                    Object_801618D8 *global = lbl_803EB38C;
                    global->mUnknown30 = item->mUnknown30;
                    global->mUnknown20 |= 2;
                    global->mUnknown4.mX = item->mUnknown4.mX;
                    global->mUnknown4.mY = item->mUnknown4.mY;
                    global->mUnknown4.mZ = 0.0f;
                    if (global->mUnknown20 & 0x10)
                        global->mUnknown14 = (global->mUnknown14 - 0x16C16) & 0xFFFFFF;
                    else
                        global->mUnknown14 = 0;
                    fn_80161A88(lbl_803EB390, lbl_803EB38C);
                }
            } else {
                item->mUnknown20 &= ~2;
                other->mUnknown20 &= ~2;
            }
            fn_80161A88(lbl_802E97A4[i], item);
        }
    }
    fn_801621B8();
}
int fn_8016295C(Vector_80039F5C *input, Vector_80039F5C *out, int *angle, float *scale) {
    struct Projection_8016295C {
        float mX, mY, mZ, mW;
    };
    int result;
    fn_801D0470(VptGetMatrixStack());
    fn_801D04C4();
    fn_801D12BC(4);
    Projection_8016295C point;
    Vector_80039F5C unused;
    Projection_8016295C original;
    unused.mX = input->mX;
    unused.mY = input->mY;
    unused.mZ = 0.5f;
    original.mX = input->mX;
    original.mY = input->mY;
    original.mZ = 0.5f;
    original.mW = 1.0f;
    fn_80227E40(&point, &original);
    if (point.mX < -point.mW || point.mX > point.mW || point.mY < -point.mW || !(point.mY <= point.mW)) {
        original.mX = point.mX;
        original.mY = point.mY;
        original.mZ = point.mZ;
        *angle = fn_801CFE40(-point.mX, point.mY);
        float ratio = 1.0f;
        if (!(fabsf(point.mW) >= 1.0f)) {
            if (!(point.mW >= 0.0f))
                ratio = -1.0f;
        } else
            ratio = 1.0f / point.mW;
        point.mX *= ratio;
        point.mY *= ratio;
        float a = fn_802270D4((Vector_80039F5C *)&original) - 10.25f;
        a *= 0.11111111f;
        Vec2_t pair;
        pair.mX = point.mX;
        pair.mY = point.mY;
        float b = (fn_802270A4(&pair) - 1.0f) * 0.5f;
        if (!(original.mZ >= 0.0f))
            b = a;
        else if (!(original.mZ > 1.0f))
            b = b * original.mZ + a * (1.0f - original.mZ);
        if (!(b >= 0.0f))
            b = 0.0f;
        if (!(b <= 1.0f))
            b = 1.0f;
        float alpha = 1.0f - b;
        if (!(point.mW >= 0.0f)) {
            point.mX = -point.mX;
            point.mY = -0.9f;
        }
        if (!(point.mX <= 0.7f))
            point.mX = (point.mX - 0.7f) * 0.020000001f + 0.7f;
        else if (!(point.mX >= -0.7f))
            point.mX = (point.mX - 0.7f) * 0.020000001f + -0.7f;
        if (!(point.mY <= 0.7f))
            point.mY = (point.mY - 0.7f) * 0.080000006f + 0.7f;
        else if (!(point.mY >= -0.7f))
            point.mY = (point.mY - 0.7f) * 0.080000006f + -0.7f;
        if (!(point.mX <= 0.9f))
            point.mX = 0.9f;
        if (!(point.mX >= -0.9f))
            point.mX = -0.9f;
        if (!(point.mY <= 0.9f))
            point.mY = 0.9f;
        if (!(point.mY >= -0.9f))
            point.mY = -0.9f;
        out->mX = point.mX * 5.0f;
        out->mY = -(point.mY * -3.0f);
        out->mZ = -10.0f;
        if (!(out->mX >= -5.0f))
            out->mX = -5.0f;
        if (!(out->mX <= 5.0f))
            out->mX = 5.0f;
        if (!(out->mY <= 3.0f))
            out->mY = 3.0f;
        if (!(out->mY >= -3.0f))
            out->mY = -3.0f;
        float amount = alpha * 0.75f + 0.25f;
        if (!(amount >= 0.25f))
            amount = 0.25f;
        if (!(amount <= 1.0f))
            amount = 1.0f;
        *scale = amount;
        result = 1;
    } else
        result = 0;
    fn_801D0544();
    return result;
}
void fn_80162D78(void) {
    lbl_803ECAEC = fn_80161ED4();
    fn_80030ACC(fn_80162074, fn_801620D4, lbl_803ECAEC * 10, "Stars");
}
Object_801618D8 *fn_80162DBC(int index) {
    return lbl_8031D2A4[index];
}
void fn_80162DD0(Object_801618D8 *item, Vector_80039F5C *point) {
    item->mUnknown4.mX = point->mX;
    item->mUnknown4.mY = point->mY;
    item->mUnknown4.mZ = point->mZ;
    if (fn_801784C4()) {
        item->mUnknown4.mX = -item->mUnknown4.mX;
        item->mUnknown4.mY = -item->mUnknown4.mY;
    }
    item->mUnknown20 |= 2;
}
unsigned int fn_80162E40(int index) {
    float r = lbl_802E97EC[index][0];
    if (!(r <= 1.0f))
        r = 1.0f;
    unsigned char red = (int)(r * 255.0f);
    float g = lbl_802E97EC[index][1];
    if (!(g <= 1.0f))
        g = 1.0f;
    unsigned char green = (int)(g * 255.0f);
    float b = lbl_802E97EC[index][2];
    if (!(b <= 1.0f))
        b = 1.0f;
    unsigned char blue = (int)(b * 255.0f);
    float a = lbl_802E97EC[index][3];
    if (!(a <= 1.0f))
        a = 1.0f;
    return ((unsigned int)(int)(a * 255.0f) << 24) | (red << 16) | (green << 8) | blue;
}
void fn_80162F28(Object_801618D8 *source) {
    if (source) {
        Object_801618D8 *item = fn_8016216C();
        if (item) {
            item->mUnknown100 = source->mUnknown100;
            item->mUnknown20 |= 0x22;
            item->mUnknown14 = 0;
            item->mUnknown18 = 1.0f;
            item->mUnknown38 = fn_801621AC(item);
            item->mUnknown30 = source->mUnknown30;
            Vec2_t *point = (Vec2_t *)&item->mUnknown100->mMotion.mPos;
            fn_80161E7C(item, point, fn_801784C4());
        }
    }
}
void fn_80162FB8(int index, int ref) {
    Object_801618D8 *item = index == 255 ? lbl_802E9780[8] : lbl_802E9780[index];
    fn_80163020();
    if (item) {
        item->mUnknown104 = ref;
        item->mUnknown20 |= 4;
    }
}
void fn_80163020(void) {
    for (unsigned char i = 0; i < 9; ++i) {
        Object_801618D8 *item = lbl_802E9780[i];
        if (item) {
            item->mUnknown104 = 0;
            item->mUnknown20 &= ~4;
        }
    }
}
Object_80039F5C *fn_80163064(void) {
    return lbl_803EB398;
}
void fn_8016306C(unsigned char value) {
    lbl_803EB397 = value;
}
}
