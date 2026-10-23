#include "game/cu_8008E978.h"
#include "game/Frame_800DF7CC.h"
#include "engine/cu_801D03D0.h"

extern "C" {
Frame_80141210 *fn_801C02C4(Actor_801C009C *pActor);
int fn_80093AF0(Object_80039F5C *p);
void fn_80091EC0(Character_80093BCC *pCharacter, Actor_801C009C *pActor, Object_80039F5C *p, Vector_80039F5C *pOut,
                 int *pAngle);
}

/* Spot and 24-bit facing for p at frame frameIndex of character's actor.
   With actor flag 0x400 the actor's first frame moves pRef by its offset and
   turn (or p copies pRef) and p's own spot is returned. Otherwise the start
   comes from fn_80091EC0, and a nonzero frameIndex takes that frame's
   offset and turn: flag 0x10 keeps p's spot, flag 0x20 turns the offset
   through the matrix stack around the start. For index 0 fn_801C029C
   returns the actor's +0x18 record; other indexes return 0x30-byte entries
   of the array at actor +0x1C. Only fields below +0x30 (+0x18..+0x24) are
   read from that frame, and those offsets line up in both, so the
   Frame_80141210 view is used for it. */
extern "C" int fn_80093814(Character_80093BCC *pCharacter, Object_80039F5C *p, Object_80039F5C *pRef,
                           unsigned short frameIndex, Vector_80039F5C *pOut, int *pAngle)
{
    Vector_80039F5C spot;
    Vector_80039F5C start;
    int angles[3];
    int angle;
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);

    if (pActor->mUnknown8 & 0x400) {
        Frame_80141210 *pFrame = fn_801C02C4(pActor);

        if (!(pActor->mUnknown8 & 0x800)) {
            p->mMotion.mFacing = 0;
            p->mMotion.mPos.mX = 0.0f;
            p->mMotion.mPos.mY = 0.0f;
            p->mMotion.mPos.mZ = 0.0f;
            p->mpUnknown796->mUnknown8 = 0;
        }
        pActor->mUnknown18->mUnknown30 = -pFrame->mUnknown18;
        pFrame->mUnknown34 = 0.0f;
        pFrame->mUnknown38 = 0.0f;
        pFrame->mUnknown3C = 0.0f;
        if (p == pRef) {
            pRef->mMotion.mPos.mX += pFrame->mUnknown1C;
            pRef->mMotion.mPos.mY += pFrame->mUnknown20;
            pRef->mMotion.mPos.mZ += pFrame->mUnknown24;
            pRef->mMotion.mFacing += (int)(pFrame->mUnknown18 * 2670176.75f);
        } else {
            p->mMotion.mPos = pRef->mMotion.mPos;
            p->mMotion.mFacing = pRef->mMotion.mFacing;
        }
        spot.mX = p->mMotion.mPos.mX;
        spot.mY = p->mMotion.mPos.mY;
        spot.mZ = p->mMotion.mPos.mZ;
        pOut->mX = spot.mX;
        pOut->mY = spot.mY;
        pOut->mZ = spot.mZ;
        *pAngle = p->mMotion.mFacing;
        return 0;
    }
    fn_80091EC0(pCharacter, pActor, pRef, &start, &angle);
    spot.mX = start.mX;
    spot.mY = start.mY;
    spot.mZ = start.mZ;
    if (frameIndex != 0) {
        Frame_80141210 *pFrame = (Frame_80141210 *)fn_801C029C(pActor, frameIndex);

        if (pActor->mUnknown8 & 0x10) {
            spot.mX = p->mMotion.mPos.mX;
            spot.mY = p->mMotion.mPos.mY;
            spot.mZ = p->mMotion.mPos.mZ;
        } else {
            pCharacter->mUnknown8 |= 0x20;
            if (pActor->mUnknown8 & 0x20) {
                fn_801D04C4();
                fn_801D0558();
                fn_801D0C58(&start.mX);
                fn_801D0ADC(fn_80093AF0(pRef));
                spot.mX = pFrame->mUnknown24;
                spot.mY = pFrame->mUnknown1C;
                spot.mZ = pFrame->mUnknown20;
                fn_801D0C58(&spot.mX);
                angle = (int)(pFrame->mUnknown18 * 2670176.75f);
                fn_801D0ADC(angle);
                fn_801D0FB8(&spot.mX);
                fn_801D11F4(angles, 0);
                angle = angles[2];
                fn_801D0544();
            } else {
                spot.mX = pFrame->mUnknown24;
                spot.mY = pFrame->mUnknown1C;
                spot.mZ = pFrame->mUnknown20;
                angle = (int)(pFrame->mUnknown18 * 2670176.75f);
            }
        }
    }
    pOut->mX = spot.mX;
    pOut->mY = spot.mY;
    pOut->mZ = spot.mZ;
    *pAngle = angle;
    return 0;
}
