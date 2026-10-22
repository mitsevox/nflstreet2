#include "engine/fn_801F7BD4.h"

extern void *fn_801C68FC(int a, int b, int count, int size, int (*compare)(const void *, const void *), int c);
extern void fn_801C69E4(void *pPool);
extern int fn_801F7ABC(void);

extern unsigned char lbl_803EBE9C;
extern void *lbl_803ECFAC;
extern int lbl_803ECFB0;
extern int lbl_803ECFB4;
extern int lbl_803ECFB8;

void fn_8020D0A8(void);

int fn_8020CFA0(const void *pA, const void *pB)
{
    return ((const unsigned short *)pA)[1] - ((const unsigned short *)pB)[1];
}

int fn_8020CFB0(int count)
{
    int err = 0;

    if (lbl_803EBE9C == 0) {
        lbl_803ECFAC = fn_801C68FC(1, 0, count, 0x2C, fn_8020CFA0, 0);
        if (lbl_803ECFAC == 0) {
            err = fn_801F7C88();
        }
        fn_8020D0A8();
        lbl_803EBE9C = 1;
    } else {
        err = 0x80001;
    }
    lbl_803ECFB4 = 0;
    lbl_803ECFB8 = 0;
    fn_801F7BD4(err);
    return err;
}

int fn_8020D048(void)
{
    int err = 0;

    if (lbl_803EBE9C != 0) {
        if (lbl_803ECFAC != 0) {
            fn_801C69E4(lbl_803ECFAC);
        }
        lbl_803EBE9C = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}

void fn_8020D0A8(void)
{
    lbl_803ECFB0 = fn_801F7ABC();
}
