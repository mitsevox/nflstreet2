/* PATH music nodes (pathnode.c): beat timing, choosing the synchronization point for a branch and
   moving a track from node to node. */

#include "engine/pathlib.h"

extern "C" int fn_801B6780(int index)
{
    if (index < 0 || index >= lbl_803EBB28->mUnknown18->mUnknown12)
        return 0;
    Record_801B6780 *p = (Record_801B6780 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown1C[index] * 4);
    int result = 0;
    int value = p->mUnknown0;
    if (value > 0)
        result = lbl_803EBB28->mUnknown3C[(value - 1) * 2];
    return result;
}

extern "C" int fn_801B6CB4(Node_801B3FE0 *p)
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
