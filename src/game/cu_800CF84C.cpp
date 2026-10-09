#include "game/fn_80195EFC.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80096A58.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80218FC4.h"
#include "game/fn_800B65A0.h"

#include "game/Class_803EC99C.h"
#include "game/cu_8017F264.h"

/* One step of the sequence that mpEntries points to; a step whose first word
   is 0x42 ends it. */
struct Entry_800CFB44 {
    int mUnknown0;
    char mUnknown4[16];
    unsigned char mUnknown20;
};

/* Allocated through fn_80238174 under the id 'qend' (fn_800CFEFC). */
struct State_803EAC98 {
    int mUnknown0;
    int mState;
    short mUnknown8;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    int mUnknown12;
    Entry_800CFB44 *mpEntries;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    unsigned short mUnknown32;
    unsigned char mUnknown34;
    unsigned char mUnknown35;
    unsigned char mUnknown36;
};

struct Params_80092E54 {
    int mUnknown0;
    char mUnknown4[4];
    int mUnknown8;
    char mUnknown12[212];
    unsigned char mUnknown224;
    int mUnknown228;
    int mUnknown232;
};

struct Pair_802DA864 {
    int mUnknown0;
    int mUnknown4;
};

extern "C" {
extern void *lbl_803EB688;

void fn_8004A230(int a);
void fn_80064EFC(int a, int b, int c);
void fn_800655B8(void);
int fn_8006560C(void);
int fn_80092784(unsigned char index);
int fn_80092830(int handle);
int fn_80092E54(Params_80092E54 *pParams, void *pBuffer, int size);
void fn_80092F98(int handle);
void fn_80093348(int handle);
void fn_80093410(int handle);
void fn_800940F0(int handle);
int fn_8009D86C(void);
int fn_800A3444(void);
void fn_800AD910(int a, float b);
void fn_800AFDD4(void (*pCallback)(int, unsigned int));
void fn_800AFE20(void (*pCallback)(int, unsigned int));
void fn_800B14E4(void);
void fn_800B43C8(void);
void fn_800CC560(int a);
void fn_801383E4(int a);
void fn_80139274(void);
void fn_80162780(int a, int b);
void fn_80168C40(void);
void fn_8016DCD4(int a);
int fn_801735EC(void);
void fn_80177E6C(int a, int b);
int fn_80178308(void);
int fn_80178320(void);
int fn_801787DC(int a);
void fn_801789F8(void);
void fn_8017CFB4(int a);
void fn_8017DB44(void);
void fn_8017F048(void);
int fn_801F0F18(int a);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_8021956C(void *p, int a, int b, int c);
void *fn_8023816C(void *pHandle);
}

static State_803EAC98 *lbl_803EAC98 = 0;
static Class_803EC99C lbl_803EC99C;
Class_803EC99C *lbl_803EAC9C = &lbl_803EC99C;
static unsigned char lbl_803EACA0 = 0;
static unsigned char lbl_803EACA1 = 0;
static unsigned char lbl_803EACA2 = 0;
static void *lbl_803EC9A0[1];
static Pair_802DA864 lbl_802DA864[3] = { { 1, 0 }, { 1, 1 }, { 2, 0 } };

extern "C" {
unsigned char fn_800CF84C(void)
{
    if (++lbl_803EACA1 >= sizeof(lbl_803EC9A0) / sizeof(lbl_803EC9A0[0])) {
        lbl_803EACA1 = 0;
    }
    return lbl_803EACA1;
}

int fn_800CF874(void)
{
    int result = 0;

    if (lbl_803EAC98->mUnknown20 != -1 && fn_80092830(lbl_803EAC98->mUnknown20)) {
        result = 1;
    }
    return result;
}

void fn_800CF8C0(void) {}

void fn_800CF8C4(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(lbl_803EC9A0) / sizeof(lbl_803EC9A0[0]); i++) {
        if (lbl_803EC9A0[i] != 0) {
            fn_801D2BD0(lbl_803EC9A0[i]);
            lbl_803EC9A0[i] = 0;
        }
    }
}

