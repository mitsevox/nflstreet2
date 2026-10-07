#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/Message_800F01CC.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

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

struct Record_8011F518;

/* Bytes at +336 of the player object as fn_8010BA00, fn_8010B5B0 and
   fn_8010BC48 access them. Partial layout. */
struct State_8010BA00 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Record that fn_8010B738 reads through each table entry. Partial layout. */
struct Record_8010B738 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
};

struct Entry_8010B738 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Record_8010B738 *mpRecord;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_8010B738 {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_8010B738 mEntries[1];
};

/* Output of fn_801076F0. */
struct Result_801076F0 {
    Point_8017886C mUnknown0;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
};

/* Input of fn_801076F0. Partial layout. */
struct Input_801076F0 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[4];
    Point_8017886C mUnknown16;
};

extern "C" {
void fn_8003AB08(Object_80039F5C *p, int a);
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_800A2178(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
int fn_800B65A0(int team);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800D6914(int a, Object_80039F5C *p);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int a, int b);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_80106618(Object_80039F5C *p);
void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
void fn_8010CEB8(Object_80039F5C *p, int kind);
Record_8011F518 *fn_8011F518(void);
float fn_8012506C(Object_80039F5C *p, int kind);
int fn_801485D4(void);
int fn_801486A0(void);
int fn_80156704(void);
unsigned char fn_80156D14(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern float lbl_803EAEF4;
extern int lbl_803EAF10;
extern unsigned char lbl_802DAB60[];
extern unsigned char lbl_802DABBC[];

extern "C" void fn_80104C3C(Object_80039F5C *p, Vector_80039F5C *pOut, float scale) {
    Vector_80039F5C v;

    fn_80104B3C(p, &v);
    fn_80227264(pOut, &v, scale);
    fn_8022765C(pOut, pOut, &p->mMotion.mPos);
}

extern "C" int fn_8010531C(Object_80039F5C *p) {
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 12:
    case 16:
    case 17:
    case 28:
    case 32:
    case 51:
        return 0;
    }
    return 1;
}

extern "C" int fn_801064A4(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, 1, 0);

    if (pTarget == 0) {
        if (fn_801486A0() == 0) {
            fn_8013791C(fn_801374BC(), 3, 1);
        }
    } else if (fn_80105E90(p, pTarget, 11)) {
        Message_800F01CC message;

        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 25;
        fn_800D0BF4(p, a, 25);
        message.mUnknown1[0] = pTarget->mIdBytes[1];
        message.mUnknown1[1] = 11;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_8010CEB8(pTarget, 11);
    }
    return result;
}

extern "C" int fn_80106580(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, a, 0);

    if (pTarget != 0 && fn_80105E90(p, pTarget, 11) && fn_80106618(p)) {
        result = 1;
        fn_80106678(fn_8011F518(), pTarget, 6, 11);
        fn_8010CEB8(pTarget, 11);
        fn_800D6914(0, p);
    }
    return result;
}

extern "C" int fn_80106618(Object_80039F5C *p) {
    int *pValue;

    switch (p->mUnknown776) {
    case 1:
        pValue = &p->mUnknown108;
        break;
    case 2:
        pValue = &p->mUnknown200;
        break;
    default:
        pValue = 0;
        break;
    }
    if (pValue != 0) {
        return *pValue != 0 && *pValue != 4;
    }
    return 0;
}

extern "C" int fn_80106794(Object_80039F5C *p) {
    if (fn_80137C48(p) == fn_801374BC()) {
        fn_80137C10(0);
    }
    return 1;
}

extern "C" int fn_801067D8(Object_80039F5C *p) {
    return fn_8012506C(p, 6) < lbl_803EAEF4;
}

extern "C" void fn_801076F0(Object_80039F5C *pA, Object_80039F5C *pB, Result_801076F0 *pOut, Input_801076F0 *pIn) {
    Point_8017886C delta;

    fn_80227690(&pOut->mUnknown0, &pIn->mUnknown16, &pB->mMotion.mPos);
    pOut->mUnknown16 = fn_801CFE40(pOut->mUnknown0.mY, pOut->mUnknown0.mX);
    fn_80227690(&pOut->mUnknown8, &pA->mMotion.mPos, &pB->mMotion.mPos);
    pOut->mUnknown20 = fn_801CFE40(pOut->mUnknown8.mY, pOut->mUnknown8.mX);
    pOut->mUnknown32 = fn_802270A4(&pOut->mUnknown8);
    fn_80227690(&delta, &pIn->mUnknown4, &pB->mMotion.mPos);
    pOut->mUnknown24 = fn_801CFE40(delta.mY, delta.mX);
    pOut->mUnknown36 = fn_802270A4(&delta);
    fn_80227690(&delta, &pIn->mUnknown4, &pA->mMotion.mPos);
    pOut->mUnknown28 = fn_801CFE40(delta.mY, delta.mX);
    pOut->mUnknown40 = fn_802270A4(&delta);
}

extern "C" int fn_8010A07C(Object_80039F5C *p) {
    int result = 0;

    switch ((p->mUnknown388 >> 25) & 0xF) {
    case 1:
    case 2:
        result = 1;
        break;
    }
    return result;
}

extern "C" void fn_8010A1C4(int team) {
    int i;
    int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        fn_8003AB08(fn_80039F5C(team, i), 62);
    }
}

extern "C" void fn_8010A220(void) {
    fn_8010A1C4(fn_80178308());
    fn_8010A1C4(fn_80178320());
    lbl_803EAF10 = 0;
}

extern "C" int fn_8010A254(Object_80039F5C *p, int kind) {
    int result = 0;
    Message_800F01CC message;

    if (fn_80137C48(p) == 0 && (kind == 5 || kind == 9)) {
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 9;
        message.mUnknown1[2] = kind;
        fn_8003AB28(p, &message, 1);
    }
    return result;
}

