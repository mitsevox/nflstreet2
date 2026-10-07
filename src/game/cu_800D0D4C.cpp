#include <string.h>
#include "game/Entry_80219044.h"
#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8021D7B8.h"

/* Partial view of the object that lbl_803EACD4 points to; its total size is
   unknown and unaccessed regions remain opaque. */
struct State_800D0D4C {
    char mUnknown0[6776];
    int mUnknown1A78;
    int mUnknown1A7C;
    char mUnknown1A80[508];
    char mUnknown1C7C[80];
    Entry_80219044 mUnknown1CCC;
    char mUnknown1CD8[251];
    char mUnknown1DD3[251];
    char mUnknown1ECE[7];
    unsigned char mUnknown1ED5;
    unsigned char mUnknown1ED6;
    unsigned char mUnknown1ED7;
    char mUnknown1ED8[2];
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
    char mUnknown1EE5[2];
    unsigned char mUnknown1EE7;
    unsigned char mUnknown1EE8;
    unsigned char mUnknown1EE9;
    unsigned char mUnknown1EEA;
    unsigned char mUnknown1EEB;
    unsigned char mUnknown1EEC;
    unsigned char mUnknown1EED;
    unsigned char mUnknown1EEE;
    char mUnknown1EEF[4];
    unsigned char mUnknown1EF3;
    unsigned char mUnknown1EF4;
    char mUnknown1EF5[2];
    unsigned char mUnknown1EF7;
    char mUnknown1EF8[1];
    unsigned char mUnknown1EF9;
    unsigned char mUnknown1EFA;
    unsigned char mUnknown1EFB;
    unsigned char mUnknown1EFC;
    unsigned char mUnknown1EFD;
    unsigned char mUnknown1EFE;
    unsigned char mUnknown1EFF;
    char mUnknown1F00[2];
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
    char mUnknown1F0C[4];
    unsigned char mUnknown1F10;
    unsigned char mUnknown1F11;
    char mUnknown1F12[26];
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
    char mUnknown1F6C[4];
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
extern void *lbl_803EB688;

void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_801486A0(void);
void fn_800AE7F0(int a, int b, Object_80039F5C *p);
void fn_80156C78(int a, int b);
int fn_80177C38(void);
int fn_80177F7C(void);
int fn_80178308(void);
int fn_80178348(void);
int fn_80178360(void);
Object_80039F5C *fn_8017876C(void);
int fn_801787A0(void);
int fn_80179138(void);

void fn_800D0D48(int a);
void fn_800D1788(int a, int b, int c, int *p0, int *p1, int *p2, int *p3, int *p4, int *p5, int *p6);
void fn_800D1D84(int a, int b, int c);
void fn_800D20A0(int a, int b);
void fn_800D2378(int a, int b, int c);
void fn_800D59C8(int a);
void fn_800D5A28(void);

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
extern "C" int fn_800D3D8C() {
    return 0;
}
extern "C" int fn_800D3E68() {
    return 8304;
}
extern "C" int fn_800D42CC() {
    return lbl_803EACD8;
}
extern "C" void fn_800D750C() {
    lbl_803EACC8 = 2;
    lbl_803EACD0 = 20000;
}
extern "C" void fn_800D7520(int a) {
    lbl_803EACC4 = a;
}
extern "C" void fn_800D7604(Callback_800D7604 a) {
    lbl_803EACC0 = a;
}
