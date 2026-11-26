/* The coloured markers on the field that show which player each controller runs: a ring under every
   human-controlled player and the ball carrier, an arrow at the screen edge when he is off screen, and a
   pulse when control switches. Also records them in replays ("Stars"). */

#include <dolphin/gx/GXPixel.h>
#include "engine/viewport.h"
#include "game/Object_80039F5C.h"
#include "game/PlayBookTeam.h"
#include "game/bitstream.h"
#include "game/ResLoad.h"
#include "game/Vec3Magnitude.h"
#include <math.h>
#include "game/fn_800B65A0.h"

struct PlyrStar_t {
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
struct PlyrStarDesc_t {
    void *mUnknown0;
    int mUnknown4, mUnknown8;
    PlyrStar_t *mUnknownC;
};
extern "C" {
static PlyrStar_t *_PlyrStar_apRing[9] = {0};
static PlyrStar_t *_PlyrStar_apRingOutline[9] = {0};
static PlyrStar_t *_PlyrStar_apArrow[9] = {0};
static float _PlyrStar_afColor[10][4] = {
    {0.2734375f, 0.0f, 0.0f, 1.0f},        {0.0f, 0.0f, 0.390625f, 1.0f},
    {0.2734375f, 0.390625f, 0.0f, 1.0f},   {0.390625f, 0.19921875f, 0.0f, 1.0f},
    {0.19921875f, 0.0f, 0.2734375f, 1.0f}, {0.3515625f, 0.3515625f, 0.0f, 1.0f},
    {0.0f, 0.2734375f, 0.390625f, 1.0f},   {0.0f, 0.19921875f, 0.0f, 1.0f},
    {0.390625f, 0.390625f, 0.390625f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f},
};
static PlyrStar_t *_PlyrStar_apPulse[5];
static unsigned char _PlyrStar_bDrawRing = 1;
static unsigned char _PlyrStar_bDrawRingOutline = 1;
static unsigned char _PlyrStar_bDrawBallMarker = 1;
static unsigned char _PlyrStar_bDrawBallOutline = 1;
static PlyrStar_t *_PlyrStar_pBallMarker = 0;
static PlyrStar_t *_PlyrStar_pBallOutline = 0;
static unsigned char _PlyrStar_bShowRings = 1;
static unsigned char _PlyrStar_bShowArrows = 1;
static unsigned char _PlyrStar_uBallPad = 0;
static unsigned char _PlyrStar_bBallRingEnabled = 1;
static Object_80039F5C *_PlyrStar_pBallPlayer = 0;
static int _PlyrStar_iReplayBits;
Object_80039F5C *BallGetCurrentHolder(void);
Object_80039F5C *fn_800B6544(int);
int GameTextGetPadPlayer(int);
int ConGetCurrentContext(void);
void MatSetStack(int);
void MatPush(void);
void MatPop(void);
void MatMakeUnit(void);
void MatRotX(int);
void MatRotZ(int);
void MatTranslate(void *);
void MatScale(float);
void MatScaleCol(float, float, float);
void MatLoadSlot(int);
int MathArcTan2(float, float);
void Vec4Mat44Mul(void *, void *);
void TMRenderBindTexture(int, int, int);
void TMRenderSetZRange(float, float);
void fn_802353D8(void *, int);
void fn_80235588(void *, int);
void ModelObjReset(void *);
void ModelObjSetModel(void *, int);
void ModelObjSetShader(void *, const char *);
void ModelObjStoreMatrix(void *, int);
void ModelObjDraw(void *, int);
void ModelObjSetParamNop(void *, int);
void ModelObjSetAmbientColor(void *, int, float, float, float, float);
void ModelObjSetModeNop(void *, int);
void ModelObjRelocateModelRes(int);
int PlyrGetIndex(Object_80039F5C *);
int fn_801784C4(void);
int ObjNewType_(int, int, int, void (*)(PlyrStar_t *, PlyrStarDesc_t *), void (*)(PlyrStar_t *));
int ObjDelType(int);
int ObjSetListObjFunc(void *, int, int, int (*)(PlyrStar_t *));
int ObjNewInList(void *, int, int, void *);
void ObjSetPriority(void *, int, int);
void ObjRemoveFromList(void *, int);
void *fn_800C47C4(void);
void ReplayRegisterChannel(void (*)(BitStream_t *),
                 void (*)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float), int,
                 const char *);
int PlyrStarProjectOffscreen(Vector_80039F5C *, Vector_80039F5C *, int *, float *);
void PlyrStarStartPulse(PlyrStar_t *);
void PlyrStarClearLinks(void);

Object_80039F5C *PlyrStarFindPlayer(int index, unsigned char *enabled) {
    PlyrStar_t *item = _PlyrStar_apRing[index];
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
            if (_PlyrStar_bBallRingEnabled) {
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
            _PlyrStar_pBallPlayer = player;
        }
    }
    if (player)
        *enabled = 1;
    else
        *enabled = 0;
    return player;
}
void PlyrStarCreate(PlyrStar_t *item, PlyrStarDesc_t *desc) {
    int kind = desc->mUnknown8;
    // FAKEMATCH: store order of the field initializers below was found by permutation search
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
        ModelObjRelocateModelRes(item->mUnknownFC);
    } else {
        item->mUnknown20 |= 1;
        item->mUnknownFC = desc->mUnknownC->mUnknownFC;
    }
    fn_80235588(item->mUnknown3C, 6);
    ModelObjSetModel(item->mUnknown3C, item->mUnknownFC);
    ModelObjSetParamNop(item->mUnknown3C, 3);
    ModelObjSetModeNop(item->mUnknown3C, 128);
    fn_802353D8(item->mUnknown3C, 0x401002);
    ModelObjSetShader(item->mUnknown3C, "Flat");
}
void PlyrStarDestroy(PlyrStar_t *item) {
    ModelObjReset(item->mUnknown3C);
    if ((item->mUnknown20 & 1) == 0 && item->mUnknownFC)
        ResUnLoad(item->mUnknown24, item->mUnknown28);
}
void PlyrStarCopyState(PlyrStar_t *out, PlyrStar_t *in) {
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
void PlyrStarSetColor(void *render, int index) {
    int context = ConGetCurrentContext();
    ModelObjSetAmbientColor(render, context, _PlyrStar_afColor[index][0], _PlyrStar_afColor[index][1], _PlyrStar_afColor[index][2],
                _PlyrStar_afColor[index][3]);
}
int PlyrStarDraw(PlyrStar_t *item) {
    PlyrStar_t *extra = 0;
    int draw = 1, valid = 1;
    if (item->mUnknownFC && (item->mUnknown20 & 2)) {
        MatSetStack(VptGetMatrixStack());
        MatPush();
        switch (item->mUnknown28) {
        case 5:
            if (_PlyrStar_bShowRings == 1) {
                float scale = item->mUnknown1C;
                MatTranslate(&item->mUnknown4);
                MatRotZ(item->mUnknown14);
                MatScaleCol(scale, scale, 1.0f);
                PlyrStarSetColor(item->mUnknown3C, item->mUnknown30);
                if (!_PlyrStar_bDrawRing)
                    draw = 0;
                if (_PlyrStar_bDrawRingOutline) {
                    extra = _PlyrStar_apRingOutline[item->mUnknown34];
                    PlyrStarSetColor(extra->mUnknown3C, 9);
                }
            } else
                valid = 0;
            break;
        case 6:
            if (_PlyrStar_bShowArrows && item->mUnknown34 != 8) {
                Vector_80039F5C point;
                float scale;
                if (PlyrStarProjectOffscreen(&item->mUnknown4, &point, &item->mUnknown14, &scale)) {
                    MatMakeUnit();
                    scale = (scale + item->mUnknown18) * 0.5f;
                    item->mUnknown18 = scale;
                    MatTranslate(&point);
                    MatRotZ(item->mUnknown14);
                    MatRotX(0x400000);
                    MatScale(item->mUnknown18);
                    PlyrStarSetColor(item->mUnknown3C, item->mUnknown30);
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
            if (_PlyrStar_bShowArrows == 1) {
                float scale = item->mUnknown1C * item->mUnknown18;
                MatTranslate(&item->mUnknown4);
                MatRotZ(item->mUnknown14);
                MatScaleCol(scale, scale, 1.0f);
                PlyrStarSetColor(item->mUnknown3C, item->mUnknown30);
                if (!_PlyrStar_bDrawBallMarker)
                    draw = 0;
                if (_PlyrStar_bDrawBallOutline) {
                    extra = _PlyrStar_pBallOutline;
                    PlyrStarSetColor(extra->mUnknown3C, 9);
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
                ModelObjStoreMatrix(item->mUnknown3C, ConGetCurrentContext());
                TMRenderSetZRange(0.0f, 0.0f);
                MatSetStack(VptGetMatrixStack());
                MatPop();
                ModelObjDraw(item->mUnknown3C, ConGetCurrentContext());
                TMRenderSetZRange(0.0f, 1.0f);
            } else {
                if (extra)
                    ModelObjStoreMatrix(extra->mUnknown3C, ConGetCurrentContext());
                if (draw)
                    ModelObjStoreMatrix(item->mUnknown3C, ConGetCurrentContext());
                MatSetStack(VptGetMatrixStack());
                MatPop();
                if (extra)
                    ModelObjDraw(extra->mUnknown3C, ConGetCurrentContext());
                if (draw)
                    ModelObjDraw(item->mUnknown3C, ConGetCurrentContext());
            }
        } else {
            MatSetStack(VptGetMatrixStack());
            MatPop();
        }
    }
    return 0;
}
void PlyrStarSetPosition(PlyrStar_t *item, Vec2_t *point, int flip) {
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
int PlyrStarGetReplayBits(void) {
    return 6;
}
void PlyrStarWriteReplay(PlyrStar_t *item, BitStream_t *stream) {
    if (item) {
        unsigned char active = (item->mUnknown20 >> 1) & 1;
        fn_80191068(stream, active, 1);
        fn_80191068(stream, PlyrGetIndex(item->mUnknown100), 5);
    } else
        fn_80191068(stream, 0, 6);
}
void PlyrStarReadReplay(PlyrStar_t *item, BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d,
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
            Object_80039F5C *player = PlyrGet((unsigned char)(id / 7), (unsigned short)(id % 7));
            PlyrStarSetPosition(item, (Vec2_t *)&player->mpUnknown4->mUnknown4, 0);
        }
    } else
        ReadBitStream(b, 6);
}
void PlyrStarWriteReplayAll(BitStream_t *stream) {
    for (unsigned char i = 0; i < 9; ++i)
        PlyrStarWriteReplay(_PlyrStar_apRing[i], stream);
    PlyrStarWriteReplay(_PlyrStar_pBallMarker, stream);
}
void PlyrStarReadReplayAll(BitStream_t *a, BitStream_t *b, BitStream_t *c, BitStream_t *d, float blend) {
    for (unsigned char i = 0; i < 9; ++i)
        PlyrStarReadReplay(_PlyrStar_apRing[i], a, b, c, d, blend);
    PlyrStarReadReplay(_PlyrStar_pBallMarker, a, b, c, d, blend);
}
PlyrStar_t *PlyrStarFindFreePulse(void) {
    unsigned int i = 0;
    PlyrStar_t *item;
    while ((item = _PlyrStar_apPulse[i])->mUnknown100) {
        if (++i >= 5)
            return 0;
    }
    return item;
}
float PlyrStarGetPulseScale(PlyrStar_t *item) {
    return 2.5f;
}
void PlyrStarUpdatePulses(void) {
    for (unsigned int i = 0; i < 5; ++i) {
        PlyrStar_t *item = _PlyrStar_apPulse[i];
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
                PlyrStarSetPosition(item, (Vec2_t *)&item->mUnknown100->mMotion.mPos, fn_801784C4());
                if (!(item->mUnknown18 <= item->mUnknown38)) {
                    item->mUnknown18 = item->mUnknown38;
                    item->mUnknown20 = (item->mUnknown20 & ~0x20) | 0x40;
                }
            }
            if (item->mUnknown20 & 0x40) {
                PlyrStarSetPosition(item, (Vec2_t *)&item->mUnknown100->mMotion.mPos, fn_801784C4());
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
void PlyrStarRegisterType(void *arg) {
    ObjNewType_(8, 264, 34, PlyrStarCreate, PlyrStarDestroy);
    ObjSetListObjFunc(arg, 8, 0, PlyrStarDraw);
    _PlyrStar_pBallPlayer = 0;
}
void PlyrStarReleaseType(void) {
    VptFlushObjectTrashSync();
    ObjDelType(8);
    _PlyrStar_pBallPlayer = 0;
}
PlyrStar_t *PlyrStarNew(void *arg, int index, PlyrStar_t *shared, void *data, int mode) {
    PlyrStarDesc_t desc;
    // FAKEMATCH: store order +0, +0xC, +8, +4 chosen to reproduce the target schedule
    desc.mUnknown0 = data;
    desc.mUnknownC = shared;
    desc.mUnknown8 = index;
    desc.mUnknown4 = mode;
    int handle = ObjNewInList(arg, 8, 0, &desc);
    ObjSetPriority(arg, handle, 3);
    return (PlyrStar_t *)handle;
}
void PlyrStarDelete(void *arg, PlyrStar_t *item) {
    if (item) {
        ObjRemoveFromList(arg, (int)item);
        VptTrashObject((int)item);
    }
}
void PlyrStarInit(void *arg) {
    void *data = fn_800C47C4();
    PlyrStarRegisterType(arg);
    PlyrStar_t *shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        PlyrStar_t *item = PlyrStarNew(arg, i, shared, data, 6);
        item->mUnknown18 = 0.25f;
        _PlyrStar_apArrow[i] = item;
        if (!i)
            shared = item;
    }
    _PlyrStar_pBallMarker = PlyrStarNew(arg, 9, 0, data, 7);
    _PlyrStar_pBallMarker->mUnknown18 = 1.0f;
    for (unsigned int i = 0; i < 5; ++i) {
        PlyrStar_t *item = PlyrStarNew(arg, i, _PlyrStar_pBallMarker, data, 7);
        item->mUnknown18 = 1.0f;
        item->mUnknown20 &= ~2;
        _PlyrStar_apPulse[i] = item;
    }
    _PlyrStar_pBallOutline = PlyrStarNew(arg, 9, 0, data, 12);
    _PlyrStar_pBallOutline->mUnknown18 = 1.0f;
    shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        PlyrStar_t *item = PlyrStarNew(arg, i, shared, data, 5);
        item->mUnknown18 = 1.0f;
        _PlyrStar_apRing[i] = item;
        if (!i)
            shared = item;
    }
    shared = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        PlyrStar_t *item = PlyrStarNew(arg, i, shared, data, 11);
        item->mUnknown18 = 1.0f;
        _PlyrStar_apRingOutline[i] = item;
        if (!i)
            shared = item;
    }
}
void PlyrStarShutdown(void *arg) {
    unsigned int i;
    for (i = 0; i < 9; ++i) {
        PlyrStarDelete(arg, _PlyrStar_apRing[i]);
        _PlyrStar_apRing[i] = 0;
        PlyrStarDelete(arg, _PlyrStar_apRingOutline[i]);
        _PlyrStar_apRing[i] = 0;
        PlyrStarDelete(arg, _PlyrStar_apArrow[i]);
        _PlyrStar_apArrow[i] = 0;
    }
    for (i = 0; i < 5; ++i) {
        PlyrStarDelete(arg, _PlyrStar_apPulse[i]);
        _PlyrStar_apPulse[i] = 0;
    }
    PlyrStarDelete(arg, _PlyrStar_pBallMarker);
    PlyrStarDelete(arg, _PlyrStar_pBallOutline);
    PlyrStarReleaseType();
}
void PlyrStarSetShown(unsigned char a, unsigned char b) {
    _PlyrStar_bShowRings = a;
    _PlyrStar_bShowArrows = b;
}
unsigned char PlyrStarGetRingsShown(void) {
    return _PlyrStar_bShowRings;
}
void PlyrStarUpdate(void) {
    Object_80039F5C *current = BallGetCurrentHolder();
    _PlyrStar_pBallMarker->mUnknown20 &= ~2;
    for (unsigned char i = 0; i < 9; ++i) {
        PlyrStar_t *item = _PlyrStar_apRing[i], *other = _PlyrStar_apArrow[i];
        unsigned char active = 0;
        if (item) {
            if (fn_800B65A0(0) != 255 || fn_800B65A0(1) != 255)
                item->mUnknown100 = PlyrStarFindPlayer(i, &active);
            if (active == 1) {
                Object_80039F5C *player = item->mUnknown100;
                if (player->mFlags & 0x2000000) {
                    PlyrStarStartPulse(item);
                    player->mFlags &= ~0x2000000;
                }
                PlyrStarSetPosition(item, (Vec2_t *)&player->mMotion.mPos, fn_801784C4());
                other->mUnknown20 |= 2;
                other->mUnknown4.mX = item->mUnknown4.mX;
                other->mUnknown4.mY = item->mUnknown4.mY;
                other->mUnknown4.mZ = item->mUnknown4.mZ;
                if (player == current) {
                    _PlyrStar_uBallPad = (unsigned char)item->mUnknown2C;
                    _PlyrStar_pBallMarker->mUnknown30 = item->mUnknown30;
                    _PlyrStar_pBallMarker->mUnknown20 |= 2;
                    _PlyrStar_pBallMarker->mUnknown4.mX = item->mUnknown4.mX;
                    _PlyrStar_pBallMarker->mUnknown4.mY = item->mUnknown4.mY;
                    _PlyrStar_pBallMarker->mUnknown4.mZ = 0.0f;
                    if (_PlyrStar_pBallMarker->mUnknown20 & 0x10)
                        _PlyrStar_pBallMarker->mUnknown14 = (_PlyrStar_pBallMarker->mUnknown14 - 0x16C16) & 0xFFFFFF;
                    else
                        _PlyrStar_pBallMarker->mUnknown14 = 0;
                    PlyrStarCopyState(_PlyrStar_pBallOutline, _PlyrStar_pBallMarker);
                }
            } else {
                item->mUnknown20 &= ~2;
                other->mUnknown20 &= ~2;
            }
            PlyrStarCopyState(_PlyrStar_apRingOutline[i], item);
        }
    }
    PlyrStarUpdatePulses();
}
int PlyrStarProjectOffscreen(Vector_80039F5C *input, Vector_80039F5C *out, int *angle, float *scale) {
    struct PlyrStarClip_t {
        float mX, mY, mZ, mW;
    };
    int result;
    MatSetStack(VptGetMatrixStack());
    MatPush();
    MatLoadSlot(4);
    PlyrStarClip_t point;
    Vector_80039F5C unused;
    PlyrStarClip_t original;
    unused.mX = input->mX;
    unused.mY = input->mY;
    unused.mZ = 0.5f;
    original.mX = input->mX;
    original.mY = input->mY;
    original.mZ = 0.5f;
    original.mW = 1.0f;
    Vec4Mat44Mul(&point, &original);
    if (point.mX < -point.mW || point.mX > point.mW || point.mY < -point.mW || !(point.mY <= point.mW)) {
        original.mX = point.mX;
        original.mY = point.mY;
        original.mZ = point.mZ;
        *angle = MathArcTan2(-point.mX, point.mY);
        float ratio = 1.0f;
        if (!(fabsf(point.mW) >= 1.0f)) {
            if (!(point.mW >= 0.0f))
                ratio = -1.0f;
        } else
            ratio = 1.0f / point.mW;
        point.mX *= ratio;
        point.mY *= ratio;
        float scaleBlend = Vec3Magnitude((Vector_80039F5C *)&original) - 10.25f;
        scaleBlend *= 0.11111111f;
        Vec2_t pair;
        pair.mX = point.mX;
        pair.mY = point.mY;
        float b = (Vec2Magnitude(&pair) - 1.0f) * 0.5f;
        if (!(original.mZ >= 0.0f))
            b = scaleBlend;
        else if (!(original.mZ > 1.0f))
            b = b * original.mZ + scaleBlend * (1.0f - original.mZ);
        if (!(b >= 0.0f))
            b = 0.0f;
        if (!(b <= 1.0f))
            b = 1.0f;
        scaleBlend = 1.0f - b;
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
        float amount = scaleBlend * 0.75f + 0.25f;
        if (!(amount >= 0.25f))
            amount = 0.25f;
        if (!(amount <= 1.0f))
            amount = 1.0f;
        *scale = amount;
        result = 1;
    } else
        result = 0;
    MatPop();
    return result;
}
void PlyrStarRegisterReplay(void) {
    _PlyrStar_iReplayBits = PlyrStarGetReplayBits();
    ReplayRegisterChannel(PlyrStarWriteReplayAll, PlyrStarReadReplayAll, _PlyrStar_iReplayBits * 10, "Stars");
}
PlyrStar_t *PlyrStarGetPulse(int index) {
    return _PlyrStar_apPulse[index];
}
void PlyrStarPlace(PlyrStar_t *item, Vector_80039F5C *point) {
    item->mUnknown4.mX = point->mX;
    item->mUnknown4.mY = point->mY;
    item->mUnknown4.mZ = point->mZ;
    if (fn_801784C4()) {
        item->mUnknown4.mX = -item->mUnknown4.mX;
        item->mUnknown4.mY = -item->mUnknown4.mY;
    }
    item->mUnknown20 |= 2;
}
unsigned int PlyrStarGetColor(int index) {
    float r = _PlyrStar_afColor[index][0];
    if (!(r <= 1.0f))
        r = 1.0f;
    unsigned char red = (int)(r * 255.0f);
    float g = _PlyrStar_afColor[index][1];
    if (!(g <= 1.0f))
        g = 1.0f;
    unsigned char green = (int)(g * 255.0f);
    float b = _PlyrStar_afColor[index][2];
    if (!(b <= 1.0f))
        b = 1.0f;
    unsigned char blue = (int)(b * 255.0f);
    float a = _PlyrStar_afColor[index][3];
    if (!(a <= 1.0f))
        a = 1.0f;
    return ((unsigned int)(int)(a * 255.0f) << 24) | (red << 16) | (green << 8) | blue;
}
void PlyrStarStartPulse(PlyrStar_t *source) {
    if (source) {
        PlyrStar_t *item = PlyrStarFindFreePulse();
        if (item) {
            item->mUnknown100 = source->mUnknown100;
            item->mUnknown20 |= 0x22;
            item->mUnknown14 = 0;
            item->mUnknown18 = 1.0f;
            item->mUnknown38 = PlyrStarGetPulseScale(item);
            item->mUnknown30 = source->mUnknown30;
            Vec2_t *point = (Vec2_t *)&item->mUnknown100->mMotion.mPos;
            PlyrStarSetPosition(item, point, fn_801784C4());
        }
    }
}
void PlyrStarLinkPlayer(int index, int ref) {
    PlyrStar_t *item = index == 255 ? _PlyrStar_apRing[8] : _PlyrStar_apRing[index];
    PlyrStarClearLinks();
    if (item) {
        item->mUnknown104 = ref;
        item->mUnknown20 |= 4;
    }
}
void PlyrStarClearLinks(void) {
    for (unsigned char i = 0; i < 9; ++i) {
        PlyrStar_t *item = _PlyrStar_apRing[i];
        if (item) {
            item->mUnknown104 = 0;
            item->mUnknown20 &= ~4;
        }
    }
}
Object_80039F5C *PlyrStarGetBallPlayer(void) {
    return _PlyrStar_pBallPlayer;
}
void PlyrStarSetBallRingEnabled(unsigned char value) {
    _PlyrStar_bBallRingEnabled = value;
}
}
