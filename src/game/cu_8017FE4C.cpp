#include "game/Object_8007A334.h"

/* Filled by fn_80152940 for one index; the constructor leaves mUnknown8 unset. */
struct Info_80152940 {
    Info_80152940() : mUnknown0(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

/* Object returned by fn_80148A58; its vtable pointer is at offset 0x18. */
class Class_80148A58 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04();
    virtual void vfn_05();
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_08();
    virtual void vfn_09();
    virtual void vfn_10();
    virtual void vfn_11();
    virtual void vfn_12();
    virtual int vfn_13();

private:
    char mUnknown0[24];
};

extern "C" {
unsigned int fn_8017F584(void);
int fn_8022F4BC(void);
int fn_80186B38(int a);
int fn_8018F2F4(int a, int b);
int fn_8007F828(int a);
int fn_8001194C(int a);
int fn_801869F0(void);
int fn_80186D64(int a);
void fn_80186F9C(int a, int b, int c);
int fn_80027DF0(void);
int fn_801486A0(void);
Class_80148A58 *fn_80148A58(void);
void fn_80152940(Class_80148A58 *pObject, int index, Info_80152940 *pInfo);
int fn_800B65A0(int a);
int fn_80178AE0(void);
void fn_801E1BE8(void);
void fn_8007AEE8(Object_8007A334 *pObject);
void fn_8007AF14(Object_8007A334 *pObject);
int fn_8007AF34(Object_8007A334 *pObject);
int fn_8007AF5C(Object_8007A334 *pObject);
int fn_801C6458(int a, int b);
int fn_801E195C(int a);
int fn_800B81A4(void);
}

static int lbl_803EB530 = 0;
static int lbl_803EB534 = -1;
static int lbl_803EB538 = -1;
static int lbl_803EB53C = -1;

extern "C" {
void fn_8017FE4C(int a, int b, int c)
{
    lbl_803EB530 = a;
    lbl_803EB534 = b;
    lbl_803EB538 = c;
    if (a == 0 && b == 0x69 && fn_8017F584() == 8) {
        fn_8018F2F4(fn_80186B38(fn_8022F4BC()), 0x3FF);
    }
}

int fn_8017FEA0(void)
{
    int value = fn_8007F828(6);

    return value == 1 || value == 2;
}

int fn_8017FED4(int a, int *pResult)
{
    int value = -1;

    if (a != -1) {
        value = fn_8001194C(a == 0);
    }
    *pResult = fn_801869F0();
    bool found = false;
    if (*pResult == 2) {
        *pResult = fn_80186D64(value);
        found = true;
    }
    return found;
}

void fn_8017FF40(int a)
{
    lbl_803EB53C = a;
}

int fn_8017FF48(int a, int b)
{
    int state;

    if (a == -1) {
        a = 1;
    }
    state = fn_801869F0();
    fn_80186F9C(state, b, a);
    return state;
}

int fn_8017FF98(void)
{
    int result = 0;

    if (fn_80027DF0() == 0) {
        Info_80152940 info;

        switch (fn_801486A0()) {
        case 0:
            result = 1;
            break;
        case 1:
            for (unsigned int i = 0; i <= 3; i++) {
                fn_80152940(fn_80148A58(), i, &info);
                if (info.mUnknown20 == 0xFF) {
                    result = 1;
                    break;
                }
            }
            break;
        default: {
            unsigned char first = fn_800B65A0(0) != 0xFF;
            unsigned char second = fn_800B65A0(1) != 0xFF;

            result = first ^ second;
            break;
        }
        }
    }
    return result;
}

int fn_80180070(void)
{
    if (fn_801486A0() != 15) {
        return fn_80148A58()->vfn_13();
    }
    return fn_800B65A0(fn_80178AE0()) != 0xFF;
}

int fn_801800D0(void)
{
    int result = -1;

    if (fn_80027DF0() != 0) {
        Object_8007A334 cursor;
        int searching = 1;

        fn_801E1BE8();
        fn_8007AEE8(&cursor);
        for (int found = fn_8007A444(&cursor); found && searching; found = fn_8007A510(&cursor)) {
            result = fn_8007AF34(&cursor);
            fn_8007AF5C(&cursor);
            searching = fn_801E195C(fn_801C6458(result, 0)) == 2;
        }
        fn_8007AF14(&cursor);
        if (searching) {
            result = -1;
        }
    } else {
        int value = fn_800B81A4();

        if (value != 0xFF) {
            result = value;
        }
    }
    return result;
}

int fn_801801B4(void)
{
    return lbl_803EB530;
}

int fn_801801BC(void)
{
    return lbl_803EB538;
}

void fn_801801C4(void)
{
}

void fn_801801C8(int a)
{
    lbl_803EB530 = a;
}

int fn_801801D0(void)
{
    int value = lbl_803EB53C;

    lbl_803EB53C = -1;
    return value;
}
}
