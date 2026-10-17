#include "game/cu_8008E978.h"

extern "C" int fn_8009679C(unsigned int index)
{
    int result = 0;
    Playback_80096DA8 *pPlayback = fn_80096DA8(index);

    if (pPlayback->mUnknown0 != -1) {
        float limit = pPlayback->mUnknown2C * 0.059999995f;
        float time;

        result = pPlayback->mUnknown10 == 2;
        time = pPlayback->mUnknown20;
        if (time < limit) {
            time = limit;
        }
        pPlayback->mUnknown20 = time;
        if (pPlayback->mUnknown24 >= time && pPlayback->mUnknown24 != 0.0f) {
            result = 0;
        }
    }
    return result;
}
