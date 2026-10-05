#include "game/cu_80067C10.h"
#include "game/fn_8007F828.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801F40F4.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/Object_80039F5C.h"

/* Block passed to fn_801F5B30; its first word holds fn_80073CB0. */
struct Params_802D63DC {
    int (*mpUnknown0)(struct Record_80073CB0 *);
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
};

/* Record passed to fn_80073CB0. */
struct Record_80073CB0 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[4];
    unsigned short mUnknownC;
    char mUnknownE[2];
    int mUnknown10;
};

struct Event_80073C24 {
    unsigned short mId;
    char mUnknown2[1];
    unsigned char mUnknown3;
};

struct Slot_8030AAB8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

struct State_8030AAA8 {
    int mUnknown0;
    void *mpUnknown4;
    void *mpUnknown8;
    int mUnknownC;
    Slot_8030AAB8 mSlots[3];
};

extern "C" {
extern char lbl_802EBE04[];

int fn_8006D65C(int a);
void fn_8006D684(int idx, unsigned char percent);
void fn_8006D6F4(int a, int b, int c);
void fn_8006D758(int a, Vector_80039F5C *pPos);
void fn_8006EA04(int a, unsigned char b);
void fn_8006ECB4(Record_80067CA8 *pRecord);
void fn_8006F0C8(int a);
int fn_800737B8(void);
unsigned char fn_800737C0(void);
int fn_80074E00(void);
int fn_80074E98(void);
int fn_80074F30(void);
int fn_80075060(void);
int fn_800750F8(void);
int fn_80075190(void);
int fn_80076D54(void);
int fn_80076D64(void);
int fn_80076D74(void);
int fn_80076D84(void);
int fn_80076D94(void);
int fn_80076DA4(void);
int fn_80076F40(int index);
void fn_801AF364(int a);
void *fn_801EECD0(void *pData, int a, int b, int c);
void fn_801F4638(int handle);
void fn_801F46F8(int handle, int a);
void fn_801F4AB0(int a, int b);
void fn_801F5B30(Params_802D63DC *pParams);
void fn_801F5C34(void);
void fn_801F5C6C(void *a, int b, void *c, int d);
void fn_801F5C94(void *pData, int a, int b);
void fn_801F5CCC(int (*pA)(void), void (*pB)(void));
void fn_801F5CEC(int (*pFunc)(Event_80073C24 *));
void fn_801F5D0C(void);

int fn_80073CB0(Record_80073CB0 *pRecord);
int fn_80074490(int side);
int fn_800745BC(int side);
void fn_80074320(unsigned char value);
void fn_80074328(int index, int value);
int fn_80074340(int index);
int fn_800744C8(int index);
int fn_800745D4(unsigned int index);
}

static unsigned char lbl_803EA720 = 0;
static unsigned char lbl_803EA721 = 1;
static unsigned char lbl_803EA722 = 0;
static unsigned char lbl_803EA723 = 1;
static int lbl_803EA724 = 0;
static unsigned char lbl_803EA728 = 1;
static int lbl_803EA72C = 0;
static int lbl_803EA730 = 0;
static int lbl_803EA734 = 0;
static int lbl_803EA738 = 0;

static int lbl_803EC84C;

static State_8030AAA8 lbl_8030AAA8;
static unsigned short lbl_8030AADC[386];

static Params_802D63DC lbl_802D63DC = { fn_80073CB0, 0, 24000, 16, 1, 4084, 0, 0, 0 };

extern "C" void fn_80073830(void *a, int b, void *c, int d)
{
    fn_801F5C6C(a, b, c, d);
}

