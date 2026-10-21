#include "game/AnimFileFormat.h"
#include "game/fn_801D2B7C.h"

typedef struct Block_801BF3C8 {
    float mUnknown0;
    float mUnknown4;
    int mType;
    unsigned char mData[1];
} Block_801BF3C8;

typedef struct Data1_801BF4A8 {
    float mUnknown0;
    int mUnknown4;
} Data1_801BF4A8;

typedef struct Data3_801BF530 {
    float mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    short mUnknownA;
} Data3_801BF530;

typedef struct Pair_801BF7BC {
    short mUnknown0;
    short mUnknown2;
} Pair_801BF7BC;

typedef struct Entry_801BF5E8 {
    unsigned short mId;
    unsigned char mDirty;
    unsigned short mCountA;
    Pair_801BF7BC *mPairsA;
    unsigned short mCountB;
    Pair_801BF7BC *mPairsB;
} Entry_801BF5E8;

typedef struct Node_801BF94C {
    struct Node_801BF94C *mPrev;
    struct Node_801BF94C *mNext;
    char *mSource;
    unsigned short mMotion;
    unsigned char mHandle;
    unsigned char mUsed;
    int mGroup;
} Node_801BF94C;

typedef struct List_801BF94C {
    unsigned short mCount;
    Node_801BF94C *mHead;
    Node_801BF94C *mTail;
    Node_801BF94C *mNodes;
} List_801BF94C;

typedef struct Cache_801BFCC4 {
    unsigned short mCount;
    unsigned short mSize;
    Node_801BF94C *mNodes;
    unsigned char *mData;
    List_801BF94C mList;
} Cache_801BFCC4;

typedef struct Curve_801C02EC {
    unsigned char mUnknown0[4];
    float mUnknown4;
    float mUnknown8;
    void *mpKeys;
} Curve_801C02EC;

typedef struct Sample_801C009C {
    float mUnknown0[3];
    Curve_801C02EC mCurves[15];
} Sample_801C009C;

typedef struct Group_801C001C {
    unsigned short mId;
    unsigned short mCount;
    Sample_801C009C *mSamples;
} Group_801C001C;

typedef struct Group_801BFFD8 {
    unsigned short mId;
    unsigned short mCount;
    Group_801C001C *mChildren;
} Group_801BFFD8;

typedef struct Key_801C065C {
    float mTime;
    unsigned char mUnknown4;
    unsigned char mValue;
    unsigned char mUnknown6[2];
} Key_801C065C;

typedef struct Frame_801C029C {
    unsigned char mUnknown0[14];
    unsigned short mUnknownE;
    unsigned char mUnknown10[16];
    float mUnknown20;
    unsigned char mUnknown24[4];
    unsigned short mKeyCount;
    unsigned short mUnknown2A;
    Key_801C065C *mKeys;
} Frame_801C029C;

typedef struct Item_801C02DC {
    unsigned char mUnknown0[16];
    void *mUnknown10;
} Item_801C02DC;

typedef struct Bank_801C009C {
    unsigned char mUnknown0[4];
    unsigned short mFrameCount;
    unsigned short mFrameCount2;
    unsigned char mUnknown8[4];
    unsigned char mItemCount;
    unsigned char mGroupCount;
    unsigned char mUnknownE[2];
    Group_801BFFD8 *mGroups;
    void *mUnknown14;
    Frame_801C029C *mFirstFrame;
    Frame_801C029C *mFrames;
    Frame_801C029C *mFrames2;
    Item_801C02DC *mItems;
} Bank_801C009C;

typedef struct File_801C02EC {
    unsigned char mUnknown0[4];
    unsigned int mCount;
    Bank_801C009C *mBanks[1];
} File_801C02EC;

typedef struct Table_801C06A0 {
    union {
        unsigned int mWord;
        struct {
            unsigned short mVersion;
            unsigned short mCount;
        } mParts;
    } mHeader;
    char *mEntries[1];
} Table_801C06A0;

