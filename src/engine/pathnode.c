/* PATH music nodes (pathnode.c): beat timing, choosing the synchronization point for a branch and
   moving a track from node to node. */

#include "engine/pathlib.h"

extern "C" int fn_801B6780(int index)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    if (index < 0 || index >= lbl_803EBB28->mUnknown18->mUnknown12)
        return 0;
    Record_801B6780 *p = (Record_801B6780 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    int result = 0;
    int value = p->mUnknown0;
    if (value > 0)
        result = lbl_803EBB28->mUnknown3C[(value - 1) * 2];
    return result;
}

extern "C" int PATHI_beatinfo(PathTrack_t *p, BeatInfo_801B67F8 *info)
{
    PathStatus_801B67F8 status;
    if (p->mUnknown4 < 0)
        return -1;
    Entry_801B63F0 *node = PATHI_getnode(p->mUnknown4);
    p->mUnknown100->vfn_07(&status);
    if (info) {
        info->mUnknown0 = node->mUnknown4 >> 8;
        info->mUnknown4b = node->mUnknown8 >> 4;
        info->mUnknown1 = status.mUnknown8;
        info->mUnknown4 = status.mUnknown20;
        info->mUnknown8 = status.mUnknown1C;
        info->mUnknownC = status.mUnknown18;
        info->mUnknown14 = status.mUnknown28;
        info->mUnknown10 = status.mUnknown2C;
        info->mUnknown18 = status.mUnknown24;
    }
    return status.mUnknown8;
}

extern "C" int PATHI_calcwaitbeat(int a, int b, int c, BeatInfo_801B67F8 *info)
{
    float ratio = (float)info->mUnknown4b / (float)b;
    float wait = (float)a;
    int start = info->mUnknown14;
    int range = info->mUnknown8 - start;
    int beat = (int)(ratio * (float)c * (float)info->mUnknown4);
    int pos = beat;
    if (pos < range)
        while (pos < start)
            pos += (int)(ratio * wait * (float)info->mUnknown4);
    if (pos > info->mUnknown8)
        pos = info->mUnknown8 + beat;
    return pos - range;
}

extern "C" int PATHI_choosesynchtime(int index, const FindNode_801B6A18 &find, const BeatInfo_801B67F8 &info, unsigned int &time)
{
    if (find.mUnknown8 < 0)
        return 1;
    Entry_801B63F0 *node;
    if (index < 0 || index > lbl_803EBB28->mUnknown18->mUnknown12)
        node = 0;
    else
        node = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    PathStreamRecord_t *record = (PathStreamRecord_t *)lbl_803EBB28->mUnknown3C + node->mUnknown0;
    float length = (float)record[-1].mDuration;
    unsigned int free = node->mUnknownC >> 31;
    if (node->mUnknown4 & 0xF00)
        length /= (float)(((node->mUnknown4 >> 8) & 15) * (unsigned char)node->mUnknown4);
    if (free)
        length = (float)info.mUnknown4;
    unsigned int start = info.mUnknown18;
    int range = info.mUnknownC - start;
    int beat = (int)((float)start / length);
    int beats = (int)((float)range / length);
    int result = -1;
    switch (find.mBits8.mSync) {
    case 1:
        ++beats;
        time = (int)((float)beats * length) % range;
        result = beats % ((node->mUnknown4 >> 8) & 15) + 1;
        break;
    case 2:
        time = start % (int)((float)beat * length);
        result = ((node->mUnknown4 >> 8) & 15) - beat % ((node->mUnknown4 >> 8) & 15) + 1;
        break;
    case 3:
        time = range % (int)length;
        result = 1;
        break;
    }
    if (time)
        time += lbl_803EBB3C;
    return result;
}

extern "C" int fn_801B6CB4(PathTrack_t *p)
{
    int sum = 0;
    for (int i = 0; ; ++i) {
        int value = p->mUnknown100->vfn_09(i);
        if (value < 0)
            break;
        sum += value;
    }
    return sum;
}

extern "C" int fn_801B6D20(int count, int value, Record_801B6D20 *entries)
{
    if (count <= 0)
        return -1;
    int best = 127;
    Record_801B6D20 *found = entries;
    for (int i = 0; i < count; ++i) {
        int a = entries[i].mUnknown0 - value;
        int b = entries[i].mUnknown1 - value;
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (b > a) b = a;
        if (best > b) {
            best = b;
            found = &entries[i];
        }
    }
    return found->mUnknown2;
}

