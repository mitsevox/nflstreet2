/* Sound stream greedy level (sstsetgl.c): passes a stream's read-ahead (greedy) level to its
   stream file tap. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_setgreedylevel(int stream, int level)
{
    SndStreamChannel_t *channel;

    channel = SNDSTRMI_getstreamptr(stream);
    if (channel == 0) {
        return -8;
    }
    STREAM_setgreedylevel(channel->mpTap, level);
    return 0;
}

}
