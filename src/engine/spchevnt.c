/* Speech events (spchevnt.c): finds a commentary event in the loaded event data, checks its
   priority against the lines already playing and queues it on a speech channel. */

#include "engine/spchlib.h"

extern "C" {

int fn_801AE3E4(int n)
{
    return (n * 2 + 7) & ~3;
}

int fn_801AE3F4(Item_801AE3F4 *item)
{
    return item->mUnknown7;
}

int fn_801AE3FC(Item_801AE3F4 *item)
{
    return item->mUnknown8 >> 4;
}

int fn_801AE408(Item_801AE3F4 *item)
{
    return (item->mUnknownA >> 1) & 1;
}

int fn_801AE414(Item_801AE3F4 *item)
{
    return (item->mUnknownA >> 2) & 1;
}

int fn_801AE420(Item_801AE3F4 *item)
{
    return (item->mUnknownA >> 3) & 1;
}

int fn_801AE42C(Item_801AE3F4 *item)
{
    return (item->mUnknownA >> 4) & 1;
}

int fn_801AE438(Item_801AE3F4 *item)
{
    return (item->mUnknownA >> 5) & 1;
}

char *fn_801AE444(Bank_801AE444 *bank)
{
    return (char *)bank->mUnknown18 + ((bank->mUnknown10 * 2 + 3) & ~3);
}

Item_801AE3F4 *fn_801AE460(Bank_801AE444 *bank, unsigned short *offsets, int i)
{
    return (Item_801AE3F4 *)((char *)bank + offsets[i] * 4);
}

char *fn_801AE474(Item_801AE3F4 *item)
{
    return (char *)(item + 1) + ((item->mUnknown6 * 2 + 3) & ~3);
}

char *fn_801AE490(Item_801AE3F4 *item)
{
    char *p = fn_801AE474(item);
    return p + ((fn_801AE3F4(item) * 3 + 3) & ~3);
}

char *fn_801AE4DC(Item_801AE3F4 *item)
{
    char *p = fn_801AE490(item);
    return p + (((fn_801AE3F4(item) + 7) / 8 * item->mUnknown6 * 2 + 3) & ~3);
}

int fn_801AE53C(Item_801AE3F4 *item, List_801AEDA4 *list)
{
    int result = 0;
    unsigned char *p;

    if (fn_801AE42C(item)) {
        result = 1;
        p = (unsigned char *)fn_801AE4DC(item);
        p += (fn_801AE3FC(item) * 3 + 3) & ~3;
        if (fn_801AE420(item)) {
            p += fn_801AE3E4(item->mUnknown6);
        }
        list->mCount = *p;
        list->mIds = (unsigned short *)(p + 2);
    }
    return result;
}

int fn_801AE5D4(int a, int b, int c)
{
    SpchEventKey_t key;

    key.mUnknown2 = b;
    key.mId = c;
    key.mUnknown3 = a;
    return *(int *)&key;
}

Item_801AE3F4 *fn_801AE5F0(Bank_801AE444 *bank, int id)
{
    int i;
    int n = bank->mUnknown10;

    for (i = 0; i < n; i++) {
        Item_801AE3F4 *item = fn_801AE460(bank, bank->mUnknown18, i);
        if (item->mId == id) {
            return item;
        }
    }
    return 0;
}

int fn_801AE658(SpchEventKey_t *key, Slot_8037E0B4 **out)
{
    int found = 0;
    int i;

    for (i = 0; i < 8; i++) {
        Bank_801AE444 *bank = lbl_8037E0B4[i].mBank;
        if (bank != 0) {
            if (bank->mUnknown9 == key->mUnknown2 && bank->mUnknown8 == key->mUnknown3) {
                *out = &lbl_8037E0B4[i];
                found = 1;
                break;
            }
        }
    }
    return found;
}

Item_801AE3F4 *fn_801AE6BC(SpchEventKey_t *key)
{
    Slot_8037E0B4 *slot;
    Item_801AE3F4 *item = 0;

    if (fn_801AE658(key, &slot)) {
        item = fn_801AE5F0(slot->mBank, key->mId);
    }
    return item;
}

int fn_801AE710(SpchEventKey_t *key, int *out)
{
    Slot_8037E0B4 *slot;
    int found = 0;

    if (fn_801AE658(key, &slot)) {
        found = 1;
        *out = slot->mValue;
    }
    return found;
}

int fn_801AE760(SpchEventKey_t *key, int *out)
{
    Slot_8037E0B4 *slot;
    int found = 0;

    if (fn_801AE658(key, &slot)) {
        found = 1;
        *out = slot->mBank->mUnknown9;
    }
    return found;
}

int fn_801AE7B4(SpchEventKey_t *key, char **out)
{
    Slot_8037E0B4 *slot;
    int found = 0;

    if (fn_801AE658(key, &slot)) {
        found = 1;
        *out = fn_801AE444(slot->mBank);
    }
    return found;
}

void fn_801AE808(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        lbl_8037E0B4[i].mBank = 0;
        lbl_8037E0B4[i].mValue = 0;
    }
}

