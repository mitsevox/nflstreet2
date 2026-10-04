#include "game/cu_8007F12C.h"
#include "game/Callees_801D57E0.h"
#include "game/cu_8018422C.h"
#include "game/Callees_8002A138.h"
#include "game/fn_8007F828.h"
#include "game/Record_80021154.h"

extern "C" {
unsigned int fn_801D6724(void);
unsigned int fn_801D6730(void);
void fn_801D6754(int a);
void fn_801D689C(const char *pSuffix, const char *pPrefix, int unused, int selector, char *pOut, int size);
int fn_801D6AC8(int a);
int fn_801D6B14(int a);
unsigned int fn_801D85A8(int a);
int fn_801D4400(int *pA, int *pB);
void fn_801D46E8(int slot);
char *fn_801C2EF0(char *pDst, const char *pSrc, int size);
int fn_801F7ABC(void);
void fn_801F8838(void);
void fn_80032220(void);
void fn_80032240(short a);
void fn_80032250(short a, char *pBuf);
unsigned int fn_80029838(int a);
int fn_80029B48(int a);
void fn_80029E6C(int a, int b);
void fn_8002A238(int a, int b, int slot, int index);
void fn_8002A260(int a, int b, char *pBuf, int size);
void fn_8002A44C(int a, int b);
void fn_8002A49C(int a);
void fn_8002A5C4(void);
void fn_8002A5F0(int a, char *pBuf, int b);
int fn_8002A824(void);
void fn_80187FD0(void);
void fn_80187FDC(void);
void fn_80191948(int a, int b, int c, int d);
}

static void (*lbl_803EB590)(int, int *) = 0;
static void (*lbl_803EB594)() = 0;
static int (*lbl_803EB598)(int *, int *, int *, int *) = 0;
static void (*lbl_803EB59C)(int, int) = 0;
static int (*lbl_803EB5A0)(int, int) = 0;
static unsigned char lbl_803EB5A4 = 0;
static unsigned char lbl_803EB5A5 = 0;
static int lbl_803EB5A8 = 0;
static unsigned char lbl_803EB5AC = 0;
static int lbl_803ECB80;

extern "C" {

int fn_8018422C(void)
{
    return 0;
}

void fn_80184234(int a, int *pB, int *pC)
{
    int unused;

    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    fn_80032220();
    if (lbl_803EB590 != 0) {
        lbl_803EB590(a, &unused);
    }
    *pB = fn_8002A824();
    *pC = 3;
}

void fn_801842AC(int a, int *pB)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
    if (lbl_803EB590 != 0) {
        lbl_803EB590(a, pB);
    }
}

void fn_8018430C(void)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    fn_801D6714(0);
}

void fn_80184340(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D6714(-1);
    if (lbl_803EB594 != 0) {
        lbl_803EB594();
    }
}

int fn_80184398(int *p0, int *p4, int *p8, int *p12)
{
    int result = 0;

    if (lbl_803EB598 != 0) {
        result = lbl_803EB598(p0, p4, p8, p12);
    }
    if (result != 0) {
        result = 1;
    } else {
        if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
            fn_801D6680(fn_801D671C());
        }
        result = 0;
    }
    return result;
}

int fn_80184408(int a, int count)
{
    int i;

    for (i = 0; i < fn_801D6B14(a); i++) {
        if (fn_801D6B74((signed char)i, a, 0, 0, 0, 0, 0) != 0) {
            count--;
        }
        if (count < 0) {
            break;
        }
    }
    return i;
}

int fn_80184488(unsigned int slot)
{
    if (slot <= 1 && slot != fn_801D671C()) {
        fn_801D6714(slot);
        fn_801D6650(8);
        return 1;
    }
    return 0;
}

int fn_801844E0(int a)
{
    if (a != 0) {
        if (fn_801D671C() != 0) {
            return 0;
        }
        fn_801D6714(1);
    }
    fn_801D6650(8);
    return 1;
}

void fn_80184528(int a, int b, int c, int d)
{
    fn_80191948(a, b, c, d);
}

void fn_80184548(void)
{
    int a = 0;
    int b = 0;

    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D4400(&a, &b);
}

int fn_8018459C(void)
{
    int a = 0;
    int b = 0;
    int result = fn_801D4400(&a, &b);
    int slot = fn_801D671C();

    if (result != 0) {
        result = ((a | b) >> slot) & 1;
    }
    return result;
}

void fn_80184600(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
}

