#include "engine/TibNew.h"
#include "game/fn_801D2B7C.h"

void *operator new(unsigned int size, int heap)
{
    return fn_801D2B7C(size, heap, 0);
}

void *operator new[](unsigned int size, int heap)
{
    return fn_801D2B7C(size, heap, 0);
}

void operator delete(void *p)
{
    if (p != 0) {
        fn_801D2BD0(p);
    }
}

void operator delete[](void *p)
{
    if (p != 0) {
        fn_801D2BD0(p);
    }
}
