#include "game/Command_800CEE74.h"
#include "game/Block_801BE60C.h"
#include "game/Input_800B6D34.h"
#include "game/Level_80054130.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800EA284.h"
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
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"

/* Player block at +336 as used by the functions of the state entry at
   0x802DB370. */
struct State_800E9E18 {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    unsigned char mUnknown12;
    char mUnknown13[3];
    int mUnknown16;
    char mUnknown20[20];
    float mUnknown40;
};

/* Player block at +336 as used by fn_800E8BE8 and fn_800E8E04. */
struct State_800E8BE8 {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
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

struct State_800E4494 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    char mUnknown4[28];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[2];
    int mUnknown36;
    char mUnknown40[9];
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    char mUnknown52[2];
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    int mUnknown56;
    char mUnknown60[8];
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    unsigned char mUnknown77;
    unsigned char mUnknown78;
    char mUnknown79[1];
};

/* Bytes of the player block at +336 that fn_800E954C sets under states 32,
   17 and 16. */
struct State_800E954C {
    char mUnknown0[8];
    unsigned char mUnknown8;
    char mUnknown9[6];
    unsigned char mUnknown15;
    char mUnknown16[15];
    unsigned char mUnknown31;
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
extern float lbl_803EADAC;
extern float lbl_803EADB0;
extern float lbl_803EADB4;
extern float lbl_803EADB8;
extern float lbl_803EADBC;
extern float lbl_803EADC0;
extern float lbl_803EADE4;
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
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *e, float f);
float fn_80178A08(void);
float fn_80178A44(void);
float fn_80178A68(Point_8017886C *pPos);
int fn_80178348(void);
int fn_800A2178(void);
int fn_8009FE24(Object_80039F5C *p);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800E55B8(Object_80039F5C *p);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011E8A4(Object_80039F5C *p);
void fn_8011E8D8(Object_80039F5C *p);
Point_8017886C fn_80177FFC(int team);
Object_80039F5C *fn_8017876C(void);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
float fn_80237260(int stream);
int fn_8023790C(void);
int fn_800C4184(Object_80039F5C *p);
void fn_800D6CC0(Object_80039F5C *p);
void fn_800D6D50(void);
void fn_800D7A18(Object_80039F5C *p);
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
void fn_800DB688(void *pBlock, Object_80039F5C *p);
void fn_800DB7A4(void *pBlock, Object_80039F5C *p);
void fn_800DB8B4(void *pBlock, Object_80039F5C *p);
void fn_8009BD60(Object_80039F5C *p);
void fn_8017D9B0(int a, int b);
void fn_80178718(Object_80039F5C *p);
int fn_800EAC9C(Object_80039F5C *p);
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