int fn_801AE838(SpchEventKey_t *key)
{
    Slot_8037E0B4 *slot;
    int value = 0;

    if (fn_801AE658(key, &slot)) {
        value = slot->mBank->mUnknown14;
    }
    return value;
}

int fn_801AE880(SpchEventKey_t *key, Item_801AE3F4 *item)
{
    Slot_8037E0B4 *slot;
    int result = 0;

    if (fn_801AE658(key, &slot)) {
        result = (unsigned int)item->mUnknown4 < (unsigned int)slot->mBank->mUnknown16;
    }
    return result;
}

void fn_801AE8DC(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        lbl_8037E0F4.mCount[i] = 0;
        lbl_8037E0F4.mCurrent[i] = -1;
    }
    for (i = 0; i <= 15; i++) {
        lbl_8037E0F4.mVoices[i].mActive = 0;
        lbl_8037E0F4.mVoices[i].mSequence = 0;
        lbl_8037E0F4.mVoices[i].mTime = 0;
        lbl_8037E0F4.mVoices[i].mItem = 0;
        lbl_8037E0F4.mVoices[i].mChannel = 255;
        if (lbl_8037E0F4.mVoices[i].mEvent) {
            fn_801AF500(lbl_8037E0F4.mVoices[i].mEvent);
        }
        lbl_8037E0F4.mVoices[i].mEvent = 0;
    }
    lbl_803ECEB0 = 0;
    lbl_803ECEAC = 0;
}

int fn_801AE9A0(unsigned int priority, int channel)
{
    int result = -1;
    int skip = -1;
    int i;
    unsigned int now;

    for (i = 0; i <= 15; i++) {
        if (!lbl_8037E0F4.mVoices[i].mActive) {
            return i;
        }
    }
    now = fn_801B2368();
    for (i = 0; i <= 15; i++) {
        unsigned int limit = lbl_8037E0F4.mVoices[i].mItem->mUnknown2;
        if (limit != 0 && now - lbl_8037E0F4.mVoices[i].mTime > limit && skip != i) {
            fn_801AF128(i);
            return i;
        }
    }
    for (i = 0; i <= 15; i++) {
        int c = lbl_8037E0F4.mVoices[i].mChannel;
        if (lbl_8037E0F4.mVoices[i].mItem->mUnknown4 <= priority && c == channel) {
            lbl_8037E0F4.mVoices[i].mActive = 0;
            lbl_8037E0F4.mCount[c]--;
            return i;
        }
    }
    return result;
}

int fn_801AEAC8(int channel)
{
    return (unsigned int)lbl_8037E0F4.mCurrent[channel] <= 15;
}

int fn_801AEAEC(int *event)
{
    int result = 0;

    if (lbl_803EBB18 == 0) {
        lbl_803EBB18 = 1;
        if (event) {
            SpchEventKey_t key;
            int channel;
            Item_801AE3F4 *item;

            key = *(SpchEventKey_t *)event;
            item = fn_801AE6BC(&key);
            if (item && fn_801AE710(&key, &channel)) {
                int level = item->mUnknown9;
                if (iSPCH_Rand(100, -1) <= level) {
                    int voice = fn_801AE9A0(item->mUnknown4, channel);
                    if (voice >= 0) {
                        unsigned int now = fn_801B2368();
                        if (now == lbl_803ECEAC) {
                            lbl_803ECEB0++;
                        } else {
                            lbl_803ECEB0 = 0;
                        }
                        lbl_8037E0F4.mVoices[voice].mItem = item;
                        lbl_8037E0F4.mVoices[voice].mChannel = channel;
                        lbl_8037E0F4.mVoices[voice].mSequence = lbl_803ECEB0;
                        lbl_8037E0F4.mVoices[voice].mTime = now;
                        lbl_803ECEAC = now;
                        if (lbl_8037E0F4.mVoices[voice].mEvent) {
                            fn_801AF500(lbl_8037E0F4.mVoices[voice].mEvent);
                        }
                        lbl_8037E0F4.mVoices[voice].mEvent = event;
                        lbl_8037E0F4.mCount[channel]++;
                        lbl_8037E0F4.mVoices[voice].mActive = 1;
                        lbl_8037E0F4.mCurrent[channel] = voice;
                        if (fn_801AE438(item)) {
                            fn_801AF2CC(channel);
                        }
                        result = 1;
                    }
                }
            }
        }
    }
    lbl_803EBB18 = 0;
    return result;
}

