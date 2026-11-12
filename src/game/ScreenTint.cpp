/* Field marker state and the screen tint. The marker part keeps fifteen fixed beam groups on
   the field and a pool of small arrows placed at random in the level's quads, which pulse and
   fade over time; FieldMarker.cpp draws them. The tint part keeps two full-screen colour layers
   that tint the screen and fade between colours. */

#include "engine/viewport.h"
#include "engine/vec.h"
#include "game/FieldMarker.h"
#include "game/LevelData.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include <string.h>

extern "C" {
float fn_80237260(int stream);
float fn_802276E8(void *pA, void *pB);
extern LevelData_t *gLevelData;
extern float gFrameTimeScale;
}

FieldMarkerBeamSet_t gFieldMarkerBeamSets[15] = {
    { { -36.75f, 41.0f, 0.15f }, 6.0f },
    { { -35.0f, 34.0f, 0.15f }, 10.0f },
    { { -33.75f, 27.75f, 0.15f }, 5.0f },
    { { -33.5f, 21.0f, 0.15f }, 2.0f },
    { { -33.25f, 13.75f, 0.15f }, 5.0f },
    { { -31.25f, 6.0f, 0.15f }, 18.0f },
    { { -28.2f, 0.0f, 0.15f }, 20.0f },
    { { -25.0f, -6.0f, 0.15f }, 18.0f },
    { { -22.25f, -12.25f, 0.15f }, 20.0f },
    { { -19.5f, -18.5f, 0.15f }, 20.0f },
    { { -17.0f, -25.0f, 0.15f }, 20.0f },
    { { -14.75f, -31.25f, 0.15f }, 17.0f },
    { { -12.25f, -37.25f, 0.15f }, 16.0f },
    { { -11.0f, -42.5f, 0.15f }, 6.0f },
    { { -10.5f, -49.0f, 0.15f }, 6.0f },
};

extern "C" {
FieldMarkerArrow_t *gFieldMarkerArrows = 0;
}
static unsigned char _FieldMarker_bArrowsReady = 0;

