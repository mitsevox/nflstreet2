/* PATH sample banks (pathbank.c): loads a track sample bank and its sub-banks, reports when a
   sub-bank is ready and unloads banks, dropping the least recently used sub-bank first. */

#include <stdio.h>
#include <string.h>
#include "engine/pathlib.h"

extern "C" int PATHI_loadbank(Node_801B3FE0 *p, int index)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    if (!p->mUnknown100) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_createbankimp not called yet\n", p->mUnknownD0);
        return -14;
    }
    if (index >= p->mUnknown100->fn_801B4548()) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_loadbank no subbank %d\n", p->mUnknownD0, index);
        return -8;
    }
    if (p->mUnknown100->fn_801B456C(index)) {
        if (lbl_803EBB40 & 0x100)
            PATHI_printf("( %.8s )  PATH_loadbank already loaded subbank %d\n", p->mUnknownD0, index);
        return -18;
    }
    Data_801B4548 *info = PATHI_trackinfo(p->mUnknown0);
    SubBank_801B51AC *sub = (SubBank_801B51AC *)(info + 1) + index;
    unsigned int a = p->mUnknown108 + sub->mUnknown4;
    unsigned int b = p->mUnknown10C + sub->mUnknown8;
    int unload = 0;
    if (sub && info && info->mUnknown6)
        unload = 1;
    int full = 0;
    if ((info->mUnknown8 && (a > info->mUnknown8 || b > info->mUnknown8)) || !p->mUnknown100->fn_801B4574())
        full = 1;
    if (unload && full) {
        if (info->mUnknown6 == 2) {
            unsigned int best = 0x7FFFFFFF;
            int victim = -1;
            for (int i = 0; i < p->mUnknown100->fn_801B4564(); ++i) {
                Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(i);
                if (entry && entry->mUnknown0.mUnknown0 <= best) {
                    best = entry->mUnknown0.mUnknown0;
                    victim = i;
                }
            }
            if (victim == index)
                return -13;
            fn_801B57C0(p, victim);
        } else if (info->mUnknown6 == 1)
            fn_801B58F0(p);
    }
    int result = PATHI_loadbankdata(p, index, (sub->mUnknown4 + sub->mUnknown8) << 10);
    if (!result) {
        p->mUnknown108 += sub->mUnknown4;
        p->mUnknown10C += sub->mUnknown8;
        Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(index);
        if (entry)
            entry->mUnknown0 = *sub;
    }
    return result;
}

extern "C" int PATHI_subbankready(Node_801B3FE0 *p, int index)
{
    Record_801B58F0 *entry;
    if (index < 0 || index >= p->mUnknown100->fn_801B4548() ||
        !(entry = p->mUnknown100->fn_801B456C(index)) || !entry->mUnknown1C)
        return -8;
    if (p->mUnknownF8) {
        if (!lbl_803EBB60->vfn_08(p->mUnknownF4, entry->mUnknown1C))
            return -18;
        p->mUnknownFC = p->mUnknown100->fn_801B457C(index, entry->mUnknown1C);
        p->mUnknownF8 = 0;
    }
    if (p->mUnknownF0 >= 0) {
        if (!p->mUnknown100->fn_801B4584(index))
            return -18;
        p->mUnknown100->fn_801B458C(index, p->mUnknownFC);
        p->mUnknownFC = 0;
        p->mUnknownF0 = -1;
    }
    entry->mUnknownC = index;
    entry->mUnknown10 = 1;
    return 0;
}

extern "C" int PATHI_loadbankdata(Node_801B3FE0 *p, int index, int size)
{
    if (index < 0 || index >= p->mUnknown100->fn_801B4548())
        return -8;
    if (p->mUnknownF0 >= 0)
        return -18;
    if (p->mUnknown100->fn_801B456C(index))
        return -18;
    Record_801B58F0 *entry = p->mUnknown100->fn_801B4574();
    if (!entry)
        return -18;
    entry->mUnknown10 = 0;
    entry->mUnknownC = index;
    char name[512] = "";
    sprintf(name, "%.*s%d.mus", strlen((char *)&p->mUnknown50) - 4, (char *)&p->mUnknown50, index);
    int handle = 0xBEDFACED;
    entry->mUnknown1C = (char *)lbl_803EBB60->vfn_07(name, handle, size);
    if (!entry->mUnknown1C)
        return -39;
    p->mUnknownF0 = index;
    p->mUnknownF8 = 1;
    p->mUnknownF4 = handle;
    PATHI_subbankready(p, index);
    return 0;
}

extern "C" int fn_801B57C0(Node_801B3FE0 *p, int index)
{
    if (index < 0 || index >= p->mUnknown100->fn_801B4548())
        return -8;
    Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(index);
    if (!entry)
        return -8;
    Record_801B58F0 saved = *entry;
    PATHI_stop(p);
    int result = p->mUnknown100->fn_801B4594(index);
    p->mUnknown108 -= saved.mUnknown0.mUnknown4;
    p->mUnknown10C -= saved.mUnknown0.mUnknown8;
    return result;
}

extern "C" int fn_801B58F0(Node_801B3FE0 *p)
{
    int best = 0x07FFFFFF;
    int index = -1;
    for (int i = 0; i < p->mUnknown100->fn_801B4564(); ++i) {
        Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(i);
        if (entry && entry->mUnknown20 >= 0 && entry->mUnknown20 < best) {
            best = entry->mUnknown20;
            index = i;
        }
    }
    if (index == -1)
        return 0;
    return fn_801B57C0(p, index);
}