int fn_801AEC58(int id, int count, ...)
{
    va_list args;
    int *event;
    int result = 0;
    int i;

    va_start(args, count);
    event = (int *)fn_801AF4A8(count * 4 + 4);
    if (event) {
        event[0] = id;
        for (i = 1; i <= count; i++) {
            event[i] = va_arg(args, int);
        }
        result = fn_801AEAEC(event);
        if (result == 0) {
            fn_801AF500(event);
        }
    }
    return result;
}

void fn_801AEDA4(List_801AEDA4 *list)
{
    list->mCount = 0;
    list->mIds = 0;
}

int fn_801AEDB4(int id, List_801AEDA4 *list)
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

int fn_801AEE04(List_801AEDA4 *list, int channel)
{
    unsigned int now = fn_801B2368() + lbl_803ECEA8;
    int best = -1;
    int bestPriority = 0;
    unsigned int bestAge = (unsigned int)-1;
    unsigned int bestSequence = 0;
    int i;

    for (i = 0; i <= 15; i++) {
        if (lbl_8037E0F4.mVoices[i].mActive && lbl_8037E0F4.mVoices[i].mChannel == channel) {
            Item_801AE3F4 *item = lbl_8037E0F4.mVoices[i].mItem;
            int expired = 0;
            int blocked = 0;
            int match = 1;
            unsigned int age;

            if (list) {
                match = fn_801AEDB4(item->mId, list);
            }
            age = now - lbl_8037E0F4.mVoices[i].mTime;
            if (item->mUnknown2 != 0 && age > item->mUnknown2) {
                expired = 1;
            }
            if (gFilterSetting[channel] == 1 && fn_801AE408(item)) {
                SpchEventKey_t key = *(SpchEventKey_t *)lbl_8037E0F4.mVoices[i].mEvent;
                blocked = fn_801AE880(&key, item);
            }
            if (expired) {
                fn_801AF128(i);
            } else if (match && !blocked) {
                int priority = item->mUnknown4;
                if (priority > bestPriority) {
                    best = i;
                    bestAge = age;
                    bestPriority = priority;
                    bestSequence = lbl_8037E0F4.mVoices[best].mSequence;
                } else if (priority == bestPriority) {
                    if (age < bestAge ||
                        (age == bestAge && lbl_8037E0F4.mVoices[i].mSequence > bestSequence)) {
                        best = i;
                        bestAge = age;
                        bestSequence = lbl_8037E0F4.mVoices[best].mSequence;
                    }
                }
            }
        }
    }
    return best;
}

int fn_801AEFA0(int channel)
{
    List_801AEDA4 list;
    int found = 0;
    int voice;

    fn_801AEDA4(&list);
    if (lbl_8037E234[channel].mKey.mId != 0xFFFF) {
        Item_801AE3F4 *item = fn_801AE6BC(&lbl_8037E234[channel].mKey);
        if (item) {
            found = fn_801AE53C(item, &list);
        }
    }
    if (found) {
        voice = fn_801AEE04(&list, channel);
    } else {
        voice = fn_801AEE04(0, channel);
    }
    if (found && voice < 0) {
        voice = fn_801AEE04(0, channel);
    }
    return voice;
}

void fn_801AF060(void)
{
    int i;

    for (i = 0; i <= 15; i++) {
        if (lbl_8037E0F4.mVoices[i].mActive) {
            lbl_8037E0F4.mVoices[i].mActive = 0;
            if (lbl_8037E0F4.mVoices[i].mEvent) {
                fn_801AF500(lbl_8037E0F4.mVoices[i].mEvent);
                lbl_8037E0F4.mVoices[i].mEvent = 0;
            }
            lbl_8037E0F4.mCount[lbl_8037E0F4.mVoices[i].mChannel]--;
        }
    }
    for (i = 0; i <= 7; i++) {
        lbl_8037E0F4.mCurrent[i] = -1;
        if (lbl_8037E0F4.mCount[i]) {
            lbl_8037E0F4.mCount[i] = 0;
        }
    }
    fn_801AF544();
}

