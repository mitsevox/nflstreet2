/* Partial source for the inferred partition 0x80264424-0x8026A664 (neutral file name). */

#include <string.h>

typedef struct Entry_80266D20 {
    unsigned char mUnknown0[11];
    signed char mUnknownB;
} Entry_80266D20;

typedef struct Object_80266AF8 {
    unsigned int mUnknown0;
    unsigned char mUnknown4[4];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[6];
    unsigned short mUnknown10;
    unsigned char mUnknown12;
} Object_80266AF8;

typedef struct Slot_8037E0B4 {
    Object_80266AF8 *mObject;
    int mKey;
} Slot_8037E0B4;

typedef struct Range_80267114 {
    int mMin;
    int mMax;
} Range_80267114;

typedef struct Object_80267114 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[2];
    Range_80267114 mUnknownC[1];
} Object_80267114;

typedef struct Object_8026739C {
    unsigned char mUnknown0[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} Object_8026739C;

typedef struct Object_80267404 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    signed char mUnknownC;
    unsigned char mUnknownD[3];
    int mUnknown10;
    int mUnknown14;
} Object_80267404;

typedef struct Object_80267480 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
} Object_80267480;

typedef struct Object_802674DC {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    signed char mUnknown3;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    int mUnknownC;
    union {
        unsigned char mBytes[1];
        unsigned short mShorts[1];
    } mUnknown10;
} Object_802674DC;

typedef struct Object_8026769C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    int mUnknown14;
} Object_8026769C;

typedef struct Object_802677B4 {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4;
    int mUnknown8[1];
} Object_802677B4;

typedef struct Object_80267814 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    int mUnknown4[1];
} Object_80267814;

typedef struct Args_80267D84 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mValues[1];
} Args_80267D84;

typedef struct Object_80267DB4 {
    unsigned char mCount;
    unsigned char mUnknown1;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC[1];
} Object_80267DB4;

typedef struct Object_80268480 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    short mUnknown8;
    unsigned char mUnknownA[2];
    unsigned short mUnknownC;
    short mUnknownE;
    unsigned char mUnknown10[4];
    unsigned short mUnknown14;
    unsigned short mUnknown16;
} Object_80268480;

typedef struct Entry_802686CC {
    unsigned char mType;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mUnknown8;
} Entry_802686CC;

typedef struct Object_802686CC {
    unsigned char mUnknown0[8];
    int mUnknown8;
    unsigned char mUnknownC[2];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} Object_802686CC;

typedef struct Owner_802685B8 {
    unsigned char mUnknown0[64];
    int mUnknown40;
} Owner_802685B8;

typedef struct Object_802685B8 {
    Owner_802685B8 *mUnknown0;
    unsigned char mUnknown4[10];
    unsigned char mUnknownE;
    unsigned char mUnknownF[13];
    Entry_802686CC mEntries[1];
} Object_802685B8;

typedef struct Result_802685B8 {
    int mUnknown0;
} Result_802685B8;

typedef struct Object_80268F54 {
    unsigned char mCount;
    unsigned char mUnknown1[3];
    int mUnknown4;
    int mValues[1];
} Object_80268F54;

typedef struct Object_80268FFC {
    unsigned char mUnknown0[24];
    int mUnknown18;
} Object_80268FFC;

typedef struct Object_80269008 {
    unsigned char mUnknown0[16];
    int mUnknown10;
} Object_80269008;

typedef struct Object_80269014 {
    unsigned char mUnknown0[16];
    unsigned char mUnknown10;
    unsigned char mUnknown11[3];
    int mUnknown14[1];
} Object_80269014;

typedef struct Object_80269048 {
    unsigned char mUnknown0[24];
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A[2];
    int mUnknown1C[1];
} Object_80269048;

typedef struct Object_803A6BCC {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8[32];
    int mUnknown28;
    int mUnknown2C;
} Object_803A6BCC;

typedef struct Voice_803A6C24 {
    int mUnknown0;
    short mUnknown4[12];
    unsigned short mUnknown1C;
    unsigned char mUnknown1E[5];
    unsigned char mUnknown23;
    unsigned char mUnknown24[59];
    unsigned char mUnknown5F;
    unsigned char mUnknown60[13];
    unsigned char mUnknown6D;
    unsigned short mUnknown6E;
    unsigned char mUnknown70[30];
    unsigned short mUnknown8E;
} Voice_803A6C24;

typedef struct Object_803A6C24 {
    unsigned char mUnknown0[364];
    short mUnknown16C;
    signed char mUnknown16E;
    unsigned char mUnknown16F[53];
    void (*mUnknown1A4[10])(void *);
    Voice_803A6C24 *mUnknown1CC;
} Object_803A6C24;

