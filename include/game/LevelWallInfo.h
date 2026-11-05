#ifndef GAME_LEVELWALLINFO_H
#define GAME_LEVELWALLINFO_H

/* 12-byte record of the array 0x800543D4 allocates at gLevelWallInfo, one per
   record of the list at +140 of the level data. */
struct LevelWallInfo_t {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" LevelWallInfo_t *gLevelWallInfo;

#endif
