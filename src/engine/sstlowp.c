/* Sound stream low-pass filter (sstlowp.c): stores a stream's low-pass setting and passes it
   to the stream's voice. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_lowpass(int stream, int value)
{
    SndStreamChannel_t *channel;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    channel->mLowPass = value;
    SNDCTRL_lowpass(channel->mVoice, value);
    return 0;
}

}
