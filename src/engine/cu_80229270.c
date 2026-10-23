/* Partial source for the engine range 0x80229270-0x8022F428 (neutral file name). */

#include "engine/Funcs_802FB3BC.h"
#include "engine/llmemory.h"
#include "game/cu_801CF5BC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

typedef struct Handlers_802294D8 {
    int (*mpUnknown0)(void);
    void *mpUnknown4;
    void *mpUnknown8;
} Handlers_802294D8;

typedef struct Object_8022A59C {
    unsigned short mUnknown0;
    int mUnknown4;
} Object_8022A59C;

typedef struct Node_8022CC6C {
    char mUnknown0[2];
    unsigned char mUnknown2;
    char mUnknown3[5];
    unsigned short mUnknown8;
    char mUnknown10[2];
    struct Node_8022CC6C *mpUnknown12;
    struct Node_8022CC6C *mpUnknown16;
} Node_8022CC6C;

extern unsigned int fn_801CF6D4(void *pStream, unsigned int range);
extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
extern int fn_802303B4(int key, unsigned short *pId);
extern int fn_80230CC8(unsigned short id);
extern int fn_80229084(void);
extern int fn_8022908C(void);

extern char lbl_802B2138[];
extern char lbl_802B2178[];
extern char lbl_802B21B8[];
extern char lbl_802B21FC[];
extern char lbl_802B2268[];
extern char lbl_802B231C[];
extern char lbl_802B238C[];
extern char lbl_802B2F64[];
extern char lbl_802B3010[];
extern char lbl_802B30D0[];
extern char lbl_802B3180[];
extern char lbl_802B3524[];
extern char lbl_802B35D4[];
extern char lbl_802B35E4[];
extern char lbl_802B35F8[];
extern char lbl_802B45F0[];
extern char lbl_802B4650[];
extern char lbl_802B5080[];
extern char lbl_802B50A0[];
extern char lbl_802B50C0[];
extern char lbl_802B50E0[];
extern char lbl_802B5100[];
extern char lbl_802B5120[];
extern char lbl_802B519C[];
extern char lbl_802B51BC[];
extern int lbl_802FA600[];
extern unsigned short lbl_802FAA1C[];
extern char lbl_803A2390[];
extern char lbl_803A23E8[];
extern char lbl_803A2474[];
extern struct QueryCursor lbl_803A25E0;
extern int (*lbl_803EBFD8)(void);
extern void *lbl_803EBFDC;
extern void *lbl_803EBFE0;
extern void (*lbl_803EBFE4)(int);
extern int lbl_803EBFE8;
extern unsigned char lbl_803EBFEC;
extern unsigned char lbl_803EBFED;
extern Object_8022A59C *lbl_803EBFF0;
extern int (*lbl_803EBFF8)(void);
extern int (*lbl_803EBFFC)(void **ppData, void *p);
extern int (*lbl_803EC000)(int a, int b);
extern int (*lbl_803EC004)(void);
extern int (*lbl_803EC008)(void);
extern int lbl_803EC020;
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a);
extern unsigned char lbl_803EC030;
extern int (*lbl_803EC034)(int a);
extern int (*lbl_803EC038)(int a);
extern void *lbl_803EC040;
extern int lbl_803EC044;
extern int (*lbl_803EC048)(int a);
extern int (*lbl_803EC04C)(int a);
extern void *lbl_803EC050;
extern Node_8022CC6C *lbl_803EC054;
extern Node_8022CC6C *lbl_803EC058;
extern void *lbl_803EC05C;
extern unsigned short lbl_803EC060;
extern int lbl_803EC064;
extern int lbl_803EC068;
extern int lbl_803EC06C;
extern int lbl_803EC070;
extern int lbl_803EC074;
extern int lbl_803EC07C;
extern int lbl_803EC080;

int fn_80229674(void);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void fn_8022C894(void);
void fn_8022C8C4(void);
int fn_8022C8F0(unsigned int low, unsigned int high);
void *fn_8022C938(int size, int a);
void fn_8022C988(void *p);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022CADC(void);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
void fn_8022CDA0(void);
int fn_8022D14C(int a);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));

