/* PATH interactive-music library start-up (pathinit.c): initializes and shuts down the library,
   routes its memory through the installed allocator, keeps the event callbacks and loads, destroys
   and sizes the music projects (map files). It also holds the library's shared state: the lock, the
   project table, the clock, the debug mask and the platform, sound and allocator back ends. */

#include <string.h>
#include "engine/pathlib.h"

extern "C" {
int pflock = 0;
PathProject_t *pfstates[4] = {0, 0, 0, 0};
PathProject_t *pfstate = 0;
void (*songprogress)(int, int) = 0;
void (*eventrelease)(int, int) = 0;
void (*eventaction)(int, int) = 0;
unsigned char inited = 0;
unsigned char paused = 0;
unsigned char volscale = 100;
unsigned char bankservice = 32;
unsigned int gPathMilliseconds = 0;
int debugchannels = 256;
int defaultfxbus = 0;
int timercalls = 0;
int timertimespent = 0;
int taskcalls = 0;
int tasktimespent = 0;
// FAKEMATCH: two words nothing in this build reads or writes; they keep the back-end pointers below
// at their target offsets in the file's .sdata.
int _Path_aiUnused[2] = {0, 0};
AllocParams gPathAllocatorParams;
}

Path::IPathToReal *Path::IPathToReal::realimp = 0;
Path::IPathToSnd *Path::IPathToSnd::sndimp = 0;
Allocator *Path::IPathToReal::memimp = 0;

extern "C" int PATHI_init(void)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    if (++pflock != 1) {
        --pflock;
        return -18;
    }
    for (int i = 3; i >= 0; --i)
        pfstates[i] = 0;
    inited = 1;
    debugchannels = 256;
    pfstate = 0;
    paused = 0;
    tasktimespent = 0;
    taskcalls = 0;
    timertimespent = 0;
    timercalls = 0;
    --pflock;
    return 0;
}

// FAKEMATCH: discarded file-static stand-in; its literal pool (int-to-double, 0.5, 2^31) is the
// unreferenced 0x802AEA20-0x802AEA38 block of the target .rodata
static unsigned int _PathRoundToUnsigned(int value)
{
    return (unsigned int)(value + 0.5);
}

extern "C" int PATH_shutdown(void)
{
    if (!inited)
        return -14;
    PATH_destroy(0x0F000000);
    if (PATHI_countprojecttracks(0x0F000000) == 0) {
        SNDSYS_entercritical();
        delete Path::IPathToSnd::sndimp;
        delete Path::IPathToReal::realimp;
        SNDSYS_leavecritical();
        Path::IPathToReal::realimp = 0;
        Path::IPathToReal::memimp = 0;
        Path::IPathToSnd::sndimp = 0;
        inited = 0;
    }
    return inited == 0;
}

extern "C" void PATH_setallocator(Allocator *allocator, const AllocParams &params)
{
    Path::IPathToReal::memimp = allocator;
    gPathAllocatorParams = params;
}

extern "C" void *PATHI_memalloc(int size)
{
    void *result;
    if (Path::IPathToReal::memimp)
        result = Path::IPathToReal::memimp->Alloc(size, gPathAllocatorParams);
    else
        result = 0;
    return result;
}

extern "C" void PATHI_memfree(void *p)
{
    if (Path::IPathToReal::memimp)
        Path::IPathToReal::memimp->Free(p, 0);
}

