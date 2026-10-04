#include "game/fn_800AD9B4.h"
#include "game/fn_8017F584.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

/* Entry returned by fn_800B1648; only the accessed fields are declared. */
struct Record_800B1648 {
    int mUnknown0;
    char mUnknown4[16];
    unsigned short mUnknown14;
    unsigned int mUnknown18;
};

extern "C" {
extern void *lbl_803EAB84;

int fn_80025708(void);
void fn_8002572C(void);
Object_80039F5C *fn_8009BCE8(int *pRef);
int fn_8009D558(int a);
void fn_8009D818(int state);
int fn_8009D86C(void);
void fn_8009D888(int index, int a);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
unsigned int fn_8009D990(int index);
int fn_8009D9A8(int index);
int fn_8009D9D8(int index);
void fn_800AD910(int a, float b);
unsigned int fn_800B15D4(void);
Record_800B1648 *fn_800B1648(unsigned short index);
int fn_800B232C(int a);
int fn_800B2624(void);
int fn_800B9A90(void *pHandle);
void fn_800B9B9C(void *pHandle);
int fn_800BA6F8(void);
int fn_801486A0(void);
void fn_8016E498(void);
int fn_8016E764(void);
int fn_80177F70(void);
void fn_80178370(void);
int fn_801787DC(int team);
int fn_80178AE0(void);
int fn_80178C24(void);
void *fn_8023816C(void *pHandle);

void fn_801735B4(unsigned int mask);
unsigned int fn_801735C8(unsigned int mask);
void fn_801735D8(unsigned int mask);
void fn_801739D0(void);
int fn_80173A88(void);
unsigned char fn_80173B64(void);
}

/* Flag word allocated through fn_80238174 under the id 'clkr' (fn_801732D0). */
static unsigned int *lbl_803ECB2C;

extern "C" {

void fn_80173298(int a, int b)
{
    fn_801FCE10(0, "update 'FNIG' set 'OTHG' = \x82 and 'OTAG' = \x82\n", a, b);
}

void fn_801732D0(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803ECB2C, sizeof(*lbl_803ECB2C), 0, 0x636C6B72);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}

void fn_80173320(void)
{
}

void fn_80173324(int a)
{
    int flags;

    if (fn_8009D86C() != 6) {
        flags = fn_8009D558(a);
    } else {
        flags = 0;
    }
    if (flags & 2) {
        if (fn_8016E764()) {
            fn_8016E498();
        }
    }
    if (flags & 1) {
        if (!fn_801735C8(0x10) && fn_80173A88() && !fn_80173B64() && fn_800AD9B4() != 3) {
            fn_8009D8CC(1);
            fn_8009D8CC(0);
            fn_801735B4(1);
            fn_80178370();
            fn_801735B4(0x10);
            fn_801735D8(0x100);
            fn_800B9B9C(lbl_803EAB84);
            if (fn_80025708()) {
                fn_8002572C();
            }
        }
    }
}

void fn_80173404(void)
{
    int state;

    fn_8009D8CC(1);
    fn_801787DC(0);
    fn_801787DC(1);
    state = fn_8009D86C();
    switch (state) {
    case 0:
        state = 4;
        fn_80173298(0, 0);
        break;
    case 2:
        fn_80173298(3, 3);
    case 1:
    case 3:
        state++;
        fn_800AD910(6, 0.0f);
        break;
    case 4:
        fn_8017F584();
        if (fn_80178AE0() == 2 && !fn_80025708()) {
            fn_801735B4(0x40);
            state = 5;
            fn_80173298(2, 2);
            fn_801FCE10(0, "update 'FNIG' set 'TOFG' = \x83\n", 1);
        } else {
            state = 6;
        }
        fn_800AD910(7, 0.0f);
        break;
    case 5:
        state = 6;
        fn_800AD910(6, 0.0f);
        break;
    }
    if (state != 6) {
        fn_8009D964(1, fn_8009D9A8(1));
    }
    if (state == 1 || state == 3 || state == 5) {
        fn_8017886C()->mUnknown1D = 0;
    }
    fn_8009D818(state);
    fn_801735D8(4);
    fn_801735D8(0x80);
    if (fn_8009D990(1) <= 120 && !fn_800BA6F8()) {
        fn_801735B4(4);
        fn_801735B4(0x80);
    }
}

void fn_801735B4(unsigned int mask)
{
    *lbl_803ECB2C |= mask;
}

unsigned int fn_801735C8(unsigned int mask)
{
    return *lbl_803ECB2C & mask;
}

void fn_801735D8(unsigned int mask)
{
    *lbl_803ECB2C &= ~mask;
}

unsigned char fn_801735EC(void)
{
    return fn_801735C8(0x40);
}

void fn_80173614(void)
{
    int allow;

    fn_801735D8(0x32B);
    if (fn_8009D9D8(0) == 1) {
        fn_8009D8CC(0);
    }
    if (fn_8009D9D8(1) == 0) {
        allow = 1;
        if (!fn_80178C24()) {
            allow = 0;
        }
        if (fn_80177F70() == 6 || fn_80177F70() == 0) {
            allow = 0;
        }
        if (allow) {
            fn_8009D888(1, 0);
        }
    }
}

