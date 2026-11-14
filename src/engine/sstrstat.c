/* Sound stream request status (sstrstat.c): reports whether a queued stream request is
   playing or waiting, and its played, total and position times in milliseconds. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_requeststatus(int id, SndStreamRequestStatus_t *status)
{
    SndStreamChannel_t *channel;
    SndStreamRequest_t *request;
    int rate;
    float scale;
    float t;

    status->mState = 0;
    status->unk_0x4 = 0;
    status->unk_0x8 = 0;
    status->unk_0xC = 0;
    if (id < 0) {
        return -8;
    }
    channel = fn_8026D610(id & 0xFF);
    if (channel == 0) {
        return -8;
    }
    request = SNDSTRMI_getrequestptr(id);
    if (request != 0) {
        if (request->mActive != 0) {
            if ((SndStreamRequest_t *)channel->mRequests.mpFirst == request) {
                status->mState = 2;
                rate = channel->mPlayRate;
            } else {
                status->mState = 1;
                rate = channel->mQueueRate;
            }
            scale = 1000.0f / (float)rate;
            t = (float)request->unk_0x14 * scale;
            if (!(t < 0.0f)) {
                status->unk_0x4 = (int)(t + 0.5f);
            } else {
                status->unk_0x4 = (int)(t - 0.5f);
            }
            t = (float)(request->unk_0x18 - request->unk_0x14) * scale;
            if (!(t < 0.0f)) {
                status->unk_0x8 = (int)(t + 0.5f);
            } else {
                status->unk_0x8 = (int)(t - 0.5f);
            }
            t = (float)request->unk_0x1C * scale;
            if (!(t < 0.0f)) {
                status->unk_0xC = (int)(t + 0.5f);
            } else {
                status->unk_0xC = (int)(t - 0.5f);
            }
        } else {
            status->mState = 0;
        }
    } else {
        status->mState = 3;
    }
    return 0;
}

}