void fn_8018463C(void)
{
    fn_801D6650(2);
}

void fn_80184660(void)
{
    int a;
    int b;

    fn_801D4400(&a, &b);
    fn_801D6650(9);
}

void fn_80184690(void)
{
    fn_801D6650(11);
}

void fn_801846B4(int a, int index)
{
    char other[32];
    char name[32];

    fn_801D6754(a);
    fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    fn_801D6C70((signed char)index, a, other, 32);
    fn_801D67E4(name, other);
    fn_801D6838(index);
    fn_801D6650(6);
}

int fn_8018473C(int a)
{
    fn_801D6754(a);
    return fn_801D6AC8(a);
}

void fn_80184770(void)
{
    fn_801D685C("GN7E-69", 0);
    fn_801D6650(7);
}

int fn_801847A4(int a, int index)
{
    char other[32];
    char name[32];

    fn_801D6754(a);
    if (fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0) != 0) {
        fn_801D6C70((signed char)index, a, other, 32);
        fn_801D67E4(name, other);
        fn_801D6838(index);
        if (lbl_803EB59C != 0) {
            lbl_803EB59C(a, index);
        }
        fn_8002A5C4();
        return 1;
    }
    return 0;
}

int fn_80184858(int a, int index)
{
    char other[32];
    char name[32];
    int result = 0;

    fn_801D6754(a);
    fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    fn_801D6C70((signed char)index, a, other, 32);
    fn_801D67E4(0, other);
    fn_801D6838(index);
    if (lbl_803EB5A0 != 0) {
        result = lbl_803EB5A0(a, index);
    }
    return result;
}

int fn_801848FC(int a)
{
    return fn_80029B48(a);
}

int fn_8018491C(int a, int index)
{
    char name[17];
    int result = fn_801D6DA8(index, a);

    if (result != 0) {
        fn_801D6B74((signed char)index, a, name, 17, 0, 0, 0);
        fn_801D67E4(name, 0);
    }
    return result;
}

void fn_8018498C(void)
{
    fn_801D6650(12);
}

void fn_801849B0(void)
{
    fn_801D6650(13);
}

void fn_801849D4(int a)
{
    if (a <= 5) {
        char name[8];

        fn_80032250(a, name);
        fn_801D685C(name, 1);
        fn_801D6650(10);
    }
}

void fn_80184A24(void)
{
    fn_801D46E8(fn_801D671C());
    fn_801D685C("GN7E-69", 0);
}

void fn_80184A58(void)
{
    fn_801D6650(14);
}

int fn_80184A7C(int a)
{
    if (a <= 5) {
        return a;
    }
    return -1;
}

void fn_80184A90(int a, int b)
{
    if (b > 0) {
        fn_80032240(a);
    }
}

void fn_80184ABC(void)
{
    fn_80187FD0();
    fn_80187FDC();
}

void fn_80184AE0(void)
{
    fn_801F8838();
}

int fn_80184B00(int a, const char *pName)
{
    unsigned char flag;

    return fn_801D6CF4(pName, a, &flag) == -1;
}

int fn_80184B3C(int a, int index, int b)
{
    char path[32];
    char name[32];
    int ok = 0;
    unsigned char flag = 0;

    fn_8002A44C(a, b);
    fn_8002A260(a, b, path, 32);
    if (a == 1) {
        ok = fn_801D6CF4("Options", 1, &flag) >= 0;
    } else if (fn_8002A138(a, b) != 0) {
        ok = fn_801D6CF4(path, a, &flag) >= 0;
    } else if (fn_801D6B74((signed char)index, a, 0, 0, 0, -1, &flag) == 0 || flag != 0) {
        fn_8002A5F0(a, path, 0);
    }
    fn_801D689C(path, "GN7E-69", (signed char)index, a, name, 32);
    fn_801D67E4(path, name);
    fn_801D6838(index);
    fn_8002A49C(ok);
    return 1;
}

int fn_80184C78(int a, int index, int b)
{
    char name[32];
    char other[32];
    int result;

    fn_8002A44C(a, b);
    result = fn_801D6B74((signed char)index, a, name, 32, 0, -1, 0);
    if (result != 0) {
        fn_801D6C70((signed char)index, a, other, 32);
        fn_801D67E4(name, other);
        fn_801D6838(index);
        fn_8002A49C(result);
    }
    return result;
}

void fn_80184D10(void)
{
    if (fn_801D671C() >= 0 && fn_801D671C() <= 1) {
        fn_801D6680(fn_801D671C());
    }
    fn_801D6714(-1);
    if (lbl_803EB594 != 0) {
        lbl_803EB594();
    }
}

