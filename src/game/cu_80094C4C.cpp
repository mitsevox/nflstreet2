#include "game/cu_8008E978.h"
#include "engine/Record_800D81C8.h"

extern "C" int fn_8009313C(Params_80092E54 *pRequest);

/* Starts the 'anmm' entry's request for the players its two refs name
   (flag 4 adds 8, flag 8 adds 1 to the request flags) and stores the
   handle; flag 1 then turns the first player to the entry's angle in
   degrees, flag 2 moves it to the entry's spot. Returns whether a handle
   was granted. */

extern "C" int fn_80094C4C(Entry_80094BC4 *p)
{
    Object_80039F5C *pFirst = fn_8009BCE8((int *)&p->mpUnknown0);
    Params_80092E54 request;

    request.mUnknown14[1] = fn_8009BCE8((int *)&p->mpUnknown4);
    request.mUnknown8 = 4;
    request.mUnknown0 = p->mUnknown8;
    request.mUnknown14[0] = pFirst;
    request.mUnknownD4 = 0;
    if (p->mUnknownC & 4) {
        request.mUnknown8 = 12;
    }
    if (p->mUnknownC & 8) {
        request.mUnknown8 |= 1;
    }
    p->mUnknown8 = fn_8009313C(&request);
    if (p->mUnknownC & 1) {
        int angle = (int)((float)p->mUnknown10 * 46603.38f);

        pFirst->mMotion.mFacing = angle;
        pFirst->mpUnknown796->mUnknown8 = angle;
        pFirst->mMotion.mUnknown28 = 0.0f;
        pFirst->mUnknown512.mUnknown14 = 0;
    }
    if (p->mUnknownC & 2) {
        pFirst->mMotion.mPos.mX = p->mUnknown14.mX;
        pFirst->mMotion.mPos.mY = p->mUnknown14.mY;
        pFirst->mUnknown512.mUnknown14 = 0;
        pFirst->mMotion.mUnknown28 = 0.0f;
    }
    return p->mUnknown8 != -1;
}
