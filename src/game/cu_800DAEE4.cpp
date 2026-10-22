#include "engine/cu_801B9F00.h"
#include "game/fn_801BA2A8.h"
#include "game/Object_800D81C8.h"
#include "game/fn_801BE60C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Record_800DB60C.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802372EC.h"
#include "game/fn_800B65A0.h"
#include "game/Table_80089904.h"

typedef Record_800DB60C Record_800DB074;

extern "C" {
extern float lbl_803ECB08;
extern float lbl_803EAD14;
extern unsigned char lbl_803EAD18;
extern unsigned char lbl_803EAD19;
int fn_800DAE4C(Object_80039F5C *p);
int fn_800DAD90(Table_80089904 *pTable, int value, int a, unsigned char b);
float fn_8012506C(Object_80039F5C *p, int value);
int fn_800ACFA8(Object_80039F5C *p);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int value, Point_8017886C *pOut);
int fn_80132630(Object_80039F5C *p, Point_8017886C *pPoint, Object_80039F5C *pOther);
int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_80178308(void);
unsigned int fn_800ABDA4(int team);
unsigned char fn_8011F59C(int index);
void fn_8011F5AC(int index);

int fn_801CFFD0(int a, int b);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_801061E8(Object_80039F5C *p, Object_80137ABC *pBall);
int fn_80106580(Object_80039F5C *p, int a);
int fn_80106618(Object_80039F5C *p);
int fn_80105FF8(Object_80039F5C *p, Object_80137ABC *pBall, float value);
int fn_80103CB0(Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);

float fn_801BD640(void *p, int flags);
float fn_801BD6D4(Block_801BD6D4 *p);
int fn_801787A0(void);
int fn_8023790C(void);
void fn_800DB40C(Record_800DB074 *pRecord, Object_80039F5C *p, Object_80137ABC *pBall);
}

extern "C" int fn_800DAEE4(Object_80039F5C *p)
{
    int result;
    if (fn_8011F518()->mUnknown4 == 11) {
        result = 1;
        if (p->mUnknown776 == 1) {
            result = 2;
        }
    } else {
        int angle = fn_801CFFD0(p->mMotion.mFacing, 0);
        result = 2;
        if (angle <= 0x3FFFFF) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800DAF5C(Table_80089904 *pTable, int key, void *pContext,
    Record_800D81C8 *pEntries, Object_80039F5C *p, int phase)
{
    if (phase != 0) {
        return 0;
    }
    Point_8017886C direction;
    direction.mX = (signed char)p->mUnknown1008.mUnknown1 * 0.1f;
    direction.mY = (signed char)p->mUnknown1008.mUnknown2 * 0.1f;
    int angle = (fn_801CFE40(direction.mY, direction.mX) - p->mMotion.mFacing) & 0xFFFFFF;
    int foot = fn_800DAE4C(p);
    unsigned char side = (unsigned char)fn_800DAEE4(p);
    int index = fn_800DAD90(pTable, angle, foot, side);
    fn_801BA2A8(pContext, pEntries, pTable->mEntries[index].mUnknown0,
        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
    return 0;
}

extern "C" void fn_800DB074(Object_80039F5C *p, Object_80137ABC *pBall, Record_800DB074 *pRecord)
{
    Record_8011F518 *pRecord8011F518 = fn_8011F518();
    pRecord8011F518->mUnknown8 = pRecord->mUnknown16;
    Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown12);
    if (pOther) {
        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        pRecord8011F518->mUnknown12 = fn_801CFE40(delta.mY, delta.mX);
    } else {
        pRecord8011F518->mUnknown12 = p->mMotion.mUnknown32;
    }
    fn_801061E8(p, pBall);
}

extern "C" void fn_800DB100(Object_80039F5C *p, Object_80137ABC *pBall, Record_800DB074 *pRecord)
{
    Vector_80039F5C ball;
    Vector_80039F5C joint;

    fn_80137D58(pBall, &ball);
    fn_8009BF5C(p, 12, &joint, 0);
    if (ball.mZ < pRecord->mUnknown4 - 0.3f) {
        return;
    }
    if (ball.mZ <= joint.mZ - 0.15f) {
        return;
    }
    Record_8011F4F8 *pRequest = fn_8011F4F8(fn_801374E0(pBall));
    if (pRequest->mUnknownB != 1) {
        return;
    }
    pRequest->mUnknown8 = (pRequest->mUnknown8 - 5) / 3 + 5;
    pRequest->mUnknownC = pRecord->mUnknown16;
    Point_8017886C delta;
    delta.mX = 0.2f;
    delta.mY = pRecord->mUnknown8 - ball.mZ;
    delta.mY = delta.mY < 0.0f ? 0.0f : delta.mY;
    int angle = delta.Heading();
    pRequest->mUnknown10 = angle + fn_802372EC(0, 0xE38E3);
    if (pRequest->mUnknownC == 0.0f) {
        float value = pRequest->mUnknown10 * 2.3841858e-07f;
        pRequest->mUnknownC = value * 0.5f + 0.5f;
    }
    float scale = pRequest->mUnknownC * 0.5f;
    pRequest->mUnknown0 -= pRequest->mUnknown0 * scale;
    pRequest->mUnknown4 -= pRequest->mUnknown4 * scale;
    if (fn_80103CB0(p)) {
        Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown12);
        if (pOther) {
            Record_800B15FC *pMessage = fn_800B15FC();
            fn_8009BD2C(pOther, &pMessage->mUnknown0);
            pMessage->mUnknownC = p->mMotion.mPos.mX;
            pMessage->mUnknown10 = p->mMotion.mPos.mY;
            pMessage->mUnknown14 = 34;
            fn_800B1508();
        }
    }
}

extern "C" void fn_800DB308(Object_80039F5C *p, float *pOut)
{
    float value = 12.0f;
    unsigned short kind = fn_801BE648(p->mpUnknown792);

    if (kind == 135 || kind == 191) {
        if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, kind)) {
            Record_800D81C8 *pRecords = p->mpUnknown800;
            unsigned short index = fn_801BA5A8(p->mpUnknown796, pRecords, kind, 0);
            value = fn_801BD640(pRecords[index].mUnknown4C.mpUnknown0, 0xC003);
            value -= fn_801BD6D4(&pRecords[index].mUnknown4C);
            value = value < 0.0f ? 0.0f : (value > 12.0f ? 12.0f : value);
        }
    } else if (kind == 69 || kind == 178) {
        value = 0.0f;
    }
    if (pOut) {
        *pOut = value;
    }
}

extern "C" void fn_800DB40C(Record_800DB074 *pRecord, Object_80039F5C *p, Object_80137ABC *pBall)
{
    fn_800DB308(p, &pRecord->mUnknown20);
    if (fn_80105FF8(p, pBall, pRecord->mUnknown20)) {
        pRecord->mUnknown1 = 1;
    }
    pRecord->mUnknown20 += (unsigned int)fn_8023790C();
}

extern "C" void fn_800DB498(Record_800DB074 *pRecord, Object_80039F5C *p, Object_80137ABC *pBall)
{
    Vector_80039F5C pos;

    fn_800DB308(p, &pRecord->mUnknown20);
    pRecord->mUnknown0 = 1;
    fn_80137D58(pBall, &pos);
    pRecord->mUnknown8 = pRecord->mUnknown4 = pos.mZ;
    pRecord->mUnknown20 += (unsigned int)fn_8023790C();
}

extern "C" void fn_800DB520(Record_800DB074 *pRecord, Object_80039F5C *p, Object_80039F5C *pOther, float value)
{
    pRecord->mUnknown0 = 0;
    pRecord->mUnknown1 = 0;
    pRecord->mUnknown4 = 0.0f;
    pRecord->mUnknown8 = 0.0f;
    fn_8009BD2C(pOther, &pRecord->mUnknown12);
    pRecord->mUnknown16 = value / (lbl_803ECB08 * 100621.12f);
    Object_80137ABC *pBall = fn_80137C48(p);
    if (pBall) {
        int kind = fn_801BE648(p->mpUnknown792);
        if (kind == 69 || kind == 178) {
            if (fn_8011F4F8(fn_801374E0(pBall))->mUnknownB == 1) {
                fn_800DB498(pRecord, p, pBall);
            }
        } else if (kind == 135 || kind == 191) {
            fn_800DB40C(pRecord, p, pBall);
        }
    }
}

extern "C" void fn_800DB60C(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    if (pRecord->mUnknown0 != 1 && pRecord->mUnknown1 != 1) {
        Object_80137ABC *pBall = fn_80137C48(p);
        if (pBall && fn_80106580(p, (p->mFlags >> 14) & 1)) {
            fn_800DB40C(pRecord, p, pBall);
        }
    }
}

extern "C" void fn_800DB688(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    int done = 0;

    if (pRecord->mUnknown0 == 1) {
        Object_80137ABC *pBall = fn_80137C48(p);
        if (!pBall) {
            pRecord->mUnknown0 = 0;
        } else if (pRecord->mUnknown20 <= (unsigned int)fn_8023790C()) {
            if (p->mFlags & 0x1000) {
                fn_800DB100(p, pBall, pRecord);
                p->mFlags &= ~0x3000;
                pRecord->mUnknown0 = 0;
            }
        } else if (!fn_80106618(p)) {
            pRecord->mUnknown0 = 0;
        } else {
            Vector_80039F5C pos;
            fn_80137D58(pBall, &pos);
            if (pRecord->mUnknown8 < pos.mZ) {
                pRecord->mUnknown8 = pos.mZ;
            }
        }
        if (!done && pRecord->mUnknown0 == 0) {
            p->mUnknown778 = -1;
            fn_8011F4F8(fn_801374E0(fn_801374BC()))->mUnknownB = 0;
        }
    }
}

extern "C" void fn_800DB7A4(Record_800DB074 *pRecord, Object_80039F5C *p)
{
    int done = 0;

    if (pRecord->mUnknown1 == 1) {
        int busy = fn_801787A0();
        if (!busy) {
            Object_80137ABC *pBall = fn_80137C48(p);
            if (!pBall) {
                pRecord->mUnknown1 = 0;
            } else {
                if (pRecord->mUnknown20 <= (unsigned int)fn_8023790C()) {
                    done = 1;
                    fn_800DB074(p, pBall, pRecord);
                    p->mFlags &= ~0x3000;
                    pRecord->mUnknown1 = 0;
                } else if (!fn_80106618(p)) {
                    pRecord->mUnknown1 = 0;
                }
                if (fn_801BE648(p->mpUnknown792) == 234) {
                    pRecord->mUnknown1 = 0;
                }
                if (!done && pRecord->mUnknown1 == 0) {
                    p->mUnknown778 = -1;
                    fn_8009BD2C(0, &fn_8011F518()->mUnknown0);
                }
            }
        }
    }
}

extern "C" void fn_800DB8B4(Record_800DB60C *pRecord, Object_80039F5C *p)
{
    int allow = 1;
    int failed = 0;
    if (fn_800B65A0(p->mIdBytes[2]) != 255 || pRecord->mUnknown1 == 1) {
        return;
    }
    switch (p->mpState->mId) {
    case 10:
    case 16:
    case 58:
        break;
    default:
        return;
    }
    if (!(fn_8012506C(p, 3) <= 65.0f)) {
        allow = 0;
    }
    unsigned int roll = (unsigned int)fn_802372EC(0, 255);
    if (roll > (unsigned int)fn_800ACFA8(p)) {
        failed = 1;
    }
    if (failed && (unsigned int)fn_802372EC(0, 100) < (unsigned int)lbl_803EAD19) {
        allow = allow == 0;
    }
    Point_8017886C point;
    Object_80039F5C *pOther = fn_80105384(p, 0, &point);
    if (!pOther) {
        return;
    }
    int can = 0;
    if (allow && fn_80132630(p, &point, pOther)) {
        can = 1;
    }
    if (!can) {
        return;
    }
    int ready = 0;
    if (fn_801066D0(p, pOther, 9)) {
        ready = 1;
    }
    if (!ready) {
        return;
    }
    allow = fn_8012506C(pOther, 5) < lbl_803EAD14;
    if (!allow) {
        return;
    }
    if (fn_800ABDA4(fn_80178308()) == 0) {
        int count = fn_8011F59C(0);
        count += fn_8011F59C(1);
        if (count > 0) {
            allow = 0;
        }
    } else if (fn_800ABDA4(fn_80178308()) == 1) {
        int count = fn_8011F59C(0);
        count += fn_8011F59C(1);
        if (count > 1) {
            allow = 0;
        }
    }
    if (!allow) {
        return;
    }
    if (failed) {
        if ((unsigned int)fn_8011F59C(1) < (unsigned int)lbl_803EAD18) {
            fn_8011F5AC(1);
        } else {
            allow = 0;
        }
    } else {
        fn_8011F5AC(0);
    }
    if (allow) {
        fn_800DB60C(pRecord, p);
    }
}

extern "C" int fn_800DBAF0(Object_80039F5C *p)
{
    Record_800DB60C *pRecord = 0;
    switch (p->mpState->mId) {
    case 16:
        pRecord = (Record_800DB60C *)((char *)p + 368);
        break;
    case 10:
    case 58:
        pRecord = (Record_800DB60C *)((char *)p + 356);
        break;
    case 36:
        pRecord = (Record_800DB60C *)((char *)p + 336);
        break;
    }
    int result = 0;
    if (pRecord && pRecord->mUnknown1) {
        result = pRecord->mUnknown20 >= 0.0f;
    }
    return result;
}


#include "game/Block_801BE60C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"

#include "game/Object_80039F5C.h"
#include "game/fn_80163E94.h"

struct Object_800DC36C {
    char mUnknown0[36];
    unsigned short mUnknown36;
    char mUnknown38[2];
    int mUnknown40;
};

struct Entry_800DC36C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Object_800DC36C *mpUnknown4;
};

struct List_800DC36C {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_800DC36C mEntries[1];
};

extern "C" {
extern float lbl_803ECB08;

void fn_8009BD60(Object_80039F5C *p);
int fn_800A7EF4(unsigned char a);
void fn_800ADB90(Object_80039F5C *p, int a, int b, int c);
float fn_800C495C(Object_80039F5C *p, float value);
void fn_800C89F0(Object_80039F5C *p, int a, int b, int c, float value);
void fn_800CABF4(Object_80039F5C *p, unsigned char *pOut, int a);
int fn_800D0B90(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_8011F1CC(void);
int fn_8011F1F4(void);
int fn_8011F2C4(void);
int fn_801481B0(void);
int fn_801483F8(void);
int fn_801486A0(void);
void fn_80156C78(int index, int value);
Object_800670B4 *fn_80168708(int team);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
int fn_801783AC(int bit);
void fn_801BD81C(void *p, float value);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *p, float value);


void fn_801BE760(void *p, unsigned short key, unsigned short flags);
float fn_801CFFA0(float value);
int fn_801CFFD0(int a, int b);
}

static unsigned int lbl_803EAD1C = 0;