int fn_80229270(void)
{
    struct QueryCursor cursor;
    int a;
    int b;
    int c;
    unsigned char i;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = fn_801FCE10(0, lbl_802B2138, &cursor);
    i = 0;
    if (err == 0) {
        do {
            err = fn_801FCE10(0, lbl_802B2178, &cursor, &a, &b, &c);
            if (err != 0) {
                break;
            }
            if (c != i) {
                err = fn_801FCE10(0, lbl_802B21B8, i, a, b);
            }
            i++;
        } while (err == 0);
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = fn_801FCFA0(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return err;
}

int fn_802293A8(void)
{
    return 0;
}

void fn_802293B0(void)
{
}

int fn_802293B4(int a, int b)
{
    int err = fn_801FCE10(0, lbl_802B21FC, a, b, 255);

    if (err == 0) {
        err = fn_80229270();
    }
    return err;
}

int fn_802293FC(void)
{
    return fn_801FCE10(0, lbl_802B2268);
}

int fn_8022942C(void)
{
    return 0;
}

void fn_80229434(void)
{
}

int fn_80229438(int column, int value)
{
    return fn_801FCE10(0, lbl_802B231C, column, value);
}

int fn_80229470(void)
{
    fn_8022C894();
    return 0;
}

void fn_80229494(void)
{
    fn_8022C8C4();
    fn_80229674();
    lbl_803EBFD8 = 0;
    lbl_803EBFDC = 0;
    lbl_803EBFE0 = 0;
    lbl_803EBFE4 = 0;
    lbl_803EBFE8 = -1;
    lbl_803EBFEC = 0;
}

void fn_802294D8(Handlers_802294D8 *p)
{
    lbl_803EBFD8 = p->mpUnknown0;
    lbl_803EBFDC = p->mpUnknown4;
    lbl_803EBFE0 = p->mpUnknown8;
}

int fn_802294F4(void)
{
    return lbl_803EBFEC;
}

int fn_802294FC(int *p)
{
    int err = 0;

    if (lbl_803EBFEC == 0) {
        err = fn_801FCE10(0, lbl_802B238C, *p);
        if (err == 0) {
            lbl_803EBFEC = 1;
        }
    }
    return err;
}

int fn_80229554(void)
{
    int err = 0;

    if (lbl_803EBFEC == 1) {
        lbl_803EBFED = 1;
        err = lbl_803EBFD8();
        if (err == 0) {
            err = fn_80229674();
        } else {
            fn_80229674();
        }
        lbl_803EBFEC = 0;
        lbl_803EBFED = 0;
    }
    return err;
}

int fn_802295C0(void)
{
    if (lbl_803EBFE4 != 0) {
        lbl_803EBFE4(lbl_803EBFE8);
    }
    return 0;
}

int fn_802295F8(int a)
{
    int err = 0;

    if (lbl_803EBFF0 == 0) {
        err = fn_8022A59C(a, &lbl_803EBFF0);
        if (err != 0) {
            fn_80229674();
        }
    }
    return err;
}

int fn_80229644(int a, int b)
{
    return fn_8022AB6C(lbl_803EBFF0, a, b);
}

int fn_80229674(void)
{
    int err = 0;

    if (lbl_803EBFF0 != 0) {
        err = fn_8022AC80(lbl_803EBFF0);
        lbl_803EBFF0 = 0;
    }
    return err;
}

int fn_802296B4(int a, int b)
{
    int err = fn_802295F8(0);

    if (err == 0) {
        err = fn_80229644(a, b);
    }
    if (err == 0) {
        err = fn_80229674();
    } else {
        fn_80229674();
    }
    return err;
}

void fn_80229718(Funcs_802FB3BC *pFuncs)
{
    lbl_803EBFF8 = pFuncs->mpUnknown0;
    lbl_803EBFFC = pFuncs->mpUnknown4;
    lbl_803EC000 = pFuncs->mpUnknown8;
    lbl_803EC004 = pFuncs->mpUnknown12;
    lbl_803EC008 = pFuncs->mpUnknown16;
}

void fn_80229744(void)
{
    lbl_803EBFF8 = 0;
    lbl_803EBFFC = 0;
    lbl_803EC000 = 0;
    lbl_803EC004 = 0;
    lbl_803EC008 = 0;
}

int fn_80229760(void **ppData, void *p)
{
    return lbl_803EBFFC(ppData, p);
}

int fn_80229788(int a, int b)
{
    return lbl_803EC000(a, b);
}

int fn_802297B0(void)
{
    return lbl_803EC004();
}

int fn_80229E78(void)
{
    return 0;
}

int fn_80229E80(void)
{
    return 0;
}

int fn_8022A428(int a)
{
    return fn_801FCE10(0, lbl_802B2F64, a, 1023, 1023, 31, -1, 3, 15, 7, -1, 0);
}

int fn_8022A490(unsigned int count)
{
    int err = fn_801FCE10(0, lbl_802B3010);

    if (err == 0) {
        int id = 0;
        unsigned short i;

        for (i = 0; i < count; i++) {
            if ((err = fn_8022A428(id++)) != 0) {
                break;
            }
        }
    }
    return err;
}

int fn_8022A508(int a, int b, int c, int d, int e)
{
    return fn_801FCE10(0, lbl_802B30D0, b, c, d, e, a);
}

int fn_8022A558(int a, int b, int c, int d)
{
    return fn_801FCE10(0, lbl_802B3180, b, c, d, a);
}

int fn_8022A59C(int a, Object_8022A59C **ppOut)
{
    int err = fn_80229084();
    Object_8022A59C *p = fn_8022C938(8, 0);

    p->mUnknown4 = a;
    p->mUnknown0 = -1;
    if (err == 0) {
        err = fn_802303B4(0, &p->mUnknown0);
    }
    if (err == 0) {
        *ppOut = p;
    } else {
        fn_8022AC80(p);
        *ppOut = 0;
    }
    return err;
}

int fn_8022AB6C(Object_8022A59C *p, int a, int b)
{
    struct QueryCursor cursor;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = fn_801FCE10(0, lbl_802B3524, &cursor);
    if (err == 0) {
        err = fn_8022A624(p, cursor, a, b);
    }
    if (QUERY_STATUS_ACCEPTED(err) == 1) {
        if (cursor.mUnknown0 != 0) {
            err = fn_801FCFA0(&cursor);
        } else {
            err = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return err;
}

int fn_8022AC80(Object_8022A59C *p)
{
    int err = 0;

    if (p->mUnknown0 != 0xFFFF) {
        err = fn_80230CC8(p->mUnknown0);
    }
    if (err == 0) {
        err = fn_8022908C();
    } else {
        fn_8022908C();
    }
    fn_8022C988(p);
    return err;
}

int fn_8022BF60(void)
{
    return 0;
}

int fn_8022BF68(void)
{
    int err = 0;
    unsigned char i;

    for (i = 0; i <= 4; i++) {
        err = fn_801FCE10(0, lbl_802B35D4, lbl_802FA600[i]);
        if (err != 0) {
            break;
        }
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35D4, lbl_803EC020);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35E4);
    }
    if (err == 0) {
        err = fn_801FCE10(0, lbl_802B35F8);
    }
    return err;
}

int fn_8022C02C(int a, int b, int c, int d)
{
    int err = 0;

    if (c == 0) {
        err = fn_8022BF68();
    }
    if (err == 0 && lbl_803EC028 != 0) {
        err = lbl_803EC028(a, b, c, d);
    }
    return err;
}

int fn_8022C098(int a)
{
    int err = 0;

    if (lbl_803EC02C != 0) {
        err = lbl_803EC02C(a);
    }
    if (err == 0) {
        err = fn_8022BF60();
    }
    return err;
}

void fn_8022C3C8(void)
{
    fn_801D34D0(lbl_803A2390, 88, 0, 4);
    lbl_803EC030 = 0;
    lbl_803EC034 = 0;
    lbl_803EC038 = 0;
}

int fn_8022C81C(int a)
{
    if (lbl_803EC034 != 0) {
        return lbl_803EC034(a);
    }
    return 0;
}

int fn_8022C858(int a)
{
    if (lbl_803EC038 != 0) {
        return lbl_803EC038(a);
    }
    return 0;
}

void fn_8022C894(void)
{
    lbl_803EC040 = fn_801CF5BC(0, fn_801CF7AC());
}

void fn_8022C8C4(void)
{
    fn_801CF67C(lbl_803EC040);
    lbl_803EC040 = 0;
}

int fn_8022C8F0(unsigned int low, unsigned int high)
{
    if (low < high) {
        return low + fn_801CF6D4(lbl_803EC040, high - low);
    }
    return low;
}

void fn_8022C930(int a)
{
    lbl_803EC044 = a;
}

void *fn_8022C938(int size, int a)
{
    void *p;

    if (a != 0) {
        p = fn_801D2BB0(lbl_803EC044, size, 0, 0);
    } else {
        p = fn_801D2B7C(size, 0, 0);
    }
    return p;
}

void fn_8022C988(void *p)
{
    fn_801D2BD0(p);
}

void *fn_8022C9A8(void)
{
    return lbl_803A23E8;
}

void fn_8022C9B4(void *p)
{
}

void fn_8022CADC(void)
{
    lbl_803EC054 = 0;
    lbl_803EC058 = 0;
}

Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key)
{
    Node_8022CC6C *p;

    for (p = *ppHead; p != 0; p = p->mpUnknown16) {
        if (p->mUnknown2 == key) {
            return p;
        }
    }
    return 0;
}

Node_8022CC6C *fn_8022CC98(Node_8022CC6C **ppHead, unsigned short key)
{
    Node_8022CC6C *p;

    for (p = *ppHead; p != 0; p = p->mpUnknown16) {
        if (p->mUnknown8 == key) {
            return p;
        }
    }
    return 0;
}

void fn_8022CCC4(Node_8022CC6C **ppHead, Node_8022CC6C *p)
{
    if (*ppHead == p) {
        *ppHead = p->mpUnknown16;
    }
    if (p->mpUnknown12 != 0) {
        p->mpUnknown12->mpUnknown16 = p->mpUnknown16;
    }
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16->mpUnknown12 = p->mpUnknown12;
    }
    p->mpUnknown12 = p;
    p->mpUnknown16 = p;
}

