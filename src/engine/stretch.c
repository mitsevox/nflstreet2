/* Time stretch filter (stretch.c): the mixer filter node that lengthens or shortens a voice's sample
   stream by repeating or dropping crossfaded frames. The period bytes of the stretch data decide, frame
   by frame, whether keeping, repeating or dropping one period keeps the output closest to the ratio set
   by SFILTER_timestretchsetratio. Function names from the GoldenEye: Rogue Agent, Medal of Honor:
   European Assault and NASCAR 2005 symbol sets (stretch.c, TIMESTRETCHSTATE). */

#include "engine/sndsys.h"
#include "engine/sndutil.h"

extern "C" {

void crossfade(float *src, float *next, float *dst, int count, int n)
{
    int len;
    int i;
    float gain;
    float step;

    if (n > 0) {
        len = n;
        gain = 1.0f;
        step = -1.0f / count;
    } else {
        len = -n;
        gain = 0.0f;
        step = 1.0f / count;
    }
    for (i = len; i < count; i++) {
        dst[i - len] = gain * src[i] + (1.0f - gain) * src[i - len];
        gain += step;
    }
    for (i = 0; i < len; i++) {
        dst[count - len + i] = gain * next[i] + (1.0f - gain) * src[count - len + i];
        gain += step;
    }
}

int determineaction(int count, unsigned char **data, float *error, float ratio)
{
    unsigned char *p = *data;
    int skip = *p;
    int len = skip + count / 2;
    float keep;
    float change;

    // FAKEMATCH: negated >= reproduces the target's ordered-greater-or-equal branch (cror/bso)
    if (!(ratio >= 1.0f)) {
        keep = (count + *error) - ratio * count;
        change = ((count + count - len) + *error) - ratio * 2 * count;
        if (__builtin_fabsf(keep) < __builtin_fabsf(change)) {
            *data = p + 1;
            *error = keep;
            return 0;
        }
        *data = p + 2;
        *error = change;
        return -len;
    } else {
        keep = (count + *error) - ratio * count;
        change = ((count + len) + *error) - ratio * count;
        if (__builtin_fabsf(keep) < __builtin_fabsf(change)) {
            *data = p + 1;
            *error = keep;
            return 0;
        }
        *data = p + 1;
        *error = change;
        return len;
    }
}

void applyaction(TIMESTRETCHSTATE *p, float **buffer, int n)
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
        crossfade(src, dst, &p->m838[n], p->m2C, n);
        p->m30 -= p->m2C;
        p->m38 = p->m2C + n;
        *buffer = dst;
    } else {
        crossfade(src, dst, p->m838, p->m2C, n);
        SNDI_memcpy(&p->m838[p->m2C], dst - n, (p->m2C + n) * 4);
        p->m30 -= p->m2C * 2;
        p->m38 = p->m2C * 2 + n;
        *buffer = dst + p->m2C;
    }
    p->m34 = 0;
    p->m3C = 0;
}

int transferframes(TIMESTRETCHSTATE *p, int *count, float **buffer)
{
    float *src = &p->m838[p->m3C];
    float *dst = *buffer;
    int n;
    if (*count <= p->m38) {
        n = *count;
    } else {
        n = p->m38;
    }
    SNDI_memcpy(dst, src, n * 4);
    p->m3C += n;
    p->m38 -= n;
    *count -= n;
    *buffer += n;
    return n;
}

int stretchframesneeded(TIMESTRETCHSTATE *p, int count)
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
        while (count > 0) {
            if (remaining < p->m2C) {
                break;
            }
            if (remaining < p->m2C * 2) {
                n = 0;
            } else {
                n = determineaction(p->m2C, &data, &value, p->m24);
            }
            if (n >= 0) {
                used = p->m2C;
                produced = used + n;
            } else {
                used = p->m2C * 2;
                produced = used + n;
            }
            total += used;
            remaining -= used;
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

int stretch(TIMESTRETCHSTATE *p, int count, float *src, float *dst)
{
    int total = transferframes(p, &count, &dst);
    int n;
    if (count == 0) {
        return total;
    }
    n = 0;
    while (count > 0) {
        if (p->m30 < p->m2C) {
            break;
        }
        if (p->m30 < p->m2C * 2) {
            n = 0;
        } else {
            n = determineaction(p->m2C, &p->m1C, &p->m28, p->m24);
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
        int left;

        if (count > p->m30) {
            left = p->m30;
        } else {
            left = count;
        }
        SNDI_memcpy(dst, src, left * 4);
        total += left;
        p->m30 -= left;
    }
    return total;
}

void SFILTER_timestretchsetratio(Node_80279D90 *node, int ratio)
{
    TIMESTRETCHSTATE *p = (TIMESTRETCHSTATE *)node;

    p->m24 = ratio * (1.0f / 4096.0f);
}

int SFILTER_timestretch(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    TIMESTRETCHSTATE *p = (TIMESTRETCHSTATE *)node;
    // FAKEMATCH: buffer pointer local (target keeps a and b in their saved registers in this order)
    float *buf = a;
    int n;
    int result;
    if (p->m30 == 0) {
        return node->m8->m0(node->m8, 200, b, a, node->m1A);
    }
    n = stretchframesneeded(p, count);
    if (p->m20 >= 0 && n > SNDPKTPLAY_framesoutstanding(p->m20)) {
        return 0;
    }
    if (n > 0) {
        if (n * 4 > p->m1830) {
            // FAKEMATCH: the size is built in two steps so both steps use the argument register
            int size = n & ~63;

            size += 64;
            if (p->m182C < size) {
                Snd::Util::ReallocBuf((void **)&p->m1828, &p->m182C, size, 4);
            }
            buf = p->m1828 + 2;
        }
        result = node->m8->m0(node->m8, n, b, buf, node->m1A);
        if (result <= 0) {
            return result;
        }
    }
    result = stretch(p, count, buf, b);
    if (result < count) {
        memset(b + result, 0, (count - result) * 4);
    }
    return count;
}

void SFILTER_timestretchrestore(TIMESTRETCHSTATE *p)
{
    if (p->m1828 != 0) {
        SNDMEMI_free(p->m1828);
        p->m1828 = 0;
        p->m182C = 0;
    }
}

int SFILTER_timestretchinit(Node_80279D90 *node, unsigned char *data, int index)
{
    TIMESTRETCHSTATE *p = (TIMESTRETCHSTATE *)node;

    p->mNode.m0 = SFILTER_timestretch;
    p->mNode.m4 = (void (*)(Node_80279D90 *))SFILTER_timestretchrestore;
    if (index >= 0) {
        p->m20 = SNDPKTPLAYI_voicetopackethandle(fn_80274304(index));
    } else {
        p->m20 = -1;
    }
    p->m1C = data + 6;
    p->m24 = 1.0f;
    p->m28 = 0.0f;
    p->m2C = data[1] * 2;
    p->m30 = SNDI_getb(data + 2, 4);
    // FAKEMATCH: store order found by search; it reproduces the target's store schedule
    p->m34 = 0;
    p->m1830 = 2748;
    p->m38 = 0;
    p->m3C = 0;
    p->m1828 = 0;
    p->m182C = 0;
    return 0;
}

}
