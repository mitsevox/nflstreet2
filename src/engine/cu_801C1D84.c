#include "unresolved.h"

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