typedef void (*Callback_801BFCB0)(AnimFileFormat_t *file, int a, unsigned char *destination,
                                  unsigned int source, unsigned int size, int group);

extern unsigned char *lbl_803EBBA0;
extern void (**lbl_803EBB9C)(Block_801BF3C8 *p);
extern unsigned int lbl_803ED618;
extern int lbl_803ED61C;
extern Entry_801BF5E8 *lbl_803ED620;
extern unsigned char lbl_803EBBA8;
extern Callback_801BFCB0 lbl_803ECEC0;
extern unsigned char lbl_803EBBAC;
extern float lbl_803EBBB0;
extern unsigned short lbl_803EBBB4;
extern unsigned short lbl_803EBBB6;
extern unsigned short lbl_803EBBB8;
extern Bank_801C009C *lbl_803EBBBC;

extern void *fn_801D2BB0(int heap, int size, int a, int b);
extern void fn_801BBB54(unsigned int index);
extern AnimFileFormat_t *fn_801BC084(int handle);
extern Cache_801BFCC4 *fn_801BC0C0(int handle);
extern void fn_801F7BD4(int err);
extern unsigned int fn_801BBE5C(unsigned short a, unsigned short b);
extern void *fn_801BAB34(void *p, int key);
extern float fn_801BD60C(void *p);
extern int fn_801B9EF8(void);

#define RELOCATE(p, base) ((p) = (void *)((char *)(base) + (int)(p)))

void fn_801BF748(unsigned int index);
void fn_801BF7BC(unsigned int index);
Frame_801C029C *fn_801C029C(Bank_801C009C *bank, unsigned short index);

void fn_801BF3C8(Block_801BF3C8 *p, int type, float a, void *source, float b)
{
    if (a != -1.0f)
        p->mUnknown0 = a;
    if (b != -1.0f)
        p->mUnknown4 = b;
    p->mType = type;
    if (source != 0 && lbl_803EBBA0[type] != 0)
        memcpy(p->mData, source, lbl_803EBBA0[type]);
}

void fn_801BF434(int type, void *data)
{
    if (lbl_803EBBA0[type] != 0)
        memset(data, 0, lbl_803EBBA0[type]);
}

void fn_801BF46C(Block_801BF3C8 *p)
{
    if (lbl_803EBB9C != 0)
        lbl_803EBB9C[p->mType](p);
}

void fn_801BF4A8(Block_801BF3C8 *p, int value, float a, float b)
{
    Data1_801BF4A8 data;

    fn_801BF434(1, &data);
    if (a == -1.0f)
        a = p->mUnknown0;
    data.mUnknown4 = value;
    data.mUnknown0 = a;
    fn_801BF3C8(p, 1, a, &data, b);
}

void fn_801BF530(Block_801BF3C8 *p, unsigned char value, short c, float a, float b)
{
    Data3_801BF530 data;

    fn_801BF434(3, &data);
    if (a == -1.0f)
        a = p->mUnknown0;
    data.mUnknown0 = a;
    data.mUnknown4 = value;
    data.mUnknown9 = 0;
    data.mUnknown8 = value;
    data.mUnknownA = c;
    fn_801BF3C8(p, 3, a, &data, b);
}

void fn_801BF5E8(int heap, unsigned int count)
{
    lbl_803ED61C = heap;
    lbl_803ED618 = count;
    lbl_803ED620 = fn_801D2BB0(heap, count * sizeof(Entry_801BF5E8), 0, 0);
    memset(lbl_803ED620, 0, count * sizeof(Entry_801BF5E8));
    lbl_803EBBA8 = 1;
}

void fn_801BF648(void)
{
    unsigned int i;

    for (i = 0; i < lbl_803ED618; i++)
        fn_801BF748(i);
    fn_801D2BD0(lbl_803ED620);
    lbl_803ED620 = 0;
    lbl_803ED618 = 0;
    lbl_803EBBA8 = 0;
}

static inline Entry_801BF5E8 *GetEntry(unsigned int index)
{
    return index < lbl_803ED618 ? &lbl_803ED620[index] : 0;
}

