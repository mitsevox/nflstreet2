/* Speech events (spchevnt.c): finds a commentary event in the loaded event data, checks its
   priority against the lines already playing and queues it on a speech channel. */

#include "engine/spchlib.h"

extern "C" {

// Re-entry guards of iSPCH_AddEvent and of SPCH_PlayLastEvent/SPCH_Play.
static int gAddEventStatus = 0;
static int gSPCHPlayStatus = 0;

int ExactMatch_NumBytes(int n)
{
    return (n * 2 + 7) & ~3;
}

int VoxEvent_GetNumRules(VoxEvent_t *item)
{
    return item->mUnknown7;
}

int VoxEvent_GetNumContexts(VoxEvent_t *item)
{
    return item->mUnknown8 >> 4;
}

int VoxEvent_GetFilterPriorityFlag(VoxEvent_t *item)
{
    return (item->mUnknownA >> 1) & 1;
}

int VoxEvent_GetKeepTillExpiresFlag(VoxEvent_t *item)
{
    return (item->mUnknownA >> 2) & 1;
}

int VoxEvent_GetExactParmMatchFlag(VoxEvent_t *item)
{
    return (item->mUnknownA >> 3) & 1;
}

int VoxEvent_GetFollowGroupFlag(VoxEvent_t *item)
{
    return (item->mUnknownA >> 4) & 1;
}

int VoxEvent_GetInterruptFlag(VoxEvent_t *item)
{
    return (item->mUnknownA >> 5) & 1;
}

static char *iSPCH_GetGlobalMatchParmAddr(VoxDat_t *bank)
{
    // FAKEMATCH: size computed then rounded up in place (reused local); the one-expression form ties the count load and the final sum into r9, the target keeps both in r0
    int size = bank->mUnknown10 * 2;
    size = (size + 3) & ~3;
    return (char *)bank + (size + 24);
}

static VoxEvent_t *iSPCH_GetOffset16(VoxDat_t *bank, unsigned short *offsets, int i)
{
    return (VoxEvent_t *)((char *)bank + offsets[i] * 4);
}

char *iSPCH_GetRuleDataAddr(VoxEvent_t *item)
{
    // FAKEMATCH: size computed then rounded up in place (reused local); the one-expression form ties the count load and the final sum into r9, the target keeps both in r0
    int size = item->mUnknown6 * 2;
    size = (size + 3) & ~3;
    return (char *)item + (size + 12);
}

char *iSPCH_GetSentenceRulesAddr(VoxEvent_t *item)
{
    char *p = iSPCH_GetRuleDataAddr(item);
    return p + ((VoxEvent_GetNumRules(item) * 3 + 3) & ~3);
}

char *iSPCH_GetContextDataAddr(VoxEvent_t *item)
{
    char *p = iSPCH_GetSentenceRulesAddr(item);
    return p + (((VoxEvent_GetNumRules(item) + 7) / 8 * item->mUnknown6 * 2 + 3) & ~3);
}

int VoxEvent_GetFollowEventData(VoxEvent_t *item, SpchFollowData_t *list)
{
    int result = 0;
    unsigned char *p;

    if (VoxEvent_GetFollowGroupFlag(item)) {
        result = 1;
        p = (unsigned char *)iSPCH_GetContextDataAddr(item);
        p += (VoxEvent_GetNumContexts(item) * 3 + 3) & ~3;
        if (VoxEvent_GetExactParmMatchFlag(item)) {
            p += ExactMatch_NumBytes(item->mUnknown6);
        }
        list->mCount = *p;
        list->mIds = (unsigned short *)(p + 2);
    }
    return result;
}

int SPCH_MakeEventSpec(int a, int b, int c)
{
    SpchEventKey_t key;

    key.mUnknown2 = b;
    key.mId = c;
    key.mUnknown3 = a;
    return *(int *)&key;
}

VoxEvent_t *iSPCH_SearchEventDat(VoxDat_t *bank, int id)
{
    int i;
    int n = bank->mUnknown10;

    for (i = 0; i < n; i++) {
        VoxEvent_t *item = iSPCH_GetOffset16(bank, bank->mUnknown18, i);
        if (item->mId == id) {
            return item;
        }
    }
    return 0;
}

int iSPCH_FindEventDatInfo(SpchEventKey_t *key, VoxDatSlot_t **out)
{
    int found = 0;
    int i;

    for (i = 0; i < 8; i++) {
        VoxDat_t *bank = gEventDats[i].mBank;
        if (bank != 0) {
            if (bank->mUnknown9 == key->mUnknown2 && bank->mUnknown8 == key->mUnknown3) {
                *out = &gEventDats[i];
                found = 1;
                // FAKEMATCH: goto past the loop; with break the loop keeps its jump-to-test form
                goto done;
            }
        }
    }
done:
    return found;
}

VoxEvent_t *iSPCH_FindEvent(SpchEventKey_t *key)
{
    VoxDatSlot_t *slot;
    VoxEvent_t *item = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        item = iSPCH_SearchEventDat(slot->mBank, key->mId);
    }
    return item;
}

