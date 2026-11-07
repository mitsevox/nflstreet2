/* Finds the first matching byte in a bounded memory region for runtime string and output processing. */

#include <string.h>

void *memchr(const void *src, int c, size_t length)
{
    const unsigned char *s = (const unsigned char *)src;
    unsigned long *asrc;
    unsigned long buffer;
    unsigned long mask;
    int i, j;

    c &= 0xff;
    if (!(length < 4) && !((long)s & 3)) {
        asrc = (unsigned long *)s;
        mask = 0;
        for (i = 0; i < 4; i++)
            mask = (mask << 8) + c;
        while (length >= 4) {
            buffer = *asrc;
            buffer ^= mask;
            if ((buffer - 0x01010101) & ~buffer & 0x80808080) {
                s = (unsigned char *)asrc;
                for (j = 0; j < 4; j++) {
                    if (*s == c)
                        return (void *)s;
                    s++;
                }
            }
            length -= 4;
            asrc++;
        }
        s = (unsigned char *)asrc;
    }
    while (length--) {
        if (*s == c)
            return (void *)s;
        s++;
    }
    return 0;
}
