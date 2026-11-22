/* Sound memory manager (smemman.c): the library's main-memory heap, allocations taken in 16-byte steps
   from the bottom of one block and recorded in a table of offset/size pairs that grows down from its
   top. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

void SNDMEMI_constrain(unsigned int *start, int *size)
{
    SndMemPool_t *heap = lbl_803A6C24.m1D4;

    if (*start + *size > heap->mFreeEndOffset) {
        *size = heap->mFreeEndOffset - *start;
    }
}

void SNDMEMI_init(void *memory, int size)
{
    lbl_803A6C24.m1D4 = (SndMemPool_t *)memory;
    lbl_803A6C24.m1D4->mHeapSize = size;
    lbl_803A6C24.m1D4->mEntries = (SndMemEntry_t *)((char *)memory + size - 8);
    lbl_803A6C24.m1D4->mBase = (char *)memory + 24;
    lbl_803A6C24.m1D4->mBase = lbl_803A6C24.m1D4->mBase + 15;
    lbl_803A6C24.m1D4->mBase = (char *)((unsigned int)lbl_803A6C24.m1D4->mBase & ~15);
    size -= 15;
    lbl_803A6C24.m1D4->mFreeEndOffset = size - 32;
    lbl_803A6C24.m1D4->mLowWaterFreeBytes = size;
}

int SNDMEMI_restore(void)
{
    return SNDMEM_gethighwater();
}

/* Try gaps between recorded allocations before using the free tail of the heap. */
void *SNDMEMI_allocz(int size)
{
    // FAKEMATCH: reuse the adjacent entry pointer and form its byte offset in two steps for the target's register allocation.
    SndMemEntry_t *next;
    int i = 0;
    unsigned int start;
    int avail;

    size += 15;
    size &= ~15;
    if (lbl_803A6C24.m1D4->mNegativeEntryCount == 0) {
        start = 0;
        avail = lbl_803A6C24.m1D4->mFreeEndOffset;
        SNDMEMI_constrain(&start, &avail);
        if (size <= avail) {
            goto found;
        }
        goto fail;
    }
    for (i = 0; i > lbl_803A6C24.m1D4->mNegativeEntryCount; i--) {
        SndMemPool_t *heap = lbl_803A6C24.m1D4;
        SndMemEntry_t *entries = heap->mEntries;
        SndMemEntry_t *entry = &entries[i];
        int currentOffset = i * (int)sizeof(SndMemEntry_t);

        if (i == 0) {
            start = 0;
            avail = entry->mOffset;
        } else {
            int nextOffset = currentOffset + (int)sizeof(SndMemEntry_t);
            next = (SndMemEntry_t *)((char *)entries + nextOffset);
            start = next->mOffset + next->mSize;
            avail = entry->mOffset - start;
        }
        SNDMEMI_constrain(&start, &avail);
        if (size <= avail) {
            int j;

            for (j = lbl_803A6C24.m1D4->mNegativeEntryCount; j < i; j++) {
                lbl_803A6C24.m1D4->mEntries[j] = lbl_803A6C24.m1D4->mEntries[j + 1];
            }
            goto found;
        }
    }
    {
        SndMemPool_t *heap = lbl_803A6C24.m1D4;
        SndMemEntry_t *entries = heap->mEntries;
        int currentOffset = i * (int)sizeof(SndMemEntry_t);
        int nextOffset = currentOffset + (int)sizeof(SndMemEntry_t);
        next = (SndMemEntry_t *)((char *)entries + nextOffset);
        start = next->mOffset + next->mSize;
    }
    avail = lbl_803A6C24.m1D4->mFreeEndOffset - start;
    SNDMEMI_constrain(&start, &avail);
    if (size > avail) {
        goto fail;
    }
found:
    {
        SndMemEntry_t *e = &lbl_803A6C24.m1D4->mEntries[i];

        e->mOffset = start;
        e->mSize = size;
    }
    lbl_803A6C24.m1D4->mNegativeEntryCount--;
    lbl_803A6C24.m1D4->mFreeEndOffset -= 8;
    {
        SndMemPool_t *heap = lbl_803A6C24.m1D4;
        int left = heap->mFreeEndOffset - (start + size);
        char *p = heap->mBase + start;

        if (left < heap->mLowWaterFreeBytes) {
            heap->mLowWaterFreeBytes = left;
        }
        return p;
    }
fail:
    return 0;
}

void SNDMEMI_free(void *p)
{
    int i;
    int offset = (char *)p - lbl_803A6C24.m1D4->mBase;

    for (i = 0; i > lbl_803A6C24.m1D4->mNegativeEntryCount; i--) {
        // FAKEMATCH: the entry-pointer local keeps the target's add order (array base first, index offset second)
        SndMemEntry_t *e = &lbl_803A6C24.m1D4->mEntries[i];

        if (e->mOffset == offset) {
            lbl_803A6C24.m1D4->mNegativeEntryCount++;
            lbl_803A6C24.m1D4->mFreeEndOffset += 8;
            for (; i > lbl_803A6C24.m1D4->mNegativeEntryCount; i--) {
                lbl_803A6C24.m1D4->mEntries[i] = lbl_803A6C24.m1D4->mEntries[i - 1];
            }
            return;
        }
    }
}
