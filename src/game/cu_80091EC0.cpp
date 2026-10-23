#include "game/cu_8008E978.h"

extern "C" {
Frame_80141210 *fn_801C02C4(Actor_801C009C *pActor);
int fn_80093AF0(Object_80039F5C *p);
}

/* Start spot and 24-bit facing for character's actor: the spot is p's
   position unless the actor's first frame gives one (stored z, x, y).
   Character kind 5 takes the facing from the frame and, for sub-kinds 3, 5
   and 7, a fixed spot written back to the frame. Actor flags 1/2 with a
   negative x/y mirror the facing. */
extern "C" void fn_80091EC0(Character_80093BCC *pCharacter, Actor_801C009C *pActor, Object_80039F5C *p,
                            Vector_80039F5C *pOut, int *pAngle)
{
    int mirror = 0;
    Frame_80141210 *pFrame = fn_801C02C4(pActor);

    pOut->mX = p->mMotion.mPos.mX;
    pOut->mY = p->mMotion.mPos.mY;
    pOut->mZ = p->mMotion.mPos.mZ;
    if (pFrame->mUnknown1C != 0.0f || pFrame->mUnknown20 != 0.0f || pFrame->mUnknown24 != 0.0f) {
        pOut->mX = pFrame->mUnknown24;
        pOut->mY = pFrame->mUnknown1C;
        pOut->mZ = pFrame->mUnknown20;
    }
    if (((pActor->mUnknown8 & 1) && pOut->mX < 0.0f) || ((pActor->mUnknown8 & 2) && pOut->mY < 0.0f)) {
        mirror = 1;
    }
    if (pCharacter->mUnknown4 == 5) {
        *pAngle = ((int)(pFrame->mUnknown30 * 2670176.75f) - 0x400000) & 0xFFFFFF;
        switch ((unsigned int)pCharacter->mUnknown0) {
        case 3:
            pOut->mX = pFrame->mUnknown24 = -24.197f;
            pOut->mY = pFrame->mUnknown1C = 47.9f;
            pOut->mZ = pFrame->mUnknown20 = 0.0f;
            break;
        case 5:
            pOut->mX = pFrame->mUnknown24 = -15.535f;
            pOut->mY = pFrame->mUnknown1C = 21.259f;
            pOut->mZ = pFrame->mUnknown20 = 0.0f;
            break;
        case 7:
            pOut->mX = pFrame->mUnknown24 = -15.658f;
            pOut->mY = pFrame->mUnknown1C = -2.154f;
            pOut->mZ = pFrame->mUnknown20 = 0.0f;
            break;
        default:
            pOut->mX = pFrame->mUnknown34;
            pOut->mY = -pFrame->mUnknown3C;
            pOut->mZ = 0.0f;
            break;
        }
    } else {
        *pAngle = fn_80093AF0(p);
    }
    if (mirror != 0) {
        *pAngle = (0x800000 - *pAngle) & 0xFFFFFF;
    }
}