void fn_8022CD0C(Node_8022CC6C **ppHead, Node_8022CC6C *p)
{
    p->mpUnknown12 = 0;
    p->mpUnknown16 = *ppHead;
    if (p->mpUnknown16 != 0) {
        p->mpUnknown16->mpUnknown12 = p;
    }
    *ppHead = p;
}

void *fn_8022CD30(void)
{
    return lbl_803A2474;
}

void fn_8022CD3C(void *p)
{
}

int fn_8022CD40(int a, int b, int c)
{
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    return fn_801FCE10(0, lbl_802B45F0, &lbl_803A25E0, a, c, b);
}

void fn_8022CDA0(void)
{
    if (lbl_803A25E0.mUnknown0 != 0) {
        fn_801FCFA0(&lbl_803A25E0);
        lbl_803A25E0.mUnknown0 = 0;
        lbl_803A25E0.mUnknown4 = 0;
        lbl_803A25E0.mUnknown8 = -1;
        lbl_803A25E0.mUnknown12 = 0;
    }
}

void fn_8022CDF8(void)
{
    int value;
    unsigned char key;
    int err;
    int resultA;
    int resultB;
    Node_8022CC6C *p;

    do {
        err = fn_801FCE10(0, lbl_802B4650, &lbl_803A25E0, &value, &key);
        if (err != 0) {
            break;
        }
        resultA = 0;
        resultB = 0;
        if (lbl_803EC048 != 0) {
            resultA = lbl_803EC048(value);
        }
        if (lbl_803EC04C != 0) {
            resultB = lbl_803EC04C(value);
        }
        if (resultA == 0 && resultB == 0) {
            p = fn_8022CC6C(&lbl_803EC054, key);
            if (p != 0) {
                fn_8022CCC4(&lbl_803EC054, p);
                p->mUnknown8 = value;
                fn_8022CD0C(&lbl_803EC058, p);
            }
        }
    } while (err == 0);
}

