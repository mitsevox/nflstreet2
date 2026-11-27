/* PATH tracks (pathtrack.c): creates and initializes stream and bank tracks, finds a track by its
   handle, reports track counts and status, and the Path::IPathTrack base class defaults. */

#include <string.h>
#include "engine/pathfinder.h"
#include "engine/pathlib.h"

extern "C" int PATH_createstreamtrack(int flags, PathfinderTrackData_t *data, int value)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = PATHI_createtrack(flags, data);
    if (result >= 0) {
        PathTrack_t *p = PATHI_gettrackptr(flags);
        if (p)
            p->mUnknown8.halves.high = value;
    }
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" IPathTrack *PATH_createstreamimp(int flags, int a, float b)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    if (!PATHI_switchvoice(flags))
        return 0;
    IPathTrack *track = 0;
    PathTrack_t *p = PATHI_gettrackptr(flags);
    if (p) {
        int rate = PATHI_bytesperms(p->mUnknown0);
        int result = Path::IPathToSnd::sndimp->CreateStreamTrack(&track, a, b, rate);
        if (track && result >= 0) {
            p->mUnknown100 = track;
            track->SetName(p->mUnknownD0);
            track->SetFilePath(&p->mUnknown50);
            track->SetTrackInfo(PATHI_trackinfo(p->mUnknown0));
        }
    }
    pfstate = 0;
    --pflock;
    return track;
}

extern "C" int PATH_createbanktrack(int flags, PathfinderTrackData_t *data, int value)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = PATHI_createtrack(flags, data);
    if (result >= 0) {
        PathTrack_t *p = PATHI_gettrackptr(flags);
        p->mUnknown104 = value;
        p->mUnknown8.word |= 0x10;
    }
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" IPathTrack *PATH_createbankobject(int flags)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    if (!PATHI_switchvoice(flags))
        return 0;
    IPathTrack *track = 0;
    PathTrack_t *p = PATHI_gettrackptr(flags);
    if (p) {
        Path::IPathToSnd::sndimp->CreateBankTrack(&track, p->mUnknown104);
        if (track) {
            p->mUnknown8.halves.high = pfstate->mUnknown10;
            p->mUnknown100 = track;
            track->SetName(p->mUnknownD0);
            track->SetFilePath(&p->mUnknown50);
            track->SetTrackInfo(PATHI_trackinfo(p->mUnknown0));
        }
    }
    pfstate = 0;
    --pflock;
    return track;
}

extern "C" int PATHI_createtrack(int flags, PathfinderTrackData_t *data)
{
    if (!PATHI_switchvoice(flags))
        return -8;
    int result = PATHI_inittrack(flags, data);
    if (result < 0)
        return result;
    PathTrack_t *p = PATHI_gettrackptr(flags);
    pfstate->mUnknown40[p->mUnknown0] = p;
    return 0;
}

extern "C" int PATHI_inittrack(int flags, PathfinderTrackData_t *data)
{
    int track = 0;
    if (!(flags & 0x00FFFFFF) || !(flags & 0x0F000000) || !(flags & 0xF0000000))
        return -8;
    PathProject_t *bank = pfstate;
    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1, as in pathcontrol.c
    for (track = 0; track < 24 && (((flags >> track) ^ 1) & 1); ++track)
        ;
    if (bank->mUnknown40[track])
        return -13;
    PathTrack_t *p = (PathTrack_t *)PATHI_memalloc(sizeof(PathTrack_t));
    if (!p)
        return -108;
    memset(p, 0, sizeof(PathTrack_t));
    p->mUnknown0 = track;
    p->mUnknown8.bits.flag20 = 0;
    p->mUnknown2 = volscale;
    p->mUnknown3 = 127;
    // FAKEMATCH: the default stores below are in a measured order (sched1 tie-breaks), not one recovered from the original
    p->mUnknown4 = -1;
    p->mUnknown1A = -1;
    p->mUnknown18 = -1;
    p->mUnknown19 = -1;
    p->mUnknown26 = -1;
    p->mUnknown24 = -1;
    p->mUnknown25 = -1;
    p->mUnknown30 = -1;
    p->mUnknown31 = -1;
    p->mUnknown8.bits.mUnknown7 = -1;
    p->mUnknown110 = 1;
    p->mUnknown8.bits.mUnknown1 = defaultfxbus;
    p->mUnknown6 = -1;
    p->mUnknown4C = -1;
    p->mUnknownF0 = -1;
    p->mUnknownF4 = 0xBEDFACED;
    p->mUnknown8.bits.flag1 = (flags & 0xF0000000) == 0x10000000;
    memcpy(&p->mUnknown50, data, sizeof(PathTrackFile_t));
    strcpy(p->mUnknownD0, "TibTrack");
    pfstate->mUnknown40[track] = p;
    return track;
}