typedef struct Object_8026A40C {
    unsigned char mUnknown0[23];
    signed char mUnknown17;
    unsigned char mUnknown18[28];
    int mUnknown34[4];
    int mUnknown44[4];
} Object_8026A40C;

typedef struct Message_8026A40C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} Message_8026A40C;

extern Slot_8037E0B4 lbl_8037E0B4[8];
extern void (*lbl_802FFB6C[])(Object_80268480 *params, int value);
extern Object_803A6BCC lbl_803A6BCC;
extern Object_803A6C24 lbl_803A6C24;
extern short lbl_803A6C04[];

extern int fn_801AC9C8(int fd, void *buf, int len);
extern void *fn_801AE6BC(int *key);
extern void fn_801AFABC(Object_80266AF8 *p, int *a, int *b);
extern int fn_801AEAEC(int *block);
extern int *fn_801AF4A8(int size);
extern void fn_801AF500(int *block);
extern void fn_801B9410(void *p, int *values);
extern void fn_801B9B30(void *p, int *value);
extern int fn_80266A2C(void *buf, int len);
extern void fn_80266DAC(Object_80266AF8 *p);
extern int fn_8026A288(int handle);
extern int fn_8026AAF0(int a, int b, Object_80268480 *params);
extern void fn_8026CA50(Object_80268480 *params);
extern unsigned int fn_8026CB14(void);
extern int fn_8026C9BC(int handle, int value);
extern int fn_8026EAC0(int handle, int a, int b);
extern int fn_8026ECCC(int handle, int value);
extern int fn_8026ED74(int handle, int value);
extern int fn_8026EDC4(int handle);
extern int fn_8026EEB0(int handle, int value);
extern int fn_8026EF38(int handle, int value);
extern int fn_8026F2C8(int handle, int value);
extern int fn_802714A8(int handle, int value);
extern int fn_80274B50(int voice, int value);
extern int fn_80274CA8(int voice, int value);
extern void fn_80274924(int voice);
extern void fn_80274960(int voice, int value);
extern void fn_80274D34(int voice, int value);
extern void fn_80274E24(int voice, int value);
extern void fn_80268188(int handle, int value);

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

int fn_80266A88(int fd, void *buf, int len)
{
    if (fd == 1 || fd == 2)
        return fn_80266A2C(buf, len);
    if (fd == 0)
        return -1;
    return fn_801AC9C8(fd, buf, len);
}

int fn_80266AD8(int fd, void *buf, int len)
{
    return fn_80266A88(fd, buf, len);
}

void *fn_80266AF8(Object_80266AF8 *p)
{
    return (char *)p + (((p->mUnknown10 * 2 + 3) & ~3) + 24);
}

void fn_80266B14(int key)
{
    int i;
    int j;
    unsigned char *bytes;

    for (i = 0; i < 8; i++) {
        if (lbl_8037E0B4[i].mObject != 0 && lbl_8037E0B4[i].mKey == key) {
            bytes = fn_80266AF8(lbl_8037E0B4[i].mObject);
            for (j = 0; j < lbl_8037E0B4[i].mObject->mUnknown12; j++)
                bytes[j] = 0xFF;
        }
    }
}

int fn_80266BB8(Object_80266AF8 *p, int key)
{
    int a;
    int b;
    int result = 0;
    int i;

    if ((p->mUnknown0 & 0xFFFF0000) == 0x03100000) {
        fn_801AFABC(p, &a, &b);
        for (i = 0; i < 8; i++) {
            Object_80266AF8 *object = lbl_8037E0B4[i].mObject;
            if (object != 0 && object->mUnknown9 == b && object->mUnknown8 == a)
                return result;
        }
        for (i = 0; i < 8; i++) {
            if (lbl_8037E0B4[i].mObject == 0) {
                lbl_8037E0B4[i].mObject = p;
                result = 1;
                lbl_8037E0B4[i].mKey = key;
                break;
            }
        }
        fn_80266B14(key);
    }
    return result;
}

int fn_80266CB8(Object_80266AF8 *p, unsigned int key)
{
    int result = 0;

    if (key <= 7) {
        result = fn_80266BB8(p, key);
        fn_80266DAC(p);
    }
    return result;
}

unsigned short *fn_80266D0C(void *base, unsigned short *offsets, int index)
{
    return (unsigned short *)((char *)base + offsets[index] * 4);
}

