#include "engine/cu_801BA818.h"
#include "game/fn_801D2B7C.h"

typedef struct Entry_801BF5E8 {
    unsigned short mId;
    unsigned char mDirty;
    unsigned short mCountA;
    Pair_801BF7BC *mPairsA;
    unsigned short mCountB;
    Pair_801BF7BC *mPairsB;
} Entry_801BF5E8;

extern unsigned int lbl_803ED618;
extern int lbl_803ED61C;
extern Entry_801BF5E8 *lbl_803ED620;
extern unsigned char lbl_803EBBA8;

void fn_801BF748(unsigned int index);

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
