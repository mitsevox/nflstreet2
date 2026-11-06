/* Task list behind the game's Task module: created at start-up with room for a given number of
   44-byte entries kept sorted by a 16-bit key, freed at shutdown, with the system time its clock starts from. */

#include "engine/fn_801F7BD4.h"
#include "game/fn_801C68FC.h"

extern int fn_801F7ABC(void);

extern unsigned char lbl_803EBE9C;
extern void *lbl_803ECFAC;
extern int lbl_803ECFB0;
extern int lbl_803ECFB4;
extern int lbl_803ECFB8;

void TaskResetClock(void);

int TaskCompareKey(void *pA, void *pB)
{
    return ((unsigned short *)pA)[1] - ((unsigned short *)pB)[1];
}

int TaskInit(int count)
{
    int err = 0;

    if (lbl_803EBE9C == 0) {
        lbl_803ECFAC = fn_801C68FC(1, 0, count, 0x2C, TaskCompareKey, 0);
        if (lbl_803ECFAC == 0) {
            err = fn_801F7C88();
        }
        TaskResetClock();
        lbl_803EBE9C = 1;
    } else {
        err = 0x80001;
    }
    lbl_803ECFB4 = 0;
    lbl_803ECFB8 = 0;
    fn_801F7BD4(err);
    return err;
}

int TaskShutdown(void)
{
    int err = 0;

    if (lbl_803EBE9C != 0) {
        if (lbl_803ECFAC != 0) {
            fn_801C69E4(lbl_803ECFAC);
        }
        lbl_803EBE9C = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}

void TaskResetClock(void)
{
    lbl_803ECFB0 = fn_801F7ABC();
}
