#ifndef GAME_CU_8002B8F8_H
#define GAME_CU_8002B8F8_H

#include "game/Camera_8013F738.h"
#include "game/Object_8017886C.h"
#include "game/Object_80039F5C.h"

/* 100-byte block of the player object at +0xB54, copied whole by the
   snapshot functions fn_8002B960 / fn_8002BAF4. It ends where
   Object_80039F5C::mRatings starts. */
struct Block_80039F5C_B54 {
    int mUnknown00[25];
};

/* The 20 bytes of the player object at +0xBB8 (Object_80039F5C::mRatings). */
struct Block_80039F5C_BB8 {
    short mRatings[10];
};

/* Snapshot of both teams' player blocks and some game state, saved by
   fn_8002B960 and restored by fn_8002BAF4. */
struct Type_8002B960 {
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

/* One entry of the five-entry table at +0x148C (filled by fn_8002D2F0). */
struct Pair_803EA368 {
    int mUnknown0;
    int mUnknown4;
};

/* One of the 60 28-byte event slots at +0xDFC, filled by fn_800310C0 and
   looked up by mId (fn_8003108C); fn_800312DC sets every mId to -1. */
struct Event_803EA368 {
    int mId;
    int mUnknown04;
    Vector_80039F5C mPos;
    int mFacing;
    Object_80039F5C *mpObject;
};

/* The 0x14BC-byte replay object allocated by fn_8002C8C0; lbl_803EA368
   points to it. */
struct Type_803EA368 {
    Type_8002B960 mUnknown000;
    Type_8002B960 mUnknown6B8;
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
    Camera_8013F738 *mpUnknownDA0;
    char mPadDA4[4];
    void *mUnknownDA8[20];
    char mPadDF8[4];
    Event_803EA368 mEvents[60];
    Pair_803EA368 mUnknown148C[5];
    unsigned char mUnknown14B4;
    unsigned char mUnknown14B5;
    char mPad14B6[6];
};

extern Type_803EA368 *lbl_803EA368;

#endif
