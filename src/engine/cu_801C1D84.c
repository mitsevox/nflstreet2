#include "unresolved.h"

void *fn_801C1F94(void *pDst, int value, int size)
{
    char *p = pDst;

    while (size--) {
        *p++ = value;
    }
    return pDst;
}

void *fn_801C1FBC(void *pDst, const void *pSrc, int size)
{
    char *d = pDst;
    const char *s = pSrc;

    while (size--) {
        *d++ = *s++;
    }
    return pDst;
}

int fn_801C1FEC(const void *pBuf1, const void *pBuf2, int size)
{
    const unsigned char *a = pBuf1;
    const unsigned char *b = pBuf2;

    while (size--) {
        if (*a != *b) {
            return *a - *b;
        }
        a++;
        b++;
    }
    return 0;
}

void *fn_801C2030(void *dst, const void *src, Uint32 n)
{
    unsigned char *out = dst;
    const unsigned char *in = src;

    if (in < out && out < in + n) {
        out += n;
        in += n;
        while (n--) {
            *--out = *--in;
        }
    } else {
        while (n--) {
            *out++ = *in++;
        }
    }
    return dst;
}
