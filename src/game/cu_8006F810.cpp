#include "game/Object_80039F5C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"

struct Constants_8006F810 {
    float mBounds[3];
    float mThreshold;
    float mScale;
    char mUnknown14[8];
    float mZ;
};

struct Record_80071594 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned short mUnknown14;
};

extern "C" {

int fn_80177F70(void);
int fn_8017F584(void);
int fn_801486A0(void);
int fn_80178308(void);
int fn_80178320(void);
Object_800670B4 *fn_80168708(int side);
int fn_8006CC54(int id);
void fn_8006C9D4(int id);
int fn_802372EC(int a, int b);
int fn_8006C548(unsigned int channel, int id, void (*callback)(int handle));
int fn_8006C674(int channel, int id);
int fn_8006C7F4(unsigned int channel);
int fn_8006C8A4(int id, Vector_80039F5C *pos, unsigned char volume);
unsigned char fn_8006CC90(int id);
unsigned char fn_8006CC48(void);
void fn_8006F54C(void);
int fn_800A3444(void);
int fn_801CB120(void);
void fn_801CAF24(void);
void fn_801F4B20(void);
int fn_801F41A0(int handle);
unsigned int fn_801F7ABC(void);
void fn_80227690(void *out, void *a, void *b);
int fn_80237470(int a, int b);
int fn_802374C8(int handle);
void fn_8023756C(int handle);
extern Constants_8006F810 lbl_80290B7C;
extern unsigned char lbl_802D63D0[];
extern unsigned char lbl_80290BAC[][2];
extern Vector_80039F5C lbl_8030AA7C;
extern int lbl_803EA6C0;
extern unsigned char lbl_803EA6C4;
extern unsigned char lbl_803EA6C5;
extern unsigned char lbl_803EA6C6;
extern unsigned char lbl_803EA6C7;
extern unsigned char lbl_803EA6C8;
extern unsigned char lbl_803EA6C9;
extern unsigned char lbl_803EA6CA;
extern unsigned char lbl_803EA6CF;
extern unsigned char lbl_803EA6D0;
extern unsigned char lbl_803EA6D1;
extern unsigned char lbl_803EA6D2;
extern unsigned char lbl_803EA6D3;
extern unsigned char lbl_803EA6D4;
extern unsigned char lbl_803EA6D5;
extern unsigned char lbl_803EA6D6;
extern unsigned char lbl_803EA6D7;
extern unsigned char lbl_803EA6D8;
extern unsigned char lbl_803EA6DB;
extern unsigned char lbl_803EA6DC;
extern unsigned char lbl_803EA6E4;
extern unsigned char lbl_803EA6E5;
extern int lbl_803EA6E8;
extern unsigned int lbl_803EA6F0;
extern int lbl_803EA6F4;
extern unsigned char lbl_803EA6FA;
extern unsigned char lbl_803EA6FB;
extern int lbl_803EC820;
extern int lbl_803EC824;
extern int lbl_803EC828;
extern int lbl_803EC82C;
extern int lbl_803EC830;
extern int lbl_803EC834;
extern int lbl_803EC838;
extern int lbl_803EC83C;
extern int lbl_803EC840;


void fn_8006CA18(int index, int value, unsigned char volume);
int fn_8006C854(int index, Vector_80039F5C *p);

extern unsigned char lbl_803EA6CC;
extern unsigned char lbl_803EA6CD;
extern unsigned char lbl_803EA6CE;
extern unsigned char lbl_803EA6F9;
extern unsigned char lbl_803EA6D9;
extern unsigned char lbl_803EA6DA;

void fn_8006F810(void)
{
    lbl_803EA6CC = lbl_803EA6CD = 1;
}

void fn_8006F820(void)
{
}

void fn_8006F824(int value)
{
    fn_8006CA18(5, value, 0);
}

void fn_800711DC(int value)
{
}

void fn_80071344(void)
{
}

void fn_80071348(void)
{
}

void fn_80071790(void)
{
}

int fn_80071974(Vector_80039F5C *p)
{
    lbl_803EA6D9 = 0;
    return fn_8006C854(34, p);
}

int fn_800719A4(Vector_80039F5C *p)
{
    lbl_803EA6DA = 0;
    return fn_8006C854(35, p);
}

void fn_800719D4(void)
{
    fn_8006CA18(lbl_803EA6D9 + 34, 100, 0);
}

int fn_80071BA0(int a, int value)
{
    switch (value) {
    case 3:
        return 105;
    case 9:
        return 111;
    case 10:
        return 108;
    default:
        return 105;
    }
}

int fn_80071BDC(int value)
{
    int result = 42;
    switch (value) {
    case 0:
    case 1:
    case 8:
        result = 44;
        break;
    case 2:
    case 3:
        break;
    case 4:
    case 6:
        result = 43;
        break;
    default:
        result = 44;
        break;
    }
    return result;
}

void fn_80071C2C(int value)
{
    lbl_803EA6CE = value;
}

void fn_80071C34(int value)
{
    lbl_803EA6F9 = value;
}

void fn_80070C40(Record_80067CA8 *p)
{
    if (!fn_80177F70()) return;
    switch (p->mType) {
    case 117: lbl_803EA6E4 = 1; break;
    case 118: fn_802372EC(1, 2); break;
    case 116: {
        unsigned char side = ((unsigned char *)&p->mUnknown10)[3];
        if (fn_8017F584() == 11 && fn_801486A0() == 15) break;
        if (side != fn_80178308()) break;
        if (fn_8006CC54(66) || fn_8006CC54(67)) break;
        lbl_803EA6DB = (lbl_803EA6DB + 1) % 2;
        fn_8006C854(lbl_803EA6DB ? 67 : 66, 0);
        break;
    }
    case 140:
        if (fn_8017F584() == 11 && fn_801486A0() == 15) break;
        fn_8006C9D4(66);
        fn_8006C9D4(67);
        fn_8006C854(65, &p->mPos);
        break;
    }
}

void fn_80070D68(void)
{
    if (!lbl_803EA6FA) return;
    if (lbl_803EA6FB) {
        unsigned char id;
        int busy;
        do {
            lbl_803EA6C4 = (lbl_803EA6C4 + 1) % 30;
            id = lbl_803EA6C4;
            busy = fn_8006C674(4, id);
        } while (busy);
        fn_8006C548(3, id, 0);
        lbl_803EA6FB = busy;
    } else {
        unsigned char id;
        do {
            lbl_803EA6C5 = (lbl_803EA6C5 + 1) % 30;
            id = lbl_803EA6C5;
        } while (fn_8006C674(3, id));
        fn_8006C548(4, id, 0);
        lbl_803EA6FB = 1;
    }
    lbl_803EA6C6 = (lbl_803EA6C6 + 1) % 10;
    fn_8006C548(5, lbl_803EA6C6 + 30, 0);
}

void fn_80070E8C(void)
{
    if (!lbl_803EA6FA) return;
    if ((lbl_803EA6D6 + 1) % 6 <= 2) {
        int id;
        do {
            lbl_803EA6C9 = (lbl_803EA6C9 + 1) % 10;
            id = lbl_803EA6C9 + 145;
        } while (fn_8006C674(14, id));
        fn_8006C548(13, id, 0);
    } else {
        int id;
        do {
            lbl_803EA6CA = (lbl_803EA6CA + 1) % 10;
            id = lbl_803EA6CA + 145;
        } while (fn_8006C674(13, id));
        fn_8006C548(14, id, 0);
    }
}

void fn_80070F84(void)
{
    if (!lbl_803EA6FA) return;
    Object_800670B4 *p = fn_80168708(fn_80178320());
    unsigned int count = 0;
    for (int i = 0; i < 7; ++i) {
        Point_8017886C *point = &p->mUnknown8.mUnknown84[0][i].mUnknown10;
        if (point->mX > lbl_80290B7C.mBounds[0] && point->mX < lbl_80290B7C.mBounds[1] && point->mY < lbl_80290B7C.mBounds[2]) ++count;
    }
    int id;
    if (count > 2) id = fn_802374C8(lbl_803EC828) + 40;
    else if (count > 1) id = fn_802374C8(lbl_803EC82C) + 56;
    else id = fn_802374C8(lbl_803EC830) + 72;
    fn_8006C548(6, id, 0);
}

void fn_8007105C(void)
{
    if (lbl_803EA6FA) {
        lbl_803EA6C7 = (lbl_803EA6C7 + 1) % 5;
        fn_8006C548(7, lbl_803EA6C7 + 77, 0);
    }
}

void fn_800710C8(void)
{
    int base = 118;
    if (lbl_803EA6FA) {
        switch (fn_800A3444()) {
        case 3: base = 133; break;
        case 9: base = 121; break;
        case 4: base = 130; break;
        case 6: case 7: case 8: base = 139; break;
        case 10: base = 127; break;
        case 0: case 5: case 11: base = 136; break;
        }
        lbl_803EA6C8 = (lbl_803EA6C8 + 1) % 3;
        fn_8006C548(8, base + lbl_803EA6C8, 0);
    }
}

void fn_800711E0(void)
{
    if (!fn_8006CC48()) return;
    if (lbl_803EA6FA) {
        switch (lbl_803EA6F4) {
        case 0: {
            fn_8006F54C();
            unsigned char id;
            do { lbl_803EA6C4 = fn_802374C8(lbl_803EC820); id = lbl_803EA6C4; }
            while (fn_8006C674(3, id));
            if (fn_801486A0()) {
                while (!fn_8006C7F4(3)) {
                    if (fn_801CB120()) fn_801CAF24();
                    fn_801F4B20();
                }
            }
            fn_8006C548(3, id, 0);
            do { lbl_803EA6C5 = fn_802374C8(lbl_803EC820); id = lbl_803EA6C5; }
            while (fn_8006C674(4, id));
            if (fn_801486A0()) {
                while (!fn_8006C7F4(4)) {
                    if (fn_801CB120()) fn_801CAF24();
                    fn_801F4B20();
                }
            }
            fn_8006C548(4, id, 0);
            break;
        }
        case 1: case 2: fn_8006F54C(); break;
        }
    }
    lbl_803EA6F4 = 3;
}

void fn_8007134C(void)
{
    int side = fn_80178308();
    unsigned char value = 0;
    unsigned short index = 0;
    unsigned int count = fn_80178D18(side);
    for (; index < count; ++index) {
        Object_80039F5C *p = fn_80039F5C(side, index);
        if (!p->mUnknown2914) { value = p->mUnknown2912; break; }
    }
    lbl_803EA6DC = (lbl_803EA6DC + 1) % 3;
    int id, other;
    if (!fn_80178308()) {
        if (value <= 2) { other = lbl_803EA6DC + 100; id = lbl_803EA6DC + 85; }
        else { other = lbl_803EA6DC + 94; id = lbl_803EA6DC + 82; }
    } else {
        if (value <= 2) { other = lbl_803EA6DC + 112; id = lbl_803EA6DC + 91; }
        else { other = lbl_803EA6DC + 106; id = lbl_803EA6DC + 88; }
    }
    fn_8006C548(2, id, 0);
    fn_8006C548(16, other, 0);
}

void fn_80071458(Object_80039F5C *p, Object_80137ABC *ball)
{
    Vector_80039F5C pos, velocity, delta;
    fn_80137D58(ball, &pos);
    int nearby = 0;
    fn_80137EC4(ball, &velocity);
    if (p->mIdBytes[3] == 1) {
        fn_80227690(&delta, &pos, &p->mMotion);
        nearby = fn_802270A4(&delta) < lbl_80290B7C.mThreshold;
    }
    fn_80067DB8(28, &pos, (unsigned int)(fn_802270D4(&velocity) * lbl_80290B7C.mScale), nearby, ball->mState.mIndex);
}

void fn_80071540(int *value, Object_80137ABC *ball)
{
    Vector_80039F5C pos;
    fn_80137D58(ball, &pos);
    fn_80067E3C(29, &pos, *value, 0, 0, ball->mState.mIndex);
}

void fn_80071594(void *record)
{
    Record_80071594 *p = (Record_80071594 *)record;
    Vector_80039F5C pos;
    pos.mX = p->mUnknownC;
    pos.mY = p->mUnknown10;
    pos.mZ = lbl_80290B7C.mZ;
    if (lbl_803EA6CD) fn_80067E3C((unsigned short)(p->mUnknown14 + 137), &pos, p->mUnknown0, p->mUnknown4, p->mUnknown8, 0);
}

void fn_80071600(void)
{
    lbl_803EC820 = fn_80237470(1, 30);
    lbl_803EC824 = fn_80237470(1, 10);
    lbl_803EC828 = fn_80237470(1, 16);
    lbl_803EC82C = fn_80237470(1, 16);
    lbl_803EC830 = fn_80237470(1, 5);
    lbl_803EC834 = fn_80237470(1, 5);
    lbl_803EC838 = fn_80237470(1, 3);
    lbl_803EC83C = fn_80237470(1, 10);
    lbl_803EC840 = fn_80237470(1, 13);
    lbl_803EA6C5 = 1;
    lbl_803EA6DC = 0;
    lbl_803EA6CF = 0;
    lbl_803EA6D0 = 0;
    lbl_803EA6D1 = 0;
    lbl_803EA6D2 = 0;
    lbl_803EA6D3 = 0;
    lbl_803EA6D4 = 0;
    lbl_803EA6D5 = 0;
    lbl_803EA6E5 = 0;
    lbl_803EA6C4 = 0;
    lbl_803EA6DB = 0;
}

void fn_800716E4(void)
{
    fn_8023756C(lbl_803EC820);
    fn_8023756C(lbl_803EC824);
    fn_8023756C(lbl_803EC828);
    fn_8023756C(lbl_803EC82C);
    fn_8023756C(lbl_803EC830);
    fn_8023756C(lbl_803EC834);
    fn_8023756C(lbl_803EC838);
    fn_8023756C(lbl_803EC83C);
    fn_8023756C(lbl_803EC840);
}

void fn_80071748(void)
{
    if (lbl_803EA6C0 != 0x7FFFFFFF && fn_801F41A0(lbl_803EA6C0)) lbl_803EA6C0 = 0x7FFFFFFF;
}

void fn_80071794(int id)
{
    fn_8006C8A4(lbl_803EA6F0 + id, 0, 127);
    if (++lbl_803EA6F0 > 2) lbl_803EA6F0 = 2;
}

int fn_800717E0(Vector_80039F5C *pos)
{
    unsigned int step = fn_802372EC(1, 2) + 1;
    lbl_803EA6D6 = (lbl_803EA6D6 + step) % 6;
    return fn_8006C854(lbl_803EA6D6 + 18, pos);
}

int fn_8007184C(Vector_80039F5C *pos)
{
    unsigned int step = fn_802372EC(1, 2) + 1;
    lbl_803EA6D7 = (lbl_803EA6D7 + step) % 4;
    return fn_8006C854(lbl_803EA6D7 + 24, pos);
}

void fn_800718A0(void)
{
    if (lbl_803EA6E8 > 0 && fn_801F7ABC() >= (unsigned int)lbl_803EA6E8) {
        lbl_803EA6D8 = (lbl_803EA6D8 + 1) % 6;
        lbl_803EA6E8 = -1;
        fn_8006C854(lbl_803EA6D8 + 28, &lbl_8030AA7C);
    }
}

void fn_80071914(Vector_80039F5C *pos)
{
    if (lbl_803EA6E8 == -1) {
        lbl_803EA6E8 = fn_801F7ABC() + 6;
        lbl_8030AA7C.mX = pos->mX;
        lbl_8030AA7C.mY = pos->mY;
        lbl_8030AA7C.mZ = pos->mZ;
    }
}

int fn_80071A04(int id, Vector_80039F5C *pos)
{
    if (++lbl_802D63D0[id] >= lbl_80290BAC[id][1]) lbl_802D63D0[id] = 0;
    return fn_8006C854(lbl_80290BAC[id][0] + lbl_802D63D0[id], pos);
}

int fn_80071A6C(int id, Vector_80039F5C *pos, unsigned int volume)
{
    if (++lbl_802D63D0[id] >= lbl_80290BAC[id][1]) lbl_802D63D0[id] = 0;
    int sound = lbl_80290BAC[id][0] + lbl_802D63D0[id];
    return fn_8006C8A4(sound, pos, (unsigned char)((volume * fn_8006CC90(sound)) / 100));
}

int fn_80071B08(int unused, int value)
{
    int result = 36;
    int choice = fn_802372EC(1, 2);
    switch (value) {
    case 2: case 4: if (!choice) result = 38; break;
    case 1: case 10: result = 40; break;
    case 9: break;
    default: result = 38; break;
    }
    return result;
}

}
