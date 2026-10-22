#include "engine/t3db.h"

void fn_80201D94(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue,
                 int isSigned)
{
    unsigned int word = bitOffset / 32;
    unsigned int shift = 64 - bitCount;
    unsigned long long bits;

    pData += word;
    bits = *(unsigned long long *)pData << (bitOffset - word * 32);
    if (isSigned) {
        bits = (long long)bits >> shift;
    } else {
        bits >>= shift;
    }
    *pValue = bits;
}

void fn_80201E10(unsigned int *pData, unsigned int bitOffset, unsigned int bitCount, unsigned int *pValue)
{
    unsigned int word = bitOffset / 32;
    unsigned int shift;
    unsigned long long *pBits = (unsigned long long *)(pData + word);
    unsigned long long mask;
    unsigned long long bits;

    bitOffset -= word * 32;
    shift = 64 - bitOffset;
    shift -= bitCount;
    bits = *pBits;
    mask = ~0ULL >> (64 - bitCount);
    mask <<= shift;
    *pBits = (bits & ~mask) | (((unsigned long long)*pValue << shift) & mask);
}
