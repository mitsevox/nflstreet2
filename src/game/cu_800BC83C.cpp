#include "game/Class_80297BF8.h"
#include "game/Object_800785C0.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8007F828.h"
#include "game/fn_80096A58.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

struct Slot_800BAE7C {
    int mUnknown0;
    unsigned char mUnknown4[3];
    unsigned char mTeam;
    Object_80039F5C *mpObject;
};

struct Record_800BAE7C {
    int mUnknown0;
    Slot_800BAE7C mSlots[4];
    unsigned char mUnknown34[12];
    int mUnknown40;
    int mUnknown44;
    float mUnknown48;
    unsigned char mUnknown4C;
    unsigned char mUnknown4D[3];
};

struct Block_800BC538 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    Record_800BAE7C *mpUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    signed char mUnknown2A;
    unsigned char mUnknown2B;
    int mUnknown2C;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
};

struct Stick_800BD608 {
    float mX;
    float mY;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

struct Slot_800BFAD0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    Stick_800BD608 mStick;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A[2];
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
};

struct Block_800BFAD0 {
    Slot_800BFAD0 mSlots[2];
    int mUnknown40;
    int mUnknown44;
    unsigned char mUnknown48[0x50];
    int mUnknown98;
    int mUnknown9C;
    int mUnknownA0;
    short mUnknownA4;
    short mUnknownA6;
    unsigned char mUnknownA8;
    unsigned char mUnknownA9[2];
    unsigned char mUnknownAB;
    unsigned int mUnknownAC;
    int mUnknownB0;
    int mUnknownB4;
    int mUnknownB8;
    int mUnknownBC;
    int mUnknownC0;
    unsigned char mUnknownC4;
    unsigned char mUnknownC5;
    unsigned char mUnknownC6;
    unsigned char mUnknownC7;
};

extern "C" {
unsigned char fn_8002892C(void);
unsigned char fn_8002D060(Type_803EA368 *p);
int fn_80025708(void);
void fn_8003A3F4(int a, int index);
void fn_8003E174(int a);
void fn_8004A230(unsigned char value);
int fn_80074638(void);
int fn_80076F40(int index);
void fn_800941B8(void);
float fn_80094454(int handle);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
int fn_800A3444(void);
void fn_800A7514(int team);
int fn_800A8444(int team);
int fn_800A8488(int team);
int fn_800A937C(void);
int fn_800AE968(int index);
void fn_800AFE20(void (*pCallback)(int, unsigned int, float));
void fn_800B0E68(void);
void fn_800B0EB8(void);
void fn_800B0F28(void);
int fn_800B0F98(void);
int fn_800B146C(void);
Object_80039F5C *fn_800B6544(int index);
int fn_800B6644(int index);
void fn_800B6868(int a, int b, int c, int d);
int fn_800BA6F8(void);
void fn_800BAAE4(void);
void fn_800BAE7C(Record_800BAE7C *p, int index);
int fn_800BAF30(void);
void fn_800BAFE8(void);
int fn_800BB050(int value);
void fn_800BB5DC(void);
void fn_800BB694(int a, unsigned int b, float c);
void fn_800BB924(void);
void fn_800BB9A0(int, float);
void fn_800BB9A4(int team, int value);
void fn_800BBA2C(void);
void fn_800BBCF0(Record_800BAE7C *p);
void fn_800BBE98(void);
void fn_800BBF18(void);
void fn_800BD1C8(Record_800BAE7C *pRecords);
void fn_800BD35C(void);
void fn_800BD958(void);
void fn_800BE808(int index, int team);
void fn_800BE944(int team, int index, unsigned int msg, float value);
unsigned char fn_800C0658(void);
int fn_800C1E40(void);
void fn_800CC560(int a);
void fn_8010A220(void);
void fn_80139274(void);
void fn_8013C824(Camera_8013F738 *pCamera, int msg, int arg);
void fn_8013F9B8(void);
Camera_8013F738 *fn_8013FA04(int index);
int fn_801485D4(void);
int fn_801486A0(void);
int fn_80156704(void);
void fn_8016E498(void);
int fn_8016E764(void);
void fn_801780A8(Point_8017886C pos);
void fn_801782B0(void);
int fn_80178308(void);
int fn_80178320(void);
void fn_801789F8(void);
float fn_80178A2C(void);
void fn_80178CD8(int a);
int fn_80178E10(void);
void fn_8017D764(void);
void fn_8017DBCC(void);
void fn_8017DD68(int index);
int fn_8017F60C(void);
int fn_8019623C(int id);
int fn_801C6280(int a, int b, void *p);
int fn_801F0F18(int a);

extern unsigned char lbl_802ED104[];
extern unsigned char lbl_803EAB94;
extern unsigned char lbl_803EAB95;
extern unsigned char lbl_803EABA0;
extern unsigned char lbl_803EABA2;
extern unsigned char lbl_803EABA3;
extern Block_800BFAD0 *lbl_803EABA8;
extern unsigned char lbl_803EABB4;
extern Block_800BC538 *lbl_803EC98C;
}

