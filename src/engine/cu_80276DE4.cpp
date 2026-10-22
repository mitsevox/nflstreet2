#include <string.h>

#include "engine/cu_802714A8.h"

typedef struct Object_80277404 {
    Node_80279D90 mNode;
    unsigned char mUnknown1C[0x10];
    int m2C;
    int m30;
    int m34;
    int m38;
    int m3C;
    float m40[510];
    float m838[1020];
    float *m1828;
    int m182C;
    unsigned char mUnknown1830[4];
} Object_80277404;

typedef struct Struct_80278894 {
    unsigned char mUnknown0[8];
    int m8;
    unsigned char mUnknownC[4];
    int m10;
} Struct_80278894;

typedef struct Parser_8027823C {
    unsigned char *m0;
    int m4;
    int m8;
    unsigned char *mC;
    unsigned int m10;
} Parser_8027823C;

typedef struct Link_80278714 Link_80278714;

struct Link_80278714 {
    Link_80278714 *m0;
    Link_80278714 *m4;
};

typedef struct List_80278714 {
    Link_80278714 *m0;
    Link_80278714 *m4;
    int m8;
} List_80278714;

typedef struct Stream_803B5364 {
    unsigned char mUnknown0[0x42];
    signed char m42;
    unsigned char mUnknown43[5];
    int m48;
    int m4C;
    unsigned char mUnknown50[8];
    void (*m58)(int index, int value, void *context);
} Stream_803B5364;

typedef struct Event_803B5064 {
    unsigned short m0;
    unsigned short m2;
    int m4;
} Event_803B5064;

typedef struct Struct_803B5060 {
    int m0;
    Event_803B5064 m4[96];
    Stream_803B5364 *m304[32];
} Struct_803B5060;

typedef struct Struct_803B53EC {
    unsigned short m0;
    unsigned short m2;
    unsigned int m4;
    unsigned int m8;
    void *mC;
} Struct_803B53EC;

typedef struct State_8027A248 {
    unsigned char mUnknown0[0x3C];
} State_8027A248;

typedef struct Struct_80279C38 {
    Node_80279D90 mNode;
    State_8027A248 m1C;
} Struct_80279C38;

typedef struct Struct_8027A4C0 {
    Node_80279D90 mNode;
    int m1C;
} Struct_8027A4C0;

typedef struct Format_8027D284 {
    int m0;
    int m4;
    int m8;
} Format_8027D284;

typedef struct Pair_8027BFDC {
    float m0;
    float m4;
} Pair_8027BFDC;

typedef struct Block_8027BC18 {
    unsigned char mUnknown0[4];
    float m4;
    float m8;
    char *mC;
    unsigned char mUnknown10[4];
} Block_8027BC18;

typedef struct Struct_8027BE24 {
    unsigned char mUnknown0[8];
    int m8;
    int mC;
    unsigned char mUnknown10[0x84];
    Block_8027BC18 m94;
} Struct_8027BE24;

typedef struct Bits_8027C078 {
    unsigned char *m0;
    unsigned int m4;
    int m8;
} Bits_8027C078;

typedef struct Decoder_8027A9FC {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    int m28;
} Decoder_8027A9FC;

typedef struct Decoder_8027AB00 {
    Node_80279D90 mNode;
    int m1C;
    unsigned int m20;
    unsigned int m24;
    unsigned int m28;
    int m2C;
} Decoder_8027AB00;

typedef struct Decoder_8027AC08 {
    Node_80279D90 mNode;
    unsigned int m1C;
    unsigned int m20;
    int m24;
    void *m28;
} Decoder_8027AC08;

typedef struct Decoder_8027AE04 {
    Node_80279D90 mNode;
    void *m1C;
    int m20;
    int m24;
    int m28;
    void *m2C;
} Decoder_8027AE04;