extern "C" int fn_8010AEA0(Object_80039F5C *p) {
    fn_8009D1AC(p);
    return 1;
}

extern "C" void fn_8010AEC4(int value) {
    lbl_803EAF10 = value;
}

extern "C" int fn_8010B1B4(Object_80039F5C *p) {
    int state = fn_800AD9B4();

    if (p->mUnknown342 != 0 && state == 2) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8010B1FC(Object_80039F5C *p, int a, short b) {
    if (p->mpState->mId == 70 && (p->mFlags & 0x40000)) {
        p->mUnknown336 = a;
        p->mUnknown340 = b;
    }
}

extern "C" unsigned char fn_8010B3A0(Object_80039F5C *p, int kind) {
    unsigned char result = 0;
    unsigned char i;

    switch (kind) {
    case 5: {
        unsigned int count = fn_80178D18(0);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, fn_80039F5C(0, i));
            if (result) {
                break;
            }
        }
        count = fn_80178D18(1);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, fn_80039F5C(1, i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 4: {
        Object_80039F5C *pOther = fn_80137B40();

        if (pOther != 0) {
            result = fn_8010B87C(p, pOther);
        }
        break;
    }
    case 3: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, i);

            if (pOther->mFlags & 0x800) {
                result = fn_8010B87C(p, pOther);
            }
            if (result) {
                break;
            }
        }
        break;
    }
    case 1: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            result = fn_8010B87C(p, fn_80039F5C(p->mIdBytes[2], i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 2: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            result = fn_8010B87C(p, fn_80039F5C(p->mIdBytes[2] ^ 1, i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 6:
        result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" unsigned char fn_8010B5B0(Object_80039F5C *p, unsigned char *pOut) {
    int mode = fn_800A2178();
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;
    unsigned char count = 0;

    if (fn_80137B40() != p) {
        pOut[count++] = pState->mUnknown2;
        if ((p->mIdBytes[2] == fn_80178348() && mode == 0) ||
            (p->mIdBytes[2] == fn_80178360() && mode == 14)) {
            pOut[count++] = 5;
        }
        if (p->mIdBytes[2] == fn_80178360()) {
            switch (mode) {
            case 12:
                pOut[count++] = 6;
                pOut[count++] = 7;
                break;
            case 7:
            case 8:
                pOut[count++] = 7;
                break;
            }
        }
    } else if (!fn_80156704() || fn_801485D4()) {
        switch (mode) {
        case 0:
        case 1:
        case 14:
        case 15:
            pOut[count++] = 8;
            break;
        case 9:
            pOut[count++] = 8;
            break;
        default:
            pOut[count++] = 9;
            break;
        }
    } else if (fn_80156D14()) {
        pOut[count++] = 8;
    } else {
        pOut[count++] = 9;
    }
    return count;
}

extern "C" unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable) {
    unsigned char choices[100];
    unsigned char kinds[8];
    unsigned char n = 0;
    unsigned char result = 255;
    unsigned char count = fn_8010B5B0(p, kinds);
    unsigned char i;

    for (i = 0; i < pTable->mCount; i++) {
        Record_8010B738 *pRecord = pTable->mEntries[i].mpRecord;
        int found = 0;
        unsigned char j;

        for (j = 0; j < count; j++) {
            if (pRecord->mUnknown4 == kinds[j] && fn_8010B3A0(p, pRecord->mUnknown5)) {
                if ((pRecord->mUnknown6 == 1 && p->mUnknown776 == 2) ||
                    (pRecord->mUnknown6 == 2 && p->mUnknown776 == 1) || fn_80137B40() != p) {
                    if (lbl_802DABBC[i] == 0) {
                        found = 1;
                    }
                }
            }
        }
        if (found) {
            choices[n++] = i;
        }
    }
    if (n != 0) {
        result = choices[fn_802372EC(0, n)];
    }
    return result;
}

extern "C" int fn_8010B924(Object_80039F5C *p) {
    int kind;

    if (!fn_80156704() || fn_801485D4()) {
        int mode = fn_800A2178();
        int team = p->mIdBytes[2];

        kind = lbl_802DAB60[mode];
        if (team == fn_80178360()) {
            switch (kind) {
            case 4:
                kind = 1;
                break;
            case 2:
                kind = 3;
                break;
            case 1:
                kind = 4;
                break;
            case 3:
                kind = 2;
                break;
            }
        }
    } else if (fn_80156D14()) {
        kind = 1;
        if (fn_800B65A0(p->mIdBytes[2]) != 255) {
            kind = 4;
        }
    } else {
        kind = 3;
        if (fn_800B65A0(p->mIdBytes[2]) != 255) {
            kind = 2;
        }
    }
    return kind;
}

extern "C" int fn_8010BA00(Object_80039F5C *p) {
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;

    pState->mUnknown0 = 0;
    pState->mUnknown2 = fn_8010B924(p);
    pState->mUnknown3 = 255;
    if (fn_801BE648(p->mpUnknown792) == 48) {
        pState->mUnknown1 = 0;
    } else {
        pState->mUnknown1 = fn_802372EC(0, 15);
    }
    if (pState->mUnknown2 == 0 && fn_80137B40() != p) {
        pState->mUnknown0 = 1;
    }
    return 0;
}

extern "C" int fn_8010BC48(Object_80039F5C *p) {
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;

    if (pState->mUnknown3 != 255) {
        lbl_802DABBC[pState->mUnknown3] = 0;
    }
    fn_800A3B58(p, 2, 0);
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_80125508() {
    return 0;
}
