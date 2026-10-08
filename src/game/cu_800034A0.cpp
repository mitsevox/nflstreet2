#include "game/fn_801D2B7C.h"
#include "game/cu_800034A0.h"
#include "game/cu_8002ACB4.h"

extern "C" {
void *fn_801D2B7C(int size, int a, int b);
int fn_8018A854(void);
void fn_80228474(int a, int b, void *c, int d);
void fn_8002A478(int *pType, void *pSlot);
int fn_80029890(int type);
void fn_8022F358(signed char slot);
void fn_8022F478(void);
int fn_8022F698(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps);
int fn_8022EB94(CardStreamTarget *pTarget, StreamOps_8002ACB4 *pOps);
void fn_8002A5A0(int *pType, void *pSlot);
int fn_8002A2A4(int a, int b);
void fn_8022F1BC(void);
void fn_80029DCC(int a, int b);
int fn_8022F0D4(void);
int fn_8002ADA0(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps);
int fn_8022F5E4(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps);
int fn_8022EB5C(CardStreamTarget *pTarget, StreamOps_8002ACB4 *pOps);

int fn_8022F53C(int a);
int fn_8022F4BC(void);
int fn_8022F384(int a);
void fn_8002A574(int a, int b);
void fn_801D6B24(char *p, int size);
void fn_80029A40(int a, int b, unsigned int c, char *d);
void fn_8022F3D4(int a);
void fn_8007A24C(void);
void fn_80029CE0(int a, int b);
int fn_801D6844(void);
void fn_801D6DE0(int a, int b);
void fn_8006EC24(void);
void fn_8022EBC8(void);
void fn_8022EB10(void);
void fn_8007F328(int a);
void fn_8007F374(void);
int fn_800298E8(int a, int b);

int fn_801D6620(void *p);
int fn_801D6EA0(int a);
void fn_801D6EFC(void);
void fn_80029990(int type, int index, int value);
void fn_80029E10(int a, int b);
void fn_802284EC(int a, void *b);
void fn_8002A804(void);

extern StreamOps_8002ACB4 gCardStreamOps;
}

