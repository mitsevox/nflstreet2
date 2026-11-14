/* Sound handle and stream helpers (neutral file name): per-handle controls, stream queries and
   the installers of the memory callbacks. */

#include "engine/sndsys.h"

extern "C" {

int fn_8027882C(int handle, int value)
{
    int index;

    handle = fn_8026A288(handle);
    if (handle >= 0) {
        index = -1;
        while (iSNDpatchkey(handle, &index)) {
            fn_80274D34(index, value);
        }
    }
    return handle;
}

int fn_80278894(void)
{
    Struct_80278894 *p;

    p = lbl_803A6C24.m1D4;
    return (p->m8 - p->m10) * 100 / p->m8;
}

int fn_802789E0(int handle)
{
    int i;
    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (lbl_803B5060.m304[i] != 0 && fn_8026A288(lbl_803B5060.m304[i]->m0) == handle) {
            return i;
        }
    }
    return -1;
}

int fn_80278A68(int index, int count)
{
    int i;
    int value = -1;
    int result = -1;
    for (i = 0; i < count; i++) {
        if (lbl_803A6C24.m1CC[index].m4[i] > value) {
            value = lbl_803A6C24.m1CC[index].m4[i];
            result = i;
        }
    }
    return result;
}

int fn_80278ABC(int count)
{
    return count * 32 + 156;
}

int fn_80278AC8(int count)
{
    return fn_80278ABC(count) + fn_80274398();
}

int fn_80279170(int index)
{
    Stream_803B5364 *stream = lbl_803B5060.m304[index];
    int value = 0;
    int i;
    for (i = 0; i < stream->m62; i++) {
        if (stream->m34[i] >= value) {
            value = stream->m34[i];
        }
    }
    return stream->m40 - value - 1;
}

int fn_802791D0(int index)
{
    Stream_803B5364 *stream;

    stream = lbl_803B5060.m304[index];
    return stream->m4C + stream->m48;
}

int fn_802791F4(int index, int a, int b)
{
    return -15;
}

int fn_8027929C(int index)
{
    SNDSYS_entercritical();
    fn_8027474C(index);
    lbl_803B5060.m304[index] = 0;
    SNDSYS_leavecritical();
    return 0;
}

void fn_8027952C(int index, int channel, int value)
{
    Stream_803B5364 *stream;
    Event_803B5064 *event;

    stream = lbl_803B5060.m304[index];
    if (channel == stream->m42) {
        stream->m4C -= value;
        if (stream->m58 != 0) {
            event = &lbl_803B5060.m4[lbl_803B5060.m0];
            event->m0 = 0;
            event->m2 = index;
            event->m4 = value;
            lbl_803B5060.m0++;
        }
    }
}

void fn_80279648(void **buffer, int *capacity, int size, int elementSize)
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

int fn_80279798(int range)
{
    if (range > 0x10000) {
        range = 0x10000;
    } else if (range < 0) {
        range = 0;
    }
    return (((int)(iSNDrandom() & 0x7FFF) - 0x4000) * range) >> 14;
}

void fn_802797F4(void *(*alloc)(int size))
{
    lbl_803B53E4 = alloc;
}

void fn_80279800(void (*release)(void *p))
{
    lbl_803B53E8 = release;
}

int fn_8027980C(int (*copy)(void *dst, void *src, int size))
{
    lbl_80301000 = copy;
    return 0;
}

}
