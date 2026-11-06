/* Low-level memory helpers: platform allocation stubs and MemFill, which fills memory with a
   repeated 1-, 2-, 4-byte or larger pattern. */

#include "engine/llmemory.h"

extern void *memset(void *pDst, int value, unsigned int size);
extern void *memcpy();

void *MemGetMemLL(unsigned int size)
{
    return 0;
}

void MemFreeMemLL(void *pAddr)
{
}

int MemFill(char *pDst, unsigned int size, int value, unsigned int width)
{
    char *pPattern;
    char *pFill;
    unsigned int count;
    unsigned int remaining;
    unsigned int chunk;

    if (width == 1) {
        memset(pDst, value, size);
        return 0;
    }
    pPattern = pDst;
    if ((unsigned int)pPattern & 3) {
        pPattern = pPattern - ((unsigned int)pPattern & 3) + 4;
    }
    pFill = pPattern;
    count = 0;
    do {
        switch (width & 3) {
        case 0:
            pFill += width;
            count += width;
            break;
        case 2:
            pFill += width * 2;
            count += width * 2;
            break;
        case 1:
        case 3:
            pFill += width * 4;
            count += width * 4;
            break;
        }
    } while (count < 4);
    count = pFill - pDst;
    if (count > size) {
        count = size;
    }
    remaining = size - count;
    while (count != 0) {
        chunk = width;
        if (count < chunk) {
            chunk = count;
        }
        if (width <= 4) {
            if (width == 1) {
                char byte = value;
                memcpy(pDst, &byte, chunk);
            } else if (width == 2) {
                short half = value;
                memcpy(pDst, &half, chunk);
            } else if (width != 3) {
                memcpy(pDst, &value, chunk);
            }
        } else {
            memcpy(pDst, (void *)value, chunk);
        }
        pDst += chunk;
        count -= chunk;
    }
    while (remaining > 3) {
        *(int *)pFill = *(int *)pPattern;
        remaining -= 4;
        pPattern += 4;
        pFill += 4;
    }
    while (remaining > 1) {
        *(short *)pFill = *(short *)pPattern;
        remaining -= 2;
        pPattern += 2;
        pFill += 2;
    }
    while (remaining != 0) {
        *pFill = *pPattern;
        remaining--;
        pPattern++;
        pFill++;
    }
    return 0;
}
