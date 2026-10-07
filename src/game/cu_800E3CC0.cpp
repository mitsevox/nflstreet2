#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

struct Record_80163E94 {
    char mUnknown0[11];
    unsigned char mUnknownB;
};

struct Block_800E7588 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    char mUnknown5[1];
    short mUnknown6;
    char mUnknown8[11];
    unsigned char mUnknown19;
};

struct Query_800CE770 {
    Object_80039F5C *mpUnknown0;
    Object_80039F5C *mpUnknown4;
    char mUnknown8[44];
    short mUnknown52;
    unsigned char mUnknown54;
    char mUnknown55[9];
};

struct Command_800CEE74 {
    char mUnknown0[64];
};

extern "C" {
int fn_800B5FEC(Object_80039F5C *p);
void fn_800B76E8(Object_80039F5C *p);
int fn_800B7F34(Object_80039F5C *p);
int fn_800B7F88(Object_80039F5C *p);
int fn_800B83A0(Object_80039F5C *p);
void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag);
int fn_800C3BEC(Object_80039F5C *p, Command_800CEE74 *pCommand, int *pValue, int *pB);
int fn_800C05F4(void);
int fn_800CE510(Query_800CE770 *pQuery);
void fn_800CE770(Query_800CE770 *pQuery);
void fn_800CEE74(Command_800CEE74 *pCommand, Object_80039F5C *p, Object_80039F5C *pOther, void *pData, int a, int b, int flag);
int fn_800A8444(int team);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800D0C0C(Object_80039F5C *p, int a);
int fn_800E5C00(Object_80039F5C *p, int value);
int fn_800E6984(Object_80039F5C *p);
void fn_800E7588(Object_80039F5C *p, Block_800E7588 *pBlock);
unsigned int fn_8011E188(void);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int a);
int fn_8011F1A4(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801486A0(void);
Record_80163E94 *fn_80163E94(Object_800670B4 *pObject, unsigned int index, void *pArg);
Object_800670B4 *fn_80168708(int team);
Point_8017886C fn_80177FE0(void);
int fn_80177F70(void);
int fn_80178320(void);
int fn_801783AC(int bit);
int fn_801787A0(void);
int fn_801BE648(void *p);
void fn_80227690(void *pOut, void *pA, void *pB);

extern int lbl_802DA8BC[7][2][3];
extern int lbl_802DA964[7][2][3];
extern int lbl_802DAA0C[7][2][3];
extern short lbl_803EAD54;
extern unsigned char lbl_803EAD69;
extern unsigned char lbl_803EAD6A;
extern unsigned char lbl_803EAD6B;
extern unsigned char lbl_803EAD6C;
extern unsigned int lbl_803EAD80;
}

