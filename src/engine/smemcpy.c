/* Sound memory copy (smemcpy.c): the library's memory copy, moving words, halfwords or bytes
   depending on how the source and destination addresses are aligned to each other. */

#include "engine/sndbank.h"

int SNDI_memcpy(void *dst, void *src, int size)
{
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;
    unsigned int n = size;
    int diff = s - d;

    if (n == 0 || diff == 0) {
        return 0;
    }
    if (diff & 1) {
        for (; n > 3; n -= 4) {
            unsigned char b0 = s[0];
            unsigned char b1 = s[1];
            unsigned char b2 = s[2];
            unsigned char b3 = s[3];

            d[0] = b0;
            d[1] = b1;
            d[2] = b2;
            d[3] = b3;
            d += 4;
            s += 4;
        }
        for (; n != 0; n--) {
            *d++ = *s++;
        }
    } else if (diff & 2) {
        unsigned char *hd;
        unsigned char *hs;

        hs = s;
        hd = d;
        if ((unsigned int)s & 1) {
            *hd = *hs;
            hd++;
            hs++;
            n--;
        }
        for (; n > 7; n -= 8) {
            short h0 = ((short *)hs)[0];
            short h1 = ((short *)hs)[1];
            short h2 = ((short *)hs)[2];
            short h3 = ((short *)hs)[3];

            ((short *)hd)[0] = h0;
            ((short *)hd)[1] = h1;
            ((short *)hd)[2] = h2;
            ((short *)hd)[3] = h3;
            hd += 8;
            hs += 8;
        }
        for (; n > 1; n -= 2) {
            *(unsigned short *)hd = *(unsigned short *)hs;
            hd += 2;
            hs += 2;
        }
        if (n != 0) {
            *hd = *hs;
        }
    } else {
        if ((unsigned int)s & 1) {
            *d++ = *s++;
            n--;
        }
        if (((unsigned int)s & 2) && n > 1) {
            *(unsigned short *)d = *(unsigned short *)s;
            n -= 2;
            s += 2;
            d += 2;
        }
        for (; n > 15; n -= 16) {
            unsigned int w0 = ((unsigned int *)s)[0];
            unsigned int w1 = ((unsigned int *)s)[1];
            unsigned int w2 = ((unsigned int *)s)[2];
            unsigned int w3 = ((unsigned int *)s)[3];

            ((unsigned int *)d)[0] = w0;
            ((unsigned int *)d)[1] = w1;
            ((unsigned int *)d)[2] = w2;
            ((unsigned int *)d)[3] = w3;
            d += 16;
            s += 16;
        }
        for (; n > 3; n -= 4) {
            *(unsigned int *)d = *(unsigned int *)s;
            d += 4;
            s += 4;
        }
        if (n > 1) {
            *(unsigned short *)d = *(unsigned short *)s;
            n -= 2;
            s += 2;
            d += 2;
        }
        if (n != 0) {
            *d = *s;
        }
    }
    return 0;
}