int iSPCH_FindEventChannel(SpchEventKey_t *key, int *out)
{
    VoxDatSlot_t *slot;
    int found = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        found = 1;
        *out = slot->mValue;
    }
    return found;
}

int iSPCH_GetDatID(SpchEventKey_t *key, int *out)
{
    VoxDatSlot_t *slot;
    int found = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        found = 1;
        *out = slot->mBank->mUnknown9;
    }
    return found;
}

int iSPCH_GetGlobalMatchParmsArray(SpchEventKey_t *key, char **out)
{
    VoxDatSlot_t *slot;
    int found = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        found = 1;
        *out = iSPCH_GetGlobalMatchParmAddr(slot->mBank);
    }
    return found;
}

void iSPCH_InitEventDat(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        gEventDats[i].mBank = 0;
        gEventDats[i].mValue = 0;
    }
}

int iSPCH_GetFilterLength(SpchEventKey_t *key)
{
    VoxDatSlot_t *slot;
    int value = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        value = slot->mBank->mUnknown14;
    }
    return value;
}

int iSPCH_TestEventPriority(SpchEventKey_t *key, VoxEvent_t *item)
{
    VoxDatSlot_t *slot;
    int result = 0;

    if (iSPCH_FindEventDatInfo(key, &slot)) {
        result = (unsigned int)item->mUnknown4 < (unsigned int)slot->mBank->mUnknown16;
    }
    return result;
}

void iSPCH_InitEventQueue(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        gVoxEvents.mCount[i] = 0;
        gVoxEvents.mCurrent[i] = -1;
    }
    for (i = 0; i <= 15; i++) {
        gVoxEvents.mVoices[i].mActive = 0;
        gVoxEvents.mVoices[i].mSequence = 0;
        gVoxEvents.mVoices[i].mTime = 0;
        gVoxEvents.mVoices[i].mItem = 0;
        gVoxEvents.mVoices[i].mChannel = 255;
        if (gVoxEvents.mVoices[i].mEvent) {
            iSPCH_MemFree(gVoxEvents.mVoices[i].mEvent);
        }
        gVoxEvents.mVoices[i].mEvent = 0;
    }
    gLastTick = 0;
    gLastSubTick = 0;
}