typedef struct Decoder_8027B168 {
    Node_80279D90 mNode;
    unsigned char *m1C;
    int m20;
    int m24;
    int m28;
    unsigned short m2C;
    unsigned char mUnknown2E[2];
    int m30;
    void *m34;
    unsigned char m38;
} Decoder_8027B168;

typedef struct Decoder_8027B328 {
    Node_80279D90 mNode;
    unsigned char *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    unsigned char m30;
    unsigned char m31;
} Decoder_8027B328;

typedef struct Decoder_8027B464 {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
    char *m20;
    int m24;
    int m28;
} Decoder_8027B464;

typedef struct Decoder_8027B7B0 {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    int m30;
    int m34;
    int m38;
    int m3C;
    int m40;
    int m44;
    int m48;
} Decoder_8027B7B0;

typedef struct Decoder_8027BA6C {
    Node_80279D90 mNode;
    Struct_8027BE24 *m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    int m30;
    int m34;
    unsigned char m38;
} Decoder_8027BA6C;

extern "C" {

extern Struct_803B5060 lbl_803B5060;
extern Struct_803B53EC lbl_803B53EC;
extern int (*lbl_80301000)(void *dst, void *src, int size);
extern unsigned char lbl_80300EDC[];
extern unsigned int lbl_80301428[];
extern int lbl_803A772C;

int fn_8026A288(int handle);
void *fn_8026B5D4(int size);
void fn_8026B7D8(void *p);
int fn_8026C910(int handle, int *index);
unsigned int fn_8026CB14(void);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
void fn_80276B7C(float *a, float *b, float *c, int count, int n);
int fn_802789E0(int handle);
void fn_80277EC4(int index);
void *fn_8027BD68(int size);
void fn_8027BD94(void *p);
Struct_8027BE24 *fn_8027BDC0(void *memory);
int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count);
int fn_8027BE24(Struct_8027BE24 *p, float **dst, int count);
void *fn_8027C020(int size);
void fn_8027C04C(void *p);
void *fn_8027CF9C(void *memory);
int fn_8027CFCC(void *handle, void *data, int size, int count);
int fn_8027D05C(void *handle, float **dst, int count);
void fn_8027D284(Format_8027D284 *format, void *handle);
void fn_8027D2C4(void *handle, Format_8027D284 *format, int flags);
void fn_8027D2E0(void *handle, int mode);
void fn_8027A21C(State_8027A248 *state);
void fn_8027A248(State_8027A248 *state, int count, float *in, float *out);
int fn_8027B4F4(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B888(Node_80279D90 *node, int count, float *a, float *b, int flag);
int fn_8027B1F8(Node_80279D90 *node, int count, float *a, float *b, int flag);

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

void fn_80278700(List_80278714 *list)
{
    list->m0 = 0;
    list->m4 = 0;
    list->m8 = 0;
}

void fn_80278714(List_80278714 *list, Link_80278714 *link)
{
    link->m0 = list->m0;
    link->m4 = 0;
    if (list->m0 != 0) {
        list->m0->m4 = link;
    } else {
        list->m4 = link;
    }
    list->m0 = link;
    list->m8++;
}

void fn_80278750(List_80278714 *list, Link_80278714 *link)
{
    link->m0 = 0;
    link->m4 = list->m4;
    if (list->m4 != 0) {
        list->m4->m0 = link;
    } else {
        list->m0 = link;
    }
    list->m4 = link;
    list->m8++;
}

Link_80278714 *fn_8027878C(List_80278714 *list)
{
    Link_80278714 *link;

    link = list->m0;
    if (link != 0) {
        list->m0 = link->m0;
        if (list->m0 == 0) {
            list->m4 = 0;
        } else {
            list->m0->m4 = 0;
        }
        list->m8--;
    }
    return link;
}

void fn_802787CC(List_80278714 *list, Link_80278714 *link)
{
    if (link == list->m0) {
        list->m0 = link->m0;
    }
    if (link == list->m4) {
        list->m4 = link->m4;
    }
    if (link->m4 != 0) {
        link->m4->m0 = link->m0;
    }
    if (link->m0 != 0) {
        link->m0->m4 = link->m4;
    }
    list->m8--;
}

int fn_8027882C(int handle, int value)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (fn_8026C910(handle, &index)) {
            fn_80274D34(index, value);
        }
    }
    return handle;
}

