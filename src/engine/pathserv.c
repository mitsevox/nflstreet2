/* PATH library servicing (pathserv.c): the millisecond clock, switching between and sorting the
   loaded music projects, and the per-tick service task and timer that drive them. */

#include "engine/pathlib.h"

extern "C" unsigned int PATH_milliseconds(void)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts this file's .rodata
    const char *header = "%s  %s";

    unsigned int result = 0;
    if (lbl_803EBB60)
        result = lbl_803EBB60->vfn_05();
    return result;
}

extern "C" unsigned int PATHI_switchproject(unsigned int index, unsigned int flags)
{
    if (index <= 3 && lbl_802F47D0[index] && lbl_802F47D0[index]->mUnknown18) {
        unsigned int value = lbl_802F47D0[index]->mUnknown14;
        unsigned int mask = flags & 0xF0000000;
        if ((!mask || (value & mask)) && ((value & 0x0F000000) & flags)) {
            lbl_803EBB28 = lbl_802F47D0[index];
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

extern "C" int PATHI_sortprojects(void)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (lbl_802F47D0[i]) {
            for (int j = i + 1; j < 4; ++j) {
                if (lbl_802F47D0[j] && lbl_802F47D0[i]->mUnknown14 > lbl_802F47D0[j]->mUnknown14) {
                    Bank_801B3480 temp = *lbl_802F47D0[i];
                    *lbl_802F47D0[i] = *lbl_802F47D0[j];
                    *lbl_802F47D0[j] = temp;
                }
            }
        }
    }
    return i;
}

extern "C" void PATHI_serviceproject(void)
{
    int bankMode = lbl_803EBB3B == 66;
    unsigned int period;
    if (bankMode)
        period = lbl_803EBB28->mUnknown10;
    else
        period = lbl_803EBB28->mUnknownC;
    if (!bankMode)
        PATHI_serviceeventqueue();

    unsigned int halfPeriod = period >> 1;
    for (unsigned int index = 0; index < 24; ++index) {
        PathTrack_t *track = lbl_803EBB28->mUnknown40[index];
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

        if (track->mPauseTime && track->mPauseTime <= lbl_803EBB3C + halfPeriod) {
            track->mUnknown100->vfn_05(1);
            track->mPauseTime = 0;
            track->mUnknown8.word |= 0x40;
        }
        if (track->mResumeTime && track->mResumeTime <= lbl_803EBB3C + halfPeriod) {
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

        int remaining = fn_801B6CB4(track);
        if (track->mUnknown40) {
            if (track->mUnknown40 > lbl_803EBB3C - track->mUnknown8.halves.high)
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
    if (!lbl_803EBB39) {
        int acquired;
        if (++lbl_803EBB24 == 1 && lbl_803EBB38)
            acquired = 1;
        else {
            --lbl_803EBB24;
            acquired = 0;
        }
        if (acquired) {
            lbl_803EBB3B = mode;
            lbl_803EBB3C = PATH_milliseconds();
            PATHI_dispatchtrackstate(0);
            for (unsigned char i = 0; i < 4; ++i) {
                if (PATHI_switchproject(i, 0xFFFFFFFF)) {
                    PATHI_updatemastertrack();
                    PATHI_serviceproject();
                }
            }
            PATHI_dispatchtrackstate(1);
            lbl_803EBB28 = 0;
            --lbl_803EBB24;
        }
    }
}

extern "C" void PATHI_servicetask(void)
{ PATHI_service(32); }

extern "C" void PATHI_servicetimer(void)
{ PATHI_service(66); }
