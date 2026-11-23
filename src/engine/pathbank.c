/* Loads and unloads PATH sample banks, reports sub-bank readiness, and chooses eviction
   candidates by the bank's configured order or priority. */

#include <stdio.h>
#include <string.h>
#include "engine/pathlib.h"

extern "C" int PATHI_loadbank(PathTrack_t *p, int index)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    if (!p->mUnknown100) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_createbankimp not called yet\n", p->mUnknownD0);
        return -14;
    }
    if (index >= p->mUnknown100->GetNumSubBanks()) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_loadbank no subbank %d\n", p->mUnknownD0, index);
        return -8;
    }
    if (p->mUnknown100->GetSubBankPtr(index)) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_loadbank already loaded subbank %d\n", p->mUnknownD0, index);
        return -18;
    }
    PathTrackInfo_t *info = PATHI_trackinfo(p->mUnknown0);
    PathSubBankInfo_t *table = (PathSubBankInfo_t *)(info + 1);
    PathSubBankInfo_t *sub = table;
    sub += index;
    unsigned int a = p->mUnknown108 + sub->mSizeA;
    unsigned int b = p->mUnknown10C + sub->mSizeB;
    int unload = 0;
    if (sub && info && info->mUnknown6)
        unload = 1;
    int full = 0;
    if ((info->mUnknown8 && (a > info->mUnknown8 || b > info->mUnknown8)) || !p->mUnknown100->GetAvailSubBankPtr())
        full = 1;
    if (unload && full) {
        if (info->mUnknown6 == 2) {
            unsigned int best = 0x7FFFFFFF;
            int victim = -1;
            for (int i = 0; i < p->mUnknown100->GetMaxSubBanks(); ++i) {
                PathSubBankState_t *entry = p->mUnknown100->GetSubBankPtr(i);
                if (entry && entry->mInfo.mEvictionOrder <= best) {
                    best = entry->mInfo.mEvictionOrder;
                    victim = i;
                }
            }
            if (victim == index)
                return -13;
            PATHI_unloadbank(p, victim);
        } else if (info->mUnknown6 == 1)
            PATHI_unloadmostneglectedsubbank(p);
    }
    int result = PATHI_loadbankdata(p, index, (sub->mSizeA + sub->mSizeB) << 10);
    if (!result) {
        p->mUnknown108 += sub->mSizeA;
        p->mUnknown10C += sub->mSizeB;
        PathSubBankState_t *entry = p->mUnknown100->GetSubBankPtr(index);
        if (entry)
            entry->mInfo = *sub;
    }
    return result;
}

extern "C" int PATHI_subbankready(PathTrack_t *p, int index)
{
    PathSubBankState_t *entry;
    if (index < 0 || index >= p->mUnknown100->GetNumSubBanks() ||
        !(entry = p->mUnknown100->GetSubBankPtr(index)) || !entry->mpData)
        return -8;
    if (p->mUnknownF8) {
        if (!lbl_803EBB60->vfn_08(p->mUnknownF4, entry->mpData))
            return -18;
        p->mUnknownFC = p->mUnknown100->AddSubBank(index, entry->mpData);
        p->mUnknownF8 = 0;
    }
    if (p->mUnknownF0 >= 0) {
        if (!p->mUnknown100->AddSubBankDone(index))
            return -18;
        p->mUnknown100->DetachSubBankHeader(index, p->mUnknownFC);
        p->mUnknownFC = 0;
        p->mUnknownF0 = -1;
    }
    entry->mIndex = index;
    entry->mReady = 1;
    return 0;
}

extern "C" int PATHI_loadbankdata(PathTrack_t *p, int index, int size)
{
    if (index < 0 || index >= p->mUnknown100->GetNumSubBanks())
        return -8;
    if (p->mUnknownF0 >= 0)
        return -18;
    PathSubBankState_t *entry = p->mUnknown100->GetSubBankPtr(index);
    if (entry)
        return -18;
    entry = p->mUnknown100->GetAvailSubBankPtr();
    if (!entry)
        return -18;
    entry->mReady = 0;
    entry->mIndex = index;
    char name[512] = "";
    sprintf(name, "%.*s%d.mus", strlen((char *)&p->mUnknown50) - 4, (char *)&p->mUnknown50, index);
    int handle = 0xBEDFACED;
    entry->mpData = (char *)lbl_803EBB60->vfn_07(name, handle, size);
    if (!entry->mpData)
        return -39;
    p->mUnknownF0 = index;
    p->mUnknownF8 = 1;
    p->mUnknownF4 = handle;
    PATHI_subbankready(p, index);
    return 0;
}

extern "C" int PATHI_unloadbank(PathTrack_t *p, int index)
{
    if (index < 0 || index >= p->mUnknown100->GetNumSubBanks())
        return -8;
    PathSubBankState_t *entry = p->mUnknown100->GetSubBankPtr(index);
    if (!entry)
        return -8;
    PathSubBankState_t saved = *entry;
    PATHI_stop(p);
    int result = p->mUnknown100->RemoveSubBank(index);
    p->mUnknown108 -= saved.mInfo.mSizeA;
    p->mUnknown10C -= saved.mInfo.mSizeB;
    return result;
}

extern "C" int PATHI_unloadmostneglectedsubbank(PathTrack_t *p)
{
    int best = 0x07FFFFFF;
    int index = -1;
    for (int i = 0; i < p->mUnknown100->GetMaxSubBanks(); ++i) {
        PathSubBankState_t *entry = p->mUnknown100->GetSubBankPtr(i);
        if (entry && entry->mEvictionPriority >= 0 && entry->mEvictionPriority < best) {
            best = entry->mEvictionPriority;
            index = i;
        }
    }
    if (index == -1)
        return 0;
    return PATHI_unloadbank(p, index);
}
