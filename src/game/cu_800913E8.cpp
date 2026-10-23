#include "game/cu_8008E978.h"
#include "game/Camera_8013F738.h"
#include "engine/Sample_801C009C.h"

extern "C" {
Camera_8013F738 *fn_8013FA04(int index);
Sample_801C009C *fn_801C00F8(Actor_801C009C *);
Sample_801C009C *fn_801C009C(Actor_801C009C *bank, unsigned short id, unsigned short subId, unsigned short index);
float fn_801C5278(float, Curve_801C02EC *, int);
void fn_80227384(void *pOut, void *pIn, int angle);
}

/* Ground spot of character's selected sample at time: the sample's x and
   negated z curves (scaled by p's scale unless actor flag 0x200 is set),
   taken relative to the actor's first frame, turned by the camera and p's
   facing and placed at p. Returns whether character has a selection. */
extern "C" int fn_800913E8(Vector_80039F5C *pOut, Character_80093BCC *pCharacter, Actor_801C009C *pActor,
                           Object_80039F5C *p, float time)
{
    int result = 0;
    Camera_8013F738 *pCamera = fn_8013FA04(0);
    float scale = 1.0f;
    Selection_80141210 *pSelection = &pCharacter->mUnknownE0;

    if (!(pActor->mUnknown8 & 0x200)) {
        scale = p->mUnknown768;
    }
    if (pSelection->mUnknown0 != 0) {
        Sample_801C009C *pSample;

        if (pSelection->mUnknown4.mWord == -1 || pSelection->mUnknown8.mWord == -1) {
            pSample = fn_801C00F8(pActor);
        } else {
            pSample = fn_801C009C(pActor, 1, pSelection->mUnknown4.mParts[1], pSelection->mUnknown8.mParts[1]);
        }
        if (pSample != 0) {
            pOut->mX = fn_801C5278(time, &pSample->mCurves[0], 0) * scale;
            pOut->mY = -fn_801C5278(time, &pSample->mCurves[2], 0) * scale;
            pOut->mX -= pActor->mUnknown18->mUnknown34;
            pOut->mY += pActor->mUnknown18->mUnknown3C;
            fn_80227384(pOut, pOut,
                        pCamera->mUnknown10C - (int)(pActor->mUnknown18->mUnknown30 * 2670176.75f) + p->mMotion.mFacing + 0x400000);
            pOut->mX += p->mMotion.mPos.mX;
            pOut->mY += p->mMotion.mPos.mY;
            pOut->mZ = 0.0f;
        }
        result = 1;
    }
    return result;
}
