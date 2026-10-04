#include "game/Callees_801D57E0.h"
#include "game/cu_8018422C.h"
#include "game/fn_801801F0.h"
#include "game/fn_801C1F94.h"

struct Record_80021548 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[3];
};

union Params_800217AC {
    int mUnknownValue;
    int *mUnknownPointer;
};

extern "C" {
int fn_801869F0();
void fn_80186ED8(signed char);
void fn_8002A574(int, int);
void fn_8002A5C4();
int fn_801E15D0(int a);
unsigned int fn_801E1954();
int fn_801E195C(int a);
unsigned int fn_801E19B4(int a);
void fn_801E1C38(unsigned char a);
unsigned int fn_801D6CB8(int, int);
void fn_80021504(int, int *);
void fn_8002153C();
int fn_80021548(int *, int *, int *, int *);
void fn_800215F0(int, int);
int fn_80021624(int, int);
}

static Record_80021548 lbl_8036B4B4[3];
static int lbl_803EBAB8 = 0;
static int lbl_803EBABC = -1;
static Callbacks_802F462C lbl_802F4640 = {
    fn_80021504, fn_8002153C, fn_80021548, fn_800215F0, fn_80021624
};

extern "C" void fn_8002132C()
{
    fn_801801F0(1);
    fn_801D685C("GN7E-69", 0);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    fn_801851A4(&lbl_802F4640);
}

extern "C" int fn_80021384()
{
    int stop = 1;
    for (unsigned char i = 0; !stop && i < fn_801E1954(); ++i) {
        fn_801E195C(i);
    }
    return !stop;
}

extern "C" void fn_800213F0(int *pFound)
{
    int found = 0;
    unsigned int count = fn_801E1954();
    for (unsigned int i = 0; i < count; ++i) {
        fn_801E1C38(i);
        if (fn_801E19B4(i) >> 16) {
            fn_801E15D0(i);
            if (fn_801E19B4(i) & 0x800) {
                lbl_803EBABC = i;
                found = 1;
                break;
            }
        }
    }
    *pFound = found;
}

extern "C" void fn_80021474()
{
}

extern "C" void fn_80021478(int *p)
{
}

extern "C" int fn_8002147C()
{
    return 0;
}

extern "C" void fn_80021484(unsigned char value)
{
}

extern "C" void fn_80021488()
{
    fn_801801F0(0);
    fn_801D685C("GN7E-69", 0);
    fn_801D6714(-1);
    fn_801D654C(0);
    fn_801851D0();
    for (signed char i = fn_801869F0() - 1; i >= 0; --i) {
        fn_80186ED8(i);
    }
}

extern "C" void fn_80021504(int value, int *pCount)
{
    *pCount = 9999;
    fn_801C1F94(lbl_8036B4B4, 0, sizeof(lbl_8036B4B4));
}

extern "C" void fn_8002153C()
{
    lbl_803EBAB8 = 0;
}

extern "C" int fn_80021548(int *p0, int *p4, int *p8, int *p12)
{
    unsigned int i;
    for (i = 0; i < 3; ++i) {
        if (i == lbl_803EBAB8) {
            if (lbl_8036B4B4[i].mUnknown16) {
                *p0 = lbl_8036B4B4[i].mUnknown0;
                *p4 = lbl_8036B4B4[i].mUnknown4;
                *p8 = lbl_8036B4B4[i].mUnknown8;
                *p12 = 0;
                ++lbl_803EBAB8;
                break;
            }
            lbl_803EBAB8 = i + 1;
        }
    }
    return i < 3;
}

extern "C" void fn_800215F0(int key, int value)
{
    int index = 0;
    if (key == 2) {
        index = lbl_803EBAB8 - 2;
    }
    fn_8002A574(key, index);
}

extern "C" int fn_80021624(int key, int value)
{
    unsigned int score = fn_801D6CB8((signed char)value, key);
    int changed = 0;

    if (key == 1) {
        if (!lbl_8036B4B4[0].mUnknown16 || score > lbl_8036B4B4[0].mUnknown12) {
            lbl_8036B4B4[0].mUnknown16 = 1;
            lbl_8036B4B4[0].mUnknown12 = score;
            lbl_8036B4B4[0].mUnknown0 = fn_801D671C();
            lbl_8036B4B4[0].mUnknown4 = key;
            lbl_8036B4B4[0].mUnknown8 = value;
        }
    } else if (key == 2) {
        int insert = 0;
        for (unsigned int i = 1; i < 3; ++i) {
            if (!lbl_8036B4B4[i].mUnknown16) {
                insert = 1;
            } else if (score > lbl_8036B4B4[i].mUnknown12) {
                insert = 1;
                for (unsigned int j = 2; j > i; --j) {
                    lbl_8036B4B4[j] = lbl_8036B4B4[j - 1];
                }
            }
            if (insert) {
                lbl_8036B4B4[i].mUnknown16 = 1;
                lbl_8036B4B4[i].mUnknown12 = score;
                lbl_8036B4B4[i].mUnknown0 = fn_801D671C();
                lbl_8036B4B4[i].mUnknown4 = key;
                lbl_8036B4B4[i].mUnknown8 = value;
                break;
            }
        }
        changed = 0;
    }
    if (changed) {
        fn_8002A574(key, 0);
        fn_8002A5C4();
    }
    return 0;
}

extern "C" int fn_800217AC(unsigned int id, Params_800217AC *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8002132C();
        break;
    case 0x80000002:
        *pResult = fn_80021384();
        break;
    case 0x80000003:
        *pResult = fn_8002147C();
        break;
    case 0x80000004:
        fn_80021484(pParams->mUnknownValue);
        break;
    case 0x80000005:
        fn_80021488();
        break;
    case 0x80000007:
        fn_800213F0(pParams->mUnknownPointer);
        break;
    case 0x80000008:
        fn_80021474();
        break;
    case 0x80000009:
        fn_80021478(pParams->mUnknownPointer);
        break;
    case 0x80000006:
        *pResult = 0;
        break;
    default:
        return 0;
    }
    return 1;
}
