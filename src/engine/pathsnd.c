/* PATH sound tracks (pathsnd.c): the PATH audio-track system's sound back end. It installs the
   Path::PathToSnd singleton, which creates the bank and stream track objects the music player plays
   through, and drives the sound library's voices and streams for their volume, pitch, send levels,
   pause, play, stop and status. */

#include <string.h>
#include "engine/pathreal.h"
#include "engine/sndstrm.h"
#include "engine/voicequery.h"

/* The parts of the PATH project state this file reads: the loaded map and its node offset table. */
struct PathSndMap_t {
    unsigned char unk_0x0[0x12];
    unsigned short mNodeCount;
};

struct PathSndNode_t {
    unsigned int unk_0x0;
    unsigned int unk_0x4 : 20, mBeats : 4, mDivisions : 8;
    unsigned int unk_0x8;
    unsigned int mFlags;
};

struct PathSndProject_t {
    unsigned char unk_0x0[0x18];
    PathSndMap_t *mpMap;
    short *mpNodeOffsets;
};

/* The status block a track keeps at +0x24 and copies out through GetPathStatus. */
struct PathStatus_t {
    int mNode;
    int unk_0x4;
    int unk_0x8;
    int unk_0xC;
    int mVoice;
    int mReady;
    unsigned int mLength;
    unsigned int unk_0x1C;
    unsigned int unk_0x20;
    unsigned int mPosition;
    unsigned int unk_0x28;
    unsigned int unk_0x2C;
    int mBuffered;
    int mRemaining;
};

/* One sub-bank slot of a bank track (36 bytes). */
struct PathSubBankState_t {
    int mPriority;
    unsigned char unk_0x4[8];
    int mIndex;
    int mReady;
    int mAttached;
    int mBank;
    void *mpHeader;
    unsigned int mLastPlayed;
};

struct PathTrackInfo_t;
struct PathTrackFile_t;

/* The base track interface as this file's tracks use it (constructor, destructor and the
   non-pure methods are pathtrack.c's). */
class IPathTrack {
public:
    int mHandle;
    int mResult;
    int mFXSendLevel;
    int mDryLevel;
    int mVolume;
    int unk_0x14;
    int unk_0x18;
    int mDirty;
    SndPlayOpts_t *mpPlayOpts;
    PathStatus_t mStatus;
    PathTrackInfo_t *mpTrackInfo;
    int mMaxSubBanks;
    PathSubBankState_t *mpSubBanks;

    IPathTrack();
    virtual ~IPathTrack();
    virtual void SetTrackInfo(PathTrackInfo_t *info);
    virtual void UpdateStatus() = 0;
    virtual int Stop() = 0;
    virtual int Pause(int pause) = 0;
    virtual void CheckStatus() = 0;
    virtual int GetPathStatus(PathStatus_t *status) = 0;
    virtual int ReadyForNewRequest() = 0;
    virtual int TimeRemaining(int index) = 0;
    virtual int TimeBuffered() = 0;
    virtual int Play(int node, unsigned int offset, int count, int key, unsigned int length) = 0;
    virtual int GetVolume();
    virtual int SetVolume(int volume) = 0;
    virtual int GetDryLevel();
    virtual int SetDryLevel(int level) = 0;
    virtual int GetFXSendLevel(int send);
    virtual int SetFXSendLevel(int send, int level) = 0;
    virtual int GetPitchMult() = 0;
    virtual int SetPitchMult(int pitch) = 0;
    virtual int GetHandle();
    virtual SndPlayOpts_t *GetPlayOpts();
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
};

struct PathTrackName_t {
    char mText[16];
};

struct PathTrackPath_t {
    char mText[128];
};

/* One queued request of a stream track (20 bytes). */
struct PathStreamRequest_t {
    unsigned int mLength;
    int mRequest;
    unsigned int mPlayed;
    int mNode;
    int unk_0x10;
};

