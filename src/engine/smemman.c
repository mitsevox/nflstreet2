/* Sound memory manager (smemman.c): the library's main-memory heap, allocations taken in 16-byte steps
   from the bottom of one block and recorded in a table of offset/size pairs that grows down from its
   top. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

void SNDMEMI_constrain(unsigned int *start, int *size)
{
    SndMemPool_t *heap = lbl_803A6C24.m1D4;

    if (*start + *size > heap->mC) {
        *size = heap->mC - *start;
    }
}

void SNDMEMI_init(void *memory, int size)
{
    lbl_803A6C24.m1D4 = (SndMemPool_t *)memory;
    lbl_803A6C24.m1D4->m8 = size;
    lbl_803A6C24.m1D4->m4 = (SndMemEntry_t *)((char *)memory + size - 8);
    lbl_803A6C24.m1D4->m0 = (char *)memory + 24;
    lbl_803A6C24.m1D4->m0 = lbl_803A6C24.m1D4->m0 + 15;
    lbl_803A6C24.m1D4->m0 = (char *)((unsigned int)lbl_803A6C24.m1D4->m0 & ~15);
    size -= 15;
    lbl_803A6C24.m1D4->mC = size - 32;
    lbl_803A6C24.m1D4->m10 = size;
}

int SNDMEMI_restore(void)
{
    return SNDMEM_gethighwater();
}

void *SNDMEMI_allocz(int size)
{
    int i = 0;
    unsigned int start;
    int avail;

    size += 15;
    size &= ~15;
    if (lbl_803A6C24.m1D4->m14 == 0) {
        start = 0;
        avail = lbl_803A6C24.m1D4->mC;
        SNDMEMI_constrain(&start, &avail);
        if (size <= avail) {
            goto found;
        }
        goto fail;
    }
    for (i = 0; i > lbl_803A6C24.m1D4->m14; i--) {
        SndMemEntry_t *e = &lbl_803A6C24.m1D4->m4[i];

        if (i == 0) {
            start = 0;
            avail = e->m0;
        } else {
            start = e[1].m0 + e[1].m4;
            avail = e->m0 - start;
        }
        SNDMEMI_constrain(&start, &avail);
        if (size <= avail) {
            int j;

            for (j = lbl_803A6C24.m1D4->m14; j < i; j++) {
                lbl_803A6C24.m1D4->m4[j] = lbl_803A6C24.m1D4->m4[j + 1];
            }
            goto found;
        }
    }
    start = lbl_803A6C24.m1D4->m4[i + 1].m0 + lbl_803A6C24.m1D4->m4[i + 1].m4;
    avail = lbl_803A6C24.m1D4->mC - start;
    SNDMEMI_constrain(&start, &avail);
    if (size > avail) {
        goto fail;
    }
found:
    {
        SndMemEntry_t *e = &lbl_803A6C24.m1D4->m4[i];

        e->m0 = start;
        e->m4 = size;
    }
    lbl_803A6C24.m1D4->m14--;
    lbl_803A6C24.m1D4->mC -= 8;
    {
        SndMemPool_t *heap = lbl_803A6C24.m1D4;
        int left = heap->mC - (start + size);
        char *p = heap->m0 + start;

        if (left < heap->m10) {
            heap->m10 = left;
        }
        return p;
    }
fail:
    return 0;
}

void SNDMEMI_free(void *p)
{
    int i;
    int offset = (char *)p - lbl_803A6C24.m1D4->m0;

    for (i = 0; i > lbl_803A6C24.m1D4->m14; i--) {
        // FAKEMATCH: the entry-pointer local keeps the target's add order (array base first, index offset second)
        SndMemEntry_t *e = &lbl_803A6C24.m1D4->m4[i];

        if (e->m0 == offset) {
            lbl_803A6C24.m1D4->m14++;
            lbl_803A6C24.m1D4->mC += 8;
            for (; i > lbl_803A6C24.m1D4->m14; i--) {
                lbl_803A6C24.m1D4->m4[i] = lbl_803A6C24.m1D4->m4[i - 1];
            }
            return;
        }
    }
}
