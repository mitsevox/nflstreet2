/* Sound voice controls (neutral file name): the end of the time-stretch filter, then controls
   that apply a value to every voice of a sound handle, pitch conversion and a tagged data reader. */

#include "engine/sndsys.h"

extern "C" {

void fn_80276DE4(Object_80277404 *p, float **buffer, int n)
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
        fn_8026B2E0(p->m838, src, p->m2C * 4);
        p->m30 -= p->m2C;
        p->m38 = p->m2C;
        *buffer = dst;
    } else if (n > 0) {
        fn_8026B2E0(p->m838, src, n * 4);
        fn_80276B7C(src, dst, &p->m838[n], p->m2C, n);
        p->m30 -= p->m2C;
        p->m38 = p->m2C + n;
        *buffer = dst;
    } else {
        fn_80276B7C(src, dst, p->m838, p->m2C, n);
        fn_8026B2E0(&p->m838[p->m2C], dst - n, (p->m2C + n) * 4);
        p->m30 -= p->m2C * 2;
        p->m38 = p->m2C * 2 + n;
        *buffer = dst + p->m2C;
    }
    p->m34 = 0;
    p->m3C = 0;
}

int fn_80276F38(Object_80277404 *p, int *count, float **buffer)
{
    float *src = &p->m838[p->m3C];
    float *dst = *buffer;
    int n;
    if (*count > p->m38) {
        n = p->m38;
    } else {
        n = *count;
    }
    fn_8026B2E0(dst, src, n * 4);
    p->m3C += n;
    p->m38 -= n;
    *count -= n;
    *buffer += n;
    return n;
}

int fn_80276FD4(Object_80277404 *p, int count)
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

int fn_802770F8(Object_80277404 *p, int count, float *src, float *dst)
{
    int total = fn_80276F38(p, &count, &dst);
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
        fn_80276DE4(p, &src, n);
        total += fn_80276F38(p, &count, &dst);
    }
    if (n > 0) {
        fn_8026B2E0(p->m40, src, p->m2C * 4);
        p->m34 = p->m2C;
        src += p->m2C;
    }
    if (count > 0) {
        n = count;
        if (n > p->m30) {
            n = p->m30;
        }
        fn_8026B2E0(dst, src, n * 4);
        total += n;
        p->m30 -= n;
    }
    return total;
}

int fn_80277280(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Object_80277404 *p = (Object_80277404 *)node;
    int n;
    int result;
    if (p->m30 == 0) {
        return node->m8->m0(node->m8, 200, b, a, node->m1A);
    }
    n = fn_80276FD4(p, count);
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
    result = fn_802770F8(p, count, a, b);
    if (result < count) {
        memset(b + result, 0, (count - result) * 4);
    }
    return count;
}

void fn_802773C0(Object_80277404 *p)
{
    if (p->m1828 != 0) {
        fn_8026B7D8(p->m1828);
        p->m1828 = 0;
        p->m182C = 0;
    }
}

int fn_80277520(int id, int offset, int value)
{
    int handle;
    int index;
    int clamped;
    Record_803A6DF0 *record;

    if (value < -0x4000) {
        clamped = -0x4000;
    } else if (value > 0x3FFF) {
        clamped = 0x3FFF;
    } else {
        clamped = value;
    }
    handle = fn_8026A288(id);
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            record = &lbl_803A6C24.m1CC[index];
            if (record->m23 == 1) {
                record->m1E = clamped;
                record->m1C = record->m4C + offset + record->m50;
                if (lbl_803A772C == 0) {
                    record->m1C = 0;
                }
                fn_80274960(index);
            }
        }
    }
    return handle;
}

