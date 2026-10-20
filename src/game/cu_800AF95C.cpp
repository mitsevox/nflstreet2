#include "game/cu_8008E978.h"

extern "C" void fn_800AF95C(Entry_800AF82C *p, int index, unsigned int count)
{
    Entry_800AF82C *pEntry = p + index;

    if (pEntry->mUnknown14 != 0) {
        pEntry->mUnknown14 = 0;
        pEntry->mUnknown3C = 1;
        pEntry->mUnknownC = pEntry->mUnknown10 = 1.0f / count;
    }
}
