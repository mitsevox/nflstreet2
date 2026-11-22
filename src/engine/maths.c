/* Math library init and shutdown. */

#include "engine/SysSetLastErrorFunc.h"

static unsigned char _Math_ModuleActive = 0;

void MathLLInit(void);

int MathInit(void)
{
    int result = 0;

    if (!_Math_ModuleActive) {
        MathLLInit();
        _Math_ModuleActive = 1;
    } else {
        result = 0x40001;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int MathShutdown(void)
{
    int result = 0;

    if (_Math_ModuleActive) {
        _Math_ModuleActive = result;
    } else {
        result = 0x40002;
    }
    SysSetLastErrorFunc(result);
    return result;
}
