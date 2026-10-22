#include <string.h>
#include "engine/t3db_table.h"

void fn_8020CEC4(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, void *pSrc, unsigned int len)
{
    unsigned int n;

    pRow += bitOffset >> 3;
    n = bitCount >> 3;
    if (len < n) {
        n = len;
    }
    memcpy(pRow, pSrc, n);
    if (n < bitCount >> 3) {
        memset(pRow + n, 0, (bitCount >> 3) - n);
    }
}

void fn_8020CF34(unsigned char *pRow, unsigned int bitOffset, unsigned int bitCount, unsigned char *pDst, unsigned int len)
{
    unsigned char *pSrc = pRow + (bitOffset >> 3);
    unsigned int n = bitCount >> 3;

    if (len < n) {
        n = len;
    }
    memcpy(pDst, pSrc, n);
    if (len > n) {
        memset(pDst + n, 0, len - n);
    }
}
