#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80227638.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_803EB028 {
    int mUnknown0;
    char mUnknown4[80];
    unsigned int mUnknown84;
    unsigned char mUnknown88;
    unsigned char mUnknown89;
    unsigned char mUnknown90;
    char mUnknown91[1];
};

extern "C" {
extern Block_803EB028 *lbl_803EB028;
int fn_801783AC(int bit);
int fn_8011F1A4(void);
int fn_8011F228(void);
float fn_8011F4D4(void);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_80227248(void *pOut, void *p, float scale);
}

extern "C" void fn_8011BAE0(Pair_8011BAE0 *pOut)
{
    Object_80039F5C *pCarrier = fn_80137B40();
    int kicking = fn_801783AC(0);
    int offense = fn_8011F1A4();
    Point_8017886C origin;

    origin = fn_80177FE0();
    if (!kicking && offense) {
        if (fn_8013BA58(fn_801374BC(), 0) == 3) {
            pCarrier = fn_80137BEC();
        }
        if (pCarrier != 0) {
            if (pCarrier->mpState->mId == 1 || pCarrier->mpState->mId == 68) {
                goto lead;
            }
            pOut->mUnknown0 = fn_8011F4D4();
            if (fn_8011F228()) {
                pOut->mUnknown0 = -pOut->mUnknown0;
            }
            pOut->mUnknown4 = fn_80177FE0().mY - 1.0f;
        } else {
            pOut->mUnknown0 = fn_8011F4D4();
            pOut->mUnknown4 = origin.mY - 1.0f;
        }
    } else if (pCarrier != 0) {
        if (offense || kicking) {
            Point_8017886C offset;

        lead:
            fn_80227248(&offset, &pCarrier->mMotion.mUnknown40, 5.0f);
            fn_80227638(pOut, &pCarrier->mMotion.mPos, &offset);
        } else if (fn_80137B40() != 0 && !(fn_80137B40()->mFlags & 0x8000)) {
            pOut->mUnknown0 = origin.mX;
            pOut->mUnknown4 = pCarrier->mMotion.mPos.mY;
            switch (lbl_803EB028->mUnknown90) {
            case 1:
                pOut->mUnknown0 = origin.mX + 0.33f;
                break;
            case 2:
                pOut->mUnknown0 = origin.mX - 0.33f;
                break;
            }
        } else {
            pOut->mUnknown0 = pCarrier->mMotion.mPos.mX;
            pOut->mUnknown4 = pCarrier->mMotion.mPos.mY;
        }
    } else {
        Vector_80039F5C spot;

        fn_80137D58(fn_801374BC(), &spot);
        fn_80138064(fn_801374BC(), &spot);
        pOut->mUnknown0 = spot.mX;
        pOut->mUnknown4 = spot.mY;
    }
}
