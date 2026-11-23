#ifndef ENGINE_PATHLIB_H
#define ENGINE_PATHLIB_H

/* Shared declarations of the PATH interactive-music library files (pathinit.c .. pathaction.c):
   the track, bank, node and event records they share and the library entry points. */

#include "engine/fn_801B3234.h"
#include "engine/csis.h"

struct PathSubBankInfo_t {
    unsigned int mEvictionOrder;
    int mSizeA;
    int mSizeB;
};

struct PathTrackInfo_t {
    unsigned int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned int mUnknown8;
    unsigned char mUnknownC[4];
};

struct PathSubBankState_t {
    PathSubBankInfo_t mInfo;
    int mIndex;
    int mReady;
    unsigned char mUnknown14[8];
    char *mpData;
    int mEvictionPriority;
};

struct PathTrackFile_t {
    void *mUnknown0;
    int mUnknown4;
};

class IPathTrack {
public:
    virtual ~IPathTrack();
    virtual void SetTrackInfo(PathTrackInfo_t *p);
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual void vfn_05(int value) = 0;
    virtual void vfn_06() = 0;
    virtual int vfn_07(void *p) = 0;
    virtual int vfn_08() = 0;
    virtual int vfn_09(int index) = 0;
    virtual void vfn_10() = 0;
    virtual int vfn_11(int node, int offset, int beats, int a, unsigned int length) = 0;
    virtual int GetVolume();
    virtual void vfn_13(int value) = 0;
    virtual int GetDryLevel();
    virtual void vfn_15(int value) = 0;
    virtual int GetFXSendLevel(int value);
    virtual void vfn_17(int send, int value) = 0;
    virtual int vfn_18() = 0;
    virtual void vfn_19(int value) = 0;
    virtual int GetHandle();
    virtual int GetPlayOpts();
    virtual void vfn_22(const char *name) = 0;
    virtual void SetFilePath(PathTrackFile_t *path);
    virtual void vfn_24() = 0;
    virtual void vfn_25() = 0;
    virtual int GetNumSubBanks();
    virtual int GetMaxSubBanks();
    virtual PathSubBankState_t *GetSubBankPtr(int index);
    virtual PathSubBankState_t *GetAvailSubBankPtr();
    virtual int AddSubBank(int index, char *data);
    virtual int AddSubBankDone(int index);
    virtual int DetachSubBankHeader(int index, int header);
    virtual int RemoveSubBank(int index);

    IPathTrack();

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    unsigned char mUnknown24[52];
    int mUnknown58;
    PathTrackInfo_t *mUnknown5C;
    int mUnknown60;
    int mUnknown64;
};

struct PathMapHeader_t {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8[2];
    unsigned short mUnknownA;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned short mUnknown12;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    int mUnknown34;
    int mUnknown38;
};

struct PathMapVariable_t {
    char mName[16];
    int mValue;
};

struct PathStreamRecord_t {
    unsigned int mByteOffset;
    unsigned int mDuration;
};

struct PathTrack_t {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    short mUnknown4;
    short mUnknown6;
    union {
        unsigned int word;
        struct { unsigned short high; unsigned char low[2]; } halves;
        struct {
            unsigned int mUnknown16:16;
            int mLoop:4;
            int mUnknown7:5;
            unsigned int flag40:1, flag20:1, flag10:1, mUnknown1:3, flag1:1;
        } bits;
    } mUnknown8;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
    unsigned int mUnknown10;
    int mUnknown14;
    signed char mUnknown18, mUnknown19, mUnknown1A;
    unsigned char mUnknown1B;
    unsigned int mUnknown1C;
    int mUnknown20;
    signed char mUnknown24, mUnknown25, mUnknown26;
    unsigned char mUnknown27;
    unsigned int mUnknown28;
    int mUnknown2C;
    signed char mUnknown30, mUnknown31, mUnknown32;
    unsigned char mUnknown33;
    unsigned int *mUnknown34;
    unsigned int mUnknown38;
    unsigned int mUnknown3C;
    unsigned int mUnknown40;
    unsigned int mPauseTime;
    unsigned int mResumeTime;
    int mUnknown4C;
    PathTrackFile_t mUnknown50;
    unsigned char mUnknown58[120];
    char mUnknownD0[32];
    int mUnknownF0;
    unsigned int mUnknownF4;
    int mUnknownF8;
    int mUnknownFC;
    IPathTrack *mUnknown100;
    unsigned short mUnknown104;
    unsigned char mUnknown106[2];
    int mUnknown108;
    int mUnknown10C;
    int mUnknown110;
};