extern "C" int fn_800E4494(Object_80039F5C *p) {
    State_800E4494 *state = (State_800E4494 *)&p->mUnknown336;
    p->mFlags &= ~4;
    fn_801C1F94(state, 0, sizeof(State_800E4494));
    state->mUnknown49 = state->mUnknown3 = state->mUnknown51 = state->mUnknown50 = 0;
    state->mUnknown36 = 0;
    state->mUnknown0 = 0;
    state->mUnknown76 = 0;
    state->mUnknown77 = 0;
    state->mUnknown56 = 0xC00000;
    fn_800E55B8(p);
    state->mUnknown1 = 0;
    state->mUnknown2 = 0;
    state->mUnknown54 = 0;
    state->mUnknown55 = 0;
    state->mUnknown32 = 0;
    state->mUnknown33 = 0;
    Object_800670B4 *pObject = fn_80168708(fn_80178308());
    switch (p->mUnknown2914) {
    case 17:
    case 18:
        if (pObject->mUnknown8.mUnknown4 == 11)
            state->mUnknown78 = 1;
        else
            state->mUnknown78 = 0;
        break;
    default:
        if (fn_8009FE24(p))
            state->mUnknown78 = 0;
        else
            state->mUnknown78 = 1;
        break;
    }
    fn_800A3B58(p, 2, 0);
    state->mUnknown68 = p->mMotion.mPos.mX;
    state->mUnknown72 = p->mMotion.mPos.mY;
    return 0;
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

extern "C" int fn_800E8BE8(Object_80039F5C *p) {
    State_800E8BE8 *state = (State_800E8BE8 *)&p->mUnknown336;
    float limit;
    int far;
    state->mUnknown0 = p->mpState->mUnknown1 << 16;
    if (p->mIdBytes[2] == fn_80178308())
        limit = 3.0f;
    else
        limit = 2.0f;
    unsigned int scale = p->mpState->mUnknown3[0];
    if (scale == 0)
        state->mUnknown4 = 1.0f;
    else
        state->mUnknown4 = scale * 0.1f;
    far = !(p->mpState->mUnknown2 != 0 && fn_80177F70() != 0 &&
            fabsf(fn_80177FFC(p->mIdBytes[2]).mY - p->mMotion.mPos.mY) <= limit &&
            fabsf(fn_80177FFC(p->mIdBytes[2]).mX - p->mMotion.mPos.mX) <= 6.0f);
    if (far)
        state->mUnknown9 = 1;
    else
        state->mUnknown9 = 0;
    if (fn_801CFFD0(p->mMotion.mFacing, state->mUnknown0) <= 0x71C70) {
        if (p->mFlags & 0x40000)
            return 1;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown0 = 0.0f;
        state->mUnknown8 = 0;
    } else {
        p->mUnknown512.mUnknown14 = state->mUnknown9 ? 6 : 7;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown0 = state->mUnknown4;
        p->mFlags &= ~4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 100, p, 1.0f);
        state->mUnknown8 = 1;
    }
    p->mFlags &= ~0x40000;
    return 0;
}

