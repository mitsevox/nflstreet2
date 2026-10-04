#include <string.h>
#include "game/Entry_80219044.h"
#include "game/cu_8017DD68.h"
#include "game/fn_8021D7B8.h"

/* Only +8 is read here. */
struct Object_8017E46C {
    char mUnknown0[8];
    unsigned char mUnknown8;
};

extern "C" {
extern void *lbl_803EB688;
extern const float lbl_803ED6A4;
extern const float lbl_803ED6A8;

int fn_800A83E0(int a);
unsigned char fn_800C1E48(void);
int fn_80162E40(int a);
int fn_80188030(int a);

unsigned char fn_8017E608(int index);
unsigned char fn_8017E614(int index);
int fn_8017E570(int key, unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue);
}

static unsigned char lbl_803EB48C[4] = { 0 };
static unsigned char lbl_803EB490[4] = { 0 };

static Entry_80219044 lbl_80362598[2];
static char lbl_803625B0[2][32];
static Entry_80219044 lbl_803625F0[6];
static char lbl_80362638[6][32];
static Entry_80219044 lbl_803626F8[6];
static char lbl_80362740[6][32];
static Entry_80219044 lbl_80362800[6];
static char lbl_80362848[6][32];
static Entry_80219044 lbl_80362908;
static char lbl_80362914[80];

static const int lbl_802A57C4[4] = { 0, 1, 7, 3 };

extern "C" void fn_8017DD68(int index)
{
    unsigned char on = 1;
    Arg_8021D7B8 args[2];

    if (!fn_8017E608(index)) {
        lbl_803EB48C[index] = on;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 1;
        fn_8021D7B8(lbl_803EB688, 0x80000031, 2, args);
    }
}

extern "C" void fn_8017DDDC(int index)
{
    Arg_8021D7B8 args[2];

    if (fn_8017E608(index)) {
        lbl_803EB48C[index] = 0;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 0;
        fn_8021D7B8(lbl_803EB688, 0x80000031, 2, args);
    }
}

extern "C" void fn_8017DE54(int a, int b, float t, int direct)
{
    Arg_8021D7B8 args[3];
    float first;
    float second;

    args[0].i = a;
    if (t <= lbl_803ED6A4) {
        first = t / lbl_803ED6A4;
        second = 0.0f;
    } else {
        first = 1.0f;
        second = (t - lbl_803ED6A4) / (lbl_803ED6A8 - lbl_803ED6A4);
    }

    args[1].f = first;
    if (direct) {
        args[2].i = b;
        fn_8021D7B8(lbl_803EB688, 0x8000002F, 3, args);
    } else {
        args[2].i = fn_800A83E0(a);
        fn_8021D7B8(lbl_803EB688, 0x80000012, 3, args);
    }

    args[1].f = second;
    if (direct) {
        args[2].i = b;
        fn_8021D7B8(lbl_803EB688, 0x80000069, 3, args);
    } else {
        args[2].i = fn_800A83E0(a);
        fn_8021D7B8(lbl_803EB688, 0x80000068, 3, args);
    }
}

extern "C" void fn_8017DF6C(int a, int b)
{
    Arg_8021D7B8 args[2];

    args[0].i = a;
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000006A, 2, args);
}

extern "C" void fn_8017DFA8(int index)
{
    unsigned char on = 1;
    Arg_8021D7B8 args[2];

    if (!fn_8017E614(index)) {
        lbl_803EB490[index] = on;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 1;
        fn_8021D7B8(lbl_803EB688, 0x8000003D, 2, args);
    }
}

extern "C" void fn_8017E01C(int index)
{
    Arg_8021D7B8 args[2];

    if (fn_8017E614(index)) {
        lbl_803EB490[index] = 0;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 0;
        fn_8021D7B8(lbl_803EB688, 0x8000003D, 2, args);
    }
}

extern "C" void fn_8017E094(int a)
{
    Arg_8021D7B8 args[1];

    args[0].i = a;
    fn_8021D7B8(lbl_803EB688, 0x80000076, 1, args);
}

extern "C" void fn_8017E0CC(const char *pText0, const char *pText1)
{
    Arg_8021D7B8 args[2];

    strncpy(lbl_803625B0[0], pText0, 32);
    lbl_80362598[0].mLength = strlen(pText0) + 1;
    lbl_80362598[0].mpText = lbl_803625B0[0];
    args[0].p = &lbl_80362598[0];
    strncpy(lbl_803625B0[1], pText1, 32);
    lbl_80362598[1].mLength = strlen(pText1) + 1;
    lbl_80362598[1].mpText = lbl_803625B0[1];
    args[1].p = &lbl_80362598[1];
    fn_8021D7B8(lbl_803EB688, 0x80000077, 2, args);
}