void fn_801736AC(void)
{
    int allow;
    int mode;

    if (fn_8009D9D8(1) == 0 && !fn_801735C8(1) && fn_801735C8(2)) {
        allow = 1;
        switch (fn_8009D86C()) {
        case 2:
            if (fn_8009D990(1) <= 119 && !fn_801735C8(0x100)) {
                allow = 0;
            }
            break;
        case 4:
        case 5:
            if (fn_8009D990(1) <= 299 && !fn_801735C8(0x100)) {
                allow = 0;
            }
            break;
        }
        mode = fn_80177F70();
        if (mode == 0 || mode == 6) {
            allow = 0;
        }
        if (!fn_80178C24()) {
            allow = 0;
        }
        if (allow) {
            fn_8009D888(1, 0);
        }
    }
}

void fn_80173794(void)
{
    unsigned int count = fn_800B15D4();
    int found = 0;
    int seen3 = 0;
    int check = 0;
    unsigned short i;

    for (i = 0; i < count; i++) {
        Record_800B1648 *pRecord = fn_800B1648(i);

        switch (pRecord->mUnknown14) {
        case 3:
            seen3 = 1;
            break;
        case 11:
        case 13:
        case 20:
        case 21:
        case 30:
            found = 1;
            fn_801735B4(1);
            break;
        case 25:
            found = 1;
            fn_801735D8(0x100);
            if (seen3) {
                switch (fn_8009D86C()) {
                case 2:
                    if (pRecord->mUnknown18 <= 119) {
                        fn_801735B4(1);
                    } else {
                        fn_801735B4(2);
                    }
                    break;
                case 4:
                case 5:
                    if (pRecord->mUnknown18 <= 299) {
                        fn_801735B4(1);
                    } else {
                        fn_801735B4(2);
                    }
                    break;
                default:
                    fn_801735B4(2);
                    break;
                }
                if (fn_800B232C(0) == 2) {
                    check = 1;
                }
            } else {
                check = 1;
            }
            if (check) {
                switch (fn_8009D86C()) {
                case 2:
                case 4:
                case 5:
                    if (fn_8009D9D8(1) && fn_8009D990(1) <= 44 && fn_800B2624()) {
                        Object_80039F5C *p = fn_8009BCE8(&pRecord->mUnknown0);
                        int score = fn_801787DC(p->mId >> 8 & 0xFF);

                        if (score < fn_801787DC((p->mId >> 8 & 0xFF) ^ 1)) {
                            fn_801735D8(1);
                            fn_801735B4(0x100);
                            fn_801735B4(2);
                        }
                    }
                    break;
                }
            }
            break;
        case 22:
        case 39:
            found = 1;
            if (seen3) {
                if (pRecord->mUnknown0) {
                    fn_801739D0();
                } else {
                    fn_801735B4(1);
                }
            }
            break;
        }
    }
    if (found) {
        fn_8009D8CC(1);
    }
    fn_8009D8CC(0);
}

void fn_801739D0(void)
{
    switch (fn_8009D86C()) {
    case 2:
        if (fn_8009D990(1) <= 119) {
            fn_801735B4(1);
        } else {
            fn_801735B4(2);
        }
        break;
    case 4:
    case 5:
        if (fn_8009D990(1) <= 299) {
            fn_801735B4(1);
        } else {
            fn_801735B4(2);
        }
        break;
    default:
        fn_801735B4(2);
        break;
    }
}

void fn_80173A50(void)
{
    fn_8009D8CC(1);
    fn_801735B4(1);
    fn_8009D964(0, 10);
}

int fn_80173A88(void)
{
    int allow = 1;
    int mode = fn_800AD9B4();
    int state = fn_8009D86C();

    if (fn_800BA6F8() || mode == 3 || (!(unsigned char)fn_800B9A90(lbl_803EAB84) && mode != 2)) {
        allow = 0;
    }
    if (fn_801486A0() == 3 && fn_8009D990(1) != 0) {
        allow = 0;
    }
    if (state == 2 || state == 4 || state == 5) {
        if (fn_800B2624() && !fn_801735C8(0x100)) {
            fn_801735B4(0x20);
            allow = 0;
        } else {
            fn_801735D8(0x20);
        }
    }
    return allow;
}

unsigned char fn_80173B64(void)
{
    return fn_801735C8(0x20);
}

void fn_80173B8C(void)
{
    fn_8009D8CC(0);
    fn_801735B4(1);
    fn_8009D8CC(1);
    fn_80173404();
    fn_801735D8(0x10);
}

void fn_80173BCC(void)
{
    fn_801735B4(4);
    fn_801735B4(0x80);
}

void fn_80173BF8(void)
{
    fn_801735B4(4);
}

void fn_80173C1C(void)
{
    *lbl_803ECB2C = 0;
}

}