void fn_80266D20(void *data, int key)
{
    Entry_80266D20 *entry;
    int *block;
    int size;

    entry = fn_801AE6BC(&key);
    if (entry != 0) {
        size = entry->mUnknownB * 4;
        block = fn_801AF4A8(size + 4);
        if (block != 0) {
            *block = key;
            memcpy(block + 1, data, size);
            if (fn_801AEAEC(block) == 0)
                fn_801AF500(block);
        }
    }
}

int fn_80266E88(int *p)
{
    int value = p[4];

    p[4] = 0;
    return value;
}

int fn_80266E9C(int *p)
{
    return p[5];
}

int fn_80266EA4(int *p)
{
    return p[6];
}

int fn_80266EAC(int *p)
{
    int value = p[0];

    p[0] = 0;
    return value;
}

int fn_80267114(Object_80267114 *p)
{
    int *values;
    int i;

    if (p->mUnknown8) {
        values = (int *)&p->mUnknownC[p->mUnknown9];
        for (i = 0; i < p->mUnknown9; i++) {
            int value = values[i + 1];
            int clamped;

            if (value < p->mUnknownC[i].mMin) {
                clamped = p->mUnknownC[i].mMin;
            } else {
                clamped = value;
                if (value > p->mUnknownC[i].mMax)
                    clamped = p->mUnknownC[i].mMax;
            }
            values[i + 1] = clamped;
        }
    } else {
        values = (int *)p->mUnknownC;
    }
    if (values[0] != 0)
        fn_801B9410(p, values + 1);
    return 0;
}

int fn_8026739C(Object_8026739C *p)
{
    int value;
    int v = p->mUnknown14;
    int lo, hi;

    if (p->mUnknown10 != v) {
        p->mUnknown10 = v;
        lo = p->mUnknown8;
        hi = p->mUnknownC;
        if (v < lo)
            value = lo;
        else if (v > hi)
            value = hi;
        else
            value = v;
        fn_801B9B30(p, &value);
    }
    return 0;
}

int fn_80267404(Object_80267404 *p)
{
    int v = p->mUnknown14;

    if (v >= p->mUnknown0 && v <= p->mUnknown4)
        return v;
    if (p->mUnknown10 > 0) {
        p->mUnknown8 += p->mUnknownC;
        if (p->mUnknown8 > p->mUnknown4)
            p->mUnknown8 = p->mUnknown0;
        else if (p->mUnknown8 < p->mUnknown0)
            p->mUnknown8 = p->mUnknown4;
        return p->mUnknown8;
    }
    return p->mUnknown8;
}

int fn_80267480(Object_80267480 *p)
{
    int result;

    if (p->mUnknownC != 0) {
        result = fn_8026CB14() % p->mUnknown4 + p->mUnknown0;
        p->mUnknown8 = result;
    } else {
        result = p->mUnknown8;
    }
    return result;
}

int fn_802674DC(Object_802674DC *p)
{
    unsigned int index;

    if (*(int *)((char *)p + p->mUnknown0) != 0) {
        index = fn_8026CB14() % (unsigned int)(p->mUnknownA - p->mUnknown8 - p->mUnknown3) + p->mUnknown8;
        if (p->mUnknown2 == 1) {
            p->mUnknownC = p->mUnknown10.mBytes[index];
            p->mUnknown10.mBytes[index] = p->mUnknown10.mBytes[p->mUnknown8];
            p->mUnknown10.mBytes[p->mUnknown8] = p->mUnknownC;
        } else {
            p->mUnknownC = p->mUnknown10.mShorts[index];
            p->mUnknown10.mShorts[index] = p->mUnknown10.mShorts[p->mUnknown8];
            p->mUnknown10.mShorts[p->mUnknown8] = p->mUnknownC;
        }
        p->mUnknownC += p->mUnknown4;
        if (++p->mUnknown8 >= p->mUnknownA) {
            p->mUnknown8 = 0;
            p->mUnknown3 = 1;
        } else {
            p->mUnknown3 = 0;
        }
    }
    return p->mUnknownC;
}

int fn_8026769C(Object_8026769C *p)
{
    if (p->mUnknown14 >= p->mUnknown0 && p->mUnknown14 <= p->mUnknown4) {
        if (p->mUnknown10 == 0) {
            p->mUnknown10 = 1;
            p->mUnknown11 = 1;
            return 1;
        }
    } else if (p->mUnknown14 >= p->mUnknown8 && p->mUnknown14 <= p->mUnknownC) {
        p->mUnknown10 = 0;
    }
    p->mUnknown11 = 0;
    return 0;
}

