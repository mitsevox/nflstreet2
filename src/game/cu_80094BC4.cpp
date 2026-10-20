#include "game/cu_8008E978.h"

extern "C" void fn_80094BC4(Entry_80094BC4 *p)
{
    p->mpUnknown0 = 0;
    p->mUnknown8 = -1;
    p->mpUnknown4 = 0;
    p->mUnknownC = 0;
    p->mUnknown10 = 0;
    {
        Vector_80039F5C *pV = &p->mUnknown14;

        pV->mX = pV->mY = pV->mZ = 0.0f;
    }
    p->mUnknown24 = 0;
}
