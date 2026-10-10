#include <string.h>
#include <math.h>
#include "game/cu_8017DD68.h"
#include "game/Object_8007A334.h"
#include "game/Entry_80219044.h"
#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"
#include "game/cu_80067C10.h"
#include "game/cu_8003108C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_80238174.h"

enum Code_800D0F98 {};

struct Record_8018FC1C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    int mUnknown28;
    int mUnknown32;
    unsigned char mUnknown36;
    int mUnknown40;
    int mUnknown44;
    int mUnknown48;
};
struct Step_800D1788 {
    int mUnknown0;
    Code_800D0F98 mUnknown4;
    int mUnknown8;
    char mUnknownC[4];
    unsigned int mUnknown10;
    unsigned char mUnknown14;
    unsigned int mUnknown18;
};
struct Increment_800D1788 {
    unsigned char mUnknown0;
    int mUnknown4;
    char mUnknown8[4];
    unsigned int mUnknownC;
};
struct Table_800D1788 {
    Increment_800D1788 *mpUnknown0;
    Step_800D1788 *mpUnknown4;
};

/* Partial view of the 0x2070-byte block that 0x800D7438 registers under the
   id 'trck' with lbl_803EACD4 as its pointer; unaccessed regions remain
   opaque. */
struct State_800D0D4C {
    Record_8018FC1C mUnknown0[127];
    char mUnknown19CC[156];
    int mUnknown1A68;
    int mUnknown1A6C;
    int mUnknown1A70;
    int mUnknown1A74;
    int mUnknown1A78;
    int mUnknown1A7C;
    unsigned short mUnknown1A80[127];
    unsigned short mUnknown1B7E[127];
    char mUnknown1C7C[80];
    Entry_80219044 mUnknown1CCC;
    char mUnknown1CD8[251];
    char mUnknown1DD3[251];
    unsigned char mUnknown1ECE;
    char mUnknown1ECF[6];
    unsigned char mUnknown1ED5;
    unsigned char mUnknown1ED6;
    unsigned char mUnknown1ED7;
    unsigned char mUnknown1ED8;
    unsigned char mUnknown1ED9;
    unsigned char mUnknown1EDA;
    unsigned char mUnknown1EDB;
    unsigned char mUnknown1EDC;
    unsigned char mUnknown1EDD;
    unsigned char mUnknown1EDE;
    unsigned char mUnknown1EDF;
    unsigned char mUnknown1EE0;
    unsigned char mUnknown1EE1;
    unsigned char mUnknown1EE2;
    unsigned char mUnknown1EE3;
    unsigned char mUnknown1EE4;
    unsigned char mUnknown1EE5;
    unsigned char mUnknown1EE6;
    unsigned char mUnknown1EE7;
    unsigned char mUnknown1EE8;
    unsigned char mUnknown1EE9;
    unsigned char mUnknown1EEA;
    unsigned char mUnknown1EEB;
    unsigned char mUnknown1EEC;
    unsigned char mUnknown1EED;
    unsigned char mUnknown1EEE;
    unsigned char mUnknown1EEF;
    unsigned char mUnknown1EF0;
    unsigned char mUnknown1EF1;
    unsigned char mUnknown1EF2;
    unsigned char mUnknown1EF3;
    unsigned char mUnknown1EF4;
    unsigned char mUnknown1EF5;
    unsigned char mUnknown1EF6;
    unsigned char mUnknown1EF7;
    unsigned char mUnknown1EF8;
    unsigned char mUnknown1EF9;
    unsigned char mUnknown1EFA;
    unsigned char mUnknown1EFB;
    unsigned char mUnknown1EFC;
    unsigned char mUnknown1EFD;
    unsigned char mUnknown1EFE;
    unsigned char mUnknown1EFF;
    unsigned char mUnknown1F00;
    unsigned char mUnknown1F01;
    unsigned char mUnknown1F02;
    unsigned char mUnknown1F03;
    unsigned char mUnknown1F04;
    unsigned char mUnknown1F05;
    unsigned char mUnknown1F06;
    unsigned char mUnknown1F07;
    unsigned char mUnknown1F08;
    unsigned char mUnknown1F09;
    unsigned char mUnknown1F0A;
    unsigned char mUnknown1F0B;
    char mUnknown1F0C[1];
    unsigned char mUnknown1F0D;
    char mUnknown1F0E[2];
    unsigned char mUnknown1F10;
    unsigned char mUnknown1F11;
    unsigned char mUnknown1F12;
    unsigned char mUnknown1F13;
    float mUnknown1F14;
    unsigned int mUnknown1F18;
    Object_80039F5C *mpUnknown1F1C[4];
    int mUnknown1F2C;
    int mUnknown1F30;
    int mUnknown1F34;
    int mUnknown1F38;
    int mUnknown1F3C;
    Object_80039F5C *mpUnknown1F40;
    int mUnknown1F44;
    int mUnknown1F48;
    int mUnknown1F4C;
    unsigned char mUnknown1F50;
    char mUnknown1F51[3];
    int mUnknown1F54;
    int mUnknown1F58;
    unsigned char mUnknown1F5C;
    char mUnknown1F5D[1];
    unsigned char mUnknown1F5E;
    unsigned char mUnknown1F5F;
    unsigned char mUnknown1F60;
    unsigned char mUnknown1F61;
    unsigned char mUnknown1F62;
    unsigned char mUnknown1F63;
    unsigned char mUnknown1F64;
    char mUnknown1F65[3];
    Object_80039F5C *mpUnknown1F68;
    Object_80039F5C *mpUnknown1F6C;
    int mUnknown1F70;
    int mUnknown1F74;
    int mUnknown1F78;
    unsigned char mUnknown1F7C;
    unsigned char mUnknown1F7D;
    char mUnknown1F7E[2];
    int mUnknown1F80[2];
    char mUnknown1F88[2][80];
    int mUnknown2028[2];
    int mUnknown2030[2];
    int mUnknown2038[2];
    int mUnknown2040[2];
    int mUnknown2048[2];
    int mUnknown2050[4];
    Object_80039F5C *mpUnknown2060;
    unsigned char mUnknown2064[2];
    char mUnknown2066[2];
    Object_80039F5C *mpUnknown2068;
    unsigned char mUnknown206C;
    char mUnknown206D[3];
};


