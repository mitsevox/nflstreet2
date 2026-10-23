#include "game/cu_8008E978.h"
#include "game/cu_80041210.h"
#include "game/Object_80040818.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_801784C4(void);
unsigned short fn_80040F10(void);
void fn_80051B3C(Object_80040818 *pOwner, float *pPos);
}

extern float lbl_802D72A4[3];
extern float lbl_802D72B0[3];

/* Two three-float corners of a box (x and y negated when fn_801784C4 is
   set). Each object fn_80041904 lists whose x and y lie inside the box gets
   x and y moved: past the corner on the side farther from it, by
   2 * (1 + 0.05 * fn_802372EC(0, 50)), unless already beyond that, and
   the result goes to fn_80051B3C for the matching fn_80040F18 owner. Two
   separate arrays: one six-float array keeps its base in a register across
   the calls. */
extern "C" void fn_80090BDC(void)
{
    float lo[3];
    float hi[3];
    float pos[3];
    int i;

    lo[0] = fn_801784C4() ? -lbl_802D72A4[0] : lbl_802D72A4[0];
    lo[1] = fn_801784C4() ? -lbl_802D72A4[1] : lbl_802D72A4[1];
    lo[2] = lbl_802D72A4[2];
    hi[0] = fn_801784C4() ? -lbl_802D72B0[0] : lbl_802D72B0[0];
    hi[1] = fn_801784C4() ? -lbl_802D72B0[1] : lbl_802D72B0[1];
    hi[2] = lbl_802D72B0[2];
    for (i = 0; i < fn_80040F10(); i++) {
        Object_80041904 *pBall = fn_80041904(i);

        pos[0] = pBall->mUnknown8;
        pos[1] = pBall->mUnknown12;
        pos[2] = pBall->mUnknown16;
        if (pos[0] >= lo[0] && pos[0] <= hi[0] && pos[1] >= lo[1] && pos[1] <= hi[1]) {
            float margin = 2.0f * (fn_802372EC(0, 50) * 0.05f + 1.0f);

            if (hi[0] - pos[0] > pos[0] - lo[0]) {
                pos[0] = (hi[0] + margin >= pos[0]) ? hi[0] + margin : pos[0];
            } else {
                pos[0] = (lo[0] - margin <= pos[0]) ? lo[0] - margin : pos[0];
            }
            margin = 2.0f * (fn_802372EC(0, 50) * 0.05f + 1.0f);
            if (hi[1] - pos[1] > pos[1] - lo[1]) {
                pos[1] = (hi[1] + margin >= pos[1]) ? hi[1] + margin : pos[1];
            } else {
                pos[1] = (lo[1] - margin <= pos[1]) ? lo[1] - margin : pos[1];
            }
            fn_80051B3C(fn_80040F18(i), pos);
        }
    }
}
