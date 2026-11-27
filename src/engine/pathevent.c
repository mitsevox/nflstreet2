/* PATH events (pathevent.c): queues music events from the game, filters and releases them and
   services the event queue each tick. */

#include <string.h>
#include "engine/pathlib.h"

static inline unsigned char *_PATHI_eventpoolbytes(PathProject_t *bank)
{
    return reinterpret_cast<unsigned char *>(bank) +
        (offsetof(PathProject_t, mUnknownC0) + 16 * sizeof(PathEvent_t *));
}

extern "C" int PATHI_addevent(int flags, PathEvent_t *sequence)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int result = -8;
    PathAction_t *entry = sequence->mActions;
    int depth = 0;
    unsigned int high = flags & 0xFF000000;
    for (unsigned int i = 0; i < sequence->mActionCount; ++i, ++entry) {
        if ((entry->mControl & 0x00FE0000) == 0x00020000) {
            switch ((entry->mControl >> 9) & 7) {
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
        if (pfstates[i] && (pfstates[i]->mUnknown14 & high) == pfstates[i]->mUnknown14) {
            int count = pfstates[i]->mUnknown1100;
            if (count > 15)
                return -13;
            result = 0;
            unsigned int now = Path::IPathToReal::realimp->GetMilliseconds();
            sequence->mActionStartedAt = now;
            sequence->mCreatedAt = now;
            pfstates[i]->mUnknownC0[count++] = sequence;
            pfstates[i]->mUnknown1100 = count;
        }
    }
    return result;
}

extern "C" int PATH_event(int flags, unsigned int id)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    unsigned int voices = id & 0x0F000000;
    int result = -8;
    PathEvent_t *copy = 0;
    id &= 0x00FFFFFF;
    for (unsigned int i = 0; i < 4; ++i) {
        if (PATHI_switchproject((unsigned char)i, flags) &&
            (voices & (0x01000000 << pfstate->mUnknown18->mUnknownC))) {
            PathMapEntry_t *event = PATHI_findevent(id);
            if (event) {
                if (!event->mEventFlags.bits.flag4000) {
                    if (!copy) {
                        copy = PATHI_copyevent((PathEvent_t *)event);
                        if (!copy)
                            continue;
                    }
                    result = PATHI_addevent(pfstates[i]->mUnknown14, copy);
                } else
                    result = -18;
            }
        }
    }
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" PathEvent_t *PATHI_copyevent(PathEvent_t *event)
{
    int size = event->mActionCount * 12 + 20;
    unsigned char *end = _PATHI_eventpoolbytes(pfstate) + PathProject_t::kEventPoolBytes;
    unsigned char *free = _PATHI_eventpoolbytes(pfstate);
    for (int i = 0; i < 16; ++i) {
        PathEvent_t *queued = pfstate->mUnknownC0[i];
        if ((unsigned char *)queued >= free && (unsigned char *)queued < end)
            free += queued->mActionCount * 12 + 20;
    }
    if (free + size < end) {
        memcpy(free, event, size);
        ((PathEvent_t *)free)->mBits10.mVoice = pfstate->mUnknown14;
        return (PathEvent_t *)free;
    }
    if (debugchannels & 0x120)
        PATHI_printf("Can't add new event, size %d bytes (%d bytes free).\n", size, end - free);
    return 0;
}

extern "C" void PATHI_releaseevent(int index, int reason)
{
    PathProject_t *bank = pfstate;
    PathEvent_t *event = bank->mUnknownC0[index];
    int size = event->mActionCount * 12 + 20;
    PathEventHeader_t saved = *(PathEventHeader_t *)event;
    unsigned char *free = _PATHI_eventpoolbytes(bank);
    unsigned char *end = free + PathProject_t::kEventPoolBytes;
    int pooled = (unsigned char *)event >= free && (unsigned char *)event < end;
    if (pooled) {
        memcpy(event, (unsigned char *)event + size, end - (unsigned char *)event);
        for (int i = 0; i <= 16; ++i) {
            PathEvent_t *queued = pfstate->mUnknownC0[i];
            if ((unsigned char *)queued > (unsigned char *)event && (unsigned char *)queued < end) {
                queued = (PathEvent_t *)((unsigned char *)queued - size);
                pfstate->mUnknownC0[i] = queued;
                if (free <= (unsigned char *)queued)
                    free = (unsigned char *)queued + (queued->mActionCount * 12 + 20);
            }
        }
    } else if (eventrelease && event->mFlags10.flag2000)
        eventrelease((int)event, reason);
    PATHI_removeevent(event);
}

extern "C" void PATHI_removeevent(PathEvent_t *p)
{
    for (int i = 0; i < 4; ++i) {
        PathProject_t *bank = pfstates[i];
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

extern "C" void PATHI_seteventfilter(PathMapEntry_t *p, int value)
{
    PathMapEntry_t *found = PATHI_findevent(p->mFlagsAndEvent >> 8);
    if (found)
        found->mEventFlags.bits.flag4000 = value;
}

extern "C" void PATHI_clearalleventfilters(void)
{
    for (int i = 0; i < pfstate->mUnknown18->mUnknownF; ++i) {
        PathMapEntry_t *entry = (PathMapEntry_t *)((unsigned char *)pfstate->mUnknown18 + pfstate->mUnknown24[i] * 4);
        if (entry)
            entry->mEventFlags.bits.flag4000 = 0;
    }
}

extern "C" int PATHI_serviceevent(int index)
{
    PathEvent_t *p = pfstate->mUnknownC0[index];
    int count = 0;
    if (p->mActionStartedAt > gPathMilliseconds)
        return 0;
    unsigned int i = p->mActionIndex;
    // The packed actions immediately follow the sequence header.
    // FAKEMATCH: Integer address addition reproduces ProDG's indexed add operand order.
    PathAction_t *entry = reinterpret_cast<PathAction_t *>(
        i * sizeof(PathAction_t) + reinterpret_cast<unsigned long long>(p->mActions));
    for (; i < p->mActionCount; ++entry, ++i) {
        if ((entry->mControl & 0x10000) || PATHI_serviceaction(p, entry)) {
            ++count;
            ++p->mActionIndex;
            p->mActionStartedAt = gPathMilliseconds;
        } else
            break;
    }
    return count;
}

extern "C" int PATHI_serviceeventqueue(void)
{
    int count = 0;
    for (int i = 0; i < 16; ++i) {
        if (i >= pfstate->mUnknown1100)
            pfstate->mUnknownC0[i] = 0;
        PathEvent_t *event = pfstate->mUnknownC0[i];
        if (event) {
            int reason = 0;
            if (event->mActionIndex >= event->mActionCount)
                reason = 3;
            if (event->mLifetime && event->mCreatedAt + event->mLifetime < gPathMilliseconds)
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
    PathEvent_t *event = pfstate->mUnknownC0[index];
    int priority = event->mBits10.mPriority;
    int odd = priority % 2;
    if (priority <= 0)
        priority = -priority;
    while (++index <= 15) {
        PathEvent_t *other = pfstate->mUnknownC0[index];
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
