/* PATH music nodes (pathnode.c): beat timing, choosing the synchronization point for a branch and
   moving a track from node to node. */

#include "engine/pathlib.h"

// Locate the stream data for a playable node; control nodes have no sample offset.
extern "C" int PATHI_sampleoffset(int index)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int result = 0;
    if (index < 0 || index >= pfstate->mUnknown18->mUnknown12)
        return 0;
    PathMapEntry_t *p = PATHI_getnode(index);
    int value = p->mSample;
    if (value > 0) {
        int slot = value - 1;
        result = pfstate->mUnknown3C[slot * 2];
    }
    return result;
}

// Combine the node meter with the backend playback position for beat scheduling.
extern "C" int PATHI_beatinfo(PathTrack_t *p, PathBeatInfo_t *info)
{
    PathBeatStatus_t status;
    if (p->mUnknown4 < 0)
        return -1;
    PathMapEntry_t *node = PATHI_getnode(p->mUnknown4);
    p->mUnknown100->GetPathStatus(&status);
    if (info) {
        info->mBeatsPerBar = (node->mTimingAndBranches >> 8) & 15;
        info->mBeatUnit = (node->mLinkAndSync >> 4) & 15;
        info->mBeat = status.mBeat;
        info->mBeatDuration = status.mBeatDuration;
        info->mBarDuration = status.mBarDuration;
        info->mNodeDuration = status.mNodeDuration;
        info->mBarRemaining = status.mBarRemaining;
        info->mBeatRemaining = status.mBeatRemaining;
        info->mRemaining = status.mRemaining;
    }
    return status.mBeat;
}

// Calculate the delay to the requested beat subdivision within the current bar.
extern "C" int PATHI_calcwaitbeat(int a, int b, int c, PathBeatInfo_t *info)
{
    float ratio = (float)info->mBeatUnit / (float)b;
    float wait = ratio * (float)a;
    int start = info->mBarRemaining;
    int range = info->mBarDuration - start;
    int beat = (int)(ratio * (float)c * (float)info->mBeatDuration);
    int pos = beat;
    if (pos < range)
        while (pos < start)
            pos += (int)(wait * (float)info->mBeatDuration);
    if (pos > info->mBarDuration)
        pos = info->mBarDuration + beat;
    return pos - range;
}

// Choose a branch beat and convert its nonzero delay to the PATH clock.
extern "C" int PATHI_choosesynchtime(int index, const PathFindNode_t &find, const PathBeatInfo_t &info, unsigned int &time)
{
    if (find.mNode < 0)
        return 1;
    PathMapEntry_t *node;
    if (index < 0 || index > pfstate->mUnknown18->mUnknown12)
        node = 0;
    else
        node = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown1C[index] * 4);
    PathStreamRecord_t record = ((PathStreamRecord_t *)pfstate->mUnknown3C)[node->mSample - 1];
    float length = (float)record.mDuration;
    unsigned int free = node->mFlagsAndEvent >> 31;
    if (node->mTimingAndBranches & 0xF00)
        length /= (float)(((node->mTimingAndBranches >> 8) & 15) * (unsigned char)node->mTimingAndBranches);
    if (free)
        length = (float)info.mBeatDuration;
    int range = info.mNodeDuration - info.mRemaining;
    unsigned int start = info.mRemaining;
    int beat = (int)((float)start / length);
    int beats = (int)((float)range / length);
    int result = -1;
    switch (find.mBits8.mSync) {
    case 1:
        ++beats;
        time = (int)((float)beats * length) % range;
        beats %= (node->mTimingAndBranches >> 8) & 15;
        result = beats + 1;
        break;
    case 2:
        time = start % (int)((float)beat * length);
        result = ((node->mTimingAndBranches >> 8) & 15) - beat % ((node->mTimingAndBranches >> 8) & 15) + 1;
        break;
    case 3:
        time = range % (int)length;
        result = 1;
        break;
    }
    if (time)
        time += gPathMilliseconds;
    return result;
}

// Accumulate queued durations until the backend reports the end of its queue.
extern "C" int PATHI_timeremaining(PathTrack_t *p)
{
    int sum = 0;
    for (int i = 0;; ++i) {
        int value = p->mUnknown100->TimeRemaining(i);
        if (value >= 0)
            sum += value;
        else
            break;
    }
    return sum;
}