extern "C" int fn_800E8E04(Object_80039F5C *p) {
    State_800E8BE8 *state = (State_800E8BE8 *)&p->mUnknown336;
    p->mFlags &= ~0x40000;
    if (p->mFlags & 0x4000)
        return 1;
    if (state->mUnknown8) {
        if (p->mFlags & 4) {
            state->mUnknown8 = 0;
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown0 = 0.0f;
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        } else if (state->mUnknown9) {
            p->mUnknown512.mUnknown14 = 6;
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        } else {
            p->mUnknown512.mUnknown14 = 7;
            p->mUnknown512.mUnknown0 = 1.0f;
            p->mUnknown512.mUnknown8 = state->mUnknown0;
            p->mUnknown512.mUnknown4 = state->mUnknown0;
        }
    } else {
        if (p->mMotion.mFacing == state->mUnknown0)
            return 1;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown0 = 0.0f;
        p->mUnknown512.mUnknown8 = state->mUnknown0;
        p->mUnknown512.mUnknown4 = state->mUnknown0;
    }
    return 0;
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

extern "C" int fn_800E948C(Object_80039F5C *p) {
    if (p->mUnknown560.mFlags.mBytes[0]) {
        if (p->mContact560.mUnknown56.mZ >= 0.5f)
            return 1;
        return 3;
    }
    switch (fn_802372EC(0, 3)) {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 1;
    }
    return 2;
}

extern "C" void fn_800E9504(Object_80039F5C *p) {
    fn_800E9024(p, 10);
}

extern "C" void fn_800E9528(Object_80039F5C *p) {
    fn_800E9024(p, 58);
}

extern "C" void fn_800E954C(Object_80039F5C *p, int id, int *pAngle, int value, int *pHeading) {
    if (fn_800E93CC(p)) {
        int heading = p->mMotion.mUnknown32;
        Message_800F01CC message;
        int difference;
        fn_801C1F94(&message, 0, 4);
        message.mId = id;
        message.mUnknown1[1] = lbl_803EADA4[((((*pAngle - p->mMotion.mFacing) & 0xFFFFFF) + 0x100000) >> 21) & 7];
        if (pHeading) {
            heading = *pHeading;
            difference = fn_801CFFD0(p->mMotion.mFacing, heading);
        } else {
            heading = (heading - p->mMotion.mFacing) & 0xFFFFFF;
            difference = fn_801CFFD0(p->mMotion.mFacing, heading);
            if (fn_80137C48(p) && p->mUnknown776 == 1)
                heading = 0x1000000 - heading;
        }
        message.mUnknown1[0] = fn_800E9010(heading, difference);
        message.mUnknown1[0] |= lbl_803EAD9C[((heading + 0x100000) >> 21) & 7] << 4;
        message.mUnknown1[2] = value;
        switch (p->mpState->mId) {
        case 16:
            ((State_800E954C *)&p->mUnknown336)->mUnknown31 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 17:
            ((State_800E954C *)&p->mUnknown336)->mUnknown15 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 32:
            ((State_800E954C *)&p->mUnknown336)->mUnknown8 = 1;
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        case 34:
        case 35:
        case 36:
            fn_800F05E4(0, p->mpState, &message, p);
            break;
        default:
            fn_800F00D4(0, p->mpState, &message, p);
            break;
        }
    }
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

extern "C" void fn_800E99A8(Object_80039F5C *p, int kind) {
    if (fn_800E92DC(p) && !fn_801787A0()) {
        Message_800F01CC message;
        Object_800B26B0 *pMotion = &p->mMotion;
        float angle;
        unsigned char value;
        fn_801C1F94(&message, 0, 4);
        message.mId = 58;
        message.mUnknown1[1] = 8;
        if (kind == 4) {
            angle = fn_801CFFD0(pMotion->mFacing, p->mUnknown528.mUnknown4) * (360.0f / 16777216.0f);
            if (angle > 165.0f) {
                message.mUnknown1[0] = 1;
                message.mUnknown1[1] = 1;
            } else {
                value = p->mUnknown1008.mUnknown1;
                message.mUnknown1[0] = value;
                message.mUnknown1[1] = value;
            }
            message.mUnknown1[2] = kind << 4 | 3;
        } else if (kind == 3) {
            message.mUnknown1[2] = 51;
            value = p->mUnknown1008.mUnknown1;
            message.mUnknown1[0] = value;
            message.mUnknown1[1] = value;
        } else {
            angle = fn_801CFFD0(pMotion->mFacing, pMotion->mUnknown32) * (360.0f / 16777216.0f);
            float heading = fn_801CFFD0(pMotion->mUnknown32, p->mUnknown512.mUnknown4) * (360.0f / 16777216.0f);
            message.mUnknown1[0] = angle < 90.0f ? 1 : 9;
            message.mUnknown1[1] = heading < 90.0f ? 1 : 9;
            message.mUnknown1[2] = kind << 4 | 3;
        }
        fn_800F00D4(0, p->mpState, &message, p);
    }
}

extern "C" int fn_800E9B84(Object_80039F5C *p, int kind) {
    if (fn_800E92DC(p) && !fn_801787A0()) {
        Message_800F01CC message;
        Object_800B26B0 *pMotion = &p->mMotion;
        float angle;
        unsigned char value;
        fn_80067E3C(38, &pMotion->mPos, p->mId, 0, 0, 0);
        fn_800D6CC0(p);
        fn_801C1F94(&message, 0, 4);
        message.mId = 10;
        if (kind == 3) {
            value = p->mUnknown1008.mUnknown1;
            message.mUnknown1[1] = value;
            message.mUnknown1[0] = value;
            message.mUnknown1[2] = 51;
            fn_800F00D4(0, p->mpState, &message, p);
        } else if (kind == 4) {
            angle = fn_801CFFD0(pMotion->mFacing, p->mUnknown528.mUnknown4) * (360.0f / 16777216.0f);
            if (angle > 165.0f) {
                message.mUnknown1[0] = 1;
                message.mUnknown1[1] = 1;
            } else {
                value = p->mUnknown1008.mUnknown1;
                message.mUnknown1[1] = value;
                message.mUnknown1[0] = value;
            }
            message.mUnknown1[2] = kind << 4 | 3;
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            angle = fn_801CFFD0(pMotion->mFacing, pMotion->mUnknown32) * (360.0f / 16777216.0f);
            float heading = fn_801CFFD0(pMotion->mUnknown32, p->mUnknown512.mUnknown4) * (360.0f / 16777216.0f);
            message.mUnknown1[0] = angle < 90.0f ? 1 : 9;
            message.mUnknown1[1] = heading < 90.0f ? 1 : 9;
            message.mUnknown1[2] = kind << 4 | 3;
            fn_800F00D4(0, p->mpState, &message, p);
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_800E9DBC(Object_80039F5C *p, Object_80039F5C *pOther) {
    Point_8017886C delta;
    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    int direction = fn_801CFE40(delta.mY, delta.mX);
    fn_800EA284(p, (direction + 0x800000) & 0xFFFFFF, direction);
}

extern "C" int fn_800E9E18(Object_80039F5C *p) {
    State_800E9E18 *state = (State_800E9E18 *)&p->mUnknown336;
    state->mUnknown0 = p->mUnknown560.mUnknown54;
    p->mUnknown9[0] = 1;
    state->mUnknown4 = p->mUnknown560.mUnknown28;
    state->mUnknown12 = fn_80137C48(p) != 0;
    state->mUnknown16 = 0;
    fn_800DB520(state->mUnknown20, p, fn_8017876C(), state->mUnknown4);
    fn_8009BD60(p);
    State_80039F5C *pState = p->mpState;
    if ((pState->mUnknown3[0] >> 4) > 1) {
        p->mUnknown1008.mUnknown0 = pState->mUnknown1;
        p->mUnknown1008.mUnknown1 = pState->mUnknown2;
        p->mUnknown1008.mUnknown2 = pState->mUnknown3[0] >> 4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 165, p, 1.0f);
    } else {
        p->mUnknown1008.mUnknown2 = pState->mUnknown1 & 15;
        p->mUnknown1011 = pState->mUnknown1 >> 4;
        p->mUnknown1008.mUnknown1 = pState->mUnknown3[0] & 15;
        p->mUnknown1008.mUnknown0 = pState->mUnknown2;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 43, p, 1.0f);
    }
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 0;
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
    if (state->mUnknown20[0] == 1 || state->mUnknown20[1] == 1)
        fn_800D7A18(p);
    return 0;
}

extern "C" int fn_800E9FC0(Object_80039F5C *p) {
    p->mFlags &= ~0x4000000;
    return 0;
}

extern "C" int fn_800E9FD8(Object_80039F5C *p) {
    int result;
    fn_8010A2DC(p, 0, -1);
    State_800E9E18 *state = (State_800E9E18 *)&p->mUnknown336;
    fn_800DB688(state->mUnknown20, p);
    fn_800DB7A4(state->mUnknown20, p);
    result = 0;
    if (state->mUnknown12) {
        if (!fn_80137C48(p)) {
            p->mFlags |= 0x4000000;
            state->mUnknown12 = 0;
        } else if (p->mpState->mId == 10) {
            fn_800DB8B4(state->mUnknown20, p);
        }
    }
    if (p->mUnknown9[0] != 1) {
        p->mFlags &= ~0x80000;
        if (p->mUnknown9[0] != 8) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            p->mFlags &= ~0x4000000;
        }
        result = 1;
    } else if (p->mFlags & 4) {
        if (!fn_801787A0() && state->mUnknown20[1]) {
            unsigned int now = fn_8023790C();
            if (state->mUnknown40 > now) {
                now = fn_8023790C();
                state->mUnknown40 = now - 1.0f;
                fn_800DB7A4(state->mUnknown20, p);
            }
        }
        p->mFlags &= ~0x4080804;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.4f;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        result = 1;
    }
    if (result == 1)
        p->mFlags &= ~8;
    return result;
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

extern "C" int fn_800EA284(Object_80039F5C *p, int angle, int direction) {
    Object_80039F5C *pOther = 0;
    int *pRef = &p->mUnknown336;
    int blocked = 0;
    int otherDirection = 0;
    int result = 0;
    int other = 0;
    int otherAngle;
    int facing = fn_801CFFD0(p->mMotion.mUnknown32, direction) <= 0x31C71C;
    int near = facing;
    int busy;
    switch (p->mpState->mId) {
    case 16:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId != 17 || fn_8009BCE8(&pOther->mUnknown336) != p)
            pOther = 0;
        break;
    case 17:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId != 16 || fn_8009BCE8(&pOther->mUnknown336) != p)
            pOther = 0;
        break;
    case 32:
        pOther = fn_8009BCE8(pRef);
        other = pOther->mId;
        if (pOther->mpState->mId != 32 || fn_8009BCE8(&pOther->mUnknown336) != p)
            pOther = 0;
        break;
    }
    busy = 1;
    if (!fn_80114E7C(p))
        busy = 0;
    if (near) {
        Record_800EA284 *pRecord = p->mpUnknown3092->mpUnknown32;
        if (pRecord->mUnknown8 < 1.0f) {
            if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.65f)
                blocked = 1;
        } else {
            if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.0f)
                blocked = 1;
        }

        if (fn_80114E7C(p))
            blocked = 0;
        if (blocked || fn_800EAC9C(p) || (p->mFlags & 0x800) || (pOther && fn_800EAC9C(pOther))) {
            unsigned short animation = fn_801BE648(p->mpUnknown792);
            if (fn_800E8ED4(animation)) {
                Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, animation);
                if (pBlock->mUnknown1C)
                    pBlock->mUnknown1C = 0;
            }
        } else {
            switch (p->mpState->mId) {
            case 16:
                result = 1;
                fn_8017D9B0(p->mId, other);
                break;
            case 17:
                fn_8017D9B0(other, p->mId);
                break;
            }
            fn_800E954C(p, 10, &direction, 1, &angle);
            if (pOther && p == fn_80137B40() && !(p->mFlags & 0x10000)) {
                fn_80178718(pOther);
                p->mFlags = (p->mFlags | 0x10000) & ~0x80000;
            }
        }
        fn_80143EBC(p, pOther);
    }
    if (pOther && near) {
        if (!busy && fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) > lbl_803EADAC)
            facing = 0;
        if (facing) {
            Point_8017886C delta;
            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            blocked = 0;
            otherDirection = fn_801CFE40(delta.mY, delta.mX);
            otherAngle = (otherDirection + 0x800000) & 0xFFFFFF;
            Record_800EA284 *pRecord = pOther->mpUnknown3092->mpUnknown32;
            if (pRecord->mUnknown8 < 1.0f)
                blocked = pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.65f;
            else if (pRecord->mUnknown32.mZ - pRecord->mUnknown16.mZ < 0.0f)
                blocked = 1;
            if (fn_80114E7C(pOther))
                blocked = 0;
            if (blocked || fn_800EAC9C(pOther) || (pOther->mFlags & 0x800)) {
                unsigned short animation = fn_801BE648(pOther->mpUnknown792);
                if (fn_800E8ED4(animation)) {
                    Block_801BE60C *pBlock = fn_801BE60C(pOther->mpUnknown792, animation);
                    if (pBlock->mUnknown1C)
                        pBlock->mUnknown1C = 0;
                }
            } else {
                result = 1;
                fn_800E954C(pOther, 10, &otherAngle, 1, &otherDirection);
                if (pOther == fn_80137B40() && !(pOther->mFlags & 0x10000)) {
                    fn_80178718(p);
                    pOther->mFlags = (pOther->mFlags | 0x10000) & ~0x80000;
                }
            }
            fn_80143EBC(pOther, p);
        }
    }
    return result;
}

