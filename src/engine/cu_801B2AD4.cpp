#include "engine/cu_801B8C18.h"

struct Data_801B4548 {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Record_801B58F0 {
    unsigned char mUnknown0[4];
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC[20];
    int mUnknown20;
};

class Class_801B44BC {
public:
    virtual ~Class_801B44BC();
    virtual void fn_801B459C(Data_801B4548 *p);
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual void vfn_05(int value) = 0;
    virtual void vfn_06() = 0;
    virtual int vfn_07(void *p) = 0;
    virtual int vfn_08() = 0;
    virtual int vfn_09(int index) = 0;
    virtual void vfn_10() = 0;
    virtual void vfn_11() = 0;
    virtual int fn_801B45A4();
    virtual void vfn_13(int value) = 0;
    virtual int fn_801B45AC();
    virtual void vfn_15() = 0;
    virtual int fn_801B45B4(int value);
    virtual void vfn_17() = 0;
    virtual void vfn_18() = 0;
    virtual void vfn_19() = 0;
    virtual int fn_801B45BC();
    virtual int fn_801B45C4();
    virtual void vfn_22() = 0;
    virtual void fn_801B45CC();
    virtual void vfn_24() = 0;
    virtual void vfn_25() = 0;
    virtual int fn_801B4548();
    virtual int fn_801B4564();
    virtual Record_801B58F0 *fn_801B456C(int index);
    virtual int fn_801B4574();
    virtual int fn_801B457C();
    virtual int fn_801B4584();
    virtual int fn_801B458C();
    virtual int fn_801B4594(int index);

    int mUnknown0;
    unsigned char mUnknown4[4];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    unsigned char mUnknown14[12];
    int mUnknown20;
    unsigned char mUnknown24[56];
    Data_801B4548 *mUnknown5C;
    int mUnknown60;
    unsigned char mUnknown64[4];
};

extern "C" {
extern Allocator *lbl_803EBB68;
AllocParams lbl_8037E814;
extern void (*lbl_803EBB2C)(int, int);
extern void (*lbl_803EBB30)(int, int);
extern void (*lbl_803EBB34)(int, int);

}

struct Header_801B2CDC {
    unsigned char mUnknown0[15];
    unsigned char mUnknownF;
    unsigned char mUnknown10[2];
    unsigned short mUnknown12;
};

struct Node_801B3FE0 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    short mUnknown4;
    short mUnknown6;
    union {
        unsigned int word;
        struct { unsigned short high; unsigned char low[2]; } halves;
        struct { unsigned int mUnknown7:25, flag40:1, mUnknown1:5, flag1:1; } bits;
    } mUnknown8;
    unsigned char mUnknownC[4];
    unsigned int mUnknown10;
    int mUnknown14;
    signed char mUnknown18, mUnknown19, mUnknown1A;
    unsigned char mUnknown1B;
    unsigned int mUnknown1C;
    int mUnknown20;
    signed char mUnknown24, mUnknown25, mUnknown26;
    unsigned char mUnknown27;
    unsigned int mUnknown28;
    int mUnknown2C;
    signed char mUnknown30, mUnknown31, mUnknown32;
    unsigned char mUnknown33;
    unsigned int *mUnknown34;
    unsigned char mUnknown38[184];
    int mUnknownF0;
    unsigned char mUnknownF4[12];
    Class_801B44BC *mUnknown100;
    short mUnknown104;
    unsigned char mUnknown106[2];
    int mUnknown108;
    int mUnknown10C;
    int mUnknown110;
};

struct Record_801B6D20 {
    signed char mUnknown0;
    signed char mUnknown1;
    unsigned short mUnknown2;
};

struct Sequence_801B84E4;

