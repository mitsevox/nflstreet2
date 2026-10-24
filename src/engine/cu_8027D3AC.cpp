#include <string.h>
#include "engine/system.h"

typedef struct Record_8027D9FC {
    int m0;
    int m4;
    int m8;
    int mC;
} Record_8027D9FC;

typedef struct Record_8027EC7C {
    unsigned int mWords[32];
} Record_8027EC7C;

typedef struct Record_8027E2D0 {
    unsigned char mUnknown0[0xC];
    int mC;
    unsigned char mUnknown10[4];
    int m14;
    int m18;
    void *m1C;
    unsigned char mUnknown20[4];
} Record_8027E2D0;

struct Class_801B44BC {
    int m0;
    unsigned char mUnknown4[4];
    int m8;
    int mC;
    int m10;
    unsigned char mUnknown14[8];
    int m1C;
    unsigned char mUnknown20[0x18];
    int m38;
    unsigned char mUnknown3C[0x18];
    int m54;
    int m58;
    unsigned char mUnknown5C[8];
    Record_8027E2D0 *m64;
    virtual ~Class_801B44BC();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual int vfn_04();
    virtual int vfn_05(int flag);
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_08();
    virtual int vfn_09(int index);
    virtual void vfn_10();
    virtual void vfn_11();
    virtual int vfn_12();
    virtual int vfn_13(int value);
    virtual void vfn_14();
    virtual int vfn_15(int value);
    virtual void vfn_16();
    virtual int vfn_17(int a, int b);
    virtual void vfn_18();
    virtual int vfn_19(int value);
    virtual void vfn_20();
    virtual void vfn_21();
    virtual void vfn_22();
    virtual void vfn_23(Record_8027EC7C *record);
    virtual void vfn_24();
    virtual int vfn_25(int value);
    virtual void vfn_26();
    virtual int vfn_27();
    virtual Record_8027E2D0 *vfn_28(int key);
    virtual Record_8027E2D0 *vfn_29();
    virtual int vfn_30(int key, void *data);
    virtual int vfn_31(int key);
    virtual int vfn_32(int key, int mode);
    virtual int vfn_33(int key);
    virtual int vfn_34(int value, int a);
    virtual int vfn_35();
};

struct Object_8027D6E8 : Class_801B44BC {
    virtual ~Object_8027D6E8();
    Record_8027D9FC m6C;
    Record_8027EC7C m7C;
    unsigned char mFC;
    unsigned char mUnknownFD[3];
    unsigned char m100;
    unsigned char m101;
    unsigned char mUnknown102[6];
    unsigned short m108;
    unsigned char mUnknown10A[0xA];
    int m114;
    virtual int vfn_13(int value);
    virtual int vfn_05(int flag);
};

struct Object_8027DAE4 : Object_8027D6E8 {
    virtual ~Object_8027DAE4();
    unsigned char mUnknown118[0xC];
    int m124;
    virtual int vfn_13(int value);
    virtual int vfn_15(int value);
    virtual int vfn_17(int a, int b);
    virtual int vfn_19(int value);
    virtual int vfn_04(void);
    virtual int vfn_30(int key, void *data);
    virtual int vfn_31(int key);
    virtual Record_8027E2D0 *vfn_28(int key);
    virtual Record_8027E2D0 *vfn_29(void);
    virtual int vfn_33(int key);
    virtual int vfn_32(int key, int mode);
};

typedef struct Record_8027EAC0 {
    unsigned char mUnknown0[4];
    int m4;
    int m8;
    unsigned char mUnknownC[8];
} Record_8027EAC0;

struct Object_8027E518 : Object_8027D6E8 {
    virtual ~Object_8027E518();
    int m118;
    int m11C;
    Record_8027EAC0 *m120;
    int m124;
    int m128;
    virtual int vfn_34(int value, int a);
    virtual int vfn_35(void);
    virtual int vfn_15(int value);
    virtual int vfn_17(int a, int b);
    virtual int vfn_25(int value);
    virtual int vfn_19(int value);
    virtual int vfn_09(int index);
    virtual int vfn_04(void);
    virtual void vfn_23(Record_8027EC7C *record);
};

/* Partial layout of the object whose members 0x8027EF94-0x8027EFA4 store
   their argument; size unknown. */
typedef struct Object_8027EF94 {
    virtual ~Object_8027EF94();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04();
    int m0;
    int m4;
    int m8;
    virtual int vfn_05(void);
    virtual int vfn_06(int value);
} Object_8027EF94;

