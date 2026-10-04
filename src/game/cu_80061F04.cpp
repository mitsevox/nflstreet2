#include "game/Object_8007A334.h"
#include "game/cu_8002ACB4.h"
#include "game/fn_800624B0.h"
#include "game/fn_8018BE68.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"

struct Setup_802D4EB0 {
    float mPosition[3];
    float mScale;
    int mUnknown16;
};

struct Pair_800624B8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

union Word_800624B8 {
    int *mpId;
    int mValue;
};

struct Block_800624B8 {
    Word_800624B8 mUnknown0;
    Pair_800624B8 *mpUnknown4;
};

extern "C" {
void fn_80022398(void);
void fn_800223C0(void);
void fn_800223E4(int index, float x, float y, float z);
void fn_8002248C(int index, unsigned char value);
void fn_800224A4(int index, float angle);
void fn_8002251C(int index, unsigned char value);
void fn_80022534(int index, float scale);
void fn_80022580(int index, int a, int b);
void fn_80022680(int index, int a, int b);
void fn_80022730(int index, int value);
void fn_80061DDC(void);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
int fn_80183950(void);
void fn_80185264(unsigned char value);
unsigned char fn_8018526C(void);
unsigned char fn_8018527C(void);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
void fn_8018BF3C(void);
int fn_8018C0E8(int a, int *p);
void fn_8018C48C(int tag);
int fn_8018D780(int a);
int fn_8018D890(int a, int b);
void fn_8018D8EC(int a, int b);
void fn_8018DCBC(int a);
int fn_8018DD04(int a);
void fn_8018DD4C(int a, int b, int c);
int fn_8018E874(int a, int b);
void fn_8018E8B0(int a, int b, int c);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);

static Setup_802D4EB0 lbl_802D4EB0 = {{330.0f, 290.0f, 7.0f}, 1.0f, 14};
static unsigned char lbl_803EA600 = 0;
static int lbl_803EC7F4;
static int lbl_803EC7F8;
static signed char lbl_803EC7FC;
static unsigned char lbl_803EC7FD;

void fn_80061F04(void)
{
    int a;
    int b;
    int handle = fn_8022F3D4(fn_8022F358(lbl_803EC7FC));
    void *p1;
    void *p2;

    fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 and 'DIGP' into \x85 from 'YPRC' where 'DIOP' = \x82\n",
                handle, &a, &b, 0x7FF4);
    fn_801FCE10(0, "use \x8c update 'YPRC' set 'PXSP' = \x85 where 'DIGP' = \x82\n", handle, 8, b);
    p1 = fn_801D2B7C(0x20000, 0, 0);
    p2 = fn_801D2B7C(0x400, 0, 0);
    fn_801FCE10(0, "use \x8c select 'XTPP' into \x89 and 'LPPP' into \x89 from 'PPRC' where 'PXSP' = \x85\n",
                handle, p1, p2, a);
    fn_801FCE10(0, "use \x8c update 'PPRC' set 'XTPP' = \x89 and 'LPPP' = \x89 where 'PXSP' = \x85\n", handle,
                p1, p2, 8);
    fn_801D2BD0(p2);
    fn_801D2BD0(p1);
}

void fn_80062000(void)
{
    Result_8018BE68 result;

    lbl_803EC7F4 = fn_8018BE68(lbl_803EC7FC, 1, &result);
    lbl_803EC7F8 = result.mUnknown0;
    fn_80022680(0, result.mUnknown0, 1);
}

void fn_8006204C(void)
{
    fn_80185264(1);
    fn_8002ADE0(lbl_803EC7FC, lbl_803EC7F8);
}

void fn_80062080(int enable)
{
    if (enable && fn_8018527C()) {
        fn_8018E8B0(lbl_803EC7FC, 0, 1);
    }
}

