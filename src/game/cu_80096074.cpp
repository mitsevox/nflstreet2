#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_802270D4.h"

extern "C" {
Frame_80141210 *fn_801C02C4(Actor_801C009C *pActor);
int fn_8009422C(void);
int fn_800AD9B4(void);
float fn_80178A08(void);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_800955D8(Actor_801C009C *pActor, unsigned short index, Object_80039F5C *pObject, Object_80039F5C **ppOut,
                unsigned short *pCount);
Object_80137ABC *fn_80093C70(Params_80092E54 *pRequest, int id, Frame_800DF7CC **ppFrame, unsigned char *pFound);
int fn_80095078(int key, Params_80092E54 *pRequest, Actor_801C009C *pActor, Object_80039F5C *pObject,
                float range);
}

/* Picks and checks the first player for request: the held one, or else the
   first one fn_800955D8 lists for the actor. When flag is set and the
   request has a 'BALL' frame, a new pick is dropped unless fn_80137C48 (on
   the player) or fn_8009422C holds. Unless request flag 0x40 is set, a new
   pick is also dropped when fn_800AD9B4 returns 4 and it is a kind 1 player
   whose x is past +/-fn_80178A08 with fn_801CFFD0 of its facing against 0
   or 0x800000 under 0x400000, or when the frame has a nonzero offset and
   the player is at least range (30, or 100000 with flag 4 or fn_8009422C)
   from the frame's 2-D offset. The pick is stored back in the request. A
   kept player passes its record's +2 halfword to the frame, loses object
   flag 0x40000 when fn_801383B0 is 0 and it is kind 3, and runs the
   fn_80095078 pass with key 1, then the pass with key 0 only if the first
   succeeds. */
extern "C" int fn_80096074(Params_80092E54 *pRequest, int flag)
{
    int result = 0;
    float range;
    Actor_801C009C *pActor;
    Frame_80141210 *pFrame;
    Object_80039F5C *pHeld;
    Object_80039F5C *p;

    if (pRequest->mUnknown8 & 4) {
        range = 100000.0f;
    } else {
        range = 30.0f;
    }
    if (fn_8009422C() != 0) {
        range = 100000.0f;
    }
    pActor = fn_80093BAC(pRequest->mUnknown0, pRequest->mUnknown4);
    pFrame = fn_801C02C4(pActor);
    pHeld = pRequest->mUnknown14[0];
    if (pHeld == 0) {
        Object_80039F5C *list[24];
        unsigned short count;
        unsigned char found;

        fn_800955D8(pActor, 0, 0, list, &count);
        p = list[0];
        if (p != 0) {
            found = 0;
            if (flag != 0) {
                fn_80093C70(pRequest, 0x42414C4C /* 'BALL' */, 0, &found);
            }
            if (found == 0 || fn_80137C48(p) != 0 || fn_8009422C() != 0) {
                if (!(pRequest->mUnknown8 & 0x40) && fn_800AD9B4() == 4 && p != 0 && p->mIdBytes[3] == 1) {
                    if ((p->mMotion.mPos.mX > fn_80178A08() && fn_801CFFD0(p->mMotion.mFacing, 0) < 0x400000) ||
                        (p->mMotion.mPos.mX < -fn_80178A08() && fn_801CFFD0(p->mMotion.mFacing, 0x800000) < 0x400000)) {
                        p = 0;
                    }
                }
                if (p != 0 && (pFrame->mUnknown1C != 0.0f || pFrame->mUnknown20 != 0.0f || pFrame->mUnknown24 != 0.0f)) {
                    float delta[2];
                    float spot[2];
                    float distance;

                    spot[0] = pFrame->mUnknown24;
                    spot[1] = pFrame->mUnknown1C;
                    fn_80227690(delta, &p->mMotion.mPos, spot);
                    distance = fn_802270A4(delta);
                    if (!(pRequest->mUnknown8 & 0x40) && distance >= range) {
                        p = 0;
                    }
                }
            } else {
                p = 0;
            }
        }
        pRequest->mUnknown14[0] = p;
    } else {
        p = pHeld;
    }
    if (p != 0) {
        pFrame->mUnknown2A = p->mpUnknown796->mUnknown2;
        if (fn_801383B0() == 0 && p->mIdBytes[3] == 3) {
            p->mFlags &= ~0x40000;
        }
        result = fn_80095078(1, pRequest, pActor, p, range);
        if (result != 0) {
            result = fn_80095078(0, pRequest, pActor, p, range);
        }
    }
    return result;
}
