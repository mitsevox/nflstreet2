/* PATH authored actions (pathaction.c): interprets music-event actions and conditions,
   updates track controls and reads and writes the values those actions refer to. */

#include "engine/pathlib.h"

// Service one authored action on each selected track and return its completion state.
extern "C" int PATHI_serviceaction(PathEvent_t *event, PathAction_t *action)
{
    // FAKEMATCH: the unused header string retains the PATH file's unreferenced diagnostic prefix.
    const char *header = "%s  %s";
    static unsigned int lastwhile = 0;
    static unsigned int lastendif = 0;
    int queued = pfstate->mUnknown1100;
    unsigned int operand = action->mOperand;
    for (int track = 0; track < 24; ++track) {
        unsigned int mask = 1U << track;
        if (!(action->mTrackMask & mask))
            continue;
        PathTrack_t *p = PATHI_gettrackptr(
            (((action->mTrackMask & 0x0F000000) | 0xF0000000) & pfstate->mUnknown14) | mask);
        if (!p || !p->mUnknown100)
            continue;
        int selected = (action->mTrackMask >> 28) & 1;
        int filter = (action->mTrackMask & 0xE0000000) != 0;
        if (selected && !p->mUnknown8.bits.flag1)
            continue;
        if (filter && !selected && p->mUnknown8.bits.flag1)
            continue;
        switch (action->mBits4.operation) {
        case 2: {
            int wait = PATHI_getvalue((short)(operand >> 16), action->mBits4.rhsKind, p, event);
            short id = operand >> 16;
            short limit = operand;
            if (limit > 0 && limit < wait)
                wait = 0;
            if (action->mBits4.rhsKind == 1 && id <= 22 && id >= 20) {
                if (!action->mHalves.low || action->mHalves.low > wait)
                    action->mHalves.low = wait;
                if (wait > 0)
                    wait = gPathMilliseconds + 3000;
            }
            if (wait <= (int)(Path::IPathToReal::realimp->GetMilliseconds() - event->mActionStartedAt)) {
                action->mHalves.low = 0;
                action->mBits4.complete = 1;
            }
            break;
        }
        case 3: {
            int wait = (short)(operand >> 16);
            if (!wait) {
                PathBeatInfo_t info;
                p->mUnknown100->vfn_03();
                if (PATHI_beatinfo(p, &info) >= 0)
                    action->mHalves.high = PATHI_calcwaitbeat(
                        (operand >> 12) & 15, (operand >> 8) & 15, (operand >> 4) & 15, &info);
                else
                    action->mBits4.complete = 1;
            } else if (wait <= (int)(Path::IPathToReal::realimp->GetMilliseconds() - event->mActionStartedAt)) {
                action->mHalves.high = -1;
                action->mBits4.complete = 1;
            }
            break;
        }
        case 4: {
            PathTrack_t saved = *p;
            int result = -9999;
            int node = PATHI_getvalue((short)(operand >> 16), action->mBits4.lhsKind, p, event);
            int section = PATHI_getvalue((signed char)(operand >> 8), action->mBits4.rhsKind, p, event);
            if (node < -1 || node > pfstate->mUnknown18->mUnknown12) {
                if (debugchannels & 0x20)
                    PATHI_printf("( %.8s )  PATHACTION_BRANCHTO bad node ID = %d, \n", p->mUnknownD0, node);
                node = -1;
            }
            PathMapEntry_t *destination = 0;
            if (node > 0)
                destination = PATHI_getnode(node);
            if (destination && destination->mBits0.mTrack != p->mUnknown0)
                break;
            if (p->mUnknown8.bits.flag20)
                break;
            if (section >= 0 && node >= 0) {
                int i;
                for (i = 0; i < pfstate->mUnknown18->mUnknown12; ++i) {
                    PathMapEntry_t *candidate = PATHI_getnode(i);
                    if ((((unsigned int *)candidate)[0] >> 5 & 63) == section && !candidate->mSample) {
                        if (--node == 0) {
                            node = i;
                            break;
                        }
                    }
                }
                if (i >= pfstate->mUnknown18->mUnknown12)
                    node = -1;
            }
            int previous = p->mUnknown4;
            if (operand & 0x80)
                PATHI_stop(p);
            int ready = 0;
            if (p->mUnknownF0 < 0)
                ready = p->mUnknown100->vfn_08();
            if (ready) {
                p->mUnknown8.bits.mUnknown7 = -1;
                p->mUnknown4 = PATHI_enternode(previous, node, p->mUnknown1, 1);
                result = PATHI_queuenode(p);
            }
            if (result >= 0)
                action->mBits4.complete = 1;
            else {
                pfstate->mUnknown1100 = queued;
                *p = saved;
            }
            break;
        }
        case 5: {
            int duration = PATHI_getvalue((unsigned short)operand, action->mBits4.rhsKind, p, event);
            PATHI_fade(p, (signed char)(operand >> 24), duration, ((int)(operand << 8)) >> 25);
            action->mBits4.complete = 1;
            break;
        }
        case 7: {
            int duration = PATHI_getvalue((unsigned short)operand, action->mBits4.rhsKind, p, event);
            PATHI_customsfxfade(p, (signed char)(operand >> 24), duration, ((int)(operand << 8)) >> 25);
            action->mBits4.complete = 1;
            break;
        }
        case 6: {
            int duration = PATHI_getvalue((unsigned short)operand, action->mBits4.rhsKind, p, event);
            PATHI_customdrylevelfade(p, (signed char)(operand >> 24), duration, ((int)(operand << 8)) >> 25);
            action->mBits4.complete = 1;
            break;
        }
        case 9: {
            PathMapEntry_t *found = PATHI_findevent(operand >> 8);
            if (found)
                PATHI_addevent(pfstate->mUnknown14 | 0xF0000000, PATHI_copyevent((PathEvent_t *)found));
            action->mBits4.complete = 1;
            break;
        }
        case 13: {
            int first = PATHI_getvalue((operand >> 8) & 255, action->mBits4.rhsKind, p, event);
            int second = PATHI_getvalue((short)(operand >> 16), action->mBits4.lhsKind, p, event);
            if (eventaction)
                eventaction(first, second);
            action->mBits4.complete = 1;
            break;
        }
        case 10:
        case 11:
        case 12:
            if (!(operand & 0xFFFFFF00))
                PATHI_clearalleventfilters();
            else {
                PathMapEntry_t *found = PATHI_findevent(operand >> 8);
                if (found)
                    PATHI_seteventfilter(found, (operand >> 7) & 1);
            }
            action->mBits4.complete = 1;
            break;
        case 8: {
            int value = PATHI_getvalue((short)(operand >> 16), action->mBits4.rhsKind, p, event);
            action->mBits4.complete = 1;
            PATHI_setvalue((operand >> 8) & 255, action->mBits4.lhsKind, value, p, event);
            break;
        }
        case 14: {
            int value = PATHI_getvalue(operand >> 24, action->mBits4.lhsKind, p, event);
            int rhs = PATHI_getvalue((short)operand, action->mBits4.rhsKind, p, event);
            action->mBits4.complete = 1;
            switch ((operand >> 16) & 255) {
            case 1: value += rhs; break;
            case 2: value -= rhs; break;
            case 3: value *= rhs; break;
            case 4: value /= rhs; break;
            case 5: value %= rhs; break;
            }
            PATHI_setvalue(operand >> 24, action->mBits4.lhsKind, value, p, event);
            break;
        }
        case 15: {
            int wait = PATHI_getvalue(operand >> 16, action->mBits4.rhsKind, p, event);
            action->mBits4.complete = 1;
            if (wait <= 0) {
                p->mUnknown8.bits.flag40 = (operand >> 15) & 1;
                p->mUnknown100->vfn_05((operand >> 15) & 1);
            } else if (operand & 0x8000)
                p->mPauseTime = gPathMilliseconds + wait;
            else
                p->mResumeTime = gPathMilliseconds + wait;
            break;
        }
        case 16:
            PATHI_getvalue(operand >> 24, action->mBits4.rhsKind, p, event);
            action->mBits4.complete = 1;
            PATHI_loadbank(p, operand >> 24);
            break;
        case 1: {
            if (action->mBits4.condition == 3) {
                action->mBits4.complete = 1;
                return 1;
            }
            if (action->mBits4.condition == 4) {
                action->mBits4.complete = 1;
                if (PATHI_restoretolastwhile(action, event)) {
                    if (event->mActionStartedAt == gPathMilliseconds)
                        ++event->mActionStartedAt;
                    action->mBits4.complete = 0;
                    lastendif = gPathMilliseconds;
                }
                return action->mBits4.complete;
            }
            int id = (short)(operand >> 16);
            int lhs = PATHI_getvalue(id, action->mBits4.lhsKind, p, event);
            int rhs = PATHI_getvalue((short)operand, action->mBits4.rhsKind, p, event);
            if (action->mBits4.lhsKind == 1 && id == 17) {
                int status = PATHI_trackstatus(p);
                if (rhs == 4 && status == 1)
                    action->mBits4.complete = 1;
            }
            switch (action->mBits4.comparison) {
            case 0: action->mBits4.complete = 1; break;
            case 1: action->mBits4.complete = lhs == rhs; break;
            case 2: action->mBits4.complete = lhs != rhs; break;
            case 3: action->mBits4.complete = lhs > rhs; break;
            case 4: action->mBits4.complete = lhs < rhs; break;
            case 5: action->mBits4.complete = lhs >= rhs; break;
            case 6: action->mBits4.complete = lhs <= rhs; break;
            }
            if (!action->mBits4.condition) {
                if (!action->mBits4.complete)
                    PATHI_conditiondone(action, 0, &event->mActions[event->mActionCount - 1]);
                lastwhile = gPathMilliseconds;
                action->mBits4.complete = !action->mBits4.complete;
                return 1;
            }
            PATHI_conditiondone(action, action->mBits4.complete, &event->mActions[event->mActionCount - 1]);
            action->mBits4.complete = 1;
            break;
        }
        default:
            action->mBits4.complete = 1;
            break;
        }
    }
    return action->mBits4.complete;
}


