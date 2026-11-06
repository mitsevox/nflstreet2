/* The saved flag byte that says whether the pass icons are shown. */

#include "game/fn_80238174.h"

extern "C" {
}

static void *_PassIconState_pFlags = 0;

extern "C" {
int PassIconStateBlockInit(void *p, int value)
{
    return 0;
}

int PassIconStateBlockShutdown(void *p, int value)
{
    return 0;
}

int PassIconStateBlockCompare(void *p, void *q)
{
    return 0;
}

void PassIconStateStart(void)
{
    void *pHandle = fn_80238174(0, &_PassIconState_pFlags, 4, 0, 0x67696E74);

    fn_80238234(pHandle, PassIconStateBlockInit, PassIconStateBlockShutdown, 0, PassIconStateBlockCompare);
    fn_802381E0(pHandle);
}

void *PassIconStateGetFlags(int value)
{
    if (value != 0) {
        return 0;
    }
    return _PassIconState_pFlags;
}
}
