#ifndef ENGINE_SARAMMAN_H
#define ENGINE_SARAMMAN_H

/* ARAM allocations are kept in address order, in units of 32 bytes. */
typedef struct SndAramAllocation_t {
    unsigned int mStart;
    int mLength;
} SndAramAllocation_t;

typedef struct SndAramState_t {
    unsigned short mCount;
    unsigned short mCapacity;
    unsigned int mLower;
    unsigned int mUpper;
    SndAramAllocation_t *mpAllocations;
} SndAramState_t;

#ifdef __cplusplus
extern "C" {
#endif
extern SndAramState_t _SndAram_sState;
void SNDARAM_init(int count);
void SNDARAM_setpool(unsigned int start, int length);
void SNDARAM_restore(void);
unsigned int SNDARAM_constrain(unsigned int *start, int *length);
void *SNDARAM_alloc(int size);
unsigned int SNDARAM_free(void *address);
#ifdef __cplusplus
}
#endif

#endif
