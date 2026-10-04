#include "game/fn_8017F584.h"
#include "game/fn_801EF390.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXStruct.h>

struct Element_8019CE3C {
    char mUnknown0[0x28];
};

struct Object_80233EAC {
    int mUnknown0[5];
};

struct Desc_80233D64 {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    char mUnknown10[0x44];
    int mUnknown54;
    char mUnknown58[4];
    int mUnknown5C;
    char mUnknown60[0x4C];
    int mUnknownAC;
    char mUnknownB0[0x40];
};

struct Object_8023417C {
    char mUnknown0[0x18];
    int mUnknown18;
};

struct Object_80144310 {
    char mUnknown0[0xC];
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
};

struct Object_8019CE3C {
    char mUnknown0[4];
    char mUnknown4[0x10];
    int mUnknown14;
    void *mpUnknown18;
    char mUnknown1C[4];
    Mtx44 mUnknown20;
    char mUnknown60[0x224];
    char mUnknown284[8];
    float mUnknown28C;
    char mUnknown290[4];
    Object_80144310 *mpUnknown294;
    float mUnknown298;
    float mUnknown29C;
    float mUnknown2A0;
    char mUnknown2A4[8];
    char mUnknown2AC[4];
};

extern "C" {
int fn_80027DF0(void);
unsigned char fn_80054D24(int index);
int fn_80144310(void *p, Object_80144310 *pObject, float *a, float *b);
int fn_801486A0(void);
void fn_801A5434(void *p, int a);
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0CFC(float a);
void fn_8020FA38(int a, void *b);
void fn_802100C0(void *p, int a);
void fn_80210114(void *p);
void fn_80210388(void);
void fn_80210654(Object_8023417C *pObject);
void fn_80210BA4(void *p);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_80210D10(int a, int b, int c);
void fn_80211350(void);
void fn_80211E08(Element_8019CE3C *pElement, int a);
void fn_80211EFC(Element_8019CE3C *pElement);
void fn_80211FF0(void);
void fn_80212018(const char *pName, Element_8019CE3C *pElement);
void fn_80233D64(Object_80233EAC *pObject, Desc_80233D64 *pDesc, const char *pName, int a,
                 void *pData, int b);
void fn_80233FCC(Object_80233EAC *pObject);
int fn_80234144(Object_80233EAC *pObject, void *p);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int a);
int fn_80234D4C(float *pBox, void *m, void *p, void *q);
void *fn_80236384(int a);
int fn_80236B98(int a, float x, float y, float z);
void fn_80236C10(int a, float *p, float *q);
void fn_8024FB58(int a, GXColor color);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
}

static float lbl_802F2574[8] = { -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f };
static Desc_80233D64 lbl_802F2594 = { 0.00390625f, 1500, 0, 13, { 0 }, 500, { 0 }, 14, { 0 }, 0xFFFF };
static Element_8019CE3C lbl_803653E4[2];
static Object_80233EAC lbl_80365434;
static unsigned char lbl_803EB7C0[2] = { 0, 0 };

extern "C" {
void fn_8019CE3C(Object_8019CE3C *pObject)
{
    int value;

    fn_80211E08(&lbl_803653E4[0], fn_801EF390(pObject->mpUnknown18, 15, 1));
    lbl_803EB7C0[0] = 1;
    value = fn_801486A0();
    if (value == 1) {
        fn_80211E08(&lbl_803653E4[1], fn_801EF390(pObject->mpUnknown18, 16, 1));
        lbl_803EB7C0[1] = 1;
    }
    fn_80233D64(&lbl_80365434, &lbl_802F2594, "BALL", 0, pObject->mpUnknown18, 0);
}

void fn_8019CEE8(Object_8019CE3C *pObject)
{
    fn_80233FCC(&lbl_80365434);
    fn_80211EFC(&lbl_803653E4[0]);
    lbl_803EB7C0[0] = 0;
    if (lbl_803EB7C0[1] != 0) {
        fn_80211EFC(&lbl_803653E4[1]);
        lbl_803EB7C0[1] = 0;
    }
    fn_801F010C(pObject->mpUnknown18, 15);
}

void fn_8019CF5C(Object_8019CE3C *pObject, int index)
{
    Object_8023417C *pResult;

    pObject->mUnknown28C = 1.0f;
    fn_80211FF0();
    fn_80212018("model", &lbl_803653E4[index]);
    pResult = fn_8023417C(&lbl_80365434, 0);
    fn_802100C0(pObject->mUnknown284, pResult->mUnknown18);
}

void fn_8019CFD0(Object_8019CE3C *pObject)
{
    fn_80210114(pObject->mUnknown284);
}

void fn_8019CFF4(Object_8019CE3C *pObject)
{
    char buffer[32];
    float unknown28[4];
    float unknown38[4];
    GXColor color = { 255, 255, 255, 255 };
    void *pUnknown;
    float x;
    float y;
    float z;
    int mask;
    int result;
    Object_8023417C *pResult;

    pUnknown = fn_80236384(0);
    fn_80210388();
    x = y = z = 1.0f;
    if (pObject->mpUnknown294 != 0) {
        x = pObject->mpUnknown294->mUnknownC;
        y = pObject->mpUnknown294->mUnknown10;
        z = pObject->mpUnknown294->mUnknown14;
    }
    if (pObject->mUnknown14 & 0x20) {
        x *= pObject->mUnknown298;
        y *= pObject->mUnknown29C;
        z *= pObject->mUnknown2A0;
    }
    color.a = pObject->mUnknown28C * 128.0f;
    mask = fn_80236B98(4, x, y, z);
    if (fn_80144310(pObject->mUnknown2AC, pObject->mpUnknown294, unknown28, unknown38)) {
        unknown38[0] *= x;
        unknown38[1] *= y;
        unknown38[2] *= z;
        fn_80236C10(0, unknown38, unknown28);
    }
    fn_8024FB58(4, color);
    fn_8024FC84(0, 1, 0, 0, mask, 2, 2);
    fn_8024FC84(2, 0, 0, 0, mask, 2, 2);
    if (!(pObject->mUnknown14 & 8)) {
        fn_80234D4C(lbl_802F2574, pObject->mUnknown20, pUnknown, 0);
        result = fn_80234D4C(lbl_802F2574, pObject->mUnknown20, 0, buffer);
    } else {
        pObject->mUnknown14 &= ~8;
        result = 63;
    }
    if (fn_80027DF0()) {
        pResult = fn_8023417C(&lbl_80365434, 0);
    } else {
        pResult = fn_8023417C(&lbl_80365434, fn_80234144(&lbl_80365434, buffer));
    }
    fn_80210654(pResult);
    fn_80210BA4(pObject->mUnknown284);
    if (!(result & 63)) {
        fn_801D04C4();
        fn_801D0664(pObject->mUnknown20);
        if (fn_80054D24(33) || fn_80054D24(34)) {
            if (!fn_8017F584()) {
                fn_801D0CFC(1.5f);
            }
        }
        fn_8020FA38(0, 0);
        fn_80210BD8(2);
        fn_80211350();
        fn_80210BD8(1);
        fn_801D0544();
    }
    if (!(pObject->mUnknown14 & 2)) {
        fn_801A5434(pObject->mUnknown4, 1);
    } else {
        fn_801A5434(pObject->mUnknown4, 0);
    }
    fn_80210D10(1, 3, 1);
    fn_80210CC4(0.0f, 1.0f);
    fn_80210BD8(1);
}
}