int fn_8022D14C(int a)
{
    return 0;
}

int fn_8022D154(void)
{
    lbl_803EC050 = fn_8022C9A8();
    lbl_803EC05C = fn_8022CD30();
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    fn_8022D250(fn_8022D14C);
    fn_8022D25C(0);
    return 0;
}

int fn_8022D1B8(void)
{
    if (lbl_803EC050 != 0) {
        fn_8022C9B4(lbl_803EC050);
        lbl_803EC050 = 0;
    }
    if (lbl_803EC05C != 0) {
        fn_8022CD3C(lbl_803EC05C);
        lbl_803EC05C = 0;
        lbl_803EC060 = 0;
    }
    fn_8022D250(0);
    fn_8022D25C(0);
    lbl_803A25E0.mUnknown0 = 0;
    lbl_803A25E0.mUnknown4 = 0;
    lbl_803A25E0.mUnknown8 = -1;
    lbl_803A25E0.mUnknown12 = 0;
    return 0;
}

int fn_8022D23C(void)
{
    lbl_803EC048 = fn_8022D14C;
    return 0;
}

int fn_8022D250(int (*pCallback)(int a))
{
    lbl_803EC048 = pCallback;
    return 0;
}

int fn_8022D25C(int (*pCallback)(int a))
{
    lbl_803EC04C = pCallback;
    return 0;
}

