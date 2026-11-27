/* PATH track control (pathcontrol.c): sets a control value on, pauses, queries the status of and
   stops the music tracks a game request selects by project and track mask. */

#include "engine/pathlib.h"

extern "C" int PATH_control(int flags, int value)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    if ((unsigned int)value <= 127) {
        for (int i = 0; i < 4; ++i) {
            if (PATHI_switchproject((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    PathTrack_t *p = pfstate->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0)
                        p->mUnknown1 = value;
                }
            }
        }
    }
    pfstate = 0;
    --pflock;
    return 0;
}

extern "C" void PATH_pause(int flags, unsigned char value)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (acquired) {
        if (flags == -1)
            paused = value;
        for (int i = 0; i < 4; ++i) {
            if (PATHI_switchproject((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    PathTrack_t *p = pfstate->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0) {
                        p->mUnknown100->Pause(value);
                        p->mUnknown8.bits.flag40 = value;
                    }
                }
            }
        }
        pfstate = 0;
        --pflock;
    }
}

extern "C" int PATH_status(int flags, PathfinderStatus_t *info)
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
    int result = -8;
    PathTrack_t *p = PATHI_gettrackptr(flags);
    if (p && PATHI_switchvoice(flags))
        result = PATHI_status(p, info);
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" int PATHI_status(PathTrack_t *p, void *info)
{
    int result;
    if (p->mUnknown100)
        result = p->mUnknown100->GetPathStatus(info);
    else
        result = -39;
    return result;
}

extern "C" void PATH_stop(int flags)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (acquired) {
        for (int i = 0; i < 4; ++i) {
            if (PATHI_switchproject(i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    PathTrack_t *p = pfstate->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0)
                        PATHI_stop(p);
                }
            }
        }
        pfstate = 0;
        --pflock;
    }
}

extern "C" int PATHI_stop(PathTrack_t *p)
{
    p->mUnknown100->Stop();
    p->mUnknown4 = -1;
    p->mUnknown8.word |= 0xF80;
    return 0;
}
