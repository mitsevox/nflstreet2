#include "engine/cu_801BFFA8.h"
#include "engine/fn_801F7BD4.h"

extern unsigned char lbl_803EBBAC;
extern float lbl_803EBBB0;

int fn_801BFEF8(float rate)
{
    int err = 0;

    if (lbl_803EBBAC)
        err = 0x1D0001;
    else {
        lbl_803EBBB0 = rate;
        lbl_803EBBAC = 1;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801BFF50(void)
{
    int err = 0;

    if (lbl_803EBBAC)
        lbl_803EBBAC = 0;
    else
        err = 0x1D0002;
    fn_801F7BD4(err);
    return err;
}

float fn_801BFFA0(void)
{
    return lbl_803EBBB0;
}
