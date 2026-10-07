#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_80136B1C.h"
#include "game/cu_80067C10.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_80238174.h"

struct State_80111F80 {
    char mUnknown0[20];
    unsigned char mUnknown20;
};

struct State_80112E10 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
};

struct State_80113478 {
    int mUnknown0;
    int mUnknown4;
};

struct State_80113AAC {
    int mRef;
    char mUnknown4[10];
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    char mUnknown16[5];
    unsigned char mUnknown21;
};

struct State_801147D4 {
    char mUnknown0[31];
    unsigned char mUnknown31;
};

struct State_80114DF4 {
    int mRef;
    char mUnknown4[52];
    unsigned char mUnknown56;
};

struct Record_801170A0 {
    char mUnknown0[1];
    unsigned char mUnknown1;
};

struct Record_80118894 {
    char mUnknown0[64];
    float mUnknown64;
    char mUnknown68[8];
    float mUnknown76;
};

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Entry_8011AFCC {
    char mUnknown0[60];
    int mUnknown60;
    char mUnknown64[4];
    float mUnknown68;
    char mUnknown72[8];
};

extern "C" {
void fn_8009A8D4(void *p);
int fn_8009F7A4(Object_80039F5C *p, int *pOut);
int fn_8009EAB0(Object_80039F5C *p, unsigned char a);
int fn_8009EF6C(void *p);
int fn_80099AD0(Object_80039F5C *p, Object_80137ABC *pBall, int a, int b, int c, int d, int e);
int fn_80099C80(Object_80039F5C *p, Object_80137ABC *pBall, int a, int *pOut, int *pOut2);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, unsigned char index);
int fn_800B65A0(int a);
void fn_800B6714(Object_80039F5C *p, int port);
int fn_800C1180(Object_80039F5C *p);
float fn_800CA9B4(int kind, Object_80039F5C *p);
void fn_800CE674(Record_800CE674 *p);
void fn_800CE684(Record_800CE674 *p);
void fn_800D6EDC(void);
void fn_800D7A0C(Object_80039F5C *p, int a);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_800E98A4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
int fn_800F2C1C(Object_80039F5C *p, int a);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_80113088(Object_80039F5C *p);
int fn_80113604(Object_80039F5C *p);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair);
void fn_8011BAE0(Pair_8011BAE0 *pOut);
void fn_8011DBC0(Object_80039F5C *p);
void fn_8011DBC4(Object_80039F5C *p);
int fn_8011DC68(unsigned int id);
void fn_8011E1BC(Object_80039F5C *p, int a, int b, int c);
void fn_8011E240(Object_80039F5C *p);
int fn_8011E3F4(Object_80039F5C *p);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex);
void fn_8017D9B0(int a, int b);
int fn_80178308(void);
int fn_801BE648(void *p);
int fn_801CFFD0(int a, int b);
void *fn_8023816C(void *pHandle);

extern float lbl_803ECB08;
extern unsigned char *lbl_803EC9F0;
}

extern "C" int fn_800F08F8() {
    return 0;
}

extern "C" int fn_800F0900() {
    return 1;
}

extern "C" int fn_800F0908() {
    return 0;
}