struct Bank_801B3480 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned char mUnknownC[8];
    unsigned int mUnknown14;
    Header_801B2CDC *mUnknown18;
    short *mUnknown1C;
    unsigned char mUnknown20[4];
    short *mUnknown24;
    unsigned char mUnknown28[8];
    unsigned int *mUnknown30;
    int *mUnknown34;
    unsigned char mUnknown38[4];
    unsigned int *mUnknown3C;
    Node_801B3FE0 *mUnknown40[24];
    unsigned char mUnknownA0[32];
    Sequence_801B84E4 *mUnknownC0[17];
    unsigned char mUnknown104[4092];
    int mUnknown1100;
};

class Class_803EBB60 {
public:
    virtual ~Class_803EBB60();
    virtual void vfn_02() = 0;
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual unsigned int vfn_05() = 0;
    unsigned char mUnknown0[12];
};

extern "C" {
extern int lbl_803EBB24;
extern Bank_801B3480 *lbl_803EBB28;
extern unsigned char lbl_803EBB38;
extern unsigned char lbl_803EBB39;
extern unsigned char lbl_803EBB3B;
extern unsigned int lbl_803EBB3C;
extern int lbl_803EBB40;
extern int lbl_803EBB48;
extern int lbl_803EBB4C;
extern int lbl_803EBB50;
extern int lbl_803EBB54;
extern Bank_801B3480 *lbl_802F47D0[4];
extern Class_803EBB60 *lbl_803EBB60;
void fn_801B3724(void);

}struct Event_801B845C {
    unsigned char mUnknown0[4];
    union {
        unsigned int mUnknown4;
        struct { unsigned int mUnknown6:26, depth:3, mUnknown0:3; } mBits4;
    };
    unsigned char mUnknown8[4];
};
struct Sequence_801B84E4 {
    unsigned int mUnknown0;
    unsigned char mUnknown4[4];
    unsigned int mUnknown8;
    unsigned char mUnknownC[3];
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11[3];
    Event_801B845C mUnknown14[1];
};
struct Info_801E1084;
struct Entry_801B63F0 {
    unsigned char mUnknown0[4];
    unsigned int mUnknown4;
    unsigned char mUnknown8[4];
    unsigned int mUnknownC;
    union {
        unsigned int word;
        struct { unsigned int mUnknownF:17, flag4000:1, mUnknown0:14; } bits;
    } mUnknown10;
};
struct Record_801B6780 {
    short mUnknown0;
};
struct Data_801E0DF0;
extern "C" {
int fn_801B3FE0(int flags, Data_801E0DF0 *data);

}

extern "C" int fn_801B7880(Sequence_801B84E4 *p, Event_801B845C *entry);

extern "C" unsigned int lbl_802F481C[6];

class Class_803EBB64 {
public:
    virtual ~Class_803EBB64();
};
extern "C" Class_803EBB64 *lbl_803EBB64;
extern "C" int fn_801B2F28(int flags);
extern "C" void fn_8026D0AC(void);
extern "C" void fn_8026D0EC(void);