void fn_801BF6AC(unsigned int index, unsigned int countA, unsigned int countB)
{
    Entry_801BF5E8 *entry;

    fn_801BF748(index);
    entry = GetEntry(index);
    if (entry != 0) {
        entry->mCountA = countA;
        entry->mCountB = countB;
        entry->mId = index;
        entry->mPairsA = fn_801D2BB0(lbl_803ED61C, (countA + countB) * sizeof(Pair_801BF7BC), 0, 0);
        entry->mPairsB = entry->mPairsA + countA;
        fn_801BF7BC(index);
    }
}

void fn_801BF748(unsigned int index)
{
    Entry_801BF5E8 *entry = GetEntry(index);

    if (entry != 0) {
        if (entry->mPairsA != 0) {
            fn_801D2BD0(entry->mPairsA);
            entry->mPairsA = 0;
        }
        entry->mPairsB = 0;
        entry->mCountA = 0;
        entry->mId = 0;
    }
}

void fn_801BF7BC(unsigned int index)
{
    Entry_801BF5E8 *entry = GetEntry(index);
    unsigned int i;

    if (entry == 0)
        return;
    for (i = 0; i < entry->mCountA; i++) {
        entry->mPairsA[i].mUnknown0 = -1;
        entry->mPairsA[i].mUnknown2 = -1;
    }
    for (i = 0; i < entry->mCountB; i++) {
        entry->mPairsB[i].mUnknown0 = -1;
        entry->mPairsB[i].mUnknown2 = -1;
    }
    entry->mDirty = 1;
}

Pair_801BF7BC *fn_801BF870(unsigned int index, unsigned int key)
{
    Entry_801BF5E8 *entry = GetEntry(index);

    if (entry != 0) {
        if (key > 0x1FFF) {
            key &= 0x1FFF;
            if (key < entry->mCountB)
                return &entry->mPairsB[key];
        } else if (key < entry->mCountA) {
            return &entry->mPairsA[key];
        }
    }
    return 0;
}

void fn_801BF8DC(void)
{
    unsigned int i;

    for (i = 0; i < lbl_803ED618; i++) {
        Entry_801BF5E8 *entry = &lbl_803ED620[i];
        if (entry->mDirty) {
            fn_801BBB54(i);
            entry->mDirty = 0;
        }
    }
}

void fn_801BF94C(List_801BF94C *list, Node_801BF94C *node)
{
    if (node == list->mHead) {
        list->mHead = node->mNext;
        list->mHead->mPrev = 0;
    } else if (node == list->mTail) {
        list->mTail = node->mPrev;
        list->mTail->mNext = 0;
    } else {
        Node_801BF94C *prev = node->mPrev;
        Node_801BF94C *next = node->mNext;
        prev->mNext = next;
        next->mPrev = prev;
    }
}

void fn_801BF9A0(List_801BF94C *list, Node_801BF94C *nodes, int count)
{
    Node_801BF94C *prev = 0;
    unsigned int i;

    list->mCount = count;
    list->mNodes = nodes;
    list->mHead = nodes;
    for (i = 0; i < count; i++) {
        Node_801BF94C *node = &list->mNodes[i];
        memset(node, 0, sizeof(Node_801BF94C));
        node->mPrev = prev;
        node->mNext = &list->mNodes[i + 1];
        prev = node;
    }
    list->mTail = &list->mNodes[count - 1];
    list->mTail->mNext = 0;
}

unsigned char *fn_801BFA50(Cache_801BFCC4 *cache, unsigned int key, int group, int check,
                           unsigned char *pFound)
{
    unsigned int index;
    Node_801BF94C *node;
    List_801BF94C *list;

    *pFound = 1;
    index = key & 0x0FFFFFFF;
    node = &cache->mNodes[index];
    if (check == 1 && node->mGroup != group) {
        *pFound = 0;
        return 0;
    }
    list = &cache->mList;
    fn_801BF94C(list, node);
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return cache->mData + index * cache->mSize;
}

