#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include <math.h>

struct Ball_t;

extern "C" {
int fn_8011F1CC(void);
int fn_8011F37C(void);
int fn_801486A0(void);
Ball_t *BallGetCurrent(void);
void BallGetPosition(Ball_t *pBall, Vector_80039F5C *pOut);
Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team);
int fn_80178308(void);
int PlayBookGetReceiver(int team, int index, unsigned char *pOut);
PlayBookFormation_t *PlayBookGetFormation(int team);
int fn_800AE9F8(unsigned char (*pEntries)[4]);
}

extern "C" Object_80039F5C *fn_800AEBA0(void)
{
    Object_80039F5C *p = 0;

    if (fn_8011F1CC() != 0 && fn_8011F37C() == 0) {
        if (fn_801486A0() == 4) {
            Vector_80039F5C pos;

            BallGetPosition(BallGetCurrent(), &pos);
            return PlyrFindNearest(&pos, 0, fn_80178308());
        } else {
            int team = fn_80178308();
            unsigned char count = 0;
            Point_8017886C spot = fn_80177FE0();
            Object_80039F5C *pCandidates[3] = { 0 };
            unsigned char i;
            unsigned int best;
            unsigned char lookup;

            for (i = 0; i <= 2; i++) {
                p = PlyrGet(team, PlayBookGetReceiver(team, i, 0));
                if (spot.mY - p->mMotion.mPos.mY > 1.5f && fabsf(p->mMotion.mPos.mX - spot.mX) < 4.0f) {
                    pCandidates[count] = p;
                    count++;
                }
            }
            lookup = PlayBookGetFormation(team)->mUnknown8.mUnknownF;
            best = 0;
            for (i = 0; i < count; i++) {
                unsigned char index;

                if (lookup != 0) {
                    index = PlaySetGetEntry(PlayBookGetFormation(team), pCandidates[i]->mIdBytes[1], 0)->mUnknownB;
                } else {
                    index = pCandidates[i]->mIdBytes[1];
                }
                if (fn_800AE9F8((unsigned char (*)[4])fn_80164EC8(PlayBookGetPlay(team), team, index))) {
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