int iSPCH_FindEventSlot(unsigned int priority, int channel)
{
    int result = -1;
    // FAKEMATCH: never-set skip index (always -1) tested in the expiry loop; the literal i != -1 gives 97.54%, no test 95.65%
    int skip = -1;
    int i;
    unsigned int now;

    for (i = 0; i <= 15; i++) {
        if (!gVoxEvents.mVoices[i].mActive) {
            // FAKEMATCH: result = i and goto done in place of return i (all three loops); with the returns the found cases return directly and the frame and registers differ
            result = i;
            goto done;
        }
    }
    now = fn_801B2368();
    for (i = 0; i <= 15; i++) {
        unsigned int limit = gVoxEvents.mVoices[i].mItem->mUnknown2;
        // FAKEMATCH: the never-set skip test (declaration above)
        if (limit != 0 && now - gVoxEvents.mVoices[i].mTime > limit && skip != i) {
            iSPCH_ClearEvent(i);
            result = i;
            goto done;
        }
    }
    for (i = 0; i <= 15; i++) {
        int c = gVoxEvents.mVoices[i].mChannel;
        if (gVoxEvents.mVoices[i].mItem->mUnknown4 <= priority && c == channel) {
            gVoxEvents.mVoices[i].mActive = 0;
            gVoxEvents.mCount[c]--;
            result = i;
            goto done;
        }
    }
done:
    return result;
}

int iSPCH_CheckLastEventIndex(int channel)
{
    return (unsigned int)gVoxEvents.mCurrent[channel] <= 15;
}

int iSPCH_AddEvent(int *event)
{
    int result = 0;

    if (gAddEventStatus == 0) {
        gAddEventStatus = 1;
        if (event) {
            SpchEventKey_t key;
            int channel;
            VoxEvent_t *item;

            key = *(SpchEventKey_t *)event;
            item = iSPCH_FindEvent(&key);
            if (item && iSPCH_FindEventChannel(&key, &channel)) {
                int level = item->mUnknown9;
                if (iSPCH_Rand(100, -1) <= level) {
                    int voice = iSPCH_FindEventSlot(item->mUnknown4, channel);
                    if (voice >= 0) {
                        unsigned int now = fn_801B2368();
                        if (now == gLastTick) {
                            gLastSubTick++;
                        } else {
                            gLastSubTick = 0;
                        }
                        gVoxEvents.mVoices[voice].mItem = item;
                        gVoxEvents.mVoices[voice].mChannel = channel;
                        gVoxEvents.mVoices[voice].mSequence = gLastSubTick;
                        gVoxEvents.mVoices[voice].mTime = now;
                        gLastTick = now;
                        if (gVoxEvents.mVoices[voice].mEvent) {
                            iSPCH_MemFree(gVoxEvents.mVoices[voice].mEvent);
                        }
                        gVoxEvents.mVoices[voice].mEvent = event;
                        gVoxEvents.mCount[channel]++;
                        gVoxEvents.mVoices[voice].mActive = 1;
                        gVoxEvents.mCurrent[channel] = voice;
                        if (VoxEvent_GetInterruptFlag(item)) {
                            SPCH_PlayLastEvent(channel);
                        }
                        result = 1;
                    }
                }
            }
        }
    }
    gAddEventStatus = 0;
    return result;
}

int SPCH_AddEventV(int id, int count, ...)
{
    va_list args;
    int *event;
    int result = 0;
    int i;

    va_start(args, count);
    event = (int *)iSPCH_MemAlloc(count * 4 + 4);
    if (event) {
        event[0] = id;
        for (i = 1; i <= count; i++) {
            event[i] = va_arg(args, int);
        }
        result = iSPCH_AddEvent(event);
        if (result == 0) {
            iSPCH_MemFree(event);
        }
    }
    return result;
}

void iSPCH_InitFollowData(SpchFollowData_t *list)
{
    list->mCount = 0;
    list->mIds = 0;
}

int iSPCH_EventInFollowGroup(int id, SpchFollowData_t *list)
{
    int found = 0;
    int i;

    for (i = 0; i < list->mCount; i++) {
        if (list->mIds[i] == id) {
            found = 1;
            break;
        }
    }
    return found;
}

