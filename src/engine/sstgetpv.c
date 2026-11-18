/* Sound stream programmed volume (sstgetpv.c): reports a stream's volume, from its voice or,
   when the voice reports none, from the channel's stored level. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_getprogvol(int stream)
{
    SndStreamChannel_t *channel;
    int vol;
    float level;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    vol = fn_802781A8(channel->mVoice);
    if (vol < 0) {
        level = channel->mSpeakers[0].mVolume * 127.0f;
        if (!(level < 0.0f)) {
            vol = (int)(level + 0.5f);
        } else {
            vol = (int)(level - 0.5f);
        }
    }
    return vol;
}

}
