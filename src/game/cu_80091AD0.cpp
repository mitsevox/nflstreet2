#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"
#include "game/Team_80167A8C.h"

extern "C" {
int fn_80093C64(void);
Object_80137ABC *fn_80093C70(Character_80093BCC *pCharacter, int id, Frame_800DF7CC **ppFrame, unsigned char *pFound);
void fn_800D7A0C(Object_80039F5C *p, int a);
void fn_80227264(void *pOut, void *pIn, float scale);
void fn_80227538(Point_80167910 *pOut, int angle, float length);

extern float lbl_803EA8D8;
}

extern "C" int fn_80091AD0(Character_80093BCC *pCharacter, Actor_801C009C *pActor)
{
    if (fn_801383B0()) {
        unsigned char found;
        int i;

        fn_80093C70(pCharacter, 0x42414C4C /* 'BALL' */, 0, &found);
        for (i = 0; i < pActor->mUnknown4; i++) {
            Object_80039F5C *p = pCharacter->mUnknown14[i];

            if (p != 0) {
                Object_80137ABC *pBall = fn_80137C48(p);

                if (pBall != 0) {
                    if (fn_80093C64() == 0) {
                        Vector_80039F5C velocity;
                        Vector_80039F5C direction;
                        Vector_80039F5C pos;
                        float speed;

                        fn_8013791C(pBall, 5, 0);
                        fn_80137EC4(pBall, &velocity);
                        speed = fn_802270D4(&velocity);
                        if (speed < lbl_803EA8D8) {
                            if (speed != 0.0f) {
                                fn_80227264(&velocity, &velocity, lbl_803EA8D8 / speed);
                            } else {
                                fn_80137D58(pBall, &pos);
                                fn_80227538((Point_80167910 *)&direction, p->mMotion.mFacing, lbl_803EA8D8);
                                direction.mZ = 0.0f;
                                fn_80137EE0(pBall, &direction);
                            }
                        }
                    } else if (fn_80093C64() == 1) {
                        if (pActor->mUnknown18 != 0) {
                            if (pActor->mUnknown18->mUnknown0[0x13] == 0) {
                                fn_800D7A0C(p, 1);
                            } else {
                                fn_800D7A0C(p, 2);
                            }
                        }
                    }
                }
                if (pBall == 0 && fn_80093C64() == 1 && i == 0) {
                    fn_80138440(fn_801374BC(), 1);
                    fn_80137A04(fn_801374BC(), p);
                }
            }
        }
    }
    return 1;
}
