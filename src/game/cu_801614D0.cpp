#include "engine/cu_80227F14.h"
#include "game/fn_801EF390.h"

/* 0x1D0-byte item of the type-13 pool created by fn_801615EC. */
struct Instance_801614D0 {
    char mPad00[4];
    float mUnknown04;
    float mUnknown08;
    float mUnknown0C;
    char mPad10[4];
    int mUnknown14;
    char mUnknown18[0x30];
    char mUnknown48[0xC0];
    char mUnknown108[0xC0];
    int mUnknown1C8;
    unsigned char mUnknown1CC;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A338C(void);
void fn_801A5478(Instance_801614D0 *pInstance);
void fn_801A553C(Instance_801614D0 *pInstance);
void fn_801A5568(int a, int b);
int fn_801DCF0C(int type, int size, int count, void *pCreate, void *pDestroy);
void fn_801DCF8C(int type);
void fn_801DD0C8(int handle, int type, int a, int (*pCallback)(int, int));
int fn_801DD268(int handle, int type, int a, void *pInit);
void fn_801DD320(int handle, int item);
void fn_801DD3AC(int handle, int item, int a);
void fn_80234DFC(int a, void *pB, int c, int d, const char *pName, int e);
void fn_80234EA0(void *p, int a);
void fn_802355E4(void *p);
void fn_80235DB8(int a);

static Instance_801614D0 *lbl_803EB380 = 0;

int fn_801614D0(void)
{
    return lbl_803EB380 != 0 && lbl_803EB380->mUnknown1CC != 0;
}

int fn_801614F4(int a, int b)
{
    if (fn_801614D0()) {
        fn_801A5568(a, b);
    }
    return 0;
}

void fn_8016153C(Instance_801614D0 *pInstance)
{
    int handle = fn_801EF390(fn_800A336C(), pInstance->mUnknown1C8, 1);

    fn_80235DB8(handle);
    pInstance->mUnknown14 = handle;
    fn_80234DFC(handle, pInstance->mUnknown18, 0, 0, "SkyObj", 1);
}

void fn_801615A0(Instance_801614D0 *pInstance)
{
    fn_802355E4(pInstance->mUnknown48);
    fn_802355E4(pInstance->mUnknown108);
    fn_80234EA0(pInstance->mUnknown18, 1);
    pInstance->mUnknown14 = 0;
}

void fn_801615EC(void *pOwner)
{
    Instance_801614D0 *pItem;

    if (lbl_803EB380 != 0) {
        return;
    }
    pItem = 0;
    if (fn_801DCF0C(13, sizeof(Instance_801614D0), 1, 0, 0) == 0) {
        fn_801DD0C8((int)pOwner, 13, 0, fn_801614F4);
        pItem = (Instance_801614D0 *)fn_801DD268((int)pOwner, 13, 0, 0);
        if (pItem != 0) {
            fn_801DD3AC((int)pOwner, (int)pItem, 0);
            pItem->mUnknown1CC = 1;
            pItem->mUnknown0C = pItem->mUnknown08 = pItem->mUnknown04 = 0.0f;
            pItem->mUnknown1C8 = fn_800A338C();
            fn_8016153C(pItem);
            fn_801A5478(pItem);
        }
    }
    lbl_803EB380 = pItem;
}

void fn_801616C0(void *pOwner)
{
    Instance_801614D0 *pItem = lbl_803EB380;

    if (pItem != 0) {
        fn_801A553C(pItem);
        fn_801615A0(lbl_803EB380);
        fn_801DD320((int)pOwner, (int)pItem);
        fn_80228D58((int)pItem);
        fn_80228E18();
        fn_801DCF8C(13);
        lbl_803EB380 = 0;
    }
}
}
