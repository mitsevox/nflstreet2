/* Partial source for the inferred partition 0x80264424-0x80266A2C (neutral file name). */

#include <string.h>

char *fn_80264424(char *dst, char *start, char *end, int *pLen)
{
    int len = end - start + 10;
    char *buf = __builtin_alloca(len);
    char *q = buf + len - 1;
    char *dot;
    char *p;
    int state;
    int count = 0;

    if (dst == 0 || start == 0 || end == 0)
        return 0;

    state = 0;
    p = start;
    dot = end;
    while (p <= end && state != 2) {
        switch (*p) {
        case '.':
            dot = p;
            if (state == 0)
                state = 1;
            break;
        case 'E':
        case 'e':
            state = 2;
            break;
        }
        p++;
    }
    if (state == 2)
        return start;

    for (p = end; p > start; p--) {
        *q-- = *p;
        if (p <= dot) {
            if (count % 3 == 0 && count != 0) {
                *q-- = ',';
                len++;
            }
            count++;
        }
    }
    *q = *p;
    len -= 10;
    memcpy(dst, q, len);
    *pLen = len;
    return dst;
}

void *fn_8026696C(const void *src, int c, unsigned long length)
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