extern "C" int fn_800E579C(Object_80039F5C *p) {
    int result = 1;
    void *pRecord;
    Object_800670B4 *pObject = fn_80168708(p->mIdBytes[2]);

    if (pObject->mUnknown8.mUnknownF == 0) {
        pRecord = fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = fn_80163E94(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if (fn_800F06F4(0, pRecord, 48, 0xFFFF) != 0xFFFF && fn_800F06F4(0, pRecord, 30, 0xFFFF) != 0xFFFF) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800E5B04(Object_80039F5C *pOther, Object_80039F5C *p, int *pList) {
    int result = 0;

    if (fn_80137C48(pOther) == 0) {
        Query_800CE770 query;

        fn_800CE770(&query);
        query.mpUnknown0 = pOther;
        query.mpUnknown4 = p;
        if (fn_800A8444(p->mIdBytes[2]) != 0) {
            query.mUnknown54 = fn_800E6984(p);
        }
        while (result == 0 && *pList != 0xFFFF) {
            query.mUnknown52 = *pList;
            if (*pList == 241 || *pList == 242) {
                query.mUnknown54 = fn_800E5C00(p, *pList);
            }
            pList++;
            result = fn_800CE510(&query);
        }
        if (result != 0) {
            fn_8011E1BC(pOther, p, 0, 5);
            fn_8011E33C(p, pOther, 6);
        }
    }
    return result;
}

extern "C" int fn_800E67AC(Object_80039F5C *p, Object_80039F5C *pOther) {
    int result = 1;

    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 34:
    case 35:
    case 36:
    case 43:
        result = 0;
        break;
    case 32:
        if (pOther == 0 || p->mUnknown1032 != 6 || pOther->mUnknown1032 != 6) {
            result = 0;
            break;
        }
    default:
        if (p->mIdBytes[2] != fn_80178320()) {
            result = 0;
        }
        if (fn_800AD9B4() != 3) {
            result = 0;
        }
        if (p->mUnknown1032 != 4 && p->mUnknown1032 != 6) {
            result = 0;
        }
        break;
    }
    return result;
}

extern "C" int *fn_800E68A8(int flag, unsigned int index) {
    int *pList;

    if (index <= 6) {
        if (fn_800A8444(fn_80178320()) != 0) {
            pList = lbl_802DAA0C[index][0];
        } else if (fn_8011F1A4() != 0 || fn_801783AC(0) != 0) {
            if (flag) {
                pList = lbl_802DA8BC[index][0];
            } else {
                pList = lbl_802DA8BC[index][1];
            }
        } else if (flag) {
            pList = lbl_802DA964[index][0];
        } else {
            pList = lbl_802DA964[index][1];
        }
    } else {
        pList = lbl_802DA8BC[4][1];
    }
    return pList;
}

extern "C" int fn_800E7330(Object_80039F5C *p) {
    if (fn_800AD9B4() != 2) {
        if (fn_80177F70() != 0) {
            if (fn_800B5FEC(p) != 0 && fn_800C05F4() == 0 && fn_801486A0() != 0) {
                fn_800B76E8(p);
            }
        } else if (p->mUnknown2914 != 19 && p->mUnknown2914 != 20 && p->mUnknown2914 != 23) {
            fn_800B7F34(p);
            p->mFlags &= ~0x4000;
        }
    }
    return 0;
}

extern "C" void fn_800E7B90(Object_80039F5C *p, Block_800E7588 *pBlock) {
    unsigned char saved = p->mUnknown1008;
    Command_800CEE74 command;
    int value;
    int unused;
    int flag;
    int index;

    if (fn_800B83A0(p) != 0) {
        p->mUnknown1008 = 1;
        pBlock->mUnknown19 = 1;
    } else {
        p->mUnknown1008 = 2;
    }
    flag = p->mUnknown776 == 1;
    fn_800CEE74(&command, p, 0, 0, 0, 237, flag);
    index = fn_800C3BEC(p, &command, &value, &unused);
    if (index != -1) {
        fn_800C39E0(p, 237, index, value, flag);
        fn_800D0C0C(p, 0);
        p->mFlags |= 8;
    } else {
        p->mUnknown1008 = saved;
        fn_800D0BF4(p, 1, 12);
        fn_800E7588(p, pBlock);
    }
}

extern "C" int fn_800E7C84(Object_80039F5C *p) {
    int result = 1;

    switch (p->mpState->mId) {
    case 32:
        if (fn_801BE648(p->mpUnknown792) != 242 || p->mIdBytes[2] != fn_80178320()) {
            result = 0;
        }
        break;
    case 36:
        break;
    default:
        result = p->mUnknown1032 != 4;
        if (fn_801787A0() != 0) {
            result = 0;
        }
        break;
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 34:
    case 35:
    case 43:
        result = 0;
        break;
    }
    if (fn_8011E188() <= 30) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800E7D80(Object_80039F5C *p) {
    int result = 1;
    Object_80137ABC *pBall = fn_801374BC();

    if (p != 0 && pBall != 0) {
        if (fn_8013BA58(pBall, 0) == 4) {
            Vector_80039F5C pos;
            int ok;

            fn_80137D58(pBall, &pos);
            ok = 0;
            if (pos.mY <= fn_80177FE0().mY) {
                ok = !fn_801783AC(11);
            }
            if (ok && p->mIdBytes[3] == 1 && p->mUnknown2914 <= 18 && p->mUnknown2914 >= 10) {
                Vector_80039F5C delta;

                fn_80227690(&delta, &p->mMotion, &pos);
                fn_802270A4(&delta);
            }
        } else if (p == fn_80137B40() && fn_801486A0() == 0) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800E86E4(Object_80039F5C *p) {
    if (p->mUnknown354 == 0 && p->mIdBytes[2] == fn_80178320()) {
        p->mFlags &= ~8;
        return 1;
    }
    return 0;
}

extern "C" int fn_800E8740() {
    return 0;
}

extern "C" int fn_800E8748(Object_80039F5C *p) {
    int done = 0;
    Block_800E7588 *pBlock = (Block_800E7588 *)&p->mUnknown336;

    if (pBlock->mUnknown4 == 1) {
        pBlock->mUnknown6++;
        if (fn_800D0B90(p) != 0) {
            Input_800B6D34 input;

            fn_800B6D34(p, &input);
            if (input.mUnknown97 & 0x40) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD69;
            } else if (input.mUnknown97 & 0x80) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD6A;
            } else if (input.mUnknown98 & 1) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD6B;
            } else if (input.mUnknown98 & 2) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD6C;
            } else if (pBlock->mUnknown6 >= lbl_803EAD54) {
                done = 1;
            }
        } else {
            done = 1;
        }
        if (done) {
            pBlock->mUnknown4 = 0;
            fn_800E7588(p, pBlock);
        }
    }
    fn_800B7F88(p);
    return 0;
}

extern "C" int fn_800E885C(void) {
    return fn_802372EC(0, 100) >= lbl_803EAD80 ? 4 : 0;
}

extern "C" int fn_800E8ED4(int value) {
    switch (value) {
    case 25:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 66:
    case 79:
    case 93:
    case 94:
    case 95:
    case 96:
    case 106:
    case 107:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 130:
    case 131:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 161:
    case 164:
    case 172:
    case 173:
    case 174:
    case 175:
    case 181:
    case 182:
    case 183:
    case 184:
    case 186:
    case 211:
    case 231:
    case 233:
    case 234:
    case 238:
    case 241:
    case 242:
    case 247:
        return 1;
    }
    return 0;
}

extern "C" int fn_800EA1D0() {
    return 0;
}

extern "C" int fn_800EAFFC() {
    return 1;
}

extern "C" int fn_800ECE28() {
    return 0;
}

extern "C" int fn_800ECE30() {
    return 0;
}
