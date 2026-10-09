#include "game/InGame.h"
#include "game/fn_800B65A0.h"

struct Record_800B2340 {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
};

extern "C" {
void fn_800655B8(void);
void fn_800655D0(void);
Record_800B2340 *fn_800B2340(unsigned char index);
void fn_8018A798(int value);
int fn_8018A7A0(void);
}

static int lbl_803EB4B8 = -1;
static unsigned char lbl_803ECB40;
static int lbl_803ECB44;
static int lbl_803ECB48;
static int lbl_803ECB4C;

extern "C" {
void fn_8017F3C8(int a, int b, int c)
{
    lbl_803ECB4C = b;
    lbl_803ECB48 = c;
    lbl_803ECB40 = 1;
    lbl_803EB4B8 = -1;
    lbl_803ECB44 = a;
    fn_800655B8();
    fn_80028918(1);
    fn_8018A798(fn_800B65A0(fn_800B2340(a)->mUnknown2 ^ 1));
}

void fn_8017F430(int value)
{
    lbl_803EB4B8 = value;
    lbl_803ECB44 = 0xFFFF;
}

void fn_8017F444(void)
{
    fn_8018A7A0();
    lbl_803ECB40 = 0;
    if (lbl_803ECB44 != 0xFFFF) {
        fn_80028918(0);
        fn_800655D0();
    }
}

unsigned char fn_8017F48C(void)
{
    return lbl_803ECB40;
}

int fn_8017F494(void)
{
    return lbl_803EB4B8;
}
}
