#include "game/fn_8016871C.h"
#include "game/SndgPathfinder.h"
#include "game/Block_800C9D6C.h"
#include "game/Object_8003DEC4.h"
#include "game/fn_80054138.h"
#include "game/fn_80177FE0.h"
#include "game/cu_8002B8F8.h"
#include "game/SndgCrowd.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"

struct Constants_8006F850 {
    float mThreshold;
    char mUnknown4[12];
    float mScale;
    char mUnknown14[12];
    float mStrong;
};

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

int fn_8007F828(int id);
int fn_800A8444(int index);
void fn_8006EA04(unsigned int index, unsigned int value);
void fn_8006BD24(void);
void fn_80072AEC(int mode);
void fn_80072E84(void);
void fn_80072F04(void);
void fn_8006BC30(int type, unsigned int index);
void fn_8006BCC8(int type);
int fn_8006B810(int type, unsigned int index);
unsigned int fn_8006BA54(int type, int value);
void fn_8006F5EC(int type, int mode, Vector_80039F5C *pPos, void *pObject, int index);
void fn_8006F6A0(int type, Record_80067CA8 *pRecord);
void fn_8006F550(void);
void fn_8006F0B8(int flags);
void fn_8006E08C(void);
unsigned char fn_8002D060(Type_803EA368 *p);
int fn_800A9680(void);
int fn_80073310(void);
int fn_801650DC(Record_80067338 *pRecord);
int fn_80178348(void);
extern Constants_8006F850 lbl_80290B58;
extern unsigned int lbl_80290B9C[4];
extern float lbl_803ECB08;
extern unsigned char lbl_803EA6EC;
extern unsigned char lbl_803EA6F8;
extern unsigned int lbl_803EA6E0;
void fn_80070D68(void);
void fn_80070E8C(void);
void fn_80070F84(void);
void fn_8007105C(void);
void fn_800710C8(void);
void fn_8007134C(void);
int fn_800717E0(Vector_80039F5C *pPos);
int fn_8007184C(Vector_80039F5C *pPos);
void fn_80071914(Vector_80039F5C *pPos);
int fn_80071A04(int id, Vector_80039F5C *pPos);
int fn_80071A6C(int id, Vector_80039F5C *pPos, unsigned int volume);
int fn_80071B08(int unused, int value);


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

