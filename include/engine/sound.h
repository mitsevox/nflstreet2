#ifndef ENGINE_SOUND_H
#define ENGINE_SOUND_H

#include "engine/Resource.h"

#ifdef __cplusplus
extern "C" {
#endif

/* One entry of an open resource file (8 bytes). stream.c copies it into a
   stream request; sound.cpp keeps up to four of them as AEMS stream file
   descriptors and passes the stream code their "AEMSnn" names instead. */
typedef struct SndFileDesc_t {
    ResFile_t *pRes;
    unsigned int mIndex;
} SndFileDesc_t;

/* Sound bank list item; +0x14 is the sound library's bank index. */
typedef struct SndBankInfo_t {
    unsigned int mFlags;
    ResFile_t *pRes;
    unsigned int mIndex;
    void *pData;
    unsigned int mBank;
    int mHandle;
    void (*pCallback)(struct SndBankInfo_t *pBank);
    unsigned char mLoaded;
    int mState;
} SndBankInfo_t;

/* Bank table entry (12 bytes). */
typedef struct SndBankHeap_t {
    int mUnk0;
    int mUnk4;
    int mUnk8;
} SndBankHeap_t;

/* sound.cpp */
void *SndGetBankTable(void);
SndFileDesc_t *SndAemsDerefrenceFileDesc(const char *pName);

/* llsound.c */
void SndllResolveBank(SndBankInfo_t *pBank, int move);
void SndSetHeap(SndBankHeap_t *pEntries, int index);

#ifdef __cplusplus
}
#endif

#endif