extern "C" void fn_800BC83C(void)
{
    lbl_803EABA2 = 0;
    lbl_803EABA3 = 0;
    if (fn_800655F8() == 0) {
        fn_800655D0();
    }
    fn_800655B8();
    if (lbl_803EAB94 == 0) {
        fn_800BBF18();
    }
    if (lbl_803EC98C->mUnknown4 == 2.0f) {
        fn_800BAFE8();
        fn_800BAE7C(lbl_803EC98C->mpUnknown10, lbl_803EAB95);
        fn_800BD1C8(lbl_803EC98C->mpUnknown10);
    }
}

extern "C" void fn_800BC8E0(void)
{
    int busy = fn_800BAF30();

    lbl_803EC98C->mUnknown24++;
    if (fn_800BB050(busy) != 0) {
        lbl_803EAB95++;
        lbl_803EC98C->mUnknown24 = 0;
        if (lbl_803EC98C->mpUnknown10[lbl_803EAB95].mUnknown0 == 9999) {
            fn_800BBE98();
        } else {
            fn_800BBA2C();
            fn_800BBCF0(lbl_803EC98C->mpUnknown10);
            fn_800BB924();
            fn_800BAE7C(lbl_803EC98C->mpUnknown10, lbl_803EAB95 + 1);
            fn_800BD1C8(lbl_803EC98C->mpUnknown10);
        }
    }
    if (lbl_803EABA2 == 0 && lbl_803EC98C->mpUnknown10[lbl_803EAB95 + 1].mUnknown0 == 9999) {
        float time = fn_80094454(lbl_803EC98C->mUnknown18);

        if (time > 0.0f && time <= 61.0f) {
            fn_80195EFC(6, 60, 0, fn_800BB9A0);
            lbl_803EABA2 = 1;
        }
    }
}

extern "C" void fn_800BCC30(Class_80297BF8 *pThis)
{
    if (fn_800AE968(14) != 0 || fn_8002892C() != 0 || fn_8017F60C() != 0 ||
        fn_80156704() != 0 || fn_801485D4() != 0 || fn_8007F828(14) != 1) {
        pThis->vfn_07();
    }
    lbl_803EC98C->mUnknown32 = 0;
    fn_8004A230(1);
    fn_8013F9B8();
    fn_800CC560(0);
    fn_8010A220();
    if (fn_80025708() != 0) {
        Point_8017886C pos = {0.0f, 0.0f};
        int spot = fn_800785C0()->mUnknown1C0;

        if (spot != -1) {
            if (spot < 50) {
                pos.mY = -(fn_80178A2C() * ((50 - spot) / 50.0f));
            } else {
                pos.mY = fn_80178A2C() * ((spot - 50) / 50.0f);
            }
        } else {
            pos.mY = 7.0f - fn_80178A2C();
        }
        fn_801780A8(pos);
        fn_801782B0();
        if (fn_800785C0()->mUnknown1A4 != 0) {
            fn_8009D964(4, fn_800785C0()->mUnknown1A4);
            fn_8009D8CC(4);
        }
    } else {
        fn_80178CD8(1);
        fn_8017886C()->mUnknown04 = 1;
        Point_8017886C spot = fn_80177FE0();
        fn_8017886C()->mUnknown08.mX = spot.mX;
        fn_8017886C()->mUnknown08.mY = spot.mY;
    }
    fn_800941B8();
    fn_8017D764();
    if (fn_800BA6F8() != 0) {
        fn_800BAAE4();
    } else {
        fn_80139274();
    }
    fn_800AFE20(fn_800BB694);
    fn_80067D4C(0x6e, 0);
    if (fn_80076F40(0) != 0) {
        fn_80067DB8(0x6d, 0, 0, 0, 0);
    }
    if (fn_80076F40(1) != 0) {
        fn_80067DB8(0x6d, 0, 1, 0, 0);
    }
    lbl_803EABA0 = 0;
    fn_801789F8();
    if (fn_800BA6F8() == 0) {
        fn_800BB9A4(1, 1);
    }
    lbl_803EC98C->mUnknown24 = 0;
    lbl_803EC98C->mUnknown30 = 0;
    lbl_803EC98C->mUnknown31 = 0;
    lbl_803EC98C->mUnknown28 = 0;
    lbl_803EAB95 = 0;
    fn_801383E4(1);
    fn_800BB5DC();
    fn_8003E174(1);
    if (lbl_803EC98C->mUnknown8 != -1) {
        fn_80096D14(lbl_803EC98C->mUnknown8);
    }
    fn_8017DBCC();
    if (fn_800C1E40() == 0 && fn_80025708() == 0 && fn_8019623C(0x23000) != 0) {
        fn_80195EFC(5, 100, 0, 0);
    }
}

