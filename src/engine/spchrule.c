/* Speech sentence rules: offsets into the event and sentence records, which parameters a
   sentence uses, its rule settings and the per-sample parameter data. */

#include "engine/spchlib.h"

extern "C" {


SpchPhraseParm_t *iSPCH_GetPhraseParmInfo(SpchPhrase_t *p, int i)
{
    // FAKEMATCH: the base-pointer local keeps the target's add order (base + 8 first)
    SpchPhraseParm_t *entries = p->mEntries;
    return entries + i;
}

int VoxSentence_GetNumPhrases(unsigned char *p)
{
    return p[2] >> 2;
}

static int _VoxEvent_GetNumRules(VoxEvent_t *p)
{
    return p->mUnknown7;
}

char *iSPCH_GetOffset8(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

static char *_iSPCH_GetOffset16(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

static char *_iSPCH_GetRuleDataAddr(VoxEvent_t *p)
{
    // FAKEMATCH: size computed then rounded up in place (reused local); the one-expression form ties the count load and the final sum into r9, the target keeps both in r0
    int size = p->mUnknown6 * 2;
    size = (size + 3) & ~3;
    return (char *)p + (size + 12);
}

static char *_iSPCH_GetSentenceRulesAddr(VoxEvent_t *p)
{
    char *result = _iSPCH_GetRuleDataAddr(p);
    return result + ((_VoxEvent_GetNumRules(p) * 3 + 3) & ~3);
}

int iSPCH_SentenceUsesParm(unsigned char *p, int value)
{
    int result = 0;
    int count = VoxSentence_GetNumPhrases(p);
    for (int i = 0; i < count; i++) {
        SpchPhrase_t *record = (SpchPhrase_t *)iSPCH_GetOffset8((char *)p, p + 8, i);
        if (record->mEventParm == value) {
            result = 1;
            break;
        }
        int n = record->mParmCount;
        for (int j = 0; j < n; j++) {
            if (iSPCH_GetPhraseParmInfo(record, j)->mEventParm == value) {
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

int iSPCH_GetRuleID(VoxEvent_t *event, unsigned int index)
{
    SpchRule_t rule;
    int id = -1;
    _VoxEvent_GetNumRules(event);
    unsigned char *data = (unsigned char *)_iSPCH_GetRuleDataAddr(event);
    if (index < 8) {
        GET_RULE(rule, data, index);
        id = rule.mId;
    }
    return id;
}

void iSPCH_RuleSet(SpchEventKey_t *key, VoxEvent_t *event, int sentence, int *values)
{
    int game;
    SpchRule_t rule;
    if (gCallbacks.mUnknown8) {
        iSPCH_GetDatID(key, &game);
        int count = _VoxEvent_GetNumRules(event);
        unsigned char *data = (unsigned char *)_iSPCH_GetRuleDataAddr(event);
        unsigned char *p = (unsigned char *)_iSPCH_GetOffset16((char *)event, (unsigned short *)((char *)event + 12), sentence);
        for (int i = 0; i < count; i++) {
            GET_RULE(rule, data, i);
            int id = rule.mId;
            int parm = rule.mParm;
            switch (rule.mType) {
            case 0:
            case 3:
                if (iSPCH_SentenceUsesParm(p, parm)) {
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

unsigned int iSPCH_GetRuleSettings(SpchEventKey_t *key, VoxEvent_t *event, int *values, unsigned int *ignored)
{
    int game;
    SpchRule_t rule;
    iSPCH_GetDatID(key, &game);
    unsigned int set = 0;
    unsigned int skip = 0;
    // FAKEMATCH: one parm local assigned in both loops (reused local); reading rule.mParm directly keeps the load register for the index, the target copies it (mr. r10,r0)
    int parm;
    int count = _VoxEvent_GetNumRules(event);
    unsigned char *data = (unsigned char *)_iSPCH_GetRuleDataAddr(event);
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

unsigned char *iSPCH_GetSentenceRuleSettings(VoxEvent_t *item, int index, unsigned int *a, unsigned int *b)
{
    *a = 0;
    *b = 0;
    int size = (_VoxEvent_GetNumRules(item) + 7) / 8;
    int offset = size * item->mUnknown6;
    unsigned char *p = (unsigned char *)_iSPCH_GetSentenceRulesAddr(item) + index * size;
    unsigned char *q = p + offset;
    if (size <= 4) {
        for (int i = 0; i < size; i++) {
            *a += p[i] << ((3 - i) * 8);
            *b += q[i] << ((3 - i) * 8);
        }
    }
    return p;
}

int iSPCH_CheckSentenceRules(VoxEvent_t *item, int index, unsigned int value, unsigned int excluded)
{
    unsigned int a, b;
    iSPCH_GetSentenceRuleSettings(item, index, &a, &b);
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

int iSPCH_GetSampleSizeData(VoxBankHdr_t *bank, int sample, int *pStart, int *pSize)
{
    int result = 0;
    int count = bank->mUnknown5;
    if (sample < count) {
        int stride = (bank->mUnknown4 & 127) + 2;
        unsigned char *record = bank->mRows;
        record += sample * stride;
        int scale = (bank->mUnknown7 + 1) << 8;
        int start = (record[0] << 8) + record[1];
        start *= scale;
        unsigned char *next = record + stride;
        int end;
        if (sample + 1 >= count) end = bank->mUnknown8;
        else end = (next[0] << 8) + next[1];
        end *= scale;
        // FAKEMATCH: dead increment of scale (unused afterwards) leaves a block
        // boundary that keeps the result in r0 and the stores after the subtraction.
        if (scale != 0) scale++;
        end -= start;
        *pStart = start;
        *pSize = end;
        result = 1;
    }
    return result;
}

unsigned int SPCHEXT_gettick(void)
{
    unsigned int tick = 0;
    if (gExtVecs.mpGetTick) {
        tick = gExtVecs.mpGetTick(0);
    }
    return tick;
}

}
