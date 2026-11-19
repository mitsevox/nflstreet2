/* Speech sentence rules: offsets into the event and sentence records, which parameters a
   sentence uses, its rule settings and the per-sample parameter data. */

#include "engine/spchlib.h"

extern "C" {


Entry_801AF84C *fn_801B1CFC(Record_801AF75C *p, int i)
{
    // FAKEMATCH: the base-pointer local keeps the target's add order (base + 8 first)
    Entry_801AF84C *entries = p->mEntries;
    return entries + i;
}

int fn_801B1D0C(unsigned char *p)
{
    return p[2] >> 2;
}

int fn_801B1D18(VoxEvent_t *p)
{
    return p->mUnknown7;
}

char *fn_801B1D20(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801B1D30(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801B1D44(VoxEvent_t *p)
{
    // FAKEMATCH: size computed then rounded up in place (reused local); the one-expression form ties the count load and the final sum into r9, the target keeps both in r0
    int size = p->mUnknown6 * 2;
    size = (size + 3) & ~3;
    return (char *)p + (size + 12);
}

char *fn_801B1D60(VoxEvent_t *p)
{
    char *result = fn_801B1D44(p);
    return result + ((fn_801B1D18(p) * 3 + 3) & ~3);
}

int fn_801B1DAC(unsigned char *p, int value)
{
    int result = 0;
    int count = fn_801B1D0C(p);
    for (int i = 0; i < count; i++) {
        Record_801AF75C *record = (Record_801AF75C *)fn_801B1D20((char *)p, p + 8, i);
        if (record->mUnknown2 == value) {
            result = 1;
            break;
        }
        int n = record->mUnknown4;
        for (int j = 0; j < n; j++) {
            if (fn_801B1CFC(record, j)->mUnknown4 == value) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

struct SpchRule_t {
    int mId;
    int mParm;
    int mType;
};

#define GET_RULE(rule, data, i)           (rule).mId = (data)[(i) * 3];         (rule).mParm = (data)[(i) * 3 + 1];     (rule).mType = (data)[(i) * 3 + 2]

int fn_801B1E58(VoxEvent_t *event, unsigned int index)
{
    SpchRule_t rule;
    int id = -1;
    fn_801B1D18(event);
    unsigned char *data = (unsigned char *)fn_801B1D44(event);
    if (index < 8) {
        GET_RULE(rule, data, index);
        id = rule.mId;
    }
    return id;
}

void fn_801B1EC8(SpchEventKey_t *key, VoxEvent_t *event, int sentence, int *values)
{
    int game;
    SpchRule_t rule;
    if (gCallbacks.mUnknown8) {
        iSPCH_GetDatID(key, &game);
        int count = fn_801B1D18(event);
        unsigned char *data = (unsigned char *)fn_801B1D44(event);
        unsigned char *p = (unsigned char *)fn_801B1D30((char *)event, (unsigned short *)((char *)event + 12), sentence);
        for (int i = 0; i < count; i++) {
            GET_RULE(rule, data, i);
            int id = rule.mId;
            int parm = rule.mParm;
            switch (rule.mType) {
            case 0:
            case 3:
                if (fn_801B1DAC(p, parm)) {
                    gCallbacks.mUnknown8(key, id, values[parm], game);
                }
                break;
            case 1:
            case 2:
                break;
            }
        }
    }
}

unsigned int fn_801B1FD8(SpchEventKey_t *key, VoxEvent_t *event, int *values, unsigned int *ignored)
{
    int game;
    SpchRule_t rule;
    iSPCH_GetDatID(key, &game);
    unsigned int set = 0;
    unsigned int skip = 0;
    // FAKEMATCH: one parm local assigned in both loops (reused local); reading rule.mParm directly keeps the load register for the index, the target copies it (mr. r10,r0)
    int parm;
    int count = fn_801B1D18(event);
    unsigned char *data = (unsigned char *)fn_801B1D44(event);
    int i;
    for (i = 0; i < count; i++) {
        unsigned int mask = 0;
        GET_RULE(rule, data, i);
        parm = rule.mParm;
        if (parm) {
            unsigned int bit = 1 << (31 - i);
            int value = values[parm];
            int result;
            if (gCallbacks.mUnknown4) result = gCallbacks.mUnknown4(key, rule.mId, value, game);
            else result = -1;
            if (result == 0) mask = 0;
            else if (result > 0) mask = bit;
            else skip |= bit;
            set |= mask;
        }
    }
    for (i = 0; i < count; i++) {
        unsigned int mask = 0;
        GET_RULE(rule, data, i);
        parm = rule.mParm;
        if (parm == 0) {
            unsigned int bit = 1 << (31 - i);
            int result;
            if (gCallbacks.mUnknown4) result = gCallbacks.mUnknown4(key, rule.mId, 0, game);
            else result = -1;
            if (result == 0) mask = 0;
            else if (result > 0) mask = bit;
            else skip |= bit;
            set |= mask;
        }
    }
    *ignored = skip;
    return set;
}

unsigned char *fn_801B2190(VoxEvent_t *item, int index, unsigned int *a, unsigned int *b)
{
    *a = 0;
    *b = 0;
    int size = (fn_801B1D18(item) + 7) / 8;
    int offset = size * item->mUnknown6;
    unsigned char *p = (unsigned char *)fn_801B1D60(item) + index * size;
    unsigned char *q = p + offset;
    if (size <= 4) {
        for (int i = 0; i < size; i++) {
            *a += p[i] << ((3 - i) * 8);
            *b += q[i] << ((3 - i) * 8);
        }
    }
    return p;
}

int fn_801B2250(VoxEvent_t *item, int index, unsigned int value, unsigned int excluded)
{
    unsigned int a, b;
    fn_801B2190(item, index, &a, &b);
    b &= ~excluded;
    a &= b;
    return (b & value) == a;
}

char *iSPCH_GetSampleParmAddr(VoxBankHdr_t *p, int i)
{
    char *result = 0;
    if (i < p->mUnknown5) {
        // FAKEMATCH: result stepped in three statements; one expression keeps the result out of r3
        result = (char *)p->mRows;
        result += i * ((p->mUnknown4 & 127) + 2);
        result += 2;
    }
    return result;
}

int fn_801B22E0(VoxBankHdr_t *p, int i, int *a, int *b)
{
    int result = 0;
    int count = p->mUnknown5;
    if (i < count) {
        int stride = (p->mUnknown4 & 127) + 2;
        unsigned char *record = p->mRows;
        record += i * stride;
        int scale = (p->mUnknown7 + 1) << 8;
        int start = ((record[0] << 8) + record[1]) * scale;
        unsigned char *next = record + stride;
        int end;
        if (i + 1 >= count) end = p->mUnknown8;
        else end = (next[0] << 8) + next[1];
        end = end * scale - start;
        *a = start;
        *b = end;
        result = 1;
    }
    return result;
}

unsigned int fn_801B2368(void)
{
    unsigned int tick = 0;
    if (gExtVecs.mVecs[2]) {
        tick = ((unsigned int (*)(int))gExtVecs.mVecs[2])(0);
    }
    return tick;
}

}
