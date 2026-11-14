/* Sound memory (smemhigh.cpp): reports the sound heap's high-water mark as a percentage of the heap
   size. */

#include "engine/sndsys.h"

extern "C" {

int SNDMEM_gethighwater(void)
{
    SndMemPool_t *p;

    p = lbl_803A6C24.m1D4;
    return (p->m8 - p->m10) * 100 / p->m8;
}

}
