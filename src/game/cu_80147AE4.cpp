#include "engine/cu_80227F14.h"

struct Object_80147AE4 {
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
void fn_80147908(unsigned int a, unsigned int b, unsigned int *pColor, float *pValue, float t, float x,
                 float y);
void fn_80196EF8(void *p, unsigned int color, float value);
void fn_80196F20(void *p, unsigned int color, float value);
void *fn_801CECCC(int index);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(Object_80147AE4 *),
                void (*pRelease)(Object_80147AE4 *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Object_80147AE4 *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, Object_80147AE4 *pObject);
void fn_801DD3AC(int handle, Object_80147AE4 *pObject, unsigned short b);
}

static int lbl_803EB28C[2] = { 15, 15 };
static Object_80147AE4 *lbl_803ECA1C[2];

extern "C" {
int fn_80147C14(Object_80147AE4 *pObject);

void fn_80147AE4(int handle)
{
    unsigned int i;

    fn_801DCF0C(20, sizeof(Object_80147AE4), 2, 0, 0);
    fn_801DD0C8(handle, 20, 0, fn_80147C14);
    for (i = 0; i < 2; i++) {
        lbl_803ECA1C[i] = (Object_80147AE4 *)fn_801DD268(handle, 20, 0, 0);
        fn_801DD3AC(handle, lbl_803ECA1C[i], lbl_803EB28C[i]);
        lbl_803ECA1C[i]->mUnknown30 = 1;
        lbl_803ECA1C[i]->mUnknown32 = i;
        lbl_803ECA1C[i]->mUnknown2C = 1;
    }
}

void fn_80147BA8(int handle)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        fn_801DD320(handle, lbl_803ECA1C[i]);
        fn_80228D58((int)lbl_803ECA1C[i]);
        lbl_803ECA1C[i] = 0;
    }
    fn_80228E18();
    fn_801DCF8C(20);
}

int fn_80147C14(Object_80147AE4 *pObject)
{
    unsigned int color;
    float value;
    void *p;

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
        p = fn_801CECCC(lbl_803EB28C[pObject->mUnknown32]);
        switch (pObject->mUnknown2C) {
        case 0:
            fn_80196EF8(p, color, value);
            break;
        case 1:
            fn_80196F20(p, color, value);
            break;
        }
    }
    return 0;
}

void fn_80147D4C(int index, unsigned char value)
{
    lbl_803ECA1C[index]->mUnknown31 = value;
}

void fn_80147D60(int index, int value)
{
    lbl_803ECA1C[index]->mUnknown2C = value;
}

void fn_80147D74(int index, unsigned int color, float value, unsigned int count)
{
    unsigned int currentColor;
    float currentValue;

    if (lbl_803ECA1C[index]->mUnknown24 < lbl_803ECA1C[index]->mUnknown28) {
        currentColor = lbl_803ECA1C[index]->mUnknown14;
        currentValue = lbl_803ECA1C[index]->mUnknown18;
        lbl_803ECA1C[index]->mUnknown24++;
        fn_80147908(lbl_803ECA1C[index]->mUnknown14, lbl_803ECA1C[index]->mUnknown1C, &currentColor,
                    &currentValue,
                    (float)lbl_803ECA1C[index]->mUnknown24 / (float)lbl_803ECA1C[index]->mUnknown28,
                    lbl_803ECA1C[index]->mUnknown18, lbl_803ECA1C[index]->mUnknown20);
        lbl_803ECA1C[index]->mUnknown14 = currentColor;
        lbl_803ECA1C[index]->mUnknown18 = currentValue;
    }
    lbl_803ECA1C[index]->mUnknown1C = color;
    lbl_803ECA1C[index]->mUnknown20 = value;
    lbl_803ECA1C[index]->mUnknown28 = count;
    lbl_803ECA1C[index]->mUnknown24 = 0;
}

unsigned char fn_80147E80(int index)
{
    return lbl_803ECA1C[index]->mUnknown31;
}
}