extern "C" int fn_800DBB74(Object_80039F5C *p, unsigned char *pOut)
{
    int result;

    *pOut = 0;
    if (p->mUnknown8 == 255 || !(p->mFlags & 0x4000)) {
        int mode = fn_800AD9B4();
        result = 1;
        if (!fn_801783AC(0)) {
            unsigned char kind = p->mUnknown2914;
            if ((kind == 0 || kind == 20 || kind == 1 || kind == 3)
                && (fn_8011F1CC() || fn_8011F1F4())
                && mode == 3 && p->mpState->mId == 18 && p->mUnknown360 == 1) {
                *pOut = 1;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

extern "C" void fn_800DBC4C(Object_80039F5C *p, int angle, float value)
{
    int dir = 0x755555;
    int result;
    int target;

    if (p->mUnknown2913 == 0) {
        dir = 0xAAAAA;
    }
    if (fn_801BE648(p->mpUnknown792) != 217 || value > 0.0f) {
        if (value <= 0.0f) {
            lbl_803EAD1C++;
            if (fn_801CFFD0(p->mMotion.mFacing, dir) > 0x400000) {
                if (lbl_803EAD1C > 15) {
                    int base = 0x800000;
                    if (p->mUnknown2913 == 0) {
                        base = 0;
                    }
                    fn_8009BD60(p);
                    if (p->mUnknown2913 == 0) {
                        p->mUnknown1008.mUnknown0 = 1;
                    } else {
                        p->mUnknown1008.mUnknown0 = 2;
                    }
                    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4 = base;
                    p->mUnknown512.mUnknown14 = 6;
                    p->mUnknown512.mUnknown0 = 1.0f;
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 217, p, 1.0f);
                    p->mUnknown512.mUnknown14 = 0;
                    p->mFlags &= ~4;
                } else {
                    if ((p->mFlags & 4) || fn_801BE648(p->mpUnknown792) != 222) {
                        p->mFlags &= ~4;
                        if (p->mUnknown2913 == 0) {
                            p->mUnknown1008.mUnknown0 = 1;
                        } else {
                            p->mUnknown1008.mUnknown0 = 2;
                        }
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 222, p, 1.0f);
                    }
                    p->mUnknown512.mUnknown14 = 0;
                }
                return;
            }
            angle = -0x400000;
        } else {
            lbl_803EAD1C = 0;
        }
        result = fn_800DC080(p);
        if (result == 1 && p->mUnknown512.mUnknown15 != 1) {
            if (fn_801CFFD0(angle, -0x38E38E) <= 0x155554) {
                if (p->mUnknown2913 == 0) {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if (facing >= 0x6E38E4 && facing <= 0xC38E38
                        && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                        target = 0x6AAAAB;
                    } else {
                        target = (angle + 0x38E38E) & 0xFFFFFF;
                    }
                } else {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if ((facing < 0x11C71C || facing > 0xBC71C7)
                        && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                        target = 0x155555;
                    } else {
                        target = (angle - 0x38E38E) & 0xFFFFFF;
                    }
                }
                p->mUnknown512.mUnknown14 = 3;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown8 = target;
                p->mUnknown512.mUnknown0 = value;
            } else {
                p->mUnknown512.mUnknown14 = result;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown0 = value;
                if (p->mUnknown512.mUnknown15 != 1) {
                    fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
                }
            }
        } else if (p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
            angle = -0x400000;
            if (p->mUnknown2913 == 0) {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if (facing >= 0x6E38E4 && facing <= 0xC38E38
                    && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                    target = 0x6AAAAB;
                } else {
                    target = (angle + 0x38E38E) & 0xFFFFFF;
                }
            } else {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if ((facing < 0x11C71C || facing > 0xBC71C7)
                    && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                    target = 0x155555;
                } else {
                    target = (angle - 0x38E38E) & 0xFFFFFF;
                }
            }
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown8 = target;
            p->mUnknown512.mUnknown0 = value;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown0 = value;
            if (p->mUnknown512.mUnknown15 != 1) {
                fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
            }
        }
    } else if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown8 = dir;
        p->mUnknown512.mUnknown0 = value;
    }
}

extern "C" int fn_800DC080(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;

    if (p->mIdBytes[3] == 1) {
        int mode = fn_800AD9B4();
        Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);
        if (!fn_801783AC(0) && fn_80137C48(p)
            && (p == fn_8016444C(pTeam)
                || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                    && (fn_801481B0() || !(p->mFlags & 0x400))))
            && (fn_8011F1CC() || fn_8011F1F4())
            && mode == 3 && p->mpState->mId != 1 && p->mUnknown512.mUnknown15 != 1) {
            if (!fn_800DBB74(p, &flag)) {
                if (!fn_801483F8()) {
                    result = 1;
                } else if (fn_801481B0() == 1) {
                    if (!(p->mFlags & 0x200000)) {
                        result = 1;
                    } else if (p->mMotion.mUnknown28 < lbl_803ECB08 * 0.4f) {
                        p->mFlags &= ~0x200000;
                        result = 1;
                    }
                } else {
                    p->mFlags |= 0x200000;
                }
            } else {
                result = flag == 0;
            }
        } else if (fn_801486A0() == 1 && p->mpState->mId == 51) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800DC21C(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;
    unsigned char shown;
    int mode = fn_800AD9B4();
    Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);

    if (!fn_801783AC(0) && fn_80137C48(p)
        && (p == fn_8016444C(pTeam)
            || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                && (fn_801481B0() || !(p->mFlags & 0x400))))
        && fn_8011F1CC() && mode == 3 && p->mpState->mId != 1 && p->mpState->mId != 91) {
        if (!fn_800DBB74(p, &flag)) {
            if (!fn_800DC080(p)) {
                result = 1;
            }
        } else {
            result = flag;
        }
    }
    if (result && p && !fn_800D0B90(p)) {
        fn_800CABF4(p, &shown, 0);
        if (shown) {
            fn_80156C78(21, 1);
        }
    }
    return result;
}

extern "C" int fn_800DC36C(List_800DC36C *pList, unsigned short key, void *pA,
                           Record_800D81C8 *pRecords, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, key);
    int side;
    int i;

    switch (phase) {
    case 0:
        if (p->mUnknown2913 == 0) {
            side = 1;
            fn_800ADB90(p, 5, 8, 1);
        } else {
            side = 0;
            fn_800ADB90(p, 5, 8, 0);
        }
        for (i = 0; i < pList->mCount; i++) {
            Object_800DC36C *pObject = pList->mEntries[i].mpUnknown4;
            if (pObject->mUnknown36 == side
                && fn_801CFFD0(pObject->mUnknown40, p->mUnknown512.mUnknown4) <= 0x400000) {
                break;
            }
        }
        fn_801BE760(p->mpUnknown792, key, 1);
        pBlock->mUnknown0Word = fn_801BA2A8(pA, pRecords, pList->mEntries[i].mUnknown0,
                                        pList->mEntries[i].mUnknown2, key, p, 1.0f);
        pBlock->mUnknown4Word = p->mMotion.mFacing;
        break;
    case 1:
        break;
    case 2:
        if (pBlock->mUnknown4Word != p->mMotion.mFacing) {
            p->mpUnknown800[pBlock->mUnknown0Word].mUnknownC =
                (p->mpUnknown800[pBlock->mUnknown0Word].mUnknownC
                 + (p->mMotion.mFacing - pBlock->mUnknown4Word)) & 0xFFFFFF;
            pBlock->mUnknown4Word = p->mMotion.mFacing;
        }
        fn_801BD81C(&pRecords[pBlock->mUnknown0Word].mUnknown4C, fn_801CFFA0(fn_800C495C(p, 1.0f)));
        if (fn_800A7EF4(p->mIdBytes[2]) == 2) {
            fn_801BD81C(&pRecords[pBlock->mUnknown0Word].mUnknown4C, fn_801CFFA0(2.0f));
        } else if (fn_800A7EF4(p->mIdBytes[2]) == 0) {
            fn_801BD81C(&pRecords[pBlock->mUnknown0Word].mUnknown4C, fn_801CFFA0(0.5f));
        }
        break;
    }
    return 0;
}

extern "C" void fn_800DC578(void)
{
    lbl_803EAD1C = 0;
}


#include "game/Object_80039F5C.h"
#include "game/fn_800DF134.h"
#include "game/Object_800EA284.h"
#include "game/Object_801BBD5C.h"
#include "game/Block_801BE60C.h"
#include "game/InGame.h"
#include "game/Message_800F01CC.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801EBC18.h"
#include "game/fn_80094488.h"
#include <math.h>

struct Record_800DC584 {
    int mUnknown0;
};

/* Views of the fn_801BE60C record, whose layout depends on the key. */
struct Record_800DD5E4 {
    char mUnknown0[6];
    unsigned char mUnknown6;
};

struct Record_800DD648 {
    char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Record_800DD780 {
    unsigned int mUnknown0;
    char mUnknown4[12];
    unsigned char mUnknown16;
};

struct Record_800DDCE4 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    short mUnknown14;
};

struct Record_800E1778 {
    unsigned char mUnknown0;
};

/* Views of the player block at +336, whose layout depends on the state. */
struct Block_800E0188 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_800E0230 {
    float mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

struct Block_800E0E8C {
    char mUnknown0[2];
    unsigned short mUnknown2;
};

struct Block_800E0EF0 {
    unsigned char mUnknown0;
    char mUnknown1[6];
    unsigned char mUnknown7;
    char mUnknown8[8];
    unsigned char mUnknown16;
    char mUnknown17[11];
    unsigned char mUnknown28;
};

/* View of the bytes from +12 of the player block at +1160. */
struct Block_800DF654 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[8];
    float mUnknown20;
    float mUnknown24;
    int mUnknown28;
};

struct Block_800E1438 {
    char mUnknown0[6];
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

struct Block_800E1778 {
    char mUnknown0[24];
    unsigned char mUnknown24;
    char mUnknown25[5];
    unsigned short mUnknown30;
};

struct Block_800E13E4 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    char mUnknown9[3];
    int mUnknown12;
};

typedef Record_800EA284 Block_800E11C0;

extern "C" {
void fn_800DD994(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                 Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask);
int fn_800DA7AC(Object_801BBD5C *pObject, float value);
float fn_800DAA68(int index, void *pA, Object_801BBD5C *pObject, int b, float value);
void fn_8009A260(Object_80039F5C *p);
int fn_8009B9A8(int a);
float fn_8009BB54(int a);
void fn_8009BD60(Object_80039F5C *p);
void fn_8009BFD0(Object_80039F5C *p, Vector_80039F5C *pPos, float *pRot);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_8009D1F4(Object_80039F5C *p);
void fn_800A8954(int event, int team, Object_80039F5C *p);
void fn_800AE7F0(int event, int team, Object_80039F5C *p);
void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock);
void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock);
int fn_800E8898(Object_80039F5C *p, int *pValue);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800F05E4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
unsigned int fn_8011E188(void);
int fn_80120794(Object_800B26B0 *pA, Object_800B26B0 *pB, float *pC, float e, float f, int d, float g);
int fn_801486A0(void);
Object_800670B4 *fn_80168708(int team);
void fn_80171DB0(Object_80039F5C *p);
int fn_80178308(void);
int fn_801CFE08(float value);
int fn_801CFFD0(int a, int b);
void fn_802271A4(Vector_80039F5C *pOut, Vector_80039F5C *p);
void fn_80227248(void *pOut, void *p, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227B04(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
}

extern float lbl_803ECB08;

#include "game/fn_80177FE0.h"
#include "game/Class_80297C60.h"
#include "game/cu_8008E978.h"

struct Block_800DFCEC {
    float mUnknown0, mUnknown4;
    unsigned char mUnknown8, mUnknown9, mUnknown10, mUnknown11, mUnknown12, mUnknown13;
};
extern "C" {
float fn_80178A2C(void);
Point_8017886C fn_80177FFC(int team);
int fn_801CFE40(float y, float x);
void fn_8003AB08(Object_80039F5C *p, int a);
void fn_8003E174(int a);
int fn_80027DF0(void);
void fn_8010A2DC(Object_80039F5C *p, int a, int b);
void fn_801BE67C(void *pA, void *pB, void *pC, Object_80039F5C *p);
void fn_8013AD04(Object_80137ABC *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, int facing, float a, float b);
void fn_800ACDE4(Object_80039F5C *p, float *pChance, float *pAngle);
int fn_80178348(void);
float fn_80237260(int a);
int fn_800DFA00(Object_80039F5C *p, float *pValue);
int fn_800B9A90(Class_80297C60 *p);
}

struct Record_800DE19C { int mUnknown0, mUnknown4; };
struct Info_800DDF34 {
    char mUnknown0[4];
    unsigned char mUnknown4[4];
    int mUnknown8, mUnknown12, mUnknown16, mUnknown20;
    float mUnknown24;
};
struct Block_800DE3B0 {
    float mUnknown0;
    Pair_802270A4 mUnknown4, mUnknownC;
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C, mUnknown1D, mUnknown1E, mUnknown1F;
    State_800D8140 mUnknown20;
    int mUnknown38;
    unsigned char mUnknown3C, mUnknown3D;
    signed char mUnknown3E, mUnknown3F;
};
struct Command_800DE3B0 {
    Pair_802270A4 mUnknown0;
    char mUnknown8[4];
    Pair_802270A4 mUnknownC;
    char mUnknown14[4];
    float mUnknown18;
};
struct State_800DE3B0 {
    int mUnknown0;
    Pair_802270A4 mUnknown4;
    char mUnknownC[6];
    unsigned char mUnknown12;
    char mUnknown13[1];
    Pair_802270A4 mUnknown14;
    int mUnknown1C;
};
extern "C" {
void fn_801BD81C(void *p, float value);
float fn_801CFFA0(float value);
void fn_80227384(void *pOut, void *p, int angle);
}
extern float lbl_803EAD20;

#include "game/Object_800DA8D8.h"
#include "game/Record_8036B55C.h"
struct Record_800DC6F4 {
    int mUnknown0, mUnknown4;
    unsigned char mUnknown8, mUnknown9, mUnknown10;
};
struct Record_800DCC14 {
    char mUnknown0[4];
    float mUnknown4;
    char mUnknown8[4];
    int mUnknown12;
    signed char mUnknown16;
};
extern "C" {
Object_801BBD5C *fn_801BBD5C(unsigned short key, unsigned short id);
int fn_801BA2D0(void *pA, Record_800D81C8 *pEntries, Record_800D81C8 *pEntry);
void fn_801BA418(void *pA, Record_800D81C8 *pEntries, int index, unsigned short a, int b, unsigned short key, Object_80039F5C *p);
void fn_800DA814(Object_800DA8D8 *pObject, Block_801BE60C *pBlock, Object_80039F5C *p, int a, int index, int key, Record_8036B55C *pA, Record_800D81C8 *pEntries);
void fn_800DA8D8(Object_800DA8D8 *pObject, Block_801BE60C *pBlock, Object_80039F5C *p, int a, int index, unsigned short key, void *pA, Record_800D81C8 *pEntries, unsigned char flag);
void fn_800DAC78(Block_801BE60C *p, float a, float b);
void fn_800DAC88(Block_801BE60C *p, void *pA, Record_800D81C8 *pEntries);
}

extern "C" {
int fn_80177F70(void);
int fn_801787A0(void);
int fn_80178320(void);
}
struct Record_800DD2E8 {
    unsigned short mUnknown0, mUnknown2, mUnknown4;
    unsigned char mUnknown6;
};

#include "game/Input_800B6D34.h"
#include "game/cu_80067C10.h"
struct Item_800E0694 {
    char mUnknown0[4];
    unsigned char mUnknown4;
};
struct Block_800E0850 {
    unsigned short mUnknown0, mUnknown2;
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
    int mUnknown20, mUnknown24;
    unsigned char mUnknown28, mUnknown29;
};
extern "C" {
Item_800E0694 *fn_8009A63C(int handle);
void fn_80099F04(Object_80039F5C *p, int handle, int index);
void fn_800A2190(int a);
void fn_8009A5DC(int a, int b, void *pKind, int *pHandle);
float fn_8009A270(int handle);
int fn_8009A578(int handle);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800B8344(Object_80039F5C *p);
int fn_8009A68C(Object_80039F5C *p);
unsigned char *fn_8009CC2C(Object_80039F5C *p, void (*callback)(int, Vector_80039F5C *, unsigned char *), int a, int b);
void fn_80042998(Block_80170E64 *p);
int fn_800C4B6C(Object_80039F5C *p);
}
extern unsigned char lbl_803EAD34;
extern unsigned int lbl_803EAD2C;
extern int lbl_803EAD28;
extern float lbl_803EAD30;

#include "game/State_803EB098.h"
struct Block_800E1954 {
    unsigned char mUnknown0, mUnknown1;
    char mUnknown2[2];
    Point_8017886C mUnknown4, mUnknown12;
    unsigned short mUnknown20;
    unsigned char mUnknown22, mUnknown23, mUnknown24;
    char mUnknown25[11];
    Object_80039F5C *mpUnknown36;
    Point_8017886C mUnknown40;
    char mUnknown48[1];
    unsigned char mUnknown49;
    char mUnknown50[28];
    unsigned char mUnknown78;
};
struct Record_800E2ABC { char mUnknown0[4]; unsigned char mUnknown4, mUnknown5, mUnknown6; };
struct Record_80168EBC { char mUnknown0[48]; unsigned char mUnknown48; };
extern "C" {
Record_8011F4E0 *fn_8011F4E0(void);
Record_80168EBC *fn_80168EBC(int team);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_8009FE24(Object_80039F5C *p);
int fn_800B0F98(void);
int fn_800B146C(void);
void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut);
int fn_8009F780(void);
int fn_8016EADC(void);
void fn_800E3DCC(Object_80039F5C *p, Point_8017886C *pOut);
void fn_80227538(Point_8017886C *pOut, int angle, float magnitude);
void fn_800E586C(Object_80039F5C *p, Point_8017886C *pPoint);
int fn_800E3A34(Object_80039F5C *p, Point_8017886C *pPoint);
}

