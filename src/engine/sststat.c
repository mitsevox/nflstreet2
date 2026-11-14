/* Sound stream status (sststat.c): reports how many requests a stream has queued, the first
   request's id and how many milliseconds of it are buffered. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_status(int stream, SndStreamStatus_t *status)
{
    SndStreamChannel_t *channel;
    SndStreamRequest_t *request;
    unsigned int bytes;

    // FAKEMATCH: clear order found by search (any order clears the same three words)
    status->mBuffered = 0;
    status->mFirstId = 0;
    status->mRequests = 0;
    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    status->mRequests = channel->mRequests.mCount;
    if (status->mRequests != 0) {
        request = (SndStreamRequest_t *)channel->mRequests.mpFirst;
        status->mFirstId = request->mId;
        if (channel->mPlayRate != 0) {
            bytes = SNDPKTPLAY_framesoutstanding(channel->mBuffer);
            status->mBuffered = bytes * 1000 / channel->mPlayRate;
            if (status->mBuffered == 0) {
                request = SNDSTRMI_getrequestptr(status->mFirstId);
                if (request->mDataRate != 0) {
                    bytes = fn_801F75C4(channel->mpTap);
                    if (bytes > 4000000) {
                        bytes = 4000000;
                    }
                    status->mBuffered = bytes * 1000 / request->mDataRate;
                }
            }
        }
    }
    return 0;
}

}
