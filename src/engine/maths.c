/* Math library init and shutdown. */

#include "engine/SysSetLastErrorFunc.h"

extern unsigned char lbl_803EBCB0;

void MathLLInit(void);

int MathInit(void)
{
    int result = 0;

    if (!lbl_803EBCB0) {
        MathLLInit();
        lbl_803EBCB0 = 1;
    } else {
        result = 0x40001;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int MathShutdown(void)
{
    int result = 0;

    if (lbl_803EBCB0) {
        lbl_803EBCB0 = result;
    } else {
        result = 0x40002;
    }
    SysSetLastErrorFunc(result);
    return result;
}