#include "game/Command_800CEE74.h"
struct Entry_800DE51C { unsigned short mUnknown0; unsigned char mUnknown2; char mUnknown3[17]; };
#include "game/Frame_800DF7CC.h"
struct Attachment_800DF7CC { Vector_80039F5C mPos; Angles_801EBC18 mAngles; int mFrame; };
struct Character_800DF7CC {
    int mUnknown0, mUnknown4; unsigned int mFlags;
    char mUnknown12[8]; struct Flags { char mUnknown0[12]; unsigned int mUnknown12; } *mpUnknown20;
    char mUnknown24[92]; Object_80137ABC *mpBall[1];
};
extern "C" {
float fn_801BFFA0(Object_80039F5C *);
int fn_801C065C(Frame_800DF7CC *, float);
Attachment_800DF7CC *fn_80093C08(unsigned short);
int fn_800943B0(unsigned short);
void fn_8009134C(unsigned short);
int fn_801BBE5C(int objectType, int fileNum);
void *fn_801BC084(unsigned int);
Anim_801BAB34 *fn_801BAB34(void *, int);
int fn_801BD934(float *, void *, unsigned short);
int fn_801BA6B0(Record_800D81C8 *);
void fn_801BA6BC(Record_800D81C8 *, int);
void fn_800D7A0C(Object_80039F5C *, int);
unsigned int fn_801BBEC0(unsigned int, int);
int fn_801BBCC8(int state, unsigned int slot);
}
extern "C" int fn_8013BA58(Object_80137ABC *, int);
extern "C" void fn_800ADBC0(Object_80039F5C *, int, int, int);
extern "C" void fn_8016DBE4(Object_80039F5C *);
extern float lbl_803EA2C4;

struct Table_800DE51C { char mUnknown0[4]; unsigned short mCount; char mUnknown6[2]; Entry_800DE51C mEntries[1]; };
extern "C" {
Table_80089904 *fn_801BE72C(unsigned short, unsigned short);
void fn_800CEDA4(Entry_800DE51C *, Pair_802270A4 *, int *, Object_80039F5C *, int);
void fn_800D8140(State_800D8140 *, Object_80039F5C *, int);
void fn_800D81C8(State_800D8140 *, Object_80039F5C *);
void fn_800D84DC(State_800D8140 *, Object_80039F5C *);
float fn_80114EE4(Object_80039F5C *, Object_80039F5C *);
int fn_800C854C(Object_80039F5C *, unsigned short, unsigned char);
void fn_800DEC10(Object_80039F5C *, Block_800DE3B0 *);
}

extern "C" int fn_801784C4(void);

extern "C" int fn_801784C4(void);
extern "C" void *fn_80040FD4(Vector_80039F5C *, int, float *);
extern "C" void fn_800538E0(void *, Object_80039F5C *);

extern "C" int fn_8009F778(Object_80039F5C *);
extern "C" int fn_8009F6B4(void);
extern "C" void fn_80164B64(int);
extern "C" float fn_802270A4(void *);


extern "C" int fn_800DC584(Object_80039F5C *p, Record_800DC584 *pRecord);
extern "C" float fn_800DC61C(Object_801BBD5C *pObject, Object_80039F5C *p);
extern "C" int fn_800DC674(Object_801BBD5C *pObject, Object_80039F5C *p);
extern "C" float fn_800DC6A8(Object_801BBD5C *pObject, Object_80039F5C *p, int index, void *pA, int b);
extern "C" int fn_800DC6F4(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int fn_800DCC14(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int fn_800DCE2C(Object_80039F5C *p, unsigned char *pInfo);
extern "C" int fn_800DD2E8(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int fn_800DD5E4(Object_80039F5C *p);
extern "C" int fn_800DD648(Object_80039F5C *p);
extern "C" int fn_800DD69C(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode);
extern "C" int fn_800DD780(Object_80039F5C *p, int value, unsigned short key);
extern "C" int fn_800DD830(void *p);
extern "C" int fn_800DD838(Object_80039F5C *p);
extern "C" void fn_800DD92C(Table_80089904 *pTable, unsigned short a, unsigned char value);
extern "C" void fn_800DD994(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                            Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask);
extern "C" void fn_800DDCE4(Object_80039F5C *p, Record_800DDCE4 *pRecord);
extern "C" int fn_800DDD24(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode);
extern "C" void fn_800DDE6C(Object_80039F5C *p);
extern "C" int fn_800DDEE4(unsigned char *pA, unsigned char *pB);
extern "C" unsigned short fn_800DDF34(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, int *pAngle, float *pTime, float *pRate);
extern "C" int fn_800DE19C(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" int fn_800DE364(unsigned int id);
extern "C" void fn_800DE3B0(Block_800DE3B0 *pBlock, Object_80039F5C *p, Command_800DE3B0 *pCommand);
extern "C" void fn_800DE51C(Object_80039F5C *p, Block_800DE3B0 *pBlock, int id);
extern "C" void fn_800DE910(Object_80039F5C *p, Block_800DE3B0 *pBlock);
extern "C" void fn_800DEAB0(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle, Entry_800DE51C *pRecord);
extern "C" void fn_800DEC10(Object_80039F5C *p, Block_800DE3B0 *pBlock);
extern "C" void fn_800DF134(Object_80039F5C *p, Point_8017886C offset, int angle, int key);
extern "C" int fn_800DF1F4(Table_80089904 *pTable, unsigned short key, void *pData, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode);
extern "C" void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord);
extern "C" int fn_800DF6EC(Object_80039F5C *p);
extern "C" void fn_800DF710(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, Angles_801EBC18 *pAngles);
extern "C" void fn_800DF750(Object_80137ABC *pBall, Vector_80039F5C *pPos, int *pAngles);
extern "C" void fn_800DF7CC(Object_80039F5C *p, Character_80093BCC *pCharacter, Attachment_800DF7CC *pAttachments, Frame_800DF7CC *pFrame, int index, unsigned int frame);
extern "C" void fn_800DF9FC(Object_80039F5C *p, void *pRecord, unsigned int value);
extern "C" int fn_800DFA00(Object_80039F5C *p, float *pValue);
extern "C" void fn_800DFCEC(Object_80039F5C *p);
extern "C" int fn_800DFD90(Object_80039F5C *p);
extern "C" int fn_800DFED0(Object_80039F5C *p);
extern "C" int fn_800E0188(Object_80039F5C *p, float *pA, float *pB);
extern "C" void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a);
extern "C" void fn_800E0230(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" float fn_800E02D0(Object_80039F5C *p);
extern "C" void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock);
extern "C" int fn_800E0574(Object_80039F5C *p);
extern "C" int fn_800E05C0(Object_80039F5C *p);
extern "C" int fn_800E068C(Object_80039F5C *p);
extern "C" void fn_800E0694(Object_80039F5C *p, int handle, int index);
extern "C" void fn_800E0818(int a, Vector_80039F5C *pOut, unsigned char *pIndex);
extern "C" int fn_800E0850(Object_80039F5C *p);
extern "C" int fn_800E0AD8(Object_80039F5C *p);
extern "C" int fn_800E0E8C(Object_80039F5C *p);
extern "C" int fn_800E0EF0(Object_80039F5C *p);
extern "C" int fn_800E0F40(Object_80039F5C *p);
extern "C" int fn_800E0F48(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
extern "C" int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget);
extern "C" int fn_800E11C0(Object_80039F5C *p);
extern "C" int fn_800E1248(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_800E12D4(Object_80039F5C *p);
extern "C" int fn_800E1350(Object_80039F5C *p);
extern "C" int fn_800E13E4(Object_80039F5C *p);
extern "C" int fn_800E1438(Object_80039F5C *p);
extern "C" int fn_800E1544(Object_80039F5C *p);
extern "C" int fn_800E1554(Object_80039F5C *p);
extern "C" int fn_800E1584(Object_80039F5C *p);
extern "C" int fn_800E1778(Object_80039F5C *p);
extern "C" int fn_800E1870(Object_80039F5C *p);
extern "C" void fn_800E1954(Object_80039F5C *p);
extern "C" void fn_800E2550(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle);
extern "C" int fn_800E283C(Object_80039F5C *p, int count, float *pValues, float *pOut, float direction, float target);
extern "C" void fn_800E2ABC(Object_80039F5C *p);
extern "C" int fn_800E2F20(Object_80039F5C *p, Point_8017886C *pPoint);

extern "C" int fn_800DC584(Object_80039F5C *p, Record_800DC584 *pRecord)
{
    Object_8016D8B0 *pBlock = &p->mUnknown512;
    int delta = fn_801CFFD0(pBlock->mUnknown4, pBlock->mUnknown8);
    int angle;
    int result;
    if (((pBlock->mUnknown4 - pBlock->mUnknown8) & 0xFFFFFF) > 0x800000) {
        angle = pBlock->mUnknown8 + (0x400000 - delta);
        result = 1;
    } else {
        angle = pBlock->mUnknown8 - (0x400000 - delta);
        result = 2;
    }
    pBlock->mUnknown8 &= 0xFFFFFF;
    p->mpUnknown800[pRecord->mUnknown0].mUnknownC = angle;
    return result;
}

extern "C" float fn_800DC61C(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    float value = p->mMotion.mUnknown28;
    if (fn_801CFFD0((p->mMotion.mUnknown32 - p->mMotion.mFacing) & 0xFFFFFF, pObject->mUnknown20) > 0x400000) {
        value = -value;
    }
    return value;
}

extern "C" int fn_800DC674(Object_801BBD5C *pObject, Object_80039F5C *p)
{
    return fn_800DA7AC(pObject, fn_800DC61C(pObject, p));
}

extern "C" float fn_800DC6A8(Object_801BBD5C *pObject, Object_80039F5C *p, int index, void *pA, int b)
{
    return fn_800DAA68(index, pA, pObject, b, fn_800DC61C(pObject, p));
}

extern "C" int fn_800DC6F4(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DC6F4 *pRecord = (Record_800DC6F4 *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        fn_8009BD60(p);
        pRecord->mUnknown8 = fn_800DC584(p, (Record_800DC584 *)pRecord);
        if (p->mIdBytes[3] != 1) {
            pRecord->mUnknown9 = 2;
            pRecord->mUnknown10 = 2;
        } else if (!p->mUnknown1052) {
            if (fn_800AD9B4() == 3) {
                pRecord->mUnknown10 = 4;
                pRecord->mUnknown9 = 2;
            } else {
                pRecord->mUnknown10 = 2;
                pRecord->mUnknown9 = !(p->mUnknown528.mUnknown0 <= 0.65f) ? 2 : 1;
            }
        } else {
            pRecord->mUnknown10 = 3;
            pRecord->mUnknown9 = 2;
        }
        p->mUnknown1008.mUnknown0 = pRecord->mUnknown8;
        p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
        p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
        int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
        unsigned char entry = fn_801BA2A8(pA, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pRecord->mUnknown0 = entry;
        pRecord->mUnknown4 = -1;
        fn_801BD81C(&pEntries[entry].mUnknown4C, fn_801CFFA0(p->mUnknown528.mUnknown0 + 0.2799999713897705f));
        break;
    }
    case 2: {
        int direction = fn_800DC584(p, (Record_800DC584 *)pRecord);
        if (direction != pRecord->mUnknown8) {
            if (pRecord->mUnknown4 != -1 && p->mpUnknown800[pRecord->mUnknown4].mUnknown8 == key) {
                fn_801BA384((Object_801BA03C *)pA, pEntries, pRecord->mUnknown4);
            }
            int next = fn_801BA2D0(pA, pEntries, &pEntries[pRecord->mUnknown0]);
            pRecord->mUnknown4 = pRecord->mUnknown0;
            fn_801BF4A8(&pEntries[pRecord->mUnknown0].mUnknown30, 12, -1.0f, 0.0f);
            pRecord->mUnknown0 = next;
            unsigned char value = pEntries[next].mUnknown4C.mUnknown1E;
            pRecord->mUnknown8 = direction;
            p->mUnknown1008.mUnknown0 = direction;
            p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
            p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
            int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
            fn_801BA418(pA, pEntries, pRecord->mUnknown0, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p);
            fn_801BF3C8(&pEntries[pRecord->mUnknown0].mUnknown30, 0, 0.0f, 0, 0.0f);
            fn_801BF4A8(&pEntries[pRecord->mUnknown0].mUnknown30, 12, -1.0f, 1.0f);
            pEntries[pRecord->mUnknown0].mUnknown24.mUnknown4 = -pEntries[pRecord->mUnknown0].mUnknown24.mUnknown4;
            pEntries[pRecord->mUnknown0].mUnknown4C.mUnknown1E = value;
            float speed = p->mUnknown528.mUnknown0;
            speed -= speed * 0.2f;
            p->mUnknown528.mUnknown0 = speed;
            if (!(speed >= 0.01f)) {
                speed = 0.01f;
            }
            p->mUnknown528.mUnknown0 = speed;
        }
        int category = pRecord->mUnknown9;
        if (pRecord->mUnknown10 != 3) {
            category = !(p->mUnknown528.mUnknown0 <= 0.65f) ? 2 : 1;
        }
        if (category != pRecord->mUnknown9) {
            if (pRecord->mUnknown4 == -1 || !p->mpUnknown800[pRecord->mUnknown4].mUnknown1) {
                if (pRecord->mUnknown4 != -1 && p->mpUnknown800[pRecord->mUnknown4].mUnknown8 == key) {
                    fn_801BA384((Object_801BA03C *)pA, pEntries, pRecord->mUnknown4);
                }
                int next = fn_801BA2D0(pA, pEntries, &pEntries[pRecord->mUnknown0]);
                pRecord->mUnknown4 = pRecord->mUnknown0;
                fn_801BF4A8(&pEntries[pRecord->mUnknown0].mUnknown30, 16, -1.0f, 0.0f);
                pRecord->mUnknown9 = category;
                pRecord->mUnknown0 = next;
                p->mUnknown1008.mUnknown0 = pRecord->mUnknown8;
                p->mUnknown1008.mUnknown1 = pRecord->mUnknown9;
                p->mUnknown1008.mUnknown2 = pRecord->mUnknown10;
                int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
                fn_801BA418(pA, pEntries, pRecord->mUnknown0, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p);
                fn_801BF3C8(&pEntries[pRecord->mUnknown0].mUnknown30, 0, 0.0f, 0, 0.0f);
                fn_801BF4A8(&pEntries[pRecord->mUnknown0].mUnknown30, 16, -1.0f, 1.0f);
            }
        }
        float rate = p->mUnknown528.mUnknown0;
        if (!(rate >= 0.01f)) {
            rate = 0.01f;
        }
        if (pRecord->mUnknown10 != 3) {
            if (pRecord->mUnknown9 == 1) {
                rate *= 1.5384615659713745f;
            } else if (!(rate >= 0.65f)) {
                rate = 0.65f;
            }
        }
        fn_801BD81C(&pEntries[pRecord->mUnknown0].mUnknown4C, fn_801CFFA0(rate));
        p->mpUnknown800[pRecord->mUnknown0].mUnknown2C = 1.5f;
        break;
    }
    }
    return 0;
}

extern "C" int fn_800DCC14(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DCC14 *pRecord = (Record_800DCC14 *)fn_801BE60C(p->mpUnknown792, key);
    Object_801BBD5C *pObject;
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        pObject = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        int index = fn_800DC674(pObject, p);
        pRecord->mUnknown4 = 1.0f;
        unsigned char *pEntry = (unsigned char *)&pTable->mEntries[index];
        fn_800DA814((Object_800DA8D8 *)pObject, (Block_801BE60C *)pRecord, p, pEntry[1], (signed char)index, key, (Record_8036B55C *)pA, pEntries);
        pRecord->mUnknown12 = index;
        fn_800DC6A8(pObject, p, index, pRecord, (int)pEntries);
        pRecord->mUnknown16 = 0;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) != key) {
            break;
        }
        pObject = fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        if (pRecord->mUnknown16 <= 0) {
            int index = fn_800DC674(pObject, p);
            if (index != pRecord->mUnknown12) {
                pRecord->mUnknown12 = index;
                pRecord->mUnknown16 = 8;
                unsigned char *pEntry = (unsigned char *)&pTable->mEntries[index];
                fn_800DA8D8((Object_800DA8D8 *)pObject, (Block_801BE60C *)pRecord, p, pEntry[1], (signed char)index, key, pA, pEntries, 8);
            }
        }
        if (pRecord->mUnknown16 > 0) {
            --pRecord->mUnknown16;
            fn_800DAC78((Block_801BE60C *)pRecord, 8.0f, pRecord->mUnknown16);
            fn_800DAC88((Block_801BE60C *)pRecord, pA, pEntries);
        } else {
            pRecord->mUnknown16 = 0;
            pRecord->mUnknown4 = 1.0f;
        }
        fn_800DC6A8(pObject, p, pRecord->mUnknown12, pRecord, (int)pEntries);
        break;
    }
    return 0;
}

