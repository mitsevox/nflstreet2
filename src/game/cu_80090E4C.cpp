#include "game/cu_8008E978.h"
#include "game/Object_8017886C.h"

extern "C" {
int fn_800AD9B4(void);
float fn_80178A44(void);
void fn_800A9D84(Point_8017886C *pOut);
void fn_800B267C(Object_800B26B0 *pMotion);
void fn_80090558(Character_80093BCC *pCharacter, Actor_801C009C *pActor, Object_80039F5C *p);
void fn_80091644(int index);
int fn_80093814(Character_80093BCC *pCharacter, Object_80039F5C *p, Object_80039F5C *pRef, unsigned short frameIndex,
                Vector_80039F5C *pOut, int *pAngle);
Object_80137ABC *fn_80093C70(Character_80093BCC *pCharacter, int id, Frame_800DF7CC **ppFrame, unsigned char *pFound);
}

extern int lbl_803EA8CC;

/* Places character index's players at the start of its actor. When the
   first player's id byte +3 is 1 it is set up first: if fn_800AD9B4
   returns 1 or 7 it goes to the origin and its facing alternates between
   0 and 0x800000 on each call; otherwise character kind 1 takes
   fn_800A9D84's spot facing 0x400000, kinds 0 and 5 keep it, and other kinds (kind 3 with sub-kind up to 7 faces 0x400000,
   the rest face 0x800000 for positive x) are clamped to x in [-1, 1] and
   y within fn_80178A44() - 8. fn_80090558 then runs, and every player
   gets its frame spot and facing from fn_80093814 unless actor flag
   0x400 is set. Partial: the target sets the zero facing only on the
   x path (li after the compare) where this source sets it before the kind
   3 test; every other form tried (else-branch zero, ternaries) turns the
   x test into an mfcr bit extract. */
extern "C" int fn_80090E4C(int index)
{
    Character_80093BCC *pCharacter = fn_80093BCC(index);
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    Object_80039F5C *p = pCharacter->mUnknown14[0];
    unsigned short i;

    if (p->mIdBytes[3] == 1) {
        if (fn_800AD9B4() == 1 || fn_800AD9B4() == 7) {
            p->mMotion.mPos.mX = 0.0f;
            p->mMotion.mPos.mY = 0.0f;
            p->mMotion.mFacing = lbl_803EA8CC != 0 ? 0x800000 : 0;
            lbl_803EA8CC = (lbl_803EA8CC + 1) & 1;
        } else {
            int kind = pCharacter->mUnknown4;

            if (kind != 5) {
                if (kind == 1) {
                    fn_800A9D84((Point_8017886C *)&p->mMotion.mPos);
                    p->mMotion.mFacing = 0x400000;
                } else if (kind != 0) {
                    int facing;
                    float limit;

                    facing = 0;
                    if (kind == 3 && (unsigned int)pCharacter->mUnknown0 <= 7) {
                        facing = 0x400000;
                    } else if (p->mMotion.mPos.mX > 0.0f) {
                        facing = 0x800000;
                    }
                    p->mMotion.mFacing = facing;
                    limit = 1.0f;
                    if (p->mMotion.mPos.mX < -limit) {
                        p->mMotion.mPos.mX = -limit;
                    } else if (p->mMotion.mPos.mX > limit) {
                        p->mMotion.mPos.mX = limit;
                    }
                    limit = fn_80178A44() - 8.0f;
                    if (p->mMotion.mPos.mY < -limit) {
                        p->mMotion.mPos.mY = -limit;
                    } else if (p->mMotion.mPos.mY > limit) {
                        p->mMotion.mPos.mY = limit;
                    }
                }
            }
        }
        pCharacter->mUnknown8 |= 0x20;
    }
    fn_80090558(pCharacter, pActor, p);
    for (i = 0; i < pActor->mUnknown4; i++) {
        Vector_80039F5C spot;
        int angle;
        unsigned char found;
        int result;

        p = pCharacter->mUnknown14[i];
        if ((unsigned int)pCharacter->mUnknown4 <= 2 && p->mUnknown9[2] != 0) {
            p->mpUnknown4->mUnknown20 |= 1;
        }
        if (pActor->mUnknown8 & 0x400) {
            p->mpUnknown4->mUnknown20 |= 0x2000;
            pCharacter->mUnknown8 |= 0x20;
        }
        result = fn_80093814(pCharacter, p, pCharacter->mUnknown14[0], i, &spot, &angle);
        fn_80093C70(pCharacter, 0x434C4950 /* 'CLIP' */, 0, &found);
        if (result != 0) {
            pCharacter->mUnknown8 |= 8;
        }
        if (found != 0) {
            pCharacter->mUnknown8 |= 0x20;
        }
        if (!(pActor->mUnknown8 & 0x400)) {
            fn_800B267C(&p->mMotion);
            p->mUnknown500 = 0;
            p->mUnknown504 = 0.0f;
            p->mMotion.mPos.mX = spot.mX;
            p->mMotion.mPos.mY = spot.mY;
            p->mMotion.mPos.mZ = spot.mZ;
            p->mMotion.mUnknown12.mX = spot.mX;
            p->mMotion.mUnknown12.mY = spot.mY;
            p->mMotion.mUnknown12.mZ = spot.mZ;
            p->mMotion.mFacing = angle;
            p->mpUnknown796->mUnknown8 = angle;
        }
    }
    fn_80091644(index);
    return 1;
}
