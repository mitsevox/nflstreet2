/* Sound stream tap creation (sstcrtap.c): opens a stream channel that feeds a tap rather
   than a voice, through the shared stream channel creator. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_createtap(int tapId, void *opts, int a, int b, void *data, int c)
{
    return SNDSTRMI_create(opts, a, b, data, c, tapId, 1);
}

}