extern "C" int fn_801B2AD4(void);
extern "C" int fn_801B2B58(void);
extern "C" void *fn_801B2C40(int size);
extern "C" void fn_801B2C94(void *p);
extern "C" void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int));
extern "C" int fn_801B3234(int flags);
extern "C" unsigned int fn_801B343C(void);
extern "C" unsigned int fn_801B3480(unsigned int index, unsigned int flags);
extern "C" int fn_801B34DC(unsigned int flags);
extern "C" int fn_801B3568(void);
extern "C" void fn_801B39B8(int mode);
extern "C" void fn_801B3A88(void);
extern "C" void fn_801B3AAC(void);
extern "C" int fn_801B3AD0(int flags, Data_801E0DF0 *data, int value);
extern "C" int fn_801B3D28(int flags, Data_801E0DF0 *data, int value);
extern "C" int fn_801B3F6C(int flags, Data_801E0DF0 *data);
extern "C" Node_801B3FE0 *fn_801B4174(unsigned int flags);
extern "C" void fn_801B421C(void);
extern "C" int fn_801B42C0(unsigned int flags);
extern "C" void fn_801B4334(Node_801B3FE0 *p, int state);
extern "C" int fn_801B43CC(int state);
extern "C" void fn_801B4824(Node_801B3FE0 *p, int value);
extern "C" void fn_801B4960(Node_801B3FE0 *p, int a, int b, int c);
extern "C" void fn_801B49C4(Node_801B3FE0 *p, int a, int b, int c);
extern "C" int fn_801B57C0(Node_801B3FE0 *p, int index);
extern "C" int fn_801B58F0(Node_801B3FE0 *p);
extern "C" int fn_801B59B0(int flags, int value);
extern "C" void fn_801B5AB0(int flags, unsigned char value);
extern "C" int fn_801B5BCC(int flags, Info_801E1084 *info);
extern "C" int fn_801B5C88(Node_801B3FE0 *p, void *info);
extern "C" void fn_801B5CD0(int flags);
extern "C" int fn_801B5DB4(Node_801B3FE0 *p);
extern "C" void fn_801B5E10(const char *format, ...);
extern "C" int fn_801B5E5C(int flags, Sequence_801B84E4 *sequence);
extern "C" void fn_801B6334(Sequence_801B84E4 *p);
extern "C" void fn_801B63F0(Entry_801B63F0 *p, int value);
extern "C" void fn_801B6460(void);
extern "C" int fn_801B64C0(int index);
extern "C" int fn_801B6780(int index);
extern "C" int fn_801B6CB4(Node_801B3FE0 *p);
extern "C" int fn_801B6D20(int count, int value, Record_801B6D20 *entries);
extern "C" int fn_801B7178(int index, int value);
extern "C" unsigned int fn_801B7778(void);
extern "C" Event_801B845C *fn_801B845C(Event_801B845C *p, int state, Event_801B845C *end);
extern "C" int fn_801B84E4(Event_801B845C *p, Sequence_801B84E4 *sequence);
extern "C" int fn_801B8580(Node_801B3FE0 *p);

extern "C" int fn_801B2AD4(void)
{
    if (++lbl_803EBB24 != 1) {
        --lbl_803EBB24;
        return -18;
    }
    for (int i = 3; i >= 0; --i)
        lbl_802F47D0[i] = 0;
    lbl_803EBB38 = 1;
    lbl_803EBB40 = 256;
    --lbl_803EBB24;
    lbl_803EBB48 = 0;
    lbl_803EBB28 = 0;
    lbl_803EBB54 = 0;
    lbl_803EBB39 = 0;
    lbl_803EBB50 = 0;
    lbl_803EBB4C = 0;
    return 0;
}

extern "C" int fn_801B2B58(void)
{
    if (!lbl_803EBB38)
        return -14;
    fn_801B2F28(0x0F000000);
    if (fn_801B42C0(0x0F000000) == 0) {
        fn_8026D0AC();
        delete lbl_803EBB64;
        delete lbl_803EBB60;
        fn_8026D0EC();
        lbl_803EBB60 = 0;
        lbl_803EBB68 = 0;
        lbl_803EBB64 = 0;
        lbl_803EBB38 = 0;
    }
    return lbl_803EBB38 == 0;
}

extern "C" void *fn_801B2C40(int size)
{
    void *result;
    if (lbl_803EBB68)
        result = lbl_803EBB68->Alloc(size, lbl_8037E814);
    else
        result = 0;
    return result;
}

extern "C" void fn_801B2C94(void *p)
{
    if (lbl_803EBB68)
        lbl_803EBB68->Free(p, 0);
}

extern "C" void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int))
{
    lbl_803EBB2C = a;
    lbl_803EBB30 = b;
    lbl_803EBB34 = c;
}

extern "C" int fn_801B3234(int flags)
{
    Node_801B3FE0 *p = fn_801B4174(flags);
    Class_801B44BC *result;
    if (p)
        result = p->mUnknown100;
    else
        result = 0;
    return (int)result;
}

extern "C" unsigned int fn_801B343C(void)
{
    unsigned int result = 0;
    if (lbl_803EBB60)
        result = lbl_803EBB60->vfn_05();
    return result;
}