extern "C" int fn_800DCE2C(Object_80039F5C *p, unsigned char *pInfo)
{
    Point_8017886C point = fn_80177FE0();
    int result = 0;
    unsigned int chance;
    switch (pInfo[3]) {
    case 1: chance = 100; break;
    case 2: chance = 70; break;
    case 3: chance = 50; break;
    case 4: chance = 25; break;
    case 5: chance = 5; break;
    default: chance = 0; break;
    }
    if ((unsigned int)fn_802372EC(0, 100) >= chance) {
        return result;
    }
    unsigned char role = p->mUnknown2914;
    int check = 0;
    if (fn_80177F70()) {
        switch (pInfo[0]) {
        case 1: result = 1; check = 1; break;
        case 12:
            if ((unsigned int)(role - 1) <= 1) {
                result = !(fabsf(point.mX - p->mMotion.mPos.mX) >= 6.0f) ? 2 : 1;
                check = 1;
            }
            if ((unsigned int)(role - 13) <= 2) {
                if (fn_80178308() == p->mIdBytes[2]) {
                    result = 0; check = 0;
                } else {
                    result = 2; check = 1;
                }
            }
            if (role == 16 || role == 18 || role == 17) {
                result = 2; check = 1;
            }
            break;
        case 7:
            if (p->mIdBytes[2] == fn_80178320()) { result = 2; check = 1; }
            break;
        case 4:
            if (role == 5 || role == 9 || role == 6 || role == 8 || role == 7 || role == 4 || role == 24) {
                result = !(fabsf(point.mX - p->mMotion.mPos.mX) >= 6.0f) ? 2 : 1;
                check = 1;
            }
            break;
        case 5:
            if (role == 3) {
                if (!(fabsf(point.mY - p->mMotion.mPos.mY) >= 3.0f)) { result = 2; check = 1; }
            } else if ((unsigned int)(role - 1) <= 1 || role == 4 || role == 25) {
                if (!(fabsf(point.mX - p->mMotion.mPos.mX) <= 6.0f)) { result = 2; check = 1; }
            }
            break;
        case 6:
            if (role == 7 || role == 24) { result = 3; check = 1; }
            break;
        }
    } else if (p->mIdBytes[2] == fn_80178308() && fn_801787A0()) {
        if (pInfo[0] == 8) {
            result = 3;
            switch (pInfo[2]) {
            case 2:
                if (!(p->mMotion.mPos.mX <= point.mX + 0.25f)) result = 0;
                break;
            case 3:
                if (!(p->mMotion.mPos.mX >= point.mX + 0.25f)) result = 0;
                break;
            case 4:
                if (p->mIdBytes[2] == 1) result = 0;
                break;
            case 7:
                result = 0;
                break;
            }
        }
    } else if (pInfo[0] == 2) {
        result = 3; check = 1;
    }
    if (check == 1) {
        fn_80178308();
        int valid = 1;
        switch (pInfo[2]) {
        case 2:
            if (role != 7 && role != 24 && !(p->mMotion.mPos.mX < point.mX + 0.25f) &&
                !(p->mMotion.mPos.mY < point.mY - 3.0f)) valid = 0;
            break;
        case 3:
            if (role == 7 || role == 24 || p->mMotion.mPos.mX < point.mX + 0.25f) {
                valid = 0;
            } else if (!(p->mMotion.mPos.mY >= point.mY - 3.0f)) {
                valid = 0;
            }
            break;
        case 7:
            valid = 0;
            if (!(p->mMotion.mPos.mY - point.mY >= 2.5f)) {
                valid = fabsf(p->mMotion.mPos.mX - point.mX) > 9.0f;
            }
            break;
        }
        if (!valid) result = 0;
    }
    return result;
}

extern "C" int fn_800DD2E8(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DD2E8 *pRecord = (Record_800DD2E8 *)fn_801BE60C(p->mpUnknown792, key);
    int found = 0;
    int chosen = -1;
    int score = 0;
    int update = 0;
    switch (mode) {
    case 0:
        pRecord->mUnknown0 = 5;
        fn_801BE760(p->mpUnknown792, key, 1);
        pRecord->mUnknown2 = 0xFFFF;
        update = 1;
    case 2:
        if (p->mFlags & 4) {
            if (fn_80177F70()) p->mFlags |= 0x40000;
            p->mFlags &= ~0x10;
            update = 1;
        }
        break;
    case 1:
        update = 1;
        break;
    }
    if (update == 1) {
        unsigned char category = 1;
        if (p->mUnknown16 != 2 && p->mUnknown108 != 2 && p->mUnknown200 != 2 && fn_801787A0() == 1) {
            --pRecord->mUnknown0;
            if (pRecord->mUnknown0 & 0x8000) {
                pRecord->mUnknown0 = 5;
                category = 0;
            }
        }
        while (!found) {
            int type = category ? 1 : 2;
            for (int i = 0; i < pTable->mCount; ++i) {
                unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
                if (pInfo[5] == type) {
                    int value = fn_800DCE2C(p, pInfo + 4);
                    if (value >= score && value > 0) {
                        if (score != value || (unsigned int)fn_802372EC(0, 100) <= 49) {
                            if (score != value) score = value;
                            chosen = i;
                        }
                    }
                }
            }
            if (chosen != -1) {
                found = 1;
            } else {
                ++category;
                if (category == 2) { chosen = 0; break; }
            }
        }
        int blend = pRecord->mUnknown6 ? 20 : 10;
        unsigned short old = pRecord->mUnknown2;
        if (old != 0xFFFF && pEntries[old].mUnknown1 == 2 && pEntries[old].mUnknown8 == key) {
            fn_801BF4A8(&pEntries[old].mUnknown30, blend, -1.0f, 0.0f);
        }
        unsigned char *pInfo = (unsigned char *)pTable->mEntries[chosen].mpInfo;
        pRecord->mUnknown6 = pInfo[5] == 2;
        pRecord->mUnknown4 = pInfo[4];
        p->mFlags &= ~4;
        pRecord->mUnknown2 = fn_801BA2A8(pA, pEntries, pTable->mEntries[chosen].mUnknown0, pTable->mEntries[chosen].mUnknown2, key, p, 1.0f);
        if (old != 0xFFFF) {
            fn_801BF4A8(&pEntries[pRecord->mUnknown2].mUnknown30, blend, 0.0f, 1.0f);
        }
    }
    return 0;
}

