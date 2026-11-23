/* PATH events (pathevent.c): queues music events from the game, filters and releases them and
   services the event queue each tick. */

#include <string.h>
#include "engine/pathlib.h"

static inline unsigned char *_PATHI_eventpoolbytes(Bank_801B3480 *bank)
{
    return reinterpret_cast<unsigned char *>(bank) +
        (offsetof(Bank_801B3480, mUnknownC0) + 16 * sizeof(Sequence_801B84E4 *));
}

extern "C" int PATHI_addevent(int flags, Sequence_801B84E4 *sequence)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int result = -8;
    Event_801B845C *entry = sequence->mUnknown14;
    int depth = 0;
    unsigned int high = flags & 0xFF000000;
    for (unsigned int i = 0; i < sequence->mUnknownF; ++i, ++entry) {
        if ((entry->mUnknown4 & 0x00FE0000) == 0x00020000) {
            switch ((entry->mUnknown4 >> 9) & 7) {
            case 0:
            case 1:
                entry->mBits4.depth = depth++;
                break;
            case 2:
            case 3:
                entry->mBits4.depth = depth - 1;
                break;
            case 4:
                entry->mBits4.depth = --depth;
                break;
            default:
                break;
            }
        } else {
            entry->mBits4.depth = depth;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i] && (lbl_802F47D0[i]->mUnknown14 & high) == lbl_802F47D0[i]->mUnknown14) {
            int count = lbl_802F47D0[i]->mUnknown1100;
            if (count > 15)
                return -13;
            result = 0;
            unsigned int now = lbl_803EBB60->vfn_05();
            sequence->mUnknown8 = now;
            sequence->mUnknown0 = now;
            lbl_802F47D0[i]->mUnknownC0[count++] = sequence;
            lbl_802F47D0[i]->mUnknown1100 = count;
        }
    }
    return result;
}

extern "C" int PATH_event(int flags, unsigned int id)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    unsigned int voices = id & 0x0F000000;
    int result = -8;
    Sequence_801B84E4 *copy = 0;
    id &= 0x00FFFFFF;
    for (unsigned int i = 0; i < 4; ++i) {
        if (PATHI_switchproject((unsigned char)i, flags) &&
            (voices & (0x01000000 << lbl_803EBB28->mUnknown18->mUnknownC))) {
            Entry_801B63F0 *event = PATHI_findevent(id);
            if (event) {
                if (!event->mUnknown10.bits.flag4000) {
                    if (!copy) {
                        copy = PATHI_copyevent((Sequence_801B84E4 *)event);
                        if (!copy)
                            continue;
                    }
                    result = PATHI_addevent(lbl_802F47D0[i]->mUnknown14, copy);
                } else
                    result = -18;
            }
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" Sequence_801B84E4 *PATHI_copyevent(Sequence_801B84E4 *event)
{
    int size = event->mUnknownF * 12 + 20;
    unsigned char *end = _PATHI_eventpoolbytes(lbl_803EBB28) + Bank_801B3480::kEventPoolBytes;
    unsigned char *free = _PATHI_eventpoolbytes(lbl_803EBB28);
    for (int i = 0; i < 16; ++i) {
        Sequence_801B84E4 *queued = lbl_803EBB28->mUnknownC0[i];
        if ((unsigned char *)queued >= free && (unsigned char *)queued < end)
            free += queued->mUnknownF * 12 + 20;
    }
    if (free + size < end) {
        memcpy(free, event, size);
        ((Sequence_801B84E4 *)free)->mBits10.mVoice = lbl_803EBB28->mUnknown14;
        return (Sequence_801B84E4 *)free;
    }
    if (lbl_803EBB40 & 0x120)
        PATHI_printf("Can't add new event, size %d bytes (%d bytes free).\n", size, end - free);
    return 0;
}

extern "C" void PATHI_releaseevent(int index, int reason)
{
    Bank_801B3480 *bank = lbl_803EBB28;
    Sequence_801B84E4 *event = bank->mUnknownC0[index];
    int size = event->mUnknownF * 12 + 20;
    SequenceHeader_801B6210 saved = *(SequenceHeader_801B6210 *)event;
    unsigned char *free = _PATHI_eventpoolbytes(bank);
    unsigned char *end = free + Bank_801B3480::kEventPoolBytes;
    int pooled = (unsigned char *)event >= free && (unsigned char *)event < end;
    if (pooled) {
        memcpy(event, (unsigned char *)event + size, end - (unsigned char *)event);
        for (int i = 0; i <= 16; ++i) {
            Sequence_801B84E4 *queued = lbl_803EBB28->mUnknownC0[i];
            if ((unsigned char *)queued > (unsigned char *)event && (unsigned char *)queued < end) {
                queued = (Sequence_801B84E4 *)((unsigned char *)queued - size);
                lbl_803EBB28->mUnknownC0[i] = queued;
                if (free <= (unsigned char *)queued)
                    free = (unsigned char *)queued + (queued->mUnknownF * 12 + 20);
            }
        }
    } else if (lbl_803EBB30 && event->mFlags10.flag2000)
        lbl_803EBB30((int)event, reason);
    PATHI_removeevent(event);
}

extern "C" void PATHI_removeevent(Sequence_801B84E4 *p)
{
    for (int i = 0; i < 4; ++i) {
        Bank_801B3480 *bank = lbl_802F47D0[i];
        if (bank) {
            for (int j = 0; j <= 16; ++j) {
                if (bank->mUnknownC0[j] == p) {
                    bank->mUnknownC0[j] = 0;
                    --bank->mUnknown1100;
                    for (++j; j < 16; ++j)
                        bank->mUnknownC0[j - 1] = bank->mUnknownC0[j];
                }
            }
        }
    }
}

extern "C" void PATHI_seteventfilter(Entry_801B63F0 *p, int value)
{
    Entry_801B63F0 *found = PATHI_findevent(p->mUnknownC >> 8);
    if (found)
        found->mUnknown10.bits.flag4000 = value;
}

extern "C" void PATHI_clearalleventfilters(void)
{
    for (int i = 0; i < lbl_803EBB28->mUnknown18->mUnknownF; ++i) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown24[i] * 4);
        if (entry)
            entry->mUnknown10.bits.flag4000 = 0;
    }
}