extern "C" {

void PATHI_servicetimer(void);
void *PATHI_memalloc(int size);
void PATHI_memfree(void *p);
extern unsigned int gPathMilliseconds;
extern PathSndProject_t *pfstate;
int SNDSTRM_overhead(int count, int requests);
int fn_8026E280(SndPlayOpts_t *opts, int count, int requests, void *buffer, int size);
void fn_8026E2A8(int handle);
int fn_8026E364(int handle, int key, void *path, int offset);
int fn_8026E388(int handle);
int SNDSTRM_drylevel(int handle, int level);
int SNDSTRM_fxlevel(int handle, int send, int level);
int SNDSTRM_modifyhold(int request, int hold);
int SNDSTRM_pitchmult(int handle, int pitch);
int SNDSTRM_lowpass(int handle, int value);
int SNDSTRM_getprogvol(int handle);
int SNDSTRM_requeststatus(int request, SndStreamRequestStatus_t *status);
void SNDSTRM_status(int handle, SndStreamStatus_t *status);
void SNDSYS_add100hzclient(void (*client)(void));
void SNDSYS_remove100hzclient(void (*client)(void));
int SNDplaysetdef(SndPlayOpts_t *opts);
int SNDvol(int handle, int volume);
int SNDBANK_asyncloadmem(int *handle, void *data);
int SNDBANK_asyncloadmemdone(void);
int SNDBANK_patchinfo(int bank, int patch, SndSampleFormat_t *format, SndSampleAttr_t *attr, void *desc);
int SNDBANK_play(int bank, int patch, SndPlayOpts_t *opts);
int SNDbankremove(int handle);
int SNDbankheadersize(int handle);
int SNDbankheadercopy(void *dest, int handle);
int SNDstop(int handle);

}

/* Two equivalent node lookups: GetPathStatus matches only with the conditional form and
   PathTrackSndBank::CheckStatus only with the if/else form (see the source-form row). */
static inline PathSndNode_t *_PathSndNodePtr(int index)
{
    return (index >= 0 && index <= pfstate->mpMap->mNodeCount)
        ? (PathSndNode_t *)((unsigned char *)pfstate->mpMap + pfstate->mpNodeOffsets[index] * 4) : 0;
}

static inline PathSndNode_t *_PathSndGetNode(int index)
{
    PathSndNode_t *node;
    if (index < 0 || index > pfstate->mpMap->mNodeCount)
        node = 0;
    else
        node = (PathSndNode_t *)((unsigned char *)pfstate->mpMap + pfstate->mpNodeOffsets[index] * 4);
    return node;
}

namespace Path {

class PathToSnd : public IPathToSnd {
public:
    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    PathToSnd();
    virtual ~PathToSnd();
    virtual int CreateStreamTrack(IPathTrack **track, int count, float seconds, int rate);
    virtual int CreateBankTrack(IPathTrack **track, int count);
    virtual void GetDefaultPlayOpts(void *opts);
};

class PathTrackSnd : public IPathTrack {
public:
    PathTrackName_t mName;
    PathTrackPath_t mPath;
    SndPlayOpts_t mPlayOpts;
    int mPitchMult;