extern "C" int fn_800DD5E4(Object_80039F5C *p)
{
    int result = 0;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        result = ((Record_800DD5E4 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown6 == 1;
    }
    return result;
}

extern "C" int fn_800DD648(Object_80039F5C *p)
{
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (key >= 85 && key <= 86) {
        return ((Record_800DD648 *)fn_801BE60C(p->mpUnknown792, key))->mUnknown4;
    }
    return 0;
}

extern "C" int fn_800DD69C(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode)
{
    if (mode == 0) {
        fn_8009BD60(p);
        Point_8017886C point = fn_80177FE0();
        if (point.mY - p->mMotion.mPos.mY > 2.5f || fn_801486A0() == 3 || fn_801486A0() == 2) {
            p->mUnknown1008.mUnknown0 = 2;
        } else {
            p->mUnknown1008.mUnknown0 = 1;
        }
        int index = fn_8009C56C(pTable, (unsigned char *)&p->mUnknown1008);
        fn_801BA2A8(pA, pB, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
    }
    return 0;
}

extern "C" int fn_800DD780(Object_80039F5C *p, int value, unsigned short key)
{
    int result = 1;
    if (fn_8002894C()) {
        unsigned char i;
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
            if (pOther != p) {
                Record_800DD780 *pRecord = (Record_800DD780 *)fn_801BE60C(pOther->mpUnknown792, key);
                if (pRecord && pRecord->mUnknown16 == value && pRecord->mUnknown0 <= 59) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800DD830(void *p) {
    return 1;
}

extern "C" int fn_800DD838(Object_80039F5C *p)
{
    int result = p->mUnknown1008Word;
    if (result == -1) {
        result = 2;
        switch (fn_800AD9B4()) {
        case 5:
            result = 30;
            if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 0 && p->mIdBytes[1] == 0) {
                result = 94;
            } else {
                result |= 32;
            }
            if (fn_80137C48(p)) {
                result &= ~8;
            }
            break;
        case 1:
        case 10:
            result |= 12;
            break;
        case 2:
            result = 2;
            break;
        case 4:
        case 9:
            result |= 28;
            if (p->mUnknown2914 == 19 || p->mUnknown2914 == 20 || fn_80137C48(p)) {
                result &= ~8;
            }
            break;
        }
    }
    return result;
}

extern "C" void fn_800DD92C(Table_80089904 *pTable, unsigned short a, unsigned char value)
{
    unsigned char values[4];
    values[0] = value;
    values[1] = 255;
    values[2] = 255;
    values[3] = 255;
    fn_801BBC3C(a, pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF, pTable);
}

extern "C" void fn_800DD994(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, void *pA, void *pB,
                            Object_80039F5C *pOther, Record_800DDCE4 *pRecord, int mask)
{
    unsigned short weights[32];
    int total = 0;
    fn_800DD92C(pTable, p->mpUnknown796->mUnknown2, pRecord->mUnknown12);
    for (int i = 0; i < pTable->mCount; ++i) {
        unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
        int weight;
        switch (pInfo[4]) {
        case 1: weight = 100; break;
        case 2: weight = 50; break;
        case 3: weight = 20; break;
        case 4: weight = 10; break;
        case 5: weight = 5; break;
        default: weight = 0; break;
        }
        unsigned int shift = pInfo[5];
        unsigned int bit = (shift & 63) < 32 ? 1u << (shift & 31) : 0;
        if (!(mask & bit)) {
            weight = 0;
        } else if (shift == 5) {
            weight <<= 2;
        } else if (shift == 6) {
            weight <<= 3;
        }
        if (pInfo[6] != 1 && !fn_800DD830(p)) weight = 0;
        weights[i] = weight;
        total += weight;
    }
    unsigned short chosen = fn_802372EC(0, pTable->mCount);
    if (chosen >= pTable->mCount) chosen = pTable->mCount - 1;
    int i = 0;
    while (i < pTable->mCount) {
        if (fn_800DD780(p, (unsigned char)chosen, key)) {
            unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
            pRecord->mUnknown8 = pInfo[5];
            *((unsigned char *)pRecord + 16) = chosen;
            pRecord->mUnknown9 = pInfo[7] == 2;
            break;
        }
        chosen = chosen == pTable->mCount - 1 ? 0 : (unsigned short)(chosen + 1);
        ++i;
    }
    if (i == pTable->mCount) {
        chosen = fn_802372EC(0, i);
        if (chosen >= pTable->mCount) {
            unsigned char *pInfo = (unsigned char *)pTable->mEntries[i].mpInfo;
            chosen = pTable->mCount - 1;
            pRecord->mUnknown8 = pInfo[5];
            *((unsigned char *)pRecord + 16) = chosen;
            pRecord->mUnknown9 = pInfo[7] == 2;
        }
    }
    fn_802372EC(0, total);
    unsigned short old = pRecord->mUnknown14;
    Record_800D81C8 *pEntries = (Record_800D81C8 *)pB;
    if (old != 0xFFFF && !fn_80027DF0()) {
        fn_801BF4A8(&pEntries[old].mUnknown30, 10, -1.0f, 0.0f);
    }
    p->mFlags &= ~4;
    pRecord->mUnknown14 = fn_801BA2A8(pA, pB, pTable->mEntries[chosen].mUnknown0, pTable->mEntries[chosen].mUnknown2, key, pOther, 1.0f);
    if (fn_80027DF0()) {
        fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    }
    unsigned char *pInfo = (unsigned char *)pTable->mEntries[chosen].mpInfo;
    pRecord->mUnknown10 = pInfo[6];
    if (old != 0xFFFF && !fn_80027DF0()) {
        fn_801BF4A8(&pEntries[(unsigned short)pRecord->mUnknown14].mUnknown30, 16, 0.0f, 1.0f);
    }
}

extern "C" void fn_800DDCE4(Object_80039F5C *p, Record_800DDCE4 *pRecord)
{
    if (p->mIdBytes[3] == 1) {
        if (pRecord->mUnknown9) {
            fn_8009D1F4(p);
        } else {
            fn_8009D1AC(p);
        }
    }
}

extern "C" int fn_800DDD24(Table_80089904 *pTable, unsigned short key, void *pA, void *pB, Object_80039F5C *p, unsigned int mode)
{
    Record_800DDCE4 *pRecord = (Record_800DDCE4 *)fn_801BE60C(p->mpUnknown792, key);
    int mask;
    pRecord->mUnknown13 = 0;
    mask = pRecord->mUnknown4;
    switch (mode) {
    case 0:
        pRecord->mUnknown0 = 0;
        pRecord->mUnknown14 = -1;
        pRecord->mUnknown8 = 0;
        pRecord->mUnknown10 = 0;
        pRecord->mUnknown12 = 1;
        mask = pRecord->mUnknown4 = fn_800DD838(p);
        fn_801BE760(p->mpUnknown792, key, 1);
        pRecord->mUnknown13 = 1;
        break;
    case 1:
        break;
    case 2:
        pRecord->mUnknown0++;
        if (key == fn_801BE648(p->mpUnknown792) && (p->mFlags & 4)) {
            pRecord->mUnknown13 = 1;
        }
        fn_800DDCE4(p, pRecord);
        break;
    case 3:
        if (p->mIdBytes[3] == 1) {
            fn_8009D1AC(p);
        }
        break;
    }
    if (pRecord->mUnknown13) {
        fn_800DD994(pTable, p, key, pA, pB, p, pRecord, mask);
    }
    return 0;
}

extern "C" void fn_800DDE6C(Object_80039F5C *p)
{
    fn_8009BD60(p);
    if (p->mIdBytes[3] != 1 && fn_80137C48(p)) {
        p->mUnknown1008.mUnknown0 = 1;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    if (p->mIdBytes[3] == 1) {
        if (p->mUnknown512.mUnknown14 == 7) {
            p->mUnknown1008.mUnknown1 = 3;
        } else {
            p->mUnknown1008.mUnknown1 = 2;
        }
    }
}

extern "C" int fn_800DDEE4(unsigned char *pA, unsigned char *pB)
{
    unsigned char i;
    int result = 1;
    for (i = 0; i < 2; i++) {
        if (pB[i] != 255 && pA[i] != pB[i]) {
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" unsigned short fn_800DDF34(Table_80089904 *pTable, Object_80039F5C *p, unsigned short key, int *pAngle, float *pTime, float *pRate)
{
    int facing = p->mMotion.mFacing & 0xFFFFFF;
    int desired = p->mUnknown512.mUnknown8 & 0xFFFFFF;
    *pAngle = 0;
    *pTime = 1.0f;
    *pRate = 1.0f;
    int difference = fn_801CFFD0(facing, desired);
    int direction = ((desired - facing) & 0xFFFFFF) > 0x800000 ? -1 : 1;
    Info_800DDF34 *pChosen = 0;
    unsigned int chosen = 0;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        Info_800DDF34 *pInfo = (Info_800DDF34 *)pTable->mEntries[i].mpInfo;
        if (fn_800DDEE4(pInfo->mUnknown4, (unsigned char *)&p->mUnknown1008) &&
            difference >= pInfo->mUnknown16 && difference <= pInfo->mUnknown20 &&
            ((direction > 0 && pInfo->mUnknown12 > 0) || (direction < 0 && pInfo->mUnknown12 < 0))) {
            if (!pChosen || (unsigned int)fn_802372EC(0, 100) <= 49) {
                pChosen = pInfo;
                chosen = i;
            }
        }
    }
    if (pChosen && chosen < pTable->mCount) {
        if (key == 100 || p->mIdBytes[3] != 1) {
            *pRate = (float)(pChosen->mUnknown12 < 0 ? -pChosen->mUnknown12 : pChosen->mUnknown12) / (float)difference;
            if (!(*pRate >= 1.0f)) {
                *pRate = 1.0f;
            }
        }
        *pRate *= p->mUnknown512.mUnknown0;
        int magnitude = pChosen->mUnknown12 < 0 ? -pChosen->mUnknown12 : pChosen->mUnknown12;
        *pAngle = fn_801CFFD0(magnitude, difference);
        if ((((facing + pChosen->mUnknown12) & 0xFFFFFF) - desired & 0xFFFFFF) <= 0x7FFFFF) {
            *pAngle = -*pAngle;
        }
        *pTime = pChosen->mUnknown24;
        *pTime /= *pRate;
    } else {
        chosen = 0;
    }
    return chosen;
}

extern "C" int fn_800DE19C(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Record_800DE19C *pRecord = (Record_800DE19C *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        if (p->mIdBytes[3] != 1 || key == 100) {
            fn_800DDE6C(p);
        }
        int angle;
        float time, rate;
        int index = fn_800DDF34(pTable, p, key, &angle, &time, &rate);
        int entry = fn_801BA2A8(pA, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        pRecord->mUnknown0 = entry;
        fn_801BD81C(&pEntries[entry].mUnknown4C, fn_801CFFA0(rate));
        pRecord->mUnknown4 = (int)((float)angle / time);
        p->mFlags &= ~4;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            p->mMotion.mFacing = (p->mMotion.mFacing + pRecord->mUnknown4) & 0xFFFFFF;
            Record_800D81C8 *pEntry = &p->mpUnknown800[pRecord->mUnknown0];
            pEntry->mUnknownC = (pEntry->mUnknownC + pRecord->mUnknown4) & 0xFFFFFF;
            if (p->mFlags & 4) {
                p->mMotion.mFacing &= 0xFFFFFF;
                pRecord->mUnknown4 = 0;
            }
        }
        break;
    }
    return 0;
}

extern "C" int fn_800DE364(unsigned int id)
{
    int result = 1;
    switch (id) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
    case 173:
        result = 0;
    }
    return result;
}

extern "C" void fn_800DE3B0(Block_800DE3B0 *pBlock, Object_80039F5C *p, Command_800DE3B0 *pCommand)
{
    int desired = fn_801CFE40(pCommand->mUnknown0.mUnknown4, pCommand->mUnknown0.mUnknown0) & 0xFFFFFF;
    State_800DE3B0 *pState = (State_800DE3B0 *)p->mUnknown1160.mUnknown12;
    int original = pState->mUnknown0 & 0xFFFFFF;
    Pair_802270A4 old = pState->mUnknown4;
    signed char frames = (int)(lbl_803EAD20 * pCommand->mUnknown18);
    if (frames < 1) {
        frames = 1;
    }
    pBlock->mUnknown3E = frames;
    pBlock->mUnknown38 = (original - desired) & 0xFFFFFF;
    if (pBlock->mUnknown38 > 0x800000) {
        pBlock->mUnknown38 -= 0x1000000;
    }
    pState->mUnknown1C = (p->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
    pState->mUnknown14.mUnknown0 = p->mMotion.mPos.mX;
    pState->mUnknown14.mUnknown4 = p->mMotion.mPos.mY;
    pBlock->mUnknown38 /= pBlock->mUnknown3E;
    pBlock->mUnknown3F = (int)(pCommand->mUnknown18 - (float)pBlock->mUnknown3E);
    pBlock->mUnknown4 = pCommand->mUnknownC;
    if (pState->mUnknown12 == 1) {
        fn_80227690(&pBlock->mUnknownC, &pBlock->mUnknown4, &p->mMotion);
        pBlock->mUnknown14 = desired;
    } else {
        fn_80227690(&pBlock->mUnknownC, &p->mMotion, &old);
        pBlock->mUnknown14 = original;
    }
}

extern "C" void fn_800DE51C(Object_80039F5C *p, Block_800DE3B0 *pBlock, int id)
{
    Table_80089904 *pTable = fn_801BE72C(p->mpUnknown796->mUnknown2, fn_801BE648(p->mpUnknown792));
    Entry_800DE51C *pChosen = 0, *pFallback = 0;
    int fallbackKey = 0;
    pBlock->mUnknown3F = pBlock->mUnknown3E = -1;
    for (unsigned int i = 0; i < pTable->mCount; i++) {
        int key = pTable->mEntries[i].mUnknown2 & 0x7FFF;
        Table_800DE51C *pRecords = (Table_800DE51C *)fn_801BBD5C(key, p->mpUnknown796->mUnknown2);
        for (unsigned int j = 0; j < pRecords->mCount; j++) {
            Entry_800DE51C *pEntry = &pRecords->mEntries[j];
            if (!pEntry->mUnknown2) {
                pChosen = pEntry;
                if (pEntry->mUnknown0 == id) break;
            } else if (pEntry->mUnknown2 == 1 && pEntry->mUnknown0 == id) {
                fallbackKey = key;
                for (signed char k = 0; k < pRecords->mCount; k++) {
                    if (!pRecords->mEntries[k].mUnknown2) pFallback = &pRecords->mEntries[k];
                }
            }
        }
        if (pChosen->mUnknown0 == id) break;
        pChosen = 0;
    }
    if (pChosen && pChosen->mUnknown0 == id) {
        pBlock->mUnknown1C = 1;
        Object_80039F5C *pOther = 0;
        switch (p->mpState->mId) {
        case 16:
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (p->mUnknown776 == 1) pBlock->mUnknown1F = 1;
            break;
        case 17:
            pOther = fn_80039F5C((unsigned char)(1-p->mIdBytes[2]), p->mpState->mUnknown3[0]);
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (pOther->mUnknown776 == 1) pBlock->mUnknown1F = 1;
            break;
        case 32:
            if (p->mUnknown1036) pOther = fn_80039F5C((p->mUnknown1036 >> 8) & 255, p->mpState->mUnknown3[0]);
            else if (fn_801486A0() == 0 || fn_801486A0() == 1) pOther = fn_80039F5C(p->mIdBytes[2], p->mpState->mUnknown3[0]);
            else pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
            if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
            break;
        case 27: case 52: pOther = fn_80137B40(); break;
        default:
            if (p->mIdBytes[3] == 1) {
                int state = p->mUnknown1032;
                if (state == 4 || state == 5 || state == 2 || state == 8) {
                    pOther = fn_8009BCE8(&p->mUnknown1036);
                    if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
                } else if (state == 7) {
                    pOther = p;
                    if (pOther->mUnknown1128[4] & 2) pBlock->mUnknown1F = 1;
                }
            }
        }
        pBlock->mUnknownC.mUnknown0 = pBlock->mUnknownC.mUnknown4 = 0.0f;
        fn_800CEDA4(pChosen, &pBlock->mUnknown4, &pBlock->mUnknown14, pOther, pBlock->mUnknown1F);
        pBlock->mUnknown0 = 0.0f;
    } else {
        if (p->mpState->mId == 16) {
            if (((unsigned char *)&p->mUnknown1160)[56]) pBlock->mUnknown1F = ((unsigned char *)&p->mUnknown1160)[55];
            else if (p->mUnknown776 == 1) pBlock->mUnknown1F = 1;
        } else if (p->mpState->mId == 32 && (p->mUnknown1128[4] & 2)) pBlock->mUnknown1F = 1;
        Pair_802270A4 point;
        int angle;
        pBlock->mUnknown1C = 0;
        fn_800CEDA4(pFallback, &point, &angle, p, pBlock->mUnknown1F);
        fn_800DEAB0(p, pBlock, fallbackKey, &point, angle, pFallback);
    }
}

extern "C" void fn_800DE910(Object_80039F5C *p, Block_800DE3B0 *pBlock)
{
    Record_800D81C8 *pEntry = &p->mpUnknown800[pBlock->mUnknown1D];
    pBlock->mUnknown0 += 0.03333333507180214f;
    if (!(pBlock->mUnknown0 < 1.0f)) {
        pBlock->mUnknown1C = 0;
        pBlock->mUnknown0 = 1.0f;
        pEntry->mUnknownC = pBlock->mUnknown14;
    }
    Pair_802270A4 delta;
    fn_80227384(&delta, p->mUnknown552, -pEntry->mUnknownC);
    fn_80227638(&pBlock->mUnknownC, &delta, &pBlock->mUnknownC);
    fn_80227384(&delta, &pBlock->mUnknownC, pBlock->mUnknown14);
    fn_80227638(&delta, &delta, &pBlock->mUnknown4);
    p->mMotion.mPos.mX = (delta.mUnknown0 - p->mMotion.mPos.mX) * pBlock->mUnknown0 + p->mMotion.mPos.mX;
    p->mMotion.mPos.mY = (delta.mUnknown4 - p->mMotion.mPos.mY) * pBlock->mUnknown0 + p->mMotion.mPos.mY;
    int desired = (pBlock->mUnknown14 + pEntry->mUnknown1C) & 0xFFFFFF;
    int angle = (int)((float)fn_801CFFD0(desired, p->mMotion.mFacing) * pBlock->mUnknown0);
    if (((p->mMotion.mFacing - desired) & 0xFFFFFF) <= 0x7FFFFF) {
        p->mMotion.mFacing = (p->mMotion.mFacing - angle) & 0xFFFFFF;
        pEntry->mUnknownC = (pEntry->mUnknownC - angle) & 0xFFFFFF;
    } else {
        p->mMotion.mFacing = (p->mMotion.mFacing + angle) & 0xFFFFFF;
        pEntry->mUnknownC = (pEntry->mUnknownC + angle) & 0xFFFFFF;
    }
}

extern "C" void fn_800DEAB0(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key, void *pData, int angle, Entry_800DE51C *pRecord)
{
    int active = fn_801BE648(p->mpUnknown792);
    unsigned char table[3048];
    union { Command_800CEE74 command; Command_800DE3B0 view; } command;
    switch (active) {
    case 181: case 186:
        fn_801BBC3C(1, key, (Table_80089904 *)table);
        fn_800CEE74(&command.command, p, fn_8009BCE8(&p->mUnknown336), pData, angle, (unsigned short)key, pBlock->mUnknown1F);
        fn_800CE804(&command.command, (Table_80089904 *)table, 0);
        fn_800DE3B0(pBlock, p, &command.view);
        break;
    case 195: case 196: case 197: case 210: case 224: case 228: case 229: case 230: case 235: case 237:
        fn_801BBC3C(1, key, (Table_80089904 *)table);
        fn_800CEE74(&command.command, p, 0, 0, 0, (unsigned short)key, pBlock->mUnknown1F);
        fn_800CE804(&command.command, (Table_80089904 *)table, pRecord->mUnknown0);
        fn_800DE3B0(pBlock, p, &command.view);
        break;
    }
}

extern "C" void fn_800DEC10(Object_80039F5C *p, Block_800DE3B0 *pBlock)
{
    State_800DE3B0 *pState = (State_800DE3B0 *)p->mUnknown1160.mUnknown12;
    Record_800D81C8 *pEntry = &p->mpUnknown800[pBlock->mUnknown1D];
    Object_80039F5C *pOther = 0;
    Record_800D81C8 *pOtherEntry = 0;
    Block_801BE60C *pOtherBlock = 0;
    int index = 0xFFFF;
    unsigned short key = (unsigned short)pBlock->mUnknown18;
    if (fn_801BE648(p->mpUnknown792) == 181 || fn_801BE648(p->mpUnknown792) == 186) {
        pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
        index = fn_801BA5A8(pOther->mpUnknown796, pOther->mpUnknown800, key, 0);
    }
    Pair_802270A4 point = pState->mUnknown4;
    if (index != 0xFFFF) {
        pOtherEntry = &pOther->mpUnknown800[index];
        pOtherBlock = fn_801BE60C(pOther->mpUnknown792, key);
    }
    Pair_802270A4 rotated, delta, offset;
    if (pBlock->mUnknown3E > 0) {
        --pBlock->mUnknown3E;
        if (pState->mUnknown12 == 1) {
            fn_80227384(&rotated, &pBlock->mUnknownC, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &pBlock->mUnknownC);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            pBlock->mUnknownC = rotated;
            pBlock->mUnknown14 += pBlock->mUnknown38;
        } else {
            fn_80227690(&delta, &pBlock->mUnknown4, &point);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &delta);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            fn_80227384(&rotated, &pBlock->mUnknownC, pBlock->mUnknown38);
            fn_80227690(&delta, &rotated, &pBlock->mUnknownC);
            pBlock->mUnknownC = rotated;
            fn_80227638(&p->mMotion, &p->mMotion, &delta);
            if (index != 0xFFFF) {
                fn_80227638(&pOther->mMotion, &pOther->mMotion, &delta);
                Point_8017886C adjustment = {delta.mUnknown0, delta.mUnknown4};
                fn_800DF134(pOther, adjustment, 0, pBlock->mUnknown18);
            }
        }
        p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
        p->mpUnknown800[pBlock->mUnknown1D].mUnknownC = (pEntry->mUnknownC + pBlock->mUnknown38) & 0xFFFFFF;
        if (index != 0xFFFF) {
            fn_80227690(&delta, &pOther->mMotion, &p->mMotion);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227638(&pOther->mMotion, &rotated, &p->mMotion);
            pOther->mMotion.mFacing = (pOther->mMotion.mFacing + pBlock->mUnknown38) & 0xFFFFFF;
            pOtherEntry->mUnknownC = (pOtherEntry->mUnknownC + pBlock->mUnknown38) & 0xFFFFFF;
            fn_80227690(&delta, &pOtherBlock->mUnknown4, &p->mMotion);
            fn_80227384(&rotated, &delta, pBlock->mUnknown38);
            fn_80227690(&offset, &rotated, &delta);
            Point_8017886C adjustment = {offset.mUnknown0, offset.mUnknown4};
            fn_800DF134(pOther, adjustment, pBlock->mUnknown38, pBlock->mUnknown18);
        }
    } else if (pBlock->mUnknown3E == 0) {
        --pBlock->mUnknown3E;
        if (pState->mUnknown12 == 1) {
            fn_80227384(&rotated, (char *)pEntry + 36, pState->mUnknown1C);
            fn_80227690(&delta, &p->mMotion, &pState->mUnknown14);
            fn_80227690(&delta, &delta, &rotated);
            fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &delta);
            fn_80227690(&pBlock->mUnknownC, &point, &pBlock->mUnknown4);
        } else {
            fn_80227690(&pBlock->mUnknownC, &point, &pBlock->mUnknown4);
        }
        pBlock->mUnknownC.mUnknown0 /= (float)pBlock->mUnknown3F;
        pBlock->mUnknownC.mUnknown4 /= (float)pBlock->mUnknown3F;
    }
    if (pBlock->mUnknown3E < 0 && pBlock->mUnknown3F > 0) {
        --pBlock->mUnknown3F;
        fn_80227638(&pBlock->mUnknown4, &pBlock->mUnknown4, &pBlock->mUnknownC);
        fn_80227638(&p->mMotion, &p->mMotion, &pBlock->mUnknownC);
        if (index != 0xFFFF) {
            fn_80227638(&pOther->mMotion, &pOther->mMotion, &pBlock->mUnknownC);
            Point_8017886C adjustment = {pBlock->mUnknownC.mUnknown0, pBlock->mUnknownC.mUnknown4};
            fn_800DF134(pOther, adjustment, 0, pBlock->mUnknown18);
        }
    }
    if (pBlock->mUnknown3F == 0) {
        --pBlock->mUnknown3F;
        Vector_80039F5C position = {pBlock->mUnknown4.mUnknown0, pBlock->mUnknown4.mUnknown4, pBlock->mUnknownC.mUnknown0};
        if (fn_801784C4()) {
            position.mX = -position.mX;
            position.mY = -position.mY;
        }
        float distance;
        void *pSurface = fn_80040FD4(&position, 7, &distance);
        if (pSurface && !(distance >= 1.6f)) fn_800538E0(pSurface, p);
    }
}

extern "C" void fn_800DF134(Object_80039F5C *p, Point_8017886C offset, int angle, int key)
{
    if (key == fn_801BE648(p->mpUnknown792)) {
        Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
        if (pRecord) {
            if (pRecord->mUnknown1C) {
                pRecord->mUnknown4 += offset.mX;
                pRecord->mUnknown14 = (pRecord->mUnknown14 + angle) & 0xFFFFFF;
                pRecord->mUnknown8 += offset.mY;
            }
            p->mpUnknown800[pRecord->mUnknown1D].mUnknownC =
                (p->mpUnknown800[pRecord->mUnknown1D].mUnknownC + angle) & 0xFFFFFF;
        }
    }
}

extern "C" int fn_800DF1F4(Table_80089904 *pTable, unsigned short key, void *pData, Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int mode)
{
    Block_800DE3B0 *pBlock = (Block_800DE3B0 *)fn_801BE60C(p->mpUnknown792, key);
    switch (mode) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        int first = p->mUnknown1008.mUnknown0 | (p->mUnknown1008.mUnknown1 << 8);
        int second = p->mUnknown1008.mUnknown2 | (p->mUnknown1011 << 8);
        pBlock->mUnknown1D = fn_801BA2A8(pData, pEntries, second, first, key, p, 1.0f);
        pBlock->mUnknown18 = key;
        if (fn_800DE364(key)) p->mFlags |= 512;
        bool excluded = (key >= 49 && key <= 55) || key == 59 || key == 60 || key == 106 || key == 107;
        if (key == 172 || key == 173) {
            for (unsigned short i = 0; i < pTable->mCount; i++) {
                if (pTable->mEntries[i].mUnknown0 == second) {
                    Table_800DE51C *pRecords = (Table_800DE51C *)fn_801BBD5C(pTable->mEntries[i].mUnknown2 & 0x7FFF, p->mpUnknown796->mUnknown2);
                    if (pRecords->mEntries[0].mUnknown0 == first || pRecords->mEntries[1].mUnknown0 == first) {
                        pBlock->mUnknown3C = ((unsigned char *)pTable->mEntries[i].mpInfo)[4];
                        break;
                    }
                }
            }
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown336);
            float rate = p->mpState->mId == 16 ? fn_80114EE4(p, pOther) : fn_80114EE4(pOther, p);
            fn_801BD81C(&pEntries[pBlock->mUnknown1D].mUnknown4C, fn_801CFFA0(rate));
        } else if (!excluded && p->mUnknown512.mUnknown14 == 5) {
            float rate = p->mUnknown512.mUnknown0 + 0.8f;
            if (!(rate <= 1.2f)) rate = 1.2f;
            fn_801BD81C(&pEntries[pBlock->mUnknown1D].mUnknown4C, fn_801CFFA0(rate));
        }
        fn_800DE51C(p, pBlock, first);
        if (pBlock->mUnknown1F) {
            Record_800D81C8 *pEntry = &pEntries[pBlock->mUnknown1D];
            fn_801BA6BC(pEntry, !fn_801BA6B0(pEntry));
            pBlock->mUnknown1F = fn_801BA6B0(&pEntries[pBlock->mUnknown1D]);
        }
        fn_800D8140(&pBlock->mUnknown20, p, pBlock->mUnknown1D);
        pBlock->mUnknown1E = fn_801784C4();
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            int orientation = fn_801784C4();
            if (orientation != pBlock->mUnknown1E) {
                pBlock->mUnknown1E = orientation;
                if (pBlock->mUnknown1C) {
                    pBlock->mUnknown4.mUnknown0 = -pBlock->mUnknown4.mUnknown0;
                    pBlock->mUnknown4.mUnknown4 = -pBlock->mUnknown4.mUnknown4;
                    pBlock->mUnknown14 = (pBlock->mUnknown14 + 0x800000) & 0xFFFFFF;
                } else if (key == 181 || key == 186) fn_800DF654(p, (Block_801BE60C *)pBlock);
            }
            if (key == 181 || key == 186) fn_800DEC10(p, pBlock);
            if (pBlock->mUnknown1C) fn_800DE910(p, pBlock);
            if (fn_801BE648(p->mpUnknown792) == 94 || fn_801BE648(p->mpUnknown792) == 95 || fn_801BE648(p->mpUnknown792) == 234) fn_800D84DC(&pBlock->mUnknown20, p);
            else fn_800D81C8(&pBlock->mUnknown20, p);
        } else if (!fn_800DE364(fn_801BE648(p->mpUnknown792))) p->mFlags &= ~512;
        if ((key == 172 || key == 173) && (p->mFlags & 4)) fn_800C854C(p, key, pBlock->mUnknown3C);
        break;
    case 1: case 3:
        pBlock->mUnknown1C = 0;
        if (key == fn_801BE648(p->mpUnknown792) || !fn_800DE364(fn_801BE648(p->mpUnknown792))) p->mFlags &= ~512;
        break;
    }
    return 0;
}

extern "C" void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord)
{
    Block_800DF654 *pBlock = (Block_800DF654 *)p->mUnknown1160.mUnknown12;
    pRecord->mUnknown4 = -pRecord->mUnknown4;
    pRecord->mUnknown8 = -pRecord->mUnknown8;
    pRecord->mUnknownC = -pRecord->mUnknownC;
    pRecord->mUnknown10 = -pRecord->mUnknown10;
    pRecord->mUnknown14 = (pRecord->mUnknown14 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown0 = (pBlock->mUnknown0 + 0x800000) & 0xFFFFFF;
    pBlock->mUnknown4 = -pBlock->mUnknown4;
    pBlock->mUnknown8 = -pBlock->mUnknown8;
    pBlock->mUnknown20 = -pBlock->mUnknown20;
    pBlock->mUnknown24 = -pBlock->mUnknown24;
    pBlock->mUnknown28 = (pBlock->mUnknown28 + 0x800000) & 0xFFFFFF;
}

extern "C" int fn_800DF6EC(Object_80039F5C *p)
{
    int result = 0;
    if (p->mFlags & 0x1000) {
        p->mFlags &= ~0x1000;
        result = 1;
    }
    return result;
}

extern "C" void fn_800DF710(Object_80039F5C *p, int joint, Vector_80039F5C *pPos, Angles_801EBC18 *pAngles)
{
    float rot[4];
    fn_8009BFD0(p, pPos, rot);
    fn_801EBC18(pAngles, rot);
}

extern "C" void fn_800DF750(Object_80137ABC *pBall, Vector_80039F5C *pPos, int *pAngles)
{
    Vector_80039F5C old;
    Vector_80039F5C delta;
    fn_80137D58(pBall, &old);
    fn_802276B4(&delta, pPos, &old);
    fn_80137E74(pBall, &old);
    fn_80137D74(pBall, pPos);
    fn_80137E90(pBall, pAngles);
    fn_80137EE0(pBall, &delta);
}

extern "C" void fn_800DF7CC(Object_80039F5C *p, Character_80093BCC *pCharacter, Attachment_800DF7CC *pAttachments, Frame_800DF7CC *pFrame, int index, unsigned int frame)
{
    float time = (float)frame / fn_801BFFA0(p);
    Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
    fn_80093BAC(pView->mUnknown0, pView->mUnknown4);
    Vector_80039F5C position;
    Angles_801EBC18 angles;
    if (pFrame->mUnknown20 && pFrame->mUnknown20 != 0x4E4F4E45) {
        if (fn_801C065C(pFrame, time) && !fn_800DF6EC(p)) {
            int joint = !pFrame->mUnknown19 || (pView->mFlags & 8) ? 25 : 19;
            fn_800DF710(p, joint, &position, &angles);
            pAttachments[index].mPos = position;
            pAttachments[index].mAngles = angles;
            pAttachments[index].mFrame = frame;
        } else {
            *(int *)(p->mpUnknown4->mUnknown24 + 8) = 0;
            if (pAttachments[index].mFrame != -1) {
                pAttachments[index].mFrame = -1;
                if (pFrame->mUnknown20 == 0x42414C4C) {
                    if (fn_801383B0()) {
                        Object_80137ABC *pBall = pView->mpBall[index];
                        if (pBall) fn_801379B4(pBall, 3, 0);
                    } else {
                        pView->mpUnknown20->mUnknown12 &= ~0x40000;
                    }
                }
            }
        }
        if (pFrame->mUnknown20 == 0x42414C4C && fn_801383B0()) {
            Object_80137ABC *pBall = pView->mpBall[index];
            if (fn_8013BA58(pBall, 0) == 8) fn_800DF750(pBall, &position, (int *)&angles);
        }
    }
}

extern "C" void fn_800DF9FC(Object_80039F5C *p, void *pRecord, unsigned int value) {
}

extern "C" int fn_800DFA00(Object_80039F5C *p, float *pValue)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    if (!pCharacter) return 1;
    Character_800DF7CC *pView = (Character_800DF7CC *)pCharacter;
    Frame_800DF7CC *pFrame = fn_801C029C(fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4), pBlock->mUnknown9);
    p->mpUnknown4->mUnknown20 |= 0x1000;
    unsigned int handle = fn_801BBE5C(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14);
    void *pData = fn_801BC084(handle);
    if (!pData) return 1;
    float value;
    pBlock->mUnknown13 = fn_801BD934(&value, fn_801BAB34(pData, 0), 0x8003) || fn_801BD934(&value, fn_801BAB34(pData, 0), 0x8001);
    *pValue = fn_801BD60C(fn_801BAB34(pData, 0));
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = ((unsigned char *)pCharacter)[3];
    p->mUnknown1008.mUnknown1 = ((unsigned char *)pCharacter)[7];
    p->mUnknown1008.mUnknown2 = pBlock->mUnknown9;
    p->mUnknown1011 = pBlock->mUnknown10;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 10, p, 1.0f);
    if ((pView->mFlags & 32) || p->mIdBytes[3] == 3) fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    if (pView->mFlags & 8) {
        unsigned char count = fn_801BA568(p->mpUnknown796, p->mpUnknown800, 10);
        for (unsigned char i = 0; i < count; i++) {
            Record_800D81C8 *pEntry = &p->mpUnknown800[fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 10, i)];
            fn_801BA6BC(pEntry, !fn_801BA6B0(pEntry));
        }
        fn_800D7A0C(p, p->mUnknown776 == 2 ? 1 : 2);
    }
    if ((pView->mFlags & 16) && fn_801BA568(p->mpUnknown796, p->mpUnknown800, 10)) {
        p->mpUnknown800[fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 10, 0)].mUnknown2C = 1.0f / p->mUnknown768;
    }
    if (handle != 0xFFFFFF) {
        unsigned int other = fn_801BBEC0(handle, 1024);
        if (other != 0xFFFFFF) {
            fn_8009BD60(p);
            unsigned int key = fn_801BBCC8(0, other);
            p->mUnknown1012[1] = key >> 8;
            p->mUnknown1012[0] = key;
            fn_801BE068(p->mpUnknown804, p->mpUnknown808, p->mpUnknown812, 0, p, 1.0f);
        }
    }
    p->mpUnknown4->mUnknown20 |= 16;
    p->mFlags &= ~4;
    p->mFlags &= ~0x1000;
    return 0;
}

