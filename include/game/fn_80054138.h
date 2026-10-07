#ifndef GAME_FN_80054138_H
#define GAME_FN_80054138_H

/* Area record returned by fn_80054138 for a position; +8 is its surface. */
struct Area_80054138 {
    int mUnknown0;
    int mUnknown4;
    int mSurface;
};

extern "C" Area_80054138 *fn_80054138(float *pPos);

#endif
