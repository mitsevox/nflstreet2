/* Sound memory manager (smemman.c): the library's main-memory heap, allocations taken in 16-byte steps
   from the bottom of one block and recorded in a table of offset/size pairs that grows down from its
   top. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

void SNDMEMI_constrain(unsigned int *start, int *size)
{
    Struct_80278894 *heap = lbl_803A6C24.m1D4;

    if (*start + *size > heap->mC) {
        *size = heap->mC - *start;
    }
}

void SNDMEMI_init(void *memory, int size)
{
    lbl_803A6C24.m1D4 = (Struct_80278894 *)memory;
    lbl_803A6C24.m1D4->m8 = size;
    lbl_803A6C24.m1D4->m4 = (SndMemEntry_t *)((char *)memory + size - 8);
    lbl_803A6C24.m1D4->m0 = (char *)memory + 24;
    lbl_803A6C24.m1D4->m0 = lbl_803A6C24.m1D4->m0 + 15;
    lbl_803A6C24.m1D4->m0 = (char *)((unsigned int)lbl_803A6C24.m1D4->m0 & ~15);
    size -= 15;
    lbl_803A6C24.m1D4->mC = size - 32;
    lbl_803A6C24.m1D4->m10 = size;
}

void SNDMEMI_restore(void)
{
    fn_80278894();
}

void *SNDMEMI_allocz(int size)
{
    int need = (size + 15) & ~15;
    int i = 0;
    unsigned int start;
    int avail;

    if (lbl_803A6C24.m1D4->m14 == 0) {
        start = 0;
        avail = lbl_803A6C24.m1D4->mC;
        SNDMEMI_constrain(&start, &avail);
        if (need > avail) {
            return 0;
        }
    } else {
        for (i = 0; i > lbl_803A6C24.m1D4->m14; i--) {
            SndMemEntry_t *table = lbl_803A6C24.m1D4->m4;

            if (i == 0) {
                start = 0;
                avail = table[i].m0;
            } else {
                start = table[i + 1].m0 + table[i + 1].m4;
                avail = table[i].m0 - start;
            }
            SNDMEMI_constrain(&start, &avail);
            if (need <= avail) {
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
        if (need > avail) {
            return 0;
        }
    }
found:
    lbl_803A6C24.m1D4->m4[i].m0 = start;
    lbl_803A6C24.m1D4->m4[i].m4 = need;
    lbl_803A6C24.m1D4->m14--;
    lbl_803A6C24.m1D4->mC -= 8;
    {
        Struct_80278894 *heap = lbl_803A6C24.m1D4;
        int left = heap->mC - (start + need);
        char *p = heap->m0 + start;

        if (left < heap->m10) {
            heap->m10 = left;
        }
        return p;
    }
}

void SNDMEMI_free(void *p)
{
    int i;
    int offset = (char *)p - lbl_803A6C24.m1D4->m0;

    for (i = 0; i > lbl_803A6C24.m1D4->m14; i--) {
        if (lbl_803A6C24.m1D4->m4[i].m0 == offset) {
            lbl_803A6C24.m1D4->m14++;
            lbl_803A6C24.m1D4->mC += 8;
            for (; i > lbl_803A6C24.m1D4->m14; i--) {
                lbl_803A6C24.m1D4->m4[i] = lbl_803A6C24.m1D4->m4[i - 1];
            }
            return;
        }
    }
}
