/* PATH authored actions (pathaction.c): runs the actions and conditions authored into music
   events and reads and writes the values they refer to. */

#include "engine/pathlib.h"

extern "C" Event_801B845C *fn_801B845C(Event_801B845C *p, int state, Event_801B845C *end)
{
    unsigned int value = (p->mUnknown4 >> 3) & 7;
    ++p;
    while (p <= end && state >= 0) {
        if (((p->mUnknown4 >> 3) & 7) == value) {
            if ((p->mUnknown4 & 0x00FE0E00) == 0x00020800) {
                p->mUnknown4 |= 0x10000;
                return p;
            }
            if (!state)
                return p;
            state = 0;
        }
        if (!state)
            p->mUnknown4 |= 0x10000;
        ++p;
    }
    return p;
}

extern "C" int fn_801B84E4(Event_801B845C *p, Sequence_801B84E4 *sequence)
{
    unsigned int value = (p->mUnknown4 >> 3) & 7;
    Event_801B845C *end = p;
    Event_801B845C *start = sequence->mUnknown14;
    Event_801B845C *found = 0;
    while (--p >= start) {
        if (((p->mUnknown4 >> 3) & 7) == value &&
            (p->mUnknown4 & 0x00FE0E00) == 0x00020000) {
            found = p;
            break;
        }
    }
    if (!found)
        return 0;
    sequence->mUnknown10 = found - start;
    for (; p <= end; ++p)
        p->mUnknown4 &= ~0x10000U;
    return 1;
}

extern "C" int fn_801B8580(Node_801B3FE0 *p)
{
    if (!p)
        return 0;
    p->mUnknown110 = 1;
    if (p->mUnknown8.word & 0x40)
        p->mUnknown110 = 3;
    else if (p->mUnknown4 >= 0) {
        p->mUnknown110 = 5;
        int value = 0;
        if (p->mUnknownF0 < 0)
            value = p->mUnknown100->vfn_08();
        if (value && fn_801B6CB4(p) <= (p->mUnknown8.halves.high))
            p->mUnknown110 = 4;
        if (p->mUnknown1A == -1)
            p->mUnknown110 = 6;
    }
    return p->mUnknown110;
}
