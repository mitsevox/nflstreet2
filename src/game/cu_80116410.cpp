#include "engine/cu_801B9F00.h"
#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/Block_801BE60C.h"

/* View of the 21-byte state fn_8011569C passes in (its State_8011569C):
   a heading at +4 and a speed scale at +12 are written here. */
struct State_8011569C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    char mUnknown18[2];
    unsigned char mUnknown20;
};

extern "C" {
int fn_8009EAB0(Object_80039F5C *p, int a);
Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut);
Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
int fn_80116984(Object_80039F5C *p, Object_80039F5C *pOther, float *pOut);
Record_8011F4E0 *fn_8011F4E0(void);
int fn_80178308(void);
void fn_80227690(void *pOut, void *pA, void *pB);
}

/* Picks a spot past a teammate in a neighbouring slot to run to. Partial:
   seven instruction words differ, all from one register choice. The
   target keeps the slot index in r29 and copies its byte offset into r31
   for the inner loop (0x80116580); this source puts the index in r31
   itself. Everything else matches. */
extern "C" int fn_80116410(Object_80039F5C *p, Object_80039F5C *pOther, State_8011569C *pState, Point_8017886C *pTarget) {
    float best = -1000.0f;
    float extra = 0.0f;
    Object_80039F5C *pBest = 0;
    int i = 0;
    int found = 0;
    int result = 0;
    int slots[24];
    unsigned int count;
    unsigned int j;
    unsigned int k;
    int ok;
    Object_80039F5C *pMate;
    Object_80039F5C *pGuard;
    Object_80039F5C *q;
    Record_8011F4E0 *pRecord;
    Object_80039F5C *pCover;
    Object_80039F5C *pMark;
    Point_8017886C spot;
    Point_8017886C apart;
    int near;

    if (p && pTarget) {
        switch (p->mpState->mUnknown1) {
        case 3:
        case 5:
            slots[0] = 4;
            slots[1] = 24;
            break;
        case 4:
            slots[0] = 3;
            slots[1] = 5;
            slots[2] = 24;
            break;
        case 6:
            slots[0] = 7;
            slots[1] = 24;
            break;
        case 7:
            slots[0] = 6;
            slots[1] = 8;
            slots[2] = 24;
            break;
        case 8:
            slots[0] = 7;
            slots[1] = 9;
            slots[2] = 24;
            break;
        case 9:
            slots[0] = 8;
            slots[1] = 24;
            break;
        case 1:
            slots[0] = 2;
            slots[1] = 24;
            break;
        case 2:
            slots[0] = 1;
            slots[1] = 24;
            break;
        case 0:
        default:
            slots[0] = 24;
            break;
        }
        count = fn_80178D18(p->mIdBytes[2]);
        for (; slots[i] != 24; i++) {
            for (j = 0; j < count; j++) {
                pMate = fn_80039F5C(p->mIdBytes[2], j);
                if (pMate != p && pMate->mpState->mId == 40 && pMate->mpState->mUnknown1 == slots[i]) {
                    fn_8009EAB0(pMate, pMate->mpState->mUnknown1);
                    pCover = fn_8009EC60(0, &spot);
                    if (pCover && spot.mY > best) {
                        ok = 0;
                        pGuard = fn_800FB9D4(pCover);
                        if (pGuard) {
                            fn_80227690(&apart, &pGuard->mMotion.mPos, &pCover->mMotion.mPos);
                            ok = fn_802270A4(&apart) < 5.0f;
                        } else if (pOther != pCover) {
                            if (!pOther) {
                                ok = 1;
                            } else if (pCover->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 2.0f) {
                                ok = 1;
                            }
                        }
                        if (ok) {
                            pBest = pCover;
                            best = spot.mY;
                            found = 1;
                        }
                    }
                    break;
                }
            }
        }
        if (found) {
            near = fn_80116984(p, pBest, &extra);
            best += extra;
            if (best + 2.0f > p->mMotion.mPos.mY) {
                pTarget->mY = best + 2.0f;
                pState->mUnknown12 = near ? 1.0f : 0.8f;
                result = 1;
            } else {
                pTarget->mY = p->mMotion.mPos.mY;
                pState->mUnknown4 = 0xC00000;
                result = 1;
                pState->mUnknown12 = 0.0f;
            }
        } else {
            for (k = 0; k <= 2; k++) {
                pRecord = fn_8011F4E0();
                q = fn_80039F5C(fn_80178308(), pRecord->mUnknown8[k]);
                if (q) {
                    pMark = fn_800FB9D4(q);
                    if (pMark && (fn_8022781C(&pMark->mMotion.mPos, &q->mMotion.mPos) > 5.0f || (pMark->mFlags & 0x20000)) &&
                        pMark->mMotion.mPos.mY < q->mMotion.mPos.mY) {
                        pTarget->mX = q->mMotion.mPos.mX;
                        result = 1;
                        break;
                    }
                }
            }
        }
    }
    return result;
}