void fn_800620C4(void)
{
    Result_8018BE68 result;
    int handle;

    fn_80185264(lbl_803EC7FD);
    handle = fn_8018D890(lbl_803EC7FC, 0);
    if (fn_8018DD04(handle) > 0) {
        fn_8018DCBC(handle);
    }
    fn_8018BECC(lbl_803EC7FC, 0, &result);
    fn_8018DD4C(handle, result.mUnknown0, 1);
    fn_8018D8EC(lbl_803EC7FC, handle);
    fn_8018C48C(0x54415453);
    fn_80061F04();
    fn_80062000();
}

void fn_80062160(int *pId)
{
    fn_80061DDC();
    if (lbl_803EA600 == 0) {
        lbl_803EA600 = 1;
        lbl_803EC7FC = fn_8022F384(fn_8022F4BC());
        fn_80022398();
        fn_800223E4(0, lbl_802D4EB0.mPosition[0], lbl_802D4EB0.mPosition[1], lbl_802D4EB0.mPosition[2]);
        fn_800224A4(0, 0.0f);
        fn_80022534(0, lbl_802D4EB0.mScale);
        fn_8002248C(0, 0);
        fn_8002251C(0, 0);
        fn_80022730(0, lbl_802D4EB0.mUnknown16);
        fn_80022580(0, 82, 0);
        fn_80062000();
        lbl_803EC7FD = fn_8018526C();
        if (fn_8018C0E8(lbl_803EC7FC, pId)) {
            Object_8007A334 cursor;
            fn_80083E40(&cursor, 0, 0x54415453);
            fn_80084034(&cursor, *pId, 0);
            if (!fn_80084438(&cursor)) {
                unsigned char values[3];
                values[0] = fn_800841AC(&cursor);
                values[1] = fn_800841D8(&cursor);
                values[2] = fn_80084204(&cursor);
                fn_80188CBC(0, 4, fn_80084158(&cursor), 172, values);
                fn_80188CBC(1, 4, fn_80084158(&cursor), 172, values);
            }
            fn_80083F68(&cursor);
        } else {
            *pId = 0;
        }
    }
}

void fn_80062308(void)
{
    if (lbl_803EA600) {
        fn_8002ADAC();
        fn_800223C0();
        if (fn_80183950() == 0) {
            fn_8018C48C(0x54415453);
        }
        fn_80185264(lbl_803EC7FD);
        lbl_803EA600 = 0;
    }
}

int fn_80062360(int which)
{
    int result = 1;

    switch (which) {
    case 0:
        if (fn_8018E874(lbl_803EC7FC, 0) == 0) {
            result = 0;
        }
        break;
    case 1:
        if (fn_8018E874(lbl_803EC7FC, 1) == 0 && fn_8018D780(lbl_803EC7FC) != 0) {
            result = 0;
        }
        break;
    }
    return result;
}

void fn_800623EC(int a, int b, int c) {}

void fn_800623F0(void)
{
    int active = fn_8018E874(lbl_803EC7FC, 1);

    fn_8018BF3C();
    if (active) {
        fn_8018E8B0(lbl_803EC7FC, 1, 1);
    }
}

void fn_80062448(int which)
{
    switch (which) {
    case 0:
        fn_8006204C();
        break;
    case 1:
        if (fn_8018E874(lbl_803EC7FC, 1) == 0) {
            fn_800620C4();
            fn_8018E8B0(lbl_803EC7FC, 1, 1);
        }
        break;
    }
}

unsigned char fn_800624B0(void)
{
    return lbl_803EA600;
}

int fn_800624B8(unsigned int id, Block_800624B8 *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80062160(pBlock->mUnknown0.mpId);
        break;
    case 0x80000002:
        fn_80062308();
        break;
    case 0x80000003:
        if (fn_80062360(pBlock->mUnknown0.mValue)) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x80000004:
        fn_800623EC(pBlock->mUnknown0.mValue, pBlock->mpUnknown4->mUnknown8, pBlock->mpUnknown4->mUnknown4);
        break;
    case 0x80000005:
        fn_800623F0();
        break;
    case 0x80000006:
        fn_80062448(pBlock->mUnknown0.mValue);
        break;
    case 0x80000007: {
        int enable = 0;
        if (pBlock->mUnknown0.mValue) {
            enable = 1;
        }
        fn_80062080(enable);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
