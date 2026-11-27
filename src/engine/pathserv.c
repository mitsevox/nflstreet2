/* PATH library servicing (pathserv.c): the millisecond clock, switching between and sorting the
   loaded music projects, and the per-tick service task and timer that drive them. */

#include "engine/pathlib.h"

extern "C" unsigned int PATH_milliseconds(void)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts this file's .rodata
    const char *header = "%s  %s";

    unsigned int result = 0;
    if (Path::IPathToReal::realimp)
        result = Path::IPathToReal::realimp->GetMilliseconds();
    return result;
}

extern "C" unsigned int PATHI_switchproject(unsigned int index, unsigned int flags)
{
    if (index <= 3 && pfstates[index] && pfstates[index]->mUnknown18) {
        unsigned int value = pfstates[index]->mUnknown14;
        unsigned int mask = flags & 0xF0000000;
        if ((!mask || (value & mask)) && ((value & 0x0F000000) & flags)) {
            pfstate = pfstates[index];
            return value;
        }
    }
    return 0;
}

extern "C" int PATHI_switchvoice(unsigned int flags)
{
    int i = 0;
    int hasMask = (flags & 0x0F000000) != 0;
    for (; i < 4; ++i) {
        unsigned int mask = 0;
        if (!hasMask)
            mask = 0x01000000 << i;
        if (PATHI_switchproject(i, flags | mask))
            return 1;
    }
    return 0;
}

extern "C" void PATHI_sortprojects(void)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (pfstates[i]) {
            for (int j = i + 1; j < 4; ++j) {
                if (pfstates[j] && pfstates[i]->mUnknown14 > pfstates[j]->mUnknown14) {
                    PathProject_t temp = *pfstates[i];
                    *pfstates[i] = *pfstates[j];
                    *pfstates[j] = temp;
                }
            }
        }
    }
}

extern "C" void PATHI_serviceproject(void)
{
    int bankMode = bankservice == 66;
    unsigned int period;
    if (bankMode)
        period = pfstate->mUnknown10;
    else
        period = pfstate->mUnknownC;
    if (!bankMode)
        PATHI_serviceeventqueue();

    unsigned int halfPeriod = period >> 1;
    for (unsigned int index = 0; index < 24; ++index) {
        PathTrack_t *track = pfstate->mUnknown40[index];
        if (!track || !track->mUnknown100)
            continue;

        unsigned char active = track->mUnknown4 >= 0 && track->mUnknown34 != 0;
        if (active) {
            if (!(track->mUnknown19 & 0x80))
                PATHI_setfadevolume(track);
            if (!(track->mUnknown25 & 0x80))
                PATHI_setsfxfadevolume(track);
            if (!(track->mUnknown31 & 0x80))
                PATHI_setdrylevelfadevolume(track);
        }

        if (track->mPauseTime && track->mPauseTime <= gPathMilliseconds + halfPeriod) {
            track->mUnknown100->vfn_05(1);
            track->mPauseTime = 0;
            track->mUnknown8.word |= 0x40;
        }
        if (track->mResumeTime && track->mResumeTime <= gPathMilliseconds + halfPeriod) {
            track->mUnknown100->vfn_05(0);
            track->mResumeTime = 0;
            track->mUnknown8.word &= ~0x40;
        }

        if (!bankMode && track->mUnknownF0 >= 0)
            PATHI_subbankready(track, track->mUnknownF0);

        if (((track->mUnknown8.word >> 4) & 1) != (unsigned int)bankMode ||
            !active || (track->mUnknown8.word & 0x40))
            continue;

        int ready;
        if (track->mUnknownF0 >= 0)
            ready = 0;
        else
            ready = track->mUnknown100->vfn_08();
        if (!ready)
            continue;

        int remaining = PATHI_timeremaining(track);
        if (track->mUnknown40) {
            if (track->mUnknown40 > gPathMilliseconds - track->mUnknown8.halves.high)
                continue;
        } else if (remaining > track->mUnknown8.halves.high) {
            continue;
        }

        if (track->mUnknown1A == 0 && track->mUnknown100->GetVolume() == 0)
            track->mUnknown1A = -1;
        PATHI_seeknextnode(index);
    }

    while (!bankMode && PATHI_serviceeventqueue())
        ;
}

extern "C" void PATHI_service(int mode)
{
    if (!paused) {
        int acquired;
        if (++pflock == 1 && inited)
            acquired = 1;
        else {
            --pflock;
            acquired = 0;
        }
        if (acquired) {
            bankservice = mode;
            gPathMilliseconds = PATH_milliseconds();
            PATHI_dispatchtrackstate(0);
            for (unsigned char i = 0; i < 4; ++i) {
                if (PATHI_switchproject(i, 0xFFFFFFFF)) {
                    PATHI_updatemastertrack();
                    PATHI_serviceproject();
                }
            }
            PATHI_dispatchtrackstate(1);
            pfstate = 0;
            --pflock;
        }
    }
}

extern "C" void PATHI_servicetask(void)
{ PATHI_service(32); }

extern "C" void PATHI_servicetimer(void)
{ PATHI_service(66); }
