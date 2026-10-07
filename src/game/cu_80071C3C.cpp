#include "game/Object_8007A334.h"
#include "game/Query_8008352C.h"
#include "game/SndgPathfinder.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_800AD9B4.h"

struct Text_800724F4 {
    int mUnknown0;
    unsigned int mUnknown4;
    char *mpUnknown8;
};

/* Allocation is 0x130 bytes; unaccessed words remain opaque. */
struct State_80071C3C {
    unsigned long long mUnknown0;
    unsigned long long mUnknown8;
    unsigned int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    char mUnknown1C[4];
    void *mpUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    Text_800724F4 mUnknown34[3];
    char mUnknown58[51];
    char mUnknown8B[51];
    char mUnknownBE[51];
    signed char mUnknownF1[40];
    char mUnknown119[3];
    int mUnknown11C;
    unsigned char mUnknown120;
    unsigned char mUnknown121;
    unsigned char mUnknown122;
    unsigned char mUnknown123;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
    unsigned char mUnknown127;
    unsigned char mUnknown128;
    unsigned char mUnknown129;
    unsigned char mUnknown12A;
    char mUnknown12B[5];
};

/* The calendar helper writes all twelve bytes, including its final word. */
struct Calendar_801F81F4 {
    char mUnknown0[12];
};

struct Info_801E1084 {
    int mUnknown0;
    char mUnknown4[44];
    int mUnknown30;
    char mUnknown34[4];
};

