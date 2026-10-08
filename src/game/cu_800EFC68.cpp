#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/cu_80067C10.h"
#include "game/fn_80238174.h"
#include "game/fn_802270D4.h"

/* Record whose address fn_8011F4E0 returns. Only the accessed fields are
   declared; the size is unknown. */
struct Record_8011F4E0 {
    char mUnknown0[2];
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8[4];
    unsigned char mUnknown12[4];
    unsigned char mUnknown16[7];
    char mUnknown23[1];
    unsigned char mUnknown24[8];
    unsigned char mUnknown32[7];
    char mUnknown39[1];
    unsigned char mUnknown40[8];
};

/* Views of the block at player +336. Only the accessed fields
   are declared. */
struct Block_800FBAA8 {
    char mUnknown0[36];
    int mUnknown36;
};

struct Block_800FCC24 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[9];
    unsigned char mUnknown33;
    char mUnknown34[3];
    unsigned char mUnknown37;
};

struct Block_800FD650 {
    float mUnknown0;
    float mUnknown4;
    char mUnknown8[8];
    unsigned int mUnknown16;
};

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



extern float lbl_803EAEF4;
extern int lbl_803EAF10;
extern unsigned char lbl_802DAB60[];
extern unsigned char lbl_802DABBC[];

extern "C" {
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
int fn_800B65A0(int unknown);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800E9528(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8010D508(Object_80039F5C *p);
int fn_801101DC(Object_80039F5C *p);
int fn_801102A4(Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, int a, unsigned char count, float *pOut, int b);
float fn_801250B8(Object_80039F5C *p, int a, int b);
int fn_80178308(void);
int fn_80178320(void);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803EAF58;
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
int fn_8009FE24(Object_80039F5C *p);
int fn_800F5AD4(Object_80039F5C *p);
void fn_800F6AD8(float *p);
Point_8017886C fn_800F97A8(Object_80039F5C *p);
void fn_800FBB70(void);
unsigned char fn_800FC014(Object_80039F5C *p, Object_80039F5C *pOther);
unsigned char fn_800FC0C4(Object_80039F5C *p);
int fn_800FC4A8(Object_80039F5C *p, Block_800FCC24 *pBlock, int a);
int fn_800FC7A0(Object_80039F5C *p, Block_800FCC24 *pBlock);
void fn_800FD724(Object_80039F5C *p);
int fn_8011F1CC(void);
Record_8011F4E0 *fn_8011F4E0(void);
void fn_8016DF34(Object_80039F5C *p);
int fn_801783AC(int bit);
void fn_8009A8D4(void *p);
int fn_8009EAB0(Object_80039F5C *p, unsigned char a);
int fn_8009EF6C(void *p);
int fn_80099AD0(Object_80039F5C *p, Object_80137ABC *pBall, int a, int b, int c, int d, int e);
int fn_80099C80(Object_80039F5C *p, Object_80137ABC *pBall, int a, int *pOut, int *pOut2);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, unsigned char index);
int fn_800C1180(Object_80039F5C *p);
float fn_800CA9B4(int kind, Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
void fn_800D6EDC(void);
void fn_800D7A0C(Object_80039F5C *p, int a);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_800E98A4(Object_80039F5C *p, Object_80039F5C *pOther);
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
int fn_8011E3F4(Object_80039F5C *p);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex);
void fn_8017D9B0(int a, int b);
void *fn_8023816C(void *pHandle);
extern float lbl_803ECB08;
extern unsigned char *lbl_803EC9F0;
void fn_8003AB08(Object_80039F5C *p, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_800A2178(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800D6914(int a, Object_80039F5C *p);
void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int a, int b);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_80106618(Object_80039F5C *p);
void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
void fn_8010CEB8(Object_80039F5C *p, int kind);
Record_8011F518 *fn_8011F518(void);
float fn_8012506C(Object_80039F5C *p, int kind);
int fn_801485D4(void);
int fn_80156704(void);
unsigned char fn_80156D14(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther);
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

extern "C" int fn_800F62A4(Object_80039F5C *p) {
    Message_800F01CC message;

    if (fn_800F5AD4(p)) {
        fn_801C1F94(&message, 0, 4);
        if (fn_8011F1CC() && !fn_801783AC(0)) {
            message.mId = 31;
        } else {
            message.mId = 33;
        }
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    } else {
        fn_801C1F94(&message, 0, 4);
        message.mId = 47;
        message.mUnknown1[1] = p->mpState->mUnknown2;
        message.mUnknown1[0] = p->mpState->mUnknown1;
        message.mUnknown1[2] = p->mpState->mUnknown3[0];
        fn_800F053C(0, p->mpState, &message, p);
    }
    return 0;
}

extern "C" int fn_800F6790(Object_80039F5C *p) {
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" void fn_800F67CC(unsigned char *p) {
    p[2] = ((0x800000 - (p[2] << 17)) >> 17) & 0x7F;
}

extern "C" unsigned int fn_800F67E8(Object_80039F5C *pTarget) {
    unsigned int count = 0;

    if (pTarget) {
        unsigned int i = 0;
        unsigned int n = fn_80178D18(fn_80178320());
        for (; i < n; i++) {
            Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
            if (p->mpState->mId == 22) {
                Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown336);
                if (pOther && pOther == pTarget) {
                    count++;
                }
            }
        }
    }
    return count;
}

extern "C" void fn_800F722C(Object_80039F5C *p, Object_80039F5C *pOther, float *pX, float *pOut) {
    if (p && pOther && pOut) {
        Vector_80039F5C pos;
        int side;
        int flag;
        float distance;

        fn_80137D58(fn_801374BC(), &pos);
        side = (p->mpState->mUnknown2 ^ 1) & 1;
        if (*pX > pos.mX ? side == 0 : side != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        distance = fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX);
        if (flag) {
            if (*pX > p->mMotion.mPos.mX) {
                *pOut = distance;
            } else {
                *pOut = -distance;
            }
        } else {
            if (*pX > p->mMotion.mPos.mX) {
                *pOut = distance;
            } else {
                *pOut = -distance;
            }
        }
        fn_800F6AD8(pOut);
    }
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" Object_80039F5C *fn_800F93D0(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i;

    for (i = 0; i < 7; i++) {
        if (pRecord->mUnknown16[i] == p->mIdBytes[1]) {
            pResult = fn_80039F5C(fn_80178320(), i);
            break;
        }
    }
    return pResult;
}

extern "C" void fn_800F9440(Object_80039F5C *p, Object_80039F5C *pOther) {
    fn_8011F4E0()->mUnknown16[p->mIdBytes[1]] = pOther->mIdBytes[1];
}

extern "C" Object_80039F5C *fn_800F9AF0(unsigned char slot) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    unsigned char index = pRecord->mUnknown8[slot];
    Object_80039F5C *p = fn_80039F5C(fn_80178308(), index);

    do {
        if (pRecord->mUnknown32[i] == fn_800FC0C4(p)) {
            unsigned char j;
            for (j = 0; j < 8; j++) {
                if (pRecord->mUnknown24[j] == ((p->mId >> 16) & 0xFF) && pRecord->mUnknown40[j] == i) {
                    break;
                }
            }
            if (j == 8) {
                p = 0;
                break;
            }
        }
        i++;
    } while (i < 7);
    return p;
}

