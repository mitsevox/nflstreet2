/* Sound stream high-pass filter (ssthighp.c): stores a stream's high-pass setting and
   passes it to the stream's voice. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_highpass(int stream, int value)
{
    SndStreamChannel_t *channel;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    channel->mHighPass = value;
    SNDCTRL_highpass(channel->mVoice, value);
    return 0;
}

}
