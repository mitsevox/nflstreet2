/* Sound stream time multiplier (ssttmul.c): clamps and stores a stream's playback time
   multiplier and passes it to the stream's voice. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_timemult(int stream, int mult)
{
    SndStreamChannel_t *channel;

    if (mult > 8192) {
        mult = 8192;
    } else if (mult < 2048) {
        mult = 2048;
    }
    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    channel->mTimeMult = mult;
    fn_80270D6C(channel->mVoice, mult);
    return 0;
}

}
