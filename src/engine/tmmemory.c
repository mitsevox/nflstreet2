/* TM renderer memory: array allocation and release on the engine heap. */

#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"

void *TMMemAllocArray(int count, int size)
{
    if (count > 0 && size > 0) {
        return fn_801D2B7C(count * size, 0, 0);
    }
    return 0;
}

void TMMemFreeArray(void *p)
{
    if (p != 0) {
        fn_801D2BD0(p);
    }
}
