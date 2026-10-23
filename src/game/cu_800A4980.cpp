#include "game/Object_80039F5C.h"
#include "game/fn_802372EC.h"
#include "game/fn_800B65A0.h"
#include "game/Object_8017886C.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))

/* Stack block whose address fn_800A4E8C passes as the fourth argument of the
   callbacks of the .data table 0x802D7E20. */
struct Params_800A4E8C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
};

extern "C" {
int fn_800AC87C(Object_80039F5C *p, int value);
int fn_8009AFE8(int team, int value);
int fn_800A7ECC(int team);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
float fn_802270A4(void *pV);
unsigned short fn_801BE648(void *p);
int fn_80177C38(void);
float fn_8016B938(void);
float fn_8016B974(void);
int fn_8011F1CC(void);

extern void (*lbl_802D7E20[11])(Object_80039F5C *p, Object_80039F5C *pOther, int index,
                                 Params_800A4E8C *pParams);
}

extern "C" void fn_800A4980(Object_80039F5C *p, Object_80039F5C *pOther, int index, Params_800A4E8C *pParams)
{
    Point_8017886C delta;
    float distance;

    fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
    fn_801CFE40(delta.mY, delta.mX);
    distance = fn_802270A4(&delta);
    if (distance < 3.0f) {
        pParams->mUnknown4 = (int)(pParams->mUnknown4 * distance / 3.0f);
        pParams->mUnknown0 = (int)(pParams->mUnknown0 * distance / 3.0f);
    }
    if (index == 5) {
        pParams->mUnknown8 = 400;
        pParams->mUnknown0 = 30;
        pParams->mUnknown4 = 15;
        pParams->mUnknownC = index;
    } else if (index == 4 && pOther != 0 && fn_801BE648(pOther->mpUnknown792) == 229) {
        pParams->mUnknown8 = 500;
        pParams->mUnknown0 = 30;
        pParams->mUnknown4 = 15;
        pParams->mUnknownC = 5;
    }
    if (pOther != 0 && fn_800B65A0(p->mIdBytes[2]) != 0xFF && fn_800B65A0(pOther->mIdBytes[2]) == 0xFF
        && fn_80177C38() == 0) {
        pParams->mUnknown8 = pParams->mUnknown8 - (int)MIN(pParams->mUnknown8 - 1, pParams->mUnknown8 * fn_8016B938());
        pParams->mUnknown0 = pParams->mUnknown0
                             - (int)MIN(pParams->mUnknown0 - pParams->mUnknown4 - 1,
                                        (pParams->mUnknown0 - pParams->mUnknown4) * fn_8016B938());
        if (fn_8011F1CC() && (pOther->mFlags & 0x8000)) {
            pParams->mUnknown8 = pParams->mUnknown8 - (int)MIN(pParams->mUnknown8 - 1, pParams->mUnknown8 * fn_8016B974());
            pParams->mUnknown0 = pParams->mUnknown0
                                 - (int)MIN(pParams->mUnknown0 - pParams->mUnknown4,
                                            (pParams->mUnknown0 - pParams->mUnknown4) * fn_8016B974());
        }
    }
}

extern "C" int fn_800A4E8C(Object_80039F5C *p, Object_80039F5C *pOther, int kind, int level)
{
    Params_800A4E8C params;
    int result = 0;

    if ((p->mFlags & 0x20000) == 0) {
        params.mUnknown10 = level;
        params.mUnknown8 = 300;
        params.mUnknown0 = 20;
        params.mUnknown4 = 10;
        params.mUnknownC = 6;
        if (lbl_802D7E20[kind] != 0) {
            lbl_802D7E20[kind](p, pOther, kind, &params);
        }
        params.mUnknown8 = fn_800AC87C(p, params.mUnknown8);
        params.mUnknown8 = fn_8009AFE8(p->mIdBytes[2], params.mUnknown8);
        if (fn_800A7ECC(p->mIdBytes[2]) != 2) {
            int skill;
            int rating8 = p->mRatings[8];
            int rating5 = p->mRatings[5];

            if (rating5 > rating8) {
                skill = rating5;
            } else {
                skill = rating8;
            }
            if (fn_802372EC(0, params.mUnknown8) >= skill || fn_800A7ECC(p->mIdBytes[2]) == 0) {
                p->mUnknown1140 = pOther->mId;
                p->mUnknown1154 = kind;
                if (fn_800A7ECC(p->mIdBytes[2]) == 0 && (kind == 4 || kind == 5)) {
                    p->mUnknown1152 = params.mUnknown0;
                } else {
                    int spread;

                    p->mUnknown1152 = fn_802372EC(0, params.mUnknown0 - params.mUnknown4);
                    spread = 255 - p->mRatings[5];
                    if (spread < 0) {
                        spread = 0;
                    }
                    p->mUnknown1152 = p->mUnknown1152 + fn_802372EC(0, spread / params.mUnknownC) + params.mUnknown4;
                    p->mUnknown1152 = p->mUnknown1152 < params.mUnknown4 ? params.mUnknown4
                                      : (p->mUnknown1152 > params.mUnknown0 ? params.mUnknown0 : p->mUnknown1152);
                }
                p->mFlags |= 0x20000;
                p->mUnknown1158 = p->mUnknown1152;
                result = 1;
                p->mUnknown1156 = 0;
                p->mUnknown1144 = -1;
                p->mUnknown1148 = 1.0f;
            }
        }
    }
    return result;
}
