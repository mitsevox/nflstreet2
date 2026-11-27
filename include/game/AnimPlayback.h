#ifndef GAME_ANIMPLAYBACK_H
#define GAME_ANIMPLAYBACK_H

/* 0x30-byte request cleared before use and passed to AnimPlaybackStart. */
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
int AnimPlaybackStart(Params_80096A58 *pParams);
int AnimPlaybackUpdate(int handle);
void AnimPlaybackStop(int handle);
}

#endif