struct Record_801B6D20 {
    signed char mUnknown0;
    signed char mUnknown1;
    unsigned short mUnknown2;
};

struct Sequence_801B84E4;

struct Bank_801B3480 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    unsigned int mUnknown14;
    PathMapHeader_t *mUnknown18;
    short *mUnknown1C;
    void *mUnknown20;
    short *mUnknown24;
    void *mUnknown28;
    PathMapVariable_t *mUnknown2C;
    unsigned int *mUnknown30;
    int *mUnknown34;
    void *mUnknown38;
    unsigned int *mUnknown3C;
    PathTrack_t *mUnknown40[24];
    unsigned char mUnknownA0[32];
    enum { kEventPoolBytes = 4096 };
    // The last scanned slot shares the first bytes of the event pool.
    Sequence_801B84E4 *mUnknownC0[17];
    unsigned char mEventPoolTail[kEventPoolBytes - sizeof(Sequence_801B84E4 *)];
    int mUnknown1100;
};

class Class_803EBB60 {
public:
    virtual ~Class_803EBB60();
    virtual void vfn_02() = 0;
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual unsigned int vfn_05() = 0;
    virtual int vfn_06(int channels) = 0;
    virtual int vfn_07(char *name, int &size, int flags) = 0;
    virtual int vfn_08(int handle, char *&data) = 0;
    unsigned char mUnknown0[12];
};

struct Event_801B845C {
    unsigned char mUnknown0[4];
    union {
        unsigned int mUnknown4;
        struct { unsigned int mUnknown6:26, depth:3, mUnknown0:3; } mBits4;
    };
    unsigned char mUnknown8[4];
};
struct SequenceHeader_801B6210 {
    unsigned int mUnknown0[5];
};
struct Sequence_801B84E4 {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned char mUnknownC[3];
    unsigned char mUnknownF;
    union {
        unsigned char mUnknown10;
        unsigned int mWord10;
        struct {
            unsigned int mUnknown18:8, mUnknown14:4;
            int mPriority:4;
            unsigned int mUnknownF:1, flag4000:1, mVoice:3, mUnknown0:11;
        } mBits10;
        struct {
            unsigned int mUnknown13:18, flag2000:1, mUnknown0:13;
        } mFlags10;
    };
    Event_801B845C mUnknown14[1];
};
struct PathfinderStatus_t;
struct Entry_801B63F0 {
    union {
        struct {
            short mUnknown0;
            short mUnknown2;
        };
        struct {
            unsigned int mUnknown16:16, mUnknown14:2, mTrack:5, mUnknown5:4;
            int mLoop:5;
        } mBits0;
    };
    union {
        unsigned int mUnknown4;
        struct {
            unsigned int mUnknown20:12, mBranches:5, mKind:3, mBeats:4, mUnknown0:8;
        } mBits4;
    };
    unsigned int mUnknown8;
    unsigned int mUnknownC;
    union {
        unsigned int word;
        struct { unsigned int mUnknownF:17, flag4000:1, mUnknown0:14; } bits;
    } mUnknown10;
};
struct PathStatus_801B67F8 {
    unsigned char mUnknown0[8];
    int mUnknown8;
    unsigned char mUnknownC[12];
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
};
struct BeatInfo_801B67F8 {
    unsigned int mUnknown0:4, mUnknown4b:4, mUnknown1:8, mUnknown2:16;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    unsigned int mUnknown18;
};
struct FindNode_801B6A18 {
    unsigned char mUnknown0[8];
    union {
        short mUnknown8;
        struct { unsigned int mUnknown4:28, mSync:2, mUnknown0:2; } mBits8;
    };
};
struct TrackStatus_801B864C {
    int mUnknown0;
    unsigned char mUnknown4[20];
    int mUnknown18;
    unsigned char mUnknown1C[8];
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
    unsigned char mUnknown30[12];
};
struct Record_801B6780 {
    short mUnknown0;
};
struct PathfinderTrackData_t;

