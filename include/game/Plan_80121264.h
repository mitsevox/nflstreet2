#ifndef GAME_PLAN_80121264_H
#define GAME_PLAN_80121264_H

/* 48-byte entry of Plan_80121264; the array fills +0 to +1440. */
struct Entry_80120E98 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[20];
    int mUnknown36;
    char mUnknown40[8];
};

/* 32-byte entry of Plan_80121264; the array fills +1444 to +2372. */
struct Entry_801230B8 {
    char mUnknown0[16];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
};

/* 2376-byte record cleared and filled by fn_80121264 (fn_801231E4 keeps one
   on its stack). */
struct Plan_80121264 {
    Entry_80120E98 mUnknown0[30];
    int mUnknown1440;
    Entry_801230B8 mUnknown1444[29];
    unsigned int mUnknown2372;
};

#endif
