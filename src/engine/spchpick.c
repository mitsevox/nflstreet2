/* Commentary selection: choose sentences and recorded samples for speech events
   using event parameters, selection weights and recent playback history. */

#include "engine/spchlib.h"

extern "C" {

int _SpchPick_iWeightMultipliers[8] = {1, 4, 16, 64, 256, 1024, 4096, 16384};
SpchEventChoice_t gEventChoice[8];

struct SpchSampleRequest_t {
    int mBank;
    int mStart;
    int mSize;
    SpchEventKey_t mKey;
    int mChannel;
    int mUnknown14;
    int mGame;
    int mInterrupt;
};

struct SpchContextRule_t {
    int mId;
    int mParm;
    int mType;
};

extern int gClearCycle;
int iSPCHBank_GetSampleTimeInQueue(VoxBankHdr_t *, int);
void iSPCHBank_AddToQueue(VoxBankHdr_t *, int);
int iSPCH_FindBankIndexFromHandle(int);
int iSPCH_FindEventDatInfo(SpchEventKey_t *, VoxDatSlot_t **);
int iSPCH_FindEventChannel(SpchEventKey_t *, int *);
int iSPCH_GetFilterLength(SpchEventKey_t *);
int iSPCH_GetRuleID(VoxEvent_t *, unsigned int);
void iSPCH_RuleSet(SpchEventKey_t *, VoxEvent_t *, int, int *);
unsigned int iSPCH_GetRuleSettings(SpchEventKey_t *, VoxEvent_t *, int *, unsigned int *);
int iSPCH_CheckSentenceRules(VoxEvent_t *, int, unsigned int, unsigned int);

// Locate the bank's parameter-validity masks after its sample rows.
char *iSPCHPick_BANKHDR_GetValidParmMask(VoxBankHdr_t *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

// Locate the bank's per-sample cycle bits.
char *iSPCHPick_BANKHDR_GetCycleBitsAddr(VoxBankHdr_t *p)
{
    char *result = iSPCHPick_BANKHDR_GetValidParmMask(p);
    return result + (p->mUnknown4 & 127) * 4;
}

// Locate the repeat history after any cycle-bit storage.
char *iSPCHPick_BANKHDR_GetSampleRepeatAddr(VoxBankHdr_t *p)
{
    int size = 0;
    char *result = iSPCHPick_BANKHDR_GetCycleBitsAddr(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

// Locate the sub-bank availability bits after the repeat history.
char *BANKHDR_GetArrayBankBitsAddr(VoxBankHdr_t *p)
{
    char *result = iSPCHPick_BANKHDR_GetSampleRepeatAddr(p);
    int size = p->mUnknown6;
    if (size) {
        result += size + 1;
    }
    return result;
}

// Access a phrase's parameter descriptor.
SpchPhraseParm_t *iSPCHPick_GetPhraseParmInfo(SpchPhrase_t *p, int i)
{
    // FAKEMATCH: the base-pointer local keeps the target's add order (base + 8 first)
    SpchPhraseParm_t *entries = p->mEntries;
    return entries + i;
}

// Read the sentence's packed phrase count.
int iSPCHPick_VoxSentence_GetNumPhrases(unsigned char *p)
{
    return p[2] >> 2;
}

// Read the sentence's short-selection rule.
int VoxSentence_GetShortRule(unsigned char *p)
{
    return p[2] & 3;
}

// Locate the sentence's context masks after its phrase offsets.
char *VoxSentence_GetContextFlagsAddr(unsigned char *p)
{
    return (char *)p + (((iSPCHPick_VoxSentence_GetNumPhrases(p) + 3) & ~3) + 8);
}

// Locate the sentence's shared parameter workspace.
char *VoxSentence_GetMatchParmIO(unsigned char *p)
{
    int size = p[4] * 4;
    return VoxSentence_GetContextFlagsAddr(p) + size;
}

// Read the number of event rules.
int iSPCHPick_VoxEvent_GetNumRules(VoxEvent_t *p)
{
    return p->mUnknown7;
}

// Read the allowed number of consecutive repetitions.
int VoxEvent_GetNumInARow(VoxEvent_t *p)
{
    return p->mUnknown8 & 15;
}

// Read the number of event contexts.
int iSPCHPick_VoxEvent_GetNumContexts(VoxEvent_t *p)
{
    return p->mUnknown8 >> 4;
}

// Test whether the event supplies a duration filter.
int VoxEvent_GetFilterLengthFlag(VoxEvent_t *p)
{
    return p->mUnknownA & 1;
}

// Test whether sentence parameters must match exactly.
int iSPCHPick_VoxEvent_GetExactParmMatchFlag(VoxEvent_t *p)
{
    return (p->mUnknownA >> 3) & 1;
}

// Read the event's interrupt flag.
int iSPCHPick_VoxEvent_GetInterruptFlag(VoxEvent_t *p)
{
    return (p->mUnknownA >> 5) & 1;
}

// Resolve a byte-sized, four-byte-unit offset.
char *iSPCHPick_GetOffset8(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

// Resolve a halfword-sized, four-byte-unit offset.
char *iSPCHPick_GetOffset16(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

// Locate event rule records after the sentence offsets.
char *iSPCHPick_GetRuleDataAddr(VoxEvent_t *p)
{
    // FAKEMATCH: size computed then rounded up in place (reused local); the one-expression form ties the count load and the final sum into r9, the target keeps both in r0
    int size = p->mUnknown6 * 2;
    size = (size + 3) & ~3;
    return (char *)p + (size + 12);
}

// Locate per-sentence rule masks after the rule records.
char *iSPCHPick_GetSentenceRulesAddr(VoxEvent_t *p)
{
    char *result = iSPCHPick_GetRuleDataAddr(p);
    return result + ((iSPCHPick_VoxEvent_GetNumRules(p) * 3 + 3) & ~3);
}

// Locate event context descriptors after the rule masks.
char *iSPCHPick_GetContextDataAddr(VoxEvent_t *p)
{
    char *result = iSPCHPick_GetSentenceRulesAddr(p);
    return result + ((((iSPCHPick_VoxEvent_GetNumRules(p) + 7) / 8) * p->mUnknown6 * 2 + 3) & ~3);
}

// Read one sentence's required parameter mask.
int VoxEvent_GetSentenceParmMask(VoxEvent_t *p, int i)
{
    char *result = iSPCHPick_GetContextDataAddr(p);
    result += (iSPCHPick_VoxEvent_GetNumContexts(p) * 3 + 3) & ~3;
    unsigned short *masks = (unsigned short *)(result + 4);
    return masks[i];
}

// Read the event's parameter-type mask.
int VoxEvent_GetParmTypesMask(VoxEvent_t *p)
{
    char *result = iSPCHPick_GetContextDataAddr(p);
    return *(int *)(result + ((iSPCHPick_VoxEvent_GetNumContexts(p) * 3 + 3) & ~3));
}

// Return the two database header identifiers.
void SPCH_GetEventDatInfo(VoxDatHeader_t *p, int *a, int *b)
{
    *a = p->mUnknown8;
    *b = p->mUnknown9;
}

// Publish a sample's output parameters for dependent phrases.
void iSPCH_PostMatchParmValue(unsigned char *p, SpchPhrase_t *record, unsigned char *values)
{
    int *words = (int *)VoxSentence_GetMatchParmIO(p);
    int count = record->mParmCount;
    for (int i = 0; i < count; i++) {
        if (iSPCHPick_GetPhraseParmInfo(record, i)->mEventParm == 254) {
            int flags = iSPCHPick_GetPhraseParmInfo(record, i)->mMatchParm;
            if (flags & 128) {
                words[flags & 127] |= 1 << values[i];
            }
        }
    }
}

// Test whether a phrase publishes any shared parameter values.
int iSPCH_HasMatchParmToPost(SpchPhrase_t *record)
{
    int found = 0;
    int count = record->mParmCount;
    for (int i = 0; i < count; i++) {
        if (iSPCHPick_GetPhraseParmInfo(record, i)->mEventParm == 254) {
            found = 1;
            break;
        }
    }
    return found;
}

// Check a sample against event, shared and fixed phrase parameters.
int iSPCH_MatchSample(unsigned char *p, SpchPhrase_t *record, SpchEventParm_t *event, unsigned char *values)
{
    int count = record->mParmCount;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int value = values[i];
        result = 0;
        // FAKEMATCH: goto past the loop; with break the loop keeps its jump-to-test form
        if ((unsigned int)value > 31) goto done;
        unsigned int mask = 1U << value;
        int id = iSPCHPick_GetPhraseParmInfo(record, i)->mEventParm;
        if (mask & iSPCHPick_GetPhraseParmInfo(record, i)->mMask) {
            if (id == 0 || id == 254) {
                result = 1;
            } else if (id == 255) {
                int flags = iSPCHPick_GetPhraseParmInfo(record, i)->mMatchParm;
                if (flags & 128) {
                    int *words = (int *)VoxSentence_GetMatchParmIO(p);
                    if (mask & words[flags & 127]) result = 1;
                } else {
                    SpchEventKey_t key = event[0].mKey;
                    char *text;
                    if (iSPCH_GetGlobalMatchParmsArray(&key, &text) && value == (unsigned char)text[flags]) result = 1;
                }
            } else {
                if (mask & event[id].mWord) result = 1;
            }
        }
        if (!result) goto done;
    }
done:
    return result;
}

// Resolve a phrase's bank handle, slot and optional sub-bank.
int iSPCH_GetPhraseBank(SpchEventKey_t *key, SpchEventParm_t *event, SpchPhraseBankView_t *out)
{
    int id = key->mId;
    int mode = key->mUnknown3;
    int index = key->mUnknown2;
    int value = -1;
    int slot = -1;
    out->mSubBank = slot;
    out->mHandle = slot;
    out->mBankIndex = slot;
    switch (mode) {
    case 0:
        out->mBankIndex = iSPCH_FindBank(id, &value);
        out->mHandle = (short)value;
        break;
    case 1:
        out->mBankIndex = iSPCH_FindSubBank(id, event[index].mHalfwords[1], &value);
        out->mHandle = value;
        break;
    case 2:
        slot = iSPCH_FindBank(id, &value);
        if (iSPCH_TestSubBankBounds(slot, event[index].mWord)) out->mSubBank = event[index].mHalfwords[1];
        else value = -1;
        out->mBankIndex = slot;
        out->mHandle = value;
        break;
    }
    return out->mHandle >= 0;
}

// Clear a sample's cycle bit after selecting it for playback.
void iSPCH_ClearCycleBit(VoxBankHdr_t *p, int i)
{
    int index = i / 8 + 1;
    unsigned char mask = ~(1 << (i % 8));
    unsigned char *bits = (unsigned char *)iSPCHPick_BANKHDR_GetCycleBitsAddr(p);
    bits[index] &= mask;
}

// Test a packed sample bit.
int iSPCH_TestBit(unsigned char *bits, int i)
{
    unsigned char mask = 1 << (i % 8);
    return bits[i / 8] & mask;
}

// Check whether a sample exists in the selected sub-bank.
int iSPCH_CheckTemplateSample(SpchPhraseBankView_t *result, VoxBankHdr_t *p, int i)
{
    int index = result->mSubBank;
    int found = 0;
    if (p->mUnknownA > index) {
        i += p->mUnknown5 * index;
        found = iSPCH_TestBit((unsigned char *)BANKHDR_GetArrayBankBitsAddr(p), i);
    }
    return found;
}

// Check sample bounds, sub-bank membership and cycle eligibility.
int iSPCH_SampleExists(SpchPhraseBankView_t *result, VoxBankHdr_t *p, int i)
{
    int found = 1;
    if (i > p->mUnknown5) {
        found = 0;
    } else if (result->mSubBank == -1 || (found = iSPCH_CheckTemplateSample(result, p, i)) != 0) {
        if (p->mUnknown4 & 128) {
            found = iSPCH_TestBit((unsigned char *)iSPCHPick_BANKHDR_GetCycleBitsAddr(p) + 1, i);
        }
    }
    return found;
}

// Append a valid sample to the bounded sentence-choice list.
int iSPCH_AddSampleToValidPicks(SpchValidPicksView_t *p, int value)
{
    int result = 0;
    if (p->mCount < 200) {
        result = 1;
        p->mValues[p->mCount] = value;
        p->mCount++;
    }
    return result;
}

// Reject a bank whose parameter masks cannot satisfy the phrase.
int iSPCH_BankHasValidSamples(SpchPhrase_t *a, VoxBankHdr_t *b, int *values)
{
    int *words = (int *)iSPCHPick_BANKHDR_GetValidParmMask(b);
    int count = b->mUnknown4 & 127;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int id = iSPCHPick_GetPhraseParmInfo(a, i)->mEventParm;
        if (id != 0 && id != 255 && id != 254) {
            if (!(words[i] & values[id])) {
                result = 0;
                // FAKEMATCH: goto past the loop; with break the loop keeps its jump-to-test form
                goto done;
            }
        }
    }
done:
    return result;
}

// Collect eligible samples, falling back to the oldest queued sample.
int iSPCH_ChooseSamples(SpchSentencePick_t *work, unsigned char *sentence,
    SpchPhrasePick_t *pick, SpchPhrase_t *phrase, SpchEventParm_t *event)
{
    int post = iSPCH_HasMatchParmToPost(phrase);
    int chosen = 0;
    VoxBankHdr_t *bank = gVoxBanks[pick->mBankIndex].mUnknown4;
    int count = bank->mUnknown5;
    int oldest = 0;
    int fallback = -1;
    if (iSPCH_BankHasValidSamples(phrase, bank, (int *)event)) {
        unsigned char *parameters = (unsigned char *)bank + 14;
        int stride = (bank->mUnknown4 & 127) + 2;
        for (int i = 0; i < count; i++, parameters += stride) {
            if (iSPCH_MatchSample(sentence, phrase, event, parameters) &&
                iSPCH_SampleExists((SpchPhraseBankView_t *)pick, bank, i)) {
                int age = iSPCHBank_GetSampleTimeInQueue(bank, i);
                if (age > 0) {
                    if (age > oldest) {
                        oldest = age;
                        fallback = i;
                    }
                } else {
                    if (iSPCH_AddSampleToValidPicks((SpchValidPicksView_t *)work, i)) chosen++;
                    if (post) iSPCH_PostMatchParmValue(sentence, phrase, parameters);
                }
            }
        }
        if (!chosen && fallback != -1) {
            if (iSPCH_AddSampleToValidPicks((SpchValidPicksView_t *)work, fallback)) chosen++;
            if (post) {
                parameters = (unsigned char *)bank + 12 + fallback * stride;
                iSPCH_PostMatchParmValue(sentence, phrase, parameters + 2);
            }
        }
    }
    return chosen;
}

// Convert accumulated sample units to speech duration.
int iSPCH_ConvertTime(int value)
{
    int result = 0;
    if (gDataRate) {
        result = value * 100 / gDataRate;
    }
    return result;
}

// Measure the total duration of the current phrase choices.
int iSPCH_SentenceLength(unsigned char *p, SpchSentencePick_t *work)
{
    int total = 0;
    int i = 0;
    int count = iSPCHPick_VoxSentence_GetNumPhrases(p);
    if (count > 0) do {
        int index = work->mEntries[i].mBankIndex;
        VoxBankHdr_t *record = gVoxBanks[index].mUnknown4;
        int a, b;
        if (iSPCH_GetSampleSizeData(record, work->mValues[work->mEntries[i].mCurrent], &a, &b)) {
            total += b;
        }
    } while (++i < count);
    return iSPCH_ConvertTime(total);
}

// Expand a packed sentence weight.
int iSPCH_DecodeWeight(unsigned int value)
{
    return (value & 31) * _SpchPick_iWeightMultipliers[(value >> 5) & 7];
}

// Read and decode the sentence's weight.
int VOXSENTENCE_GetWeight(unsigned char *p)
{
    return iSPCH_DecodeWeight(*p);
}

// Order weighted sentences without replacement, then append zero-weight entries.
void iSPCH_OrderSentences(VoxEvent_t *event, signed char *order)
{
    int weights[100];
    int count = event->mUnknown6;
    int total = 0;
    int i;
    for (i = 0; i < count; i++) {
        unsigned char *sentence = (unsigned char *)iSPCHPick_GetOffset16((char *)event,
            (unsigned short *)((char *)event + 12), i);
        weights[i] = VOXSENTENCE_GetWeight(sentence);
        total += VOXSENTENCE_GetWeight(sentence);
    }
    int out = 0;
    while (total > 0) {
        int roll = iSPCH_Rand(total, -1);
        for (i = 0; i < count; i++) {
            roll -= weights[i];
            if (roll < 0) break;
        }
        order[out++] = i;
        total -= weights[i];
        weights[i] = 0;
    }
    for (i = 0; i < count; i++) {
        unsigned char *sentence = (unsigned char *)iSPCHPick_GetOffset16((char *)event,
            (unsigned short *)((char *)event + 12), i);
        if (!VOXSENTENCE_GetWeight(sentence)) order[out++] = i;
    }
}

// Enforce the event's consecutive-repeat limit on a channel.
int iSPCH_RepeatEvent(VoxEvent_t *p, int channel)
{
    int result = 1;
    if (p->mId == gVoxInGame[channel].mKey.mId) {
        int limit = VoxEvent_GetNumInARow(p);
        if (limit > 0) result = gVoxInGame[channel].mUnknown4 < limit;
    }
    return result;
}

// Check whether the sentence's short rule permits this selection mode.
int iSPCH_ShortRuleStatus(unsigned char *p, int mode)
{
    int result = 0;
    int value = VoxSentence_GetShortRule(p);
    if (value == 1 && mode == 2) {
        result = 1;
    } else if (value == 2 && mode != 2) {
        result = 1;
    } else if (value == 0) {
        result = 1;
    }
    return result;
}

// Clear the sentence's shared parameter masks.
void iSPCH_InitMatchParmIO(unsigned char *p)
{
    int *words = (int *)VoxSentence_GetMatchParmIO(p);
    for (int i = 0; i < p[3]; i++) {
        words[i] = 0;
    }
}

// Check that a phrase's shared input parameters have been supplied.
int iSPCH_MatchParmInputsSet(unsigned char *p, SpchPhrase_t *record)
{
    int count = record->mParmCount;
    int result = 1;
    for (int i = 0; i < count; i++) {
        if (iSPCHPick_GetPhraseParmInfo(record, i)->mEventParm == 255) {
            int flags = iSPCHPick_GetPhraseParmInfo(record, i)->mMatchParm;
            if (flags != 255 && (flags & 128)) {
                flags &= 127;
                int *words = (int *)VoxSentence_GetMatchParmIO(p);
                if (words && !words[flags]) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}

// Propagate and validate shared parameters across the chosen samples.
int iSPCH_TestMatchParms(SpchSentencePick_t *work, unsigned char *sentence)
{
    int i;
    int result = 1;
    int *parameters = (int *)VoxSentence_GetMatchParmIO(sentence);
    int done = 0;
    iSPCH_InitMatchParmIO(sentence);
    for (i = 0; i <= 11; i++) work->mEntries[i].mReady = 0;
    int count = iSPCHPick_VoxSentence_GetNumPhrases(sentence);
    while (!done) {
        done = 1;
        for (i = 0; i < count; i++) {
            SpchPhrasePick_t *pick = &work->mEntries[i];
            if (!pick->mReady) {
                pick->mReady = 1;
                SpchPhrase_t *phrase = (SpchPhrase_t *)iSPCHPick_GetOffset8(
                    (char *)sentence, sentence + 8, i);
                VoxBankHdr_t *bank = gVoxBanks[pick->mBankIndex].mUnknown4;
                int n = phrase->mParmCount;
                unsigned char *values = (unsigned char *)iSPCH_GetSampleParmAddr(
                    bank, work->mValues[pick->mCurrent]);
                if (!values) { result = 0; goto done; }
                for (int j = 0; j < n; j++) {
                    int flags = iSPCHPick_GetPhraseParmInfo(phrase, j)->mMatchParm;
                    if (flags != 255 && (flags & 128)) {
                        flags &= 127;
                        if (iSPCHPick_GetPhraseParmInfo(phrase, j)->mEventParm == 255) {
                            int mask = parameters[flags];
                            if (!mask) {
                                work->mEntries[i].mReady = 0;
                                done = 0;
                            } else if (((mask >> values[j]) & 1) == 0) {
                                result = 0;
                                goto done;
                            }
                        } else if (iSPCHPick_GetPhraseParmInfo(phrase, j)->mEventParm == 254) {
                            parameters[flags] = 1 << values[j];
                        }
                    }
                }
            }
        }
    }
done:
    return result;
}

// Resolve phrase banks and collect choices in dependency order.
int iSPCH_SentenceGetChoices(SpchSentencePick_t *work, unsigned char *sentence,
    SpchEventParm_t *event, int mode)
{
    int result = 1;
    int count = iSPCHPick_VoxSentence_GetNumPhrases(sentence);
    int tries = 200;
    if (count > 12 || !iSPCH_ShortRuleStatus(sentence, mode)) { result = 0; goto done; }
    iSPCH_InitMatchParmIO(sentence);
    work->mPhraseCount = count;
    int done;
    do {
        done = 1;
        tries--;
        for (int i = 0; i < count; i++) {
            SpchPhrasePick_t *pick = &work->mEntries[i];
            SpchPhrase_t *phrase = (SpchPhrase_t *)iSPCHPick_GetOffset8(
                (char *)sentence, sentence + 8, i);
            if (!iSPCH_MatchParmInputsSet(sentence, phrase)) {
                done = 0;
            } else if (!pick->mReady) {
                pick->mFirst = work->mCount;
                if (!iSPCH_GetPhraseBank((SpchEventKey_t *)phrase, event, (SpchPhraseBankView_t *)pick)) { result = 0; goto done; }
                int n = iSPCH_ChooseSamples(work, sentence, pick, phrase, event);
                if (!n) { result = 0; goto done; }
                pick->mCount = n;
                pick->mReady = 1;
            }
        }
    } while (!done && tries > 0);
    if (!tries) result = 0;
done:
    return result;
}

// Shuffle each phrase's candidate samples.
void iSPCH_RandomizeSentencePicks(unsigned char *p, SpchSentencePick_t *work)
{
    int count = iSPCHPick_VoxSentence_GetNumPhrases(p);
    for (int i = 0; i < count; i++) {
        int n = work->mEntries[i].mCount;
        unsigned char *values = work->mValues + work->mEntries[i].mFirst;
        while (n > 1) {
            int j = iSPCH_Rand(n, -1);
            unsigned char value = values[n - 1];
            values[n - 1] = values[j];
            values[j] = value;
            n--;
        }
    }
}

// Advance the mixed-radix combination of phrase choices.
int iSPCH_IterateChoice(unsigned char *p, SpchSentencePick_t *work)
{
    int result = 0;
    int index = iSPCHPick_VoxSentence_GetNumPhrases(p) - 1;
    int done = 0;
    SpchPhrasePick_t *entry = &work->mEntries[index];
    int count = entry->mCount;
    int end = entry->mFirst + count;
    do {
        entry->mCurrent++;
        if (entry->mCurrent < end) {
            done = 1;
        } else {
            entry->mCurrent = entry->mFirst;
            if (--index < 0) {
                done = 1;
                result = 1;
            }
            entry = &work->mEntries[index];
            count = entry->mCount;
            end = entry->mFirst + count;
        }
    } while (!done);
    return result;
}

// Search sample combinations for duration and parameter compatibility.
int iSPCH_ChooseSentenceIteratively(unsigned char *p, SpchSentencePick_t *work, int limit)
{
    int count = iSPCHPick_VoxSentence_GetNumPhrases(p);
    int found = 0;
    int done = 0;
    for (int i = 0; i < count; i++) work->mEntries[i].mCurrent = work->mEntries[i].mFirst;
    while (!done && !found) {
        found = 1;
        if (limit) found = iSPCH_SentenceLength(p, work) <= limit;
        if (found) {
            if (p[3] && !iSPCH_TestMatchParms(work, p)) found = 0;
        }
        if (!found) done = iSPCH_IterateChoice(p, work);
    }
    return found;
}

// Choose a sample from one phrase's candidate range.
int iSPCH_PickPhraseSample(SpchPhrasePick_t *p)
{
    int value = iSPCH_Rand(p->mCount, p->mBankIndex);
    p->mCurrent = p->mFirst + value;
    return 1;
}

// Publish the selected samples' global output parameters.
void iSPCH_PostGlobalMatchParms(SpchEventKey_t *key, SpchSentencePick_t *work, unsigned char *p)
{
    char *text;
    if (iSPCH_GetGlobalMatchParmsArray(key, &text)) {
        int count = iSPCHPick_VoxSentence_GetNumPhrases(p);
        for (int i = 0; i < count; i++) {
            SpchPhrase_t *record = (SpchPhrase_t *)iSPCHPick_GetOffset8((char *)p, p + 8, i);
            for (int j = 0; j < record->mParmCount; j++) {
                if (iSPCHPick_GetPhraseParmInfo(record, j)->mEventParm == 254) {
                    if (!(iSPCHPick_GetPhraseParmInfo(record, j)->mMatchParm & 128)) {
                        int slot = work->mEntries[i].mBankIndex;
                        VoxBankHdr_t *bank = gVoxBanks[slot].mUnknown4;
                        char *values = iSPCH_GetSampleParmAddr(bank, work->mValues[work->mEntries[i].mCurrent]);
                        if (values) {
                            int index = iSPCHPick_GetPhraseParmInfo(record, j)->mMatchParm;
                            text[index] = values[j];
                        }
                    }
                }
            }
        }
    }
}

// Choose phrase samples and publish their output parameters.
int iSPCH_SentenceMakeChoice(SpchEventKey_t *key, SpchSentencePick_t *work, unsigned char *p, int a, int limit)
{
    int result;
    if (limit > 0 || p[3]) {
        iSPCH_RandomizeSentencePicks(p, work);
        result = iSPCH_ChooseSentenceIteratively(p, work, limit);
    } else {
        int count = iSPCHPick_VoxSentence_GetNumPhrases(p);
        result = 1;
        for (int i = 0; i < count; i++) {
            SpchPhrasePick_t *entry = &work->mEntries[i];
            if (!entry->mCount) { result = 0; goto done; }
            iSPCHPick_GetOffset8((char *)p, p + 8, i);
            if (!iSPCH_PickPhraseSample(entry)) { result = 0; goto done; }
        }
    }
    iSPCH_PostGlobalMatchParms(key, work, p);
done:
    return result;
}

// Notify rule callbacks for fixed parameters in the selected samples.
void iSPCH_ConstantRuleSet(SpchEventKey_t *key, VoxEvent_t *event, unsigned char *sentence)
{
    VoxDatSlot_t *slot;
    if (gCallbacks.mUnknown8 && iSPCH_FindEventDatInfo(key, &slot)) {
        int game = slot->mBank->mUnknown9;
        int channel = slot->mValue;
        int count = iSPCHPick_VoxSentence_GetNumPhrases(sentence);
        for (int i = 0; i < count; i++) {
            SpchPhrase_t *phrase = (SpchPhrase_t *)iSPCHPick_GetOffset8(
                (char *)sentence, sentence + 8, i);
            int n = phrase->mParmCount;
            for (int j = 0; j < n; j++) {
                int rule = iSPCHPick_GetPhraseParmInfo(phrase, j)->mRuleIndex;
                if (rule != 255) {
                    int id = iSPCH_GetRuleID(event, rule);
                    VoxBankHdr_t *bank = gVoxBanks[gEventChoice[channel].mEntries[i].mBankIndex].mUnknown4;
                    unsigned char *values = (unsigned char *)iSPCH_GetSampleParmAddr(bank, gEventChoice[channel].mEntries[i].mSample);
                    if (values) {
                        int mask = 1 << values[j];
                        gCallbacks.mUnknown8(key, id, mask, game);
                    }
                }
            }
        }
    }
}

// Resolve saved bank handles and submit playback requests in phrase order.
int iSPCH_MakeSampleRequests(VoxEvent_t *event, unsigned char *sentence, SpchEventKey_t *key)
{
    SpchSampleRequest_t request;
    VoxDatSlot_t *slot;
    int total = 0;
    int result = 0;
    if (gCallbacks.mUnknown0 && iSPCH_FindEventDatInfo(key, &slot)) {
        int game = slot->mBank->mUnknown9;
        int channel = slot->mValue;
        int count = iSPCHPick_VoxSentence_GetNumPhrases(sentence);
        int i;
        for (i = 0; i < count; i++) {
            SpchChosenSample_t *pick = &gEventChoice[channel].mEntries[i];
            int handle = pick->mHandle;
            if (gVoxBanks[pick->mBankIndex].mUnknown0 != handle) {
                int index = iSPCH_FindBankIndexFromHandle(handle);
                pick->mBankIndex = index;
                if (index & 0x8000) goto done;
            }
        }
        for (i = 0; i < count; i++) {
            SpchChosenSample_t *pick = &gEventChoice[channel].mEntries[i];
            int handle = pick->mHandle;
            int sample = pick->mSample;
            VoxBankHdr_t *bank = gVoxBanks[pick->mBankIndex].mUnknown4;
            if ((bank->mUnknown4 & 128) && gClearCycle) iSPCH_ClearCycleBit(bank, sample);
            int start, size;
            if (iSPCH_GetSampleSizeData(bank, sample, &start, &size)) {
                int offset = start;
                int stride = bank->mUnknown8 * ((bank->mUnknown7 + 1) << 8);
                if (pick->mSubBank != -1) offset += pick->mSubBank * stride;
                request.mBank = handle;
                request.mStart = offset;
                request.mSize = size;
                total += size;
                request.mKey = *key;
                request.mGame = game;
                request.mChannel = channel;
                request.mUnknown14 = bank->mUnknown2;
                request.mInterrupt = i == 0 ? iSPCHPick_VoxEvent_GetInterruptFlag(event) : 0;
                ((void (*)(SpchSampleRequest_t *))gCallbacks.mUnknown0)(&request);
                iSPCHBank_AddToQueue(bank, sample);
            }
        }
        result = iSPCH_ConvertTime(total);
    }
done:
    return result;
}

// Clear the sentence selection counts and phrase-ready flags.
void iSPCH_InitSentencePickInfo(SpchSentencePick_t *p)
{
    p->mCount = 0;
    p->mPhraseCount = 0;
    for (int i = 0; i <= 11; i++) p->mEntries[i].mReady = 0;
}

// Free one channel's saved event and clear its selected samples.
void iSPCH_ClearSentenceChoiceChannel(int channel)
{
    if (gEventChoice[channel].mParameters) {
        iSPCH_MemFree(gEventChoice[channel].mParameters);
        gEventChoice[channel].mParameters = 0;
    }
    gEventChoice[channel].mSentence = 0;
    gEventChoice[channel].mEvent = 0;
    gEventChoice[channel].mSentenceIndex = 0;
    gEventChoice[channel].mReady = 0;
    gEventChoice[channel].mPhraseCount = 0;
    gEventChoice[channel].unk_0xB = 0;
    gEventChoice[channel].mParameters = 0;
    for (int i = 0; i <= 11; i++) {
        gEventChoice[channel].mEntries[i].mHandle = -1;
        gEventChoice[channel].mEntries[i].mBankIndex = -1;
        gEventChoice[channel].mEntries[i].mSubBank = -1;
        gEventChoice[channel].mEntries[i].mSample = 0;
    }
}

// Initialize the eight saved sentence-choice channels.
void iSPCH_InitSentenceChoice(void)
{
    for (int channel = 0; channel <= 7; channel++) {
        gEventChoice[channel].mEvent = 0;
        gEventChoice[channel].mSentence = 0;
        gEventChoice[channel].mSentenceIndex = 0;
        gEventChoice[channel].mReady = 0;
        gEventChoice[channel].mPhraseCount = 0;
        gEventChoice[channel].unk_0xB = 0;
        gEventChoice[channel].mParameters = 0;
        for (int i = 0; i <= 11; i++) {
            gEventChoice[channel].mEntries[i].mHandle = -1;
            gEventChoice[channel].mEntries[i].mBankIndex = -1;
            gEventChoice[channel].mEntries[i].mSubBank = -1;
            gEventChoice[channel].mEntries[i].mSample = 0;
        }
    }
}

// Save the event parameters and selected samples for a channel.
void iSPCH_SaveChosenSentence(SpchSentencePick_t *work, unsigned int channel, VoxEvent_t *event,
    unsigned char *sentence, int index, int *values)
{
    int i;
    if (gEventChoice[channel].mParameters) iSPCH_MemFree(gEventChoice[channel].mParameters);
    gEventChoice[channel].mParameters = iSPCH_MemAlloc((event->mUnknownB + 1) * 4);
    if (gEventChoice[channel].mParameters) {
        gEventChoice[channel].mSentence = (int)sentence;
        gEventChoice[channel].mEvent = (int)event;
        gEventChoice[channel].mSentenceIndex = index;
        for (i = 0; i <= event->mUnknownB; i++) {
            ((int *)gEventChoice[channel].mParameters)[i] = values[i];
        }
        gEventChoice[channel].mReady = 1;
        int count = iSPCHPick_VoxSentence_GetNumPhrases(sentence);
        for (i = 0; i < count; i++) {
            gEventChoice[channel].mEntries[i].mBankIndex = work->mEntries[i].mBankIndex;
            gEventChoice[channel].mEntries[i].mHandle = work->mEntries[i].mHandle;
            gEventChoice[channel].mEntries[i].mSubBank = work->mEntries[i].mSubBank;
            gEventChoice[channel].mEntries[i].mSample = work->mValues[work->mEntries[i].mCurrent];
        }
        gEventChoice[channel].mPhraseCount = count;
    }
}

// Test whether a channel has a saved sentence ready to play.
int iSPCH_OneChosen(unsigned int channel)
{
    return gEventChoice[channel].mReady;
}

// Apply the saved sentence's rules, request playback and clear the channel.
int iSPCH_PlayChosen(int channel)
{
    int result = 0;
    if ((unsigned int)channel <= 7 && iSPCH_OneChosen(channel)) {
        SpchEventKey_t key = *(SpchEventKey_t *)gEventChoice[channel].mParameters;
        iSPCH_RuleSet(&key, (VoxEvent_t *)gEventChoice[channel].mEvent,
            gEventChoice[channel].mSentenceIndex, (int *)gEventChoice[channel].mParameters);
        iSPCH_ConstantRuleSet(&key, (VoxEvent_t *)gEventChoice[channel].mEvent,
            (unsigned char *)gEventChoice[channel].mSentence);
        iSPCH_MakeSampleRequests((VoxEvent_t *)gEventChoice[channel].mEvent,
            (unsigned char *)gEventChoice[channel].mSentence, &key);
        result = iSPCHPick_VoxSentence_GetNumPhrases((unsigned char *)gEventChoice[channel].mSentence);
        if (key.mId == gVoxInGame[channel].mKey.mId) {
            gVoxInGame[channel].mUnknown4++;
        } else {
            gVoxInGame[channel].mKey = key;
            gVoxInGame[channel].mUnknown4 = 1;
        }
    }
    iSPCH_ClearSentenceChoiceChannel(channel);
    return result;
}

// Test one event parameter according to its packed type.
int iSPCH_TestValidParm(unsigned int bits, int value, int index)
{
    int result = 0;
    switch ((bits >> (index * 2)) & 3) {
    case 1:
        if (value != 0) result = 1;
        break;
    case 2:
        if (value != -1) result = 1;
        break;
    }
    return result;
}

// Build the mask of valid event parameters.
int iSPCH_MakeValidParmsMask(VoxEvent_t *p, int *values)
{
    unsigned short mask = 1;
    unsigned int bits = VoxEvent_GetParmTypesMask(p);
    int result = 0;
    for (int i = 0; i <= 15; i++) {
        if (iSPCH_TestValidParm(bits, values[i + 1], i)) {
            result |= mask;
        }
        mask <<= 1;
    }
    return result;
}

// Check sentence context masks against the supplied event parameters.
int iSPCH_SentenceIsContextMatch(VoxEvent_t *event, unsigned char *sentence, int *values)
{
    SpchContextRule_t rule;
    int count = iSPCHPick_VoxEvent_GetNumContexts(event);
    int result = 1;
    if (count) {
        int *flags = (int *)VoxSentence_GetContextFlagsAddr(sentence);
        unsigned char *rules = (unsigned char *)iSPCHPick_GetContextDataAddr(event);
        for (int i = 0; i < count; i++) {
            rule.mId = rules[i * 3];
            rule.mParm = rules[i * 3 + 1];
            rule.mType = rules[i * 3 + 2];
            int mask = flags[i];
            if (mask && !(mask & values[rule.mParm])) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

// Apply the sentence's percentage-frequency gate.
int iSPCH_CheckFrequency(unsigned char *p)
{
    return iSPCH_Rand(100, -1) < p[1];
}

// Choose and save the first sentence satisfying all event filters.
int iSPCH_ChooseSentence(int *values)
{
    signed char order[100];
    SpchSentencePick_t work;
    SpchEventKey_t key = *(SpchEventKey_t *)values;
    int channel;
    int result = 0;
    unsigned int ignored = result;
    int current = 0;
    VoxEvent_t *event = iSPCH_FindEvent(&key);
    int mask = 0;
    int limit = 0;
    if (event && iSPCH_FindEventChannel(&key, &channel) && iSPCH_RepeatEvent(event, channel)) {
        int mode = gFilterSetting[channel];
        if (mode == 1) {
            if (!VoxEvent_GetFilterLengthFlag(event)) mode = 0;
            else limit = iSPCH_GetFilterLength(&key);
        }
        unsigned int rules = iSPCH_GetRuleSettings(&key, event, values, &ignored);
        iSPCH_OrderSentences(event, order);
        int count = event->mUnknown6;
        if (count <= 0) { result = -1; goto done; }
        int exact = iSPCHPick_VoxEvent_GetExactParmMatchFlag(event);
        if (exact) mask = iSPCH_MakeValidParmsMask(event, values);
        result = 0;
        while (current < count) {
            int index = order[current];
            int match = 1;
            if (index < 0 || index >= count) goto done;
            unsigned char *sentence = (unsigned char *)iSPCHPick_GetOffset16((char *)event,
                (unsigned short *)((char *)event + 12), index);
            if (iSPCH_CheckFrequency(sentence) && iSPCH_SentenceIsContextMatch(event, sentence, values) &&
                iSPCH_CheckSentenceRules(event, index, rules, ignored)) {
                if (exact) match = VoxEvent_GetSentenceParmMask(event, index) == mask;
                if (match) {
                    iSPCH_InitSentencePickInfo(&work);
                    if (iSPCH_SentenceGetChoices(&work, sentence, (SpchEventParm_t *)values, mode) > 0) {
                        result = iSPCH_SentenceMakeChoice(&key, &work, sentence, mode, limit);
                        if (result) iSPCH_SaveChosenSentence(&work, channel, event, sentence, index, values);
                    }
                }
            }
            current++;
            if (result) break;
        }
    }
done:
    return result;
}

// Choose a queued voice's sentence, allowing callback-driven retries.
int iSPCH_ChooseSingleSentence(int voice)
{
    int result = 0;
    int *values = gVoxEvents.mVoices[voice].mEvent;
    if (values) {
        result = iSPCH_ChooseSentence(values);
        if (!result && gCallbacks.mUnknown10) {
            int attempt = 0;
            int retry;
            do {
                retry = ((int (*)(int, int *))gCallbacks.mUnknown10)(attempt, values);
                if (retry >= 0) result = iSPCH_ChooseSentence(values);
                attempt++;
            } while (!result && retry > 0);
        }
        if (result < 0) result = 0;
    }
    return result;
}

// Set the speech preload scheduling offset.
void SPCH_SetPreLoadTicks(int value)
{
    gPreLoadTicks = value;
}

// Advance the shared six-word generator and return its leading word.
unsigned int iSPCH_EACrandom(void)
{
    unsigned int sum = seedX[5] + seedX[4];
    unsigned int carry = sum < seedX[5] || sum < seedX[4];
    seedX[4] = sum;
    unsigned int old3 = seedX[3];
    sum = sum + old3 + carry;
    seedX[3] = sum;
    unsigned int old2 = seedX[2];
    carry = sum < old3;
    sum = sum + old2 + carry;
    seedX[2] = sum;
    unsigned int old1 = seedX[1];
    carry = sum < old2;
    sum = sum + old1 + carry;
    seedX[1] = sum;
    carry = sum < old1;
    sum = sum + seedX[0] + carry;
    seedX[0] = sum;
    if (++seedX[5] == 0) {
        if (++seedX[4] == 0) {
            if (++seedX[3] == 0) {
                if (++seedX[2] == 0) {
                    if (++seedX[1] == 0) {
                        // FAKEMATCH: re-read of the stored word keeps the
                        // incremented value in its own register (mr r3,r0).
                        seedX[0] = sum + 1;
                        sum = seedX[0];
                    }
                }
            }
        }
    }
    return sum;
}

}
