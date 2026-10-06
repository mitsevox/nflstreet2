#include <dolphin/gx/GXStruct.h>
#include "game/cu_80191398.h"
#include "game/fn_801C1F94.h"

extern "C" {
/* Text screen of 24 rows of 80 columns plus a terminator; a row is drawn only while its flag is set. */
static char lbl_802EAF6C[24 * 81] = { 0 };
static unsigned char lbl_80364F40[24];
static GXColor lbl_803EB6E0 = { 180, 180, 180, 255 };
static unsigned char lbl_803ECB98;

void fn_80191248(unsigned short row)
{
    fn_801C1F94(&lbl_802EAF6C[row * 81], ' ', 80);
    lbl_802EAF6C[row * 81 + 80] = 0;
    lbl_80364F40[row] = 0;
}

void fn_801912A4(void)
{
    unsigned int row;

    for (row = 0; row < 24; row++) {
        fn_80191248(row);
    }
    lbl_803ECB98 = 0;
}

void fn_801912E8(void)
{
    unsigned int row;

    fn_80191424(lbl_803EB6E0.r, lbl_803EB6E0.g, lbl_803EB6E0.b);
    if (lbl_803ECB98) {
        for (row = 0; row < 24; row++) {
            if (lbl_80364F40[row]) {
                fn_8019143C(0, row * 9, 0, &lbl_802EAF6C[row * 81], 0);
            }
        }
    }
}
}
