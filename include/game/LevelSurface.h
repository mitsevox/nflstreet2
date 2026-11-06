#ifndef GAME_LEVELSURFACE_H
#define GAME_LEVELSURFACE_H

/* Area record returned by LevelFindArea for a position; +8 is its surface. */
struct LevelSurface_t {
    int mUnknown0;
    int mUnknown4;
    int mSurface;
};

extern "C" LevelSurface_t *LevelFindArea(float *pPos);

#endif