extern "C" void fn_800DFCEC(Object_80039F5C *p)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    pBlock->mUnknown8 = p->mpState->mUnknown1;
    pBlock->mUnknown9 = p->mpState->mUnknown2;
    pBlock->mUnknown10 = 0;
    pBlock->mUnknown12 = 0;
    pBlock->mUnknown0 = 0.0f;
    pBlock->mUnknown4 = 0.0f;
    pBlock->mUnknown11 = 0;
    p->mpUnknown4->mUnknown20 |= 0x80;
    if (p->mIdBytes[3] == 1 || p->mIdBytes[3] == 3) {
        fn_8003AB08(p, 0);
        p->mUnknown512.mUnknown14 = 0;
    }
    fn_800DFA00(p, &pBlock->mUnknown4);
}

extern "C" int fn_800DFD90(Object_80039F5C *p)
{
    Character_80093BCC *pCharacter = fn_80093BCC(p->mUnknown344);
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    fn_8003E174(1);
    p->mpUnknown4->mUnknown20 &= ~0x80;
    if (!fn_80027DF0() && fn_800AD9B4() == 7) {
        return 0;
    }
    if (!(pActor->mUnknown8 & 0x40)) {
        if (p->mIdBytes[3] == 3) {
            fn_8009BD60(p);
            p->mUnknown1008.mUnknown0 = 1;
            p->mUnknown1008Word = 6;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, p, 1.0f);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
        } else if (p->mIdBytes[3] == 1) {
            int mode = fn_800AD9B4();
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
            fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            if (mode == 4) {
                fn_8010A2DC(p, 0, -1);
            }
        }
    }
    return 1;
}

extern "C" int fn_800DFED0(Object_80039F5C *p)
{
    Block_800DFCEC *pBlock = (Block_800DFCEC *)&p->mUnknown336;
    Character_80093BCC *pCharacter = fn_80093BCC(pBlock->mUnknown8);
    Attachment_800DF7CC *pAttachments = fn_80093C08(pBlock->mUnknown8);
    if (!pCharacter || !pAttachments) {
        fn_800ADBC0(p, 1, 8, 0);
        fn_800ADBC0(p, 1, 8, 1);
        return 1;
    }
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    Frame_800DF7CC *pFrame = fn_801C029C(pActor, pBlock->mUnknown9);
    fn_800DF9FC(p, pCharacter, (unsigned int)pBlock->mUnknown0);
    fn_800DF7CC(p, pCharacter, pAttachments, pFrame, pBlock->mUnknown9, (unsigned int)pBlock->mUnknown0);
    if (fn_800943B0(pBlock->mUnknown8)) return 0;
    pBlock->mUnknown0 += lbl_803EA2C4;
    if (!(pBlock->mUnknown0 <= pBlock->mUnknown4) && !pBlock->mUnknown13) {
        fn_8009134C(pBlock->mUnknown8);
        p->mpUnknown4->mUnknown20 &= ~0x1000;
        p->mpUnknown4->mUnknown20 &= ~0x80;
        if (!(pActor->mUnknown8 & 64)) {
            if (p->mIdBytes[3] == 3) {
                fn_8009BD60(p);
                p->mUnknown1008.mUnknown0 = 1;
                p->mUnknown1008Word = 6;
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 82, p, 1.0f);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
            } else if (p->mIdBytes[3] == 1) {
                int mode = fn_800AD9B4();
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
                fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
                if (mode == 4) fn_8016DBE4(p);
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
                p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            }
        }
        fn_800ADBC0(p, 1, 8, 0);
        fn_800ADBC0(p, 1, 8, 1);
        return 1;
    }
    return 0;
}

extern "C" int fn_800E0188(Object_80039F5C *p, float *pA, float *pB)
{
    if (p->mIdBytes[3] == 1 && p->mpState->mId == 50) {
        Block_800E0188 *pBlock = (Block_800E0188 *)&p->mUnknown336;
        if (pA) {
            *pA = pBlock->mUnknown0;
        }
        if (pB) {
            *pB = pBlock->mUnknown4;
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_800E01D8(Object_80039F5C *p, Block_800E0230 *pBlock, int a)
{
    if (p == fn_80137B40() && fn_801BE648(p->mpUnknown792) == 74 && fn_801486A0()) {
        fn_80171DB0(p);
    }
}

extern "C" void fn_800E0230(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (fn_802372EC(0, 100) <= 64) {
        pBlock->mUnknown9 = 0;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    } else {
        pBlock->mUnknown9 = 1;
        if (p->mUnknown776 == 2) {
            fn_800E01D8(p, pBlock, 6);
        } else {
            fn_800E01D8(p, pBlock, 3);
        }
    }
}

extern "C" float fn_800E02D0(Object_80039F5C *p)
{
    float value;
    if (fn_80124C28(p, &value, 0x355555, p->mMotion.mFacing, 5.0f, 0.5f)) {
        return (1.0f - value * 0.2f) * 0.5f + 0.5f;
    }
    return 0.5f;
}

extern "C" void fn_800E034C(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.2f || (unsigned char)fn_800B9A90(lbl_803EAB84) != 1) {
        pBlock->mUnknown8 = 0;
        pBlock->mUnknown0 = fn_800E02D0(p);
        pBlock->mUnknown4 = p->mMotion.mFacing;
        float y = fabsf(p->mMotion.mPos.mY);
        if (!(y <= fn_80178A2C())) {
            pBlock->mUnknown4 = fn_801CFFD0(p->mMotion.mFacing, 0) > 0x400000 ? 0x800000 : 0;
        }
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    } else {
        fn_800E0230(p, pBlock);
    }
}

extern "C" void fn_800E0438(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    Object_80137ABC *pBall = fn_80137C48(p);
    if (pBall) {
        switch (pBlock->mUnknown9) {
        case 0:
        case 1: {
            Vector_80039F5C velocity;
            fn_80137BC0(pBall, 0);
            fn_80137EC4(pBall, &velocity);
            fn_8013791C(pBall, 3, 0);
            fn_8013AD04(pBall, &velocity, 3, 0.0f, 1.0f);
            break;
        }
        }
    }
}

extern "C" void fn_800E04C8(Object_80039F5C *p, Block_800E0230 *pBlock)
{
    if (!(p->mMotion.mUnknown28 / lbl_803ECB08 > 0.2f) && (unsigned char)fn_800B9A90(lbl_803EAB84) == 1) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = 0.2f;
        fn_800E0230(p, pBlock);
    } else {
        p->mUnknown512.mUnknown14 = 10;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown0;
    }
}

extern "C" int fn_800E0574(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (fn_80137C48(p) == 0) {
        return 1;
    }
    fn_800E034C(p, pBlock);
    return 0;
}

extern "C" int fn_800E05C0(Object_80039F5C *p)
{
    Block_800E0230 *pBlock = (Block_800E0230 *)&p->mUnknown336;
    if (fn_80137C48(p) == 0) {
        return 1;
    }
    unsigned char state = pBlock->mUnknown8;
    switch (state) {
    case 0:
        fn_800E04C8(p, pBlock);
        break;
    case 1:
        if (p->mFlags & 0x1000) {
            p->mFlags &= ~0x1000;
            fn_800E0438(p, pBlock);
        }
        if (p->mFlags & 4) {
            fn_800E0438(p, pBlock);
            p->mUnknown512.mUnknown14 = state;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            return 1;
        }
        break;
    }
    return 0;
}

extern "C" int fn_800E068C(Object_80039F5C *p) {
    return 0;
}

extern "C" void fn_800E0694(Object_80039F5C *p, int handle, int index)
{
    if (p->mRatings[0] < lbl_803EAD34) {
        unsigned int threshold = p->mRatings[0] * lbl_803EAD2C;
        if ((unsigned int)fn_802372EC(0, lbl_803EAD28) > threshold) {
            p->mUnknown1008.mUnknown0 = fn_8009A63C(handle)->mUnknown4;
            p->mUnknown1008.mUnknown1 = !(fn_80237260(0) >= lbl_803EAD30) ? 1 : 2;
            p->mUnknown1008.mUnknown2 = handle < 0 ? 2 : 1;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 226, p, 1.0f);
            return;
        }
    }
    fn_80099F04(p, handle, index);
    p->mUnknown1160.mUnknown53 = 1;
    fn_800A2190(1);
    fn_80067E3C(49, &p->mMotion.mPos, p->mId, 0, 0, 0);
    fn_80067E3C(54, &p->mMotion.mPos, p->mId, 0, 0, 0);
}

