/* Sound stream memory overhead (sstovrhd.c): the bytes a stream channel needs for its
   requests and buffers, with and without the stream file system's share. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_overheadtap(int requests, int channels)
{
    int size;

    size = lbl_8030002C * sizeof(float) + sizeof(SndStreamChannel_t);
    size += requests * sizeof(SndStreamRequest_t);
    size += SNDPKTPLAY_overhead(channels);
    return size;
}

int SNDSTRM_overhead(int requests, int channels)
{
    return SNDSTRM_overheadtap(requests, channels) + fn_801F685C(requests + 2, 1, 1);
}

}
