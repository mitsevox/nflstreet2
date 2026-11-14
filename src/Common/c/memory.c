/* The C library's memory block functions: fill, copy, compare and overlap-safe move of byte
   blocks, used throughout the game, the engine and the Nintendo SDK. Each works one byte at a time. */
#include <string.h>

void *memset(void *pDst, int value, size_t size)
{
    char *p = pDst;

    while (size--) {
        *p++ = value;
    }
    return pDst;
}

void *memcpy(void *pDst, const void *pSrc, size_t size)
{
    char *d = pDst;
    const char *s = pSrc;

    while (size--) {
        *d++ = *s++;
    }
    return pDst;
}

int memcmp(const void *pBuf1, const void *pBuf2, size_t size)
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

void *memmove(void *pDst, const void *pSrc, size_t size)
{
    unsigned char *out = pDst;
    const unsigned char *in = pSrc;

    if (in < out && out < in + size) {
        out += size;
        in += size;
        while (size--) {
            *--out = *--in;
        }
    } else {
        while (size--) {
            *out++ = *in++;
        }
    }
    return pDst;
}