int fn_802677B4(Object_802677B4 *p)
{
    int *flags = (int *)((char *)p + p->mUnknown0);
    int i;

    for (i = 0; i < p->mUnknown2; i++) {
        if (flags[i] != 0) {
            p->mUnknown4 = p->mUnknown8[i];
            break;
        }
    }
    return p->mUnknown4;
}

int fn_80267814(Object_80267814 *p)
{
    int i;

    for (i = 0; i < p->mUnknown0; i++) {
        if (p->mUnknown4[i] != 0)
            return 1;
    }
    return 0;
}

int fn_80267D84(Args_80267D84 *p)
{
    int index = p->mValues[0];

    if (index <= 0 || index > p->mCount)
        return 0;
    return p->mValues[index];
}

int fn_80267DB4(Object_80267DB4 *p)
{
    int index;

    p->mUnknownC[p->mUnknown2 - 1] = 0;
    index = p->mUnknown4;
    if (index > 0 && index <= p->mCount) {
        p->mUnknownC[index - 1] = p->mUnknown8;
        p->mUnknown2 = p->mUnknown4;
    }
    return p->mUnknownC[0];
}

int fn_80267E04(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] < result)
            result = p->mValues[i];
    }
    return result;
}

int fn_80267E48(int *p)
{
    int a = p[0];
    int b = p[1];

    if (a < b)
        return a;
    return b;
}

int fn_80267E64(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++) {
        if (p->mValues[i] > result)
            result = p->mValues[i];
    }
    return result;
}

int fn_80267EA8(int *p)
{
    int a = p[0];
    int b = p[1];

    if (a > b)
        return a;
    return b;
}

int fn_8026801C(Args_80267D84 *p)
{
    int i;
    int result = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        result += p->mValues[i];
    return result;
}

int fn_80268058(int *p)
{
    return p[0] + p[1];
}

int fn_80268068(int *p)
{
    return p[0] - p[1];
}

int fn_80268078(int *p)
{
    return p[0] * p[1];
}

int fn_80268088(int *p)
{
    if (p[1] != 0)
        return p[0] / p[1];
    return 0;
}

int fn_802680A8(int *p)
{
    if (p[1] != 0)
        return p[0] % p[1];
    return 0;
}

void fn_802680D0(void)
{
}

int fn_802680D4(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    lbl_803A6C24.mUnknown1CC[voice].mUnknown8E = value;
    return fn_80274B50(voice, value);
}

int fn_80268130(int voice, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    lbl_803A6C24.mUnknown1CC[voice].mUnknown6E = value;
    return fn_80274CA8(voice, value);
}

void fn_80268270(int voice, int value)
{
    Voice_803A6C24 *v = &lbl_803A6C24.mUnknown1CC[voice];

    if (v->mUnknown23 == 1) {
        v->mUnknown1C = value;
        fn_80274960(voice, value);
    }
}

void fn_80268354(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    fn_80274D34(voice, value);
}

void fn_8026839C(int voice, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    fn_80274E24(voice, value);
}

void fn_802683E4(int voice, int value)
{
    Voice_803A6C24 *v = &lbl_803A6C24.mUnknown1CC[voice];
    int clamped;
    int i;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    value = clamped >> 8;
    for (i = 0; i < v->mUnknown23; i++) {
        int index = v->mUnknown4[i];
        lbl_803A6C24.mUnknown1CC[index].mUnknown5F = value;
        fn_80274924(index);
    }
}

void fn_80268480(Object_80268480 *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->mUnknownC = value;
}

void fn_802684B0(Object_80268480 *p, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    p->mUnknownE = value;
}

void fn_802684D4(Object_80268480 *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->mUnknown0 = clamped >> 8;
}

void fn_802684FC(Object_80268480 *p, int value)
{
    p->mUnknown8 = value;
}

void fn_80268504(Object_80268480 *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->mUnknown5 = clamped >> 8;
}

void fn_8026852C(Object_80268480 *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->mUnknown14 = value;
}

void fn_8026855C(Object_80268480 *p, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    p->mUnknown16 = value;
}

void fn_8026858C(Object_80268480 *p, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    p->mUnknown4 = clamped >> 8;
}

void fn_802685B4(void)
{
}

Result_802685B8 fn_802685B8(Object_802685B8 *p, int *q)
{
    Object_80268480 params;
    Result_802685B8 result;
    Entry_802686CC *e;
    int i;

    fn_8026CA50(&params);
    params.mUnknown5 = 0;
    e = p->mEntries;
    for (i = 0; i < p->mUnknownE; i++, e++) {
        lbl_802FFB6C[e->mType](&params, e->mUnknown8);
        e->mUnknown4 = e->mUnknown8;
    }
    result.mUnknown0 = fn_8026AAF0(p->mUnknown0->mUnknown40, q[1], &params);
    return result;
}