extern "C" int fn_800F2C14() {
    return 0;
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_80111F80(Object_80039F5C *p)
{
    State_80111F80 *state = (State_80111F80 *)&p->mUnknown336;

    fn_8009A8D4(state);
    state->mUnknown20 = 0;
    return 0;
}

extern "C" int fn_80112E10(Object_80039F5C *p)
{
    State_80112E10 *state = (State_80112E10 *)&p->mUnknown336;

    if (p->mUnknown776 == 2) {
        state->mUnknown4 = 1;
    } else {
        state->mUnknown4 = 2;
    }
    state->mUnknown0 = 15;
    if (p->mUnknown528.mUnknown15 == 1) {
        state->mUnknown12 = 23;
    } else {
        state->mUnknown12 = 22;
    }
    state->mUnknown8 = p->mUnknown528.mUnknown0;
    state->mUnknown13 = 0;
    p->mUnknown512.mUnknown15 = state->mUnknown12;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = state->mUnknown8;
    return 0;
}

extern "C" int fn_80112E8C(Object_80039F5C *p)
{
    State_80112E10 *state = (State_80112E10 *)&p->mUnknown336;
    int result = 0;

    if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown15 = state->mUnknown12;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = state->mUnknown8;
    }
    if (--state->mUnknown0 <= 0) {
        switch (state->mUnknown13) {
        case 0:
            fn_800D7A0C(p, state->mUnknown4);
            if (state->mUnknown12 == 23) {
                state->mUnknown12 = 1;
            } else {
                state->mUnknown12 = 0;
            }
            state->mUnknown0 = 8;
            state->mUnknown13 = 1;
            break;
        case 1:
            p->mUnknown512.mUnknown14 = 1;
            result = 1;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            break;
        }
    } else if (state->mUnknown13 == 1) {
        fn_800D7A0C(p, state->mUnknown4);
    }
    return result;
}

extern "C" int fn_80113088(Object_80039F5C *p)
{
    int result = 0;
    int ballState = fn_8013BA58(fn_801374BC(), 0);
    int *pMode = &p->mUnknown1032;

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
    case 28:
    case 32:
    case 34:
    case 35:
    case 36:
    case 43:
    case 51:
    case 88:
        result = 0;
        break;
    default:
        if (*pMode == 0 || *pMode == 8) {
            if (ballState == 3 || ballState == 4) {
                result = 1;
            } else {
                Object_80039F5C *pCarrier = fn_80137B40();
                if (pCarrier != 0 && pCarrier->mpState->mId == 15) {
                    result = 1;
                }
            }
            if (result == 0 && fn_801486A0() == 1) {
                unsigned int count = fn_801383C8();
                unsigned int i;
                for (i = 1; i < count; i++) {
                    Object_80137ABC *pBall = fn_80137ABC(i);
                    int state = fn_8013BA58(pBall, 0);
                    Object_80039F5C *pOther;
                    if (state == 3 || state == 4) {
                        result = 1;
                        break;
                    }
                    pOther = fn_80137AD0(pBall);
                    if (pOther != 0 && pOther->mpState->mId == 15) {
                        result = 1;
                        break;
                    }
                }
            }
        }
        break;
    }
    return result;
}

