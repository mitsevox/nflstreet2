#ifndef GAME_FN_80096A58_H
#define GAME_FN_80096A58_H

/* 0x30-byte request cleared before use and passed to fn_80096A58. */
struct Params_80096A58 {
    int mUnknown0;
    char mUnknown4[8];
    int mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    char mUnknown36[4];
    unsigned short mUnknown40;
    unsigned short mUnknown42;
    char mUnknown44[4];
};

extern "C" {
int fn_80096A58(Params_80096A58 *pParams);
int fn_80096B1C(int handle);
void fn_80096D14(int handle);
}

#endif