extern "C" Object_80039F5C *fn_800F9BD8(int forward, Object_80039F5C *p) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Object_80039F5C *pResult = 0;
    unsigned char id = 0;
    int found = 0;
    unsigned char i;

    if (!p) {
        found = 1;
    } else {
        id = p->mIdBytes[1];
    }
    for (i = 0; i < 3; i++) {
        unsigned char slot = !forward ? 2 - i : i;
        if (found) {
            Object_80039F5C *pSlot = fn_800F9AF0(slot);
            if (pSlot) {
                pResult = pSlot;
                break;
            }
        } else if (fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot])->mIdBytes[1] == id) {
            found = 1;
        }
    }
    return pResult;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" void fn_800FA014(Object_80039F5C *p, int *pRef) {
    Object_80039F5C *pOther = 0;

    if (p->mUnknown2914 == 16) {
        Object_80039F5C *pCurrent = fn_8009BCE8(pRef);
        if (!pCurrent || fn_800FC0C4(pCurrent) != p->mpState->mUnknown1) {
            if (fn_8009F7A4(p, &pOther)) {
                fn_8009BD2C(pOther, pRef);
            }
        }
    }
}

extern "C" void fn_800FAD10(unsigned char *p) {
    unsigned char value = p[1];
    if (value != 0) {
        value = 6 - value;
    }
    p[1] = value;
}