extern "C" unsigned int fn_801B3480(unsigned int index, unsigned int flags)
{
    if (index <= 3 && lbl_802F47D0[index] && lbl_802F47D0[index]->mUnknown18) {
        unsigned int value = lbl_802F47D0[index]->mUnknown14;
        unsigned int mask = flags & 0xF0000000;
        if ((!mask || (value & mask)) && ((flags & 0x0F000000) & value)) {
            lbl_803EBB28 = lbl_802F47D0[index];
            return value;
        }
    }
    return 0;
}

extern "C" int fn_801B34DC(unsigned int flags)
{
    int i = 0;
    int hasMask = (flags & 0x0F000000) != 0;
    for (; i < 4; ++i) {
        unsigned int mask = 0;
        if (!hasMask)
            mask = 0x01000000 << i;
        if (fn_801B3480(i, flags | mask))
            return 1;
    }
    return 0;
}

extern "C" int fn_801B3568(void)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (lbl_802F47D0[i]) {
            for (int j = i + 1; j < 4; ++j) {
                if (lbl_802F47D0[j] && lbl_802F47D0[i]->mUnknown14 > lbl_802F47D0[j]->mUnknown14) {
                    Bank_801B3480 temp = *lbl_802F47D0[i];
                    *lbl_802F47D0[i] = *lbl_802F47D0[j];
                    *lbl_802F47D0[j] = temp;
                }
            }
        }
    }
    return i;
}

extern "C" void fn_801B39B8(int mode)
{
    if (!lbl_803EBB39) {
        int acquired;
        if (++lbl_803EBB24 == 1 && lbl_803EBB38)
            acquired = 1;
        else {
            --lbl_803EBB24;
            acquired = 0;
        }
        if (acquired) {
            lbl_803EBB3B = mode;
            lbl_803EBB3C = fn_801B343C();
            fn_801B43CC(0);
            for (unsigned char i = 0; i < 4; ++i) {
                if (fn_801B3480(i, 0xFFFFFFFF)) {
                    fn_801B421C();
                    fn_801B3724();
                }
            }
            fn_801B43CC(1);
            lbl_803EBB28 = 0;
            --lbl_803EBB24;
        }
    }
}

extern "C" void fn_801B3A88(void)
{ fn_801B39B8(32); }

extern "C" void fn_801B3AAC(void)
{ fn_801B39B8(66); }

extern "C" int fn_801B3AD0(int flags, Data_801E0DF0 *data, int value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = fn_801B3F6C(flags, data);
    if (result >= 0) {
        Node_801B3FE0 *p = fn_801B4174(flags);
        if (p)
            p->mUnknown8.halves.high = value;
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" int fn_801B3D28(int flags, Data_801E0DF0 *data, int value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = fn_801B3F6C(flags, data);
    if (result >= 0) {
        Node_801B3FE0 *p = fn_801B4174(flags);
        p->mUnknown104 = value;
        p->mUnknown8.word |= 0x10;
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" int fn_801B3F6C(int flags, Data_801E0DF0 *data)
{
    if (!fn_801B34DC(flags))
        return -8;
    int result = fn_801B3FE0(flags, data);
    if (result < 0)
        return result;
    Node_801B3FE0 *p = fn_801B4174(flags);
    lbl_803EBB28->mUnknown40[p->mUnknown0] = p;
    return 0;
}

extern "C" Node_801B3FE0 *fn_801B4174(unsigned int flags)
{
    unsigned int bits = flags & 0x00FFFFFF;
    unsigned int high = flags & 0xF0000000;
    flags &= 0x0F000000;
    for (unsigned int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i] && (lbl_802F47D0[i]->mUnknown14 & high) &&
            (lbl_802F47D0[i]->mUnknown14 & flags)) {
            for (int j = 0; j < 24; ++j) {
                if ((bits >> j) & 1)
                    return lbl_802F47D0[i]->mUnknown40[j];
            }
        }
    }
    return 0;
}

extern "C" void fn_801B421C(void)
{
    lbl_803EBB28->mUnknown0 = -1;
    lbl_803EBB28->mUnknown4 = 0;
    lbl_803EBB28->mUnknown8 = 0;
    for (int i = 0; i < 24; ++i) {
        Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[i];
        if (p && !(p->mUnknown8.word & 0x40)) {
            int active = 0;
            if (p->mUnknown4 >= 0 && p->mUnknown34)
                active = 1;
            if (active && lbl_803EBB28->mUnknown4 < (p->mUnknown8.halves.high)) {
                lbl_803EBB28->mUnknown4 = p->mUnknown8.halves.high;
                lbl_803EBB28->mUnknown0 = i;
                lbl_803EBB28->mUnknown8 = (*p->mUnknown34 >> 5) & 63;
            }
        }
    }
}

extern "C" int fn_801B42C0(unsigned int flags)
{
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if ((flags & (0x01000000 << i)) && lbl_802F47D0[i]) {
            for (int j = 0; j < 24; ++j) {
                if (lbl_802F47D0[i]->mUnknown40[j])
                    ++count;
            }
        }
    }
    return count;
}

