#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8022781C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[8];
};

struct Table_8015005C {
    Entry_8015005C mEntries[4];
    Vector_80039F5C mUnknown80;
    Point_8017886C mUnknown92[2];
    char mUnknown108[9];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

extern "C" {
Table_8015005C *fn_801530FC(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
float fn_802373C8(int selector, float first, float last);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFFD0(int a, int b);
int fn_8015228C(Object_80039F5C *p, unsigned char *pIndex);

void fn_80152068(int index, Vector_80039F5C *pOut)
{
    pOut->mX = (fn_801530FC()->mUnknown92 + index)->mX;
    pOut->mY = (fn_801530FC()->mUnknown92 + index)->mY;
    pOut->mZ = 0.0f;
}

int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex)
{
    unsigned int count = fn_801383C8();
    int result = 0;
    float best = -3.4028234663852886e38f;

    if (p->mUnknown8 != 255) {
        return fn_8015228C(p, pIndex);
    }
    *pIndex = 0;
    unsigned int players = fn_801530FC()->mCount;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80137ABC *pBall = fn_80137ABC(i);
        float score = 0.0f;

        if (fn_8013846C(pBall) && fn_8013BA58(pBall, 0) == 4) {
            Vector_80039F5C position;
            fn_80138064(pBall, &position);
            float distance = fn_8022781C(&position, &p->mMotion.mPos);
            score = fn_802373C8(0, score, 0.75f);
            if (i == 0) {
                score += 0.5f;
            }
            unsigned char closer = 0;
            unsigned char j;
            for (j = 0; j < players; j++) {
                Object_80039F5C *pOther = fn_80039F5C(1, j);
                if (pOther != p && !(fn_8022781C(&position, &pOther->mMotion.mPos) >= distance)) {
                    closer++;
                }
            }
            score -= closer * closer * 1.5f;
            if (!(score <= best)) {
                *pIndex = i;
                best = score;
                result = 1;
            }
        }
    }
    return result;
}

int fn_8015228C(Object_80039F5C *p, unsigned char *pIndex)
{
    unsigned int count = fn_801383C8();
    int result = 0;
    *pIndex = 0;
    float best = -3.4028234663852886e38f;
    fn_801530FC();
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80137ABC *pBall = fn_80137ABC(i);
        if (fn_8013846C(pBall) && fn_8013BA58(pBall, 0) == 4) {
            Vector_80039F5C position;
            Point_8017886C delta;
            fn_80138064(pBall, &position);
            fn_80227690(&delta, &position, &p->mMotion.mPos);
            int direction = delta.Heading();
            float score = fn_801CFFD0(direction, p->mUnknown512.mUnknown4);
            score *= 0.00000011920928955078125f;
            score = 1.0f - score;
            score *= 5.0f;
            score *= p->mUnknown512.mUnknown0;
            score -= fn_8022781C(&position, &p->mMotion.mPos);
            if (!(score <= best)) {
                *pIndex = i;
                best = score;
                result = 1;
            }
        }
    }
    return result;
}
}
