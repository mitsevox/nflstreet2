#ifndef ENGINE_SOUND_H
#define ENGINE_SOUND_H

#include "engine/Resource.h"

#ifdef __cplusplus
extern "C" {
#endif

/* One entry of an open resource file (8 bytes). stream.c copies it into a
   stream request; sound.cpp keeps up to four of them as AEMS stream file
   descriptors and passes the stream code their "AEMSnn" names instead. */
typedef struct StreamFile_801F6D54 {
    Res_801EDC2C *pRes;
    unsigned int mIndex;
} StreamFile_801F6D54;

/* Sound bank list item of sound.cpp (NASCAR 2005 mangled names call the type
   SndBankInfo_t). +0x14 is the sound library's bank index: fn_8026A9F4 and
   fn_8026A980 multiply it by 12 to index their bank table. */
typedef struct SndBankInfo_801F3524 {
    unsigned int mFlags;
    Res_801EDC2C *pRes;
    unsigned int mIndex;
    void *pData;
    unsigned int mBank;
    int mHandle;
    void (*pCallback)(struct SndBankInfo_801F3524 *pBank);
    unsigned char mLoaded;
    int mState;
} SndBankInfo_801F3524;

/* Bank table entry (12 bytes). */
typedef struct SndBankEntry_801F50C8 {
    int mUnk0;
    int mUnk4;
    int mUnk8;
} SndBankEntry_801F50C8;

/* sound.cpp */
StreamFile_801F6D54 *fn_801F5000(const char *pName);

/* llsound.c */
void fn_801F5034(SndBankInfo_801F3524 *pBank, int move);
void fn_801F50C8(SndBankEntry_801F50C8 *pEntries, int index);

#ifdef __cplusplus
}
#endif

#endif