extern "C" void fn_800E0818(int a, Vector_80039F5C *pOut, unsigned char *pIndex)
{
    fn_80137D58(fn_80137ABC(*pIndex), pOut);
}

extern "C" int fn_800E0850(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown2 = 0;
    unsigned char index;
    int handle;
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    float time = fn_8009A270(handle);
    if (fn_801BE648(p->mpUnknown792) == 224) {
        unsigned char entry = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, 224, 0);
        time += fn_801BD60C(p->mpUnknown800[entry].mUnknown4C.mpUnknown0);
    }
    Object_80137ABC *pBall = fn_80137ABC(index);
    fn_80137D58(pBall, &pBlock->mUnknown4);
    Vector_80039F5C velocity;
    fn_80137EC4(pBall, &velocity);
    float drop = time * 0.002981481608003378f;
    drop = time * drop;
    drop *= 0.5f;
    float z = velocity.mZ * time - drop;
    pBlock->mUnknown4.mX = velocity.mX * time + pBlock->mUnknown4.mX;
    pBlock->mUnknown4.mZ += z;
    pBlock->mUnknown4.mY = velocity.mY * time + pBlock->mUnknown4.mY;
    pBlock->mUnknown16 = (unsigned int)time;
    pBlock->mUnknown24 = (int)(time * 0.8f);
    pBlock->mUnknown20 = (int)(p->mpState->mUnknown3[0] << 16);
    if (pBlock->mUnknown20 > 0x800000) pBlock->mUnknown20 -= 0x1000000;
    if (pBlock->mUnknown24) pBlock->mUnknown20 /= pBlock->mUnknown24;
    if (fn_8009A578(handle) == 5) {
        Vector_80039F5C pos = p->mMotion.mPos;
        pos.mZ = (float)p->mMotion.mUnknown32;
    }
    pBlock->mUnknown28 = (p->mFlags & 0x4000) != 0;
    fn_800A3B58(p, 4, 0);
    if (fn_801BE648(p->mpUnknown792) == 227) {
        p->mUnknown1160.mUnknown54 = 1;
        fn_800D0BF4(p, 1, 28);
    }
    if (fn_801BE648(p->mpUnknown792) == 224 || fn_801BE648(p->mpUnknown792) == 225) {
        p->mFlags |= 8;
    }
    return 0;
}

extern "C" int fn_800E0AD8(Object_80039F5C *p)
{
    Block_800E0850 *pBlock = (Block_800E0850 *)&p->mUnknown336;
    ++pBlock->mUnknown0;
    fn_800B8344(p);
    if (!fn_8009A68C(p)) return 1;
    unsigned char index;
    int handle;
    fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &index, &handle);
    if (p->mFlags & 0x4000) {
        Input_800B6D34 input;
        fn_800B6D34(p, &input);
        pBlock->mUnknown29 = (input.mUnknown96 & 0x11) != 0;
    }
    float time = fn_8009A270(handle);
    if (--pBlock->mUnknown24 >= 0) {
        p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown20) & 0xFFFFFF;
        p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
        unsigned short entry = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, fn_801BE648(p->mpUnknown792), 0);
        if (entry != 0xFFFF) {
            p->mpUnknown800[entry].mUnknownC = (p->mpUnknown800[entry].mUnknownC + pBlock->mUnknown20) & 0xFFFFFF;
        }
    }
    if (!pBlock->mUnknown2) {
        if (!(p->mFlags & 4) && !((float)pBlock->mUnknown0 <= time - 90.0f) &&
            !((float)pBlock->mUnknown0 >= time) && p->mUnknown16 != 0 && p->mUnknown16 != 4) {
            *fn_8009CC2C(p, fn_800E0818, 15, 2) = index;
        }
        pBlock->mUnknown2 = 1;
    } else if ((p->mFlags & 4) || !((float)pBlock->mUnknown0 <= time)) {
        fn_8009CE88(p, &p->mUnknown16, 8);
    }
    if (!((float)pBlock->mUnknown0 <= time - 30.0f)) fn_80042998(p->mpUnknown4);
    Object_80137ABC *pBall = fn_80137ABC(index);
    unsigned short key = fn_801BE648(p->mpUnknown792);
    if (fn_80137AD0(pBall) && fn_80137AD0(pBall) != p && !fn_8009A68C(p) && key != 70) return 1;
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        if (fn_800C4B6C(p)) return 1;
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        if (p->mUnknown9[0] != 8 && p->mUnknown9[0] != 1) {
            Message_800F01CC message;
            fn_801C1F94(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F00D4(0, p->mpState, &message, p);
            fn_8009A260(p);
            return 1;
        }
        if (fn_801BE648(p->mpUnknown792) == 224) {
            fn_800E0694(p, handle, index);
        } else if (fn_801BE648(p->mpUnknown792) == 226) {
            return 1;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            fn_8009A260(p);
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_800E0E8C(Object_80039F5C *p)
{
    Block_800E0E8C *pBlock = (Block_800E0E8C *)&p->mUnknown336;
    if (pBlock->mUnknown2 == 1) {
        fn_8009CE88(p, &p->mUnknown16, 8);
        pBlock->mUnknown2 = 0;
    }
    fn_8009A260(p);
    p->mFlags &= ~8;
    return 1;
}

extern "C" int fn_800E0EF0(Object_80039F5C *p)
{
    int result = 0;
    unsigned char id = p->mpState->mId;
    if (id == 28) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown28;
    } else if (id == 5) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown0;
    } else if (id == 12) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown16;
    } else if (id == 94) {
        result = ((Block_800E0EF0 *)&p->mUnknown336)->mUnknown7;
    }
    return result;
}

extern "C" int fn_800E0F40(Object_80039F5C *p) {
    return 0;
}