/* Maps x from the range x0..x1 onto y0..y1. */
static inline float MapRange(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

extern "C" {
unsigned int gFieldMarkerArrowCount;

static void _FieldMarkerInitBeams(void)
{
    for (int i = 0; i < 15; i++) {
        FieldMarkerBeamSet_t *pSet = &gFieldMarkerBeamSets[i];
        memset(pSet->mUnknown10, 0, sizeof(pSet->mUnknown10));
        pSet->mUnknown10[1].mUnknown0 = 12.0f;
        pSet->mUnknown10[1].mUnknown4 = 1.0f;
        pSet->mUnknown10[1].mUnknown8 = 4.0f;
        pSet->mUnknown10[1].mUnknown10 = 1;
        pSet->mUnknown10[2].mUnknown0 = 12.0f;
        pSet->mUnknown10[2].mUnknown8 = 4.0f;
    }
}

static void _FieldMarkerUpdateBeams(float dt)
{
    for (unsigned int i = 0; i < 15; i++) {
        FieldMarkerBeamSet_t *pSet = &gFieldMarkerBeamSets[i];
        for (unsigned int j = 0; j < 2; j++) {
            FieldMarkerBeam_t *pBeam = &pSet->mUnknown10[j];
            float time = pBeam->mUnknownC + dt;
            pBeam->mUnknownC = time;
            switch (pBeam->mUnknown10) {
            case 0:
                pBeam->mUnknown0 = MapRange(time, 0.0f, 275.0f, 1.0f, 12.0f);
                pBeam->mUnknown4 = MapRange(time > 100.0f ? 100.0f : time, 0.0f, 100.0f, 0.35f, 1.0f);
                pBeam->mUnknown8 = MapRange(time, 0.0f, 275.0f, 0.0f, 4.0f);
                if (time > 275.0f) {
                    pBeam->mUnknown10 = 1;
                    pBeam->mUnknownC = 0.0f;
                    pSet->mUnknown10[2].mUnknownC = 0.0f;
                }
                break;
            case 1:
                pBeam->mUnknown0 = MapRange(time > 250.0f ? 250.0f : time, 0.0f, 250.0f, 12.0f, 1.0f);
                pBeam->mUnknown4 = MapRange(time > 115.0f ? 115.0f : time, 0.0f, 115.0f, 0.95f, 0.0f);
                pBeam->mUnknown8 = MapRange(time, 0.0f, 275.0f, 4.0f, 0.0f);
                if (time > 275.0f) {
                    pBeam->mUnknown10 = 0;
                    pBeam->mUnknownC = 0.0f;
                }
                break;
            }
        }
        pSet->mUnknown10[2].mUnknown4 = 0.0f;
    }
}

static void _FieldMarkerPlaceArrow(FieldMarkerArrow_t *pArrow)
{
    Vector_80039F5C side, across, toSecond, toThird, toFourth, point;
    LevelQuad_t *pQuad = (LevelQuad_t *)gLevelData->mUnknown124 + fn_802372EC(1, gLevelData->mUnknown120);
    float u = fn_80237260(1);
    float v = fn_80237260(1);

    fn_802276B4(&toSecond, &pQuad->mPoint[1], &pQuad->mPoint[0]);
    fn_802276B4(&toThird, &pQuad->mPoint[2], &pQuad->mPoint[0]);
    fn_802276B4(&toFourth, &pQuad->mPoint[3], &pQuad->mPoint[0]);
    float third = fn_802276E8(&toSecond, &toThird);
    side = toSecond;
    if (fn_802276E8(&toSecond, &toFourth) > third)
        across = toThird;
    else
        across = toFourth;
    fn_80227264(&side, &side, u);
    fn_80227264(&across, &across, v);
    fn_8022765C(&point, &side, &across);
    fn_8022765C(&point, &point, &pQuad->mPoint[0]);
    pArrow->mPosition[0] = point.mX;
    pArrow->mPosition[1] = point.mY;
    pArrow->mPosition[2] = point.mZ;
}

static void _FieldMarkerInitArrows(void)
{
    gFieldMarkerArrows = (FieldMarkerArrow_t *)fn_801D2B7C(100 * sizeof(FieldMarkerArrow_t), 0, 0);
    gFieldMarkerArrowCount = 0;
    _FieldMarker_bArrowsReady = 1;
}

static void _FieldMarkerShutdownArrows(void)
{
    _FieldMarker_bArrowsReady = 0;
    fn_801D2BD0(gFieldMarkerArrows);
    gFieldMarkerArrowCount = 0;
}

static void _FieldMarkerUpdateArrows(float dt)
{
    if (gFieldMarkerArrowCount == 0) {
        for (unsigned int i = 0; i < 100; i++) {
            FieldMarkerArrow_t *pArrow = &gFieldMarkerArrows[i];
            pArrow->mUnknownC = fn_80237260(1);
            pArrow->mUnknown10 = 1.0f;
            pArrow->mUnknown14 = 0;
            _FieldMarkerPlaceArrow(pArrow);
            gFieldMarkerArrowCount++;
        }
        return;
    }
    for (unsigned int i = 0; i < gFieldMarkerArrowCount; i++) {
        FieldMarkerArrow_t *pArrow = &gFieldMarkerArrows[i];
        float step = gFrameTimeScale * 0.2f * dt;
        if (pArrow->mUnknown14 == 0) {
            pArrow->mUnknownC += step;
            if (pArrow->mUnknownC > 1.0f) {
                pArrow->mUnknownC = 1.0f;
                pArrow->mUnknown14 = 1;
            }
        } else {
            pArrow->mUnknownC -= step;
            pArrow->mUnknown10 -= step;
            if (pArrow->mUnknownC < 0.0f) {
                pArrow->mUnknownC = 0.0f;
                pArrow->mUnknown10 = 1.0f;
                pArrow->mUnknown14 = 0;
                _FieldMarkerPlaceArrow(pArrow);
            }
        }
    }
}

void ScreenTintLerp(unsigned int a, unsigned int b, unsigned int *pColor, float *pValue, float t, float x,
                    float y)
{
    unsigned int ar = (a >> 16) & 255;
    unsigned int ag = (a >> 8) & 255;
    unsigned int ab = a & 255;
    unsigned int bg = (b >> 8) & 255;
    unsigned int bb = b & 255;
    unsigned int br = (b >> 16) & 255;

    *pValue = x * (1.0f - t) + y * t;
    unsigned int r = (unsigned int)(ar * (1.0f - t) + br * t);
    unsigned int g = (unsigned int)(ag * (1.0f - t) + bg * t);
    unsigned int blue = (unsigned int)(ab * (1.0f - t) + bb * t);
    *pColor = (r << 16) + (g << 8) + blue;
}
}

struct ScreenTintLayer_t {
    char mUnknown0[0x14];
    unsigned int mUnknown14;
    float mUnknown18;
    unsigned int mUnknown1C;
    float mUnknown20;
    unsigned int mUnknown24;
    unsigned int mUnknown28;
    int mUnknown2C;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    unsigned char mUnknown32;
};

extern "C" {
void FxTintDrawAlpha(int a, unsigned int color, float value);
void FxTintDrawSrcColor(int a, unsigned int color, float value);
int GlibRenderGetBin(int index);
int ObjNewType_(int a, int size, int c, void (*pInit)(ScreenTintLayer_t *, int *),
                void (*pRelease)(ScreenTintLayer_t *));
int ObjDelType(int a);
void ObjSetListObjFunc(int handle, int a, int b, int (*pCallback)(ScreenTintLayer_t *));
int ObjNewInList(int handle, int a, int b, int *pDesc);
void ObjRemoveFromList(int handle, ScreenTintLayer_t *pObject);
void ObjSetPriority(int handle, ScreenTintLayer_t *pObject, unsigned short b);
}

static int _ScreenTint_iBins[2] = { 15, 15 };
static ScreenTintLayer_t *_ScreenTint_pLayers[2];

extern "C" {
int ScreenTintDraw(ScreenTintLayer_t *pObject);

void ScreenTintInit(int handle)
{
    unsigned int i;

    ObjNewType_(20, sizeof(ScreenTintLayer_t), 2, 0, 0);
    ObjSetListObjFunc(handle, 20, 0, ScreenTintDraw);
    for (i = 0; i < 2; i++) {
        _ScreenTint_pLayers[i] = (ScreenTintLayer_t *)ObjNewInList(handle, 20, 0, 0);
        ObjSetPriority(handle, _ScreenTint_pLayers[i], _ScreenTint_iBins[i]);
        _ScreenTint_pLayers[i]->mUnknown30 = 1;
        _ScreenTint_pLayers[i]->mUnknown32 = i;
        _ScreenTint_pLayers[i]->mUnknown2C = 1;
    }
}

void ScreenTintShutdown(int handle)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        ObjRemoveFromList(handle, _ScreenTint_pLayers[i]);
        VptTrashObject((int)_ScreenTint_pLayers[i]);
        _ScreenTint_pLayers[i] = 0;
    }
    VptFlushObjectTrashSync();
    ObjDelType(20);
}

