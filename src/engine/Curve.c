/* Curve module init and shutdown. */

#include "engine/SysSetLastErrorFunc.h"

static unsigned char _Curve_ModuleActive = 0;

int CurveInit(void)
{
    int error = 0;

    if (_Curve_ModuleActive) {
        error = 0x1E0001;
    } else {
        _Curve_ModuleActive = 1;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int CurveShutdown(void)
{
    int error = 0;

    if (_Curve_ModuleActive) {
        _Curve_ModuleActive = 0;
    } else {
        error = 0x1E0002;
    }
    SysSetLastErrorFunc(error);
    return error;
}
