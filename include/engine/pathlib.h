#ifndef ENGINE_PATHLIB_H
#define ENGINE_PATHLIB_H

/* Shared declarations of the PATH interactive-music library files (pathinit.c .. pathaction.c):
   the track, bank, node and event records they share and the library entry points. */

#include "engine/csis.h"
#include "engine/pathreal.h"

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
    virtual void UpdateStatus() = 0;
    virtual void Stop() = 0;
    virtual void Pause(int value) = 0;
    virtual void CheckStatus() = 0;
    virtual int GetPathStatus(void *p) = 0;
    virtual int ReadyForNewRequest() = 0;
    virtual int TimeRemaining(int index) = 0;
    virtual int TimeBuffered() = 0;
    virtual int Play(int node, int offset, int beats, int a, unsigned int length) = 0;
    virtual int GetVolume();
    virtual void SetVolume(int value) = 0;
    virtual int GetDryLevel();
    virtual void SetDryLevel(int value) = 0;
    virtual int GetFXSendLevel(int value);
    virtual void SetFXSendLevel(int send, int value) = 0;
    virtual int GetPitchMult() = 0;
    virtual void SetPitchMult(int value) = 0;
    virtual int GetHandle();
    virtual int GetPlayOpts();
    virtual void SetName(const char *name) = 0;
    virtual void SetFilePath(PathTrackFile_t *path);
    virtual void StreamCache(char *data, int size) = 0;
    virtual int ModifyHold(int hold) = 0;
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

struct PathFindBranch_t {
    signed char mLow;
    signed char mHigh;
    unsigned short mNode;
};

struct PathEvent_t;

struct PathProject_t {
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
    PathEvent_t *mUnknownC0[17];
    unsigned char mEventPoolTail[kEventPoolBytes - sizeof(PathEvent_t *)];
    int mUnknown1100;
};

