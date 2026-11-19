/* Curve module init and shutdown. */

#include "engine/SysSetLastErrorFunc.h"

extern unsigned char lbl_803EBBE8;

int CurveInit(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        error = 0x1E0001;
    } else {
        lbl_803EBBE8 = 1;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int CurveShutdown(void)
{
    int error = 0;

    if (lbl_803EBBE8) {
        lbl_803EBBE8 = 0;
    } else {
        error = 0x1E0002;
    }
    SysSetLastErrorFunc(error);
    return error;
}