    PathTrackSnd();
    virtual ~PathTrackSnd();
    virtual void UpdateStatus() { mDirty = 1; }
    virtual int Pause(int pause);
    virtual int GetPathStatus(PathStatus_t *status);
    virtual int ReadyForNewRequest();
    virtual int TimeBuffered();
    virtual int GetVolume();
    virtual int SetVolume(int volume);
    virtual int SetDryLevel(int level);
    virtual int SetFXSendLevel(int send, int level);
    virtual void SetName(const char *name);
    virtual void StreamCache(char *data, int size) {}
    virtual int ModifyHold(int hold) { return -1; }
    virtual int GetPitchMult() { return mPitchMult; }
};

class PathTrackSndStream : public PathTrackSnd {
public:
    void *mpBuffer;
    int mMaxRequests;
    PathStreamRequest_t *mpRequests;
    char *mpCache;
    int mCacheSize;

    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    PathTrackSndStream(int count);
    virtual ~PathTrackSndStream();
    virtual int AttachStreamInstance(int handle, char *buffer);
    virtual int DetachStreamInstance();
    virtual void CheckStatus();
    virtual int SetVolume(int volume);
    virtual int SetDryLevel(int level);
    virtual int SetFXSendLevel(int send, int level);
    virtual int ModifyHold(int hold);
    virtual int SetPitchMult(int pitch);
    virtual void StreamCache(char *data, int size);
    virtual int TimeRemaining(int index);
    virtual int Play(int node, unsigned int offset, int count, int key, unsigned int length);
    virtual int Stop();
    virtual void SetFilePath(PathTrackFile_t *path);
};

class PathTrackSndBank : public PathTrackSnd {
public:
    int unk_0x118;
    int mPatch;
    unsigned int mLength;
    int mVoice;
    int mRemaining;
    int mNode;
    int mBeat;

    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    PathTrackSndBank(int count);
    virtual ~PathTrackSndBank();
    virtual int AttachSubBank(int index, int bank);
    virtual int DetachSubBank(int index);
    virtual void CheckStatus();
    virtual int SetVolume(int volume);
    virtual int SetDryLevel(int level);
    virtual int SetFXSendLevel(int send, int level);
    virtual int SetPitchMult(int pitch);
    virtual int TimeRemaining(int index);
    virtual int Play(int node, unsigned int offset, int count, int key, unsigned int length);
    virtual int Stop();
    virtual int AddSubBank(int index, char *data);
    virtual int AddSubBankDone(int index);
    virtual PathSubBankState_t *GetSubBankPtr(int index);
    virtual PathSubBankState_t *GetAvailSubBankPtr();
    virtual int RemoveSubBank(int index);
    virtual int DetachSubBankHeader(int index, int header);
};

}

void PATH_vectortosnd()
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *format = "%s  %s";

    if (Path::IPathToSnd::sndimp != 0) {
        delete Path::IPathToSnd::sndimp;
    }
    Path::IPathToSnd::sndimp = new Path::PathToSnd;
}