extern "C" void fn_801B4334(Node_801B3FE0 *p, int state)
{
    unsigned int id = p->mUnknown0;
    int found = state > 0;
    p->mUnknown8.bits.flag1 = state != 0;
    for (int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i]) {
            Node_801B3FE0 *other = lbl_802F47D0[i]->mUnknown40[id];
            if (other && other != p) {
                other->mUnknown8.bits.flag1 = !found;
                found = 1;
            }
        }
    }
    if (!found)
        p->mUnknown8.bits.flag1 = 1;
}

extern "C" int fn_801B43CC(int state)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (lbl_802F47D0[i] && fn_801B3480(i, 0xFFFFFFFF)) {
            for (int j = 0; j < 24; ++j) {
                Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                if (p && !(p->mUnknown8.word & 0x40) && p->mUnknown100) {
                    if (state)
                        p->mUnknown100->vfn_03();
                    else
                        p->mUnknown100->vfn_06();
                }
            }
        }
    }
    return i;
}

int Class_801B44BC::fn_801B4548()
{
    Data_801B4548 *p = mUnknown5C;
    int result;
    if (p)
        result = p->mUnknown4;
    else
        result = 0;
    return result;
}

int Class_801B44BC::fn_801B4564()
{ return mUnknown60; }

Record_801B58F0 *Class_801B44BC::fn_801B456C(int index)
{ return 0; }

int Class_801B44BC::fn_801B4574()
{ return 0; }

int Class_801B44BC::fn_801B457C()
{ return -8; }

int Class_801B44BC::fn_801B4584()
{ return -8; }

int Class_801B44BC::fn_801B458C()
{ return -8; }

int Class_801B44BC::fn_801B4594(int index)
{ return -8; }

void Class_801B44BC::fn_801B459C(Data_801B4548 *p)
{ mUnknown5C = p; }

int Class_801B44BC::fn_801B45A4()
{ return mUnknown10; }

int Class_801B44BC::fn_801B45AC()
{ return mUnknownC; }

int Class_801B44BC::fn_801B45B4(int value)
{ return mUnknown8; }

int Class_801B44BC::fn_801B45BC()
{ return mUnknown0; }

int Class_801B44BC::fn_801B45C4()
{ return mUnknown20; }

void Class_801B44BC::fn_801B45CC()
{}

extern "C" void fn_801B4824(Node_801B3FE0 *p, int value)
{
    p->mUnknown3 = value;
    if (p->mUnknown1A & 0x80)
        p->mUnknown100->vfn_13((signed char)value * (signed char)p->mUnknown2 / 100);
}

extern "C" void fn_801B4960(Node_801B3FE0 *p, int a, int b, int c)
{
    p->mUnknown1C = lbl_803EBB3C;
    p->mUnknown20 = b;
    p->mUnknown25 = c;
    p->mUnknown24 = p->mUnknown100->fn_801B45B4(0);
    p->mUnknown26 = a;
}

