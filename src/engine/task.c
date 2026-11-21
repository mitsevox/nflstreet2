/* Task list behind the game's Task module: created at start-up with room for a given number of
   44-byte entries kept sorted by a 16-bit key, freed at shutdown, with the system time its clock starts from. */

#include "engine/SysSetLastErrorFunc.h"
#include "engine/dslist.h"

extern int SysGetSystemTime(void);

static unsigned char _Task_ModuleActive = 0;

/* The task list, the system time of the last clock reset, and two words TaskInit clears. */
static void *_Task_pList;
static int _Task_iClockStart;
static int _Task_iUnused0;
static int _Task_iUnused1;

void TaskResetClock(void);

int TaskCompareKey(void *pA, void *pB)
{
    return ((unsigned short *)pA)[1] - ((unsigned short *)pB)[1];
}

int TaskInit(int count)
{
    int err = 0;

    if (_Task_ModuleActive == 0) {
        _Task_pList = DSNewList(1, 0, count, 0x2C, TaskCompareKey, 0);
        if (_Task_pList == 0) {
            err = SysGetLastError();
        }
        TaskResetClock();
        _Task_ModuleActive = 1;
    } else {
        err = 0x80001;
    }
    _Task_iUnused0 = 0;
    _Task_iUnused1 = 0;
    SysSetLastErrorFunc(err);
    return err;
}

int TaskShutdown(void)
{
    int err = 0;

    if (_Task_ModuleActive != 0) {
        if (_Task_pList != 0) {
            DSDelList(_Task_pList);
        }
        _Task_ModuleActive = 0;
    } else {
        err = 0x80002;
    }
    SysSetLastErrorFunc(err);
    return err;
}

void TaskResetClock(void)
{
    _Task_iClockStart = SysGetSystemTime();
}
