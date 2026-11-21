/* Graphics library front end: init/shutdown guards and the TV mode word (1 selects 50 Hz frame timing). */

#include "engine/llglib.h"
#include "engine/SysSetLastErrorFunc.h"

static unsigned char _Glib_ModuleActive = 0;

/* The TV mode GlibGetTvMode returns. */
static int _Glib_iTvMode = 0;

int GlibLLInit(GlibConfig_t *pConfig);
int GlibLLShutdown(void);

int GlibInit(GlibConfig_t *pConfig)
{
    int result;

    if (!_Glib_ModuleActive) {
        result = GlibLLInit(pConfig);
        _Glib_ModuleActive = 1;
    } else {
        result = 0xE0001;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int GlibShutdown(void)
{
    int result;

    if (_Glib_ModuleActive) {
        result = GlibLLShutdown();
        _Glib_ModuleActive = 0;
    } else {
        result = 0xE0002;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int GlibGetTvMode(void)
{
    return _Glib_iTvMode;
}

void GlibSetTvMode(int value)
{
    _Glib_iTvMode = value;
}