extern "C" void fn_801B49C4(Node_801B3FE0 *p, int a, int b, int c)
{
    p->mUnknown28 = lbl_803EBB3C;
    p->mUnknown2C = b;
    p->mUnknown31 = c;
    p->mUnknown30 = p->mUnknown100->fn_801B45AC();
    p->mUnknown32 = a;
}

extern "C" int fn_801B57C0(Node_801B3FE0 *p, int index)
{
    if (index < 0 || index >= p->mUnknown100->fn_801B4548())
        return -8;
    Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(index);
    if (!entry)
        return -8;
    Record_801B58F0 saved = *entry;
    fn_801B5DB4(p);
    int result = p->mUnknown100->fn_801B4594(index);
    p->mUnknown108 -= saved.mUnknown4;
    p->mUnknown10C -= saved.mUnknown8;
    return result;
}

extern "C" int fn_801B58F0(Node_801B3FE0 *p)
{
    int best = 0x07FFFFFF;
    int index = -1;
    for (int i = 0; i < p->mUnknown100->fn_801B4564(); ++i) {
        Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(i);
        if (entry && entry->mUnknown20 >= 0 && entry->mUnknown20 < best) {
            best = entry->mUnknown20;
            index = i;
        }
    }
    if (index == -1)
        return 0;
    return fn_801B57C0(p, index);
}

extern "C" int fn_801B59B0(int flags, int value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    if ((unsigned int)value <= 127) {
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    if (p && ((((unsigned int)flags >> j) & 1) == 1))
                        p->mUnknown1 = value;
                }
            }
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return 0;
}

extern "C" void fn_801B5AB0(int flags, unsigned char value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (acquired) {
        if (flags == -1)
            lbl_803EBB39 = value;
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    if (p && ((((unsigned int)flags >> j) & 1) == 1)) {
                        p->mUnknown100->vfn_05(value);
                        p->mUnknown8.bits.flag40 = value;
                    }
                }
            }
        }
        lbl_803EBB28 = 0;
        --lbl_803EBB24;
    }
}

extern "C" int fn_801B5BCC(int flags, Info_801E1084 *info)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = -8;
    {
        Node_801B3FE0 *p = fn_801B4174(flags);
        if (p && fn_801B34DC(flags))
            result = fn_801B5C88(p, info);
        lbl_803EBB28 = 0;
        --lbl_803EBB24;
    }
    return result;
}

extern "C" int fn_801B5C88(Node_801B3FE0 *p, void *info)
{
    int result;
    if (p->mUnknown100)
        result = p->mUnknown100->vfn_07(info);
    else
        result = -39;
    return result;
}

extern "C" void fn_801B5CD0(int flags)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (acquired) {
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480(i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    if (p && ((((unsigned int)flags >> j) & 1) == 1))
                        fn_801B5DB4(p);
                }
            }
        }
        lbl_803EBB28 = 0;
        --lbl_803EBB24;
    }
}

extern "C" int fn_801B5DB4(Node_801B3FE0 *p)
{
    p->mUnknown100->vfn_04();
    p->mUnknown4 = -1;
    p->mUnknown8.word |= 0xF80;
    return 0;
}

extern "C" void fn_801B5E10(const char *format, ...)
{}