extern "C" {
extern void *lbl_803EB688;
extern void *lbl_803EB690;
extern char lbl_802EBF88[];
int fn_80027DF0(void);
int fn_801486A0(void);
void fn_8006CA84(int a);
void fn_8006DDB4(int a, int b, unsigned int c);
void fn_8006DEA8(int a, int b);
void fn_8006DEEC(int a);
void fn_8006DF2C(int a);
void fn_8006DF6C(int a);
void fn_8006DFA8(void (*callback)(int, int));
void fn_8006E010(void (*callback)(int, int));
void fn_8007B358(Object_8007A334 *p);
void fn_8007B3AC(Object_8007A334 *p);
void fn_8007B3CC(Object_8007A334 *p, int id, int *pResult);
void fn_8007B42C(Object_8007A334 *p, char *pBuffer, int size);
void fn_8007B460(Object_8007A334 *p, char *pBuffer, int size);
void fn_8007B494(Object_8007A334 *p, char *pBuffer, int size);
void fn_8008352C(Object_8007A334 *p, Query_8008352C *pQuery);
void fn_800835D0(Object_8007A334 *p);
void fn_80083644(Object_8007A334 *p);
int fn_800836A4(Object_8007A334 *p, int a, int b, int c);
int fn_800837B8(Object_8007A334 *p);
unsigned char fn_800837D8(Object_8007A334 *p);
int fn_80083804(Object_8007A334 *p);
int fn_8008382C(Object_8007A334 *p);
void fn_801B3084(int flags, const char *pName, int value);
unsigned int fn_801C3180(const char *pText);
void fn_801CE7D0(int a);
int fn_801E1084(int id, Info_801E1084 *pInfo);
void *fn_801EEB44(const char *pName, int flags);
void fn_801EEFAC(void *p);
int fn_801F3E28(void);
unsigned long long fn_801F7D34(Calendar_801F81F4 *p);
void fn_801F81F4(Calendar_801F81F4 *p);
void fn_80219650(void *p, unsigned short *a, unsigned short *b);

static unsigned int lbl_803EA700 = 100;
static State_80071C3C *lbl_803EA704 = 0;
static unsigned char lbl_803EA708 = 0;
static unsigned char lbl_803EA709 = 0;

void fn_80071C3C(int flags, int event);
void fn_80071EA8(int a, int b, int c);
int fn_80071EDC(int mode);
int fn_8007224C(int value);
void fn_80072298(void);
int fn_800723DC(void);
void fn_80072424(void);
void fn_800724F4(void);
void fn_800726B8(void);
void fn_8007272C(void);
void fn_80072890(void);
void fn_800728F8(void);
void fn_80072AA8(void);
unsigned char fn_80072ACC(void);
void fn_80072AD8(unsigned char value);
void fn_80072AEC(int mode);
void fn_80072B84(int a, int b, int c);
void fn_80072C54(unsigned int value);
void fn_80072C90(unsigned int delay, int wait);
void fn_80072D98(unsigned int delay);
unsigned char fn_80072E6C(void);
void fn_80072E84(void);
void fn_80072F04(void);
unsigned char fn_80072F84(void);
void fn_80072F90(void);
void fn_80073094(void);
void fn_80073144(int value, unsigned int duration);
void fn_800731D0(int draw);
void fn_80073210(int frames);
int fn_80073310(void);
void fn_80073328(int resume);

void fn_80071C3C(int flags, int event)
{
    if (flags & 0x1000000) {
        switch (event) {
        case 0x0: {
        case 0x7C:
        case 0xF8:
        case 0x174:
        case 0x1F0:
        case 0x26C:
        case 0x2E8:
        case 0x364:
        case 0x3E0:
        case 0x45C:
        case 0x4D8:
        case 0x554:
        case 0x5D0:
        case 0x64C:
        case 0x6C8:
        case 0x744:
        case 0x7C0:
        case 0x83C:
        case 0x8B8:
        case 0x934:
        case 0x9B0:
            State_80071C3C *p = lbl_803EA704;
            p->mUnknown127 = 1;
            p->mUnknown30 = p->mUnknown2C;
            fn_800724F4();
            break;
        }
        case 0x75:
        case 0xF1:
        case 0x16D:
        case 0x1E9:
        case 0x265:
        case 0x2E1:
        case 0x35D:
        case 0x3D9:
        case 0x455:
        case 0x4D1:
        case 0x54D:
        case 0x5C9:
        case 0x645:
        case 0x6C1:
        case 0x73D:
        case 0x7B9:
        case 0x835:
        case 0x8B1:
        case 0x92D:
        case 0x9A9:
        case 0xA25:
            if (lbl_803EA704->mUnknown12A > 1 &&
                lbl_803EA704->mUnknown30 == lbl_803EA704->mUnknown2C) {
                fn_80072424();
            }
            break;
        case -1:
            if (!lbl_803EA704->mUnknown129 && !lbl_803EA704->mUnknown122 && lbl_803EA704->mUnknown127) {
                lbl_803EA708 = 1;
            }
            break;
        }
    }
}

void fn_80071EA8(int a, int b, int c)
{
    if (a) {
        fn_801B3084(0x1000000, "SongNum", c);
    }
}

int fn_80071EDC(int mode)
{
    int result = 0;
    if (lbl_803EA704->mUnknown121 || lbl_803EA704->mUnknown125) {
        int id = 0x1679406;
        int blocked = 0;
        int stop = 0;
        int start = 0;
        int same = 0;
        if (!lbl_803EA704->mUnknown122) {
            same = lbl_803EA704->mUnknown30 == lbl_803EA704->mUnknown2C;
        }
        switch (mode) {
        case 0: id = 0x1AC89E8; break;
        case 1: break;
        case 2: id = 0x18B0457; break;
        case 5: id = 0x199B6D8; break;
        case 6: id = 0x136E6A7; break;
        case 9:
            if (lbl_803EA704->mUnknown11C == 3 || lbl_803EA704->mUnknown11C == 15 ||
                lbl_803EA704->mUnknown11C == 14 || lbl_803EA704->mUnknown11C == 16 ||
                lbl_803EA704->mUnknown30 != lbl_803EA704->mUnknown2C) {
                blocked = 1;
            } else {
                id = 0x1262E0A;
            }
            break;
        case 7:
            if (lbl_803EA704->mUnknown30 != lbl_803EA704->mUnknown2C) {
                blocked = 1;
            } else {
                lbl_803EA704->mUnknown129 = 1;
                id = 0x19BE6DB;
            }
            break;
        case 8:
            if (lbl_803EA704->mUnknown11C != 7) {
                blocked = 1;
            } else {
                lbl_803EA704->mUnknown129 = 0;
                id = 0x1FDFBA7;
            }
            break;
        case 10:
            lbl_803EA704->mUnknown129 = 1;
            start = same;
            id = 0x1C739C4;
            break;
        case 11:
            lbl_803EA704->mUnknown129 = 0;
            stop = same;
            id = 0x1E045E4;
            break;
        case 3:
            start = same;
            lbl_803EA704->mUnknown129 = 1;
            id = 0x189CE52;
            lbl_803EA704->mUnknown128 = 1;
            break;
        case 4:
            lbl_803EA704->mUnknown129 = 0;
            stop = same;
            id = 0x156195E;
            lbl_803EA704->mUnknown128 = 0;
            break;
        case 14:
            lbl_803EA704->mUnknown128 = 1;
            id = 0x1BEFEF2;
            break;
        case 15:
            start = same;
            lbl_803EA704->mUnknown129 = 1;
            id = 0x1AA9D96;
            lbl_803EA704->mUnknown128 = 1;
            break;
        case 16: id = 0x1F322AD; break;
        case 17:
            lbl_803EA704->mUnknown129 = 0;
            stop = same;
            id = 0x18ABBB7;
            lbl_803EA704->mUnknown128 = 0;
            break;
        case 12:
            lbl_803EA704->mUnknown129 = 1;
            start = same;
            id = 0x11E6027;
            break;
        case 13:
            stop = same;
            lbl_803EA704->mUnknown129 = 0;
            id = 0x10DE592;
            break;
        default: blocked = 1; break;
        }
        if (!blocked && mode != 5 && mode != 6) {
            lbl_803EA704->mUnknown11C = mode;
        }
        if (stop) {
            fn_801B3084(0x1000000, "SongNum", 0);
            fn_8006DEEC(0x11000001);
        } else if (start) {
            fn_801B3084(0x1000000, "SongNum", 1);
            fn_8006DF2C(0x11000001);
        }
        if (!blocked) {
            result = fn_8006DE00(0x11000001, id);
        } else if ((unsigned int)(mode - 7) <= 2) {
            result = 1;
        }
    }
    return result;
}

int fn_8007224C(int value)
{
    if (lbl_803EA704->mUnknown121 || lbl_803EA704->mUnknown125) {
        fn_8006DEA8(0x11000001, value);
    }
    return 1;
}

void fn_80072298(void)
{
    Object_8007A334 cursor;
    unsigned int i = 0;
    lbl_803EA704->mUnknown120 = 0;
    fn_8008352C(&cursor, 0);
    fn_800835D0(&cursor);
    unsigned int count = fn_800837B8(&cursor);
    for (i = 0; i < 40; ++i) {
        if (i < count) {
            lbl_803EA704->mUnknownF1[i] = i;
        } else {
            lbl_803EA704->mUnknownF1[i] = -1;
        }
    }
    if (count) {
        for (int round = 0; round <= 7; ++round) {
            for (unsigned int j = 0; j < count - 1; ++j) {
                int k = j + fn_802372EC(1, count - j);
                signed char first = lbl_803EA704->mUnknownF1[j];
                signed char second = lbl_803EA704->mUnknownF1[k];
                lbl_803EA704->mUnknownF1[k] = first;
                lbl_803EA704->mUnknownF1[j] = second;
            }
        }
        lbl_803EA704->mUnknown121 = 1;
    } else {
        lbl_803EA704->mUnknown121 = 0;
        fn_80073094();
    }
    fn_80083644(&cursor);
    lbl_803EA704->mUnknown12A = count;
}

int fn_800723DC(void)
{
    unsigned char index = lbl_803EA704->mUnknown120;
    int result = lbl_803EA704->mUnknownF1[index];
    if (index == 39 || (lbl_803EA704->mUnknownF1[index + 1] & 0x80)) {
        lbl_803EA704->mUnknown120 = 0;
    } else {
        ++lbl_803EA704->mUnknown120;
    }
    return result;
}

void fn_80072424(void)
{
    if (!lbl_803EA704->mUnknown126) {
        Object_8007A334 cursor;
        Query_8008352C query;
        query.mUnknown0 = 1;
        query.mUnknown4 = 0;
        query.mUnknown8 = 0;
        fn_8008352C(&cursor, &query);
        if (fn_800837B8(&cursor)) {
            fn_8007A600(&cursor, fn_800723DC());
            lbl_803EA704->mUnknown122 = fn_800837D8(&cursor);
            lbl_803EA704->mUnknown28 = fn_80083804(&cursor);
            lbl_803EA704->mUnknown2C = fn_8008382C(&cursor);
        } else {
            lbl_803EA704->mUnknown121 = 0;
        }
        fn_80083644(&cursor);
    }
}

void fn_800724F4(void)
{
    Object_8007A334 cursor;
    if ((!fn_80027DF0() && !lbl_803EA709) || !lbl_803EA700 || lbl_803EA704->mUnknown124) {
        lbl_803EA709 = 1;
    } else {
        unsigned short a, b;
        if (lbl_803EB688) {
            fn_80219650(lbl_803EB688, &a, &b);
            if (a == 5 && b == 1) {
                return;
            }
        }
        if (lbl_803EA704->mUnknown122) {
            fn_8007B358(&cursor);
            fn_8007B3CC(&cursor, lbl_803EA704->mUnknown2C, 0);
            fn_8007B42C(&cursor, lbl_803EA704->mUnknown58, 51);
            fn_8007B460(&cursor, lbl_803EA704->mUnknown8B, 51);
            fn_8007B494(&cursor, lbl_803EA704->mUnknownBE, 51);
            fn_8007B3AC(&cursor);
        }
        struct {
            int count;
            Text_800724F4 *records[3];
        } args;
        args.count = 3;
        args.records[0] = &lbl_803EA704->mUnknown34[0];
        args.records[0]->mpUnknown8 = lbl_803EA704->mUnknown58;
        args.records[0]->mUnknown4 = fn_801C3180(lbl_803EA704->mUnknown58);
        args.records[1] = &lbl_803EA704->mUnknown34[1];
        args.records[1]->mpUnknown8 = lbl_803EA704->mUnknown8B;
        args.records[1]->mUnknown4 = fn_801C3180(lbl_803EA704->mUnknown8B);
        args.records[2] = &lbl_803EA704->mUnknown34[2];
        args.records[2]->mpUnknown8 = lbl_803EA704->mUnknownBE;
        args.records[2]->mUnknown4 = fn_801C3180(lbl_803EA704->mUnknownBE);
        if (lbl_803EB690) {
            lbl_803EA709 = 0;
            fn_8021D7B8(lbl_803EB690, 0x80000004, 4, &args);
        }
    }
}

void fn_800726B8(void)
{
    if (lbl_803EA709) {
        int ready = 0;
        if (fn_80027DF0() || !fn_801486A0() || fn_801486A0() == 1 || fn_800AD9B4() != 3) {
            ready = 1;
        }
        if (ready) {
            fn_800724F4();
        }
    }
}

void fn_8007272C(void)
{
    lbl_803EA704 = (State_80071C3C *)fn_801D2B7C(0x130, 0, 0);
    fn_801C1F94(lbl_803EA704, 0, 0x130);
    lbl_803EA704->mUnknown128 = 0;
    lbl_803EA704->mUnknown14 = 20000;
    lbl_803EA704->mUnknown24 = -1;
    lbl_803EA704->mpUnknown20 = (void *)-1;
    lbl_803EA704->mUnknown18 = 20000;
    lbl_803EA704->mUnknown129 = 0;
    lbl_803EA704->mUnknown122 = 1;
    lbl_803EA704->mUnknown11C = 19;
    lbl_803EA704->mUnknown127 = 1;
    Object_8007A334 cursor;
    fn_8008352C(&cursor, 0);
    lbl_803EA704->mUnknown12A = fn_800837B8(&cursor);
    if (lbl_803EA704->mUnknown12A) {
        lbl_803EA704->mUnknown121 = 1;
    }
    fn_80083644(&cursor);
    if (fn_801F3E28()) {
        lbl_803EA704->mpUnknown20 = fn_801EEB44(lbl_802EBF88, 44);
        lbl_803EA704->mUnknown24 = fn_8006DBF8(lbl_803EA704->mpUnknown20, 1);
        fn_8006DC98(lbl_803EA704->mpUnknown20, 2, 0x11000001, 2.0f);
        fn_8006DFA8(fn_80071C3C);
        fn_80072C54(lbl_803EA700);
        fn_80072424();
        fn_80071EA8(lbl_803EA704->mUnknown122, lbl_803EA704->mUnknown28, lbl_803EA704->mUnknown2C);
    }
}

void fn_80072890(void)
{
    if (fn_801F3E28()) {
        fn_8006E010(fn_80071C3C);
        fn_8006DD24(0x11000001);
        fn_8006DC4C(lbl_803EA704->mUnknown24);
        fn_801EEFAC(lbl_803EA704->mpUnknown20);
    }
    fn_801D2BD0(lbl_803EA704);
    lbl_803EA704 = 0;
}

void fn_800728F8(void)
{
    if (fn_801F3E28()) {
        Calendar_801F81F4 calendar;
        fn_801F81F4(&calendar);
        unsigned long long now = fn_801F7D34(&calendar);
        if (lbl_803EA704->mUnknown0 && now > lbl_803EA704->mUnknown0) {
            State_80071C3C *p = lbl_803EA704;
            int value = p->mUnknown18;
            if (value < p->mUnknown14) {
                value += (unsigned int)(now - p->mUnknown0) * p->mUnknown10;
                if (value > p->mUnknown14) {
                    value = p->mUnknown14;
                }
                p->mUnknown18 = value;
                fn_8007224C(value);
            } else if (value > p->mUnknown14) {
                value -= (unsigned int)(now - p->mUnknown0) * p->mUnknown10;
                if (value < p->mUnknown14) {
                    value = p->mUnknown14;
                }
                lbl_803EA704->mUnknown18 = value;
                fn_8007224C(value);
            }
            lbl_803EA704->mUnknown0 = lbl_803EA704->mUnknown18 == lbl_803EA704->mUnknown14 ? 0 : now;
        }
        if (lbl_803EA704->mUnknown8 && now > lbl_803EA704->mUnknown8) {
            lbl_803EA704->mUnknown8 = 0;
            fn_80072E84();
        }
        if (lbl_803EA708) {
            lbl_803EA708 = 0;
            fn_8006DF6C(0x11000001);
            fn_80072B84(lbl_803EA704->mUnknown122, lbl_803EA704->mUnknown28, lbl_803EA704->mUnknown2C);
        } else {
            fn_80071EA8(lbl_803EA704->mUnknown122, lbl_803EA704->mUnknown28, lbl_803EA704->mUnknown2C);
        }
    }
}

void fn_80072AA8(void)
{
    fn_80073094();
    fn_80072298();
}

unsigned char fn_80072ACC(void) { return lbl_803EA704->mUnknown12A; }
void fn_80072AD8(unsigned char value)
{
    if (lbl_803EA704) {
        lbl_803EA704->mUnknown126 = value;
    }
}

void fn_80072AEC(int mode)
{
    if ((unsigned int)mode <= 17) {
        fn_80071EDC(mode);
        switch (mode) {
        case 0: lbl_803EA704->mUnknown123 = 1; break;
        case 1: lbl_803EA704->mUnknown123 = 0; break;
        case 5: lbl_803EA704->mUnknown124 = 1; break;
        case 6: lbl_803EA704->mUnknown124 = 0; break;
        }
    }
}

void fn_80072B84(int a, int b, int c)
{
    fn_80073094();
    lbl_803EA704->mUnknown125 = 1;
    if (a) {
        lbl_803EA704->mUnknown122 = 1;
        lbl_803EA704->mUnknown2C = c;
        lbl_803EA704->mUnknown28 = b;
        fn_80071EA8(a, b, c);
        fn_80071EDC(0);
    } else {
        lbl_803EA704->mUnknown122 = 0;
        lbl_803EA704->mUnknown127 = 0;
        lbl_803EA704->mUnknown30 = c;
        lbl_803EA704->mUnknown28 = b;
        lbl_803EA704->mUnknown2C = c;
        fn_801B3084(0x1000000, "SongNum", 0);
        fn_800724F4();
    }
    lbl_803EA704->mUnknown123 = 1;
    lbl_803EA704->mUnknown128 = 0;
    lbl_803EA704->mUnknown129 = 0;
}

void fn_80072C54(unsigned int value)
{
    lbl_803EA700 = value;
    if (lbl_803EA704) {
        fn_8006DD70(0x11000001, value);
    }
}

void fn_80072C90(unsigned int delay, int wait)
{
    if (fn_801F3E28() && lbl_803EA704->mUnknown123 && !lbl_803EA704->mUnknown124) {
        fn_80073328(0);
        Calendar_801F81F4 calendar;
        fn_801F81F4(&calendar);
        lbl_803EA704->mUnknown8 = fn_801F7D34(&calendar) + delay;
        if (lbl_803EA704->mUnknown122 || lbl_803EA704->mUnknown128) {
            fn_8006DDB4(0x11000001, 0, delay);
        }
        if (fn_80027DF0() && lbl_803EB690) {
            fn_8021D7B8(lbl_803EB690, 0x80000003, 0, 0);
        }
        if (wait) {
            while (lbl_803EA704->mUnknown8) {
                fn_800731D0(1);
            }
        }
    }
}

void fn_80072D98(unsigned int delay)
{
    if (fn_801F3E28()) {
        fn_80073328(1);
        fn_800731D0(1);
        if (lbl_803EA704->mUnknown123 &&
            (lbl_803EA704->mUnknown124 || lbl_803EA704->mUnknown8 || lbl_803EA700)) {
            fn_80072F04();
            if (lbl_803EA704->mUnknown122 || lbl_803EA704->mUnknown128) {
                fn_8006DDB4(0x11000001, 100, delay);
            }
            lbl_803EA704->mUnknown8 = 0;
            fn_800731D0(1);
            fn_80073210(90);
        }
    }
}

unsigned char fn_80072E6C(void)
{
    unsigned char result = 0;
    if (lbl_803EA704) {
        result = lbl_803EA704->mUnknown124;
    }
    return result;
}

void fn_80072E84(void)
{
    if ((lbl_803EA704->mUnknown121 || lbl_803EA704->mUnknown125) &&
        lbl_803EA704->mUnknown123 && !lbl_803EA704->mUnknown124) {
        if (lbl_803EA704->mUnknown122 || lbl_803EA704->mUnknown128) {
            fn_8006DEEC(0x11000001);
        }
        lbl_803EA704->mUnknown124 = 1;
    }
}

void fn_80072F04(void)
{
    if ((lbl_803EA704->mUnknown121 || lbl_803EA704->mUnknown125) && lbl_803EA700 &&
        lbl_803EA704->mUnknown124) {
        if (lbl_803EA704->mUnknown122 || lbl_803EA704->mUnknown128) {
            fn_8006DF2C(0x11000001);
        }
        lbl_803EA704->mUnknown124 = 0;
    }
}

unsigned char fn_80072F84(void) { return lbl_803EA704->mUnknown123; }

void fn_80072F90(void)
{
    if (fn_801F3E28() && lbl_803EA704) {
        lbl_803EA704->mUnknown125 = 0;
        if (lbl_803EA704->mUnknown121 && lbl_803EA700) {
            fn_80072F04();
            int next = 1;
            if (lbl_803EA704->mUnknown123) {
                Object_8007A334 cursor;
                fn_8008352C(&cursor, 0);
                if (fn_800836A4(&cursor, lbl_803EA704->mUnknown122, lbl_803EA704->mUnknown28,
                               lbl_803EA704->mUnknown2C)) {
                    next = 0;
                    fn_800724F4();
                } else {
                    fn_80073094();
                }
                fn_80083644(&cursor);
            }
            if (next) {
                fn_80072424();
                fn_80072B84(lbl_803EA704->mUnknown122, lbl_803EA704->mUnknown28, lbl_803EA704->mUnknown2C);
            }
        } else {
            fn_80073094();
        }
    }
}

void fn_80073094(void)
{
    if (lbl_803EA704) {
        if (lbl_803EA704->mUnknown123) {
            if (lbl_803EA704->mUnknown122 || lbl_803EA704->mUnknown127) {
                fn_8006DF2C(0x11000001);
                fn_8006DF6C(0x11000001);
            }
            lbl_803EA704->mUnknown124 = 0;
            lbl_803EA704->mUnknown123 = 0;
            if (fn_80027DF0() && lbl_803EB690) {
                fn_8021D7B8(lbl_803EB690, 0x80000003, 0, 0);
            }
        }
        lbl_803EA704->mUnknown125 = 0;
    }
}

void fn_80073144(int value, unsigned int duration)
{
    State_80071C3C *p = lbl_803EA704;
    if (p->mUnknown122) {
        p->mUnknown14 = value;
        if (!duration) {
            if (p->mUnknown18 != value) {
                p->mUnknown18 = value;
                fn_8007224C(value);
            }
        } else {
            unsigned int delta;
            if (value < p->mUnknown18) {
                delta = p->mUnknown18 - value;
            } else {
                delta = value - p->mUnknown18;
            }
            p->mUnknown10 = delta / duration;
            Calendar_801F81F4 calendar;
            fn_801F81F4(&calendar);
            lbl_803EA704->mUnknown0 = fn_801F7D34(&calendar);
        }
    }
}

void fn_800731D0(int draw)
{
    fn_8006CA84(1);
    if (draw) {
        fn_801CE7D0(1);
    }
}

void fn_80073210(int frames)
{
    Info_801E1084 info;
    fn_801E1084(0x11000001, &info);
    if (lbl_803EA704 && fn_801F3E28() && info.mUnknown0 >= 0 && lbl_803EA704->mUnknown122) {
        int count = 0;
        int previous = info.mUnknown30;
        if (frames <= 0) {
            frames = 90;
        }
        int limit = frames * 1000 / 60;
        if (!lbl_803EA704->mUnknown124) {
            while (info.mUnknown30 < limit && count < frames) {
                ++count;
                fn_800731D0(1);
                previous = info.mUnknown30;
                fn_801E1084(0x11000001, &info);
                if (lbl_803EA704->mUnknown124 || info.mUnknown30 > previous) {
                    break;
                }
            }
        }
    }
}

int fn_80073310(void)
{
    if (!lbl_803EA704) {
        return 19;
    }
    return lbl_803EA704->mUnknown11C;
}

void fn_80073328(int resume)
{
    int handled = 1;
    switch (lbl_803EA704->mUnknown11C) {
    case 7: fn_80072AEC(8); break;
    case 10: fn_80072AEC(11); break;
    case 12: fn_80072AEC(13); break;
    case 3: fn_80072AEC(4); break;
    case 15:
        fn_80072AEC(16);
        for (int i = 20; i; --i) {
            fn_800731D0(1);
        }
    case 14:
        fn_80072AEC(17);
        for (int i = 20; i; --i) {
            fn_800731D0(1);
        }
        break;
    default: handled = 0; break;
    }
    if (handled && resume) {
        fn_800731D0(1);
        fn_80072E84();
    }
}
}
