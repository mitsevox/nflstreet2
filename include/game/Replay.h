#ifndef GAME_REPLAY_H
#define GAME_REPLAY_H

#include "game/GameCamera.h"
#include "game/Object_8017886C.h"
#include "game/Object_80039F5C.h"

/* 100-byte block of the player object at +0xB54, copied whole by the
   snapshot functions ReplaySaveGameState / ReplayRestoreGameState. It ends where
   Object_80039F5C::mRatings starts. */
struct Block_80039F5C_B54 {
    int mUnknown00[25];
};

/* The 20 bytes of the player object at +0xBB8 (Object_80039F5C::mRatings). */
struct Block_80039F5C_BB8 {
    short mRatings[10];
};

/* Snapshot of both teams' player blocks and some game state, saved by
   ReplaySaveGameState and restored by ReplayRestoreGameState. */
struct ReplayGameState_t {
    Block_80039F5C_B54 mUnknown000[2][7];
    Block_80039F5C_BB8 mUnknown578[2][7];
    int mUnknown690;
    int mUnknown694;
    Point_8017886C mUnknown698;
    float mUnknown6A0;
    int mUnknown6A4[3];
    short mUnknown6B0[2];
    short mUnknown6B4;
    unsigned char mUnknown6B6;
};

/* One entry of the five-entry table at +0x148C (filled by ReplaySetEventMark). */
struct Pair_803EA368 {
    int mUnknown0;
    int mUnknown4;
};

/* One of the 60 28-byte event slots at +0xDFC, filled by ReplayEventAdd and
   looked up by mId (ReplayEventFind); ReplayEventClearAll sets every mId to -1. */
struct ReplayEvent_t {
    int mId;
    int mUnknown04;
    Vector_80039F5C mPos;
    int mFacing;
    Object_80039F5C *mpObject;
};

/* The 0x14BC-byte replay object allocated by ReplayCreate; gpReplay
   points to it. */
struct Type_803EA368 {
    ReplayGameState_t mUnknown000;
    ReplayGameState_t mUnknown6B8;
    int mUnknownD70;
    int mUnknownD74;
    int mUnknownD78;
    int mUnknownD7C;
    int mUnknownD80;
    int mUnknownD84;
    int mUnknownD88;
    int mUnknownD8C;
    int mUnknownD90;
    unsigned int mUnknownD94;
    int mUnknownD98;
    char mPadD9C[4];
    GameCamera_t *mpUnknownDA0;
    char mPadDA4[4];
    void *mUnknownDA8[20];
    char mPadDF8[4];
    ReplayEvent_t mEvents[60];
    Pair_803EA368 mUnknown148C[5];
    unsigned char mUnknown14B4;
    unsigned char mUnknown14B5;
    char mPad14B6[6];
};

extern Type_803EA368 *gpReplay;

#endif
