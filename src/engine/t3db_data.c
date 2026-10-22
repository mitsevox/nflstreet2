#include "engine/tmlib.h"

void fn_8020CEC4(unsigned char *pRecord, unsigned int bitOffset, unsigned int bitSize, void *pSrc, unsigned int len)
{
    unsigned int n;

    pRecord += bitOffset >> 3;
    n = bitSize >> 3;
    if (len < n) {
        n = len;
    }
    memcpy(pRecord, pSrc, n);
    if (n < bitSize >> 3) {
        memset(pRecord + n, 0, (bitSize >> 3) - n);
    }
}

void fn_8020CF34(unsigned char *pRecord, unsigned int bitOffset, unsigned int bitSize, unsigned char *pDst, unsigned int len)
{
    unsigned char *pSrc = pRecord + (bitOffset >> 3);
    unsigned int n = bitSize >> 3;

    if (len < n) {
        n = len;
    }
    memcpy(pDst, pSrc, n);
    if (len > n) {
        memset(pDst + n, 0, len - n);
    }
}