extern "C" {
typedef void (*Callback_800D7604)(int, int, const char *, int, int, int, int);
extern Callback_800D7604 lbl_803EACC0;
extern unsigned char lbl_803EACC4;
extern unsigned char lbl_803EACC5;
extern int lbl_803EACC8;
extern int lbl_803EACD0;
extern State_800D0D4C *lbl_803EACD4;
extern unsigned char lbl_803EACD8;
extern int lbl_803EC9A4[2];
extern int lbl_803EC9AC[2];
extern unsigned char lbl_803EC9B4[2], lbl_803EC9B8[2], lbl_803EC9BC[2], lbl_803EC9C0[2];
extern unsigned char lbl_803EC9C4[2], lbl_803EC9C8[2];
extern unsigned char lbl_803EC9D4[2], lbl_803EC9D8[2], lbl_803EC9DC[2];
extern const Table_800D1788 lbl_80298140[];
extern const char lbl_802981A8[][80];
extern const char lbl_8029C6B8[][20];
extern const char lbl_803ED6C0[4], lbl_803ED6C4[1];
extern float lbl_803EACCC;
extern unsigned char lbl_803EC9CC[2];
extern unsigned char lbl_803EC9D0[2];
extern void *lbl_803EB688;

int fn_80025708(void);
struct Object_800785C0;
Object_800785C0 *fn_800785C0(void);
int fn_800254E8(Object_800785C0 *, int, int *);
void fn_800A20D0(int, signed char);
float fn_800A32B4(void);
void fn_800A72B4(void);
void fn_800A7B5C(void);
Object_80039F5C *fn_801244F0(Object_80039F5C *, int, int, unsigned char, float *, int);
Object_80039F5C *fn_801245DC(Object_80039F5C *, int, int, unsigned char, int, float *, int);
float fn_80178A2C(void);
Point_8017886C fn_80178070(void);
int fn_801787DC(int);
void fn_8017E3CC(int);
int fn_80186F7C(unsigned char);
int fn_8022F358(int);
void fn_8008880C(int, unsigned int);
void fn_8018FB4C(Object_8007A334 *, int);
void fn_8018FBC8(Object_8007A334 *);
int fn_8018FBE8(Object_8007A334 *, int);
void fn_8018FC1C(Object_8007A334 *, Record_8018FC1C *);
void fn_8017C5A0(unsigned short, int);
void fn_8017C5CC(unsigned short, int);
void fn_8017C5F8(unsigned short, int);
void fn_8017C648(unsigned short, int);
void fn_8017C6A0(unsigned short, int);
void fn_8017C6CC(unsigned short, int, int);
void fn_8017C724(unsigned short, int);
void fn_8017C750(unsigned short, int, int);
void fn_8017C7A8(unsigned short, int);
void fn_8017C7D4(unsigned short, int);
void fn_8017C800(unsigned short, int);
void fn_8017C82C(unsigned short, int);
void fn_8017C884(unsigned short, int);
void fn_8017C8DC(unsigned short, int);
void fn_8017C908(unsigned short, int);
void fn_8017C98C(unsigned short, int);

unsigned char fn_80054D24(int index);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800A7A0C(int team);
int fn_800A8444(int team);
int fn_800A8488(int team);
int fn_800A84C8(void);
int fn_800A8740(void);
int fn_800A8F84(unsigned char index);
void fn_800AE7F0(int a, int b, Object_80039F5C *p);
void fn_800B1698(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
void fn_80156C78(int a, int b);
int fn_801650DC(Record_80067338 *pRecord);
int fn_80177C38(void);
int fn_80177F70(void);
int fn_80177F7C(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
Object_80039F5C *fn_8017876C(void);
int fn_801787A0(void);
int fn_801788D8(int *pValue);
int fn_80179138(void);
void fn_8017C674(unsigned short team, int value);
void fn_8017C9B8(unsigned short team, int value);
void fn_8017C9E4(unsigned short team, int value);
void fn_8017CA10(unsigned short team, int value);
void fn_8017CA68(unsigned short team, int value);
int fn_801BE648(void *p);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);

int fn_800D0B90(Object_80039F5C *p);
void fn_800D0D48(int a);
void fn_800D1A90(int, int, int, int, int, int, int, int, int, int);
unsigned short fn_800D3EB0(int, int);
void fn_800D3EDC(int, int, unsigned short);
int fn_800D3F08(int);
void fn_800D3FBC(int, int, int);
int fn_800D41F8(int);
void fn_800D421C(int, int);
void fn_800D2108(int, int, int, int);
void fn_800D2280(void);
void fn_800D1634(int a, int b, int c, int d);
void fn_800D1788(int a, int b, int c, int *p0, int *p1, int *p2, int *p3, int *p4, int *p5, int *p6);
void fn_800D1D84(int a, int b, int c);
void fn_800D20A0(int a, int b);
void fn_800D2378(int a, int b, int c);
void fn_800D59C8(int a);
void fn_800D5A28(void);
int fn_800D5A6C(int a, int b, int c);
void fn_800D7158(void);

void fn_800D0D4C(int i);
void fn_800D0DBC(int i, int a, int b);
void fn_800D0E64(int i, const char *pName, int a, int b, int c, int mode, int d);
int fn_800D0F98(Code_800D0F98 a);
void fn_800D1500(int i, const char *pName, int a, int mode);
void fn_800D15E8(int i, int a);
void fn_800D1700(int i);
int fn_800D207C(int i);
void fn_800D2C10(int a, int b);
void fn_800D2C9C(int a);
void fn_800D2D64(void);
void fn_800D2DF0(void);
void fn_800D2E50(void);
int fn_800D2EB0(int a);
void fn_800D2F9C(int a, int b);
void fn_800D3094(void);
void fn_800D30D0(void);
void fn_800D310C(void);
void fn_800D3238(void);
void fn_800D338C(void);
void fn_800D3294(int, unsigned int);
void fn_800D3400(void);
void fn_800D343C(void);
void fn_800D3560(void);
void fn_800D35D4(void);
void fn_800D3648(void);
void fn_800D371C(void);
void fn_800D378C(void);
int fn_800D3850(int a);
void fn_800D391C(int a);
void fn_800D3C00(int a);
int fn_800D3C80(void);
int fn_800D3CC0(void);
}

extern "C" void fn_800D0D4C(int i) {
    fn_800D0D48(86);
    lbl_803EACD4->mUnknown1F88[i][0] = 0;
    lbl_803EACD4->mUnknown2028[i] = 0;
    lbl_803EACD4->mUnknown2038[i] = 0;
    lbl_803EACD4->mUnknown2040[i] = 0;
    lbl_803EACD4->mUnknown2048[i] = 0;
}

extern "C" void fn_800D0DBC(int i, int a, int b) {
    if (lbl_803EACC4) {
        fn_800D0D48(87);
        if (a && lbl_803EACD4->mUnknown2040[i]) {
            fn_800D15E8(i, lbl_803EACD4->mUnknown2040[i]);
        }
        if (b && lbl_803EACD4->mUnknown2038[i]) {
            fn_800D1500(i, lbl_803EACD4->mUnknown1F88[i], lbl_803EACD4->mUnknown2038[i],
                        lbl_803EACD4->mUnknown2030[i]);
        }
    }
}

extern "C" void fn_800D0E64(int i, const char *pName, int a, int b, int c, int mode, int d) {
    switch (mode) {
    case 1:
        fn_800D0D48(85);
        break;
    case 0:
        fn_800D0D48(82);
        break;
    case 3:
        fn_800D0D48(83);
        break;
    case 2:
        fn_800D0D48(84);
        break;
    }
    if (strlen(pName) < 80) {
        lbl_803EACD4->mUnknown2028[i]++;
        lbl_803EACD4->mUnknown2038[i] += a;
        lbl_803EACD4->mUnknown2040[i] = c;
        lbl_803EACD4->mUnknown2048[i] = b;
        lbl_803EACD4->mUnknown2048[i == 0] = d;
        strcpy(lbl_803EACD4->mUnknown1F88[i], pName);
        if (lbl_803EACD4->mUnknown2028[i] == 1) {
            lbl_803EACD4->mUnknown2030[i] = mode;
        } else if (lbl_803EACD4->mUnknown2030[i] != 3) {
            lbl_803EACD4->mUnknown2030[i] = mode;
        }
    }
}

extern "C" int fn_800D0F98(Code_800D0F98 a) {
    switch (a) {
    case 104:
        switch (lbl_803EACD4->mUnknown1F50) {
        case 0:
            return 105;
        case 1:
            return 106;
        case 2:
            return 107;
        case 3:
            return 108;
        case 4:
            return 109;
        case 5:
            return 110;
        case 6:
            return 111;
        case 7:
            return 112;
        case 8:
            return 113;
        case 9:
            return 114;
        case 10:
            return 115;
        case 11:
            return 116;
        case 12:
            return 117;
        case 13:
            return 118;
        case 14:
            return 119;
        case 15:
            return 120;
        case 16:
            return 121;
        case 17:
            return 122;
        case 18:
            return 123;
        case 19:
            return 124;
        case 20:
            return 125;
        case 21:
            return 126;
        case 22:
            return 127;
        case 23:
            return 128;
        case 24:
            return 129;
        case 25:
            return 130;
        case 26:
            return 131;
        case 27:
            return 132;
        case 28:
            return 133;
        case 29:
            return 134;
        case 30:
            return 135;
        case 31:
            return 136;
        case 32:
            return 103;
        default:
            return 103;
        }
    case 10:
        switch (lbl_803EACD4->mUnknown1F5C) {
        case 2:
            return 16;
        case 3:
            return 22;
        case 4:
            return 14;
        case 5:
            return 18;
        case 6:
            return 20;
        default:
            return 8;
        }
    case 11:
        switch (lbl_803EACD4->mUnknown1F5C) {
        case 2:
            return 17;
        case 3:
            return 23;
        case 4:
            return 15;
        case 5:
            return 19;
        case 6:
            return 21;
        default:
            return 9;
        }
    case 60:
        switch (lbl_803EACD4->mUnknown1F5E) {
        case 0:
            return 61;
        case 1:
            return 62;
        case 4:
            return 63;
        case 5:
            return 64;
        case 8:
            return 65;
        case 9:
            return 66;
        case 12:
            return 67;
        case 13:
            return 68;
        case 16:
            return 69;
        case 17:
            return 70;
        default:
            return 59;
        }
    case 72:
        switch (lbl_803EACD4->mUnknown1F5E) {
        case 0:
            return 73;
        case 1:
            return 74;
        case 4:
            return 75;
        case 5:
            return 76;
        case 8:
            return 77;
        case 9:
            return 78;
        case 12:
            return 79;
        case 13:
            return 80;
        case 16:
            return 81;
        case 17:
            return 82;
        default:
            return 71;
        }
    case 85:
        switch (lbl_803EACD4->mUnknown1F5F) {
        case 0:
            return 87;
        case 1:
            return 88;
        case 2:
            return 89;
        case 3:
            return 90;
        case 4:
            return 91;
        case 5:
            return 92;
        case 6:
            return 93;
        case 7:
            return 94;
        case 8:
            return 95;
        default:
            return 86;
        }
    }
    return a;
}

extern "C" void fn_800D1500(int i, const char *pName, int a, int mode) {
    Arg_8021D7B8 args[4];

    if (lbl_803EACC4) {
        strcpy(lbl_803EACD4->mUnknown1C7C, pName);
        switch (mode) {
        case 1:
            fn_800D0D48(81);
            break;
        case 0:
            fn_800D0D48(78);
            break;
        case 3:
            fn_800D0D48(79);
            break;
        case 2:
            fn_800D0D48(80);
            break;
        }
        args[0].i = i;
        args[1].p = &lbl_803EACD4->mUnknown1CCC;
        ((Entry_80219044 *)args[1].p)->mpText = lbl_803EACD4->mUnknown1C7C;
        ((Entry_80219044 *)args[1].p)->mLength = strlen(lbl_803EACD4->mUnknown1C7C);
        args[2].i = a;
        args[3].i = mode;
        fn_8021D7B8(lbl_803EB688, 0x80000013, 4, args);
    }
}

extern "C" void fn_800D15E8(int i, int a) {
    Arg_8021D7B8 args[2];

    if (lbl_803EACC4) {
        args[0].i = i;
        args[1].i = a;
        fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
    }
}

extern "C" void fn_800D1634(int side, int value, int a, int b) {
    if (lbl_803EACC4 && fn_800A8740() == 0) {
        float t;
        if (value == 0) t = 0.0f;
        else if (value >= lbl_803EACD0) t = 1.0f;
        else t = (float)value / (float)lbl_803EACD0;
        fn_8017DE54((unsigned char)side, t, a, b);
    }
}

extern "C" void fn_800D1700(int i) {
    Entry_80219044 *args[1];

    if (lbl_803EACC4) {
        args[0] = &lbl_803EACD4->mUnknown1CCC;
        args[0]->mpText = i == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3;
        args[0]->mLength = strlen(i == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3);
        fn_8021D7B8(lbl_803EB688, 0x80000018, 1, args);
    }
}

extern "C" void fn_800D1788(int side, int id, int count, int *pScaled, int *pSubtract, int *pValue, int *pText, int *pExtra, int *pMode, int *pName) {
    Record_8018FC1C *record = &lbl_803EACD4->mUnknown0[id];
    int subtract, value, mode, name;
    unsigned int threshold = 0;
    if (record->mUnknown20 == -1) {
        subtract = record->mUnknown12;
        value = record->mUnknown4;
        mode = record->mUnknown44;
        name = fn_800D0F98((Code_800D0F98)record->mUnknown48);
    } else {
        const Table_800D1788 *table = &lbl_80298140[record->mUnknown20];
        Step_800D1788 *steps = table->mpUnknown4;
        subtract = value = mode = name = 0;
        unsigned int i = 0;
        int found = 0, ended = 0;
        for (; i <= 9; i++) {
            int stepValue = steps[i].mUnknown8;
            if (stepValue == 0) { ended = 1; break; }
            if ((unsigned int)count < steps[i].mUnknown10) break;
            value = stepValue;
            mode = steps[i].mUnknown0;
            name = fn_800D0F98(steps[i].mUnknown4);
            threshold = steps[i].mUnknown10;
            found = 1;
        }
        if (i > 9) ended = 1;
        if (found && !ended && steps[i-1].mUnknown14) {
            Step_800D1788 *previous = &steps[i-1];
            unsigned int percent = (((unsigned int)count - previous->mUnknown10) / previous->mUnknown18) *
                ((previous->mUnknown18 * 100) / (steps[i].mUnknown10 - previous->mUnknown10));
            if (percent >= 1 && percent <= 99) value += (percent * (steps[i].mUnknown8 - previous->mUnknown8)) / 100;
        }
        Increment_800D1788 *increment = lbl_80298140[lbl_803EACD4->mUnknown0[id].mUnknown20].mpUnknown0;
        if (increment && ended && increment->mUnknown0) {
            unsigned int repeats = ((unsigned int)count - threshold) / increment->mUnknownC;
            if (repeats) value += repeats * increment->mUnknown4;
        }
    }
    int extra = lbl_803EACD4->mUnknown0[id].mUnknown32;
    if (lbl_803EACD4->mUnknown1F0D) value += lbl_803EACD4->mUnknown1F54;
    int text = lbl_803EACD4->mUnknown0[id].mUnknown16;
    if (pScaled) *pScaled = (value * 10) / 100;
    if (pSubtract) *pSubtract = subtract;
    if (pValue) *pValue = value;
    if (pText) *pText = text;
    if (pExtra) *pExtra = extra;
    if (pMode) *pMode = mode;
    if (pName) *pName = name;
}

extern "C" void fn_800D1A90(int side, int id, int scaled, int subtract, int value, int text, int extra, int mode, int name, int arg) {
    if (lbl_803EACC4) {
        Record_8018FC1C *record = &lbl_803EACD4->mUnknown0[id];
        if (record->mUnknown0) {
            if (value != 0 || record->mUnknown2) {
                fn_800D3EDC(side, id, fn_800D3EB0(side, id) + 1);
                char message[80];
                strcpy(message, lbl_802981A8[name]);
                if (lbl_803EACC0) lbl_803EACC0(id, side, message, value, record->mUnknown1, arg, lbl_803EACD4->mUnknown1F0C[0] == 0);
                if (lbl_803EACD4->mUnknown0[id].mUnknown1) {
                    if (fn_800A8488(side == 0) == 0 && subtract != 0) {
                        fn_800D3FBC(side == 0, fn_800D3F08(side == 0) - subtract, 0);
                        fn_800D3FBC(side, fn_800D3F08(side) + scaled, 1);
                    } else fn_800D3FBC(side, fn_800D3F08(side) + scaled, 0);
                    fn_800D421C(side, fn_800D41F8(side) + value);
                    fn_800D2108(side, id, mode, extra);
                } else {
                    if (fn_800A8488(side == 0) == 0 && subtract != 0) {
                        fn_800D1634(side == 0, fn_800D3F08(side == 0) - subtract, 0, 1);
                        fn_800D1634(side, fn_800D3F08(side) + scaled, 1, 1);
                    } else fn_800D1634(side, fn_800D3F08(side) + scaled, 0, 1);
                }
                if (lbl_803EACD4->mUnknown1F0C[0]) {
                    int meter = fn_800D3F08(side);
                    int total = fn_800D41F8(side);
                    int other = fn_800D3F08(side == 0);
                    fn_800D0E64(side, message, value, meter, total, arg, other);
                } else {
                    fn_800D1500(side, message, value, arg);
                    fn_800D15E8(side, fn_800D41F8(side));
                }
                if (fn_801486A0() == 3 && text != 0) fn_800A20D0(fn_80178348(), (signed char)text);
            } else fn_800D0D48(76);
        } else fn_800D0D48(77);
    }
}

extern "C" void fn_800D1D84(int side, int id, int count) {
    if (lbl_803EACC4) {
        int scaled, subtract, value, text, extra, mode, name;
        fn_800D1788(side, id, count, &scaled, &subtract, &value, &text, &extra, &mode, &name);
        switch (id) {
        case 15:
            lbl_803EC9AC[side]++;
            lbl_803EC9D8[side]++;
            if (lbl_803EC9D8[side] > lbl_803EC9DC[side]) lbl_803EC9DC[side] = lbl_803EC9D8[side];
            break;
        case 14: case 17: lbl_803EC9D8[side] = 0; break;
        case 19: case 20: case 21: case 22: case 23: case 24:
            lbl_803EC9AC[side]++;
            lbl_803EC9D8[side]++;
            if (lbl_803EC9D8[side] > lbl_803EC9DC[side]) lbl_803EC9DC[side] = lbl_803EC9D8[side];
            lbl_803EC9A4[side] += value;
            fn_8017C7D4(side, 1);
            break;
        case 10: case 11:
            if (id == 11) fn_8017C6A0(side, 1); else fn_8017C648(side, 1);
            lbl_803EC9D4[side] = 1;
            lbl_803EC9A4[side] += value;
            break;
        case 38: case 39: case 50: case 51:
            fn_8017C6CC(side, 1, 0); lbl_803EC9A4[side] += value; break;
        case 53: case 54:
            fn_8017C724(side, 1); lbl_803EC9A4[side] += value; break;
        case 63: fn_8017C7A8(side, 1); lbl_803EC9A4[side] += value; break;
        case 60: fn_8017C750(side, 1, 0); lbl_803EC9A4[side] += value; break;
        case 67: case 68: fn_8017C8DC(side, 1);
        case 66: lbl_803EC9A4[side] += value; break;
        case 77: lbl_803EC9B8[side] = 1; lbl_803EC9C0[side] = 1; break;
        case 76: lbl_803EC9B8[side] = 1; break;
        case 18: lbl_803EC9C8[side] = 1; break;
        }
        fn_800D1A90(side, id, scaled, subtract, value, text, extra, mode, name, lbl_803EACD4->mUnknown0[id].mUnknown40);
    }
}

extern "C" int fn_800D207C(int i) {
    return *(i == 0 ? &lbl_803EACD4->mUnknown1A78 : &lbl_803EACD4->mUnknown1A7C);
}

extern "C" void fn_800D20A0(int side, int value) {
    *(side == 0 ? &lbl_803EACD4->mUnknown1A78 : &lbl_803EACD4->mUnknown1A7C) = value;
    if (value == 0) strcpy(side == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3, lbl_803ED6C4);
}

extern "C" void fn_800D2108(int side, int id, int text, int value) {
    if (id == 66) {
        if (side == 0) {
            if (lbl_803EACD4->mUnknown1F0E[0]) text = 0;
            lbl_803EACD4->mUnknown1F0E[0] = 1;
        } else {
            if (lbl_803EACD4->mUnknown1F0E[1]) text = 0;
            lbl_803EACD4->mUnknown1F0E[1] = 1;
        }
    }
    if (text != 0) {
        unsigned int length = strlen(side == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3);
        length += strlen(lbl_8029C6B8[text]);
        length += strlen(lbl_803ED6C0);
        length++;
        if (length <= 249) {
            int current = strlen(side == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3);
            if (current != (int)strlen(lbl_803ED6C4)) strcat(side == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3, lbl_803ED6C0);
            strcat(side == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3, lbl_8029C6B8[text]);
        }
        fn_800D20A0(side, fn_800D207C(side) + value);
    }
}

extern "C" void fn_800D2280(void) {
    Object_80039F5C *p = lbl_803EACD4->mpUnknown1F40;
    int team = p->mIdBytes[2] ^ 1;
    float distance;
    fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
    unsigned int limit;
    if (distance < 5.0f) limit = 1;
    else if (distance < 10.0f) limit = 3;
    else limit = 5;
    if ((unsigned int)++lbl_803EACD4->mUnknown1F30 >= limit) {
        Object_80039F5C *carrier = fn_80137B40();
        if (carrier) {
            if (carrier->mMotion.mUnknown28 == 0.0f) lbl_803EACD4->mUnknown1F2C += 3;
            else lbl_803EACD4->mUnknown1F2C++;
        }
        lbl_803EACD4->mUnknown1F30 = 0;
    }
}

extern "C" void fn_800D2378(int id, int team, int count) {
    if (lbl_803EACC4 == 0) return;
    int limit = 0;
    int flag = 0;
    if (id == 99) fn_800D2C9C(0);
    if (id <= 126) {
        fn_800D1D84(team, id, count);
        if (id == 23 || id == 24 || id == 19 || id == 20 || id == 21 || id == 22) lbl_803EACD4->mUnknown1ED5 = 1;
        return;
    }
    if (id == 128) {
        lbl_803EC9A4[0] = 0; lbl_803EC9A4[1] = 0;
        lbl_803EC9AC[0] = 0; lbl_803EC9AC[1] = 0;
        lbl_803EC9D8[0] = 0; lbl_803EC9D8[1] = 0;
        lbl_803EC9DC[0] = 0; lbl_803EC9DC[1] = 0;
        lbl_803EACD4->mUnknown1F80[1] = 0; lbl_803EACD4->mUnknown1F80[0] = 0;
        lbl_803EC9B8[0] = 0; lbl_803EC9B8[1] = 0;
        lbl_803EC9C0[0] = 0; lbl_803EC9C0[1] = 0;
        lbl_803EC9C8[0] = 0; lbl_803EC9C8[1] = 0;
        lbl_803EC9D4[0] = 0; lbl_803EC9D4[1] = 0;
        lbl_803EC9CC[0] = 0; lbl_803EC9CC[1] = 0;
        fn_800D20A0(0, 0); fn_800D20A0(1, 0);
        signed char y = (signed char)(int)fn_80178A2C();
        Point_8017886C point = fn_80177FE0();
        lbl_803EACD4->mUnknown1F70 = y - (signed char)(int)point.mY;
        fn_800D2E50();
        lbl_803EACD4->mUnknown2064[0] = 0;
        lbl_803EACD4->mpUnknown2060 = 0;
        lbl_803EACD4->mUnknown1F18 = 0;
        lbl_803EACD4->mUnknown1F54 = 0;
        lbl_803EACD4->mUnknown1F58 = 0;
        lbl_803EACD4->mUnknown2064[1] = 0;
        lbl_803EACD4->mUnknown2050[0] = fn_800D41F8(0);
        lbl_803EACD4->mUnknown2050[1] = fn_800D41F8(1);
        for (int i = 6; i < 69; i++) ((unsigned char *)lbl_803EACD4)[0x1ECF + i] = 0;
        return;
    }
    if (id != 129 || lbl_803EACD4->mUnknown1F12) return;
    lbl_803EACD4->mUnknown1F12 = 1;
    if (lbl_803EACD4->mUnknown1EF6) {
        lbl_803EACD4->mUnknown1F0B = 1;
        lbl_803EACD4->mUnknown1F74 = lbl_803EACD4->mUnknown1F70;
    } else if (fn_80177F7C() != 6 && fn_80178348() == fn_80178308()) {
        float first = fn_80178A2C();
        float second = fn_80178A2C();
        signed char firstY = (signed char)(int)first;
        Point_8017886C end = fn_80178070();
        int difference = firstY - (signed char)(int)end.mY;
        signed char secondY = (signed char)(int)second;
        Point_8017886C start = fn_80177FE0();
        lbl_803EACD4->mUnknown1F74 = difference - (secondY - (signed char)(int)start.mY);
        lbl_803EACD4->mUnknown1F0B = 1;
    } else lbl_803EACD4->mUnknown1F0B = 0;
    fn_800D2C9C(0);
    fn_800D391C(67);
    fn_800D3C00(0);
    fn_800D0D4C(0); fn_800D0D4C(1);
    lbl_803EACD4->mUnknown1F0C[0] = 1;
    fn_800D5A28(); fn_800D2DF0();
    if (lbl_803EACD4->mUnknown1EF8) fn_800D343C();
    else if (lbl_803EACD4->mUnknown1EFB || lbl_803EACD4->mUnknown1EFC) fn_800D338C();
    else { fn_800D3560(); fn_800D35D4(); }
    fn_800D310C(); fn_800D3094(); fn_800D30D0(); fn_800D3238(); fn_800D3400();
    if (lbl_803EACD4->mUnknown1F13 == 0) {
        switch (fn_801788D8(&limit)) {
        case 0:
            if (fn_801787DC(1) >= limit) fn_800D3294(1, limit - fn_801787DC(0));
            else if (fn_801787DC(0) >= limit) fn_800D3294(0, limit - fn_801787DC(1));
            break;
        case 1:
            if (lbl_803EACD8 == 1) fn_800D3294(1, limit - fn_800D41F8(0));
            else if (lbl_803EACD8 == 0) fn_800D3294(0, limit - fn_800D41F8(1));
            break;
        }
    }
    fn_800D2F9C(0, fn_800D2EB0(0)); fn_800D2F9C(1, fn_800D2EB0(1));
    if (fn_80025708()) {
        Object_800785C0 *object = fn_800785C0();
        if (fn_800254E8(object, 20, 0) || fn_800254E8(object, 31, 0)) flag = 1;
    }
    if ((lbl_803EACD4->mUnknown1F13 == 0 || flag) && fn_800A8740() == 0) { fn_800A72B4(); fn_800A7B5C(); }
    fn_800D1634(0, lbl_803EACD4->mUnknown1A70, 0, 1); fn_800D1634(1, lbl_803EACD4->mUnknown1A74, 0, 1);
    fn_800D1634(0, lbl_803EACD4->mUnknown1A70, 0, 0); fn_800D1634(1, lbl_803EACD4->mUnknown1A74, 0, 0);
    if (fn_80178348() != fn_80178308() || fn_80177C38() != 0) lbl_803EACD4->mUnknown1ECE = 1;
    else lbl_803EACD4->mUnknown1ECE = 0;
    lbl_803EACD4->mUnknown2050[2] = fn_800D41F8(0) - lbl_803EACD4->mUnknown2050[0];
    lbl_803EACD4->mUnknown2050[3] = fn_800D41F8(1) - lbl_803EACD4->mUnknown2050[1];
    if (lbl_803EACD4->mUnknown2050[2 + fn_80178320()] > lbl_803EACD4->mUnknown2050[2 + fn_80178308()]) {
        if (lbl_803EACD4->mUnknown2050[2 + fn_80178320()] > 0) fn_8017E3CC(fn_80178320());
    } else if (lbl_803EACD4->mUnknown2050[2 + fn_80178308()] > 0) fn_8017E3CC(fn_80178308());
    fn_8017C5A0(0, lbl_803EACD4->mUnknown2050[2]); fn_8017C5A0(1, lbl_803EACD4->mUnknown2050[3]);
    fn_8017C5CC(0, lbl_803EC9A4[0]); fn_8017C5CC(1, lbl_803EC9A4[1]);
    fn_8017C5F8(0, lbl_803EC9AC[0]); fn_8017C5F8(1, lbl_803EC9AC[1]);
    if (lbl_803EC9B8[0]) fn_8017C800(0, ++lbl_803EC9B4[0]); else if (fn_80178360() == 0) lbl_803EC9B4[0] = 0;
    if (lbl_803EC9B8[1]) fn_8017C800(1, ++lbl_803EC9B4[1]); else if (fn_80178360() == 1) lbl_803EC9B4[1] = 0;
    if (lbl_803EC9C0[0]) fn_8017C82C(0, ++lbl_803EC9BC[0]); else if (fn_80178360() == 0) lbl_803EC9BC[0] = 0;
    if (lbl_803EC9C0[1]) fn_8017C82C(1, ++lbl_803EC9BC[1]); else if (fn_80178360() == 1) lbl_803EC9BC[1] = 0;
    if (lbl_803EC9C8[0]) fn_8017C884(0, ++lbl_803EC9C4[0]); else if (lbl_803EC9CC[0] && fn_80178348() == 0) lbl_803EC9C4[0] = 0;
    if (lbl_803EC9C8[1]) fn_8017C884(1, ++lbl_803EC9C4[1]); else if (lbl_803EC9CC[1] && fn_80178348() == 1) lbl_803EC9C4[1] = 0;
    if (lbl_803EC9C8[0] && lbl_803EC9D4[0]) fn_8017C908(0, ++lbl_803EC9D0[0]); else if (lbl_803EC9CC[0] && fn_80178348() == 0) lbl_803EC9D0[0] = 0;
    if (lbl_803EC9C8[1] && lbl_803EC9D4[1]) fn_8017C908(1, ++lbl_803EC9D0[1]); else if (lbl_803EC9CC[1] && fn_80178348() == 1) lbl_803EC9D0[1] = 0;
    fn_8017C98C(0, lbl_803EC9DC[0]); fn_8017C98C(1, lbl_803EC9DC[1]);
}

extern "C" void fn_800D2C10(int a, int b) {
    int flag = 0;

    switch (a) {
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 114:
        flag = 1;
        break;
    }
    fn_800D0D48(62);
    fn_800D2C9C(1);
    if (flag) {
        fn_800D2D64();
    } else {
        fn_800D391C(0);
        fn_800D3C00(0);
    }
    fn_800D2378(a, b, 1);
}

extern "C" void fn_800D2C9C(int a) {
    int notify = 0;

    fn_800D0D48(63);
    if (lbl_803EACD4->mUnknown1F11) {
        fn_800D0D48(64);
        if (a == 0 || (a == 1 && lbl_803EACD4->mpUnknown2060 != fn_80137B40())) {
            notify = 1;
            fn_800D0D48(65);
            fn_800D3C00(0);
            fn_800D1D84(fn_80178360(), 95, 1);
        }
        if (notify) {
            fn_800AE7F0(11, fn_80178360(), lbl_803EACD4->mpUnknown2060);
        }
        lbl_803EACD4->mUnknown1F10 = 0;
        lbl_803EACD4->mUnknown1F11 = 0;
    }
}

extern "C" void fn_800D2D64(void) {
    if (lbl_803EACD4->mUnknown1EEA) {
        lbl_803EACD4->mUnknown1EEA = 0;
        if (lbl_803EACD4->mUnknown1EF4) {
            fn_800D2378(11, fn_80178348(), 1);
            lbl_803EACD4->mUnknown1EF4 = 0;
            fn_80156C78(24, 1);
        } else {
            fn_800D2378(10, fn_80178348(), 1);
        }
    }
}

extern "C" void fn_800D2DF0(void) {
    if (lbl_803EACD4->mUnknown1EDC) {
        fn_800D1D84(lbl_803EACD4->mUnknown1F3C, 66, lbl_803EACD4->mUnknown1F48);
        fn_800D2E50();
        lbl_803EACD4->mUnknown1EDC = 0;
        fn_800AE7F0(5, (unsigned char)lbl_803EACD4->mUnknown1F3C, lbl_803EACD4->mpUnknown1F40);
    }
}

extern "C" void fn_800D2E50(void) {
    fn_800D0D48(50);
    lbl_803EACD4->mUnknown1F2C = 0;
    lbl_803EACD4->mUnknown1F30 = 0;
    lbl_803EACD4->mUnknown1F34 = 0;
    lbl_803EACD4->mUnknown1F38 = 0;
    lbl_803EACD4->mpUnknown1F40 = 0;
    lbl_803EACD4->mUnknown1EDA = 0;
    lbl_803EACD4->mUnknown1EDB = 0;
    lbl_803EACD4->mUnknown1F44 = 0;
    fn_80067D4C(122, 0);
}

extern "C" int fn_800D2EB0(int a) {
    int result = 0;

    if (fn_80178360() == a) {
        if (lbl_803EACD4->mUnknown1EFA || lbl_803EACD4->mUnknown1EF7) {
            result = 1;
        } else if (fn_80177F7C() == 6) {
            if (!lbl_803EACD4->mUnknown1EFB) {
                result = 1;
            }
        } else if (fn_80178360() == fn_80178308() || lbl_803EACD4->mUnknown1F74 <= 0) {
            result = 1;
        }
    } else if (fn_80177F7C() == 6) {
        if (lbl_803EACD4->mUnknown1EF9) {
            result = 1;
        }
    } else if (lbl_803EACD4->mUnknown1F74 > 0) {
        result = 1;
    }
    if (fn_801486A0() == 0) {
        result = a == 1;
    }
    return result;
}

extern "C" void fn_800D2F9C(int a, int b) {
    int found;

    if (lbl_803EACC4) {
        if (b && lbl_803EACC5) {
            fn_800D1788(a, 108, fn_800D207C(a), 0, 0, &found, 0, 0, 0, 0);
            if (found) {
                fn_800D1700(a);
                fn_800D0DBC(a, 1, 1);
                fn_800D0D4C(a);
                fn_800D1D84(a, 108, fn_800D207C(a));
                fn_800D0DBC(a, 1, 0);
            } else {
                fn_800D0DBC(a, 1, 1);
            }
        } else {
            fn_800D0DBC(a, 1, 1);
        }
    }
}

extern "C" void fn_800D3094(void) {
    if (lbl_803EACD4->mUnknown1F09) {
        fn_800D1D84(fn_80178360(), 99, 1);
    }
}

extern "C" void fn_800D30D0(void) {
    if (lbl_803EACD4->mUnknown1F0A) {
        fn_800D1D84(lbl_803EACD4->mUnknown1F7D, 100, 1);
    }
}

extern "C" void fn_800D310C(void) {
    if (lbl_803EACD4->mUnknown1F03 && lbl_803EACD4->mUnknown1F04) {
        fn_800D1D84(fn_80178360(), 102, 1);
    } else if (lbl_803EACD4->mUnknown1F03 && (lbl_803EACD4->mUnknown1F05 || lbl_803EACD4->mUnknown1F08)) {
        fn_800D1D84(fn_80178360(), 103, 1);
    } else if (lbl_803EACD4->mUnknown1F04) {
        fn_800D1D84(fn_80178360(), 76, 1);
    } else if (lbl_803EACD4->mUnknown1F05) {
        fn_800D1D84(fn_80178360(), 77, 1);
    } else if (lbl_803EACD4->mUnknown1F03) {
        fn_800D1D84(lbl_803EACD4->mUnknown1F7C, 101, 1);
    } else if (lbl_803EACD4->mUnknown1F06) {
        fn_800D1D84(fn_80178360(), 96, 1);
    } else if (lbl_803EACD4->mUnknown1F08) {
        fn_800D1D84(fn_80178360(), 98, 1);
    } else if (lbl_803EACD4->mUnknown1F02) {
        fn_800D1D84(fn_80178360(), 78, 1);
    } else if (lbl_803EACD4->mUnknown1F07) {
        fn_800D1D84(fn_80178360(), 97, 1);
    }
}

extern "C" void fn_800D3238(void) {
    if (lbl_803EACD4->mUnknown1EFF) {
        if (lbl_803EACD4->mUnknown1EFE) {
            fn_800D1D84(fn_80178348(), 71, 1);
        } else {
            fn_800D1D84(fn_80178348(), 70, 1);
        }
    }
}

extern "C" void fn_800D3294(int team, unsigned int value) {
    int limit = 0;

    fn_801788D8(&limit);
    if (fn_800A8740() == 0) {
        if (fn_800A8488(0)) {
            fn_800A7A0C(0);
        }
        if (fn_800A8488(1)) {
            fn_800A7A0C(1);
        }
    }
    if (value == limit) {
        value = 100;
    } else {
        value = value * 100 / limit;
    }
    if (fn_80025708() == 0 && fn_801486A0() != 5) {
        if (fn_800A84C8() != 0 && fn_800A8444((unsigned char)team) != 0) {
            fn_800D1D84(team, 107, value);
        } else {
            fn_800D1D84(team, 106, value);
        }
    }
    lbl_803EACD4->mUnknown1F13 = 1;
}

extern "C" void fn_800D338C(void) {
    int value = fn_80179138();

    if (lbl_803EACD4->mUnknown1EFB) {
        if (value == 2) {
            fn_800D1D84(fn_80178348(), 2, 1);
        } else {
            fn_800D1D84(fn_80178348(), 3, 1);
        }
    } else if (lbl_803EACD4->mUnknown1EFC) {
        fn_800D1D84(fn_80178360(), 4, 1);
    }
}

extern "C" void fn_800D3400(void) {
    if (lbl_803EACD4->mUnknown1EFD) {
        fn_800D1D84(fn_80178360(), 5, 1);
    }
}

extern "C" void fn_800D343C(void) {
    switch (lbl_803EACD4->mUnknown1F78) {
    case 67:
        fn_800D1D84(fn_80178348(), 67, 1);
        break;
    case 0:
        fn_800D1D84(fn_80178348(), 0, lbl_803EACD4->mUnknown1F70);
        break;
    case 91:
        fn_800D1D84(fn_80178360(), 91, 1);
        break;
    case 68:
        fn_800D1D84(fn_80178348(), 68, 1);
        break;
    case 1:
        fn_800D1D84(fn_80178348(), 1, lbl_803EACD4->mUnknown1F70);
        break;
    case 69:
        fn_800D1D84(fn_80178348(), 69, 1);
        break;
    case 92:
        fn_800D1D84(fn_80178360(), 92, 1);
        break;
    case 93:
        fn_800D1D84(fn_80178360(), 93, 1);
        break;
    case 94:
        fn_800D1D84(fn_80178348(), 94, 1);
        break;
    case 126:
        fn_800D1D84(fn_80178348(), 126, 1);
        break;
    }
}

extern "C" void fn_800D3560(void) {
    if (lbl_803EACD4->mUnknown1F0B && !fn_80177C38() && !lbl_803EACD4->mUnknown1ED6 &&
        lbl_803EACD4->mUnknown1ED5 && lbl_803EACD4->mUnknown1F74 > 0) {
        fn_800D1D84(fn_80178348(), 26, lbl_803EACD4->mUnknown1F74);
    }
}

extern "C" void fn_800D35D4(void) {
    if (lbl_803EACD4->mUnknown1F0B && !fn_80177C38() && !lbl_803EACD4->mUnknown1ED6) {
        if (!lbl_803EACD4->mUnknown1ED5 && lbl_803EACD4->mUnknown1F74 > 0) {
            fn_800D1D84(fn_80178348(), 25, lbl_803EACD4->mUnknown1F74);
        }
    }
}

extern "C" void fn_800D3648(void) {
    if (lbl_803EACD4->mUnknown1EDB) {
        fn_800AE7F0(0, fn_80178308(), 0);
    }
    if ((fn_80177C38() & 1) == 0) {
        lbl_803EACD4->mUnknown1ED6 = 1;
        fn_800D20A0(fn_80178348(), 0);
    } else {
        lbl_803EACD4->mUnknown1ED7 = 1;
        fn_800D20A0(fn_80178360(), 0);
    }
    if (lbl_803EACD4->mpUnknown1F40) {
        if (!lbl_803EACD4->mUnknown1EEE) {
            lbl_803EACD4->mUnknown1F54 = lbl_803EACD4->mUnknown1F34;
            lbl_803EACD4->mUnknown1F58 = lbl_803EACD4->mUnknown1F38;
            lbl_803EACD4->mUnknown1EEE = 1;
        }
        fn_800D59C8(lbl_803EACD4->mpUnknown1F40->mIdBytes[2]);
    }
    fn_800D391C(0);
    fn_800D3C00(0);
}

extern "C" void fn_800D371C(void) {
    lbl_803EACD4->mUnknown1EEB = 1;
    lbl_803EACD4->mUnknown1EE4 = 0;
    if (lbl_803EACD4->mUnknown1EE9) {
        fn_800D0D48(9);
        lbl_803EACD4->mUnknown1EEA = 1;
        fn_800D2378(8, fn_80178348(), 1);
    }
}

extern "C" void fn_800D378C(void) {
    fn_800D0D48(17);
    if (lbl_803EACD4->mUnknown1EE1 || lbl_803EACD4->mUnknown1EE2) {
        lbl_803EACD4->mUnknown1EE3 = 1;
        lbl_803EACD4->mUnknown1F64 = fn_80178308();
        fn_800D391C(20);
        if (lbl_803EACD4->mUnknown1EE2) {
            fn_800D2378(16, fn_80178308(), lbl_803EACD4->mUnknown1F80[fn_80178308()] + 1);
        } else {
            fn_800D2378(13, fn_80178308(), lbl_803EACD4->mUnknown1F80[fn_80178308()] + 1);
        }
    }
}

extern "C" int fn_800D3850(int a) {
    int event = 28;

    fn_800D0D48(48);
    if (lbl_803EACD4->mUnknown1EE7) {
        if (lbl_803EACD4->mUnknown1EE8) {
            if (a) {
                event = 29;
            }
            if (event == 29) {
                Object_80039F5C *p = lbl_803EACD4->mpUnknown1F68;
                Record_800B15FC *pRecord = fn_800B15FC();

                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = p->mMotion.mPos.mX;
                pRecord->mUnknown10 = p->mMotion.mPos.mY;
                pRecord->mUnknown14 = 58;
                fn_800B1508();
            }
        }
        fn_800D2378(event, fn_80178308(), 1);
        lbl_803EACD4->mUnknown1EE8 = 0;
        lbl_803EACD4->mUnknown1EE7 = 0;
    }
    return event == 29;
}

extern "C" void fn_800D391C(int a) {
    if (a != 67 && a != 11 && a != 1 && a != 14 && a != 15 && a != 16 && a != 24 && a != 18) {
        fn_800D5A28();
        lbl_803EACD4->mUnknown1EE0 = 0;
        lbl_803EACD4->mUnknown1EF3 = 0;
    }
    if (lbl_803EACD4->mUnknown1EDD && a != 14) {
        if (lbl_803EACD4->mUnknown1EF3) {
            fn_800D2378(41, lbl_803EACD4->mUnknown1F60, 1);
        } else if (lbl_803EACD4->mUnknown1EE0) {
            fn_800D2378(37, lbl_803EACD4->mUnknown1F60, 1);
        } else {
            fn_800D2378(33, lbl_803EACD4->mUnknown1F60, 1);
        }
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1EDD = 0;
    }
    if (lbl_803EACD4->mUnknown1EDE && a != 15) {
        if (lbl_803EACD4->mUnknown1EE0) {
            fn_800D2378(49, lbl_803EACD4->mUnknown1F61, 1);
        } else {
            fn_800D2378(45, lbl_803EACD4->mUnknown1F61, 1);
        }
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1EDE = 0;
    }
    if (lbl_803EACD4->mUnknown1EE7 && a != 24 && a != 1) {
        fn_800D2378(28, lbl_803EACD4->mUnknown1F62, 1);
        lbl_803EACD4->mUnknown1EE7 = 0;
        lbl_803EACD4->mUnknown1EE8 = 0;
    }
    if (lbl_803EACD4->mUnknown1EDF && a != 16 && a != 1) {
        if (lbl_803EACD4->mUnknown1EF3) {
            fn_800D2378(62, lbl_803EACD4->mUnknown1F63, 1);
        } else if (lbl_803EACD4->mUnknown1EE0) {
            fn_800D2378(59, lbl_803EACD4->mUnknown1F63, 1);
        } else {
            fn_800D2378(56, lbl_803EACD4->mUnknown1F63, 1);
        }
        lbl_803EACD4->mUnknown1EDF = 0;
    }
    if (lbl_803EACD4->mUnknown1EE3 && a != 20 && (a < 1 || a > 5)) {
        if (lbl_803EACD4->mUnknown1EE2) {
            fn_800D2378(17, lbl_803EACD4->mUnknown1F64, 1);
        } else {
            fn_800D2378(14, lbl_803EACD4->mUnknown1F64, 1);
        }
        lbl_803EACD4->mUnknown1EE3 = 0;
        lbl_803EACD4->mUnknown1EE1 = 0;
        lbl_803EACD4->mUnknown1EE2 = 0;
    }
    if (lbl_803EACD4->mUnknown1EEA && a != 27 && (a < 1 || a > 5)) {
        Object_80039F5C *p = fn_80137B40();

        if (p == 0 || p->mIdBytes[2] == fn_80178360() || fn_801787A0()) {
            fn_800D2378(9, fn_80178348(), 1);
            lbl_803EACD4->mUnknown1EEA = 0;
        }
    }
}

extern "C" void fn_800D3C00(int a) {
    if (lbl_803EACD4->mUnknown1EEC && a != 29) {
        if (lbl_803EACD4->mUnknown1EED) {
            fn_800D2378(83, fn_80178360(), 1);
        } else {
            fn_800D2378(82, fn_80178360(), 1);
        }
        lbl_803EACD4->mUnknown1EEC = 0;
        lbl_803EACD4->mUnknown1EED = 0;
    }
}

extern "C" int fn_800D3C80(void) {
    int result = 0;
    Object_80039F5C *p = fn_8017876C();

    if (p) {
        result = (p->mFlags >> 14) & 1;
    }
    return result;
}

extern "C" int fn_800D3CC0(void) {
    Object_80039F5C *p = fn_8017876C();
    int result = 0;
    Object_80039F5C *pTarget = 0;

    if (!p) {
        Object_80039F5C *pBall = fn_80137B40();

        if (pBall || (pBall = fn_80137B64())) {
            if (pBall->mpState->mId == 16) {
                pTarget = fn_8009BCE8(&pBall->mUnknown336);
            }
        }
    }
    if (p) {
        result = (p->mFlags >> 14) & 1;
    } else if (pTarget) {
        result = pTarget->mUnknown8 != 255 ? 1 : 0;
    }
    return result;
}

extern "C" void fn_800D3D64() {
}

extern "C" int fn_800D3D68(void *p, int value) {
    fn_800D3D64();
    return 0;
}

extern "C" int fn_800D3D8C(void *p, int value) {
    return 0;
}

extern "C" int fn_800D3D94(void *p, void *q) {
    if (q == 0) {
        return fn_80238278(p, sizeof(State_800D0D4C), 0);
    }
    return fn_80238258(p, q, sizeof(State_800D0D4C));
}

extern "C" int fn_800D3DD0(void *p, void *pBuffer) {
    *(State_800D0D4C *)pBuffer = *(State_800D0D4C *)p;
    return 1;
}

extern "C" int fn_800D3E1C(void *p, void *pBuffer) {
    *(State_800D0D4C *)p = *(State_800D0D4C *)pBuffer;
    return 1;
}

extern "C" int fn_800D3E68(void *p) {
    return sizeof(State_800D0D4C);
}

extern "C" void fn_800D3E70(void) {
    Object_80039F5C *p = lbl_803EACD4->mpUnknown2068;

    if (p != 0) {
        fn_800310C0(lbl_803EA368, 56, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    }
}

extern "C" unsigned short fn_800D3EB0(int side, int index) {
    return (side == 0 ? lbl_803EACD4->mUnknown1A80 : lbl_803EACD4->mUnknown1B7E)[index];
}

extern "C" void fn_800D3EDC(int side, int index, unsigned short value) {
    (side == 0 ? lbl_803EACD4->mUnknown1A80 : lbl_803EACD4->mUnknown1B7E)[index] = value;
}

extern "C" int fn_800D3F08(int side) {
    return *(side == 0 ? &lbl_803EACD4->mUnknown1A70 : &lbl_803EACD4->mUnknown1A74);
}

extern "C" float fn_800D3F2C(int side) {
    int value = fn_800D3F08(side);
    float result;
    if (value == 0) result = 0.0f;
    else if (value == lbl_803EACD0) result = 1.0f;
    else result = (float)value / (float)lbl_803EACD0;
    return result;
}

extern "C" void fn_800D3FBC(int side, int value, int arg) {
    if (fn_800A8740() == 0) {
        if (value > lbl_803EACD0) {
            value = lbl_803EACD0;
        }
        if (value < 0) {
            value = 0;
        }
        if (fn_800A8F84(side) == 0 || value < *(side == 0 ? &lbl_803EACD4->mUnknown1A70 : &lbl_803EACD4->mUnknown1A74)) {
            if (value == 0 && fn_800D3F08(side) > 0) {
                fn_80067DB8(6, 0, side, 0, 0);
            }
            if (value == lbl_803EACD0 && fn_800D3F08(side) < lbl_803EACD0) {
                lbl_803EACD4->mUnknown2064[side] = 1;
                fn_80067DB8(5, 0, side, 0, 0);
            }
            if (value < *(side == 0 ? &lbl_803EACD4->mUnknown1A70 : &lbl_803EACD4->mUnknown1A74)) {
                fn_800D1634(side, value, arg, 0);
            }
            fn_800D1634(side, value, arg, 1);
            *(side == 0 ? &lbl_803EACD4->mUnknown1A70 : &lbl_803EACD4->mUnknown1A74) = value;
        }
    } else {
        *(side == 0 ? &lbl_803EACD4->mUnknown1A70 : &lbl_803EACD4->mUnknown1A74) = 0;
    }
}

extern "C" void fn_800D4164(int side, float t, int arg) {
    int value = 0;
    if (!(t <= 0.0f)) {
        if (!(t < 1.0f)) value = lbl_803EACD0;
        else value = (int)(t * (float)lbl_803EACD0);
    }
    fn_800D3FBC(side, value, arg);
}

extern "C" int fn_800D41F8(int side) {
    return *(side == 0 ? &lbl_803EACD4->mUnknown1A68 : &lbl_803EACD4->mUnknown1A6C);
}

extern "C" void fn_800D421C(int side, int value) {
    int limit = 0;

    if (value < 0) {
        value = 0;
    }
    if (lbl_803EACD8 == 2 && fn_801788D8(&limit) == 1 && value >= limit) {
        lbl_803EACD8 = side;
        if (fn_80025708() == 0) {
            fn_80067DB8(94, 0, lbl_803EACD8, 0, 0);
            fn_80178370();
        }
    }
    *(side == 0 ? &lbl_803EACD4->mUnknown1A68 : &lbl_803EACD4->mUnknown1A6C) = value;
}

extern "C" int fn_800D42CC() {
    return lbl_803EACD8;
}

extern "C" void fn_800D42D4(void) {
    int value;

    fn_800D0D48(44);
    if (fn_80178348() == fn_80178308()) {
        lbl_803EACD4->mUnknown1EF6 = 1;
    } else {
        lbl_803EACD4->mUnknown1EF7 = 1;
    }
    value = fn_800D5A6C(0, 0, 0);
    if (value == 0) {
        value = fn_800D5A6C(0, 0, 0);
    }
    if (fn_80177C38() == 1 && lbl_803EACD4->mUnknown1ED7 == 0) {
        lbl_803EACD4->mUnknown1EF8 = 1;
        if (lbl_803EACD4->mUnknown1ED8 != 0) {
            lbl_803EACD4->mUnknown1F78 = 92;
        } else if (lbl_803EACD4->mUnknown1ED9 != 0) {
            lbl_803EACD4->mUnknown1F78 = 93;
        } else {
            lbl_803EACD4->mUnknown1F78 = 91;
        }
    } else if (fn_80177C38() == 0 && lbl_803EACD4->mUnknown1ED6 == 0) {
        if (fn_800A84C8() != 0 && fn_800A8444(fn_80178320()) != 0) {
            lbl_803EACD4->mUnknown1EF8 = 1;
            lbl_803EACD4->mUnknown1F78 = 94;
        } else if (lbl_803EACD4->mUnknown1ECE != 0) {
            lbl_803EACD4->mUnknown1EF8 = 1;
            lbl_803EACD4->mUnknown1F78 = 69;
        } else if (lbl_803EACD4->mUnknown1ED5 != 0 && lbl_803EACD4->mUnknown1ED6 == 0) {
            if (value != 0) {
                lbl_803EACD4->mUnknown1EF8 = 1;
                lbl_803EACD4->mUnknown1F78 = 67;
            } else {
                lbl_803EACD4->mUnknown1EF8 = 1;
                lbl_803EACD4->mUnknown1F78 = 0;
            }
        } else if (value != 0) {
            lbl_803EACD4->mUnknown1EF8 = 1;
            lbl_803EACD4->mUnknown1F78 = 68;
        } else {
            lbl_803EACD4->mUnknown1EF8 = 1;
            lbl_803EACD4->mUnknown1F78 = 1;
        }
    } else {
        lbl_803EACD4->mUnknown1EF8 = 1;
        lbl_803EACD4->mUnknown1F78 = 126;
    }
}

extern "C" void fn_800D44A8(float a) {
    fn_800D0D48(40);
    if (fn_8017876C() != 0) {
        fn_800B1698(fn_80137AD0(fn_801374BC()), fn_8017876C());
    }
    if (fn_80177C38() == 0) {
        if (a < fn_80177FE0().mY && fn_80177F70() != 6) {
            if (fn_8017876C() != 0) {
                fn_800D0D48(74);
                if (fn_800D3C80() != 0) {
                    lbl_803EACD4->mUnknown1F08 = 1;
                } else {
                    lbl_803EACD4->mUnknown1F06 = 1;
                }
            } else {
                fn_800D0D48(75);
                lbl_803EACD4->mUnknown1F07 = 1;
            }
        }
    }
}

extern "C" void fn_800D45A0(void) {
    fn_800D0D48(43);
    lbl_803EACD4->mUnknown1F03 = 1;
    if ((fn_80177C38() & 1) == 0) {
        lbl_803EACD4->mUnknown1F7C = fn_80178360();
    } else {
        lbl_803EACD4->mUnknown1F7C = fn_80178348();
    }
}

extern "C" void fn_800D45F0(Object_80039F5C *p, float a) {
    fn_800D0D48(41);
    if (p != 0) {
        fn_800D3850(0);
        if (fn_80177C38() == 0) {
            if (fn_801650DC(fn_8016871C(fn_80178348())) != 0 && fn_801783AC(0) == 0 &&
                a <= fn_80177FE0().mY && (p->mFlags & 0x10000000)) {
                if (fn_800D3C80() != 0) {
                    lbl_803EACD4->mUnknown1F05 = 1;
                } else {
                    lbl_803EACD4->mUnknown1F04 = 1;
                }
            } else {
                if (a < fn_80177FE0().mY && fn_80177F70() != 6) {
                    if (fn_800D3C80() != 0) {
                        lbl_803EACD4->mUnknown1F08 = 1;
                    } else {
                        lbl_803EACD4->mUnknown1F06 = 1;
                    }
                } else if (lbl_803EACD4->mUnknown1F00 != 0) {
                    lbl_803EACD4->mUnknown1F02 = 1;
                }
            }
        }
    }
}

extern "C" void fn_800D4748(Object_80039F5C *p) {
    fn_800D0D48(39);
    if (p != 0 && !(p->mFlags & 0x10000)) {
        if (fn_801787A0() == 0 && p == fn_80137B40()) {
            fn_800D391C(0);
            if (lbl_803EACD4->mUnknown1F01 == 0) {
                fn_800D2378(30, p->mIdBytes[2], 1);
            }
            lbl_803EACD4->mUnknown1F01 = 0;
        }
    }
}

extern "C" void fn_800D47D4(int flag, Object_80039F5C *p) {
    fn_800D0D48(38);
    if (p == fn_80137B40()) {
        if (flag != 0) {
            lbl_803EACD4->mUnknown1F00 = 1;
        } else if (fn_801787A0() == 0) {
            fn_800D2378(31, fn_80178308(), 1);
            lbl_803EACD4->mUnknown1F01 = 1;
        }
    }
}

extern "C" void fn_800D4858(void) {
    fn_800D0D48(37);
    lbl_803EACD4->mUnknown1F09 = 1;
}

extern "C" void fn_800D4888(int flag) {
    fn_800D0D48(42);
    if (lbl_803EACD4->mUnknown1F0A == 0) {
        lbl_803EACD4->mUnknown1F0A = 1;
        if ((fn_80177C38() & 1) == 0) {
            lbl_803EACD4->mUnknown1F7D = fn_80178348();
        } else {
            lbl_803EACD4->mUnknown1F7D = fn_80178360();
        }
        if (flag != 0) {
            lbl_803EACD4->mUnknown1F7D = lbl_803EACD4->mUnknown1F7D == 0;
        }
    }
}

extern "C" void fn_800D490C(void) {
    fn_800D0D48(36);
    if (fn_80177C38() == 0) {
        lbl_803EACD4->mUnknown1EFF = 1;
    }
}

extern "C" void fn_800D4948(void) {
    fn_800D0D48(35);
    fn_800D391C(0);
    fn_800AE7F0(12, fn_80178308(), fn_80137B40());
    lbl_803EACD4->mUnknown1EFE = 1;
}

extern "C" void fn_800D49A4(void) {
    fn_800D0D48(33);
    lbl_803EACD4->mUnknown1EF9 = 1;
    if (fn_80177C38() == 0 && lbl_803EACD4->mUnknown1ED6 == 0) {
        lbl_803EACD4->mUnknown1EFB = 1;
    }
}

extern "C" void fn_800D49FC(void) {
    fn_800D0D48(32);
    lbl_803EACD4->mUnknown1EFA = 1;
    if (lbl_803EACD4->mUnknown1ED7 == 0) {
        lbl_803EACD4->mUnknown1EFC = 1;
    }
}

extern "C" void fn_800D4A40(void) {
    fn_800D0D48(34);
    lbl_803EACD4->mUnknown1EFD = 1;
}

extern "C" void fn_800D4A70(Object_80039F5C *p) {
    fn_800D0D48(31);
    if (p != 0 && fn_801787A0() == 0 && fn_801BE648(p->mpUnknown792) != 234 &&
        fn_801BE648(p->mpUnknown792) != 238) {
        if (fn_80177C38() == 0 && p->mIdBytes[2] == fn_80178360() && lbl_803EACD4->mUnknown1EEE != 0 &&
            lbl_803EACD4->mUnknown1F54 != 0) {
            lbl_803EACD4->mUnknown1F0D = 1;
            fn_800D2378(90, p->mIdBytes[2], 1);
            lbl_803EACD4->mUnknown1F0D = 0;
            lbl_803EACD4->mUnknown1EEE = 0;
            lbl_803EACD4->mUnknown1F54 = 0;
            lbl_803EACD4->mUnknown1F58 = 0;
        } else if (p->mFlags & 0x4000) {
            if (p->mIdBytes[2] == fn_80178308()) {
                fn_800D2378(89, p->mIdBytes[2], 1);
            } else {
                fn_800D2378(87, p->mIdBytes[2], 1);
            }
        } else if (p->mIdBytes[2] == fn_80178308()) {
            fn_800D2378(88, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(86, p->mIdBytes[2], 1);
        }
        if (p->mIdBytes[2] == fn_80178320()) {
            Vector_80039F5C pos;

            fn_80137D58(fn_801374BC(), &pos);
            lbl_803EACD4->mUnknown1F14 = -pos.mY;
            lbl_803EACD4->mUnknown1F80[fn_80178308()] = 0;
        }
    }
}

extern "C" void fn_800D4BF0(Object_80039F5C *p, int team) {
    fn_800D0D48(30);
    if (lbl_803EACD4->mUnknown1EDB != 0) {
        fn_800AE7F0(0, fn_80178308(), 0);
    }
    if (lbl_803EACD4->mpUnknown1F40 != 0) {
        if (lbl_803EACD4->mUnknown1EEE == 0) {
            lbl_803EACD4->mUnknown1F54 = lbl_803EACD4->mUnknown1F34;
            lbl_803EACD4->mUnknown1F58 = lbl_803EACD4->mUnknown1F38;
            lbl_803EACD4->mUnknown1EEE = 1;
        }
        fn_800D59C8(lbl_803EACD4->mpUnknown1F40->mIdBytes[2]);
    }
    fn_800D391C(0);
    fn_800D3C00(0);
    if (fn_80177C38() == 0) {
        if (fn_800D3CC0() != 0) {
            fn_800D2378(85, team, 1);
        } else {
            fn_800D2378(84, team, 1);
        }
    }
}

extern "C" void fn_800D4CD4(void) {
    unsigned char team;

    lbl_803EACD4->mUnknown1F18 = 0;
    for (team = 0; team <= 1; team++) {
        unsigned int count = fn_80178D18(team);
        unsigned short i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            if (p->mUnknown8 != 255) {
                if (lbl_803EACD4->mUnknown1F18 <= 3) {
                    lbl_803EACD4->mpUnknown1F1C[lbl_803EACD4->mUnknown1F18] = p;
                }
                lbl_803EACD4->mUnknown1F18++;
            }
        }
    }
}

extern "C" void fn_800D4D84(Object_80039F5C *p) {
    fn_800D0D48(28);
    if (fn_801787A0() == 0) {
        if (fn_800D0B90(p) == 0) fn_80156C78(3, 1);
        int team = p->mIdBytes[2] ^ 1;
        float distance;
        fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
        if (lbl_803EACD4->mUnknown0[6].mUnknown24 == 0.0f || !(distance > lbl_803EACD4->mUnknown0[6].mUnknown24)) {
            if (lbl_803EACD4->mUnknown1EE4) {
                lbl_803EACD4->mUnknown1EE4 = 0;
                fn_800D2378(7, fn_80178308(), 1);
            } else fn_800D2378(6, fn_80178308(), 1);
        }
    }
}

extern "C" void fn_800D4E68(int flag) {
    fn_800D0D48(7);
    if (flag != 0) {
        lbl_803EACD4->mUnknown1EE9 = 1;
        fn_800D0D48(66);
    } else {
        fn_800D0D48(68);
    }
}

extern "C" void fn_800D4EC0(int value) {
    fn_800D0D48(8);
    lbl_803EACD4->mUnknown1F5C = value;
    if (value != 1) {
        fn_800D0D48(67);
        if (value == 6) {
            lbl_803EACD4->mUnknown1EF4 = 1;
        }
    } else {
        fn_800D0D48(69);
        lbl_803EACD4->mUnknown1EE9 = 0;
    }
}

extern "C" void fn_800D4F34(int flag) {
    fn_800D0D48(5);
    fn_800D391C(24);
    if (flag != 0) {
        Object_80039F5C *p = fn_80137B40();

        lbl_803EACD4->mUnknown1EE7 = 1;
        lbl_803EACD4->mUnknown1F62 = fn_80178308();
        fn_800D2378(27, fn_80178308(), 1);
        fn_800AE7F0(10, fn_80178308(), p);
    }
}

extern "C" void fn_800D4FBC(Object_80039F5C *p, int flag) {
    fn_800D0D48(6);
    if (lbl_803EACD4->mUnknown1EE7 != 0 && p == fn_80137B40() && fn_801787A0() == 0) {
        if (flag != 0) {
            lbl_803EACD4->mUnknown1EE8 = 1;
            lbl_803EACD4->mpUnknown1F68 = p;
            fn_800D3850(1);
            fn_80156C78(16, 1);
        } else {
            fn_800D3850(0);
        }
    }
}

extern "C" void fn_800D5054(Object_80039F5C *p, int kind) {
    if (p == fn_80137B40() && fn_801787A0() == 0) {
        int accept = 0;
        fn_800D0D48(1);
        fn_800D391C(14);
        fn_800AE7F0(7, fn_80178308(), p);
        int id = 34;
        if (kind == 1) id = 38;
        else if (kind == 4) id = 42;
        if (lbl_803EACD4->mUnknown0[id].mUnknown24 != 0.0f && lbl_803EACD4->mUnknown0[id].mUnknown28 != 0) {
            int team = p->mIdBytes[2] ^ 1;
            float distance;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)lbl_803EACD4->mUnknown0[id].mUnknown28 * 46603.37890625f), &distance, 0) && !(distance > lbl_803EACD4->mUnknown0[id].mUnknown24)) accept = 1;
        } else accept = 1;
        if (accept == 0 && kind != 0) {
            if (fn_800D0B90(p) == 0) fn_80156C78(4, 1);
            lbl_803EACD4->mUnknown1EF5 = 1;
            accept = 1;
        }
        Vector_80039F5C position;
        fn_80137D58(fn_801374BC(), &position);
        Point_8017886C point = fn_80177FE0();
        if (!(position.mY >= point.mY - 4.0f) && (kind == 4 || kind == 1)) accept = 0;
        if (accept) {
            lbl_803EACD4->mUnknown1EDD = 1;
            lbl_803EACD4->mUnknown1EE0 = kind == 1;
            lbl_803EACD4->mUnknown1EF3 = kind == 4;
            lbl_803EACD4->mUnknown1EE4 = 0;
            lbl_803EACD4->mUnknown1F60 = fn_80178308();
            if (lbl_803EACD4->mUnknown1EF3) fn_800D2378(40, fn_80178308(), 1);
            else if (lbl_803EACD4->mUnknown1EE0) fn_800D2378(36, fn_80178308(), 1);
            else fn_800D2378(32, fn_80178308(), 1);
        }
    }
}