// Skip a conditional block at the current nesting depth and mark skipped actions complete.
extern "C" PathAction_t *PATHI_conditiondone(PathAction_t *p, int state, PathAction_t *end)
{
    unsigned int value = (p->mControl >> 3) & 7;
    // The entry state controls where to stop even after marking has begun.
    const int initialState = state;
    ++p;
    while (p <= end && state >= 0) {
        if (((p->mControl >> 3) & 7) == value) {
            if ((p->mControl & 0x00FE0E00) == 0x00020800) {
                p->mControl |= 0x10000;
                return p;
            }
            if (!initialState)
                return p;
            state = 0;
        }
        if (!state)
            p->mControl |= 0x10000;
        ++p;
    }
    return p;
}

// Rewind the event to its enclosing while action and make that span runnable again.
extern "C" int PATHI_restoretolastwhile(PathAction_t *p, PathEvent_t *sequence)
{
    unsigned int value = (p->mControl >> 3) & 7;
    PathAction_t *end = p;
    PathAction_t *start = sequence->mActions;
    PathAction_t *found = 0;
    while (--p >= start) {
        if (((p->mControl >> 3) & 7) == value &&
            (p->mControl & 0x00FE0E00) == 0x00020000) {
            found = p;
            break;
        }
    }
    if (!found)
        return 0;
    sequence->mActionIndex = found - start;
    for (; p <= end; ++p)
        p->mControl &= ~0x10000U;
    return 1;
}

