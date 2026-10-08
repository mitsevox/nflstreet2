#include "game/cu_80026BB0.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/cu_8017F264.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80096A58.h"
#include "game/fn_80218FC4.h"
#include "game/fn_802372EC.h"
#include "game/InGame.h"
#include "game/Class_80297CE8.h"

typedef void (*Callback_8030A4A8)(int value);

/* Camera returned by fn_8013FA04 (defined in src/game/cu_8013F460.cpp). */
struct Camera_8013F738;

/* Object at lbl_803EABA4 (declared in include/game/Class_80297CE8.h). */
class Class_80297CE8;

/* mId is also read as one word, compared with 0x10002, 0x30001 and 0x30016;
   mArgs holds mArgCount words for fn_80218FC4. */
struct State_8030A478 {
    int mUnknown0;
    int mState;
    union {
        int mId;
        struct {
            unsigned short mHigh;
            unsigned short mLow;
        } mPair;
    };
    int mArgCount;
    int mArgs[4];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    int mUnknown44;
    Callback_8030A4A8 mCallbacks[1];
    void *mHandlers[20];
    unsigned char mUnknown132;
    int mUnknown136;
    int mUnknown140;
    int mUnknown144;
};

extern "C" {
extern void *lbl_803EA368;
extern void *lbl_803EB688;

void fn_8002C9A8(void *p, int a, int b);
void fn_8002CA74(void *p, int a, int b);
int fn_8002D060(void *p);
int fn_8002D0AC(void *p);
void fn_8002D198(void *p);
int fn_8002D228(void *p);
int fn_80059004(void);
int fn_8005900C(void);
void fn_80065834(void);
void fn_8006F824(int a);
void fn_800719D4(void);
void fn_8007420C(int index);
void fn_80074250(int index);
void fn_800744B0(unsigned char value);
void fn_80094DF0(void);
void fn_8009B924(void);
void fn_8009BA10(int a);
unsigned char fn_8009BA94(void);
int fn_800A3444(void);
int fn_800A8444(int a);
int fn_800A8488(int a);
void fn_800ABD80(void);
void fn_800AD910(int a, float b);
void fn_800B22E0(void);
void fn_800B43C8(void);
void fn_800B4408(void);
int fn_800B81A4(void);
void fn_800BA5B0(void);
void fn_800BF658(int a);
void fn_800BF6CC(int a);
int fn_800BF718(int a);
void fn_800C0330(void *p);
void fn_800C1CA0(void);
int fn_800C1E40(void);
int fn_8013C678(Camera_8013F738 *pCamera);
void fn_8013C6F0(Camera_8013F738 *pCamera);
void fn_8013F97C(int a);
int fn_8013F9F8(void);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013FA24(void);
void fn_8013FA8C(int a);
void fn_8013FB44(void);
void fn_80162780(int a, int b);
unsigned char fn_8016278C(void);
void fn_80178370(void);
void fn_8017CFB4(int a);
void fn_8017D8D4(void);
void fn_8017D9D8(int a);
void fn_8017DA9C(int a);
void fn_8017EFB0(void);
unsigned char fn_8017F2EC(unsigned char value);
void fn_80188014(int a);
void fn_8018A4B4(int a);
void fn_8018A798(int value);
void fn_8018A7A0(void);
void fn_8018AFD8(unsigned char value);
void fn_80194CBC(void);
void fn_80194D20(void);
void fn_80194D70(void);
void fn_80194DB8(void);
void fn_80194F1C(int a);
unsigned char fn_80194F24(void);
int fn_8019626C(void);
void fn_801F5D0C(void);
void fn_802195E4(void *p, unsigned short a, unsigned short b);
}

static Callback_803EA638 *lbl_803EA638 = 0;
static unsigned char lbl_803EA63C = 0;
static unsigned char lbl_803EA63D = 0;
static unsigned char lbl_803EA63E = 0;
static unsigned char lbl_803EA63F = 0;
static int lbl_803EA640 = -1;
static unsigned char lbl_803EA644 = 0;
static unsigned char lbl_803EA645 = 1;
static unsigned char lbl_803EA646 = 0;
static unsigned char lbl_803EA647 = 0;
static unsigned char lbl_803EA648 = 0;
static unsigned char lbl_803EA649 = 0;
static unsigned char lbl_803EA64A = 0;
static unsigned char lbl_803EA64B = 0;
static unsigned char lbl_803EA64C = 0;
static int lbl_803EA650 = 0;
static State_8030A478 lbl_8030A478;