extern "C" void fn_800D52F8(Object_80039F5C *p) {
    fn_800D0D48(2);
    if (lbl_803EACD4->mUnknown1EDD != 0 && p == fn_80137B40() && fn_801787A0() == 0) {
        int b = 0;
        int id;
        int a;
        Record_800B15FC *pRecord;

        if (lbl_803EACD4->mUnknown1EF3 != 0) {
            id = 42;
            b = 4;
            fn_80156C78(6, 1);
        } else if (lbl_803EACD4->mUnknown1EE0 != 0) {
            id = 38;
            b = 1;
            fn_80156C78(5, 1);
        } else {
            id = 34;
            if (fn_800D0B90(p) == 0) {
                fn_80156C78(4, 1);
            }
        }
        if (lbl_803EACD4->mUnknown1EE4 != 0) {
            a = 1;
            id++;
        } else {
            if (lbl_803EACD4->mUnknown1EF5 != 0) {
                b = 0;
                if (id == 42) {
                    id = 110;
                    fn_80156C78(6, 1);
                } else if (id == 38) {
                    id = 109;
                    fn_80156C78(5, 1);
                }
            }
            a = 0;
        }
        fn_800D2378(id, fn_80178308(), 1);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 57;
        pRecord->mUnknown4 = a;
        pRecord->mUnknown8 = b;
        fn_800B1508();
        lbl_803EACD4->mUnknown1EE0 = 0;
        lbl_803EACD4->mUnknown1EF3 = 0;
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1EDD = 0;
        lbl_803EACD4->mUnknown1EF5 = 0;
    }
}