int fn_80268668(Object_802686CC *p)
{
    return fn_8026EDC4(p->mUnknown8);
}

int fn_8026868C(int *p)
{
    int handle = *p;

    fn_802714A8(handle, 0);
    return fn_8026C9BC(handle, 0);
}

void fn_802686CC(Object_802686CC *p)
{
    int a = 4096;
    int b = 32767;
    int handle;
    int i;
    Entry_802686CC *e;

    handle = fn_8026A288(p->mUnknown8);
    if (handle >= 0) {
        e = p->mEntries;
        for (i = 0; i < p->mUnknownE; i++, e++) {
            if (e->mType == 0) {
                a = e->mUnknown8;
                e->mUnknown4 = a;
            } else if (e->mType == 2) {
                b = e->mUnknown8;
                e->mUnknown4 = b;
            }
        }
        fn_802680D4(handle, a);
        fn_80268188(handle, b);
    }
}

int fn_80268F54(Object_80268F54 *p)
{
    int i;
    int sum = p->mValues[0];

    for (i = 1; i < p->mCount; i++)
        sum += p->mValues[i];
    if (sum > p->mUnknown4)
        return p->mUnknown4;
    return sum;
}

int fn_80268FA0(int *p)
{
    int value = p[1] - p[2];

    if (value < p[0])
        return p[0];
    return value;
}

int fn_80268FC4(int *p)
{
    int value = p[1] * p[2];

    if (value > p[0])
        return p[0];
    return value;
}

int fn_80268FE8(Object_80269048 *p)
{
    int value = p->mUnknown19;

    p->mUnknown19 = 0;
    return value;
}

void fn_80268FFC(int *values, Object_80268FFC *p)
{
    p->mUnknown18 = values[0];
}

void fn_80269008(int *values, Object_80269008 *p)
{
    p->mUnknown10 = 1;
}

void fn_80269014(int *values, Object_80269014 *p)
{
    int i;

    for (i = 0; i < p->mUnknown10; i++)
        p->mUnknown14[i] = values[i];
}

void fn_80269048(int *values, Object_80269048 *p)
{
    int i;

    for (i = 0; i < p->mUnknown18; i++)
        p->mUnknown1C[i] = values[i];
    p->mUnknown19 = 1;
}

void fn_80269990(int a, int b)
{
    if (b == 0xFFFF && a != 0) {
        lbl_803A6BCC.mUnknown0 = 0;
        lbl_803A6BCC.mUnknown4 = 0;
        lbl_803A6BCC.mUnknown28 = 0;
        lbl_803A6BCC.mUnknown2C = 0;
    }
}

void fn_802699C8(void)
{
    fn_80269990(1, 0xFFFF);
}

int fn_802699F4(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    return fn_8026EEB0(handle, value);
}

int fn_80269A3C(int handle, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    return fn_8026F2C8(handle, value);
}

int fn_80269B58(int handle, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    return fn_8026EAC0(handle, 0, clamped >> 8);
}

int fn_80269B9C(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    return fn_8026ED74(handle, value);
}

int fn_80269BE4(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    return fn_8026ECCC(handle, value);
}

int fn_80269C2C(int handle, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    return fn_8026EF38(handle, clamped >> 8);
}

void fn_80269C6C(void)
{
}

int fn_80269CE8(int value, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (lbl_803A6C04[i] == value)
            return 1;
    }
    return 0;
}

int fn_8026A288(int handle)
{
    int index;
    Voice_803A6C24 *v;

    if (handle < 0)
        return -8;
    index = handle & 0xFF;
    if (index >= lbl_803A6C24.mUnknown16C)
        return -8;
    v = lbl_803A6C24.mUnknown1CC + index;
    if (v->mUnknown6D != 0 && v->mUnknown0 == handle)
        return index;
    return -8;
}

void fn_8026A40C(Object_8026A40C *p, int value)
{
    Message_8026A40C message;
    int i;

    while (p->mUnknown17 > 0) {
        p->mUnknown17--;
        message.mUnknown0 = value;
        message.mUnknown8 = p->mUnknown44[p->mUnknown17];
        message.mUnknown4 = p->mUnknown34[p->mUnknown17];
        for (i = 0; i < lbl_803A6C24.mUnknown16E; i++)
            lbl_803A6C24.mUnknown1A4[i](&message);
    }
}
