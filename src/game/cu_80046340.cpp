#include "engine/cu_80227F14.h"
#include "game/fn_801EF390.h"

struct Object_80046340 {
    char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mUnknown10[8];
    void *mpUnknown18;
    int mUnknown1C;
    int mUnknown20;
    char mUnknown24[0x6C0];
    unsigned char mUnknown6E4[10][192];
    unsigned char mUnknownE64[48];
};

struct Object_800463D8 {
    char mUnknown0[0x14];
    Object_80046340 *mpUnknown14;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A3374(void);
int fn_80146EDC(unsigned int index);
float fn_80146F0C(unsigned int index);
float fn_80146F40(unsigned int index);
void fn_801A582C(Object_80046340 *pObject);
void fn_801A5CA4(Object_80046340 *pObject);
int fn_801A5D0C(void *pObject);
int fn_801A5E90(void *pObject);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(void *), void (*pRelease)(void *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(void *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, void *pItem);
void fn_801DD3AC(int handle, void *pItem, int b);
void fn_80234DCC(int a, void *p, const char *pName, int b);
void fn_80234EA0(void *p, int a);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235DB8(int a);
}

static Object_80046340 *lbl_803EA4B0 = 0;
static Object_800463D8 *lbl_803EA4B4 = 0;

extern "C" {
void fn_80046340(void)
{
    void *pData = fn_800A336C();
    int index = fn_800A3374();
    int handle = fn_801EF390(pData, index, 1);
    Object_80046340 *pObject;

    fn_80235DB8(handle);
    pObject = lbl_803EA4B0;
    pObject->mpUnknown18 = pData;
    pObject->mUnknown1C = index;
    pObject->mUnknown20 = handle;
    fn_80234DCC(handle, pObject->mUnknownE64, "Environment", 1);
}

int fn_800463B4(void *pObject)
{
    fn_801A5E90(pObject);
    return 0;
}

int fn_800463D8(void *pObject)
{
    fn_801A5D0C(pObject);
    return 0;
}

void fn_800463FC(int handle)
{
    Object_80046340 *pObject;

    fn_801DCF0C(6, sizeof(Object_80046340), 1, 0, 0);
    fn_801DCF0C(25, sizeof(Object_800463D8), 1, 0, 0);
    fn_801DD0C8(handle, 6, 0, fn_800463B4);
    lbl_803EA4B0 = (Object_80046340 *)fn_801DD268(handle, 6, 0, 0);
    fn_801DD0C8(handle, 25, 0, fn_800463D8);
    lbl_803EA4B4 = (Object_800463D8 *)fn_801DD268(handle, 25, 0, 0);
    fn_801DD3AC(handle, lbl_803EA4B0, 4);
    lbl_803EA4B4->mpUnknown14 = lbl_803EA4B0;
    fn_801DD3AC(handle, lbl_803EA4B4, 12);
    fn_80046340();
    pObject = lbl_803EA4B0;
    pObject->mUnknownC = pObject->mUnknown8 = pObject->mUnknown4 = 0.0f;
    fn_801A582C(pObject);
}

void fn_80046504(int handle)
{
    fn_801A5CA4(lbl_803EA4B0);
    fn_80234EA0(lbl_803EA4B0->mUnknownE64, 1);
    fn_801F010C(lbl_803EA4B0->mpUnknown18, lbl_803EA4B0->mUnknown1C);
    fn_801DD320(handle, lbl_803EA4B0);
    fn_80228D58((int)lbl_803EA4B0);
    fn_801DD320(handle, lbl_803EA4B4);
    fn_80228D58((int)lbl_803EA4B4);
    fn_80228E18();
    fn_801DCF8C(6);
    lbl_803EA4B0 = 0;
    fn_801DCF8C(25);
    lbl_803EA4B4 = 0;
}

void fn_8004659C(void)
{
    unsigned int i;
    void *pElement;
    float a;
    float b;
    int state;
    float value;

    for (i = 0; i < 10; i++) {
        pElement = lbl_803EA4B0->mUnknown6E4[i];
        a = fn_80146F0C(i);
        b = fn_80146F40(i);
        state = fn_80146EDC(i);
        if (a == b) {
            if (state == 1) {
                value = 0.5f;
            } else {
                value = 1.0f;
            }
        } else if (state == 1) {
            value = a * -0.5f / b + 1.0f;
        } else {
            value = a * 0.5f / b + 0.5f;
        }
        fn_80235C90(pElement, 0, 1.0f, 1.0f, 1.0f, value * 0.5f);
    }
}
}