extern "C" void fn_800FB768(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();

    if (!(pRecord->mUnknown2 & 0x8000)) {
        pRecord->mUnknown2--;
        if (pRecord->mUnknown2 & 0x8000) {

            int team = fn_80178308();
            int swapped;
            do {
                unsigned char i;
                swapped = 0;
                for (i = 0; i < 2; i++) {

                    Object_80039F5C *pA = fn_80039F5C(team, pRecord->mUnknown12[i]);
                    Object_80039F5C *pB = fn_80039F5C(team, pRecord->mUnknown12[i + 1]);
                    if (pA->mMotion.mPos.mX < pB->mMotion.mPos.mX) {
                        unsigned char t = pRecord->mUnknown12[i];
                        pRecord->mUnknown12[i] = pRecord->mUnknown12[i + 1];
                        pRecord->mUnknown12[i + 1] = t;
                        swapped = 1;
                    }
                }
            } while (swapped == 1);
        }
    }
}

extern "C" void fn_800FB824(Object_80039F5C *p, Object_80039F5C *pOther) {
    fn_800F9440(p, pOther);
}

extern "C" Object_80039F5C *fn_800FB844(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();

    if (fn_8009FE24(p)) {
        Point_8017886C pos;
        unsigned char ahead;
        unsigned char behind;
        signed char i;
        int n;

        if (pRecord->mUnknown5 == 0) {
            fn_800FBB70();
        }
        pos = fn_800F97A8(p);
        ahead = 1;
        behind = 1;
        n = fn_80178D18(fn_80178320());
        for (i = 0; i < n; i++) {
            Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
            if (pOther != p && fn_8009FE24(pOther)) {
                Point_8017886C otherPos = fn_800F97A8(pOther);
                if (otherPos.mX > pos.mX) {
                    ahead++;
                } else {
                    behind++;
                }
            }
        }
        if (ahead < behind) {
            for (i = 0; i < 8; i++) {
                if (pRecord->mUnknown24[i] != 255) {
                    ahead--;
                }
                if (ahead == 0) {
                    pResult = fn_80039F5C(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        } else {
            for (i = 7; i >= 0; i--) {
                if (pRecord->mUnknown24[i] != 255) {
                    behind--;
                }
                if (behind == 0) {
                    pResult = fn_80039F5C(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        }
    }
    return pResult;
}

extern "C" void fn_800FBAA8(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i;
    unsigned int n;

    for (i = 0; i < 7; i++) {
        pRecord->mUnknown16[i] = 255;
    }
    for (i = 0; i < 7; i++) {
        pRecord->mUnknown32[i] = 255;
    }
    pRecord->mUnknown4 = 0;
    pRecord->mUnknown5 = 0;
    pRecord->mUnknown6 = 0;
    n = fn_80178D18(fn_80178320());
    for (i = 0; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
        if (p->mpState->mId == 42) {
            Block_800FBAA8 *pBlock = (Block_800FBAA8 *)&p->mUnknown336;
            pBlock->mUnknown36 = 0;
        }
    }
}

extern "C" Object_80039F5C *fn_800FBF74(Object_80039F5C *pTarget, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Object_80039F5C *pResult = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
        unsigned short slot = fn_800FC014(p, pOther) - 1;
        if (slot <= 4 && fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot]) == pTarget) {
            pResult = p;
            break;
        }
    }
    return pResult;
}

extern "C" unsigned char fn_800FC014(Object_80039F5C *p, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char value;

    if (pRecord->mUnknown4) {
        value = pRecord->mUnknown32[p->mIdBytes[1]];
        if (value == 255) {
            value = 253;
        }
    } else {
        value = pOther->mIdBytes[1];
    }
    return value;
}

extern "C" Object_80039F5C *fn_800FC070(Object_80039F5C *p, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char slot = fn_800FC014(p, pOther);
    return fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot - 1]);
}

extern "C" unsigned char fn_800FC0C4(Object_80039F5C *p) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char id = p->mIdBytes[1];
    unsigned char i;

    for (i = 1; i < 4; i++) {
        if (pRecord->mUnknown8[i - 1] == id) {
            break;
        }
    }
    return i;
}

extern "C" unsigned char fn_800FC128(Object_80039F5C *p) {
    unsigned char count = 0;
    unsigned char i = 0;
    unsigned int n = fn_80178D18(fn_80178320());

    for (; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
        if (fn_800F06F4(0, pOther->mpState, 22, 0xFFFF) != 0xFFFF && pOther != p
            && pOther->mMotion.mPos.mX > p->mMotion.mPos.mX) {
            count++;
        }
    }
    return count;
}