class Class_803EBB64 {
public:
    virtual ~Class_803EBB64();
    virtual int vfn_02(IPathTrack **track, int a, float b, int c) = 0;
    virtual int vfn_03(IPathTrack **track, int a) = 0;
};

extern "C" {
extern Allocator *lbl_803EBB68;
extern AllocParams gPathAllocatorParams;
extern void (*lbl_803EBB2C)(int, int);
extern void (*lbl_803EBB30)(int, int);
extern void (*lbl_803EBB34)(int, int);
extern int lbl_803EBB24;
extern Bank_801B3480 *lbl_803EBB28;
extern unsigned char lbl_803EBB38;
extern unsigned char lbl_803EBB39;
extern unsigned char lbl_803EBB3B;
extern unsigned int lbl_803EBB3C;
extern int lbl_803EBB40;
extern int lbl_803EBB48;
extern int lbl_803EBB4C;
extern int lbl_803EBB50;
extern int lbl_803EBB54;
extern Bank_801B3480 *lbl_802F47D0[4];
extern Class_803EBB60 *lbl_803EBB60;
void PATHI_serviceproject(void);
int PATHI_inittrack(int flags, PathfinderTrackData_t *data);
int fn_801B7880(Sequence_801B84E4 *p, Event_801B845C *entry);
extern unsigned int seedPATH[6];
extern Class_803EBB64 *lbl_803EBB64;
int PATH_destroy(int flags);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
int PATHI_init(void);
int PATH_shutdown(void);
void *PATHI_memalloc(int size);
void PATHI_memfree(void *p);
void PATH_seteventcallbacks(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int));
unsigned int PATH_milliseconds(void);
unsigned int PATHI_switchproject(unsigned int index, unsigned int flags);
int PATHI_switchvoice(unsigned int flags);
int PATHI_sortprojects(void);
void PATHI_service(int mode);
void PATHI_servicetask(void);
void PATHI_servicetimer(void);
int PATH_createstreamtrack(int flags, PathfinderTrackData_t *data, int value);
int PATH_createbanktrack(int flags, PathfinderTrackData_t *data, int value);
int PATHI_createtrack(int flags, PathfinderTrackData_t *data);
PathTrack_t *PATHI_gettrackptr(unsigned int flags);
void PATHI_updatemastertrack(void);
int PATHI_countprojecttracks(unsigned int flags);
void PATHI_selectprojecttrack(PathTrack_t *p, int state);
int PATHI_dispatchtrackstate(int state);
void fn_801B4824(PathTrack_t *p, int value);
void fn_801B4960(PathTrack_t *p, int a, int b, int c);
void fn_801B49C4(PathTrack_t *p, int a, int b, int c);
int PATHI_unloadbank(PathTrack_t *p, int index);
int PATHI_unloadmostneglectedsubbank(PathTrack_t *p);
int PATH_control(int flags, int value);
void PATH_pause(int flags, unsigned char value);
int PATH_status(int flags, PathfinderStatus_t *info);
int PATHI_status(PathTrack_t *p, void *info);
void PATH_stop(int flags);
int PATHI_stop(PathTrack_t *p);
void PATHI_printf(const char *format, ...);
int PATHI_addevent(int flags, Sequence_801B84E4 *sequence);
void PATHI_removeevent(Sequence_801B84E4 *p);
void PATHI_seteventfilter(Entry_801B63F0 *p, int value);
void PATHI_clearalleventfilters(void);
int PATHI_serviceevent(int index);
int fn_801B6780(int index);
int fn_801B6CB4(PathTrack_t *p);
int fn_801B6D20(int count, int value, Record_801B6D20 *entries);
int fn_801B7178(int index, int value);
unsigned int PATHI_random(void);
Event_801B845C *fn_801B845C(Event_801B845C *p, int state, Event_801B845C *end);
int fn_801B84E4(Event_801B845C *p, Sequence_801B84E4 *sequence);
int fn_801B8580(PathTrack_t *p);
int PATHI_getvalue(int id, int kind, PathTrack_t *p, Sequence_801B84E4 *event);
void PATHI_setvalue(int id, int kind, int value, PathTrack_t *p, Sequence_801B84E4 *event);
extern unsigned char lbl_803EBB3A;
extern int lbl_803EBB44;
void PATH_setallocator(Allocator *allocator, const AllocParams &params);
int PATH_addmapfile(PathMapHeader_t *map);
int PATH_destroy(int flags);
int PATH_setvariable(int flags, const char *name, int value);
int PATHI_bytesperms(int index);
IPathTrack *PATH_createstreamimp(int flags, int a, float b);
IPathTrack *PATH_createbankobject(int flags);
void PATH_volume(int flags, signed char volume);
void PATH_fade(int flags, int a, int b, int c);
void PATHI_fade(PathTrack_t *p, int a, int b, int c);
void PATHI_setfadevolume(PathTrack_t *p);
void PATHI_setsfxfadevolume(PathTrack_t *p);
void PATHI_setdrylevelfadevolume(PathTrack_t *p);
int PATHI_loadbank(PathTrack_t *p, int index);
int PATHI_subbankready(PathTrack_t *p, int index);
int PATHI_loadbankdata(PathTrack_t *p, int index, int size);
int PATH_event(int flags, unsigned int id);
Sequence_801B84E4 *PATHI_copyevent(Sequence_801B84E4 *event);
void PATHI_releaseevent(int index, int reason);
int PATHI_serviceeventqueue(void);
int PATHI_eventtakespriority(int index);
int PATHI_beatinfo(PathTrack_t *p, BeatInfo_801B67F8 *info);
int PATHI_calcwaitbeat(int a, int b, int c, BeatInfo_801B67F8 *info);
int PATHI_nextnode(int index, int value, int advance);
int PATHI_enternode(int track, int index, int value, int advance);
void PATHI_seeknextnode(int index);
int PATHI_queuenode(PathTrack_t *p);
int PATHI_choosesynchtime(int index, const FindNode_801B6A18 &find, const BeatInfo_801B67F8 &info, unsigned int &time);
}

static inline PathTrackInfo_t *PATHI_trackinfo(int index)
{
    PathTrackInfo_t *info = 0;
    if (index >= 0 && index < lbl_803EBB28->mUnknown18->mUnknownD)
        info = (PathTrackInfo_t *)((char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown34[index] * 4);
    return info;
}

static inline Entry_801B63F0 *PATHI_findevent(int key)
{
    int i = lbl_803EBB28->mUnknown18->mUnknownF;
    while (--i >= 0) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown24[i] * 4);
        if ((int)(entry->mUnknownC >> 8) == key)
            return entry;
    }
    return 0;
}

static inline Entry_801B63F0 *PATHI_getnode(int index)
{
    Entry_801B63F0 *node;
    if (index < 0 || index > lbl_803EBB28->mUnknown18->mUnknown12)
        node = 0;
    else
        node = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    return node;
}

#endif