extern "C" void fn_800D5494(Object_80039F5C *p, int kind, unsigned char flag) {
    if (p == fn_80137B40() && fn_801787A0() == 0) {
        int accept = 0;
        fn_800D0D48(3);
        fn_800D391C(15);
        fn_800AE7F0(7, fn_80178308(), p);
        int id = 46;
        if (kind == 1 || kind == 4) id = 50;
        lbl_803EACD4->mUnknown1F5E = flag;
        if (lbl_803EACD4->mUnknown0[id].mUnknown24 != 0.0f && lbl_803EACD4->mUnknown0[id].mUnknown28 != 0) {
            int team = p->mIdBytes[2] ^ 1;
            float distance;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)lbl_803EACD4->mUnknown0[id].mUnknown28 * 46603.37890625f), &distance, 0) && !(distance > lbl_803EACD4->mUnknown0[id].mUnknown24)) accept = 1;
        } else accept = 1;
        if (accept == 0) {
            if (fn_800D0B90(p) == 0) fn_80156C78(7, 1);
            if (kind != 0) { lbl_803EACD4->mUnknown1EF5 = 1; accept = 1; }
        }
        Vector_80039F5C position;
        fn_80137D58(fn_801374BC(), &position);
        Point_8017886C point = fn_80177FE0();
        if (!(position.mY >= point.mY - 4.0f) && (kind == 4 || kind == 1)) accept = 0;
        if (accept) {
            lbl_803EACD4->mUnknown1EDE = 1;
            lbl_803EACD4->mUnknown1EE0 = kind != 0;
            lbl_803EACD4->mUnknown1EE4 = 0;
            lbl_803EACD4->mUnknown1F61 = fn_80178308();
            if (lbl_803EACD4->mUnknown1EE0) fn_800D2378(48, fn_80178308(), 1);
            else fn_800D2378(44, fn_80178308(), 1);
        }
    }
}

