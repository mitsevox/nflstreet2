/* Curve module init and shutdown. */

#include "engine/fn_801F7BD4.h"

extern unsigned char lbl_803EBBE8;

int fn_801C4F64(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        error = 0x1E0001;
    } else {
        lbl_803EBBE8 = 1;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C4FB8(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        lbl_803EBBE8 = 0;
    } else {
        error = 0x1E0002;
    }
    fn_801F7BD4(error);
    return error;
}