int iSPCH_ChooseEventSearch(SpchFollowData_t *list, int channel)
{
    unsigned int now = fn_801B2368() + gPreLoadTicks;
    int best = -1;
    int bestPriority = 0;
    unsigned int bestAge = (unsigned int)-1;
    unsigned int bestSequence = 0;
    int i;

    for (i = 0; i <= 15; i++) {
        if (gVoxEvents.mVoices[i].mActive && gVoxEvents.mVoices[i].mChannel == channel) {
            VoxEvent_t *item = gVoxEvents.mVoices[i].mItem;
            int expired = 0;
            int blocked = 0;
            int match = 1;
            unsigned int age;

            if (list) {
                match = iSPCH_EventInFollowGroup(item->mId, list);
            }
            age = now - gVoxEvents.mVoices[i].mTime;
            if (item->mUnknown2 != 0 && age > item->mUnknown2) {
                expired = 1;
            }
            if (gFilterSetting[channel] == 1 && VoxEvent_GetFilterPriorityFlag(item)) {
                SpchEventKey_t key = *(SpchEventKey_t *)gVoxEvents.mVoices[i].mEvent;
                blocked = iSPCH_TestEventPriority(&key, item);
            }
            if (expired) {
                iSPCH_ClearEvent(i);
            } else if (match && !blocked) {
                int priority = item->mUnknown4;
                if (priority > bestPriority) {
                    best = i;
                    bestAge = age;
                    bestPriority = priority;
                    bestSequence = gVoxEvents.mVoices[best].mSequence;
                } else if (priority == bestPriority) {
                    if (age < bestAge ||
                        (age == bestAge && gVoxEvents.mVoices[i].mSequence > bestSequence)) {
                        best = i;
                        bestAge = age;
                        bestSequence = gVoxEvents.mVoices[best].mSequence;
                    }
                }
            }
        }
    }
    return best;
}

int iSPCH_ChooseEvent(int channel)
{
    SpchFollowData_t list;
    int found = 0;
    int voice;

    iSPCH_InitFollowData(&list);
    if (gVoxInGame[channel].mKey.mId != 0xFFFF) {
        VoxEvent_t *item = iSPCH_FindEvent(&gVoxInGame[channel].mKey);
        if (item) {
            found = VoxEvent_GetFollowEventData(item, &list);
        }
    }
    if (found) {
        voice = iSPCH_ChooseEventSearch(&list, channel);
    } else {
        voice = iSPCH_ChooseEventSearch(0, channel);
    }
    if (found && voice < 0) {
        voice = iSPCH_ChooseEventSearch(0, channel);
    }
    return voice;
}

void SPCH_ClearEventQueue(void)
{
    int i;

    for (i = 0; i <= 15; i++) {
        if (gVoxEvents.mVoices[i].mActive) {
            gVoxEvents.mVoices[i].mActive = 0;
            if (gVoxEvents.mVoices[i].mEvent) {
                iSPCH_MemFree(gVoxEvents.mVoices[i].mEvent);
                gVoxEvents.mVoices[i].mEvent = 0;
            }
            gVoxEvents.mCount[gVoxEvents.mVoices[i].mChannel]--;
        }
    }
    for (i = 0; i <= 7; i++) {
        gVoxEvents.mCurrent[i] = -1;
        if (gVoxEvents.mCount[i]) {
            gVoxEvents.mCount[i] = 0;
        }
    }
    iSPCH_InitInGame();
}

void iSPCH_ClearEvent(unsigned int voice)
{
    if (voice <= 15) {
        int channel;

        if (gVoxEvents.mVoices[voice].mEvent) {
            iSPCH_MemFree(gVoxEvents.mVoices[voice].mEvent);
            gVoxEvents.mVoices[voice].mEvent = 0;
        }
        gVoxEvents.mVoices[voice].mActive = 0;
        channel = gVoxEvents.mVoices[voice].mChannel;
        if (voice == gVoxEvents.mCurrent[channel]) {
            gVoxEvents.mCurrent[channel] = -1;
        }
        gVoxEvents.mCount[channel]--;
        if (gVoxEvents.mCount[channel] < 0) {
            gVoxEvents.mCount[channel] = 0;
        }
    }
}

