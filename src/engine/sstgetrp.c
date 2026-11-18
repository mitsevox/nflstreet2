/* Sound stream request lookup (sstgetrp.c): finds a queued request by its id on the request
   list of the channel the id names. */

#include "engine/sndstrm.h"

SndStreamRequest_t *SNDSTRMI_getrequestptr(int id)
{
    SndStreamChannel_t *channel;
    SndStreamRequest_t *request;

    if (id < 0) {
        return 0;
    }
    channel = fn_8026D610(id & 0xFF);
    if (channel == 0) {
        return 0;
    }
    request = (SndStreamRequest_t *)channel->mRequests.mpFirst;
    while (request != 0 && request->mId != id) {
        request = (SndStreamRequest_t *)request->mLink.mpNext;
    }
    return request;
}