namespace Path {

int PathToSnd::CreateStreamTrack(IPathTrack **track, int count, float seconds, int rate)
{
    PathTrackSndStream *stream = new PathTrackSndStream(count);

    if (seconds != 0.0f) {
        int requests = (int)(seconds * 15.0f) + 1;
        int size = (int)(seconds * ((float)rate * 1000.0f));
        void *buffer;
        int handle;

        size += SNDSTRM_overhead(count, requests);
        if (size < IPathToReal::realimp->GetMinStreamBufferSize(count)) {
            size = IPathToReal::realimp->GetMinStreamBufferSize(count);
        }
        buffer = PATHI_memalloc(size);
        handle = -108;
        if (buffer != 0) {
            handle = fn_8026E280(stream->GetPlayOpts(), count, requests, buffer, size);
        }
        stream->AttachStreamInstance(handle, (char *)buffer);
    }
    *track = stream;
    return 0;
}

int PathToSnd::CreateBankTrack(IPathTrack **track, int count)
{
    *track = new PathTrackSndBank(count);
    return 0;
}

void *PathToSnd::operator new(unsigned int size)
{
    return PATHI_memalloc(size);
}

void PathToSnd::operator delete(void *p)
{
    PATHI_memfree(p);
}

PathToSnd::PathToSnd()
{
    SNDSYS_add100hzclient(PATHI_servicetimer);
}

PathToSnd::~PathToSnd()
{
    SNDSYS_remove100hzclient(PATHI_servicetimer);
}

void PathToSnd::GetDefaultPlayOpts(void *opts)
{
    SNDplaysetdef((SndPlayOpts_t *)opts);
    ((SndPlayOpts_t *)opts)->m5 = 0;
}

PathTrackSnd::PathTrackSnd()
{
    mName.mText[0] = 0;
    mPath.mText[0] = 0;
    mpPlayOpts = &mPlayOpts;
    IPathToSnd::sndimp->GetDefaultPlayOpts(&mPlayOpts);
    mHandle = -1;
    mPitchMult = mPlayOpts.mC;
}

PathTrackSnd::~PathTrackSnd()
{
}

int PathTrackSnd::GetPathStatus(PathStatus_t *status)
{
    PathSndNode_t *node;
    int beatLength;
    int barLength;

    if (mDirty) {
        CheckStatus();
    }
    beatLength = barLength = mStatus.mLength;
    node = _PathSndNodePtr(mStatus.mNode);
    if (node != 0 && node->mDivisions != 0) {
        mStatus.unk_0x1C = mStatus.mLength / node->mDivisions;
        beatLength = barLength / node->mDivisions;
        if (node->mBeats != 0) {
            mStatus.unk_0x20 = mStatus.mLength / (node->mBeats * node->mDivisions);
            barLength = barLength / (node->mBeats * node->mDivisions);
        }
    }
    {
        unsigned int remain = mStatus.mLength - mStatus.mPosition;
        mStatus.unk_0x8 = mStatus.unk_0x20 != 0 ? remain / mStatus.unk_0x20 + 1 : 0;
    }
    if (beatLength > 0) {
        mStatus.unk_0x28 = mStatus.mPosition % beatLength;
    } else {
        mStatus.unk_0x28 = 0;
    }
    if (barLength > 0) {
        mStatus.unk_0x2C = mStatus.mPosition % barLength;
    } else {
        mStatus.unk_0x2C = 0;
    }
    *status = mStatus;
    return 1;
}

int PathTrackSnd::ReadyForNewRequest()
{
    return mStatus.mReady;
}

int PathTrackSnd::TimeBuffered()
{
    return mStatus.mBuffered;
}

int PathTrackSnd::GetVolume()
{
    return mVolume;
}

int PathTrackSnd::SetVolume(int volume)
{
    int current;
    if ((unsigned int)volume > 127) {
        return -8;
    }
    current = GetVolume();
    if (current != volume && volume >= 0 && current >= 0) {
        return 0;
    }
    return -1;
}

int PathTrackSnd::SetDryLevel(int level)
{
    return 0;
}

int PathTrackSnd::SetFXSendLevel(int send, int level)
{
    return 0;
}

void PathTrackSnd::SetName(const char *name)
{
    mName = *(const PathTrackName_t *)name;
}

int PathTrackSnd::Pause(int pause)
{
    int arg = 0;
    int value = 0;
    if (mPitchMult > 0) {
        value = mPitchMult;
    } else if (mPlayOpts.mC != 0) {
        value = mPlayOpts.mC;
    }
    if (pause == 0) {
        arg = value = mPitchMult;
    }
    SetPitchMult(arg);
    mPitchMult = value;
    return 0;
}

void *PathTrackSndBank::operator new(unsigned int size)
{
    return PATHI_memalloc(size);
}

void PathTrackSndBank::operator delete(void *p)
{
    PATHI_memfree(p);
}

PathTrackSndBank::PathTrackSndBank(int count)
{
    int size = count * sizeof(PathSubBankState_t);
    int i;

    mPatch = -1;
    mRemaining = 0;
    mLength = 0;
    mVoice = -1;
    mpSubBanks = (PathSubBankState_t *)PATHI_memalloc(size);
    memset(mpSubBanks, 0, size);
    for (i = 0; i < count; i++) {
        mpSubBanks[i].mIndex = -1;
    }
    mMaxSubBanks = count;
}

PathTrackSndBank::~PathTrackSndBank()
{
    int i;
    for (i = 0; i < GetNumSubBanks(); i++) {
        RemoveSubBank(i);
    }
    if (mpSubBanks != 0) {
        PATHI_memfree(mpSubBanks);
    }
}

int PathTrackSndBank::AttachSubBank(int index, int bank)
{
    PathSubBankState_t *state;

    if (GetSubBankPtr(index) != 0) {
        return -18;
    }
    state = GetAvailSubBankPtr();
    if (state == 0) {
        return -13;
    }
    state->mIndex = index;
    state->mBank = bank;
    state->mAttached = state->mReady = 1;
    state->mPriority = 100;
    return 0;
}

int PathTrackSndBank::DetachSubBank(int index)
{
    PathSubBankState_t *state = GetSubBankPtr(index);
    int bank;
    if (state == 0) {
        return -8;
    }
    bank = state->mBank;
    RemoveSubBank(index);
    return bank;
}

void PathTrackSndBank::CheckStatus()
{
    SndSampleAttr_t attr;
    SndSampleDesc_t desc;
    SndSampleFormat_t format;
    PathSndNode_t *node;
    int result;
    int elapsed; /* ms played so far (voice metric * 10) */
    int beatsLeft;
    int length;
    int rate;

    memset(&mStatus, 0, sizeof(mStatus));
    mStatus.mVoice = -1;
    elapsed = 0;
    mStatus.unk_0xC = -1;
    mStatus.mNode = -1;
    result = -8;
    mStatus.mRemaining = -1;
    beatsLeft = 0;
    mStatus.mReady = 1;
    if (mHandle >= 0) {
        mDirty = 1;
        SNDSYS_entercritical();
        if (mPatch >= 0 && mVoice >= 0) {
            length = 0;
            result = SNDBANK_patchinfo(mHandle, mPatch, &format, &attr, &desc);
            if (result >= 0) {
                elapsed = AudioVoiceGetMaxMetric(mVoice);
                if (elapsed < 0) {
                    mVoice = mHandle = -1;
                    goto done;
                }
                elapsed *= 10;
                rate = format.mRate;
                length = (int)((float)desc.mFrames / (float)rate * 1000.0f);
                node = _PathSndGetNode(mNode);
                if (node->mFlags & 0x40000000) {
                    int lastBeat = node->mBeats - 1;
                    mStatus.mLength = length * (lastBeat + 1);
                    beatsLeft = lastBeat - mBeat;
                } else {
                    mStatus.mLength = length;
                }
            } else {
                mVoice = mHandle = mNode = -1;
            }
            mStatus.mBuffered = length;
            mLength = length;
            mRemaining = elapsed;
            mStatus.mRemaining = elapsed;
            mStatus.mPosition = length * beatsLeft + elapsed;
            mStatus.unk_0x8 = mBeat;
            mStatus.unk_0xC = mStatus.mNode = mNode;
            mStatus.mVoice = mVoice;
            mVolume = SNDCTRL_getprogvol(mVoice);
        }
    done:
        mResult = result;
        mDirty = 0;
        SNDSYS_leavecritical();
    }
}

int PathTrackSndBank::SetVolume(int volume)
{
    int status = PathTrackSnd::SetVolume(volume);
    int result = 0;
    if (status == 0) {
        SNDSYS_entercritical();
        result = SNDvol(mVoice, volume);
        SNDSYS_leavecritical();
        mVolume = volume;
        mPlayOpts.m0 = volume;
    }
    return result;
}

int PathTrackSndBank::SetDryLevel(int level)
{
    int status = PathTrackSnd::SetDryLevel(level);
    int result = 0;
    if (status == 0) {
        SNDSYS_entercritical();
        result = SNDCTRL_drylevel(mVoice, level);
        SNDSYS_leavecritical();
        mDryLevel = level;
        mPlayOpts.m4 = level;
    }
    return result;
}

int PathTrackSndBank::SetFXSendLevel(int send, int level)
{
    int status = PathTrackSnd::SetFXSendLevel(send, level);
    int result = 0;
    if (status == 0) {
        SNDSYS_entercritical();
        result = SNDfxlevel(mVoice, send, level);
        SNDSYS_leavecritical();
        mFXSendLevel = level;
        mPlayOpts.m5 = level;
    }
    return result;
}

int PathTrackSndBank::SetPitchMult(int pitch)
{
    int result;
    SNDSYS_entercritical();
    result = SNDpitchmult(mVoice, pitch);
    SNDSYS_leavecritical();
    mPitchMult = pitch;
    mPlayOpts.mC = pitch;
    return result;
}

int PathTrackSndBank::TimeRemaining(int index)
{
    if (index == 0) {
        return mStatus.mRemaining;
    }
    return -1;
}

int PathTrackSndBank::Play(int node, unsigned int offset, int count, int key, unsigned int length)
{
    PathSubBankState_t *state = GetSubBankPtr(offset >> 16);
    int bank;
    int result;

    if (state == 0 || state->mBank < 0) {
        return -1;
    }
    mPatch = (offset & 0xFFFF) + count - 1;
    SNDSYS_entercritical();
    bank = state->mBank;
    if (mHandle != bank && mHandle >= 0) {
        SNDstop(mHandle);
    }
    result = SNDBANK_play(state->mBank, mPatch, &mPlayOpts);
    mHandle = bank;
    SNDSYS_leavecritical();
    if (result >= 0) {
        mNode = node;
        mBeat = count - 1;
        mLength = length;
        mVoice = result;
        state->mLastPlayed = gPathMilliseconds;
        mDirty = 1;
    }
    return result;
}

int PathTrackSndBank::Stop()
{
    int result;
    SNDSYS_entercritical();
    result = SNDstop(mHandle);
    SNDSYS_leavecritical();
    mStatus.mReady = 1;
    mVoice = -1;
    mHandle = -1;
    UpdateStatus();
    return result;
}

int PathTrackSndBank::AddSubBank(int index, char *data)
{
    int result = -8;
    PathSubBankState_t *state = GetSubBankPtr(index);
    if (state != 0) {
        result = SNDBANK_asyncloadmem(&state->mBank, data);
    }
    return result;
}

int PathTrackSndBank::AddSubBankDone(int index)
{
    int result = 0;
    PathSubBankState_t *state = GetSubBankPtr(index);
    if (state != 0) {
        result = SNDBANK_asyncloadmemdone();
    }
    return result;
}

PathSubBankState_t *PathTrackSndBank::GetSubBankPtr(int index)
{
    int i;
    PathSubBankState_t *state;
    for (i = 0; i < GetMaxSubBanks(); i++) {
        // FAKEMATCH: integer address arithmetic; it keeps the target operand order of the slot address add (offset first)
        state = (PathSubBankState_t *)(i * sizeof(PathSubBankState_t) + (int)mpSubBanks);
        if (state->mIndex == index) {
            return state;
        }
    }
    return 0;
}

PathSubBankState_t *PathTrackSndBank::GetAvailSubBankPtr()
{
    int i;
    PathSubBankState_t *state;
    for (i = 0; i < GetMaxSubBanks(); i++) {
        // FAKEMATCH: integer address arithmetic; it keeps the target operand order of the slot address add (offset first)
        state = (PathSubBankState_t *)(i * sizeof(PathSubBankState_t) + (int)mpSubBanks);
        if (state->mIndex < 0) {
            return state;
        }
    }
    return 0;
}

int PathTrackSndBank::RemoveSubBank(int index)
{
    int result = 0;
    PathSubBankState_t *state = GetSubBankPtr(index);
    if (state != 0 && state->mBank != -1) {
        if (state->mAttached == 0) {
            result = SNDbankremove(state->mBank);
            PATHI_memfree(state->mpHeader);
        }
        memset(state, 0, sizeof(*state));
        state->mBank = -1;
    }
    return result;
}

int PathTrackSndBank::DetachSubBankHeader(int index, int header)
{
    int result = -8;
    void *copy;
    PathSubBankState_t *state = GetSubBankPtr(index);
    if (state != 0 && state->mBank != -1 && header == 7) {
        copy = PATHI_memalloc(SNDbankheadersize(state->mBank));
        if (copy != 0) {
            SNDbankheadercopy(copy, state->mBank);
            result = 0;
            PATHI_memfree(state->mpHeader);
            state->mpHeader = copy;
        }
    }
    return result;
}

void *PathTrackSndStream::operator new(unsigned int size)
{
    return PATHI_memalloc(size);
}

void PathTrackSndStream::operator delete(void *p)
{
    PATHI_memfree(p);
}

PathTrackSndStream::PathTrackSndStream(int count)
{
    int i;

    mMaxRequests = count;
    if (count <= 0) {
        mMaxRequests = 1;
    }
    mpRequests = (PathStreamRequest_t *)PATHI_memalloc(mMaxRequests * sizeof(PathStreamRequest_t));
    if (mpRequests == 0) {
        mMaxRequests = 0;
    }
    for (i = 0; i < mMaxRequests; i++) {
        mpRequests[i].mLength = mpRequests[i].mPlayed = 0;
        mpRequests[i].mRequest = -1;
    }
    mpCache = 0;
    mCacheSize = 0;
    mpBuffer = 0;
}

PathTrackSndStream::~PathTrackSndStream()
{
    if (mHandle >= 0) {
        fn_8026E2A8(mHandle);
        if (mpBuffer != 0) {
            PATHI_memfree(mpBuffer);
        }
    }
    PATHI_memfree(mpRequests);
}

int PathTrackSndStream::AttachStreamInstance(int handle, char *buffer)
{
    if (mHandle >= 0) {
        return -18;
    }
    mHandle = handle;
    mDirty = 1;
    mpBuffer = buffer;
    return 0;
}

int PathTrackSndStream::DetachStreamInstance()
{
    int handle = mHandle;
    if (handle < 0) {
        return -18;
    }
    mHandle = -1;
    mpBuffer = 0;
    return handle;
}

void PathTrackSndStream::CheckStatus()
{
    SndStreamStatus_t status;
    SndStreamRequestStatus_t request;
    unsigned int played;
    int i;

    memset(&mStatus, 0, sizeof(mStatus));
    mStatus.mVoice = -1;
    mStatus.unk_0xC = -1;
    mStatus.mNode = -1;
    if (mHandle >= 0) {
        mDirty = 1;
        mStatus.mReady = 1;
        SNDSYS_entercritical();
        SNDSTRM_status(mHandle, &status);
        mStatus.mRemaining = 0;
        mStatus.mBuffered = 0;
        if (status.mRequests >= mMaxRequests) {
            mStatus.mReady = 0;
        }
        for (i = 0; i < mMaxRequests; i++) {
            mpRequests[i].mPlayed = 0;
            if (mpRequests[i].mRequest >= 0) {
                SNDSTRM_requeststatus(mpRequests[i].mRequest, &request);
                switch (request.mState) {
                case 1:
                    mpRequests[i].mPlayed = mpRequests[i].mLength;
                    mStatus.mRemaining += mpRequests[i].mLength;
                    mStatus.mBuffered += request.unk_0xC;
                    mStatus.mReady = 0;
                    break;
                case 0:
                case 2:
                    mpRequests[i].mPlayed = request.unk_0x8;
                    if (request.unk_0x4 == 0 && request.unk_0x8 == 0) {
                        mpRequests[i].mPlayed = mpRequests[i].mLength;
                    }
                    played = mpRequests[i].mPlayed;
                    mStatus.mRemaining += played;
                    mStatus.mBuffered += request.unk_0xC;
                    mStatus.mPosition = played;
                    if (request.unk_0xC < request.unk_0x8) {
                        mStatus.mReady = 0;
                    }
                    break;
                default:
                    mpRequests[i].mRequest = -1;
                    mpRequests[i].mNode = -1;
                    break;
                }
                if (mpRequests[i].mNode >= 0) {
                    mStatus.mNode = mpRequests[i].mNode;
                    mStatus.unk_0x8 = mpRequests[i].unk_0x10;
                }
            }
        }
        mStatus.unk_0xC = mpRequests[0].mNode;
        mStatus.mVoice = mpRequests[0].mRequest;
        mStatus.mLength = mpRequests[0].mLength;
        mVolume = SNDSTRM_getprogvol(mHandle);
        mDirty = 0;
        SNDSYS_leavecritical();
    }
}

int PathTrackSndStream::SetVolume(int volume)
{
    int result = 0;
    if (PathTrackSnd::SetVolume(volume) == 0) {
        SNDSYS_entercritical();
        result = SNDSTRM_setvol(mHandle, -1, (float)volume * (1.0f / 127.0f));
        SNDSYS_leavecritical();
        mVolume = volume;
        mPlayOpts.m0 = volume;
    }
    return result;
}

int PathTrackSndStream::SetDryLevel(int level)
{
    int result = 0;
    if (PathTrackSnd::SetDryLevel(level) == 0) {
        SNDSYS_entercritical();
        result = SNDSTRM_drylevel(mHandle, level);
        SNDSYS_leavecritical();
        mDryLevel = level;
    }
    return result;
}

int PathTrackSndStream::SetFXSendLevel(int send, int level)
{
    int result = 0;
    if (PathTrackSnd::SetFXSendLevel(send, level) == 0) {
        SNDSYS_entercritical();
        result = SNDSTRM_fxlevel(mHandle, send, level);
        SNDSYS_leavecritical();
        mFXSendLevel = level;
    }
    return result;
}

int PathTrackSndStream::ModifyHold(int hold)
{
    return SNDSTRM_modifyhold(mpRequests->mRequest, hold);
}

int PathTrackSndStream::SetPitchMult(int pitch)
{
    int result;
    SNDSYS_entercritical();
    result = SNDSTRM_pitchmult(mHandle, pitch);
    SNDSYS_leavecritical();
    mPlayOpts.mC = pitch;
    mPitchMult = pitch;
    return result;
}

void PathTrackSndStream::StreamCache(char *data, int size)
{
    mpCache = data;
    mCacheSize = size;
}

int PathTrackSndStream::TimeRemaining(int index)
{
    PathStreamRequest_t *request;
    if (index < 0) {
        return mStatus.mRemaining;
    }
    if (index < mMaxRequests) {
        // FAKEMATCH: integer address arithmetic; it keeps the target operand order of the request address add (offset first)
        request = (PathStreamRequest_t *)(index * sizeof(PathStreamRequest_t) + (int)mpRequests);
        if (request->mRequest >= 0) {
            return request->mPlayed;
        }
    }
    return -8;
}

int PathTrackSndStream::Play(int node, unsigned int offset, int count, int key, unsigned int length)
{
    int result;
    int i;

    if (mpCache != 0 && (int)(offset << 7) < mCacheSize) {
        result = AudioVoiceForwardData(mHandle, key, mpCache, offset << 7);
    } else {
        result = fn_8026E364(mHandle, key, &mPath, offset << 7);
    }
    if (result >= 0) {
        unk_0x18 = mMaxRequests;
        for (i = mMaxRequests - 1; i > 0; i--) {
            mpRequests[i] = mpRequests[i - 1];
            if (mpRequests[i].mRequest < 0) {
                unk_0x18 = i - 1;
            }
        }
        mpRequests[0].mRequest = result;
        mpRequests[0].mLength = length;
        mpRequests[0].mNode = node;
        mpRequests[0].unk_0x10 = -1;
        mStatus.mReady = 0;
    }
    mDirty = 1;
    return result;
}

int PathTrackSndStream::Stop()
{
    int result;
    SNDSYS_entercritical();
    result = fn_8026E388(mHandle);
    SNDSYS_leavecritical();
    mStatus.mReady = 1;
    UpdateStatus();
    return result;
}

void PathTrackSndStream::SetFilePath(PathTrackFile_t *path)
{
    mPath = *(PathTrackPath_t *)path;
}

}

extern "C" void PATHI_streamlowpass(void *track, int value)
{
    SNDSYS_entercritical();
    SNDSTRM_lowpass(((Path::PathTrackSndStream *)track)->mHandle, value);
    SNDSYS_leavecritical();
}
