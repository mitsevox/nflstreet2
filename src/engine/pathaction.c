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

extern "C" int fn_801B8580(PathTrack_t *p)
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

extern "C" int PATHI_getvalue(int id, int kind, PathTrack_t *p, Sequence_801B84E4 *event)
{
    int value = id;
    TrackStatus_801B864C status;
    if (kind == 2)
        value = pfstate->mUnknown2C[id].mValue;
    else if (kind == 1) {
        switch (id) {
        case 1:
            value = p->mUnknown1;
            break;
        case 2:
            value = p->mUnknown4;
            break;
        case 3: {
            Entry_801B63F0 *node = PATHI_getnode(p->mUnknown4);
            value = -1;
            if (node)
                value = node->mUnknown8 >> 16;
            break;
        }
        case 4: {
            Entry_801B63F0 *node = PATHI_getnode(p->mUnknown4);
            if (node)
                value = (node->mUnknown4 >> 5) & 63;
            else
                value = -1;
            break;
        }
        case 5:
            value = event->mUnknown4;
            break;
        case 6:
            value = event->mBits10.mPriority;
            break;
        case 7:
            value = p->mUnknown8.bits.mUnknown1;
            break;
        case 8:
            value = p->mUnknownE;
            break;
        case 9:
            value = p->mUnknownC;
            break;
        case 10:
            value = p->mUnknown8.bits.flag1;
            break;
        case 11:
            value = PATHI_enternode(p->mUnknown4, PATHI_nextnode(p->mUnknown4, p->mUnknown1, 0), p->mUnknown1, 0);
            break;
        case 12:
            value = p->mUnknown8.bits.flag20;
            break;
        case 13:
            PATHI_status(p, &status);
            value = status.mUnknown18;
            break;
        case 14:
            value = p->mUnknown8.bits.flag40;
            break;
        case 15:
            if (p->mUnknown100)
                value = p->mUnknown100->vfn_18();
            else
                value = 1;
            break;
        case 16:
            PATHI_status(p, &status);
            value = status.mUnknown0;
            break;
        case 17:
            value = fn_801B8580(p);
            break;
        case 18:
            value = (unsigned short)PATHI_random();
            break;
        case 19:
            value = Path::IPathToReal::realimp->GetMilliseconds();
            break;
        case 20:
            PATHI_status(p, &status);
            value = status.mUnknown2C;
            break;
        case 21:
            PATHI_status(p, &status);
            value = status.mUnknown28;
            break;
        case 22:
            PATHI_status(p, &status);
            value = status.mUnknown24;
            break;
        case 23:
            value = (signed char)p->mUnknown3;
            break;
        }
    }
    return value;
}

extern "C" void PATHI_setvalue(int id, int kind, int value, PathTrack_t *p, Sequence_801B84E4 *event)
{
    if (kind == 2)
        pfstate->mUnknown2C[id].mValue = value;
    else if (kind == 1) {
        switch (id) {
        case 1:
            p->mUnknown1 = value;
            if (value < 0)
                value = 0;
            if (value > 127)
                value = 127;
            break;
        case 5:
            event->mUnknown4 = value;
            break;
        case 6:
            event->mBits10.mPriority = value;
            if (value < -7)
                value = -7;
            if (value > 7)
                value = 7;
            break;
        case 7:
            p->mUnknown8.bits.mUnknown1 = value;
            break;
        case 8:
            if (value > 127)
                value = 127;
            if (value < 0)
                value = 0;
            p->mUnknownE = value;
            if (p->mUnknown100)
                p->mUnknown100->vfn_15(value);
            break;
        case 9:
            if (value > 127)
                value = 127;
            if (value < 0)
                value = 0;
            if (p->mUnknown100)
                p->mUnknown100->vfn_17(p->mUnknown8.bits.mUnknown1, value);
            p->mUnknownC = value;
            break;
        case 10:
            PATHI_selectprojecttrack(p, value);
            break;
        case 12:
            p->mUnknown8.bits.flag20 = value != 0;
            break;
        case 14:
            value = value != 0;
            p->mUnknown8.bits.flag40 = value;
            if (p->mUnknown100)
                p->mUnknown100->vfn_05(value);
            break;
        case 15:
            if (p->mUnknown100)
                p->mUnknown100->vfn_19(value);
            break;
        case 23:
            if (value > 127)
                value = 127;
            if (value < 0)
                value = 0;
            fn_801B4824(p, (signed char)value);
            break;
        }
    }
}
