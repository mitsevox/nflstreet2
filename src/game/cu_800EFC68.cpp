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
extern char lbl_802DABBC[];
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

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_80125508() {
    return 0;
}