Node_801BF94C *fn_801BFAEC(Cache_801BFCC4 *cache)
{
    List_801BF94C *list = &cache->mList;
    Node_801BF94C *node = list->mHead;

    list->mHead = node->mNext;
    list->mHead->mPrev = 0;
    node->mPrev = list->mTail;
    node->mPrev->mNext = node;
    list->mTail = node;
    node->mNext = 0;
    return node;
}

static inline void SetMotion(AnimFileFormat_t *file, unsigned short motion, int group, char *value)
{
    if (file->flags & 4)
        file->groupMotion[group].motion[motion] = value;
    else
        file->motion[motion] = value;
}

unsigned char *fn_801BFB20(AnimFileFormat_t *file, Cache_801BFCC4 *cache, int handle,
                           unsigned short motion, char *source, int group)
{
    Node_801BF94C *node = fn_801BFAEC(cache);
    int index;
    unsigned char *data;

    if (node->mUsed == 1)
        SetMotion(fn_801BC084(node->mHandle), node->mMotion, (unsigned short)node->mGroup,
                  node->mSource);
    node->mSource = source;
    node->mHandle = handle;
    node->mUsed = 1;
    node->mMotion = motion;
    node->mGroup = group;
    index = node - cache->mNodes;
    data = cache->mData + index * cache->mSize;
    SetMotion(file, motion, group, (char *)(index | 0xF0000000));
    return data;
}

unsigned char *fn_801BFC34(AnimFileFormat_t *file, int a, Cache_801BFCC4 *cache,
                           int handle, unsigned short motion, char *source, int group)
{
    unsigned char *data = fn_801BFB20(file, cache, handle, motion, source, group);

    lbl_803ECEC0(file, a, data, (unsigned int)source, cache->mSize, group);
    return data;
}

void fn_801BFCB0(Callback_801BFCB0 callback)
{
    lbl_803ECEC0 = callback;
}

void fn_801BFCB8(void)
{
    lbl_803ECEC0 = 0;
}

Cache_801BFCC4 *fn_801BFCC4(int count, int size)
{
    Cache_801BFCC4 *cache = fn_801D2B7C(sizeof(Cache_801BFCC4), 0, 0);

    cache->mNodes = fn_801D2B7C(count * sizeof(Node_801BF94C), 0, 0);
    cache->mData = fn_801D2B7C(count * size, 0, 0);
    cache->mSize = size;
    cache->mCount = count;
    fn_801BF9A0(&cache->mList, cache->mNodes, count);
    return cache;
}

void fn_801BFE4C(Cache_801BFCC4 *cache);

void fn_801BFD48(Cache_801BFCC4 *cache)
{
    fn_801BFE4C(cache);
    fn_801D2BD0(cache->mNodes);
    fn_801D2BD0(cache->mData);
    fn_801D2BD0(cache);
}

unsigned char *fn_801BFD8C(AnimFileFormat_t *file, int a, int handle, unsigned short motion,
                           char *source, int group)
{
    Cache_801BFCC4 *cache = fn_801BC0C0(handle);
    unsigned char *data;
    unsigned char found;

    if (((unsigned int)source & 0xF0000000) == 0xF0000000) {
        data = fn_801BFA50(cache, (unsigned int)source, group, (file->flags & 4) != 0, &found);
        if (!found)
            data = fn_801BFC34(file, a, cache, handle, motion, source, group);
    } else {
        data = fn_801BFC34(file, a, cache, handle, motion, source, group);
    }
    return data;
}

void fn_801BFE4C(Cache_801BFCC4 *cache)
{
    unsigned int i;

    for (i = 0; i < cache->mList.mCount; i++) {
        Node_801BF94C *node = &cache->mList.mNodes[i];
        if (node->mUsed == 1)
            SetMotion(fn_801BC084(node->mHandle), node->mMotion, (unsigned short)node->mGroup,
                      node->mSource);
    }
}

