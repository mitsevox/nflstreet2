#ifndef ENGINE_SNDUTIL_H
#define ENGINE_SNDUTIL_H

/* The sound library's C++ helpers: the buffer grower of sreallocbuf.cpp, the decoder allocation
   callbacks of coda.cpp and the decoder copy routine of setmemcpy.cpp. */

namespace Snd {

extern void *(*CODANew)(unsigned int size);
extern void (*CODADelete)(void *p);

void CODASetNew(void *(*alloc)(unsigned int size));
void CODASetDelete(void (*release)(void *p));

namespace Util {

void ReallocBuf(void **buffer, int *capacity, int size, int elementSize);

}

namespace Coda {

extern void *(*gpMemCpy)(void *dst, const void *src, unsigned int size);

namespace System {

int SetMemCpy(void *(*copy)(void *dst, const void *src, unsigned int size));

}
}

}

#endif