extern "C" PathTrack_t *PATHI_gettrackptr(unsigned int flags)
{
    unsigned int high = flags & 0xF0000000;
    unsigned int voice = flags & 0x0F000000;
    unsigned int bits = flags & 0x00FFFFFF;
    for (unsigned int i = 0; i < 4; ++i) {
        if (pfstates[i] && (pfstates[i]->mUnknown14 & high) &&
            (pfstates[i]->mUnknown14 & voice)) {
            for (int j = 0; j < 24; ++j) {
                if ((bits >> j) & 1)
                    return pfstates[i]->mUnknown40[j];
            }
        }
    }
    return 0;
}

extern "C" void PATHI_updatemastertrack(void)
{
    pfstate->mUnknown0 = -1;
    pfstate->mUnknown4 = 0;
    pfstate->mUnknown8 = 0;
    for (int i = 0; i < 24; ++i) {
        PathTrack_t *p = pfstate->mUnknown40[i];
        if (p && !(p->mUnknown8.word & 0x40)) {
            int active = 0;
            if (p->mUnknown4 >= 0 && p->mUnknown34)
                active = 1;
            if (active && pfstate->mUnknown4 < (p->mUnknown8.halves.high)) {
                pfstate->mUnknown4 = p->mUnknown8.halves.high;
                pfstate->mUnknown0 = i;
                pfstate->mUnknown8 = (*p->mUnknown34 >> 5) & 63;
            }
        }
    }
}

extern "C" int PATHI_countprojecttracks(unsigned int flags)
{
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if ((flags & (0x01000000 << i)) && pfstates[i]) {
            for (int j = 0; j < 24; ++j) {
                if (pfstates[i]->mUnknown40[j])
                    ++count;
            }
        }
    }
    return count;
}

extern "C" void PATHI_selectprojecttrack(PathTrack_t *p, int state)
{
    unsigned int id = p->mUnknown0;
    int found = state > 0;
    p->mUnknown8.bits.flag1 = state != 0;
    for (int i = 0; i < 4; ++i) {
        if (pfstates[i]) {
            PathTrack_t *other = pfstates[i]->mUnknown40[id];
            if (other && other != p) {
                other->mUnknown8.bits.flag1 = !found;
                found = 1;
            }
        }
    }
    if (!found)
        p->mUnknown8.bits.flag1 = 1;
}

extern "C" void PATHI_dispatchtrackstate(int state)
{
    for (int i = 0; i < 4; ++i) {
        if (pfstates[i] && PATHI_switchproject(i, 0xFFFFFFFF)) {
            for (int j = 0; j < 24; ++j) {
                PathTrack_t *p = pfstate->mUnknown40[j];
                if (p && !(p->mUnknown8.word & 0x40) && p->mUnknown100) {
                    if (state)
                        p->mUnknown100->UpdateStatus();
                    else
                        p->mUnknown100->CheckStatus();
                }
            }
        }
    }
}

IPathTrack::IPathTrack()
{
    mUnknown0 = 0;
    mUnknown4 = 0;
    mUnknown8 = 0;
    mUnknownC = 127;
    mUnknown10 = 127;
    mUnknown14 = 1;
    mUnknown18 = 0;
    mUnknown5C = 0;
    mUnknown20 = 0;
    mUnknown64 = 0;
    mUnknown60 = 0;
    mUnknown1C = 1;
    mUnknown58 = -1;
}

IPathTrack::~IPathTrack()
{
}

int IPathTrack::GetNumSubBanks()
{
    PathTrackInfo_t *p = mUnknown5C;
    int result;
    if (p)
        result = p->mUnknown4;
    else
        result = 0;
    return result;
}

int IPathTrack::GetMaxSubBanks()
{ return mUnknown60; }

PathSubBankState_t *IPathTrack::GetSubBankPtr(int index)
{ return 0; }

PathSubBankState_t *IPathTrack::GetAvailSubBankPtr()
{ return 0; }

int IPathTrack::AddSubBank(int index, char *data)
{ return -8; }

int IPathTrack::AddSubBankDone(int index)
{ return -8; }

int IPathTrack::DetachSubBankHeader(int index, int header)
{ return -8; }

int IPathTrack::RemoveSubBank(int index)
{ return -8; }

void IPathTrack::SetTrackInfo(PathTrackInfo_t *p)
{ mUnknown5C = p; }

int IPathTrack::GetVolume()
{ return mUnknown10; }

int IPathTrack::GetDryLevel()
{ return mUnknownC; }

int IPathTrack::GetFXSendLevel(int value)
{ return mUnknown8; }

int IPathTrack::GetHandle()
{ return mUnknown0; }

int IPathTrack::GetPlayOpts()
{ return mUnknown20; }

void IPathTrack::SetFilePath(PathTrackFile_t *path)
{}
