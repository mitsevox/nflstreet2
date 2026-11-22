/* Sound system options and start-up (ssysinit.c): the default options the sound library starts
   from, reading and applying them, bringing the sound system up on the memory the game hands it
   and taking it down again, and the per-channel records with their speaker level tables. */

#include <string.h>

#include "engine/ssysinit.h"
#include "engine/sndbank.h"
#include "engine/ssys.h"

extern "C" {

extern unsigned char lbl_80300E9C;
extern float lbl_80300028;
extern int lbl_8030002C;
extern unsigned char lbl_803A7728;

int SNDPLATFORM_init(int mode);
int SNDPLATFORM_outputcaps(void);
int SNDPLATFORM_outputset(void);
int SNDPLATFORM_restore(int flag);
void SNDI_mutexalloc(void);
void SNDI_mutexfree(void);
void SNDI_spkrconfig(void);
void SNDI_precalcaztospkrvol(void);
void SNDI_freespkrtable(void);

int SNDSYS_getopts(SNDSYSOPTS *opts)
{
    static int gotcaps = 0;
    static int ret = 0;

    if (gotcaps == 0) {
        lbl_803A6C24.m1C.m8 = 16;
        lbl_803A6C24.m1C.m27 = 90;
        lbl_803A6C24.m1C.m18 = 1;
        lbl_803A6C24.m1C.m13 = 0;
        lbl_803A6C24.m1C.m14 = -1.0f;
        lbl_803A6C24.mCC = lbl_803A6C24.m1C;
        ret = SNDPLATFORM_outputcaps();
        gotcaps = 1;
    }
    *opts = *(SNDSYSOPTS *)&lbl_803A6C24;
    return ret;
}

int SNDSYS_setopts(SNDSYSOPTS *opts)
{
    lbl_803A6C24.m1C = opts->mParams;
    ((SNDSYSOPTS *)&lbl_803A6C24)->mMem = opts->mMem;
    SNDPLATFORM_outputset();
    lbl_803A6C24.mCC = lbl_803A6C24.m1C;
    return 0;
}

int SNDSYSI_init(void *memory, int size, int unused)
{
    int result;

    lbl_80300E9C = 'S';
    if (lbl_803A6C24.m168 != 0) {
        return 0;
    }
    memset(memory, 0, size);
    SNDMEMI_init(memory, size);
    if (lbl_803A6C24.m16C == 0) {
        result = SNDSYS_getopts((SNDSYSOPTS *)&lbl_803A6C24);
        if (result < 0) {
            return result;
        }
        SNDSYS_setopts((SNDSYSOPTS *)&lbl_803A6C24);
    }
    SNDI_randomseed(lbl_803A6C24.m1C.m4);
    SNDI_mutexalloc();
    lbl_803A6C24.m168 = 1;
    SNDSYS_entercritical();
    SNDSYSI_chanpubinit();
    lbl_803A6C24.m1D0 = (struct SndBankSlot_t *)SNDMEMI_allocz(lbl_803A6C24.m1C.m8 * 12);
    SNDSYS_leavecritical();
    lbl_80300028 = 1.0f;
    lbl_803A6C24.m170 = 0;
    lbl_803A6C24.mBankUserDataCallbackCount = 0;
    lbl_803A6C24.m16A = 0;
    lbl_803A6C24.m16B = 0;
    result = SNDPLATFORM_init(0);
    if (result < 0) {
        SNDPLATFORM_restore(0);
        SNDI_mutexfree();
        lbl_803A6C24.m168 = 0;
        return result;
    }
    lbl_803A7728 = lbl_803A6C24.m1C.m23 + lbl_803A6C24.m1C.m24;
    SNDI_spkrconfig();
    SNDI_precalcaztospkrvol();
    return 0;
}

int SNDSYS_restore(void)
{
    int result;

    if (!Snd::System::IsInited()) {
        return -14;
    }
    if (lbl_803A6C24.m1B4[0] != 0) {
        lbl_803A6C24.m1B4[0]();
    }
    if (lbl_803A6C24.m1B4[1] != 0) {
        lbl_803A6C24.m1B4[1]();
    }
    if (lbl_803A6C24.m1B4[2] != 0) {
        lbl_803A6C24.m1B4[2]();
    }
    if (lbl_803A6C24.m1C8 != 0) {
        lbl_803A6C24.m1C8();
    }
    if (lbl_803A6C24.m1C4 != 0) {
        lbl_803A6C24.m1C4();
    }
    SNDI_freespkrtable();
    if (lbl_803A6C24.m1C0 != 0) {
        lbl_803A6C24.m1C0(-1);
    }
    SNDPLATFORM_restore(0);
    SNDSYS_entercritical();
    SNDMEMI_free(lbl_803A6C24.m1CC);
    SNDMEMI_free(lbl_803A6C24.m1D0);
    SNDSYS_leavecritical();
    result = SNDMEMI_restore();
    lbl_803A6C24.m168 = 0;
    SNDI_mutexfree();
    return result;
}

int SNDSYSI_chanpubinit(void)
{
    int size;
    float *levels;
    int i;
    int j;

    size = lbl_803A6C24.m16C * 144 + lbl_8030002C * (lbl_803A6C24.m16C << 2);
    lbl_803A6C24.m1CC = (Record_803A6DF0 *)SNDMEMI_allocz(size);
    memset(lbl_803A6C24.m1CC, 0, size);
    levels = (float *)(lbl_803A6C24.m1CC + lbl_803A6C24.m16C);
    for (i = 0; i < lbl_803A6C24.m16C; i++) {
        lbl_803A6C24.m1CC[i].m64 = levels;
        for (j = 0; j < lbl_8030002C; j++) {
            lbl_803A6C24.m1CC[i].m64[j] = 1.0f;
        }
        levels += lbl_8030002C;
    }
    return 0;
}

}
