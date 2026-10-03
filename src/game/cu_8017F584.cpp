#include "game/InGame.h"

extern "C" {
int fn_801FCE10(int a, const char *pFormat, ...);
int fn_802294F4(void);
}

static int lbl_803EB4C0 = 99;

extern "C" {
unsigned int fn_8017F584(void)
{
    int value = 99;

    if (fn_802294F4() != 0) {
        int cached = lbl_803EB4C0;

        if (cached == 99) {
            if (fn_801FCE10(0, "select 'PYTM' into \x82 from 'NIOM'\n", &value) != 0) {
                value = cached;
            }
            if (fn_8002894C() != 0) {
                lbl_803EB4C0 = value;
            }
        } else {
            value = cached;
        }
    }
    return value;
}

int fn_8017F60C(void)
{
    switch (fn_8017F584()) {
    case 3:
        return 1;
    case 4:
        return 1;
    case 5:
        return 1;
    case 13:
        return 1;
    default:
        return 0;
    }
}

void fn_8017F664(void)
{
    lbl_803EB4C0 = 99;
}
}
