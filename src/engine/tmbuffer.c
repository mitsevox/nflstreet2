#include "engine/tmlib.h"

void fn_80214554(Buffer_80214554 *pBuffer, int size, int align)
{
    size = (size + (align - 1)) & -align;
    pBuffer->mpData = fn_802127D0(size, 1);
    pBuffer->mUsed = 0;
    pBuffer->mAlign = align;
    pBuffer->mSize = size;
}

void fn_802145B0(Buffer_80214554 *pBuffer)
{
    fn_80212814(pBuffer->mpData);
    pBuffer->mpData = 0;
    pBuffer->mUsed = 0;
    pBuffer->mAlign = 0;
    pBuffer->mSize = 0;
}

void fn_802145F4(Buffer_80214554 *pBuffer)
{
    pBuffer->mUsed = 0;
}

int fn_80214600(Buffer_80214554 *pBuffer)
{
    return pBuffer->mSize - pBuffer->mUsed;
}

unsigned char *fn_80214610(Buffer_80214554 *pBuffer, int size)
{
    if (size <= fn_80214600(pBuffer)) {
        return pBuffer->mpData + pBuffer->mUsed;
    }
    return 0;
}

void fn_8021465C(Buffer_80214554 *pBuffer, unsigned char *pEnd)
{
    pBuffer->mUsed = ((pEnd - pBuffer->mpData) + (pBuffer->mAlign - 1)) & -pBuffer->mAlign;
}

unsigned char *fn_80214680(Buffer_80214554 *pBuffer, int size)
{
    unsigned char *p = fn_80214610(pBuffer, size);

    if (p != 0) {
        fn_8021465C(pBuffer, p + size);
    }
    return p;
}
