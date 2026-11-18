/* Decoder allocators (coda.cpp): the allocate and free callbacks the audio decoders use for their
   state, and the setters the sound system calls at start-up to install them. */

#include "engine/sndutil.h"

namespace Snd {

void *(*CODANew)(unsigned int size);
void (*CODADelete)(void *p);

void CODASetNew(void *(*alloc)(unsigned int size))
{
    CODANew = alloc;
}

void CODASetDelete(void (*release)(void *p))
{
    CODADelete = release;
}

}