extern "C" int fn_80073850(int side, unsigned int id)
{
    int result;

    switch (id) {
    case 0x201C:
    case 0x401C:
        result = fn_80074E00();
        break;
    case 0x201D:
    case 0x401D:
        result = fn_80074F30();
        break;
    case 0x2006:
    case 0x4006:
        result = fn_80076D64();
        break;
    case 0x2014:
    case 0x2019:
    case 0x4014:
    case 0x4019:
        result = fn_80074490(side);
        break;
    case 0x2020:
    case 0x4020:
        result = fn_80075060();
        break;
    case 0x2021:
    case 0x4021:
        result = fn_800750F8();
        break;
    case 0x2022:
    case 0x4022:
        result = fn_80075190();
        break;
    case 0x2004:
    case 0x4004:
        result = fn_80074E98();
        break;
    case 0x2005:
    case 0x4005:
        result = fn_80076D74();
        break;
    case 0x2007:
    case 0x4007:
        result = fn_80076D84();
        break;
    case 0x2008:
    case 0x4008:
        result = fn_80076DA4();
        if (result != 0) {
            break;
        }
        result = fn_800745BC(side);
        break;
    case 0x200F:
    case 0x2010:
    case 0x2013:
    case 0x2015:
    case 0x400F:
    case 0x4010:
    case 0x4013:
    case 0x4015:
        result = fn_80076D54();
        if (result != 0) {
            break;
        }
        result = fn_800745BC(side);
        break;
    case 0x2017:
    case 0x4017:
        result = fn_80076D94();
        if (result != 0) {
            break;
        }
        result = fn_800745BC(side);
        break;
    case 0x2002:
    case 0x2003:
    case 0x2009:
    case 0x200B:
    case 0x200C:
    case 0x2012:
    case 0x2016:
    case 0x2018:
    case 0x201A:
    case 0x201B:
    case 0x2023:
    case 0x2024:
    case 0x2025:
    case 0x2026:
    case 0x2027:
    case 0x2028:
    case 0x2029:
    case 0x202A:
    case 0x202B:
    case 0x202C:
    case 0x202D:
    case 0x202E:
    case 0x4002:
    case 0x4003:
    case 0x4009:
    case 0x400B:
    case 0x400C:
    case 0x4012:
    case 0x4016:
    case 0x4018:
    case 0x401A:
    case 0x401B:
    case 0x4023:
    case 0x4024:
    case 0x4025:
    case 0x4026:
    case 0x4027:
    case 0x4028:
    case 0x4029:
    case 0x402A:
    case 0x402B:
    case 0x402C:
    case 0x402D:
    case 0x402E:
        result = fn_800745BC(side);
        break;
    case 0x201E:
    case 0x401E:
        if (fn_800AD9B4() == 1) {
            if (id == 0x401E) {
                result = fn_80076F40(0);
            } else {
                result = fn_80076F40(1);
            }
        } else {
            result = fn_800737B8();
        }
        break;
    default:
        result = fn_800745BC(side);
        break;
    }
    return result;
}

extern "C" void fn_80073B64(unsigned int index, int id)
{
    int side;
    int value;

    if (index <= 1) {
        side = 1;
        if (index == 1) {
            side = 0;
        }
        if (id != lbl_803EA724) {
            value = fn_80073850(side, id);
            if (value == 0) {
                value = fn_800745BC(side);
            }
            fn_80074328(index, value);
            lbl_803EA724 = id;
        }
        if (id == 0x201E || id == 0x401E) {
            fn_80074320(0);
        } else {
            fn_80074320(1);
        }
    }
}

extern "C" int fn_80073C04(int id)
{
    int result = 0;

    if (id == 0x201E || id == 0x401E) {
        result = -1;
    }
    return result;
}

extern "C" int fn_80073C24(Event_80073C24 *pEvent)
{
    int current;
    int side;

    if (pEvent->mUnknown3 != 3) {
        current = fn_800737B8();
        side = 1;
        if (pEvent->mUnknown3 == 1) {
            side = 0;
        }
        if (fn_800737C0() != 0 || current == fn_80073850(side, pEvent->mId)) {
            if (pEvent->mId != 0x401E && pEvent->mId != 0x201E) {
                return 0;
            }
        }
    }
    return 1;
}

extern "C" int fn_80073CB0(Record_80073CB0 *pRecord)
{
    Pair_80073CB0 pair;
    int handle;
    int value;

    fn_80073B64((unsigned char)pRecord->mUnknown10, pRecord->mUnknownC);
    pair.mpUnknown0 = lbl_8030AAA8.mpUnknown4;
    if (pRecord->mUnknown0 >= lbl_803EC84C) {
        pair.mUnknown4 = lbl_8030AADC[pRecord->mUnknown0 - lbl_803EC84C];
    } else {
        pair.mUnknown4 = lbl_8030AAA8.mUnknownC + pRecord->mUnknown0;
    }
    handle = fn_800745D4(pRecord->mUnknown10);
    value = fn_80073C04(pRecord->mUnknownC);
    lbl_8030AAA8.mSlots[pRecord->mUnknown10].mUnknown8 = value;
    lbl_8030AAA8.mSlots[pRecord->mUnknown10].mUnknown4 = fn_801F4580(handle, &pair, value, pRecord->mUnknown4);
    return lbl_8030AAA8.mSlots[pRecord->mUnknown10].mUnknown4;
}

extern "C" int fn_80073D9C(void)
{
    return 0;
}

extern "C" void fn_80073DA4(void)
{
}