extern "C" void fn_800D5704(Object_80039F5C *p) {
    fn_800D0D48(4);
    if (lbl_803EACD4->mUnknown1EDE != 0 && p == fn_80137B40() && fn_801787A0() == 0) {
        int b = 0;
        Record_800B15FC *pRecord;

        if (lbl_803EACD4->mUnknown1EE4 != 0) {
            if (lbl_803EACD4->mUnknown1EE0 != 0) {
                b = 1;
                fn_800D2378(51, fn_80178308(), 1);
                fn_80156C78(8, 1);
            } else {
                fn_800D2378(47, fn_80178308(), 1);
                if (fn_800D0B90(p) == 0) {
                    fn_80156C78(7, 1);
                }
            }
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 57;
            pRecord->mUnknown4 = 1;
            pRecord->mUnknown8 = b;
            fn_800B1508();
        } else {
            if (lbl_803EACD4->mUnknown1EE0 != 0) {
                if (lbl_803EACD4->mUnknown1EF5 != 0) {
                    fn_800D2378(111, fn_80178308(), 1);
                    fn_80156C78(8, 1);
                } else {
                    b = 1;
                    fn_800D2378(50, fn_80178308(), 1);
                    fn_80156C78(8, 1);
                }
            } else {
                fn_800D2378(46, fn_80178308(), 1);
                if (fn_800D0B90(p) == 0) {
                    fn_80156C78(7, 1);
                }
            }
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 57;
            pRecord->mUnknown4 = 0;
            pRecord->mUnknown8 = b;
            fn_800B1508();
        }
        lbl_803EACD4->mUnknown1EE0 = 0;
        lbl_803EACD4->mUnknown1EF3 = 0;
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1EDE = 0;
        lbl_803EACD4->mUnknown1EF5 = 0;
    }
}

