/* Sound over test (sover.c): tells whether a sound has finished, that is whether its voice
   handle no longer names a playing voice. */

#include "engine/sndbank.h"

extern "C" {

int SNDover(int handle)
{
    return SNDVOICEI_get(handle) < 0;
}

}
