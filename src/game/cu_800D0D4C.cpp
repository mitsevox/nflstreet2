#include <string.h>
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

/* Partial view of the 0x2070-byte block that 0x800D7438 registers under the
   id 'trck' with lbl_803EACD4 as its pointer; unaccessed regions remain
   opaque. */
struct State_800D0D4C {
    char mUnknown0[6760];
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
    char mUnknown1F12[1];
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
    char mUnknown1F4C[4];
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
    char mUnknown2050[16];
    Object_80039F5C *mpUnknown2060;
    unsigned char mUnknown2064[2];
    char mUnknown2066[2];
    Object_80039F5C *mpUnknown2068;
    char mUnknown206C[4];
};

enum Code_800D0F98 {
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
extern unsigned char lbl_803EC9C4[2];
extern unsigned char lbl_803EC9CC[2];
extern unsigned char lbl_803EC9D0[2];
extern void *lbl_803EB688;

int fn_80025708(void);
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

extern "C" void fn_800D1700(int i) {
    Entry_80219044 *args[1];

    if (lbl_803EACC4) {
        args[0] = &lbl_803EACD4->mUnknown1CCC;
        args[0]->mpText = i == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3;
        args[0]->mLength = strlen(i == 0 ? lbl_803EACD4->mUnknown1CD8 : lbl_803EACD4->mUnknown1DD3);
        fn_8021D7B8(lbl_803EB688, 0x80000018, 1, args);
    }
}

extern "C" int fn_800D207C(int i) {
    return *(i == 0 ? &lbl_803EACD4->mUnknown1A78 : &lbl_803EACD4->mUnknown1A7C);
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
extern "C" void fn_800D7604(Callback_800D7604 a) {
    lbl_803EACC0 = a;
}
