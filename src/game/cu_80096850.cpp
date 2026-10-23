#include "game/cu_8008E978.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"

extern "C" float fn_80178A2C(void);

/* Camera spot for playback index: by its flags, the fn_80177FE0 spot
   (flag 8), that spot pushed 3 forward (0x100), the spot with its depth
   pulled back 7 or 10 depending on fn_80178A2C (0x200), or the origin.
   Clears *pFlag. */
extern "C" void fn_80096850(int index, Point_8017886C *pOut, int *pFlag)
{
    Playback_80096DA8 *pPlayback = fn_80096DA8(index);
    Point_8017886C spot = fn_80177FE0();

    if (pPlayback->mUnknownC & 8) {
        pOut->mY = spot.mY;
        pOut->mX = spot.mX;
    } else if (pPlayback->mUnknownC & 0x200) {
        pOut->mX = spot.mX;
        pOut->mY = spot.mY;
        if (spot.mY < 3.0f - fn_80178A2C()) {
            pOut->mY -= 7.0f;
        } else {
            pOut->mY -= 10.0f;
        }
    } else if (pPlayback->mUnknownC & 0x100) {
        pOut->mX = spot.mX;
        pOut->mY = spot.mY;
        pOut->mY += 3.0f;
    } else {
        pOut->mX = pOut->mY = 0.0f;
    }
    *pFlag = 0;
}