extern "C" unsigned char fn_800FC1DC(Object_80039F5C *p) {
    unsigned char count = 0;
    unsigned char i = 0;
    unsigned int n = fn_80178D18(fn_80178320());

    for (; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
        if (fn_800F06F4(0, pOther->mpState, 22, 0xFFFF) != 0xFFFF && pOther != p
            && pOther->mMotion.mPos.mX < p->mMotion.mPos.mX) {
            count++;
        }
    }
    return count;
}

extern "C" int fn_800FCC24(Object_80039F5C *p) {
    int result = 0;
    Block_800FCC24 *pBlock = (Block_800FCC24 *)&p->mUnknown336;
    unsigned int flags = p->mFlags;
    unsigned int state = pBlock->mUnknown0;
    Message_800F01CC message;

    p->mFlags = flags & ~0x40000;
    switch (state) {
    case 0:
        if (flags & 4) {
            p->mFlags &= ~4;
            pBlock->mUnknown0 = pBlock->mUnknown37;
        }
        if (pBlock->mUnknown0 == 2) {
            fn_800FC7A0(p, pBlock);
        }
        break;
    case 1:
        if (fn_800FC4A8(p, pBlock, 0)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = 2;
            p->mUnknown512.mUnknown14 = 0;
        } else {
            pBlock->mUnknown0 = 2;
        }
        break;
    case 2:
        if (fn_800FC4A8(p, pBlock, 1)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = state;
            p->mUnknown512.mUnknown14 = 0;
        } else if (fn_800FC4A8(p, pBlock, 2)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = 3;
            p->mUnknown512.mUnknown14 = 0;
        } else if (fn_800FC7A0(p, pBlock)) {
            if (fn_800FC4A8(p, pBlock, 3)) {
                pBlock->mUnknown0 = 0;
                pBlock->mUnknown37 = 3;
                p->mUnknown512.mUnknown14 = 0;
            } else {
                result = 1;
            }
        }
        break;
    case 3:
        result = 1;
        break;
    }
    if (result == 1) {
        if (fn_801CFFD0(p->mMotion.mFacing, pBlock->mUnknown20) > 0x200000) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 6;
            message.mUnknown1[0] = pBlock->mUnknown20 >> 16;
            message.mUnknown1[1] = 1;
            fn_800F03D8(0, p->mpState, &message, p);
            fn_801C1F94(&message, 0, 4);
            message.mId = 9;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 255;
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 87;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = pBlock->mUnknown20 >> 16;
            fn_800F03D8(0, p->mpState, &message, p);
        }
        fn_8016DF34(p);
    }
    return result;
}

extern "C" int fn_800FD3F0(Object_80039F5C *p) {
    if (p) {
        fn_800FD724(p);
    }
    return 1;
}

extern "C" int fn_800FD650(Object_80039F5C *p, int mode) {
    Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;

    if (mode == 1) {
        pBlock->mUnknown0 = -pBlock->mUnknown0;
        pBlock->mUnknown4 = -pBlock->mUnknown4;
        pBlock->mUnknown16 = (pBlock->mUnknown16 + 0x800000) & 0xFFFFFF;
    }
    return 0;
}

extern "C" int fn_800FF860() {
    return 1;
}

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

extern "C" void fn_8010BE54(Object_80039F5C *p)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    message.mId = 93;
    fn_8003AB28(p, &message, 0);
}

extern "C" void fn_8010BEA4(void)
{
    fn_801C1F94(lbl_802DABBC, 0, 100);
}

extern "C" int fn_8010C864(Object_80039F5C *p)
{
    int found = 0;
    unsigned char i;
    unsigned int count = fn_80178D18(fn_80178308());

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178308(), i);

        if (pOther != p && fn_800F06F4(0, pOther->mpState, 26, 0xFFFF) != 0xFFFF) {
            found = 1;
            break;
        }
    }
    return found;
}

extern "C" void fn_8010CFD4(Object_80039F5C *p)
{
    if (((p->mMotion.mUnknown32 - 0x400000) & 0xFFFFFF) > 0x800000) {
        p->mUnknown512.mUnknown15 = 15;
    } else {
        p->mUnknown512.mUnknown15 = 16;
    }
}

extern "C" int fn_8010D6D4(Object_80039F5C *p)
{
    int port;

    fn_8010D508(p);
    port = fn_800B65A0(p->mIdBytes[2]);
    if (port != 255 && p->mUnknown8 == 255) {
        fn_800B6714(p, port);
    }
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude)
{
    unsigned char i;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);

        if (pOther != pExclude && pOther->mpState->mId == 90) {
            return pOther;
        }
    }
    return 0;
}

