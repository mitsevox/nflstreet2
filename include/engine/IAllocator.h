#ifndef ENGINE_IALLOCATOR_H
#define ENGINE_IALLOCATOR_H

/* Memory allocator handed to the audio libraries: the abstract interface and its engine-heap
   implementation. Every method is inline, so each file that uses the class compiles its own
   local copies of the bodies and tables (pathfinder.cpp and sound.cpp). */

#include "game/fn_801D2B7C.h"

/* Abstract allocator interface. */
class IAllocator {
public:
    virtual void *Alloc(unsigned int size) = 0;
    virtual void Free(void *p) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IAllocator() {}
};

/* Allocator on an engine heap, with an optional lock callback. */
class TiburonIAllocator13Impl : public IAllocator {
public:
    TiburonIAllocator13Impl(int heap, void (*pLock)(int lock) = 0) : mHeap(heap), mpLock(pLock) {}
    virtual void *Alloc(unsigned int size)
    {
        void *p;

        if (mpLock) {
            mpLock(1);
        }
        p = fn_801D2BB0(mHeap, size, 0, 0);
        if (mpLock) {
            mpLock(0);
        }
        return p;
    }
    virtual void Free(void *p) { fn_801D2BD0(p); }
    virtual int AddRef() { return 0; }
    virtual int Release() { return 0; }

    void *operator new(unsigned int size) { return fn_801D2BB0(1, size, 0, 0); }
    void operator delete(void *p) { fn_801D2BD0(p); }

    int mHeap;
    void (*mpLock)(int lock);
};

#endif
