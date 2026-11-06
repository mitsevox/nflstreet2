/* A small aligned bump allocator the renderer uses for generated vertex data. */

#include "engine/tmlib.h"

void TMBufferNew(TMBuffer_t *pBuffer, int size, int align)
{
    size = (size + (align - 1)) & -align;
    pBuffer->mpData = TMMemAllocArray(size, 1);
    pBuffer->mUsed = 0;
    pBuffer->mAlign = align;
    pBuffer->mSize = size;
}

void TMBufferDelete(TMBuffer_t *pBuffer)
{
    TMMemFreeArray(pBuffer->mpData);
    pBuffer->mpData = 0;
    pBuffer->mUsed = 0;
    pBuffer->mAlign = 0;
    pBuffer->mSize = 0;
}

void TMBufferReset(TMBuffer_t *pBuffer)
{
    pBuffer->mUsed = 0;
}

int TMBufferGetFreeSpace(TMBuffer_t *pBuffer)
{
    return pBuffer->mSize - pBuffer->mUsed;
}

unsigned char *TMBufferOpen(TMBuffer_t *pBuffer, int size)
{
    if (size <= TMBufferGetFreeSpace(pBuffer)) {
        return pBuffer->mpData + pBuffer->mUsed;
    }
    return 0;
}

void TMBufferClose(TMBuffer_t *pBuffer, unsigned char *pEnd)
{
    pBuffer->mUsed = ((pEnd - pBuffer->mpData) + (pBuffer->mAlign - 1)) & -pBuffer->mAlign;
}

unsigned char *TMBufferAlloc(TMBuffer_t *pBuffer, int size)
{
    unsigned char *p = TMBufferOpen(pBuffer, size);

    if (p != 0) {
        TMBufferClose(pBuffer, p + size);
    }
    return p;
}