extern "C" void fn_8017E17C(int slot, const char *pText0, const char *pText1, const char *pText2, int key)
{
    Arg_8021D7B8 args[4];
    Arg_8021D7B8 colour[5];
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    strncpy(lbl_80362638[slot - 1], pText0, 32);
    strncpy(lbl_80362740[slot - 1], pText1, 32);
    strncpy(lbl_80362848[slot - 1], pText2, 32);
    lbl_803625F0[slot - 1].mLength = strlen(lbl_80362638[slot - 1]) + 1;
    lbl_803625F0[slot - 1].mpText = lbl_80362638[slot - 1];
    lbl_803626F8[slot - 1].mLength = strlen(lbl_80362740[slot - 1]) + 1;
    lbl_803626F8[slot - 1].mpText = lbl_80362740[slot - 1];
    lbl_80362800[slot - 1].mLength = strlen(lbl_80362848[slot - 1]) + 1;
    lbl_80362800[slot - 1].mpText = lbl_80362848[slot - 1];
    args[0].i = slot;
    args[1].p = &lbl_803625F0[slot - 1];
    args[2].p = &lbl_803626F8[slot - 1];
    args[3].p = &lbl_80362800[slot - 1];
    fn_8021D7B8(lbl_803EB688, 0x80000078, 4, args);

    colour[0].i = slot;
    if (fn_8017E570(key, &red, &green, &blue)) {
        colour[1].i = red;
        colour[2].i = green;
        colour[3].i = blue;
        colour[4].i = 0xFF;
    } else {
        colour[1].i = 0;
        colour[2].i = 0;
        colour[3].i = 0;
        colour[4].i = 0;
    }
    fn_8021D7B8(lbl_803EB688, 0x80000079, 5, colour);
}

extern "C" void fn_8017E328(int a, int b)
{
    Arg_8021D7B8 args[2];

    if (a == 0) {
        args[0].i = 0;
    } else {
        args[0].i = 1;
    }
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000006F, 2, args);
}

extern "C" void fn_8017E380(int a)
{
    Arg_8021D7B8 args[1];

    if (a == 0) {
        args[0].i = 0;
    } else {
        args[0].i = 1;
    }
    fn_8021D7B8(lbl_803EB688, 0x80000070, 1, args);
}

extern "C" void fn_8017E3CC(int a)
{
    Arg_8021D7B8 args[1];

    if (!fn_800C1E48()) {
        if (a == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000006B, 1, args);
    }
}

extern "C" void fn_8017E430(void)
{
    Arg_8021D7B8 args[1];

    args[0].i = 0;
    fn_8021D7B8(lbl_803EB688, 0x80000071, 1, args);
}

extern "C" void fn_8017E46C(Object_8017E46C *pObject, int a, const char *pText, int c, int d)
{
    Arg_8021D7B8 args[7];
    int red;
    int green;
    int blue;
    int rgb;

    strncpy(lbl_80362914, pText, 79);
    if (pObject != 0) {
        rgb = fn_80162E40(8);
        red = (rgb & 0xFF0000) >> 16;
        green = (rgb & 0xFF00) >> 8;
        blue = rgb & 0xFF;
        if (pObject->mUnknown8 != 0xFF) {
            int index = fn_80188030(pObject->mUnknown8);
            if (index != -1) {
                rgb = fn_80162E40(lbl_802A57C4[index]);
                red = (rgb & 0xFF0000) >> 16;
                green = (rgb & 0xFF00) >> 8;
                blue = rgb & 0xFF;
            }
        }
    } else {
        red = 30;
        green = 150;
        blue = 200;
    }
    args[0].i = a;
    args[1].p = &lbl_80362908;
    lbl_80362908.mpText = lbl_80362914;
    lbl_80362908.mLength = strlen(lbl_80362914);
    args[2].i = c;
    args[3].i = d;
    args[4].i = red;
    args[5].i = green;
    args[6].i = blue;
    fn_8021D7B8(lbl_803EB688, 0x8000007D, 7, args);
}

extern "C" int fn_8017E570(int key, unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue)
{
    int found = 0;
    int rgb;

    *pRed = 0;
    *pGreen = 0;
    *pBlue = 0;
    if (key == 0xFE) {
        found = 1;
        rgb = fn_80162E40(8);
        *pRed = (rgb & 0xFF0000) >> 16;
        *pGreen = (rgb & 0xFF00) >> 8;
        *pBlue = rgb & 0xFF;
    } else if (key != 0xFF) {
        int index = fn_80188030(key);
        if (index != -1) {
            found = 1;
            rgb = fn_80162E40(lbl_802A57C4[index]);
            *pRed = (rgb & 0xFF0000) >> 16;
            *pGreen = (rgb & 0xFF00) >> 8;
            *pBlue = rgb & 0xFF;
        }
    }
    return found;
}

extern "C" unsigned char fn_8017E608(int index)
{
    return lbl_803EB48C[index];
}

extern "C" unsigned char fn_8017E614(int index)
{
    return lbl_803EB490[index];
}

extern "C" void fn_8017E620(int a, int b)
{
    Arg_8021D7B8 args[2];

    args[0].i = a;
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
}