extern "C" {

void fn_80064864(void)
{
    fn_8006F824(0);
    fn_800719D4();
    fn_801F5D0C();
    fn_8007420C(0);
    fn_8007420C(1);
    fn_8007420C(2);
    fn_800744B0(0);
    fn_80067D4C(0x71, 0);
    lbl_803EA64A = 1;
}

void fn_800648C4(void)
{
    fn_800744B0(1);
    fn_80074250(0);
    fn_80074250(1);
    fn_80074250(2);
    lbl_803EA64A = 0;
}

void fn_80064908(void)
{
    lbl_8030A478.mPair.mHigh = 0xFFFF;
    lbl_8030A478.mPair.mLow = 0xFFFF;
    lbl_8030A478.mState = 0;
    lbl_8030A478.mUnknown0 = fn_800AD9B4();
    if (lbl_8030A478.mUnknown132) {
        fn_80027230(lbl_8030A478.mHandlers);
        fn_80027358(-1);
        lbl_8030A478.mUnknown132 = 0;
    }
}

int fn_80064970(void)
{
    return lbl_8030A478.mState > 0;
}

void fn_8006498C(void)
{
    fn_80065834();
}

void fn_800649AC(void)
{
    Params_80096A58 params;

    lbl_8030A478.mUnknown136 = -1;
    if (fn_800AD9B4() == 1) {
        return;
    }
    fn_8013FB44();
    fn_800B43C8();
    lbl_8030A478.mUnknown136 = -1;
    lbl_8030A478.mUnknown140 = fn_8013F9F8();
    lbl_8030A478.mUnknown144 = fn_8013C678(fn_8013FA04(5));
    fn_801C1F94(&params, 0, sizeof(params));
    params.mUnknown40 = 0xFFFF;
    params.mUnknown42 = 0xFFFF;
    switch (fn_800A3444()) {
    case 0:
        params.mUnknown0 = 13;
        break;
    case 2:
        params.mUnknown0 = 1;
        break;
    case 3:
        params.mUnknown0 = 25;
        break;
    case 1:
        params.mUnknown0 = 19;
        break;
    case 4:
        params.mUnknown0 = 7;
        break;
    case 5:
        params.mUnknown0 = 32;
        break;
    case 6:
        params.mUnknown0 = 35;
        break;
    case 7:
        params.mUnknown0 = 29;
        break;
    case 8:
        params.mUnknown0 = 10;
        break;
    case 10:
        params.mUnknown0 = 16;
        break;
    case 11:
        params.mUnknown0 = 22;
        break;
    case 9:
    default:
        params.mUnknown0 = 4;
        break;
    }
    params.mUnknown28 = fn_802372EC(1, 3);
    params.mUnknown20 = 2;
    params.mUnknown24 = 0;
    if (lbl_8030A478.mPair.mHigh != 7 && fn_8019626C() != 5 && !fn_8002D0AC(lbl_803EA368)
        && fn_800AD9B4() != 7) {
        params.mUnknown12 |= 2;
    }
    params.mUnknown12 |= 0x10;
    params.mUnknown32 = 60.0f;
    lbl_8030A478.mUnknown136 = fn_80096A58(&params);
}

int fn_80064B94(void)
{
    int result;

    if (lbl_8030A478.mUnknown136 != -1 && fn_800AD9B4() != 1) {
        result = fn_80096B1C(lbl_8030A478.mUnknown136);
        if (result) {
            fn_8013FA24();
        }
    } else {
        result = 0;
    }
    return result;
}

int fn_80064BF8(void)
{
    if (!fn_80028310() && fn_800AD9B4() != 1) {
        if ((fn_800C1E40() && fn_800AD9B4() == 7) || fn_800AD9B4() != 7) {
            if (lbl_8030A478.mUnknown136 != -1) {
                fn_80096D14(lbl_8030A478.mUnknown136);
                lbl_8030A478.mUnknown136 = -1;
            }
            fn_80162780(lbl_803EA646, lbl_803EA646);
            fn_8013F97C(lbl_8030A478.mUnknown140);
            fn_8013FA8C(lbl_8030A478.mUnknown144);
            fn_8013C6F0(fn_8013FA04(lbl_8030A478.mUnknown140));
        }
        if (fn_800AD9B4() == 5 && !fn_80059004() && !fn_8005900C()) {
            fn_800B4408();
        }
    }
    return 0;
}

void fn_80064CCC(void) {}

void fn_80064CD0(void) {}

void fn_80064CD4(void)
{
    unsigned int i;
    int enabled = 1;

    if (lbl_803EA638 && !fn_80028310()) {
        for (i = 0; i < 1; i++) {
            if (lbl_803EA638[i]) {
                unsigned short a;
                unsigned short b;
                int c;

                if (lbl_803EA638[i](&a, &b, &c) && lbl_8030A478.mUnknown44 == 0) {
                    fn_80064EFC(a, b, c);
                }
            }
        }
        int value = fn_800B81A4();
        if (value != 0xFF && lbl_8030A478.mUnknown44 == 0 && enabled) {
            int args[2];

            args[0] = value;
            args[1] = 1;
            fn_80064F58(1, 2, value, 2, args, 0);
        }
    }
}

void fn_80064DC0(int index, Callback_803EA638 pCallback)
{
    lbl_803EA638[index] = pCallback;
}

void fn_80064DD0(int index)
{
    if (fn_80064970()) {
        fn_800652DC();
    }
    lbl_803EA638[index] = 0;
}

void fn_80064E18(void)
{
    int i;

    lbl_803EA638 = (Callback_803EA638 *)fn_801D2B7C(sizeof(Callback_803EA638), 0, 0);
    fn_801C1F94(lbl_803EA638, 0, sizeof(Callback_803EA638));
    lbl_8030A478.mUnknown132 = 0;
    fn_80064908();
    fn_8006498C();
    lbl_8030A478.mUnknown44 = 0;
    for (i = 0; i < 1; i++) {
        lbl_8030A478.mCallbacks[i] = 0;
    }
    lbl_803EA647 = 0;
    lbl_803EA648 = 0;
}

void fn_80064EA4(void)
{
    int i;

    if (lbl_803EA638) {
        for (i = 0; i < 1; i++) {
            fn_80064DD0(i);
        }
        fn_801D2BD0(lbl_803EA638);
    }
    lbl_803EA638 = 0;
    fn_80064908();
}

void fn_80064EFC(unsigned short a, unsigned short b, int c)
{
    if (a == 10 && b == 0) {
        int arg = 0;

        fn_80064F58(10, 0, c, 1, &arg, 0);
    } else {
        fn_80064F58(a, b, c, 0, 0, 0);
    }
}

void fn_80064F58(unsigned short a, unsigned short b, int c, unsigned int count, int *pArgs, int keep)
{
    int i;
    unsigned char j;

    for (i = 0; i < 1; i++) {
        if (lbl_8030A478.mCallbacks[i]) {
            lbl_8030A478.mCallbacks[i](1);
        }
    }
    lbl_8030A478.mPair.mHigh = a;
    lbl_8030A478.mPair.mLow = b;
    lbl_8030A478.mUnknown32 = c;
    lbl_8030A478.mArgCount = count;
    for (j = 0; j < count && j <= 3; j++) {
        lbl_8030A478.mArgs[j] = pArgs[j];
    }
    lbl_8030A478.mState = 1;
    lbl_803EA64B = 0;
    lbl_803EA64C = 0;
    fn_8018A4B4(c);
    fn_8018A798(c);
    fn_800C0330(lbl_803EABA4);
    lbl_803EA63E = fn_8017F2EC(0);
    lbl_803EA63C = fn_8017F2DC(2);
    lbl_8030A478.mUnknown0 = fn_800AD9B4();
    fn_800271D4(lbl_8030A478.mHandlers);
    lbl_8030A478.mUnknown132 = 1;
    fn_800271A4();
    if (!keep) {
        fn_800649AC();
        lbl_803EA646 = fn_8016278C();
    }
    lbl_803EA645 = 1;
    if (fn_8002D060(lbl_803EA368)) {
        fn_8002D198(lbl_803EA368);
    }
    fn_8002885C();
    lbl_803EA63F = fn_80194F24();
    fn_80194CBC();
    if (lbl_8030A478.mId == 0x10002 || lbl_8030A478.mId == 0x30001) {
        fn_80064864();
        fn_80194DB8();
        fn_80194D70();
    }
    if (lbl_8030A478.mUnknown0 == 2) {
        if (fn_800A8488(0) && !fn_800A8444(0)) {
            fn_8017DA9C(0);
        }
        if (fn_800A8488(1) && !fn_800A8444(1)) {
            fn_8017DA9C(1);
        }
    }
    lbl_803EA649 = fn_8009BA94();
    if (lbl_803EA649 == 1) {
        fn_8009BA10(0);
    }
    fn_8017D8D4();
    fn_8002C9A8(lbl_803EA368, 4, 0);
    fn_800655B8();
    lbl_803EA640 = c;
    fn_8018AFD8(1);
}

void fn_80065194(void)
{
    if (!fn_80064970() && fn_800655F8() && lbl_803EA650 == 0) {
        fn_80064CD4();
    }
    if (lbl_803EA650 != 0) {
        lbl_803EA650--;
    }
    if (fn_80064970()) {
        fn_8002C9A8(lbl_803EA368, 4, 0);
        switch (lbl_8030A478.mState) {
        case 1:
            fn_8017CFB4(7);
            fn_80218FC4(lbl_803EB688, lbl_8030A478.mPair.mHigh, lbl_8030A478.mPair.mLow,
                        lbl_8030A478.mArgCount, lbl_8030A478.mArgs);
            fn_802195E4(lbl_803EB688, lbl_8030A478.mPair.mHigh, lbl_8030A478.mPair.mLow);
            lbl_8030A478.mState = 2;
            break;
        case 2:
            if (lbl_8030A478.mId != 0x10002) {
                fn_80064B94();
            }
            break;
        case 3:
            fn_80064CD0();
            fn_800652DC();
            break;
        }
    }
}

void fn_800652A8(void)
{
    if (fn_80064970()) {
        lbl_8030A478.mState = 3;
    }
}

void fn_800652DC(void)
{
    int i;

    lbl_803EA640 = -1;
    fn_8018A7A0();
    fn_8018AFD8(0);
    fn_80064BF8();
    if (lbl_803EA647 == 1) {
        lbl_803EA647 = 0;
    }
    fn_800655D0();
    fn_80027230(lbl_8030A478.mHandlers);
    fn_80027358(-1);
    lbl_8030A478.mUnknown132 = 0;
    fn_800288B0();
    fn_80194DB8();
    fn_80194D20();
    fn_80194F1C(lbl_803EA63F);
    fn_8017EFB0();
    fn_800ABD80();
    fn_800B22E0();
    fn_80188014(0);
    if (fn_8006565C()) {
        fn_800648C4();
    }
    if (lbl_8030A478.mId == 0x30016) {
        fn_80067DB8(0x72, 0, lbl_803EA64B, 0, 0);
    }
    if (lbl_8030A478.mUnknown0 == 2) {
        if (fn_800A8488(0) && !fn_800A8444(0)) {
            fn_8017D9D8(0);
        }
        if (fn_800A8488(1) && !fn_800A8444(1)) {
            fn_8017D9D8(1);
        }
    }
    if (lbl_8030A478.mUnknown0 != fn_800AD9B4()) {
        fn_800AD910(lbl_8030A478.mUnknown0, 0.0f);
    }
    fn_80064908();
    fn_800BA5B0();
    fn_8002C9A8(lbl_803EA368, 5, 0);
    fn_8017F2EC(lbl_803EA63E);
    fn_8017F2DC(lbl_803EA63C);
    fn_80064CCC();
    if (fn_800BF718(1)) {
        int busy = fn_80028310() || lbl_803EA64B || lbl_803EA64C || lbl_803EA648;

        if (busy) {
            fn_800BF6CC(1);
        } else {
            fn_800BF658(1);
        }
    }
    for (i = 0; i < 1; i++) {
        if (lbl_8030A478.mCallbacks[i]) {
            lbl_8030A478.mCallbacks[i](0);
        }
    }
    if (lbl_803EA648) {
        fn_80178370();
        lbl_803EA648 = 0;
    }
    if (lbl_803EA649 == 1) {
        fn_8009BA10(1);
    }
    if (lbl_803EA64B) {
        fn_8002C9A8(lbl_803EA368, 3, 0);
        if (fn_8002D228(lbl_803EA368) && !fn_8002D060(lbl_803EA368)) {
            fn_8009B924();
            fn_80094DF0();
            fn_8002CA74(lbl_803EA368, 10, fn_80065650());
            fn_8002CA74(lbl_803EA368, 11, 0);
            fn_8002CA74(lbl_803EA368, 7, 0);
        }
    } else if (lbl_803EA64C) {
        fn_800C1CA0();
    }
}

void fn_800655B8(void)
{
    lbl_8030A478.mUnknown44++;
}

void fn_800655D0(void)
{
    lbl_8030A478.mUnknown44--;
}

void fn_800655E8(void)
{
    lbl_8030A478.mUnknown44 = 0;
}

int fn_800655F8(void)
{
    return lbl_8030A478.mUnknown44 == 0;
}

int fn_8006560C(void)
{
    return fn_80064970();
}

int fn_8006562C(void)
{
    return lbl_8030A478.mUnknown0;
}

void fn_80065638(void) {}

void fn_8006563C(void)
{
    lbl_803EA63C = 0;
    lbl_803EA63D = 0;
    lbl_803EA63E = 0;
}

int fn_80065650(void)
{
    return lbl_8030A478.mUnknown32;
}

unsigned char fn_8006565C(void)
{
    return lbl_803EA64A;
}

void fn_80065664(unsigned char value)
{
    if (fn_80064970()) {
        lbl_803EA64B = value;
    }
}

unsigned char fn_8006569C(void)
{
    return lbl_803EA64B;
}

void fn_800656A4(unsigned char value)
{
    lbl_803EA63F = value;
}

void fn_800656AC(unsigned char value)
{
    if (fn_80064970()) {
        lbl_803EA64C = value;
    }
}

void fn_800656E4(int value)
{
    lbl_803EA650 = value;
}

}