void fn_801AF128(unsigned int voice)
{
    if (voice <= 15) {
        int channel;

        if (lbl_8037E0F4.mVoices[voice].mEvent) {
            fn_801AF500(lbl_8037E0F4.mVoices[voice].mEvent);
            lbl_8037E0F4.mVoices[voice].mEvent = 0;
        }
        lbl_8037E0F4.mVoices[voice].mActive = 0;
        channel = lbl_8037E0F4.mVoices[voice].mChannel;
        if (voice == lbl_8037E0F4.mCurrent[channel]) {
            lbl_8037E0F4.mCurrent[channel] = -1;
        }
        lbl_8037E0F4.mCount[channel]--;
        if (lbl_8037E0F4.mCount[channel] < 0) {
            lbl_8037E0F4.mCount[channel] = 0;
        }
    }
}

void fn_801AF1C8(int voice)
{
    unsigned int sequence = lbl_8037E0F4.mVoices[voice].mSequence;
    int channel = lbl_8037E0F4.mVoices[voice].mChannel;
    unsigned int time = lbl_8037E0F4.mVoices[voice].mTime;
    int i;

    for (i = 0; i <= 15; i++) {
        if (i != voice && lbl_8037E0F4.mVoices[i].mActive && lbl_8037E0F4.mVoices[i].mChannel == channel) {
            unsigned int t = lbl_8037E0F4.mVoices[i].mTime;
            unsigned int s = lbl_8037E0F4.mVoices[i].mSequence;
            if (t < time || (t == time && s < sequence)) {
                if (!fn_801AE414(lbl_8037E0F4.mVoices[i].mItem)) {
                    fn_801AF128(i);
                }
            }
        }
    }
}

int fn_801AF28C(SpchEventKey_t *key)
{
    int result = 1;

    if (gCallbacks.mCallback) {
        result = gCallbacks.mCallback(key);
    }
    return result;
}

void fn_801AF2CC(unsigned int channel)
{
    if (lbl_803EBB1C == 0) {
        lbl_803EBB1C = 1;
        if (channel <= 7 && fn_801AEAC8(channel)) {
            int voice = lbl_8037E0F4.mCurrent[channel];
            int started;

            fn_801B10D8(channel);
            started = fn_801B1864(voice);
            fn_801AF128(voice);
            if (started) {
                fn_801B1380(channel);
            }
        }
    }
    lbl_803EBB1C = 0;
}

int fn_801AF364(unsigned int channel)
{
    int result = 0;

    if (lbl_803EBB1C == 0) {
        lbl_803EBB1C = 1;
        if (fn_801B1368(channel) || fn_801AF3D8(channel)) {
            result = fn_801B1380(channel);
        }
    }
    lbl_803EBB1C = 0;
    return result;
}

int fn_801AF3D8(unsigned int channel)
{
    int started = 0;

    if (channel <= 7 && lbl_8037E0F4.mCount[channel]) {
        do {
            SpchEventKey_t key;
            int voice = fn_801AEFA0(channel);

            if (voice < 0) {
                break;
            }
            key = *(SpchEventKey_t *)lbl_8037E0F4.mVoices[voice].mEvent;
            if (fn_801AF28C(&key) == 1) {
                fn_801B10D8(channel);
                started = fn_801B1864(voice);
                if (started) {
                    fn_801AF1C8(voice);
                    fn_801AF128(voice);
                } else {
                    fn_801AF128(voice);
                }
            } else {
                fn_801AF128(voice);
            }
        } while (started == 0);
    }
    return started;
}

void fn_801AF4A0(SpchAllocator *allocator)
{
    gSPCH_Allocator = allocator;
}

void *fn_801AF4A8(int size)
{
    void *p = 0;

    if (gSPCH_Allocator) {
        p = gSPCH_Allocator->vfn_01(size, 4, -1);
    }
    return p;
}

void fn_801AF500(void *p)
{
    if (gSPCH_Allocator) {
        gSPCH_Allocator->vfn_02(p);
    }
}

void fn_801AF544(void)
{
    int i;

    for (i = 0; i <= 7; i++) {
        lbl_8037E234[i].mKey.mId = 0xFFFF;
        lbl_8037E234[i].mUnknown4 = 0;
    }
}

int fn_801AF578(int a, int b, int mode)
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

void fn_801AF5E4(int a, int b)
{
    if (gSPCH_Initialized == 0x01789A34) {
        gCallbacks.mUnknown4 = a;
        gCallbacks.mUnknown8 = b;
    }
}

}
