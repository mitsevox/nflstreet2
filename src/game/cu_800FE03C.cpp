#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
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

extern "C" {
int fn_80178320(void);
int fn_8009FE24(Object_80039F5C *p);
Object_800670B4 *fn_80168708(int team);
float fn_80178A08(void);
float fn_80178A44(void);
Point_8017886C fn_80177FFC(int team);
}

extern float lbl_803EAE68;

extern float lbl_803EAE6C;

extern float lbl_803EAE70;
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

static inline void GetFormationPoint(Object_800670B4 *pTeam, int index, Point_8017886C *pOut)
{
    Entry_8006719C *pEntry = &pTeam->mUnknown8.mUnknown84[0][index];

    pOut->mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    pOut->mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
}

static inline void AddPoint(Point_8017886C *pOut, Point_8017886C *pOffset)
{
    pOut->mX += pOffset->mX;
    pOut->mY += pOffset->mY;
}

extern "C" Object_80039F5C *fn_800FB844(Object_80039F5C *p);

extern "C" void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut)
{
    Point_8017886C base;
    Object_800670B4 *pTeam;

    base = fn_80177FFC(p->mIdBytes[2]);
    pTeam = fn_80168708(p->mIdBytes[2]);
    GetFormationPoint(pTeam, p->mIdBytes[1], pOut);
    if (fn_8009FE24(p)) {
        Object_80039F5C *pOther = fn_800FB844(p);

        if (pOther) {
            Object_800670B4 *pOtherTeam = fn_80168708(pOther->mIdBytes[2]);
            Point_8017886C other;
            unsigned char i;
            unsigned int count;

            GetFormationPoint(pOtherTeam, pOther->mIdBytes[1], &other);
            if (fabsf(other.mX) < lbl_803EAE70) {
                if (p->mUnknown2914 == 16) {
                    if (pOut->mX < -lbl_803EAE70) {
                        other.mX = other.mX > -lbl_803EAE70 ? -lbl_803EAE70 : other.mX;
                    } else if (pOut->mX > lbl_803EAE70) {
                        other.mX = other.mX < lbl_803EAE70 ? lbl_803EAE70 : other.mX;
                    } else {
                        other.mX = pOut->mX;
                    }
                } else if (p->mUnknown2914 != 17 && p->mUnknown2914 != 18) {
                    if (pOut->mX < -lbl_803EAE70 * 0.5f) {
                        other.mX = other.mX > -lbl_803EAE70 * 0.5f ? -lbl_803EAE70 * 0.5f : other.mX;
                    } else if (pOut->mX > lbl_803EAE70 * 0.5f) {
                        other.mX = other.mX < lbl_803EAE70 * 0.5f ? lbl_803EAE70 * 0.5f : other.mX;
                    } else {
                        pOut->mX = other.mX;
                    }
                }
            }
            if (p->mUnknown2914 != 17 && p->mUnknown2914 != 18) {
                pOut->mX = other.mX;
            } else if (pOtherTeam->mUnknown8.mUnknown4 == 11) {
                pOut->mX = other.mX;
            }
            count = fn_80178D18(fn_80178320());
            for (i = 0; i < count; i++) {
                Entry_8006719C *pEntry;
                Point_8017886C *pPoint;
                int carrier;
                int open;

                if (i == p->mIdBytes[1]) {
                    continue;
                }
                open = 0;
                carrier = 0;
                pEntry = &pTeam->mUnknown8.mUnknown84[0][i];
                pPoint = pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10;
                if (fn_8009FE24(fn_80039F5C(fn_80178320(), i))) {
                    carrier = 1;
                }
                if (!carrier) {
                    open = 1;
                }
                if (open && fn_8022781C(pPoint, pOut) < lbl_803EAE68) {
                    if (pOut->mX >= 0.0) {
                        pOut->mX = pOut->mX + lbl_803EAE6C;
                    } else {
                        pOut->mX = pOut->mX - lbl_803EAE6C;
                    }
                    break;
                }
            }
        }
    }
    AddPoint(pOut, &base);
    pOut->mX = CLAMP(pOut->mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
    pOut->mY = CLAMP(pOut->mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
}