extern "C" void fn_800D5900(int value) {
    fn_800D0D48(27);
    if (value == 4 || value == 5 || value == 2) {
        lbl_803EACD4->mUnknown1EE4 = 1;
    } else if (value == 1 && lbl_803EACD4->mUnknown1EE5 != 0 && lbl_803EACD4->mUnknown1EE6 == 0) {
        fn_800D2378(12, fn_80178308(), 1);
        lbl_803EACD4->mUnknown1EE6 = value;
    }
}

extern "C" void fn_800D5998(void) {
    fn_800D0D48(29);
    lbl_803EACD4->mUnknown1EE5 = 1;
}

extern "C" void fn_800D59C8(int a) {
    fn_800D0D48(49);
    if (lbl_803EACD4->mUnknown1F34 != 0) {
        fn_800D2378(65, a, 1);
    }
    fn_800D2E50();
    lbl_803EACD4->mUnknown1EDC = 0;
}

extern "C" void fn_800D5A28(void) {
    fn_800D0D48(51);
    fn_800D5A6C(0, 0, 0);
    fn_800D5A6C(0, 0, 0);
}

extern "C" int fn_800D5A6C(int active, int a, int b) {
    int requested = active;
    int result = 0;
    if (active != 0) {
        if (fn_801787A0() != 0) active = 0;
        if (active != 0) {
            fn_80156C78(15, 1);
            if (fn_801787A0() == 0 && lbl_803EACD4->mUnknown1EDA == 0) {
                fn_800D0D48(53); fn_800D391C(11);
            }
            if (active != 0) {
                Vector_80039F5C position;
                if (fn_80178348() == fn_80137B40()->mIdBytes[2]) {
                    fn_80137D58(fn_801374BC(), &position);
                    if (lbl_803EACD4->mUnknown0[64].mUnknown36 == 0) {
                        Point_8017886C point = fn_80177FE0();
                        if (!(position.mY >= point.mY)) { active = 0; fn_800D59C8(fn_80137B40()->mIdBytes[2]); }
                    }
                } else {
                    fn_80137D58(fn_801374BC(), &position);
                    if (lbl_803EACD4->mUnknown0[64].mUnknown36 == 0 && !(position.mY >= lbl_803EACD4->mUnknown1F14)) {
                        active = 0; fn_800D59C8(fn_80137B40()->mIdBytes[2]);
                    }
                }
            }
        }
    }
    if (requested) lbl_803EACD4->mUnknown1EDB = 1;
    if (active) {
        lbl_803EACD4->mUnknown1F44 = 0;
        if (lbl_803EACD4->mUnknown1EDA == 0) {
            lbl_803EACD4->mUnknown1EDA = 1;
            lbl_803EACD4->mpUnknown1F40 = fn_80137B40();
            lbl_803EACD4->mUnknown1F2C = 0;
            fn_800D2280();
            lbl_803EACD4->mUnknown1F50 = b;
            lbl_803EACD4->mUnknown1F4C = a;
            fn_800D0D48(26);
            if (lbl_803EACD4->mUnknown206C == 0) {
                lbl_803EACD4->mpUnknown2068 = lbl_803EACD4->mpUnknown1F40;
                fn_800D3E70();
                lbl_803EACD4->mUnknown206C = 1;
            }
        } else {
            if (lbl_803EACD4->mpUnknown1F40 != fn_80137B40()) fn_800D0D48(54);
            if (lbl_803EACD4->mpUnknown1F40 == fn_80137B40()) {
                fn_800D2280();
                lbl_803EACD4->mUnknown1F50 = b;
                lbl_803EACD4->mUnknown1F4C = a;
                int scaled, value;
                fn_800D1788(fn_80137B40()->mIdBytes[2], 64, lbl_803EACD4->mUnknown1F2C, &scaled, 0, &value, 0, 0, 0, 0);
                if (value != lbl_803EACD4->mUnknown1F34) {
                    lbl_803EACD4->mUnknown1F34 = value;
                    lbl_803EACD4->mUnknown1F38 = scaled;
                    fn_800D2378(64, fn_80137B40()->mIdBytes[2], lbl_803EACD4->mUnknown1F2C);
                    if (lbl_803EACD4->mUnknown1F34 > 499) fn_80067D4C(121, 0);
                }
                if (lbl_803EACD4->mUnknown206C) {
                    float distance = (float)fabs(lbl_803EACD4->mpUnknown1F40->mMotion.mPos.mX) + 6.0f;
                    if (!(distance <= fn_800A32B4())) {
                        Object_80039F5C *p = lbl_803EACD4->mpUnknown2068;
                        fn_800310C0(lbl_803EA368, 57, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                        lbl_803EACD4->mUnknown206C = 0;
                    }
                }
            }
        }
    } else if (lbl_803EACD4->mUnknown1F2C + lbl_803EACD4->mUnknown1F30 != 0) {
        if (lbl_803EACD4->mpUnknown1F40 != fn_80137B40()) { fn_800D0D48(55); lbl_803EACD4->mUnknown1F44++; }
        if ((unsigned int)++lbl_803EACD4->mUnknown1F44 > 1) {
            int value;
            fn_800D1788(lbl_803EACD4->mpUnknown1F40->mIdBytes[2], 64, lbl_803EACD4->mUnknown1F2C, 0, 0, &value, 0, 0, 0, 0);
            fn_800D0D48(56);
            if (value) fn_800D0D48(57);
            if (lbl_803EACD4->mpUnknown1F40 == fn_80137B40()) fn_800D0D48(58);
            if (fn_801787A0()) fn_800D0D48(59);
            if (value) {
                if (lbl_803EACD4->mUnknown1F12 || lbl_803EACD4->mpUnknown1F40 == fn_80137B40()) {
                    lbl_803EACD4->mUnknown1EDC = 1;
                    lbl_803EACD4->mUnknown1F3C = lbl_803EACD4->mpUnknown1F40->mIdBytes[2];
                    lbl_803EACD4->mUnknown1F48 = lbl_803EACD4->mUnknown1F2C;
                    if (fn_801787A0() == 0) fn_800D2DF0();
                    result = 1;
                } else if (value && lbl_803EACD4->mpUnknown1F40 != fn_80137B40()) {
                    if (lbl_803EACD4->mUnknown1EEE == 0) {
                        lbl_803EACD4->mUnknown1EEE = 1;
                        lbl_803EACD4->mUnknown1F54 = lbl_803EACD4->mUnknown1F34;
                        lbl_803EACD4->mUnknown1F58 = lbl_803EACD4->mUnknown1F38;
                    }
                    fn_800D59C8(lbl_803EACD4->mpUnknown1F40->mIdBytes[2]);
                }
            }
            fn_800D2E50();
            if (lbl_803EACD4->mUnknown206C) {
                Object_80039F5C *p = lbl_803EACD4->mpUnknown2068;
                fn_800310C0(lbl_803EA368, 57, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                lbl_803EACD4->mUnknown206C = 0;
            }
        }
    }
    return result;
}

extern "C" void fn_800D5F1C(Object_80039F5C *p, int kind, unsigned char flag) {
    if (p == fn_80137B40()) { fn_800D0D48(25); fn_800D391C(0); }
    if (p == fn_80137B40() && fn_801787A0() == 0) {
        fn_800D391C(0);
        int id = 52;
        switch (kind) {
        case 0: if (fn_800D0B90(p) == 0) fn_80156C78(12, 1); break;
        case 1: id = 53; fn_80156C78(13, 1); break;
        case 4: id = 54; fn_80156C78(14, 1); break;
        }
        lbl_803EACD4->mUnknown1F5F = flag;
        fn_800AE7F0(12, p->mIdBytes[2], p);
        int team = p->mIdBytes[2] ^ 1;
        float distance;
        fn_801244F0(p, team, 0, fn_80178D18(team), &distance, 0);
        if (p->mpState->mId == 12 && p->mUnknown355[0] == 0) return;
        if (lbl_803EACD4->mUnknown0[id].mUnknown24 != 0.0f && distance > lbl_803EACD4->mUnknown0[id].mUnknown24) return;
        fn_800D2378(id, p->mIdBytes[2], 1);
        Record_800B15FC *record = fn_800B15FC();
        fn_8009BD2C(p, &record->mUnknown0);
        record->mUnknownC = p->mMotion.mPos.mX;
        record->mUnknown10 = p->mMotion.mPos.mY;
        record->mUnknown4 = kind;
        record->mUnknown14 = 59;
        fn_800B1508();
    }
}

extern "C" void fn_800D60BC(Object_80039F5C *p, int kind, unsigned char flag) {
    int accept = 0;
    if (p == fn_80137B40() && fn_801787A0() == 0) {
        fn_800D0D48(23);
        fn_800D391C(16);
        int id = 57;
        if (kind == 1) id = 60;
        else if (kind == 4) id = 63;
        lbl_803EACD4->mUnknown1F5D[0] = flag;
        fn_800AE7F0(12, p->mIdBytes[2], p);
        if (lbl_803EACD4->mUnknown0[id].mUnknown24 != 0.0f && lbl_803EACD4->mUnknown0[id].mUnknown28 != 0) {
            float distance;
            int team = p->mIdBytes[2] ^ 1;
            if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)lbl_803EACD4->mUnknown0[id].mUnknown28 * 46603.37890625f), &distance, 0) && !(distance > lbl_803EACD4->mUnknown0[id].mUnknown24)) accept = 1;
            if (accept == 0) {
                team = p->mIdBytes[2];
                if (fn_801245DC(p, team, 0, fn_80178D18(team), (int)((float)(unsigned int)lbl_803EACD4->mUnknown0[id].mUnknown28 * 46603.37890625f), &distance, 0) && !(distance > lbl_803EACD4->mUnknown0[id].mUnknown24)) accept = 1;
            }
        } else accept = 1;
    }
    if (accept == 0) {
        if (fn_800D0B90(p) == 0) fn_80156C78(9, 1);
        if (kind != 0) { lbl_803EACD4->mUnknown1EF5 = 1; accept = 1; }
    }
    Vector_80039F5C position;
    fn_80137D58(fn_801374BC(), &position);
    Point_8017886C point = fn_80177FE0();
    if (!(position.mY >= point.mY - 4.0f) && (kind == 4 || kind == 1)) accept = 0;
    if (accept) {
        lbl_803EACD4->mUnknown1EDF = 1;
        lbl_803EACD4->mUnknown1EE0 = kind == 1;
        lbl_803EACD4->mUnknown1EF3 = kind == 4;
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1F63 = fn_80178308();
        if (lbl_803EACD4->mUnknown1EF3) fn_800D2378(61, fn_80178308(), 1);
        else if (lbl_803EACD4->mUnknown1EE0) fn_800D2378(58, fn_80178308(), 1);
        else fn_800D2378(55, fn_80178308(), 1);
    }
}