int fn_80184D68(int a, int b, int *pError)
{
    int ok = 1;
    int index = 0;
    int i;

    if (fn_801D6730() < fn_801D85A8(a)) {
        *pError = 0x73;
        ok = 0;
    }
    if (fn_801D6724() < fn_80029838(a)) {
        *pError = 0x40;
        ok = 0;
    }
    if (ok) {
        for (i = 0; i < fn_801D6B14(a); i++) {
            if (fn_801D6B74((signed char)i, a, 0, 0, 0, 0, 0) == 0) {
                break;
            }
        }
        if (i < fn_801D6B14(a)) {
            index = i;
        } else {
            *pError = 0x13;
            ok = 0;
        }
        if (ok) {
            fn_8002A238(a, b, fn_801D671C(), index);
        }
    }
    return ok;
}

void fn_80184E7C(int a, int b)
{
    if (fn_8007F828(12) == 1) {
        fn_8007F6F8(12, 0);
        fn_80029E6C(a, b);
    }
}

void fn_80184ED0(Record_80021154 *pRecord)
{
    char name[32];

    fn_801D6B24(name, 32);
    fn_801C2EF0(pRecord->mUnknown8, name, pRecord->mUnknown4);
}

void fn_80184F14(int slot)
{
    fn_801D6714(slot);
    fn_801D6650(8);
}

int fn_80184F3C(int slot, int step, int *pSlot)
{
    unsigned int next = slot + step;

    if (step != 0 && next > 1) {
        next = step < 0;
    }
    *pSlot = next;
    return 1;
}

void fn_80184F60(int a, int slot)
{
    fn_801D65B4(0);
    fn_801D654C(1);
    lbl_803EB5A8 = a;
    if (a == 0) {
        lbl_803EB5AC = 1;
    }
    fn_801D6714(slot);
}

void fn_80184FB8(int a, int *pB, int c, int d, int e)
{
    fn_801D6754(c);
    if (e != 0) {
        fn_80184F60(d, 0);
    } else {
        fn_80184F60(d, fn_801D671C());
    }
    if (lbl_803EB590 != 0) {
        lbl_803EB590(a, pB);
    }
}

int fn_80185038(int *pSlot)
{
    int slot;

    if (lbl_803EB5AC) {
        fn_801D6650(8);
        lbl_803EB5AC = 0;
        *pSlot = fn_801D671C();
    } else if (fn_80184F3C(fn_801D671C(), lbl_803EB5A8, &slot) != 0) {
        fn_801D6714(slot);
        fn_801D6650(8);
        *pSlot = slot;
        return 1;
    } else {
        return 0;
    }
    return 1;
}

void fn_801850CC(int a, Record_80021154 *pRecord)
{
    fn_801D57E0(a, pRecord->mUnknown8, pRecord->mUnknown4);
}

void fn_801850F4(int a, int b, int *pOut)
{
    int result = fn_8002A190(a, b);

    if (result == -1) {
        result = 0;
    }
    *pOut = result;
}

int fn_80185130(void)
{
    return fn_801D671C();
}

void fn_80185150(int slot)
{
    fn_801D6714(slot);
}

void fn_80185170(int a, int b)
{
    char name[24];

    fn_8002A260(a, b, name, 32);
    fn_801D67E4(name, 0);
}

void fn_801851A4(Callbacks_802F462C *pCallbacks)
{
    lbl_803EB590 = pCallbacks->mUnknown0;
    lbl_803EB594 = pCallbacks->mUnknown4;
    lbl_803EB598 = pCallbacks->mUnknown8;
    lbl_803EB59C = pCallbacks->mUnknown12;
    lbl_803EB5A0 = pCallbacks->mUnknown16;
}

void fn_801851D0()
{
    lbl_803EB590 = 0;
    lbl_803EB594 = 0;
    lbl_803EB598 = 0;
    lbl_803EB59C = 0;
    lbl_803EB5A0 = 0;
}

int fn_801851EC(void)
{
    return fn_801F7ABC() == lbl_803ECB80;
}

void fn_8018521C(int enable)
{
    if (enable != 0) {
        if (!lbl_803EB5A5) {
            lbl_803ECB80 = fn_801F7ABC();
        }
        lbl_803EB5A5 = 1;
    } else {
        lbl_803EB5A5 = 0;
    }
}
}
