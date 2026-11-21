/* Data-structure library module: init/shutdown and the shared size alignment. */

#include "engine/list.h"
#include "engine/SysSetLastErrorFunc.h"

static unsigned char _DS_ModuleActive = 0;

/* The size alignment of the data-structure library's allocations. */
static int _DS_Alignment = 4;

char DS_ModuleID[] = "DS.LIB";

void DSListInitModule(void);

int DSSetAlignment(int alignment);

int DSInit(void)
{
    int error = 0;

    if (!_DS_ModuleActive) {
        DSListInitModule();
        DSSetAlignment(4);
        _DS_ModuleActive = 1;
    } else {
        error = 0x30001;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int DSShutdown(void)
{
    int error = 0;

    if (_DS_ModuleActive) {
        _DS_ModuleActive = 0;
    } else {
        error = 0x30002;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int DSSetAlignment(int alignment)
{
    int old = _DS_Alignment;

    _DS_Alignment = alignment;
    return old;
}

int DSAlignSize(int size)
{
    return (size + (_DS_Alignment - 1)) & ~(_DS_Alignment - 1);
}