extern "C" void fn_80073DA8(Params_802D63DC *pParams, int unused)
{
    int i;

    lbl_803EA722 = fn_8017F584() == 11;
    lbl_803EA728 = 1;
    lbl_8030AAA8.mpUnknown4 = fn_801EEB44(lbl_802EBE04, 44);
    lbl_8030AAA8.mpUnknown8 = fn_801EECD0(lbl_8030AAA8.mpUnknown4, 0, 1, 1);
    fn_801F5B30(pParams);
    fn_801F5CEC(fn_80073C24);
    lbl_8030AAA8.mUnknown0 = pParams->mUnknown14;
    fn_801F5C94(lbl_8030AAA8.mpUnknown4, 1, 0);
    fn_801F5C94(lbl_8030AAA8.mpUnknown4, 2, 1);
    fn_801F5C94(lbl_8030AAA8.mpUnknown4, 3, 2);
    for (i = 0; i < 895; i++) {
        fn_80073830(lbl_8030AAA8.mpUnknown8, i, lbl_8030AAA8.mpUnknown4, i + 4);
    }
    lbl_803EC84C = i;
    lbl_8030AAA8.mUnknownC = 4;
    for (i = 0; i < 3; i++) {
        lbl_8030AAA8.mSlots[i].mUnknown0 = 0;
        lbl_8030AAA8.mSlots[i].mUnknown4 = -1;
        lbl_8030AAA8.mSlots[i].mUnknown8 = 0;
    }
    lbl_803EA72C = 0;
    lbl_803EA730 = 0;
    lbl_803EA734 = 0;
    lbl_803EA738 = 0;
}

extern "C" void fn_80073EE4(void)
{
    lbl_802D63DC.mUnknown4 = (lbl_802D63DC.mUnknown4 + 1) & 0x7FFFFFFF;
    fn_80073DA8(&lbl_802D63DC, 1);
    fn_801F5CCC(fn_80073D9C, fn_80073DA4);
    fn_8006F0C8(127);
    fn_80067EC8(fn_8006ECB4);
    lbl_803EA720 = 1;
    lbl_803EA721 = 1;
}

extern "C" void fn_80073F58(void)
{
}

extern "C" void fn_80073F5C(void)
{
    Status_801F4834 status;
    Vector_80039F5C pos;
    int handle;
    int first;
    int second;
    int id;

    if (lbl_803EA721 == 0) {
        return;
    }
    first = 0;
    second = 0;
    if (fn_800AD9B4() == 1) {
        first = fn_80076F40(0);
        second = fn_80076F40(1);
    } else if (fn_800737C0() != 0) {
        id = fn_800737B8();
        if (id != 0) {
            if (((id >> 8) & 0xFF) == 0) {
                second = id;
                first = 0;
            } else {
                first = id;
            }
        }
    }
    fn_8006EA04(3, fn_8007F828(3) * 10);
    if (first != 0) {
        fn_8006D684(4, 95);
    }
    if (second != 0) {
        fn_8006D684(5, 95);
    }

    fn_801F4834(fn_800745D4(0), &status);
    fn_8006D758(4, 0);
    if (lbl_803EA728 != 0) {
        handle = fn_80074340(0);
        if (handle != 0) {
            fn_8009BF5C(fn_8009BCE8(&handle), 13, &pos, 0);
            fn_8006D758(4, &pos);
        }
    }
    fn_8006D6F4(4, 0, 127);
    if (status.mUnknown0 == 0) {
        fn_801AF364(0);
    }

    fn_801F4834(fn_800745D4(1), &status);
    fn_8006D758(5, 0);
    if (lbl_803EA728 != 0) {
        handle = fn_80074340(1);
        if (handle != 0) {
            fn_8009BF5C(fn_8009BCE8(&handle), 13, &pos, 0);
            fn_8006D758(5, &pos);
        }
    }
    fn_8006D6F4(5, 0, 127);
    if (status.mUnknown0 == 0) {
        fn_801AF364(1);
    }

    if (lbl_803EA722 != 0) {
        fn_801F4834(fn_800745D4(2), &status);
        fn_8006D758(6, 0);
        fn_8006D6F4(6, 0, 127);
        if (status.mUnknown0 == 0) {
            fn_801AF364(2);
        }
    }
}

extern "C" void fn_8007418C(void)
{
}

extern "C" void fn_80074190(void)
{
    lbl_803EA720 = 0;
    lbl_803EA722 = 0;
    fn_80067EF0(fn_8006ECB4);
    fn_801F5D0C();
    fn_801F5C34();
    if (lbl_8030AAA8.mpUnknown8 != 0) {
        fn_801EEFAC(lbl_8030AAA8.mpUnknown8);
        lbl_8030AAA8.mpUnknown8 = 0;
    }
    if (lbl_8030AAA8.mpUnknown4 != 0) {
        fn_801EEFAC(lbl_8030AAA8.mpUnknown4);
        lbl_8030AAA8.mpUnknown4 = 0;
    }
}