int fn_801BFEF8(float rate)
{
    int err = 0;

    if (lbl_803EBBAC)
        err = 0x1D0001;
    else {
        lbl_803EBBB0 = rate;
        lbl_803EBBAC = 1;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_801BFF50(void)
{
    int err = 0;

    if (lbl_803EBBAC)
        lbl_803EBBAC = 0;
    else
        err = 0x1D0002;
    fn_801F7BD4(err);
    return err;
}

float fn_801BFFA0(void)
{
    return lbl_803EBBB0;
}

void fn_801BFFA8(void)
{
    lbl_803EBBB4 = -1;
    lbl_803EBBB6 = -1;
    lbl_803EBBB8 = -1;
    lbl_803EBBBC = 0;
}

void fn_801BFFC4(Bank_801C009C *bank, unsigned short group, unsigned short sample, unsigned short index)
{
    lbl_803EBBB4 = group;
    lbl_803EBBB6 = sample;
    lbl_803EBBB8 = index;
    lbl_803EBBBC = bank;
}

Group_801BFFD8 *fn_801BFFD8(Bank_801C009C *bank, unsigned short id)
{
    unsigned short i;

    for (i = 0; i < bank->mGroupCount; i++) {
        Group_801BFFD8 *group = &bank->mGroups[i];
        if (group->mId == id)
            return group;
    }
    return 0;
}

Group_801C001C *fn_801C001C(Bank_801C009C *bank, unsigned short id, unsigned short subId)
{
    Group_801BFFD8 *group = fn_801BFFD8(bank, id);
    unsigned short i;

    if (group == 0)
        return 0;
    for (i = 0; i < group->mCount; i++) {
        Group_801C001C *child = &group->mChildren[i];
        if (child->mId == subId)
            return child;
    }
    return 0;
}

Sample_801C009C *fn_801C009C(Bank_801C009C *bank, unsigned short id, unsigned short subId,
                             unsigned short index)
{
    Group_801C001C *group = fn_801C001C(bank, id, subId);

    if (group != 0 && index < group->mCount && group->mSamples != 0)
        return &group->mSamples[index];
    return 0;
}

Sample_801C009C *fn_801C00F8(Bank_801C009C *bank)
{
    unsigned short i;
    unsigned short j;

    fn_801BFFA8();
    if (bank->mGroupCount == 0)
        return 0;
    for (i = 0; i < bank->mGroupCount; i++) {
        Group_801BFFD8 *group = &bank->mGroups[i];
        for (j = 0; j < group->mCount; j++) {
            Group_801C001C *child = &group->mChildren[j];
            if (child->mCount != 0) {
                fn_801BFFC4(bank, i, j, j);
                return child->mSamples;
            }
        }
    }
    return 0;
}

int fn_801C01B8(Frame_801C029C *frame)
{
    return frame->mUnknownE & 0x7FFF;
}

int fn_801C01C4(Frame_801C029C *frame)
{
    if (frame->mUnknownE & 0x8000)
        return 1;
    return 0;
}

void *fn_801C01DC(void *base, int offset)
{
    return (char *)base + offset;
}

float fn_801C01E4(Bank_801C009C *bank)
{
    float result = 0.0f;
    unsigned short i;

    for (i = 0; i < bank->mFrameCount; i++) {
        Frame_801C029C *frame = fn_801C029C(bank, i);
        AnimFileFormat_t *file = fn_801BC084(fn_801BBE5C(frame->mUnknown2A | 0x4000, frame->mUnknownE));
        if (file != 0) {
            float length = fn_801BD60C(fn_801BAB34(file, 0)) / fn_801BFFA0();
            if (length <= result)
                result = length;
        }
    }
    return result;
}

Frame_801C029C *fn_801C029C(Bank_801C009C *bank, unsigned short index)
{
    if (index == 0)
        return bank->mFirstFrame;
    return &bank->mFrames[index - 1];
}

Frame_801C029C *fn_801C02C4(Bank_801C009C *bank)
{
    return bank->mFirstFrame;
}

Frame_801C029C *fn_801C02CC(Bank_801C009C *bank, int index)
{
    return &bank->mFrames2[index];
}

Item_801C02DC *fn_801C02DC(Bank_801C009C *bank, int index)
{
    return &bank->mItems[index];
}

void fn_801C02EC(File_801C02EC *file)
{
    unsigned int i;

    for (i = 0; i < file->mCount; i++) {
        Bank_801C009C *bank;
        unsigned short j;
        unsigned int k;

        file->mBanks[i] = bank = fn_801C01DC(file, (int)file->mBanks[i]);
        bank->mUnknown14 = fn_801C01DC(file, (int)bank->mUnknown14);
        bank->mFirstFrame = fn_801C01DC(file, (int)bank->mFirstFrame);
        bank->mFrames = fn_801C01DC(file, (int)bank->mFrames);
        bank->mFrames2 = fn_801C01DC(file, (int)bank->mFrames2);
        bank->mGroups = fn_801C01DC(file, (int)bank->mGroups);
        bank->mItems = fn_801C01DC(file, (int)bank->mItems);
        if (bank->mFrameCount == 0xFFFF) {
            bank->mFrameCount = 0;
            bank->mFirstFrame = 0;
        }
        for (j = 0; j < bank->mGroupCount; j++) {
            Group_801BFFD8 *group = &bank->mGroups[j];
            unsigned short m;

            group->mChildren = fn_801C01DC(file, (int)group->mChildren);
            if (fn_801B9EF8() != 2)
                continue;
            for (m = 0; m < group->mCount; m++) {
                Group_801C001C *child = &group->mChildren[m];
                unsigned short n;

                child->mSamples = fn_801C01DC(file, (int)child->mSamples);
                for (n = 0; n < child->mCount; n++) {
                    Curve_801C02EC *curves = child->mSamples[n].mCurves;
                    RELOCATE(curves[0].mpKeys, file);
                    RELOCATE(curves[1].mpKeys, file);
                    RELOCATE(curves[2].mpKeys, file);
                    RELOCATE(curves[3].mpKeys, file);
                    RELOCATE(curves[4].mpKeys, file);
                    RELOCATE(curves[5].mpKeys, file);
                    RELOCATE(curves[6].mpKeys, file);
                    RELOCATE(curves[7].mpKeys, file);
                    RELOCATE(curves[8].mpKeys, file);
                    RELOCATE(curves[9].mpKeys, file);
                    RELOCATE(curves[10].mpKeys, file);
                    RELOCATE(curves[11].mpKeys, file);
                    RELOCATE(curves[12].mpKeys, file);
                    RELOCATE(curves[13].mpKeys, file);
                    RELOCATE(curves[14].mpKeys, file);
                }
            }
        }
        for (k = 0; k < bank->mFrameCount; k++) {
            bank->mFrames[k].mKeys = fn_801C01DC(file, (int)bank->mFrames[k].mKeys);
            bank->mFrames[k].mUnknown20 = 0.0f;
        }
        if (bank->mFirstFrame != 0) {
            bank->mFirstFrame->mKeys = fn_801C01DC(file, (int)bank->mFirstFrame->mKeys);
            bank->mFrameCount++;
        }
        for (k = 0; k < bank->mFrameCount2; k++)
            bank->mFrames2[k].mKeys = fn_801C01DC(file, (int)bank->mFrames2[k].mKeys);
        for (k = 0; k < bank->mItemCount; k++)
            bank->mItems[k].mUnknown10 = fn_801C01DC(file, (int)bank->mItems[k].mUnknown10);
    }
}

int fn_801C065C(Frame_801C029C *frame, float time)
{
    unsigned int i;
    int value = 0;

    i = 0;
    while (i < frame->mKeyCount) {
        if (time < frame->mKeys[i].mTime)
            break;
        value = frame->mKeys[i].mValue;
        i++;
    }
    return value;
}

void fn_801C06A0(Table_801C06A0 *table)
{
    int i;

    if ((table->mHeader.mWord & 0xFFFF0000) != 0x01000000)
        return;
    for (i = 0; i < table->mHeader.mParts.mCount; i++)
        table->mEntries[i] = (char *)table + (int)table->mEntries[i];
}
