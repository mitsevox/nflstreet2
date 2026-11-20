/* Sound voice allocator (salloc.c): picks the hardware voices a sound plays on (free voices
   first, then the lowest-priority ones it may steal), hands out voice handles, groups the voices
   of one sound and releases them again. */

#include "engine/sndaems.h"

extern "C" {

extern short lbl_803A6C04[];

void SNDstop(int handle);

int SNDVOICEI_isreserved(int value, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (lbl_803A6C04[i] == value)
            return 1;
    }
    return 0;
}

int SNDVOICEI_alloc(int count, int priority, int *handle, int first, int last)
{
    static int lasthandle = 0;
    int result = -9;
    int found = 0;
    int i;
    int v;
    int best;
    unsigned int besttime;
    int bestpri;
    int sorted;
    Voice_803A6C24 *p;

    for (i = 0; i < count; i++) {
        lbl_803A6C04[i] = -1;
    }
    lasthandle += 256;
    if (lasthandle < 0) {
        lasthandle = 0;
    }
    for (i = found; i < count; i++) {
        best = -1;
        besttime = 0xFFFFFFFF;
        for (v = first; v < last; v++) {
            p = &lbl_803A6C24.mUnknown1CC[v];
            if (p->mUnknown6D == 0 && SNDVOICEI_isreserved(v, found) == 0 && p->m2C < besttime) {
                besttime = p->m2C;
                best = v;
            }
        }
        if (best >= 0) {
            lbl_803A6C04[found++] = best;
        }
    }
    for (i = found; i < count; i++) {
        bestpri = priority;
        if (lbl_803A6C24.m34 == 0) {
            bestpri = priority - 1;
        }
        best = -1;
        besttime = 0xFFFFFFFF;
        for (v = first; v < last; v++) {
            if (SNDVOICEI_isreserved(v, found) == 0) {
                p = &lbl_803A6C24.mUnknown1CC[v];
                if (p->m2A <= 100) {
                    if (p->m2A < bestpri) {
                        bestpri = p->m2A;
                        besttime = p->m2C;
                        best = v;
                    } else if (p->m2A == bestpri && p->m2C < besttime) {
                        besttime = p->m2C;
                        best = v;
                    }
                }
            }
        }
        if (best >= 0) {
            lbl_803A6C04[found++] = best;
            if (found >= count) {
                break;
            }
        }
    }
    if (found == count) {
        do {
            sorted = 1;
            for (i = 0; i < found - 1; i++) {
                if (lbl_803A6C04[i] > lbl_803A6C04[i + 1]) {
                    short t = lbl_803A6C04[i];
                    lbl_803A6C04[i] = lbl_803A6C04[i + 1];
                    lbl_803A6C04[i + 1] = t;
                    sorted = 0;
                }
            }
        } while (sorted == 0);
        *handle = lasthandle | lbl_803A6C04[0];
        result = lbl_803A6C04[0];
        for (i = 0; i < found; i++) {
            int h;

            p = &lbl_803A6C24.mUnknown1CC[lbl_803A6C04[i]];
            h = lbl_803A6C24.mUnknown1CC[lbl_803A6C04[i]].mUnknown0;
            if (p->mUnknown6D != 0) {
                if (h < 0) {
                    h = lbl_803A6C24.mUnknown1CC[p->m28].mUnknown0;
                }
                SNDstop(h);
            }
            p->mUnknown6D = 1;
            p->m2C = lbl_803A6C24.m170;
            p->m2A = priority;
        }
        lbl_803A6C24.mUnknown1CC[lbl_803A6C04[0]].mUnknown0 = *handle;
        lbl_803A6C24.mUnknown1CC[lbl_803A6C04[0]].mUnknown4[0] = lbl_803A6C04[0];
        lbl_803A6C24.mUnknown1CC[lbl_803A6C04[0]].m28 = -1;
        for (i = 1; i < found; i++) {
            lbl_803A6C24.mUnknown1CC[lbl_803A6C04[0]].mUnknown4[i] = lbl_803A6C04[i];
            lbl_803A6C24.mUnknown1CC[lbl_803A6C04[i]].mUnknown0 = -1;
            lbl_803A6C24.mUnknown1CC[lbl_803A6C04[i]].m28 = lbl_803A6C04[0];
        }
    }
    return result;
}

#if defined(DECOMP_COMPARE)
static inline void _SndVoiceClear(Voice_803A6C24 *v)
{
    v->mUnknown6D = 0;
    v->m26 = 0;
    v->m27 = 0;
    v->m2C = lbl_803A6C24.m170;
}

void SNDVOICEI_free(int voice)
{
    int count = 0;
    int other = -1;
    int group;
    int i;
    Voice_803A6C24 *v;

    v = &lbl_803A6C24.mUnknown1CC[voice];
    group = v->m26;
    if (group != 0) {
        for (i = 0; i < lbl_803A6C24.mUnknown16C; i++) {
            v = &lbl_803A6C24.mUnknown1CC[i];
            if (v->m26 == group && v->mUnknown0 >= 0 && v->mUnknown6D != 0) {
                count++;
                if (v->m27 != 0) {
                    other = i;
                }
            }
        }
        v = &lbl_803A6C24.mUnknown1CC[voice];
        if (count == 1) {
            _SndVoiceClear(v);
        } else if (lbl_803A6C24.mUnknown1CC[other].mUnknown6D == 2 && voice != other && count == 2) {
            _SndVoiceClear(v);
            lbl_803A6C24.mUnknown1CC[other].mUnknown6D = 0;
            lbl_803A6C24.mUnknown1CC[other].m26 = 0;
            lbl_803A6C24.mUnknown1CC[other].m27 = 0;
            lbl_803A6C24.mUnknown1CC[other].m2C = lbl_803A6C24.m170;
        } else if (lbl_803A6C24.mUnknown1CC[other].mUnknown6D == 1 && voice == other) {
            lbl_803A6C24.mUnknown1CC[other].mUnknown6D = 2;
        } else {
            _SndVoiceClear(v);
        }
    } else {
        _SndVoiceClear(v);
    }
}

int SNDVOICEI_get(int handle)
{
    int index;
    Voice_803A6C24 *v;

    if (handle < 0)
        return -8;
    index = handle & 0xFF;
    if (index >= lbl_803A6C24.mUnknown16C)
        return -8;
    v = lbl_803A6C24.mUnknown1CC + index;
    if (v->mUnknown6D != 0 && v->mUnknown0 == handle)
        return index;
    return -8;
}
#endif
}
