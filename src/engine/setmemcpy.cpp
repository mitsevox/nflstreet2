/* Decoder memory copy (setmemcpy.cpp): the copy routine the audio decoders use to move decoded
   samples, memcpy until the sound system installs its own at start-up. */

#include <string.h>

#include "engine/sndutil.h"

namespace Snd {
namespace Coda {
namespace System {

void *(*gMemCpy)(void *dst, const void *src, unsigned int size) = memcpy;

int SetMemCpy(void *(*copy)(void *dst, const void *src, unsigned int size))
{
    gMemCpy = copy;
    return 0;
}

}
}
}
