#include "game/Callees_801D57E0.h"
#include "game/cu_8018422C.h"
#include "game/fn_801801F0.h"
#include "game/Record_80021154.h"
#include "game/fn_801C1F94.h"
#include <string.h>

struct Record_80020F5C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    char mUnknown12[4];
    unsigned char mUnknown16;
    char mUnknown17[3];
};

union Word_800211B4 {
    int mUnknownValue;
    Record_80021154 *mUnknownPointer;
};

struct Params_800211B4 {
    Word_800211B4 mUnknown0;
    int mUnknown4;
    Record_80021154 *mUnknown8;
};

extern "C" {
int fn_801869F0();
void fn_8002A574(int, int);
void fn_8002118C();
void *fn_80020F18(int, int *);
void fn_80020F50();
int fn_80020F5C(int *, int *, int *, int *);
void fn_80021004(int, int);
}

static Record_80020F5C lbl_8036B360[16];
static int lbl_803EBAB0 = 0;
static Callbacks_802F462C lbl_802F462C = {
    fn_80020F18, fn_80020F50, fn_80020F5C, fn_80021004, 0
};

extern "C" void fn_80020E80()
{
    fn_801801F0(1);
    fn_801D685C("GN7E-69", 0);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    fn_8002118C();
}

extern "C" void fn_80020ED0()
{
    fn_801801F0(0);
    fn_801D685C("GN7E-69", 0);
    fn_801D6714(-1);
    fn_801D654C(0);
    fn_801851D0();
}

extern "C" void *fn_80020F18(int value, int *pCount)
{
    *pCount = 16;
    return fn_801C1F94(lbl_8036B360, 0, 320);
}

extern "C" void fn_80020F50()
{
    lbl_803EBAB0 = 0;
}

extern "C" int fn_80020F5C(int *p0, int *p4, int *p8, int *p12)
{
    unsigned int i;
    for (i = 0; i < 16; ++i) {
        if (i == lbl_803EBAB0) {
            if (lbl_8036B360[i].mUnknown16) {
                *p0 = lbl_8036B360[i].mUnknown0;
                *p4 = lbl_8036B360[i].mUnknown4;
                *p8 = lbl_8036B360[i].mUnknown8;
                *p12 = 0;
                ++lbl_803EBAB0;
                break;
            }
            lbl_803EBAB0 = i + 1;
        }
    }
    return i < 16;
}

extern "C" void fn_80021004(int key, int value)
{
    fn_8002A574(key, (key == 2 || key == 3) ? fn_801869F0() : 0);
    char first[32];
    char second[32];
    fn_801D6B74((signed char)value, key, first, 32, 0, -1, 0);
    fn_801D6C70((signed char)value, key, second, 32);
    fn_801D67E4(first, second);
    fn_801D6838(value);
}

extern "C" int fn_800210A4(int key, int value, Record_80021154 *p)
{
    if (key == 2 || key == 3) {
        char text[32];
        fn_801D6B74((signed char)value, key, text, 32, 0, -1, 0);
        strcpy(p->mUnknown8, text);
    } else if (fn_801D6DA8(0, 1)) {
        strcpy(p->mUnknown8, "???");
    } else {
        strcpy(p->mUnknown8, "Options");
    }
    return 0;
}

extern "C" int fn_80021154(Record_80021154 *p)
{
    return fn_801D57E0(fn_801D671C(), p->mUnknown8, p->mUnknown4);
}

extern "C" void fn_8002118C()
{
    fn_801851A4(&lbl_802F462C);
}

extern "C" int fn_800211B4(unsigned int value, Params_800211B4 *p)
{
    switch (value) {
    case 0x80000012:
        fn_80020E80();
        break;
    case 0x80000014:
        fn_800210A4(p->mUnknown0.mUnknownValue, p->mUnknown4, p->mUnknown8);
        break;
    case 0x80000015:
        fn_80021154(p->mUnknown0.mUnknownPointer);
        break;
    case 0x80000013:
        fn_80020ED0();
        break;
    default:
        return 0;
    }
    return 1;
}