int fn_80278894(void)
{
    Struct_80278894 *p;

    p = lbl_803A6C24.m1D4;
    return (p->m8 - p->m10) * 100 / p->m8;
}

int fn_80278ABC(int count)
{
    return count * 32 + 156;
}

int fn_80278AC8(int count)
{
    return fn_80278ABC(count) + fn_80274398();
}

int fn_802791D0(int index)
{
    Stream_803B5364 *stream;

    stream = lbl_803B5060.m304[index];
    return stream->m48 + stream->m4C;
}

int fn_802791F4(int index, int a, int b)
{
    return -15;
}

int fn_8027929C(int index)
{
    fn_8026D0AC();
    fn_8027474C(index);
    lbl_803B5060.m304[index] = 0;
    fn_8026D0EC();
    return 0;
}

void fn_8027952C(int index, int channel, int value)
{
    Stream_803B5364 *stream;
    Event_803B5064 *event;

    stream = lbl_803B5060.m304[index];
    if (channel == stream->m42) {
        stream->m4C -= value;
        if (stream->m58 != 0) {
            event = &lbl_803B5060.m4[lbl_803B5060.m0];
            event->m0 = 0;
            event->m2 = index;
            event->m4 = value;
            lbl_803B5060.m0++;
        }
    }
}

void fn_80279648(void **buffer, int *capacity, int size, int elementSize)
{
    int old;
    void *oldBuffer;
    void *newBuffer;

    old = *capacity;
    if (old < size) {
        if (old == 0) {
            *capacity = size;
        } else {
            while (*capacity < size) {
                *capacity += *capacity;
            }
        }
        oldBuffer = *buffer;
        newBuffer = fn_8026B5D4(*capacity * elementSize);
        if (oldBuffer != 0) {
            fn_8026B2E0(newBuffer, oldBuffer, old * elementSize);
            fn_8026B7D8(oldBuffer);
        }
        *buffer = newBuffer;
    }
}

int fn_80279798(int range)
{
    if (range > 0x10000) {
        range = 0x10000;
    } else if (range < 0) {
        range = 0;
    }
    return (((fn_8026CB14() & 0x7FFF) - 0x4000) * range) >> 14;
}

void fn_802797F4(void *(*alloc)(int size))
{
    lbl_803B53E4 = alloc;
}

void fn_80279800(void (*release)(void *p))
{
    lbl_803B53E8 = release;
}

int fn_8027980C(int (*copy)(void *dst, void *src, int size))
{
    lbl_80301000 = copy;
    return 0;
}

void fn_8027981C(int count)
{
    fn_8026D0AC();
    lbl_803B53EC.mC = fn_8026B5D4(count * 8);
    fn_8026D0EC();
    lbl_803B53EC.m0 = 0;
    lbl_803B53EC.m2 = count;
}

void fn_8027986C(unsigned int start, unsigned int length)
{
    lbl_803B53EC.m8 = (start + length) & ~4;
    if (start < 32) {
        start = 32;
    }
    lbl_803B53EC.m4 = start;
    if (start & 31) {
        lbl_803B53EC.m4 = (start + 31) & ~31;
    }
    lbl_803B53EC.m4 >>= 5;
    lbl_803B53EC.m8 >>= 5;
}

void fn_802798C0(void)
{
    if (lbl_803B53EC.mC != 0) {
        fn_8026D0AC();
        fn_8026B7D8(lbl_803B53EC.mC);
        fn_8026D0EC();
        lbl_803B53EC.mC = 0;
    }
}

