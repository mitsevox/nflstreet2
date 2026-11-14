/* Time stretch filter (stretch.c): the mixer filter node that lengthens or shortens a voice's sample
   stream by repeating or dropping crossfaded frames. */

#include "engine/sndsys.h"

extern "C" {

void applyaction(Object_80277404 *p, float **buffer, int n)
{
    float *src;
    float *dst;

    if (p->m34 > 0) {
        src = p->m40;
        dst = *buffer;
    } else {
        src = *buffer;
        dst = src + p->m2C;
    }
    if (n == 0) {
        SNDI_memcpy(p->m838, src, p->m2C * 4);
        p->m30 -= p->m2C;
        p->m38 = p->m2C;
        *buffer = dst;
    } else if (n > 0) {
        SNDI_memcpy(p->m838, src, n * 4);
        fn_80276B7C(src, dst, &p->m838[n], p->m2C, n);
        p->m30 -= p->m2C;
        p->m38 = p->m2C + n;
        *buffer = dst;
    } else {
        fn_80276B7C(src, dst, p->m838, p->m2C, n);
        SNDI_memcpy(&p->m838[p->m2C], dst - n, (p->m2C + n) * 4);
        p->m30 -= p->m2C * 2;
        p->m38 = p->m2C * 2 + n;
        *buffer = dst + p->m2C;
    }
    p->m34 = 0;
    p->m3C = 0;
}

int transferframes(Object_80277404 *p, int *count, float **buffer)
{
    float *src = &p->m838[p->m3C];
    float *dst = *buffer;
    int n;
    if (*count > p->m38) {
        n = p->m38;
    } else {
        n = *count;
    }
    SNDI_memcpy(dst, src, n * 4);
    p->m3C += n;
    p->m38 -= n;
    *count -= n;
    *buffer += n;
    return n;
}

int stretchframesneeded(Object_80277404 *p, int count)
{
    unsigned char *data;
    float value;
    int total;
    int remaining;
    int n;
    int used;
    int produced;
    if (count > p->m38) {
        data = p->m1C;
        value = p->m28;
        total = 0;
        n = 0;
        count -= p->m38;
        remaining = p->m30;
        while (count > 0 && remaining >= p->m2C) {
            if (remaining < p->m2C * 2) {
                n = 0;
            } else {
                n = fn_80276C98(p->m2C, &data, &value, p->m24);
            }
            if (n >= 0) {
                used = p->m2C;
                produced = used + n;
            } else {
                used = p->m2C * 2;
                produced = used + n;
            }
            remaining -= used;
            total += used;
            if (count <= produced) {
                count = 0;
            } else {
                count -= produced;
            }
        }
        if (n > 0) {
            total += p->m2C;
        }
        if (count > 0) {
            if (count > remaining) {
                total += remaining;
            } else {
                total += count;
            }
        }
        if (total > p->m34) {
            return total - p->m34;
        }
    }
    return 0;
}

int stretch(Object_80277404 *p, int count, float *src, float *dst)
{
    int total = transferframes(p, &count, &dst);
    int n;
    if (count == 0) {
        return total;
    }
    n = 0;
    while (count > 0 && p->m30 >= p->m2C) {
        if (p->m30 < p->m2C * 2) {
            n = 0;
        } else {
            n = fn_80276C98(p->m2C, &p->m1C, &p->m28, p->m24);
        }
        applyaction(p, &src, n);
        total += transferframes(p, &count, &dst);
    }
    if (n > 0) {
        SNDI_memcpy(p->m40, src, p->m2C * 4);
        p->m34 = p->m2C;
        src += p->m2C;
    }
    if (count > 0) {
        n = count;
        if (n > p->m30) {
            n = p->m30;
        }
        SNDI_memcpy(dst, src, n * 4);
        total += n;
        p->m30 -= n;
    }
    return total;
}

int SFILTER_timestretch(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Object_80277404 *p = (Object_80277404 *)node;
    int n;
    int result;
    if (p->m30 == 0) {
        return node->m8->m0(node->m8, 200, b, a, node->m1A);
    }
    n = stretchframesneeded(p, count);
    if (p->m20 >= 0 && n > fn_802791D0(p->m20)) {
        return 0;
    }
    if (n > 0) {
        if (n * 4 > p->m1830) {
            if (p->m182C < (n & ~63) + 64) {
                fn_80279648((void **)&p->m1828, &p->m182C, (n & ~63) + 64, 4);
            }
            a = p->m1828 + 2;
        }
        result = node->m8->m0(node->m8, n, b, a, node->m1A);
        if (result <= 0) {
            return result;
        }
    }
    result = stretch(p, count, a, b);
    if (result < count) {
        memset(b + result, 0, (count - result) * 4);
    }
    return count;
}

void SFILTER_timestretchrestore(Object_80277404 *p)
{
    if (p->m1828 != 0) {
        SNDMEMI_free(p->m1828);
        p->m1828 = 0;
        p->m182C = 0;
    }
}

}
