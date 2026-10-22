#include "game/Object_80039F5C.h"
#include "game/fn_80178D18.h"

extern "C" {
int fn_80178308(void);
int fn_80178320(void);
void *fn_8011F4EC(void);
int fn_8009EAB0(Object_80039F5C *p, int a);
int fn_8009EF6C(void *p);
}

/* View of the record returned by fn_8011F4EC: a count at +408 and the
   player indices that follow it. */
struct Record_80117934 {
    char mUnknown0[408];
    unsigned char mUnknown408;
    unsigned char mUnknown409[3];
};

/* View of the block at player +336 used by fn_80117934. */
struct Block_80117934 {
    char mUnknown0[20];
    Object_80039F5C *mpUnknown20;
};

extern "C" float lbl_803EAFE4;
extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
extern "C" float fn_80227890(Vector_80039F5C *pA, Vector_80039F5C *pB);

extern "C" int fn_8009EFDC(int index);

extern "C" Object_80039F5C *fn_80117794(int index)
{
    Object_80039F5C *pBest = 0;
    float bestX = 0.0f;
    unsigned char i = 0;
    Record_80117934 *pRecord = (Record_80117934 *)fn_8011F4EC();

    for (; i < pRecord->mUnknown408; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178308(), pRecord->mUnknown409[i]);
        int covered = 0;
        Object_80039F5C *pOther = fn_800FB9D4(p);

        if (pOther != 0) {
            covered = fn_80227890(&pOther->mMotion.mPos, &p->mMotion.mPos) < lbl_803EAFE4;
        }
        if (!covered) {
            unsigned char j = 0;
            unsigned int count = fn_80178D18(fn_80178320());

            for (; j < count; j++) {
                Object_80039F5C *pDefender = fn_80039F5C(fn_80178320(), j);
                State_80039F5C *pState = pDefender->mpState;

                if (pState->mId == 40) {
                    fn_8009EAB0(pDefender, pState->mUnknown1);
                    if (fn_8009EF6C(p) && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                        covered = 1;
                    }
                } else if (pState->mId == 92 && ((Block_80117934 *)&pDefender->mUnknown336)->mpUnknown20 == p
                           && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                    covered = 1;
                }
            }
            /* Both direction tests compare against -1 and keep the smaller x
               in the target (0x801178CC and 0x801178E8). */
            if (!covered
                && (pBest == 0 || (fn_8009EFDC(index) == -1 && p->mMotion.mPos.mX < bestX)
                    || (fn_8009EFDC(index) == -1 && p->mMotion.mPos.mX < bestX))) {
                pBest = p;
                bestX = pBest->mMotion.mPos.mX;
            }
        }
    }
    return pBest;
}

extern "C" Object_80039F5C *fn_80117934(void)
{
    Object_80039F5C *pBest = 0;
    float bestY = 0.0f;
    unsigned char i = 0;
    Record_80117934 *pRecord = (Record_80117934 *)fn_8011F4EC();

    for (; i < pRecord->mUnknown408; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178308(), pRecord->mUnknown409[i]);
        int covered = 0;
        Object_80039F5C *pOther = fn_800FB9D4(p);

        if (pOther != 0) {
            covered = fn_80227890(&pOther->mMotion.mPos, &p->mMotion.mPos) < lbl_803EAFE4;
        }
        if (!covered) {
            unsigned char j = 0;
            unsigned int count = fn_80178D18(fn_80178320());

            for (; j < count; j++) {
                Object_80039F5C *pDefender = fn_80039F5C(fn_80178320(), j);
                State_80039F5C *pState = pDefender->mpState;

                if (pState->mId == 40) {
                    fn_8009EAB0(pDefender, pState->mUnknown1);
                    if (fn_8009EF6C(p) && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                        covered = 1;
                    }
                } else if (pState->mId == 92 && ((Block_80117934 *)&pDefender->mUnknown336)->mpUnknown20 == p
                           && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                    covered = 1;
                }
            }
            if (!covered && (pBest == 0 || p->mMotion.mPos.mY > bestY)) {
                pBest = p;
                bestY = pBest->mMotion.mPos.mY;
            }
        }
    }
    return pBest;
}

