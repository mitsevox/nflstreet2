/* Task list behind the game's Task module: created at start-up with room for a given number of
   44-byte entries kept sorted by a 16-bit key, freed at shutdown, with the system time its clock starts from. */

#include "engine/SysSetLastErrorFunc.h"
#include "engine/dslist.h"

extern int SysGetSystemTime(void);

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
        lbl_803ECFAC = DSNewList(1, 0, count, 0x2C, TaskCompareKey, 0);
        if (lbl_803ECFAC == 0) {
            err = SysGetLastError();
        }
        TaskResetClock();
        lbl_803EBE9C = 1;
    } else {
        err = 0x80001;
    }
    lbl_803ECFB4 = 0;
    lbl_803ECFB8 = 0;
    SysSetLastErrorFunc(err);
    return err;
}

int TaskShutdown(void)
{
    int err = 0;

    if (lbl_803EBE9C != 0) {
        if (lbl_803ECFAC != 0) {
            DSDelList(lbl_803ECFAC);
        }
        lbl_803EBE9C = 0;
    } else {
        err = 0x80002;
    }
    SysSetLastErrorFunc(err);
    return err;
}

void TaskResetClock(void)
{
    lbl_803ECFB0 = SysGetSystemTime();
}