extern "C" void fn_8007420C(int index)
{
    if (fn_800745D4(index) != 0) {
        fn_801F46F8(fn_800745D4(index), 0);
    }
}

extern "C" void fn_80074250(int index)
{
    Info_801F40F4 info;

    fn_801F40F4(&info);
    if (fn_800745D4(index) != 0) {
        fn_801F46F8(fn_800745D4(index), info.mUnknownC);
    }
}

extern "C" void fn_800742A0(int index)
{
    Status_801F4834 status;

    if (fn_800745D4(index) != 0) {
        fn_801F4834(fn_800745D4(index), &status);
        if (status.mUnknown0 > 0) {
            lbl_8030AAA8.mSlots[index].mUnknown8 = 0;
            fn_801F4AB0(status.mUnknown4, 0);
            lbl_8030AAA8.mSlots[index].mUnknown4 = -1;
        }
    }
}

extern "C" void fn_80074320(unsigned char value)
{
    lbl_803EA728 = value;
}

extern "C" void fn_80074328(int index, int value)
{
    lbl_8030AAA8.mSlots[index].mUnknown0 = value;
}

extern "C" int fn_80074340(int index)
{
    return lbl_8030AAA8.mSlots[index].mUnknown0;
}

extern "C" void fn_80074358(int index)
{
    if (fn_800745D4(index) != 0) {
        fn_801F4638(fn_800745D4(index));
    }
}

extern "C" void fn_80074398(int handle)
{
    Vector_80039F5C delta;
    Object_80039F5C *pObject;
    Object_80039F5C *pOther;
    int *pNearest;
    int team;
    unsigned short i;
    unsigned int count;
    float best;
    float distance;

    pObject = fn_8009BCE8(&handle);
    if (pObject != 0) {
        team = ((handle >> 8) & 0xFF) ^ 1;
        pNearest = &lbl_803EA72C;
        if (team == 0) {
            pNearest = &lbl_803EA730;
        }
        pOther = fn_80039F5C(team, 0);
        *pNearest = pOther->mId;
        fn_802276B4(&delta, &pObject->mMotion.mPos, &pOther->mMotion.mPos);
        best = fn_802270D4(&delta);
        count = fn_80178D18(team);
        for (i = 1; i < count; i++) {
            pOther = fn_80039F5C(team, i);
            fn_802276B4(&delta, &pObject->mMotion.mPos, &pOther->mMotion.mPos);
            distance = fn_802270D4(&delta);
            if (distance < best) {
                best = distance;
                *pNearest = pOther->mId;
            }
        }
    }
}

extern "C" int fn_80074490(int side)
{
    return side ? lbl_803EA72C : lbl_803EA730;
}

extern "C" unsigned char fn_800744A8(void)
{
    return lbl_803EA721;
}

extern "C" void fn_800744B0(unsigned char value)
{
    lbl_803EA721 = value;
}

extern "C" unsigned char fn_800744B8(void)
{
    return lbl_803EA723;
}

extern "C" void fn_800744C0(unsigned char value)
{
    lbl_803EA723 = value;
}

extern "C" int fn_800744C8(int index)
{
    Status_801F4834 status;

    fn_801F4834(fn_800745D4(index), &status);
    return status.mUnknown0 == 0;
}

extern "C" int fn_800744FC(void)
{
    unsigned int i;

    for (i = 0; i < 3; i++) {
        if (fn_800744C8(i) == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" void fn_8007454C(int side)
{
    int stream = fn_80178D70(side);

    if (side == 0) {
        lbl_803EA738 = 1 | (fn_802372EC(1, stream) & 0xFF) << 16;
    } else {
        lbl_803EA734 = side << 8 | 1 | (fn_802372EC(1, stream) & 0xFF) << 16;
    }
}

extern "C" int fn_800745BC(int side)
{
    return side ? lbl_803EA734 : lbl_803EA738;
}

extern "C" int fn_800745D4(unsigned int index)
{
    int result;

    switch (index) {
    case 0:
        result = fn_8006D65C(4);
        break;
    case 1:
        result = fn_8006D65C(5);
        break;
    case 2:
        result = fn_8006D65C(6);
        break;
    default:
        result = fn_8006D65C(4);
        break;
    }
    return result;
}

extern "C" int fn_80074638(void)
{
    int result = 1;

    if (lbl_803EA721 != 0 && fn_800744C8(2) == 0) {
        result = 0;
    }
    return result;
}