extern "C" void fn_800BCF7C(void)
{
    Params_80096A58 crowd;
    Params_80096A58 ambience;

    fn_801C1F94(&crowd, 0, sizeof(crowd));
    crowd.mUnknown40 = 0xFFFF;
    crowd.mUnknown42 = 0xFFFF;
    fn_801C1F94(&ambience, 0, sizeof(ambience));
    ambience.mUnknown40 = 0xFFFF;
    ambience.mUnknown42 = 0xFFFF;
    switch (fn_800A3444()) {
    case 0:
        crowd.mUnknown0 = 14;
        ambience.mUnknown0 = 12;
        break;
    case 2:
        crowd.mUnknown0 = 2;
        ambience.mUnknown0 = 0;
        break;
    case 3:
        crowd.mUnknown0 = 26;
        ambience.mUnknown0 = 24;
        break;
    case 1:
        crowd.mUnknown0 = 20;
        ambience.mUnknown0 = 18;
        break;
    case 4:
        crowd.mUnknown0 = 8;
        ambience.mUnknown0 = 6;
        break;
    case 5:
        crowd.mUnknown0 = 33;
        ambience.mUnknown0 = 31;
        break;
    case 6:
        crowd.mUnknown0 = 36;
        ambience.mUnknown0 = 34;
        break;
    case 7:
        crowd.mUnknown0 = 30;
        ambience.mUnknown0 = 28;
        break;
    case 8:
        crowd.mUnknown0 = 11;
        ambience.mUnknown0 = 9;
        break;
    case 10:
        crowd.mUnknown0 = 17;
        ambience.mUnknown0 = 15;
        break;
    case 9:
        crowd.mUnknown0 = 5;
        ambience.mUnknown0 = 3;
        break;
    case 11:
        crowd.mUnknown0 = 23;
        ambience.mUnknown0 = 21;
        break;
    default:
        crowd.mUnknown0 = 5;
        ambience.mUnknown0 = 3;
        break;
    }
    crowd.mUnknown20 = 2;
    crowd.mUnknown24 = 0;
    crowd.mUnknown28 = fn_802372EC(1, 2);
    crowd.mUnknown32 = 300.0f;
    ambience.mUnknown20 = 2;
    ambience.mUnknown24 = 0;
    crowd.mUnknown12 |= 0x50;
    ambience.mUnknown12 |= 0x10;
    ambience.mUnknown32 = 300.0f;
    ambience.mUnknown28 = 0;
    lbl_803EC98C->mUnknown8 = fn_80096A58(&crowd);
    fn_801F0F18(0);
    if (lbl_803EC98C->mUnknown8 != -1) {
        fn_80096B1C(lbl_803EC98C->mUnknown8);
    }
    lbl_803EC98C->mUnknownC = fn_80096A58(&ambience);
    fn_801F0F18(0);
}

extern "C" float fn_800BD190(void)
{
    float result = 0.1f;

    if (lbl_803EC98C->mpUnknown10 != 0) {
        result = lbl_803EC98C->mpUnknown10[lbl_803EAB95].mUnknown48;
    }
    return result;
}

extern "C" int fn_800BD608(Stick_800BD608 *pStick, int team)
{
    Camera_8013F738 *pCamera = fn_8013FA04(5);
    int result = 0;
    float value;

    if (fn_802270A4(pStick) == 0.0f) {
        if (pStick->mUnknown9 == 1) {
            fn_8013C824(pCamera, 10, 0);
        }
    } else {
        result = 1;
        if (pStick->mUnknown9 == 1) {
            fn_8013C824(pCamera, 10, 0);
            value = pStick->mX;
            if (value != 0.0f) {
                if (value < 0.0f) {
                    value = -value;
                    fn_8013C824(pCamera, 9, (int)&value);
                } else {
                    fn_8013C824(pCamera, 8, (int)&value);
                }
            }
            value = pStick->mY;
            if (value != 0.0f) {
                fn_8013C824(pCamera, 7, (int)&value);
            } else {
                result = 0;
            }
        } else if (fn_8017F60C() != 0 && lbl_803EABA8->mSlots[team].mUnknown0 == 4 &&
                   pStick->mY == 0.0f) {
            result = 0;
        }
    }
    if (pStick->mUnknown8 == 0) {
        fn_8003A3F4(0, team);
    } else {
        fn_8003A3F4(1, team);
        result = 1;
    }
    return result;
}

