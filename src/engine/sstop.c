/* Sound stop (sstop.c): stops every voice playing under one sound handle. */

#include "engine/sndstrm.h"

extern "C" {

int SNDstop(int handle)
{
    int voice;
    int index;

    voice = SNDVOICEI_get(handle);
    if (voice >= 0) {
        index = -1;
        while (iSNDpatchkey(voice, &index)) {
            SNDPLATFORM_stop(index);
        }
    }
    return voice;
}

}
