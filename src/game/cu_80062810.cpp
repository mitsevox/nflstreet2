#include "game/fn_8007F6F8.h"
#include "game/Callees_801D57E0.h"
#include "game/Callees_8002A138.h"
#include "game/cu_8018422C.h"
#include "game/FMCAPPORT.h"

extern "C" {
int fn_8002A1B0(int, int);
void fn_8002A330(int, int, int *, int *, int);
void fn_8002A478(int *, int *);
void fn_80062840(int, int *);
void fn_80062910();
int fn_8006291C(int *, int *, int *, int *);
}

static unsigned char lbl_803EA608 = 0;
static int lbl_803EA60C = 2;
static int lbl_803EC804;
static int lbl_803EC808;
static Callbacks_802F462C lbl_802D4EC4 = {
    fn_80062840, fn_80062910, fn_8006291C, 0, 0
};

extern "C" void fn_80062810()
{
    fn_801D6714(-1);
    fn_801851A4(&lbl_802D4EC4);
}

extern "C" void fn_80062840(int value, int *pCount)
{
    int a;
    int b;
    int index;

    *pCount = 9999;
    fn_8002A478(&a, &b);
    index = fn_8002A190(a, b);
    if (index == -1) {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        index = 0;
        if (lbl_803EC808 != -1) {
            index = lbl_803EC808;
        }
    } else if (lbl_803EC808 != -1 && lbl_803EC808 != index) {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        index = lbl_803EC808;
    }
    fn_801D6714(index);
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6650(8);
}

extern "C" void fn_80062910()
{
    lbl_803EC804 = 0;
}

extern "C" int fn_8006291C(int *p0, int *p4, int *p8, int *p12)
{
    unsigned char flag = 0;
    int a;
    int b;

    fn_8002A478(&a, &b);
    lbl_803EC804 = 0;
    do {
        fn_8002A330(0, lbl_803EC804, p4, p12, 0);
        lbl_803EC804++;
    } while (*p4 != a || *p12 != b);
    *p0 = fn_8002A190(*p4, *p12);
    *p8 = fn_8002A1B0(a, b);
    if (a == 1 || ((a == 2 || a == 3) && fn_8002A138(a, b))) {
        char text[32];
        fn_801D6B24(text, 32);
        *p8 = fn_801D6CF4(text, a, &flag);
        int found = *p8 != -1;
        if (found) {
            *p4 += 256;
        }
    }
    if (fn_8002A190(a, b) == -1) {
        *p4 += 512;
    }
    return 1;
}

extern "C" void fn_80062A58(unsigned char value)
{
    lbl_803EA608 = value;
}

extern "C" unsigned char fn_80062A60()
{
    return lbl_803EA608;
}

extern "C" int fn_80062A68(unsigned int id, int *p, int c, int *pResult)
{
    switch (id) {
    case 0x80000003:
        fn_8007F6F8(12, *p);
        break;
    case 0x80000004:
        fn_80062810();
        break;
    case 0x80000002:
        lbl_803EC808 = -1;
        fn_801D65B4(0);
        fn_801D654C(1);
        fn_801D6714(0);
        fn_801851D0();
        break;
    case 0x80000005:
        fn_801D6714(-1);
        fn_801D654C(0);
        fn_801851D0();
        break;
    case 0x80000006:
        lbl_803EC808 = *p;
        break;
    case 0x80000007:
        lbl_803EA60C = *p;
        break;
    case 0x80000008:
        *pResult = gFMCAPPORT.IsBusy();
        break;
    default:
        return 0;
    }
    return 1;
}
