#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Record_800DB60C.h"
#include "game/Record_8011F518.h"
#include "game/cu_80136B1C.h"

struct Record_800DB074 {
    char mUnknown0[12];
    int mUnknown12;
    float mUnknown16;
};

extern "C" {
int fn_801CFFD0(int a, int b);
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_801061E8(Object_80039F5C *p, Object_80137ABC *pBall);
int fn_80106580(Object_80039F5C *p, int a);
void fn_800DB40C(Record_800DB60C *pRecord, Object_80039F5C *p, Object_80137ABC *pBall);
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

extern "C" void fn_800DB60C(Record_800DB60C *pRecord, Object_80039F5C *p)
{
    if (pRecord->mUnknown0 != 1 && pRecord->mUnknown1 != 1) {
        Object_80137ABC *pBall = fn_80137C48(p);
        if (pBall && fn_80106580(p, (p->mFlags >> 14) & 1)) {
            fn_800DB40C(pRecord, p, pBall);
        }
    }
}
