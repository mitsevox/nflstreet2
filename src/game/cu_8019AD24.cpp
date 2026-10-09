#include "engine/cu_80227F14.h"
#include "game/fn_801EF390.h"
#include "game/fn_8021216C.h"
#include "game/Object_80235588.h"

struct Element_8019AD5C {
    char mUnknown0[0x30];
};

struct Object_8019AD5C {
    char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mUnknown10[4];
    void *mpUnknown14;
    int mUnknown18[5];
    Object_80235588 mUnknown2C[6];
    int mUnknown4AC[5];
    Element_8019AD5C mUnknown4C0[5];
};

struct Entry_802EE948 {
    const char *mpName;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    int mUnknown10;
    float mUnknown14;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
};

struct Record_802EE9D4 {
    float mUnknown0[3];
    float mUnknownC;
};

extern "C" {
void fn_80044114(void);
void *fn_800A336C(void);
int fn_800A3398(void);
void fn_801A5104(void);
int fn_801C657C(void);
void fn_801D0470(int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0C58(void *a);
int fn_801DCF0C(int a, int size, int c, void (*pInit)(Object_8019AD5C *, int *),
                void (*pRelease)(Object_8019AD5C *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Object_8019AD5C *));
int fn_801DD268(int handle, int a, int b, int *pDesc);
void fn_801DD320(int handle, int item);
void fn_801DD3AC(int handle, int item, int a);
void fn_80234DFC(int a, void *pB, int c, int d, const char *pName, int e);
void fn_80234EA0(void *p, int a);
void fn_802353D8(void *p, int flags);
void fn_802353F8(void *p, int a);
void fn_80235588(void *p, int a);
void fn_802355E4(void *p);
void fn_80235630(void *p, int a);
void fn_80235740(void *p, int a);
void fn_80235764(void *p, int a);
void fn_80235B6C(void *p, void *q, int a);
void fn_80235C48(void *p, int a);
void fn_80235C4C(int a, void *p, float b);
void fn_80235C90(void *p, int a, float b, float c, float d, float e);
void fn_80235D0C(void *p, int a);
void fn_80235DB8(int a);
}

static Entry_802EE948 lbl_802EE948[5] = {
    { "Base", 1, 1, 0.0f, 0x103, 0.51f, 0, 1 },
    { "Overlay", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Lines", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Degradation", 1, 1, 0.01f, 0x10B, 0.51f, 0, 1 },
    { "Shadow", 1, 1, 0.0f, 0x40000B, 0.51f, 0, 1 },
};
static Record_802EE9D4 lbl_802EE9D4[1] = {
    { { 0.0f, 0.0f, 0.0f }, 1.0f },
};
static Desc_802EE9E4 lbl_802EE9E4 = { 5, 1, -4.0f, 0, 0, 1 };
static int lbl_803EB7B0 = 0;
static float lbl_803ECBF0;

extern "C" {
int fn_8019AD24(void *pData, int index)
{
    int handle = fn_801EF390(pData, index, 1);

    fn_80235DB8(handle);
    return handle;
}

void fn_8019AD5C(Object_8019AD5C *pObject, int *pArgs)
{
    unsigned int i;

    pObject->mUnknownC = pObject->mUnknown8 = pObject->mUnknown4 = 0.0f;
    pObject->mpUnknown14 = (void *)pArgs[0];
    for (i = 0; i < 5; i++) {
        pObject->mUnknown18[i] = pArgs[i + 1];
        pObject->mUnknown4AC[i] = fn_8019AD24(pObject->mpUnknown14, pObject->mUnknown18[i]);
        fn_80234DFC(pObject->mUnknown4AC[i], &pObject->mUnknown4C0[i], 0, 0, lbl_802EE948[i].mpName,
                    lbl_802EE948[i].mUnknown4);
        fn_8021216C(&pObject->mUnknown4C0[i], &lbl_802EE9E4);
        fn_80235588(&pObject->mUnknown2C[i], 6);
        fn_80235630(&pObject->mUnknown2C[i], pObject->mUnknown4AC[i]);
        fn_80235B6C(&pObject->mUnknown2C[i], &pObject->mUnknown4C0[i], 1);
        fn_802353D8(&pObject->mUnknown2C[i], lbl_802EE948[i].mUnknown10);
        fn_80235C48(&pObject->mUnknown2C[i], lbl_802EE948[i].mUnknown8);
        fn_80235D0C(&pObject->mUnknown2C[i], lbl_802EE948[i].mUnknown18);
        fn_802353F8(&pObject->mUnknown2C[i], 0);
    }
    fn_80235588(&pObject->mUnknown2C[5], 6);
    fn_80235630(&pObject->mUnknown2C[5], pObject->mUnknown4AC[4]);
    fn_80235B6C(&pObject->mUnknown2C[5], &pObject->mUnknown4C0[4], 1);
    fn_80235C48(&pObject->mUnknown2C[5], lbl_802EE948[4].mUnknown8);
    fn_802353F8(&pObject->mUnknown2C[5], 0x20000000);
    fn_802353D8(&pObject->mUnknown2C[5], 0x60040B);
    fn_80235D0C(&pObject->mUnknown2C[5], lbl_802EE948[4].mUnknown18);
}

void fn_8019AEE8(Object_8019AD5C *pObject)
{
    unsigned int i;

    for (i = 0; i < 5; i++) {
        fn_802355E4(&pObject->mUnknown2C[i]);
    }
    fn_802355E4(&pObject->mUnknown2C[5]);
    for (i = 0; i < 5; i++) {
        fn_80234EA0(&pObject->mUnknown4C0[i], lbl_802EE948[i].mUnknown4);
        fn_801F010C(pObject->mpUnknown14, pObject->mUnknown18[i]);
    }
}

void fn_8019AF7C(Object_8019AD5C *pObject, int index, void *pPos, float scale)
{
    Object_80235588 *pSub = &pObject->mUnknown2C[index];
    int handle;

    if (pObject->mUnknown4AC[index] != 0 && lbl_802EE948[index].mUnknown19 != 0) {
        handle = fn_801C657C();
        if (pPos != 0) {
            fn_801D04C4();
            fn_801D0C58(pPos);
        }
        fn_80235740(pSub, handle);
        fn_80235C90(pSub, handle, 1.0f, 1.0f, 1.0f, scale * lbl_802EE948[index].mUnknown14);
        if (lbl_802EE948[index].mUnknownC > 0.0f) {
            fn_80235C4C(handle, pSub, lbl_802EE948[index].mUnknownC);
        }
        fn_80235764(pSub, handle);
        if (pPos != 0) {
            fn_801D0544();
        }
    }
}

void fn_8019B088(Object_8019AD5C *pObject, float scale, void *pPos)
{
    Object_80235588 *pSub = &pObject->mUnknown2C[5];
    int handle;

    if (pObject->mUnknown4AC[4] != 0 && lbl_802EE948[4].mUnknown19 != 0) {
        handle = fn_801C657C();
        if (pPos != 0) {
            fn_801D04C4();
            fn_801D0C58(pPos);
        }
        fn_80235740(pSub, handle);
        fn_80235C90(pSub, handle, 0.5f, 0.5f, 0.5f, scale * lbl_802EE948[4].mUnknown14);
        if (lbl_802EE948[4].mUnknownC > 0.0f) {
            fn_80235C4C(handle, pSub, lbl_802EE948[4].mUnknownC);
        }
        fn_80235764(pSub, handle);
        if (pPos != 0) {
            fn_801D0544();
        }
    }
}

int fn_8019B174(Object_8019AD5C *pObject)
{
    unsigned int i;

    fn_801D0470(fn_80228668());
    fn_801D04C4();
    fn_801D0C58(&pObject->mUnknown4);
    fn_8019AF7C(pObject, 0, 0, 1.0f);
    fn_8019AF7C(pObject, 1, 0, 1.0f);
    for (i = 0; i < sizeof(lbl_802EE9D4) / sizeof(lbl_802EE9D4[0]); i++) {
        float scale = lbl_802EE9D4[i].mUnknownC;
        fn_8019AF7C(pObject, 2, &lbl_802EE9D4[i], scale);
    }
    fn_8019AF7C(pObject, 3, 0, lbl_803ECBF0);
    fn_80044114();
    fn_8019AF7C(pObject, 4, 0, 1.0f);
    fn_8019B088(pObject, 1.0f, 0);
    fn_801D0544();
    fn_801A5104();
    return 0;
}

void fn_8019B25C(int handle)
{
    int args[6];
    unsigned int i;

    lbl_803ECBF0 = 1.0f;
    fn_801DCF0C(7, sizeof(Object_8019AD5C), 1, fn_8019AD5C, fn_8019AEE8);
    fn_801DD0C8(handle, 7, 0, fn_8019B174);
    args[0] = (int)fn_800A336C();
    for (i = 0; i < 5; i++) {
        args[i + 1] = fn_800A3398() + i;
    }
    lbl_803EB7B0 = fn_801DD268(handle, 7, 0, args);
    fn_801DD3AC(handle, lbl_803EB7B0, 1);
}

void fn_8019B320(int handle)
{
    if (lbl_803EB7B0 != 0) {
        fn_801DD320(handle, lbl_803EB7B0);
        fn_80228D58(lbl_803EB7B0);
    }
    fn_80228E18();
    fn_801DCF8C(7);
    lbl_803EB7B0 = 0;
}
}