// Use the nearest branch endpoint when no authored range contains the control value.
extern "C" int PATHI_pickclosestbranch(int count, int value, PathFindBranch_t *entries)
{
    if (count <= 0)
        return -1;
    int best = 127;
    PathFindBranch_t *found = entries;
    for (int i = 0; i < count; ++i) {
        int a = entries[i].mLow - value;
        int b = entries[i].mHigh - value;
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (b > a) b = a;
        if (best > b) {
            best = b;
            found = &entries[i];
        }
    }
    return found->mNode;
}

// Select an outgoing branch, using the active loop counter when this is its loop node.
extern "C" int PATHI_nextnode(int index, int value, int advance)
{
    int result = -1;
    PathMapEntry_t *node;
    if (index < 0 || !(node = PATHI_getnode(index)))
        return -1;
    PathFindBranch_t *branches = (PathFindBranch_t *)((unsigned char *)node + 16);
    PathTrack_t *track = pfstate->mUnknown40[node->mBits0.mTrack];
    if (track->mUnknown6 == index) {
        int loop = track->mUnknown8.bits.mLoop;
        value = loop & 127;
        if (node->mBits0.mLoop > 0 && advance) {
            if ((track->mUnknown8.bits.mLoop = loop - 1) == -1)
                track->mUnknown6 = -1;
        }
    }
    for (unsigned int i = 0; i < node->mBits4.mBranches; ++i) {
        if (value >= branches[i].mLow && value <= branches[i].mHigh) {
            result = (short)branches[i].mNode;
            break;
        }
    }
    if (result < 0)
        result = PATHI_pickclosestbranch(node->mBits4.mBranches, value, branches);
    return result;
}

// Follow routing and control nodes until a playable sample or the end of the path.
extern "C" int PATHI_enternode(int track, int index, int value, int advance)
{
    int first = value;
    if (index < 0)
        return -1;
    index = (short)PATHI_routenode(track, index);
    if (index < 0)
        return -1;
    PathMapEntry_t *node;
    if (index > pfstate->mUnknown18->mUnknown12)
        node = 0;
    else
        node = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown1C[index] * 4);
    if (!node)
        return -1;
    PathTrack_t *p = pfstate->mUnknown40[node->mBits0.mTrack];
    while (node->mSample <= 0) {
        if (advance) {
            if (node->mSample == 0) {
                p->mUnknown34 = (unsigned int *)node;
                if (node->mBits4.mKind == 1)
                    value = PATHI_random() & 127;
                if (songprogress)
                    songprogress(pfstate->mUnknown14, index);
            } else if (node->mSample == -1) {
                if (node->mBits0.mLoop && index != p->mUnknown6) {
                    p->mUnknown8.bits.mLoop = node->mBits0.mLoop;
                    p->mUnknown6 = index;
                }
            } else if (node->mSample == -2)
                value = PATHI_random() & 127;
            else if (node->mSample == -3) {
                PathMapEntry_t *event = PATHI_findevent(node->mFlagsAndEvent >> 8);
                if (event) {
                    PathEvent_t *copy = PATHI_copyevent((PathEvent_t *)event);
                    PATHI_addevent(pfstate->mUnknown14 | 0xF0000000, copy);
                }
            }
        }
        index = PATHI_nextnode(index, value, advance);
        if (index < 0 || (index = (short)PATHI_routenode(track, index)) < 0) {
            if (songprogress && advance && track >= 0)
                songprogress(pfstate->mUnknown14, index);
            return -1;
        }
        if (index > pfstate->mUnknown18->mUnknown12)
            node = 0;
        else
            node = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown1C[index] * 4);
        if (!node)
            return -1;
        value = first;
    }
    return (short)PATHI_routenode(track, index);
}

// Apply route substitutions in order so later entries can redirect an earlier result.
extern "C" int PATHI_routenode(int index, int value)
{
    if (index < 0)
        return value;
    PathMapEntry_t *p = PATHI_getnode(index);
    int key = (p->mTimingAndBranches >> 20) & 255;
    if (!key)
        return value;
    {
        unsigned int end = pfstate->mUnknown30[key];
        unsigned int start = pfstate->mUnknown30[key - 1];
        int count = end - start;
        int *words = (int *)pfstate->mUnknown18 + start;
        for (int i = 0; i < count; ++i) {
            int word = words[i];
            if (value == word >> 16)
                value = word & 0xFFFF;
        }
    }
    return value;
}

