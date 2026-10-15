#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8009D990.h"
#include "game/fn_800F06F4.h"
#include "game/Class_80297C60.h"
#include <string.h>

struct State_802A23A8 {
    char mUnknown0[4];
    unsigned char mUnknown4;
};

extern "C" {
extern unsigned char lbl_803EB2D0;
extern unsigned char lbl_803EB2D1;
extern char *lbl_803EB2BC;
extern char *lbl_803EB2C0;
extern char *lbl_803EB2C4;
extern char *lbl_803EB2C8;
extern char *lbl_803EB2CC;
extern void *lbl_803EB688;

void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
void fn_8009D888(int index, int value);
float fn_80178A2C(void);
void fn_80178A20(float value);
void fn_80178E88(float v);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
void fn_80178370(void);
int fn_801783AC(int bit);
void fn_801790D0(int team, float a, float b);
void fn_80157514(void);
int fn_80054568(void);
int fn_800C1E40(void);
void fn_801486A8(void);
void fn_801487C0(int team, unsigned char begin);
int fn_8011F1CC(void);
void fn_8017D7C4(const char *pText);
int fn_800A2178(void);
int fn_800A937C(void);
int fn_800A8444(int team);
int fn_800A8EA4(int team);
int fn_80218FC4(void *p, unsigned short a, unsigned short b, unsigned char count, int *pArgs);
int fn_8014BC90(void);
int fn_800B9A90(Class_80297C60 *p);

void fn_800BC5DC(void *p);
void fn_800BCB18(void *p, float dt);
void fn_800B3718(void *p, float dt);
void fn_800B9654(void *p);
void fn_800B9830(void *p, float dt);
void fn_800BFB88(void *p, float dt);
void fn_800A042C(void *p, float dt);
void fn_800A050C(void *p, float dt);
int fn_800B8E18(void *p, char *pText);
void fn_800B925C(void *p, char *pText);

void fn_8014BC98(const int *pValues, int *pOrder, unsigned int count)
{
    int has0 = 0, has2 = 0, has3 = 0, has1 = 0, has4 = 0, has5 = 0, has6 = 0;
    for (unsigned char i = 0; i < count; i++) {
        if (pOrder[0] == pValues[i]) {
            has0 = 1;
        } else if (pOrder[2] == pValues[i]) {
            has2 = 1;
        } else if (pOrder[3] == pValues[i]) {
            has3 = 1;
        } else if (pOrder[1] == pValues[i]) {
            has1 = 1;
        } else if (pOrder[4] == pValues[i]) {
            has4 = 1;
        } else if (pOrder[5] == pValues[i]) {
            has5 = 1;
        } else if (pOrder[6] == pValues[i]) {
            has6 = 1;
        }
    }
    int temp;
    if (!has0) {
        if (has4) {
            temp = pOrder[0];
            pOrder[0] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[0];
            pOrder[0] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[0];
            pOrder[0] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has2) {
        if (has4) {
            temp = pOrder[2];
            pOrder[2] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[2];
            pOrder[2] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[2];
            pOrder[2] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has3) {
        if (has4) {
            temp = pOrder[3];
            pOrder[3] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[3];
            pOrder[3] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[3];
            pOrder[3] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has1) {
        if (has4) {
            temp = pOrder[1];
            pOrder[1] = pOrder[4];
            pOrder[4] = temp;
        } else if (has5) {
            temp = pOrder[1];
            pOrder[1] = pOrder[5];
            pOrder[5] = temp;
        } else if (has6) {
            temp = pOrder[1];
            pOrder[1] = pOrder[6];
            pOrder[6] = temp;
        }
    }
}

void fn_8014BED8(const int *pValues, int *pOrder, unsigned int count)
{
    int has11 = 0, has9 = 0, has13 = 0, has10 = 0, has7 = 0, has12 = 0, has8 = 0;
    for (unsigned char i = 0; i < count; i++) {
        if (pOrder[11] == pValues[i]) {
            has11 = 1;
        } else if (pOrder[9] == pValues[i]) {
            has9 = 1;
        } else if (pOrder[13] == pValues[i]) {
            has13 = 1;
        } else if (pOrder[10] == pValues[i]) {
            has10 = 1;
        } else if (pOrder[7] == pValues[i]) {
            has7 = 1;
        } else if (pOrder[12] == pValues[i]) {
            has12 = 1;
        } else if (pOrder[8] == pValues[i]) {
            has8 = 1;
        }
    }
    int temp;
    if (!has11) {
        if (has7) {
            temp = pOrder[11];
            pOrder[11] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[11];
            pOrder[11] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[11];
            pOrder[11] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has9) {
        if (has7) {
            temp = pOrder[9];
            pOrder[9] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[9];
            pOrder[9] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[9];
            pOrder[9] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has13) {
        if (has7) {
            temp = pOrder[13];
            pOrder[13] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[13];
            pOrder[13] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[13];
            pOrder[13] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has10) {
        if (has7) {
            temp = pOrder[10];
            pOrder[10] = pOrder[7];
            pOrder[7] = temp;
        } else if (has12) {
            temp = pOrder[10];
            pOrder[10] = pOrder[12];
            pOrder[12] = temp;
        } else if (has8) {
            temp = pOrder[10];
            pOrder[10] = pOrder[8];
            pOrder[8] = temp;
        }
    }
}

void fn_8014C118(void *p, float dt)
{
    fn_800B3718(p, dt);
    fn_801487C0(0, 4);
    fn_801487C0(1, 4);
}

int fn_8014C150(void)
{
    return 4;
}

int fn_8014C158(void)
{
    return 1;
}

void fn_8014C160(void *p)
{
    fn_800B9654(p);
    fn_8009D8CC(5);
}

void fn_8014C188(void *p)
{
    char text[32];
    int changed = fn_800B8E18(p, text);
    if (fn_800A2178() == 14) {
        changed = 1;
        strcpy(text, lbl_803EB2CC);
    } else if (fn_80178308() != fn_80178348()) {
        changed = 1;
        strcpy(text, lbl_803EB2C8);
    }
    if (changed) {
        fn_800B925C(p, text);
    }
}

void fn_8014C214(void *p, float dt)
{
    fn_800B9830(p, dt);
    if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
        if (fn_8014BC90()) {
            if (!lbl_803EB2D0) {
                fn_8017D7C4(lbl_803EB2C4);
                lbl_803EB2D0 = 1;
            }
        } else {
            lbl_803EB2D0 = 0;
        }
    }
}

void fn_8014C278(State_802A23A8 *p, float dt)
{
    fn_800A042C(p, dt);
    if (fn_800A937C() == 0) {
        fn_8009D888(5, 0);
    }
    unsigned char blocked = 0;
    if ((fn_800A8444(0) && fn_800A8EA4(0) == 2) || (fn_800A8444(1) && fn_800A8EA4(1) == 2)) {
        blocked = 1;
    }
    p->mUnknown4 = blocked;
}

void fn_8014C308(State_802A23A8 *p, float dt)
{
    int clear = 1;
    fn_800A050C(p, dt);
    if (fn_800A937C() == 0) {
        unsigned char i;
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = fn_80039F5C(fn_80178308(), i);
            if (fn_800F06F4(0, pPlayer->mpState, 18, 0xFFFF) != 0xFFFF) {
                clear = 0;
            }
            if (fn_800F06F4(0, pPlayer->mpState, 26, 0xFFFF) != 0xFFFF) {
                clear = 0;
            }
        }
        if (clear || fn_801783AC(13) || fn_801783AC(1)) {
            fn_8009D8CC(5);
        }
        Object_80039F5C *pCarrier = fn_80137B40();
        int special = 0;
        if (pCarrier) {
            special = pCarrier->mpState->mId == 16;
        }
        if (fn_8011F1CC() && fn_801783AC(0) && !fn_801783AC(13) && !fn_801783AC(1) &&
            !fn_801783AC(20) && !p->mUnknown4 && !special) {
            fn_80178370();
            fn_8017D7C4(lbl_803EB2BC);
        } else if (fn_80178308() != fn_80178348()) {
            fn_80178370();
        } else if (fn_8009D990(5) == 0 && !p->mUnknown4) {
            fn_80178370();
            fn_8017D7C4(lbl_803EB2C0);
        }
    }
}

void fn_8014C4C0(void *p, float dt)
{
    fn_801486A8();
    fn_800BFB88(p, dt);
    fn_801487C0(0, 4);
    fn_801487C0(1, 4);
    fn_8009D964(5, 5);
}

void fn_8014C528(void *p)
{
    fn_800BC5DC(p);
    fn_80178E88(5.0f);
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 3.0f, 0.0f);
    fn_80178A20(fn_80178A2C());
    fn_8009D964(5, 5);
    lbl_803EB2D0 = 1;
    lbl_803EB2D1 = 0;
    fn_80157514();
}

void fn_8014C5AC(void *p, float dt)
{
    if (fn_80054568()) {
        if (!lbl_803EB2D1 && fn_800C1E40() == 0) {
            fn_80218FC4(lbl_803EB688, 3, 8, 0, 0);
            lbl_803EB2D1 = 1;
        }
        fn_800BCB18(p, dt);
    }
}
}
