#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "game/Object_80228224.h"
#include "game/fn_80063A0C.h"
#include "game/fn_80072AA8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801F40F4.h"
#include "game/fn_8021D7B8.h"

struct Params_80186010 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int fn_8006D65C(int idx);
void fn_8006D670(int idx, int handle);
void fn_8006D6F4(int idx, int a, int volume);
void fn_8006D758(int idx, Vector_80039F5C *pos);
void fn_8006D8DC(int idx);
unsigned char fn_80072ACC(void);
void fn_80072B84(int a, int b, int c);
void fn_80072E84(void);
void fn_80072F04(void);
unsigned char fn_80072F84(void);
void fn_80073094(void);
void fn_8007420C(int index);
void fn_80074250(int index);
void fn_80074358(int a);
int fn_800744C8(int index);
int fn_800745D4(unsigned int index);
void fn_8013CF98(void);
void fn_8018A7F8(Object_80228224 *pObject, int mode);
Object_80228224 *fn_8018A854(void);
int fn_801F48B8(int handle);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

extern void *lbl_803EB688;
extern char lbl_802EBFCC[];

void fn_80185F4C(int mode, int flag);
}

static unsigned char lbl_803EB5B8 = 1;
static void *lbl_803EB5BC = (void *)-1;
static int lbl_803EB5C0 = -1;
static unsigned char lbl_803EB5C4 = 9;
static int lbl_803EB5C8 = 3;
static int lbl_803EB5CC = 0;
static int lbl_803EB5D0 = -1;
static unsigned char lbl_803ECB84;

