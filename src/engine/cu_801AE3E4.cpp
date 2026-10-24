#include <stdarg.h>

#include "engine/cu_801AE3E4.h"
#include "engine/Object_80266AF8.h"

struct Entry_801AF84C {
    unsigned int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

struct Record_801AF75C {
    unsigned char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    Entry_801AF84C mEntries[1];
};



struct Result_801AFD04 {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
};

struct Buffer_801AFF74 {
    unsigned char mUnknown0[145];
    unsigned char mCount;
    unsigned char mValues[200];
};

struct Slot_801B2450 {
    int mUnknown0;
    unsigned char *mUnknown4;
};

struct WorkEntry_801B0B18 {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

struct Work_801B10AC {
    WorkEntry_801B0B18 mEntries[12];
    unsigned char mUnknown90;
    unsigned char mCount;
    unsigned char mValues[200];
};

struct ChannelEntry_801B118C {
    int mUnknown0;
    short mUnknown4;
    short mUnknown6;
    unsigned short mUnknown8;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
};

struct Channel_801B118C {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    void *mUnknownC;
    ChannelEntry_801B118C mEntries[12];
};

struct Key_801AE658 {
    unsigned short mId;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

struct Item_801AE3F4 {
    unsigned short mId;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    signed char mUnknown9;
    unsigned char mUnknownA;
};

struct Bank_801AE444 {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[6];
    unsigned short mUnknown10;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    unsigned short mUnknown18[1];
};

struct Slot_8037E0B4 {
    Bank_801AE444 *mBank;
    int mValue;
};

struct Voice_8037E0F4 {
    unsigned int mTime;
    unsigned short mSequence;
    unsigned char mActive;
    unsigned char mChannel;
    Item_801AE3F4 *mItem;
    int *mEvent;
};

struct State_8037E0F4 {
    int mCount[8];
    int mCurrent[8];
    Voice_8037E0F4 mVoices[16];
};

struct Pending_8037E234 {
    Key_801AE658 mKey;
    int mUnknown4;
};

struct List_801AEDA4 {
    int mCount;
    unsigned short *mIds;
};

struct Config_8037E0A0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int (*mCallback)(Key_801AE658 *key);
    int mUnknown10;
};

class Class_803EBAF8 {
public:
    virtual void *vfn_01(int size, int align, int flags);
    virtual void vfn_02(void *p);
};

extern "C" {
extern Config_8037E0A0 lbl_8037E0A0;
extern Slot_8037E0B4 lbl_8037E0B4[8];
extern State_8037E0F4 lbl_8037E0F4;
extern Pending_8037E234 lbl_8037E234[8];
extern int lbl_8037E274[8];
extern char lbl_802F4794[];
extern Class_803EBAF8 *lbl_803EBAF8;
extern int lbl_803EBAFC;
extern int lbl_803EBB18;
extern int lbl_803EBB1C;
extern int lbl_803ECEA0;
extern int lbl_803ECEA4;
extern int lbl_803ECEA8;
extern unsigned int lbl_803ECEAC;
extern unsigned short lbl_803ECEB0;
extern int lbl_803EBB04;
extern int lbl_803EBB08;
extern int lbl_803EBB0C;
extern Slot_801B2450 *lbl_803EBB00;
extern int lbl_802F475C[8];
extern Channel_801B118C lbl_8037E294[8];
extern unsigned int lbl_802F477C[6];
extern unsigned short lbl_8037E794[32][2];
extern int lbl_803EBB20;
unsigned int fn_801B1934(void);
int fn_801B22E0(Record_801AF75C *, int, int *, int *);
int fn_801B05E4(Work_801B10AC *, unsigned char *);
char *fn_801B22B0(Record_801AF75C *, int);
int fn_801B2648(unsigned int, int *);
int fn_801B26D8(unsigned int, unsigned int, int *);
int fn_801B2798(int, unsigned int);

unsigned int fn_801B2368(void);
int fn_801B1C1C(int a, int b);
void fn_801B10D8(int channel);
int fn_801B1864(int voice);
int fn_801B1380(int channel);
int fn_801B1368(unsigned int channel);
void fn_801B1B70(int a);
void fn_801B118C(void);
void fn_801B192C(int a);
void fn_801B2450(void);
void fn_801B2468(void);

void *fn_801AF4A8(int size);
void fn_801AF500(void *p);
void fn_801AF128(unsigned int voice);
int fn_801AF3D8(unsigned int channel);
void fn_801AF544(void);
void fn_801AF60C(void);
int fn_801AEC58(int id, int count, ...);

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
    Key_801AE658 key;

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

int fn_801AE658(Key_801AE658 *key, Slot_8037E0B4 **out)
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

Item_801AE3F4 *fn_801AE6BC(Key_801AE658 *key)
{
    Slot_8037E0B4 *slot;
    Item_801AE3F4 *item = 0;

    if (fn_801AE658(key, &slot)) {
        item = fn_801AE5F0(slot->mBank, key->mId);
    }
    return item;
}

int fn_801AE710(Key_801AE658 *key, int *out)
{
    Slot_8037E0B4 *slot;
    int found = 0;

    if (fn_801AE658(key, &slot)) {
        found = 1;
        *out = slot->mValue;
    }
    return found;
}

int fn_801AE760(Key_801AE658 *key, int *out)
{
    Slot_8037E0B4 *slot;
    int found = 0;

    if (fn_801AE658(key, &slot)) {
        found = 1;
        *out = slot->mBank->mUnknown9;
    }
    return found;
}

int fn_801AE7B4(Key_801AE658 *key, char **out)
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

int fn_801AE838(Key_801AE658 *key)
{
    Slot_8037E0B4 *slot;
    int value = 0;

    if (fn_801AE658(key, &slot)) {
        value = slot->mBank->mUnknown14;
    }
    return value;
}

int fn_801AE880(Key_801AE658 *key, Item_801AE3F4 *item)
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
            Key_801AE658 key;
            int channel;
            Item_801AE3F4 *item;

            key = *(Key_801AE658 *)event;
            item = fn_801AE6BC(&key);
            if (item && fn_801AE710(&key, &channel)) {
                int level = item->mUnknown9;
                if (fn_801B1C1C(100, -1) <= level) {
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
            if (lbl_8037E274[channel] == 1 && fn_801AE408(item)) {
                Key_801AE658 key = *(Key_801AE658 *)lbl_8037E0F4.mVoices[i].mEvent;
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

int fn_801AF28C(Key_801AE658 *key)
{
    int result = 1;

    if (lbl_8037E0A0.mCallback) {
        result = lbl_8037E0A0.mCallback(key);
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
            Key_801AE658 key;
            int voice = fn_801AEFA0(channel);

            if (voice < 0) {
                break;
            }
            key = *(Key_801AE658 *)lbl_8037E0F4.mVoices[voice].mEvent;
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

void fn_801AF4A0(Class_803EBAF8 *allocator)
{
    lbl_803EBAF8 = allocator;
}

void *fn_801AF4A8(int size)
{
    void *p = 0;

    if (lbl_803EBAF8) {
        p = lbl_803EBAF8->vfn_01(size, 4, -1);
    }
    return p;
}

void fn_801AF500(void *p)
{
    if (lbl_803EBAF8) {
        lbl_803EBAF8->vfn_02(p);
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
    if (lbl_803EBAFC == 0x01789A34) {
        lbl_8037E0A0.mUnknown4 = a;
        lbl_8037E0A0.mUnknown8 = b;
    }
}

void fn_801AF60C(void)
{
    lbl_8037E0A0.mUnknown0 = 0;
    lbl_8037E0A0.mUnknown4 = 0;
    lbl_8037E0A0.mUnknown8 = 0;
    lbl_8037E0A0.mCallback = 0;
    lbl_8037E0A0.mUnknown10 = 0;
}

void fn_801AF630(int (*callback)(Key_801AE658 *key))
{
    if (lbl_803EBAFC == 0x01789A34) {
        lbl_8037E0A0.mCallback = callback;
    }
}

int fn_801AF650(int a, int b, int c)
{
    int i;

    lbl_802F4794[0] = 'S';
    if (lbl_803EBAF8 != 0) {
        fn_801AF60C();
        lbl_803ECEA4 = c;
        lbl_8037E0A0.mUnknown0 = a;
        lbl_803EBB10 = fn_801AEC58;
        lbl_803ECEA0 = b;
        fn_801B1B70(b);
        fn_801B118C();
        fn_801B192C(0);
        for (i = 0; i <= 7; i++) {
            lbl_8037E274[i] = 0;
        }
        fn_801AE808();
        fn_801AF544();
        fn_801B2450();
        fn_801AE8DC();
        lbl_803EBAFC = 0x01789A34;
        return 1;
    }
    return 0;
}

void fn_801AF718(void)
{
    if (lbl_803EBAFC == 0x01789A34) {
        lbl_803EBAFC = 0;
        fn_801AF60C();
        fn_801B2468();
        fn_801AE808();
    }
}


char *fn_801AF75C(Record_801AF75C *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

char *fn_801AF780(Record_801AF75C *p)
{
    char *result = fn_801AF75C(p);
    return result + (p->mUnknown4 & 127) * 4;
}

char *fn_801AF7B8(Record_801AF75C *p)
{
    int size = 0;
    char *result = fn_801AF780(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

char *fn_801AF80C(Record_801AF75C *p)
{
    char *result = fn_801AF7B8(p);
    int size = p->mUnknown6;
    if (size) {
        result += size + 1;
    }
    return result;
}

Entry_801AF84C *fn_801AF84C(Record_801AF75C *p, int i)
{
    return p->mEntries + i;
}

int fn_801AF85C(unsigned char *p)
{
    return p[2] >> 2;
}

int fn_801AF868(unsigned char *p)
{
    return p[2] & 3;
}

char *fn_801AF874(unsigned char *p)
{
    return (char *)p + (((fn_801AF85C(p) + 3) & ~3) + 8);
}

char *fn_801AF8B0(unsigned char *p)
{
    int size = p[4] * 4;
    return fn_801AF874(p) + size;
}

int fn_801AF8E4(Item_801AE3F4 *p)
{
    return p->mUnknown7;
}

int fn_801AF8EC(Item_801AE3F4 *p)
{
    return p->mUnknown8 & 15;
}

int fn_801AF8F8(Item_801AE3F4 *p)
{
    return p->mUnknown8 >> 4;
}

int fn_801AF904(Item_801AE3F4 *p)
{
    return p->mUnknownA & 1;
}

int fn_801AF910(Item_801AE3F4 *p)
{
    return (p->mUnknownA >> 3) & 1;
}

int fn_801AF91C(Item_801AE3F4 *p)
{
    return (p->mUnknownA >> 5) & 1;
}

char *fn_801AF928(char *p, unsigned char *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801AF938(char *p, unsigned short *offsets, int i)
{
    return p + offsets[i] * 4;
}

char *fn_801AF94C(Item_801AE3F4 *p)
{
    return (char *)p + (((p->mUnknown6 * 2 + 3) & ~3) + 12);
}

char *fn_801AF968(Item_801AE3F4 *p)
{
    char *result = fn_801AF94C(p);
    return result + ((fn_801AF8E4(p) * 3 + 3) & ~3);
}

char *fn_801AF9B4(Item_801AE3F4 *p)
{
    char *result = fn_801AF968(p);
    return result + ((((fn_801AF8E4(p) + 7) / 8) * p->mUnknown6 * 2 + 3) & ~3);
}

int fn_801AFA14(Item_801AE3F4 *p, int i)
{
    char *result = fn_801AF9B4(p);
    result += (fn_801AF8F8(p) * 3 + 3) & ~3;
    return ((unsigned short *)(result + 4))[i];
}

int fn_801AFA70(Item_801AE3F4 *p)
{
    char *result = fn_801AF9B4(p);
    return *(int *)(result + ((fn_801AF8F8(p) * 3 + 3) & ~3));
}

void fn_801AFABC(Object_80266AF8 *p, int *a, int *b)
{
    *a = p->mUnknown8;
    *b = p->mUnknown9;
}


void fn_801AFAD0(unsigned char *p, Record_801AF75C *record, unsigned char *values)
{
    int *words = (int *)fn_801AF8B0(p);
    int count = (signed char)record->mUnknown4;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 254) {
            int flags = fn_801AF84C(record, i)->mUnknown6;
            if (flags & 128) {
                words[flags & 127] |= 1 << values[i];
            }
        }
    }
}

int fn_801AFB70(Record_801AF75C *record)
{
    int found = 0;
    int count = (signed char)record->mUnknown4;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 254) {
            found = 1;
            break;
        }
    }
    return found;
}

int fn_801AFBD8(unsigned char *p, Record_801AF75C *record, int *event, unsigned char *values)
{
    int count = (signed char)record->mUnknown4;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int value = values[i];
        result = 0;
        if ((unsigned int)value > 31) break;
        unsigned int mask = 1U << value;
        int id = fn_801AF84C(record, i)->mUnknown4;
        if (fn_801AF84C(record, i)->mUnknown0 & mask) {
            if (id == 0 || id == 254) {
                result = 1;
            } else if (id == 255) {
                int flags = fn_801AF84C(record, i)->mUnknown6;
                if (flags & 128) {
                    int *words = (int *)fn_801AF8B0(p);
                    if (words[flags & 127] & mask) result = 1;
                } else {
                    Key_801AE658 key = *(Key_801AE658 *)event;
                    char *text;
                    if (fn_801AE7B4(&key, &text) && (unsigned char)text[flags] == value) result = 1;
                }
            } else {
                if (event[id] & mask) result = 1;
            }
        }
        if (!result) break;
    }
    return result;
}
int fn_801AFD04(Key_801AE658 *key, int *event, Result_801AFD04 *out)
{
    int mode = key->mUnknown3;
    int index = key->mUnknown2;
    int id = key->mId;
    int value = -1;
    out->mUnknown4 = -1;
    out->mUnknown6 = -1;
    out->mUnknown0 = -1;
    switch (mode) {
    case 0:
        out->mUnknown4 = fn_801B2648(id, &value);
        out->mUnknown0 = (short)value;
        break;
    case 1:
        out->mUnknown4 = fn_801B26D8(id, ((unsigned short *)event)[index * 2 + 1], &value);
        out->mUnknown0 = value;
        break;
    case 2:
        {
            int slot = fn_801B2648(id, &value);
            if (fn_801B2798(slot, event[index])) out->mUnknown6 = ((unsigned short *)event)[index * 2 + 1];
            else value = -1;
            out->mUnknown4 = slot;
            out->mUnknown0 = value;
        }
        break;
    }
    return out->mUnknown0 >= 0;
}

void fn_801AFDFC(Record_801AF75C *p, int i)
{
    int index = i / 8 + 1;
    unsigned char mask = ~(1 << (i % 8));
    unsigned char *bits = (unsigned char *)fn_801AF780(p);
    bits[index] &= mask;
}

int fn_801AFE58(unsigned char *bits, int i)
{
    unsigned char mask = 1 << (i % 8);
    return bits[i / 8] & mask;
}

int fn_801AFE90(Result_801AFD04 *result, Record_801AF75C *p, int i)
{
    int index = result->mUnknown6;
    int found = 0;
    if (((unsigned short *)p)[5] > index) {
        i += p->mUnknown5 * index;
        found = fn_801AFE58((unsigned char *)fn_801AF80C(p), i);
    }
    return found;
}

int fn_801AFEE8(Result_801AFD04 *result, Record_801AF75C *p, int i)
{
    int found = 1;
    if (i > p->mUnknown5) {
        found = 0;
    } else {
        if (result->mUnknown6 != -1) {
            found = fn_801AFE90(result, p, i);
        }
        if (found && (p->mUnknown4 & 128)) {
            found = fn_801AFE58((unsigned char *)fn_801AF780(p) + 1, i);
        }
    }
    return found;
}

int fn_801AFF74(Buffer_801AFF74 *p, int value)
{
    int result = 0;
    if (p->mCount < 200) {
        result = 1;
        p->mValues[p->mCount] = value;
        p->mCount++;
    }
    return result;
}

int fn_801AFFA4(Record_801AF75C *a, Record_801AF75C *b, int *values)
{
    int *words = (int *)fn_801AF75C(b);
    int count = b->mUnknown4 & 127;
    int result = 1;
    for (int i = 0; i < count; i++) {
        int id = fn_801AF84C(a, i)->mUnknown4;
        if (id != 0 && id != 255 && id != 254) {
            if (!(words[i] & values[id])) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

int fn_801B01E8(int value)
{
    int result = 0;
    if (lbl_803ECEA4) {
        result = value * 100 / lbl_803ECEA4;
    }
    return result;
}

int fn_801B0208(unsigned char *p, Work_801B10AC *work)
{
    int total = 0;
    int count = fn_801AF85C(p);
    for (int i = 0; i < count; i++) {
        int index = work->mEntries[i].mUnknown4;
        Record_801AF75C *record = (Record_801AF75C *)lbl_803EBB00[index].mUnknown4;
        int a, b;
        if (fn_801B22E0(record, work->mValues[work->mEntries[i].mUnknownA], &a, &b)) {
            total += b;
        }
    }
    return fn_801B01E8(total);
}
int fn_801B029C(unsigned int value)
{
    return (value & 31) * lbl_802F475C[(value >> 5) & 7];
}

int fn_801B02B8(unsigned char *p)
{
    return fn_801B029C(*p);
}

int fn_801B040C(Item_801AE3F4 *p, int channel)
{
    int result = 1;
    if (p->mId == lbl_8037E234[channel].mKey.mId) {
        int limit = fn_801AF8EC(p);
        if (limit > 0) result = lbl_8037E234[channel].mUnknown4 < limit;
    }
    return result;
}
int fn_801B0474(unsigned char *p, int mode)
{
    int result = 0;
    int value = fn_801AF868(p);
    if ((value == 1 && mode == 2) || (value == 2 && mode != 2) || value == 0) {
        result = 1;
    }
    return result;
}

void fn_801B04D4(unsigned char *p)
{
    int *words = (int *)fn_801AF8B0(p);
    for (int i = 0; i < p[3]; i++) {
        words[i] = 0;
    }
}

int fn_801B052C(unsigned char *p, Record_801AF75C *record)
{
    int count = (signed char)record->mUnknown4;
    int result = 1;
    for (int i = 0; i < count; i++) {
        if (fn_801AF84C(record, i)->mUnknown4 == 255) {
            int flags = fn_801AF84C(record, i)->mUnknown6;
            if (flags != 255 && (flags & 128)) {
                flags &= 127;
                int *words = (int *)fn_801AF8B0(p);
                if (words && !words[flags]) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}
void fn_801B08DC(unsigned char *p, Work_801B10AC *work)
{
    int count = fn_801AF85C(p);
    for (int i = 0; i < count; i++) {
        int n = work->mEntries[i].mUnknown9;
        unsigned char *values = work->mValues + work->mEntries[i].mUnknown8;
        while (n > 1) {
            int j = fn_801B1C1C(n, -1);
            unsigned char value = values[j];
            values[j] = values[n - 1];
            values[n - 1] = value;
            n--;
        }
    }
}

int fn_801B0974(unsigned char *p, Work_801B10AC *work)
{
    int result = 0;
    int index = fn_801AF85C(p) - 1;
    int done = 0;
    WorkEntry_801B0B18 *entry = &work->mEntries[index];
    int end = entry->mUnknown8 + entry->mUnknown9;
    do {
        entry->mUnknownA++;
        if (entry->mUnknownA < end) {
            done = 1;
        } else {
            entry->mUnknownA = entry->mUnknown8;
            if (--index < 0) {
                done = 1;
                result = 1;
            }
            entry = &work->mEntries[index];
            end = entry->mUnknown8 + entry->mUnknown9;
        }
    } while (!done);
    return result;
}


int fn_801B0A18(unsigned char *p, Work_801B10AC *work, int limit)
{
    int count = fn_801AF85C(p);
    int found = 0;
    int done = 0;
    for (int i = 0; i < count; i++) work->mEntries[i].mUnknownA = work->mEntries[i].mUnknown8;
    while (!done && !found) {
        found = 1;
        if (limit) found = fn_801B0208(p, work) <= limit;
        if (found) {
            if (p[3] && !fn_801B05E4(work, p)) found = 0;
        }
        if (!found) done = fn_801B0974(p, work);
    }
    return found;
}

int fn_801B0B18(WorkEntry_801B0B18 *p)
{
    int value = fn_801B1C1C(p->mUnknown9, p->mUnknown4);
    p->mUnknownA = p->mUnknown8 + value;
    return 1;
}


void fn_801B0B5C(Key_801AE658 *key, Work_801B10AC *work, unsigned char *p)
{
    char *text;
    if (fn_801AE7B4(key, &text)) {
        int count = fn_801AF85C(p);
        for (int i = 0; i < count; i++) {
            Record_801AF75C *record = (Record_801AF75C *)fn_801AF928((char *)p, p + 8, i);
            for (int j = 0; j < (signed char)record->mUnknown4; j++) {
                if (fn_801AF84C(record, j)->mUnknown4 == 254) {
                    if (!(fn_801AF84C(record, j)->mUnknown6 & 128)) {
                        int slot = work->mEntries[i].mUnknown4;
                        Record_801AF75C *bank = (Record_801AF75C *)lbl_803EBB00[slot].mUnknown4;
                        char *values = fn_801B22B0(bank, work->mValues[work->mEntries[i].mUnknownA]);
                        if (values) {
                            int index = fn_801AF84C(record, j)->mUnknown6;
                            text[index] = values[j];
                        }
                    }
                }
            }
        }
    }
}


int fn_801B0C7C(Key_801AE658 *key, Work_801B10AC *work, unsigned char *p, int a, int limit)
{
    int result;
    if (limit > 0 || p[3]) {
        fn_801B08DC(p, work);
        result = fn_801B0A18(p, work, limit);
    } else {
        int count = fn_801AF85C(p);
        result = 1;
        for (int i = 0; i < count; i++) {
            WorkEntry_801B0B18 *entry = &work->mEntries[i];
            if (!entry->mUnknown9) return 0;
            fn_801AF928((char *)p, p + 8, i);
            if (!fn_801B0B18(entry)) return 0;
        }
    }
    fn_801B0B5C(key, work, p);
    return result;
}

void fn_801B10AC(Work_801B10AC *p)
{
    p->mUnknown90 = 0;
    p->mCount = 0;
    for (int i = 0; i <= 11; i++) p->mEntries[i].mUnknownB = 0;
}

void fn_801B10D8(int channel)
{
    Channel_801B118C *p = &lbl_8037E294[channel];
    if (p->mUnknownC) {
        fn_801AF500(p->mUnknownC);
        p->mUnknownC = 0;
    }
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    p->mUnknownB = 0;
    p->mUnknown8 = 0;
    p->mUnknown9 = 0;
    p->mUnknownA = 0;
    p->mUnknownC = 0;
    for (int i = 0; i <= 11; i++) {
        p->mEntries[i].mUnknown0 = -1;
        p->mEntries[i].mUnknown8 = 0;
        p->mEntries[i].mUnknown4 = -1;
        p->mEntries[i].mUnknown6 = -1;
    }
}

void fn_801B118C(void)
{
    for (int channel = 0; channel <= 7; channel++) {
        Channel_801B118C *p = &lbl_8037E294[channel];
        p->mUnknown0 = 0;
        p->mUnknown4 = 0;
        p->mUnknownB = 0;
        p->mUnknown8 = 0;
        p->mUnknown9 = 0;
        p->mUnknownA = 0;
        p->mUnknownC = 0;
        for (int i = 0; i <= 11; i++) {
            p->mEntries[i].mUnknown0 = -1;
            p->mEntries[i].mUnknown8 = 0;
            p->mEntries[i].mUnknown4 = -1;
            p->mEntries[i].mUnknown6 = -1;
        }
    }
}
int fn_801B1368(unsigned int channel)
{
    return lbl_8037E294[channel].mUnknown9;
}

int fn_801B1474(unsigned int bits, int value, int index)
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

int fn_801B14B4(Item_801AE3F4 *p, int *values)
{
    unsigned int bits = fn_801AFA70(p);
    int result = 0;
    unsigned short mask = 1;
    for (int i = 0; i <= 15; i++) {
        if (fn_801B1474(bits, values[i + 1], i)) {
            result |= mask;
        }
        mask <<= 1;
    }
    return result;
}

int fn_801B15E4(unsigned char *p)
{
    return fn_801B1C1C(100, -1) < p[1];
}
void fn_801B192C(int value)
{
    lbl_803ECEA8 = value;
}

unsigned int fn_801B1934(void)
{
    unsigned int old = lbl_802F477C[4];
    unsigned int sum = old + lbl_802F477C[5];
    unsigned int carry = sum < old || sum < lbl_802F477C[5];
    lbl_802F477C[4] = sum;
    old = lbl_802F477C[3];
    sum += old + carry;
    lbl_802F477C[3] = sum;
    carry = sum < old;
    old = lbl_802F477C[2];
    sum += old + carry;
    lbl_802F477C[2] = sum;
    carry = sum < old;
    old = lbl_802F477C[1];
    sum += old + carry;
    lbl_802F477C[1] = sum;
    carry = sum < old;
    sum += lbl_802F477C[0] + carry;
    lbl_802F477C[0] = sum;
    for (int i = 5; i >= 0; i--) {
        if (++lbl_802F477C[i]) break;
    }
    return lbl_802F477C[0];
}
unsigned int fn_801B1A3C(unsigned int seed)
{
    seed += 0xF22D0E56U;
    unsigned int first = seed;
    lbl_802F477C[0] = seed;
    seed += 0x96041893U;
    lbl_802F477C[1] = seed;
    seed += 0x3DF3B646U;
    lbl_802F477C[2] = seed;
    seed += 0x40DDE76DU;
    lbl_802F477C[3] = seed;
    seed += 0x97327AE1U;
    lbl_802F477C[4] = seed;
    seed += 0xD1A9FBE7U;
    lbl_802F477C[5] = seed;
    return first;
}

int fn_801B1A90(int value, int count, int id)
{
    int result = -1;
    if (count > 32) count = 32;
    int index = lbl_803EBB20;
    int matched = 0;
    int scanned = 0;
    int done = 0;
    do {
        if (matched < count) {
            if (lbl_8037E794[index][1] == id) {
                matched++;
                if (lbl_8037E794[index][0] == value) {
                    done = 1;
                    result = matched - 1;
                }
            }
        } else {
            done = 1;
        }
        if (--index < 0) index += 32;
        if (++scanned > 32) done = 1;
    } while (!done);
    return result;
}

void fn_801B1B34(int value, int id)
{
    if (++lbl_803EBB20 > 31) lbl_803EBB20 = 0;
    lbl_8037E794[lbl_803EBB20][0] = value;
    lbl_8037E794[lbl_803EBB20][1] = id;
}

void fn_801B1B70(int seed)
{
    for (int i = 0; i <= 31; i++) {
        lbl_8037E794[i][1] = 65535;
        lbl_8037E794[i][0] = 65535;
    }
    seed += seed << 16;
    lbl_803EBB20 = 0;
    fn_801B1A3C(seed);
    int count = 32 - seed % 32;
    for (int i = 0; i < count; i++) {
        fn_801B1C1C(10, -1);
    }
}

int fn_801B1C1C(int count, int id)
{
    int tries = 0;
    int done = 0;
    int best = -1;
    int limit = count / 2;
    if (limit > 10) limit = 10;
    int value = ((fn_801B1934() >> 16) * count) >> 16;
    int selected = value;
    if (id != -1) {
        id = (unsigned short)id;
        do {
            int age = fn_801B1A90(value, limit, id);
            if (age == -1) {
                selected = value;
                done = 1;
            } else if (age > best) {
                best = age;
                selected = value;
            }
            if (++tries > 31) done = 1;
            if (!done) value = ((fn_801B1934() >> 16) * count) >> 16;
        } while (!done);
        fn_801B1B34(selected, id);
    }
    return value;
}
Entry_801AF84C *fn_801B1CFC(Record_801AF75C *p, int i)
{
    return p->mEntries + i;
}

int fn_801B1D0C(unsigned char *p)
{
    return p[2] >> 2;
}

int fn_801B1D18(Item_801AE3F4 *p)
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

char *fn_801B1D44(Item_801AE3F4 *p)
{
    return (char *)p + (((p->mUnknown6 * 2 + 3) & ~3) + 12);
}

char *fn_801B1D60(Item_801AE3F4 *p)
{
    char *result = fn_801B1D44(p);
    return result + ((fn_801B1D18(p) * 3 + 3) & ~3);
}

int fn_801B1DAC(unsigned char *p, int value)
{
    int result = 0;
    int count = fn_801B1D0C(p);
    for (int i = 0; i < count; i++) {
        unsigned char *record = (unsigned char *)fn_801B1D20((char *)p, p + 8, i);
        if (record[2] == value) {
            result = 1;
            break;
        }
        int n = (signed char)record[4];
        for (int j = 0; j < n; j++) {
            if (fn_801B1CFC((Record_801AF75C *)record, j)->mUnknown4 == value) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

unsigned char *fn_801B2190(Item_801AE3F4 *item, int index, unsigned int *a, unsigned int *b)
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

int fn_801B2250(Item_801AE3F4 *item, int index, unsigned int value, unsigned int excluded)
{
    unsigned int a, b;
    fn_801B2190(item, index, &a, &b);
    b &= ~excluded;
    a &= b;
    value &= b;
    return value == a;
}

char *fn_801B22B0(Record_801AF75C *p, int i)
{
    char *result = 0;
    if (i < p->mUnknown5) {
        result = (char *)p + i * ((p->mUnknown4 & 127) + 2) + 14;
    }
    return result;
}

int fn_801B22E0(Record_801AF75C *p, int i, int *a, int *b)
{
    int result = 0;
    int count = p->mUnknown5;
    if (i < count) {
        int stride = (p->mUnknown4 & 127) + 2;
        unsigned char *record = (unsigned char *)p + 12 + i * stride;
        int scale = (p->mUnknown7 + 1) << 8;
        int start = ((record[0] << 8) + record[1]) * scale;
        unsigned char *next = record + stride;
        int end;
        if (i + 1 >= count) end = ((unsigned short *)p)[4];
        else end = (next[0] << 8) + next[1];
        *a = start;
        *b = end * scale - start;
        result = 1;
    }
    return result;
}

char *fn_801B23A0(Record_801AF75C *p)
{
    return (char *)p + ((p->mUnknown5 * ((p->mUnknown4 & 127) + 2) + 15) & ~3);
}

char *fn_801B23C4(Record_801AF75C *p)
{
    char *result = fn_801B23A0(p);
    return result + (p->mUnknown4 & 127) * 4;
}

char *fn_801B23FC(Record_801AF75C *p)
{
    int size = 0;
    char *result = fn_801B23C4(p);
    if (p->mUnknown4 & 128) {
        size = (p->mUnknown5 + 7) / 8 + 1;
    }
    return result + size;
}

void fn_801B2450(void)
{
    lbl_803EBB00 = 0;
    lbl_803EBB08 = 0;
    lbl_803EBB0C = 0;
    lbl_803EBB04 = 0;
}

void fn_801B2468(void)
{
    lbl_803EBB00 = 0;
    lbl_803EBB08 = 0;
    lbl_803EBB0C = 0;
    lbl_803EBB04 = 0;
}

int fn_801B2480(int count)
{
    return count * 8;
}

void fn_801B2488(int count, Slot_801B2450 *slots)
{
    lbl_803EBB08 = count;
    lbl_803EBB00 = slots;
    if (slots) {
        for (int i = 0; i < count; i++) {
            slots[i].mUnknown0 = 0;
            slots[i].mUnknown4 = 0;
        }
    }
}

int fn_801B2648(unsigned int id, int *out)
{
    int low = 0;
    int high = lbl_803EBB0C - 1;
    if (lbl_803EBB00 && lbl_803EBB0C) {
        while (low <= high) {
            int mid = (low + high) / 2;
            unsigned short *p = (unsigned short *)lbl_803EBB00[mid].mUnknown4;
            if (id == p[0]) {
                *out = lbl_803EBB00[mid].mUnknown0;
                return (short)mid;
            }
            if (id > p[0]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

int fn_801B26D8(unsigned int id, unsigned int key, int *out)
{
    int low = 0;
    int high = lbl_803EBB0C - 1;
    if (lbl_803EBB00 && lbl_803EBB0C) {
        while (low <= high) {
            int mid = (low + high) / 2;
            unsigned short *p = (unsigned short *)lbl_803EBB00[mid].mUnknown4;
            if (id == p[0] && key == p[1]) {
                *out = lbl_803EBB00[mid].mUnknown0;
                return (short)mid;
            }
            if (id > p[0] || (id == p[0] && key > p[1])) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}
int fn_801B2798(int i, unsigned int value)
{
    int result = 0;
    if (lbl_803EBB00 && i >= 0) {
        int limit = ((unsigned short *)lbl_803EBB00[i].mUnknown4)[5];
        if (limit != 65535) {
            result = value < (unsigned int)limit;
        }
    }
    return result;
}

int fn_801B27E4(int id)
{
    for (int i = 0; i < lbl_803EBB0C; i++) {
        if (lbl_803EBB00[i].mUnknown0 == id) {
            return i;
        }
    }
    return -1;
}

void fn_801B2828(Record_801AF75C *p, int value)
{
    if (p->mUnknown6) {
        unsigned char *history = (unsigned char *)fn_801B23FC(p);
        unsigned int index = history[0];
        if (index < p->mUnknown6) {
            history[index + 1] = value;
        }
        index = (unsigned char)(index + 1);
        if (index >= p->mUnknown6) {
            index = 0;
        }
        history[0] = index;
    }
}

int fn_801B2898(Record_801AF75C *p, int value)
{
    int count = p->mUnknown6;
    int result = 0;
    if (count > 0) {
        unsigned char *history = (unsigned char *)fn_801B23FC(p);
        int index = *history++;
        for (int i = 0; i < count; i++) {
            if (--index < 0) {
                index = count - 1;
            }
            if (history[index] == value) {
                result = i + 1;
                break;
            }
        }
    }
    return result;
}

unsigned int fn_801B2918(unsigned int a, int b, int c)
{
    int quotient = b / c;
    int remainder = b % c;
    if (a > (unsigned int)remainder) {
        return quotient * a + remainder;
    }
    return quotient * a + a;
}


void fn_801B2944(Record_801AF75C *p)
{
    unsigned char *bits = (unsigned char *)fn_801B23C4(p);
    int count = bits[0];
    if (count > 0) {
        unsigned int time = (unsigned int)lbl_803ECEA0 % count;
        int size = p->mUnknown5;
        unsigned int start = fn_801B2918(time, size, count);
        int length = fn_801B2918(time + 1, size, count) - start;
        int index = start / 8 + 1;
        int bit = start & 7;
        for (int i = 0; i < length; i++) {
            bits[index] |= 1 << bit;
            if (bit == 7) {
                bit = 0;
                index++;
            } else {
                bit++;
            }
        }
    }
}


}
