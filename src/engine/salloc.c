/* Partial source of the sound library's voice allocator (salloc.c). */

#include "engine/sndaems.h"

extern "C" {

extern short lbl_803A6C04[];

int fn_80269CE8(int value, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (lbl_803A6C04[i] == value)
            return 1;
    }
    return 0;
}

int fn_8026A288(int handle)
{
    int index;
    Voice_803A6C24 *v;

    if (handle < 0)
        return -8;
    index = handle & 0xFF;
    if (index >= lbl_803A6C24.mUnknown16C)
        return -8;
    v = lbl_803A6C24.mUnknown1CC + index;
    if (v->mUnknown6D != 0 && v->mUnknown0 == handle)
        return index;
    return -8;
}
}
