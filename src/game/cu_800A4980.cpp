#include "game/Object_80039F5C.h"
#include "game/fn_802372EC.h"

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

extern void (*lbl_802D7E20[11])(Object_80039F5C *p, Object_80039F5C *pOther, int index,
                                 Params_800A4E8C *pParams);
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
            int skill = p->mRatings[8];

            if (p->mRatings[5] > skill) {
                skill = p->mRatings[5];
            }
            if (fn_802372EC(0, params.mUnknown8) >= skill || fn_800A7ECC(p->mIdBytes[2]) == 0) {
                p->mUnknown1154 = kind;
                p->mUnknown1140 = pOther->mId;
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
