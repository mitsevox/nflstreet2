/* Sound stream pitch multiplier (sstpmult.c): clamps and stores a stream's pitch multiplier
   and passes it to the stream's voice. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_pitchmult(int stream, int mult)
{
    SndStreamChannel_t *channel;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    if (mult > 16384) {
        mult = 16384;
    }
    channel->mPitchMult = mult;
    fn_8026C9BC(channel->mVoice, mult);
    return 0;
}

}
