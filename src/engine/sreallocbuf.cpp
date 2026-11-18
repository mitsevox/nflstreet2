/* Sound utility (sreallocbuf.cpp): grows a heap buffer to hold at least a requested number of
   elements, doubling its capacity and copying the old contents into the new allocation. */

#include "engine/sndsys.h"
#include "engine/sndutil.h"

namespace Snd {
namespace Util {

void ReallocBuf(void **buffer, int *capacity, int size, int elementSize)
{
    int old;
    void *oldBuffer;
    void *newBuffer;

    old = *capacity;
    if (old < size) {
        if (old == 0) {
            *capacity = size;
        } else {
            while (*capacity < size) {
                *capacity += *capacity;
            }
        }
        oldBuffer = *buffer;
        newBuffer = SNDMEMI_allocz(*capacity * elementSize);
        if (oldBuffer != 0) {
            SNDI_memcpy(newBuffer, oldBuffer, old * elementSize);
            SNDMEMI_free(oldBuffer);
        }
        *buffer = newBuffer;
    }
}

}
}