extern "C" int PATH_addmapfile(PathMapHeader_t *map)
{
    if (!inited)
        PATHI_init();
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int slot = 4;
    int voice = map->mUnknownC;
    int result = -1;
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (!pfstates[i]) {
            if (slot == 4)
                slot = i;
        } else if (pfstates[i]->mUnknown18->mUnknownC == voice) {
            if (map->mUnknownA != pfstates[i]->mUnknown18->mUnknownA)
                goto done;
            ++count;
        }
    }
    if (slot <= 3 && map->mUnknown0 == 0x50464478 && (map->mUnknown4 & 0xFFFF0000) == 0x05000000) {
        pfstates[slot] = (PathProject_t *)PATHI_memalloc(sizeof(PathProject_t));
        if (pfstates[slot]) {
            memset(pfstates[slot], 0, sizeof(PathProject_t));
            pfstates[slot]->mUnknown18 = map;
            pfstates[slot]->mUnknown14 = (0x10000000 << count) | (0x01000000 << voice);
            PATHI_switchproject(slot, pfstates[slot]->mUnknown14);
            pfstate->mUnknown1C = (short *)((char *)map + pfstate->mUnknown18->mUnknown14);
            pfstate->mUnknown20 = (char *)map + pfstate->mUnknown18->mUnknown18;
            pfstate->mUnknown24 = (short *)((char *)map + pfstate->mUnknown18->mUnknown1C);
            pfstate->mUnknown28 = (char *)map + pfstate->mUnknown18->mUnknown20;
            pfstate->mUnknown2C = (PathMapVariable_t *)((char *)map + pfstate->mUnknown18->mUnknown24);
            pfstate->mUnknown30 = (unsigned int *)((char *)map + pfstate->mUnknown18->mUnknown28);
            pfstate->mUnknown34 = (int *)((char *)map + pfstate->mUnknown18->mUnknown2C);
            pfstate->mUnknown38 = (char *)map + pfstate->mUnknown18->mUnknown30;
            pfstate->mUnknown3C = (unsigned int *)((char *)map + pfstate->mUnknown18->mUnknown34);
            for (int j = 15; j >= 0; --j)
                pfstate->mUnknownC0[j] = 0;
            pfstate->mUnknownC = 50;
            pfstate->mUnknown10 = 10;
            result = voice;
        }
    }
done:
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" void PATH_seteventcallbacks(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int))
{
    songprogress = a;
    eventrelease = b;
    eventaction = c;
}

extern "C" int PATH_destroy(int flags)
{
    int acquired;
    if (++pflock == 1 && inited)
        acquired = 1;
    else {
        --pflock;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (PATHI_switchproject((unsigned char)i, flags)) {
            for (int j = 0; j < 24; ++j) {
                PathTrack_t *p = pfstate->mUnknown40[j];
                // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0, as in pathcontrol.c; == 1 drops the target xori
                if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0) {
                    pfstate->mUnknown40[j] = 0;
                    if (p->mUnknown100)
                        delete p->mUnknown100;
                    p->mUnknown100 = 0;
                    ++count;
                    PATHI_memfree(p);
                }
            }
            if (PATHI_countprojecttracks(0x01000000 << i) == 0) {
                PATHI_memfree(pfstate);
                pfstates[i] = 0;
            }
        }
    }
    PATHI_sortprojects();
    pfstate = 0;
    --pflock;
    return count;
}

extern "C" int PATH_setvariable(int flags, const char *name, int value)
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
    if (!name)
        return -8;
    char lower[16];
    int result = -8;
    for (int i = 0; i < 16; ++i) {
        lower[i] = name[i];
        if (lower[i] == 0)
            break;
        lower[i] |= 32;
    }
    flags &= 0x0F000000;
    for (int i = 0; i < 4; ++i) {
        if (pfstates[i] && pfstates[i]->mUnknown18 && (pfstates[i]->mUnknown14 & flags)) {
            for (int j = 0; j < pfstates[i]->mUnknown18->mUnknown11; ++j) {
                if (pfstates[i]->mUnknown2C[j].mName[0] &&
                    !strcmp(lower, pfstates[i]->mUnknown2C[j].mName)) {
                    result = 0;
                    pfstates[i]->mUnknown2C[j].mValue = value;
                }
            }
        }
    }
    pfstate = 0;
    --pflock;
    return result;
}

extern "C" void *PATHI_gettrackimp(int flags)
{
    PathTrack_t *p = PATHI_gettrackptr(flags);
    if (!p)
        return 0;
    return p->mUnknown100;
}

extern "C" int PATHI_bytesperms(int index)
{
    float best = 0.0f;
    PathStreamRecord_t *end = 0;
    PathTrackInfo_t *info = PATHI_trackinfo(index);
    if (!info)
        return 0;
    PathStreamRecord_t *p = (PathStreamRecord_t *)pfstate->mUnknown3C + info->mUnknown0;
    ++index;
    if (index < pfstate->mUnknown18->mUnknownD) {
        PathTrackInfo_t *next = PATHI_trackinfo(index);
        if (next)
            end = (PathStreamRecord_t *)pfstate->mUnknown3C + next->mUnknown0;
    } else
        end = (PathStreamRecord_t *)((char *)pfstate->mUnknown18 + pfstate->mUnknown18->mUnknown38);
    for (; p < end - 1; ++p) {
        float rate = (float)(int)((p[1].mByteOffset - p[0].mByteOffset) << 7) / (float)p->mDuration;
        if (!(best >= rate))
            best = rate;
    }
    return (int)(best + 0.5);
}