// Refresh the state exposed to authored conditions from the track and backend.
extern "C" int PATHI_trackstatus(PathTrack_t *p)
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
        if (value && PATHI_timeremaining(p) <= (p->mUnknown8.halves.high))
            p->mUnknown110 = 4;
        if (p->mUnknown1A == -1)
            p->mUnknown110 = 6;
    }
    return p->mUnknown110;
}

// Resolve an immediate, map variable, or authored track/event property.
extern "C" int PATHI_getvalue(int id, int kind, PathTrack_t *p, PathEvent_t *event)
{
    PathActionStatus_t status;
    if (kind == 2)
        id = pfstate->mUnknown2C[id].mValue;
    else if (kind == 1) {
        switch (id) {
        case 1:
            id = p->mUnknown1;
            break;
        case 2:
            id = p->mUnknown4;
            break;
        case 3: {
            PathMapEntry_t *node = PATHI_getnode(p->mUnknown4);
            id = -1;
            if (node)
                id = node->mLinkAndSync >> 16;
            break;
        }
        case 4: {
            PathMapEntry_t *node = PATHI_getnode(p->mUnknown4);
            if (node)
                id = node->mBits0.mSection;
            else
                id = -1;
            break;
        }
        case 5:
            id = event->mLifetime;
            break;
        case 6:
            id = event->mBits10.mPriority;
            break;
        case 7:
            id = p->mUnknown8.bits.mUnknown1;
            break;
        case 8:
            id = p->mUnknownE;
            break;
        case 9:
            id = p->mUnknownC;
            break;
        case 10:
            id = p->mUnknown8.bits.flag1;
            break;
        case 11: {
            int next = PATHI_nextnode(p->mUnknown4, p->mUnknown1, 0);
            id = PATHI_enternode(p->mUnknown4, next, p->mUnknown1, 0);
            break;
        }
        case 12:
            id = p->mUnknown8.bits.flag20;
            break;
        case 14:
            id = p->mUnknown8.bits.flag40;
            break;
        case 15:
            if (p->mUnknown100)
                id = p->mUnknown100->vfn_18();
            else
                id = 1;
            break;
        case 16:
            PATHI_status(p, &status);
            id = status.mNode;
            break;
        case 17:
            id = PATHI_trackstatus(p);
            break;
        case 18:
            id = (unsigned short)PATHI_random();
            break;
        case 19:
            id = Path::IPathToReal::realimp->GetMilliseconds();
            break;
        case 13:
            PATHI_status(p, &status);
            id = status.mNodeDuration;
            break;
        case 20:
            PATHI_status(p, &status);
            id = status.mBeatRemaining;
            break;
        case 21:
            PATHI_status(p, &status);
            id = status.mBarRemaining;
            break;
        case 22:
            PATHI_status(p, &status);
            id = status.mRemaining;
            break;
        case 23:
            id = (signed char)p->mUnknown3;
            break;
        }
    }
    return id;
}

// Write a map variable or writable track/event property, forwarding backend controls.
extern "C" void PATHI_setvalue(int id, int kind, int value, PathTrack_t *p, PathEvent_t *event)
{
    if (kind == 2)
        pfstate->mUnknown2C[id].mValue = value;
    else if (kind == 1) {
        switch (id) {
        case 1:
            // These bounds checks follow the store and do not alter the stored control value.
            p->mUnknown1 = value;
            if (value < 0)
                value = 0;
            if (value > 127)
                value = 127;
            break;
        case 5:
            event->mLifetime = value;
            break;
        case 6:
            // Priority is likewise stored before the local bounds checks.
            event->mBits10.mPriority = value;
            if (value < -7)
                value = -7;
            if (value > 7)
                value = 7;
            break;
        case 7:
            p->mUnknown8.bits.mUnknown1 = value;
            break;
        case 10:
            PATHI_selectprojecttrack(p, value);
            break;
        case 12:
            p->mUnknown8.bits.flag20 = value != 0;
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