extern "C" int PATHI_serviceevent(int index)
{
    Sequence_801B84E4 *p = lbl_803EBB28->mUnknownC0[index];
    int count = 0;
    if (p->mUnknown8 > lbl_803EBB3C)
        return 0;
    unsigned int i = p->mUnknown10;
    // The packed actions immediately follow the sequence header.
    // FAKEMATCH: Integer address addition reproduces ProDG's indexed add operand order.
    Event_801B845C *entry = reinterpret_cast<Event_801B845C *>(
        i * sizeof(Event_801B845C) + reinterpret_cast<unsigned long long>(p->mUnknown14));
    for (; i < p->mUnknownF; ++entry, ++i) {
        if ((entry->mUnknown4 & 0x10000) || fn_801B7880(p, entry)) {
            ++count;
            ++p->mUnknown10;
            p->mUnknown8 = lbl_803EBB3C;
        } else
            break;
    }
    return count;
}

extern "C" int PATHI_serviceeventqueue(void)
{
    int count = 0;
    for (int i = 0; i < 16; ++i) {
        if (i >= lbl_803EBB28->mUnknown1100)
            lbl_803EBB28->mUnknownC0[i] = 0;
        Sequence_801B84E4 *event = lbl_803EBB28->mUnknownC0[i];
        if (event) {
            int reason = 0;
            if (event->mUnknown10 >= event->mUnknownF)
                reason = 3;
            if (event->mUnknown4 && event->mUnknown0 + event->mUnknown4 < lbl_803EBB3C)
                reason = 1;
            if (event->mBits10.mPriority && !PATHI_eventtakespriority(i))
                reason = 2;
            if (reason) {
                PATHI_releaseevent(i, reason);
                --i;
            } else
                count += PATHI_serviceevent(i);
        }
    }
    return count;
}

extern "C" int PATHI_eventtakespriority(int index)
{
    Sequence_801B84E4 *event = lbl_803EBB28->mUnknownC0[index];
    int priority = event->mBits10.mPriority;
    int odd = priority % 2;
    if (priority <= 0)
        priority = -priority;
    while (++index <= 15) {
        Sequence_801B84E4 *other = lbl_803EBB28->mUnknownC0[index];
        if (other && other->mBits10.mPriority) {
            int level = other->mBits10.mPriority;
            if (level < 0)
                level = -level;
            if (event->mBits10.mPriority > 0 && level < priority + odd) {
                PATHI_releaseevent(index, 2);
                --index;
            } else if (other->mBits10.mPriority < 0) {
                odd = level % 2;
                if (priority < level + odd)
                    return 0;
            }
        }
    }
    return 1;
}