extern "C" int fn_80113208(Object_80039F5C *p, int a, int mode, int c)
{
    int result = 0;
    unsigned char index;
    int value = -1;
    int extra = 0;
    int flag = 0;
    Object_80137ABC *pBall;
    int target;

    index = 0;
    if (mode == 1 || mode == 3) {
        flag = 1;
    }
    if (fn_801486A0() == 1 && fn_801520C4(p, &index) != 0) {
        pBall = fn_80137ABC(index);
    } else {
        pBall = fn_801374BC();
        index = fn_801374E0(pBall);
    }
    if (p->mpState->mUnknown2 != 0) {
        target = fn_80099AD0(p, pBall, 3, 3, mode, a, c);
    } else if (mode == 3) {
        if (c != 0) {
            target = fn_80099C80(p, pBall, 0, &value, &extra);
        } else {
            target = fn_80099C80(p, pBall, a, &value, &extra);
        }
    } else {
        target = fn_80099AD0(p, pBall, 0, 2, mode, a, c);
    }
    if (target != 0x1FFFFFFF && (value != -1 || mode != 3)) {
        if (mode == 3) {
            if (fn_8009A1A8(p, target, value, extra, index) == 1) {
                result = 1;
            }
        } else if (fn_80099F04(p, target, index) == 1) {
            result = 1;
        }
    } else if (a != 0) {
        if (mode == 3) {
            result = fn_80113208(p, a, 1, c);
        } else if (p->mpState->mUnknown2 != 0) {
            fn_800E815C(p, 0, 0);
            result = 1;
        } else {
            fn_800F2C1C(p, flag);
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_801133FC(Object_80039F5C *p, int a, int b)
{
    int result = 0;

    if (fn_80113088(p) != 0) {
        Message_800F01CC message;
        result = 1;
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 88;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80113478(Object_80039F5C *p)
{
    State_80113478 *state = (State_80113478 *)&p->mUnknown336;

    state->mUnknown0 = 0;
    state->mUnknown4 = p->mpState->mUnknown1;
    return 0;
}

extern "C" int fn_801135E4(Object_80039F5C *p)
{
    return fn_80113604(p);
}

extern "C" int fn_80113604(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;
    Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], pState->mUnknown1);
    unsigned int bit = 1 << pState->mUnknown2;

    if ((pOther->mFlags & bit) == bit) {
        return 1;
    }
    if (pState->mUnknown3[0] != 0) {
        fn_8010A2DC(p, 0, -1);
    }
    return 0;
}

extern "C" int fn_80113AAC(Object_80039F5C *p)
{
    State_80113AAC *state = (State_80113AAC *)&p->mUnknown336;

    if (state->mUnknown21 != 0 || state->mUnknown15 != 0) {
        state->mUnknown15 = 0;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        p->mUnknown1218 = 0;
        return 1;
    }
    return 0;
}

extern "C" int fn_80113BCC(Object_80039F5C *p)
{
    int result = 0;

    if (p->mpState->mId == 17 && fn_80114E7C(p) != 0) {
        result = 1;
    }
    return result;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_801147D4(Object_80039F5C *p)
{
    State_801147D4 *state = (State_801147D4 *)&p->mUnknown336;

    if (state->mUnknown31 != 0) {
        p->mFlags &= ~0x2000;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        return 1;
    }
    return 0;
}

extern "C" int fn_80114D14(int a, unsigned int b, int c, unsigned int d)
{
    int result = a - c;

    if (b > d) {
        if ((int)(b - d) > 100) {
            result++;
        }
    } else if (d > b) {
        if ((int)(d - b) > 100) {
            result--;
        }
    }
    return result;
}

extern "C" void fn_80114D50(Object_80039F5C *p, Object_80039F5C *pOther)
{
    p->mUnknown392 = 4;
    ((State_80113AAC *)&pOther->mUnknown336)->mUnknown14 = 4;
    fn_800D6EDC();
    fn_80067DB8(101, &p->mMotion.mPos, p->mId, pOther->mId, 0);
    if (!(pOther->mFlags & 0x400) && fn_801486A0() != 0) {
        int port = fn_800B65A0(pOther->mIdBytes[2]);
        if (port != 255) {
            fn_800B6714(pOther, port);
        }
    }
}

extern "C" unsigned char fn_80114DD8(Object_80039F5C *p)
{
    return p->mUnknown402;
}

extern "C" int fn_80114DE0(Object_80039F5C *p)
{
    return p->mUnknown392 == 1;
}

extern "C" void fn_80114DF4(Object_80039F5C *p)
{
    State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
    unsigned char kind = state->mUnknown56;

    if (kind == 1) {
        Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);
        ((State_80113AAC *)&pOther->mUnknown336)->mUnknown15 = kind;
        pOther->mpState->mUnknown3[0] = 255;
        fn_800E98A4(pOther, p);
        fn_80143EBC(p, pOther);
        fn_80067DB8(102, &p->mMotion.mPos, 0, 0, 0);
        fn_8017D9B0(p->mId, pOther->mId);
    }
}

extern "C" Object_80039F5C *fn_80114E7C(Object_80039F5C *p)
{
    Object_80039F5C *result = 0;
    unsigned char id = p->mpState->mId;

    if (id == 16) {
        State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
        if (state->mUnknown56 == 1 || state->mUnknown56 == 4) {
            result = fn_8009BCE8(&state->mRef);
        }
    } else if (id == 17) {
        State_80113AAC *state = (State_80113AAC *)&p->mUnknown336;
        if (state->mUnknown14 == 1 || state->mUnknown14 == 4) {
            result = fn_8009BCE8(&state->mRef);
        }
    }
    return result;
}

extern "C" int fn_801163B4(Object_80039F5C *p)
{
    int value = 0;
    int result = 0;

    switch (p->mUnknown2914) {
    case 17:
    case 18:
        if (fn_8009F7A4(p, &value) != 0) {
            result = 1;
        }
        break;
    }
    return result;
}

extern "C" int fn_801167C4(void *pTarget, Object_80039F5C *p)
{
    int found = 0;

    if (pTarget != 0) {
        unsigned int i = 0;
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (; i < count && found == 0; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
            if (pOther != p) {
                unsigned char id = pOther->mpState->mId;
                if (id == 40 || id == 92) {
                    fn_8009EAB0(pOther, fn_800C1180(pOther));
                    if (fn_8009EF6C(pTarget) != 0) {
                        found = 1;
                    }
                }
            }
        }
    }
    return found;
}

extern "C" void fn_80116880(Object_80039F5C *p, Object_80039F5C *pOther, float *pValue, float *pOut, float range)
{
    int pending = 1;

    if (p != 0 && pValue != 0 && pOut != 0 && pOther != 0) {
        if (fabsf(p->mMotion.mPos.mX - *pValue) < range) {
            int limit = 0x2AAAA9;
            fn_801CFFD0(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);
            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) <= limit) {
                pending = 0;
                *pOut = *pValue + range;
            } else if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x800000) <= limit) {
                pending = 0;
                *pOut = *pValue - range;
            }
        }
        if (pending != 0) {
            if (p->mMotion.mPos.mX > *pValue) {
                *pOut = *pValue + range;
            } else {
                *pOut = *pValue - range;
            }
        }
    }
}

