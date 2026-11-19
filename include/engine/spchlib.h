#ifndef ENGINE_SPCHLIB_H
#define ENGINE_SPCHLIB_H

/* Declarations shared by the files of the speech (play-by-play commentary) library:
   spchevnt.c, the start-up file spchinit.c, spchpick.c, spchrand.c, the rules file
   spchrule.c, the sample banks file spchbank.c, the database registration file spchrslv.c,
   sputil.c and the Csis binding file spchcsis.cpp. */

#include <stdarg.h>

#include "engine/spchevnt.h"
#include "engine/VoxDatHeader.h"

struct Entry_801AF84C {
    unsigned int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

struct Record_801AF75C {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    signed char mUnknown4;
    unsigned char mUnknown5[3];
    Entry_801AF84C mEntries[1];
};

struct VoxBankHdr_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned char mRows[1];
};

struct Result_801AFD04 {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
};

struct Buffer_801AFF74 {
    unsigned char mUnknown0[145];
    unsigned char mCount;
    unsigned char mValues[200];
};

struct VoxBankSlot_t {
    int mUnknown0;
    VoxBankHdr_t *mUnknown4;
};

struct WorkEntry_801B0B18 {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

struct Work_801B10AC {
    WorkEntry_801B0B18 mEntries[12];
    unsigned char mUnknown90;
    unsigned char mCount;
    unsigned char mValues[200];
};

struct ChannelEntry_801B118C {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
    unsigned short mUnknown8;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

struct Channel_801B118C {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    void *mUnknownC;
    ChannelEntry_801B118C mEntries[12];
};

struct SpchEventKey_t {
    unsigned short mId;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

union EventWord_801AFBD8 {
    int mWord;
    SpchEventKey_t mKey;
    unsigned short mHalfwords[2];
};

struct VoxEvent_t {
    unsigned short mId;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    signed char mUnknown9;
    unsigned char mUnknownA;
    signed char mUnknownB;
};

struct VoxDat_t {
    unsigned char mUnknown0[4];
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    unsigned char mUnknownC[4];
    unsigned short mUnknown10;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    unsigned short mUnknown18[1];
};

struct VoxDatSlot_t {
    VoxDat_t *mBank;
    int mValue;
};

struct VoxEventSlot_t {
    unsigned int mTime;
    unsigned short mSequence;
    unsigned char mActive;
    unsigned char mChannel;
    VoxEvent_t *mItem;
    int *mEvent;
};

struct VoxEventQueue_t {
    int mCount[8];
    int mCurrent[8];
    VoxEventSlot_t mVoices[16];
};

struct VoxInGameSlot_t {
    SpchEventKey_t mKey;
    int mUnknown4;
};

struct SpchFollowData_t {
    int mCount;
    unsigned short *mIds;
};

struct SpchCallbacks_t {
    int mUnknown0;
    /* Rule test (0x801B1FD8) and rule set (0x801B1EC8): key, rule id, parameter value, game. */
    int (*mUnknown4)(SpchEventKey_t *key, int rule, int value, int game);
    void (*mUnknown8)(SpchEventKey_t *key, int rule, int value, int game);
    int (*mCallback)(SpchEventKey_t *key);
    int mUnknown10;
};

/* The three words the game's speech set-up stores through SPCH_GetExtVecs (0x801F5BC4). */
struct SpchExtVecs_t {
    void *mVecs[3];
};

class SpchAllocator {
public:
    virtual void *vfn_01(int size, int align, int flags);
    virtual void vfn_02(void *p);
};

extern "C" {
extern SpchCallbacks_t gCallbacks;
extern SpchExtVecs_t gExtVecs;
extern VoxDatSlot_t gEventDats[8];
extern VoxEventQueue_t gVoxEvents;
extern VoxInGameSlot_t gVoxInGame[8];
extern int gFilterSetting[8];
extern char spchlibauthor[];
extern SpchAllocator *gSPCH_Allocator;
extern int gSPCH_Initialized;
extern int gGameNum;
extern int gDataRate;
extern int gPreLoadTicks;
extern unsigned int gLastTick;
extern unsigned short gLastSubTick;
extern int gUniqueBankHandle;
extern int gNumBanks;
extern int gBankCount;
extern VoxBankSlot_t *gVoxBanks;
extern int lbl_802F475C[8];
extern Channel_801B118C lbl_8037E294[8];
extern unsigned int seedX[6];
extern unsigned short gRandArray[32][2];
extern int gRandArrayIndex;
unsigned int iSPCH_EACrandom(void);
int fn_801B22E0(VoxBankHdr_t *, int, int *, int *);
int fn_801B05E4(Work_801B10AC *, unsigned char *);
char *iSPCH_GetSampleParmAddr(VoxBankHdr_t *, int);
int iSPCH_FindBank(unsigned int, int *);
int iSPCH_FindSubBank(unsigned int, unsigned int, int *);
int iSPCH_TestSubBankBounds(int, unsigned int);

unsigned int fn_801B2368(void);
int iSPCH_Rand(int count, int category);
void fn_801B10D8(int channel);
int fn_801B1864(int voice);
int fn_801B1380(int channel);
int fn_801B1368(unsigned int channel);
void iSPCH_InitRandom(int seed);
void fn_801B118C(void);
void fn_801B192C(int a);
void iSPCH_InitBanks(void);
void iSPCH_DisposeBanks(void);

void *iSPCH_MemAlloc(int size);
void iSPCH_MemFree(void *p);
void iSPCH_ClearEvent(unsigned int voice);
int SPCH_Choose(unsigned int channel);
void iSPCH_InitInGame(void);
void iSPCH_InitCallbacks(void);
int SPCH_AddEventV(int id, int count, ...);

VoxEvent_t *iSPCH_FindEvent(SpchEventKey_t *key);
int iSPCH_AddEvent(int *event);
void iSPCH_InitCsis(VoxDat_t *bank);
SpchExtVecs_t *SPCH_GetExtVecs(void);

/* Defined in another file of the library. */
int iSPCH_GetDatID(SpchEventKey_t *key, int *out);
int iSPCH_GetGlobalMatchParmsArray(SpchEventKey_t *key, char **out);
void iSPCH_InitEventDat(void);
void iSPCH_InitEventQueue(void);

}

#endif
