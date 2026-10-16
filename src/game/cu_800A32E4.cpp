#include "game/Block_8030E6E8.h"

extern "C" {
unsigned char fn_80054D24(int index);
unsigned int fn_8017F584(void);

extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" float fn_800A32E4(void)
{
    if (fn_80054D24(27) != 0 && fn_8017F584() == 0) {
        return 10.0f;
    }
    if (fn_80054D24(26) != 0 && fn_8017F584() == 0) {
        return lbl_8030E6E8.mUnknown2C * 2.0;
    }
    return lbl_8030E6E8.mFloat38;
}
