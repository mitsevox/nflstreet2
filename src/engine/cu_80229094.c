#include "engine/fn_801F8D60.h"
#include "game/fn_801EEB44.h"
#include "engine/cu_801C2EB4.h"
#include "engine/cu_80229094.h"
#include "engine/fn_8022C938.h"
#include "engine/fn_801F9134.h"
#include "engine/tdbiores.h"

extern int fn_801F8CE8(int *pHandle);

static char *lbl_803EBFC8 = 0;
static void *lbl_803EBFCC = 0;
static int lbl_803EBFD0 = -1;
static int lbl_803EBFD4 = -1;

int fn_80229094(const char *pName)
{
    lbl_803EBFC8 = fn_8022C938(fn_801C3180(pName) + 1, 1);
    fn_801C2EB4(lbl_803EBFC8, pName);
    return 0;
}

void fn_802290E0(void)
{
    fn_8022C988(lbl_803EBFC8);
    lbl_803EBFC8 = 0;
}

int fn_8022910C(void)
{
    int err = 0;

    lbl_803EBFCC = fn_801EEB44(lbl_803EBFC8, 44);
    if (lbl_803EBFCC == 0) {
        err = 38;
    }
    if (err == 0) {
        err = fn_801F8CE8(&lbl_803EBFD4);
        if (err == 0) {
            err = fn_801F8D60(lbl_803EBFD4, -1);
            if (err != 0) {
                lbl_803EBFD4 = -1;
            }
        }
    }
    return err;
}

int fn_80229188(void)
{
    if (lbl_803EBFCC) {
        return 1;
    }
    return 0;
}

int fn_802291A0(void)
{
    int err = fn_801F8EEC(lbl_803EBFD4);

    if (err == 0) {
        lbl_803EBFD4 = -1;
        if (fn_801EEFAC(lbl_803EBFCC) != 0) {
            err = 39;
        }
    } else {
        fn_801EEFAC(lbl_803EBFCC);
    }
    lbl_803EBFCC = 0;
    lbl_803EBFD0 = -1;
    return err;
}

int fn_80229210(int a, int *pOut)
{
    int err;
    int *pState = &lbl_803EBFD0;

    *pState = a;
    err = fn_801F9134(lbl_803EBFD4, (int)&lbl_803EBFCC, 0, (int)&lbl_802F9BAC);
    *pState = -1;
    *pOut = err != 0 ? -1 : lbl_803EBFD4;
    return err;
}