extern "C" {

void fn_800034A0(void)
{
    lbl_803ECCA4 = fn_801D2B7C(16384, 0, 0);
}

void fn_800034D0(void)
{
    fn_801D2BD0(lbl_803ECCA4);
    lbl_803ECCA4 = 0;
}

void fn_800034FC(void)
{
    Request_8002AD64 req;
    char slot[4];
    int type;

    fn_800034A0();

    *(void **)&req.mUnknown0[0] = &lbl_803EB8C8;
    *(void **)&req.mUnknown0[4] = lbl_803ECCA4;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mTarget = (int)&lbl_80367580;
    req.mUnknown10 = 1;

    lbl_80367580.mFillToEnd = 1;
    lbl_80367580.mPosition = 0;

    if (fn_8018A854()) {
        fn_80228474(fn_8018A854(), 2, (void *)fn_8002A804, 31);
    }

    lbl_803EB8D4 = 1;
    fn_8002A478(&type, slot);
    lbl_803EB8C8 = 0;
    lbl_80367580.mSize = fn_80029890(type);

    switch (type) {
    case 1:
        fn_8022EB94(&lbl_80367580, &gCardStreamOps);
        break;
    case 2:
        fn_8022F358(slot[3]);
        fn_8022F478();
        fn_8022F698(&req, &gCardStreamOps);
        break;
    case 3:
        fn_8022F358(slot[3]);
        fn_8022F478();
        fn_8002AD64(&req, &gCardStreamOps);
        break;
    }
}

void fn_80003620(void)
{
    Request_8002AD64 req;
    char slot[4];
    int type;
    int handle = 0;

    fn_800034A0();

    *(void **)&req.mUnknown0[0] = &lbl_803EB8C8;
    *(void **)&req.mUnknown0[4] = lbl_803ECCA4;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mTarget = (int)&lbl_80367580;
    req.mUnknown10 = 1;

    lbl_803EB8C8 = 0;
    lbl_80367580.mFillToEnd = 1;
    lbl_80367580.mPosition = 0;

    if (fn_8018A854()) {
        fn_80228474(fn_8018A854(), 2, (void *)fn_8002A804, 31);
    }

    lbl_803EB8D4 = 1;
    fn_8002A5A0(&type, slot);
    lbl_80367580.mSize = fn_80029890(type);

    switch (type) {
    case 1:
        handle = fn_8022EB5C(&lbl_80367580, &gCardStreamOps);
        break;
    case 2:
        if (fn_8002A2A4(2, *(int *)slot)) {
            fn_8022F358(slot[3]);
            fn_8022F1BC();
            fn_80029DCC(type, *(int *)slot);
        }
        if (fn_8022F0D4() != -1) {
            fn_8022F478();
            handle = fn_8022F5E4(&req, &gCardStreamOps);
        }
        break;
    case 3:
        if (fn_8002A2A4(3, *(int *)slot)) {
            fn_8022F358(slot[3]);
            fn_8022F1BC();
            fn_80029DCC(type, *(int *)slot);
        }
        if (fn_8022F0D4() != -1) {
            fn_8022F478();
            handle = fn_8002ADA0(&req, &gCardStreamOps);
        }
        break;
    }

    if (handle) {
        lbl_803EB8C8 = handle;
    }
}

void fn_800037C0(int a, int *b)
{
    char buf[24];
    int slot;
    int type;

    buf[0] = 1;

    fn_8002A5A0(&type, &slot);

    switch (type) {
    case 1:
        if (a) {
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
            fn_8022EBC8();
            fn_8022EB10();
            fn_8007F328(1);
            fn_8007F374();
        } else {
            fn_8006EC24();
            fn_801D6B24(buf + 8, 17);
            fn_80029A40(type, slot, fn_800298E8(type, slot), buf + 8);
        }
        break;
    case 2: {
        int res = fn_8022F53C(a);
        if (res == 1) {
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
        } else if (res == 0) {
            int res_f4bc = fn_8022F4BC();
            slot = fn_8022F384(res_f4bc);
            fn_8002A574(type, slot);
            fn_801D6B24(buf + 8, 17);
            fn_80029A40(type, slot, lbl_80367580.mChecksum, buf + 8);
            fn_8022F3D4(res_f4bc);
            fn_8007A24C();
            fn_80029CE0(type, slot);
        } else {
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
        }
        break;
    }
    case 3: {
        int res = fn_8022F53C(a);
        if (res == 1) {
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
        } else if (res == 0) {
            int res_f4bc = fn_8022F4BC();
            slot = fn_8022F384(res_f4bc);
            fn_8002A574(type, slot);
            fn_801D6B24(buf + 8, 17);
            fn_80029A40(type, slot, lbl_80367580.mChecksum, buf + 8);
            fn_80029CE0(type, slot);
        } else {
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
        }
        break;
    }
    }
}

int fn_800039E4(int a, int *b, int *c)
{
    char val = 0;
    int state = a;

    switch (state) {
    case 0:
        *b = fn_801D6620(c);
        break;
    case 1:
        state = 4;
        *b = fn_801D6620(c);
        break;
    case 4:
        *b = fn_801D6620(c);
        if (fn_801D6EA0(0)) {
            fn_800034FC();
            state = 5;
        }
        break;
    case 5:
        *b = 0;
        if ((unsigned int)(lbl_803EB8C8 - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                fn_800034D0();
                state = 6;
                fn_801D6EFC();
            }
            if (val) {
                fn_800034D0();
                state = 6;
            }
        }
        break;
    case 6: {
        int type;
        int slot;
        *b = fn_801D6620(c);
        if (*b == 0) {
            return state;
        }
        if (lbl_803EB8C8 == 0 && c != 0 && *c < 0) {
            lbl_803EB8C8 = 36;
        }
        fn_8002A478(&type, &slot);
        if (lbl_803EB8C8 == 0) {
            fn_80029990(type, slot, lbl_80367580.mChecksum);
        } else {
            fn_80029E10(type, slot);
        }
        state = 0;
        break;
    }
    case 7:
        state = 9;
        *b = fn_801D6620(c);
        break;
    case 9:
        *b = fn_801D6620(c);
        if (fn_801D6EA0(0)) {
            fn_80003620();
            state = 10;
        }
        break;
    case 10:
        *b = 0;
        if ((unsigned int)(lbl_803EB8C8 - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                fn_800034D0();
                state = 11;
                fn_801D6EFC();
            }
            if (val) {
                fn_800034D0();
                state = 11;
            }
        }
        break;
    case 11:
        *b = fn_801D6620(c);
        if (*b == 0) {
            return state;
        }
        if (lbl_803EB8C8 == 0 && c != 0 && *c < 0) {
            lbl_803EB8C8 = 36;
        }
        state = 0;
        fn_800037C0(lbl_803EB8C8, c);
        break;
    }

    if (*b != 0 && lbl_803EB8D4 != 0) {
        if (fn_8018A854()) {
            fn_802284EC(fn_8018A854(), (void *)fn_8002A804);
        }
        lbl_803EB8D4 = 0;
    }

    return state;
}

}