extern "C" void fn_800D640C(Object_80039F5C *p) {
    fn_800D0D48(24);
    if (lbl_803EACD4->mUnknown1EDF != 0 && p == fn_80137B40() && fn_801787A0() == 0) {
        int a = 0;
        Record_800B15FC *pRecord;

        if (lbl_803EACD4->mUnknown1EF3 != 0) {
            if (lbl_803EACD4->mUnknown1EF5 != 0) {
                fn_800D2378(113, fn_80178308(), 1);
            } else {
                a = 4;
                fn_800D2378(63, fn_80178308(), 1);
            }
            fn_80156C78(11, 1);
        } else if (lbl_803EACD4->mUnknown1EE0 != 0) {
            if (lbl_803EACD4->mUnknown1EF5 != 0) {
                fn_800D2378(112, fn_80178308(), 1);
            } else {
                a = 1;
                fn_800D2378(60, fn_80178308(), 1);
            }
            fn_80156C78(10, 1);
        } else {
            fn_800D2378(57, fn_80178308(), 1);
            if (fn_800D0B90(p) == 0) {
                fn_80156C78(9, 1);
            }
        }
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 59;
        pRecord->mUnknown4 = a;
        fn_800B1508();
        lbl_803EACD4->mUnknown1EF3 = 0;
        lbl_803EACD4->mUnknown1EE0 = 0;
        lbl_803EACD4->mUnknown1EE4 = 0;
        lbl_803EACD4->mUnknown1EDF = 0;
        lbl_803EACD4->mUnknown1EF5 = 0;
    }
}

extern "C" void fn_800D65A4(int a, int b, unsigned char c) {
    fn_800D0D48(18);
    if (fn_801787A0() == 0) {
        lbl_803EACD4->mUnknown1EEF = 1;
        lbl_803EACD4->mUnknown1EF0 = a;
        lbl_803EACD4->mUnknown1EF1 = b;
        lbl_803EACD4->mUnknown1EF2 = c;
    }
}

extern "C" void fn_800D660C(Object_80039F5C *p) {
    int id;

    fn_800D0D48(19);
    if (fn_801787A0() == 0 && lbl_803EACD4->mUnknown1EEF != 0) {
        if (lbl_803EACD4->mUnknown1EF0 != 0) {
            if (lbl_803EACD4->mUnknown1EF1 != 0) {
                if (lbl_803EACD4->mUnknown1EF4 != 0) {
                    id = 114;
                    fn_8017CA10(p->mIdBytes[2], 1);
                } else {
                    id = 22;
                }
                fn_8017C9E4(p->mIdBytes[2], 1);
                fn_80156C78(38, 1);
            } else if (lbl_803EACD4->mUnknown1EF2 != 0) {
                id = 24;
                fn_8017C674(p->mIdBytes[2], 1);
                fn_80156C78(37, 1);
            } else {
                id = 20;
            }
        } else if (lbl_803EACD4->mUnknown1EF1 != 0) {
            id = 21;
            if (lbl_803EACD4->mUnknown1EF4 != 0) {
                id = 114;
            }
            fn_80156C78(38, 1);
        } else {
            id = 19;
            if (lbl_803EACD4->mUnknown1EF2 != 0) {
                id = 23;
            }
        }
        fn_800D2C10(id, fn_80178308());
    }
}