void fn_800CF91C(void)
{
    fn_801F0F18(0);
    if (lbl_803EAC98->mUnknown28 != -1) {
        fn_800940F0(lbl_803EAC98->mUnknown28);
        fn_80093410(lbl_803EAC98->mUnknown28);
        lbl_803EAC98->mUnknown28 = -1;
    }
    if (lbl_803EAC98->mUnknown20 != -1) {
        fn_800940F0(lbl_803EAC98->mUnknown20);
        fn_80093410(lbl_803EAC98->mUnknown20);
        lbl_803EAC98->mUnknown20 = -1;
    }
    if (lbl_803EAC98->mUnknown24 != -1) {
        fn_80093410(lbl_803EAC98->mUnknown24);
        lbl_803EAC98->mUnknown24 = -1;
    }
    fn_800CF8C0();
    fn_8004A230(1);
    fn_801383E4(1);
    fn_800CF8C4();
    fn_80195EFC(1, 20, 0x808080, 0);
}

void fn_800CF9E8(void)
{
    lbl_803EAC98->mUnknown20 = -1;
    lbl_803EAC98->mUnknown24 = -1;
    lbl_803EAC98->mUnknown28 = -1;
}

void fn_800CFA00(int a, void *pBuffer, int size)
{
    Params_80092E54 params;
    int index;

    fn_801C1F94(&params, 0, sizeof(params));
    params.mUnknown0 = a;
    params.mUnknown8 = 36;
    index = fn_802372EC(0, 3);
    params.mUnknown224 = 1;
    params.mUnknown228 = lbl_802DA864[index].mUnknown0;
    params.mUnknown232 = lbl_802DA864[index].mUnknown4;
    lbl_803EAC98->mUnknown24 = fn_80092E54(&params, pBuffer, size);
}

void fn_800CFA98(void)
{
    fn_80092F98(lbl_803EAC98->mUnknown24);
    lbl_803EAC98->mUnknown28 = lbl_803EAC98->mUnknown20;
    lbl_803EAC98->mUnknown20 = lbl_803EAC98->mUnknown24;
}

void fn_800CFAD4(void)
{
    fn_800940F0(lbl_803EAC98->mUnknown20);
    fn_80093348(lbl_803EAC98->mUnknown20);
    fn_80093410(lbl_803EAC98->mUnknown28);
    fn_80092F98(lbl_803EAC98->mUnknown24);
    lbl_803EAC98->mUnknown28 = lbl_803EAC98->mUnknown20;
    lbl_803EAC98->mUnknown20 = lbl_803EAC98->mUnknown24;
    lbl_803EAC98->mUnknown24 = -1;
    fn_80092830(lbl_803EAC98->mUnknown20);
}

void fn_800CFB44(Entry_800CFB44 *pEntries, int index)
{
    if (lbl_803EAC98->mpEntries[index].mUnknown0 != 0x42) {
        int size = 0;
        void *pBuffer = 0;

        if (pEntries[index].mUnknown20 == 1) {
            size = 0x57800;
            pBuffer = lbl_803EC9A0[lbl_803EACA1];
            lbl_803EACA1 = fn_800CF84C();
        }
        fn_800CFA00(pEntries[index].mUnknown0, pBuffer, size);
    }
}

void fn_800CFD08(int a, unsigned int b);

void fn_800CFBCC(void)
{
    fn_800AFE20(fn_800CFD08);
    if (lbl_803EAC98->mUnknown11) {
        if (fn_8009D86C() != 6) {
            fn_80064EFC(3, 1, -1);
            lbl_803EAC98->mState = 3;
        } else {
            lbl_803EAC98->mState = 4;
        }
    } else {
        lbl_803EAC98->mState = 4;
    }
}

