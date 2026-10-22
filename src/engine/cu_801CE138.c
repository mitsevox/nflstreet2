/* Graphics library front end: init/shutdown guards and a context word. */

#include "engine/cu_801CE1F8.h"

extern unsigned char lbl_803EBC60;
extern int lbl_803EBC64;

int fn_801CE2F4(GlibConfig_801CE1F8 *pConfig);
int fn_801CE718(void);
void fn_801F7BD4(int error);

int fn_801CE138(GlibConfig_801CE1F8 *pConfig)
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

int fn_801CE190(void)
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

int fn_801CE1E8(void)
{
    return lbl_803EBC64;
}

void fn_801CE1F0(int value)
{
    lbl_803EBC64 = value;
}