int ScreenTintDraw(ScreenTintLayer_t *pObject)
{
    unsigned int color;
    float value;
    int result;

    if (pObject->mUnknown31 != 0) {
        color = pObject->mUnknown14;
        value = pObject->mUnknown18;
        if (pObject->mUnknown24 < pObject->mUnknown28) {
            pObject->mUnknown24++;
            ScreenTintLerp(pObject->mUnknown14, pObject->mUnknown1C, &color, &value,
                        (float)pObject->mUnknown24 / (float)pObject->mUnknown28, pObject->mUnknown18,
                        pObject->mUnknown20);
            if (pObject->mUnknown24 == pObject->mUnknown28) {
                pObject->mUnknown14 = pObject->mUnknown1C;
                pObject->mUnknown18 = pObject->mUnknown20;
                if (pObject->mUnknown1C == 0 || pObject->mUnknown20 == 0.0f) {
                    pObject->mUnknown31 = 0;
                }
            }
        }
        result = GlibRenderGetBin(_ScreenTint_iBins[pObject->mUnknown32]);
        switch (pObject->mUnknown2C) {
        case 0:
            FxTintDrawAlpha(result, color, value);
            break;
        case 1:
            FxTintDrawSrcColor(result, color, value);
            break;
        }
    }
    return 0;
}

void ScreenTintSetActive(int index, unsigned char value)
{
    _ScreenTint_pLayers[index]->mUnknown31 = value;
}

void ScreenTintSetMode(int index, int value)
{
    _ScreenTint_pLayers[index]->mUnknown2C = value;
}

void ScreenTintFadeTo(int index, unsigned int color, float value, unsigned int count)
{
    unsigned int currentColor;
    float currentValue;

    if (_ScreenTint_pLayers[index]->mUnknown24 < _ScreenTint_pLayers[index]->mUnknown28) {
        currentColor = _ScreenTint_pLayers[index]->mUnknown14;
        currentValue = _ScreenTint_pLayers[index]->mUnknown18;
        _ScreenTint_pLayers[index]->mUnknown24++;
        ScreenTintLerp(_ScreenTint_pLayers[index]->mUnknown14, _ScreenTint_pLayers[index]->mUnknown1C, &currentColor,
                    &currentValue,
                    (float)_ScreenTint_pLayers[index]->mUnknown24 / (float)_ScreenTint_pLayers[index]->mUnknown28,
                    _ScreenTint_pLayers[index]->mUnknown18, _ScreenTint_pLayers[index]->mUnknown20);
        _ScreenTint_pLayers[index]->mUnknown14 = currentColor;
        _ScreenTint_pLayers[index]->mUnknown18 = currentValue;
    }
    _ScreenTint_pLayers[index]->mUnknown1C = color;
    _ScreenTint_pLayers[index]->mUnknown20 = value;
    _ScreenTint_pLayers[index]->mUnknown28 = count;
    _ScreenTint_pLayers[index]->mUnknown24 = 0;
}

unsigned char ScreenTintIsActive(int index)
{
    return _ScreenTint_pLayers[index]->mUnknown31;
}
}
