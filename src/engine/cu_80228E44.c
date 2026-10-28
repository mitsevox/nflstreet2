#include "engine/cu_80228E44.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

/* 28-byte pool entry; only the byte at +8 is written here. */
typedef struct Entry_80228E44 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9[19];
} Entry_80228E44;


static unsigned short lbl_803EBFA8 = 0;
static Entry_80228E44 *lbl_803EBFAC = 0;
static int lbl_803EBFB0 = -1;
static unsigned char lbl_803EBFB4 = 0;

int fn_80228E44(Desc_80228E44 *pDesc)
{
    int err = 0;
    unsigned int i;

    if (lbl_803EBFB4 == 0) {
        lbl_803EBFA8 = pDesc->mUnknown0;
        lbl_803EBFB0 = err;
        lbl_803EBFAC = fn_801D2BB0(1, lbl_803EBFA8 * sizeof(Entry_80228E44), 0, 0);
        if (lbl_803EBFAC == 0) {
            err = fn_801F7C88();
        } else {
            for (i = 0; i < lbl_803EBFA8; i++) {
                lbl_803EBFAC[i].mUnknown8 = 0xFF;
            }
            lbl_803EBFB4 = 1;
        }
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_80228F0C(void)
{
    int err = 0;

    if (lbl_803EBFB4) {
        lbl_803EBFB0 = -1;
        lbl_803EBFA8 = 0;
        fn_801D2BD0(lbl_803EBFAC);
        lbl_803EBFB4 = 0;
        lbl_803EBFAC = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}