/* Record set up by 0x80277CF0 (callers 0x8026C4DC and 0x8027838C); partial layout. */
typedef struct Channel_80277CF0 {
    unsigned short m0;
    unsigned char m2;
    unsigned char m3;
    unsigned char m4;
    unsigned char m5;
    unsigned char m6;
    unsigned char m7;
    unsigned short m8;
    unsigned char mUnknownA[2];
    short mC[6];
    int m18[6];
    unsigned char mUnknown30[0x18];
    int m48[4];
    int m58[4];
} Channel_80277CF0;

int fn_80277CF0(Channel_80277CF0 *p)
{
    int i;

    p->m2 = 0;
    p->m3 = 127;
    p->m4 = 64;
    p->m6 = 0;
    p->m7 = 2;
    p->m8 = 512;
    p->m0 = 0;
    p->m5 = 0;
    for (i = 0; i < 4; i++) {
        p->m48[i] = 0;
        p->m58[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        p->mC[i] = 0;
        p->m18[i] = 0;
    }
    return 0;
}

int fn_80277D88(int handle, int value)
{
    int index;
    Record_803A6DF0 *record;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            record = &lbl_803A6C24.m1CC[index];
            if (record->m68 == value || record->m86 == 0) {
                return 0;
            }
            record->m68 = value;
            record->m8A = 0;
            fn_80277EC4(index);
            fn_80274B50(index);
        }
    }
    return handle;
}

int fn_80277E38(int value)
{
    int scale;

    scale = 0x1000;
    while (value > 1199) {
        value -= 1200;
        scale <<= 1;
    }
    while (value <= -1200) {
        value += 1200;
        scale >>= 1;
    }
    value = (value * 13981) >> 16;
    if (value < -255) {
        value = -255;
    }
    if (value < 0) {
        scale = (scale * (lbl_80300EDC[value + 256] + 256)) >> 9;
    } else {
        scale = (scale * (lbl_80300EDC[value] + 256)) >> 8;
    }
    return scale;
}

void fn_80277EC4(int index)
{
    Record_803A6DF0 *record;
    int value;
    signed char key;

    record = &lbl_803A6C24.m1CC[index];
    if (record->m8A == 0) {
        value = record->m88;
        if (record->m86 != 0) {
            if (record->m78 != 0) {
                key = record->m78[record->m68];
            } else {
                key = record->m68;
            }
            value += ((key - 64) * record->m86) >> 6;
        }
        if (record->m80 != 0) {
            value += ((record->m80[record->m6C] - 64) * record->m84) >> 6;
        }
        record->m8A = fn_80277E38(value);
    }
    record->m8E = (record->m8A * record->m8C) >> 12;
}

int fn_80277F98(int handle, Desc_80276798 *desc)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            fn_802750B8(index, desc);
        }
    }
    return handle;
}

int fn_80278128(unsigned char *p, int size)
{
    int value;
    int i;

    value = 0;
    i = size;
    while (i-- != 0) {
        value = (value << 8) + *p++;
    }
    if (size == 1 && value > 0x7F) {
        value -= 0x100;
    } else if (size == 2 && value > 0x7FFF) {
        value -= 0x10000;
    } else if (size == 3 && value > 0x7FFFFF) {
        value -= 0x1000000;
    }
    return value;
}

int fn_8027823C(Parser_8027823C *p)
{
    while (*p->m0 == 0xFC) {
        p->m0++;
    }
    p->m4 = *p->m0;
    if (p->m4 == 0xFF) {
        return 0;
    }
    p->m0++;
    if (p->m4 == 0xFD) {
        return 1;
    }
    if (p->m4 == 0xFE) {
        return 1;
    }
    p->m10 = *p->m0;
    if (p->m10 == 0xFF) {
        p->m10 = fn_80278128(p->m0 + 1, 4);
        p->m0 += 4;
    }
    p->m0++;
    p->mC = p->m0;
    if (p->m10 <= 4) {
        p->m8 = fn_80278128(p->m0, p->m10);
    }
    p->m0 += p->m10;
    return 1;
}

int fn_80278530(int handle, int value)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            fn_80274E24(index, value);
        }
    }
    return handle;
}

}
