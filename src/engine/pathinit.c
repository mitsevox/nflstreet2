/* PATH interactive-music library start-up (pathinit.c): initializes and shuts down the library,
   routes its memory through the installed allocator, keeps the debug callbacks and loads, destroys
   and sizes the music projects (map files). */

#include <string.h>
#include "engine/pathlib.h"

extern "C" {
AllocParams gPathAllocatorParams;
}

extern "C" int PATHI_init(void)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    if (++lbl_803EBB24 != 1) {
        --lbl_803EBB24;
        return -18;
    }
    for (int i = 3; i >= 0; --i)
        lbl_802F47D0[i] = 0;
    lbl_803EBB38 = 1;
    lbl_803EBB40 = 256;
    lbl_803EBB28 = 0;
    lbl_803EBB39 = 0;
    lbl_803EBB54 = 0;
    lbl_803EBB50 = 0;
    lbl_803EBB4C = 0;
    lbl_803EBB48 = 0;
    --lbl_803EBB24;
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
    if (!lbl_803EBB38)
        return -14;
    PATH_destroy(0x0F000000);
    if (PATHI_countprojecttracks(0x0F000000) == 0) {
        SNDSYS_entercritical();
        delete lbl_803EBB64;
        delete lbl_803EBB60;
        SNDSYS_leavecritical();
        lbl_803EBB60 = 0;
        lbl_803EBB68 = 0;
        lbl_803EBB64 = 0;
        lbl_803EBB38 = 0;
    }
    return lbl_803EBB38 == 0;
}

extern "C" void PATH_setallocator(Allocator *allocator, const AllocParams &params)
{
    lbl_803EBB68 = allocator;
    gPathAllocatorParams = params;
}

extern "C" void *PATHI_memalloc(int size)
{
    void *result;
    if (lbl_803EBB68)
        result = lbl_803EBB68->Alloc(size, gPathAllocatorParams);
    else
        result = 0;
    return result;
}

extern "C" void PATHI_memfree(void *p)
{
    if (lbl_803EBB68)
        lbl_803EBB68->Free(p, 0);
}

extern "C" int PATH_addmapfile(PathMapHeader_t *map)
{
    if (!lbl_803EBB38)
        PATHI_init();
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int slot = 4;
    int voice = map->mUnknownC;
    int result = -1;
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (!lbl_802F47D0[i]) {
            if (slot == 4)
                slot = i;
        } else if (lbl_802F47D0[i]->mUnknown18->mUnknownC == voice) {
            if (map->mUnknownA != lbl_802F47D0[i]->mUnknown18->mUnknownA)
                goto done;
            ++count;
        }
    }
    if (slot <= 3 && map->mUnknown0 == 0x50464478 && (map->mUnknown4 & 0xFFFF0000) == 0x05000000) {
        lbl_802F47D0[slot] = (Bank_801B3480 *)PATHI_memalloc(sizeof(Bank_801B3480));
        if (lbl_802F47D0[slot]) {
            memset(lbl_802F47D0[slot], 0, sizeof(Bank_801B3480));
            lbl_802F47D0[slot]->mUnknown18 = map;
            lbl_802F47D0[slot]->mUnknown14 = (0x10000000 << count) | (0x01000000 << voice);
            PATHI_switchproject(slot, lbl_802F47D0[slot]->mUnknown14);
            lbl_803EBB28->mUnknown1C = (short *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown14);
            lbl_803EBB28->mUnknown20 = (char *)map + lbl_803EBB28->mUnknown18->mUnknown18;
            lbl_803EBB28->mUnknown24 = (short *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown1C);
            lbl_803EBB28->mUnknown28 = (char *)map + lbl_803EBB28->mUnknown18->mUnknown20;
            lbl_803EBB28->mUnknown2C = (PathMapVariable_t *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown24);
            lbl_803EBB28->mUnknown30 = (unsigned int *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown28);
            lbl_803EBB28->mUnknown34 = (int *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown2C);
            lbl_803EBB28->mUnknown38 = (char *)map + lbl_803EBB28->mUnknown18->mUnknown30;
            lbl_803EBB28->mUnknown3C = (unsigned int *)((char *)map + lbl_803EBB28->mUnknown18->mUnknown34);
            for (int j = 15; j >= 0; --j)
                lbl_803EBB28->mUnknownC0[j] = 0;
            lbl_803EBB28->mUnknownC = 50;
            lbl_803EBB28->mUnknown10 = 10;
            result = voice;
        }
    }
done:
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" void PATH_seteventcallbacks(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int))
{
    lbl_803EBB2C = a;
    lbl_803EBB30 = b;
    lbl_803EBB34 = c;
}

extern "C" int PATH_destroy(int flags)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (PATHI_switchproject((unsigned char)i, flags)) {
            for (int j = 0; j < 24; ++j) {
                PathTrack_t *p = lbl_803EBB28->mUnknown40[j];
                // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0, as in pathcontrol.c; == 1 drops the target xori
                if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0) {
                    lbl_803EBB28->mUnknown40[j] = 0;
                    if (p->mUnknown100)
                        delete p->mUnknown100;
                    p->mUnknown100 = 0;
                    ++count;
                    PATHI_memfree(p);
                }
            }
            if (PATHI_countprojecttracks(0x01000000 << i) == 0) {
                PATHI_memfree(lbl_803EBB28);
                lbl_802F47D0[i] = 0;
            }
        }
    }
    PATHI_sortprojects();
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return count;
}

extern "C" int PATH_setvariable(int flags, const char *name, int value)
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
        if (lbl_802F47D0[i] && lbl_802F47D0[i]->mUnknown18 && (lbl_802F47D0[i]->mUnknown14 & flags)) {
            for (int j = 0; j < lbl_802F47D0[i]->mUnknown18->mUnknown11; ++j) {
                if (lbl_802F47D0[i]->mUnknown2C[j].mName[0] &&
                    !strcmp(lower, lbl_802F47D0[i]->mUnknown2C[j].mName)) {
                    result = 0;
                    lbl_802F47D0[i]->mUnknown2C[j].mValue = value;
                }
            }
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" void *PATHI_findnodedata(int flags)
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
    PathStreamRecord_t *p = (PathStreamRecord_t *)lbl_803EBB28->mUnknown3C + info->mUnknown0;
    ++index;
    if (index < lbl_803EBB28->mUnknown18->mUnknownD) {
        PathTrackInfo_t *next = PATHI_trackinfo(index);
        if (next)
            end = (PathStreamRecord_t *)lbl_803EBB28->mUnknown3C + next->mUnknown0;
    } else
        end = (PathStreamRecord_t *)((char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown18->mUnknown38);
    for (; p < end - 1; ++p) {
        float rate = (float)(int)((p[1].mByteOffset - p[0].mByteOffset) << 7) / (float)p->mDuration;
        if (!(best >= rate))
            best = rate;
    }
    return (int)(best + 0.5);
}
