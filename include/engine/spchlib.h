#ifndef ENGINE_SPCHLIB_H
#define ENGINE_SPCHLIB_H

/* Declarations shared by the files of the speech (play-by-play commentary) library:
   spchevnt.c, the start-up file cu_801AF60C.cpp, spchpick.c, spchrand.c and the rules and banks
   file cu_801B1CFC.cpp. */

#include <stdarg.h>

#include "engine/spchevnt.h"
#include "engine/Object_80266AF8.h"

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

struct RowBank_801AFE90 {
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

struct Slot_801B2450 {
    int mUnknown0;
    RowBank_801AFE90 *mUnknown4;
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

struct Key_801AE658 {
    unsigned short mId;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

union EventWord_801AFBD8 {
    int mWord;
    Key_801AE658 mKey;
    unsigned short mHalfwords[2];
};

struct Item_801AE3F4 {
    unsigned short mId;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    signed char mUnknown9;
    unsigned char mUnknownA;
};

struct Bank_801AE444 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[6];
    unsigned short mUnknown10;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    unsigned short mUnknown18[1];
};

struct Slot_8037E0B4 {
    Bank_801AE444 *mBank;
    int mValue;
};

struct Voice_8037E0F4 {
    unsigned int mTime;
    unsigned short mSequence;
    unsigned char mActive;
    unsigned char mChannel;
    Item_801AE3F4 *mItem;
    int *mEvent;
};

struct State_8037E0F4 {
    int mCount[8];
    int mCurrent[8];
    Voice_8037E0F4 mVoices[16];
};

struct Pending_8037E234 {
    Key_801AE658 mKey;
    int mUnknown4;
};

struct List_801AEDA4 {
    int mCount;
    unsigned short *mIds;
};

struct Config_8037E0A0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int (*mCallback)(Key_801AE658 *key);
    int mUnknown10;
};

class Class_803EBAF8 {
public:
    virtual void *vfn_01(int size, int align, int flags);
    virtual void vfn_02(void *p);
};

extern "C" {
extern Config_8037E0A0 lbl_8037E0A0;
extern Slot_8037E0B4 lbl_8037E0B4[8];
extern State_8037E0F4 lbl_8037E0F4;
extern Pending_8037E234 lbl_8037E234[8];
extern int lbl_8037E274[8];
extern char lbl_802F4794[];
extern Class_803EBAF8 *lbl_803EBAF8;
extern int lbl_803EBAFC;
extern int lbl_803EBB18;
extern int lbl_803EBB1C;
extern int lbl_803ECEA0;
extern int lbl_803ECEA4;
extern int lbl_803ECEA8;
extern unsigned int lbl_803ECEAC;
extern unsigned short lbl_803ECEB0;
extern int lbl_803EBB04;
extern int lbl_803EBB08;
extern int lbl_803EBB0C;
extern Slot_801B2450 *lbl_803EBB00;
extern int lbl_802F475C[8];
extern Channel_801B118C lbl_8037E294[8];
extern unsigned int gSpchRandomState[6];
extern unsigned short _SpchRandom_aHistory[32][2];
extern int _SpchRandom_iHistoryIndex;
unsigned int iSPCH_EACrandom(void);
int fn_801B22E0(RowBank_801AFE90 *, int, int *, int *);
int fn_801B05E4(Work_801B10AC *, unsigned char *);
char *fn_801B22B0(RowBank_801AFE90 *, int);
int fn_801B2648(unsigned int, int *);
int fn_801B26D8(unsigned int, unsigned int, int *);
int fn_801B2798(int, unsigned int);

unsigned int fn_801B2368(void);
int iSPCH_Rand(int count, int category);
void fn_801B10D8(int channel);
int fn_801B1864(int voice);
int fn_801B1380(int channel);
int fn_801B1368(unsigned int channel);
void iSPCH_InitRandom(int seed);
void fn_801B118C(void);
void fn_801B192C(int a);
void fn_801B2450(void);
void fn_801B2468(void);

void *fn_801AF4A8(int size);
void fn_801AF500(void *p);
void fn_801AF128(unsigned int voice);
int fn_801AF3D8(unsigned int channel);
void fn_801AF544(void);
void fn_801AF60C(void);
int fn_801AEC58(int id, int count, ...);

/* Defined in another file of the library. */
int fn_801AE7B4(Key_801AE658 *key, char **out);
void fn_801AE808(void);
void fn_801AE8DC(void);

}

#endif