extern "C" int fn_80116AB8(Object_80039F5C *p)
{
    int result = 1;

    if (p != 0) {
        int eligible;
        switch (p->mpState->mUnknown1) {
        case 0:
        case 4:
            eligible = 1;
            break;
        case 1:
        case 2:
        case 3:
            eligible = 0;
            break;
        case 9:
            eligible = 0;
            break;
        default:
            eligible = 0;
            break;
        }
        if (eligible) {
            unsigned int i = 0;
            unsigned int count = fn_80178D18(p->mIdBytes[2]);
            for (; i < count && result != 0; i++) {
                Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
                if (pOther != p && pOther->mpState->mId == 40) {
                    result = 0;
                }
            }
        } else {
            result = 0;
        }
    }
    return result;
}

extern "C" void fn_801170A0(Record_801170A0 *p)
{
    unsigned char value = p->mUnknown1;

    if (value >= 1 && value <= 2) {
        value = 3 - value;
    } else if (value >= 3 && value <= 5) {
        value = 8 - value;
    } else if (value >= 6 && value <= 9) {
        value = 15 - value;
    }
    p->mUnknown1 = value;
}

extern "C" void fn_80118704(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EC9F0, 4, 0, 0x7A736674);
    unsigned char *pData = (unsigned char *)fn_8023816C(pHandle);

    *pData = 0;
    fn_802381E0(pHandle);
}

extern "C" void fn_8011875C(void)
{
    *lbl_803EC9F0 = 0;
}

extern "C" void fn_8011876C(void)
{
    lbl_803EC9F0 = 0;
}

extern "C" void fn_80118778(Record_801170A0 *p)
{
    unsigned char value = p->mUnknown1 + 14;

    if (value >= 15 && value <= 16) {
        value = 31 - value;
    } else if (value >= 17 && value <= 19) {
        value = 36 - value;
    } else if (value >= 20 && value <= 23) {
        value = 43 - value;
    }
    p->mUnknown1 = value - 14;
}

extern "C" void fn_80118894(Record_80118894 *pA, Record_80118894 *pB, int a, int b, Object_80039F5C *pPlayerA, Object_80039F5C *pPlayerB)
{
    if (a != 0) {
        pA->mUnknown64 *= fn_800CA9B4(9, pPlayerA);
        pA->mUnknown76 *= fn_800CA9B4(9, pPlayerA);
    }
    if (b != 0) {
        pB->mUnknown64 *= fn_800CA9B4(9, pPlayerB);
        pB->mUnknown76 *= fn_800CA9B4(9, pPlayerB);
    }
}

