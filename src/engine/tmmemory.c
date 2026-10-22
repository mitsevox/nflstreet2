#include "engine/tmlib.h"
#include "game/fn_801D2B7C.h"


void *fn_802127D0(int count, int size)
{
    if (count > 0 && size > 0) {
        return fn_801D2B7C(count * size, 0, 0);
    }
    return 0;
}

void fn_80212814(void *p)
{
    if (p != 0) {
        fn_801D2BD0(p);
    }
}
