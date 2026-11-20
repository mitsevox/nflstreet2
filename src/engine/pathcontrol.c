/* PATH track control (pathcontrol.c): sets a control value on, pauses, queries the status of and
   stops the music tracks a game request selects by project and track mask. */

#include "engine/pathlib.h"

extern "C" int PATH_control(int flags, int value)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    if ((unsigned int)value <= 127) {
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0)
                        p->mUnknown1 = value;
                }
            }
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return 0;
}

extern "C" void PATH_pause(int flags, unsigned char value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (acquired) {
        if (flags == -1)
            lbl_803EBB39 = value;
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480((unsigned char)i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0) {
                        p->mUnknown100->vfn_05(value);
                        p->mUnknown8.bits.flag40 = value;
                    }
                }
            }
        }
        lbl_803EBB28 = 0;
        --lbl_803EBB24;
    }
}

extern "C" int PATH_status(int flags, PathfinderStatus_t *info)
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
    int result = -8;
    Node_801B3FE0 *p = fn_801B4174(flags);
    if (p && fn_801B34DC(flags))
        result = PATHI_status(p, info);
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" int PATHI_status(Node_801B3FE0 *p, void *info)
{
    int result;
    if (p->mUnknown100)
        result = p->mUnknown100->vfn_07(info);
    else
        result = -39;
    return result;
}

extern "C" void PATH_stop(int flags)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (acquired) {
        for (int i = 0; i < 4; ++i) {
            if (fn_801B3480(i, flags)) {
                for (int j = 0; j < 24; ++j) {
                    Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1 == 0; == 1 drops the target xori
                    if (p && ((((unsigned int)flags >> j) ^ 1) & 1) == 0)
                        PATHI_stop(p);
                }
            }
        }
        lbl_803EBB28 = 0;
        --lbl_803EBB24;
    }
}

extern "C" int PATHI_stop(Node_801B3FE0 *p)
{
    p->mUnknown100->vfn_04();
    p->mUnknown4 = -1;
    p->mUnknown8.word |= 0xF80;
    return 0;
}
