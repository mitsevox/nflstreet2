#include "game/Object_80039F5C.h"

struct Animation_8009C630 {
    char mUnknown0[4];
    unsigned short mUnknown4;
    char mUnknown6[74];
    float mUnknown80;
    char mUnknown84[16];
};

/* Partial, not exact: the target keeps the index * 0x64 offset and loads
   the float with lfsx from base + 0x50; ours loads it from the element
   address. Register allocation differs as a result. */
extern "C" float fn_8009C630(Object_80039F5C *p, int id)
{
    float result = 0.0f;
    for (unsigned int i = 0; i <= 3; i++) {
        if (((Animation_8009C630 *)p->mpUnknown792)[i].mUnknown4 == id) {
            result = ((Animation_8009C630 *)p->mpUnknown792)[i].mUnknown80;
            break;
        }
    }
    return result;
}
