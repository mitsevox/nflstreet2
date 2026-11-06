/* Two full-screen colour layers that tint the screen and fade between colours. */

#include "engine/viewport.h"
#include "game/fn_80147908.h"

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
            fn_80147908(pObject->mUnknown14, pObject->mUnknown1C, &color, &value,
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
        fn_80147908(_ScreenTint_pLayers[index]->mUnknown14, _ScreenTint_pLayers[index]->mUnknown1C, &currentColor,
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