extern "C" {

void *fn_801B2C40(int size);
void fn_801B3A88(void);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
int fn_8026EEB0(int handle, int value);
int fn_8026EF38(int handle, int value);
int fn_8026EAC0(int handle, int a, int b);
int fn_8026ED1C(int handle, int value);
int fn_801F685C(int count, int filters, int taps);
int fn_802714A8(int handle, int value);
int fn_8026AEAC(int handle, int value);
int fn_80278070(int handle, int a, int b);
int fn_8026C9BC(int handle, int value);
int fn_8026A870(int *handle, void *data);
int fn_8026A96C(void);
int fn_8026AB88(int handle);
int fn_8026A9F4(int handle);
int fn_8026A980(void *dest, int handle);
int fn_8026EDC4(int handle);
int fn_8026E388(int handle);
void fn_801B2C94(void *p);

void *fn_8027D5CC(int size)
{
    return fn_801B2C40(size);
}

void fn_8027D5EC(void *p)
{
    fn_801B2C94(p);
}

int fn_8027D960(Object_8027D6E8 *p)
{
    return p->m38;
}

int fn_8027D968(Object_8027D6E8 *p)
{
    return p->m54;
}

int fn_8027D970(Object_8027D6E8 *p)
{
    return p->m10;
}

}

int Object_8027D6E8::vfn_13(int value)
{
    int current;
    if ((unsigned int)value > 127) {
        return -8;
    }
    current = vfn_12();
    if (current == value || value < 0 || current < 0) {
        return -1;
    }
    return 0;
}

extern "C" {

int fn_8027D9EC(Object_8027D6E8 *p)
{
    return 0;
}

int fn_8027D9F4(Object_8027D6E8 *p)
{
    return 0;
}

void fn_8027D9FC(Object_8027D6E8 *p, Record_8027D9FC *record)
{
    p->m6C = *record;
}

}

int Object_8027D6E8::vfn_05(int flag)
{
    int arg = 0;
    int value = 0;
    if (m114 > 0) {
        value = m114;
    } else if (m108 != 0) {
        value = m108;
    }
    if (flag == 0) {
        arg = value = m114;
    }
    vfn_19(arg);
    m114 = value;
    return 0;
}

extern "C" {

void *fn_8027DAA4(int size)
{
    return fn_801B2C40(size);
}

void fn_8027DAC4(void *p)
{
    fn_801B2C94(p);
}

}

int Object_8027DAE4::vfn_13(int value)
{
    int status = Object_8027D6E8::vfn_13(value);
    int result = 0;
    if (status == 0) {
        fn_8026D0AC();
        result = fn_802714A8(m124, value);
        fn_8026D0EC();
        m10 = value;
        mFC = value;
    }
    return result;
}

int Object_8027DAE4::vfn_15(int value)
{
    int status = fn_8027D9EC(this);
    int result = 0;
    if (status == 0) {
        fn_8026D0AC();
        result = fn_8026AEAC(m124, value);
        fn_8026D0EC();
        mC = value;
        m100 = value;
    }
    return result;
}

int Object_8027DAE4::vfn_17(int a, int b)
{
    int status = fn_8027D9F4(this);
    int result = 0;
    if (status == 0) {
        fn_8026D0AC();
        result = fn_80278070(m124, a, b);
        fn_8026D0EC();
        m8 = b;
        m101 = b;
    }
    return result;
}

int Object_8027DAE4::vfn_19(int value)
{
    int result;
    fn_8026D0AC();
    result = fn_8026C9BC(m124, value);
    fn_8026D0EC();
    m114 = value;
    m108 = value;
    return result;
}

extern "C" {

int fn_8027E0AC(Object_8027DAE4 *p, int index)
{
    if (index == 0) {
        return p->m58;
    }
    return -1;
}

}

int Object_8027DAE4::vfn_04(void)
{
    int result;
    fn_8026D0AC();
    result = fn_8026EDC4(m0);
    fn_8026D0EC();
    m38 = 1;
    m124 = -1;
    m0 = -1;
    vfn_03();
    return result;
}

int Object_8027DAE4::vfn_30(int key, void *data)
{
    int result = -8;
    Record_8027E2D0 *record = vfn_28(key);
    if (record != 0) {
        result = fn_8026A870(&record->m18, data);
    }
    return result;
}

int Object_8027DAE4::vfn_31(int key)
{
    int result = 0;
    Record_8027E2D0 *record = vfn_28(key);
    if (record != 0) {
        result = fn_8026A96C();
    }
    return result;
}

Record_8027E2D0 *Object_8027DAE4::vfn_28(int key)
{
    int i;
    Record_8027E2D0 *record;
    for (i = 0; i < vfn_27(); i++) {
        record = &m64[i];
        if (record->mC == key) {
            return record;
        }
    }
    return 0;
}