extern "C" int fn_800E0F48(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);
    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f) ||
        (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget)
{
    int result = 0;
    if (fn_8009B9A8(0) && fn_80094488() > 1) {
        Vector_80039F5C end;
        Vector_80039F5C start;
        unsigned short i;
        fn_80227690(&end, pTarget, &p->mMotion.mPos);
        fn_802271A4(&end, &end);
        fn_80227248(&end, &end, p->mMotion.mUnknown28 * fn_8009BB54(0));
        fn_80227638(&end, &end, &p->mMotion.mPos);
        end.mZ = 0.0f;
        start = p->mMotion.mPos;
        start.mZ = 0.0f;
        for (i = 0; i < fn_80094488() - 1; i++) {
            if (fn_800E0F48(&p->mMotion.mPos, &end, fn_80094490(i), fn_80094490(i + 1)) ||
                fn_80227B04(&start, &end, fn_80094490(i)) < 4.0f ||
                fn_80227B04(&start, &end, fn_80094490(i + 1)) < 4.0f) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" int fn_800E11C0(Object_80039F5C *p)
{
    int result = 0;
    Block_800E11C0 *pBlock = p->mpUnknown3092->mpUnknown32;
    float distance = fn_8022781C(&pBlock->mUnknown32, &pBlock->mUnknown16);
    if (distance > 0.0f) {
        result = fn_801CFE08(fabsf(pBlock->mUnknown32.mZ - pBlock->mUnknown16.mZ) / distance) <= 0x155555;
    }
    return result;
}

extern "C" int fn_800E1248(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    if (p && pOther) {
        result = fn_80120794(&p->mMotion, &pOther->mMotion, &pOther->mMotion.mUnknown40, 0.2f,
                             pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                             fn_8022781C(&pOther->mMotion, &p->mMotion));
    }
    return result;
}

extern "C" int fn_800E12D4(Object_80039F5C *p)
{
    int result = 1;
    switch (p->mpState->mId) {
    case 16:
    case 17:
    case 28:
        result = 0;
        break;
    default:
        if (p->mUnknown1032 == 4 || p->mUnknown1032 == 6 || p->mUnknown1032 == 5) {
            result = 0;
        }
        break;
    }
    if (fn_8011E188() <= 30) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800E1350(Object_80039F5C *p)
{
    int result = 0;
    if (p && fn_800E12D4(p)) {
        Message_800F01CC message;
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 94;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_800AE7F0(13, p->mIdBytes[2], p);
        fn_800A8954(11, p->mIdBytes[2], p);
    }
    return result;
}

extern "C" int fn_800E13E4(Object_80039F5C *p)
{
    Block_800E13E4 *pBlock = (Block_800E13E4 *)&p->mUnknown336;
    pBlock->mUnknown4 = 30;
    pBlock->mUnknown5 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown6 = 0;
    p->mUnknown1160.mUnknown52 = 1;
    pBlock->mUnknown0 = p->mUnknown512.mUnknown8;
    pBlock->mUnknown12 = 0;
    if (p->mFlags & 0x4000) {
        pBlock->mUnknown7 = 1;
    } else {
        pBlock->mUnknown7 = 0;
    }
    return 0;
}

extern "C" int fn_800E1438(Object_80039F5C *p)
{
    int result = 0;
    Block_801718E8 *pBlock1160 = &p->mUnknown1160;
    Block_800E1438 *pBlock = (Block_800E1438 *)&p->mUnknown336;
    if (fn_801BE648(p->mpUnknown792) != 70) {
        p->mUnknown1008.mUnknown0 = 2;
        p->mUnknown1008.mUnknown1 = 2;
        p->mUnknown1008.mUnknown2 = 10;
        p->mUnknown1011 = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 70, p, 1.0f);
    }
    if (pBlock->mUnknown8 == 0) {
        pBlock->mUnknown8 = fn_800E11C0(p);
    }
    if (pBlock->mUnknown6 == 0) {
        pBlock->mUnknown6 = fn_800E8898(p, &pBlock->mUnknown12);
    }
    if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 11;
        message.mUnknown1[0] = p->mUnknown9[0];
        fn_800F05E4(0, p->mpState, &message, p);
        pBlock1160->mUnknown52 = 0;
        result = 1;
    }
    return result;
}

extern "C" int fn_800E1544(Object_80039F5C *p)
{
    return ((Block_800E13E4 *)&p->mUnknown336)->mUnknown8 == 0;
}

extern "C" int fn_800E1554(Object_80039F5C *p)
{
    int result = 0;
    if (p && p->mpState->mId == 94) {
        result = ((Block_800E13E4 *)&p->mUnknown336)->mUnknown5 == 0;
    }
    return result;
}

extern "C" int fn_800E1584(Object_80039F5C *p)
{
    float chance = 0.1f;
    float angle = 10.0f;
    int result = 0;
    Object_80039F5C *pOther = fn_80137B40();
    if (pOther && fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) <= 0x38E38E && p && !(p->mFlags & 0x4000)) {
        int special = 0;
        fn_800ACDE4(p, &chance, &angle);
        if (fn_80178308() == fn_80178348() && !(p->mMotion.mPos.mY >= fn_80177FE0().mY) &&
            (pOther->mpState->mId == 1 || pOther->mpState->mId == 18)) {
            special = 1;
        }
        if (special) {
            if (!(fn_8022781C(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                fn_801CFFD0(fn_800E1248(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(fn_80237260(0) >= chance) && fn_800E1350(p)) {
                result = 1;
            }
        } else {
            if (!(p->mMotion.mPos.mY >= pOther->mMotion.mPos.mY) &&
                !(fn_8022781C(&p->mMotion, &pOther->mMotion) >= 3.0f) &&
                fn_801CFFD0(fn_800E1248(p, pOther), p->mMotion.mUnknown32) < (int)(angle * 46603.37890625f) &&
                !(fn_80237260(0) >= 0.1f) && fn_800E1350(p)) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" int fn_800E1778(Object_80039F5C *p)
{
    Block_800E1778 *pBlock = (Block_800E1778 *)&p->mUnknown336;
    unsigned int chance = 0;
    Record_800E1778 *pRecord;
    switch (p->mUnknown2914) {
    case 13:
    case 15:
        chance = 15;
        break;
    case 14:
        chance = 10;
        break;
    }
    Object_800670B4 *pObject = fn_80168708(p->mIdBytes[2]);
    if (pObject->mUnknown8.mUnknownF == 0) {
        pRecord = (Record_800E1778 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
    } else {
        unsigned char index = fn_80163E94(pObject, p->mIdBytes[1], 0)->mUnknownB;
        pRecord = (Record_800E1778 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
    }
    if ((pRecord->mUnknown0 & ~0x80) == 85) {
        chance = 0;
    }
    if (chance != 0 && fn_802372EC(0, 100) < chance) {
        pBlock->mUnknown24 = 1;
        pBlock->mUnknown30 = 0;
    }
    return 0;
}

extern "C" int fn_800E1870(Object_80039F5C *p)
{
    int result = 0;
    int inArea = 0;
    if (!(p->mMotion.mPos.mY >= fn_80177FFC(p->mIdBytes[2]).mY + 2.0f) &&
        !(p->mMotion.mPos.mY <= fn_80177FFC(p->mIdBytes[2]).mY + 1.0f) &&
        !(fabsf(p->mMotion.mPos.mX) >= 8.0f)) {
        inArea = (unsigned int)(p->mUnknown2914 - 4) <= 8;
    }
    if (inArea) {
        result = 1;
    }
    if (fn_801BE648(p->mpUnknown792) == 86) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800E1954(Object_80039F5C *p)
{
    Point_8017886C marked = {0.0f, 0.0f};
    Record_8011F4E0 *pTactics = fn_8011F4E0();
    Point_8017886C goal = fn_80177FFC(p->mIdBytes[2]);
    Object_80039F5C *pLeft = 0, *pRight = 0, *pSpecial = 0, *pMarked = 0;
    unsigned int count = fn_80178D18(fn_80178320());
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
        Block_800E1954 *pOtherBlock = (Block_800E1954 *)&pOther->mUnknown336;
        if (pOther->mUnknown2914 >= 17 && pOther->mUnknown2914 <= 18) {
            if (!(pOther->mMotion.mPos.mX <= goal.mX)) pRight = pOther;
            else pLeft = pOther;
        }
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1) pSpecial = pOther;
        if (fn_8009F778(pOther) && fn_8009F6B4() == 1 && !pOtherBlock->mpUnknown36) fn_80164B64(2);
    }
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    Object_800670B4 *pTeam = fn_80168708(fn_80178320());
    Entry_8006719C *pEntry = fn_80163E94(pTeam, p->mIdBytes[1], 0);
    Point_8017886C own = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18 : pEntry->mUnknown10;
    fn_80227638(&own, &own, &goal);
    if (!fn_8009F780() || fn_801BE648(p->mpUnknown792) == 86) {
        if (pBlock->mUnknown49 && !pBlock->mUnknown0) {
            pBlock->mUnknown49 = 0;
            pBlock->mUnknown1 = 1;
        }
        return;
    }
    pBlock->mUnknown49 = 0;
    if (pTactics->mUnknown4) {
        unsigned char slot = pTactics->mUnknown32[p->mIdBytes[1]];
        if (slot <= 3) pMarked = fn_80039F5C(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
    }
    if (pMarked) {
        {
            Object_800670B4 *pMarkedTeam = fn_80168708(fn_80178308());
            Entry_8006719C *pMarkedEntry = fn_80163E94(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
    }
    switch (p->mUnknown2914) {
    case 17: case 18:
        if (pMarked) {
            if (!(own.mX <= goal.mX)) {
                if (!(marked.mX <= own.mX + 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX - 3.0f;
                    float y = own.mY - 4.5f;
                    if (!(y >= goal.mY + 3.5f)) y = goal.mY + 3.5f;
                    pBlock->mUnknown40.mY = y;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float y = own.mY - 3.0f;
                    if (!(y >= goal.mY + 6.0f)) y = goal.mY + 6.0f;
                    pBlock->mUnknown40.mY = y;
                }
            } else {
                if (!(marked.mX >= own.mX - 4.0f)) {
                    pBlock->mUnknown40.mX = marked.mX + 3.0f;
                    float y = own.mY - 4.5f;
                    if (!(y >= goal.mY + 3.5f)) y = goal.mY + 3.5f;
                    pBlock->mUnknown40.mY = y;
                } else {
                    pBlock->mUnknown40.mX = own.mX;
                    float y = own.mY - 3.0f;
                    if (!(y >= goal.mY + 6.0f)) y = goal.mY + 6.0f;
                    pBlock->mUnknown40.mY = y;
                }
            }
            pBlock->mUnknown49 = 1;
        }
        break;
    case 16:
        if (!fn_8009F778(p) && pTactics->mUnknown16[p->mIdBytes[1]] == 255) {
            if (pMarked) {
                if (!(own.mX <= goal.mX)) {
                    if (!(marked.mX >= own.mX - 2.0f)) {
                        pBlock->mUnknown40.mX = own.mX - 3.5f;
                        pBlock->mUnknown49 = 1;
                        pBlock->mUnknown40.mY = own.mY;
                        float y = own.mY + 2.5f;
                        if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                        pBlock->mUnknown40.mY = y;
                    }
                } else if (!(marked.mX <= own.mX + 2.0f)) {
                    pBlock->mUnknown40.mX = own.mX + 3.5f;
                    pBlock->mUnknown49 = 1;
                    pBlock->mUnknown40.mY = own.mY;
                    float y = own.mY + 2.5f;
                    if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                }
            } else {
                int slot = !(own.mX <= goal.mX) ? 1 : 5;
                pMarked = fn_80039F5C(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
                {
            Object_800670B4 *pMarkedTeam = fn_80168708(fn_80178308());
            Entry_8006719C *pMarkedEntry = fn_80163E94(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
                if ((slot == 1 && marked.mX < goal.mX + 6.0f) || (slot == 5 && !(marked.mX <= goal.mX - 6.0f))) {
                    pBlock->mUnknown40.mX = slot == 1 ? own.mX - 3.5f : own.mX + 3.5f;
                    float y = own.mY + 2.5f;
                    if (y > fn_80178A44() - 5.0f) y = fn_80178A44() - 5.0f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        } else if (fn_8009F778(p) && pTactics->mUnknown16[p->mIdBytes[1]] == 255) {
            if (pMarked) {
                if (!(own.mX <= goal.mX)) {
                    if (!(own.mX <= marked.mX + 3.0f)) pBlock->mUnknown40.mX = own.mX - 2.5f;
                } else if (!(own.mX >= marked.mX - 3.0f)) pBlock->mUnknown40.mX = own.mX + 2.5f;
                pBlock->mUnknown40.mY = own.mY;
            } else {
                int slot = !(own.mX <= goal.mX) ? 2 : 4;
                pMarked = fn_80039F5C(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
                {
            Object_800670B4 *pMarkedTeam = fn_80168708(fn_80178308());
            Entry_8006719C *pMarkedEntry = fn_80163E94(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
                if ((slot == 2 && marked.mX < goal.mX + 6.0f) || (slot == 4 && !(marked.mX <= goal.mX - 6.0f))) {
                    pBlock->mUnknown40.mX = slot == 2 ? own.mX - 2.0f : own.mX + 2.0f;
                    pBlock->mUnknown49 = 1;
                    pBlock->mUnknown40.mY = own.mY;
                }
            }
        }
        break;
    case 13: case 15: {
        bool specialRight = pSpecial && pSpecial->mMotion.mPos.mX > p->mMotion.mPos.mX;
        if (pMarked) {
            if (!(p->mMotion.mPos.mX <= goal.mX) && (!pSpecial || !specialRight)) {
                if (!(marked.mX <= own.mX + 3.0f)) {
                    pBlock->mUnknown40.mX = marked.mX - 1.5f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(marked.mX >= own.mX - 3.0f) && (!pSpecial || specialRight)) {
                pBlock->mUnknown40.mX = marked.mX + 1.5f;
                float y = own.mY;
                if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                pBlock->mUnknown40.mY = y;
                pBlock->mUnknown49 = 1;
            }
        } else {
            int slot = !(own.mX <= goal.mX) ? 2 : 4;
            pMarked = fn_80039F5C(fn_80178308(), ((unsigned char *)pTactics)[7 + slot]);
            {
            Object_800670B4 *pMarkedTeam = fn_80168708(fn_80178308());
            Entry_8006719C *pMarkedEntry = fn_80163E94(pMarkedTeam, pMarked->mIdBytes[1], 0);
            marked = pMarkedTeam->mUnknown8.mUnknownF == 1 ? pMarkedEntry->mUnknown18 : pMarkedEntry->mUnknown10;
            fn_80227638(&marked, &marked, &goal);
        }
            if (!(own.mX <= goal.mX) && !(marked.mX <= own.mX + 3.0f)) {
                if (pRight && !pRight->mUnknown361[24] && (!pSpecial || !specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX - 1.5f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            } else if (!(own.mX >= goal.mX) && !(marked.mX >= own.mX - 3.0f)) {
                if (pLeft && !pLeft->mUnknown361[24] && (!pSpecial || specialRight)) {
                    pBlock->mUnknown40.mX = marked.mX + 1.5f;
                    float y = own.mY;
                    if (!(y >= goal.mY + 2.5f)) y = goal.mY + 2.5f;
                    pBlock->mUnknown40.mY = y;
                    pBlock->mUnknown49 = 1;
                }
            }
        }
        break;
    }
    default: pBlock->mUnknown49 = 0;
    }
    if (!pBlock->mUnknown0) {
        Point_8017886C delta;
        if (pBlock->mUnknown49) fn_80227690(&delta, &pBlock->mUnknown40, &p->mMotion);
        else fn_80227690(&delta, &own, &p->mMotion);
        if (!(fn_802270A4(&delta) <= 1.5f) && !pBlock->mUnknown24) pBlock->mUnknown1 = 1;
    }
}

extern "C" void fn_800E2550(Object_80039F5C *p, Point_8017886C *pOut, int *pAngle)
{
    Point_8017886C point = fn_80177FFC(p->mIdBytes[2]);
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    Object_800670B4 *pTeam = fn_80168708(fn_80178320());
    Entry_8006719C *pEntry = fn_80163E94(pTeam, p->mIdBytes[1], 0);
    *pOut = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown18 : pEntry->mUnknown10;
    fn_80227638(pOut, pOut, &point);
    if (!(pOut->mX >= 1.0f - fn_80178A08())) {
        pOut->mX = 1.0f - fn_80178A08();
    } else if (pOut->mX > fn_80178A08() - 1.0f) {
        pOut->mX = fn_80178A08() - 1.0f;
    }
    if (!(pOut->mY >= 1.0f - fn_80178A44())) {
        pOut->mY = 1.0f - fn_80178A44();
    } else if (pOut->mY > fn_80178A44() - 1.0f) {
        pOut->mY = fn_80178A44() - 1.0f;
    }
    if (pBlock->mpUnknown36) {
        fn_8011F4E0();
        Object_80039F5C *pOther = pBlock->mpUnknown36;
        if (pOther) {
            Point_8017886C delta;
            fn_80227690(&delta, &p->mMotion, &pOther->mMotion);
            fn_801CFE40(delta.mY, delta.mX);
            if (p->mUnknown2914 >= 17 && p->mUnknown2914 <= 18) {
                pBlock->mUnknown78 = pTeam->mUnknown8.mUnknown4 == 11;
            } else {
                pBlock->mUnknown78 = !fn_8009FE24(p);
            }
            int ref = fn_800B0F98();
            if (fn_800B146C() && fn_8009BCE8(&ref) == pBlock->mpUnknown36) pBlock->mUnknown78 = 1;
            if (pBlock->mUnknown78) {
                pOut->mX = pOther->mMotion.mUnknown40 * 10.0f + pOther->mMotion.mPos.mX;
                if (!(pOut->mX <= p->mMotion.mPos.mX)) {
                    if (!(pOut->mX >= 4.0f)) pOut->mY += 1.5f;
                } else {
                    if (!(pOut->mX <= -4.0f)) pOut->mY += 1.5f;
                }
            } else {
                fn_800FE03C(p, pOut);
            }
        }
    } else if (pBlock->mUnknown49 && fn_8009F780() && fn_8016EADC()) {
        *pOut = pBlock->mUnknown40;
    } else {
        fn_800E3DCC(p, pOut);
    }
    *pAngle = pEntry->mUnknown20;
}

extern "C" int fn_800E283C(Object_80039F5C *p, int count, float *pValues, float *pOut, float direction, float target)
{
    int result = 0;
    if (direction == -1.0f) {
        int i = 0;
        if (i < count && !(pValues[i] > p->mMotion.mPos.mX)) {
            do { ++i; } while (i < count && pValues[i] <= p->mMotion.mPos.mX);
        }
        if (i == count) return result;
        if (!i) {
            *pOut = pValues[0] - 0.7f;
            return 1;
        }
        while (!result && i > 0) {
            --i;
            float left = pValues[i];
            float right = pValues[i + 1];
            if (!((left + right) * 0.5f >= target)) {
                float upper = right - 0.7f;
                if (!(upper <= target)) upper = target;
                if (!(upper <= p->mMotion.mPos.mX + 1.2f)) upper = p->mMotion.mPos.mX + 1.2f;
                float lower = left + 0.7f;
                if (!(lower >= p->mMotion.mPos.mX - 1.2f)) lower = p->mMotion.mPos.mX - 1.2f;
                if (!(upper <= lower)) {
                    result = 1;
                    *pOut = (upper + lower) * 0.5f;
                }
            }
        }
    } else {
        int i = count - 1;
        if (i < 0) return result;
        if (!(pValues[i] < p->mMotion.mPos.mX)) {
            do { --i; } while (i >= 0 && pValues[i] >= p->mMotion.mPos.mX);
        }
        if (i < 0) return result;
        if (i == count - 1) {
            *pOut = pValues[i] + 0.7f;
            return 1;
        }
        while (!result && i < count - 1) {
            ++i;
            float right = pValues[i];
            float left = pValues[i - 1];
            if (!((right + left) * 0.5f <= target)) {
                float upper = right - 0.7f;
                if (!(upper <= p->mMotion.mPos.mX + 1.2f)) upper = p->mMotion.mPos.mX + 1.2f;
                float lower = left + 0.7f;
                if (!(lower >= p->mMotion.mPos.mX - 1.2f)) lower = p->mMotion.mPos.mX - 1.2f;
                if (!(lower >= target)) lower = target;
                if (!(upper <= lower)) {
                    result = 1;
                    *pOut = (upper + lower) * 0.5f;
                }
            }
        }
    }
    return result;
}

extern "C" void fn_800E2ABC(Object_80039F5C *p)
{
    Block_800E1954 *pBlock = (Block_800E1954 *)&p->mUnknown336;
    Point_8017886C point = fn_80177FFC(p->mIdBytes[2]);
    float random = fn_80237260(0);
    Point_8017886C target;
    target.mY = point.mY + 1.4f + random;
    if (!(target.mY <= p->mMotion.mPos.mY)) {
        target.mY = fn_80177FFC(p->mIdBytes[2]).mY + 1.0f;
        if (!(target.mY <= p->mMotion.mPos.mY)) target.mY = p->mMotion.mPos.mY;
    }
    Record_800E2ABC *pRecord = (Record_800E2ABC *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[1], p->mIdBytes[2]);
    if ((pRecord->mUnknown4 & ~0x80) == 30) {
        Point_8017886C velocity;
        float value = (float)(pRecord->mUnknown5 >> 3) + (float)(pRecord->mUnknown5 & 7) * 0.1428571492433548f;
        fn_80227538(&velocity, pRecord->mUnknown6 << 17, value);
        target.mX = (target.mY - p->mMotion.mPos.mY) * velocity.mX;
        target.mX /= velocity.mY;
        target.mX = (point.mX - p->mMotion.mPos.mX) * 0.0833333358168602f + target.mX;
    } else {
        float x = (point.mX - p->mMotion.mPos.mX) * 0.75f;
        float y = point.mY - 6.0f;
        y -= p->mMotion.mPos.mY;
        target.mX = (target.mY - p->mMotion.mPos.mY) * x / y;
    }
    target.mX += p->mMotion.mPos.mX;
    fn_800E586C(p, &target);
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown4 = target;
    if (!fn_800E3A34(p, &pBlock->mUnknown4)) {
        float values[7];
        int count = 0;
        int players = fn_80178D18(p->mIdBytes[2]);
        for (int i = 0; i < players; ++i) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
            if (pOther != p && !(pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY)) {
                values[count++] = pOther->mMotion.mPos.mX;
            }
        }
        if (count) {
            int changed;
            do {
                changed = 0;
                for (int i = 0; i < count - 1; ++i) {
                    if (!(values[i + 1] >= values[i])) {
                        float temp = values[i + 1];
                        values[i + 1] = values[i];
                        values[i] = temp;
                        changed = 1;
                    }
                }
            } while (changed == 1);
            Point_8017886C goal = fn_80177FFC(p->mIdBytes[2]);
            float direction = !(pBlock->mUnknown4.mX <= goal.mX) ? -1.0f : 1.0f;
            int next = 0;
            float value;
            pBlock->mUnknown22 = 0;
            pBlock->mUnknown23 = 0;
            pBlock->mUnknown12.mY = pBlock->mUnknown4.mY;
            if (fn_800E283C(p, count, values, &value, direction, target.mX) == 1) {
                next = 1;
                pBlock->mUnknown4.mX = value;
                pBlock->mUnknown22 = 1;
            }
            if (fn_800E283C(p, count, values, &value, -direction, target.mX) == 1) {
                (&pBlock->mUnknown4)[next].mX = value;
                (&pBlock->mUnknown22)[next] = 1;
            }
        } else {
            pBlock->mUnknown22 = 1;
        }
    } else {
        pBlock->mUnknown22 = 1;
    }
    if (!pBlock->mUnknown22) {
        pBlock->mUnknown24 = 0;
    } else if (pBlock->mUnknown22 == 1 && pBlock->mUnknown23 == 1) {
        int angle = pRecord->mUnknown6 << 17;
        if (fn_80168EBC(fn_80178320())->mUnknown48) angle = (0x800000 - angle) & 0xFFFFFF;
        if (angle <= 0xBFFFFF) {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX >= pBlock->mUnknown12.mX;
        } else {
            pBlock->mUnknown20 = pBlock->mUnknown4.mX < pBlock->mUnknown12.mX;
        }
    }
}

extern "C" int fn_800E2F20(Object_80039F5C *p, Point_8017886C *pPoint)
{
    int result = 0;
    if (fn_801BE648(p->mpUnknown792) == 86) {
        Point_8017886C delta = *pPoint;
        if (!(fabsf(delta.mY - p->mMotion.mPos.mY) >= 1.0f)) {
            delta.mY = p->mMotion.mPos.mY;
            fn_80227690(&delta, &delta, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            result = (unsigned int)(fn_801CFFD0(p->mMotion.mFacing, angle) - 0x271C72) <= 0x31C71B;
        }
    }
    return result;
}
