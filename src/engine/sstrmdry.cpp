/* Sound stream dry level (sstrmdry.cpp): stores a stream's dry (unprocessed) send level and
   passes it to the stream's voice. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_drylevel(int stream, int level)
{
    SndStreamChannel_t *channel;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    channel->mDryLevel = level;
    fn_8026AEAC(channel->mVoice, level);
    return 0;
}

}
