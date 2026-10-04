#ifndef GAME_FN_801F40F4_H
#define GAME_FN_801F40F4_H

/* Sound parameters filled in by fn_801F40F4 and passed to fn_801F4050. */
struct Info_801F40F4 {
    signed char mVolume;
    unsigned char mUnknown1[7];
    unsigned short mPan;
    short mSpan;
    unsigned short mUnknownC;
    char mUnknownE[10];
};

/* Status that fn_801F4834 writes for a playing sound. */
struct Status_801F4834 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[8];
};

extern "C" {
int fn_801F4050(int a, int b, Info_801F40F4 *pInfo);
void fn_801F40F4(Info_801F40F4 *pInfo);
void fn_801F4834(int handle, Status_801F4834 *pStatus);
}

#endif
