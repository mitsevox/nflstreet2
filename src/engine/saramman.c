/* ARAM manager (saramman.c): sets up, constrains, allocates and frees the sound system's pool
   in ARAM, the GameCube's audio memory. */

#include "engine/sndsys.h"

extern "C" {

void fn_8027981C(int count)
{
    SNDSYS_entercritical();
    lbl_803B53EC.mC = SNDMEMI_allocz(count * 8);
    SNDSYS_leavecritical();
    lbl_803B53EC.m0 = 0;
    lbl_803B53EC.m2 = count;
}

void fn_8027986C(unsigned int start, unsigned int length)
{
    lbl_803B53EC.m8 = (start + length) & ~4;
    if (start < 32) {
        start = 32;
    }
    lbl_803B53EC.m4 = start;
    if (start & 31) {
        lbl_803B53EC.m4 = (start + 31) & ~31;
    }
    lbl_803B53EC.m4 >>= 5;
    lbl_803B53EC.m8 >>= 5;
}

void fn_802798C0(void)
{
    if (lbl_803B53EC.mC != 0) {
        SNDSYS_entercritical();
        SNDMEMI_free(lbl_803B53EC.mC);
        SNDSYS_leavecritical();
        lbl_803B53EC.mC = 0;
    }
}

void fn_80279910(unsigned int *start, unsigned int *length)
{
    unsigned int old = *start;
    unsigned int lower = lbl_803B53EC.m4;
    if (old < lower) {
        *start = lower;
        *length -= lower - old;
    }
    if (*start + *length > lbl_803B53EC.m8) {
        *length = lbl_803B53EC.m8 - *start;
    }
}

}
