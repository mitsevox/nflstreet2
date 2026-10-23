#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include <math.h>

struct Object_80137ABC;

extern "C" {
int fn_8011F1CC(void);
int fn_8011F37C(void);
int fn_801486A0(void);
Object_80137ABC *fn_801374BC(void);
void fn_80137D58(Object_80137ABC *pBall, Vector_80039F5C *pOut);
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team);
int fn_80178308(void);
int fn_80168E00(int team, int index, unsigned char *pOut);
Object_800670B4 *fn_80168708(int team);
int fn_800AE9F8(unsigned char (*pEntries)[4]);
}

extern "C" Object_80039F5C *fn_800AEBA0(void)
{
    Object_80039F5C *p = 0;

    if (fn_8011F1CC() != 0 && fn_8011F37C() == 0) {
        if (fn_801486A0() == 4) {
            Vector_80039F5C pos;

            fn_80137D58(fn_801374BC(), &pos);
            return fn_8003A130(&pos, 0, fn_80178308());
        } else {
            int team = fn_80178308();
            unsigned char count = 0;
            Point_8017886C spot = fn_80177FE0();
            Object_80039F5C *pCandidates[3] = { 0 };
            unsigned char i;
            unsigned int best;
            unsigned char lookup;

            for (i = 0; i <= 2; i++) {
                p = fn_80039F5C(team, fn_80168E00(team, i, 0));
                if (spot.mY - p->mMotion.mPos.mY > 1.5f && fabsf(p->mMotion.mPos.mX - spot.mX) < 4.0f) {
                    pCandidates[count] = p;
                    count++;
                }
            }
            lookup = fn_80168708(team)->mUnknown8.mUnknownF;
            best = 0;
            for (i = 0; i < count; i++) {
                unsigned char index;

                if (lookup != 0) {
                    index = fn_80163E94(fn_80168708(team), pCandidates[i]->mIdBytes[1], 0)->mUnknownB;
                } else {
                    index = pCandidates[i]->mIdBytes[1];
                }
                if (fn_800AE9F8((unsigned char (*)[4])fn_80164EC8(fn_8016871C(team), team, index))) {
                    if ((unsigned int)pCandidates[i]->mRatings[7] > best) {
                        best = pCandidates[i]->mRatings[7];
                        p = pCandidates[i];
                    }
                }
            }
        }
    }
    return p;
}