int fn_8022D3AC(void)
{
    fn_8022CADC();
    fn_8022CDA0();
    return 0;
}

unsigned short fn_8022D3D4(unsigned char key)
{
    unsigned short value = 32767;
    Node_8022CC6C *p = fn_8022CC6C(&lbl_803EC058, key);

    if (p != 0) {
        value = p->mUnknown8;
    }
    return value;
}

int fn_8022D6E8(void)
{
    return 0;
}

void fn_8022D6F0(void)
{
    lbl_803EC064 = 0;
}

unsigned short fn_8022D6FC(int index)
{
    return lbl_802FAA1C[index];
}

int fn_8022D864(void)
{
    return 0;
}

int fn_8022D86C(void)
{
    return 0;
}

void fn_8022DB08(void)
{
    lbl_803EC068 = 0;
    lbl_803EC06C = 0;
    lbl_803EC070 = 0;
    lbl_803EC074 = 0;
}

int fn_8022DBF4(int value)
{
    int err = fn_801FCE10(0, lbl_802B5080, value);

    lbl_803EC07C = value;
    return err;
}

int fn_8022DC38(int value)
{
    int err = fn_801FCE10(0, lbl_802B50A0, value);

    lbl_803EC080 = value;
    return err;
}

int fn_8022DC7C(int value)
{
    return fn_801FCE10(0, lbl_802B50C0, value);
}

int fn_8022DCB0(int value)
{
    return fn_801FCE10(0, lbl_802B50E0, value);
}

int fn_8022DCE4(int value)
{
    return fn_801FCE10(0, lbl_802B5100, value);
}

int fn_8022DD18(int value)
{
    return fn_801FCE10(0, lbl_802B5120, value);
}

int fn_8022DD4C(int value)
{
    return fn_801FCE10(0, lbl_802B519C, value);
}

int fn_8022DD80(int value)
{
    return fn_801FCE10(0, lbl_802B51BC, value);
}

int fn_8022DDB4(int a, void *p)
{
    return 0;
}