extern "C" void fn_8010EF40(Object_80039F5C *p)
{
    int found = 0;
    Block_80170374 *pBlock = &p->mUnknown560;
    Object_80039F5C *pCarrier;
    Object_80039F5C *pOther;
    Point_8017886C delta;

    if (pBlock->mFlags.mBytes[0] == 1) {
        pCarrier = fn_80137B40();
        if (pCarrier != 0 && (pCarrier->mFlags & 0x10000)) {
            switch (pBlock->mUnknown54) {
            case 0:
            case 5:
            case 7:
                pOther = fn_8009BCE8(&pBlock->mUnknown44);
                if (pOther == pCarrier) {
                    found = 1;
                } else {
                    pOther = fn_8009BCE8(&pBlock->mUnknown40);
                    if (pOther != 0 && (pOther->mpState->mId == 17 || pOther == pCarrier)) {
                        found = 1;
                    }
                }
                if (found && fn_802372EC(0, 100) <= 74) {
                    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                        fn_800E96EC(p, pOther);
                    }
                }
                break;
            }
        }
    }
}

extern "C" int fn_8010FB10(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_801100A0(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;

    if (pState->mUnknown2) {
        p->mFlags |= 1 << pState->mUnknown1;
    } else {
        p->mFlags &= ~(1 << pState->mUnknown1);
    }
    return 1;
}

extern "C" int fn_801105B0(Object_80039F5C *p)
{
    int angle;

    if (p->mUnknown776 == 1) {
        angle = (0x800000 - p->mMotion.mFacing) & 0xFFFFFF;
    } else {
        angle = p->mMotion.mFacing;
    }
    if (p->mUnknown1008.mUnknown1 == 6) {
        angle = (angle + 0xB1C71D) & 0xFFFFFF;
    } else {
        angle = (0x131C71D - angle) & 0xFFFFFF;
    }
    if (angle <= 0x5FFFFF) {
        if (angle <= 0x3FFFFF) {
            angle = 0x1000000;
        } else {
            angle = 0x600000;
        }
    }
    return angle;
}

extern "C" int fn_80110630(Key_80110630 *pA, Key_80110630 *pB)
{
    int result = pA->mUnknown0 == pB->mUnknown0;

    if (pA->mUnknown1 != pB->mUnknown1) {
        result = 0;
    }
    if (pA->mUnknown2 != pB->mUnknown2 && pA->mUnknown2 != 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80110824(Object_80039F5C *p, int a, int b, int c)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_801101DC(p)) {
        if (b == 0) {
            b = fn_801102A4(p);
        }
        if (a == 1) {
            a = 2;
        }
        result = 1;
        fn_800D0BF4(p, c, 35);
        fn_801C1F94(&message, 0, 4);
        message.mId = 35;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80110EB0(Object_80039F5C *p, int a)
{
    return fn_801250B8(p, a, 6) < lbl_803EAF58;
}

extern "C" int fn_80110EE4(Object_80039F5C *p)
{
    int result;
    int team;
    int angle;
    Object_80039F5C *pTarget;
    float distance;
    Point_8017886C delta;

    switch (p->mpState->mUnknown1) {
    case 1:
        result = 6;
        break;
    case 2:
        result = 8;
        break;
    case 0:
    default:
        team = fn_80178320();
        result = 6;
        pTarget = fn_801244F0(p, team, 0, fn_80178D70(fn_80178320()), &distance, 1);
        if (pTarget != 0) {
            fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            fn_801CFFD0(angle, p->mMotion.mFacing);
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mpState->mUnknown1 = 1;
            } else {
                p->mpState->mUnknown1 = 2;
                result = 8;
            }
        } else if (p->mUnknown776 == 2) {
            result = 8;
        }
        break;
    }
    return result;
}

extern "C" int fn_80110FE4(Object_80039F5C *p)
{
    int result = 0;

    if (fn_800AD9B4() == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (p != fn_80137B40()) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_80111090(Object_80039F5C *p, int a)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_80110FE4(p)) {
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 43;
        message.mUnknown1[0] = a;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" void fn_80111354(Object_80039F5C *p)
{
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
    case 32:
    case 36:
    case 58:
        break;
    default:
        fn_800E9528(p);
        break;
    }
}

extern "C" int fn_80111580(Object_80039F5C *p)
{
    switch (fn_801BE648(p->mpUnknown792)) {
    case 196:
    case 210:
        return 0;
    }
    return 1;
}

extern "C" int fn_80111964(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown15 = 0;
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
    Object_80039F5C *value = 0;
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
