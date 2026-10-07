#ifndef GAME_TEAM_80167A8C_H
#define GAME_TEAM_80167A8C_H

#include "game/fn_800670B4.h"

struct Point_80167910 {
    float mX;
    float mY;
};

/* One 0xF04-byte state block; fn_80168908, fn_801689AC, fn_80168A14 and
   fn_80168A7C copy it whole. */
struct State_80167A8C {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned int mUnknownC;
    unsigned char mUnknown10;
    Object_800670B4 mUnknown14;
    Record_80067338 mUnknownCF8;
};

/* One of the two 0x6974-byte entries indexed by the team argument. */
struct Team_80167A8C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned int mUnknown14;
    unsigned int mUnknown18;
    unsigned int mUnknown1C;
    State_80167A8C mUnknown20;
    State_80167A8C mUnknownF24;
    State_80167A8C mUnknown1E28;
    State_80167A8C mUnknown2D2C[4];
    Point_80167910 mUnknown693C[7];
};

#endif