int fn_80279BC0(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int i;
    int value;
    int clamped;

    for (i = 0; i < count; i++) {
        value = (int)a[i];
        if (value < -32767) {
            clamped = -32767;
        } else if (value > 32767) {
            clamped = 32767;
        } else {
            clamped = value;
        }
        ((int *)b)[i] = clamped;
    }
    return count;
}

void fn_80279C20(Node_80279D90 *node)
{
    node->m0 = fn_80279BC0;
    node->m4 = 0;
}

int fn_80279C38(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    int n;

    if (node->m8 != 0) {
        n = node->m8->m0(node->m8, count, b, a, node->m1A);
        if (n <= 0) {
            return n;
        }
    } else {
        n = count;
    }
    fn_8027A248(&((Struct_80279C38 *)node)->m1C, n, a, b);
    return n;
}

int fn_80279CB8(Node_80279D90 *node)
{
    node->m8 = 0;
    node->mC = 0;
    node->m10 = 0;
    node->m14 = 0;
    node->m1B = 0;
    node->m4 = 0;
    node->m0 = fn_80279C38;
    fn_8027A21C(&((Struct_80279C38 *)node)->m1C);
    return 0;
}

void fn_80279D90(Node_80279D90 **list, Node_80279D90 *node)
{
    Node_80279D90 *prev;
    Node_80279D90 *cur;

    prev = 0;
    cur = *list;
    while (cur != 0 && cur->m18 < node->m18) {
        prev = cur;
        cur = cur->m8;
    }
    node->m8 = cur;
    if (cur != 0) {
        cur->m10 = node;
    }
    if (prev == 0) {
        *list = node;
    } else {
        prev->m8 = node;
        node->m10 = prev;
    }
}

void fn_8027A4C0(Node_80279D90 *node, int value)
{
    ((Struct_8027A4C0 *)node)->m1C = value;
}

void fn_8027A9FC(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AB00(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AC08(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027AE04(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B168(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B328(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B464(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027B7B0(Node_80279D90 *node, Params_80275F80 *params);
void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params);

void fn_8027A7FC(void)
{
    lbl_803B4E34.m18[0][0] = fn_8027A9FC;
    lbl_803B4E34.m60[0][0] = 44;
    lbl_803B4E34.m18[0][1] = fn_8027AB00;
    lbl_803B4E34.m60[0][1] = 48;
    lbl_803B4E34.m18[0][2] = fn_8027B328;
    lbl_803B4E34.m60[0][2] = 52;
}

void fn_8027A844(void)
{
    lbl_803B4E34.m18[2][0] = fn_8027AC08;
    lbl_803B4E34.m60[2][0] = 44;
    lbl_803B4E34.m18[2][2] = fn_8027B168;
    lbl_803B4E34.m60[2][2] = 60;
    lbl_803B4E34.m18[2][1] = fn_8027AE04;
    lbl_803B4E34.m60[2][1] = 48;
    lbl_803B4E34.m18[3][0] = fn_8027AC08;
    lbl_803B4E34.m60[3][0] = 44;
    lbl_803B4E34.m18[3][2] = fn_8027B168;
    lbl_803B4E34.m60[3][2] = 60;
    lbl_803B4E34.m18[3][1] = fn_8027AE04;
    lbl_803B4E34.m60[3][1] = 48;
}

void fn_8027A8A4(void)
{
    lbl_803B4E34.m18[1][0] = fn_8027B464;
    lbl_803B4E34.m60[1][0] = 44;
    lbl_803B4E34.m60[1][1] = 84;
    lbl_803B4E34.m18[1][1] = fn_8027B7B0;
    lbl_803B4E34.m18[1][2] = fn_8027BA6C;
    lbl_803B4E34.m60[1][2] = 60;
}

void fn_8027A8EC(int count, float *src, float *dst, float gain)
{
    int i;

    for (i = 0; i < count; i++) {
        dst[i] = src[i] * gain + dst[i];
    }
}

int fn_8027A91C(Node_80279D90 *node)
{
    return ((Decoder_8027A9FC *)node)->m20;
}

int fn_8027A924(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027A9FC *decoder;
    unsigned int pos;
    int n;

    decoder = (Decoder_8027A9FC *)node;
    pos = decoder->m20;
    if (pos >= decoder->m24) {
        return -1;
    }
    decoder->m20 = pos + count;
    if (decoder->m20 < decoder->m24) {
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(count, (short *)(decoder->m1C + (pos << 1)), b);
        }
    } else {
        n = decoder->m24 - pos;
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (pos << 1)), b);
        }
        memset(b + n, 0, (count - n) * 4);
    }
    return 1;
}

void fn_8027A9FC(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027A9FC *decoder;

    decoder = (Decoder_8027A9FC *)node;
    node->m0 = fn_8027A924;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = params->m18;
    params->m28 = fn_8027A91C;
    node->m4 = 0;
}

int fn_8027AA3C(Node_80279D90 *node)
{
    return ((Decoder_8027AB00 *)node)->m20;
}

int fn_8027AA44(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AB00 *decoder;
    int n;

    decoder = (Decoder_8027AB00 *)node;
    while (count > 0) {
        n = decoder->m28 - decoder->m20 + 1;
        if (count < n) {
            n = count;
        }
        if (decoder->m2C != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (decoder->m20 << 1)), b);
        }
        b += n;
        decoder->m20 += n;
        count -= n;
        if (decoder->m20 > decoder->m28) {
            decoder->m20 = decoder->m24;
        }
    }
    return 1;
}

