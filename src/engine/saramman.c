/* ARAM manager (saramman.c): sets up, constrains, allocates and frees the sound system's pool
   in ARAM, the GameCube's audio memory. */

#include "engine/sndsys.h"
#include "engine/saramman.h"

extern "C" {

SndAramState_t _SndAram_sState;

void SNDARAM_init(int count)
{
    SNDSYS_entercritical();
    _SndAram_sState.mpAllocations = (SndAramAllocation_t *)SNDMEMI_allocz(count * 8);
    SNDSYS_leavecritical();
    _SndAram_sState.mCount = 0;
    _SndAram_sState.mCapacity = count;
}

void SNDARAM_setpool(unsigned int start, int length)
{
    _SndAram_sState.mUpper = (start + length) & ~4;
    if (start < 32) {
        start = 32;
    }
    _SndAram_sState.mLower = start;
    if (start & 31) {
        _SndAram_sState.mLower = (start + 31) & ~31;
    }
    _SndAram_sState.mLower >>= 5;
    _SndAram_sState.mUpper >>= 5;
}

void SNDARAM_restore(void)
{
    if (_SndAram_sState.mpAllocations != 0) {
        SNDSYS_entercritical();
        SNDMEMI_free(_SndAram_sState.mpAllocations);
        SNDSYS_leavecritical();
        _SndAram_sState.mpAllocations = 0;
    }
}

unsigned int SNDARAM_constrain(unsigned int *start, int *length)
{
    unsigned int old = *start;
    unsigned int lower = _SndAram_sState.mLower;
    if (old < lower) {
        *start = lower;
        *length -= lower - old;
    }
    unsigned int clippedStart = *start;
    if (clippedStart + *length > _SndAram_sState.mUpper) {
        *length = _SndAram_sState.mUpper - clippedStart;
    }
    return clippedStart;
}

// Keep the descriptor table ordered while selecting the first usable gap.
void *SNDARAM_alloc(int size)
{
    int index = 0;
    unsigned int start;
    int length;

    if (_SndAram_sState.mCount < _SndAram_sState.mCapacity) {
        size = (size + 31) >> 5;
        if (_SndAram_sState.mCount == 0) {
            start = _SndAram_sState.mLower;
            length = _SndAram_sState.mUpper - start;
        } else {
            for (; index < _SndAram_sState.mCount; index++) {
                SndAramAllocation_t *pAllocs = _SndAram_sState.mpAllocations;
                if (index == 0) {
                    start = _SndAram_sState.mLower;
                } else {
                    start = pAllocs[index - 1].mStart + pAllocs[index - 1].mLength;
                }
                length = pAllocs[index].mStart - start;
                SNDARAM_constrain(&start, &length);
                if (size <= length) {
                    for (int i = _SndAram_sState.mCount; i > index; i--) {
                        _SndAram_sState.mpAllocations[i] = _SndAram_sState.mpAllocations[i - 1];
                    }
                    goto insert;
                }
            }
            start = _SndAram_sState.mpAllocations[index - 1].mStart +
                    _SndAram_sState.mpAllocations[index - 1].mLength;
            length = _SndAram_sState.mUpper - start;
        }
        SNDARAM_constrain(&start, &length);
        if (size <= length) {
        insert:
            SndAramAllocation_t *pAlloc = _SndAram_sState.mpAllocations;
            pAlloc[index].mStart = start;
            pAlloc[index].mLength = size;
            _SndAram_sState.mCount++;
            return (void *)(start << 5);
        }
    }
    return 0;
}

// Removing an allocation closes its slot without changing the other addresses.
unsigned int SNDARAM_free(void *address)
{
    unsigned int start = (unsigned int)address >> 5;
    for (int index = 0; index < _SndAram_sState.mCount; index++) {
        SndAramAllocation_t *pAlloc = _SndAram_sState.mpAllocations + index;
        if (pAlloc->mStart == start) {
            _SndAram_sState.mCount--;
            for (; index < _SndAram_sState.mCount; index++) {
                _SndAram_sState.mpAllocations[index] = _SndAram_sState.mpAllocations[index + 1];
            }
            return start;
        }
    }
    return start;
}

}
