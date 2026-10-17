#include "game/Object_80039F5C.h"
#include "game/Block_801BE60C.h"

extern "C" void fn_800A42BC(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    float scale = 0.4f;

    pBlock->mUnknown8 = 1.0f;
    if (p->mRatings[0] > 127) {
        pBlock->mUnknown8 = (float)(short)(p->mRatings[0] - 127) / 128.0f * scale + 1.0f;
    }
}