extern "C" int PATHI_nextnode(int index, int value, int advance)
{
    int result = -1;
    Entry_801B63F0 *node;
    if (index < 0 || !(node = PATHI_getnode(index)))
        return -1;
    Record_801B6D20 *branches = (Record_801B6D20 *)((unsigned char *)node + 16);
    PathTrack_t *track = lbl_803EBB28->mUnknown40[node->mBits0.mTrack];
    if (track->mUnknown6 == index) {
        int loop = track->mUnknown8.bits.mLoop;
        if (node->mBits0.mLoop > 0 && advance) {
            value = loop & 127;
            if ((track->mUnknown8.bits.mLoop = loop - 1) == -1)
                track->mUnknown6 = -1;
        }
    }
    for (unsigned int i = 0; i < node->mBits4.mBranches; ++i) {
        if (value >= branches[i].mUnknown0 && value <= branches[i].mUnknown1) {
            result = (short)branches[i].mUnknown2;
            break;
        }
    }
    if (result < 0)
        result = fn_801B6D20(node->mBits4.mBranches, value, branches);
    return result;
}

extern "C" int PATHI_enternode(int track, int index, int value, int advance)
{
    int first = value;
    if (index < 0)
        return -1;
    index = (short)fn_801B7178(track, index);
    if (index < 0)
        return -1;
    Entry_801B63F0 *node = PATHI_getnode(index);
    if (!node)
        return -1;
    PathTrack_t *p = lbl_803EBB28->mUnknown40[node->mBits0.mTrack];
    while (node->mUnknown0 <= 0) {
        if (advance) {
            if (node->mUnknown0 == 0) {
                p->mUnknown34 = (unsigned int *)node;
                if (node->mBits4.mKind == 1)
                    value = PATHI_random() & 127;
                if (lbl_803EBB34)
                    lbl_803EBB34(lbl_803EBB28->mUnknown14, index);
            } else if (node->mUnknown0 == -1) {
                if (node->mBits0.mLoop && p->mUnknown6 != index) {
                    p->mUnknown6 = index;
                    p->mUnknown8.bits.mLoop = node->mBits0.mLoop;
                }
            } else if (node->mUnknown0 == -2)
                value = PATHI_random() & 127;
            else if (node->mUnknown0 == -3) {
                Entry_801B63F0 *event = PATHI_findevent(node->mUnknownC >> 8);
                if (event)
                    PATHI_addevent(lbl_803EBB28->mUnknown14 | 0xF0000000, PATHI_copyevent((Sequence_801B84E4 *)event));
            }
        }
        index = PATHI_nextnode(index, value, advance);
        if (index < 0 || (index = (short)fn_801B7178(track, index)) < 0) {
            if (lbl_803EBB34 && advance && track >= 0)
                lbl_803EBB34(lbl_803EBB28->mUnknown14, index);
            return -1;
        }
        node = PATHI_getnode(index);
        if (!node)
            return -1;
        value = first;
    }
    return (short)fn_801B7178(track, index);
}

extern "C" int fn_801B7178(int index, int value)
{
    if (index < 0)
        return value;
    Entry_801B63F0 *p = 0;
    if (index <= lbl_803EBB28->mUnknown18->mUnknown12)
        p = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    int key = (p->mUnknown4 >> 20) & 255;
    if (key) {
        unsigned int end = lbl_803EBB28->mUnknown30[key];
        unsigned int start = lbl_803EBB28->mUnknown30[key - 1];
        int count = end - start;
        int *words = (int *)lbl_803EBB28->mUnknown18 + start;
        for (int i = 0; i < count; ++i) {
            int word = words[i];
            if (value == word >> 16)
                value = word & 0xFFFF;
        }
    }
    return value;
}