extern "C" void fn_800BDB14(int index, unsigned int msg, float value)
{
    int twoPlayer = fn_801486A0() == 2;
    Object_80039F5C *pObject = fn_800B6544(index);
    int valid = pObject != 0 && pObject->mUnknown8 != 255;
    int team;
    int other;
    int side;
    int involved;

    team = fn_80178308();
    other = fn_80178320();
    if (index == 255) {
        side = other;
        if (fn_800B65A0(team) == 255) {
            side = team;
        }
        involved = 1;
    } else {
        involved = 0;
        side = fn_800B6644(index);
        if (fn_800B65A0(team) == index || fn_800B65A0(other) == index) {
            involved = 1;
        }
    }
    switch (msg) {
    case 0x59: {
        int ok = 0;

        if (involved && side == team && lbl_803EABA8->mUnknownC5 != 0) {
            if (fn_800C0658() != 0) {
                ok = 1;
            } else {
                ok = fn_8016E764();
            }
        }
        if (ok && fn_800B146C() != 0) {
            int ref = fn_800B0F98();
            Object_80039F5C *pCarrier = fn_8009BCE8(&ref);
            Point_8017886C spot = fn_80177FE0();

            if (!(__builtin_fabsf(pCarrier->mMotion.mPos.mX + spot.mX) >= 4.0f)) {
                ok = 0;
            }
        }
        if (ok == 1) {
            fn_8016E498();
        } else {
            fn_800BD958();
        }
        break;
    }
    case 0x5A:
        if (fn_80178E10() != 0 && fn_8002D060(lbl_803EA368) == 0 && fn_800BA6F8() == 0 &&
            fn_800A937C() == 0 && involved && (side != other || !twoPlayer)) {
            lbl_803EABA8->mSlots[side].mUnknown0 = 1;
            fn_801C6280(index, 3, lbl_802ED104);
            fn_8017DD68(side);
        }
        break;
    case 0x5B:
        if (involved && fn_800A8444(side) == 0 && fn_800A8488(side) != 0) {
            int blocked = 0;

            if (fn_80156704() != 0) {
                blocked = fn_80074638() == 0;
            }
            if (!blocked) {
                fn_800A7514(side);
                lbl_803EABA8->mUnknownB0 = side;
                fn_800BD35C();
                lbl_803EABB4 = 0;
            }
        }
        break;
    case 6:
        if (other == fn_800B6644(index) || !involved) {
            Object_80039F5C *p = fn_800B6544(index);

            fn_800B6868((unsigned char)(p->mId >> 8), (unsigned char)(p->mId >> 16), p->mUnknown8, 0);
        }
        break;
    case 9:
        if (other == fn_800B6644(index) || !involved) {
            Object_80039F5C *p = fn_800B6544(index);

            fn_800B6868((unsigned char)(p->mId >> 8), (unsigned char)(p->mId >> 16), p->mUnknown8, 1);
        }
        break;
    case 0x64:
        if (team == side && involved && lbl_803EABA8->mUnknownC5 != 0) {
            if (fn_800B0F98() == 0) {
                fn_800B0E68();
            }
            if (value < 0.0f) {
                fn_800B0F28();
            } else {
                fn_800B0EB8();
            }
        }
        break;
    case 0x61:
        if (team == side && (involved || (twoPlayer && valid)) && lbl_803EABA8->mUnknownC5 != 0) {
            if (fn_800B0F98() == 0) {
                fn_800B0E68();
            }
            fn_800B0F28();
        }
        break;
    case 0x62:
        if (team == side && (involved || (twoPlayer && valid)) && lbl_803EABA8->mUnknownC5 != 0) {
            if (fn_800B0F98() == 0) {
                fn_800B0E68();
            }
            fn_800B0EB8();
        }
        break;
    case 0x60:
    case 0x63:
        break;
    case 0x84:
    case 0x85:
        if (fn_8002D060(lbl_803EA368) == 0 && involved == 1 && !twoPlayer && value != 0.0f &&
            lbl_803EABA8->mUnknownC0 <= 0) {
            fn_800BE808(index, side);
            fn_800BE944(side, index, msg, value);
        }
        break;
    }
}
