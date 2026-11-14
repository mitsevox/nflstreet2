#ifndef GAME_FN_801F40F4_H
#define GAME_FN_801F40F4_H

/* Sound parameters filled in by SndFillPatchOpts and passed to SndPlayPatch. */
struct Info_801F40F4 {
    signed char mVolume;
    unsigned char mUnknown1[7];
    unsigned short mPan;
    short mSpan;
    unsigned short mUnknownC;
    char mUnknownE[10];
};

/* Two-word block passed to SndStreamQueueFile. */
struct SndStreamFile_t {
    void *mpUnknown0;
    int mUnknown4;
};

/* Status that SndStreamGetStatus writes for a playing sound. */
struct Status_801F4834 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[8];
};

extern "C" {
int SndPlayPatch(int a, int b, Info_801F40F4 *pInfo);
void SndFillPatchOpts(Info_801F40F4 *pInfo);
int SndStreamQueueFile(int handle, SndStreamFile_t *pPair, int a, int b);
void SndStreamGetStatus(int handle, Status_801F4834 *pStatus);
}

#endif
