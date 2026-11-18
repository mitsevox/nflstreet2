/* EA-XA block decoder (eaxadecf.cpp): decodes EA-XA compressed sample blocks to floats for the unpack
   filters. Allocation goes through the sound library's allocator callbacks. */

#include "engine/sndsys.h"

extern "C" {

void *fn_8027BD68(int size)
{
    return lbl_803B53E4(size);
}

void fn_8027BD94(void *p)
{
    lbl_803B53E8(p);
}

int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count)
{
    if (data == 0) {
        return -1;
    }
    if (p->m8 != 0) {
        return -1;
    }
    p->m8 = count;
    p->mC = size;
    p->m94.mC = data;
    return 0;
}

Pair_8027BFDC fn_8027BFDC(Struct_8027BE24 *p)
{
    Pair_8027BFDC pair;

    pair.m0 = p->m94.m4;
    pair.m4 = p->m94.m8;
    return pair;
}

void fn_8027C00C(Struct_8027BE24 *p, Pair_8027BFDC *pair)
{
    p->m94.m4 = pair->m0;
    p->m94.m8 = pair->m4;
}

}