void fn_8027AB00(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AB00 *decoder;

    decoder = (Decoder_8027AB00 *)node;
    node->m0 = fn_8027AA44;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m2C = params->m18;
    params->m28 = fn_8027AA3C;
}

int fn_8027AB44(Node_80279D90 *node)
{
    return ((Decoder_8027AC08 *)node)->m20;
}

int fn_8027AB4C(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AC08 *decoder;
    int n;

    decoder = (Decoder_8027AC08 *)node;
    if (decoder->m20 >= decoder->m1C) {
        return -1;
    }
    n = fn_8027D05C(decoder->m28, &b, count);
    decoder->m20 += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
    }
    return 1;
}

void fn_8027ABDC(Node_80279D90 *node)
{
    Decoder_8027AC08 *decoder;

    decoder = (Decoder_8027AC08 *)node;
    if (decoder->m28 != 0) {
        fn_8027C04C(decoder->m28);
    }
}

void fn_8027AC08(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AC08 *decoder;
    Format_8027D284 format;
    Format_8027D284 info;

    decoder = (Decoder_8027AC08 *)node;
    node->m0 = fn_8027AB4C;
    decoder->m1C = params->mC;
    decoder->m20 = 0;
    decoder->m24 = params->m24;
    params->m28 = fn_8027AB44;
    node->m4 = fn_8027ABDC;
    decoder->m28 = fn_8027CF9C(fn_8027C020(3432));
    fn_8027D284(&info, decoder->m28);
    format = info;
    format.m8 = 1;
    fn_8027D2C4(decoder->m28, &format, 0);
    if (decoder->m24 <= 2) {
        fn_8027D2E0(decoder->m28, 0);
    } else {
        fn_8027D2E0(decoder->m28, 1);
    }
    fn_8027CFCC(decoder->m28, (void *)params->m0, decoder->m1C * 4, decoder->m1C);
}

int fn_8027AD08(Node_80279D90 *node)
{
    return ((Decoder_8027AE04 *)node)->m20;
}

int fn_8027AD10(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027AE04 *decoder;
    Format_8027D284 format;
    int n;

    decoder = (Decoder_8027AE04 *)node;
    while (count > 0) {
        n = fn_8027D05C(decoder->m1C, &b, count);
        b += n;
        decoder->m20 += n;
        count -= n;
        if (n < count) {
            decoder->m20 = decoder->m24;
            format.m4 = 0;
            format.m0 = 0;
            format.m8 = 1;
            fn_8027D2C4(decoder->m1C, &format, 0);
            fn_8027CFCC(decoder->m1C, decoder->m2C, (decoder->m28 - decoder->m24 + 1) * 4,
                        decoder->m28 - decoder->m24 + 1);
        }
    }
    return 1;
}