void fn_800CFC38(void)
{
    if (lbl_803EAC98->mpEntries[lbl_803EACA0].mUnknown0 == 0x42) {
        fn_800CFBCC();
    } else {
        fn_800CFA98();
        fn_800CFB44(lbl_803EAC98->mpEntries, lbl_803EACA0 + 1);
        lbl_803EAC98->mUnknown32 = 0;
        lbl_803EAC98->mState = 2;
    }
}

void fn_800CFCA4(void)
{
    lbl_803EAC98->mUnknown10 = 0;
    if (lbl_803EAC98->mUnknown12 != -1) {
        fn_80096D14(lbl_803EAC98->mUnknown12);
        lbl_803EAC98->mUnknown12 = -1;
    }
    if (lbl_803EAC98->mUnknown36) {
        fn_800CFC38();
    } else {
        fn_800CFBCC();
    }
}

void fn_800CFD08(int a, unsigned int b)
{
    switch (b) {
    case 0:
        if (fn_8009D86C() != 6) {
            lbl_803EAC98->mUnknown8 = 181;
        }
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    default:
        return;
    }
    if (lbl_803EAC98->mUnknown10) {
        if (lbl_803EAC98->mUnknown8 > 90) {
            lbl_803EAC98->mUnknown8 = 181;
            fn_800CFCA4();
        }
    } else if (lbl_803EAC98->mState <= 2 && lbl_803EAC98->mUnknown32 > 60) {
        fn_800CF91C();
        fn_800CFBCC();
    }
}

void fn_800CFDA4(void)
{
    Params_80096A58 params;

    fn_800B43C8();
    fn_801C1F94(&params, 0, sizeof(params));
    params.mUnknown40 = 0xFFFF;
    params.mUnknown42 = 0xFFFF;
    switch (fn_800A3444()) {
    case 0:
        params.mUnknown0 = 14;
        break;
    case 2:
        params.mUnknown0 = 2;
        break;
    case 3:
        params.mUnknown0 = 26;
        break;
    case 1:
        params.mUnknown0 = 20;
        break;
    case 4:
        params.mUnknown0 = 8;
        break;
    case 5:
        params.mUnknown0 = 33;
        break;
    case 6:
        params.mUnknown0 = 36;
        break;
    case 7:
        params.mUnknown0 = 30;
        break;
    case 8:
        params.mUnknown0 = 11;
        break;
    case 10:
        params.mUnknown0 = 17;
        break;
    case 11:
        params.mUnknown0 = 23;
        break;
    case 9:
    default:
        params.mUnknown0 = 5;
        break;
    }
    params.mUnknown28 = fn_802372EC(1, 2);
    params.mUnknown20 = 2;
    params.mUnknown24 = 0;
    params.mUnknown12 |= 0x10;
    lbl_803EAC98->mUnknown12 = fn_80096A58(&params);
}

void fn_800CFEF8(void) {}
}

void Class_803EC99C::fn_800CFEFC()
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAC98, sizeof(State_803EAC98), 0, 0x71656E64);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}

void Class_803EC99C::fn_800CFF4C()
{
    fn_800B14E4();
    lbl_803EAC98->mState = 0;
    fn_80177E6C(1, 0);
    lbl_803EAC98->mUnknown0 = fn_8009D86C();
    fn_8017F2DC(0);
    lbl_803EAC98->mUnknown10 = 0;
    lbl_803EAC98->mUnknown11 = 0;
    lbl_803EAC98->mUnknown36 = 0;
    fn_801789F8();
    fn_800CF9E8();
    fn_800CFDA4();
}