void iSPCH_ClearOldEvents(int voice)
{
    unsigned int sequence = gVoxEvents.mVoices[voice].mSequence;
    int channel = gVoxEvents.mVoices[voice].mChannel;
    unsigned int time = gVoxEvents.mVoices[voice].mTime;
    int i;

    for (i = 0; i <= 15; i++) {
        if (i != voice && gVoxEvents.mVoices[i].mActive && gVoxEvents.mVoices[i].mChannel == channel) {
            unsigned int t = gVoxEvents.mVoices[i].mTime;
            unsigned int s = gVoxEvents.mVoices[i].mSequence;
            if (t < time || (t == time && s < sequence)) {
                if (!VoxEvent_GetKeepTillExpiresFlag(gVoxEvents.mVoices[i].mItem)) {
                    iSPCH_ClearEvent(i);
                }
            }
        }
    }
}

int iSPCH_Callback_EventRule(SpchEventKey_t *key)
{
    int result = 1;

    if (gCallbacks.mCallback) {
        result = gCallbacks.mCallback(key);
    }
    return result;
}

void SPCH_PlayLastEvent(unsigned int channel)
{
    if (gSPCHPlayStatus == 0) {
        gSPCHPlayStatus = 1;
        if (channel <= 7 && iSPCH_CheckLastEventIndex(channel)) {
            int voice = gVoxEvents.mCurrent[channel];
            int started;

            fn_801B10D8(channel);
            started = fn_801B1864(voice);
            iSPCH_ClearEvent(voice);
            if (started) {
                fn_801B1380(channel);
            }
        }
    }
    gSPCHPlayStatus = 0;
}

int SPCH_Play(unsigned int channel)
{
    int result = 0;

    if (gSPCHPlayStatus == 0) {
        gSPCHPlayStatus = 1;
        if (fn_801B1368(channel) || SPCH_Choose(channel)) {
            result = fn_801B1380(channel);
        }
    }
    gSPCHPlayStatus = 0;
    return result;
}

int SPCH_Choose(unsigned int channel)
{
    int started = 0;

    if (channel <= 7 && gVoxEvents.mCount[channel]) {
        int voice;
        do {
            SpchEventKey_t key;
            voice = iSPCH_ChooseEvent(channel);

            if (voice < 0) {
                return started;
            }
            key = *(SpchEventKey_t *)gVoxEvents.mVoices[voice].mEvent;
            if (iSPCH_Callback_EventRule(&key) == 1) {
                fn_801B10D8(channel);
                started = fn_801B1864(voice);
                if (!started) {
                    iSPCH_ClearEvent(voice);
                }
            } else {
                iSPCH_ClearEvent(voice);
            }
        } while (started == 0);
        iSPCH_ClearOldEvents(voice);
        iSPCH_ClearEvent(voice);
    }
    return started;
}

void SPCH_SetAllocator(SpchAllocator *allocator)
{
    gSPCH_Allocator = allocator;
}

void *iSPCH_MemAlloc(int size)
{
    void *p = 0;

    if (gSPCH_Allocator) {
        p = gSPCH_Allocator->vfn_01(size, 4, -1);
    }
    return p;
}

void iSPCH_MemFree(void *p)
{
    if (gSPCH_Allocator) {
        gSPCH_Allocator->vfn_02(p);
    }
}

void iSPCH_InitInGame(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        gVoxInGame[i].mKey.mId = 0xFFFF;
        gVoxInGame[i].mUnknown4 = 0;
    }
}

int SPCH_GetSampleDataRate(int a, int b, int mode)
{
    int n = a * b / 8;

    switch (mode) {
    case 0:
        break;
    case 1:
        n = n / 10;
        break;
    case 2:
        n = n * 2 / 7;
        break;
    }
    return n;
}

void SPCH_InitRuleCallbacks(int (*a)(SpchEventKey_t *, int, int, int), void (*b)(SpchEventKey_t *, int, int, int))
{
    if (gSPCH_Initialized == 0x01789A34) {
        gCallbacks.mUnknown4 = a;
        gCallbacks.mUnknown8 = b;
    }
}

}