extern "C" void fn_800EA6F0(Object_80039F5C *p) {
    int nearX = 0;
    int nearY = 0;
    int index = 0;
    if (!fn_800C4184(p))
        return;
    if (fn_80054130()->mUnknown136) {
        if (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - lbl_803EADB0)
            nearX = 1;
        else if (fabsf(p->mMotion.mPos.mY) > fn_80178A44() - lbl_803EADB0)
            nearY = 1;
    }
    if (!nearX && !nearY)
        return;
    if (p->mMotion.mUnknown28 < lbl_803EADB4 * lbl_803ECB08)
        return;
    if (nearX) {
        if (p->mMotion.mPos.mX > 0.0f) {
            if (fn_801CFFD0(p->mMotion.mUnknown32, 0) > 0x2E38E3)
                return;
        } else {
            if (fn_801CFFD0(p->mMotion.mUnknown32, 0x800000) > 0x2E38E3)
                return;
        }
    } else if (nearY) {
        if (p->mMotion.mPos.mY > 0.0f) {
            if (fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) > 0x2E38E3)
                return;
        } else {
            if (fn_801CFFD0(p->mMotion.mUnknown32, 0xC00000) > 0x2E38E3)
                return;
        }
    }
    int flag = p->mUnknown776 == 1;
    Command_800CEE74 command;
    Message_800F01CC message;
    int id;
    int kind;
    float chance;
    fn_801C1F94(&message, 0, 4);
    if (fn_80137B40() == p) {
        chance = p->mRatings[0] / 510.0f + 0.5f;
        if (fn_80237260(0) < chance && !index) {
            id = 58;
            kind = 196;
        } else {
            id = 10;
            kind = 197;
        }
    } else {
        chance = p->mRatings[0] / 510.0f + 0.5f;
        if (fn_80237260(0) < chance && !index) {
            id = 58;
            kind = 210;
        } else {
            id = 10;
            kind = 195;
        }
    }
    message.mId = id;
    fn_800CEE74(&command, p, 0, 0, 0, kind, flag);
    p->mUnknown1008.mUnknown0 = 8;
    if (kind == 196) {
        if (nearX) {
            if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = !flag ? 3 : 6;
            else if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = !flag ? 6 : 3;
        } else if (nearY) {
            if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xE38E2 || fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = fn_80237260(0) >= 0.5f ? 3 : 6;
        }
    } else if (kind == 210) {
        if (nearX) {
            Vector_80039F5C pos;
            fn_80137D58(fn_801374BC(), &pos);
            int ahead = pos.mY > p->mMotion.mPos.mY;
            if (fn_801CFFD0(p->mMotion.mFacing, 0) <= 0xE38E2) {
                if (flag)
                    p->mUnknown1008.mUnknown0 = !ahead ? 3 : 6;
                else
                    p->mUnknown1008.mUnknown0 = !ahead ? 6 : 3;
            } else if (fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0xE38E2) {
                if (flag)
                    p->mUnknown1008.mUnknown0 = !ahead ? 6 : 3;
                else
                    p->mUnknown1008.mUnknown0 = !ahead ? 3 : 6;
            }
        } else if (nearY) {
            if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0xE38E2 || fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0xE38E2)
                p->mUnknown1008.mUnknown0 = fn_80237260(0) >= 0.5f ? 3 : 6;
        }
    }
    int value;
    index = fn_800C3BEC(p, &command, &value, 0);
    if (index == -1) {
        if (p != fn_80137B40()) {
            if (p->mUnknown1008.mUnknown0 == 3)
                p->mUnknown1008.mUnknown0 = 6;
            else if (p->mUnknown1008.mUnknown0 == 6)
                p->mUnknown1008.mUnknown0 = 3;
            fn_800CEE74(&command, p, 0, 0, 0, kind, flag);
            command.mUnknown62 = !command.mUnknown62;
            index = fn_800C3BEC(p, &command, &value, 0);
        }
        if (index == -1)
            return;
    }
    if (fn_80137B40() == p) {
        int previous = fn_800F06F4(0, p->mpState, 18, 0xFFFF);
        fn_800EFE60(0, p->mpState, p);
        fn_800F053C(0, p->mpState, &message, p);
        p->mFlags &= ~0x2000;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        fn_800D6D50();
        if (previous == 0xFFFF) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 18;
        }
        fn_800F03D8(0, p->mpState, &message, p);
    } else if (p->mpState->mId == 58) {
        fn_800F05E4(0, p->mpState, &message, p);
    } else {
        fn_800F00D4(0, p->mpState, &message, p);
    }
    p->mFlags |= 8;
    fn_800C39E0(p, kind, index, value, command.mUnknown62);
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