void fn_8006F850(Record_80067CA8 *p)
{
    switch (p->mType) {
    case 53: fn_8006C854(48, &p->mPos); break;
    case 50: fn_8006C854(55, &p->mPos); break;
    case 51: fn_8006C854(56, &p->mPos); break;
    case 52: fn_8006C854(57, &p->mPos); break;
    case 48:
        fn_8006F394(14, fn_8009BCE8(&p->mUnknown0)->mIdBytes[2]);
        fn_8006C854(54, &p->mPos);
        break;
    case 49:
        fn_8006F394(15, fn_8009BCE8(&p->mUnknown0)->mIdBytes[2]);
        fn_8006C854(53, &p->mPos);
        break;
    case 132: fn_8006BD24(); fn_8006F394(2, 0); break;
    case 126: fn_80072AEC(10); break;
    case 127: fn_80072AEC(11); break;
    case 107: case 128:
        if ((unsigned char)(fn_8007F828(5) * 10) > 52 && !fn_800A8444(0) && !fn_800A8444(1)) fn_8006EA04(2, 52);
        break;
    case 109: case 130: fn_8006EA04(2, (unsigned char)(fn_8007F828(5) * 10) & ~1U); break;
    case 88: {
        int surface = 15;
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        Object_8003DEC4 *pose = (Object_8003DEC4 *)player->mpUnknown4;
        if (pose && pose->mUnknown972) surface = ((Area_80054138 *)pose->mUnknown972)->mSurface;
        int id = fn_80071BDC(surface);
        if (fn_80137B40() == player) {
            int volume = fn_8006CC90(id) * 2;
            if (volume > 127) volume = 127;
            else volume = fn_8006CC90(id) * 2;
            fn_8006C8A4(id, &p->mPos, (unsigned char)volume);
        } else fn_8006C854(id, &p->mPos);
        break;
    }
    case 97: {
        Block_800C9D6C *table = fn_800CA8EC();
        int active = 0;
        unsigned char index = 0;
        unsigned int side = ((unsigned int)p->mUnknown0 >> 8) & 255;
        for (; index < 2; ++index) {
            Entry_800C9D6C *entry = &table->mEntries[side][index];
            if (entry->mRef == p->mUnknown0) { active = entry->mUnknown10 == 1; break; }
        }
        int id;
        switch (p->mUnknown10.mValue) {
        case 12: fn_8007184C(&p->mPos); break;
        case 34: id = active ? 46 : 45; fn_8006C854(id, &p->mPos); fn_800717E0(&p->mPos); break;
        case 35: id = active ? 48 : 47; fn_8006C854(id, &p->mPos); fn_800717E0(&p->mPos); break;
        case 36: id = active ? 50 : 49; fn_8006C854(id, &p->mPos); fn_800717E0(&p->mPos); break;
        case 43: id = active ? 52 : 51; fn_8006C854(id, &p->mPos); fn_800717E0(&p->mPos); break;
        default: break;
        }
        break;
    }
    case 36: {
        int surface = 15;
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        Object_8003DEC4 *pose = (Object_8003DEC4 *)player->mpUnknown4;
        if (pose && pose->mUnknown972) surface = ((Area_80054138 *)pose->mUnknown972)->mSurface;
        int state = fn_800A3444();
        lbl_803EA6D1 = (lbl_803EA6D1 + 1) % 2;
        fn_8006C854(fn_80071B08(state, surface) + lbl_803EA6D1, &p->mPos);
        break;
    }
    case 101: fn_80071974(&p->mPos); break;
    case 102: fn_800719D4(); break;
    case 103: fn_800719A4(&p->mPos); break;
    case 62:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(108, &p->mPos);
        } else { fn_80071A04(10, &p->mPos); fn_80071914(&p->mPos); }
        break;
    case 63:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(104, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled <= 24) volume = 25;
                else volume = scaled > 100 ? 100 : (unsigned char)scaled;
            }
            fn_80071A6C(0, &p->mPos, volume);
        }
        break;
    case 65:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(106, &p->mPos);
        } else fn_80071A04(3, &p->mPos);
        break;
    case 66:
        if (p->mUnknown14) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(105, &p->mPos);
        }
        break;
    case 67:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(110, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled <= 24) volume = 25;
                else volume = scaled > 100 ? 100 : (unsigned char)scaled;
            }
            fn_80071A6C(2, &p->mPos, volume);
        }
        break;
    case 68:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(106, &p->mPos);
        } else { fn_80071A04(4, &p->mPos); fn_80071914(&p->mPos); }
        break;
    case 69:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(108, &p->mPos);
        } else { fn_80071A04(5, &p->mPos); fn_80071914(&p->mPos); }
        break;
    case 70:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(108, &p->mPos);
        } else { fn_80071A04(6, &p->mPos); fn_80071914(&p->mPos); }
        break;
    case 72:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(105, &p->mPos);
        }
        break;
    case 73:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(110, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled <= 24) volume = 25;
                else volume = scaled > 100 ? 100 : (unsigned char)scaled;
            }
            fn_80071A6C(8, &p->mPos, volume);
        }
        break;
    case 64: case 74:
        if (p->mUnknown14 || !p->mUnknown0) fn_8006BC30(4, (unsigned char)p->mUnknown18);
        fn_80071A04(9, &p->mPos);
        break;
    case 75:
        if (p->mUnknown14) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(111, &p->mPos);
        } else fn_80071A04(8, &p->mPos);
        break;
    case 76:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(112, &p->mPos);
        }
        break;
    case 77:
        if (p->mUnknown14 || !p->mUnknown0) {
            fn_8006BC30(4, (unsigned char)p->mUnknown18);
            fn_8006C854(107, &p->mPos);
        } else { fn_80071A04(8, &p->mPos); fn_80071914(&p->mPos); }
        break;
    case 78:
        fn_80071A04(1, &p->mPos);
        if (p->mUnknown14) fn_8006BC30(4, (unsigned char)p->mUnknown18);
        else fn_80071914(&p->mPos);
        break;
    case 47: fn_8006BC30(4, (unsigned char)p->mUnknown18); break;
    case 86: case 87:
        fn_8006F5EC(7, fn_8006B810(7, 0) ? 2 : 1, &p->mPos, 0, 0);
        break;
    case 85: fn_8006F6A0(12, p); break;
    case 81: fn_8006F6A0(5, p); break;
    case 79: fn_8006F6A0(8, p); break;
    case 80: fn_8006F6A0(11, p); break;
    case 82: fn_8006F6A0(9, p); break;
    case 83: fn_8006F6A0(10, p); break;
    case 84:
        fn_8006F5EC(6, fn_8006B810(6, (unsigned char)fn_8006BA54(6, p->mUnknown18)) ? 2 : 1, &p->mPos, 0, 0);
        break;
    case 44: lbl_803EA6EC = 1; break;
    case 46: fn_80071914(&p->mPos); break;
    case 96: if (p->mUnknown10.mValue <= 4) fn_800717E0(&p->mPos); break;
    case 22: fn_8006C854(132, 0); break;
    case 23: fn_8006C854(133, 0); break;
    case 8: fn_80072AEC(3); break;
    case 9: fn_80072AEC(4); break;
    case 11: fn_80072AEC(14); break;
    case 10: fn_80072AEC(15); break;
    case 13: fn_80072AEC(16); break;
    case 12: fn_80072AEC(17); break;
    case 15:
        if (p->mUnknown10.mValue && !fn_8002D060(lbl_803EA368) && !fn_8006CC54(62)) fn_8006C854(62, 0);
        break;
    case 17: if (!fn_8006CC54(60)) fn_8006C854(60, 0); break;
    case 20: fn_8006C854(61, 0); break;
    case 18: fn_8006C854(58, &p->mPos); break;
    case 125:
        if (fn_801486A0()) {
            lbl_803EA6E5 = (lbl_803EA6E5 + 1) % 4;
            switch (lbl_803EA6E5) {
            case 0: fn_80070D68(); break;
            case 1: fn_80070E8C(); fn_8007105C(); break;
            case 2: fn_80070D68(); fn_800710C8(); break;
            case 3: fn_80070E8C(); break;
            }
        }
        break;
    case 115: if (fn_801486A0()) fn_80070F84(); break;
    case 112: if (fn_801486A0()) fn_8007134C(); break;
    case 113:
        fn_8006C854(130, 0);
        fn_8006BCC8(2);
        fn_80072E84();
        fn_8006F394(2, 0);
        break;
    case 114:
        fn_8006BCC8(3);
        if (!p->mUnknown10.mValue) fn_80072F04();
        fn_8006F394(3, 0);
        break;
    case 95: if (fn_801486A0()) fn_8006C854(63, 0); break;
    case 89: fn_8006F394(4, (unsigned char)p->mUnknown10.mValue); break;
    case 94: fn_8006F394(11, (unsigned char)p->mUnknown10.mValue); break;
    case 92: fn_8006F394(9, (unsigned char)p->mUnknown10.mValue); fn_8006C854(134, 0); break;
    case 90: fn_8006F394(13, (unsigned char)p->mUnknown10.mValue); break;
    case 24: fn_8006C854(136, 0); break;
    case 25: fn_8006C854(137, 0); break;
    case 26: fn_8006C854(138, 0); break;
    case 35: {
        Object_80039F5C *a = (Object_80039F5C *)p->mUnknown10.mpObject;
        Object_80039F5C *b = (Object_80039F5C *)p->mUnknown14;
        int id;
        if (a->mUnknown560.mUnknown28 > lbl_803ECB08 * lbl_80290B58.mThreshold ||
            b->mUnknown560.mUnknown28 > lbl_803ECB08 * lbl_80290B58.mThreshold || fn_800A9680()) {
            lbl_803EA6D0 = (lbl_803EA6D0 + 1) % 3;
            id = lbl_803EA6D0 + 15;
        } else {
            lbl_803EA6CF = (lbl_803EA6CF + 1) % 3;
            id = lbl_803EA6CF + 12;
        }
        unsigned char volume;
        if (fn_800A9680()) volume = fn_8006CC90(id);
        else {
            float scaled = (a->mUnknown560.mUnknown28 + a->mUnknown560.mUnknown28) * fn_8006CC90(id) / (lbl_803ECB08 * lbl_80290B58.mScale);
            if (!(scaled <= fn_8006CC90(id))) volume = (unsigned char)(int)(float)fn_8006CC90(id);
            else volume = (unsigned char)(int)((a->mUnknown560.mUnknown28 + a->mUnknown560.mUnknown28) * fn_8006CC90(id) / (lbl_803ECB08 * lbl_80290B58.mScale));
        }
        fn_8006C8A4(id, &a->mMotion.mPos, volume);
        break;
    }
    case 27:
        fn_8006C854(p->mUnknown10.mValue == 1, &p->mPos);
        fn_8006C854(5, &p->mPos);
        break;
    case 140:
        fn_8006E08C();
        lbl_803EA6E8 = -1;
        lbl_803EA6EC = lbl_803EA6F8 = 0;
        break;
    case 144: fn_8006C854(1, &p->mPos); break;
    case 157: {
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        if (fn_801486A0() != 1) {
            if (!lbl_803EA6F9) fn_80072AEC(9);
            else lbl_803EA6F9 = 0;
            fn_8006F394(5, player->mIdBytes[2]);
        } else if (lbl_803EA6CE) {
            fn_80071C2C(0);
            lbl_803EA6E0 = (lbl_803EA6E0 + 1) % 4;
            fn_8006F394(lbl_80290B9C[lbl_803EA6E0], player->mIdBytes[2]);
        }
        break;
    }
    case 104:
        fn_8006C854(64, &p->mPos);
        if (fn_801486A0()) {
            Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
            if (!lbl_803EA6F9) fn_80072AEC(7);
            fn_8006F394(6, player->mIdBytes[2]);
            lbl_803EA6F8 = 1;
        }
        break;
    case 105:
        if (fn_801486A0()) {
            Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
            if (!lbl_803EA6F9 || fn_80073310() == 7) fn_80072AEC(8);
            lbl_803EA6F9 = 0;
            fn_8006F394(7, player->mIdBytes[2]);
            lbl_803EA6F8 = 0;
        }
        break;
    case 175:
        lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
        fn_8006C854(lbl_803EA6D4 + 10, &p->mPos);
        break;
    case 43: fn_8007184C(&p->mPos); break;
    case 37: {
        unsigned int amount = p->mUnknown10.mValue;
        int state = p->mUnknown14;
        int previous = p->mUnknown18;
        fn_8006F550();
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        float value = (float)amount;
        int id;
        if (((unsigned int)state <= 1 || state == 3 || state == 5 || state == 7) &&
            ((unsigned int)previous <= 1 || previous == 3 || previous == 5 || previous == 7)) {
            if (!(value <= lbl_803ECB08 * lbl_80290B58.mStrong)) {
                lbl_803EA6D2 = (lbl_803EA6D2 + 1) % 2;
                id = lbl_803EA6D2 + 6;
            } else if (value > lbl_803ECB08 * lbl_80290B58.mThreshold) {
                lbl_803EA6D3 = (lbl_803EA6D3 + 1) % 2;
                id = lbl_803EA6D3 + 8;
            } else {
                lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
                id = lbl_803EA6D4 + 10;
            }
        } else {
            if (!(value <= lbl_803ECB08 * lbl_80290B58.mStrong)) {
                lbl_803EA6D3 = (lbl_803EA6D3 + 1) % 2;
                id = lbl_803EA6D3 + 8;
            } else {
                lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
                id = lbl_803EA6D4 + 10;
            }
        }
        fn_8006C854(id, &p->mPos);
        if ((unsigned int)(id - 6) <= 1) {
            fn_8006F0B8(4);
            if (!fn_8006CC54(60)) fn_8006C854(60, &p->mPos);
            fn_80071914(&p->mPos);
        }
        if ((unsigned int)(id - 10) > 1) {
            int eligible = 0;
            if (player && (player->mFlags & 0x10000000)) {
                Point_8017886C point = fn_80177FE0();
                if (!(player->mMotion.mPos.mY >= point.mY) && fn_801650DC(fn_8016871C(fn_80178348()))) eligible = fn_80137B40() == player;
            }
            if (eligible) fn_8006F394(8, player->mIdBytes[2]);
        }
        break;
    }
    case 124: fn_8017886C(); break;
    case 139:
        fn_8006F824(50);
        fn_8006BC30(4, (unsigned char)p->mUnknown18);
        if (lbl_803EA6F8) {
            fn_80072AEC(8);
            lbl_803EA6F8 = 0;
        }
        break;
    }
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
