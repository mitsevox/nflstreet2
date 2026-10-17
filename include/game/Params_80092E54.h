#ifndef GAME_PARAMS_80092E54_H
#define GAME_PARAMS_80092E54_H

/* 236-byte request that fn_800A8FA0, fn_800AA1B0 and fn_800CFA00 build on
   the stack and pass to fn_80092E54. */
struct Params_80092E54 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC[212];
    unsigned char mUnknownE0;
    unsigned char mUnknownE1[3];
    int mUnknownE4;
    int mUnknownE8;
};

extern "C" int fn_80092E54(Params_80092E54 *pParams, void *pBuffer, int size);

#endif