extern "C" int fn_800EAD44(Object_80039F5C *p, Object_80137ABC *pBall) {
    int result = 0;
    Vector_80039F5C pos;
    Point_8017886C delta;
    float distance;
    fn_80137D58(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > lbl_803EADC0) {
        Object_80039F5C *pOther = fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1),
                                              (int)(lbl_803EADB8 * 46603.37890625f), &distance, 1);
        if (pOther && distance < lbl_803EADBC)
            result = fn_8011EAC0(p, pOther);
        if (!fn_801486A0() && !result) {
            pOther = fn_801245DC(p, p->mIdBytes[2], 0, fn_80178D18(p->mIdBytes[2]),
                                 (int)(lbl_803EADB8 * 46603.37890625f), &distance, 1);
            if (pOther && distance < lbl_803EADBC)
                result = fn_8011EAC0(p, pOther);
        }
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

extern "C" int fn_800EAF34(Object_80039F5C *p, int a, int b, int c) {
    int result = 0xFFFF;
    if (fn_8011E8A4(p)) {
        fn_8011E8D8(p);
        p->mUnknown1008.mUnknown0 = a;
        p->mUnknown1008.mUnknown1 = b;
        p->mUnknown1008.mUnknown2 = c;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 48, p, 1.0f);
        result = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 48, 0);
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 0;
        if (((State_800EBCE0 *)&p->mUnknown336)->mUnknown45 == 5)
            p->mFlags |= 8;
        p->mUnknown9[0] = 1;
    }
    return result;
}