extern "C" void PATHI_seeknextnode(int index)
{
    int queued = lbl_803EBB28->mUnknown1100;
    PathTrack_t *p = lbl_803EBB28->mUnknown40[index];
    int next = -1;
    if (p->mUnknown4 < 0)
        return;
    PathTrack_t saved = *p;
    Entry_801B63F0 *node = PATHI_getnode(p->mUnknown4);
    signed char beat = -1;
    if (p->mUnknown8.bits.flag10)
        beat = 1;
    int loop = p->mUnknown8.bits.mUnknown7;
    if (loop > 0 && (node->mUnknownC & 0x40000000) && loop <= (int)(node->mBits4.mBeats * (unsigned char)node->mUnknown4)) {
        beat = loop;
        next = p->mUnknown4;
    } else if (p->mUnknown4 >= 0) {
        next = PATHI_nextnode(p->mUnknown4, p->mUnknown1, 1);
        if (lbl_803EBB34 && next < 0)
            lbl_803EBB34(lbl_803EBB28->mUnknown14, next);
    }
    if (next >= 0)
        next = PATHI_enternode(p->mUnknown4, next, p->mUnknown1, 1);
    p->mUnknown4 = next;
    p->mUnknown8.bits.mUnknown7 = next >= 0 ? beat : -1;
    int result = PATHI_queuenode(p);
    if (result < 0 && result != -9999) {
        lbl_803EBB28->mUnknown1100 = queued;
        *p = saved;
    }
}

extern "C" int PATHI_queuenode(PathTrack_t *p)
{
    PathTrack_t *master = 0;
    int beats = 0;
    unsigned int length = 0;
    if (lbl_803EBB28->mUnknown0 >= 0)
        master = lbl_803EBB28->mUnknown40[lbl_803EBB28->mUnknown0];
    if (p->mUnknown4 < 0) {
        p->mUnknown34 = 0;
        p->mUnknown8.bits.mUnknown7 = -1;
        p->mUnknown4C = -1;
        p->mUnknown4 = -1;
        return 0;
    }
    Entry_801B63F0 *node = PATHI_getnode(p->mUnknown4);
    p->mUnknown34 = (unsigned int *)PATHI_getnode((unsigned short)node->mUnknown8);
    length = ((PathStreamRecord_t *)lbl_803EBB28->mUnknown3C)[node->mUnknown0 - 1].mDuration;
    p->mUnknown3C = length;
    p->mUnknown38 = length;
    if ((unsigned char)node->mUnknown4)
        p->mUnknown3C = length / (unsigned char)node->mUnknown4;
    if (node->mUnknown4 & 0xF00)
        p->mUnknown38 /= node->mBits4.mBeats * (unsigned char)node->mUnknown4;
    if (!p->mUnknown8.bits.flag10)
        p->mUnknown8.bits.mUnknown7 = -1;
    else {
        int slave = master && master != p;
        Entry_801B63F0 *next = (Entry_801B63F0 *)p->mUnknown34;
        int sync = 0;
        if ((int)next->mUnknownC < 0 && slave)
            sync = 1;
        int bar = (next->mUnknownC >> 29) & 1;
        BeatInfo_801B67F8 info;
        info.mUnknown10 = 0;
        if (slave)
            PATHI_beatinfo(master, &info);
        if (p->mUnknown8.bits.mUnknown7 < 0 && (((Entry_801B63F0 *)p->mUnknown34)->mUnknown8 & 12) && slave) {
            p->mUnknown8.bits.mUnknown7 = PATHI_choosesynchtime(p->mUnknown4, *(FindNode_801B6A18 *)p->mUnknown34, info, p->mUnknown40);
            if (lbl_803EBB40 & 1)
                PATHI_printf("JUST SET nextbeattime %d nodebeat %d\n", p->mUnknown40, p->mUnknown8.bits.mUnknown7);
            return 0;
        }
        if (p->mUnknown8.bits.mUnknown7 <= 0)
            p->mUnknown8.bits.mUnknown7 = 1;
        p->mUnknown40 = 0;
        beats = p->mUnknown8.bits.mUnknown7;
        if (sync && info.mUnknown10)
            p->mUnknown40 = info.mUnknown10 + lbl_803EBB3C;
        if (!bar || p->mUnknown8.bits.mUnknown7++ >= (int)(node->mBits4.mBeats * (unsigned char)node->mUnknown4))
            p->mUnknown8.bits.mUnknown7 = 0;
        if (bar)
            length /= node->mBits4.mBeats * (unsigned char)node->mUnknown4;
    }
    return p->mUnknown4C = p->mUnknown100->vfn_11(p->mUnknown4, fn_801B6780(p->mUnknown4), beats, 0, length);
}
