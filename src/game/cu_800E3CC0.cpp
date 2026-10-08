#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/Record_800B15FC.h"
#include "game/Record_800DB60C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800670B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

/* Player block at +336 as used by the functions of the state entry at
   0x802DB370. */
struct State_800E9E18 {
    char mUnknown0[20];
    char mUnknown20[20];
};

/* Player block at +336 as used by the functions of the state entry at
   0x802DB7D8. */
struct State_800EBCE0 {
    char mUnknown0[28];
    int mUnknown28;
    char mUnknown32[8];
    unsigned short mUnknown40;
    unsigned char mUnknown42;
    unsigned char mUnknown43;
    signed char mUnknown44;
    signed char mUnknown45;
    char mUnknown46[2];
    char mUnknown48[12];
};

/* Player block at +336 as used by the functions of the state entry at
   0x802DB4F0. */
struct State_800EDC68 {
    int mUnknown0;
    char mUnknown4[3];
    unsigned char mUnknown7;
    unsigned int mUnknown8;
};

/* Player block at +336 as used by the functions of the state entries at
   0x802DB3B8 and 0x802DB3D0. */
struct State_800EE9AC {
    char mUnknown0[48];
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    char mUnknown51[1];
    int mUnknown52;
};

struct State_800EE7C8 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Block_800E7588 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    char mUnknown5[1];
    short mUnknown6;
    char mUnknown8[11];
    unsigned char mUnknown19;
};

