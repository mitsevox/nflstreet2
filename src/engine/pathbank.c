/* PATH sample banks (pathbank.c): loads a track sample bank and its sub-banks, reports when a
   sub-bank is ready and unloads banks, dropping the least recently used sub-bank first. */

#include "engine/pathlib.h"

extern "C" int fn_801B57C0(Node_801B3FE0 *p, int index)
{
    if (index < 0 || index >= p->mUnknown100->fn_801B4548())
        return -8;
    Record_801B58F0 *entry = p->mUnknown100->fn_801B456C(index);
    if (!entry)
        return -8;
    Record_801B58F0 saved = *entry;
    fn_801B5DB4(p);
    int result = p->mUnknown100->fn_801B4594(index);
    p->mUnknown108 -= saved.mUnknown4;
    p->mUnknown10C -= saved.mUnknown8;
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
