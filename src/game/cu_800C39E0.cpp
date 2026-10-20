#include "game/Object_80039F5C.h"

extern "C" int fn_801BE068(void *, void *, void *, unsigned short, void *, float);

extern "C" void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag)
{
    if (flag != 0) {
        index |= 0x8000;
    }
    p->mUnknown1008.mUnknown0 = index;
    p->mUnknown1008.mUnknown1 = (unsigned int)index >> 8;
    p->mUnknown1008.mUnknown2 = value;
    p->mUnknown1011 = (unsigned int)value >> 8;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, a, p, 1.0f);
}