extern "C" {
extern unsigned char lbl_803EAD9C[8];
extern unsigned char lbl_803EADA4[8];
extern float lbl_803ECB08;
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A578(int handle);
void fn_8009A8D4(void *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
Object_80039F5C *fn_800B6544(int index);
int fn_800B65A0(int team);
void fn_800B67FC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800B78DC(Object_80039F5C *p);
int fn_800B7FE8(Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
void fn_800EFE60(int a, void *p, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_8011E9D8(State_80039F5C *pState);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801486A0(void);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_80178308(void);
int fn_80178320(void);
int fn_801787A0(void);
int fn_801BA5A8(void *a, void *b, unsigned short c, int d);
float fn_801BD660(void *p, int key);
int fn_801BE648(void *p);
int fn_800E92DC(Object_80039F5C *p);
int fn_800E948C(Object_80039F5C *p);
int fn_800EA284(Object_80039F5C *p, int angle, int direction);
int fn_800EAF34(Object_80039F5C *p, int a, int b, int c);
int fn_800EB004(Object_80137ABC *pBall);
void fn_800EC9E4(Object_80039F5C *p, int a, int b);
int fn_800EB3E8(Object_80039F5C *p, State_800EBCE0 *pState, Object_80137ABC *pBall, int a, int b);
void fn_800EE964(State_800EE9AC *pState, Object_80039F5C *p, Point_8017886C *pPoint, int value);
void fn_800EEE3C(Point_8017886C *pOut, int *pFacing, Object_80039F5C *p, int value);
int fn_800EEA20(Object_80039F5C *p);
int fn_800B5FEC(Object_80039F5C *p);
int fn_800B76E8(Object_80039F5C *p);
int fn_800B7F34(Object_80039F5C *p);
int fn_800B7F88(Object_80039F5C *p);
int fn_800B83A0(Object_80039F5C *p);
int fn_800C05F4(void);
int fn_800CE510(Query_800CE770 *pQuery);
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
Object_800670B4 *fn_80168708(int team);
Point_8017886C fn_80177FE0(void);
int fn_80177F70(void);
int fn_801783AC(int bit);
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
    unsigned char saved = p->mUnknown1008.mUnknown0;
    Command_800CEE74 command;
    int value;
    int unused;
    int flag;
    int index;

    if (fn_800B83A0(p) != 0) {
        p->mUnknown1008.mUnknown0 = 1;
        pBlock->mUnknown19 = 1;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    flag = p->mUnknown776 == 1;
    fn_800CEE74(&command, p, 0, 0, 0, 237, flag);
    index = fn_800C3BEC(p, &command, &value, &unused);
    if (index != -1) {
        fn_800C39E0(p, 237, index, value, flag);
        fn_800D0C0C(p, 0);
        p->mFlags |= 8;
    } else {
        p->mUnknown1008.mUnknown0 = saved;
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
            if (input.mBytes92[5] & 0x40) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD69;
            } else if (input.mBytes92[5] & 0x80) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD6A;
            } else if (input.mBytes92[6] & 1) {
                done = 1;
                p->mpState->mUnknown3[0] = lbl_803EAD6B;
            } else if (input.mBytes92[6] & 2) {
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

extern "C" unsigned char fn_800E9010(int angle, int difference) {
    return lbl_803EADA4[((angle + 0x100000) >> 21) & 7];
}

extern "C" void fn_800E9024(Object_80039F5C *p, int id) {
    if (fn_800E92DC(p)) {
        int heading = p->mMotion.mUnknown32;
        Message_800F01CC message;
        int difference;
        int relative;
        fn_801C1F94(&message, 0, 4);
        message.mId = id;
        message.mUnknown1[1] = 8;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pOther) {
            Point_8017886C delta;
            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            difference = fn_801CFFD0(p->mMotion.mFacing, angle);
            angle = (angle - p->mMotion.mFacing) & 0xFFFFFF;
            if (fn_80137C48(p) && p->mUnknown776 == 1)
                angle = 0x1000000 - angle;
            if (id == 58 && fn_80137B40() == p)
                message.mUnknown1[1] = lbl_803EADA4[((angle + 0x100000) >> 21) & 7];
            else
                message.mUnknown1[1] = fn_800E9010(angle, difference);
        }
        difference = fn_801CFFD0(p->mMotion.mFacing, heading);
        relative = (heading - p->mMotion.mFacing) & 0xFFFFFF;
        if (fn_80137C48(p) && p->mUnknown776 == 1)
            relative = 0x1000000 - relative;
        int octant = ((relative + 0x100000) >> 21) & 7;
        message.mUnknown1[0] = fn_800E9010(relative, difference) | lbl_803EAD9C[octant] << 4;
        message.mUnknown1[2] = fn_800E948C(p);
        if (p == fn_80137B40()) {
            if (id == 58 && message.mUnknown1[1] != 8)
                message.mUnknown1[0] = 0x88;
            int previous = fn_800F06F4(0, p->mpState, 18, 0xFFFF);
            fn_800EFE60(0, p->mpState, p);
            fn_800F053C(0, p->mpState, &message, p);
            p->mFlags &= ~0x2000;
            p->mFlags &= ~0x8;
            fn_800CE674(&p->mUnknown1240);
            fn_800CE684(&p->mUnknown1240);
            if (previous == 0xFFFF) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 1;
                fn_800F03D8(0, p->mpState, &message, p);
            } else {
                fn_801C1F94(&message, 0, 4);
                message.mId = 18;
                fn_800F03D8(0, p->mpState, &message, p);
            }
        } else {
            switch (p->mpState->mId) {
            case 57:
            case 94:
                break;
            case 25:
            case 26:
                fn_800F05E4(0, p->mpState, &message, p);
                break;
            default:
                fn_800F00D4(0, p->mpState, &message, p);
                break;
            }
        }
    }
}

extern "C" int fn_800E92DC(Object_80039F5C *p) {
    int result;
    if (p->mFlags & 0x800)
        result = 0;
    else
        result = 1;
    switch (p->mpState->mId) {
    case 10:
    case 11:
    case 17:
    case 32:
    case 94:
        result = 0;
        break;
    case 28: {
        int unknown;
        int handle;
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        if (fn_8009A578(handle) == 5 || fn_8009A578(handle) == 4)
            result = 0;
        break;
    }
    case 16:
        result = 0;
        if (p == fn_80137B40() && (p->mFlags & 0x80000))
            result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" int fn_800E93CC(Object_80039F5C *p) {
    int result = 1;
    switch (p->mpState->mId) {
    case 10:
    case 50:
    case 94:
        result = 0;
        break;
    case 28: {
        int unknown;
        int handle;
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        if (fn_8009A578(handle) == 5)
            result = 0;
        if ((handle >> 29 & 3) == 1)
            result = 0;
        break;
    }
    case 16:
    case 17:
    case 32:
        result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" void fn_800E9504(Object_80039F5C *p) {
    fn_800E9024(p, 10);
}

extern "C" void fn_800E9528(Object_80039F5C *p) {
    fn_800E9024(p, 58);
}

extern "C" int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther) {
    if (fn_800E92DC(p)) {
        Message_800F01CC message;
        Point_8017886C delta;
        Object_800B26B0 *pOtherMotion = &pOther->mMotion;
        Object_800B26B0 *pMotion = &p->mMotion;
        fn_80227690(&delta, &pOtherMotion->mPos, &pMotion->mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int away = (angle - 0x800000) & 0xFFFFFF;
        int difference = fn_801CFFD0(pOtherMotion->mUnknown32, away) * 2 / 3;
        if (((away - pOtherMotion->mUnknown32) & 0xFFFFFF) > 0x800000)
            away = (away + difference) & 0xFFFFFF;
        else
            away = (away - difference) & 0xFFFFFF;
        difference = fn_801CFFD0(pMotion->mFacing, angle);
        angle = (angle - pMotion->mFacing) & 0xFFFFFF;
        fn_801C1F94(&message, 0, 4);
        message.mId = 10;
        message.mUnknown1[1] = fn_800E9010(angle, difference);
        difference = fn_801CFFD0(pMotion->mFacing, away);
        away = (away - pMotion->mFacing) & 0xFFFFFF;
        int octant = ((away + 0x100000) >> 21) & 7;
        message.mUnknown1[0] = fn_800E9010(away, difference) | lbl_803EAD9C[octant] << 4;
        message.mUnknown1[2] = fn_800E948C(p);
        if (p->mpState->mId == 31) {
            if (fn_8011E9D8(p->mpState))
                fn_800F05E4(0, p->mpState, &message, p);
            else
                fn_800F00D4(0, p->mpState, &message, p);
        } else {
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    return 0;
}

extern "C" int fn_800E98A4(Object_80039F5C *p, Object_80039F5C *pOther) {
    Message_800F01CC message;
    Point_8017886C delta;
    Object_800B26B0 *pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    int away = (angle - 0x800000) & 0xFFFFFF;
    int difference = fn_801CFFD0(angle, away);
    fn_801C1F94(&message, 0, 4);
    message.mId = 10;
    message.mUnknown1[1] = fn_800E9010(angle, difference);
    difference = fn_801CFFD0(pMotion->mFacing, away);
    away = (away - pMotion->mFacing) & 0xFFFFFF;
    int octant = ((away + 0x100000) >> 21) & 7;
    message.mUnknown1[0] = fn_800E9010(away, difference) | lbl_803EAD9C[octant] << 4;
    message.mUnknown1[2] = fn_800E948C(p);
    fn_800F00D4(0, p->mpState, &message, p);
    return p->mpState->mId == 10;
}

extern "C" void fn_800E9DBC(Object_80039F5C *p, Object_80039F5C *pOther) {
    Point_8017886C delta;
    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    int direction = fn_801CFE40(delta.mY, delta.mX);
    fn_800EA284(p, (direction + 0x800000) & 0xFFFFFF, direction);
}

extern "C" int fn_800E9FC0(Object_80039F5C *p) {
    p->mFlags &= ~0x4000000;
    return 0;
}

extern "C" int fn_800EA1D0() {
    return 0;
}

extern "C" int fn_800EA1D8(Object_80039F5C *p) {
    int index = fn_800B65A0(p->mIdBytes[2]);
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    if (input.mUnknown95 & 0x40) {
        fn_800DB60C((Record_800DB60C *)((State_800E9E18 *)&p->mUnknown336)->mUnknown20, p);
    } else {
        int mode = fn_800AD9B4();
        if (p->mIdBytes[2] == fn_80178320() || mode == 3
            || (mode == 2 && index != 255 && fn_800B6544(index) != p))
            return fn_800B7FE8(p);
    }
    return 0;
}

extern "C" int fn_800EAC9C(Object_80039F5C *p) {
    int result = 0;
    int animation = fn_801BE648(p->mpUnknown792);
    int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, 0);
    if (index != 0xFFFF) {
        float start = fn_801BD660(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0xC001);
        result = start < fn_801BD660(p->mpUnknown800[index].mUnknown4C.mpUnknown0, 0x8000);
    }
    return result;
}

extern "C" int fn_800EAEA4(Object_80039F5C *p) {
    if (p->mpState->mId != 28)
        return 1;
    return 0;
}

extern "C" void fn_800EAEC0(Vector_80039F5C *pOut, Object_80137ABC *pBall, float scale) {
    Vector_80039F5C step;
    Vector_80039F5C velocity;
    fn_80137D58(pBall, pOut);
    fn_80137EC4(pBall, &velocity);
    fn_80227264(&step, &velocity, scale);
    fn_8022765C(pOut, pOut, &step);
}

extern "C" int fn_800EAFFC(Object_80039F5C *p, Object_80137ABC *pBall) {
    return 1;
}

extern "C" int fn_800EB0C4(Object_80137ABC *pBall, Object_80039F5C *p) {
    switch (fn_800EB004(pBall)) {
    case 0:
        if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 7;
        if (fn_801CFFD0(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 2;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 3;
        if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 4;
        return 6;
    case 1:
        if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 2;
        if (fn_801CFFD0(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 3;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 5;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 6;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 7;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 1;
        return 1;
    case 3:
        if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 4;
        if (fn_801CFFD0(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 6;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 7;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 2;
        return 3;
    case 2:
        if (fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0xA00000) <= 0xFFFFF)
            return 1;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xFFFFF)
            return 2;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x600000) <= 0xFFFFF)
            return 3;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xFFFFF)
            return 4;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x200000) <= 0xFFFFF)
            return 6;
        if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xFFFFF)
            return 7;
        break;
    }
    return 1;
}

extern "C" void fn_800EB78C(Object_80039F5C *p) {
    State_800EBCE0 *state = (State_800EBCE0 *)&p->mUnknown336;
    if (fn_800EB3E8(p, state, fn_80137ABC(state->mUnknown43), 1, 1))
        state->mUnknown40 = fn_800EAF34(p, 0, 0, 0);
}

extern "C" int fn_800EB7F8(Object_80039F5C *p, State_800EBCE0 *state) {
    int result = 1;
    int value;
    fn_8013BA58(fn_80137ABC(state->mUnknown43), &value);
    if (p->mIdBytes[2] != fn_80178308() && !fn_800EAFFC(p, fn_80137ABC(state->mUnknown43)))
        result = 0;
    return result;
}

extern "C" int fn_800EBCE0(Object_80039F5C *p) {
    State_800EBCE0 *state = (State_800EBCE0 *)&p->mUnknown336;
    state->mUnknown40 = 0xFFFF;
    state->mUnknown45 = -1;
    state->mUnknown42 = state->mUnknown28 = 0;
    state->mUnknown43 = p->mpState->mUnknown1;
    if (p->mIdBytes[3] == 1) {
        fn_8011E3EC(p, 0);
        if (p->mIdBytes[2] == fn_80178308()) {
            fn_8011E240(p);
        } else {
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
            if (pOther)
                fn_8011E240(pOther);
        }
    }
    state->mUnknown44 = -1;
    fn_8009A8D4(state->mUnknown48);
    return 0;
}

extern "C" int fn_800EBD8C(Object_80039F5C *p) {
    State_800EBCE0 *state = (State_800EBCE0 *)&p->mUnknown336;
    if (state->mUnknown40 != 0xFFFF) {
        state->mUnknown42 = 1;
        return 0;
    }
    p->mFlags &= ~8;
    return 1;
}

extern "C" int fn_800EC640(Object_80039F5C *p) {
    State_800EBCE0 *state = (State_800EBCE0 *)&p->mUnknown336;
    int result = 1;
    if (state->mUnknown40 != 0xFFFF)
        result = state->mUnknown45 == 2;
    return result;
}

extern "C" int fn_800EC6DC(Object_80039F5C *p) {
    if (((State_800EBCE0 *)&p->mUnknown336)->mUnknown40 != 0xFFFF)
        return 0;
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    if (input.mBytes92[0] & 1) {
        fn_800EB78C(p);
        return 0;
    }
    int value;
    fn_8013BA58(fn_801374BC(), &value);
    return fn_800B78DC(p);
}

extern "C" int fn_800EC758(Object_80039F5C *p) {
    return ((State_800EBCE0 *)&p->mUnknown336)->mUnknown40 == 0xFFFF;
}

extern "C" int fn_800EC840(Object_80039F5C *p, int value) {
    return fn_801787A0() == 0 ? 208 : 209;
}

extern "C" int fn_800ECD14(Object_80039F5C *p) {
    int result = 0;
    if (p->mUnknown336 != 0) {
        p->mUnknown336--;
        return 0;
    }
    fn_8010A2DC(p, 0, 0);
    if (p->mIdBytes[3] == 1 && (p->mFlags & 0x1000)) {
        p->mFlags &= ~0x1000;
        Object_80137ABC *pBall = fn_80137C48(p);
        if (pBall && fn_801486A0())
            fn_8013791C(pBall, 5, 0);
    }
    int kind = p->mUnknown9[0];
    unsigned int flags = p->mFlags;
    if (kind == 8 || (flags & 4)) {
        p->mUnknown9[0] = 1;
        p->mUnknown512.mUnknown14 = 1;
        p->mFlags = flags & ~0x10804;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        result = 1;
    } else if (kind != 1) {
        fn_800EC9E4(p, kind, 0);
    }
    return result;
}

extern "C" int fn_800ECE28() {
    return 0;
}

extern "C" int fn_800ECE30() {
    return 0;
}

extern "C" int fn_800ECE38(Object_80039F5C *p) {
    int mode = fn_800AD9B4();
    int index = fn_800B65A0(p->mIdBytes[2]);
    if (p->mIdBytes[2] == fn_80178320() || mode == 3
        || (mode == 2 && index != 255 && fn_800B6544(index) != p))
        return fn_800B7FE8(p);
    return 0;
}

extern "C" int fn_800ED0F4(Object_80039F5C *p, State_800EDC68 *state) {
    int result = 0;
    unsigned int kind = state->mUnknown8;
    if (kind == 1 || kind == 3 || kind == 5 || kind == 7 || kind == 9 || kind == 11) {
        if (kind >= 6 && kind <= 11)
            result = 1;
        if (!result) {
            int pending = fn_800F06F4(0, &p->mpState->mUnknown4, 26, 0xFFFF) != 0xFFFF;
            if (pending)
                result = 1;
        }
        if (!result && fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF) {
            if (p->mUnknown2913 == 1) {
                if (state->mUnknown7 == 3 || state->mUnknown7 == 4)
                    result = 1;
            } else if (state->mUnknown7 == 5 || state->mUnknown7 == 6) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" void fn_800EDB48(Object_80039F5C *p, Object_80039F5C *pOther, Object_80137ABC *pBall, State_800EDC68 *state) {
    if (pBall) {
        int mode = fn_800AD9B4();
        fn_80137A04(pBall, pOther);
        fn_80138398(pBall, 0);
        if (mode == 3) {
            switch (state->mUnknown8) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
            case 10:
            case 12:
            case 13:
            case 15: {
                Record_800B15FC *pRecord = fn_800B15FC();
                fn_8009BD2C(pOther, &pRecord->mUnknown0);
                pRecord->mUnknownC = pOther->mMotion.mPos.mX;
                pRecord->mUnknown10 = pOther->mMotion.mPos.mY;
                pRecord->mUnknown14 = 8;
                fn_800B1508();
                fn_80067E3C(30, &pOther->mMotion.mPos, pOther->mId, 1, 1, 0);
                break;
            }
            }
            fn_800B67FC(p, pOther);
        }
    }
}

extern "C" int fn_800EE61C(Object_80039F5C *p) {
    State_800EDC68 *state = (State_800EDC68 *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mUnknown0);
    if (fn_80137C48(p) == fn_801374BC())
        fn_80137C10(0);
    fn_80143EBC(p, pOther);
    if (pOther)
        fn_80143EBC(pOther, p);
    return 1;
}

extern "C" int fn_800EE7C8(Object_80039F5C *p) {
    return ((State_800EE7C8 *)&p->mUnknown336)->mUnknown4 == 1;
}

extern "C" int fn_800EE9AC(Object_80039F5C *p) {
    Point_8017886C point;
    int facing;
    fn_800EEE3C(&point, &facing, p, 0);
    State_800EE9AC *state = (State_800EE9AC *)&p->mUnknown336;
    fn_800EE964(state, p, &point, facing);
    state->mUnknown48 = 0;
    state->mUnknown49 = 0;
    state->mUnknown50 = 0;
    state->mUnknown52 = 0;
    return 0;
}

extern "C" int fn_800EEDC8(Object_80039F5C *p) {
    Point_8017886C point;
    int facing;
    fn_800EEE3C(&point, &facing, p, 0);
    State_800EE9AC *state = (State_800EE9AC *)&p->mUnknown336;
    fn_800EE964(state, p, &point, facing);
    state->mUnknown48 = 0;
    state->mUnknown49 = 0;
    state->mUnknown50 = 0;
    state->mUnknown52 = 0;
    return 0;
}

extern "C" int fn_800EF0DC(Object_80039F5C *p) {
    return fn_800EEA20(p);
}