extern "C" int fn_800EAFFC(Object_80039F5C *p, Object_80137ABC *pBall) {
    return 1;
}

extern "C" int fn_800EB004(Object_80137ABC *pBall) {
    int result = 5;
    Vector_80039F5C pos;
    fn_80137D58(pBall, &pos);
    if (pos.mX > fn_80178A08() - 3.0f)
        result = 0;
    else if (pos.mX < 3.0f - fn_80178A08())
        result = 1;
    else if (pos.mY > fn_80178A44() - 3.0f)
        result = 2;
    else if (pos.mY < 3.0f - fn_80178A44())
        result = 3;
    return result;
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

extern "C" int fn_800EC76C(Object_80039F5C *p) {
    if (fn_80178A68((Point_8017886C *)&p->mMotion.mPos) < lbl_803EADE4)
        return 5;
    int mode = fn_800A2178();
    if (p->mIdBytes[2] == fn_80178348()) {
        switch (mode) {
        case 0:
        case 1:
        case 3:
        case 13:
            return 2;
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
        case 15:
        case 16:
        case 17:
            return 3;
        }
    } else {
        switch (mode) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 16:
            return 4;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 17:
            return 3;
        }
    }
    return 3;
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
            int pending = fn_800F06F4(0, &p->mpState[1], 26, 0xFFFF) != 0xFFFF;
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

extern "C" void fn_800EE694(Object_80039F5C *p) {
    if (p->mIdBytes[3] == 1)
        p->mIdBytes[3] = 2;
    else if (p->mIdBytes[3] == 2)
        p->mIdBytes[3] = 1;
    switch (p->mIdBytes[2]) {
    case 2:
        p->mIdBytes[2] = 4;
        break;
    case 4:
        p->mIdBytes[2] = 2;
        break;
    case 3:
        p->mIdBytes[2] = 5;
        break;
    case 5:
        p->mIdBytes[2] = 3;
        break;
    case 8:
        p->mIdBytes[2] = 10;
        break;
    case 10:
        p->mIdBytes[2] = 8;
        break;
    case 9:
        p->mIdBytes[2] = 11;
        break;
    case 11:
        p->mIdBytes[2] = 9;
        break;
    }
    Object_800670B4 *pObject = fn_80168708(fn_80178308());
    unsigned int count = fn_80178D18(fn_80178308());
    for (unsigned char i = 0; i < count; i++) {
        if (fn_80163E94(pObject, i, 0)->mUnknownB == p->mIdBytes[1]) {
            p->mIdBytes[1] = i;
            break;
        }
    }
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
