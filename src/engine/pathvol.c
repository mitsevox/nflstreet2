/* PATH track volume (pathvol.c): sets track volume, starts volume, effect-send and dry-level fades
   and applies them each tick. */

#include "engine/pathlib.h"

struct FadeCurve_801B4A24 {
    unsigned int mShape:7, mRising:1, mUnknown8:8, mTime:16;
};

extern "C" void PATH_volume(int flags, signed char volume)
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
    if (acquired) {
        if (volume > 100)
            volume = 100;
        if (volume < 0)
            volume = 0;
        if (flags == -1)
            volscale = volume;
        for (int i = 0; i < 4; ++i) {
            if (PATHI_switchproject(i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    PathTrack_t *p = pfstate->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0, as in pathcontrol.c
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0) {
                        p->mUnknown2 = volume;
                        if (p->mUnknown1A & 0x80)
                            p->mUnknown100->vfn_13((signed char)p->mUnknown3 * volume / 100);
                    }
                }
            }
        }
        pfstate = 0;
        --pflock;
    }
}

extern "C" void PATH_fade(int flags, int a, int b, int c)
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
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0, as in pathcontrol.c
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0)
                        PATHI_fade(p, a, b, c);
                }
            }
        }
        pfstate = 0;
        --pflock;
    }
}

extern "C" void fn_801B4824(PathTrack_t *p, int value)
{
    p->mUnknown3 = value;
    if (p->mUnknown1A & 0x80)
        p->mUnknown100->vfn_13((signed char)value * (signed char)p->mUnknown2 / 100);
}

extern "C" void PATHI_fade(PathTrack_t *p, int a, int b, int c)
{
    p->mUnknown10 = gPathMilliseconds;
    p->mUnknown19 = c;
    p->mUnknown14 = b;
    p->mUnknown18 = (float)p->mUnknown100->GetVolume();
    p->mUnknown1A = a;
    p->mUnknown3 = (float)a;
}

extern "C" void fn_801B4960(PathTrack_t *p, int a, int b, int c)
{
    p->mUnknown1C = gPathMilliseconds;
    p->mUnknown20 = b;
    p->mUnknown25 = c;
    p->mUnknown24 = p->mUnknown100->GetFXSendLevel(0);
    p->mUnknown26 = a;
}

extern "C" void fn_801B49C4(PathTrack_t *p, int a, int b, int c)
{
    p->mUnknown28 = gPathMilliseconds;
    p->mUnknown2C = b;
    p->mUnknown31 = c;
    p->mUnknown30 = p->mUnknown100->GetDryLevel();
    p->mUnknown32 = a;
}

extern "C" void PATHI_setfadevolume(PathTrack_t *p)
{
    FadeCurve_801B4A24 curve;
    float delta = (float)p->mUnknown1A - (float)p->mUnknown18;
    float factor = -1.0f;
    curve.mTime = p->mUnknown14;
    curve.mShape = p->mUnknown19;
    curve.mRising = delta >= 0.0f;
    float t = (float)(gPathMilliseconds - p->mUnknown10) / (float)curve.mTime;
    if (!(t < 1.0f)) {
        p->mUnknown100->vfn_13((signed char)p->mUnknown3 * (signed char)p->mUnknown2 / 100);
        p->mUnknown10 = 0;
        p->mUnknown3 = p->mUnknown1A;
        p->mUnknown18 = -1;
        p->mUnknown19 = -1;
        p->mUnknown1A = -1;
    } else {
        if (curve.mRising)
            t = 1.0f - t;
        switch (curve.mShape) {
        case 2:
            t = t * t;
        case 1:
            factor = 1.0f - t;
            break;
        case 3:
            factor = 1.0f / t * 0.04f;
            break;
        }
        float base = p->mUnknown18;
        if (p->mUnknown1A < p->mUnknown18)
            base = p->mUnknown1A;
        if (!(delta >= 0.0f))
            delta = -delta;
        if (factor < 0.0f || factor > 1.0f)
            return;
        p->mUnknown100->vfn_13((int)((delta * factor + base) * (float)(signed char)p->mUnknown2 * 0.01f));
    }
}

extern "C" void PATHI_setsfxfadevolume(PathTrack_t *p)
{
    FadeCurve_801B4A24 curve;
    float delta = (float)p->mUnknown26 - (float)p->mUnknown24;
    float factor = -1.0f;
    curve.mTime = p->mUnknown20;
    curve.mShape = p->mUnknown25;
    curve.mRising = delta >= 0.0f;
    float t = (float)(gPathMilliseconds - p->mUnknown1C) / (float)curve.mTime;
    if (!(t < 1.0f)) {
        p->mUnknown100->vfn_17(p->mUnknown8.bits.mUnknown1, p->mUnknown26);
        p->mUnknown24 = -1;
        p->mUnknown1C = 0;
        p->mUnknown25 = -1;
        p->mUnknown26 = -1;
    } else {
        if (curve.mRising)
            t = 1.0f - t;
        switch (curve.mShape) {
        case 2:
            t = t * t;
        case 1:
            factor = 1.0f - t;
            break;
        case 3:
            factor = 1.0f / t * 0.04f;
            break;
        }
        float base = p->mUnknown24;
        if (p->mUnknown26 < p->mUnknown24)
            base = p->mUnknown26;
        if (!(delta >= 0.0f))
            delta = -delta;
        if (factor < 0.0f || factor > 1.0f)
            return;
        p->mUnknown100->vfn_17(p->mUnknown8.bits.mUnknown1, (int)(delta * factor + base));
    }
}

extern "C" void PATHI_setdrylevelfadevolume(PathTrack_t *p)
{
    FadeCurve_801B4A24 curve;
    float delta = (float)p->mUnknown32 - (float)p->mUnknown30;
    float factor = -1.0f;
    curve.mTime = p->mUnknown2C;
    curve.mShape = p->mUnknown31;
    curve.mRising = delta >= 0.0f;
    float t = (float)(gPathMilliseconds - p->mUnknown28) / (float)curve.mTime;
    if (!(t < 1.0f)) {
        p->mUnknown100->vfn_15(p->mUnknown32);
        p->mUnknown30 = -1;
        p->mUnknown28 = 0;
        p->mUnknown31 = -1;
        p->mUnknown32 = -1;
    } else {
        if (curve.mRising)
            t = 1.0f - t;
        switch (curve.mShape) {
        case 2:
            t = t * t;
        case 1:
            factor = 1.0f - t;
            break;
        case 3:
            factor = 1.0f / t * 0.04f;
            break;
        }
        float base = p->mUnknown30;
        if (p->mUnknown32 < p->mUnknown30)
            base = p->mUnknown32;
        if (!(delta >= 0.0f))
            delta = -delta;
        if (factor < 0.0f || factor > 1.0f)
            return;
        p->mUnknown100->vfn_15((int)(delta * factor + base));
    }
}
