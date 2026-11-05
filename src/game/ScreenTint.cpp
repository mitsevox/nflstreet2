/* Two full-screen colour layers that tint the screen and fade between colours. */

#include "engine/cu_80227F14.h"
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
void fn_80196EF8(int a, unsigned int color, float value);
void fn_80196F20(int a, unsigned int color, float value);
int fn_801CECCC(int index);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(ScreenTintLayer_t *, int *),
                void (*pRelease)(ScreenTintLayer_t *));
int fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(ScreenTintLayer_t *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, ScreenTintLayer_t *pObject);
void fn_801DD3AC(int handle, ScreenTintLayer_t *pObject, unsigned short b);
}

static int _ScreenTint_iBins[2] = { 15, 15 };
static ScreenTintLayer_t *_ScreenTint_pLayers[2];

extern "C" {
int ScreenTintDraw(ScreenTintLayer_t *pObject);

void ScreenTintInit(int handle)
{
    unsigned int i;

    fn_801DCF0C(20, sizeof(ScreenTintLayer_t), 2, 0, 0);
    fn_801DD0C8(handle, 20, 0, ScreenTintDraw);
    for (i = 0; i < 2; i++) {
        _ScreenTint_pLayers[i] = (ScreenTintLayer_t *)fn_801DD268(handle, 20, 0, 0);
        fn_801DD3AC(handle, _ScreenTint_pLayers[i], _ScreenTint_iBins[i]);
        _ScreenTint_pLayers[i]->mUnknown30 = 1;
        _ScreenTint_pLayers[i]->mUnknown32 = i;
        _ScreenTint_pLayers[i]->mUnknown2C = 1;
    }
}

void ScreenTintShutdown(int handle)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        fn_801DD320(handle, _ScreenTint_pLayers[i]);
        fn_80228D58((int)_ScreenTint_pLayers[i]);
        _ScreenTint_pLayers[i] = 0;
    }
    fn_80228E18();
    fn_801DCF8C(20);
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
        result = fn_801CECCC(_ScreenTint_iBins[pObject->mUnknown32]);
        switch (pObject->mUnknown2C) {
        case 0:
            fn_80196EF8(result, color, value);
            break;
        case 1:
            fn_80196F20(result, color, value);
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