extern "C" int fn_801B5E5C(int flags, Sequence_801B84E4 *sequence)
{
    int result = -8;
    Event_801B845C *entry = sequence->mUnknown14;
    int depth = 0;
    unsigned int high = flags & 0xFF000000;
    for (unsigned int i = 0; i < sequence->mUnknownF; ++i, ++entry) {
        if ((entry->mUnknown4 & 0x00FE0000) == 0x00020000) {
            switch ((entry->mUnknown4 >> 9) & 7) {
            case 0:
            case 1:
                entry->mBits4.depth = depth++;
                break;
            case 2:
            case 3:
                entry->mBits4.depth = depth - 1;
                break;
            case 4:
                entry->mBits4.depth = --depth;
                break;
            default:
                break;
            }
        } else {
            entry->mBits4.depth = depth;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i] && (lbl_802F47D0[i]->mUnknown14 & high) == lbl_802F47D0[i]->mUnknown14) {
            int count = lbl_802F47D0[i]->mUnknown1100;
            if (count > 15)
                return -13;
            result = 0;
            unsigned int now = lbl_803EBB60->vfn_05();
            sequence->mUnknown8 = now;
            sequence->mUnknown0 = now;
            lbl_802F47D0[i]->mUnknownC0[count++] = sequence;
            lbl_802F47D0[i]->mUnknown1100 = count;
        }
    }
    return result;
}

extern "C" void fn_801B6334(Sequence_801B84E4 *p)
{
    for (int i = 0; i < 4; ++i) {
        Bank_801B3480 *bank = lbl_802F47D0[i];
        if (bank) {
            for (int j = 0; j <= 16; ++j) {
                if (bank->mUnknownC0[j] == p) {
                    bank->mUnknownC0[j] = 0;
                    --bank->mUnknown1100;
                    for (++j; j < 16; ++j)
                        bank->mUnknownC0[j - 1] = bank->mUnknownC0[j];
                }
            }
        }
    }
}

extern "C" void fn_801B63F0(Entry_801B63F0 *p, int value)
{
    Header_801B2CDC *base = lbl_803EBB28->mUnknown18;
    unsigned int key = p->mUnknownC >> 8;
    short *offsets = lbl_803EBB28->mUnknown24;
    Entry_801B63F0 *found = 0;
    for (int i = base->mUnknownF - 1; i >= 0; --i) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)base + offsets[i] * 4);
        if ((entry->mUnknownC >> 8) == key) {
            found = entry;
            break;
        }
    }
    if (found)
        found->mUnknown10.bits.flag4000 = value;
}

extern "C" void fn_801B6460(void)
{
    for (int i = 0; i < lbl_803EBB28->mUnknown18->mUnknownF; ++i) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown24[i] * 4);
        if (entry)
            entry->mUnknown10.bits.flag4000 = 0;
    }
}

extern "C" int fn_801B64C0(int index)
{
    Sequence_801B84E4 *p = lbl_803EBB28->mUnknownC0[index];
    int count = 0;
    if (p->mUnknown8 > lbl_803EBB3C)
        return 0;
    unsigned int i = p->mUnknown10;
    Event_801B845C *entry = &p->mUnknown14[i];
    for (; i < p->mUnknownF; ++i, ++entry) {
        if (!(entry->mUnknown4 & 0x10000) && !fn_801B7880(p, entry))
            break;
        ++count;
        ++p->mUnknown10;
        p->mUnknown8 = lbl_803EBB3C;
    }
    return count;
}