extern "C" {
void fn_80185AB4(int mode)
{
    if (mode != 10) {
        if (lbl_803EB5B8 != 0) {
            fn_80072E84();
            lbl_803EB5B8 = 0;
        }
        switch (mode) {
        case 8:
            lbl_803EB5C0 = 2;
            if (lbl_803EB5CC == 0) {
                lbl_803EB5C4 = 4;
            } else {
                lbl_803EB5C4 = 5;
            }
            break;
        case 9:
            lbl_803EB5C0 = 3;
            lbl_803EB5C4 = 1;
            break;
        default:
            return;
        }
        fn_8006D8DC(lbl_803EB5C4);
        fn_8006D758(lbl_803EB5C4, 0);
        fn_8006D6F4(lbl_803EB5C4, 0, 127);
    }
}

void fn_80185B70(void)
{
    if (lbl_803EB5B8 == 0) {
        if (lbl_803EB5C0 != -1) {
            lbl_803EB5C0 = -1;
            fn_8006D8DC(lbl_803EB5C4);
        }
        if (fn_80027DF0() != 0 || lbl_803EB5D0 == 10) {
            if (fn_8007F828(fn_80063A0C(10)) > 0) {
                fn_80072F04();
                lbl_803EB5B8 = 1;
            }
        }
    }
}

void fn_80185BEC(int mode, int value, int notify)
{
    int flag = 0;
    int index = fn_80063A0C(mode);

    if (index != 24) {
        if (fn_8007F828(index) == 0 && value != 0) {
            flag = 1;
        }
        fn_8007F6F8(index, value);
        if (notify == 1) {
            fn_80185F4C(mode, flag);
        }
    }
}

int fn_80185C68(int mode)
{
    int result = 0;
    int index = fn_80063A0C(mode);

    if (index != 24) {
        result = fn_8007F828(index);
    }
    return result;
}

void fn_80185CA8(int mode)
{
    if (fn_80063A0C(mode) != 24) {
        lbl_803EB5D0 = mode;
        if (mode >= 8 && mode <= 10) {
            if (mode == 10) {
                fn_80185B70();
                if (lbl_803ECB84 == 0) {
                    fn_80072B84(1, 0, 1);
                }
            } else {
                fn_80185AB4(mode);
            }
        } else {
            fn_80185B70();
            if (fn_80027DF0() == 0) {
                fn_80072E84();
                lbl_803EB5B8 = 0;
            }
            if (lbl_803ECB84 == 0) {
                fn_80073094();
            }
        }
    } else {
        if (lbl_803EB5C0 != -1) {
            lbl_803EB5C0 = -1;
            fn_8006D8DC(lbl_803EB5C4);
        }
        fn_80072E84();
        lbl_803EB5B8 = 0;
    }
}

void fn_80185D78(void)
{
    int value;

    fn_80185B70();
    if (lbl_803EB5C8 != fn_8007F828(6)) {
        if (fn_8007F828(6) == 0) {
            value = 0;
        } else {
            value = 1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000000F, 1, &value);
        if (fn_8007F828(6) == 1) {
            fn_8018A7F8(fn_8018A854(), 0);
        } else {
            fn_8018A7F8(fn_8018A854(), fn_8007F828(6));
        }
        fn_8013CF98();
    }
    if (lbl_803ECB84 == 0) {
        fn_80073094();
    }
    fn_8006D670(1, 0);
    if (fn_80027DF0() == 0) {
        fn_8007420C(lbl_803EB5CC);
        fn_80072E84();
    } else if (lbl_803ECB84 != 0) {
        fn_80072F04();
    }
    fn_801EEFAC(lbl_803EB5BC);
    lbl_803EB5BC = (void *)-1;
    lbl_803EB5C0 = -1;
}

void fn_80185E88(void)
{
    int result;

    lbl_803EB5C0 = -1;
    result = fn_80027DF0();
    lbl_803EB5B8 = 0;
    fn_80072E84();
    lbl_803EB5C8 = fn_8007F828(6);
    lbl_803EB5BC = fn_801EEB44(lbl_802EBFCC, 44);
    if (result != 0 || fn_800744C8(0) != 0) {
        lbl_803EB5CC = 0;
    } else {
        lbl_803EB5CC = 1;
    }
    fn_80074358(lbl_803EB5CC);
    fn_80074250(lbl_803EB5CC);
    fn_8006D670(1, fn_800745D4(lbl_803EB5CC));
    lbl_803ECB84 = fn_80072ACC() != 0;
}

void fn_80185F4C(int mode, int flag)
{
    if (mode >= 8 && mode <= 10) {
        if (flag != 0) {
            if (mode == 10) {
                if (lbl_803ECB84 != 0) {
                    if (fn_80072F84() != 0) {
                        fn_80072F04();
                    } else {
                        fn_80072F90();
                    }
                } else {
                    fn_80072B84(1, 0, 1);
                }
            }
            lbl_803EB5B8 = 1;
            fn_80185AB4(mode);
        } else if (fn_8007F828(fn_80063A0C(mode)) == 0 && mode == 10) {
            if (lbl_803ECB84 == 0) {
                fn_80073094();
            } else {
                fn_80072E84();
            }
        }
    }
}

int fn_80186010(unsigned int id, Params_80186010 *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80185E88();
        break;
    case 0x80000002:
        fn_80185D78();
        break;
    case 0x80000003:
        fn_80185CA8(pParams->mUnknown0);
        break;
    case 0x80000004:
        *pResult = fn_80185C68(pParams->mUnknown0);
        break;
    case 0x80000005:
        fn_80185BEC(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_801860E4(int unknown)
{
    Status_801F4834 status;
    unsigned short a;
    unsigned short b;
    Pair_80073CB0 pair;

    if (lbl_803EB5C0 != -1) {
        fn_80219650(lbl_803EB688, &a, &b);
        if ((a == 5 && b == 5) || (a == 3 && b == 11)) {
            fn_8006D6F4(lbl_803EB5C4, 0, 127);
            fn_801F4834(fn_8006D65C(lbl_803EB5C4), &status);
            if (status.mUnknown0 <= 0 && fn_801F48B8(fn_8006D65C(lbl_803EB5C4)) != 0) {
                pair.mpUnknown0 = lbl_803EB5BC;
                pair.mUnknown4 = lbl_803EB5C0;
                fn_801F4580(fn_8006D65C(lbl_803EB5C4), &pair, 0, 0);
            }
        } else {
            fn_8006D6F4(lbl_803EB5C4, 0, 0);
        }
    }
}
}