// Advance and queue a track, restoring its state and the shared queue on failure.
extern "C" void PATHI_seeknextnode(int index)
{
    int queued = pfstate->mUnknown1100;
    PathTrack_t *p = pfstate->mUnknown40[index];
    int next = -1;
    if (p->mUnknown4 < 0)
        return;
    PathTrack_t saved = *p;
    PathMapEntry_t *node = PATHI_getnode(p->mUnknown4);
    int beat = -1;
    if (p->mUnknown8.bits.flag10)
        beat = 1;
    int loop = p->mUnknown8.bits.mUnknown7;
    if (loop > 0 && (node->mFlagsAndEvent & 0x40000000) && loop <= (int)(node->mBits4.mBeats * (unsigned char)node->mTimingAndBranches)) {
        beat = loop;
        next = p->mUnknown4;
    } else if (p->mUnknown4 >= 0) {
        next = PATHI_nextnode(p->mUnknown4, p->mUnknown1, 1);
        if (songprogress && next < 0)
            songprogress(pfstate->mUnknown14, next);
    }
    if (next >= 0)
        next = PATHI_enternode(p->mUnknown4, next, p->mUnknown1, 1);
    p->mUnknown4 = next;
    p->mUnknown8.bits.mUnknown7 = next >= 0 ? (signed char)beat : -1;
    int result = PATHI_queuenode(p);
    if (result < 0 && result != -9999) {
        pfstate->mUnknown1100 = queued;
        *p = saved;
    }
}

// Prepare node timing and synchronization before queueing the sample on its backend.
extern "C" int PATHI_queuenode(PathTrack_t *p)
{
    PathTrack_t *master = 0;
    int beats = 0;
    unsigned int length = 0;
    if (pfstate->mUnknown0 >= 0)
        master = pfstate->mUnknown40[pfstate->mUnknown0];
    if (p->mUnknown4 < 0) {
        // FAKEMATCH: reset-store order measured (five of the 24 orders compile to the target's store schedule); independent stores, same behavior
        p->mUnknown34 = 0;
        p->mUnknown4C = -1;
        p->mUnknown4 = -1;
        p->mUnknown8.bits.mUnknown7 = -1;
        return 0;
    }
    PathMapEntry_t *node = PATHI_getnode(p->mUnknown4);
    p->mUnknown34 = (unsigned int *)PATHI_getnode(node->mLinkAndSync >> 16);
    length = ((PathStreamRecord_t *)pfstate->mUnknown3C)[node->mSample - 1].mDuration;
    p->mUnknown3C = length;
    p->mUnknown38 = length;
    if ((unsigned char)node->mTimingAndBranches)
        p->mUnknown3C = length / (unsigned char)node->mTimingAndBranches;
    if (node->mTimingAndBranches & 0xF00)
        p->mUnknown38 /= node->mBits4.mBeats * (unsigned char)node->mTimingAndBranches;
    if (!p->mUnknown8.bits.flag10)
        p->mUnknown8.bits.mUnknown7 = -1;
    else {
        bool slave = master && master != p;
        PathMapEntry_t *next = (PathMapEntry_t *)p->mUnknown34;
        int sync = 0;
        if ((int)next->mFlagsAndEvent < 0 && slave)
            sync = 1;
        int bar = (((PathMapEntry_t *)p->mUnknown34)->mFlagsAndEvent >> 30) & 1;
        PathBeatInfo_t info;
        info.mBeatRemaining = 0;
        if (slave)
            PATHI_beatinfo(master, &info);
        if (p->mUnknown8.bits.mUnknown7 < 0 && (((PathMapEntry_t *)p->mUnknown34)->mLinkAndSync & 12) && slave) {
            p->mUnknown8.bits.mUnknown7 = PATHI_choosesynchtime(p->mUnknown4, *(PathFindNode_t *)p->mUnknown34, info, p->mUnknown40);
            if (debugchannels & 1)
                PATHI_printf("JUST SET nextbeattime %d nodebeat %d\n", p->mUnknown40, p->mUnknown8.bits.mUnknown7);
            return 0;
        }
        if (p->mUnknown8.bits.mUnknown7 <= 0)
            p->mUnknown8.bits.mUnknown7 = 1;
        p->mUnknown40 = 0;
        beats = p->mUnknown8.bits.mUnknown7;
        if (sync && info.mBeatRemaining)
            p->mUnknown40 = info.mBeatRemaining + gPathMilliseconds;
        if (!bar || p->mUnknown8.bits.mUnknown7++ >= (int)(node->mBits4.mBeats * (unsigned char)node->mTimingAndBranches))
            p->mUnknown8.bits.mUnknown7 = 0;
        if (bar)
            length /= node->mBits4.mBeats * (unsigned char)node->mTimingAndBranches;
    }
    int offset = PATHI_sampleoffset(p->mUnknown4);
    return p->mUnknown4C = p->mUnknown100->Play(p->mUnknown4, offset, beats, 0, length);
}
