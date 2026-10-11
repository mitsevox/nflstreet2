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
int fn_801BA2A8(void *record, Record_800D81C8 *entries, unsigned short value, int animation, int key, Object_80039F5C *p, float weight);
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
int fn_801BE648(void *p);
int fn_801BA568(Object_8016D9B8 *p, Record_800D81C8 *pRecords, int key);
int fn_801BA5A8(Object_8016D9B8 *p, Record_800D81C8 *pRecords, int key, int index);
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
    if (delta.mY < 0.0f) {
        delta.mY = 0.0f;
    }
    int angle = fn_801CFE40(delta.mY, delta.mX);
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
    int kind = fn_801BE648(p->mpUnknown792);

    if (kind == 135 || kind == 191) {
        if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, kind)) {
            Record_800D81C8 *pRecords = p->mpUnknown800;
            Record_800D81C8 *pRecord = &pRecords[fn_801BA5A8(p->mpUnknown796, pRecords, kind, 0)];
            value = fn_801BD640(pRecord->mUnknown4C.mpUnknown0, 0xC003);
            value -= fn_801BD6D4(&pRecord->mUnknown4C);
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