void fn_8027ADD8(Node_80279D90 *node)
{
    Decoder_8027AE04 *decoder;

    decoder = (Decoder_8027AE04 *)node;
    if (decoder->m1C != 0) {
        fn_8027C04C(decoder->m1C);
    }
}

void fn_8027AE04(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027AE04 *decoder;
    Format_8027D284 format;
    Format_8027D284 info;

    decoder = (Decoder_8027AE04 *)node;
    node->m0 = fn_8027AD10;
    node->m4 = fn_8027ADD8;
    decoder->m2C = (void *)params->m4;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = fn_8027CF9C(fn_8027C020(3432));
    fn_8027D284(&info, decoder->m1C);
    format = info;
    format.m8 = 1;
    fn_8027D2C4(decoder->m1C, &format, 0);
    fn_8027CFCC(decoder->m1C, (void *)params->m0, decoder->m24 * 4, decoder->m24);
    params->m28 = fn_8027AD08;
}

int fn_8027AEE4(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027B168 *decoder;
    Format_8027D284 format;
    Format_8027D284 info;
    int last;
    int total;
    int n;

    decoder = (Decoder_8027B168 *)node;
    total = 0;
    if (decoder->m28 != 0) {
        fn_8027952C(decoder->m24, decoder->m38, decoder->m28);
        decoder->m28 = 0;
    }
    while (count > 0) {
        n = fn_8027D05C(decoder->m34, &b, count);
        decoder->m2C += n;
        b += n;
        decoder->m28 += n;
        total += n;
        if (n < count) {
            count -= n;
            decoder->m1C = fn_802792F0(decoder->m24, decoder->m38, &decoder->m20, &last);
            if (decoder->m1C != 0) {
                decoder->m2C = 0;
                if (decoder->m30 <= 2) {
                    if (last == 0) {
                        fn_8027D284(&info, decoder->m34);
                        format = info;
                        format.m8 = 1;
                        fn_8027D2C4(decoder->m34, &format, 0);
                    } else {
                        fn_8027D284(&info, decoder->m34);
                        format = info;
                        format.m8 = 0;
                        fn_8027D2C4(decoder->m34, &format, 0);
                    }
                    fn_8027D2E0(decoder->m34, 0);
                } else {
                    if (last == 0) {
                        fn_8027D284(&info, decoder->m34);
                        format = info;
                        format.m4 = 0;
                        format.m8 = 1;
                    } else {
                        fn_8027D284(&info, decoder->m34);
                        format = info;
                        format.m8 = 0;
                    }
                    fn_8027D2C4(decoder->m34, &format, 0);
                    fn_8027D2E0(decoder->m34, 1);
                }
                fn_8027CFCC(decoder->m34, decoder->m1C + 1, decoder->m20 * 4, decoder->m20);
            } else {
                if (count > 0 && decoder->m28 != 0) {
                    memset(b, 0, count * 4);
                }
                decoder->m20 = 0;
                count = 0;
            }
        } else {
            count -= n;
        }
    }
    return total;
}

void fn_8027B13C(Node_80279D90 *node)
{
    Decoder_8027B168 *decoder;

    decoder = (Decoder_8027B168 *)node;
    if (decoder->m34 != 0) {
        fn_8027C04C(decoder->m34);
    }
}

void fn_8027B168(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B168 *decoder;

    decoder = (Decoder_8027B168 *)node;
    node->m0 = fn_8027AEE4;
    decoder->m24 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m1C = 0;
    decoder->m2C = 0;
    decoder->m30 = params->m24;
    decoder->m20 = params->mC;
    node->m4 = fn_8027B13C;
    decoder->m34 = fn_8027CF9C(fn_8027C020(3432));
    decoder->m28 = 0;
}