Record_8027E2D0 *Object_8027DAE4::vfn_29(void)
{
    int i;
    Record_8027E2D0 *record;
    for (i = 0; i < vfn_27(); i++) {
        record = &m64[i];
        if (record->mC < 0) {
            return record;
        }
    }
    return 0;
}

int Object_8027DAE4::vfn_33(int key)
{
    int result = 0;
    Record_8027E2D0 *record = vfn_28(key);
    if (record != 0 && record->m18 != -1) {
        if (record->m14 == 0) {
            result = fn_8026AB88(record->m18);
            fn_801B2C94(record->m1C);
        }
        memset(record, 0, sizeof(*record));
        record->m18 = -1;
    }
    return result;
}

int Object_8027DAE4::vfn_32(int key, int mode)
{
    int result = -8;
    void *data;
    Record_8027E2D0 *record = vfn_28(key);
    if (record != 0 && record->m18 != -1 && mode == 7) {
        data = fn_801B2C40(fn_8026A9F4(record->m18));
        if (data != 0) {
            fn_8026A980(data, record->m18);
            result = 0;
            fn_801B2C94(record->m1C);
            record->m1C = data;
        }
    }
    return result;
}

extern "C" {

void *fn_8027E4D8(int size)
{
    return fn_801B2C40(size);
}

void fn_8027E4F8(void *p)
{
    fn_801B2C94(p);
}

}

int Object_8027E518::vfn_34(int value, int a)
{
    if (m0 >= 0) {
        return -18;
    }
    m0 = value;
    m1C = 1;
    m118 = a;
    return 0;
}

int Object_8027E518::vfn_35(void)
{
    int value = m0;
    if (value < 0) {
        return -18;
    }
    m0 = -1;
    m118 = 0;
    return value;
}

int Object_8027E518::vfn_15(int value)
{
    int result = 0;
    if (fn_8027D9EC(this) == 0) {
        fn_8026D0AC();
        result = fn_8026EF38(m0, value);
        fn_8026D0EC();
        mC = value;
    }
    return result;
}

int Object_8027E518::vfn_17(int a, int b)
{
    int result = 0;
    if (fn_8027D9F4(this) == 0) {
        fn_8026D0AC();
        result = fn_8026EAC0(m0, a, b);
        fn_8026D0EC();
        m8 = b;
    }
    return result;
}

int Object_8027E518::vfn_25(int value)
{
    return fn_8026ED1C(m120->m4, value);
}

int Object_8027E518::vfn_19(int value)
{
    int result;
    fn_8026D0AC();
    result = fn_8026EEB0(m0, value);
    fn_8026D0EC();
    m108 = value;
    m114 = value;
    return result;
}

extern "C" {

void fn_8027EAB4(Object_8027E518 *p, int a, int b)
{
    p->m124 = a;
    p->m128 = b;
}

}

int Object_8027E518::vfn_09(int index)
{
    Record_8027EAC0 *record;
    if (index < 0) {
        return m58;
    }
    if (index < m11C) {
        record = &m120[index];
        if (record->m4 >= 0) {
            return record->m8;
        }
    }
    return -8;
}

int Object_8027E518::vfn_04(void)
{
    int result;
    fn_8026D0AC();
    result = fn_8026E388(m0);
    fn_8026D0EC();
    m38 = 1;
    vfn_03();
    return result;
}

void Object_8027E518::vfn_23(Record_8027EC7C *record)
{
    m7C = *record;
}

extern "C" {

void fn_8027ED4C(Object_8027D6E8 *p)
{
    p->m1C = 1;
}

void fn_8027ED58(Object_8027D6E8 *p)
{
}

int fn_8027ED5C(Object_8027D6E8 *p)
{
    return -1;
}

int fn_8027ED64(Object_8027D6E8 *p)
{
    return p->m114;
}

void fn_8027EDC0(void)
{
    fn_801B3A88();
}

void *fn_8027EDE0(int size)
{
    return fn_801B2C40(size);
}

void fn_8027EE00(void *p)
{
    fn_801B2C94(p);
}

}

int Object_8027EF94::vfn_06(int value)
{
    return fn_801F685C(value, 0, 0) + 6144;
}

int Object_8027EF94::vfn_05(void)
{
    return ((int)fn_801F7ABC() * 50) / 3;
}

extern "C" {

int fn_8027EF50(Object_8027EF94 *p)
{
    return 0;
}

int fn_8027EF58(Object_8027EF94 *p)
{
    return 1;
}

void fn_8027EF94(Object_8027EF94 *p, int value)
{
    p->m0 = value;
}

void fn_8027EF9C(Object_8027EF94 *p, int value)
{
    p->m4 = value;
}

void fn_8027EFA4(Object_8027EF94 *p, int value)
{
    p->m8 = value;
}

}
