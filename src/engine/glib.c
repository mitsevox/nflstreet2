/* Graphics library front end: init/shutdown guards and the TV mode word (1 selects 50 Hz frame timing). */

#include "engine/llglib.h"
#include "engine/fn_801F7BD4.h"

extern unsigned char lbl_803EBC60;
extern int lbl_803EBC64;

int fn_801CE2F4(GlibConfig_801CE1F8 *pConfig);
int fn_801CE718(void);

int GlibInit(GlibConfig_801CE1F8 *pConfig)
{
    int result;

    if (!lbl_803EBC60) {
        result = fn_801CE2F4(pConfig);
        lbl_803EBC60 = 1;
    } else {
        result = 0xE0001;
    }
    fn_801F7BD4(result);
    return result;
}

int GlibShutdown(void)
{
    int result;

    if (lbl_803EBC60) {
        result = fn_801CE718();
        lbl_803EBC60 = 0;
    } else {
        result = 0xE0002;
    }
    fn_801F7BD4(result);
    return result;
}

int GlibGetTvMode(void)
{
    return lbl_803EBC64;
}

void GlibSetTvMode(int value)
{
    lbl_803EBC64 = value;
}