extern "C" void fn_800D6724(Object_80039F5C *p) {
    fn_800D0D48(22);
    if (lbl_803EACD4->mUnknown1F10 == 0) {
        if (fn_80178320() == p->mIdBytes[2]) {
            if (lbl_803EACD4->mUnknown1F11 == 0) {
                fn_800D0D48(61);
                lbl_803EACD4->mUnknown1F11 = 1;
                lbl_803EACD4->mpUnknown2060 = p;
            }
        } else {
            fn_800D0D48(60);
        }
    }
    lbl_803EACD4->mUnknown1F10 = 1;
}

extern "C" void fn_800D67B8(int a, Object_80039F5C *p) {
    Vector_80039F5C pos;

    fn_800D0D48(21);
    fn_800D391C(0);
    fn_800D20A0(fn_80178348(), 0);
    lbl_803EACD4->mUnknown1ED8 = 1;
    lbl_803EACD4->mUnknown1EF2 = fn_800D0B90(p);
    if (a != 0) {
        if (lbl_803EACD4->mUnknown1EF2 != 0) {
            fn_800D2C10(75, fn_80178360());
            fn_80156C78(22, 1);
        } else {
            fn_800D2C10(74, fn_80178360());
            fn_80156C78(22, 1);
        }
        fn_8017C9B8(p->mIdBytes[2], 1);
    } else if (lbl_803EACD4->mUnknown1EF2 != 0) {
        fn_800D2C10(73, fn_80178360());
        fn_80156C78(22, 1);
    } else {
        fn_800D2C10(72, fn_80178360());
        fn_80156C78(22, 1);
    }
    fn_800AE7F0(11, fn_80178360(), p);
    fn_80137D58(fn_801374BC(), &pos);
    lbl_803EACD4->mUnknown1F14 = -pos.mY;
    lbl_803EACD4->mUnknown1F80[fn_80178348()] = 0;
}

extern "C" void fn_800D6914(int flag, Object_80039F5C *p) {
    fn_800D0D48(15);
    if (p == fn_80137B40() && fn_801787A0() == 0) {
        lbl_803EACD4->mUnknown1EE1 = 1;
        lbl_803EACD4->mUnknown1EE2 = flag;
        if (flag != 0) {
            fn_800D0D48(70);
        } else {
            fn_800D0D48(71);
        }
        fn_800AE7F0(8, fn_80178308(), p);
    }
}

extern "C" void fn_800D69A4(int team, int a, int b) {
    int flag;

    fn_800D0D48(16);
    flag = lbl_803EACD4->mUnknown1EE1 != 0 && lbl_803EACD4->mUnknown1EE3 != 0;
    if (a | flag) {
        if (a == 0) {
            int count = ++lbl_803EACD4->mUnknown1F80[team];

            if (lbl_803EACD4->mUnknown1EE2 != 0) {
                fn_800D2378(18, team, count);
                fn_80156C78(18, 1);
            } else {
                fn_800D2378(15, team, count);
                fn_80156C78(17, 1);
            }
        } else {
            Vector_80039F5C pos;

            fn_800D391C(0);
            fn_800D20A0(team == 0, 0);
            lbl_803EACD4->mUnknown1ED9 = 1;
            if (b != 0) {
                fn_800D2378(105, team, 1);
            } else {
                fn_800D2378(104, team, 1);
            }
            fn_80137D58(fn_801374BC(), &pos);
            lbl_803EACD4->mUnknown1F14 = -pos.mY;
            lbl_803EACD4->mUnknown1F80[team == 0] = 0;
        }
        lbl_803EACD4->mUnknown1EE3 = 0;
        lbl_803EACD4->mUnknown1EE1 = 0;
        lbl_803EACD4->mUnknown1EE2 = 0;
    }
}

extern "C" void fn_800D6B18(Object_80039F5C *p, int flag) {
    fn_800D0D48(12);
    if (p != 0 && p->mIdBytes[2] == fn_80178360() && fn_80177C38() == 0 && fn_801787A0() == 0 &&
        lbl_803EACD4->mUnknown1ED6 == 0 && lbl_803EACD4->mUnknown1EEB == 0 && fn_801783AC(0) == 0 &&
        p->mUnknown8 != 255) {
        fn_800D0D48(13);
        if (p->mUnknown8 == 255) {
            fn_800D2378(80, p->mIdBytes[2], 1);
        } else {
            if (flag != 0) {
                fn_800D0D48(10);
            } else {
                fn_800D0D48(11);
            }
            fn_800D3C00(29);
            lbl_803EACD4->mpUnknown1F6C = p;
            lbl_803EACD4->mUnknown1EEC = 1;
            lbl_803EACD4->mUnknown1EED = flag;
            if (flag != 0 && fn_801BE648(p->mpUnknown792) != 246 && fn_801BE648(p->mpUnknown792) != 242) {
                fn_80156C78(39, 1);
            }
            fn_800D2378(81, p->mIdBytes[2], 1);
        }
        fn_800AE7F0(9, p->mIdBytes[2], p);
    }
}

extern "C" void fn_800D6C70(Object_80039F5C *p) {
    if (p != 0 && lbl_803EACD4->mUnknown1EEC != 0 && p == lbl_803EACD4->mpUnknown1F6C) {
        fn_800D0D48(14);
        fn_800D3C00(0);
    }
}

extern "C" void fn_800D6CC0(Object_80039F5C *p) {
    if (p != 0 && p == fn_80137B40()) {
        fn_800D0D48(46);
        fn_800D391C(2);
    }
}

extern "C" void fn_800D6D08(Object_80039F5C *p) {
    if (p != 0 && p == fn_80137B40()) {
        fn_800D0D48(52);
        fn_800D391C(5);
    }
}

extern "C" void fn_800D6D50(void) {
    fn_800D0D48(47);
    fn_800D391C(3);
}

extern "C" void fn_800D6D7C(Object_80039F5C *p, unsigned int count, int changed) {
    fn_800D0D48(45);
    switch (count) {
    case 1:
        if (changed != 0) {
            fn_800D2378(121, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(115, p->mIdBytes[2], 1);
        }
        break;
    case 2:
        if (changed != 0) {
            fn_800D2378(122, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(116, p->mIdBytes[2], 1);
        }
        break;
    case 3:
        if (changed != 0) {
            fn_800D2378(123, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(117, p->mIdBytes[2], 1);
        }
        break;
    case 4:
        if (changed != 0) {
            fn_800D2378(124, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(118, p->mIdBytes[2], 1);
        }
        break;
    case 5:
        if (changed != 0) {
            fn_800D2378(125, p->mIdBytes[2], 1);
        } else {
            fn_800D2378(119, p->mIdBytes[2], 1);
        }
        break;
    }
}

extern "C" void fn_800D6E98(unsigned short team) {
    fn_800D2378(120, team, 1);
    fn_8017CA68(team, 1);
}

extern "C" void fn_800D6EDC(void) {
    fn_800D0D48(45);
    fn_800D391C(4);
}

extern "C" void fn_800D6F08(void) {
    fn_800D0D48(0);
    fn_800D2378(129, 0, 1);
}

extern "C" void fn_800D6F3C(Record_800B15FC *pRecord) {
    switch (pRecord->mUnknown14) {
    case 3:
        fn_800D0D48(88);
        fn_800D2378(128, 0, 1);
        break;
    case 5:
        fn_800D0D48(89);
        fn_800D3C00(0);
        if (lbl_803EACD4->mUnknown1EE1 != 0 || lbl_803EACD4->mUnknown1EE2 != 0) {
            fn_800D378C();
        } else {
            fn_800D371C();
        }
        break;
    case 7:
        fn_800D0D48(90);
        fn_800D378C();
        break;
    case 18:
        fn_800D0D48(92);
        fn_800D3648();
        break;
    case 24:
        fn_800D0D48(94);
        fn_800D3C00(0);
        break;
    case 56:
        fn_800D0D48(93);
        fn_800D3C00(0);
        fn_800D2378(79, fn_80178320(), 1);
        break;
    case 60:
        fn_800D0D48(95);
        if (pRecord->mUnknown4 != 0) {
            fn_800D0D48(72);
            lbl_803EACD4->mUnknown1F05 = 1;
        } else {
            fn_800D0D48(73);
            lbl_803EACD4->mUnknown1F04 = 1;
        }
        break;
    }
}

extern "C" void fn_800D70CC(Record_80067CA8 *pRecord) {
    switch (pRecord->mType) {
    case 37:
        fn_800D0D48(96);
        fn_800D3C00(0);
        fn_800D391C(1);
        break;
    case 44:
        fn_800D0D48(98);
        fn_800D391C(1);
        break;
    case 100:
        fn_800D0D48(100);
        fn_800D391C(1);
        break;
    case 104:
        fn_800D0D48(101);
        fn_800D391C(0);
        break;
    }
}

extern "C" void fn_800D7158(void) {
    int mode = fn_801486A0();
    int changed = 0;
    if (mode == 0) {
        if (lbl_803EACC8 != 1) { lbl_803EACC8 = 1; changed = 1; }
    } else if (lbl_803EACC8 != 0) { lbl_803EACC8 = 0; changed = 1; }
    if (changed) {
        Object_8007A334 cursor;
        fn_8018FB4C(&cursor, lbl_803EACC8);
        for (int i = 0; i <= 126; i++) {
            if (fn_8018FBE8(&cursor, i)) fn_8018FC1C(&cursor, &lbl_803EACD4->mUnknown0[i]);
            else memset(&lbl_803EACD4->mUnknown0[i], 0, sizeof(Record_8018FC1C));
        }
        fn_8018FBC8(&cursor);
    }
    fn_800D421C(0, 0); fn_800D421C(1, 0);
    fn_800D3FBC(0, 0, 0); fn_800D3FBC(1, 0, 0);
    fn_800D20A0(0, 0); fn_800D20A0(1, 0);
    for (int i = 0; i <= 126; i++) { fn_800D3EDC(0, i, 0); fn_800D3EDC(1, i, 0); }
    lbl_803EACD4->mUnknown2064[0] = 0;
    lbl_803EACD4->mUnknown2064[1] = 0;
    lbl_803EACD4->mUnknown1ECE = 1;
    lbl_803EACD4->mUnknown1F14 = 0.0f;
    lbl_803EACD4->mUnknown2050[3] = 0;
    lbl_803EACD4->mUnknown2050[0] = 0;
    lbl_803EACD4->mUnknown2050[2] = 0;
    lbl_803EACD4->mUnknown2050[1] = 0;
    lbl_803EC9A4[0] = lbl_803EC9A4[1] = 0;
    lbl_803EC9AC[0] = lbl_803EC9AC[1] = 0;
    lbl_803EC9B4[0] = lbl_803EC9B8[0] = lbl_803EC9BC[0] = lbl_803EC9C0[0] = lbl_803EC9C4[0] = lbl_803EC9C8[0] = 0;
    lbl_803EC9B4[1] = lbl_803EC9B8[1] = lbl_803EC9BC[1] = lbl_803EC9C0[1] = lbl_803EC9C4[1] = lbl_803EC9C8[1] = 0;
    lbl_803EC9CC[0] = lbl_803EC9CC[1] = 0;
    lbl_803EC9D0[0] = lbl_803EC9D0[1] = 0;
    lbl_803EC9D4[0] = lbl_803EC9D4[1] = 0;
    lbl_803EC9DC[1] = lbl_803EC9D4[1] = lbl_803EC9D8[0] = lbl_803EC9D8[1] = lbl_803EC9DC[0] = 0;
    for (int i = 6; i < 69; i++) ((unsigned char *)lbl_803EACD4)[0x1ECF + i] = 0;
    lbl_803EACD8 = 2;
    lbl_803EACC4 = 1;
    lbl_803EACC5 = (unsigned int)(mode - 2) > 1;
}

extern "C" void fn_800D7438(void) {
    void *pHandle;

    lbl_803EACD0 = 20000;
    if (fn_8017F584() == 0) {
        if (fn_80054D24(28)) {
            lbl_803EACD0 = 10000;
        } else if (fn_80054D24(29)) {
            lbl_803EACD0 = 2000;
        }
    }
    pHandle = fn_80238174(0, (void **)&lbl_803EACD4, sizeof(State_800D0D4C), 0, 0x7472636B);
    fn_80238234(pHandle, fn_800D3D68, fn_800D3D8C, 0, fn_800D3D94);
    fn_80238248(pHandle, fn_800D3DD0, fn_800D3E68, fn_800D3E1C);
    fn_802381E0(pHandle);
    fn_800D7158();
}

extern "C" void fn_800D750C() {
    lbl_803EACC8 = 2;
    lbl_803EACD0 = 20000;
}

extern "C" void fn_800D7520(int a) {
    lbl_803EACC4 = a;
}

extern "C" unsigned char fn_800D7528(int team) {
    return lbl_803EC9C4[team];
}

extern "C" void fn_800D7534(int team) {
    lbl_803EC9CC[team] = 1;
}

extern "C" unsigned char fn_800D7544(int team) {
    return lbl_803EC9D0[team];
}

extern "C" unsigned int fn_800D7550(int side, unsigned int value) {
    int index = fn_80186F7C((unsigned char)side);
    unsigned int result = 0;
    if (index != -1) {
        result = (unsigned int)((float)value * lbl_803EACCC);
        fn_8008880C(fn_8022F358(index), result);
    }
    return result;
}

extern "C" void fn_800D7604(Callback_800D7604 a) {
    lbl_803EACC0 = a;
}