extern "C" int fn_801B6780(int index)
{
    if (index < 0 || index >= lbl_803EBB28->mUnknown18->mUnknown12)
        return 0;
    Record_801B6780 *p = (Record_801B6780 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    int result = 0;
    int value = p->mUnknown0;
    if (value > 0)
        result = lbl_803EBB28->mUnknown3C[(value - 1) * 2];
    return result;
}

extern "C" int fn_801B6CB4(Node_801B3FE0 *p)
{
    int sum = 0;
    for (int i = 0; ; ++i) {
        int value = p->mUnknown100->vfn_09(i);
        if (value < 0)
            break;
        sum += value;
    }
    return sum;
}

extern "C" int fn_801B6D20(int count, int value, Record_801B6D20 *entries)
{
    if (count <= 0)
        return -1;
    int best = 127;
    Record_801B6D20 *found = entries;
    for (int i = 0; i < count; ++i) {
        int a = entries[i].mUnknown0 - value;
        int b = entries[i].mUnknown1 - value;
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (b > a) b = a;
        if (best > b) {
            best = b;
            found = &entries[i];
        }
    }
    return found->mUnknown2;
}

extern "C" int fn_801B7178(int index, int value)
{
    if (index < 0)
        return value;
    Entry_801B63F0 *p = 0;
    if (index <= lbl_803EBB28->mUnknown18->mUnknown12)
        p = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    int key = (p->mUnknown4 >> 20) & 255;
    if (key) {
        unsigned int end = lbl_803EBB28->mUnknown30[key];
        unsigned int start = lbl_803EBB28->mUnknown30[key - 1];
        int count = end - start;
        int *words = (int *)lbl_803EBB28->mUnknown18 + start;
        for (int i = 0; i < count; ++i) {
            int word = words[i];
            if (value == word >> 16)
                value = word & 0xFFFF;
        }
    }
    return value;
}

extern "C" unsigned int fn_801B7778(void)
{
    unsigned int sum = lbl_802F481C[5] + lbl_802F481C[4];
    unsigned int carry = 0;
    if (sum < lbl_802F481C[5] || sum < lbl_802F481C[4])
        carry = 1;
    unsigned int a = lbl_802F481C[3];
    unsigned int b = lbl_802F481C[2];
    unsigned int c = lbl_802F481C[1];
    unsigned int e = lbl_802F481C[0];
    lbl_802F481C[4] = sum;
    sum = sum + a + carry;
    lbl_802F481C[3] = sum;
    carry = sum < a;
    sum = sum + b + carry;
    lbl_802F481C[2] = sum;
    carry = sum < b;
    sum = sum + c + carry;
    lbl_802F481C[1] = sum;
    carry = sum < c;
    sum = sum + e + carry;
    lbl_802F481C[0] = sum;
    if (++lbl_802F481C[5]) return sum;
    if (++lbl_802F481C[4]) return sum;
    if (++lbl_802F481C[3]) return sum;
    if (++lbl_802F481C[2]) return sum;
    if (++lbl_802F481C[1]) return sum;
    return ++lbl_802F481C[0];
}

extern "C" Event_801B845C *fn_801B845C(Event_801B845C *p, int state, Event_801B845C *end)
{
    unsigned int value = (p->mUnknown4 >> 3) & 7;
    ++p;
    while (p <= end && state >= 0) {
        if (((p->mUnknown4 >> 3) & 7) == value) {
            if ((p->mUnknown4 & 0x00FE0E00) == 0x00020800) {
                p->mUnknown4 |= 0x10000;
                return p;
            }
            if (!state)
                return p;
            state = 0;
        }
        if (!state)
            p->mUnknown4 |= 0x10000;
        ++p;
    }
    return p;
}

extern "C" int fn_801B84E4(Event_801B845C *p, Sequence_801B84E4 *sequence)
{
    unsigned int value = (p->mUnknown4 >> 3) & 7;
    Event_801B845C *end = p;
    Event_801B845C *start = sequence->mUnknown14;
    Event_801B845C *found = 0;
    while (--p >= start) {
        if (((p->mUnknown4 >> 3) & 7) == value &&
            (p->mUnknown4 & 0x00FE0E00) == 0x00020000) {
            found = p;
            break;
        }
    }
    if (!found)
        return 0;
    sequence->mUnknown10 = found - start;
    for (; p <= end; ++p)
        p->mUnknown4 &= ~0x10000U;
    return 1;
}

extern "C" int fn_801B8580(Node_801B3FE0 *p)
{
    if (!p)
        return 0;
    p->mUnknown110 = 1;
    if (p->mUnknown8.word & 0x40)
        p->mUnknown110 = 3;
    else if (p->mUnknown4 >= 0) {
        p->mUnknown110 = 5;
        int value = 0;
        if (p->mUnknownF0 < 0)
            value = p->mUnknown100->vfn_08();
        if (value && fn_801B6CB4(p) <= (p->mUnknown8.halves.high))
            p->mUnknown110 = 4;
        if (p->mUnknown1A == -1)
            p->mUnknown110 = 6;
    }
    return p->mUnknown110;
}