void Class_803EC99C::fn_800CFFC4(float f)
{
    unsigned short a = 0;
    unsigned short b = 0;

    fn_8004A230(0);
    switch (lbl_803EAC98->mState) {
    case 0:
        lbl_803EACA2 = 0;
        fn_80219650(lbl_803EB688, &a, &b);
        if (a == 3 && b == 2) {
            break;
        }
        fn_8017CFB4(7);
        switch (lbl_803EAC98->mUnknown0) {
        case 4:
        case 5:
            if (fn_801787DC(0) != fn_801787DC(1)) {
                lbl_803EAC98->mUnknown11 = 1;
            }
            break;
        case 2:
            lbl_803EAC98->mUnknown11 = 1;
            fn_800CFEF8();
            break;
        default:
            lbl_803EAC98->mUnknown11 = 0;
            break;
        }
        if (fn_800B65A0(fn_80178308()) == 0xFF && fn_800B65A0(fn_80178320()) == 0xFF) {
            lbl_803EAC98->mUnknown11 = 0;
        }
        if (lbl_803EAC98->mUnknown11 == 1) {
            fn_800655B8();
        }
        lbl_803EAC98->mUnknown8 = 0;
        lbl_803EAC98->mUnknown10 = 1;
        fn_800AFDD4(fn_800CFD08);
        fn_80162780(1, 1);
        if (fn_8009D86C() == 6) {
            fn_8017DB44();
        } else if (fn_8009D86C() == 5) {
            if (fn_801735EC()) {
                fn_80168C40();
                fn_800CC560(1);
            }
        } else {
            fn_8016DCD4(1);
            fn_8016DCD4(0);
        }
        if (fn_8009D86C() != 6 && fn_8009D86C() == 3) {
            fn_8017F048();
        }
        fn_801789F8();
        lbl_803EAC98->mState = 1;
        break;
    case 1:
        lbl_803EAC98->mUnknown8++;
        fn_80096B1C(lbl_803EAC98->mUnknown12);
        if (lbl_803EACA2 == 0 && lbl_803EAC98->mUnknown8 > 59) {
            fn_80218FC4(lbl_803EB688, 3, 5, 0, 0);
            lbl_803EACA2 = 1;
        }
        if (lbl_803EAC98->mUnknown8 > 600) {
            fn_8021956C(lbl_803EB688, 3, 5, 1);
            lbl_803EACA2 = 0;
            fn_800CFCA4();
        }
        break;
    case 2:
        lbl_803EAC98->mUnknown32++;
        if (fn_800CF874()) {
            if (fn_80092784(lbl_803EAC98->mUnknown20)) {
                fn_8004A230(0);
                fn_801383E4(0);
            }
        } else {
            lbl_803EACA0++;
            if (lbl_803EAC98->mpEntries[lbl_803EACA0].mUnknown0 == 0x42) {
                fn_800CF91C();
                fn_800CFBCC();
            } else {
                fn_800CFAD4();
                fn_800CFB44(lbl_803EAC98->mpEntries, lbl_803EACA0 + 1);
            }
        }
        break;
    case 3:
        if (fn_8006560C() == 0) {
            fn_80162780(1, 1);
            lbl_803EAC98->mState = 4;
        }
        break;
    case 4:
        if (fn_8009D86C() != 6) {
            switch (fn_8009D86C()) {
            case 5:
                fn_800AD910(9, f);
                break;
            case 3:
                fn_8017F048();
                fn_800AD910(5, f);
                fn_80139274();
                break;
            default:
                fn_80139274();
                fn_800AD910(5, f);
                break;
            }
        } else {
            if (lbl_803EACA2) {
                fn_8021956C(lbl_803EB688, 3, 5, 1);
                lbl_803EACA2 = 0;
            }
            fn_800AD910(7, 0.0f);
        }
        break;
    }
}

void Class_803EC99C::fn_800D0394()
{
    fn_800B14E4();
    if (lbl_803EAC98->mUnknown10) {
        lbl_803EAC98->mUnknown10 = 0;
        fn_800AFE20(fn_800CFD08);
    }
    fn_801789F8();
    lbl_803EAC98->mUnknown35 = 0;
    lbl_803EAC98->mUnknown36 = 0;
    lbl_803EAC98->mpEntries = 0;
    lbl_803EAC98->mUnknown34 = 0;
    lbl_803EACA0 = 0;
    lbl_803EACA1 = 0;
}

bool Class_803EC99C::fn_800D0408()
{
    return lbl_803EAC98->mUnknown10 == 1;
}