struct PathAction_t {
    unsigned int mTrackMask;
    union {
        unsigned int mControl;
        struct {
            unsigned int unknownHigh:8, operation:7, complete:1;
            unsigned int lhsKind:2, rhsKind:2, condition:3, comparison:3, depth:3, unknownLow:3;
        } mBits4;
    };
    union {
        unsigned int mOperand;
        struct { short high, low; } mHalves;
    };
};
struct PathEventHeader_t {
    unsigned int mUnknown0[5];
};
struct PathEvent_t {
    unsigned int mCreatedAt;
    unsigned int mLifetime;
    unsigned int mActionStartedAt;
    unsigned char mUnknownC[3];
    unsigned char mActionCount;
    union {
        unsigned char mActionIndex;
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
    PathAction_t mActions[1];
};
struct PathfinderStatus_t;
struct PathMapEntry_t {
    union {
        struct {
            short mSample;
            short mPackedControl;
        };
        struct {
            unsigned int mUnknown16:16, mTrack:5, mSection:6;
            int mLoop:5;
        } mBits0;
    };
    union {
        unsigned int mTimingAndBranches;
        struct {
            unsigned int mUnknown20:12, mBranches:5, mKind:3, mBeats:4, mUnknown0:8;
        } mBits4;
    };
    unsigned int mLinkAndSync;
    unsigned int mFlagsAndEvent;
    union {
        unsigned int word;
        struct { unsigned int mUnknownF:17, flag4000:1, mUnknown0:14; } bits;
    } mEventFlags;
};
struct PathBeatStatus_t {
    unsigned char mUnknown0[8];
    int mBeat;
    unsigned char mUnknownC[12];
    int mNodeDuration;
    int mBarDuration;
    int mBeatDuration;
    int mRemaining;
    int mBarRemaining;
    int mBeatRemaining;
    unsigned char mUnknown30[8];
};
struct PathBeatInfo_t {
    unsigned int mBeatsPerBar:4, mBeatUnit:4, mBeat:8, mUnknown2:16;
    unsigned int mBeatDuration;
    int mBarDuration;
    int mNodeDuration;
    int mBeatRemaining;
    int mBarRemaining;
    unsigned int mRemaining;
};
struct PathFindNode_t {
    unsigned char mUnknown0[8];
    union {
        short mNode;
        struct { unsigned int mUnknown4:28, mSync:2, mUnknown0:2; } mBits8;
    };
};
struct PathActionStatus_t {
    int mNode;
    unsigned char mUnknown4[20];
    int mNodeDuration;
    unsigned char mUnknown1C[8];
    int mRemaining;
    int mBarRemaining;
    int mBeatRemaining;
    unsigned char mUnknown30[8];
};
struct PathSamplePrefix_t {
    short mSample;
};
struct PathfinderTrackData_t;

extern "C" {
extern AllocParams gPathAllocatorParams;
extern void (*songprogress)(int, int);
extern void (*eventrelease)(int, int);
extern void (*eventaction)(int, int);
extern int pflock;
extern PathProject_t *pfstate;
extern unsigned char inited;
extern unsigned char paused;
extern unsigned char bankservice;
extern unsigned int gPathMilliseconds;
extern int debugchannels;
extern int timercalls;
extern int timertimespent;
extern int taskcalls;
extern int tasktimespent;
extern PathProject_t *pfstates[4];
void PATHI_serviceproject(void);
int PATHI_inittrack(int flags, PathfinderTrackData_t *data);
int PATHI_serviceaction(PathEvent_t *p, PathAction_t *entry);
extern unsigned int seedPATH[6];
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
void PATHI_sortprojects(void);
void PATHI_service(int mode);
void PATHI_servicetask(void);
void PATHI_servicetimer(void);
int PATH_createstreamtrack(int flags, PathfinderTrackData_t *data, int value);
int PATH_createbanktrack(int flags, PathfinderTrackData_t *data, int value);
int PATHI_createtrack(int flags, PathfinderTrackData_t *data);
PathTrack_t *PATHI_gettrackptr(unsigned int flags);
void *PATHI_gettrackimp(int flags);
void PATHI_updatemastertrack(void);
int PATHI_countprojecttracks(unsigned int flags);
void PATHI_selectprojecttrack(PathTrack_t *p, int state);
void PATHI_dispatchtrackstate(int state);
void PATHI_volume(PathTrack_t *p, int value);
void PATHI_customsfxfade(PathTrack_t *p, int a, int b, int c);
void PATHI_customdrylevelfade(PathTrack_t *p, int a, int b, int c);
int PATHI_unloadbank(PathTrack_t *p, int index);
int PATHI_unloadmostneglectedsubbank(PathTrack_t *p);
int PATH_control(int flags, int value);
void PATH_pause(int flags, unsigned char value);
int PATH_status(int flags, PathfinderStatus_t *info);
int PATHI_status(PathTrack_t *p, void *info);
void PATH_stop(int flags);
int PATHI_stop(PathTrack_t *p);
void PATHI_printf(const char *format, ...);
int PATHI_addevent(int flags, PathEvent_t *sequence);
void PATHI_removeevent(PathEvent_t *p);
void PATHI_seteventfilter(PathMapEntry_t *p, int value);
void PATHI_clearalleventfilters(void);
int PATHI_serviceevent(int index);
int PATHI_sampleoffset(int index);
int PATHI_timeremaining(PathTrack_t *p);
int PATHI_pickclosestbranch(int count, int value, PathFindBranch_t *entries);
int PATHI_routenode(int index, int value);
unsigned int PATHI_random(void);
PathAction_t *PATHI_conditiondone(PathAction_t *p, int state, PathAction_t *end);
int PATHI_restoretolastwhile(PathAction_t *p, PathEvent_t *sequence);
int PATHI_trackstatus(PathTrack_t *p);
int PATHI_getvalue(int id, int kind, PathTrack_t *p, PathEvent_t *event);
void PATHI_setvalue(int id, int kind, int value, PathTrack_t *p, PathEvent_t *event);
extern unsigned char volscale;
extern int defaultfxbus;
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
PathEvent_t *PATHI_copyevent(PathEvent_t *event);
void PATHI_releaseevent(int index, int reason);
int PATHI_serviceeventqueue(void);
int PATHI_eventtakespriority(int index);
int PATHI_beatinfo(PathTrack_t *p, PathBeatInfo_t *info);
int PATHI_calcwaitbeat(int a, int b, int c, PathBeatInfo_t *info);
int PATHI_nextnode(int index, int value, int advance);
int PATHI_enternode(int track, int index, int value, int advance);
void PATHI_seeknextnode(int index);
int PATHI_queuenode(PathTrack_t *p);
int PATHI_choosesynchtime(int index, const PathFindNode_t &find, const PathBeatInfo_t &info, unsigned int &time);
}

static inline PathTrackInfo_t *PATHI_trackinfo(int index)
{
    PathTrackInfo_t *info = 0;
    if (index >= 0 && index < pfstate->mUnknown18->mUnknownD)
        info = (PathTrackInfo_t *)((char *)pfstate->mUnknown18 + pfstate->mUnknown34[index] * 4);
    return info;
}

static inline PathMapEntry_t *PATHI_findevent(int key)
{
    int i = pfstate->mUnknown18->mUnknownF;
    while (--i >= 0) {
        PathMapEntry_t *entry = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown24[i] * 4);
        if ((int)(entry->mFlagsAndEvent >> 8) == key)
            return entry;
    }
    return 0;
}

static inline PathMapEntry_t *PATHI_getnode(int index)
{
    PathMapEntry_t *node;
    if (index < 0 || index > pfstate->mUnknown18->mUnknown12)
        node = 0;
    else
        node = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown1C[index] * 4);
    return node;
}

#endif