extern "C" void fn_8011893C(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    unsigned int count = fn_80178D70(team);

    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        int *pRef = &p->mUnknown1036;
        Object_80039F5C *pOther;
        unsigned short value;
        int mode;
        int otherMode;

        if (p->mUnknown1032 == 7) {
            pRef = &p->mUnknown1040;
        }
        pOther = fn_8009BCE8(pRef);
        if (fn_8011E3F4(p) != 0) {
            value = 0;
            switch (p->mUnknown1032) {
            case 2:
            case 3:
            case 4:
                mode = 4;
                otherMode = 4;
                value = 20 - (p->mRatings[7] >> 4);
                fn_8011DBC4(p);
                break;
            default:
                mode = p->mUnknown1032;
                otherMode = pOther != 0 ? pOther->mUnknown1032 : 0;
                break;
            }
        } else {
            value = 0;
            fn_8011DBC0(p);
            switch (p->mUnknown1032) {
            case 4:
                fn_80143EBC(p, pOther);
                mode = 2;
                otherMode = 8;
                fn_80143EBC(pOther, p);
                break;
            case 3:
                if (pOther != 0) {
                    mode = 1;
                    if (fn_801CFFD0(p->mMotion.mFacing, pOther->mMotion.mFacing) > 0x471C71) {
                        mode = p->mUnknown1032;
                    }
                    otherMode = pOther->mUnknown1032;
                } else {
                    otherMode = 0;
                    mode = 3;
                }
                break;
            default:
                mode = p->mUnknown1032;
                otherMode = pOther != 0 ? pOther->mUnknown1032 : 0;
                break;
            }
        }
        if (p->mUnknown1032 != mode) {
            p->mUnknown1134 = value;
            p->mUnknown1032 = mode;
            p->mUnknown1136 = 0;
            p->mUnknown1137 = 0;
            switch (mode) {
            case 4:
                p->mUnknown1126 = 1;
                if (fn_8011DC68(fn_801BE648(p->mpUnknown792)) != 0) {
                    p->mUnknown1064 = fn_801BE648(p->mpUnknown792);
                } else {
                    p->mUnknown1064 = -1;
                }
                break;
            case 1:
                pOther = 0;
                fn_8011E240(p);
                fn_8011E1BC(p, 0, 0, 1);
                break;
            }
        }
        if (pOther != 0 && pOther->mUnknown1032 != otherMode) {
            pOther->mUnknown1032 = otherMode;
            pOther->mUnknown1137 = 0;
            pOther->mUnknown1134 = 0;
            pOther->mUnknown1136 = 0;
        }
    }
}
extern "C" void fn_80119478(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    Pair_8011BAE0 pair;
    unsigned int count;

    fn_8011BAE0(&pair);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        fn_80118B4C(fn_80039F5C(team, i), &pair);
    }
}

extern "C" void fn_8011AFCC(Entry_8011AFCC *pEntries)
{
    int swapped;

    do {
        Entry_8011AFCC *pPrev = pEntries;
        Entry_8011AFCC *pEntry;

        swapped = 0;
        for (pEntry = pEntries + 1; pEntry->mUnknown60 != 0; pEntry++) {
            if (pEntry->mUnknown68 < pPrev->mUnknown68) {
                Entry_8011AFCC temp = *pEntry;
                *pEntry = *pPrev;
                *pPrev = temp;
                swapped = 1;
            }
            pPrev = pEntry;
        }
    } while (swapped);
}

extern "C" void fn_8011B138(Entry_8011AFCC *pEntries)
{
    int swapped;

    do {
        Entry_8011AFCC *pPrev = pEntries;
        Entry_8011AFCC *pEntry;

        swapped = 0;
        for (pEntry = pEntries + 1; pEntry->mUnknown60 != 0; pEntry++) {
            if (pEntry->mUnknown68 > pPrev->mUnknown68) {
                Entry_8011AFCC temp = *pEntry;
                *pEntry = *pPrev;
                *pPrev = temp;
                swapped = 1;
            }
            pPrev = pEntry;
        }
    } while (swapped);
}

extern "C" int fn_80125508() {
    return 0;
}