void fn_8027B328(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B328 *decoder;

    decoder = (Decoder_8027B328 *)node;
    node->m0 = fn_8027B1F8;
    decoder->m28 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m31 = fn_80274334(params->m1C);
    decoder->m20 = -1;
    decoder->m1C = 0;
    decoder->m24 = 0;
    decoder->m30 = params->m18;
    decoder->m2C = 0;
}

int fn_8027B39C(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027B464 *decoder;
    int n;

    decoder = (Decoder_8027B464 *)node;
    if (decoder->m28 >= decoder->m24) {
        return -1;
    }
    n = fn_8027BE24(decoder->m1C, &b, count);
    decoder->m28 += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
        n += count;
    }
    return n;
}

int fn_8027B430(Node_80279D90 *node)
{
    return ((Decoder_8027B464 *)node)->m28;
}

void fn_8027B438(Node_80279D90 *node)
{
    Decoder_8027B464 *decoder;

    decoder = (Decoder_8027B464 *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027B464(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B464 *decoder;

    decoder = (Decoder_8027B464 *)node;
    node->m0 = fn_8027B39C;
    node->m4 = fn_8027B438;
    decoder->m20 = (char *)params->m0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = fn_8027B430;
    fn_8027BDE8(decoder->m1C, decoder->m20, decoder->m24 * 4, decoder->m24);
}

int fn_8027B77C(Node_80279D90 *node)
{
    return ((Decoder_8027B7B0 *)node)->m20;
}

void fn_8027B784(Node_80279D90 *node)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027B7B0(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    node->m0 = fn_8027B4F4;
    node->m4 = fn_8027B784;
    decoder->m20 = 0;
    decoder->m2C = params->m4;
    decoder->m30 = params->m24;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = fn_8027B77C;
    if (decoder->m30 <= 2) {
        decoder->m34 = params->m0;
        decoder->m40 = 0;
        decoder->m38 = params->mC;
        decoder->m3C = 0;
        decoder->m44 = params->m10;
        decoder->m48 = params->m14;
    } else {
        fn_8027BDE8(decoder->m1C, (char *)params->m0, decoder->m24 * 4, decoder->m24);
    }
}

void fn_8027BA40(Node_80279D90 *node)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    node->m0 = fn_8027B888;
    node->m4 = fn_8027BA40;
    decoder->m30 = fn_802789E0(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m2C = params->m24;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m34 = 0;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
}

void *fn_8027BD68(int size)
{
    return lbl_803B53E4(size);
}

void fn_8027BD94(void *p)
{
    lbl_803B53E8(p);
}

int fn_8027BDE8(Struct_8027BE24 *p, char *data, int size, int count)
{
    if (data == 0) {
        return -1;
    }
    if (p->m8 != 0) {
        return -1;
    }
    p->m8 = count;
    p->mC = size;
    p->m94.mC = data;
    return 0;
}

Pair_8027BFDC fn_8027BFDC(Struct_8027BE24 *p)
{
    Pair_8027BFDC pair;

    pair.m0 = p->m94.m4;
    pair.m4 = p->m94.m8;
    return pair;
}

void fn_8027C00C(Struct_8027BE24 *p, Pair_8027BFDC *pair)
{
    p->m94.m4 = pair->m0;
    p->m94.m8 = pair->m4;
}

void *fn_8027C020(int size)
{
    return lbl_803B53E4(size);
}

void fn_8027C04C(void *p)
{
    lbl_803B53E8(p);
}

unsigned int fn_8027C078(Bits_8027C078 *bits, int count)
{
    unsigned int value;

    value = bits->m4 & lbl_80301428[count];
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
    return value;
}

void fn_8027C0D8(Bits_8027C078 *bits, int count)
{
    bits->m4 >>= count;
    bits->m8 -= count;
    if (bits->m8 <= 7) {
        bits->m4 |= *bits->m0++ << bits->m8;
        bits->m8 += 8;
    }
}

}
